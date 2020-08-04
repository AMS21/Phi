project("PhiEngine_Tests" CXX)

file(GLOB TEST_HEADERS "include/StringHelper.hpp")

file(
  GLOB
  TEST_SOURCES
  # Main
  "src/main.cpp"
  # Selftest
  "src/Selftest/StringHelper.test.cpp"
  # Config
  "src/PhiConfig.test.cpp")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TEST_HEADERS} ${TEST_SOURCES})

# Dynamic unittests
set(UnittestName "PhiEngine_Unittests")

add_executable(${UnittestName} "${TEST_HEADERS}" "${TEST_SOURCES}")

target_link_libraries(${UnittestName} PRIVATE Phi::ProjectOptions Phi::Engine Catch2::Catch2)
target_compile_definitions(${UnittestName} PRIVATE CATCH_CONFIG_RUNTIME_STATIC_REQUIRE)
target_include_directories(${UnittestName} PRIVATE "include")

enable_static_analyzers(${UnittestName})

add_test(Unittest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${UnittestName})

# Constexpr unittests
set(ConstexprTestName "PhiEngine_ConstexprUnittests")

add_executable(${ConstexprTestName} "${TEST_HEADERS}" "${TEST_SOURCES}")

target_link_libraries(${ConstexprTestName} PRIVATE Phi::ProjectOptions Phi::Engine Catch2::Catch2)
target_include_directories(${ConstexprTestName} PRIVATE "include")

enable_static_analyzers(${ConstexprTestName})

add_test(ConstexprUnittest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ConstexprTestName})
