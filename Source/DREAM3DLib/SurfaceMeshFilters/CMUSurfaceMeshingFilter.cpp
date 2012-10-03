/* ============================================================================
 * Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
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

 //
 //  This code was written under United States Air Force Contract number
 //                           FA8650-07-D-5800
 //
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "CMUSurfaceMeshingFilter.h"

#include "MXA/Utilities/MXADir.h"
#include "MXA/Utilities/MXAFileInfo.h"
#include "MXA/Common/MXAMath.h"


#include "SurfaceMeshStructs.h"
// #include "SurfaceMeshGeneralMCABoundedMulti.h"


#ifndef M_PI
#define M_PI 3.14159265
#endif

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
CMUSurfaceMeshingFilter::CMUSurfaceMeshingFilter() :
AbstractFilter(),
m_GrainIdsArrayName(DREAM3D::CellData::GrainIds),
m_VoxelCoordsArrayName(DREAM3D::CellData::SurfaceMesh::VoxelCoords),
m_GrainIds(NULL)
{
  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
CMUSurfaceMeshingFilter::~CMUSurfaceMeshingFilter()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void CMUSurfaceMeshingFilter::setupFilterParameters()
{
  std::vector<FilterParameter::Pointer> parameters;
//  {
//    FilterOption::Pointer option = FilterOption::New();
//    option->setHumanLabel("Output Directory");
//    option->setPropertyName("OutputDirectory");
//    option->setWidgetType(FilterOption::OutputFileWidget);
//    option->setValueType("string");
//    parameters.push_back(option);
//  }
//  {
//    FilterParameter::Pointer option = FilterParameter::New();
//    option->setHumanLabel("Output Nodes File");
//    option->setPropertyName("OutputNodesFile");
//    option->setWidgetType(FilterParameter::OutputFileWidget);
//    option->setValueType("string");
//    parameters.push_back(option);
//  }
//  {
//    FilterParameter::Pointer option = FilterParameter::New();
//    option->setHumanLabel("Output Edges File");
//    option->setPropertyName("OutputEdgesFile");
//    option->setWidgetType(FilterParameter::OutputFileWidget);
//    option->setValueType("string");
//    parameters.push_back(option);
//  }
//  {
//    FilterParameter::Pointer option = FilterParameter::New();
//    option->setHumanLabel("Output Triangles File");
//    option->setPropertyName("OutputTrianglesFile");
//    option->setWidgetType(FilterParameter::OutputFileWidget);
//    option->setValueType("string");
//    parameters.push_back(option);
//  }
//  {
//    FilterParameter::Pointer option = FilterParameter::New();
//    option->setHumanLabel("X Step");
//    option->setPropertyName("XStep");
//    option->setWidgetType(FilterParameter::DoubleWidget);
//    option->setValueType("float");
//    parameters.push_back(option);
//  }
//  {
//    FilterParameter::Pointer option = FilterParameter::New();
//    option->setHumanLabel("Y Step");
//    option->setPropertyName("YStep");
//    option->setWidgetType(FilterParameter::DoubleWidget);
//    option->setValueType("float");
//    parameters.push_back(option);
//  }
//  {
//    FilterParameter::Pointer option = FilterParameter::New();
//    option->setHumanLabel("Z Step");
//    option->setPropertyName("ZStep");
//    option->setWidgetType(FilterParameter::DoubleWidget);
//    option->setValueType("float");
//    parameters.push_back(option);
//  }
  setFilterParameters(parameters);
}
// -----------------------------------------------------------------------------
void CMUSurfaceMeshingFilter::writeFilterParameters(AbstractFilterParametersWriter* writer)
{
//  writer->writeValue("OutputDirectory", getOutputDirectory() );
//  writer->writeValue("OutputNodesFile", getOutputNodesFile() );
//  writer->writeValue("OutputEdgesFile", getOutputEdgesFile() );
//  writer->writeValue("OutputTrianglesFile", getOutputTrianglesFile() );
//  writer->writeValue("XStep", getXStep() );
//  writer->writeValue("YStep", getYStep() );
//  writer->writeValue("ZStep", getZStep() );
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void CMUSurfaceMeshingFilter::dataCheck(bool preflight, size_t voxels, size_t fields, size_t ensembles)
{
  setErrorCondition(0);
  std::stringstream ss;
  VoxelDataContainer* m = getVoxelDataContainer();

//  if (true == m_OutputDirectory.empty())
//  {
//    ss << getHumanLabel() << " needs the Output directory set";
//    setErrorCondition(-387);
//  }
//  if(true == m_OutputNodesFile.empty())
//  {
//    addErrorMessage(getHumanLabel(), "The output Nodes file needs to be set", -380);
//    setErrorCondition(-380);
//  }
//  if(true == m_OutputEdgesFile.empty())
//  {
//    addErrorMessage(getHumanLabel(), "The output Edges file needs to be set", -381);
//    setErrorCondition(-381);
//  }
//  if(true == m_OutputTrianglesFile.empty())
//  {
//    addErrorMessage(getHumanLabel(), "The output Triangles file needs to be set", -382);
//    setErrorCondition(-382);
//  }

  GET_PREREQ_DATA(m, DREAM3D, CellData, GrainIds, ss, -300, int32_t, Int32ArrayType, voxels, 1);

  // Create the array of "voxel" coordinates
  CREATE_NON_PREREQ_DATA(m, DREAM3D, CellData, VoxelCoords, ss, float, FloatArrayType, 0, voxels, 3)

}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void CMUSurfaceMeshingFilter::preflight()
{
  /* Place code here that sanity checks input arrays and input values. Look at some
  * of the other DREAM3DLib/Filters/.cpp files for sample codes */
  dataCheck(true, 1, 1, 1);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void CMUSurfaceMeshingFilter::execute()
{
  int err = 0;
  std::stringstream ss;
  setErrorCondition(err);
  VoxelDataContainer* m = getVoxelDataContainer();
  if(NULL == m)
  {
    setErrorCondition(-1);
    std::stringstream ss;
    ss << " DataContainer was NULL";
    PipelineMessage em(getNameOfClass(), ss.str(), -1);
    addErrorMessage(em);
    return;
  }
  setErrorCondition(0);
  int64_t totalPoints = m->getTotalPoints();
  size_t totalFields = m->getNumFieldTuples();
  size_t totalEnsembles = m->getNumEnsembleTuples();
  dataCheck(false, totalPoints, totalFields, totalEnsembles);
  if(getErrorCondition() < 0)
  {
    return;
  }
  size_t dims[3];
  m->getDimensions(dims);
  float res[3];
  m->getResolution(res);

  size_t id = 0;
  // Let's fill out the coordinate of each voxel. Remember that x coordinate goes fastest...
  for (size_t k = 0; k < dims[2]; k++)
  {
    for (size_t j = 0; j < dims[1]; j++)
    {
      for (size_t i = 0; i < dims[0]; i++)
      {
        id = (k * dims[0] * dims[1]) + (j * dims[0]) + i;
        m_VoxelCoords[id*3] = (float)(i) * res[0];
        m_VoxelCoords[id*3+1] = (float)(j) * res[1];
        m_VoxelCoords[id*3+2] = (float)(k) * res[2];
      }
    }
  }

  err = createMesh();
  if (err < 0)
    {
    setErrorCondition(-1);
    std::stringstream ss;
    ss << "Error Creating the Surface Mesh";
    PipelineMessage em(getNameOfClass(), ss.str(), -1);
    addErrorMessage(em);
    return;
  }

  notifyStatusMessage("Complete");
}


static int edgeTable_2d[20][8] =
{
  { -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 2, -1, -1, -1, -1, -1, -1 },
  { 1, 2, -1, -1, -1, -1, -1, -1 },
  { 0, 4, 2, 4, 1, 4, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1 },
  { 3, 0, -1, -1, -1, -1, -1, -1 },
  { 3, 1, -1, -1, -1, -1, -1, -1 },
  { 3, 4, 0, 4, 1, 4, -1, -1 },
  { 2, 3, -1, -1, -1, -1, -1, -1 },
  { 3, 4, 0, 4, 2, 4, -1, -1 },
  { 3, 4, 1, 4, 2, 4, -1, -1 },
  { 3, 0, 1, 2, -1, -1, -1, -1 },
  { 0, 1, 2, 3, -1, -1, -1, -1 },
  { 0, 1, 2, 3, -1, -1, -1, -1 },
  { 3, 0, 1, 2, -1, -1, -1, -1 },
  { 3, 4, 1, 4, 0, 4, 2, 4 } };

