phi_include_guard()

include(CheckCXXSourceCompiles)
include(CheckTypeSize)

# Set compile flags
set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${phi_latest_standard_flag}")

function(phi_check_cxx_source_compiles source var)
  check_cxx_source_compiles("${source}" ${var})

  if(NOT ${var})
    phi_set_cache_value(NAME ${var} VALUE "0")
  endif()
endfunction()

# Features

# C++-11 Features
phi_check_cxx_source_compiles("int main() { constexpr int i = 3; return i; }"
                              PHI_HAS_FEATURE_CONSTEXPR)

# C++-14 Features
phi_check_cxx_source_compiles("int main() { int i = 0b1; }" PHI_HAS_FEATURE_BINARY_LITERALS)
phi_check_cxx_source_compiles("int main() { int i = 1; decltype(auto) c1 = i; }"
                              PHI_HAS_FEATURE_DECLTYPE_AUTO)
phi_check_cxx_source_compiles("template <typename T> T i = T(3); int main() { return i<int>; }"
                              PHI_HAS_FEATURE_VARIABLE_TEMPLATE)
phi_check_cxx_source_compiles("[[deprecated]] void f() {} int main() { f(); }"
                              PHI_HAS_FEATURE_ATTRIBUTE_DEPRECATED)
phi_check_cxx_source_compiles(
  "constexpr int foo(bool boolean) { int i = 5; while (i) { --i; } if (boolean) { return 5; } else { return 0; } }
int main() { return foo(false); }"
  PHI_HAS_FEATURE_EXTENDED_CONSTEXPR)

# C++-17 Features
phi_check_cxx_source_compiles(
  "auto f = [](int a, int b) constexpr { return a + b; }; int main() { return f(3, -3); }"
  PHI_HAS_FEATURE_CONSTEXPR_LAMBDA)
