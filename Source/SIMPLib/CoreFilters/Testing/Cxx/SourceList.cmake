
set(TEST_TESTFILES_DIR ${SIMPLib_SOURCE_DIR}/${SUBDIR_NAME}/Testing/Cxx/TestFiles)

set(TEST_${SUBDIR_NAME}_NAMES
  ArrayCalculatorTest
  # CombineAttributeArraysTest
  # CombineAttributeMatricesTest
  # ConditionalSetValueTest
  # ConvertDataTest
  # CreateAttributeMatrixTest
  # CreateDataArrayTest
  # CreateDataContainerTest
  # CreateFeatureArrayFromElementArrayTest
  # CreateImageGeometryTest
  # DataContainerTest
  # ErrorMessageTest
  # ExecuteProcessTest
  # ExtractComponentAsArrayTest
  # FindDerivativesFilterTest
  # GenerateColorTableTest
  # ImportAsciDataArrayTest
  # ImportHDF5DatasetTest
  # MultiThresholdObjectsTest
  # MultiThresholdObjects2Test
  # RawBinaryReaderTest
  # ReadASCIIDataTest
  # RecursivePipelineTest
  # RemoveArraysTest
  # RemoveComponentFromArrayTest
  # RenameAttributeArrayTest
  # RenameAttributeMatrixTest
  # RenameDataContainerTest
  # ReplaceValueTest
  # RequiredZThicknessTest
  # ScaleVolumeTest
  # SetOriginResolutionImageGeomTest
  # WriteASCIIDataTest
)

SIMPL_ADD_UNIT_TEST("${TEST_${SUBDIR_NAME}_NAMES}" "${SIMPLib_SOURCE_DIR}/${SUBDIR_NAME}/Testing/Cxx")
SIMPL_ADD_UNIT_TEST_MOC_FILE(ExecuteProcessTest "${SIMPLib_SOURCE_DIR}/${SUBDIR_NAME}/Testing/Cxx")

set(SIMPLTest_SOURCE_DIR ${SIMPLib_SOURCE_DIR}/Testing)
set(SIMPLTest_BINARY_DIR ${SIMPLib_BINARY_DIR}/Testing)

# # QT5_WRAP_CPP( execute_process_moc  ${SIMPLTest_SOURCE_DIR}/ExecuteProcessTest.cpp)
# set_source_files_properties( ${execute_process_moc} PROPERTIES GENERATED TRUE)
# set_source_files_properties( ${execute_process_moc} PROPERTIES HEADER_FILE_ONLY TRUE)
