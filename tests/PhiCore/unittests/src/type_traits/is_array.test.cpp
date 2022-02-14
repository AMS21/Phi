#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/container/array.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_arithmetic.hpp>
#include <phi/type_traits/is_array.hpp>
#include <phi/type_traits/is_bool.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_compound.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_floating_point.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_fundamental.hpp>
#include <phi/type_traits/is_integer.hpp>
#include <phi/type_traits/is_integral.hpp>
#include <phi/type_traits/is_lvalue_reference.hpp>
#include <phi/type_traits/is_member_function_pointer.hpp>
#include <phi/type_traits/is_member_object_pointer.hpp>
#include <phi/type_traits/is_member_pointer.hpp>
#include <phi/type_traits/is_null_pointer.hpp>
#include <phi/type_traits/is_object.hpp>
#include <phi/type_traits/is_pointer.hpp>
#include <phi/type_traits/is_reference.hpp>
#include <phi/type_traits/is_rvalue_reference.hpp>
#include <phi/type_traits/is_scalar.hpp>
#include <phi/type_traits/is_union.hpp>
#include <phi/type_traits/is_void.hpp>
#include <array>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_array_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<T>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
#endif
    STATIC_REQUIRE(phi::is_compound<T>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_fundamental<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<T>::value);
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_scalar<T>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_array<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<T>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
#    endif
    STATIC_REQUIRE(phi::is_compound_v<T>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<T>);
#    if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
#    if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_scalar_v<T>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);
#endif

    // Standard compatbility
    STATIC_REQUIRE(std::is_array<T>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_array_v<T>);
#endif
}

template <typename T>
void test_is_array()
{
    test_is_array_impl<T>();
    test_is_array_impl<const T>();
    test_is_array_impl<volatile T>();
    test_is_array_impl<const volatile T>();
}

template <typename T>
void test_is_not_array_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE(phi::is_not_array<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE(phi::is_not_array_v<T>);
#endif

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_array<T>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_array_v<T>);
#endif
}

template <typename T>
void test_is_not_array()
{
    test_is_not_array_impl<T>();
    test_is_not_array_impl<const T>();
    test_is_not_array_impl<volatile T>();
    test_is_not_array_impl<const volatile T>();
}

using array            = char[3];
using const_array      = const char[3];
using incomplete_array = char[];

