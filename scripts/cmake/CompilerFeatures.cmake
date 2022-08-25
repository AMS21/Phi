phi_include_guard()

include(CheckTypeSize)
include(CompilerWarnings)
include(Standard)
include(internal/PhiCheckCXXSourceCompiles)
include(Common)

# Set compile flags
list(JOIN _common_flags " " common_flags_joined)
set(CMAKE_REQUIRED_FLAGS
    "${CMAKE_REQUIRED_FLAGS} ${phi_latest_standard_flag} ${_phi_check_required_flags}")

# Features

# C++-11 Features
phi_check_cxx_source_compiles("int main() { constexpr int i = 3; return i; }"
                              PHI_HAS_FEATURE_CONSTEXPR)
phi_check_cxx_source_compiles("[[noreturn]] void f(); int main() { }" PHI_HAS_FEATURE_NORETURN)

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
phi_check_cxx_source_compiles("[[nodiscard]] int f() { return 3; } int main() { return f(); }"
                              PHI_HAS_FEATURE_NODISCARD)
phi_check_cxx_source_compiles("void f([[maybe_unused]] int a) {} int main() { f(3); }"
                              PHI_HAS_FEATURE_MAYBE_UNUSED)
phi_check_cxx_source_compiles("int main() { if constexpr (true) {} }" PHI_HAS_FEATURE_IF_CONSTEXPR)

# C++-20 Features
phi_check_cxx_source_compiles("int main() { char8_t c; }" PHI_HAS_FEATURE_CHAR8_T)
phi_check_cxx_source_compiles("struct A{ constexpr ~A() {} }; int main() { A a; }"
                              PHI_HAS_FEATURE_CONSTEXPR_DESTRUCTOR)
phi_check_cxx_source_compiles(
  "struct A{ constexpr virtual void f() {}; }; int main() { A a; a.f(); }"
  PHI_HAS_FEATURE_CONSTEXPR_VIRTUAL)
phi_check_cxx_source_compiles("int main() { if ( 1 == 1) [[likely]] {} return 0; }"
                              PHI_HAS_FEATURE_LIKELY)
phi_check_cxx_source_compiles("int main() { switch (1) { [[likely]] case 1: return 0; } }"
                              PHI_HAS_FEATURE_LIKELY_CASE)
