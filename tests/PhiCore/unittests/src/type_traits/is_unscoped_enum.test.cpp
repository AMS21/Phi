#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unscoped_enum.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_unscoped_enum_impl()
{
#if PHI_HAS_WORKING_IS_UNSCOPED_ENUM()
    STATIC_REQUIRE(phi::is_unscoped_enum<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unscoped_enum<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unscoped_enum_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_unscoped_enum_v<T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unscoped_enum<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unscoped_enum<T>);
#endif
}

template <typename T>
void test_is_not_unscoped_enum_impl()
{
#if PHI_HAS_WORKING_IS_UNSCOPED_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_unscoped_enum<T>::value);
    STATIC_REQUIRE(phi::is_not_unscoped_enum<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unscoped_enum_v<T>);
    STATIC_REQUIRE(phi::is_not_unscoped_enum_v<T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unscoped_enum<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unscoped_enum<T>);
#endif
}

template <typename T>
void test_is_unscoped_enum()
{
    test_is_unscoped_enum_impl<T>();
    test_is_unscoped_enum_impl<const T>();
    test_is_unscoped_enum_impl<volatile T>();
    test_is_unscoped_enum_impl<const volatile T>();
}

template <typename T>
void test_is_not_unscoped_enum()
{
    test_is_not_unscoped_enum_impl<T>();
    test_is_not_unscoped_enum_impl<const T>();
    test_is_not_unscoped_enum_impl<volatile T>();
    test_is_not_unscoped_enum_impl<const volatile T>();
}

class A
{};

enum E
{
};

enum struct EStruct
{
};

enum class EClass
{
};

