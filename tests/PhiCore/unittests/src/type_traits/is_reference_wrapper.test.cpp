#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_lvalue_reference.hpp>
#include <phi/type_traits/is_reference.hpp>
#include <phi/type_traits/is_reference_wrapper.hpp>
#include <phi/type_traits/is_rvalue_reference.hpp>
#include <functional>
#include <vector>

template <typename T>
void test_is_reference_wrapper_impl()
{
    STATIC_REQUIRE(phi::is_reference_wrapper<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_reference_wrapper<T>::value);

#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE(phi::is_class<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_reference_wrapper_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_reference_wrapper_v<T>);

#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE(phi::is_class_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_reference_wrapper<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_reference_wrapper<T>);
}

template <typename T>
void test_is_not_reference_wrapper_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper<T>::value);
    STATIC_REQUIRE(phi::is_not_reference_wrapper<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper_v<T>);
    STATIC_REQUIRE(phi::is_not_reference_wrapper_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_reference_wrapper<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_reference_wrapper<T>);
}

template <typename T>
void test_is_reference_wrapper()
{
    test_is_reference_wrapper_impl<T>();
    test_is_reference_wrapper_impl<const T>();
    test_is_reference_wrapper_impl<volatile T>();
    test_is_reference_wrapper_impl<const volatile T>();
}

template <typename T>
void test_is_not_reference_wrapper()
{
    test_is_not_reference_wrapper_impl<T>();
    test_is_not_reference_wrapper_impl<const T>();
    test_is_not_reference_wrapper_impl<volatile T>();
    test_is_not_reference_wrapper_impl<const volatile T>();
}

