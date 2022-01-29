project("PhiTestUnittests" CXX)

file(
  GLOB
  TEST_SOURCES
  "src/Check.test.cpp"
  "src/CheckFalse.test.cpp"
  "src/CheckNoexcept.test.cpp"
  "src/CheckNotNoexcept.test.cpp"
  "src/CheckNotSameType.test.cpp"
  "src/CheckSameType.test.cpp"
  "src/MultipleTestCasesWithSameName.test.cpp"
  "src/Require.test.cpp"
  "src/RequireFalse.test.cpp"
  "src/Section.test.cpp")

file(GLOB TEST_HEADERS)

if(${CMAKE_VERSION} VERSION_GREATER "3.7")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TEST_HEADERS} ${TEST_SOURCES})
endif()

phi_add_executable(
  NAME
  ${PROJECT_NAME}
  SOURCES
  ${TEST_SOURCES}
  FOLDER
  "Tests/PhiTest/Unittests"
  PRIVATE_LINK_LIBRARIES
  Phi::InternalProjectOptions
  Phi::Test)
phi_enable_static_analyzers(${PROJECT_NAME})
phi_add_test(TARGET ${PROJECT_NAME})
