# PhiCore
project(PhiCore LANGUAGES CXX)

file(
  GLOB
  PHI_CORE_HEADERS
  # Algorithm
  "include/Phi/Algorithm/StringCompare.hpp"
  "include/Phi/Algorithm/StringEquals.hpp"
  "include/Phi/Algorithm/StringLength.hpp"
  # CompilerSupport
  "include/Phi/CompilerSupport/Char8_t.hpp"
  "include/Phi/CompilerSupport/Constexpr.hpp"
  "include/Phi/CompilerSupport/InlineVariables.hpp"
  "include/Phi/CompilerSupport/Nodiscard.hpp"
  # Config
  "include/Phi/Config/Assume.hpp"
  "include/Phi/Config/Compiler.hpp"
  "include/Phi/Config/CPlusPlus.hpp"
  "include/Phi/Config/CurrentFunction.hpp"
  "include/Phi/Config/Flatten.hpp"
  "include/Phi/Config/FunctionLikeMacro.hpp"
  "include/Phi/Config/Glue.hpp"
  "include/Phi/Config/Inline.hpp"
  "include/Phi/Config/Likely.hpp"
  "include/Phi/Config/Platform.hpp"
  "include/Phi/Config/SourceLine.hpp"
  "include/Phi/Config/Stringify.hpp"
  "include/Phi/Config/Unreachable.hpp"
  "include/Phi/Config/Versioning.hpp"
  "include/Phi/Config/Warning.hpp"
  # Container
  "include/Phi/Container/StringView.hpp"
  # Core
  "include/Phi/Core/AddressOf.hpp"
  "include/Phi/Core/Assert.hpp"
  "include/Phi/Core/At.hpp"
  "include/Phi/Core/Boolean.hpp"
  "include/Phi/Core/Conversion.hpp"
  "include/Phi/Core/CRTP.hpp"
  "include/Phi/Core/FlatPtr.hpp"
  "include/Phi/Core/FloatingPoint.hpp"
  "include/Phi/Core/Integer.hpp"
  "include/Phi/Core/Invoke.hpp"
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
  # Math
  "include/Phi/Math/Abs.hpp"
  "include/Phi/Math/Common.hpp"
  "include/Phi/Math/Constants.hpp"
  "include/Phi/Math/Signum.hpp"
  "include/Phi/Math/Vector2.hpp"
  "include/Phi/Math/Vector3.hpp"
  # TypeTraits
  "include/Phi/TypeTraits/add_const.hpp"
  "include/Phi/TypeTraits/add_cv.hpp"
  "include/Phi/TypeTraits/add_lvalue_reference.hpp"
  "include/Phi/TypeTraits/add_reference.hpp"
  "include/Phi/TypeTraits/add_rvalue_reference.hpp"
  "include/Phi/TypeTraits/add_volatile.hpp"
  "include/Phi/TypeTraits/always_false.hpp"
  "include/Phi/TypeTraits/bool_pack.hpp"
  "include/Phi/TypeTraits/conditional.hpp"
  "include/Phi/TypeTraits/conjunction.hpp"
  "include/Phi/TypeTraits/copy_const.hpp"
  "include/Phi/TypeTraits/copy_cv.hpp"
  "include/Phi/TypeTraits/copy_volatile.hpp"
  "include/Phi/TypeTraits/disable_if.hpp"
  "include/Phi/TypeTraits/disjunction.hpp"
  "include/Phi/TypeTraits/enable_if.hpp"
  "include/Phi/TypeTraits/integral_constant.hpp"
  "include/Phi/TypeTraits/invoke_result.hpp"
  "include/Phi/TypeTraits/is_array.hpp"
  "include/Phi/TypeTraits/is_bounded_array.hpp"
  "include/Phi/TypeTraits/is_const.hpp"
  "include/Phi/TypeTraits/is_lvalue_reference.hpp"
  "include/Phi/TypeTraits/is_not_same.hpp"
  "include/Phi/TypeTraits/is_nothrow_swappable_with.hpp"
  "include/Phi/TypeTraits/is_nothrow_swappable.hpp"
  "include/Phi/TypeTraits/is_null_pointer.hpp"
  "include/Phi/TypeTraits/is_pointer.hpp"
  "include/Phi/TypeTraits/is_reference_wrapper.hpp"
  "include/Phi/TypeTraits/is_reference.hpp"
  "include/Phi/TypeTraits/is_referenceable.hpp"
  "include/Phi/TypeTraits/is_rvalue_reference.hpp"
  "include/Phi/TypeTraits/is_same.hpp"
  "include/Phi/TypeTraits/is_scoped_enum.hpp"
  "include/Phi/TypeTraits/is_swappable_with.hpp"
  "include/Phi/TypeTraits/is_swappable.hpp"
  "include/Phi/TypeTraits/is_unbounded_array.hpp"
  "include/Phi/TypeTraits/is_void.hpp"
  "include/Phi/TypeTraits/is_volatile.hpp"
  "include/Phi/TypeTraits/nat.hpp"
  "include/Phi/TypeTraits/remove_const.hpp"
  "include/Phi/TypeTraits/remove_cv.hpp"
  "include/Phi/TypeTraits/remove_cvref.hpp"
  "include/Phi/TypeTraits/remove_reference.hpp"
  "include/Phi/TypeTraits/remove_volatile.hpp"
  "include/Phi/TypeTraits/void_t.hpp")

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
