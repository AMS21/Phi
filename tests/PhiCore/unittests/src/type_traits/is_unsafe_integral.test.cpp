#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_arithmetic.hpp>
#include <phi/type_traits/is_array.hpp>
#include <phi/type_traits/is_bool.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_compound.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_fundamental.hpp>
#include <phi/type_traits/is_integer.hpp>
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
#include <phi/type_traits/is_unsafe_floating_point.hpp>
#include <phi/type_traits/is_unsafe_integral.hpp>
#include <phi/type_traits/is_unsafe_scalar.hpp>
#include <phi/type_traits/is_void.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_unsafe_integral_impl()
{
    STATIC_REQUIRE(phi::is_unsafe_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_compound<T>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
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
#if PHI_HAS_WORKING_IS_UNSAFE_SCALAR()
    STATIC_REQUIRE(phi::is_unsafe_scalar<T>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

    STATIC_REQUIRE(phi::is_unsafe_integral<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_integral<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_compound_v<T>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
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
#    if PHI_HAS_WORKING_IS_UNSAFE_SCALAR()
    STATIC_REQUIRE(phi::is_unsafe_scalar_v<T>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);

    STATIC_REQUIRE(phi::is_unsafe_integral_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_integral_v<T>);
#endif

    // Standard compatibility
    STATIC_REQUIRE(std::is_integral<T>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_integral_v<T>);
#endif
}

template <typename T>
void test_is_unsafe_integral()
{
    test_is_unsafe_integral_impl<T>();
    test_is_unsafe_integral_impl<const T>();
    test_is_unsafe_integral_impl<volatile T>();
    test_is_unsafe_integral_impl<const volatile T>();
}

template <typename T>
void test_is_not_unsafe_integral_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integral<T>::value);
    STATIC_REQUIRE(phi::is_not_unsafe_integral<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integral_v<T>);
    STATIC_REQUIRE(phi::is_not_unsafe_integral_v<T>);
#endif

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_integral<T>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_integral_v<T>);
#endif
}

template <typename T>
void test_is_not_unsafe_integral()
{
    test_is_not_unsafe_integral_impl<T>();
    test_is_not_unsafe_integral_impl<const T>();
    test_is_not_unsafe_integral_impl<volatile T>();
    test_is_not_unsafe_integral_impl<const volatile T>();
}

