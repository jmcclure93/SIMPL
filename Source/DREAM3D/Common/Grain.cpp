/* ============================================================================
 * Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2010, Dr. Michael A. Grober (US Air Force Research Laboratories
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
 * Neither the name of Michael A. Jackson nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
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
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "Grain.h"
#include <iostream>

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Grain::Grain() :
nucleus(0),
active(0),
numvoxels(0),
numneighbors(0),
newgrainname(0),
gotcontainedmerged(0),
gottwinmerged(0),
gotcolonymerged(0),
surfacegrain(0),
twinnewnumber(0),
colonynewnumber(-1),
slipsystem(0),
packquality(0.0),
phase(0),
centroidx(0.0),
centroidy(0.0),
centroidz(0.0),
aspectratio1(0.0),
aspectratio2(0.0),
Ixx(0.0),
Iyy(0.0),
Izz(0.0),
Ixy(0.0),
Iyz(0.0),
Ixz(0.0),
omega3(0.0),
averageimagequality(0.0),
averagemisorientation(0.0),
kernelmisorientation(10000.0),
red(0.0),
green(0.0),
blue(0.0),
schmidfactor(0.0),
euler1(0.0),
euler2(0.0),
euler3(0.0),
axiseuler1(0.0),
axiseuler2(0.0),
axiseuler3(0.0),
volume(0.0),
equivdiameter(0.0),
neigherror(0.0),
radius1(0.0),
radius2(0.0),
radius3(0.0),
lowanglefraction(0.0)
{
  neighborlist = IntVectorType(new std::vector<int>(0) );
  neighborsurfarealist = FloatVectorType(new std::vector<float>(0) );

  voxellist = NULL; //new std::vector<int>;
  columnlist = NULL; //new std::vector<int>;
  rowlist = NULL; //new std::vector<int>;
  planelist = NULL; //new std::vector<int>;
  misorientationlist = NULL; //new std::vector<float>;

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Grain::deepCopy(Grain::Pointer grain)
{
  if (grain.get() == this) { return; } // The pointers are the same just return
  nucleus = grain->nucleus;
  active = grain->active ;
  numvoxels = grain->numvoxels ;
  numneighbors = grain->numneighbors ;
  newgrainname = grain->newgrainname ;
  gotcontainedmerged = grain->gotcontainedmerged ;
  gottwinmerged = grain->gottwinmerged ;
  gotcolonymerged = grain->gotcolonymerged ;
  surfacegrain = grain->surfacegrain ;
  twinnewnumber = grain->twinnewnumber;
  colonynewnumber = grain->colonynewnumber;
  slipsystem = grain->slipsystem;
  packquality = grain->packquality;

  centroidx = grain->centroidx ;
  centroidy = grain->centroidy ;
  centroidz = grain->centroidz ;
  Ixx = grain->Ixx ;
  Iyy = grain->Iyy ;
  Izz = grain->Izz ;
  Ixy = grain->Ixy;
  Iyz = grain->Iyz ;
  Ixz = grain->Ixz ;
  omega3 = grain->omega3 ;
  averageimagequality = grain->averageimagequality;
  averagemisorientation = grain->averagemisorientation ;
  kernelmisorientation = grain->kernelmisorientation;
  red = grain->red ;
  green = grain->green ;
  blue = grain->blue ;

  COPY_ARRAY_3(IPF, grain);
  schmidfactor = grain->schmidfactor ;
  euler1 = grain->euler1 ;
  euler2 = grain->euler2 ;
  euler3 = grain->euler3 ;
  axiseuler1 = grain->axiseuler1 ;
  axiseuler2 = grain->axiseuler2 ;
  axiseuler3 = grain->axiseuler3 ;
  volume = grain->volume ;
  equivdiameter = grain->equivdiameter ;
  neigherror = grain->neigherror ;
  radius1 = grain->radius1 ;
  radius2 = grain->radius2 ;
  radius3 = grain->radius3 ;
  lowanglefraction = grain->lowanglefraction;
  COPY_ARRAY_5(avg_quat, grain);
  COPY_ARRAY_3(neighbordistfunc, grain);

  // These are shared pointers
  DEEP_COPY_SHARED_VECTOR(neighborlist, grain, IntVectorType, int)
  DEEP_COPY_SHARED_VECTOR(neighborsurfarealist, grain, FloatVectorType, float)

  // These are Normal pointers
  if (NULL != voxellist)
  {
    delete voxellist;
    delete columnlist;
    delete rowlist;
    delete planelist;
  }
  if (NULL != misorientationlist)
  {
    delete misorientationlist;
  }

  if (NULL != grain->voxellist)
  {
    voxellist = new std::vector<int>(0);
    voxellist->assign(grain->voxellist->begin(), grain->voxellist->end());
  }
  if (NULL != grain->columnlist) {
    columnlist = new std::vector<int>(0);
    columnlist->assign(grain->columnlist->begin(), grain->columnlist->end());
  }
  if (NULL != grain->rowlist)
  {
    rowlist = new std::vector<int>(0);
    rowlist->assign(grain->rowlist->begin(), grain->rowlist->end());
  }
  if (NULL != grain->planelist) {
    planelist = new std::vector<int>(0);
    planelist->assign(grain->planelist->begin(), grain->planelist->end());
  }

  if (NULL != grain->misorientationlist)
  {
    misorientationlist = new std::vector<float>(0);
    misorientationlist->assign(grain->misorientationlist->begin(), grain->misorientationlist->end());
  }
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Grain::~Grain()
{

  if (NULL != voxellist)
  {
    delete voxellist;
  }
  if (NULL != columnlist)
    delete columnlist;
  if(NULL != rowlist)
    delete rowlist;

  if (NULL != planelist) {
    delete planelist;
  }
  if (NULL != misorientationlist)
  {
    delete misorientationlist;
  }

}







