project("Phi_CoreUnittestsTests" CXX)

file(GLOB TEST_HEADERS "include/ConstexprHelper.hpp" "include/StringHelper.hpp"
     "include/Unwrap.hpp")

file(
  GLOB
  TEST_SOURCES
  # Algorithm
  "src/Algorithm/StringLength.test.cpp"
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
  "src/Core/FlatPtr.test.cpp"
  "src/Core/FloatingPoint.test.cpp"
  "src/Core/Integer.test.cpp"
  "src/Core/Log.test.cpp"
  "src/Core/Monitor.test.cpp"
  "src/Core/NamedType.test.cpp"
  "src/Core/NonCopyable.test.cpp"
  "src/Core/NotNull.test.cpp"
  "src/Core/ObserverPtr.test.cpp"
  "src/Core/Optional.test.cpp"
  "src/Core/ScopedValueGuard.test.cpp"
  "src/Core/ScopeGuard.test.cpp"
  "src/Core/ScopePtr.test.cpp"
  "src/Core/StopWatch.test.cpp"
  "src/Core/Types.test.cpp"
  "src/Core/TypeTraits.test.cpp"
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

list(APPEND UnittestLibs ${UnittestName})

# Constexpr unittests
if(${PHI_ENABLE_CONSTEXPRTESTS})
  set(ConstexprTestName "Phi_ConstexprUnittests")

  list(APPEND UnittestLibs ${ConstexprTestName})
endif()

foreach(lib ${UnittestLibs})
  add_executable(${lib} "${TEST_HEADERS}" "${TEST_SOURCES}")

  target_link_libraries(${lib} PRIVATE Phi::InternalProjectOptions Phi::Core Catch2::Catch2WithMain)

  target_include_directories(${lib} PRIVATE "include")

  set_target_properties(${lib} PROPERTIES FOLDER "Tests/Unittest")

  phi_enable_static_analyzers(${lib})

  phi_add_test(TARGET ${lib})
endforeach()

# Runtime static require for Runtime tests
target_compile_definitions(${UnittestName} PRIVATE CATCH_CONFIG_RUNTIME_STATIC_REQUIRE)