static int nsTable_2d[20][8] =
{
  { -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1 },
  { 1, 0, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1 },
  { 1, 0, -1, -1, -1, -1, -1, -1, },
  { 2, 1, -1, -1, -1, -1, -1, -1 },
  { 1, 0, 3, 2, 2, 1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1 },
  { 0, 3, -1, -1, -1, -1, -1, -1 },
  { 0, 3, -1, -1, -1, -1, -1, -1 },
  { 0, 3, 1, 0, 2, 1, -1, -1 },
  { 3, 2, -1, -1, -1, -1, -1, -1 },
  { 0, 3, 1, 0, 3, 2, -1, -1 },
  { 0, 3, 2, 1, 3, 2, -1, -1 },
  { 0, 3, 2, 1, -1, -1, -1, -1 },
  { 1, 0, 3, 2, -1, -1, -1, -1 },
  { 1, 0, 3, 2, -1, -1, -1, -1 },
  { 0, 3, 2, 1, -1, -1, -1, -1 },
  { 0, 3, 2, 1, 1, 0, 3, 2 } };



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int CMUSurfaceMeshingFilter::createMesh()
{
  std::stringstream ss;
  VoxelDataContainer* m = getVoxelDataContainer();
  if (NULL == m)
  {return -1;}

  if (getSurfaceMeshDataContainer() == NULL)
  {return -1;}

  SurfaceMeshDataContainer* sm = getSurfaceMeshDataContainer();

  int NSP;
  int nFEdge; // number of edges on the square...
  int nTriangle; // number of triangles...
  int nNodes; // number of total nodes used...
  int tnIEdge; // number of endges inside marching square...

  neighbor *neigh = NULL; // contains nearest neighbor information...
  Face *square = NULL; // contains square information...
  //Node *vertex = NULL; // contains node information...
  Segment *fedge = NULL; // cotains edges on square faces for open/closed loops...
  isegment *iedge = NULL; // contains edges inside marching square...
  Patch *triangle = NULL;

  int32_t* point = m_GrainIds;
  size_t xnum = 0;
  size_t ynum = 0;
  size_t znum = 0;
  float xstep = 0.0f;
  float ystep = 0.0f;
  float zstep = 0.0f;
  m->getDimensions(xnum, ynum, znum);
  m->getResolution(xstep, ystep, zstep);

  int NS = xnum * ynum * znum;
  NSP = xnum * ynum;

  neigh = (neighbor *)malloc((NS) * sizeof(neighbor));
  square = (Face *)malloc(3 * NS * sizeof(Face));

  // Preallocate all possible nodes
  //vertex = (Node *)malloc(7 * NS * sizeof(Node));
  StructArray<Node>::Pointer vertices = StructArray<Node>::CreateArray(7 * NS, DREAM3D::CellData::SurfaceMesh::Nodes);
  sm->setNodes(vertices);


  ss.str("");
  ss << "Finding neighbors for each site...";
  std::cout << ss.str() << std::endl;
  get_neighbor_list(neigh, NS, NSP, xnum, ynum, znum);

  //printf("\nReading edge and neighbor spin tables...";
  //read_edge_neighspin_table(edgeTable_2d, nsTable_2d);

  ss.str("");
  ss << "Initializing all possible nodes...";
  std::cout << ss.str() << std::endl;
  initialize_nodes(point, vertices, NS, xstep, ystep, zstep);

  ss.str("");
  ss << "Initializing all possible squares...";
  std::cout << ss.str() << std::endl;
  initialize_squares(neigh, square, NS, NSP);

  ss.str("");
  ss << "Counting number of total edges turned on...";
  std::cout << ss.str() << std::endl;
  nFEdge = get_number_fEdges(square, point, neigh, edgeTable_2d, NS);
  printf("\ttotal number of face edges = %d\n", nFEdge);

  // memory allocation for face edges...
  fedge = (Segment *)malloc(nFEdge * sizeof(Segment));

  ss.str("");
  ss << "Finding nodes and edges on each square...";
  std::cout << ss.str() << std::endl;
  get_nodes_fEdges(square, point, neigh, vertices, fedge, edgeTable_2d, nsTable_2d, NS, NSP, xnum);

  ss.str("");
  ss << "Counting number of triangles...";
  std::cout << ss.str() << std::endl;
  nTriangle = get_number_triangles(point, square, vertices, fedge, NS, NSP, xnum);
  printf("\ttotal number of triangles = %d\n", nTriangle);

  // memory allocation for triangle...
  triangle = (Patch *)malloc(nTriangle * sizeof(Patch));

  ss.str("");
  ss << "Finding triangles...";
  std::cout << ss.str() << std::endl;
  get_triangles(point, triangle, square, vertices, fedge, neigh, NS, NSP, xnum);

  /*
     int t, z;
     for(t=0; t<nTriangle; t++){
     printf("%3d    ", triangle[t].mCubeID);
     for(z=0; z<3; z++){
     printf("%3d ", triangle[t].edgePlace[z]);
     }
     printf("";
     }
     */

  ss.str("");
  ss << "updating triangle sides as face edges...";
  std::cout << ss.str() << std::endl;
  update_triangle_sides_with_fedge(triangle, fedge, square, nTriangle, xnum, NSP);

  ss.str("");
  ss << "Counting the number of inner edges including duplicates...";
  std::cout << ss.str() << std::endl;
  tnIEdge = get_number_unique_inner_edges(triangle, nTriangle);
  //printf("\ttotal number of unique inner edges = %d\n", tnIEdge);
  // memory allocation for inner edges...
  iedge = (isegment *)malloc(tnIEdge * sizeof(isegment));

  ss.str("");
  ss << "Finidng unique inner edges and updating triagle sides as inner edges...";
  std::cout << ss.str() << std::endl;
  get_unique_inner_edges(triangle, iedge, nTriangle, nFEdge);

  ss.str("");
  ss << "updating node and edge kinds...";
  std::cout << ss.str() << std::endl;
  update_node_edge_kind(vertices, fedge, iedge, triangle, nTriangle, nFEdge);

  ss.str("");
  ss << "Arranging neighboring spins across the triangle patches...";
  std::cout << ss.str() << std::endl;
  arrange_spins(point, triangle, vertices, nTriangle, xnum, NSP);

  ss.str("");
  ss << "Assigning new node IDs...";
  std::cout << ss.str() << std::endl;
  nNodes = assign_new_nodeID(vertices, NS);
  printf("\tnumber of nodes used = %d\n", nNodes);

  //  ss.str("");
  //    ss << "Outputting nodes and triangles...";
  //  get_output(vertex, fedge, iedge, triangle, NS, nNodes, nFEdge, tnIEdge, nTriangle, mp);

  free(neigh);
  free(square);
  //  free(vertex);
  free(fedge);
  free(iedge);

  return 0;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
#if 0
voxel* CMUSurfaceMeshingFilter::initialize_micro_from_dx_file(size_t &xDim, size_t &yDim, size_t &zDim, double dx, double dy, double dz, const std::string ifn)
{

  int id;
  //  char name[128];
  //  char datStr[255];
  double tx, ty, tz;

  VoxelDataContainer::Pointer m = VoxelDataContainer::New();

  DxReader::Pointer reader = DxReader::New();
  reader->setVoxelDataContainer(m.get());
  reader->setInputFile(ifn);
  reader->setXRes(1.0f);
  reader->setYRes(1.0f);
  reader->setZRes(1.0f);
  reader->execute();
  int err = reader->getErrorCondition();
  if(err < 0)
  {
    return NULL;
  }

  m->getDimensions(xDim, yDim, zDim);

  int NS = xDim * yDim * zDim;
  voxel* p = (voxel *)malloc((NS+1)*sizeof(voxel));


  // Point 0 is a garbage...
  p[0].spin = 0;

  // Let's fill out the coordinate of each voxel. Remember that x coordinate goes fastest...
  for (size_t k = 0; k < zDim; k++)
  {
    for (size_t j = 0; j < yDim; j++)
    {
      for (size_t i = 0; i < xDim; i++)
      {
        id = k * xDim * yDim + j * xDim + i + 1;
        tx = (double)(i) * dx;
        ty = (double)(j) * dy;
        tz = (double)(k) * dz;
        //printf("%10d %6.3f %6.3f %6.3f\n", id, tx, ty, tz);
        p[id].coord[0] = tx;
        p[id].coord[1] = ty;
        p[id].coord[2] = tz;
      }
    }
  }
  return p;
}
#endif

void CMUSurfaceMeshingFilter::get_neighbor_list(neighbor *neigh, int ns, int nsp, int xDim, int yDim, int zDim)
{
  // nsp = number of sites in a plane of xDim by yDim...
  // n[][] = 2 dimensional array storing its site number and neighbors...
  // site_id = id number for each site...starting from 1 to xDim*yDim*zDim....
  //
  // I assumed the square lattice...so the order of neighbors as follows...
  //
  //    4   3   2         13  12  11          22  21  20
  //    5 site  1         14   9  10          23  18  19
  //    6   7   8         15  16  17          24  25  26
  //
  //    in-plane          upper plane         lower plane

  int i, j, k; // loop indices...
  int site_id; // id number for each site...

  for (k = 0; k < (ns - nsp); k = k + nsp)
  {
    for (j = 0; j < (nsp - xDim); j = j + xDim)
    {
      for (i = 0; i < xDim; i++)
      {

        site_id = k + j + i;
        neighbor& n = neigh[site_id];
        //same plane...
        n.neigh_id[1] = k + j + i % xDim + 1;
        n.neigh_id[2] = k + (j - xDim + nsp) % nsp + i % xDim + 1;
        n.neigh_id[3] = k + (j - xDim + nsp) % nsp + i;
        n.neigh_id[4] = k + (j - xDim + nsp) % nsp + (i - 2 + xDim) % xDim + 1;

        n.neigh_id[5] = k + j + (i - 2 + xDim) % xDim + 1;
        n.neigh_id[6] = k + (j + xDim) % nsp + (i - 2 + xDim) % xDim + 1;
        n.neigh_id[7] = k + (j + xDim) % nsp + i;
        n.neigh_id[8] = k + (j + xDim) % nsp + i % xDim + 1;

        //upper plane...
        //move the plane up and use the same scheme...
        n.neigh_id[9] = (k - nsp + ns) % ns + j + i;
        n.neigh_id[10] = (k - nsp + ns) % ns + j + i % xDim + 1;
        n.neigh_id[11] = (k - nsp + ns) % ns + (j - xDim + nsp) % nsp + i % xDim + 1;

        n.neigh_id[12] = (k - nsp + ns) % ns + (j - xDim + nsp) % nsp + i;
        n.neigh_id[13] = (k - nsp + ns) % ns + (j - xDim + nsp) % nsp + (i - 2 + xDim) % xDim + 1;
        n.neigh_id[14] = (k - nsp + ns) % ns + j + (i - 2 + xDim) % xDim + 1;

        n.neigh_id[15] = (k - nsp + ns) % ns + (j + xDim) % nsp + (i - 2 + xDim) % xDim + 1;
        n.neigh_id[16] = (k - nsp + ns) % ns + (j + xDim) % nsp + i;
        n.neigh_id[17] = (k - nsp + ns) % ns + (j + xDim) % nsp + i % xDim + 1;

        //lower plane...
        n.neigh_id[18] = (k + nsp) % ns + j + i;
        n.neigh_id[19] = (k + nsp) % ns + j + i % xDim + 1;
        n.neigh_id[20] = (k + nsp) % ns + (j - xDim + nsp) % nsp + i % xDim + 1;

        n.neigh_id[21] = (k + nsp) % ns + (j - xDim + nsp) % nsp + i;
        n.neigh_id[22] = (k + nsp) % ns + (j - xDim + nsp) % nsp + (i - 2 + xDim) % xDim + 1;
        n.neigh_id[23] = (k + nsp) % ns + j + (i - 2 + xDim) % xDim + 1;

        n.neigh_id[24] = (k + nsp) % ns + (j + xDim) % nsp + (i - 2 + xDim) % xDim + 1;
        n.neigh_id[25] = (k + nsp) % ns + (j + xDim) % nsp + i;
        n.neigh_id[26] = (k + nsp) % ns + (j + xDim) % nsp + i % xDim + 1;
      }
    }
  }
  /*
     int i2;
     for( i2=1; i2<=ns; i2++){
     printf("site %d\n\n ", i2);
     printf("%d  %d  %d\n",   n[i2].neigh_id[4], n[i2].neigh_id[3], n[i2].neigh_id[2]);
     printf("%d  %d  %d\n",   n[i2].neigh_id[5], i2               , n[i2].neigh_id[1]);
     printf("%d  %d  %d\n\n", n[i2].neigh_id[6], n[i2].neigh_id[7], n[i2].neigh_id[8]);

     printf("%d  %d  %d\n",   n[i2].neigh_id[13], n[i2].neigh_id[12],n[i2].neigh_id[11]);
     printf("%d  %d  %d\n",   n[i2].neigh_id[14], n[i2].neigh_id[9], n[i2].neigh_id[10]);
     printf("%d  %d  %d\n\n", n[i2].neigh_id[15], n[i2].neigh_id[16],n[i2].neigh_id[17]);

     printf("%d  %d  %d\n",   n[i2].neigh_id[22], n[i2].neigh_id[21], n[i2].neigh_id[20]);
     printf("%d  %d  %d\n",   n[i2].neigh_id[23], n[i2].neigh_id[18], n[i2].neigh_id[19]);
     printf("%d  %d  %d\n\n", n[i2].neigh_id[24], n[i2].neigh_id[25], n[i2].neigh_id[26]);
     }
     */
}


void CMUSurfaceMeshingFilter::initialize_nodes(int32_t *p, StructArray<Node>::Pointer v0, int ns, double dx, double dy, double dz)
{

  // this function finds the coordinates of possible nodes...
  int i;
  int id;
  float tx, ty, tz, halfdx, halfdy, halfdz;

  halfdx = dx / 2.0;
  halfdy = dy / 2.0;
  halfdz = dz / 2.0;

  // Get a reference varible to the Nodes so our syntax is a bit less verbose
  StructArray<Node>& v = *v0;
  // node id starts with 0....
  for (i = 0; i < ns; i++)
  {

    tx = m_VoxelCoords[i*3 + 0];
    ty = m_VoxelCoords[i*3 + 1];
    tz = m_VoxelCoords[i*3 + 2];

    // coordinates of the spin, id...
    id = 7 * (i);
    // possible node id goes from id to id+6...
    v[id].coord[0] = tx + halfdx;
    v[id].coord[1] = ty;
    v[id].coord[2] = tz;
    v[id].nodeKind = 0; // kind of the node; 2 for binary, 3 for triple points, 4 quadruple points and so on...
    v[id].newID = -1; // newID for used nodes; if not used, it's -1...

    v[id + 1].coord[0] = tx;
    v[id + 1].coord[1] = ty + halfdy;
    v[id + 1].coord[2] = tz;
    v[id + 1].nodeKind = 0;
    v[id + 1].newID = -1;

    v[id + 2].coord[0] = tx;
    v[id + 2].coord[1] = ty;
    v[id + 2].coord[2] = tz + halfdz;
    v[id + 2].nodeKind = 0;
    v[id + 2].newID = -1;

    v[id + 3].coord[0] = tx + halfdx;
    v[id + 3].coord[1] = ty + halfdy;
    v[id + 3].coord[2] = tz;
    v[id + 3].nodeKind = 0;
    v[id + 3].newID = -1;

    v[id + 4].coord[0] = tx + halfdx;
    v[id + 4].coord[1] = ty;
    v[id + 4].coord[2] = tz + halfdz;
    v[id + 4].nodeKind = 0;
    v[id + 4].newID = -1;

    v[id + 5].coord[0] = tx;
    v[id + 5].coord[1] = ty + halfdy;
    v[id + 5].coord[2] = tz + halfdz;
    v[id + 5].nodeKind = 0;
    v[id + 5].newID = -1;

    v[id + 6].coord[0] = tx + halfdx;
    v[id + 6].coord[1] = ty + halfdy;
    v[id + 6].coord[2] = tz + halfdz;
    v[id + 6].nodeKind = 0;
    v[id + 6].newID = -1;
    /*
       printf("\n%10d %5.2f %5.2f %5.2f\n", i, tx, ty, tz);
       printf("%10d %5.2f %5.2f %5.2f\n", id,   v[id].coord[0], v[id].coord[1], v[id].coord[2]);
       printf("%10d %5.2f %5.2f %5.2f\n", id+1, v[id+1].coord[0], v[id+1].coord[1], v[id+1].coord[2]);
       printf("%10d %5.2f %5.2f %5.2f\n", id+2, v[id+2].coord[0], v[id+2].coord[1], v[id+2].coord[2]);
       printf("%10d %5.2f %5.2f %5.2f\n", id+3, v[id+3].coord[0], v[id+3].coord[1], v[id+3].coord[2]);
       printf("%10d %5.2f %5.2f %5.2f\n", id+4, v[id+4].coord[0], v[id+4].coord[1], v[id+4].coord[2]);
       printf("%10d %5.2f %5.2f %5.2f\n", id+5, v[id+5].coord[0], v[id+5].coord[1], v[id+5].coord[2]);
       printf("%10d %5.2f %5.2f %5.2f\n", id+6, v[id+6].coord[0], v[id+6].coord[1], v[id+6].coord[2]);
       */
  }

}

void CMUSurfaceMeshingFilter::initialize_squares(neighbor *n, Face *sq, int ns, int nsp)
{

  // This function gathers initial information on each square...
  int id, i, j, k;
  // square id starts with 0....
  // notice that voxels at the surface will have the wrong values of node at the other end...
  // since it includes periodic boundary condition...
  // but, since the structure surrounded by ghost layer of spin -3, it's OK...
  for (i = 0; i < ns; i++)
  {

    id = 3 * (i);
    // There are 3 squares for each data id; store 4 corners of each square...

    //    4   3   2         13  12  11          22  21  20
    //    5 site  1         14   9  10          23  18  19
    //    6   7   8         15  16  17          24  25  26
    //
    //    in-plane          upper plane         lower plane

    // top, where z coordinates are same...
    sq[id].site_id[0] = i;
    sq[id].site_id[1] = n[i].neigh_id[1];
    sq[id].site_id[2] = n[i].neigh_id[8];
    sq[id].site_id[3] = n[i].neigh_id[7];
    // back, where y coordinates are same...
    sq[id + 1].site_id[0] = i;
    sq[id + 1].site_id[1] = n[i].neigh_id[1];
    sq[id + 1].site_id[2] = n[i].neigh_id[19];
    sq[id + 1].site_id[3] = n[i].neigh_id[18];
    // left, where x coordinates are same...
    sq[id + 2].site_id[0] = n[i].neigh_id[7];
    sq[id + 2].site_id[1] = i;
    sq[id + 2].site_id[2] = n[i].neigh_id[18];
    sq[id + 2].site_id[3] = n[i].neigh_id[25];

    // initialize node, edge...-1 is dummy initial value...
    for (j = 0; j < 4; j++)
    {
      sq[id].edge_id[j] = -1;
      sq[id + 1].edge_id[j] = -1;
      sq[id + 2].edge_id[j] = -1;
    }

    for (k = 0; k < 3; k++)
    {
      sq[id + k].nEdge = 0;
      sq[id + k].FCnode = -1;
      sq[id + k].effect = 0;
    }
  }

}

int CMUSurfaceMeshingFilter::get_number_fEdges(Face *sq, int32_t* p, neighbor *n, int eT2d[20][8], int ns)
{

  int k, m;
  int csite, cspin, tsite;
  int tnsite[4];
  int tnspin[4];
  int atBulk; // if it's 0, the square is at Bulk...
  int sqIndex, anFlag; // square index and anormality flag...
  int sumEdge, numCEdge;

  sumEdge = 0;
  // There are 3*ns squares in total...
  for (k = 0; k < (3 * ns); k++)
  { // for each square...
    // for the first node of each square, get site, spin and 4 sites of the square...
    csite = sq[k].site_id[0];
    cspin = p[csite];
    tnsite[0] = sq[k].site_id[0];
    tnsite[1] = sq[k].site_id[1];
    tnsite[2] = sq[k].site_id[2];
    tnsite[3] = sq[k].site_id[3];

    atBulk = 0;
    for (m = 0; m < 4; m++)
    { // if one of the corners of each square is - value,
      tsite = tnsite[m]; // mark the square as atSurface --> atBulk = 1
      tnspin[m] = p[tsite];
      if(tnspin[m] < 0)
      {
        atBulk++;
      }
    }
    // if at least one of the node of each square is positive, dummy wrapper,
    if(atBulk != 4)
    {
      sq[k].effect = 1;
    } // mark current square as effective one that can be "marching cubed"...

    // Let's count the number of edges...
    if(atBulk != 4)
    { // consider the effective square only...

      sqIndex = get_square_index(tnspin);
      // correction for anormal case...
      if(sqIndex == 15)
      {
        anFlag = treat_anomaly(tnsite, p, n, k);
        sqIndex = sqIndex + anFlag;
      }
      // let's count the number of face edges...
      if(sqIndex == 0)
      {
        numCEdge = 0;
      }
      else if(sqIndex == 19)
      {
        numCEdge = 4;
      }
      else if(sqIndex == 15 || sqIndex == 16 || sqIndex == 17 || sqIndex == 18)
      {
        numCEdge = 2;
      }
      else if(sqIndex == 7 || sqIndex == 11 || sqIndex == 13 || sqIndex == 14)
      {
        // Let's treat special cases for surface of the materials...
        if(atBulk == 3)
        { // 3 negative spins, ex, -4, -4, -3, 1 = corners and edges of microstructure
          numCEdge = 2; // get rid of one edge...
          //printf("%5d  %3d %3d %3d %3d\n", 3, tnspin[0], tnspin[1], tnspin[2], tnspin[3]);
        }
        else if(atBulk == 2)
        { // 2 negative spins and 2 different positive spin, ex, -4, -4, 1, 2
          numCEdge = 3; // = faces of microstructure, all will be used...
          //printf("%5d  %3d %3d %3d %3d\n", 2, tnspin[0], tnspin[1], tnspin[2], tnspin[3]);
        }
        else if(atBulk == 1)
        {
          printf("one negative spin case is not supposed to happen! Wrong!");
        }
        else
        { // positive spins only...normal case!
          numCEdge = 3;
        }
      }
      else
      {
        numCEdge = 1;
      }

      sumEdge = sumEdge + numCEdge;
    }
  }
  //printf("\ttotal number of face edges = %d\n", sumEdge);
  return sumEdge;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void CMUSurfaceMeshingFilter::get_nodes(int cst, int ord, int nidx[2], int* nid, int nsp1, int xDim1)
{

  int ii;
  int tempIndex;

  for (ii = 0; ii < 2; ii++)
  {

    tempIndex = nidx[ii];

    if(ord == 0)
    { // if the square index is 0 for corner site...

      switch(tempIndex)
      {
        case 0:
          nid[ii] = 7 * (cst - 1);
          break;
        case 1:
          nid[ii] = 7 * cst + 1;
          break;
        case 2:
          nid[ii] = 7 * (cst + xDim1 - 1);
          break;
        case 3:
          nid[ii] = 7 * (cst - 1) + 1;
          break;
        case 4:
          nid[ii] = 7 * (cst - 1) + 3;
          break;
      }

    }
    else if(ord == 1)
    { // if the square index is 1...

      switch(tempIndex)
      {
        case 0:
          nid[ii] = 7 * (cst - 1);
          break;
        case 1:
          nid[ii] = 7 * cst + 2;
          break;
        case 2:
          nid[ii] = 7 * (cst + nsp1 - 1);
          break;
        case 3:
          nid[ii] = 7 * (cst - 1) + 2;
          break;
        case 4:
          nid[ii] = 7 * (cst - 1) + 4;
          break;
      }

    }
    else
    { // if the square index is 2...

      switch(tempIndex)
      {
        case 0:
          nid[ii] = 7 * (cst - 1) + 1;
          break;
        case 1:
          nid[ii] = 7 * (cst - 1) + 2;
          break;
        case 2:
          nid[ii] = 7 * (cst + nsp1 - 1) + 1;
          break;
        case 3:
          nid[ii] = 7 * (cst + xDim1 - 1) + 2;
          break;
        case 4:
          nid[ii] = 7 * (cst - 1) + 5;
          break;
      }

    }
    //printf("%10d %7d %2d\t", cst, nid[ii], tempIndex);
  }

  //printf("";

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void CMUSurfaceMeshingFilter::get_nodes_fEdges(Face *sq, int32_t* p, neighbor *n, StructArray<Node>::Pointer vertices, Segment *e, int eT2d[20][8], int nsT2d[20][8], int ns, int nsp, int xDim)
{

  int j, k, m, ii;
  int csite, cspin, tsite, tnode, eid;
  int cubeOrigin; // stores the site id of 0th corner of each cube...
  int sqOrder; // stores the 0th, 1st and 2nd square...
  int tnsite[4], tnspin[4];
  int atBulk, sqIndex, anFlag;
  int edgeCount; // number of edges for each square...
  int nodeIndex[2], pixIndex[2];
  int nodeID[2];
  int pixSpin[2];
  int tn1, tn2, tnk;
  //int *pixSite;

  StructArray<Node>& v = *vertices;


//  nodeID = (int *)malloc(2 * sizeof(int));
//  pixSpin = (int *)malloc(2 * sizeof(int));
  eid = 0;

  for (k = 0; k < (3 * ns); k++)
  { // for each square...

    cubeOrigin = k / 3;
    sqOrder = k % 3;

    csite = sq[k].site_id[0];
    cspin = p[csite];
    tnsite[0] = sq[k].site_id[0];
    tnsite[1] = sq[k].site_id[1];
    tnsite[2] = sq[k].site_id[2];
    tnsite[3] = sq[k].site_id[3];

    atBulk = 0;
    for (m = 0; m < 4; m++)
    {
      tsite = tnsite[m];
      tnspin[m] = p[tsite];
      if(tnspin[m] < 0)
      {
        atBulk++;
      }
    }

    edgeCount = 0;

    // Let's find the edges...
    if(atBulk != 4)
    { // consider the square inside the bulk only...

      sqIndex = get_square_index(tnspin);
      // correction for anormal case...
      if(sqIndex == 15)
      {
        anFlag = treat_anomaly(tnsite, p, n, k);
        sqIndex = sqIndex + anFlag;
      }
      // If square is effective...
      if(sqIndex != 0)
      {

        for (j = 0; j < 8; j = j + 2)
        {

          if(eT2d[sqIndex][j] != -1)
          {

            nodeIndex[0] = eT2d[sqIndex][j];
            nodeIndex[1] = eT2d[sqIndex][j + 1];
            pixIndex[0] = nsT2d[sqIndex][j];
            pixIndex[1] = nsT2d[sqIndex][j + 1];
            // get id of the nodes of edge and spins across the edge...
            get_nodes(cubeOrigin, sqOrder, nodeIndex, nodeID, nsp, xDim);

            if(nodeID[0] > vertices->GetNumberOfTuples())
            get_nodes(cubeOrigin, sqOrder, nodeIndex, nodeID, nsp, xDim);
            if(nodeID[1] > vertices->GetNumberOfTuples())
            get_nodes(cubeOrigin, sqOrder, nodeIndex, nodeID, nsp, xDim);


            get_spins(p, cubeOrigin, sqOrder, pixIndex, pixSpin, nsp, xDim);
            // get rid of edge that has only negative neighbor spin...
            if(pixSpin[0] > 0 || pixSpin[1] > 0)
            {
              e[eid].node_id[0] = nodeID[0]; // actual node ids for each edge...
              e[eid].node_id[1] = nodeID[1];
              e[eid].neigh_spin[0] = pixSpin[0];
              e[eid].neigh_spin[1] = pixSpin[1];
              sq[k].edge_id[edgeCount] = eid;
              e[eid].edgeKind = 2;
              edgeCount++; // edges of the open loops are always binary...
              eid++; // triple lines only occurs inside the marching cubes...
            }
            else
            {
              tn1 = nodeID[0];
              tn2 = nodeID[1];
              v[tn1].nodeKind = -1; // extra nodes from meshing the surface of the box...
              v[tn2].nodeKind = -1; // we don't need them...
            }

            // Categorize the node on the faces of marching cubes...if it's triple junction or not...
            for (ii = 0; ii < 2; ii++)
            {
              if(nodeIndex[ii] == 4)
              {
                if(sqIndex == 7 || sqIndex == 11 || sqIndex == 13 || sqIndex == 14)
                {

                  tnode = nodeID[ii];
                  sq[k].FCnode = tnode;

                  // Let's treat special cases for surface of the materials...
                  if(atBulk == 3)
                  { // 3 negative spins, ex, -4, -4, -3, 1 = corners and edges of microstructure
                    v[tnode].nodeKind = 3; // mark face centered node as 13, corner & edge point on the surface of microstructure
                  }
                  else if(atBulk == 2)
                  { // 2 negative spins and 2 different positive spin, ex, -4, -4, 1, 2 = faces of microstructure, all will be used..
                    v[tnode].nodeKind = 3; // mark face centered node as 13, triple point on the surface of microstructure
                  }
                  else if(atBulk == 1)
                  {
                    printf("one negative spin case is not supposed to happen! Wrong!");
                    v[tnode].nodeKind = 3;
                  }
                  else
                  { // positive spins only...normal case!
                    v[tnode].nodeKind = 3; // mark face centered node as 3, triple point
                  }

                }
                else if(sqIndex == 19)
                {
                  tnode = nodeID[ii];
                  sq[k].FCnode = tnode;
                  if(atBulk == 0)
                  {
                    v[tnode].nodeKind = 4;
                  }
                  else
                  {
                    v[tnode].nodeKind = 4;
                  }
                  //printf("atBulk = %3d and nk = %d\n", atBulk, 4);
                }
                else
                {
                  // do nothing...
                }

              }
              else
              {
                tnode = nodeID[ii];
                tnk = v[tnode].nodeKind;
                if(tnk != -1)
                {
                  if(atBulk == 0)
                  {
                    v[tnode].nodeKind = 2;
                  }
                  else
                  {
                    v[tnode].nodeKind = 2;
                  }
                }
                //printf("atBulk = %d and nk = %d  %3d %3d %3d %3d\n", atBulk, 2, tnspin[0], tnspin[1], tnspin[2], tnspin[3]);
              }
            }

          }
        }
      }
    }

    sq[k].nEdge = edgeCount;
    //if(edgeCount!=0 && edgeCount==4){ printf("%3d", edgeCount);}
  }

  printf("\ttotal number of identified face edges = %d\n", eid);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int CMUSurfaceMeshingFilter::get_square_index(int tns[4])
{

  // identify each square configuration using binary bit...
  // returns the unique decimal integer for each configuration...
  int aBit[6];
  int tempIndex, subIndex;

  if(tns[0] == tns[1])
  {
    aBit[0] = 0;
  }
  else
  {
    aBit[0] = 1;
  }
  if(tns[1] == tns[2])
  {
    aBit[1] = 0;
  }
  else
  {
    aBit[1] = 1;
  }
  if(tns[2] == tns[3])
  {
    aBit[2] = 0;
  }
  else
  {
    aBit[2] = 1;
  }
  if(tns[3] == tns[0])
  {
    aBit[3] = 0;
  }
  else
  {
    aBit[3] = 1;
  }
  if(tns[0] == tns[2])
  {
    aBit[4] = 0;
  }
  else
  {
    aBit[4] = 1;
  }
  if(tns[1] == tns[3])
  {
    aBit[5] = 0;
  }
  else
  {
    aBit[5] = 1;
  }

  tempIndex = 8 * aBit[3] + 4 * aBit[2] + 2 * aBit[1] + 1 * aBit[0];

  if(tempIndex == 15)
  {
    subIndex = 2 * aBit[4] + 1 * aBit[5];
    if(subIndex == 0)
    {
      tempIndex = tempIndex;
    }
    else
    {
      tempIndex = tempIndex + subIndex + 1;
    }
  }

  return tempIndex;
}

int CMUSurfaceMeshingFilter::treat_anomaly(int tnst[4], int32_t* p1, neighbor *n1, int sqid)
{

  int i, j, k, ii;
  int csite, cspin, nsite, nspin;
  int temp, tempFlag;
  int min, minid;
  int numNeigh[4]; // number of neighbors for each node in a square that has same spin...
  // int whichSQ, numFaceNeigh, tNindex;
  //  int tNList[8];

  min = 1000;
  minid = -1;

  for (k = 0; k < 4; k++)
  {
    numNeigh[k] = 0;
  }

  /*
     // THIS IS USING FACE NEIGHBORS FOR TREATING ANORMAL CASE...
     whichSQ = sqid%3;
     numFaceNeigh = 8;

     //    4   3   2         13  12  11          22  21  20
     //    5 site  1         14   9  10          23  18  19
     //    6   7   8         15  16  17          24  25  26

     if(whichSQ==0){
     tNList[0] = 1;  tNList[1] = 2;  tNList[2] = 3;  tNList[3] = 4;
     tNList[4] = 5;  tNList[5] = 6;  tNList[6] = 7;  tNList[7] = 8;
     }else if(whichSQ==1){
     tNList[0] = 1;  tNList[1] = 5;  tNList[2] = 14;  tNList[3] = 9;
     tNList[4] = 10; tNList[5] = 23; tNList[6] = 18;  tNList[7] = 19;
     }else{
     tNList[0] = 3;  tNList[1] = 7;  tNList[2] = 12;  tNList[3] = 9;
     tNList[4] = 16; tNList[5] = 21; tNList[6] = 18;  tNList[7] = 25;
     }

     for(i=0; i<4; i++){               // for each vertex of the square, get site, spin and num neighbor
     csite = tnst[i];                // that has same spin...
     cspin = p1[csite].spin;
     for(j=0; j<numFaceNeigh; j++){
     tNindex = tNList[j];
     nsite = n1[csite].neigh_id[tNindex];
     nspin = p1[nsite].spin;
     if(cspin==nspin){ numNeigh[i] = numNeigh[i] + 1;}
     }
     }
     */

  // THIS IS USING ALL 3D NEIGHBORS FOR TREATING ANORMAL CASE...
  for (i = 0; i < 4; i++)
  {
    csite = tnst[i];
    cspin = p1[csite];
    for (j = 1; j <= num_neigh; j++)
    {
      nsite = n1[csite].neigh_id[j];
      nspin = p1[nsite];
      if(cspin == nspin && nspin > 0)
      {
        numNeigh[i] = numNeigh[i] + 1;
      }
    }
  }

  for (ii = 0; ii < 4; ii++)
  {
    temp = numNeigh[ii];
    if(temp < min)
    {
      min = temp;
      minid = ii;
    }
  }

  if(minid == -1)
  {
    printf("Something wrong with counting same-spin neighbors for each corner of the square!");
    tempFlag = 0;
  }
  else if(minid == 1 || minid == 3)
  { // we can reverse this...let's try this later...
    tempFlag = 0;
  }
  else
  {
    tempFlag = 1;
  }

  return tempFlag;
}

void CMUSurfaceMeshingFilter::get_spins(int32_t* p1, int cst, int ord, int pID[2], int *pSpin, int nsp1, int xDim1)
{
  int i;
  int pixTemp, tempSpin;
  for (i = 0; i < 2; i++)
  {
    pixTemp = pID[i];
    if(ord == 0)
    {
      switch(pixTemp)
      {
        case 0:
          tempSpin = p1[cst];
          pSpin[i] = tempSpin;
          break;
        case 1:
          tempSpin = p1[cst + 1];
          pSpin[i] = tempSpin;
          break;
        case 2:
          tempSpin = p1[cst + xDim1 + 1];
          pSpin[i] = tempSpin;
          break;
        case 3:
          tempSpin = p1[cst + xDim1];
          pSpin[i] = tempSpin;
          break;
      }
    }
    else if(ord == 1)
    {
      switch(pixTemp)
      {
        case 0:
          tempSpin = p1[cst];
          pSpin[i] = tempSpin;
          break;
        case 1:
          tempSpin = p1[cst + 1];
          pSpin[i] = tempSpin;
          break;
        case 2:
          tempSpin = p1[cst + nsp1 + 1];
          pSpin[i] = tempSpin;
          break;
        case 3:
          tempSpin = p1[cst + nsp1];
          pSpin[i] = tempSpin;
          break;
      }
    }
    else if(ord == 2)
    {
      switch(pixTemp)
      {
        case 0:
          tempSpin = p1[cst + xDim1];
          pSpin[i] = tempSpin;
          break;
        case 1:
          tempSpin = p1[cst];
          pSpin[i] = tempSpin;
          break;
        case 2:
          tempSpin = p1[cst + nsp1];
          pSpin[i] = tempSpin;
          break;
        case 3:
          tempSpin = p1[cst + nsp1 + xDim1];
          pSpin[i] = tempSpin;
          break;
      }
    }
    else
    {
      // do nothing...
    }

    //printf("%7d %2d ", nid[i], tempIndex);
  }

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int CMUSurfaceMeshingFilter::get_number_triangles(int32_t* p, Face *sq, StructArray<Node>::Pointer vertices, Segment *e, int ns, int nsp, int xDim)
{

  int i, ii, i1, i2, j, k, kk;
  int sqID[6];
  int tsq; // current sq id...
  int tnfe; // temp number of edges...
  int nFC; // number of FC turned on...
  int tFCnode;
  int nFE; // number of face edges...
  int eff; // all the squares effective?...
  int cubeFlag; // if 1, we can do marching cube; if 0, useless...
  int *arrayFE, *arrayFC, *arraySpin;
  arrayFC = (int *)malloc(6 * sizeof(int)); // stores face center node of each square. possible max = 6...
  arraySpin = (int *)malloc(8 * sizeof(int)); // stores 8 corner spins for center node kind...

  int tsqid1, tsqid2;
  int tsite1, tsite2, tspin1, tspin2;
  int cspin, nspin;
  int nburnt;
  int nds; // number of different spin of upper square...
  int BCnode, nkFlag; // body centered node and it's nodeFlag...
  int fcid;
  int tindex;
  int nTri, nTri0, nTri2, nTriM; // # triangles when fcenter is 0, 2 and more than 2...

  nTri0 = 0;
  nTri2 = 0;
  nTriM = 0;

  StructArray<Node>& v = *vertices;

  for (i = 0; i < (ns - nsp); i++)
  {

    cubeFlag = 0;
    // for each marching cube, collect faces...
    sqID[0] = 3 * (i - 1);
    sqID[1] = 3 * (i - 1) + 1;
    sqID[2] = 3 * (i - 1) + 2;
    sqID[3] = 3 * i + 2;
    sqID[4] = 3 * (i + xDim - 1) + 1;
    sqID[5] = 3 * (i + nsp - 1);
    BCnode = 7 * (i - 1) + 6;
    nFC = 0;
    nFE = 0;
    eff = 0;
    //initialize face center array...
    for (ii = 0; ii < 6; ii++)
    {
      arrayFC[ii] = -1;
    }
    // Count the numbers of face center turned on and face edges...
    fcid = 0;
    ii = 0;
    for (ii = 0; ii < 6; ii++)
    {
      tsq = sqID[ii];
      tFCnode = sq[tsq].FCnode;
      if(tFCnode != -1)
      {
        arrayFC[fcid] = tFCnode;
        fcid++;
      }
      //nFC = nFC + 1;
      nFE = nFE + sq[tsq].nEdge;
      eff = eff + sq[tsq].effect;
    }
    nFC = fcid;
    //if(fcid!=nFC){ printf("Something's wrong with counting face centers...";}
    if(eff > 0)
    {
      cubeFlag = 1;
    } // this is very important flag. only disregard marching cubes that has -spins...

    if(nFC >= 3)
    {
      // If number of face centers turned on is more than 2...
      // let's update the nodeKind of body center node...
      tsqid1 = sqID[0];
      tsqid2 = sqID[5];
      nkFlag = 0;
      // get spin numbers for 8 corners for each marching cube...
      for (j = 0; j < 4; j++)
      {
        tsite1 = sq[tsqid1].site_id[j];
        tsite2 = sq[tsqid2].site_id[j];
        tspin1 = p[tsite1];
        tspin2 = p[tsite2];
        arraySpin[j] = tspin1;
        arraySpin[j + 4] = tspin2;
        if(tspin1 < 0 || tspin2 < 0)
        {
          nkFlag++;
        }
      }
      //int t;
      //for(t=0; t<8; t++){ printf("%3d ", arraySpin[t]);}
      nds = 0; // number of different spins in each marching cube...
      nburnt = 0; // so nds = nodeKind of body center position...
      for (k = 0; k < 8; k++)
      {
        // arraySpin contains no -1 before any of it is burnt...
        cspin = arraySpin[k];
        if(cspin != -1)
        {
          nds++;
          arraySpin[k] = -1; // burn...
          nburnt++;
          for (kk = 0; kk < 8; kk++)
          {
            nspin = arraySpin[kk];
            if(cspin == nspin)
            {
              arraySpin[kk] = -1; //burn...
              nburnt++;
            }
          }
        }
      }

      if(nburnt != 8)
      {
        printf("\tcorners are wrongfully burnt in this marching cube: cube id = %d, number burnt = %d\n", i, nburnt);
      }
      // update nodeKind of body center node in the current marching cube...
      if(nkFlag > 0)
      {
        v[BCnode].nodeKind = nds;
      }
      else
      {
        v[BCnode].nodeKind = nds;
      }
      //printf("%2d %2d\n", nds, v[BCnode].nodeKind);

    }

    // Checking the number of edges for loops in the cube...
    if(nFE >= 3)
    {
      //printf("%4d", nFE);  // normal case 1...
    }
    else if(nFE > 0 && nFE < 3)
    {
      printf("\t? cube id = %d, # face edges %d --> cannot form any loop!\n", i, nFE);
      // not supposed to happen. We have to ignore this case...
    }
    else if(nFE == 0)
    {
      //printf("\tcube inside grain"; // normal case 2...
    }
    else
    {
      printf("\twhat?");
    }

    // if the current marching cube is a collection of 6 effective squares...and
    // the number of face edges at least 3...
    // when nFE==2, it doen't happen
    // when nFE==1, the edge will contribute for the neighboring marching cube...
    // when nFE==0, it means the cube is inside a grain, perfectly normal case!!!
    if(cubeFlag == 1 && nFE > 2)
    {
      // Make face edge array for each marching cube...
      arrayFE = (int *)malloc(nFE * sizeof(int));
      tindex = 0;
      for (i1 = 0; i1 < 6; i1++)
      {
        tsq = sqID[i1]; // get number of edges of each faces of the current marching cube
        tnfe = sq[tsq].nEdge; // if the marching cube is effective, i.e. cubeFlag = 1...
        if(tnfe != 0)
        {
          for (i2 = 0; i2 < tnfe; i2++)
          { // make face edge array for the current marching cube...
            arrayFE[tindex] = sq[tsq].edge_id[i2];
            tindex++;
          }
        }
      }

      if(tindex != nFE)
      {
        printf("\tsomething wrong with counting number of edges for marching cube...");
      }

      // Consider each case as Z. Wu's paper...
      if(nFC == 0)
      { // when there's no face center, all the face edges forms one loop!
        //printf("\n%3d marching cubes at %3d = and case 0\n", tcount, i);
        //tcount++;
        nTri0 = nTri0 + get_number_case0_triangles(arrayFE, vertices, e, nFE);
      }
      else if(nFC == 2)
      {
        //printf("\n%3d marching cubes at %3d = and case 2\n", tcount, i);
        //tcount++;
        nTri2 = nTri2 + get_number_case2_triangles(arrayFE, vertices, e, nFE, arrayFC, nFC);
      }
      else if(nFC > 2 && nFC <= 6)
      {
        //printf("\n%3d marching cubes at %3d = and case M\n", tcount, i);
        //tcount++;
        nTriM = nTriM + get_number_caseM_triangles(arrayFE, vertices, e, nFE, arrayFC, nFC);
      }
      else
      {
        //printf("Somthing's wrong in counting face centers turned on...";
        //printf("%5d %10d\n\n", nFC, i);
      }

      free(arrayFE);
    }
  }

  printf("\tnumber of triangles for case 0, case 1 and case 2 = %d %d %d\n", nTri0, nTri2, nTriM);
  // sum up triangle numbers...
  nTri = nTri0 + nTri2 + nTriM;

  free(arraySpin);

  return (nTri);
}

int CMUSurfaceMeshingFilter::get_number_case0_triangles(int *afe, StructArray<Node>::Pointer v1, Segment *e1, int nfedge)
{

  int ii, i, j, jj, k, kk, k1;
  int loopID;
  int tail, head, coin;
  int cedge, nedge;
  int cspin1, cspin2, cnode1, cnode2;
  int nspin1, nspin2, nnode1, nnode2;
  //  int tspin, tnode;
  int nucleus, chaser;
  //  int start, end;
  int spinFlag, nodeFlag, flip;
  int bflag, nbflag;
  int *burnt;
  int *burnt_list;
  burnt = (int *)malloc(nfedge * sizeof(int));
  burnt_list = (int *)malloc(nfedge * sizeof(int));

  int *count;
  int numN, numTri, tnumTri;
  //  int te, tn1, tn2;

  // initialize burn flags for face edges...
  for (ii = 0; ii < nfedge; ii++)
  {
    burnt[ii] = 0;
    burnt_list[ii] = -1;
  }

  loopID = 1;
  tail = 0;
  head = 0;

  for (i = 0; i < nfedge; i++)
  { // for face edges in each marching cubes...

    cedge = afe[i];
    bflag = burnt[i];

    if(bflag == 0)
    {

      nucleus = cedge;
      burnt[i] = loopID; // for identifying loops...
      burnt_list[tail] = cedge;

      do
      {

        chaser = burnt_list[tail];
        cspin1 = e1[chaser].neigh_spin[0];
        cspin2 = e1[chaser].neigh_spin[1];
        cnode1 = e1[chaser].node_id[0];
        cnode2 = e1[chaser].node_id[1];

        for (j = 0; j < nfedge; j++)
        {

          nedge = afe[j];
          nbflag = burnt[j];

          if(nbflag == 0)
          {

            nspin1 = e1[nedge].neigh_spin[0];
            nspin2 = e1[nedge].neigh_spin[1];
            nnode1 = e1[nedge].node_id[0];
            nnode2 = e1[nedge].node_id[1];
            // checking if neighbor edge has same neighboring spins...
            if(((cspin1 == nspin1) && (cspin2 == nspin2)) || ((cspin1 == nspin2) && (cspin2 == nspin1)))
            {
              spinFlag = 1;
            }
            else
            {
              spinFlag = 0;
            }
            // checking if neighor egde is contiguous...
            if((cnode2 == nnode1) && (cnode1 != nnode2))
            {
              nodeFlag = 1;
              flip = 0;
            }
            else if((cnode2 == nnode2) && (cnode1 != nnode1))
            {
              nodeFlag = 1;
              flip = 1;
            }
            else
            {
              nodeFlag = 0;
              flip = 0;
            }
            // if 2 edges share same neighbor spins and contiguous...
            if(spinFlag == 1 && nodeFlag == 1)
            { // update nedge to burnt_list and give proper loop id...
              head = head + 1;
              burnt_list[head] = nedge;
              burnt[j] = loopID;
              if(flip == 1)
              { // why do we flip the nodes and spins?
                e1[nedge].neigh_spin[0] = nspin2;
                e1[nedge].neigh_spin[1] = nspin1;
                e1[nedge].node_id[0] = nnode2;
                e1[nedge].node_id[1] = nnode1;
              }

            }
            else
            {
              // do nothing...
            }

          }
          else
          {
            // do nothing...
          }
        }

        if(tail == head)
        {
          coin = 0;
          tail = tail + 1;
          head = tail;
          loopID++;
        }
        else
        {
          tail = tail + 1;
          coin = 1;
        }

      }
      while (coin);
    }
  }

  count = (int *)malloc(loopID * sizeof(int));

  for (k1 = 1; k1 < loopID; k1++)
  {
    count[k1] = 0;
  }

  for (k = 1; k < loopID; k++)
  {
    for (kk = 0; kk < nfedge; kk++)
    {
      if(k == burnt[kk])
      {
        count[k] = count[k] + 1;
      }
    }
  }

  numTri = 0;
  for (jj = 1; jj < loopID; jj++)
  {
    numN = count[jj];
    if(numN == 3)
    {
      tnumTri = 1;
      numTri = numTri + tnumTri;
    }
    else if(numN > 3)
    {
      tnumTri = numN - 2;
      numTri = numTri + tnumTri;
    }
    else
    {
      // do nothing...
      printf("\tsomething wrong in counting # case 0 triangles...%d %d\n", numN, nfedge);
    }
  }

  free(burnt);
  free(burnt_list);
  free(count);

  return (numTri);
}

int CMUSurfaceMeshingFilter::get_number_case2_triangles(int *afe, StructArray<Node>::Pointer v1, Segment *e1, int nfedge, int *afc, int nfctr)
{

  int ii, i, j, k, kk, k1, n, i1, j1;
  int loopID;
  int tail, head, coin;
  int cedge, nedge;
  int cspin1, cspin2, cnode1, cnode2;
  int nspin1, nspin2, nnode1, nnode2;
  int tspin, tnode;
  int nucleus, chaser;
  int start, end;
  int from, to;
  int spinFlag, nodeFlag, flip;
  int bflag, nbflag;
  int *burnt;
  int *burnt_list;
  burnt = (int *)malloc(nfedge * sizeof(int));
  burnt_list = (int *)malloc(nfedge * sizeof(int));

  int *count;
  int numN, numTri;
  int *burnt_loop;
  int openL; // if a loop is an open loop, it's 1; if closed, it's 0...
  int startEdge;
  int endNode;
  int index;

  // initialize burn flags for face edges...
  for (ii = 0; ii < nfedge; ii++)
  {
    burnt[ii] = 0;
    burnt_list[ii] = -1;
  }

  loopID = 1;
  tail = 0;
  head = 0;

  for (i = 0; i < nfedge; i++)
  {

    cedge = afe[i];
    bflag = burnt[i];

    if(bflag == 0)
    {

      nucleus = cedge;
      burnt[i] = loopID;
      burnt_list[tail] = cedge;

      do
      {

        chaser = burnt_list[tail];
        cspin1 = e1[chaser].neigh_spin[0];
        cspin2 = e1[chaser].neigh_spin[1];
        cnode1 = e1[chaser].node_id[0];
        cnode2 = e1[chaser].node_id[1];

        for (j = 0; j < nfedge; j++)
        {

          nedge = afe[j];
          nbflag = burnt[j];

          if(nbflag == 0)
          {

            nspin1 = e1[nedge].neigh_spin[0];
            nspin2 = e1[nedge].neigh_spin[1];
            nnode1 = e1[nedge].node_id[0];
            nnode2 = e1[nedge].node_id[1];
            // checking if neighbor edge has same neighboring spins...
            if(((cspin1 == nspin1) && (cspin2 == nspin2)) || ((cspin1 == nspin2) && (cspin2 == nspin1)))
            {
              spinFlag = 1;
            }
            else
            {
              spinFlag = 0;
            }
            // checking if neighor egde is contiguous...
            if((cnode1 == nnode1) && (cnode2 != nnode2))
            {
              nodeFlag = 1;
            }
            else if((cnode1 == nnode2) && (cnode2 != nnode1))
            {
              nodeFlag = 1;
            }
            else if((cnode2 == nnode1) && (cnode1 != nnode2))
            {
              nodeFlag = 1;
            }
            else if((cnode2 == nnode2) && (cnode1 != nnode1))
            {
              nodeFlag = 1;
            }
            else
            {
              nodeFlag = 0;
            }

            if(spinFlag == 1 && nodeFlag == 1)
            {

              head = head + 1;
              burnt_list[head] = nedge;
              burnt[j] = loopID;

            }
            else
            {
              // do nothing...
            }

          }
          else
          {
            // do nothing...
          }
        }

        if(tail == head)
        {
          coin = 0;
          tail = tail + 1;
          head = tail;
          loopID++;
        }
        else
        {
          tail = tail + 1;
          coin = 1;
        }

      }
      while (coin);
    }
  }

  count = (int *)malloc(loopID * sizeof(int));

  for (k1 = 1; k1 < loopID; k1++)
  {
    count[k1] = 0;
  }

  for (k = 1; k < loopID; k++)
  {
    for (kk = 0; kk < nfedge; kk++)
    {
      if(k == burnt[kk])
      {
        count[k] = count[k] + 1;
      }
    }
  }
  // Let's make complete loops...
  numTri = 0;
  start = afc[0];
  end = afc[1];
  to = 0;
  from = 0;
  j1 = 1;

  for (j1 = 1; j1 < loopID; j1++)
  {

    openL = 0; // current loop is closed...
    numN = count[j1];
    //printf("%5d\n", numN);
    to = to + numN;
    from = to - numN;
    //printf("%5d %5d   ", from, to);
    burnt_loop = (int *)malloc((numN + 2) * sizeof(int));

    for (i1 = from; i1 < to; i1++)
    {

      cedge = burnt_list[i1];
      cnode1 = e1[cedge].node_id[0];
      cnode2 = e1[cedge].node_id[1];

      if(start == cnode1)
      {
        openL = 1; // loop is open...
        startEdge = cedge;
        flip = 0;
      }
      else if(start == cnode2)
      {
        openL = 1;
        startEdge = cedge;
        flip = 1;
      }
      else
      {
        // do nothing...
      }
    }
    //printf("   start edge & node: %5d %5d", startEdge, e1[startEdge].node_id[0]);
    //printf("   open flag: %2d", openL);
    //printf("   flip flag: %2d", flip);
    //printf("";
    if(openL == 1)
    { // if current loop is an open loop...

      if(flip == 1)
      {
        tnode = e1[startEdge].node_id[0];
        tspin = e1[startEdge].neigh_spin[0];
        e1[startEdge].node_id[0] = e1[startEdge].node_id[1];
        e1[startEdge].node_id[1] = tnode;
        e1[startEdge].neigh_spin[0] = e1[startEdge].neigh_spin[1];
        e1[startEdge].neigh_spin[1] = tspin;
      }
      else
      {
        // do nothing...
      }

      burnt_loop[0] = startEdge;
      index = 1;
      endNode = e1[startEdge].node_id[1];
      chaser = startEdge;

      do
      {
        for (n = from; n < to; n++)
        {
          cedge = burnt_list[n];
          cnode1 = e1[cedge].node_id[0];
          cnode2 = e1[cedge].node_id[1];
          if((cedge != chaser) && (endNode == cnode1))
          {
            burnt_loop[index] = cedge;
            index++;
          }
          else if((cedge != chaser) && (endNode == cnode2))
          {
            burnt_loop[index] = cedge;
            index++;
            // flip...
            tnode = e1[cedge].node_id[0];
            tspin = e1[cedge].neigh_spin[0];
            e1[cedge].node_id[0] = e1[cedge].node_id[1];
            e1[cedge].node_id[1] = tnode;
            e1[cedge].neigh_spin[0] = e1[cedge].neigh_spin[1];
            e1[cedge].neigh_spin[1] = tspin;
          }
          else
          {
            // do nothing...
          }
        }
        chaser = burnt_loop[index - 1];
        endNode = e1[chaser].node_id[1];
      }
      while (index < numN);

      if((numN + 1) == 3)
      {
        numTri = numTri + 1;
      }
      else if((numN + 1) > 3)
      {
        numTri = numTri + ((numN + 1) - 2);
      }
      else
      {
        //do nothing...
      }

      free(burnt_loop);

    }
    else
    { // if current loop is a closed one....i.e., openL = 0...

      startEdge = burnt_list[from];
      burnt_loop[0] = startEdge;
      index = 1;
      endNode = e1[startEdge].node_id[1];
      chaser = startEdge;

      do
      {
        for (n = from; n < to; n++)
        {
          cedge = burnt_list[n];
          cnode1 = e1[cedge].node_id[0];
          cnode2 = e1[cedge].node_id[1];
          if((cedge != chaser) && (endNode == cnode1))
          {
            burnt_loop[index] = cedge;
            index++;
          }
          else if((cedge != chaser) && (endNode == cnode2))
          {
            burnt_loop[index] = cedge;
            index++;
            // flip...
            tnode = e1[cedge].node_id[0];
            tspin = e1[cedge].neigh_spin[0];
            e1[cedge].node_id[0] = e1[cedge].node_id[1];
            e1[cedge].node_id[1] = tnode;
            e1[cedge].neigh_spin[0] = e1[cedge].neigh_spin[1];
            e1[cedge].neigh_spin[1] = tspin;
          }
          else
          {
            // do nothing...
          }
        }
        chaser = burnt_loop[index - 1];
        endNode = e1[chaser].node_id[1];
      }
      while (index < numN);

      if(numN == 3)
      {
        numTri = numTri + 1;
      }
      else if(numN > 3)
      {
        numTri = numTri + (numN - 2);
      }
      else
      {
        //do nothing...
      }

      free(burnt_loop);
    }
  }

  free(burnt);
  free(burnt_list);
  free(count);

  return (numTri);
}

int CMUSurfaceMeshingFilter::get_number_caseM_triangles(int *afe, StructArray<Node>::Pointer v1, Segment *e1, int nfedge, int *afc, int nfctr)
{

  int ii, i, j, k, kk, k1, n, i1, j1, n1;
  int loopID;
  int tail, head, coin;
  int cedge, nedge;
  int cspin1, cspin2, cnode1, cnode2;
  int nspin1, nspin2, nnode1, nnode2;
  int tspin, tnode;
  int nucleus, chaser;
  int start;
  int from, to;
  int spinFlag, nodeFlag, flip;
  int bflag, nbflag;
  int *burnt;
  int *burnt_list;
  burnt = (int *)malloc(nfedge * sizeof(int));
  burnt_list = (int *)malloc(nfedge * sizeof(int));

  int *count;
  int numN, numTri;
  int *burnt_loop;
  int openL; // if a loop is an open loop, it's 1; if closed, it's 0...
  int startEdge;
  int endNode;
  int index;

  // initialize burn flags for face edges...
  for (ii = 0; ii < nfedge; ii++)
  {
    burnt[ii] = 0;
    burnt_list[ii] = -1;
  }

  loopID = 1;
  tail = 0;
  head = 0;

  for (i = 0; i < nfedge; i++)
  {

    cedge = afe[i];
    bflag = burnt[i];

    if(bflag == 0)
    {

      nucleus = cedge;
      burnt[i] = loopID;
      burnt_list[tail] = cedge;

      do
      {

        chaser = burnt_list[tail];
        cspin1 = e1[chaser].neigh_spin[0];
        cspin2 = e1[chaser].neigh_spin[1];
        cnode1 = e1[chaser].node_id[0];
        cnode2 = e1[chaser].node_id[1];

        for (j = 0; j < nfedge; j++)
        {

          nedge = afe[j];
          nbflag = burnt[j];

          if(nbflag == 0)
          {

            nspin1 = e1[nedge].neigh_spin[0];
            nspin2 = e1[nedge].neigh_spin[1];
            nnode1 = e1[nedge].node_id[0];
            nnode2 = e1[nedge].node_id[1];
            // checking if neighbor edge has same neighboring spins...
            if(((cspin1 == nspin1) && (cspin2 == nspin2)) || ((cspin1 == nspin2) && (cspin2 == nspin1)))
            {
              spinFlag = 1;
            }
            else
            {
              spinFlag = 0;
            }
            // checking if neighor egde is contiguous...
            if((cnode1 == nnode1) && (cnode2 != nnode2))
            {
              nodeFlag = 1;
            }
            else if((cnode1 == nnode2) && (cnode2 != nnode1))
            {
              nodeFlag = 1;
            }
            else if((cnode2 == nnode1) && (cnode1 != nnode2))
            {
              nodeFlag = 1;
            }
            else if((cnode2 == nnode2) && (cnode1 != nnode1))
            {
              nodeFlag = 1;
            }
            else
            {
              nodeFlag = 0;
            }

            if(spinFlag == 1 && nodeFlag == 1)
            {
              head = head + 1;
              burnt_list[head] = nedge;
              burnt[j] = loopID;
            }
            else
            {
              // do nothing...
            }

          }
          else
          {
            // do nothing...
          }
        }

        if(tail == head)
        {
          coin = 0;
          tail = tail + 1;
          head = tail;
          loopID++;
        }
        else
        {
          tail = tail + 1;
          coin = 1;
        }

      }
      while (coin);
    }
  }

  count = (int *)malloc(loopID * sizeof(int));

  for (k1 = 1; k1 < loopID; k1++)
  {
    count[k1] = 0;
  }

  for (k = 1; k < loopID; k++)
  {
    for (kk = 0; kk < nfedge; kk++)
    {
      if(k == burnt[kk])
      {
        count[k] = count[k] + 1;
      }
    }
  }

  // Let's make complete loops...
  numTri = 0;
  to = 0;
  from = 0;
  j1 = 1;

  for (j1 = 1; j1 < loopID; j1++)
  {

    openL = 0; // current loop is closed...
    numN = count[j1];
    //printf("%5d\n", numN);
    to = to + numN;
    from = to - numN;
    //printf("%5d %5d   ", from, to);
    burnt_loop = (int *)malloc((numN + 2) * sizeof(int));

    for (i1 = from; i1 < to; i1++)
    {

      cedge = burnt_list[i1];
      cnode1 = e1[cedge].node_id[0];
      cnode2 = e1[cedge].node_id[1];

      for (n1 = 0; n1 < nfctr; n1++)
      {

        start = afc[n1];

        if(start == cnode1)
        {
          openL = 1; // loop is open...
          startEdge = cedge;
          flip = 0;
        }
        else if(start == cnode2)
        {
          openL = 1;
          startEdge = cedge;
          flip = 1;
        }
        else
        {
          // do nothing...
        }
      }
    }
    //printf("   start edge & node: %5d %5d", startEdge, e1[startEdge].node_id[0]);
    //printf("   open flag: %2d", openL);
    //printf("   flip flag: %2d", flip);
    //printf("";
    if(openL == 1)
    { // if current loop is an open loop...

      if(flip == 1)
      {
        tnode = e1[startEdge].node_id[0];
        tspin = e1[startEdge].neigh_spin[0];
        e1[startEdge].node_id[0] = e1[startEdge].node_id[1];
        e1[startEdge].node_id[1] = tnode;
        e1[startEdge].neigh_spin[0] = e1[startEdge].neigh_spin[1];
        e1[startEdge].neigh_spin[1] = tspin;
      }
      else
      {
        // do nothing...
      }

      burnt_loop[0] = startEdge;
      index = 1;
      endNode = e1[startEdge].node_id[1];
      chaser = startEdge;

      do
      {
        for (n = from; n < to; n++)
        {
          cedge = burnt_list[n];
          cnode1 = e1[cedge].node_id[0];
          cnode2 = e1[cedge].node_id[1];
          if((cedge != chaser) && (endNode == cnode1))
          {
            burnt_loop[index] = cedge;
            index++;
          }
          else if((cedge != chaser) && (endNode == cnode2))
          {
            burnt_loop[index] = cedge;
            index++;
            // flip...
            tnode = e1[cedge].node_id[0];
            tspin = e1[cedge].neigh_spin[0];
            e1[cedge].node_id[0] = e1[cedge].node_id[1];
            e1[cedge].node_id[1] = tnode;
            e1[cedge].neigh_spin[0] = e1[cedge].neigh_spin[1];
            e1[cedge].neigh_spin[1] = tspin;
          }
          else
          {
            // do nothing...
          }
        }
        chaser = burnt_loop[index - 1];
        endNode = e1[chaser].node_id[1];
      }
      while (index < numN);

      if((numN + 2) == 3)
      {
        numTri = numTri + 1;
      }
      else if((numN + 2) > 3)
      {
        numTri = numTri + ((numN + 2) - 2);
      }
      else
      {
        //do nothing...
      }
      free(burnt_loop);

    }
    else
    { // if current loop is a closed one....i.e., openL = 0...

      startEdge = burnt_list[from];
      burnt_loop[0] = startEdge;
      index = 1;
      endNode = e1[startEdge].node_id[1];
      chaser = startEdge;

      do
      {
        for (n = from; n < to; n++)
        {
          cedge = burnt_list[n];
          cnode1 = e1[cedge].node_id[0];
          cnode2 = e1[cedge].node_id[1];
          if((cedge != chaser) && (endNode == cnode1))
          {
            burnt_loop[index] = cedge;
            index++;
          }
          else if((cedge != chaser) && (endNode == cnode2))
          {
            burnt_loop[index] = cedge;
            index++;
            // flip...
            tnode = e1[cedge].node_id[0];
            tspin = e1[cedge].neigh_spin[0];
            e1[cedge].node_id[0] = e1[cedge].node_id[1];
            e1[cedge].node_id[1] = tnode;
            e1[cedge].neigh_spin[0] = e1[cedge].neigh_spin[1];
            e1[cedge].neigh_spin[1] = tspin;
          }
          else
          {
            // do nothing...
          }
        }
        chaser = burnt_loop[index - 1];
        endNode = e1[chaser].node_id[1];
      }
      while (index < numN);

      if(numN == 3)
      {
        numTri = numTri + 1;
      }
      else if(numN > 3)
      {
        numTri = numTri + (numN - 2);
      }
      else
      {
        //do nothing...
      }
      free(burnt_loop);
    }
  }

  free(burnt);
  free(burnt_list);
  free(count);

  return (numTri);
}

int CMUSurfaceMeshingFilter::get_triangles(int32_t* p, Patch *t, Face *sq, StructArray<Node>::Pointer v, Segment *e, neighbor *n, int ns, int nsp, int xDim)
{

  int i, ii, i1, i2, k;
  int sqID[6];
  int tsq; // current sq id...
  int tnfe; // temp number of edges...
  int nFC; // number of FC turned on...
  int tFCnode;
  int nFE; // number of face edges...
  int eff; // all the squares effective?...
  int cubeFlag; // if 1, we can do marching cube; if 0, useless...
  int bodyCtr; // cube center node...
  int *arrayFE;
  int *arrayFC;
  arrayFC = (int *)malloc(6 * sizeof(int));
  int fcid;
  int tindex;
  int tidIn, tidOut;
  tidIn = 0;
  int csite, nsite;
  double coord1[3], coord2[3];

  for (i = 1; i <= (ns - nsp); i++)
  {

    cubeFlag = 0;
    // for each marching cube, collect faces...
    sqID[0] = 3 * (i - 1);
    sqID[1] = 3 * (i - 1) + 1;
    sqID[2] = 3 * (i - 1) + 2;
    sqID[3] = 3 * i + 2;
    sqID[4] = 3 * (i + xDim - 1) + 1;
    sqID[5] = 3 * (i + nsp - 1);
    nFC = 0;
    nFE = 0;
    eff = 0;
    bodyCtr = 7 * (i - 1) + 6;
    //initialize face center array...
    for (ii = 0; ii < 6; ii++)
    {
      arrayFC[ii] = -1;
    }
    // Count the number of face center turned on and face edges...
    fcid = 0;
    ii = 0;
    for (ii = 0; ii < 6; ii++)
    {
      tsq = sqID[ii];
      tFCnode = sq[tsq].FCnode;
      if(tFCnode != -1)
      {
        arrayFC[fcid] = tFCnode;
        fcid++;
      }
      //nFC = nFC + 1;
      nFE = nFE + sq[tsq].nEdge;
      eff = eff + sq[tsq].effect;
    }
    nFC = fcid;
    //if(fcid!=nFC){ printf("Something's wrong with counting face centers...";}

    if(eff > 0)
    {
      cubeFlag = 1;
    }

    // Checking the number of edges for loops in the cube...
    if(nFE >= 3)
    {
      //printf("%4d", nFE);
    }
    else if(nFE > 0 && nFE < 3)
    {
      //printf("\t? %5d %3d\n", i, nFE);  // We have to ignore this case...
    }
    else if(nFE == 0)
    {
      //printf("\tcube inside grain";
    }
    else
    {
      printf("\twhat?");
    }

    // if the current marching cube is a collection of 6 effective squares...and
    // the number of face edges at least 3...
    // when nFE==2, it doen't happen
    // when nFE==1, the edge will contribute for the neighboring marching cube...
    // when nFE==0, it means the cube is inside a grain...
    if(cubeFlag == 1 && nFE > 2)
    {
      // get coordinates of corners 0 and 6, i.e. coordinates at site i and i+1+xDim+nsp...
      // this is for picking up inner edges when constructing triangles...
      csite = i;
      nsite = n[i].neigh_id[26];
      for (k = 0; k < 3; k++)
      {
        coord1[k] = p[i*3+k];
        coord2[k] = p[(i + 1 + xDim + nsp)*3+k];
      }
      // Make edge array for each marching cube...
      arrayFE = (int *)malloc(nFE * sizeof(int));
      tindex = 0;
      for (i1 = 0; i1 < 6; i1++)
      {
        tsq = sqID[i1];
        tnfe = sq[tsq].nEdge;
        if(tnfe != 0)
        {
          for (i2 = 0; i2 < tnfe; i2++)
          {
            arrayFE[tindex] = sq[tsq].edge_id[i2];
            tindex++;
          }
        }
      }

      if(tindex != nFE)
      {
        printf("Something wrong with counting number of edges for marching cube...");
      }

      // Consider each case as Z. Wu's paper...
      if(nFC == 0)
      { // when there's no face center
        //printf("%5d ", tidIn);
        get_case0_triangles(t, arrayFE, v, e, nFE, tidIn, &tidOut, coord1, coord2, i);
        tidIn = tidOut;
        //printf("%5d\n", tidIn);
      }
      else if(nFC == 2)
      {
        //printf("%5d ", tidIn);
        get_case2_triangles(t, arrayFE, v, e, nFE, arrayFC, nFC, tidIn, &tidOut, coord1, coord2, i);
        tidIn = tidOut;
        //printf("%5d\n", tidIn);
      }
      else if(nFC > 2 && nFC <= 6)
      {
        get_caseM_triangles(t, arrayFE, v, e, nFE, arrayFC, nFC, tidIn, &tidOut, bodyCtr, coord1, coord2, i);
        tidIn = tidOut;
      }
      else
      {
        printf("Somthing's wrong in counting face centers turned on...");
        printf("%5d %10d\n\n", nFC, i);
      }

      free(arrayFE);
    }
  }

  printf("\tnumber of triangles found = %5d\n", tidIn);
  return 0;
}

void CMUSurfaceMeshingFilter::get_case0_triangles(Patch *t1, int *afe, StructArray<Node>::Pointer vertices, Segment *e1, int nfedge, int tin, int *tout, double tcrd1[3], double tcrd2[3], int mcid)
{

  int ii, i, j, jj, k, kk, k1, mm;
  int loopID;
  int tail, head, coin;
  int cedge, nedge;
  int cspin1, cspin2, cnode1, cnode2;
  int nspin1, nspin2, nnode1, nnode2;
  int nucleus, chaser;
  int spinFlag, nodeFlag, flip;
  int bflag, nbflag;
  int *burnt;
  int *burnt_list;
  DataArray<int>::Pointer burntPtr = DataArray<int>::CreateArray(nfedge, 1, "burnt_array_surface_mesh");
  burnt = burntPtr->GetPointer(0);
 // burnt = (int *)malloc(nfedge * sizeof(int));

  DataArray<int>::Pointer burnt_listPtr = DataArray<int>::CreateArray(nfedge, 1, "nfedge_array_surface_mesh");
  burnt_list = burnt_listPtr->GetPointer(0);
  //burnt_list = (int *)malloc(nfedge * sizeof(int));

  int *count;
  int numN, sumN;
  int from;
  int *loop;
  int ctid;
  int front, back;
  int ce;
  int te0, te1, te2, tv0, tv1, tv2;
  int numT, cnumT, new_node0, new_node1;
  int tmcid;
  tmcid = mcid;

  int iii, jjj;
  int where[3];
  double vcrd1[3], vcrd2[3], vcrd3[3];
  double xhigh, xlow, yhigh, ylow, zhigh, zlow;
  xhigh = tcrd2[0];
  yhigh = tcrd2[1];
  zhigh = tcrd2[2];
  xlow = tcrd1[0];
  ylow = tcrd1[1];
  zlow = tcrd1[2];

  // initialize burn flags for face edges...
  for (ii = 0; ii < nfedge; ii++)
  {
    burnt[ii] = 0;
    burnt_list[ii] = -1;
  }

  loopID = 1;
  tail = 0;
  head = 0;

  for (i = 0; i < nfedge; i++)
  {

    cedge = afe[i];
    bflag = burnt[i];

    if(bflag == 0)
    {

      nucleus = cedge;
      burnt[i] = loopID;
      burnt_list[tail] = cedge;

      do
      {

        chaser = burnt_list[tail];
        cspin1 = e1[chaser].neigh_spin[0];
        cspin2 = e1[chaser].neigh_spin[1];
        cnode1 = e1[chaser].node_id[0];
        cnode2 = e1[chaser].node_id[1];

        for (j = 0; j < nfedge; j++)
        {

          nedge = afe[j];
          nbflag = burnt[j];

          if(nbflag == 0)
          {

            nspin1 = e1[nedge].neigh_spin[0];
            nspin2 = e1[nedge].neigh_spin[1];
            nnode1 = e1[nedge].node_id[0];
            nnode2 = e1[nedge].node_id[1];

            // checking if neighbor edge has same neighboring spins...
            if(((cspin1 == nspin1) && (cspin2 == nspin2)) || ((cspin1 == nspin2) && (cspin2 == nspin1)))
            {
              spinFlag = 1;
            }
            else
            {
              spinFlag = 0;
            }

            // checking if neighor egde is contiguous...
            if((cnode2 == nnode1) && (cnode1 != nnode2))
            {
              nodeFlag = 1;
              flip = 0;
            }
            else if((cnode2 == nnode2) && (cnode1 != nnode1))
            {
              nodeFlag = 1;
              flip = 1;
            }
            else
            {
              nodeFlag = 0;
              flip = 0;
            }

            if(spinFlag == 1 && nodeFlag == 1)
            {

              head = head + 1;
              burnt_list[head] = nedge;
              burnt[j] = loopID;

              if(flip == 1)
              {
                e1[nedge].neigh_spin[0] = nspin2;
                e1[nedge].neigh_spin[1] = nspin1;
                e1[nedge].node_id[0] = nnode2;
                e1[nedge].node_id[1] = nnode1;
              }

            }
            else
            {
              // do nothing...
            }

          }
          else
          {
            // do nothing...
          }
        }

        if(tail == head)
        {
          coin = 0;
          tail = tail + 1;
          head = tail;
          loopID++;
        }
        else
        {
          tail = tail + 1;
          coin = 1;
        }

      }
      while (coin);

    }
  }

  DataArray<int>::Pointer countPtr = DataArray<int>::CreateArray(loopID, 1, "count_array_surface_mesh");
  count = countPtr->GetPointer(0);

  for (k1 = 1; k1 < loopID; k1++)
  {
    count[k1] = 0;
  }

  for (k = 1; k < loopID; k++)
  {
    for (kk = 0; kk < nfedge; kk++)
    {
      if(k == burnt[kk])
      {
        count[k] = count[k] + 1;
      }
    }
  }

  // Let's do triangulation...
  sumN = 0;
  ctid = tin;


  StructArray<Node>& v1 = *vertices;
  for (jj = 1; jj < loopID; jj++)
  {

    numN = count[jj];
    sumN = sumN + numN;
    from = sumN - numN;

    DataArray<int>::Pointer loopPtr = DataArray<int>::CreateArray(numN, 1, "loop_array_surface_mesh");
    loop = loopPtr->GetPointer(0);

    for (mm = 0; mm < numN; mm++)
    {
      loop[mm] = burnt_list[from + mm];
    }

    if(numN == 3)
    {

      te0 = loop[0];
      te1 = loop[1];
      te2 = loop[2];
      tv0 = e1[te0].node_id[0];
      tv1 = e1[te1].node_id[0];
      tv2 = e1[te2].node_id[0];
      t1[ctid].node_id[0] = tv0;
      t1[ctid].node_id[1] = tv1;
      t1[ctid].node_id[2] = tv2;
      // Let's identify the place of edge, either face or inner...
      for (iii = 0; iii < 3; iii++)
      {
        vcrd1[iii] = v1[tv0].coord[iii];
        vcrd2[iii] = v1[tv1].coord[iii];
        vcrd3[iii] = v1[tv2].coord[iii];
      }
      // find edgePlace...
      find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
      // update edgePlace...
      for (jjj = 0; jjj < 3; jjj++)
      {
        t1[ctid].edgePlace[jjj] = where[jjj];
      }
      // update spins...
      t1[ctid].nSpin[0] = e1[te0].neigh_spin[0];
      t1[ctid].nSpin[1] = e1[te0].neigh_spin[1];
      t1[ctid].mCubeID = tmcid;
      ctid++;

    }
    else if(numN > 3)
    {

      numT = numN - 2;
      cnumT = 0;
      front = 0;
      back = numN - 1;

      te0 = loop[front];
      te1 = loop[back];
      tv0 = e1[te0].node_id[0];
      tv1 = e1[te0].node_id[1];
      tv2 = e1[te1].node_id[0];
      t1[ctid].node_id[0] = tv0;
      t1[ctid].node_id[1] = tv1;
      t1[ctid].node_id[2] = tv2;
      // Let's identify the place of edge, either face or inner...
      for (iii = 0; iii < 3; iii++)
      {
        vcrd1[iii] = v1[tv0].coord[iii];
        vcrd2[iii] = v1[tv1].coord[iii];
        vcrd3[iii] = v1[tv2].coord[iii];
      }
      // find edgePlace...
      find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
      // update edgePlace...
      for (jjj = 0; jjj < 3; jjj++)
      {
        t1[ctid].edgePlace[jjj] = where[jjj];
      }
      // update spins...
      t1[ctid].nSpin[0] = e1[te0].neigh_spin[0];
      t1[ctid].nSpin[1] = e1[te0].neigh_spin[1];
      t1[ctid].mCubeID = tmcid;
      new_node0 = tv2;
      new_node1 = tv1;

      cnumT++;
      ctid++;

      do
      {

        if((cnumT % 2) != 0)
        {

          front = front + 1;
          ce = loop[front];
          tv0 = e1[ce].node_id[0];
          tv1 = e1[ce].node_id[1];
          tv2 = new_node0;
          t1[ctid].node_id[0] = tv0;
          t1[ctid].node_id[1] = tv1;
          t1[ctid].node_id[2] = tv2;
          // Let's identify the place of edge, either face or inner...
          for (iii = 0; iii < 3; iii++)
          {
            vcrd1[iii] = v1[tv0].coord[iii];
            vcrd2[iii] = v1[tv1].coord[iii];
            vcrd3[iii] = v1[tv2].coord[iii];
          }
          // find edgePlace...
          find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
          // update edgePlace...
          for (jjj = 0; jjj < 3; jjj++)
          {
            t1[ctid].edgePlace[jjj] = where[jjj];
          }
          // update spins...
          t1[ctid].nSpin[0] = e1[ce].neigh_spin[0];
          t1[ctid].nSpin[1] = e1[ce].neigh_spin[1];
          t1[ctid].mCubeID = tmcid;
          new_node0 = tv1;
          cnumT++;
          ctid++;

        }
        else
        {

          back = back - 1;
          ce = loop[back];
          tv0 = e1[ce].node_id[0];
          tv1 = e1[ce].node_id[1];
          tv2 = new_node0;
          t1[ctid].node_id[0] = tv0;
          t1[ctid].node_id[1] = tv1;
          t1[ctid].node_id[2] = tv2;
          // Let's identify the place of edge, either face or inner...
          for (iii = 0; iii < 3; iii++)
          {
            vcrd1[iii] = v1[tv0].coord[iii];
            vcrd2[iii] = v1[tv1].coord[iii];
            vcrd3[iii] = v1[tv2].coord[iii];
          }
          // find edgePlace...
          find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
          // update edgePlace...
          for (jjj = 0; jjj < 3; jjj++)
          {
            t1[ctid].edgePlace[jjj] = where[jjj];
          }
          // update spins...
          t1[ctid].nSpin[0] = e1[ce].neigh_spin[0];
          t1[ctid].nSpin[1] = e1[ce].neigh_spin[1];
          t1[ctid].mCubeID = tmcid;
          new_node0 = tv0;
          cnumT++;
          ctid++;
        }

      }
      while (cnumT < numT);

    }
    else
    {
      // do nothing...
    }

    //free(loop);
  }

  *tout = ctid;
  //printf("%10d\n", ctid);

//  free(burnt);
//  free(burnt_list);
 // free(count);
}

void CMUSurfaceMeshingFilter::get_case2_triangles(Patch *t1,
                                                  int *afe,
                                                  StructArray<Node>::Pointer vertices,
                                                  Segment *e1,
                                                  int nfedge,
                                                  int *afc,
                                                  int nfctr,
                                                  int tin,
                                                  int *tout,
                                                  double tcrd1[3],
                                                  double tcrd2[3],
                                                  int mcid)
{

  int ii, i, j, k, kk, k1, n, i1, j1;
  int loopID;
  int tail, head, coin;
  int cedge, nedge;
  int cspin1, cspin2, cnode1, cnode2;
  int nspin1, nspin2, nnode1, nnode2;
  int tspin, tnode;
  int nucleus, chaser;
  int start, end;
  int from, to;
  int spinFlag, nodeFlag, flip;
  int bflag, nbflag;
  int *burnt;
  int *burnt_list;
  DataArray<int>::Pointer burntPtr = DataArray<int>::CreateArray(nfedge, 1, "burnt_array_surface_mesh");
  burnt = burntPtr->GetPointer(0);
 // burnt = (int *)malloc(nfedge * sizeof(int));

  DataArray<int>::Pointer burnt_listPtr = DataArray<int>::CreateArray(nfedge, 1, "nfedge_array_surface_mesh");
  burnt_list = burnt_listPtr->GetPointer(0);
  //burnt_list = (int *)malloc(nfedge * sizeof(int));

  int *count;
  int numN, numTri;
  int *burnt_loop;
  int openL; // if a loop is an open loop, it's 1; if closed, it's 0...
  int startEdge;
  int endNode;
  int index;
  //  int sumN;
  int ctid;
  int front, back;
  int ce;
  int te0, te1, te2, tv0, tv1, tv2;
  int numT, cnumT, new_node0, new_node1;
  int tmcid;
  tmcid = mcid;

  int iii, jjj;
  int where[3];
  double vcrd1[3], vcrd2[3], vcrd3[3];
  double xhigh, xlow, yhigh, ylow, zhigh, zlow;
  xhigh = tcrd2[0];
  yhigh = tcrd2[1];
  zhigh = tcrd2[2];
  xlow = tcrd1[0];
  ylow = tcrd1[1];
  zlow = tcrd1[2];

  // initialize burn flags for face edges...
  for (ii = 0; ii < nfedge; ii++)
  {
    burnt[ii] = 0;
    burnt_list[ii] = -1;
  }

  loopID = 1;
  tail = 0;
  head = 0;

  for (i = 0; i < nfedge; i++)
  {

    cedge = afe[i];
    bflag = burnt[i];

    if(bflag == 0)
    {

      nucleus = cedge;
      burnt[i] = loopID;
      burnt_list[tail] = cedge;

      do
      {

        chaser = burnt_list[tail];
        cspin1 = e1[chaser].neigh_spin[0];
        cspin2 = e1[chaser].neigh_spin[1];
        cnode1 = e1[chaser].node_id[0];
        cnode2 = e1[chaser].node_id[1];

        for (j = 0; j < nfedge; j++)
        {

          nedge = afe[j];
          nbflag = burnt[j];

          if(nbflag == 0)
          {

            nspin1 = e1[nedge].neigh_spin[0];
            nspin2 = e1[nedge].neigh_spin[1];
            nnode1 = e1[nedge].node_id[0];
            nnode2 = e1[nedge].node_id[1];

            // checking if neighbor edge has same neighboring spins...
            if(((cspin1 == nspin1) && (cspin2 == nspin2)) || ((cspin1 == nspin2) && (cspin2 == nspin1)))
            {
              spinFlag = 1;
            }
            else
            {
              spinFlag = 0;
            }

            // checking if neighor egde is contiguous...
            if((cnode1 == nnode1) && (cnode2 != nnode2))
            {
              nodeFlag = 1;
            }
            else if((cnode1 == nnode2) && (cnode2 != nnode1))
            {
              nodeFlag = 1;
            }
            else if((cnode2 == nnode1) && (cnode1 != nnode2))
            {
              nodeFlag = 1;
            }
            else if((cnode2 == nnode2) && (cnode1 != nnode1))
            {
              nodeFlag = 1;
            }
            else
            {
              nodeFlag = 0;
            }

            if(spinFlag == 1 && nodeFlag == 1)
            {

              head = head + 1;
              burnt_list[head] = nedge;
              burnt[j] = loopID;

            }
            else
            {
              // do nothing...
            }

          }
          else
          {
            // do nothing...
          }
        }

        if(tail == head)
        {
          coin = 0;
          tail = tail + 1;
          head = tail;
          loopID++;
        }
        else
        {
          tail = tail + 1;
          coin = 1;
        }

      }
      while (coin);
    }
  }

      DataArray<int>::Pointer countPtr = DataArray<int>::CreateArray(loopID, 1, "count_loop_array_surface_mesh");
      count = countPtr->GetPointer(0);
  //count = (int *)malloc(loopID * sizeof(int));

  for (k1 = 1; k1 < loopID; k1++)
  {
    count[k1] = 0;
  }

  for (k = 1; k < loopID; k++)
  {
    for (kk = 0; kk < nfedge; kk++)
    {
      if(k == burnt[kk])
      {
        count[k] = count[k] + 1;
      }
    }
  }

  // Let's make complete loops...
  numTri = 0;
  start = afc[0];
  end = afc[1];
  //printf("\n";
  //printf("%10d %10d\n", start, end);
  to = 0;
  from = 0;
  j1 = 1;

  // Let's do triangulation...
  ctid = tin;

  for (j1 = 1; j1 < loopID; j1++)
  {

    openL = 0; // current loop is closed...
    numN = count[j1];
    to = to + numN;
    from = to - numN;

      DataArray<int>::Pointer burnt_loopPtr = DataArray<int>::CreateArray(numN, 1, "burnt_loop_array_surface_mesh");
      burnt_loop = burnt_loopPtr->GetPointer(0);
//    burnt_loop = (int *)malloc(numN * sizeof(int));

    for (i1 = from; i1 < to; i1++)
    {

      cedge = burnt_list[i1];
      cnode1 = e1[cedge].node_id[0];
      cnode2 = e1[cedge].node_id[1];

      if(start == cnode1)
      {
        openL = 1; // loop is open...
        startEdge = cedge;
        flip = 0;
      }
      else if(start == cnode2)
      {
        openL = 1;
        startEdge = cedge;
        flip = 1;
      }
      else
      {
        // do nothing...
      }
    }
    //printf("   start edge & node: %5d %5d", startEdge, e1[startEdge].node_id[0]);
    //printf("   open flag: %2d", openL);
    //printf("   flip flag: %2d", flip);
    //printf("";

    if(openL == 1)
    { // if current loop is an open loop...

      if(flip == 1)
      {
        tnode = e1[startEdge].node_id[0];
        tspin = e1[startEdge].neigh_spin[0];
        e1[startEdge].node_id[0] = e1[startEdge].node_id[1];
        e1[startEdge].node_id[1] = tnode;
        e1[startEdge].neigh_spin[0] = e1[startEdge].neigh_spin[1];
        e1[startEdge].neigh_spin[1] = tspin;
      }
      else
      {
        // do nothing...
      }

      burnt_loop[0] = startEdge;
      index = 1;
      endNode = e1[startEdge].node_id[1];
      chaser = startEdge;

      do
      {

        for (n = from; n < to; n++)
        {

          cedge = burnt_list[n];
          cnode1 = e1[cedge].node_id[0];
          cnode2 = e1[cedge].node_id[1];
          if((cedge != chaser) && (endNode == cnode1))
          {
            burnt_loop[index] = cedge;
            index++;
          }
          else if((cedge != chaser) && (endNode == cnode2))
          {
            burnt_loop[index] = cedge;
            index++;
            // flip...
            tnode = e1[cedge].node_id[0];
            tspin = e1[cedge].neigh_spin[0];
            e1[cedge].node_id[0] = e1[cedge].node_id[1];
            e1[cedge].node_id[1] = tnode;
            e1[cedge].neigh_spin[0] = e1[cedge].neigh_spin[1];
            e1[cedge].neigh_spin[1] = tspin;
          }
          else
          {
            // do nothing...
          }
        }

        chaser = burnt_loop[index - 1];
        endNode = e1[chaser].node_id[1];

      }
      while (index < numN);

      StructArray<Node>& v1 = *vertices;
      if(numN == 2)
      {

        te0 = burnt_loop[0];
        te1 = burnt_loop[1];
        tv0 = e1[te0].node_id[0];
        tv1 = e1[te1].node_id[0];
        tv2 = e1[te1].node_id[1];
        t1[ctid].node_id[0] = tv0;
        t1[ctid].node_id[1] = tv1;
        t1[ctid].node_id[2] = tv2;
        // Let's identify the place of edge, either face or inner...
        for (iii = 0; iii < 3; iii++)
        {
          vcrd1[iii] = v1[tv0].coord[iii];
          vcrd2[iii] = v1[tv1].coord[iii];
          vcrd3[iii] = v1[tv2].coord[iii];
        }
        // find edgePlace...
        find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
        // update edgePlace...
        for (jjj = 0; jjj < 3; jjj++)
        {
          t1[ctid].edgePlace[jjj] = where[jjj];
        }
        // update spins...
        t1[ctid].nSpin[0] = e1[te0].neigh_spin[0];
        t1[ctid].nSpin[1] = e1[te0].neigh_spin[1];
        t1[ctid].mCubeID = tmcid;
        ctid++;

      }
      else if(numN > 2)
      {

        numT = numN - 1; // Note that it's open loop...
        cnumT = 0;
        front = 0;
        back = numN;

        te0 = burnt_loop[front];
        te1 = burnt_loop[back - 1];
        tv0 = e1[te0].node_id[0];
        tv1 = e1[te0].node_id[1];
        tv2 = e1[te1].node_id[1];
        t1[ctid].node_id[0] = tv0;
        t1[ctid].node_id[1] = tv1;
        t1[ctid].node_id[2] = tv2;
        // Let's identify the place of edge, either face or inner...
        for (iii = 0; iii < 3; iii++)
        {
          vcrd1[iii] = v1[tv0].coord[iii];
          vcrd2[iii] = v1[tv1].coord[iii];
          vcrd3[iii] = v1[tv2].coord[iii];
        }
        // find edgePlace...
        find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
        // update edgePlace...
        for (jjj = 0; jjj < 3; jjj++)
        {
          t1[ctid].edgePlace[jjj] = where[jjj];
        }
        // update spins...
        t1[ctid].nSpin[0] = e1[te0].neigh_spin[0];
        t1[ctid].nSpin[1] = e1[te0].neigh_spin[1];
        t1[ctid].mCubeID = tmcid;
        new_node0 = tv2;
        new_node1 = tv1;

        cnumT++;
        ctid++;

        do
        {

          if((cnumT % 2) != 0)
          {

            front = front + 1;
            ce = burnt_loop[front];
            tv0 = e1[ce].node_id[0];
            tv1 = e1[ce].node_id[1];
            tv2 = new_node0;
            t1[ctid].node_id[0] = tv0;
            t1[ctid].node_id[1] = tv1;
            t1[ctid].node_id[2] = tv2;
            // Let's identify the place of edge, either face or inner...
            for (iii = 0; iii < 3; iii++)
            {
              vcrd1[iii] = v1[tv0].coord[iii];
              vcrd2[iii] = v1[tv1].coord[iii];
              vcrd3[iii] = v1[tv2].coord[iii];
            }
            // find edgePlace...
            find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
            // update edgePlace...
            for (jjj = 0; jjj < 3; jjj++)
            {
              t1[ctid].edgePlace[jjj] = where[jjj];
            }
            // update spins...
            t1[ctid].nSpin[0] = e1[ce].neigh_spin[0];
            t1[ctid].nSpin[1] = e1[ce].neigh_spin[1];
            t1[ctid].mCubeID = tmcid;
            new_node0 = tv1;
            cnumT++;
            ctid++;

          }
          else
          {

            back = back - 1;
            ce = burnt_loop[back];
            tv0 = e1[ce].node_id[0];
            tv1 = e1[ce].node_id[1];
            tv2 = new_node0;
            t1[ctid].node_id[0] = tv0;
            t1[ctid].node_id[1] = tv1;
            t1[ctid].node_id[2] = tv2;
            // Let's identify the place of edge, either face or inner...
            for (iii = 0; iii < 3; iii++)
            {
              vcrd1[iii] = v1[tv0].coord[iii];
              vcrd2[iii] = v1[tv1].coord[iii];
              vcrd3[iii] = v1[tv2].coord[iii];
            }
            // find edgePlace...
            find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
            // update edgePlace...
            for (jjj = 0; jjj < 3; jjj++)
            {
              t1[ctid].edgePlace[jjj] = where[jjj];
            }
            // update spins...
            t1[ctid].nSpin[0] = e1[ce].neigh_spin[0];
            t1[ctid].nSpin[1] = e1[ce].neigh_spin[1];
            t1[ctid].mCubeID = tmcid;
            new_node0 = tv0;
            cnumT++;
            ctid++;
          }

        }
        while (cnumT < numT);

      }
      else
      {
        // do nothing...
      }

//      free(burnt_loop);

    }
    else
    { // if current loop is a closed one....i.e., openL = 0...

      startEdge = burnt_list[from];
      burnt_loop[0] = startEdge;
      index = 1;
      endNode = e1[startEdge].node_id[1];
      chaser = startEdge;

      do
      {

        for (n = from; n < to; n++)
        {

          cedge = burnt_list[n];
          cnode1 = e1[cedge].node_id[0];
          cnode2 = e1[cedge].node_id[1];
          if((cedge != chaser) && (endNode == cnode1))
          {
            burnt_loop[index] = cedge;
            index++;
          }
          else if((cedge != chaser) && (endNode == cnode2))
          {
            burnt_loop[index] = cedge;
            index++;
            // flip...
            tnode = e1[cedge].node_id[0];
            tspin = e1[cedge].neigh_spin[0];
            e1[cedge].node_id[0] = e1[cedge].node_id[1];
            e1[cedge].node_id[1] = tnode;
            e1[cedge].neigh_spin[0] = e1[cedge].neigh_spin[1];
            e1[cedge].neigh_spin[1] = tspin;
          }
          else
          {
            // do nothing...
          }
        }

        chaser = burnt_loop[index - 1];
        endNode = e1[chaser].node_id[1];

      }
      while (index < numN);

      StructArray<Node>& v1 = *vertices;
      if(numN == 3)
      {

        te0 = burnt_loop[0];
        te1 = burnt_loop[1];
        te2 = burnt_loop[2];
        tv0 = e1[te0].node_id[0];
        tv1 = e1[te1].node_id[0];
        tv2 = e1[te2].node_id[0];
        t1[ctid].node_id[0] = tv0;
        t1[ctid].node_id[1] = tv1;
        t1[ctid].node_id[2] = tv2;
        // Let's identify the place of edge, either face or inner...
        for (iii = 0; iii < 3; iii++)
        {
          vcrd1[iii] = v1[tv0].coord[iii];
          vcrd2[iii] = v1[tv1].coord[iii];
          vcrd3[iii] = v1[tv2].coord[iii];
        }
        // find edgePlace...
        find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
        // update edgePlace...
        for (jjj = 0; jjj < 3; jjj++)
        {
          t1[ctid].edgePlace[jjj] = where[jjj];
        }
        // update spins...
        t1[ctid].nSpin[0] = e1[te0].neigh_spin[0];
        t1[ctid].nSpin[1] = e1[te0].neigh_spin[1];
        t1[ctid].mCubeID = tmcid;
        ctid++;

      }
      else if(numN > 3)
      {

        numT = numN - 2;
        cnumT = 0;
        front = 0;
        back = numN - 1;

        te0 = burnt_loop[front];
        te1 = burnt_loop[back];
        tv0 = e1[te0].node_id[0];
        tv1 = e1[te0].node_id[1];
        tv2 = e1[te1].node_id[0];
        t1[ctid].node_id[0] = tv0;
        t1[ctid].node_id[1] = tv1;
        t1[ctid].node_id[2] = tv2;
        // Let's identify the place of edge, either face or inner...
        for (iii = 0; iii < 3; iii++)
        {
          vcrd1[iii] = v1[tv0].coord[iii];
          vcrd2[iii] = v1[tv1].coord[iii];
          vcrd3[iii] = v1[tv2].coord[iii];
        }
        // find edgePlace...
        find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
        // update edgePlace...
        for (jjj = 0; jjj < 3; jjj++)
        {
          t1[ctid].edgePlace[jjj] = where[jjj];
        }
        // update spins...
        t1[ctid].nSpin[0] = e1[te0].neigh_spin[0];
        t1[ctid].nSpin[1] = e1[te0].neigh_spin[1];
        t1[ctid].mCubeID = tmcid;
        new_node0 = tv2;
        new_node1 = tv1;

        cnumT++;
        ctid++;

        do
        {

          if((cnumT % 2) != 0)
          {

            front = front + 1;
            ce = burnt_loop[front];
            tv0 = e1[ce].node_id[0];
            tv1 = e1[ce].node_id[1];
            tv2 = new_node0;
            t1[ctid].node_id[0] = tv0;
            t1[ctid].node_id[1] = tv1;
            t1[ctid].node_id[2] = tv2;
            // Let's identify the place of edge, either face or inner...
            for (iii = 0; iii < 3; iii++)
            {
              vcrd1[iii] = v1[tv0].coord[iii];
              vcrd2[iii] = v1[tv1].coord[iii];
              vcrd3[iii] = v1[tv2].coord[iii];
            }
            // find edgePlace...
            find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
            // update edgePlace...
            for (jjj = 0; jjj < 3; jjj++)
            {
              t1[ctid].edgePlace[jjj] = where[jjj];
            }
            // update spins...
            t1[ctid].nSpin[0] = e1[ce].neigh_spin[0];
            t1[ctid].nSpin[1] = e1[ce].neigh_spin[1];
            t1[ctid].mCubeID = tmcid;
            new_node0 = tv1;
            cnumT++;
            ctid++;

          }
          else
          {

            back = back - 1;
            ce = burnt_loop[back];
            tv0 = e1[ce].node_id[0];
            tv1 = e1[ce].node_id[1];
            tv2 = new_node0;
            t1[ctid].node_id[0] = tv0;
            t1[ctid].node_id[1] = tv1;
            t1[ctid].node_id[2] = tv2;
            // Let's identify the place of edge, either face or inner...
            for (iii = 0; iii < 3; iii++)
            {
              vcrd1[iii] = v1[tv0].coord[iii];
              vcrd2[iii] = v1[tv1].coord[iii];
              vcrd3[iii] = v1[tv2].coord[iii];
            }
            // find edgePlace...
            find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
            // update edgePlace...
            for (jjj = 0; jjj < 3; jjj++)
            {
              t1[ctid].edgePlace[jjj] = where[jjj];
            }
            // update spins...
            t1[ctid].nSpin[0] = e1[ce].neigh_spin[0];
            t1[ctid].nSpin[1] = e1[ce].neigh_spin[1];
            t1[ctid].mCubeID = tmcid;
            new_node0 = tv0;
            cnumT++;
            ctid++;
          }

        }
        while (cnumT < numT);

      }
      else
      {
        // do nothing...
      }

     // free(burnt_loop);
    }
  }

  *tout = ctid;
  //printf("%10d ", ctid);

 // free(burnt);
 // free(burnt_list);
 // free(count);
}

void CMUSurfaceMeshingFilter::get_caseM_triangles(Patch *t1,
                                                  int *afe,
                                                  StructArray<Node>::Pointer vertices,
                                                  Segment *e1,
                                                  int nfedge,
                                                  int *afc,
                                                  int nfctr,
                                                  int tin,
                                                  int *tout,
                                                  int ccn,
                                                  double tcrd1[3],
                                                  double tcrd2[3],
                                                  int mcid)
{

  int ii, i, j, k, kk, k1, n, i1, j1, n1, iii;
  int loopID;
  int tail, head, coin;
  int cedge, nedge;
  int cspin1, cspin2, cnode1, cnode2;
  int nspin1, nspin2, nnode1, nnode2;
  int tspin, tnode;
  int nucleus, chaser;
  int start;
  int from, to;
  int spinFlag, nodeFlag, flip;
  int bflag, nbflag;
  int *burnt;
  int *burnt_list;
  DataArray<int>::Pointer burntPtr = DataArray<int>::CreateArray(nfedge, 1, "burnt_array_surface_mesh");
  burnt = burntPtr->GetPointer(0);
 // burnt = (int *)malloc(nfedge * sizeof(int));

  DataArray<int>::Pointer burnt_listPtr = DataArray<int>::CreateArray(nfedge, 1, "nfedge_array_surface_mesh");
  burnt_list = burnt_listPtr->GetPointer(0);
  //burnt_list = (int *)malloc(nfedge * sizeof(int));

  int *count;
  int numN, numTri;
  int tn0, tn1;
  int *burnt_loop;
  int openL; // if a loop is an open loop, it's 1; if closed, it's 0...
  int startEdge;
  int endNode;
  int index;
  int ctid;
  int front, back;
  int ce;
  int te0, te1, te2, tv0, tv1, tv2, ts0, ts1;
  int numT, cnumT, new_node0, new_node1;
  int tmcid;
  tmcid = mcid;

  int i4, jjj;
  int where[3];
  double vcrd1[3], vcrd2[3], vcrd3[3];
  double xhigh, xlow, yhigh, ylow, zhigh, zlow;
  xhigh = tcrd2[0];
  yhigh = tcrd2[1];
  zhigh = tcrd2[2];
  xlow = tcrd1[0];
  ylow = tcrd1[1];
  zlow = tcrd1[2];

  StructArray<Node>& v1 = *vertices;
  // initialize burn flags for face edges...
  for (ii = 0; ii < nfedge; ii++)
  {
    burnt[ii] = 0;
    burnt_list[ii] = -1;
  }

  loopID = 1;
  tail = 0;
  head = 0;

  for (i = 0; i < nfedge; i++)
  {

    cedge = afe[i];
    bflag = burnt[i];

    if(bflag == 0)
    {

      nucleus = cedge;
      burnt[i] = loopID;
      burnt_list[tail] = cedge;

      do
      {

        chaser = burnt_list[tail];
        cspin1 = e1[chaser].neigh_spin[0];
        cspin2 = e1[chaser].neigh_spin[1];
        cnode1 = e1[chaser].node_id[0];
        cnode2 = e1[chaser].node_id[1];

        for (j = 0; j < nfedge; j++)
        {

          nedge = afe[j];
          nbflag = burnt[j];

          if(nbflag == 0)
          {

            nspin1 = e1[nedge].neigh_spin[0];
            nspin2 = e1[nedge].neigh_spin[1];
            nnode1 = e1[nedge].node_id[0];
            nnode2 = e1[nedge].node_id[1];

            // checking if neighbor edge has same neighboring spins...
            if(((cspin1 == nspin1) && (cspin2 == nspin2)) || ((cspin1 == nspin2) && (cspin2 == nspin1)))
            {
              spinFlag = 1;
            }
            else
            {
              spinFlag = 0;
            }

            // checking if neighor egde is contiguous...
            if((cnode1 == nnode1) && (cnode2 != nnode2))
            {
              nodeFlag = 1;
            }
            else if((cnode1 == nnode2) && (cnode2 != nnode1))
            {
              nodeFlag = 1;
            }
            else if((cnode2 == nnode1) && (cnode1 != nnode2))
            {
              nodeFlag = 1;
            }
            else if((cnode2 == nnode2) && (cnode1 != nnode1))
            {
              nodeFlag = 1;
            }
            else
            {
              nodeFlag = 0;
            }

            if(spinFlag == 1 && nodeFlag == 1)
            {

              head = head + 1;
              burnt_list[head] = nedge;
              burnt[j] = loopID;

            }
            else
            {
              // do nothing...
            }

          }
          else
          {
            // do nothing...
          }
        }

        if(tail == head)
        {
          coin = 0;
          tail = tail + 1;
          head = tail;
          loopID++;
        }
        else
        {
          tail = tail + 1;
          coin = 1;
        }

      }
      while (coin);
    }
  }

      DataArray<int>::Pointer countPtr = DataArray<int>::CreateArray(loopID, 1, "count_loop_array_surface_mesh");
      count = countPtr->GetPointer(0);
  //count = (int *)malloc(loopID * sizeof(int));

  for (k1 = 1; k1 < loopID; k1++)
  {
    count[k1] = 0;
  }

  for (k = 1; k < loopID; k++)
  {
    for (kk = 0; kk < nfedge; kk++)
    {
      if(k == burnt[kk])
      {
        count[k] = count[k] + 1;
      }
    }
  }

  // Let's make complete loops...
  numTri = 0;
  to = 0;
  from = 0;
  j1 = 1;

  ctid = tin;

  for (j1 = 1; j1 < loopID; j1++)
  {

    openL = 0; // current loop is closed...
    numN = count[j1];
    to = to + numN;
    from = to - numN;
      DataArray<int>::Pointer burnt_loopPtr = DataArray<int>::CreateArray(numN, 1, "burnt_loop_array_surface_mesh");
      burnt_loop = burnt_loopPtr->GetPointer(0);
//    burnt_loop = (int *)malloc(numN * sizeof(int));

    for (i1 = from; i1 < to; i1++)
    {

      cedge = burnt_list[i1];
      cnode1 = e1[cedge].node_id[0];
      cnode2 = e1[cedge].node_id[1];

      for (n1 = 0; n1 < nfctr; n1++)
      {

        start = afc[n1];

        if(start == cnode1)
        {
          openL = 1; // loop is open...
          startEdge = cedge;
          flip = 0;
        }
        else if(start == cnode2)
        {
          openL = 1;
          startEdge = cedge;
          flip = 1;
        }
        else
        {
          // do nothing...
        }
      }
    }

    if(openL == 1)
    { // if current loop is an open loop...

      if(flip == 1)
      {
        tnode = e1[startEdge].node_id[0];
        tspin = e1[startEdge].neigh_spin[0];
        e1[startEdge].node_id[0] = e1[startEdge].node_id[1];
        e1[startEdge].node_id[1] = tnode;
        e1[startEdge].neigh_spin[0] = e1[startEdge].neigh_spin[1];
        e1[startEdge].neigh_spin[1] = tspin;
      }
      else
      {
        // do nothing...
      }

      burnt_loop[0] = startEdge;
      index = 1;
      endNode = e1[startEdge].node_id[1];
      chaser = startEdge;

      do
      {

        for (n = from; n < to; n++)
        {

          cedge = burnt_list[n];
          cnode1 = e1[cedge].node_id[0];
          cnode2 = e1[cedge].node_id[1];
          if((cedge != chaser) && (endNode == cnode1))
          {
            burnt_loop[index] = cedge;
            index++;
          }
          else if((cedge != chaser) && (endNode == cnode2))
          {
            burnt_loop[index] = cedge;
            index++;
            // flip...
            tnode = e1[cedge].node_id[0];
            tspin = e1[cedge].neigh_spin[0];
            e1[cedge].node_id[0] = e1[cedge].node_id[1];
            e1[cedge].node_id[1] = tnode;
            e1[cedge].neigh_spin[0] = e1[cedge].neigh_spin[1];
            e1[cedge].neigh_spin[1] = tspin;
          }
          else
          {
            // do nothing...
          }
        }

        chaser = burnt_loop[index - 1];
        endNode = e1[chaser].node_id[1];

      }
      while (index < numN);

      //triangulation...
      for (iii = 0; iii < numN; iii++)
      {
        ce = burnt_loop[iii];
        tn0 = e1[ce].node_id[0];
        tn1 = e1[ce].node_id[1];
        ts0 = e1[ce].neigh_spin[0];
        ts1 = e1[ce].neigh_spin[1];
        t1[ctid].node_id[0] = ccn;
        t1[ctid].node_id[1] = tn0;
        t1[ctid].node_id[2] = tn1;
        // Let's identify the place of edge, either face or inner...
        for (i4 = 0; i4 < 3; i4++)
        {
          vcrd1[i4] = v1[ccn].coord[i4];
          vcrd2[i4] = v1[tn0].coord[i4];
          vcrd3[i4] = v1[tn1].coord[i4];
        }
        // find edgePlace...
        find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
        // update edgePlace...
        for (jjj = 0; jjj < 3; jjj++)
        {
          t1[ctid].edgePlace[jjj] = where[jjj];
        }
        // update spins...
        t1[ctid].nSpin[0] = ts0;
        t1[ctid].nSpin[1] = ts1;
        t1[ctid].mCubeID = tmcid;
        ctid++;
      }

    //  free(burnt_loop);

    }
    else
    { // if current loop is a closed one....i.e., openL = 0...

      startEdge = burnt_list[from];
      burnt_loop[0] = startEdge;
      index = 1;
      endNode = e1[startEdge].node_id[1];
      chaser = startEdge;

      do
      {

        for (n = from; n < to; n++)
        {

          cedge = burnt_list[n];
          cnode1 = e1[cedge].node_id[0];
          cnode2 = e1[cedge].node_id[1];
          if((cedge != chaser) && (endNode == cnode1))
          {
            burnt_loop[index] = cedge;
            index++;
          }
          else if((cedge != chaser) && (endNode == cnode2))
          {
            burnt_loop[index] = cedge;
            index++;
            // flip...
            tnode = e1[cedge].node_id[0];
            tspin = e1[cedge].neigh_spin[0];
            e1[cedge].node_id[0] = e1[cedge].node_id[1];
            e1[cedge].node_id[1] = tnode;
            e1[cedge].neigh_spin[0] = e1[cedge].neigh_spin[1];
            e1[cedge].neigh_spin[1] = tspin;
          }
          else
          {
            // do nothing...
          }
        }

        chaser = burnt_loop[index - 1];
        endNode = e1[chaser].node_id[1];

      }
      while (index < numN);

      if(numN == 3)
      {

        te0 = burnt_loop[0];
        te1 = burnt_loop[1];
        te2 = burnt_loop[2];
        tv0 = e1[te0].node_id[0];
        tv1 = e1[te1].node_id[0];
        tv2 = e1[te2].node_id[0];
        t1[ctid].node_id[0] = tv0;
        t1[ctid].node_id[1] = tv1;
        t1[ctid].node_id[2] = tv2;
        // Let's identify the place of edge, either face or inner...
        for (i4 = 0; i4 < 3; i4++)
        {
          vcrd1[i4] = v1[tv0].coord[i4];
          vcrd2[i4] = v1[tv1].coord[i4];
          vcrd3[i4] = v1[tv2].coord[i4];
        }
        // find edgePlace...
        find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
        // update edgePlace...
        for (jjj = 0; jjj < 3; jjj++)
        {
          t1[ctid].edgePlace[jjj] = where[jjj];
        }
        // update spins...
        t1[ctid].nSpin[0] = e1[te0].neigh_spin[0];
        t1[ctid].nSpin[1] = e1[te0].neigh_spin[1];
        t1[ctid].mCubeID = tmcid;
        ctid++;

      }
      else if(numN > 3)
      {

        numT = numN - 2;
        cnumT = 0;
        front = 0;
        back = numN - 1;

        te0 = burnt_loop[front];
        te1 = burnt_loop[back];
        tv0 = e1[te0].node_id[0];
        tv1 = e1[te0].node_id[1];
        tv2 = e1[te1].node_id[0];
        t1[ctid].node_id[0] = tv0;
        t1[ctid].node_id[1] = tv1;
        t1[ctid].node_id[2] = tv2;
        // Let's identify the place of edge, either face or inner...
        for (i4 = 0; i4 < 3; i4++)
        {
          vcrd1[i4] = v1[tv0].coord[i4];
          vcrd2[i4] = v1[tv1].coord[i4];
          vcrd3[i4] = v1[tv2].coord[i4];
        }
        // find edgePlace...
        find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
        // update edgePlace...
        for (jjj = 0; jjj < 3; jjj++)
        {
          t1[ctid].edgePlace[jjj] = where[jjj];
        }
        // update spins...
        t1[ctid].nSpin[0] = e1[te0].neigh_spin[0];
        t1[ctid].nSpin[1] = e1[te0].neigh_spin[1];
        t1[ctid].mCubeID = tmcid;
        new_node0 = tv2;
        new_node1 = tv1;

        cnumT++;
        ctid++;

        do
        {

          if((cnumT % 2) != 0)
          {

            front = front + 1;
            ce = burnt_loop[front];
            tv0 = e1[ce].node_id[0];
            tv1 = e1[ce].node_id[1];
            tv2 = new_node0;
            t1[ctid].node_id[0] = tv0;
            t1[ctid].node_id[1] = tv1;
            t1[ctid].node_id[2] = tv2;
            // Let's identify the place of edge, either face or inner...
            for (i4 = 0; i4 < 3; i4++)
            {
              vcrd1[i4] = v1[tv0].coord[i4];
              vcrd2[i4] = v1[tv1].coord[i4];
              vcrd3[i4] = v1[tv2].coord[i4];
            }
            // find edgePlace...
            find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
            // update edgePlace...
            for (jjj = 0; jjj < 3; jjj++)
            {
              t1[ctid].edgePlace[jjj] = where[jjj];
            }
            // update spins...
            t1[ctid].nSpin[0] = e1[ce].neigh_spin[0];
            t1[ctid].nSpin[1] = e1[ce].neigh_spin[1];
            t1[ctid].mCubeID = tmcid;
            new_node0 = tv1;
            cnumT++;
            ctid++;

          }
          else
          {

            back = back - 1;
            ce = burnt_loop[back];
            tv0 = e1[ce].node_id[0];
            tv1 = e1[ce].node_id[1];
            tv2 = new_node0;
            t1[ctid].node_id[0] = tv0;
            t1[ctid].node_id[1] = tv1;
            t1[ctid].node_id[2] = tv2;
            // Let's identify the place of edge, either face or inner...
            for (i4 = 0; i4 < 3; i4++)
            {
              vcrd1[i4] = v1[tv0].coord[i4];
              vcrd2[i4] = v1[tv1].coord[i4];
              vcrd3[i4] = v1[tv2].coord[i4];
            }
            // find edgePlace...
            find_edgePlace(vcrd1, vcrd2, vcrd3, where, xhigh, xlow, yhigh, ylow, zhigh, zlow);
            // update edgePlace...
            for (jjj = 0; jjj < 3; jjj++)
            {
              t1[ctid].edgePlace[jjj] = where[jjj];
            }
            // update spins...
            t1[ctid].nSpin[0] = e1[ce].neigh_spin[0];
            t1[ctid].nSpin[1] = e1[ce].neigh_spin[1];
            t1[ctid].mCubeID = tmcid;
            new_node0 = tv0;
            cnumT++;
            ctid++;
          }

        }
        while (cnumT < numT);

      }
      else
      {
        // do nothing...
      }
     // free(burnt_loop);
    }
  }

  *tout = ctid;

 // free(burnt);
 // free(burnt_list);
 // free(count);
}

void CMUSurfaceMeshingFilter::find_edgePlace(double tvcrd1[3], double tvcrd2[3], double tvcrd3[3], int tw[3], double xh, double xl, double yh, double yl, double zh, double zl)
{

  double txc, tyc, tzc;
  double tx1, tx2, tx3;
  double ty1, ty2, ty3;
  double tz1, tz2, tz3;
  double eps;
  int count, count1;

  eps = 1.0e-6;
  count = 0;
  count1 = 0;

  tx1 = tvcrd1[0];
  tx2 = tvcrd2[0];
  tx3 = tvcrd3[0];
  ty1 = tvcrd1[1];
  ty2 = tvcrd2[1];
  ty3 = tvcrd3[1];
  tz1 = tvcrd1[2];
  tz2 = tvcrd2[2];
  tz3 = tvcrd3[2];
  //printf("%5f %5f   %5f %5f   %5f %5f   %5f %5f %5f\n", xh, xl, yh, yl, zh, zl, xh-xl, yh-yl, zh-zl);

  // find inner edges, between corner 0 and 1...
  txc = (tx1 + tx2) / 2.0;
  tyc = (ty1 + ty2) / 2.0;
  tzc = (tz1 + tz2) / 2.0;
  if((txc < (xh - eps) && txc > (xl + eps)) && (tyc < (yh - eps) && tyc > (yl + eps)) && (tzc < (zh - eps) && tzc > (zl + eps)))
  {
    tw[0] = 1;
  }
  else
  {
    tw[0] = 1;
    count1++;
  }

  // find inner edges, between corner 1 and 2...
  txc = (tx2 + tx3) / 2.0;
  tyc = (ty2 + ty3) / 2.0;
  tzc = (tz2 + tz3) / 2.0;
  if((txc < (xh - eps) && txc > (xl + eps)) && (tyc < (yh - eps) && tyc > (yl + eps)) && (tzc < (zh - eps) && tzc > (zl + eps)))
  {
    tw[1] = 1;
  }
  else
  {
    tw[1] = 1;
    count1++;
  }

  // find inner edges, between corner 2 and 0...
  txc = (tx3 + tx1) / 2.0;
  tyc = (ty3 + ty1) / 2.0;
  tzc = (tz3 + tz1) / 2.0;
  if((txc < (xh - eps) && txc > (xl + eps)) && (tyc < (yh - eps) && tyc > (yl + eps)) && (tzc < (zh - eps) && tzc > (zl + eps)))
  {
    tw[2] = 1;
  }
  else
  {
    tw[2] = 1;
    count1++;
  }

}

void CMUSurfaceMeshingFilter::update_triangle_sides_with_fedge(Patch *t, Segment *e, Face *sq, int nT, int xDim, int nsp)
{

  int i, ii, i1, i2, j, k;
  int sqID[6];
  int tFEarray[100]; // max number is 24 but set up at 100...
  int index, tsq, nFE;
  int index1, index2;
  int cnode1, cnode2, tnode1, tnode2;
  int prevMCID;
  int cfe;

  prevMCID = -1;

  for (i = 0; i < nT; i++)
  {

    ii = t[i].mCubeID;

    if(ii != prevMCID)
    {
      // if next triangle is in the same marching cube, don,t need to update face edges...
      nFE = 0;
      index = 0;
      // for each marching cube ii, collect faces...
      sqID[0] = 3 * (ii - 1);
      sqID[1] = 3 * (ii - 1) + 1;
      sqID[2] = 3 * (ii - 1) + 2;
      sqID[3] = 3 * ii + 2;
      sqID[4] = 3 * (ii + xDim - 1) + 1;
      sqID[5] = 3 * (ii + nsp - 1);

      for (i1 = 0; i1 < 6; i1++)
      {
        tsq = sqID[i1];
        nFE = sq[tsq].nEdge;
        for (i2 = 0; i2 < nFE; i2++)
        {
          tFEarray[index] = sq[tsq].edge_id[i2];
          index++;
        }
      }
    }

    for (j = 0; j < 3; j++)
    {
      //printf("%6d   %6d\n", i, j);
      index1 = j;
      index2 = j + 1;
      if(index2 == 3)
      {
        index2 = 0;
      }
      cnode1 = t[i].node_id[index1];
      cnode2 = t[i].node_id[index2];

      for (k = 0; k < index; k++)
      {
        cfe = tFEarray[k];
        tnode1 = e[cfe].node_id[0];
        tnode2 = e[cfe].node_id[1];
        if((cnode1 == tnode1 && cnode2 == tnode2) || (cnode2 == tnode1 && cnode1 == tnode2))
        {
          t[i].e_id[index1] = cfe;
          t[i].edgePlace[index1] = 0;
          //printf("break!\n********";
          break;
        }
      }

    }

    prevMCID = ii;
  }

}

int CMUSurfaceMeshingFilter::get_number_unique_inner_edges(Patch *t, int nT)
{

  int i, j, k, kk, m, mm;
  int cmcID, nmcID; // marching cube ids for the current triangle and next triangle...
  int nIEDmc, nIEmc; // number of inner edges, including duplicates, and unique inner edges in the current marching cube...
  int nIED, nIE; // total number of inner edges, including duplicates and unique inner edges...
  int index, index1, index2;
  int numT, cnode1, cnode2, nnode1, nnode2;
  //  int arrayTri[24];        // max number of triangles inside a marching cube is 24...
  int arrayIEnode[120][2]; // max number of unique inner edges inside a marching cube is 36 and each has 2 nodes...
  int bFlag[120]; // burnFlag for unique inner edges...

  numT = nT;
  nIED = 0;
  nIE = 0;
  index = 0;

  for (mm = 0; mm < 120; mm++)
  {
    bFlag[mm] = 0;
    arrayIEnode[mm][0] = -1;
    arrayIEnode[mm][1] = -1;
  }

  i = 0;
  // make inner edge array, including duplicates inside each marching cube...
  do
  {
    //printf("triangle %10d -->", i);
    cmcID = t[i].mCubeID;
    nmcID = t[i + 1].mCubeID;
    if(i == (numT - 1))
    {
      nmcID = -1;
    } // Let's get out when it hits the last triangle...
    //printf("cmcID = %10d, nmcID = %10d, index = %10d\n", cmcID, nmcID, index);

    for (j = 0; j < 3; j++)
    {
      if(t[i].edgePlace[j] == 1)
      { // only for inner edges...
        index1 = j;
        index2 = j + 1;
        if(index2 == 3)
        {
          index2 = 0;
        }
        arrayIEnode[index][0] = t[i].node_id[index1];
        arrayIEnode[index][1] = t[i].node_id[index2];
        index++;
      }
    }

    if(cmcID != nmcID)
    {
      // once we find the array, i.e.cmcID!=nmcID, count number of unique inner edge inside the marching cube...
      nIEDmc = index;
      nIED = nIED + nIEDmc; // update total number of inner, duplicate, edges...
      //printf("\n*****num IED mc = %5d\n\n", nIEDmc);

      for (m = 0; m < nIEDmc; m++)
      {
        bFlag[m] = 0;
      } // initialize burn flag...
      nIEmc = 0; // total number of unique inner edges in a marching cube...

      for (k = 0; k < nIEDmc; k++)
      {

        if(bFlag[k] == 0)
        {

          cnode1 = arrayIEnode[k][0];
          cnode2 = arrayIEnode[k][1];
          bFlag[k] = -1;

          for (kk = 0; kk < nIEDmc; kk++)
          {
            if(bFlag[kk] == 0)
            {
              nnode1 = arrayIEnode[kk][0];
              nnode2 = arrayIEnode[kk][1];
              if((cnode1 == nnode1 && cnode2 == nnode2) || (cnode2 == nnode1 && cnode1 == nnode2))
              {
                bFlag[kk] = -1;
              }
            }
          }
          nIEmc++;
        }
      }
      nIE = nIE + nIEmc; // total number of unique inner edges...
      index = 0;
    }

    i++;
    //printf("";

  }
  while (i < numT);

  printf("\ttotal number of inner edges including duplicates = %d\n", nIED);
  printf("\ttotal number of unique inner edges = %d\n", nIE);

  return (nIE);
}

void CMUSurfaceMeshingFilter::get_unique_inner_edges(Patch *t, isegment *ie, int nT, int nfedge)
{

  int i, j, k, kk, m, mm, ii, jj, jjj;
  int cmcID, nmcID; // marching cube ids for the current triangle and next triangle...
  int nIEDmc; // number of inner edges, including duplicates, and unique inner edges in the current marching cube...
  int nIED; // total number of inner edges, including duplicates and unique inner edges...
  int index, index1, index2;
  int numT, cnode1, cnode2, nnode1, nnode2;
  int arrayTri[120]; // max number of triangles inside a marching cube is 24...Triangle ids, matched with arrayIEnode...
  int arrayIEnode[120][2]; // max number of unique inner edges inside a marching cube is 36 and each has 2 nodes...
  int bFlag[120]; // burnFlag for unique inner edges...
  int IEindex, ctri, cspin1, cspin2, ntri, nspin1, nspin2, tedgeKind;
  int nspin1Flag, nspin2Flag;
  int tnode1, tnode2;

  numT = nT;
  nIED = 0;
  index = 0;
  IEindex = 0;

  for (mm = 0; mm < 120; mm++)
  {
    bFlag[mm] = 0;
    arrayIEnode[mm][0] = -1;
    arrayIEnode[mm][1] = -1;
  }

  i = 0;
  // make inner edge array, including duplicates inside each marching cube...
  do
  {
    //printf("triangle %5d    ", i);
    cmcID = t[i].mCubeID;
    nmcID = t[i + 1].mCubeID;
    if(i == (numT - 1))
    {
      nmcID = -1;
    } // Let's get out when it hits the last triangle...

    for (j = 0; j < 3; j++)
    {
      if(t[i].edgePlace[j] == 1)
      { // only for inner edges...
        index1 = j;
        index2 = j + 1;
        if(index2 == 3)
        {
          index2 = 0;
        }
        arrayIEnode[index][0] = t[i].node_id[index1];
        arrayIEnode[index][1] = t[i].node_id[index2];
        arrayTri[index] = i;
        index++;
      }
    }

    if(cmcID != nmcID)
    {
      // once we find the array, i.e.cmcID!=nmcID, count number of unique inner edge inside the marching cube...
      nIEDmc = index;

      for (m = 0; m <= nIEDmc; m++)
      {
        bFlag[m] = 0;
      } // initialize burn flag...

      for (k = 0; k < nIEDmc; k++)
      {

        if(bFlag[k] == 0)
        {

          cnode1 = arrayIEnode[k][0];
          cnode2 = arrayIEnode[k][1];
          bFlag[k] = -1;
          // update inner edge information...
          ie[IEindex].node_id[0] = cnode1; // nodes...
          ie[IEindex].node_id[1] = cnode2;
          ctri = arrayTri[k]; // current triangle and neighboring spins...
          cspin1 = t[ctri].nSpin[0];
          cspin2 = t[ctri].nSpin[1];
          ie[IEindex].nSpin[0] = cspin1; // update inner edges in terms of spin...
          ie[IEindex].nSpin[1] = cspin2;
          ie[IEindex].nSpin[2] = 0;
          ie[IEindex].nSpin[3] = 0;
          tedgeKind = 2; // initially edge kind is 2...
          // update triangle edge information; update only sides of triangles that are inner edges!
          for (jj = 0; jj < 3; jj++)
          {
            if(t[ctri].edgePlace[jj] == 1)
            { // only for inner edges...
              index1 = jj;
              index2 = jj + 1;
              if(index2 == 3)
              {
                index2 = 0;
              }
              tnode1 = t[ctri].node_id[index1];
              tnode2 = t[ctri].node_id[index2];
              if((tnode1 == cnode1 && tnode2 == cnode2) || (tnode2 == cnode1 && tnode1 == cnode2))
              {
                t[ctri].e_id[index1] = IEindex + nfedge;
                //printf("updated inner edge on Tri = %d\n", IEindex + nfedge);
              }
            }
          }

          for (kk = 0; kk < nIEDmc; kk++)
          {

            if(bFlag[kk] == 0)
            { // if current neigh edge is a new one...

              nnode1 = arrayIEnode[kk][0]; // get nodes...
              nnode2 = arrayIEnode[kk][1];

              if((cnode1 == nnode1 && cnode2 == nnode2) || (cnode2 == nnode1 && cnode1 == nnode2))
              {
                bFlag[kk] = -1; // if nodes are the same, burn it!
                nspin1Flag = 0; // update spins for current inner edge...
                nspin2Flag = 0;
                ntri = arrayTri[kk];
                nspin1 = t[ntri].nSpin[0];
                nspin2 = t[ntri].nSpin[1];
                // update triangle edge information; update only sides of triangles that are inner edges!
                for (jjj = 0; jjj < 3; jjj++)
                {
                  if(t[ntri].edgePlace[jjj] == 1)
                  { // only for inner edges...
                    index1 = jjj;
                    index2 = jjj + 1;
                    if(index2 == 3)
                    {
                      index2 = 0;
                    }
                    tnode1 = t[ntri].node_id[index1];
                    tnode2 = t[ntri].node_id[index2];
                    if((tnode1 == cnode1 && tnode2 == cnode2) || (tnode2 == cnode1 && tnode1 == cnode2))
                    {
                      t[ntri].e_id[index1] = IEindex + nfedge;
                      //printf("updated inner edge on Tri = %d\n", IEindex + nfedge);
                    }
                  }
                }
                // back to spin update...
                for (ii = 0; ii < 4; ii++)
                {
                  if(nspin1 == ie[IEindex].nSpin[ii])
                  {
                    nspin1Flag++;
                  }
                  if(nspin2 == ie[IEindex].nSpin[ii])
                  {
                    nspin2Flag++;
                  }
                }
                if((nspin1Flag * nspin2Flag) == 0)
                {
                  if(nspin1Flag == 0)
                  {
                    ie[IEindex].nSpin[tedgeKind] = nspin1;
                    tedgeKind++;
                  }
                  else if(nspin2Flag == 0)
                  {
                    ie[IEindex].nSpin[tedgeKind] = nspin2;
                    tedgeKind++;
                  }
                  else
                  {
                    ie[IEindex].nSpin[tedgeKind] = nspin1;
                    tedgeKind++;
                    ie[IEindex].nSpin[tedgeKind] = nspin2;
                    tedgeKind++;
                  }
                }
                else
                {
                  // do nothing...
                  //printf("nspinFlags = %d %d\n", nspin1Flag, nspin2Flag);
                }
              }

            }
          }

          ie[IEindex].edgeKind = tedgeKind;
          if(tedgeKind > 4)
          {
            printf("something's wrong in counting inner edge kind!!! %d\n", tedgeKind);
          }
          IEindex++;
        }
      }

      index = 0;
    }

    i++;

  }
  while (i < numT);

  printf("\ttotal number of unique inner edges updated = %d\n", IEindex);

}

void CMUSurfaceMeshingFilter::arrange_spins(int32_t* p, Patch *t, StructArray<Node>::Pointer vertices, int numT, int xDim, int nsp)
{

  int i, j, k;
  int cnode;
  int csite, kind;
  int tsite1, tsite2;
  int nspin1, nspin2;
  int tspin1, tspin2;
  double cx, cy, cz;
  double xSum, ySum, zSum;
  double xSum1, ySum1, zSum1;
  double xSum2, ySum2, zSum2;
  int nEnode;
  double ctr1[3];
  double ctr2[3];
  double nv[3];
  double tv1[3];
  double tv2[3];
  double vcoord[3][3];
  double u[3];
  double w[3];
  double a, b, c, length;
  double cs1, cs2;
  double length1, length2; // length of the vectors...
  double dotP1, dotP2;
  double theta1, theta2;
  double tn[3];

  StructArray<Node>& v = *vertices;

  for (i = 0; i < numT; i++)
  { // for each triangle...
    // get neighboring spins...
    nspin1 = t[i].nSpin[0];
    nspin2 = t[i].nSpin[1];
    // initialize sums...
    xSum = 0.0;
    ySum = 0.0;
    zSum = 0.0;
    xSum1 = 0.0;
    ySum1 = 0.0;
    zSum1 = 0.0;
    xSum2 = 0.0;
    ySum2 = 0.0;
    zSum2 = 0.0;
    // number of edge node...
    nEnode = 0;

    for (j = 0; j < 3; j++)
    { // for each node inside the triangle...

      cnode = t[i].node_id[j]; // current node
      csite = cnode / 7 + 1; // get original data site for this triangle...
      kind = cnode % 7;

      xSum = xSum + v[cnode].coord[0];
      ySum = ySum + v[cnode].coord[1];
      zSum = zSum + v[cnode].coord[2];

      vcoord[j][0] = v[cnode].coord[0];
      vcoord[j][1] = v[cnode].coord[1];
      vcoord[j][2] = v[cnode].coord[2];

      if(kind == 0)
      {
        nEnode++;
        tsite1 = csite;
        tsite2 = csite + 1;
        tspin1 = p[tsite1];
        tspin2 = p[tsite2];
      }
      else if(kind == 1)
      {
        nEnode++;
        tsite1 = csite;
        tsite2 = csite + xDim;
        tspin1 = p[tsite1];
        tspin2 = p[tsite2];
      }
      else if(kind == 2)
      {
        nEnode++;
        tsite1 = csite;
        tsite2 = csite + nsp;
        tspin1 = p[tsite1];
        tspin2 = p[tsite2];
      }
      else
      {
        tspin1 = -1;
        tspin2 = -1;
      }
      //printf("%3d %3d\t", tspin1, tspin2);
      if(tspin1 == nspin1)
      {
        xSum1 = xSum1 + m_VoxelCoords[tsite1*3+0];
        ySum1 = ySum1 + m_VoxelCoords[tsite1*3+1];
        zSum1 = zSum1 + m_VoxelCoords[tsite1*3+2];
        xSum2 = xSum2 + m_VoxelCoords[tsite2*3+0];
        ySum2 = ySum2 + m_VoxelCoords[tsite2*3+1];
        zSum2 = zSum2 + m_VoxelCoords[tsite2*3+2];
      }
      else if(tspin2 == nspin1)
      {
        xSum1 = xSum1 + m_VoxelCoords[tsite2*3+0];
        ySum1 = ySum1 + m_VoxelCoords[tsite2*3+1];
        zSum1 = zSum1 + m_VoxelCoords[tsite2*3+2];
        xSum2 = xSum2 + m_VoxelCoords[tsite1*3+0];
        ySum2 = ySum2 + m_VoxelCoords[tsite1*3+1];
        zSum2 = zSum2 + m_VoxelCoords[tsite1*3+2];
      }
      else
      {
        // do nothing...
      }
    }
    // Getting the vectors from center of triangle to each center of mass...
    cx = xSum / 3.0;
    cy = ySum / 3.0;
    cz = zSum / 3.0;

    ctr1[0] = xSum1 / (double)nEnode;
    ctr1[1] = ySum1 / (double)nEnode;
    ctr1[2] = zSum1 / (double)nEnode;
    ctr2[0] = xSum2 / (double)nEnode;
    ctr2[1] = ySum2 / (double)nEnode;
    ctr2[2] = zSum2 / (double)nEnode;

    tv1[0] = ctr1[0] - cx;
    tv1[1] = ctr1[1] - cy;
    tv1[2] = ctr1[2] - cz;
    tv2[0] = ctr2[0] - cx;
    tv2[1] = ctr2[1] - cy;
    tv2[2] = ctr2[2] - cz;

    length1 = sqrt(tv1[0] * tv1[0] + tv1[1] * tv1[1] + tv1[2] * tv1[2]);
    length2 = sqrt(tv2[0] * tv2[0] + tv2[1] * tv2[1] + tv2[2] * tv2[2]);
    // Getting normal vector of the triangle...(Right-hand Rule!!!)
    // Getting 2 edge vectors of triangle originating from vertex 0...
    u[0] = vcoord[1][0] - vcoord[0][0];
    u[1] = vcoord[1][1] - vcoord[0][1];
    u[2] = vcoord[1][2] - vcoord[0][2];
    w[0] = vcoord[2][0] - vcoord[0][0];
    w[1] = vcoord[2][1] - vcoord[0][1];
    w[2] = vcoord[2][2] - vcoord[0][2];
    // Cross product, UxW = aX + bY + cZ...
    // Note that UxW follows the same direction of triangle loop...
    a = u[1] * w[2] - u[2] * w[1];
    b = u[2] * w[0] - u[0] * w[2];
    c = u[0] * w[1] - u[1] * w[0];
    length = sqrt(a * a + b * b + c * c);
    tn[0] = a / length;
    tn[1] = b / length;
    tn[2] = c / length;

    for (k = 0; k < 3; k++)
    {
      if(fabs(tn[k]) < 0.0001)
      {
        tn[k] = 0.0;
      }
    }
    // update patch info...
    //t[i].normal[0] = tn[0];
    //t[i].normal[1] = tn[1];
    //t[i].normal[2] = tn[2];
    //t[i].area = 0.5*length;
    // normals to triangle...
    nv[0] = a;
    nv[1] = b;
    nv[2] = c;
    // Let's arrange the spin order...
    // Getting angles between vectors...
    dotP1 = tv1[0] * nv[0] + tv1[1] * nv[1] + tv1[2] * nv[2];
    dotP2 = tv2[0] * nv[0] + tv2[1] * nv[1] + tv2[2] * nv[2];
    cs1 = dotP1 / (length * length1);
    cs2 = dotP2 / (length * length2);

    if(cs1 > 1.0)
    {
      cs1 = 1.0;
    }
    else if(cs1 < -1.0)
    {
      cs1 = -1.0;
    }

    if(cs2 > 1.0)
    {
      cs2 = 1.0;
    }
    else if(cs2 < -1.0)
    {
      cs2 = -1.0;
    }

    theta1 = 180.0 / M_PI * acos(cs1);
    theta2 = 180.0 / M_PI * acos(cs2);
    // update neighboring spins...
    if(theta1 < theta2)
    {
      t[i].nSpin[0] = nspin1;
      t[i].nSpin[1] = nspin2;
    }
    else
    {
      t[i].nSpin[0] = nspin2;
      t[i].nSpin[1] = nspin1;
    }
    //printf("%10.5f %10.5f\n", theta1, theta2);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void CMUSurfaceMeshingFilter::update_node_edge_kind(StructArray<Node>::Pointer vertices, Segment *fe, isegment *ie, Patch *t, int nT, int nfedge)
{
  int i, j;
  int tn, te;
  int tnkind, tekind;
  int tspin1, tspin2;
  StructArray<Node>& v = *vertices;
  for (j = 0; j < nT; j++)
  {
    tspin1 = t[j].nSpin[0];
    tspin2 = t[j].nSpin[1];

    if(tspin1 * tspin2 < 0)
    { // if the triangle is the surface of whole microstructure...
      // increase edge and node kind by 10...
      for (i = 0; i < 3; i++)
      {
        // nodeKind...
        tn = t[j].node_id[i];
        tnkind = v[tn].nodeKind;
        if(tnkind < 10)
        {
          v[tn].nodeKind = tnkind + 10;
        }
        // edgeKind...
        te = t[j].e_id[i];
        if(te < nfedge)
        {
          tekind = fe[te].edgeKind;
          if(tekind < 10)
          {
            fe[te].edgeKind = tekind + 10;
          }
        }
        else
        {
          te = te - nfedge;
          tekind = ie[te].edgeKind;
          if(tekind < 10)
          {
            ie[te].edgeKind = tekind + 10;
          }
        }
      }
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int CMUSurfaceMeshingFilter::assign_new_nodeID(StructArray<Node>::Pointer vertices, int ns)
{
  int i;
  int numN;
  int newnid;
  int nkind;

  numN = 7 * ns;
  newnid = 0;
  StructArray<Node>& v = *vertices;

  for (i = 0; i < numN; i++)
  {
    nkind = v[i].nodeKind;
    if(nkind > 0)
    {
      v[i].newID = newnid;
      newnid++;
    }
  }
  return (newnid);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
#if 0
void CMUSurfaceMeshingFilter::get_output(StructArray<Node>::Pointer v, Segment *fe, isegment *ie, Patch *t, int ns, int nN, int nfe, int nie, int nT, MeshParameters* mp)
{

  FILE *f1, *f2, *f3;

  int i, j, k, kk;
  int numN;
  int kind;

  int tn1, tn2, tn3;
  int n1, n2, n3, newnid1, newnid2;
  int e1, e2, e3;

  numN = 7 * ns;

  // Open the streams for 3 output files...

  if((f1 = fopen(mp->nodes_file.c_str(), "w")) == NULL)
  {
    printf("\nCannot create the output nodes file! '%s'\n", mp->nodes_file.c_str());
    return;
  }

  if((f2 = fopen(mp->edges_file.c_str(), "w")) == NULL)
  {
    printf("\nCannot create the output edges file! '%s'\n", mp->edges_file.c_str());
    return;
  }

  if((f3 = fopen(mp->triangles_file.c_str(), "w")) == NULL)
  {
    printf("\nCannot create the output file! '%s'\n", mp->triangles_file.c_str());
    return;
  }

  // nodes_raw.txt...
  fprintf(f1, "%d\n", nN);

  for (i = 0; i < numN; i++)
  {

    kind = v[i].nodeKind;

    if(kind > 0)
    {

      fprintf(f1, "%10d    %3d    %8.4f %8.4f %8.4f\n", v[i].newID, kind, v[i].coord[0], v[i].coord[1], v[i].coord[2]);
    }
  }

  fclose(f1);

  // edges_raw.txt...
  fprintf(f2, "%d\n", nfe + nie);

  for (k = 0; k < nfe; k++)
  {

    kind = fe[k].edgeKind;
    tn1 = fe[k].node_id[0];
    tn2 = fe[k].node_id[1];
    newnid1 = v[tn1].newID;
    newnid2 = v[tn2].newID;

    fprintf(f2, "%10d    %8d %8d    %6d    %6d %6d %6d %6d\n", k, newnid1, newnid2, kind, fe[k].neigh_spin[0], fe[k].neigh_spin[1], 0, 0);
  }

  //fprintf(f2, "************";

  for (kk = 0; kk < nie; kk++)
  {

    kind = ie[kk].edgeKind;
    tn1 = ie[kk].node_id[0];
    tn2 = ie[kk].node_id[1];
    newnid1 = v[tn1].newID;
    newnid2 = v[tn2].newID;

    fprintf(f2, "%10d    %8d %8d    %6d    %6d %6d %6d %6d\n", kk + nfe, newnid1, newnid2, kind, ie[kk].nSpin[0], ie[kk].nSpin[1], ie[kk].nSpin[2], ie[kk].nSpin[3]);
  }

  fclose(f2);

  // triangles_raw.txt...
  fprintf(f3, "%d\n", nT);

  for (j = 0; j < nT; j++)
  {

    tn1 = t[j].node_id[0];
    tn2 = t[j].node_id[1];
    tn3 = t[j].node_id[2];

    n1 = v[tn1].newID;
    n2 = v[tn2].newID;
    n3 = v[tn3].newID;

    e1 = t[j].e_id[0];
    e2 = t[j].e_id[1];
    e3 = t[j].e_id[2];

    fprintf(f3, "%10d    %10d %10d %10d    %10d %10d %10d    %5d %5d\n", j, n1, n2, n3, e1, e2, e3, t[j].nSpin[0], t[j].nSpin[1]);
  }

  fclose(f3);

}
#endif



