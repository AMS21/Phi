project("PhiEngine_Tests" CXX)

file(GLOB TEST_HEADERS "include/ConstexprHelper.hpp" "include/StringHelper.hpp" "include/Unwrap.hpp")

file(
  GLOB
  TEST_SOURCES
  # Main
  "src/main.cpp"
  # Math
  "src/Math/Constants.test.cpp"
  # Meta
  "src/Meta/AlwaysFalse.test.cpp"
  # Selftest
  "src/Selftest/ConstexprHelper.test.cpp"
  "src/Selftest/StringHelper.test.cpp"
  "src/Selftest/Unwrap.test.cpp"
  # Utility
  "src/Utility/Assert.test.cpp"
  "src/Utility/At.test.cpp"
  "src/Utility/Boolean.test.cpp"
  "src/Utility/Conversion.test.cpp"
  "src/Utility/FloatingPoint.test.cpp"
  "src/Utility/Integer.test.cpp"
  "src/Utility/Log.test.cpp"
  "src/Utility/Types.test.cpp"
  # Config
  "src/PhiConfig.test.cpp")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TEST_HEADERS} ${TEST_SOURCES})

# Dynamic unittests
set(UnittestName "PhiEngine_Unittests")

add_executable(${UnittestName} "${TEST_HEADERS}" "${TEST_SOURCES}")

target_link_libraries(${UnittestName} PRIVATE Phi::InternalProjectOptions Phi::Engine Catch2::Catch2)
target_compile_definitions(${UnittestName} PRIVATE CATCH_CONFIG_RUNTIME_STATIC_REQUIRE)
target_include_directories(${UnittestName} PRIVATE "include")

set_target_properties(${UnittestName} PROPERTIES FOLDER "Tests/Unittest")

enable_static_analyzers(${UnittestName})

add_test(Unittest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${UnittestName})

# Constexpr unittests
if(${PHI_ENABLE_CONSTEXPRTESTS})
  set(ConstexprTestName "PhiEngine_ConstexprUnittests")

  add_executable(${ConstexprTestName} "${TEST_HEADERS}" "${TEST_SOURCES}")

  target_link_libraries(${ConstexprTestName} PRIVATE Phi::InternalProjectOptions Phi::Engine Catch2::Catch2)
  target_include_directories(${ConstexprTestName} PRIVATE "include")

  set_target_properties(${ConstexprTestName} PROPERTIES FOLDER "Tests/Unittest")

  enable_static_analyzers(${ConstexprTestName})

  add_test(ConstexprUnittest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ConstexprTestName})
endif()
