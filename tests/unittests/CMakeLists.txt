project("Phi_Tests" CXX)

file(GLOB TEST_HEADERS "include/ConstexprHelper.hpp" "include/StringHelper.hpp"
     "include/Unwrap.hpp")

file(
  GLOB
  TEST_SOURCES
  # Config
  "src/Config/Assume.test.cpp"
  "src/Config/Compiler.test.cpp"
  "src/Config/CurrentFunction.test.cpp"
  "src/Config/FunctionLikemacro.test.cpp"
  "src/Config/Glue.test.cpp"
  "src/Config/Inline.test.cpp"
  "src/Config/Likely.test.cpp"
  "src/Config/Platform.test.cpp"
  "src/Config/SourceLine.test.cpp"
  "src/Config/Stringify.test.cpp"
  "src/Config/Unreachable.test.cpp"
  "src/Config/Versioning.test.cpp"
  "src/Config/Warnings.test.cpp"
  # Core
  "src/Core/Assert.test.cpp"
  "src/Core/At.test.cpp"
  "src/Core/Boolean.test.cpp"
  "src/Core/Conversion.test.cpp"
  "src/Core/FloatingPoint.test.cpp"
  "src/Core/Integer.test.cpp"
  "src/Core/Log.test.cpp"
  "src/Core/NotNull.test.cpp"
  "src/Core/ScopeGuard.test.cpp"
  "src/Core/Types.test.cpp"
  # Math
  "src/Math/Constants.test.cpp"
  "src/Math/Vector2.test.cpp"
  # Meta
  "src/Meta/AlwaysFalse.test.cpp"
  # Selftest
  "src/Selftest/ConstexprHelper.test.cpp"
  "src/Selftest/StringHelper.test.cpp"
  "src/Selftest/Unwrap.test.cpp"
  # Base
  "src/PhiConfig.test.cpp")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TEST_HEADERS} ${TEST_SOURCES})

set(UnittestLibs)

# Runtime unittests
set(UnittestName "Phi_Unittests")
set(UnittestDynName "${UnittestName}Dynamic")

list(APPEND UnittestLibs ${UnittestName} ${UnittestDynName})

# Constexpr unittests
if(${PHI_ENABLE_CONSTEXPRTESTS})
  set(ConstexprTestName "Phi_ConstexprUnittests")
  set(ConstexprDynTestName "${ConstexprTestName}Dynamic")

  list(APPEND UnittestLibs ${ConstexprTestName} ${ConstexprDynTestName})
endif()

foreach(lib ${UnittestLibs})
  add_executable(${lib} "${TEST_HEADERS}" "${TEST_SOURCES}")

  target_link_libraries(${lib} PRIVATE Phi::InternalProjectOptions Catch2::Catch2WithMain)

  target_include_directories(${lib} PRIVATE "include")

  set_target_properties(${lib} PROPERTIES FOLDER "Tests/Unittest")

  enable_static_analyzers(${lib})

  add_test(${lib} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${lib})
endforeach()

# Runtime static require for Runtime tests
target_compile_definitions(${UnittestName} PRIVATE CATCH_CONFIG_RUNTIME_STATIC_REQUIRE)
target_compile_definitions(${UnittestDynName} PRIVATE CATCH_CONFIG_RUNTIME_STATIC_REQUIRE)

# Link to correct Phi::Core library
target_link_libraries(${UnittestName} PRIVATE Phi::Core)
target_link_libraries(${UnittestDynName} PRIVATE Phi::CoreDynamic)

if(${PHI_ENABLE_CONSTEXPRTESTS})
  target_link_libraries(${ConstexprTestName} PRIVATE Phi::Core)
  target_link_libraries(${ConstexprDynTestName} PRIVATE Phi::CoreDynamic)
endif()
