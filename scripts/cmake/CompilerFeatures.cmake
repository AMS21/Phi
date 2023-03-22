phi_include_guard()

include(CheckTypeSize)
include(Common)
include(CompilerWarnings)
include(internal/CheckCXXSourceCompiles)
include(internal/CXXCheckTypeSize)
include(Standard)

# Set compile flags
string(JOIN " " _glued_flags ${phi_check_required_flags} ${_phi_common_flags_supported}
       ${_phi_common_cxx_flags_supported})
set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${phi_latest_standard_flag} ${_glued_flags}")

# Features

# Lib
phi_check_cxx_source_compiles("#include <string_view>
int main() {}" PHI_HAS_LIB_STRING_VIEW)

# Intrinsics

# TODO: Combine these with the builin gcc uses
phi_check_cxx_source_compiles("int main() { return __builtin_LINE(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_LINE)
phi_check_cxx_source_compiles("int main() { return __builtin_COLUMN(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_COLUMN)
phi_check_cxx_source_compiles("int main() { const char* f =  __builtin_FUNCTION(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_FUNCTION)
phi_check_cxx_source_compiles("int main() { const char* f = __builtin_FILE(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_FILE)

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
phi_check_cxx_source_compiles("int main() { int i = 0 / 0; float f = 0.0 / 0.0; }"
                              PHI_HAS_EXTENSION_ALLOW_DIVIDE_BY_ZERO_CONSTANT)
phi_check_cxx_source_compiles("int main() { return __builtin_constant_p(1); }"
                              PHI_HAS_EXTENSION_BUILTIN_CONSTANT_P)
phi_check_cxx_source_compiles("_Noreturn void f(); int main(){ }" PHI_HAS_EXTENSION_NORETURN)
phi_check_cxx_source_compiles("__attribute__ ((noreturn)) void fatal (); int main() {}"
                              PHI_HAS_EXTENSION_ATTRIBUTE_NORETURN)
phi_check_cxx_source_compiles("__declspec(noreturn) void f(); int main() {}"
                              PHI_HAS_EXTENSION_DECLSPEC_NORETURN)
phi_check_cxx_source_compiles("int main() { return __COUNTER__; }" PHI_HAS_EXTENSION_COUNTER)
phi_check_cxx_source_compiles("int main() { __int8 i; }" PHI_HAS_EXTENSION_INT8)
phi_check_cxx_source_compiles("int main() { __int16 i; }" PHI_HAS_EXTENSION_INT16)
phi_check_cxx_source_compiles("int main() { __int32 i; }" PHI_HAS_EXTENSION_INT32)
phi_check_cxx_source_compiles("int main() { __int64 i; }" PHI_HAS_EXTENSION_INT64)
phi_check_cxx_source_compiles("int main() { __int128 i; }" PHI_HAS_EXTENSION_INT128)
phi_check_cxx_source_compiles("int main() { _Float16 f; }" PHI_HAS_EXTENSION_FLOAT16)
phi_check_cxx_source_compiles("int main() { __float128 f; }" PHI_HAS_EXTENSION_FLOAT128)
phi_check_cxx_source_compiles("int main() { __fp16 f; }" PHI_HAS_EXTENSION_FP16)
phi_check_cxx_source_compiles("__attribute__ ((const)) int main() {}"
                              PHI_HAS_EXTENSION_ATTRIBUTE_CONST)
phi_check_cxx_source_compiles("__attribute__ ((pure)) int main() {}"
                              PHI_HAS_EXTENSION_ATTRIBUTE_PURE)
phi_check_cxx_source_compiles("int main() { int a[0]; }" PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY)
phi_check_cxx_source_compiles("class [[gsl::Owner]] A{}; int main() {}" PHI_HAS_EXTENSION_GSL_OWNER)
phi_check_cxx_source_compiles("class [[gsl::Pointer]] A{}; int main() {}"
                              PHI_HAS_EXTENSION_GSL_POINTER)
phi_check_cxx_source_compiles("void* __attribute__((returns_nonnull)) f(); int main() {}"
                              PHI_HAS_EXTENSION_ATTRIBUTE_RETURNS_NONNULL)
phi_check_cxx_source_compiles("void* _Ret_notnull_ f(); int main() {}"
                              PHI_HAS_EXTENSION_RET_NONNULL)
phi_check_cxx_source_compiles("void f(void* a) __attribute__((nonnull)); int main(){}"
                              PHI_HAS_EXTENSION_ATTRIBUTE_NONNULL)
phi_check_cxx_source_compiles(
  "extern \"C\" void __fastfail(unsigned int); int main() { __fastfail(0); }"
  PHI_HAS_EXTENSION_FASTFAIL)
phi_check_cxx_source_compiles("__attribute__ ((cold)) void f(); int main() { return 0; }"
                              PHI_HAS_EXTENSION_ATTRIBUTE_COLD)
phi_check_cxx_source_compiles("void f(int* __restrict a) {} int main() {}"
                              PHI_HAS_EXTENSION_RESTRICT)
phi_check_cxx_source_compiles("void f(int* __restrict__ a) {} int main() {}"
                              PHI_HAS_EXTENSION_RESTRICT_UNDERSCORE)
phi_check_cxx_source_compiles("int main(){ long double a = 1e+4932L; }"
                              PHI_HAS_EXTENSION_FLOAT128_LITERALS)

# Bugs
phi_check_cxx_source_compiles(
  "template <typename> struct abstract_template { virtual ~abstract_template() = 0;}; int main() { static_assert(__is_constructible(abstract_template<int>), \"\"); }"
  PHI_HAS_BUG_GCC_102305) # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=102305)

# Used standard library
phi_check_cxx_source_compiles(
  "#include <cstddef>
#if !defined(__GLIBCXX__)
#error
#endif
int main() {}"
  PHI_DEFAULT_STDLIB_GLIBCXX)
phi_check_cxx_source_compiles(
  "#include <cstddef>
#if !defined(_LIBCPP_VERSION)
#error
#endif
int main() {}"
  PHI_DEFAULT_STDLIB_LLVM_LIBCXX)
phi_check_cxx_source_compiles(
  "#include <cstddef>
#if !defined(_MSVC_STL_VERSION)
#error
#endif
int main() {}"
  PHI_DEFAULT_STDLIB_MSVC_STL)

# Only require the latest standard flag
set(CMAKE_REQUIRED_FLAGS "${phi_latest_standard_flag}")

# Type system
phi_cxx_check_type_size("void*" PHI_TYPE_SYSTEM_SIZEOF_VOIDPTR)

phi_cxx_check_type_size("bool" PHI_TYPE_SYSTEM_SIZEOF_BOOL)
phi_cxx_check_type_size("char" PHI_TYPE_SYSTEM_SIZEOF_CHAR)
phi_cxx_check_type_size("wchar_t" PHI_TYPE_SYSTEM_SIZEOF_WCHAR_T)
phi_cxx_check_type_size("short" PHI_TYPE_SYSTEM_SIZEOF_SHORT)
phi_cxx_check_type_size("int" PHI_TYPE_SYSTEM_SIZEOF_INT)
phi_cxx_check_type_size("long" PHI_TYPE_SYSTEM_SIZEOF_LONG)
phi_cxx_check_type_size("long long" PHI_TYPE_SYSTEM_SIZEOF_LONG_LONG)

phi_cxx_check_type_size("float" PHI_TYPE_SYSTEM_SIZEOF_FLOAT)
phi_cxx_check_type_size("double" PHI_TYPE_SYSTEM_SIZEOF_DOUBLE)
phi_cxx_check_type_size("long double" PHI_TYPE_SYSTEM_SIZEOF_LONG_DOUBLE)

phi_check_cxx_source_compiles("int main() { static_assert(char(-1) < char(0), \"\"); }"
                              PHI_TYPE_SYSTEM_CHAR_SIGNED)
phi_check_cxx_source_compiles("int main() { static_assert(wchar_t(-1) < wchar_t(0), \"\"); }"
                              PHI_TYPE_SYSTEM_WCHAR_T_SIGNED)

# configure files
configure_file("scripts/cmake/features.hpp.in"
               "${PHI_GENERATED_FILES_DIR}/phi/generated/compiler_support/features.hpp")
configure_file("scripts/cmake/type_system.hpp.in"
               "${PHI_GENERATED_FILES_DIR}/phi/generated/compiler_support/type_system.hpp")