phi_check_cxx_source_compiles(
  "#include <compare>
struct Point {int x; int y; friend auto operator<=>(const Point&, const Point&) = default;};
int main() {}" PHI_HAS_FEATURE_THREE_WAY_COMPARISON)
phi_check_cxx_source_compiles("consteval void f(); int main() { return 0; }"
                              PHI_HAS_FEATURE_CONSTEVAL)
phi_check_cxx_source_compiles("int main() { constinit static int a = 21; }"
                              PHI_HAS_FEATURE_CONSTINIT)

# C++-23 Features
phi_check_cxx_source_compiles("int main() { if consteval { return 1; } else { return 0; } }"
                              PHI_HAS_FEATURE_IF_CONSTEVAL)

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
phi_check_cxx_source_compiles("int main() { return __builtin_floorf(3.14); }"
                              PHI_HAS_INTRINSIC_BUILTIN_FLOORF)
phi_check_cxx_source_compiles("int main() { return __builtin_floor(3.14); }"
                              PHI_HAS_INTRINSIC_BUILTIN_FLOOR)
phi_check_cxx_source_compiles("int main() { return __builtin_floorl(3.14); }"
                              PHI_HAS_INTRINSIC_BUILTIN_FLOORL)
phi_check_cxx_source_compiles("int main() { return __array_rank(int[2]); }"
                              PHI_HAS_INTRINSIC_ARRAY_RANK)
phi_check_cxx_source_compiles("int main() { return __has_nothrow_assign(int); }"
                              PHI_HAS_INTRINSIC_HAS_NOTHROW_ASSIGN)
phi_check_cxx_source_compiles("int main() { return __has_nothrow_move_assign(int); }"
                              PHI_HAS_INTRINSIC_HAS_NOTHROW_MOVE_ASSIGN)
phi_check_cxx_source_compiles("int main() { return __has_nothrow_copy(int); }"
                              PHI_HAS_INTRINSIC_HAS_NOTHROW_COPY)
phi_check_cxx_source_compiles("int main() { return __has_nothrow_constructor(int); }"
                              PHI_HAS_INTRINSIC_HAS_NOTHROW_CONSTRUCTOR)
phi_check_cxx_source_compiles("int main() { return __has_nothrow_move_constructor(int); }"
                              PHI_HAS_INTRINSIC_HAS_NOTHROW_MOVE_CONSTRUCTOR)
phi_check_cxx_source_compiles("int main() { return __has_trivial_assign(int); }"
                              PHI_HAS_INTRINSIC_HAS_TRIVIAL_ASSIGN)
phi_check_cxx_source_compiles("int main() { return __has_trivial_move_assign(int); }"
                              PHI_HAS_INTRINSIC_HAS_TRIVIAL_MOVE_ASSIGN)
phi_check_cxx_source_compiles("int main() { return __has_trivial_copy(int); }"
                              PHI_HAS_INTRINSIC_HAS_TRIVIAL_COPY)
phi_check_cxx_source_compiles("int main() { return __has_trivial_constructor(int); }"
                              PHI_HAS_INTRINSIC_HAS_TRIVIAL_CONSTRUCTOR)
phi_check_cxx_source_compiles("int main() { return __has_trivial_move_constructor(int); }"
                              PHI_HAS_INTRINSIC_HAS_TRIVIAL_MOVE_CONSTRUCTOR)
phi_check_cxx_source_compiles("int main() { return __is_arithmetic(int); }"
                              PHI_HAS_INTRINSIC_IS_ARITHMETIC)
phi_check_cxx_source_compiles("int main() { return __is_complete_type(int); }"
                              PHI_HAS_INTRINSIC_IS_COMPLETE_TYPE)
phi_check_cxx_source_compiles("int main() { return __is_convertible(int, int); }"
                              PHI_HAS_INTRINSIC_IS_CONVERTIBLE)
phi_check_cxx_source_compiles("int main() { return __is_function(int); }"
                              PHI_HAS_INTRINSIC_IS_FUNCTION)
phi_check_cxx_source_compiles("int main() { return __is_fundamental(int); }"
                              PHI_HAS_INTRINSIC_IS_FUNDAMENTAL)
phi_check_cxx_source_compiles("int main() { return __is_nothrow_destructible(int); }"
                              PHI_HAS_INTRINSIC_IS_NOTHROW_DESTRUCTIBLE)
phi_check_cxx_source_compiles("int main() { return __is_same_as(int, int); }"
                              PHI_HAS_INTRINSIC_IS_SAME_AS)
phi_check_cxx_source_compiles("int main() { return __is_lvalue_expr(3); }"
                              PHI_HAS_INTRINSIC_IS_LVALUE_EXPR)
phi_check_cxx_source_compiles("int main() { return __is_rvalue_expr(3); }"
                              PHI_HAS_INTRINSIC_IS_RVALUE_EXPR)
phi_check_cxx_source_compiles("int main() { return __has_assign(int); }"
                              PHI_HAS_INTRINSIC_HAS_ASSIGN)
phi_check_cxx_source_compiles("int main() { return __has_copy(int); }" PHI_HAS_INTRINSIC_HAS_COPY)
phi_check_cxx_source_compiles("int main() { return __is_signed(int); }" PHI_HAS_INTRINSIC_IS_SIGNED)
phi_check_cxx_source_compiles("int main() { return __is_unsigned(int); }"
                              PHI_HAS_INTRINSIC_IS_UNSIGNED)
phi_check_cxx_source_compiles("int main() { return __is_pod(int); }" PHI_HAS_INTRINSIC_IS_POD)
phi_check_cxx_source_compiles("int main() { return __is_floating_point(float); }"
                              PHI_HAS_INTRINSIC_IS_FLOATING_POINT)
phi_check_cxx_source_compiles("int main() { return __is_sealed(int); }" PHI_HAS_INTRINSIC_IS_SEALED)
phi_check_cxx_source_compiles("int main() { return __is_literal(int); }"
                              PHI_HAS_INTRINSIC_IS_LITERAL)
phi_check_cxx_source_compiles("int main() { return __is_literal_type(int); }"
                              PHI_HAS_INTRINSIC_IS_LITERAL_TYPE)
phi_check_cxx_source_compiles("int main() { return __builtin_LINE(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_LINE)
phi_check_cxx_source_compiles("int main() { return __builtin_COLUMN(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_COLUMN)
phi_check_cxx_source_compiles("int main() { const char* f =  __builtin_FUNCTION(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_FUNCTION)
phi_check_cxx_source_compiles("int main() { const char* f = __builtin_FILE(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_FILE)
phi_check_cxx_source_compiles("int main() { double d = __builtin_huge_val(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_HUGE_VAL)
phi_check_cxx_source_compiles("int main() { float d = __builtin_huge_valf(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_HUGE_VALF)
phi_check_cxx_source_compiles("int main() { long double d = __builtin_huge_vall(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_HUGE_VALL)
phi_check_cxx_source_compiles("int main() { double d = __builtin_inf(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_INF)
phi_check_cxx_source_compiles("int main() { float d = __builtin_inff(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_INFF)
phi_check_cxx_source_compiles("int main() { long double d = __builtin_infl(); }"
                              PHI_HAS_INTRINSIC_BUILTIN_INFL)
phi_check_cxx_source_compiles("int main() { int i == __builtin_isinf_sign(0.0); }"
                              PHI_HAS_INTRINSIC_BUILTIN_ISINF_SIGN)
phi_check_cxx_source_compiles("int main() { double d = __builtin_nan(\"\"); }"
                              PHI_HAS_INTRINSIC_BUILTIN_NAN)
phi_check_cxx_source_compiles("int main() { float f = __builtin_nanf(\"\"); }"
                              PHI_HAS_INTRINSIC_BUILTIN_NANF)
phi_check_cxx_source_compiles("int main() { long double l = __builtin_nanl(\"\"); }"
                              PHI_HAS_INTRINSIC_BUILTIN_NANL)
phi_check_cxx_source_compiles("int main() { double d = __builtin_nans(\"\"); }"
                              PHI_HAS_INTRINSIC_BUILTIN_NANS)
phi_check_cxx_source_compiles("int main() { float f = __builtin_nansf(\"\"); }"
                              PHI_HAS_INTRINSIC_BUILTIN_NANSF)
phi_check_cxx_source_compiles("int main() { long double l = __builtin_nansl(\"\"); }"
                              PHI_HAS_INTRINSIC_BUILTIN_NANSL)
phi_check_cxx_source_compiles("int main() { int i = __builtin_ffs(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_FFS)
phi_check_cxx_source_compiles("int main() { int i = __builtin_ffsl(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_FFSL)
phi_check_cxx_source_compiles("int main() { int i = __builtin_ffsll(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_FFSLL)
phi_check_cxx_source_compiles("int main() { int i = __builtin_clz(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_CLZ)
phi_check_cxx_source_compiles("int main() { int i = __builtin_clzl(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_CLZL)
phi_check_cxx_source_compiles("int main() { int i = __builtin_clzll(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_CLZLL)
phi_check_cxx_source_compiles("int main() { int i = __builtin_ctz(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_CTZ)
phi_check_cxx_source_compiles("int main() { int i = __builtin_ctzl(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_CTZL)
phi_check_cxx_source_compiles("int main() { int i = __builtin_ctzll(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_CTZLL)
phi_check_cxx_source_compiles("int main() { int i = __builtin_clrsb(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_CLRSB)
phi_check_cxx_source_compiles("int main() { int i = __builtin_clrsbl(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_CLRSBL)
phi_check_cxx_source_compiles("int main() { int i = __builtin_clrsbll(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_CLRSBLL)
phi_check_cxx_source_compiles("int main() { int i = __builtin_popcount(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_POPCOUNT)
phi_check_cxx_source_compiles("int main() { int i = __builtin_popcountl(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_POPCOUNTL)
phi_check_cxx_source_compiles("int main() { int i = __builtin_popcountll(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_POPCOUNTLL)
phi_check_cxx_source_compiles("int main() { int i = __builtin_parity(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_PARITY)
phi_check_cxx_source_compiles("int main() { int i = __builtin_parityl(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_PARITYL)
phi_check_cxx_source_compiles("int main() { int i = __builtin_parityll(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_PARITYLL)
phi_check_cxx_source_compiles("int main() { int i = __builtin_bswap16(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_BSWAP16)
phi_check_cxx_source_compiles("int main() { int i = __builtin_bswap32(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_BSWAP32)
phi_check_cxx_source_compiles("int main() { int i = __builtin_bswap64(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_BSWAP64)
phi_check_cxx_source_compiles("int main() { int i = __builtin_bswap128(1); }"
                              PHI_HAS_INTRINSIC_BUILTIN_BSWAP128)
phi_check_cxx_source_compiles("int main() { return __builtin_isnan(0.0); }"
                              PHI_HAS_INTRINSIC_BUILTIN_ISNAN)
phi_check_cxx_source_compiles("int main() { return __is_layout_compatible(int, int); }"
                              PHI_HAS_INTRINSIC_IS_LAYOUT_COMPATIBLE)
phi_check_cxx_source_compiles(
  "int main() { return __is_pointer_interconvertible_base_of(int, int); }"
  PHI_HAS_INTRINSIC_IS_POINTER_INTERCONVERTIBLE_BASE_OF)
phi_check_cxx_source_compiles(
  "struct A { int i; long l; };
int main() { return __builtin_is_pointer_interconvertible_with_class(&A::i); }"
  PHI_HAS_INTRINSIC_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS)
phi_check_cxx_source_compiles(
  "struct A { int a; };
int main() { return __builtin_is_corresponding_member(&A::a,&A::a); }"
  PHI_HAS_INTRINSIC_IS_CORRESPONDING_MEMBER)
phi_check_cxx_source_compiles("struct A { int a; };
int main() { return __builtin_offsetof(A, a); }" PHI_HAS_INTRINSIC_BUILTIN_OFFSET_OF)
phi_check_cxx_source_compiles("int main() { return __builtin_isinf(0.0); }"
                              PHI_HAS_INTRINSIC_BUILTIN_ISINF)
phi_check_cxx_source_compiles("int main() { __builtin_abort(); }" PHI_HAS_INTRINSIC_BUILTIN_ABORT)

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
  PHI_STDLIB_GLIBCXX)
phi_check_cxx_source_compiles(
  "#include <cstddef>
#if !defined(_LIBCPP_VERSION)
#error
#endif
int main() {}"
  PHI_STDLIB_LLVM_LIBCXX)
phi_check_cxx_source_compiles(
  "#include <cstddef>
#if !defined(_MSVC_STL_VERSION)
#error
#endif
int main() {}"
  PHI_STDLIB_MSVC_STL)

# Only require the latest standard flag
set(CMAKE_REQUIRED_FLAGS "${phi_latest_standard_flag}")

# Type system
include(internal/PhiCXXCheckTypeSize)

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

# configure files
configure_file("scripts/cmake/features.hpp.in"
               "${PHI_GENERATED_FILES_DIR}/phi/generated/compiler_support/features.hpp")
configure_file("scripts/cmake/type_system.hpp.in"
               "${PHI_GENERATED_FILES_DIR}/phi/generated/compiler_support/type_system.hpp")
