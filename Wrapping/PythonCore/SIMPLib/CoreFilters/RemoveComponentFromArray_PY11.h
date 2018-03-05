#pragma once

/**
* @brief This header file is genererate from a program. Make changes with caution.
* 
* This header file wraps the SIMPL class RemoveComponentFromArray located at
* SIMPLib/CoreFilters/RemoveComponentFromArray.h. 
* The Python bindings are created using Pybind11.
*/

#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "SIMPLib/CoreFilters/RemoveComponentFromArray.h"

/**
* @brief This defines a C++11 alias so loading the file by itself into an IDE
* will allow the proper code completion for a wrapped std::shared_ptr<> class.
*/
#ifndef PySharedPtrClass_TEMPLATE
#define PySharedPtrClass_TEMPLATE
template <typename T>
using PySharedPtrClass = py::class_<T, std::shared_ptr<T> >;
#endif

/**
* @brief
* @param m The Python module
* @param parent The parent class of the wrapped class
* @return A std::shared_ptr<T> wrapped instance of the wrapped class properly 
* initialized.
*/
PySharedPtrClass<RemoveComponentFromArray> pybind11_init_SIMPLib_RemoveComponentFromArray(py::module &m, PySharedPtrClass<AbstractFilter>& parent)
{
  PySharedPtrClass<RemoveComponentFromArray> instance(m, "RemoveComponentFromArray", parent);
  instance
  .def(py::init([]()
    { 
      return RemoveComponentFromArray::New();
    }
))
  .def_static("New", &RemoveComponentFromArray::New)
  /* Property accessors for SelectedArrayPath */
  .def_property("SelectedArrayPath", &RemoveComponentFromArray::getSelectedArrayPath, &RemoveComponentFromArray::setSelectedArrayPath)
  /* Property accessors for CompNumber */
  .def_property("CompNumber", &RemoveComponentFromArray::getCompNumber, &RemoveComponentFromArray::setCompNumber)
  /* Property accessors for SaveRemovedComponent */
  .def_property("SaveRemovedComponent", &RemoveComponentFromArray::getSaveRemovedComponent, &RemoveComponentFromArray::setSaveRemovedComponent)
  /* Property accessors for NewArrayArrayName */
  .def_property("NewArrayArrayName", &RemoveComponentFromArray::getNewArrayArrayName, &RemoveComponentFromArray::setNewArrayArrayName)
  /* Property accessors for ReducedArrayArrayName */
  .def_property("ReducedArrayArrayName", &RemoveComponentFromArray::getReducedArrayArrayName, &RemoveComponentFromArray::setReducedArrayArrayName)
  ;
  return instance;
}