TEST_CASE("is_unsafe_integral")
{
    test_is_not_unsafe_integral<void>();
    test_is_not_unsafe_integral<phi::nullptr_t>();
    test_is_unsafe_integral<bool>();
    test_is_unsafe_integral<char>();
    test_is_unsafe_integral<signed char>();
    test_is_unsafe_integral<unsigned char>();
    test_is_unsafe_integral<short>();
    test_is_unsafe_integral<unsigned short>();
    test_is_unsafe_integral<int>();
    test_is_unsafe_integral<unsigned int>();
    test_is_unsafe_integral<long>();
    test_is_unsafe_integral<unsigned long>();
    test_is_unsafe_integral<long long>();
    test_is_unsafe_integral<unsigned long long>();
    test_is_not_unsafe_integral<float>();
    test_is_not_unsafe_integral<double>();
    test_is_not_unsafe_integral<long double>();
    test_is_unsafe_integral<char8_t>();
    test_is_unsafe_integral<char16_t>();
    test_is_unsafe_integral<char32_t>();
    test_is_unsafe_integral<wchar_t>();

    test_is_not_unsafe_integral<phi::boolean>();
    test_is_not_unsafe_integral<phi::integer<signed char>>();
    test_is_not_unsafe_integral<phi::integer<unsigned char>>();
    test_is_not_unsafe_integral<phi::integer<short>>();
    test_is_not_unsafe_integral<phi::integer<unsigned short>>();
    test_is_not_unsafe_integral<phi::integer<int>>();
    test_is_not_unsafe_integral<phi::integer<unsigned int>>();
    test_is_not_unsafe_integral<phi::integer<long>>();
    test_is_not_unsafe_integral<phi::integer<unsigned long>>();
    test_is_not_unsafe_integral<phi::integer<long long>>();
    test_is_not_unsafe_integral<phi::integer<unsigned long long>>();
    test_is_not_unsafe_integral<phi::floating_point<float>>();
    test_is_not_unsafe_integral<phi::floating_point<double>>();
    test_is_not_unsafe_integral<phi::floating_point<long double>>();

    test_is_not_unsafe_integral<std::vector<int>>();
    test_is_not_unsafe_integral<phi::scope_ptr<int>>();

    test_is_not_unsafe_integral<int&>();
    test_is_not_unsafe_integral<const int&>();
    test_is_not_unsafe_integral<volatile int&>();
    test_is_not_unsafe_integral<const volatile int&>();
    test_is_not_unsafe_integral<int&&>();
    test_is_not_unsafe_integral<const int&&>();
    test_is_not_unsafe_integral<volatile int&&>();
    test_is_not_unsafe_integral<const volatile int&&>();
    test_is_not_unsafe_integral<int*>();
    test_is_not_unsafe_integral<const int*>();
    test_is_not_unsafe_integral<volatile int*>();
    test_is_not_unsafe_integral<const volatile int*>();
    test_is_not_unsafe_integral<int**>();
    test_is_not_unsafe_integral<const int**>();
    test_is_not_unsafe_integral<volatile int**>();
    test_is_not_unsafe_integral<const volatile int**>();
    test_is_not_unsafe_integral<int*&>();
    test_is_not_unsafe_integral<const int*&>();
    test_is_not_unsafe_integral<volatile int*&>();
    test_is_not_unsafe_integral<const volatile int*&>();
    test_is_not_unsafe_integral<int*&&>();
    test_is_not_unsafe_integral<const int*&&>();
    test_is_not_unsafe_integral<volatile int*&&>();
    test_is_not_unsafe_integral<const volatile int*&&>();
    test_is_not_unsafe_integral<void*>();
    test_is_not_unsafe_integral<char[3]>();
    test_is_not_unsafe_integral<char[]>();
    test_is_not_unsafe_integral<char* [3]>();
    test_is_not_unsafe_integral<char*[]>();
    test_is_not_unsafe_integral<int(*)[3]>();
    test_is_not_unsafe_integral<int(*)[]>();
    test_is_not_unsafe_integral<int(&)[3]>();
    test_is_not_unsafe_integral<int(&)[]>();
    test_is_not_unsafe_integral<int(&&)[3]>();
    test_is_not_unsafe_integral<int(&&)[]>();
    test_is_not_unsafe_integral<char[3][2]>();
    test_is_not_unsafe_integral<char[][2]>();
    test_is_not_unsafe_integral<char* [3][2]>();
    test_is_not_unsafe_integral<char*[][2]>();
    test_is_not_unsafe_integral<int(*)[3][2]>();
    test_is_not_unsafe_integral<int(*)[][2]>();
    test_is_not_unsafe_integral<int(&)[3][2]>();
    test_is_not_unsafe_integral<int(&)[][2]>();
    test_is_not_unsafe_integral<int(&&)[3][2]>();
    test_is_not_unsafe_integral<int(&&)[][2]>();
    test_is_not_unsafe_integral<Class>();
    test_is_not_unsafe_integral<Class[]>();
    test_is_not_unsafe_integral<Class[2]>();
    test_is_not_unsafe_integral<Template<void>>();
    test_is_not_unsafe_integral<Template<int>>();
    test_is_not_unsafe_integral<Template<Class>>();
    test_is_not_unsafe_integral<Template<IncompleteType>>();
    test_is_not_unsafe_integral<VariadicTemplate<>>();
    test_is_not_unsafe_integral<VariadicTemplate<void>>();
    test_is_not_unsafe_integral<VariadicTemplate<int>>();
    test_is_not_unsafe_integral<VariadicTemplate<Class>>();
    test_is_not_unsafe_integral<VariadicTemplate<IncompleteType>>();
    test_is_not_unsafe_integral<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_integral<PublicDerivedFromTemplate<Base>>();
    test_is_not_unsafe_integral<PublicDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_integral<PublicDerivedFromTemplate<Class>>();
    test_is_not_unsafe_integral<PrivateDerivedFromTemplate<Base>>();
    test_is_not_unsafe_integral<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_integral<PrivateDerivedFromTemplate<Class>>();
    test_is_not_unsafe_integral<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_unsafe_integral<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_integral<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_unsafe_integral<Union>();
    test_is_not_unsafe_integral<NonEmptyUnion>();
    test_is_not_unsafe_integral<Empty>();
    test_is_not_unsafe_integral<NotEmpty>();
    test_is_not_unsafe_integral<BitZero>();
    test_is_not_unsafe_integral<BitOne>();
    test_is_not_unsafe_integral<Base>();
    test_is_not_unsafe_integral<Derived>();
    test_is_not_unsafe_integral<Abstract>();
    test_is_not_unsafe_integral<PublicAbstract>();
    test_is_not_unsafe_integral<PrivateAbstract>();
    test_is_not_unsafe_integral<ProtectedAbstract>();
    test_is_not_unsafe_integral<AbstractTemplate<int>>();
    test_is_not_unsafe_integral<AbstractTemplate<double>>();
    test_is_not_unsafe_integral<AbstractTemplate<Class>>();
    test_is_not_unsafe_integral<AbstractTemplate<IncompleteType>>();
    test_is_not_unsafe_integral<Final>();
    test_is_not_unsafe_integral<PublicDestructor>();
    test_is_not_unsafe_integral<ProtectedDestructor>();
    test_is_not_unsafe_integral<PrivateDestructor>();
    test_is_not_unsafe_integral<VirtualPublicDestructor>();
    test_is_not_unsafe_integral<VirtualProtectedDestructor>();
    test_is_not_unsafe_integral<VirtualPrivateDestructor>();
    test_is_not_unsafe_integral<PurePublicDestructor>();
    test_is_not_unsafe_integral<PureProtectedDestructor>();
    test_is_not_unsafe_integral<PurePrivateDestructor>();
    test_is_not_unsafe_integral<DeletedPublicDestructor>();
    test_is_not_unsafe_integral<DeletedProtectedDestructor>();
    test_is_not_unsafe_integral<DeletedPrivateDestructor>();
    test_is_not_unsafe_integral<DeletedVirtualPublicDestructor>();
    test_is_not_unsafe_integral<DeletedVirtualProtectedDestructor>();
    test_is_not_unsafe_integral<DeletedVirtualPrivateDestructor>();
    test_is_not_unsafe_integral<Final>();
    test_is_not_unsafe_integral<Enum>();
    test_is_not_unsafe_integral<EnumSigned>();
    test_is_not_unsafe_integral<EnumUnsigned>();
    test_is_not_unsafe_integral<EnumClass>();
    test_is_not_unsafe_integral<EnumStruct>();
    test_is_not_unsafe_integral<Function>();
    test_is_not_unsafe_integral<FunctionPtr>();
    test_is_not_unsafe_integral<MemberObjectPtr>();
    test_is_not_unsafe_integral<MemberFunctionPtr>();
    test_is_not_unsafe_integral<IncompleteType>();
    test_is_not_unsafe_integral<IncompleteTemplate<void>>();
    test_is_not_unsafe_integral<IncompleteTemplate<int>>();
    test_is_not_unsafe_integral<IncompleteTemplate<Class>>();
    test_is_not_unsafe_integral<IncompleteTemplate<IncompleteType>>();
    test_is_not_unsafe_integral<IncompleteVariadicTemplate<>>();
    test_is_not_unsafe_integral<IncompleteVariadicTemplate<void>>();
    test_is_not_unsafe_integral<IncompleteVariadicTemplate<int>>();
    test_is_not_unsafe_integral<IncompleteVariadicTemplate<Class>>();
    test_is_not_unsafe_integral<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_unsafe_integral<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_integral<int Class::*>();
    test_is_not_unsafe_integral<float Class::*>();
    test_is_not_unsafe_integral<void * Class::*>();
    test_is_not_unsafe_integral<int * Class::*>();
    test_is_not_unsafe_integral<int Class::*&>();
    test_is_not_unsafe_integral<float Class::*&>();
    test_is_not_unsafe_integral<void * Class::*&>();
    test_is_not_unsafe_integral<int * Class::*&>();
    test_is_not_unsafe_integral<int Class::*&&>();
    test_is_not_unsafe_integral<float Class::*&&>();
    test_is_not_unsafe_integral<void * Class::*&&>();
    test_is_not_unsafe_integral<int * Class::*&&>();
    test_is_not_unsafe_integral<int Class::*const>();
    test_is_not_unsafe_integral<float Class::*const>();
    test_is_not_unsafe_integral<void * Class::*const>();
    test_is_not_unsafe_integral<int Class::*const&>();
    test_is_not_unsafe_integral<float Class::*const&>();
    test_is_not_unsafe_integral<void * Class::*const&>();
    test_is_not_unsafe_integral<int Class::*const&&>();
    test_is_not_unsafe_integral<float Class::*const&&>();
    test_is_not_unsafe_integral<void * Class::*const&&>();
    test_is_not_unsafe_integral<int Class::*volatile>();
    test_is_not_unsafe_integral<float Class::*volatile>();
    test_is_not_unsafe_integral<void * Class::*volatile>();
    test_is_not_unsafe_integral<int Class::*volatile&>();
    test_is_not_unsafe_integral<float Class::*volatile&>();
    test_is_not_unsafe_integral<void * Class::*volatile&>();
    test_is_not_unsafe_integral<int Class::*volatile&&>();
    test_is_not_unsafe_integral<float Class::*volatile&&>();
    test_is_not_unsafe_integral<void * Class::*volatile&&>();
    test_is_not_unsafe_integral<int Class::*const volatile>();
    test_is_not_unsafe_integral<float Class::*const volatile>();
    test_is_not_unsafe_integral<void * Class::*const volatile>();
    test_is_not_unsafe_integral<int Class::*const volatile&>();
    test_is_not_unsafe_integral<float Class::*const volatile&>();
    test_is_not_unsafe_integral<void * Class::*const volatile&>();
    test_is_not_unsafe_integral<int Class::*const volatile&&>();
    test_is_not_unsafe_integral<float Class::*const volatile&&>();
    test_is_not_unsafe_integral<void * Class::*const volatile&&>();
    test_is_not_unsafe_integral<NonCopyable>();
    test_is_not_unsafe_integral<NonMoveable>();
    test_is_not_unsafe_integral<NonConstructible>();
    test_is_not_unsafe_integral<Tracked>();
    test_is_not_unsafe_integral<TrapConstructible>();
    test_is_not_unsafe_integral<TrapImplicitConversion>();
    test_is_not_unsafe_integral<TrapComma>();
    test_is_not_unsafe_integral<TrapCall>();
    test_is_not_unsafe_integral<TrapSelfAssign>();
    test_is_not_unsafe_integral<TrapDeref>();
    test_is_not_unsafe_integral<TrapArraySubscript>();

    test_is_not_unsafe_integral<void()>();
    test_is_not_unsafe_integral<void()&>();
    test_is_not_unsafe_integral<void() &&>();
    test_is_not_unsafe_integral<void() const>();
    test_is_not_unsafe_integral<void() const&>();
    test_is_not_unsafe_integral<void() const&&>();
    test_is_not_unsafe_integral<void() volatile>();
    test_is_not_unsafe_integral<void() volatile&>();
    test_is_not_unsafe_integral<void() volatile&&>();
    test_is_not_unsafe_integral<void() const volatile>();
    test_is_not_unsafe_integral<void() const volatile&>();
    test_is_not_unsafe_integral<void() const volatile&&>();
    test_is_not_unsafe_integral<void() noexcept>();
    test_is_not_unsafe_integral<void()& noexcept>();
    test_is_not_unsafe_integral<void()&& noexcept>();
    test_is_not_unsafe_integral<void() const noexcept>();
    test_is_not_unsafe_integral<void() const& noexcept>();
    test_is_not_unsafe_integral<void() const&& noexcept>();
    test_is_not_unsafe_integral<void() volatile noexcept>();
    test_is_not_unsafe_integral<void() volatile& noexcept>();
    test_is_not_unsafe_integral<void() volatile&& noexcept>();
    test_is_not_unsafe_integral<void() const volatile noexcept>();
    test_is_not_unsafe_integral<void() const volatile& noexcept>();
    test_is_not_unsafe_integral<void() const volatile&& noexcept>();

    test_is_not_unsafe_integral<void(int)>();
    test_is_not_unsafe_integral<void(int)&>();
    test_is_not_unsafe_integral<void(int) &&>();
    test_is_not_unsafe_integral<void(int) const>();
    test_is_not_unsafe_integral<void(int) const&>();
    test_is_not_unsafe_integral<void(int) const&&>();
    test_is_not_unsafe_integral<void(int) volatile>();
    test_is_not_unsafe_integral<void(int) volatile&>();
    test_is_not_unsafe_integral<void(int) volatile&&>();
    test_is_not_unsafe_integral<void(int) const volatile>();
    test_is_not_unsafe_integral<void(int) const volatile&>();
    test_is_not_unsafe_integral<void(int) const volatile&&>();
    test_is_not_unsafe_integral<void(int) noexcept>();
    test_is_not_unsafe_integral<void(int)& noexcept>();
    test_is_not_unsafe_integral<void(int)&& noexcept>();
    test_is_not_unsafe_integral<void(int) const noexcept>();
    test_is_not_unsafe_integral<void(int) const& noexcept>();
    test_is_not_unsafe_integral<void(int) const&& noexcept>();
    test_is_not_unsafe_integral<void(int) volatile noexcept>();
    test_is_not_unsafe_integral<void(int) volatile& noexcept>();
    test_is_not_unsafe_integral<void(int) volatile&& noexcept>();
    test_is_not_unsafe_integral<void(int) const volatile noexcept>();
    test_is_not_unsafe_integral<void(int) const volatile& noexcept>();
    test_is_not_unsafe_integral<void(int) const volatile&& noexcept>();

    test_is_not_unsafe_integral<void(...)>();
    test_is_not_unsafe_integral<void(...)&>();
    test_is_not_unsafe_integral<void(...) &&>();
    test_is_not_unsafe_integral<void(...) const>();
    test_is_not_unsafe_integral<void(...) const&>();
    test_is_not_unsafe_integral<void(...) const&&>();
    test_is_not_unsafe_integral<void(...) volatile>();
    test_is_not_unsafe_integral<void(...) volatile&>();
    test_is_not_unsafe_integral<void(...) volatile&&>();
    test_is_not_unsafe_integral<void(...) const volatile>();
    test_is_not_unsafe_integral<void(...) const volatile&>();
    test_is_not_unsafe_integral<void(...) const volatile&&>();
    test_is_not_unsafe_integral<void(...) noexcept>();
    test_is_not_unsafe_integral<void(...)& noexcept>();
    test_is_not_unsafe_integral<void(...)&& noexcept>();
    test_is_not_unsafe_integral<void(...) const noexcept>();
    test_is_not_unsafe_integral<void(...) const& noexcept>();
    test_is_not_unsafe_integral<void(...) const&& noexcept>();
    test_is_not_unsafe_integral<void(...) volatile noexcept>();
    test_is_not_unsafe_integral<void(...) volatile& noexcept>();
    test_is_not_unsafe_integral<void(...) volatile&& noexcept>();
    test_is_not_unsafe_integral<void(...) const volatile noexcept>();
    test_is_not_unsafe_integral<void(...) const volatile& noexcept>();
    test_is_not_unsafe_integral<void(...) const volatile&& noexcept>();

    test_is_not_unsafe_integral<void(int, ...)>();
    test_is_not_unsafe_integral<void(int, ...)&>();
    test_is_not_unsafe_integral<void(int, ...) &&>();
    test_is_not_unsafe_integral<void(int, ...) const>();
    test_is_not_unsafe_integral<void(int, ...) const&>();
    test_is_not_unsafe_integral<void(int, ...) const&&>();
    test_is_not_unsafe_integral<void(int, ...) volatile>();
    test_is_not_unsafe_integral<void(int, ...) volatile&>();
    test_is_not_unsafe_integral<void(int, ...) volatile&&>();
    test_is_not_unsafe_integral<void(int, ...) const volatile>();
    test_is_not_unsafe_integral<void(int, ...) const volatile&>();
    test_is_not_unsafe_integral<void(int, ...) const volatile&&>();
    test_is_not_unsafe_integral<void(int, ...) noexcept>();
    test_is_not_unsafe_integral<void(int, ...)& noexcept>();
    test_is_not_unsafe_integral<void(int, ...)&& noexcept>();
    test_is_not_unsafe_integral<void(int, ...) const noexcept>();
    test_is_not_unsafe_integral<void(int, ...) const& noexcept>();
    test_is_not_unsafe_integral<void(int, ...) const&& noexcept>();
    test_is_not_unsafe_integral<void(int, ...) volatile noexcept>();
    test_is_not_unsafe_integral<void(int, ...) volatile& noexcept>();
    test_is_not_unsafe_integral<void(int, ...) volatile&& noexcept>();
    test_is_not_unsafe_integral<void(int, ...) const volatile noexcept>();
    test_is_not_unsafe_integral<void(int, ...) const volatile& noexcept>();
    test_is_not_unsafe_integral<void(int, ...) const volatile&& noexcept>();

    test_is_not_unsafe_integral<int()>();
    test_is_not_unsafe_integral<int()&>();
    test_is_not_unsafe_integral<int() &&>();
    test_is_not_unsafe_integral<int() const>();
    test_is_not_unsafe_integral<int() const&>();
    test_is_not_unsafe_integral<int() const&&>();
    test_is_not_unsafe_integral<int() volatile>();
    test_is_not_unsafe_integral<int() volatile&>();
    test_is_not_unsafe_integral<int() volatile&&>();
    test_is_not_unsafe_integral<int() const volatile>();
    test_is_not_unsafe_integral<int() const volatile&>();
    test_is_not_unsafe_integral<int() const volatile&&>();
    test_is_not_unsafe_integral<int() noexcept>();
    test_is_not_unsafe_integral<int()& noexcept>();
    test_is_not_unsafe_integral<int()&& noexcept>();
    test_is_not_unsafe_integral<int() const noexcept>();
    test_is_not_unsafe_integral<int() const& noexcept>();
    test_is_not_unsafe_integral<int() const&& noexcept>();
    test_is_not_unsafe_integral<int() volatile noexcept>();
    test_is_not_unsafe_integral<int() volatile& noexcept>();
    test_is_not_unsafe_integral<int() volatile&& noexcept>();
    test_is_not_unsafe_integral<int() const volatile noexcept>();
    test_is_not_unsafe_integral<int() const volatile& noexcept>();
    test_is_not_unsafe_integral<int() const volatile&& noexcept>();

    test_is_not_unsafe_integral<int(int)>();
    test_is_not_unsafe_integral<int(int)&>();
    test_is_not_unsafe_integral<int(int) &&>();
    test_is_not_unsafe_integral<int(int) const>();
    test_is_not_unsafe_integral<int(int) const&>();
    test_is_not_unsafe_integral<int(int) const&&>();
    test_is_not_unsafe_integral<int(int) volatile>();
    test_is_not_unsafe_integral<int(int) volatile&>();
    test_is_not_unsafe_integral<int(int) volatile&&>();
    test_is_not_unsafe_integral<int(int) const volatile>();
    test_is_not_unsafe_integral<int(int) const volatile&>();
    test_is_not_unsafe_integral<int(int) const volatile&&>();
    test_is_not_unsafe_integral<int(int) noexcept>();
    test_is_not_unsafe_integral<int(int)& noexcept>();
    test_is_not_unsafe_integral<int(int)&& noexcept>();
    test_is_not_unsafe_integral<int(int) const noexcept>();
    test_is_not_unsafe_integral<int(int) const& noexcept>();
    test_is_not_unsafe_integral<int(int) const&& noexcept>();
    test_is_not_unsafe_integral<int(int) volatile noexcept>();
    test_is_not_unsafe_integral<int(int) volatile& noexcept>();
    test_is_not_unsafe_integral<int(int) volatile&& noexcept>();
    test_is_not_unsafe_integral<int(int) const volatile noexcept>();
    test_is_not_unsafe_integral<int(int) const volatile& noexcept>();
    test_is_not_unsafe_integral<int(int) const volatile&& noexcept>();

    test_is_not_unsafe_integral<int(...)>();
    test_is_not_unsafe_integral<int(...)&>();
    test_is_not_unsafe_integral<int(...) &&>();
    test_is_not_unsafe_integral<int(...) const>();
    test_is_not_unsafe_integral<int(...) const&>();
    test_is_not_unsafe_integral<int(...) const&&>();
    test_is_not_unsafe_integral<int(...) volatile>();
    test_is_not_unsafe_integral<int(...) volatile&>();
    test_is_not_unsafe_integral<int(...) volatile&&>();
    test_is_not_unsafe_integral<int(...) const volatile>();
    test_is_not_unsafe_integral<int(...) const volatile&>();
    test_is_not_unsafe_integral<int(...) const volatile&&>();
    test_is_not_unsafe_integral<int(...) noexcept>();
    test_is_not_unsafe_integral<int(...)& noexcept>();
    test_is_not_unsafe_integral<int(...)&& noexcept>();
    test_is_not_unsafe_integral<int(...) const noexcept>();
    test_is_not_unsafe_integral<int(...) const& noexcept>();
    test_is_not_unsafe_integral<int(...) const&& noexcept>();
    test_is_not_unsafe_integral<int(...) volatile noexcept>();
    test_is_not_unsafe_integral<int(...) volatile& noexcept>();
    test_is_not_unsafe_integral<int(...) volatile&& noexcept>();
    test_is_not_unsafe_integral<int(...) const volatile noexcept>();
    test_is_not_unsafe_integral<int(...) const volatile& noexcept>();
    test_is_not_unsafe_integral<int(...) const volatile&& noexcept>();

    test_is_not_unsafe_integral<int(int, ...)>();
    test_is_not_unsafe_integral<int(int, ...)&>();
    test_is_not_unsafe_integral<int(int, ...) &&>();
    test_is_not_unsafe_integral<int(int, ...) const>();
    test_is_not_unsafe_integral<int(int, ...) const&>();
    test_is_not_unsafe_integral<int(int, ...) const&&>();
    test_is_not_unsafe_integral<int(int, ...) volatile>();
    test_is_not_unsafe_integral<int(int, ...) volatile&>();
    test_is_not_unsafe_integral<int(int, ...) volatile&&>();
    test_is_not_unsafe_integral<int(int, ...) const volatile>();
    test_is_not_unsafe_integral<int(int, ...) const volatile&>();
    test_is_not_unsafe_integral<int(int, ...) const volatile&&>();
    test_is_not_unsafe_integral<int(int, ...) noexcept>();
    test_is_not_unsafe_integral<int(int, ...)& noexcept>();
    test_is_not_unsafe_integral<int(int, ...)&& noexcept>();
    test_is_not_unsafe_integral<int(int, ...) const noexcept>();
    test_is_not_unsafe_integral<int(int, ...) const& noexcept>();
    test_is_not_unsafe_integral<int(int, ...) const&& noexcept>();
    test_is_not_unsafe_integral<int(int, ...) volatile noexcept>();
    test_is_not_unsafe_integral<int(int, ...) volatile& noexcept>();
    test_is_not_unsafe_integral<int(int, ...) volatile&& noexcept>();
    test_is_not_unsafe_integral<int(int, ...) const volatile noexcept>();
    test_is_not_unsafe_integral<int(int, ...) const volatile& noexcept>();
    test_is_not_unsafe_integral<int(int, ...) const volatile&& noexcept>();

    test_is_not_unsafe_integral<void (*)()>();
    test_is_not_unsafe_integral<void (*)() noexcept>();

    test_is_not_unsafe_integral<void (*)(int)>();
    test_is_not_unsafe_integral<void (*)(int) noexcept>();

    test_is_not_unsafe_integral<void (*)(...)>();
    test_is_not_unsafe_integral<void (*)(...) noexcept>();

    test_is_not_unsafe_integral<void (*)(int, ...)>();
    test_is_not_unsafe_integral<void (*)(int, ...) noexcept>();

    test_is_not_unsafe_integral<int (*)()>();
    test_is_not_unsafe_integral<int (*)() noexcept>();

    test_is_not_unsafe_integral<int (*)(int)>();
    test_is_not_unsafe_integral<int (*)(int) noexcept>();

    test_is_not_unsafe_integral<int (*)(...)>();
    test_is_not_unsafe_integral<int (*)(...) noexcept>();

    test_is_not_unsafe_integral<int (*)(int, ...)>();
    test_is_not_unsafe_integral<int (*)(int, ...) noexcept>();

    test_is_not_unsafe_integral<void (&)()>();
    test_is_not_unsafe_integral<void (&)() noexcept>();

    test_is_not_unsafe_integral<void (&)(int)>();
    test_is_not_unsafe_integral<void (&)(int) noexcept>();

    test_is_not_unsafe_integral<void (&)(...)>();
    test_is_not_unsafe_integral<void (&)(...) noexcept>();

    test_is_not_unsafe_integral<void (&)(int, ...)>();
    test_is_not_unsafe_integral<void (&)(int, ...) noexcept>();

    test_is_not_unsafe_integral<int (&)()>();
    test_is_not_unsafe_integral<int (&)() noexcept>();

    test_is_not_unsafe_integral<int (&)(int)>();
    test_is_not_unsafe_integral<int (&)(int) noexcept>();

    test_is_not_unsafe_integral<int (&)(...)>();
    test_is_not_unsafe_integral<int (&)(...) noexcept>();

    test_is_not_unsafe_integral<int (&)(int, ...)>();
    test_is_not_unsafe_integral<int (&)(int, ...) noexcept>();

    test_is_not_unsafe_integral<void(&&)()>();
    test_is_not_unsafe_integral<void(&&)() noexcept>();

    test_is_not_unsafe_integral<void(&&)(int)>();
    test_is_not_unsafe_integral<void(&&)(int) noexcept>();

    test_is_not_unsafe_integral<void(&&)(...)>();
    test_is_not_unsafe_integral<void(&&)(...) noexcept>();

    test_is_not_unsafe_integral<void(&&)(int, ...)>();
    test_is_not_unsafe_integral<void(&&)(int, ...) noexcept>();

    test_is_not_unsafe_integral<int(&&)()>();
    test_is_not_unsafe_integral<int(&&)() noexcept>();

    test_is_not_unsafe_integral<int(&&)(int)>();
    test_is_not_unsafe_integral<int(&&)(int) noexcept>();

    test_is_not_unsafe_integral<int(&&)(...)>();
    test_is_not_unsafe_integral<int(&&)(...) noexcept>();

    test_is_not_unsafe_integral<int(&&)(int, ...)>();
    test_is_not_unsafe_integral<int(&&)(int, ...) noexcept>();

    test_is_not_unsafe_integral<void (Class::*)()>();
    test_is_not_unsafe_integral<void (Class::*)()&>();
    test_is_not_unsafe_integral<void (Class::*)() &&>();
    test_is_not_unsafe_integral<void (Class::*)() const>();
    test_is_not_unsafe_integral<void (Class::*)() const&>();
    test_is_not_unsafe_integral<void (Class::*)() const&&>();
    test_is_not_unsafe_integral<void (Class::*)() noexcept>();
    test_is_not_unsafe_integral<void (Class::*)()& noexcept>();
    test_is_not_unsafe_integral<void (Class::*)()&& noexcept>();
    test_is_not_unsafe_integral<void (Class::*)() const noexcept>();
    test_is_not_unsafe_integral<void (Class::*)() const& noexcept>();
    test_is_not_unsafe_integral<void (Class::*)() const&& noexcept>();

    test_is_not_unsafe_integral<void (Class::*)(int)>();
    test_is_not_unsafe_integral<void (Class::*)(int)&>();
    test_is_not_unsafe_integral<void (Class::*)(int) &&>();
    test_is_not_unsafe_integral<void (Class::*)(int) const>();
    test_is_not_unsafe_integral<void (Class::*)(int) const&>();
    test_is_not_unsafe_integral<void (Class::*)(int) const&&>();
    test_is_not_unsafe_integral<void (Class::*)(int) noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(int)& noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(int) const noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_integral<void (Class::*)(...)>();
    test_is_not_unsafe_integral<void (Class::*)(...)&>();
    test_is_not_unsafe_integral<void (Class::*)(...) &&>();
    test_is_not_unsafe_integral<void (Class::*)(...) const>();
    test_is_not_unsafe_integral<void (Class::*)(...) const&>();
    test_is_not_unsafe_integral<void (Class::*)(...) const&&>();
    test_is_not_unsafe_integral<void (Class::*)(...) noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(...)& noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(...) const noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(...) const&& noexcept>();

    test_is_not_unsafe_integral<void (Class::*)(int, ...)>();
    test_is_not_unsafe_integral<void (Class::*)(int, ...)&>();
    test_is_not_unsafe_integral<void (Class::*)(int, ...) &&>();
    test_is_not_unsafe_integral<void (Class::*)(int, ...) const>();
    test_is_not_unsafe_integral<void (Class::*)(int, ...) const&>();
    test_is_not_unsafe_integral<void (Class::*)(int, ...) const&&>();
    test_is_not_unsafe_integral<void (Class::*)(int, ...) noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(int, ...)& noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(int, ...) const noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsafe_integral<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_unsafe_integral<int (Class::*)()>();
    test_is_not_unsafe_integral<int (Class::*)()&>();
    test_is_not_unsafe_integral<int (Class::*)() &&>();
    test_is_not_unsafe_integral<int (Class::*)() const>();
    test_is_not_unsafe_integral<int (Class::*)() const&>();
    test_is_not_unsafe_integral<int (Class::*)() const&&>();
    test_is_not_unsafe_integral<int (Class::*)() noexcept>();
    test_is_not_unsafe_integral<int (Class::*)()& noexcept>();
    test_is_not_unsafe_integral<int (Class::*)()&& noexcept>();
    test_is_not_unsafe_integral<int (Class::*)() const noexcept>();
    test_is_not_unsafe_integral<int (Class::*)() const& noexcept>();
    test_is_not_unsafe_integral<int (Class::*)() const&& noexcept>();

    test_is_not_unsafe_integral<int (Class::*)(int)>();
    test_is_not_unsafe_integral<int (Class::*)(int)&>();
    test_is_not_unsafe_integral<int (Class::*)(int) &&>();
    test_is_not_unsafe_integral<int (Class::*)(int) const>();
    test_is_not_unsafe_integral<int (Class::*)(int) const&>();
    test_is_not_unsafe_integral<int (Class::*)(int) const&&>();
    test_is_not_unsafe_integral<int (Class::*)(int) noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(int)& noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(int) const noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_integral<int (Class::*)(...)>();
    test_is_not_unsafe_integral<int (Class::*)(...)&>();
    test_is_not_unsafe_integral<int (Class::*)(...) &&>();
    test_is_not_unsafe_integral<int (Class::*)(...) const>();
    test_is_not_unsafe_integral<int (Class::*)(...) const&>();
    test_is_not_unsafe_integral<int (Class::*)(...) const&&>();
    test_is_not_unsafe_integral<int (Class::*)(...) noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(...)& noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(...) const noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(...) const&& noexcept>();

    test_is_not_unsafe_integral<int (Class::*)(int, ...)>();
    test_is_not_unsafe_integral<int (Class::*)(int, ...)&>();
    test_is_not_unsafe_integral<int (Class::*)(int, ...) &&>();
    test_is_not_unsafe_integral<int (Class::*)(int, ...) const>();
    test_is_not_unsafe_integral<int (Class::*)(int, ...) const&>();
    test_is_not_unsafe_integral<int (Class::*)(int, ...) const&&>();
    test_is_not_unsafe_integral<int (Class::*)(int, ...) noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(int, ...)& noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(int, ...) const noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsafe_integral<int (Class::*)(int, ...) const&& noexcept>();
}