TEST_CASE("is_unscoped_enum")
{
    test_is_unscoped_enum<E>();
    test_is_not_unscoped_enum<EStruct>();
    test_is_not_unscoped_enum<EClass>();
    test_is_not_unscoped_enum<A>();

    test_is_not_unscoped_enum<void>();
    test_is_not_unscoped_enum<phi::nullptr_t>();
    test_is_not_unscoped_enum<bool>();
    test_is_not_unscoped_enum<char>();
    test_is_not_unscoped_enum<signed char>();
    test_is_not_unscoped_enum<unsigned char>();
    test_is_not_unscoped_enum<short>();
    test_is_not_unscoped_enum<unsigned short>();
    test_is_not_unscoped_enum<int>();
    test_is_not_unscoped_enum<unsigned int>();
    test_is_not_unscoped_enum<long>();
    test_is_not_unscoped_enum<unsigned long>();
    test_is_not_unscoped_enum<long long>();
    test_is_not_unscoped_enum<unsigned long long>();
    test_is_not_unscoped_enum<float>();
    test_is_not_unscoped_enum<double>();
    test_is_not_unscoped_enum<long double>();
    test_is_not_unscoped_enum<char8_t>();
    test_is_not_unscoped_enum<char16_t>();
    test_is_not_unscoped_enum<char32_t>();
    test_is_not_unscoped_enum<wchar_t>();

    test_is_not_unscoped_enum<phi::boolean>();
    test_is_not_unscoped_enum<phi::integer<signed char>>();
    test_is_not_unscoped_enum<phi::integer<unsigned char>>();
    test_is_not_unscoped_enum<phi::integer<short>>();
    test_is_not_unscoped_enum<phi::integer<unsigned short>>();
    test_is_not_unscoped_enum<phi::integer<int>>();
    test_is_not_unscoped_enum<phi::integer<unsigned int>>();
    test_is_not_unscoped_enum<phi::integer<long>>();
    test_is_not_unscoped_enum<phi::integer<unsigned long>>();
    test_is_not_unscoped_enum<phi::integer<long long>>();
    test_is_not_unscoped_enum<phi::integer<unsigned long long>>();
    test_is_not_unscoped_enum<phi::floating_point<float>>();
    test_is_not_unscoped_enum<phi::floating_point<double>>();
    test_is_not_unscoped_enum<phi::floating_point<long double>>();

    test_is_not_unscoped_enum<std::vector<int>>();
    test_is_not_unscoped_enum<phi::scope_ptr<int>>();

    test_is_not_unscoped_enum<int&>();
    test_is_not_unscoped_enum<const int&>();
    test_is_not_unscoped_enum<volatile int&>();
    test_is_not_unscoped_enum<const volatile int&>();
    test_is_not_unscoped_enum<int&&>();
    test_is_not_unscoped_enum<const int&&>();
    test_is_not_unscoped_enum<volatile int&&>();
    test_is_not_unscoped_enum<const volatile int&&>();
    test_is_not_unscoped_enum<int*>();
    test_is_not_unscoped_enum<const int*>();
    test_is_not_unscoped_enum<volatile int*>();
    test_is_not_unscoped_enum<const volatile int*>();
    test_is_not_unscoped_enum<int**>();
    test_is_not_unscoped_enum<const int**>();
    test_is_not_unscoped_enum<volatile int**>();
    test_is_not_unscoped_enum<const volatile int**>();
    test_is_not_unscoped_enum<int*&>();
    test_is_not_unscoped_enum<const int*&>();
    test_is_not_unscoped_enum<volatile int*&>();
    test_is_not_unscoped_enum<const volatile int*&>();
    test_is_not_unscoped_enum<int*&&>();
    test_is_not_unscoped_enum<const int*&&>();
    test_is_not_unscoped_enum<volatile int*&&>();
    test_is_not_unscoped_enum<const volatile int*&&>();
    test_is_not_unscoped_enum<void*>();
    test_is_not_unscoped_enum<char[3]>();
    test_is_not_unscoped_enum<char[]>();
    test_is_not_unscoped_enum<char* [3]>();
    test_is_not_unscoped_enum<char*[]>();
    test_is_not_unscoped_enum<int(*)[3]>();
    test_is_not_unscoped_enum<int(*)[]>();
    test_is_not_unscoped_enum<int(&)[3]>();
    test_is_not_unscoped_enum<int(&)[]>();
    test_is_not_unscoped_enum<int(&&)[3]>();
    test_is_not_unscoped_enum<int(&&)[]>();
    test_is_not_unscoped_enum<char[3][2]>();
    test_is_not_unscoped_enum<char[][2]>();
    test_is_not_unscoped_enum<char* [3][2]>();
    test_is_not_unscoped_enum<char*[][2]>();
    test_is_not_unscoped_enum<int(*)[3][2]>();
    test_is_not_unscoped_enum<int(*)[][2]>();
    test_is_not_unscoped_enum<int(&)[3][2]>();
    test_is_not_unscoped_enum<int(&)[][2]>();
    test_is_not_unscoped_enum<int(&&)[3][2]>();
    test_is_not_unscoped_enum<int(&&)[][2]>();
    test_is_not_unscoped_enum<Class>();
    test_is_not_unscoped_enum<Class[]>();
    test_is_not_unscoped_enum<Class[2]>();
    test_is_not_unscoped_enum<Template<void>>();
    test_is_not_unscoped_enum<Template<int>>();
    test_is_not_unscoped_enum<Template<Class>>();
    test_is_not_unscoped_enum<Template<IncompleteType>>();
    test_is_not_unscoped_enum<VariadicTemplate<>>();
    test_is_not_unscoped_enum<VariadicTemplate<void>>();
    test_is_not_unscoped_enum<VariadicTemplate<int>>();
    test_is_not_unscoped_enum<VariadicTemplate<Class>>();
    test_is_not_unscoped_enum<VariadicTemplate<IncompleteType>>();
    test_is_not_unscoped_enum<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unscoped_enum<PublicDerivedFromTemplate<Base>>();
    test_is_not_unscoped_enum<PublicDerivedFromTemplate<Derived>>();
    test_is_not_unscoped_enum<PublicDerivedFromTemplate<Class>>();
    test_is_not_unscoped_enum<PrivateDerivedFromTemplate<Base>>();
    test_is_not_unscoped_enum<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_unscoped_enum<PrivateDerivedFromTemplate<Class>>();
    test_is_not_unscoped_enum<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_unscoped_enum<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_unscoped_enum<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_unscoped_enum<Union>();
    test_is_not_unscoped_enum<NonEmptyUnion>();
    test_is_not_unscoped_enum<Empty>();
    test_is_not_unscoped_enum<NotEmpty>();
    test_is_not_unscoped_enum<BitZero>();
    test_is_not_unscoped_enum<BitOne>();
    test_is_not_unscoped_enum<Base>();
    test_is_not_unscoped_enum<Derived>();
    test_is_not_unscoped_enum<Abstract>();
    test_is_not_unscoped_enum<PublicAbstract>();
    test_is_not_unscoped_enum<PrivateAbstract>();
    test_is_not_unscoped_enum<ProtectedAbstract>();
    test_is_not_unscoped_enum<AbstractTemplate<int>>();
    test_is_not_unscoped_enum<AbstractTemplate<double>>();
    test_is_not_unscoped_enum<AbstractTemplate<Class>>();
    test_is_not_unscoped_enum<AbstractTemplate<IncompleteType>>();
    test_is_not_unscoped_enum<Final>();
    test_is_not_unscoped_enum<PublicDestructor>();
    test_is_not_unscoped_enum<ProtectedDestructor>();
    test_is_not_unscoped_enum<PrivateDestructor>();
    test_is_not_unscoped_enum<VirtualPublicDestructor>();
    test_is_not_unscoped_enum<VirtualProtectedDestructor>();
    test_is_not_unscoped_enum<VirtualPrivateDestructor>();
    test_is_not_unscoped_enum<PurePublicDestructor>();
    test_is_not_unscoped_enum<PureProtectedDestructor>();
    test_is_not_unscoped_enum<PurePrivateDestructor>();
    test_is_not_unscoped_enum<DeletedPublicDestructor>();
    test_is_not_unscoped_enum<DeletedProtectedDestructor>();
    test_is_not_unscoped_enum<DeletedPrivateDestructor>();
    test_is_not_unscoped_enum<DeletedVirtualPublicDestructor>();
    test_is_not_unscoped_enum<DeletedVirtualProtectedDestructor>();
    test_is_not_unscoped_enum<DeletedVirtualPrivateDestructor>();
    test_is_unscoped_enum<Enum>();
    test_is_unscoped_enum<EnumSigned>();
    test_is_unscoped_enum<EnumUnsigned>();
    test_is_not_unscoped_enum<EnumClass>();
    test_is_not_unscoped_enum<EnumStruct>();
    test_is_not_unscoped_enum<Function>();
    test_is_not_unscoped_enum<FunctionPtr>();
    test_is_not_unscoped_enum<MemberObjectPtr>();
    test_is_not_unscoped_enum<MemberFunctionPtr>();
    test_is_not_unscoped_enum<IncompleteType>();
    test_is_not_unscoped_enum<IncompleteTemplate<void>>();
    test_is_not_unscoped_enum<IncompleteTemplate<int>>();
    test_is_not_unscoped_enum<IncompleteTemplate<Class>>();
    test_is_not_unscoped_enum<IncompleteTemplate<IncompleteType>>();
    test_is_not_unscoped_enum<IncompleteVariadicTemplate<>>();
    test_is_not_unscoped_enum<IncompleteVariadicTemplate<void>>();
    test_is_not_unscoped_enum<IncompleteVariadicTemplate<int>>();
    test_is_not_unscoped_enum<IncompleteVariadicTemplate<Class>>();
    test_is_not_unscoped_enum<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_unscoped_enum<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unscoped_enum<int Class::*>();
    test_is_not_unscoped_enum<float Class::*>();
    test_is_not_unscoped_enum<void * Class::*>();
    test_is_not_unscoped_enum<int * Class::*>();
    test_is_not_unscoped_enum<int Class::*&>();
    test_is_not_unscoped_enum<float Class::*&>();
    test_is_not_unscoped_enum<void * Class::*&>();
    test_is_not_unscoped_enum<int * Class::*&>();
    test_is_not_unscoped_enum<int Class::*&&>();
    test_is_not_unscoped_enum<float Class::*&&>();
    test_is_not_unscoped_enum<void * Class::*&&>();
    test_is_not_unscoped_enum<int * Class::*&&>();
    test_is_not_unscoped_enum<int Class::*const>();
    test_is_not_unscoped_enum<float Class::*const>();
    test_is_not_unscoped_enum<void * Class::*const>();
    test_is_not_unscoped_enum<int Class::*const&>();
    test_is_not_unscoped_enum<float Class::*const&>();
    test_is_not_unscoped_enum<void * Class::*const&>();
    test_is_not_unscoped_enum<int Class::*const&&>();
    test_is_not_unscoped_enum<float Class::*const&&>();
    test_is_not_unscoped_enum<void * Class::*const&&>();
    test_is_not_unscoped_enum<int Class::*volatile>();
    test_is_not_unscoped_enum<float Class::*volatile>();
    test_is_not_unscoped_enum<void * Class::*volatile>();
    test_is_not_unscoped_enum<int Class::*volatile&>();
    test_is_not_unscoped_enum<float Class::*volatile&>();
    test_is_not_unscoped_enum<void * Class::*volatile&>();
    test_is_not_unscoped_enum<int Class::*volatile&&>();
    test_is_not_unscoped_enum<float Class::*volatile&&>();
    test_is_not_unscoped_enum<void * Class::*volatile&&>();
    test_is_not_unscoped_enum<int Class::*const volatile>();
    test_is_not_unscoped_enum<float Class::*const volatile>();
    test_is_not_unscoped_enum<void * Class::*const volatile>();
    test_is_not_unscoped_enum<int Class::*const volatile&>();
    test_is_not_unscoped_enum<float Class::*const volatile&>();
    test_is_not_unscoped_enum<void * Class::*const volatile&>();
    test_is_not_unscoped_enum<int Class::*const volatile&&>();
    test_is_not_unscoped_enum<float Class::*const volatile&&>();
    test_is_not_unscoped_enum<void * Class::*const volatile&&>();
    test_is_not_unscoped_enum<NonCopyable>();
    test_is_not_unscoped_enum<NonMoveable>();
    test_is_not_unscoped_enum<NonConstructible>();
    test_is_not_unscoped_enum<Tracked>();
    test_is_not_unscoped_enum<TrapConstructible>();
    test_is_not_unscoped_enum<TrapImplicitConversion>();
    test_is_not_unscoped_enum<TrapComma>();
    test_is_not_unscoped_enum<TrapCall>();
    test_is_not_unscoped_enum<TrapSelfAssign>();
    test_is_not_unscoped_enum<TrapDeref>();
    test_is_not_unscoped_enum<TrapArraySubscript>();

    test_is_not_unscoped_enum<void()>();
    test_is_not_unscoped_enum<void()&>();
    test_is_not_unscoped_enum<void() &&>();
    test_is_not_unscoped_enum<void() const>();
    test_is_not_unscoped_enum<void() const&>();
    test_is_not_unscoped_enum<void() const&&>();
    test_is_not_unscoped_enum<void() volatile>();
    test_is_not_unscoped_enum<void() volatile&>();
    test_is_not_unscoped_enum<void() volatile&&>();
    test_is_not_unscoped_enum<void() const volatile>();
    test_is_not_unscoped_enum<void() const volatile&>();
    test_is_not_unscoped_enum<void() const volatile&&>();
    test_is_not_unscoped_enum<void() noexcept>();
    test_is_not_unscoped_enum<void()& noexcept>();
    test_is_not_unscoped_enum<void()&& noexcept>();
    test_is_not_unscoped_enum<void() const noexcept>();
    test_is_not_unscoped_enum<void() const& noexcept>();
    test_is_not_unscoped_enum<void() const&& noexcept>();
    test_is_not_unscoped_enum<void() volatile noexcept>();
    test_is_not_unscoped_enum<void() volatile& noexcept>();
    test_is_not_unscoped_enum<void() volatile&& noexcept>();
    test_is_not_unscoped_enum<void() const volatile noexcept>();
    test_is_not_unscoped_enum<void() const volatile& noexcept>();
    test_is_not_unscoped_enum<void() const volatile&& noexcept>();

    test_is_not_unscoped_enum<void(int)>();
    test_is_not_unscoped_enum<void(int)&>();
    test_is_not_unscoped_enum<void(int) &&>();
    test_is_not_unscoped_enum<void(int) const>();
    test_is_not_unscoped_enum<void(int) const&>();
    test_is_not_unscoped_enum<void(int) const&&>();
    test_is_not_unscoped_enum<void(int) volatile>();
    test_is_not_unscoped_enum<void(int) volatile&>();
    test_is_not_unscoped_enum<void(int) volatile&&>();
    test_is_not_unscoped_enum<void(int) const volatile>();
    test_is_not_unscoped_enum<void(int) const volatile&>();
    test_is_not_unscoped_enum<void(int) const volatile&&>();
    test_is_not_unscoped_enum<void(int) noexcept>();
    test_is_not_unscoped_enum<void(int)& noexcept>();
    test_is_not_unscoped_enum<void(int)&& noexcept>();
    test_is_not_unscoped_enum<void(int) const noexcept>();
    test_is_not_unscoped_enum<void(int) const& noexcept>();
    test_is_not_unscoped_enum<void(int) const&& noexcept>();
    test_is_not_unscoped_enum<void(int) volatile noexcept>();
    test_is_not_unscoped_enum<void(int) volatile& noexcept>();
    test_is_not_unscoped_enum<void(int) volatile&& noexcept>();
    test_is_not_unscoped_enum<void(int) const volatile noexcept>();
    test_is_not_unscoped_enum<void(int) const volatile& noexcept>();
    test_is_not_unscoped_enum<void(int) const volatile&& noexcept>();

    test_is_not_unscoped_enum<void(...)>();
    test_is_not_unscoped_enum<void(...)&>();
    test_is_not_unscoped_enum<void(...) &&>();
    test_is_not_unscoped_enum<void(...) const>();
    test_is_not_unscoped_enum<void(...) const&>();
    test_is_not_unscoped_enum<void(...) const&&>();
    test_is_not_unscoped_enum<void(...) volatile>();
    test_is_not_unscoped_enum<void(...) volatile&>();
    test_is_not_unscoped_enum<void(...) volatile&&>();
    test_is_not_unscoped_enum<void(...) const volatile>();
    test_is_not_unscoped_enum<void(...) const volatile&>();
    test_is_not_unscoped_enum<void(...) const volatile&&>();
    test_is_not_unscoped_enum<void(...) noexcept>();
    test_is_not_unscoped_enum<void(...)& noexcept>();
    test_is_not_unscoped_enum<void(...)&& noexcept>();
    test_is_not_unscoped_enum<void(...) const noexcept>();
    test_is_not_unscoped_enum<void(...) const& noexcept>();
    test_is_not_unscoped_enum<void(...) const&& noexcept>();
    test_is_not_unscoped_enum<void(...) volatile noexcept>();
    test_is_not_unscoped_enum<void(...) volatile& noexcept>();
    test_is_not_unscoped_enum<void(...) volatile&& noexcept>();
    test_is_not_unscoped_enum<void(...) const volatile noexcept>();
    test_is_not_unscoped_enum<void(...) const volatile& noexcept>();
    test_is_not_unscoped_enum<void(...) const volatile&& noexcept>();

    test_is_not_unscoped_enum<void(int, ...)>();
    test_is_not_unscoped_enum<void(int, ...)&>();
    test_is_not_unscoped_enum<void(int, ...) &&>();
    test_is_not_unscoped_enum<void(int, ...) const>();
    test_is_not_unscoped_enum<void(int, ...) const&>();
    test_is_not_unscoped_enum<void(int, ...) const&&>();
    test_is_not_unscoped_enum<void(int, ...) volatile>();
    test_is_not_unscoped_enum<void(int, ...) volatile&>();
    test_is_not_unscoped_enum<void(int, ...) volatile&&>();
    test_is_not_unscoped_enum<void(int, ...) const volatile>();
    test_is_not_unscoped_enum<void(int, ...) const volatile&>();
    test_is_not_unscoped_enum<void(int, ...) const volatile&&>();
    test_is_not_unscoped_enum<void(int, ...) noexcept>();
    test_is_not_unscoped_enum<void(int, ...)& noexcept>();
    test_is_not_unscoped_enum<void(int, ...)&& noexcept>();
    test_is_not_unscoped_enum<void(int, ...) const noexcept>();
    test_is_not_unscoped_enum<void(int, ...) const& noexcept>();
    test_is_not_unscoped_enum<void(int, ...) const&& noexcept>();
    test_is_not_unscoped_enum<void(int, ...) volatile noexcept>();
    test_is_not_unscoped_enum<void(int, ...) volatile& noexcept>();
    test_is_not_unscoped_enum<void(int, ...) volatile&& noexcept>();
    test_is_not_unscoped_enum<void(int, ...) const volatile noexcept>();
    test_is_not_unscoped_enum<void(int, ...) const volatile& noexcept>();
    test_is_not_unscoped_enum<void(int, ...) const volatile&& noexcept>();

    test_is_not_unscoped_enum<int()>();
    test_is_not_unscoped_enum<int()&>();
    test_is_not_unscoped_enum<int() &&>();
    test_is_not_unscoped_enum<int() const>();
    test_is_not_unscoped_enum<int() const&>();
    test_is_not_unscoped_enum<int() const&&>();
    test_is_not_unscoped_enum<int() volatile>();
    test_is_not_unscoped_enum<int() volatile&>();
    test_is_not_unscoped_enum<int() volatile&&>();
    test_is_not_unscoped_enum<int() const volatile>();
    test_is_not_unscoped_enum<int() const volatile&>();
    test_is_not_unscoped_enum<int() const volatile&&>();
    test_is_not_unscoped_enum<int() noexcept>();
    test_is_not_unscoped_enum<int()& noexcept>();
    test_is_not_unscoped_enum<int()&& noexcept>();
    test_is_not_unscoped_enum<int() const noexcept>();
    test_is_not_unscoped_enum<int() const& noexcept>();
    test_is_not_unscoped_enum<int() const&& noexcept>();
    test_is_not_unscoped_enum<int() volatile noexcept>();
    test_is_not_unscoped_enum<int() volatile& noexcept>();
    test_is_not_unscoped_enum<int() volatile&& noexcept>();
    test_is_not_unscoped_enum<int() const volatile noexcept>();
    test_is_not_unscoped_enum<int() const volatile& noexcept>();
    test_is_not_unscoped_enum<int() const volatile&& noexcept>();

    test_is_not_unscoped_enum<int(int)>();
    test_is_not_unscoped_enum<int(int)&>();
    test_is_not_unscoped_enum<int(int) &&>();
    test_is_not_unscoped_enum<int(int) const>();
    test_is_not_unscoped_enum<int(int) const&>();
    test_is_not_unscoped_enum<int(int) const&&>();
    test_is_not_unscoped_enum<int(int) volatile>();
    test_is_not_unscoped_enum<int(int) volatile&>();
    test_is_not_unscoped_enum<int(int) volatile&&>();
    test_is_not_unscoped_enum<int(int) const volatile>();
    test_is_not_unscoped_enum<int(int) const volatile&>();
    test_is_not_unscoped_enum<int(int) const volatile&&>();
    test_is_not_unscoped_enum<int(int) noexcept>();
    test_is_not_unscoped_enum<int(int)& noexcept>();
    test_is_not_unscoped_enum<int(int)&& noexcept>();
    test_is_not_unscoped_enum<int(int) const noexcept>();
    test_is_not_unscoped_enum<int(int) const& noexcept>();
    test_is_not_unscoped_enum<int(int) const&& noexcept>();
    test_is_not_unscoped_enum<int(int) volatile noexcept>();
    test_is_not_unscoped_enum<int(int) volatile& noexcept>();
    test_is_not_unscoped_enum<int(int) volatile&& noexcept>();
    test_is_not_unscoped_enum<int(int) const volatile noexcept>();
    test_is_not_unscoped_enum<int(int) const volatile& noexcept>();
    test_is_not_unscoped_enum<int(int) const volatile&& noexcept>();

    test_is_not_unscoped_enum<int(...)>();
    test_is_not_unscoped_enum<int(...)&>();
    test_is_not_unscoped_enum<int(...) &&>();
    test_is_not_unscoped_enum<int(...) const>();
    test_is_not_unscoped_enum<int(...) const&>();
    test_is_not_unscoped_enum<int(...) const&&>();
    test_is_not_unscoped_enum<int(...) volatile>();
    test_is_not_unscoped_enum<int(...) volatile&>();
    test_is_not_unscoped_enum<int(...) volatile&&>();
    test_is_not_unscoped_enum<int(...) const volatile>();
    test_is_not_unscoped_enum<int(...) const volatile&>();
    test_is_not_unscoped_enum<int(...) const volatile&&>();
    test_is_not_unscoped_enum<int(...) noexcept>();
    test_is_not_unscoped_enum<int(...)& noexcept>();
    test_is_not_unscoped_enum<int(...)&& noexcept>();
    test_is_not_unscoped_enum<int(...) const noexcept>();
    test_is_not_unscoped_enum<int(...) const& noexcept>();
    test_is_not_unscoped_enum<int(...) const&& noexcept>();
    test_is_not_unscoped_enum<int(...) volatile noexcept>();
    test_is_not_unscoped_enum<int(...) volatile& noexcept>();
    test_is_not_unscoped_enum<int(...) volatile&& noexcept>();
    test_is_not_unscoped_enum<int(...) const volatile noexcept>();
    test_is_not_unscoped_enum<int(...) const volatile& noexcept>();
    test_is_not_unscoped_enum<int(...) const volatile&& noexcept>();

    test_is_not_unscoped_enum<int(int, ...)>();
    test_is_not_unscoped_enum<int(int, ...)&>();
    test_is_not_unscoped_enum<int(int, ...) &&>();
    test_is_not_unscoped_enum<int(int, ...) const>();
    test_is_not_unscoped_enum<int(int, ...) const&>();
    test_is_not_unscoped_enum<int(int, ...) const&&>();
    test_is_not_unscoped_enum<int(int, ...) volatile>();
    test_is_not_unscoped_enum<int(int, ...) volatile&>();
    test_is_not_unscoped_enum<int(int, ...) volatile&&>();
    test_is_not_unscoped_enum<int(int, ...) const volatile>();
    test_is_not_unscoped_enum<int(int, ...) const volatile&>();
    test_is_not_unscoped_enum<int(int, ...) const volatile&&>();
    test_is_not_unscoped_enum<int(int, ...) noexcept>();
    test_is_not_unscoped_enum<int(int, ...)& noexcept>();
    test_is_not_unscoped_enum<int(int, ...)&& noexcept>();
    test_is_not_unscoped_enum<int(int, ...) const noexcept>();
    test_is_not_unscoped_enum<int(int, ...) const& noexcept>();
    test_is_not_unscoped_enum<int(int, ...) const&& noexcept>();
    test_is_not_unscoped_enum<int(int, ...) volatile noexcept>();
    test_is_not_unscoped_enum<int(int, ...) volatile& noexcept>();
    test_is_not_unscoped_enum<int(int, ...) volatile&& noexcept>();
    test_is_not_unscoped_enum<int(int, ...) const volatile noexcept>();
    test_is_not_unscoped_enum<int(int, ...) const volatile& noexcept>();
    test_is_not_unscoped_enum<int(int, ...) const volatile&& noexcept>();

    test_is_not_unscoped_enum<void (*)()>();
    test_is_not_unscoped_enum<void (*)() noexcept>();

    test_is_not_unscoped_enum<void (*)(int)>();
    test_is_not_unscoped_enum<void (*)(int) noexcept>();

    test_is_not_unscoped_enum<void (*)(...)>();
    test_is_not_unscoped_enum<void (*)(...) noexcept>();

    test_is_not_unscoped_enum<void (*)(int, ...)>();
    test_is_not_unscoped_enum<void (*)(int, ...) noexcept>();

    test_is_not_unscoped_enum<int (*)()>();
    test_is_not_unscoped_enum<int (*)() noexcept>();

    test_is_not_unscoped_enum<int (*)(int)>();
    test_is_not_unscoped_enum<int (*)(int) noexcept>();

    test_is_not_unscoped_enum<int (*)(...)>();
    test_is_not_unscoped_enum<int (*)(...) noexcept>();

    test_is_not_unscoped_enum<int (*)(int, ...)>();
    test_is_not_unscoped_enum<int (*)(int, ...) noexcept>();

    test_is_not_unscoped_enum<void (&)()>();
    test_is_not_unscoped_enum<void (&)() noexcept>();

    test_is_not_unscoped_enum<void (&)(int)>();
    test_is_not_unscoped_enum<void (&)(int) noexcept>();

    test_is_not_unscoped_enum<void (&)(...)>();
    test_is_not_unscoped_enum<void (&)(...) noexcept>();

    test_is_not_unscoped_enum<void (&)(int, ...)>();
    test_is_not_unscoped_enum<void (&)(int, ...) noexcept>();

    test_is_not_unscoped_enum<int (&)()>();
    test_is_not_unscoped_enum<int (&)() noexcept>();

    test_is_not_unscoped_enum<int (&)(int)>();
    test_is_not_unscoped_enum<int (&)(int) noexcept>();

    test_is_not_unscoped_enum<int (&)(...)>();
    test_is_not_unscoped_enum<int (&)(...) noexcept>();

    test_is_not_unscoped_enum<int (&)(int, ...)>();
    test_is_not_unscoped_enum<int (&)(int, ...) noexcept>();

    test_is_not_unscoped_enum<void(&&)()>();
    test_is_not_unscoped_enum<void(&&)() noexcept>();

    test_is_not_unscoped_enum<void(&&)(int)>();
    test_is_not_unscoped_enum<void(&&)(int) noexcept>();

    test_is_not_unscoped_enum<void(&&)(...)>();
    test_is_not_unscoped_enum<void(&&)(...) noexcept>();

    test_is_not_unscoped_enum<void(&&)(int, ...)>();
    test_is_not_unscoped_enum<void(&&)(int, ...) noexcept>();

    test_is_not_unscoped_enum<int(&&)()>();
    test_is_not_unscoped_enum<int(&&)() noexcept>();

    test_is_not_unscoped_enum<int(&&)(int)>();
    test_is_not_unscoped_enum<int(&&)(int) noexcept>();

    test_is_not_unscoped_enum<int(&&)(...)>();
    test_is_not_unscoped_enum<int(&&)(...) noexcept>();

    test_is_not_unscoped_enum<int(&&)(int, ...)>();
    test_is_not_unscoped_enum<int(&&)(int, ...) noexcept>();

    test_is_not_unscoped_enum<void (Class::*)()>();
    test_is_not_unscoped_enum<void (Class::*)()&>();
    test_is_not_unscoped_enum<void (Class::*)() &&>();
    test_is_not_unscoped_enum<void (Class::*)() const>();
    test_is_not_unscoped_enum<void (Class::*)() const&>();
    test_is_not_unscoped_enum<void (Class::*)() const&&>();
    test_is_not_unscoped_enum<void (Class::*)() noexcept>();
    test_is_not_unscoped_enum<void (Class::*)()& noexcept>();
    test_is_not_unscoped_enum<void (Class::*)()&& noexcept>();
    test_is_not_unscoped_enum<void (Class::*)() const noexcept>();
    test_is_not_unscoped_enum<void (Class::*)() const& noexcept>();
    test_is_not_unscoped_enum<void (Class::*)() const&& noexcept>();

    test_is_not_unscoped_enum<void (Class::*)(int)>();
    test_is_not_unscoped_enum<void (Class::*)(int)&>();
    test_is_not_unscoped_enum<void (Class::*)(int) &&>();
    test_is_not_unscoped_enum<void (Class::*)(int) const>();
    test_is_not_unscoped_enum<void (Class::*)(int) const&>();
    test_is_not_unscoped_enum<void (Class::*)(int) const&&>();
    test_is_not_unscoped_enum<void (Class::*)(int) noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(int)& noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(int)&& noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(int) const noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(int) const& noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(int) const&& noexcept>();

    test_is_not_unscoped_enum<void (Class::*)(...)>();
    test_is_not_unscoped_enum<void (Class::*)(...)&>();
    test_is_not_unscoped_enum<void (Class::*)(...) &&>();
    test_is_not_unscoped_enum<void (Class::*)(...) const>();
    test_is_not_unscoped_enum<void (Class::*)(...) const&>();
    test_is_not_unscoped_enum<void (Class::*)(...) const&&>();
    test_is_not_unscoped_enum<void (Class::*)(...) noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(...)& noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(...)&& noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(...) const noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(...) const& noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(...) const&& noexcept>();

    test_is_not_unscoped_enum<void (Class::*)(int, ...)>();
    test_is_not_unscoped_enum<void (Class::*)(int, ...)&>();
    test_is_not_unscoped_enum<void (Class::*)(int, ...) &&>();
    test_is_not_unscoped_enum<void (Class::*)(int, ...) const>();
    test_is_not_unscoped_enum<void (Class::*)(int, ...) const&>();
    test_is_not_unscoped_enum<void (Class::*)(int, ...) const&&>();
    test_is_not_unscoped_enum<void (Class::*)(int, ...) noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(int, ...)& noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(int, ...) const noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_unscoped_enum<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_unscoped_enum<int (Class::*)()>();
    test_is_not_unscoped_enum<int (Class::*)()&>();
    test_is_not_unscoped_enum<int (Class::*)() &&>();
    test_is_not_unscoped_enum<int (Class::*)() const>();
    test_is_not_unscoped_enum<int (Class::*)() const&>();
    test_is_not_unscoped_enum<int (Class::*)() const&&>();
    test_is_not_unscoped_enum<int (Class::*)() noexcept>();
    test_is_not_unscoped_enum<int (Class::*)()& noexcept>();
    test_is_not_unscoped_enum<int (Class::*)()&& noexcept>();
    test_is_not_unscoped_enum<int (Class::*)() const noexcept>();
    test_is_not_unscoped_enum<int (Class::*)() const& noexcept>();
    test_is_not_unscoped_enum<int (Class::*)() const&& noexcept>();

    test_is_not_unscoped_enum<int (Class::*)(int)>();
    test_is_not_unscoped_enum<int (Class::*)(int)&>();
    test_is_not_unscoped_enum<int (Class::*)(int) &&>();
    test_is_not_unscoped_enum<int (Class::*)(int) const>();
    test_is_not_unscoped_enum<int (Class::*)(int) const&>();
    test_is_not_unscoped_enum<int (Class::*)(int) const&&>();
    test_is_not_unscoped_enum<int (Class::*)(int) noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(int)& noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(int)&& noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(int) const noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(int) const& noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(int) const&& noexcept>();

    test_is_not_unscoped_enum<int (Class::*)(...)>();
    test_is_not_unscoped_enum<int (Class::*)(...)&>();
    test_is_not_unscoped_enum<int (Class::*)(...) &&>();
    test_is_not_unscoped_enum<int (Class::*)(...) const>();
    test_is_not_unscoped_enum<int (Class::*)(...) const&>();
    test_is_not_unscoped_enum<int (Class::*)(...) const&&>();
    test_is_not_unscoped_enum<int (Class::*)(...) noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(...)& noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(...)&& noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(...) const noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(...) const& noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(...) const&& noexcept>();

    test_is_not_unscoped_enum<int (Class::*)(int, ...)>();
    test_is_not_unscoped_enum<int (Class::*)(int, ...)&>();
    test_is_not_unscoped_enum<int (Class::*)(int, ...) &&>();
    test_is_not_unscoped_enum<int (Class::*)(int, ...) const>();
    test_is_not_unscoped_enum<int (Class::*)(int, ...) const&>();
    test_is_not_unscoped_enum<int (Class::*)(int, ...) const&&>();
    test_is_not_unscoped_enum<int (Class::*)(int, ...) noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(int, ...)& noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(int, ...) const noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_unscoped_enum<int (Class::*)(int, ...) const&& noexcept>();
}
