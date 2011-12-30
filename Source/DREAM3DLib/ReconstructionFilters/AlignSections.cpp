/* ============================================================================
 * Copyright (c) 2011 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2011 Dr. Michael A. Groeber (US Air Force Research Laboratories)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Michael A. Groeber, Michael A. Jackson, the US Air Force,
 * BlueQuartz Software nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  This code was written under United States Air Force Contract number
 *                           FA8650-07-D-5800
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "AlignSections.h"

#include "DREAM3DLib/Common/Constants.h"
#include "DREAM3DLib/Common/DREAM3DMath.h"
#include "DREAM3DLib/Common/OrientationMath.h"
#include "DREAM3DLib/Common/DREAM3DRandom.h"

#include "DREAM3DLib/OrientationOps/CubicOps.h"
#include "DREAM3DLib/OrientationOps/HexagonalOps.h"
#include "DREAM3DLib/OrientationOps/OrthoRhombicOps.h"

#define ERROR_TXT_OUT 1
#define ERROR_TXT_OUT1 1

const static float m_pi = M_PI;

#define NEW_SHARED_ARRAY(var, type, size)\
  boost::shared_array<type> var##Array(new type[size]);\
  type* var = var##Array.get();

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AlignSections::AlignSections() :
        AbstractFilter()
{
  Seed = MXA::getMilliSeconds();

  m_HexOps = HexagonalOps::New();
  m_OrientationOps.push_back(m_HexOps.get());
  m_CubicOps = CubicOps::New();
  m_OrientationOps.push_back(m_CubicOps.get());
  m_OrthoOps = OrthoRhombicOps::New();
  m_OrientationOps.push_back(m_OrthoOps.get());


  graincounts = NULL;
  INIT_DataArray(m_GrainCounts, int);

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AlignSections::~AlignSections()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void AlignSections::execute()
{
  setErrorCondition(0);
  if(m_alignmeth == DREAM3D::Reconstruction::MutualInformation)
  {
    form_grains_sections();
  }

  align_sections();
  if (getErrorCondition() < 0 )
  {
    return;
  }

  if(m_alignmeth == DREAM3D::Reconstruction::MutualInformation)
  {
    //    threshold_points();
  }

  // If there is an error set this to something negative and also set a message
  notify("AlignSections Completed", 0, Observable::UpdateProgressMessage);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void AlignSections::align_sections()
{
  DataContainer* m = getDataContainer();
  if (NULL == m)
  {
    setErrorCondition(-1);
    std::stringstream ss;
    ss << getNameOfClass() << " DataContainer was NULL";
    setErrorMessage(ss.str());
    return;
  }
  int64_t totalPoints = m->totalPoints();

    int32_t* grain_indicies = m->getVoxelDataSizeCheck<int32_t, Int32ArrayType, AbstractFilter>(DREAM3D::VoxelData::GrainIds, totalPoints, this);
  if (NULL == grain_indicies) { return; }
    int32_t* phases = m->getVoxelDataSizeCheck<int32_t, Int32ArrayType, AbstractFilter>(DREAM3D::VoxelData::Phases, totalPoints, this);
  if (NULL == phases) { return; }
    float* euler1s = m->getVoxelDataSizeCheck<float, FloatArrayType, AbstractFilter>(DREAM3D::VoxelData::Euler1, totalPoints, this);
  if (NULL == euler1s) { return; }
  float* euler2s = m->getVoxelDataSizeCheck<float, FloatArrayType, AbstractFilter>(DREAM3D::VoxelData::Euler2, totalPoints, this);
  if (NULL == euler2s) { return; }
  float* euler3s = m->getVoxelDataSizeCheck<float, FloatArrayType, AbstractFilter>(DREAM3D::VoxelData::Euler3, totalPoints, this);
  if (NULL == euler3s) { return; }
  bool* goodVoxels = m->getVoxelDataSizeCheck<bool, BoolArrayType, AbstractFilter>(DREAM3D::VoxelData::GoodVoxels, totalPoints, this);
  if (NULL == goodVoxels) { return; }
  float* quats = m->getVoxelDataSizeCheck<float, FloatArrayType, AbstractFilter>(DREAM3D::VoxelData::Quats, (totalPoints*5), this);
  if (NULL == quats) { return; }

  float disorientation = 0;
  float mindisorientation = 100000000;
  float **mutualinfo12 = NULL;
  float *mutualinfo1 = NULL;
  float *mutualinfo2 = NULL;
  int graincount1, graincount2;
  int newxshift = 0;
  int newyshift = 0;
  int oldxshift = 0;
  int oldyshift = 0;
  float count = 0;
  int slice = 0;
  int xspot, yspot;
  float w;
  float n1, n2, n3;
  float q1[5];
  float q2[5];
  int refgnum, curgnum;
  int refposition = 0;
  int curposition = 0;
  int position;
  int tempposition;
  Ebsd::CrystalStructure phase1, phase2;

  int** shifts = AlignSections::Allocate2DArray<int>(m->getZPoints(), 2);
  for (size_t a = 0; a < m->getZPoints(); a++)
  {
    for (int b = 0; b < 2; b++)
    {
      shifts[a][b] = 0;
    }
  }

  int** misorients = AlignSections::Allocate2DArray<int>(m->getXPoints(), m->getYPoints());
 // int** misorients = new int *[m->getXPoints()];
  for (size_t a = 0; a < m->getXPoints(); a++)
  {
//    misorients[a] = new int[m->getYPoints()];
    for (size_t b = 0; b < m->getYPoints(); b++)
    {
      misorients[a][b] = 0;
    }
  }
  for (size_t iter = 1; iter < m->getZPoints(); iter++)
  {

    mindisorientation = 100000000;
    slice = (m->getZPoints() - 1) - iter;
    if(m_alignmeth == DREAM3D::Reconstruction::MutualInformation)
    {
      graincount1 = graincounts[slice];
      graincount2 = graincounts[slice + 1];
      mutualinfo12 = AlignSections::Allocate2DArray<float>(graincount1, graincount2);
//      mutualinfo12 = new float *[graincount1];
      mutualinfo1 = new float[graincount1];
      mutualinfo2 = new float[graincount2];

      for (int a = 0; a < graincount1; a++)
      {
        mutualinfo1[a] = 0.0f;
      //  mutualinfo12[a] = new float[graincount2];
        for (int b = 0; b < graincount2; b++)
        {
          mutualinfo12[a][b] = 0.0f;
          mutualinfo2[b] = 0.0f;
        }
      }
    }
    oldxshift = -1;
    oldyshift = -1;
    newxshift = 0;
    newyshift = 0;
    for (size_t a = 0; a < m->getXPoints(); a++)
    {
      for (size_t b = 0; b < m->getYPoints(); b++)
      {
        misorients[a][b] = 0;
      }
    }
    while (newxshift != oldxshift || newyshift != oldyshift)
    {
      oldxshift = newxshift;
      oldyshift = newyshift;
      for (int j = -3; j < 4; j++)
      {
        for (int k = -3; k < 4; k++)
        {
          disorientation = 0;
          count = 0;
          if(misorients[k + oldxshift + size_t(m->getXPoints() / 2)][j + oldyshift + size_t(m->getYPoints() / 2)] == 0 && abs(k + oldxshift) < (m->getXPoints() / 2)
              && (j + oldyshift) < (m->getYPoints() / 2))
          {
            for (size_t l = 0; l < m->getYPoints(); l = l + 4)
            {
              for (size_t n = 0; n < m->getXPoints(); n = n + 4)
              {
                count++;
                if((l + j + oldyshift) >= 0 && (l + j + oldyshift) < m->getYPoints() && (n + k + oldxshift) >= 0 && (n + k + oldxshift) < m->getXPoints())
                {
                  refposition = ((slice + 1) * m->getXPoints() * m->getYPoints()) + (l * m->getXPoints()) + n;
                  curposition = (slice * m->getXPoints() * m->getYPoints()) + ((l + j + oldyshift) * m->getXPoints()) + (n + k + oldxshift);
                  refgnum = grain_indicies[refposition];
                  curgnum = grain_indicies[curposition];
                  if(m_alignmeth == DREAM3D::Reconstruction::MutualInformation)
                  {
                    if(curgnum >= 0 && refgnum >= 0)
                    {
                      mutualinfo12[curgnum][refgnum]++;
                      mutualinfo1[curgnum]++;
                      mutualinfo2[refgnum]++;
                    }
                  }
                  else if(m_alignmeth == DREAM3D::Reconstruction::Misorientation)
                  {
                    if(goodVoxels[refposition] == true && goodVoxels[curposition] == true)
                    {
                      w = 10000.0;
                      if(phases[refposition] > 0 && phases[curposition] > 0)
                      {
                        q1[1] = quats[refposition * 5 + 1];
                        q1[2] = quats[refposition * 5 + 2];
                        q1[3] = quats[refposition * 5 + 3];
                        q1[4] = quats[refposition * 5 + 4];
                        phase1 = m->crystruct[phases[refposition]];
                        q2[1] = quats[curposition * 5 + 1];
                        q2[2] = quats[curposition * 5 + 2];
                        q2[3] = quats[curposition * 5 + 3];
                        q2[4] = quats[curposition * 5 + 4];
                        phase2 = m->crystruct[phases[curposition]];
                        if(phase1 == phase2) w = m_OrientationOps[phase1]->getMisoQuat(q1, q2, n1, n2, n3);
                      }
                      if(w > m_misorientationtolerance) disorientation++;
                    }
                    if(goodVoxels[refposition] == true && goodVoxels[curposition] == false) disorientation++;
                    if(goodVoxels[refposition] == false && goodVoxels[curposition] == true) disorientation++;
                  }
                  else if(m_alignmeth == DREAM3D::Reconstruction::OuterBoundary)
                  {
                    if(grain_indicies[refposition] != grain_indicies[curposition]) disorientation++;
                  }
                }
                else
                {
                  if(m_alignmeth == DREAM3D::Reconstruction::MutualInformation)
                  {
                    mutualinfo12[0][0]++;
                    mutualinfo1[0]++;
                    mutualinfo2[0]++;
                  }
                }
              }
            }
            if(m_alignmeth == DREAM3D::Reconstruction::MutualInformation)
            {
              float ha = 0;
              float hb = 0;
              float hab = 0;
              for (int b = 0; b < graincount1; b++)
              {
                mutualinfo1[b] = mutualinfo1[b] / float(count);
                if(mutualinfo1[b] != 0) ha = ha + mutualinfo1[b] * log(mutualinfo1[b]);
              }
              for (int c = 0; c < graincount2; c++)
              {
                mutualinfo2[c] = mutualinfo2[c] / float(count);
                if(mutualinfo2[c] != 0) hb = hb + mutualinfo2[c] * log(mutualinfo2[c]);
              }
              for (int b = 0; b < graincount1; b++)
              {
                for (int c = 0; c < graincount2; c++)
                {
                  mutualinfo12[b][c] = mutualinfo12[b][c] / float(count);
                  if(mutualinfo12[b][c] != 0) hab = hab + mutualinfo12[b][c] * log(mutualinfo12[b][c]);
                  float value = 0;
                  if(mutualinfo1[b] > 0 && mutualinfo2[c] > 0) value = (mutualinfo12[b][c] / (mutualinfo1[b] * mutualinfo2[c]));
                  if(value != 0) disorientation = disorientation + (mutualinfo12[b][c] * log(value));
                }
              }
              for (int b = 0; b < graincount1; b++)
              {
                for (int c = 0; c < graincount2; c++)
                {
                  mutualinfo12[b][c] = 0;
                  mutualinfo1[b] = 0;
                  mutualinfo2[c] = 0;
                }
              }
              disorientation = 1.0 / disorientation;
            }
            if(m_alignmeth == DREAM3D::Reconstruction::OuterBoundary || m_alignmeth == DREAM3D::Reconstruction::Misorientation) disorientation = disorientation
                / count;
            misorients[k + oldxshift + int(m->getXPoints() / 2)][j + oldyshift + int(m->getYPoints() / 2)] = disorientation;
            if(disorientation < mindisorientation)
            {
              newxshift = k + oldxshift;
              newyshift = j + oldyshift;
              mindisorientation = disorientation;
            }
          }
        }
      }
    }
    shifts[iter][0] = shifts[iter - 1][0] + newxshift;
    shifts[iter][1] = shifts[iter - 1][1] + newyshift;
    if(m_alignmeth == DREAM3D::Reconstruction::MutualInformation)
    {
      AlignSections::Deallocate2DArray<float>(graincount1, graincount2, mutualinfo12);
      delete [] mutualinfo1;
      delete [] mutualinfo2;
      mutualinfo1 = NULL;
      mutualinfo2 = NULL;
      mutualinfo12 = NULL;
    }
  }
  for (size_t iter = 1; iter < m->getZPoints(); iter++)
  {
    slice = (m->getZPoints() - 1) - iter;
    for (size_t l = 0; l < m->getYPoints(); l++)
    {
      for (size_t n = 0; n < m->getXPoints(); n++)
      {
        if(shifts[iter][1] >= 0) yspot = l;
        if(shifts[iter][0] >= 0) xspot = n;
        if(shifts[iter][1] < 0) yspot = m->getYPoints() - 1 - l;
        if(shifts[iter][0] < 0) xspot = m->getXPoints() - 1 - n;
        position = (slice * m->getXPoints() * m->getYPoints()) + (yspot * m->getXPoints()) + xspot;
        tempposition = (slice * m->getXPoints() * m->getYPoints()) + ((yspot + shifts[iter][1]) * m->getXPoints()) + (xspot + shifts[iter][0]);
        if((yspot + shifts[iter][1]) >= 0 && (yspot + shifts[iter][1]) <= m->getYPoints() - 1 && (xspot + shifts[iter][0]) >= 0
            && (xspot + shifts[iter][0]) <= m->getXPoints() - 1)
        {
          euler1s[position] = euler1s[tempposition];
          euler2s[position] = euler2s[tempposition];
          euler3s[position] = euler3s[tempposition];
          quats[position * 5 + 0] = quats[tempposition * 5 + 0];
          quats[position * 5 + 1] = quats[tempposition * 5 + 1];
          quats[position * 5 + 2] = quats[tempposition * 5 + 2];
          quats[position * 5 + 3] = quats[tempposition * 5 + 3];
          quats[position * 5 + 4] = quats[tempposition * 5 + 4];
          goodVoxels[position] = goodVoxels[tempposition];
          phases[position] = phases[tempposition];
          grain_indicies[position] = grain_indicies[tempposition];
        }
        if((yspot + shifts[iter][1]) < 0 || (yspot + shifts[iter][1]) > m->getYPoints() - 1 || (xspot + shifts[iter][0]) < 0
            || (xspot + shifts[iter][0]) > m->getXPoints() - 1)
        {
          euler1s[position] = 0.0;
          euler2s[position] = 0.0;
          euler3s[position] = 0.0;
          quats[position * 5 + 0] = 0.0;
          quats[position * 5 + 1] = 0.0;
          quats[position * 5 + 2] = 0.0;
          quats[position * 5 + 3] = 0.0;
          quats[position * 5 + 4] = 1.0;
          goodVoxels[position] = false;
          phases[position] = 0;
          grain_indicies[position] = 0;
        }
      }
    }
  }


#if 1
  Deallocate2DArray(m->getZPoints(), 2, shifts);
  Deallocate2DArray(m->getXPoints(), m->getYPoints(), misorients);

#else
  // Clean up the memory
  for (int a = 0; a < m->getZPoints(); a++)
  {
    delete[] shifts[a];
  }
  for (int a = 0; a < m->getXPoints(); a++)
  {
    delete[] misorients[a];
  }
  delete[] shifts;
  delete[] misorients;
#endif
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void AlignSections::form_grains_sections()
{
  DREAM3D_RANDOMNG_NEW()
  DataContainer* m = getDataContainer();

  int64_t totalPoints = m->totalPoints();
    int32_t* grain_indicies = m->getVoxelDataSizeCheck<int32_t, Int32ArrayType, AbstractFilter>(DREAM3D::VoxelData::GrainIds, totalPoints, this);
  if (NULL == grain_indicies) { return; }
    int32_t* phases = m->getVoxelDataSizeCheck<int32_t, Int32ArrayType, AbstractFilter>(DREAM3D::VoxelData::Phases, totalPoints, this);
  if (NULL == phases) { return; }
  bool* goodVoxels = m->getVoxelDataSizeCheck<bool, BoolArrayType, AbstractFilter>(DREAM3D::VoxelData::GoodVoxels, totalPoints, this);
  if (NULL == goodVoxels) { return; }
  float* quats = m->getVoxelDataSizeCheck<float, FloatArrayType, AbstractFilter>(DREAM3D::VoxelData::Quats, (totalPoints*5), this);
  if (NULL == quats) { return; }

  int point = 0;
  int seed = 0;
  int noseeds = 0;
  int graincount = 1;
  int neighbor;
  // int currentpoint;
  float q1[5];
  float q2[5];
//  float qs[5];
  float w;
  float n1;
  float n2;
  float n3;
  int randx = 0;
  int randy = 0;
  int good = 0;
  int x, y, z;
  int col, row;
  size_t size = 0;
  size_t initialVoxelsListSize = 1000;

  graincounts = m_GrainCounts->WritePointer(0, m->getZPoints());

  std::vector<int> voxelslist(initialVoxelsListSize, -1);
  int neighpoints[8];
  neighpoints[0] = -m->getXPoints() - 1;
  neighpoints[1] = -m->getXPoints();
  neighpoints[2] = -m->getXPoints() + 1;
  neighpoints[3] = -1;
  neighpoints[4] = 1;
  neighpoints[5] = m->getXPoints() - 1;
  neighpoints[6] = m->getXPoints();
  neighpoints[7] = m->getXPoints() + 1;
  Ebsd::CrystalStructure phase1, phase2;
  for (size_t slice = 0; slice < m->getZPoints(); slice++)
  {
    graincount = 1;
    noseeds = 0;
    while (noseeds == 0)
    {
      seed = -1;
      randx = int(float(rg.genrand_res53()) * float(m->getXPoints()));
      randy = int(float(rg.genrand_res53()) * float(m->getYPoints()));
      for (size_t j = 0; j < m->getYPoints(); ++j)
      {
        for (size_t i = 0; i < m->getXPoints(); ++i)
        {
          x = randx + i;
          y = randy + j;
          z = slice;
          if(x > m->getXPoints() - 1) x = x - m->getXPoints();
          if(y > m->getYPoints() - 1) y = y - m->getYPoints();
          point = (z * m->getXPoints() * m->getYPoints()) + (y * m->getXPoints()) + x;
          if(goodVoxels[point] == true && grain_indicies[point] == -1 && phases[point] > 0)
          {
            seed = point;
          }
          if(seed > -1) break;
        }
        if(seed > -1) break;
      }
      if(seed == -1) noseeds = 1;
      if(seed >= 0)
      {
        size = 0;
        grain_indicies[seed] = graincount;
        voxelslist[size] = seed;
        size++;
//        qs[0] = 0;
//        qs[1] = quats[seed * 5 + 1];
//        qs[2] = quats[seed * 5 + 2];
//        qs[3] = quats[seed * 5 + 3];
//        qs[4] = quats[seed * 5 + 4];
        for (size_t j = 0; j < size; ++j)
        {
          int currentpoint = voxelslist[j];
          col = currentpoint % m->getXPoints();
          row = (currentpoint / m->getXPoints()) % m->getYPoints();
          q1[0] = 0;
          q1[1] = quats[currentpoint * 5 + 1];
          q1[2] = quats[currentpoint * 5 + 2];
          q1[3] = quats[currentpoint * 5 + 3];
          q1[4] = quats[currentpoint * 5 + 4];
          phase1 = m->crystruct[phases[currentpoint]];
          for (int i = 0; i < 8; i++)
          {
            good = 1;
            neighbor = currentpoint + neighpoints[i];
            if((i == 0 || i == 1 || i == 2) && row == 0) good = 0;
            if((i == 5 || i == 6 || i == 7) && row == (m->getYPoints() - 1)) good = 0;
            if((i == 0 || i == 3 || i == 5) && col == 0) good = 0;
            if((i == 2 || i == 4 || i == 7) && col == (m->getXPoints() - 1)) good = 0;
            if(good == 1 && grain_indicies[neighbor] <= 0 && phases[neighbor] > 0)
            {
              w = 10000.0;
              q2[0] = 0;
              q2[1] = quats[neighbor * 5 + 1];
              q2[2] = quats[neighbor * 5 + 2];
              q2[3] = quats[neighbor * 5 + 3];
              q2[4] = quats[neighbor * 5 + 4];
              phase2 = m->crystruct[phases[neighbor]];
              if(phase1 == phase2) w = m_OrientationOps[phase1]->getMisoQuat(q1, q2, n1, n2, n3);
              if(w < m_misorientationtolerance)
              {
                grain_indicies[neighbor] = graincount;
                voxelslist[size] = neighbor;
                size++;
                if(size >= voxelslist.size()) voxelslist.resize(size + initialVoxelsListSize, -1);
              }
            }
          }
        }
        voxelslist.erase(std::remove(voxelslist.begin(), voxelslist.end(), -1), voxelslist.end());
        graincount++;
        voxelslist.clear();
        voxelslist.resize(initialVoxelsListSize, -1);
      }
    }
    graincounts[slice] = graincount;
  }
}