TEST_CASE("is_array")
{
    test_is_array<char[3]>();
    test_is_array<char[]>();
    test_is_array<char[][3]>();
    test_is_array<char[3][3]>();
    test_is_array<Union[]>();
    test_is_array<Union[2]>();
    test_is_array<Class[]>();
    test_is_array<Class[3]>();
    test_is_array<array>();
    test_is_array<const_array>();
    test_is_array<incomplete_array>();
    test_is_array<IncompleteType[]>();
    test_is_array<IncompleteType[3]>();
    test_is_array<int[1]>();
    test_is_array<int[1][2]>();
    test_is_array<int[1][2][3]>();
    test_is_array<int[1][2][3][4]>();
    test_is_array<int[1][2][3][4][5]>();
    test_is_array<int[1][2][3][4][5][6]>();
    test_is_array<int[1][2][3][4][5][6][7]>();
    test_is_array<int[1][2][3][4][5][6][7][8]>();
    test_is_array<int[1][2][3][4][5][6][7][8][9]>();
    test_is_array<int[1][2][3][4][5][6][7][8][9][10]>();
    test_is_not_array<std::array<int, 3>>();
    test_is_not_array<phi::array<int, 3>>();

    test_is_array<int[2]>();
    test_is_array<int[]>();
    test_is_array<int[2][3]>();
    test_is_array<int[][3]>();
    test_is_array<float* [2]>();
    test_is_array<float*[]>();
    test_is_array<float* [2][3]>();
    test_is_array<float*[][3]>();
    test_is_array<Class[2]>();
    test_is_array<Class[]>();
    test_is_array<Class[2][3]>();
    test_is_array<Class[][3]>();

    test_is_not_array<void>();
    test_is_not_array<phi::nullptr_t>();
    test_is_not_array<bool>();
    test_is_not_array<char>();
    test_is_not_array<signed char>();
    test_is_not_array<unsigned char>();
    test_is_not_array<short>();
    test_is_not_array<unsigned short>();
    test_is_not_array<int>();
    test_is_not_array<unsigned int>();
    test_is_not_array<long>();
    test_is_not_array<unsigned long>();
    test_is_not_array<long long>();
    test_is_not_array<unsigned long long>();
    test_is_not_array<float>();
    test_is_not_array<double>();
    test_is_not_array<long double>();
    test_is_not_array<char8_t>();
    test_is_not_array<char16_t>();
    test_is_not_array<char32_t>();
    test_is_not_array<wchar_t>();

    test_is_not_array<phi::boolean>();
    test_is_not_array<phi::integer<signed char>>();
    test_is_not_array<phi::integer<unsigned char>>();
    test_is_not_array<phi::integer<short>>();
    test_is_not_array<phi::integer<unsigned short>>();
    test_is_not_array<phi::integer<int>>();
    test_is_not_array<phi::integer<unsigned int>>();
    test_is_not_array<phi::integer<long>>();
    test_is_not_array<phi::integer<unsigned long>>();
    test_is_not_array<phi::integer<long long>>();
    test_is_not_array<phi::integer<unsigned long long>>();
    test_is_not_array<phi::floating_point<float>>();
    test_is_not_array<phi::floating_point<double>>();
    test_is_not_array<phi::floating_point<long double>>();

    test_is_not_array<std::vector<int>>();
    test_is_not_array<phi::scope_ptr<int>>();

    test_is_not_array<int&>();
    test_is_not_array<const int&>();
    test_is_not_array<volatile int&>();
    test_is_not_array<const volatile int&>();
    test_is_not_array<int&&>();
    test_is_not_array<const int&&>();
    test_is_not_array<volatile int&&>();
    test_is_not_array<const volatile int&&>();
    test_is_not_array<int*>();
    test_is_not_array<const int*>();
    test_is_not_array<volatile int*>();
    test_is_not_array<const volatile int*>();
    test_is_not_array<int**>();
    test_is_not_array<const int**>();
    test_is_not_array<volatile int**>();
    test_is_not_array<const volatile int**>();
    test_is_not_array<int*&>();
    test_is_not_array<const int*&>();
    test_is_not_array<volatile int*&>();
    test_is_not_array<const volatile int*&>();
    test_is_not_array<int*&&>();
    test_is_not_array<const int*&&>();
    test_is_not_array<volatile int*&&>();
    test_is_not_array<const volatile int*&&>();
    test_is_not_array<void*>();
    test_is_array<char[3]>();
    test_is_array<char[]>();
    test_is_array<char* [3]>();
    test_is_array<char*[]>();
    test_is_not_array<int(*)[3]>();
    test_is_not_array<int(*)[]>();
    test_is_not_array<int(&)[3]>();
    test_is_not_array<int(&)[]>();
    test_is_not_array<int(&&)[3]>();
    test_is_not_array<int(&&)[]>();
    test_is_array<char[3][2]>();
    test_is_array<char[][2]>();
    test_is_array<char* [3][2]>();
    test_is_array<char*[][2]>();
    test_is_not_array<int(*)[3][2]>();
    test_is_not_array<int(*)[][2]>();
    test_is_not_array<int(&)[3][2]>();
    test_is_not_array<int(&)[][2]>();
    test_is_not_array<int(&&)[3][2]>();
    test_is_not_array<int(&&)[][2]>();
    test_is_not_array<Class>();
    test_is_array<Class[]>();
    test_is_array<Class[2]>();
    test_is_not_array<Template<void>>();
    test_is_not_array<Template<int>>();
    test_is_not_array<Template<Class>>();
    test_is_not_array<Template<IncompleteType>>();
    test_is_not_array<VariadicTemplate<>>();
    test_is_not_array<VariadicTemplate<void>>();
    test_is_not_array<VariadicTemplate<int>>();
    test_is_not_array<VariadicTemplate<Class>>();
    test_is_not_array<VariadicTemplate<IncompleteType>>();
    test_is_not_array<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_array<PublicDerivedFromTemplate<Base>>();
    test_is_not_array<PublicDerivedFromTemplate<Derived>>();
    test_is_not_array<PublicDerivedFromTemplate<Class>>();
    test_is_not_array<PrivateDerivedFromTemplate<Base>>();
    test_is_not_array<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_array<PrivateDerivedFromTemplate<Class>>();
    test_is_not_array<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_array<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_array<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_array<Union>();
    test_is_not_array<NonEmptyUnion>();
    test_is_not_array<Empty>();
    test_is_not_array<NotEmpty>();
    test_is_not_array<BitZero>();
    test_is_not_array<BitOne>();
    test_is_not_array<Base>();
    test_is_not_array<Derived>();
    test_is_not_array<Abstract>();
    test_is_not_array<PublicAbstract>();
    test_is_not_array<PrivateAbstract>();
    test_is_not_array<ProtectedAbstract>();
    test_is_not_array<AbstractTemplate<int>>();
    test_is_not_array<AbstractTemplate<double>>();
    test_is_not_array<AbstractTemplate<Class>>();
    test_is_not_array<AbstractTemplate<IncompleteType>>();
    test_is_not_array<Final>();
    test_is_not_array<PublicDestructor>();
    test_is_not_array<ProtectedDestructor>();
    test_is_not_array<PrivateDestructor>();
    test_is_not_array<VirtualPublicDestructor>();
    test_is_not_array<VirtualProtectedDestructor>();
    test_is_not_array<VirtualPrivateDestructor>();
    test_is_not_array<PurePublicDestructor>();
    test_is_not_array<PureProtectedDestructor>();
    test_is_not_array<PurePrivateDestructor>();
    test_is_not_array<DeletedPublicDestructor>();
    test_is_not_array<DeletedProtectedDestructor>();
    test_is_not_array<DeletedPrivateDestructor>();
    test_is_not_array<DeletedVirtualPublicDestructor>();
    test_is_not_array<DeletedVirtualProtectedDestructor>();
    test_is_not_array<DeletedVirtualPrivateDestructor>();
    test_is_not_array<Final>();
    test_is_not_array<Enum>();
    test_is_not_array<EnumSigned>();
    test_is_not_array<EnumUnsigned>();
    test_is_not_array<EnumClass>();
    test_is_not_array<EnumStruct>();
    test_is_not_array<Function>();
    test_is_not_array<FunctionPtr>();
    test_is_not_array<MemberObjectPtr>();
    test_is_not_array<MemberFunctionPtr>();
    test_is_not_array<IncompleteType>();
    test_is_not_array<IncompleteTemplate<void>>();
    test_is_not_array<IncompleteTemplate<int>>();
    test_is_not_array<IncompleteTemplate<Class>>();
    test_is_not_array<IncompleteTemplate<IncompleteType>>();
    test_is_not_array<IncompleteVariadicTemplate<>>();
    test_is_not_array<IncompleteVariadicTemplate<void>>();
    test_is_not_array<IncompleteVariadicTemplate<int>>();
    test_is_not_array<IncompleteVariadicTemplate<Class>>();
    test_is_not_array<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_array<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_array<int Class::*>();
    test_is_not_array<float Class::*>();
    test_is_not_array<void * Class::*>();
    test_is_not_array<int * Class::*>();
    test_is_not_array<int Class::*&>();
    test_is_not_array<float Class::*&>();
    test_is_not_array<void * Class::*&>();
    test_is_not_array<int * Class::*&>();
    test_is_not_array<int Class::*&&>();
    test_is_not_array<float Class::*&&>();
    test_is_not_array<void * Class::*&&>();
    test_is_not_array<int * Class::*&&>();
    test_is_not_array<int Class::*const>();
    test_is_not_array<float Class::*const>();
    test_is_not_array<void * Class::*const>();
    test_is_not_array<int Class::*const&>();
    test_is_not_array<float Class::*const&>();
    test_is_not_array<void * Class::*const&>();
    test_is_not_array<int Class::*const&&>();
    test_is_not_array<float Class::*const&&>();
    test_is_not_array<void * Class::*const&&>();
    test_is_not_array<int Class::*volatile>();
    test_is_not_array<float Class::*volatile>();
    test_is_not_array<void * Class::*volatile>();
    test_is_not_array<int Class::*volatile&>();
    test_is_not_array<float Class::*volatile&>();
    test_is_not_array<void * Class::*volatile&>();
    test_is_not_array<int Class::*volatile&&>();
    test_is_not_array<float Class::*volatile&&>();
    test_is_not_array<void * Class::*volatile&&>();
    test_is_not_array<int Class::*const volatile>();
    test_is_not_array<float Class::*const volatile>();
    test_is_not_array<void * Class::*const volatile>();
    test_is_not_array<int Class::*const volatile&>();
    test_is_not_array<float Class::*const volatile&>();
    test_is_not_array<void * Class::*const volatile&>();
    test_is_not_array<int Class::*const volatile&&>();
    test_is_not_array<float Class::*const volatile&&>();
    test_is_not_array<void * Class::*const volatile&&>();
    test_is_not_array<NonCopyable>();
    test_is_not_array<NonMoveable>();
    test_is_not_array<NonConstructible>();
    test_is_not_array<Tracked>();
    test_is_not_array<TrapConstructible>();
    test_is_not_array<TrapImplicitConversion>();
    test_is_not_array<TrapComma>();
    test_is_not_array<TrapCall>();
    test_is_not_array<TrapSelfAssign>();
    test_is_not_array<TrapDeref>();
    test_is_not_array<TrapArraySubscript>();

    test_is_not_array<void()>();
    test_is_not_array<void()&>();
    test_is_not_array<void() &&>();
    test_is_not_array<void() const>();
    test_is_not_array<void() const&>();
    test_is_not_array<void() const&&>();
    test_is_not_array<void() volatile>();
    test_is_not_array<void() volatile&>();
    test_is_not_array<void() volatile&&>();
    test_is_not_array<void() const volatile>();
    test_is_not_array<void() const volatile&>();
    test_is_not_array<void() const volatile&&>();
    test_is_not_array<void() noexcept>();
    test_is_not_array<void()& noexcept>();
    test_is_not_array<void()&& noexcept>();
    test_is_not_array<void() const noexcept>();
    test_is_not_array<void() const& noexcept>();
    test_is_not_array<void() const&& noexcept>();
    test_is_not_array<void() volatile noexcept>();
    test_is_not_array<void() volatile& noexcept>();
    test_is_not_array<void() volatile&& noexcept>();
    test_is_not_array<void() const volatile noexcept>();
    test_is_not_array<void() const volatile& noexcept>();
    test_is_not_array<void() const volatile&& noexcept>();

    test_is_not_array<void(int)>();
    test_is_not_array<void(int)&>();
    test_is_not_array<void(int) &&>();
    test_is_not_array<void(int) const>();
    test_is_not_array<void(int) const&>();
    test_is_not_array<void(int) const&&>();
    test_is_not_array<void(int) volatile>();
    test_is_not_array<void(int) volatile&>();
    test_is_not_array<void(int) volatile&&>();
    test_is_not_array<void(int) const volatile>();
    test_is_not_array<void(int) const volatile&>();
    test_is_not_array<void(int) const volatile&&>();
    test_is_not_array<void(int) noexcept>();
    test_is_not_array<void(int)& noexcept>();
    test_is_not_array<void(int)&& noexcept>();
    test_is_not_array<void(int) const noexcept>();
    test_is_not_array<void(int) const& noexcept>();
    test_is_not_array<void(int) const&& noexcept>();
    test_is_not_array<void(int) volatile noexcept>();
    test_is_not_array<void(int) volatile& noexcept>();
    test_is_not_array<void(int) volatile&& noexcept>();
    test_is_not_array<void(int) const volatile noexcept>();
    test_is_not_array<void(int) const volatile& noexcept>();
    test_is_not_array<void(int) const volatile&& noexcept>();

    test_is_not_array<void(...)>();
    test_is_not_array<void(...)&>();
    test_is_not_array<void(...) &&>();
    test_is_not_array<void(...) const>();
    test_is_not_array<void(...) const&>();
    test_is_not_array<void(...) const&&>();
    test_is_not_array<void(...) volatile>();
    test_is_not_array<void(...) volatile&>();
    test_is_not_array<void(...) volatile&&>();
    test_is_not_array<void(...) const volatile>();
    test_is_not_array<void(...) const volatile&>();
    test_is_not_array<void(...) const volatile&&>();
    test_is_not_array<void(...) noexcept>();
    test_is_not_array<void(...)& noexcept>();
    test_is_not_array<void(...)&& noexcept>();
    test_is_not_array<void(...) const noexcept>();
    test_is_not_array<void(...) const& noexcept>();
    test_is_not_array<void(...) const&& noexcept>();
    test_is_not_array<void(...) volatile noexcept>();
    test_is_not_array<void(...) volatile& noexcept>();
    test_is_not_array<void(...) volatile&& noexcept>();
    test_is_not_array<void(...) const volatile noexcept>();
    test_is_not_array<void(...) const volatile& noexcept>();
    test_is_not_array<void(...) const volatile&& noexcept>();

    test_is_not_array<void(int, ...)>();
    test_is_not_array<void(int, ...)&>();
    test_is_not_array<void(int, ...) &&>();
    test_is_not_array<void(int, ...) const>();
    test_is_not_array<void(int, ...) const&>();
    test_is_not_array<void(int, ...) const&&>();
    test_is_not_array<void(int, ...) volatile>();
    test_is_not_array<void(int, ...) volatile&>();
    test_is_not_array<void(int, ...) volatile&&>();
    test_is_not_array<void(int, ...) const volatile>();
    test_is_not_array<void(int, ...) const volatile&>();
    test_is_not_array<void(int, ...) const volatile&&>();
    test_is_not_array<void(int, ...) noexcept>();
    test_is_not_array<void(int, ...)& noexcept>();
    test_is_not_array<void(int, ...)&& noexcept>();
    test_is_not_array<void(int, ...) const noexcept>();
    test_is_not_array<void(int, ...) const& noexcept>();
    test_is_not_array<void(int, ...) const&& noexcept>();
    test_is_not_array<void(int, ...) volatile noexcept>();
    test_is_not_array<void(int, ...) volatile& noexcept>();
    test_is_not_array<void(int, ...) volatile&& noexcept>();
    test_is_not_array<void(int, ...) const volatile noexcept>();
    test_is_not_array<void(int, ...) const volatile& noexcept>();
    test_is_not_array<void(int, ...) const volatile&& noexcept>();

    test_is_not_array<int()>();
    test_is_not_array<int()&>();
    test_is_not_array<int() &&>();
    test_is_not_array<int() const>();
    test_is_not_array<int() const&>();
    test_is_not_array<int() const&&>();
    test_is_not_array<int() volatile>();
    test_is_not_array<int() volatile&>();
    test_is_not_array<int() volatile&&>();
    test_is_not_array<int() const volatile>();
    test_is_not_array<int() const volatile&>();
    test_is_not_array<int() const volatile&&>();
    test_is_not_array<int() noexcept>();
    test_is_not_array<int()& noexcept>();
    test_is_not_array<int()&& noexcept>();
    test_is_not_array<int() const noexcept>();
    test_is_not_array<int() const& noexcept>();
    test_is_not_array<int() const&& noexcept>();
    test_is_not_array<int() volatile noexcept>();
    test_is_not_array<int() volatile& noexcept>();
    test_is_not_array<int() volatile&& noexcept>();
    test_is_not_array<int() const volatile noexcept>();
    test_is_not_array<int() const volatile& noexcept>();
    test_is_not_array<int() const volatile&& noexcept>();

    test_is_not_array<int(int)>();
    test_is_not_array<int(int)&>();
    test_is_not_array<int(int) &&>();
    test_is_not_array<int(int) const>();
    test_is_not_array<int(int) const&>();
    test_is_not_array<int(int) const&&>();
    test_is_not_array<int(int) volatile>();
    test_is_not_array<int(int) volatile&>();
    test_is_not_array<int(int) volatile&&>();
    test_is_not_array<int(int) const volatile>();
    test_is_not_array<int(int) const volatile&>();
    test_is_not_array<int(int) const volatile&&>();
    test_is_not_array<int(int) noexcept>();
    test_is_not_array<int(int)& noexcept>();
    test_is_not_array<int(int)&& noexcept>();
    test_is_not_array<int(int) const noexcept>();
    test_is_not_array<int(int) const& noexcept>();
    test_is_not_array<int(int) const&& noexcept>();
    test_is_not_array<int(int) volatile noexcept>();
    test_is_not_array<int(int) volatile& noexcept>();
    test_is_not_array<int(int) volatile&& noexcept>();
    test_is_not_array<int(int) const volatile noexcept>();
    test_is_not_array<int(int) const volatile& noexcept>();
    test_is_not_array<int(int) const volatile&& noexcept>();

    test_is_not_array<int(...)>();
    test_is_not_array<int(...)&>();
    test_is_not_array<int(...) &&>();
    test_is_not_array<int(...) const>();
    test_is_not_array<int(...) const&>();
    test_is_not_array<int(...) const&&>();
    test_is_not_array<int(...) volatile>();
    test_is_not_array<int(...) volatile&>();
    test_is_not_array<int(...) volatile&&>();
    test_is_not_array<int(...) const volatile>();
    test_is_not_array<int(...) const volatile&>();
    test_is_not_array<int(...) const volatile&&>();
    test_is_not_array<int(...) noexcept>();
    test_is_not_array<int(...)& noexcept>();
    test_is_not_array<int(...)&& noexcept>();
    test_is_not_array<int(...) const noexcept>();
    test_is_not_array<int(...) const& noexcept>();
    test_is_not_array<int(...) const&& noexcept>();
    test_is_not_array<int(...) volatile noexcept>();
    test_is_not_array<int(...) volatile& noexcept>();
    test_is_not_array<int(...) volatile&& noexcept>();
    test_is_not_array<int(...) const volatile noexcept>();
    test_is_not_array<int(...) const volatile& noexcept>();
    test_is_not_array<int(...) const volatile&& noexcept>();

    test_is_not_array<int(int, ...)>();
    test_is_not_array<int(int, ...)&>();
    test_is_not_array<int(int, ...) &&>();
    test_is_not_array<int(int, ...) const>();
    test_is_not_array<int(int, ...) const&>();
    test_is_not_array<int(int, ...) const&&>();
    test_is_not_array<int(int, ...) volatile>();
    test_is_not_array<int(int, ...) volatile&>();
    test_is_not_array<int(int, ...) volatile&&>();
    test_is_not_array<int(int, ...) const volatile>();
    test_is_not_array<int(int, ...) const volatile&>();
    test_is_not_array<int(int, ...) const volatile&&>();
    test_is_not_array<int(int, ...) noexcept>();
    test_is_not_array<int(int, ...)& noexcept>();
    test_is_not_array<int(int, ...)&& noexcept>();
    test_is_not_array<int(int, ...) const noexcept>();
    test_is_not_array<int(int, ...) const& noexcept>();
    test_is_not_array<int(int, ...) const&& noexcept>();
    test_is_not_array<int(int, ...) volatile noexcept>();
    test_is_not_array<int(int, ...) volatile& noexcept>();
    test_is_not_array<int(int, ...) volatile&& noexcept>();
    test_is_not_array<int(int, ...) const volatile noexcept>();
    test_is_not_array<int(int, ...) const volatile& noexcept>();
    test_is_not_array<int(int, ...) const volatile&& noexcept>();

    test_is_not_array<void (*)()>();
    test_is_not_array<void (*)() noexcept>();

    test_is_not_array<void (*)(int)>();
    test_is_not_array<void (*)(int) noexcept>();

    test_is_not_array<void (*)(...)>();
    test_is_not_array<void (*)(...) noexcept>();

    test_is_not_array<void (*)(int, ...)>();
    test_is_not_array<void (*)(int, ...) noexcept>();

    test_is_not_array<int (*)()>();
    test_is_not_array<int (*)() noexcept>();

    test_is_not_array<int (*)(int)>();
    test_is_not_array<int (*)(int) noexcept>();

    test_is_not_array<int (*)(...)>();
    test_is_not_array<int (*)(...) noexcept>();

    test_is_not_array<int (*)(int, ...)>();
    test_is_not_array<int (*)(int, ...) noexcept>();

    test_is_not_array<void (&)()>();
    test_is_not_array<void (&)() noexcept>();

    test_is_not_array<void (&)(int)>();
    test_is_not_array<void (&)(int) noexcept>();

    test_is_not_array<void (&)(...)>();
    test_is_not_array<void (&)(...) noexcept>();

    test_is_not_array<void (&)(int, ...)>();
    test_is_not_array<void (&)(int, ...) noexcept>();

    test_is_not_array<int (&)()>();
    test_is_not_array<int (&)() noexcept>();

    test_is_not_array<int (&)(int)>();
    test_is_not_array<int (&)(int) noexcept>();

    test_is_not_array<int (&)(...)>();
    test_is_not_array<int (&)(...) noexcept>();

    test_is_not_array<int (&)(int, ...)>();
    test_is_not_array<int (&)(int, ...) noexcept>();

    test_is_not_array<void(&&)()>();
    test_is_not_array<void(&&)() noexcept>();

    test_is_not_array<void(&&)(int)>();
    test_is_not_array<void(&&)(int) noexcept>();

    test_is_not_array<void(&&)(...)>();
    test_is_not_array<void(&&)(...) noexcept>();

    test_is_not_array<void(&&)(int, ...)>();
    test_is_not_array<void(&&)(int, ...) noexcept>();

    test_is_not_array<int(&&)()>();
    test_is_not_array<int(&&)() noexcept>();

    test_is_not_array<int(&&)(int)>();
    test_is_not_array<int(&&)(int) noexcept>();

    test_is_not_array<int(&&)(...)>();
    test_is_not_array<int(&&)(...) noexcept>();

    test_is_not_array<int(&&)(int, ...)>();
    test_is_not_array<int(&&)(int, ...) noexcept>();

    test_is_not_array<void (Class::*)()>();
    test_is_not_array<void (Class::*)()&>();
    test_is_not_array<void (Class::*)() &&>();
    test_is_not_array<void (Class::*)() const>();
    test_is_not_array<void (Class::*)() const&>();
    test_is_not_array<void (Class::*)() const&&>();
    test_is_not_array<void (Class::*)() noexcept>();
    test_is_not_array<void (Class::*)()& noexcept>();
    test_is_not_array<void (Class::*)()&& noexcept>();
    test_is_not_array<void (Class::*)() const noexcept>();
    test_is_not_array<void (Class::*)() const& noexcept>();
    test_is_not_array<void (Class::*)() const&& noexcept>();

    test_is_not_array<void (Class::*)(int)>();
    test_is_not_array<void (Class::*)(int)&>();
    test_is_not_array<void (Class::*)(int) &&>();
    test_is_not_array<void (Class::*)(int) const>();
    test_is_not_array<void (Class::*)(int) const&>();
    test_is_not_array<void (Class::*)(int) const&&>();
    test_is_not_array<void (Class::*)(int) noexcept>();
    test_is_not_array<void (Class::*)(int)& noexcept>();
    test_is_not_array<void (Class::*)(int)&& noexcept>();
    test_is_not_array<void (Class::*)(int) const noexcept>();
    test_is_not_array<void (Class::*)(int) const& noexcept>();
    test_is_not_array<void (Class::*)(int) const&& noexcept>();

    test_is_not_array<void (Class::*)(...)>();
    test_is_not_array<void (Class::*)(...)&>();
    test_is_not_array<void (Class::*)(...) &&>();
    test_is_not_array<void (Class::*)(...) const>();
    test_is_not_array<void (Class::*)(...) const&>();
    test_is_not_array<void (Class::*)(...) const&&>();
    test_is_not_array<void (Class::*)(...) noexcept>();
    test_is_not_array<void (Class::*)(...)& noexcept>();
    test_is_not_array<void (Class::*)(...)&& noexcept>();
    test_is_not_array<void (Class::*)(...) const noexcept>();
    test_is_not_array<void (Class::*)(...) const& noexcept>();
    test_is_not_array<void (Class::*)(...) const&& noexcept>();

    test_is_not_array<void (Class::*)(int, ...)>();
    test_is_not_array<void (Class::*)(int, ...)&>();
    test_is_not_array<void (Class::*)(int, ...) &&>();
    test_is_not_array<void (Class::*)(int, ...) const>();
    test_is_not_array<void (Class::*)(int, ...) const&>();
    test_is_not_array<void (Class::*)(int, ...) const&&>();
    test_is_not_array<void (Class::*)(int, ...) noexcept>();
    test_is_not_array<void (Class::*)(int, ...)& noexcept>();
    test_is_not_array<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_array<void (Class::*)(int, ...) const noexcept>();
    test_is_not_array<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_array<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_array<int (Class::*)()>();
    test_is_not_array<int (Class::*)()&>();
    test_is_not_array<int (Class::*)() &&>();
    test_is_not_array<int (Class::*)() const>();
    test_is_not_array<int (Class::*)() const&>();
    test_is_not_array<int (Class::*)() const&&>();
    test_is_not_array<int (Class::*)() noexcept>();
    test_is_not_array<int (Class::*)()& noexcept>();
    test_is_not_array<int (Class::*)()&& noexcept>();
    test_is_not_array<int (Class::*)() const noexcept>();
    test_is_not_array<int (Class::*)() const& noexcept>();
    test_is_not_array<int (Class::*)() const&& noexcept>();

    test_is_not_array<int (Class::*)(int)>();
    test_is_not_array<int (Class::*)(int)&>();
    test_is_not_array<int (Class::*)(int) &&>();
    test_is_not_array<int (Class::*)(int) const>();
    test_is_not_array<int (Class::*)(int) const&>();
    test_is_not_array<int (Class::*)(int) const&&>();
    test_is_not_array<int (Class::*)(int) noexcept>();
    test_is_not_array<int (Class::*)(int)& noexcept>();
    test_is_not_array<int (Class::*)(int)&& noexcept>();
    test_is_not_array<int (Class::*)(int) const noexcept>();
    test_is_not_array<int (Class::*)(int) const& noexcept>();
    test_is_not_array<int (Class::*)(int) const&& noexcept>();

    test_is_not_array<int (Class::*)(...)>();
    test_is_not_array<int (Class::*)(...)&>();
    test_is_not_array<int (Class::*)(...) &&>();
    test_is_not_array<int (Class::*)(...) const>();
    test_is_not_array<int (Class::*)(...) const&>();
    test_is_not_array<int (Class::*)(...) const&&>();
    test_is_not_array<int (Class::*)(...) noexcept>();
    test_is_not_array<int (Class::*)(...)& noexcept>();
    test_is_not_array<int (Class::*)(...)&& noexcept>();
    test_is_not_array<int (Class::*)(...) const noexcept>();
    test_is_not_array<int (Class::*)(...) const& noexcept>();
    test_is_not_array<int (Class::*)(...) const&& noexcept>();

    test_is_not_array<int (Class::*)(int, ...)>();
    test_is_not_array<int (Class::*)(int, ...)&>();
    test_is_not_array<int (Class::*)(int, ...) &&>();
    test_is_not_array<int (Class::*)(int, ...) const>();
    test_is_not_array<int (Class::*)(int, ...) const&>();
    test_is_not_array<int (Class::*)(int, ...) const&&>();
    test_is_not_array<int (Class::*)(int, ...) noexcept>();
    test_is_not_array<int (Class::*)(int, ...)& noexcept>();
    test_is_not_array<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_array<int (Class::*)(int, ...) const noexcept>();
    test_is_not_array<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_array<int (Class::*)(int, ...) const&& noexcept>();
}