phi_check_cxx_source_compiles("inline int i; int main() {}" PHI_HAS_FEATURE_INLINE_VARIABLES)
phi_check_cxx_source_compiles(
  "template<typename T> struct Thingy { T t; };
Thingy(int) -> Thingy<double>;
int main() { Thingy thing{12}; }" PHI_HAS_FEATURE_DEDUCTION_GUIDES)
phi_check_cxx_source_compiles(
  "template<typename> struct A  {};
template<class Ret, class... Args>
struct A<Ret(Args...) noexcept> {};
int main() {}"
  PHI_HAS_FEATURE_NOEXCEPT_FUNCTION_TYPE)
phi_check_cxx_source_compiles("[[nodiscard]] int f() { return 3; } int main() {}"
                              PHI_HAS_FEATURE_NODISCARD)
phi_check_cxx_source_compiles("void f([[maybe_unused]] int a) {} int main() {}"
                              PHI_HAS_FEATURE_MAYBE_UNUSED)

# C++-20 Features
phi_check_cxx_source_compiles("int main() { char8_t c; }" PHI_HAS_FEATURE_CHAR8_T)
phi_check_cxx_source_compiles("struct A{ constexpr ~A() {} }; int main() { A a; }"
                              PHI_HAS_FEATURE_CONSTEXPR_DESTRUCTOR)
phi_check_cxx_source_compiles(
  "struct A{ constexpr virtual void f() {}; }; int main() { A a; a.f(); }"
  PHI_HAS_FEATURE_CONSTEXPR_VIRTUAL)
phi_check_cxx_source_compiles("int main() { if ( 1 == 1) [[likely]] {} return 0; }"
                              PHI_HAS_FEATURE_LIKELY)

# Lib
phi_check_cxx_source_compiles("#include <string_view>
int main() {}" PHI_HAS_LIB_STRING_VIEW)

# Intrinsics
phi_check_cxx_source_compiles("int main() { return __array_extent(int, 0); }"
                              PHI_HAS_INTRINSIC_ARRAY_EXTENT)
phi_check_cxx_source_compiles("int main() { int i = 5; __builtin_addressof(i); }"
                              PHI_HAS_INTRINSIC_BUILTIN_ADDRESS_OF)
phi_check_cxx_source_compiles("int main() { return __builtin_is_constant_evaluated(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_IS_CONSTANT_EVALUATED)
phi_check_cxx_source_compiles("int main() { return __has_unique_object_representations(int); }"
                              PHI_HAS_INTRINSIC_HAS_UNIQUE_OBJECT_REPRESENTATIONS)
phi_check_cxx_source_compiles("int main() { return __builtin_fabsf(-1.0f) > 0; }"
                              PHI_HAS_INTRINSIC_BUILTIN_FABSF)
phi_check_cxx_source_compiles("int main() { return __builtin_fabs(-1.0) > 0; }"
                              PHI_HAS_INTRINSIC_BUILTIN_FABS)
phi_check_cxx_source_compiles("int main() { return __builtin_fabsl(-1.0) > 0; }"
                              PHI_HAS_INTRINSIC_BUILTIN_FABSL)
phi_check_cxx_source_compiles(
  "class A { virtual ~A(); }; int main() { return __has_virtual_destructor(A); }"
  PHI_HAS_INTRINSIC_HAS_VIRTUAL_DESTRUCTOR)
phi_check_cxx_source_compiles(
  "struct A {virtual void f() = 0;}; int main() { return __is_abstract(A); }"
  PHI_HAS_INTRINSIC_IS_ABSTRACT)
phi_check_cxx_source_compiles("struct A {}; int main() { return __is_aggregate(A); }"
                              PHI_HAS_INTRINSIC_IS_AGGREGATE)
phi_check_cxx_source_compiles("int main() { return __is_assignable(int, int); }"
                              PHI_HAS_INTRINSIC_IS_ASSIGNABLE)
phi_check_cxx_source_compiles(
  "struct A {}; struct B : A {}; int main() { return __is_base_of(A, B); }"
  PHI_HAS_INTRINSIC_IS_BASE_OF)
phi_check_cxx_source_compiles("class A {}; int main() { return __is_class(A); }"
                              PHI_HAS_INTRINSIC_IS_CLASS)
phi_check_cxx_source_compiles("int main() { return __is_constructible(int, int); }"
                              PHI_HAS_INTRINSIC_IS_CONSTRUCTIBLE)
phi_check_cxx_source_compiles("int main() { return __is_const(const int); }"
                              PHI_HAS_INTRINSIC_IS_CONST)
phi_check_cxx_source_compiles("int main() { return __is_convertible_to(int, int); }"
                              PHI_HAS_INTRINSIC_IS_CONVERTIBLE_TO)
phi_check_cxx_source_compiles("int main() { return __is_destructible(int); }"
                              PHI_HAS_INTRINSIC_IS_DESTRUCTIBLE)
phi_check_cxx_source_compiles("struct A {}; int main() { return __is_empty(A); }"
                              PHI_HAS_INTRINSIC_IS_EMPTY)
phi_check_cxx_source_compiles("enum E{}; int main() { return __is_enum(E); }"
                              PHI_HAS_INTRINSIC_IS_ENUM)
phi_check_cxx_source_compiles("class A final {}; int main() { return __is_final(A); }"
                              PHI_HAS_INTRINSIC_IS_FINAL)
phi_check_cxx_source_compiles("int main() { return __is_integral(int); }"
                              PHI_HAS_INTRINSIC_IS_INTEGRAL)
phi_check_cxx_source_compiles("int main() { return __is_scalar(int); }" PHI_HAS_INTRINSIC_IS_SCALAR)
phi_check_cxx_source_compiles("int main() { return __is_standard_layout(int); }"
                              PHI_HAS_INTRINSIC_IS_STANDARD_LAYOUT)
phi_check_cxx_source_compiles("int main() { return __is_member_pointer(void*); }"
                              PHI_HAS_INTRINSIC_IS_MEMBER_POINTER)
phi_check_cxx_source_compiles("int main() { return __is_member_function_pointer(void*); }"
                              PHI_HAS_INTRINSIC_IS_MEMBER_FUNCTION_POINTER)
phi_check_cxx_source_compiles("int main() { return __is_member_object_pointer(void*); }"
                              PHI_HAS_INTRINSIC_IS_MEMBER_OBJECT_POINTER)
phi_check_cxx_source_compiles("int main() { return __is_nothrow_assignable(int, int); }"
                              PHI_HAS_INTRINSIC_IS_NOTHROW_ASSIGNABLE)
phi_check_cxx_source_compiles("int main() { return __is_nothrow_constructible(int, int); }"
                              PHI_HAS_INTRINSIC_IS_NOTHROW_CONSTRUCTIBLE)
phi_check_cxx_source_compiles("int main() { return __is_object(int); }" PHI_HAS_INTRINSIC_IS_OBJECT)
phi_check_cxx_source_compiles(
  "struct A {virtual void f(); }; int main() { return __is_polymorphic(A); }"
  PHI_HAS_INTRINSIC_IS_POLYMORPHIC)
phi_check_cxx_source_compiles("enum E {}; int main() { using T = __underlying_type(E); }"
                              PHI_HAS_INTRINSIC_UNDERLYING_TYPE)
phi_check_cxx_source_compiles("union A {int a; float b;}; int main() { return __is_union(A); }"
                              PHI_HAS_INTRINSIC_IS_UNION)
phi_check_cxx_source_compiles("int main() { return __is_trivial(int); }"
                              PHI_HAS_INTRINSIC_IS_TRIVIAL)
phi_check_cxx_source_compiles("int main() { return __is_trivially_assignable(int, int); }"
                              PHI_HAS_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE)
phi_check_cxx_source_compiles("int main() { return __is_trivially_copyable(int); }"
                              PHI_HAS_INTRINSIC_IS_TRIVIALLY_COPYABLE)
phi_check_cxx_source_compiles("int main() { return __is_trivially_constructible(int, int); }"
                              PHI_HAS_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE)
phi_check_cxx_source_compiles("int main() { return __is_trivially_destructible(int); }"
                              PHI_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE)
phi_check_cxx_source_compiles("int main() { return __is_volatile(volatile int); }"
                              PHI_HAS_INTRINSIC_IS_VOLATILE)
phi_check_cxx_source_compiles("int main() { using t = __remove_const(const int); }"
                              PHI_HAS_INTRINSIC_REMOVE_CONST)
phi_check_cxx_source_compiles("int main() { using t = __remove_volatile(volatile int); }"
                              PHI_HAS_INTRINSIC_REMOVE_VOLATILE)
phi_check_cxx_source_compiles("int main() { using t = __remove_cv(const volatile int); }"
                              PHI_HAS_INTRINSIC_REMOVE_CV)
phi_check_cxx_source_compiles("int main() { return __is_void(void); }" PHI_HAS_INTRINSIC_IS_VOID)
phi_check_cxx_source_compiles("int main() { return __is_array(int[]); }" PHI_HAS_INTRINSIC_IS_ARRAY)
phi_check_cxx_source_compiles("int main() { return __is_pointer(int*); }"
                              PHI_HAS_INTRINSIC_IS_POINTER)
phi_check_cxx_source_compiles("int main() { return __is_reference(int&); }"
                              PHI_HAS_INTRINSIC_IS_REFERENCE)
phi_check_cxx_source_compiles("int main() { return __is_lvalue_reference(int&); }"
                              PHI_HAS_INTRINSIC_IS_LVALUE_REFERENCE)
phi_check_cxx_source_compiles("int main() { return __is_rvalue_reference(int&&); }"
                              PHI_HAS_INTRINSIC_IS_RVALUE_REFERENCE)
phi_check_cxx_source_compiles("int main() { return __is_compound(int); }"
                              PHI_HAS_INTRINSIC_IS_COMPOUND)
phi_check_cxx_source_compiles("int main() { return __is_same(int, int); }"
                              PHI_HAS_INTRINSIC_IS_SAME)
phi_check_cxx_source_compiles("int main() { return __has_trivial_destructor(int); }"
                              PHI_HAS_INTRINSIC_HAS_TRIVIAL_DESTRUCTOR)

# Extensions
phi_check_cxx_source_compiles("#define M(...) 1
int main() { return M(); }" PHI_HAS_EXTENSION_VARIADIC_MACRO_ZERO_ARGS)
phi_check_cxx_source_compiles("int main() { __assume(true); }" PHI_HAS_EXTENSION_ASSUME)
phi_check_cxx_source_compiles("int main() { __builtin_assume(true); }"
                              PHI_HAS_EXTENSION_BUILTIN_ASSUME)
phi_check_cxx_source_compiles("int main() { __builtin_unreachable(); }"
                              PHI_HAS_EXTENSION_BUILTIN_UNREACHABLE)
phi_check_cxx_source_compiles("int main() { __builtin_trap(); }" PHI_HAS_EXTENSION_BUILTIN_TRAP)
phi_check_cxx_source_compiles("__attribute__((flatten)) int main() {}"
                              PHI_HAS_EXTENSION_ATTRIBUTE_FLATTEN)
phi_check_cxx_source_compiles("__attribute__((always_inline)) inline void f(){} int main() {}"
                              PHI_HAS_EXTENSION_ATTRIBUTE_ALWAYS_INLINE)
phi_check_cxx_source_compiles("__attribute__((noinline)) void f(){} int main() {}"
                              PHI_HAS_EXTENSION_ATTRIBUTE_NOINLINE)
phi_check_cxx_source_compiles(
  "__attribute__((warn_unused_result)) int f() { return 3; } int main() {}"
  PHI_HAS_EXTENSION_ATTRIBUTE_WARN_UNUSED_RESULT)
phi_check_cxx_source_compiles("__forceinline void f(){} int main() {}"
                              PHI_HAS_EXTENSION_FORCEINLINE)
phi_check_cxx_source_compiles("__declspec(noinline) void f(){} int main() {}"
                              PHI_HAS_EXTENSION_DECLSPEC_NOINLINE)
phi_check_cxx_source_compiles("int main() { __builtin_expect(true, 1); }"
                              PHI_HAS_EXTENSION_BUILTIN_EXPECT)
phi_check_cxx_source_compiles("#pragma once
int main() {}" PHI_HAS_EXTENSION_PRAGMA_ONCE)
phi_check_cxx_source_compiles("_Check_return_ int f() { return 3; } int main() {}"
                              PHI_HAS_EXTENSION_CHECK_RETURN)
phi_check_cxx_source_compiles("__attribute__((deprecated)) void f() {} int main() { f(); }"
                              PHI_HAS_EXTENSION_ATTRIBUTE_DEPRECATED)
phi_check_cxx_source_compiles("__declspec(deprecated) void f() {} int main() { f(); }"
                              PHI_HAS_EXTENSION_DECLSPEC_DEPRECATED)
phi_check_cxx_source_compiles("struct __declspec(empty_bases) A{}; int main() { return 0; }"
                              PHI_HAS_EXTENSION_DECLSPEC_EMPTY_BASES)
phi_check_cxx_source_compiles("void f(__attribute((unused)) int a) {} int main() {}"
                              PHI_HAS_EXTENSION_ATTRIBUTE_UNUSED)

# Bugs
phi_check_cxx_source_compiles(
  "template <typename> struct AbstractTemplate { virtual ~AbstractTemplate() = 0;}; int main() { static_assert(__is_constructible(AbstractTemplate<int>), \"\"); }"
  PHI_HAS_BUG_GCC_102305) # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=102305)

# Type system
check_type_size("void*" PHI_TYPE_SYSTEM_SIZEOF_VOIDPTR BUILTIN_TYPES_ONLY LANGUAGE CXX)

check_type_size("bool" PHI_TYPE_SYSTEM_SIZEOF_BOOL BUILTIN_TYPES_ONLY LANGUAGE CXX)
check_type_size("char" PHI_TYPE_SYSTEM_SIZEOF_CHAR BUILTIN_TYPES_ONLY LANGUAGE CXX)
check_type_size("wchar_t" PHI_TYPE_SYSTEM_SIZEOF_WCHAR_T BUILTIN_TYPES_ONLY LANGUAGE CXX)
check_type_size("short" PHI_TYPE_SYSTEM_SIZEOF_SHORT BUILTIN_TYPES_ONLY LANGUAGE CXX)
check_type_size("int" PHI_TYPE_SYSTEM_SIZEOF_INT BUILTIN_TYPES_ONLY LANGUAGE CXX)
check_type_size("long" PHI_TYPE_SYSTEM_SIZEOF_LONG BUILTIN_TYPES_ONLY LANGUAGE CXX)
check_type_size("long long" PHI_TYPE_SYSTEM_SIZEOF_LONG_LONG BUILTIN_TYPES_ONLY LANGUAGE CXX)

check_type_size("float" PHI_TYPE_SYSTEM_SIZEOF_FLOAT BUILTIN_TYPES_ONLY LANGUAGE CXX)
check_type_size("double" PHI_TYPE_SYSTEM_SIZEOF_DOUBLE BUILTIN_TYPES_ONLY LANGUAGE CXX)
check_type_size("long double" PHI_TYPE_SYSTEM_SIZEOF_LONG_DOUBLE BUILTIN_TYPES_ONLY LANGUAGE CXX)

# configure file
configure_file("scripts/cmake/Features.hpp.in"
               "generated_files/include/Phi/CompilerSupport/Features.hpp")
configure_file("scripts/cmake/TypeSystem.hpp.in"
               "generated_files/include/Phi/CompilerSupport/TypeSystem.hpp")
include_directories(${CMAKE_CURRENT_BINARY_DIR}/generated_files/include)
