#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/Config/Compiler.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_default_constructible.hpp>

template <typename T>
void test_is_default_constructible()
{
    STATIC_REQUIRE(phi::is_default_constructible<T>::value);
    STATIC_REQUIRE(phi::is_default_constructible<const T>::value);
    STATIC_REQUIRE(phi::is_default_constructible<volatile T>::value);
    STATIC_REQUIRE(phi::is_default_constructible<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_default_constructible_v<T>);
    STATIC_REQUIRE(phi::is_default_constructible_v<const T>);
    STATIC_REQUIRE(phi::is_default_constructible_v<volatile T>);
    STATIC_REQUIRE(phi::is_default_constructible_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_default_constructible()
{
    STATIC_REQUIRE_FALSE(phi::is_default_constructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_default_constructible<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_default_constructible<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_default_constructible<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_default_constructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_default_constructible_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_default_constructible_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_default_constructible_v<const volatile T>);
#endif
}

class NoDefaultConstructor
{
    NoDefaultConstructor(int)
    {}
};

struct A
{
    A();
};

class B
{
    B();
};

TEST_CASE("is_default_constructible")
{
    test_is_default_constructible<phi::nullptr_t>();
    test_is_default_constructible<A>();
    test_is_default_constructible<Union>();
    test_is_default_constructible<Empty>();
    test_is_default_constructible<int>();
    test_is_default_constructible<float>();
    test_is_default_constructible<double>();
    test_is_default_constructible<int*>();
    test_is_default_constructible<const int*>();
    test_is_default_constructible<volatile int*>();
    test_is_default_constructible<const volatile int*>();
    test_is_default_constructible<int**>();
    test_is_default_constructible<char[3]>();
    test_is_default_constructible<char[5][3]>();

    test_is_default_constructible<NotEmpty>();
    test_is_default_constructible<bit_zero>();
    test_is_default_constructible<Class>();
    test_is_default_constructible<NonEmptyUnion>();
    test_is_default_constructible<AbstractTemplate<double>>();
    test_is_default_constructible<Enum>();
    test_is_default_constructible<EnumSigned>();
    test_is_default_constructible<EnumUnsigned>();
    test_is_default_constructible<EnumClass>();
    test_is_default_constructible<FunctionPtr>();
    test_is_default_constructible<MemberObjectPtr>();
    test_is_default_constructible<MemberFunctionPtr>();

    test_is_not_default_constructible<void>();
    test_is_not_default_constructible<int&>();
    test_is_not_default_constructible<int&&>();

    test_is_not_default_constructible<Abstract>();
    test_is_not_default_constructible<NoDefaultConstructor>();
    test_is_not_default_constructible<B>();

    test_is_not_default_constructible<void()>();
    test_is_not_default_constructible<void() const>();
    test_is_not_default_constructible<void() volatile>();
    test_is_not_default_constructible<void() const volatile>();
    test_is_not_default_constructible<void()&>();
    test_is_not_default_constructible<void() &&>();
    test_is_not_default_constructible<void() const&>();
    test_is_not_default_constructible<void() volatile&>();
    test_is_not_default_constructible<void() const volatile&>();
    test_is_not_default_constructible<void() const&&>();
    test_is_not_default_constructible<void() volatile&&>();
    test_is_not_default_constructible<void() const volatile&&>();

    test_is_not_default_constructible<void() noexcept>();
    test_is_not_default_constructible<void() const noexcept>();
    test_is_not_default_constructible<void() volatile noexcept>();
    test_is_not_default_constructible<void() const volatile noexcept>();
    test_is_not_default_constructible<void()& noexcept>();
    test_is_not_default_constructible<void()&& noexcept>();
    test_is_not_default_constructible<void() const& noexcept>();
    test_is_not_default_constructible<void() volatile& noexcept>();
    test_is_not_default_constructible<void() const volatile& noexcept>();
    test_is_not_default_constructible<void() const&& noexcept>();
    test_is_not_default_constructible<void() volatile&& noexcept>();
    test_is_not_default_constructible<void() const volatile&& noexcept>();

#if !PHI_HAS_BUG_GCC_102305()
    // Test GCC bug 102305 (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=102305)
    test_is_not_default_constructible<AbstractTemplate<int>>();
#endif

    // Incomplete types only work with the intrinsics
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_default_constructible<char[]>();
    test_is_not_default_constructible<char[][3]>();
#endif
}
