#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_polymorphic.hpp>
#include <phi/type_traits/is_union.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_polymorphic_impl()
{
    STATIC_REQUIRE(phi::is_polymorphic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_polymorphic<T>::value);
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
#endif

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_polymorphic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_polymorphic_v<T>);
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
#    endif
#endif

    // Standard compatibililty
    STATIC_REQUIRE(std::is_polymorphic<T>::value);
}

template <typename T>
void test_is_not_polymorphic_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_polymorphic<T>::value);
    STATIC_REQUIRE(phi::is_not_polymorphic<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_polymorphic_v<T>);
    STATIC_REQUIRE(phi::is_not_polymorphic_v<T>);
#endif

    // Standard compatibililty
    STATIC_REQUIRE_FALSE(std::is_polymorphic<T>::value);
}

template <typename T>
void test_is_polymorphic()
{
    test_is_polymorphic_impl<T>();
    test_is_polymorphic_impl<const T>();
    test_is_polymorphic_impl<volatile T>();
    test_is_polymorphic_impl<const volatile T>();
}

template <typename T>
void test_is_not_polymorphic()
{
    test_is_not_polymorphic_impl<T>();
    test_is_not_polymorphic_impl<const T>();
    test_is_not_polymorphic_impl<volatile T>();
    test_is_not_polymorphic_impl<const volatile T>();
}

