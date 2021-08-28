# PhiCore
project(PhiCore LANGUAGES CXX)

file(
  GLOB
  PHI_CORE_HEADERS
  # Algorithm
  "include/Phi/Algorithm/StringLength.hpp"
  # CompilerSupport
  "include/Phi/CompilerSupport/Char8_t.hpp"
  "include/Phi/CompilerSupport/Constexpr.hpp"
  # Config
  "include/Phi/Config/Assume.hpp"
  "include/Phi/Config/Compiler.hpp"
  "include/Phi/Config/CurrentFunction.hpp"
  "include/Phi/Config/FunctionLikeMacro.hpp"
  "include/Phi/Config/Glue.hpp"
  "include/Phi/Config/Inline.hpp"
  "include/Phi/Config/Likely.hpp"
  "include/Phi/Config/Platform.hpp"
  "include/Phi/Config/Stringify.hpp"
  "include/Phi/Config/Unreachable.hpp"
  "include/Phi/Config/Versioning.hpp"
  "include/Phi/Config/Warning.hpp"
  # Container
  "include/Phi/Container/StringView.hpp"
  # Core
  "include/Phi/Core/Assert.hpp"
  "include/Phi/Core/At.hpp"
  "include/Phi/Core/Boolean.hpp"
  "include/Phi/Core/Conversion.hpp"
  "include/Phi/Core/CRTP.hpp"
  "include/Phi/Core/FlatPtr.hpp"
  "include/Phi/Core/FloatingPoint.hpp"
  "include/Phi/Core/Integer.hpp"
  "include/Phi/Core/Log.hpp"
  "include/Phi/Core/Monitor.hpp"
  "include/Phi/Core/NamedType.hpp"
  "include/Phi/Core/NonCopyable.hpp"
  "include/Phi/Core/NotNull.hpp"
  "include/Phi/Core/ObserverPtr.hpp"
  "include/Phi/Core/Optional.hpp"
  "include/Phi/Core/ScopedValueGuard.hpp"
  "include/Phi/Core/ScopeGuard.hpp"
  "include/Phi/Core/ScopePtr.hpp"
  "include/Phi/Core/StopWatch.hpp"
  "include/Phi/Core/Types.hpp"
  "include/Phi/Core/TypeTraits.hpp"
  # Math
  "include/Phi/Math/Abs.hpp"
  "include/Phi/Math/Common.hpp"
  "include/Phi/Math/Constants.hpp"
  "include/Phi/Math/Signum.hpp"
  "include/Phi/Math/Vector2.hpp"
  "include/Phi/Math/Vector3.hpp"
  # Meta
  "include/Phi/Meta/AlwaysFalse.hpp")

file(GLOB PHI_CORE_SOURCES "src/Core/Log.cpp")

phi_add_library(
  NAME
  ${PROJECT_NAME}
  STATIC
  SOURCES
  ${PHI_CORE_SOURCES}
  HEADERS
  ${PHI_CORE_HEADERS}
  ALIAS_TARGET
  Phi::Core
  PUBLIC_LINK_LIBRARIES
  spdlog::spdlog
  Threads::Threads
  PRIVATE_LINK_LIBRARIES
  Phi::InternalProjectOptions
  PUBLIC_INCLUDE_DIRS
  "include"
  PRIVATE_INCLUDE_DIRS
  "src")

phi_enable_static_analyzers(${PROJECT_NAME})
