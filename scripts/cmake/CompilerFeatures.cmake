phi_include_guard()

include(CheckCXXSourceCompiles)

# Set compile flags
set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${phi_latest_standard_flag}")

# Features
check_cxx_source_compiles("int main() { char8_t c; }" PHI_HAS_FEATURE_CHAR8_T)
check_cxx_source_compiles("inline int i; int main() {}" PHI_HAS_FEATURE_INLINE_VARIABLES)
check_cxx_source_compiles("int main() { using T = void() noexcept; }"
                          PHI_HAS_FEATURE_NOEXCEPT_FUNCTION_TYPE)
check_cxx_source_compiles("[[nodiscard]] int f() { return 3; } int main() {}"
                          PHI_HAS_FEATURE_NODISCARD)

# Lib
check_cxx_source_compiles("#include <string_view>
int main() {}" PHI_HAS_LIB_STRING_VIEW)

# Intrinsics
check_cxx_source_compiles("int main() { return __array_extent(int, 0); }"
                          PHI_HAS_INTRINSIC_ARRAY_EXTENT)
check_cxx_source_compiles("int main() { int i = 5; __builtin_addressof(i); }"
                          PHI_HAS_INTRINSIC_BUILTIN_ADDRESS_OF)
check_cxx_source_compiles("int main() { return __builtin_is_constant_evaluated(); }"
                          PHI_HAS_INTRINSIC_BUILTIN_IS_CONSTANT_EVALUATED)
check_cxx_source_compiles("int main() { return __has_unique_object_representations(int); }"
                          PHI_HAS_INTRINSIC_HAS_UNIQUE_OBJECT_REPRESENTATIONS)
check_cxx_source_compiles("int main() { return __builtin_fabsf(-1.0f) > 0; }"
                          PHI_HAS_INTRINSIC_BUILTIN_FABSF)
check_cxx_source_compiles("int main() { return __builtin_fabs(-1.0) > 0; }"
                          PHI_HAS_INTRINSIC_BUILTIN_FABS)
check_cxx_source_compiles("int main() { return __builtin_fabsl(-1.0) > 0; }"
                          PHI_HAS_INTRINSIC_BUILTIN_FABSL)
check_cxx_source_compiles(
  "class A { virtual ~A(); }; int main() { return __has_virtual_destructor(A); }"
  PHI_HAS_INTRINSIC_HAS_VIRTUAL_DESTRUCTOR)
check_cxx_source_compiles(
  "struct A {virtual void f() = 0;}; int main() { return __is_abstract(A); }"
  PHI_HAS_INTRINSIC_IS_ABSTRACT)
check_cxx_source_compiles("struct A {}; int main() { return __is_aggregate(A); }"
                          PHI_HAS_INTRINSIC_IS_AGGREGATE)
check_cxx_source_compiles("int main() { return __is_assignable(int, int); }"
                          PHI_HAS_INTRINSIC_IS_ASSIGNABLE)
check_cxx_source_compiles("struct A {}; struct B : A {}; int main() { return __is_base_of(A, B); }"
                          PHI_HAS_INTRINSIC_IS_BASE_OF)
check_cxx_source_compiles("class A {}; int main() { return __is_class(A); }"
                          PHI_HAS_INTRINSIC_IS_CLASS)
check_cxx_source_compiles("int main() { return __is_constructible(int, int); }"
                          PHI_HAS_INTRINSIC_IS_CONSTRUCTIBLE)
check_cxx_source_compiles("int main() { return __is_const(const int); }" PHI_HAS_INTRINSIC_IS_CONST)
check_cxx_source_compiles("int main() { return __is_convertible_to(int, int); }"
                          PHI_HAS_INTRINSIC_IS_CONVERTIBLE_TO)
check_cxx_source_compiles("int main() { return __is_destructible(int); }"
                          PHI_HAS_INTRINSIC_IS_DESTRUCTIBLE)
check_cxx_source_compiles("struct A {}; int main() { return __is_empty(A); }"
                          PHI_HAS_INTRINSIC_IS_EMPTY)
check_cxx_source_compiles("enum E{}; int main() { return __is_enum(E); }" PHI_HAS_INTRINSIC_IS_ENUM)
check_cxx_source_compiles("class A final {}; int main() { return __is_final(A); }"
                          PHI_HAS_INTRINSIC_IS_FINAL)
check_cxx_source_compiles("int main() { return __is_integral(int); }" PHI_HAS_INTRINSIC_IS_INTEGRAL)
check_cxx_source_compiles("int main() { return __is_scalar(int); }" PHI_HAS_INTRINSIC_IS_SCALAR)
check_cxx_source_compiles("int main() { return __is_standard_layout(int); }"
                          PHI_HAS_INTRINSIC_IS_STANDARD_LAYOUT)
check_cxx_source_compiles("int main() { return __is_member_pointer(void*); }"
                          PHI_HAS_INTRINSIC_IS_MEMBER_POINTER)
check_cxx_source_compiles("int main() { return __is_member_function_pointer(void*); }"
                          PHI_HAS_INTRINSIC_IS_MEMBER_FUNCTION_POINTER)
check_cxx_source_compiles("int main() { return __is_member_object_pointer(void*); }"
                          PHI_HAS_INTRINSIC_IS_MEMBER_OBJECT_POINTER)
check_cxx_source_compiles("int main() { return __is_nothrow_assignable(int, int); }"
                          PHI_HAS_INTRINSIC_IS_NOTHROW_ASSIGNABLE)
check_cxx_source_compiles("int main() { return __is_nothrow_constructible(int, int); }"
                          PHI_HAS_INTRINSIC_IS_NOTHROW_CONSTRUCTIBLE)
check_cxx_source_compiles("int main() { return __is_object(int); }" PHI_HAS_INTRINSIC_IS_OBJECT)
check_cxx_source_compiles(
  "struct A {virtual void f(); }; int main() { return __is_polymorphic(A); }"
  PHI_HAS_INTRINSIC_IS_POLYMORPHIC)
check_cxx_source_compiles("enum E {}; int main() { using T = __underlying_type(E); }"
                          PHI_HAS_INTRINSIC_UNDERLYING_TYPE)
check_cxx_source_compiles("union A {int a; float b;}; int main() { return __is_union(A); }"
                          PHI_HAS_INTRINSIC_IS_UNION)
check_cxx_source_compiles("int main() { return __is_trivial(int); }" PHI_HAS_INTRINSIC_IS_TRIVIAL)
check_cxx_source_compiles("int main() { return __is_trivially_assignable(int, int); }"
                          PHI_HAS_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE)
check_cxx_source_compiles("int main() { return __is_trivially_copyable(int); }"
                          PHI_HAS_INTRINSIC_IS_TRIVIALLY_COPYABLE)
check_cxx_source_compiles("int main() { return __is_trivially_constructible(int, int); }"
                          PHI_HAS_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE)
check_cxx_source_compiles("int main() { return __is_trivially_destructible(int); }"
                          PHI_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE)
check_cxx_source_compiles("int main() { return __is_volatile(volatile int); }"
                          PHI_HAS_INTRINSIC_IS_VOLATILE)
check_cxx_source_compiles("int main() { using t = __remove_const(const int); }"
                          PHI_HAS_INTRINSIC_REMOVE_CONST)
check_cxx_source_compiles("int main() { using t = __remove_volatile(volatile int); }"
                          PHI_HAS_INTRINSIC_REMOVE_VOLATILE)
check_cxx_source_compiles("int main() { using t = __remove_cv(const volatile int); }"
                          PHI_HAS_INTRINSIC_REMOVE_CV)
check_cxx_source_compiles("int main() { return __is_void(void); }" PHI_HAS_INTRINSIC_IS_VOID)
check_cxx_source_compiles("int main() { return __is_array(int[]); }" PHI_HAS_INTRINSIC_IS_ARRAY)
check_cxx_source_compiles("int main() { return __is_pointer(int*); }" PHI_HAS_INTRINSIC_IS_POINTER)
check_cxx_source_compiles("int main() { return __is_reference(int&); }"
                          PHI_HAS_INTRINSIC_IS_REFERENCE)
check_cxx_source_compiles("int main() { return __is_lvalue_reference(int&); }"
                          PHI_HAS_INTRINSIC_IS_LVALUE_REFERENCE)
check_cxx_source_compiles("int main() { return __is_rvalue_reference(int&&); }"
                          PHI_HAS_INTRINSIC_IS_RVALUE_REFERENCE)
check_cxx_source_compiles("int main() { return __is_compound(int); }" PHI_HAS_INTRINSIC_IS_COMPOUND)
check_cxx_source_compiles("int main() { return __is_same(int, int); }" PHI_HAS_INTRINSIC_IS_SAME)
check_cxx_source_compiles("int main() { return __has_trivial_destructor(int); }"
                          PHI_HAS_INTRINSIC_HAS_TRIVIAL_DESTRUCTOR)

# Extensions
check_cxx_source_compiles("#define M(...) 1
int main() { return M(); }" PHI_HAS_EXTENSION_VARIADIC_MACRO_ZERO_ARGS)
check_cxx_source_compiles("int main() { __assume(true); }" PHI_HAS_EXTENSION_ASSUME)
check_cxx_source_compiles("int main() { __builtin_assume(true); }" PHI_HAS_EXTENSION_BUILTIN_ASSUME)
check_cxx_source_compiles("int main() { __builtin_unreachable(); }"
                          PHI_HAS_EXTENSION_BUILTIN_UNREACHABLE)
check_cxx_source_compiles("__attribute__((flatten)) int main() {}"
                          PHI_HAS_EXTENSION_ATTRIBUTE_FLATTEN)
check_cxx_source_compiles("__attribute__((always_inline)) inline void f(){} int main() {}"
                          PHI_HAS_EXTENSION_ATTRIBUTE_ALWAYS_INLINE)
check_cxx_source_compiles("__attribute__((noinline)) void f(){} int main() {}"
                          PHI_HAS_EXTENSION_ATTRIBUTE_NOINLINE)
check_cxx_source_compiles("__attribute__((warn_unused_result)) int f() { return 3; } int main() {}"
                          PHI_HAS_EXTENSION_ATTRIBUTE_WARN_UNUSED_RESULT)
check_cxx_source_compiles("__forceinline void f(){} int main() {}" PHI_HAS_EXTENSION_FORCEINLINE)
check_cxx_source_compiles("__declspec(noinline) void f(){} int main() {}"
                          PHI_HAS_EXTENSION_DECLSPEC_NOINLINE)
check_cxx_source_compiles("int main() { __builtin_expect(true, 1); }"
                          PHI_HAS_EXTENSION_BUILTIN_EXPECT)
check_cxx_source_compiles("#pragma once
int main() {}" PHI_HAS_EXTENSION_PRAGMA_ONCE)
check_cxx_source_compiles("_Check_return_ int f() { return 3; } int main() {}"
                          PHI_HAS_EXTENSION_CHECK_RETURN)

# configure file
configure_file("scripts/cmake/Features.hpp.in"
               "generated_files/include/Phi/CompilerSupport/Features.hpp")
include_directories(${CMAKE_CURRENT_BINARY_DIR}/generated_files/include)