TEST_CASE("is_polymorphic")
{
    test_is_not_polymorphic<NotEmpty&>();
    test_is_not_polymorphic<NotEmpty&&>();
    test_is_not_polymorphic<Abstract&>();
    test_is_not_polymorphic<Abstract&&>();

    test_is_not_polymorphic<void>();
    test_is_not_polymorphic<phi::nullptr_t>();
    test_is_not_polymorphic<bool>();
    test_is_not_polymorphic<char>();
    test_is_not_polymorphic<signed char>();
    test_is_not_polymorphic<unsigned char>();
    test_is_not_polymorphic<short>();
    test_is_not_polymorphic<unsigned short>();
    test_is_not_polymorphic<int>();
    test_is_not_polymorphic<unsigned int>();
    test_is_not_polymorphic<long>();
    test_is_not_polymorphic<unsigned long>();
    test_is_not_polymorphic<long long>();
    test_is_not_polymorphic<unsigned long long>();
    test_is_not_polymorphic<float>();
    test_is_not_polymorphic<double>();
    test_is_not_polymorphic<long double>();
    test_is_not_polymorphic<char8_t>();
    test_is_not_polymorphic<char16_t>();
    test_is_not_polymorphic<char32_t>();
    test_is_not_polymorphic<wchar_t>();

    test_is_not_polymorphic<phi::boolean>();
    test_is_not_polymorphic<phi::integer<signed char>>();
    test_is_not_polymorphic<phi::integer<unsigned char>>();
    test_is_not_polymorphic<phi::integer<short>>();
    test_is_not_polymorphic<phi::integer<unsigned short>>();
    test_is_not_polymorphic<phi::integer<int>>();
    test_is_not_polymorphic<phi::integer<unsigned int>>();
    test_is_not_polymorphic<phi::integer<long>>();
    test_is_not_polymorphic<phi::integer<unsigned long>>();
    test_is_not_polymorphic<phi::integer<long long>>();
    test_is_not_polymorphic<phi::integer<unsigned long long>>();
    test_is_not_polymorphic<phi::floating_point<float>>();
    test_is_not_polymorphic<phi::floating_point<double>>();
    test_is_not_polymorphic<phi::floating_point<long double>>();

    test_is_not_polymorphic<std::vector<int>>();
    test_is_not_polymorphic<phi::scope_ptr<int>>();

    test_is_not_polymorphic<int&>();
    test_is_not_polymorphic<const int&>();
    test_is_not_polymorphic<volatile int&>();
    test_is_not_polymorphic<const volatile int&>();
    test_is_not_polymorphic<int&&>();
    test_is_not_polymorphic<const int&&>();
    test_is_not_polymorphic<volatile int&&>();
    test_is_not_polymorphic<const volatile int&&>();
    test_is_not_polymorphic<int*>();
    test_is_not_polymorphic<const int*>();
    test_is_not_polymorphic<volatile int*>();
    test_is_not_polymorphic<const volatile int*>();
    test_is_not_polymorphic<int**>();
    test_is_not_polymorphic<const int**>();
    test_is_not_polymorphic<volatile int**>();
    test_is_not_polymorphic<const volatile int**>();
    test_is_not_polymorphic<int*&>();
    test_is_not_polymorphic<const int*&>();
    test_is_not_polymorphic<volatile int*&>();
    test_is_not_polymorphic<const volatile int*&>();
    test_is_not_polymorphic<int*&&>();
    test_is_not_polymorphic<const int*&&>();
    test_is_not_polymorphic<volatile int*&&>();
    test_is_not_polymorphic<const volatile int*&&>();
    test_is_not_polymorphic<void*>();
    test_is_not_polymorphic<char[3]>();
    test_is_not_polymorphic<char[]>();
    test_is_not_polymorphic<char* [3]>();
    test_is_not_polymorphic<char*[]>();
    test_is_not_polymorphic<int(*)[3]>();
    test_is_not_polymorphic<int(*)[]>();
    test_is_not_polymorphic<int(&)[3]>();
    test_is_not_polymorphic<int(&)[]>();
    test_is_not_polymorphic<int(&&)[3]>();
    test_is_not_polymorphic<int(&&)[]>();
    test_is_not_polymorphic<char[3][2]>();
    test_is_not_polymorphic<char[][2]>();
    test_is_not_polymorphic<char* [3][2]>();
    test_is_not_polymorphic<char*[][2]>();
    test_is_not_polymorphic<int(*)[3][2]>();
    test_is_not_polymorphic<int(*)[][2]>();
    test_is_not_polymorphic<int(&)[3][2]>();
    test_is_not_polymorphic<int(&)[][2]>();
    test_is_not_polymorphic<int(&&)[3][2]>();
    test_is_not_polymorphic<int(&&)[][2]>();
    test_is_not_polymorphic<Class>();
    test_is_not_polymorphic<Class[]>();
    test_is_not_polymorphic<Class[2]>();
    test_is_not_polymorphic<Template<void>>();
    test_is_not_polymorphic<Template<int>>();
    test_is_not_polymorphic<Template<Class>>();
    test_is_not_polymorphic<Template<IncompleteType>>();
    test_is_not_polymorphic<VariadicTemplate<>>();
    test_is_not_polymorphic<VariadicTemplate<void>>();
    test_is_not_polymorphic<VariadicTemplate<int>>();
    test_is_not_polymorphic<VariadicTemplate<Class>>();
    test_is_not_polymorphic<VariadicTemplate<IncompleteType>>();
    test_is_not_polymorphic<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_polymorphic<PublicDerivedFromTemplate<Base>>();
    test_is_not_polymorphic<PublicDerivedFromTemplate<Derived>>();
    test_is_not_polymorphic<PublicDerivedFromTemplate<Class>>();
    test_is_not_polymorphic<PrivateDerivedFromTemplate<Base>>();
    test_is_not_polymorphic<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_polymorphic<PrivateDerivedFromTemplate<Class>>();
    test_is_not_polymorphic<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_polymorphic<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_polymorphic<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_polymorphic<Union>();
    test_is_not_polymorphic<NonEmptyUnion>();
    test_is_not_polymorphic<Empty>();
    test_is_polymorphic<NotEmpty>();
    test_is_not_polymorphic<BitZero>();
    test_is_not_polymorphic<BitOne>();
    test_is_not_polymorphic<Base>();
    test_is_not_polymorphic<Derived>();
    test_is_polymorphic<Abstract>();
    test_is_polymorphic<PublicAbstract>();
    test_is_polymorphic<PrivateAbstract>();
    test_is_polymorphic<ProtectedAbstract>();
    test_is_polymorphic<AbstractTemplate<int>>();
    test_is_not_polymorphic<AbstractTemplate<double>>();
    test_is_polymorphic<AbstractTemplate<Class>>();
    test_is_polymorphic<AbstractTemplate<IncompleteType>>();
    test_is_not_polymorphic<Final>();
    test_is_not_polymorphic<PublicDestructor>();
    test_is_not_polymorphic<ProtectedDestructor>();
    test_is_not_polymorphic<PrivateDestructor>();
    test_is_polymorphic<VirtualPublicDestructor>();
    test_is_polymorphic<VirtualProtectedDestructor>();
    test_is_polymorphic<VirtualPrivateDestructor>();
    test_is_polymorphic<PurePublicDestructor>();
    test_is_polymorphic<PureProtectedDestructor>();
    test_is_polymorphic<PurePrivateDestructor>();
    test_is_not_polymorphic<DeletedPublicDestructor>();
    test_is_not_polymorphic<DeletedProtectedDestructor>();
    test_is_not_polymorphic<DeletedPrivateDestructor>();
    test_is_polymorphic<DeletedVirtualPublicDestructor>();
    test_is_polymorphic<DeletedVirtualProtectedDestructor>();
    test_is_polymorphic<DeletedVirtualPrivateDestructor>();
    test_is_not_polymorphic<Enum>();
    test_is_not_polymorphic<EnumSigned>();
    test_is_not_polymorphic<EnumUnsigned>();
    test_is_not_polymorphic<EnumClass>();
    test_is_not_polymorphic<EnumStruct>();
    test_is_not_polymorphic<Function>();
    test_is_not_polymorphic<FunctionPtr>();
    test_is_not_polymorphic<MemberObjectPtr>();
    test_is_not_polymorphic<MemberFunctionPtr>();
    test_is_not_polymorphic<int Class::*>();
    test_is_not_polymorphic<float Class::*>();
    test_is_not_polymorphic<void * Class::*>();
    test_is_not_polymorphic<int * Class::*>();
    test_is_not_polymorphic<int Class::*&>();
    test_is_not_polymorphic<float Class::*&>();
    test_is_not_polymorphic<void * Class::*&>();
    test_is_not_polymorphic<int * Class::*&>();
    test_is_not_polymorphic<int Class::*&&>();
    test_is_not_polymorphic<float Class::*&&>();
    test_is_not_polymorphic<void * Class::*&&>();
    test_is_not_polymorphic<int * Class::*&&>();
    test_is_not_polymorphic<int Class::*const>();
    test_is_not_polymorphic<float Class::*const>();
    test_is_not_polymorphic<void * Class::*const>();
    test_is_not_polymorphic<int Class::*const&>();
    test_is_not_polymorphic<float Class::*const&>();
    test_is_not_polymorphic<void * Class::*const&>();
    test_is_not_polymorphic<int Class::*const&&>();
    test_is_not_polymorphic<float Class::*const&&>();
    test_is_not_polymorphic<void * Class::*const&&>();
    test_is_not_polymorphic<int Class::*volatile>();
    test_is_not_polymorphic<float Class::*volatile>();
    test_is_not_polymorphic<void * Class::*volatile>();
    test_is_not_polymorphic<int Class::*volatile&>();
    test_is_not_polymorphic<float Class::*volatile&>();
    test_is_not_polymorphic<void * Class::*volatile&>();
    test_is_not_polymorphic<int Class::*volatile&&>();
    test_is_not_polymorphic<float Class::*volatile&&>();
    test_is_not_polymorphic<void * Class::*volatile&&>();
    test_is_not_polymorphic<int Class::*const volatile>();
    test_is_not_polymorphic<float Class::*const volatile>();
    test_is_not_polymorphic<void * Class::*const volatile>();
    test_is_not_polymorphic<int Class::*const volatile&>();
    test_is_not_polymorphic<float Class::*const volatile&>();
    test_is_not_polymorphic<void * Class::*const volatile&>();
    test_is_not_polymorphic<int Class::*const volatile&&>();
    test_is_not_polymorphic<float Class::*const volatile&&>();
    test_is_not_polymorphic<void * Class::*const volatile&&>();
    test_is_not_polymorphic<NonCopyable>();
    test_is_not_polymorphic<NonMoveable>();
    test_is_not_polymorphic<NonConstructible>();
    test_is_not_polymorphic<Tracked>();
    test_is_not_polymorphic<TrapConstructible>();
    test_is_not_polymorphic<TrapImplicitConversion>();
    test_is_not_polymorphic<TrapComma>();
    test_is_not_polymorphic<TrapCall>();
    test_is_not_polymorphic<TrapSelfAssign>();
    test_is_not_polymorphic<TrapDeref>();
    test_is_not_polymorphic<TrapArraySubscript>();

    test_is_not_polymorphic<void()>();
    test_is_not_polymorphic<void()&>();
    test_is_not_polymorphic<void() &&>();
    test_is_not_polymorphic<void() const>();
    test_is_not_polymorphic<void() const&>();
    test_is_not_polymorphic<void() const&&>();
    test_is_not_polymorphic<void() volatile>();
    test_is_not_polymorphic<void() volatile&>();
    test_is_not_polymorphic<void() volatile&&>();
    test_is_not_polymorphic<void() const volatile>();
    test_is_not_polymorphic<void() const volatile&>();
    test_is_not_polymorphic<void() const volatile&&>();
    test_is_not_polymorphic<void() noexcept>();
    test_is_not_polymorphic<void()& noexcept>();
    test_is_not_polymorphic<void()&& noexcept>();
    test_is_not_polymorphic<void() const noexcept>();
    test_is_not_polymorphic<void() const& noexcept>();
    test_is_not_polymorphic<void() const&& noexcept>();
    test_is_not_polymorphic<void() volatile noexcept>();
    test_is_not_polymorphic<void() volatile& noexcept>();
    test_is_not_polymorphic<void() volatile&& noexcept>();
    test_is_not_polymorphic<void() const volatile noexcept>();
    test_is_not_polymorphic<void() const volatile& noexcept>();
    test_is_not_polymorphic<void() const volatile&& noexcept>();

    test_is_not_polymorphic<void(int)>();
    test_is_not_polymorphic<void(int)&>();
    test_is_not_polymorphic<void(int) &&>();
    test_is_not_polymorphic<void(int) const>();
    test_is_not_polymorphic<void(int) const&>();
    test_is_not_polymorphic<void(int) const&&>();
    test_is_not_polymorphic<void(int) volatile>();
    test_is_not_polymorphic<void(int) volatile&>();
    test_is_not_polymorphic<void(int) volatile&&>();
    test_is_not_polymorphic<void(int) const volatile>();
    test_is_not_polymorphic<void(int) const volatile&>();
    test_is_not_polymorphic<void(int) const volatile&&>();
    test_is_not_polymorphic<void(int) noexcept>();
    test_is_not_polymorphic<void(int)& noexcept>();
    test_is_not_polymorphic<void(int)&& noexcept>();
    test_is_not_polymorphic<void(int) const noexcept>();
    test_is_not_polymorphic<void(int) const& noexcept>();
    test_is_not_polymorphic<void(int) const&& noexcept>();
    test_is_not_polymorphic<void(int) volatile noexcept>();
    test_is_not_polymorphic<void(int) volatile& noexcept>();
    test_is_not_polymorphic<void(int) volatile&& noexcept>();
    test_is_not_polymorphic<void(int) const volatile noexcept>();
    test_is_not_polymorphic<void(int) const volatile& noexcept>();
    test_is_not_polymorphic<void(int) const volatile&& noexcept>();

    test_is_not_polymorphic<void(...)>();
    test_is_not_polymorphic<void(...)&>();
    test_is_not_polymorphic<void(...) &&>();
    test_is_not_polymorphic<void(...) const>();
    test_is_not_polymorphic<void(...) const&>();
    test_is_not_polymorphic<void(...) const&&>();
    test_is_not_polymorphic<void(...) volatile>();
    test_is_not_polymorphic<void(...) volatile&>();
    test_is_not_polymorphic<void(...) volatile&&>();
    test_is_not_polymorphic<void(...) const volatile>();
    test_is_not_polymorphic<void(...) const volatile&>();
    test_is_not_polymorphic<void(...) const volatile&&>();
    test_is_not_polymorphic<void(...) noexcept>();
    test_is_not_polymorphic<void(...)& noexcept>();
    test_is_not_polymorphic<void(...)&& noexcept>();
    test_is_not_polymorphic<void(...) const noexcept>();
    test_is_not_polymorphic<void(...) const& noexcept>();
    test_is_not_polymorphic<void(...) const&& noexcept>();
    test_is_not_polymorphic<void(...) volatile noexcept>();
    test_is_not_polymorphic<void(...) volatile& noexcept>();
    test_is_not_polymorphic<void(...) volatile&& noexcept>();
    test_is_not_polymorphic<void(...) const volatile noexcept>();
    test_is_not_polymorphic<void(...) const volatile& noexcept>();
    test_is_not_polymorphic<void(...) const volatile&& noexcept>();

    test_is_not_polymorphic<void(int, ...)>();
    test_is_not_polymorphic<void(int, ...)&>();
    test_is_not_polymorphic<void(int, ...) &&>();
    test_is_not_polymorphic<void(int, ...) const>();
    test_is_not_polymorphic<void(int, ...) const&>();
    test_is_not_polymorphic<void(int, ...) const&&>();
    test_is_not_polymorphic<void(int, ...) volatile>();
    test_is_not_polymorphic<void(int, ...) volatile&>();
    test_is_not_polymorphic<void(int, ...) volatile&&>();
    test_is_not_polymorphic<void(int, ...) const volatile>();
    test_is_not_polymorphic<void(int, ...) const volatile&>();
    test_is_not_polymorphic<void(int, ...) const volatile&&>();
    test_is_not_polymorphic<void(int, ...) noexcept>();
    test_is_not_polymorphic<void(int, ...)& noexcept>();
    test_is_not_polymorphic<void(int, ...)&& noexcept>();
    test_is_not_polymorphic<void(int, ...) const noexcept>();
    test_is_not_polymorphic<void(int, ...) const& noexcept>();
    test_is_not_polymorphic<void(int, ...) const&& noexcept>();
    test_is_not_polymorphic<void(int, ...) volatile noexcept>();
    test_is_not_polymorphic<void(int, ...) volatile& noexcept>();
    test_is_not_polymorphic<void(int, ...) volatile&& noexcept>();
    test_is_not_polymorphic<void(int, ...) const volatile noexcept>();
    test_is_not_polymorphic<void(int, ...) const volatile& noexcept>();
    test_is_not_polymorphic<void(int, ...) const volatile&& noexcept>();

    test_is_not_polymorphic<int()>();
    test_is_not_polymorphic<int()&>();
    test_is_not_polymorphic<int() &&>();
    test_is_not_polymorphic<int() const>();
    test_is_not_polymorphic<int() const&>();
    test_is_not_polymorphic<int() const&&>();
    test_is_not_polymorphic<int() volatile>();
    test_is_not_polymorphic<int() volatile&>();
    test_is_not_polymorphic<int() volatile&&>();
    test_is_not_polymorphic<int() const volatile>();
    test_is_not_polymorphic<int() const volatile&>();
    test_is_not_polymorphic<int() const volatile&&>();
    test_is_not_polymorphic<int() noexcept>();
    test_is_not_polymorphic<int()& noexcept>();
    test_is_not_polymorphic<int()&& noexcept>();
    test_is_not_polymorphic<int() const noexcept>();
    test_is_not_polymorphic<int() const& noexcept>();
    test_is_not_polymorphic<int() const&& noexcept>();
    test_is_not_polymorphic<int() volatile noexcept>();
    test_is_not_polymorphic<int() volatile& noexcept>();
    test_is_not_polymorphic<int() volatile&& noexcept>();
    test_is_not_polymorphic<int() const volatile noexcept>();
    test_is_not_polymorphic<int() const volatile& noexcept>();
    test_is_not_polymorphic<int() const volatile&& noexcept>();

    test_is_not_polymorphic<int(int)>();
    test_is_not_polymorphic<int(int)&>();
    test_is_not_polymorphic<int(int) &&>();
    test_is_not_polymorphic<int(int) const>();
    test_is_not_polymorphic<int(int) const&>();
    test_is_not_polymorphic<int(int) const&&>();
    test_is_not_polymorphic<int(int) volatile>();
    test_is_not_polymorphic<int(int) volatile&>();
    test_is_not_polymorphic<int(int) volatile&&>();
    test_is_not_polymorphic<int(int) const volatile>();
    test_is_not_polymorphic<int(int) const volatile&>();
    test_is_not_polymorphic<int(int) const volatile&&>();
    test_is_not_polymorphic<int(int) noexcept>();
    test_is_not_polymorphic<int(int)& noexcept>();
    test_is_not_polymorphic<int(int)&& noexcept>();
    test_is_not_polymorphic<int(int) const noexcept>();
    test_is_not_polymorphic<int(int) const& noexcept>();
    test_is_not_polymorphic<int(int) const&& noexcept>();
    test_is_not_polymorphic<int(int) volatile noexcept>();
    test_is_not_polymorphic<int(int) volatile& noexcept>();
    test_is_not_polymorphic<int(int) volatile&& noexcept>();
    test_is_not_polymorphic<int(int) const volatile noexcept>();
    test_is_not_polymorphic<int(int) const volatile& noexcept>();
    test_is_not_polymorphic<int(int) const volatile&& noexcept>();

    test_is_not_polymorphic<int(...)>();
    test_is_not_polymorphic<int(...)&>();
    test_is_not_polymorphic<int(...) &&>();
    test_is_not_polymorphic<int(...) const>();
    test_is_not_polymorphic<int(...) const&>();
    test_is_not_polymorphic<int(...) const&&>();
    test_is_not_polymorphic<int(...) volatile>();
    test_is_not_polymorphic<int(...) volatile&>();
    test_is_not_polymorphic<int(...) volatile&&>();
    test_is_not_polymorphic<int(...) const volatile>();
    test_is_not_polymorphic<int(...) const volatile&>();
    test_is_not_polymorphic<int(...) const volatile&&>();
    test_is_not_polymorphic<int(...) noexcept>();
    test_is_not_polymorphic<int(...)& noexcept>();
    test_is_not_polymorphic<int(...)&& noexcept>();
    test_is_not_polymorphic<int(...) const noexcept>();
    test_is_not_polymorphic<int(...) const& noexcept>();
    test_is_not_polymorphic<int(...) const&& noexcept>();
    test_is_not_polymorphic<int(...) volatile noexcept>();
    test_is_not_polymorphic<int(...) volatile& noexcept>();
    test_is_not_polymorphic<int(...) volatile&& noexcept>();
    test_is_not_polymorphic<int(...) const volatile noexcept>();
    test_is_not_polymorphic<int(...) const volatile& noexcept>();
    test_is_not_polymorphic<int(...) const volatile&& noexcept>();

    test_is_not_polymorphic<int(int, ...)>();
    test_is_not_polymorphic<int(int, ...)&>();
    test_is_not_polymorphic<int(int, ...) &&>();
    test_is_not_polymorphic<int(int, ...) const>();
    test_is_not_polymorphic<int(int, ...) const&>();
    test_is_not_polymorphic<int(int, ...) const&&>();
    test_is_not_polymorphic<int(int, ...) volatile>();
    test_is_not_polymorphic<int(int, ...) volatile&>();
    test_is_not_polymorphic<int(int, ...) volatile&&>();
    test_is_not_polymorphic<int(int, ...) const volatile>();
    test_is_not_polymorphic<int(int, ...) const volatile&>();
    test_is_not_polymorphic<int(int, ...) const volatile&&>();
    test_is_not_polymorphic<int(int, ...) noexcept>();
    test_is_not_polymorphic<int(int, ...)& noexcept>();
    test_is_not_polymorphic<int(int, ...)&& noexcept>();
    test_is_not_polymorphic<int(int, ...) const noexcept>();
    test_is_not_polymorphic<int(int, ...) const& noexcept>();
    test_is_not_polymorphic<int(int, ...) const&& noexcept>();
    test_is_not_polymorphic<int(int, ...) volatile noexcept>();
    test_is_not_polymorphic<int(int, ...) volatile& noexcept>();
    test_is_not_polymorphic<int(int, ...) volatile&& noexcept>();
    test_is_not_polymorphic<int(int, ...) const volatile noexcept>();
    test_is_not_polymorphic<int(int, ...) const volatile& noexcept>();
    test_is_not_polymorphic<int(int, ...) const volatile&& noexcept>();

    test_is_not_polymorphic<void (*)()>();
    test_is_not_polymorphic<void (*)() noexcept>();

    test_is_not_polymorphic<void (*)(int)>();
    test_is_not_polymorphic<void (*)(int) noexcept>();

    test_is_not_polymorphic<void (*)(...)>();
    test_is_not_polymorphic<void (*)(...) noexcept>();

    test_is_not_polymorphic<void (*)(int, ...)>();
    test_is_not_polymorphic<void (*)(int, ...) noexcept>();

    test_is_not_polymorphic<int (*)()>();
    test_is_not_polymorphic<int (*)() noexcept>();

    test_is_not_polymorphic<int (*)(int)>();
    test_is_not_polymorphic<int (*)(int) noexcept>();

    test_is_not_polymorphic<int (*)(...)>();
    test_is_not_polymorphic<int (*)(...) noexcept>();

    test_is_not_polymorphic<int (*)(int, ...)>();
    test_is_not_polymorphic<int (*)(int, ...) noexcept>();

    test_is_not_polymorphic<void (&)()>();
    test_is_not_polymorphic<void (&)() noexcept>();

    test_is_not_polymorphic<void (&)(int)>();
    test_is_not_polymorphic<void (&)(int) noexcept>();

    test_is_not_polymorphic<void (&)(...)>();
    test_is_not_polymorphic<void (&)(...) noexcept>();

    test_is_not_polymorphic<void (&)(int, ...)>();
    test_is_not_polymorphic<void (&)(int, ...) noexcept>();

    test_is_not_polymorphic<int (&)()>();
    test_is_not_polymorphic<int (&)() noexcept>();

    test_is_not_polymorphic<int (&)(int)>();
    test_is_not_polymorphic<int (&)(int) noexcept>();

    test_is_not_polymorphic<int (&)(...)>();
    test_is_not_polymorphic<int (&)(...) noexcept>();

    test_is_not_polymorphic<int (&)(int, ...)>();
    test_is_not_polymorphic<int (&)(int, ...) noexcept>();

    test_is_not_polymorphic<void(&&)()>();
    test_is_not_polymorphic<void(&&)() noexcept>();

    test_is_not_polymorphic<void(&&)(int)>();
    test_is_not_polymorphic<void(&&)(int) noexcept>();

    test_is_not_polymorphic<void(&&)(...)>();
    test_is_not_polymorphic<void(&&)(...) noexcept>();

    test_is_not_polymorphic<void(&&)(int, ...)>();
    test_is_not_polymorphic<void(&&)(int, ...) noexcept>();

    test_is_not_polymorphic<int(&&)()>();
    test_is_not_polymorphic<int(&&)() noexcept>();

    test_is_not_polymorphic<int(&&)(int)>();
    test_is_not_polymorphic<int(&&)(int) noexcept>();

    test_is_not_polymorphic<int(&&)(...)>();
    test_is_not_polymorphic<int(&&)(...) noexcept>();

    test_is_not_polymorphic<int(&&)(int, ...)>();
    test_is_not_polymorphic<int(&&)(int, ...) noexcept>();

    test_is_not_polymorphic<void (Class::*)()>();
    test_is_not_polymorphic<void (Class::*)()&>();
    test_is_not_polymorphic<void (Class::*)() &&>();
    test_is_not_polymorphic<void (Class::*)() const>();
    test_is_not_polymorphic<void (Class::*)() const&>();
    test_is_not_polymorphic<void (Class::*)() const&&>();
    test_is_not_polymorphic<void (Class::*)() noexcept>();
    test_is_not_polymorphic<void (Class::*)()& noexcept>();
    test_is_not_polymorphic<void (Class::*)()&& noexcept>();
    test_is_not_polymorphic<void (Class::*)() const noexcept>();
    test_is_not_polymorphic<void (Class::*)() const& noexcept>();
    test_is_not_polymorphic<void (Class::*)() const&& noexcept>();

    test_is_not_polymorphic<void (Class::*)(int)>();
    test_is_not_polymorphic<void (Class::*)(int)&>();
    test_is_not_polymorphic<void (Class::*)(int) &&>();
    test_is_not_polymorphic<void (Class::*)(int) const>();
    test_is_not_polymorphic<void (Class::*)(int) const&>();
    test_is_not_polymorphic<void (Class::*)(int) const&&>();
    test_is_not_polymorphic<void (Class::*)(int) noexcept>();
    test_is_not_polymorphic<void (Class::*)(int)& noexcept>();
    test_is_not_polymorphic<void (Class::*)(int)&& noexcept>();
    test_is_not_polymorphic<void (Class::*)(int) const noexcept>();
    test_is_not_polymorphic<void (Class::*)(int) const& noexcept>();
    test_is_not_polymorphic<void (Class::*)(int) const&& noexcept>();

    test_is_not_polymorphic<void (Class::*)(...)>();
    test_is_not_polymorphic<void (Class::*)(...)&>();
    test_is_not_polymorphic<void (Class::*)(...) &&>();
    test_is_not_polymorphic<void (Class::*)(...) const>();
    test_is_not_polymorphic<void (Class::*)(...) const&>();
    test_is_not_polymorphic<void (Class::*)(...) const&&>();
    test_is_not_polymorphic<void (Class::*)(...) noexcept>();
    test_is_not_polymorphic<void (Class::*)(...)& noexcept>();
    test_is_not_polymorphic<void (Class::*)(...)&& noexcept>();
    test_is_not_polymorphic<void (Class::*)(...) const noexcept>();
    test_is_not_polymorphic<void (Class::*)(...) const& noexcept>();
    test_is_not_polymorphic<void (Class::*)(...) const&& noexcept>();

    test_is_not_polymorphic<void (Class::*)(int, ...)>();
    test_is_not_polymorphic<void (Class::*)(int, ...)&>();
    test_is_not_polymorphic<void (Class::*)(int, ...) &&>();
    test_is_not_polymorphic<void (Class::*)(int, ...) const>();
    test_is_not_polymorphic<void (Class::*)(int, ...) const&>();
    test_is_not_polymorphic<void (Class::*)(int, ...) const&&>();
    test_is_not_polymorphic<void (Class::*)(int, ...) noexcept>();
    test_is_not_polymorphic<void (Class::*)(int, ...)& noexcept>();
    test_is_not_polymorphic<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_polymorphic<void (Class::*)(int, ...) const noexcept>();
    test_is_not_polymorphic<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_polymorphic<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_polymorphic<int (Class::*)()>();
    test_is_not_polymorphic<int (Class::*)()&>();
    test_is_not_polymorphic<int (Class::*)() &&>();
    test_is_not_polymorphic<int (Class::*)() const>();
    test_is_not_polymorphic<int (Class::*)() const&>();
    test_is_not_polymorphic<int (Class::*)() const&&>();
    test_is_not_polymorphic<int (Class::*)() noexcept>();
    test_is_not_polymorphic<int (Class::*)()& noexcept>();
    test_is_not_polymorphic<int (Class::*)()&& noexcept>();
    test_is_not_polymorphic<int (Class::*)() const noexcept>();
    test_is_not_polymorphic<int (Class::*)() const& noexcept>();
    test_is_not_polymorphic<int (Class::*)() const&& noexcept>();

    test_is_not_polymorphic<int (Class::*)(int)>();
    test_is_not_polymorphic<int (Class::*)(int)&>();
    test_is_not_polymorphic<int (Class::*)(int) &&>();
    test_is_not_polymorphic<int (Class::*)(int) const>();
    test_is_not_polymorphic<int (Class::*)(int) const&>();
    test_is_not_polymorphic<int (Class::*)(int) const&&>();
    test_is_not_polymorphic<int (Class::*)(int) noexcept>();
    test_is_not_polymorphic<int (Class::*)(int)& noexcept>();
    test_is_not_polymorphic<int (Class::*)(int)&& noexcept>();
    test_is_not_polymorphic<int (Class::*)(int) const noexcept>();
    test_is_not_polymorphic<int (Class::*)(int) const& noexcept>();
    test_is_not_polymorphic<int (Class::*)(int) const&& noexcept>();

    test_is_not_polymorphic<int (Class::*)(...)>();
    test_is_not_polymorphic<int (Class::*)(...)&>();
    test_is_not_polymorphic<int (Class::*)(...) &&>();
    test_is_not_polymorphic<int (Class::*)(...) const>();
    test_is_not_polymorphic<int (Class::*)(...) const&>();
    test_is_not_polymorphic<int (Class::*)(...) const&&>();
    test_is_not_polymorphic<int (Class::*)(...) noexcept>();
    test_is_not_polymorphic<int (Class::*)(...)& noexcept>();
    test_is_not_polymorphic<int (Class::*)(...)&& noexcept>();
    test_is_not_polymorphic<int (Class::*)(...) const noexcept>();
    test_is_not_polymorphic<int (Class::*)(...) const& noexcept>();
    test_is_not_polymorphic<int (Class::*)(...) const&& noexcept>();

    test_is_not_polymorphic<int (Class::*)(int, ...)>();
    test_is_not_polymorphic<int (Class::*)(int, ...)&>();
    test_is_not_polymorphic<int (Class::*)(int, ...) &&>();
    test_is_not_polymorphic<int (Class::*)(int, ...) const>();
    test_is_not_polymorphic<int (Class::*)(int, ...) const&>();
    test_is_not_polymorphic<int (Class::*)(int, ...) const&&>();
    test_is_not_polymorphic<int (Class::*)(int, ...) noexcept>();
    test_is_not_polymorphic<int (Class::*)(int, ...)& noexcept>();
    test_is_not_polymorphic<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_polymorphic<int (Class::*)(int, ...) const noexcept>();
    test_is_not_polymorphic<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_polymorphic<int (Class::*)(int, ...) const&& noexcept>();
}