TEST_CASE("is_refenrece_wrapper")
{
    test_is_reference_wrapper<std::reference_wrapper<int>>();
    test_is_reference_wrapper<std::reference_wrapper<float>>();
    test_is_reference_wrapper<std::reference_wrapper<void>>();

    test_is_not_reference_wrapper<void>();
    test_is_not_reference_wrapper<phi::nullptr_t>();
    test_is_not_reference_wrapper<bool>();
    test_is_not_reference_wrapper<char>();
    test_is_not_reference_wrapper<signed char>();
    test_is_not_reference_wrapper<unsigned char>();
    test_is_not_reference_wrapper<short>();
    test_is_not_reference_wrapper<unsigned short>();
    test_is_not_reference_wrapper<int>();
    test_is_not_reference_wrapper<unsigned int>();
    test_is_not_reference_wrapper<long>();
    test_is_not_reference_wrapper<unsigned long>();
    test_is_not_reference_wrapper<long long>();
    test_is_not_reference_wrapper<unsigned long long>();
    test_is_not_reference_wrapper<float>();
    test_is_not_reference_wrapper<double>();
    test_is_not_reference_wrapper<long double>();
    test_is_not_reference_wrapper<char8_t>();
    test_is_not_reference_wrapper<char16_t>();
    test_is_not_reference_wrapper<char32_t>();
    test_is_not_reference_wrapper<wchar_t>();

    test_is_not_reference_wrapper<phi::boolean>();
    test_is_not_reference_wrapper<phi::integer<signed char>>();
    test_is_not_reference_wrapper<phi::integer<unsigned char>>();
    test_is_not_reference_wrapper<phi::integer<short>>();
    test_is_not_reference_wrapper<phi::integer<unsigned short>>();
    test_is_not_reference_wrapper<phi::integer<int>>();
    test_is_not_reference_wrapper<phi::integer<unsigned int>>();
    test_is_not_reference_wrapper<phi::integer<long>>();
    test_is_not_reference_wrapper<phi::integer<unsigned long>>();
    test_is_not_reference_wrapper<phi::integer<long long>>();
    test_is_not_reference_wrapper<phi::integer<unsigned long long>>();
    test_is_not_reference_wrapper<phi::floating_point<float>>();
    test_is_not_reference_wrapper<phi::floating_point<double>>();
    test_is_not_reference_wrapper<phi::floating_point<long double>>();

    test_is_not_reference_wrapper<std::vector<int>>();
    test_is_not_reference_wrapper<phi::scope_ptr<int>>();

    test_is_not_reference_wrapper<int&>();
    test_is_not_reference_wrapper<const int&>();
    test_is_not_reference_wrapper<volatile int&>();
    test_is_not_reference_wrapper<const volatile int&>();
    test_is_not_reference_wrapper<int&&>();
    test_is_not_reference_wrapper<const int&&>();
    test_is_not_reference_wrapper<volatile int&&>();
    test_is_not_reference_wrapper<const volatile int&&>();
    test_is_not_reference_wrapper<int*>();
    test_is_not_reference_wrapper<const int*>();
    test_is_not_reference_wrapper<volatile int*>();
    test_is_not_reference_wrapper<const volatile int*>();
    test_is_not_reference_wrapper<int**>();
    test_is_not_reference_wrapper<const int**>();
    test_is_not_reference_wrapper<volatile int**>();
    test_is_not_reference_wrapper<const volatile int**>();
    test_is_not_reference_wrapper<int*&>();
    test_is_not_reference_wrapper<const int*&>();
    test_is_not_reference_wrapper<volatile int*&>();
    test_is_not_reference_wrapper<const volatile int*&>();
    test_is_not_reference_wrapper<int*&&>();
    test_is_not_reference_wrapper<const int*&&>();
    test_is_not_reference_wrapper<volatile int*&&>();
    test_is_not_reference_wrapper<const volatile int*&&>();
    test_is_not_reference_wrapper<void*>();
    test_is_not_reference_wrapper<char[3]>();
    test_is_not_reference_wrapper<char[]>();
    test_is_not_reference_wrapper<char* [3]>();
    test_is_not_reference_wrapper<char*[]>();
    test_is_not_reference_wrapper<int(*)[3]>();
    test_is_not_reference_wrapper<int(*)[]>();
    test_is_not_reference_wrapper<int(&)[3]>();
    test_is_not_reference_wrapper<int(&)[]>();
    test_is_not_reference_wrapper<int(&&)[3]>();
    test_is_not_reference_wrapper<int(&&)[]>();
    test_is_not_reference_wrapper<char[3][2]>();
    test_is_not_reference_wrapper<char[][2]>();
    test_is_not_reference_wrapper<char* [3][2]>();
    test_is_not_reference_wrapper<char*[][2]>();
    test_is_not_reference_wrapper<int(*)[3][2]>();
    test_is_not_reference_wrapper<int(*)[][2]>();
    test_is_not_reference_wrapper<int(&)[3][2]>();
    test_is_not_reference_wrapper<int(&)[][2]>();
    test_is_not_reference_wrapper<int(&&)[3][2]>();
    test_is_not_reference_wrapper<int(&&)[][2]>();
    test_is_not_reference_wrapper<Class>();
    test_is_not_reference_wrapper<Class[]>();
    test_is_not_reference_wrapper<Class[2]>();
    test_is_not_reference_wrapper<Template<void>>();
    test_is_not_reference_wrapper<Template<int>>();
    test_is_not_reference_wrapper<Template<Class>>();
    test_is_not_reference_wrapper<Template<IncompleteType>>();
    test_is_not_reference_wrapper<VariadicTemplate<>>();
    test_is_not_reference_wrapper<VariadicTemplate<void>>();
    test_is_not_reference_wrapper<VariadicTemplate<int>>();
    test_is_not_reference_wrapper<VariadicTemplate<Class>>();
    test_is_not_reference_wrapper<VariadicTemplate<IncompleteType>>();
    test_is_not_reference_wrapper<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_reference_wrapper<PublicDerivedFromTemplate<Base>>();
    test_is_not_reference_wrapper<PublicDerivedFromTemplate<Derived>>();
    test_is_not_reference_wrapper<PublicDerivedFromTemplate<Class>>();
    test_is_not_reference_wrapper<PrivateDerivedFromTemplate<Base>>();
    test_is_not_reference_wrapper<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_reference_wrapper<PrivateDerivedFromTemplate<Class>>();
    test_is_not_reference_wrapper<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_reference_wrapper<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_reference_wrapper<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_reference_wrapper<Union>();
    test_is_not_reference_wrapper<NonEmptyUnion>();
    test_is_not_reference_wrapper<Empty>();
    test_is_not_reference_wrapper<NotEmpty>();
    test_is_not_reference_wrapper<BitZero>();
    test_is_not_reference_wrapper<BitOne>();
    test_is_not_reference_wrapper<Base>();
    test_is_not_reference_wrapper<Derived>();
    test_is_not_reference_wrapper<Abstract>();
    test_is_not_reference_wrapper<PublicAbstract>();
    test_is_not_reference_wrapper<PrivateAbstract>();
    test_is_not_reference_wrapper<ProtectedAbstract>();
    test_is_not_reference_wrapper<AbstractTemplate<int>>();
    test_is_not_reference_wrapper<AbstractTemplate<double>>();
    test_is_not_reference_wrapper<AbstractTemplate<Class>>();
    test_is_not_reference_wrapper<AbstractTemplate<IncompleteType>>();
    test_is_not_reference_wrapper<Final>();
    test_is_not_reference_wrapper<PublicDestructor>();
    test_is_not_reference_wrapper<ProtectedDestructor>();
    test_is_not_reference_wrapper<PrivateDestructor>();
    test_is_not_reference_wrapper<VirtualPublicDestructor>();
    test_is_not_reference_wrapper<VirtualProtectedDestructor>();
    test_is_not_reference_wrapper<VirtualPrivateDestructor>();
    test_is_not_reference_wrapper<PurePublicDestructor>();
    test_is_not_reference_wrapper<PureProtectedDestructor>();
    test_is_not_reference_wrapper<PurePrivateDestructor>();
    test_is_not_reference_wrapper<DeletedPublicDestructor>();
    test_is_not_reference_wrapper<DeletedProtectedDestructor>();
    test_is_not_reference_wrapper<DeletedPrivateDestructor>();
    test_is_not_reference_wrapper<DeletedVirtualPublicDestructor>();
    test_is_not_reference_wrapper<DeletedVirtualProtectedDestructor>();
    test_is_not_reference_wrapper<DeletedVirtualPrivateDestructor>();
    test_is_not_reference_wrapper<Enum>();
    test_is_not_reference_wrapper<EnumSigned>();
    test_is_not_reference_wrapper<EnumUnsigned>();
    test_is_not_reference_wrapper<EnumClass>();
    test_is_not_reference_wrapper<EnumStruct>();
    test_is_not_reference_wrapper<Function>();
    test_is_not_reference_wrapper<FunctionPtr>();
    test_is_not_reference_wrapper<MemberObjectPtr>();
    test_is_not_reference_wrapper<MemberFunctionPtr>();
    test_is_not_reference_wrapper<IncompleteType>();
    test_is_not_reference_wrapper<IncompleteTemplate<void>>();
    test_is_not_reference_wrapper<IncompleteTemplate<int>>();
    test_is_not_reference_wrapper<IncompleteTemplate<Class>>();
    test_is_not_reference_wrapper<IncompleteTemplate<IncompleteType>>();
    test_is_not_reference_wrapper<IncompleteVariadicTemplate<>>();
    test_is_not_reference_wrapper<IncompleteVariadicTemplate<void>>();
    test_is_not_reference_wrapper<IncompleteVariadicTemplate<int>>();
    test_is_not_reference_wrapper<IncompleteVariadicTemplate<Class>>();
    test_is_not_reference_wrapper<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_reference_wrapper<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_reference_wrapper<int Class::*>();
    test_is_not_reference_wrapper<float Class::*>();
    test_is_not_reference_wrapper<void * Class::*>();
    test_is_not_reference_wrapper<int * Class::*>();
    test_is_not_reference_wrapper<int Class::*&>();
    test_is_not_reference_wrapper<float Class::*&>();
    test_is_not_reference_wrapper<void * Class::*&>();
    test_is_not_reference_wrapper<int * Class::*&>();
    test_is_not_reference_wrapper<int Class::*&&>();
    test_is_not_reference_wrapper<float Class::*&&>();
    test_is_not_reference_wrapper<void * Class::*&&>();
    test_is_not_reference_wrapper<int * Class::*&&>();
    test_is_not_reference_wrapper<int Class::*const>();
    test_is_not_reference_wrapper<float Class::*const>();
    test_is_not_reference_wrapper<void * Class::*const>();
    test_is_not_reference_wrapper<int Class::*const&>();
    test_is_not_reference_wrapper<float Class::*const&>();
    test_is_not_reference_wrapper<void * Class::*const&>();
    test_is_not_reference_wrapper<int Class::*const&&>();
    test_is_not_reference_wrapper<float Class::*const&&>();
    test_is_not_reference_wrapper<void * Class::*const&&>();
    test_is_not_reference_wrapper<int Class::*volatile>();
    test_is_not_reference_wrapper<float Class::*volatile>();
    test_is_not_reference_wrapper<void * Class::*volatile>();
    test_is_not_reference_wrapper<int Class::*volatile&>();
    test_is_not_reference_wrapper<float Class::*volatile&>();
    test_is_not_reference_wrapper<void * Class::*volatile&>();
    test_is_not_reference_wrapper<int Class::*volatile&&>();
    test_is_not_reference_wrapper<float Class::*volatile&&>();
    test_is_not_reference_wrapper<void * Class::*volatile&&>();
    test_is_not_reference_wrapper<int Class::*const volatile>();
    test_is_not_reference_wrapper<float Class::*const volatile>();
    test_is_not_reference_wrapper<void * Class::*const volatile>();
    test_is_not_reference_wrapper<int Class::*const volatile&>();
    test_is_not_reference_wrapper<float Class::*const volatile&>();
    test_is_not_reference_wrapper<void * Class::*const volatile&>();
    test_is_not_reference_wrapper<int Class::*const volatile&&>();
    test_is_not_reference_wrapper<float Class::*const volatile&&>();
    test_is_not_reference_wrapper<void * Class::*const volatile&&>();
    test_is_not_reference_wrapper<NonCopyable>();
    test_is_not_reference_wrapper<NonMoveable>();
    test_is_not_reference_wrapper<NonConstructible>();
    test_is_not_reference_wrapper<Tracked>();
    test_is_not_reference_wrapper<TrapConstructible>();
    test_is_not_reference_wrapper<TrapImplicitConversion>();
    test_is_not_reference_wrapper<TrapComma>();
    test_is_not_reference_wrapper<TrapCall>();
    test_is_not_reference_wrapper<TrapSelfAssign>();
    test_is_not_reference_wrapper<TrapDeref>();
    test_is_not_reference_wrapper<TrapArraySubscript>();

    test_is_not_reference_wrapper<void()>();
    test_is_not_reference_wrapper<void()&>();
    test_is_not_reference_wrapper<void() &&>();
    test_is_not_reference_wrapper<void() const>();
    test_is_not_reference_wrapper<void() const&>();
    test_is_not_reference_wrapper<void() const&&>();
    test_is_not_reference_wrapper<void() volatile>();
    test_is_not_reference_wrapper<void() volatile&>();
    test_is_not_reference_wrapper<void() volatile&&>();
    test_is_not_reference_wrapper<void() const volatile>();
    test_is_not_reference_wrapper<void() const volatile&>();
    test_is_not_reference_wrapper<void() const volatile&&>();
    test_is_not_reference_wrapper<void() noexcept>();
    test_is_not_reference_wrapper<void()& noexcept>();
    test_is_not_reference_wrapper<void()&& noexcept>();
    test_is_not_reference_wrapper<void() const noexcept>();
    test_is_not_reference_wrapper<void() const& noexcept>();
    test_is_not_reference_wrapper<void() const&& noexcept>();
    test_is_not_reference_wrapper<void() volatile noexcept>();
    test_is_not_reference_wrapper<void() volatile& noexcept>();
    test_is_not_reference_wrapper<void() volatile&& noexcept>();
    test_is_not_reference_wrapper<void() const volatile noexcept>();
    test_is_not_reference_wrapper<void() const volatile& noexcept>();
    test_is_not_reference_wrapper<void() const volatile&& noexcept>();

    test_is_not_reference_wrapper<void(int)>();
    test_is_not_reference_wrapper<void(int)&>();
    test_is_not_reference_wrapper<void(int) &&>();
    test_is_not_reference_wrapper<void(int) const>();
    test_is_not_reference_wrapper<void(int) const&>();
    test_is_not_reference_wrapper<void(int) const&&>();
    test_is_not_reference_wrapper<void(int) volatile>();
    test_is_not_reference_wrapper<void(int) volatile&>();
    test_is_not_reference_wrapper<void(int) volatile&&>();
    test_is_not_reference_wrapper<void(int) const volatile>();
    test_is_not_reference_wrapper<void(int) const volatile&>();
    test_is_not_reference_wrapper<void(int) const volatile&&>();
    test_is_not_reference_wrapper<void(int) noexcept>();
    test_is_not_reference_wrapper<void(int)& noexcept>();
    test_is_not_reference_wrapper<void(int)&& noexcept>();
    test_is_not_reference_wrapper<void(int) const noexcept>();
    test_is_not_reference_wrapper<void(int) const& noexcept>();
    test_is_not_reference_wrapper<void(int) const&& noexcept>();
    test_is_not_reference_wrapper<void(int) volatile noexcept>();
    test_is_not_reference_wrapper<void(int) volatile& noexcept>();
    test_is_not_reference_wrapper<void(int) volatile&& noexcept>();
    test_is_not_reference_wrapper<void(int) const volatile noexcept>();
    test_is_not_reference_wrapper<void(int) const volatile& noexcept>();
    test_is_not_reference_wrapper<void(int) const volatile&& noexcept>();

    test_is_not_reference_wrapper<void(...)>();
    test_is_not_reference_wrapper<void(...)&>();
    test_is_not_reference_wrapper<void(...) &&>();
    test_is_not_reference_wrapper<void(...) const>();
    test_is_not_reference_wrapper<void(...) const&>();
    test_is_not_reference_wrapper<void(...) const&&>();
    test_is_not_reference_wrapper<void(...) volatile>();
    test_is_not_reference_wrapper<void(...) volatile&>();
    test_is_not_reference_wrapper<void(...) volatile&&>();
    test_is_not_reference_wrapper<void(...) const volatile>();
    test_is_not_reference_wrapper<void(...) const volatile&>();
    test_is_not_reference_wrapper<void(...) const volatile&&>();
    test_is_not_reference_wrapper<void(...) noexcept>();
    test_is_not_reference_wrapper<void(...)& noexcept>();
    test_is_not_reference_wrapper<void(...)&& noexcept>();
    test_is_not_reference_wrapper<void(...) const noexcept>();
    test_is_not_reference_wrapper<void(...) const& noexcept>();
    test_is_not_reference_wrapper<void(...) const&& noexcept>();
    test_is_not_reference_wrapper<void(...) volatile noexcept>();
    test_is_not_reference_wrapper<void(...) volatile& noexcept>();
    test_is_not_reference_wrapper<void(...) volatile&& noexcept>();
    test_is_not_reference_wrapper<void(...) const volatile noexcept>();
    test_is_not_reference_wrapper<void(...) const volatile& noexcept>();
    test_is_not_reference_wrapper<void(...) const volatile&& noexcept>();

    test_is_not_reference_wrapper<void(int, ...)>();
    test_is_not_reference_wrapper<void(int, ...)&>();
    test_is_not_reference_wrapper<void(int, ...) &&>();
    test_is_not_reference_wrapper<void(int, ...) const>();
    test_is_not_reference_wrapper<void(int, ...) const&>();
    test_is_not_reference_wrapper<void(int, ...) const&&>();
    test_is_not_reference_wrapper<void(int, ...) volatile>();
    test_is_not_reference_wrapper<void(int, ...) volatile&>();
    test_is_not_reference_wrapper<void(int, ...) volatile&&>();
    test_is_not_reference_wrapper<void(int, ...) const volatile>();
    test_is_not_reference_wrapper<void(int, ...) const volatile&>();
    test_is_not_reference_wrapper<void(int, ...) const volatile&&>();
    test_is_not_reference_wrapper<void(int, ...) noexcept>();
    test_is_not_reference_wrapper<void(int, ...)& noexcept>();
    test_is_not_reference_wrapper<void(int, ...)&& noexcept>();
    test_is_not_reference_wrapper<void(int, ...) const noexcept>();
    test_is_not_reference_wrapper<void(int, ...) const& noexcept>();
    test_is_not_reference_wrapper<void(int, ...) const&& noexcept>();
    test_is_not_reference_wrapper<void(int, ...) volatile noexcept>();
    test_is_not_reference_wrapper<void(int, ...) volatile& noexcept>();
    test_is_not_reference_wrapper<void(int, ...) volatile&& noexcept>();
    test_is_not_reference_wrapper<void(int, ...) const volatile noexcept>();
    test_is_not_reference_wrapper<void(int, ...) const volatile& noexcept>();
    test_is_not_reference_wrapper<void(int, ...) const volatile&& noexcept>();

    test_is_not_reference_wrapper<int()>();
    test_is_not_reference_wrapper<int()&>();
    test_is_not_reference_wrapper<int() &&>();
    test_is_not_reference_wrapper<int() const>();
    test_is_not_reference_wrapper<int() const&>();
    test_is_not_reference_wrapper<int() const&&>();
    test_is_not_reference_wrapper<int() volatile>();
    test_is_not_reference_wrapper<int() volatile&>();
    test_is_not_reference_wrapper<int() volatile&&>();
    test_is_not_reference_wrapper<int() const volatile>();
    test_is_not_reference_wrapper<int() const volatile&>();
    test_is_not_reference_wrapper<int() const volatile&&>();
    test_is_not_reference_wrapper<int() noexcept>();
    test_is_not_reference_wrapper<int()& noexcept>();
    test_is_not_reference_wrapper<int()&& noexcept>();
    test_is_not_reference_wrapper<int() const noexcept>();
    test_is_not_reference_wrapper<int() const& noexcept>();
    test_is_not_reference_wrapper<int() const&& noexcept>();
    test_is_not_reference_wrapper<int() volatile noexcept>();
    test_is_not_reference_wrapper<int() volatile& noexcept>();
    test_is_not_reference_wrapper<int() volatile&& noexcept>();
    test_is_not_reference_wrapper<int() const volatile noexcept>();
    test_is_not_reference_wrapper<int() const volatile& noexcept>();
    test_is_not_reference_wrapper<int() const volatile&& noexcept>();

    test_is_not_reference_wrapper<int(int)>();
    test_is_not_reference_wrapper<int(int)&>();
    test_is_not_reference_wrapper<int(int) &&>();
    test_is_not_reference_wrapper<int(int) const>();
    test_is_not_reference_wrapper<int(int) const&>();
    test_is_not_reference_wrapper<int(int) const&&>();
    test_is_not_reference_wrapper<int(int) volatile>();
    test_is_not_reference_wrapper<int(int) volatile&>();
    test_is_not_reference_wrapper<int(int) volatile&&>();
    test_is_not_reference_wrapper<int(int) const volatile>();
    test_is_not_reference_wrapper<int(int) const volatile&>();
    test_is_not_reference_wrapper<int(int) const volatile&&>();
    test_is_not_reference_wrapper<int(int) noexcept>();
    test_is_not_reference_wrapper<int(int)& noexcept>();
    test_is_not_reference_wrapper<int(int)&& noexcept>();
    test_is_not_reference_wrapper<int(int) const noexcept>();
    test_is_not_reference_wrapper<int(int) const& noexcept>();
    test_is_not_reference_wrapper<int(int) const&& noexcept>();
    test_is_not_reference_wrapper<int(int) volatile noexcept>();
    test_is_not_reference_wrapper<int(int) volatile& noexcept>();
    test_is_not_reference_wrapper<int(int) volatile&& noexcept>();
    test_is_not_reference_wrapper<int(int) const volatile noexcept>();
    test_is_not_reference_wrapper<int(int) const volatile& noexcept>();
    test_is_not_reference_wrapper<int(int) const volatile&& noexcept>();

    test_is_not_reference_wrapper<int(...)>();
    test_is_not_reference_wrapper<int(...)&>();
    test_is_not_reference_wrapper<int(...) &&>();
    test_is_not_reference_wrapper<int(...) const>();
    test_is_not_reference_wrapper<int(...) const&>();
    test_is_not_reference_wrapper<int(...) const&&>();
    test_is_not_reference_wrapper<int(...) volatile>();
    test_is_not_reference_wrapper<int(...) volatile&>();
    test_is_not_reference_wrapper<int(...) volatile&&>();
    test_is_not_reference_wrapper<int(...) const volatile>();
    test_is_not_reference_wrapper<int(...) const volatile&>();
    test_is_not_reference_wrapper<int(...) const volatile&&>();
    test_is_not_reference_wrapper<int(...) noexcept>();
    test_is_not_reference_wrapper<int(...)& noexcept>();
    test_is_not_reference_wrapper<int(...)&& noexcept>();
    test_is_not_reference_wrapper<int(...) const noexcept>();
    test_is_not_reference_wrapper<int(...) const& noexcept>();
    test_is_not_reference_wrapper<int(...) const&& noexcept>();
    test_is_not_reference_wrapper<int(...) volatile noexcept>();
    test_is_not_reference_wrapper<int(...) volatile& noexcept>();
    test_is_not_reference_wrapper<int(...) volatile&& noexcept>();
    test_is_not_reference_wrapper<int(...) const volatile noexcept>();
    test_is_not_reference_wrapper<int(...) const volatile& noexcept>();
    test_is_not_reference_wrapper<int(...) const volatile&& noexcept>();

    test_is_not_reference_wrapper<int(int, ...)>();
    test_is_not_reference_wrapper<int(int, ...)&>();
    test_is_not_reference_wrapper<int(int, ...) &&>();
    test_is_not_reference_wrapper<int(int, ...) const>();
    test_is_not_reference_wrapper<int(int, ...) const&>();
    test_is_not_reference_wrapper<int(int, ...) const&&>();
    test_is_not_reference_wrapper<int(int, ...) volatile>();
    test_is_not_reference_wrapper<int(int, ...) volatile&>();
    test_is_not_reference_wrapper<int(int, ...) volatile&&>();
    test_is_not_reference_wrapper<int(int, ...) const volatile>();
    test_is_not_reference_wrapper<int(int, ...) const volatile&>();
    test_is_not_reference_wrapper<int(int, ...) const volatile&&>();
    test_is_not_reference_wrapper<int(int, ...) noexcept>();
    test_is_not_reference_wrapper<int(int, ...)& noexcept>();
    test_is_not_reference_wrapper<int(int, ...)&& noexcept>();
    test_is_not_reference_wrapper<int(int, ...) const noexcept>();
    test_is_not_reference_wrapper<int(int, ...) const& noexcept>();
    test_is_not_reference_wrapper<int(int, ...) const&& noexcept>();
    test_is_not_reference_wrapper<int(int, ...) volatile noexcept>();
    test_is_not_reference_wrapper<int(int, ...) volatile& noexcept>();
    test_is_not_reference_wrapper<int(int, ...) volatile&& noexcept>();
    test_is_not_reference_wrapper<int(int, ...) const volatile noexcept>();
    test_is_not_reference_wrapper<int(int, ...) const volatile& noexcept>();
    test_is_not_reference_wrapper<int(int, ...) const volatile&& noexcept>();

    test_is_not_reference_wrapper<void (*)()>();
    test_is_not_reference_wrapper<void (*)() noexcept>();

    test_is_not_reference_wrapper<void (*)(int)>();
    test_is_not_reference_wrapper<void (*)(int) noexcept>();

    test_is_not_reference_wrapper<void (*)(...)>();
    test_is_not_reference_wrapper<void (*)(...) noexcept>();

    test_is_not_reference_wrapper<void (*)(int, ...)>();
    test_is_not_reference_wrapper<void (*)(int, ...) noexcept>();

    test_is_not_reference_wrapper<int (*)()>();
    test_is_not_reference_wrapper<int (*)() noexcept>();

    test_is_not_reference_wrapper<int (*)(int)>();
    test_is_not_reference_wrapper<int (*)(int) noexcept>();

    test_is_not_reference_wrapper<int (*)(...)>();
    test_is_not_reference_wrapper<int (*)(...) noexcept>();

    test_is_not_reference_wrapper<int (*)(int, ...)>();
    test_is_not_reference_wrapper<int (*)(int, ...) noexcept>();

    test_is_not_reference_wrapper<void (&)()>();
    test_is_not_reference_wrapper<void (&)() noexcept>();

    test_is_not_reference_wrapper<void (&)(int)>();
    test_is_not_reference_wrapper<void (&)(int) noexcept>();

    test_is_not_reference_wrapper<void (&)(...)>();
    test_is_not_reference_wrapper<void (&)(...) noexcept>();

    test_is_not_reference_wrapper<void (&)(int, ...)>();
    test_is_not_reference_wrapper<void (&)(int, ...) noexcept>();

    test_is_not_reference_wrapper<int (&)()>();
    test_is_not_reference_wrapper<int (&)() noexcept>();

    test_is_not_reference_wrapper<int (&)(int)>();
    test_is_not_reference_wrapper<int (&)(int) noexcept>();

    test_is_not_reference_wrapper<int (&)(...)>();
    test_is_not_reference_wrapper<int (&)(...) noexcept>();

    test_is_not_reference_wrapper<int (&)(int, ...)>();
    test_is_not_reference_wrapper<int (&)(int, ...) noexcept>();

    test_is_not_reference_wrapper<void(&&)()>();
    test_is_not_reference_wrapper<void(&&)() noexcept>();

    test_is_not_reference_wrapper<void(&&)(int)>();
    test_is_not_reference_wrapper<void(&&)(int) noexcept>();

    test_is_not_reference_wrapper<void(&&)(...)>();
    test_is_not_reference_wrapper<void(&&)(...) noexcept>();

    test_is_not_reference_wrapper<void(&&)(int, ...)>();
    test_is_not_reference_wrapper<void(&&)(int, ...) noexcept>();

    test_is_not_reference_wrapper<int(&&)()>();
    test_is_not_reference_wrapper<int(&&)() noexcept>();

    test_is_not_reference_wrapper<int(&&)(int)>();
    test_is_not_reference_wrapper<int(&&)(int) noexcept>();

    test_is_not_reference_wrapper<int(&&)(...)>();
    test_is_not_reference_wrapper<int(&&)(...) noexcept>();

    test_is_not_reference_wrapper<int(&&)(int, ...)>();
    test_is_not_reference_wrapper<int(&&)(int, ...) noexcept>();

    test_is_not_reference_wrapper<void (Class::*)()>();
    test_is_not_reference_wrapper<void (Class::*)()&>();
    test_is_not_reference_wrapper<void (Class::*)() &&>();
    test_is_not_reference_wrapper<void (Class::*)() const>();
    test_is_not_reference_wrapper<void (Class::*)() const&>();
    test_is_not_reference_wrapper<void (Class::*)() const&&>();
    test_is_not_reference_wrapper<void (Class::*)() noexcept>();
    test_is_not_reference_wrapper<void (Class::*)()& noexcept>();
    test_is_not_reference_wrapper<void (Class::*)()&& noexcept>();
    test_is_not_reference_wrapper<void (Class::*)() const noexcept>();
    test_is_not_reference_wrapper<void (Class::*)() const& noexcept>();
    test_is_not_reference_wrapper<void (Class::*)() const&& noexcept>();

    test_is_not_reference_wrapper<void (Class::*)(int)>();
    test_is_not_reference_wrapper<void (Class::*)(int)&>();
    test_is_not_reference_wrapper<void (Class::*)(int) &&>();
    test_is_not_reference_wrapper<void (Class::*)(int) const>();
    test_is_not_reference_wrapper<void (Class::*)(int) const&>();
    test_is_not_reference_wrapper<void (Class::*)(int) const&&>();
    test_is_not_reference_wrapper<void (Class::*)(int) noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(int)& noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(int)&& noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(int) const noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(int) const& noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(int) const&& noexcept>();

    test_is_not_reference_wrapper<void (Class::*)(...)>();
    test_is_not_reference_wrapper<void (Class::*)(...)&>();
    test_is_not_reference_wrapper<void (Class::*)(...) &&>();
    test_is_not_reference_wrapper<void (Class::*)(...) const>();
    test_is_not_reference_wrapper<void (Class::*)(...) const&>();
    test_is_not_reference_wrapper<void (Class::*)(...) const&&>();
    test_is_not_reference_wrapper<void (Class::*)(...) noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(...)& noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(...)&& noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(...) const noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(...) const& noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(...) const&& noexcept>();

    test_is_not_reference_wrapper<void (Class::*)(int, ...)>();
    test_is_not_reference_wrapper<void (Class::*)(int, ...)&>();
    test_is_not_reference_wrapper<void (Class::*)(int, ...) &&>();
    test_is_not_reference_wrapper<void (Class::*)(int, ...) const>();
    test_is_not_reference_wrapper<void (Class::*)(int, ...) const&>();
    test_is_not_reference_wrapper<void (Class::*)(int, ...) const&&>();
    test_is_not_reference_wrapper<void (Class::*)(int, ...) noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(int, ...)& noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(int, ...) const noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_reference_wrapper<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_reference_wrapper<int (Class::*)()>();
    test_is_not_reference_wrapper<int (Class::*)()&>();
    test_is_not_reference_wrapper<int (Class::*)() &&>();
    test_is_not_reference_wrapper<int (Class::*)() const>();
    test_is_not_reference_wrapper<int (Class::*)() const&>();
    test_is_not_reference_wrapper<int (Class::*)() const&&>();
    test_is_not_reference_wrapper<int (Class::*)() noexcept>();
    test_is_not_reference_wrapper<int (Class::*)()& noexcept>();
    test_is_not_reference_wrapper<int (Class::*)()&& noexcept>();
    test_is_not_reference_wrapper<int (Class::*)() const noexcept>();
    test_is_not_reference_wrapper<int (Class::*)() const& noexcept>();
    test_is_not_reference_wrapper<int (Class::*)() const&& noexcept>();

    test_is_not_reference_wrapper<int (Class::*)(int)>();
    test_is_not_reference_wrapper<int (Class::*)(int)&>();
    test_is_not_reference_wrapper<int (Class::*)(int) &&>();
    test_is_not_reference_wrapper<int (Class::*)(int) const>();
    test_is_not_reference_wrapper<int (Class::*)(int) const&>();
    test_is_not_reference_wrapper<int (Class::*)(int) const&&>();
    test_is_not_reference_wrapper<int (Class::*)(int) noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(int)& noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(int)&& noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(int) const noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(int) const& noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(int) const&& noexcept>();

    test_is_not_reference_wrapper<int (Class::*)(...)>();
    test_is_not_reference_wrapper<int (Class::*)(...)&>();
    test_is_not_reference_wrapper<int (Class::*)(...) &&>();
    test_is_not_reference_wrapper<int (Class::*)(...) const>();
    test_is_not_reference_wrapper<int (Class::*)(...) const&>();
    test_is_not_reference_wrapper<int (Class::*)(...) const&&>();
    test_is_not_reference_wrapper<int (Class::*)(...) noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(...)& noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(...)&& noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(...) const noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(...) const& noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(...) const&& noexcept>();

    test_is_not_reference_wrapper<int (Class::*)(int, ...)>();
    test_is_not_reference_wrapper<int (Class::*)(int, ...)&>();
    test_is_not_reference_wrapper<int (Class::*)(int, ...) &&>();
    test_is_not_reference_wrapper<int (Class::*)(int, ...) const>();
    test_is_not_reference_wrapper<int (Class::*)(int, ...) const&>();
    test_is_not_reference_wrapper<int (Class::*)(int, ...) const&&>();
    test_is_not_reference_wrapper<int (Class::*)(int, ...) noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(int, ...)& noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(int, ...) const noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_reference_wrapper<int (Class::*)(int, ...) const&& noexcept>();
}
