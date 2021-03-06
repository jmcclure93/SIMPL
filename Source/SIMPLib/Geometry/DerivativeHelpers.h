/* ============================================================================
* Copyright (c) 2009-2016 BlueQuartz Software, LLC
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
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
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
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef _derivativehelpers_h_
#define _derivativehelpers_h_

#include <math.h>

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/DataArrays/DataArray.hpp"

#include "Eigen/LU"
#include "Eigen/Eigenvalues"

class EdgeGeom;
class TriangleGeom;
class QuadGeom;
class TetrahedralGeom;
class HexahedralGeom;

/**
* @brief This file contains a namespace with classes for computing derivatives on IGeometry objects
*/
namespace DerivativeHelpers
{

  /**
   * @brief TriJacobian
   */
  typedef Eigen::Matrix<double, 2, 2, Eigen::RowMajor> TriangleJacobian;

  /**
   * @brief QuadJacobian
   */
  typedef Eigen::Matrix<double, 2, 2, Eigen::RowMajor> QuadJacobian;

  /**
   * @brief TetJacobian
   */
  typedef Eigen::Matrix<double, 3, 3, Eigen::RowMajor> TetJacobian;

  /**
  * @brief HexJacobian
  */
  typedef Eigen::Matrix<double, 3, 3, Eigen::RowMajor> HexJacobian;

  class EdgeDeriv
  {
    public:
      EdgeDeriv() {}
      virtual ~EdgeDeriv() {}

      void operator()(EdgeGeom* edges, int64_t edgeId, double values[2], double derivs[3]);
  };

  /**
   * @brief The TriangleDeriv class
   */
  class TriangleDeriv
  {
    public:
      TriangleDeriv() {}
      virtual ~TriangleDeriv() {}

      void operator()(TriangleGeom* triangles, int64_t triId, double values[3], double derivs[3]);
  };

  /**
   * @brief The QuadDeriv class
   */
  class QuadDeriv
  {
    public:
      QuadDeriv() {}
      virtual ~QuadDeriv() {}

      void operator()(QuadGeom* quads, int64_t quadId, double values[4], double derivs[3]);
  };

  /**
   * @brief The TetDeriv class
   */
  class TetDeriv
  {
    public:
      TetDeriv() {}
      virtual ~TetDeriv() {}

      void operator()(TetrahedralGeom* tets, int64_t tetId, double values[4], double derivs[3]);
  };

  /**
  * @brief The HexDeriv class
  */
  class HexDeriv
  {
    public:
    HexDeriv() {}
    virtual ~HexDeriv() {}

    void operator()(HexahedralGeom* hexas, int64_t hexId, double values[8], double derivs[3]);
  };

}

#endif /* _DerivativeHelpers_H_ */
