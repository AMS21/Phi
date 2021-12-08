#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/type_traits/is_nothrow_default_constructible.hpp>

template <typename T>
void test_is_nothrow_default_constructible()
{
    STATIC_REQUIRE(phi::is_nothrow_default_constructible<T>::value);
    STATIC_REQUIRE(phi::is_nothrow_default_constructible<const T>::value);
    STATIC_REQUIRE(phi::is_nothrow_default_constructible<volatile T>::value);
    STATIC_REQUIRE(phi::is_nothrow_default_constructible<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_default_constructible_v<T>);
    STATIC_REQUIRE(phi::is_nothrow_default_constructible_v<const T>);
    STATIC_REQUIRE(phi::is_nothrow_default_constructible_v<volatile T>);
    STATIC_REQUIRE(phi::is_nothrow_default_constructible_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_nothrow_default_constructible()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_default_constructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_default_constructible<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_default_constructible<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_default_constructible<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_default_constructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_default_constructible_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_default_constructible_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_default_constructible_v<const volatile T>);
#endif
}

struct A
{
    A();
};

struct B
{
    B() noexcept;
};

struct DThrows
{
    DThrows() noexcept(true)
    {}

    ~DThrows() noexcept(false)
    {}
};

TEST_CASE("is_nothrow_default_constructible")
{
    test_is_nothrow_default_constructible<phi::nullptr_t>();
    test_is_nothrow_default_constructible<bool>();
    test_is_nothrow_default_constructible<char>();
    test_is_nothrow_default_constructible<signed char>();
    test_is_nothrow_default_constructible<unsigned char>();
    test_is_nothrow_default_constructible<short>();
    test_is_nothrow_default_constructible<unsigned short>();
    test_is_nothrow_default_constructible<int>();
    test_is_nothrow_default_constructible<unsigned int>();
    test_is_nothrow_default_constructible<long>();
    test_is_nothrow_default_constructible<unsigned long>();
    test_is_nothrow_default_constructible<long long>();
    test_is_nothrow_default_constructible<unsigned long long>();
    test_is_nothrow_default_constructible<float>();
    test_is_nothrow_default_constructible<double>();
    test_is_nothrow_default_constructible<long double>();
    test_is_nothrow_default_constructible<char8_t>();
    test_is_nothrow_default_constructible<char16_t>();
    test_is_nothrow_default_constructible<char32_t>();
    test_is_nothrow_default_constructible<wchar_t>();

    test_is_nothrow_default_constructible<int*>();
    test_is_nothrow_default_constructible<const int*>();
    test_is_nothrow_default_constructible<volatile int*>();
    test_is_nothrow_default_constructible<const volatile int*>();
    test_is_nothrow_default_constructible<int**>();
    test_is_nothrow_default_constructible<char[3]>();
#if PHI_SUPPORTS_IS_NOTHROW_CONSTRUCTIBLE()
    test_is_not_nothrow_default_constructible<char[]>();
#endif
    test_is_nothrow_default_constructible<Class>();
    test_is_nothrow_default_constructible<Union>();
    test_is_nothrow_default_constructible<NonEmptyUnion>();
    test_is_nothrow_default_constructible<Empty>();
    test_is_nothrow_default_constructible<NotEmpty>();
    test_is_nothrow_default_constructible<bit_zero>();
    test_is_nothrow_default_constructible<bit_one>();
    test_is_not_nothrow_default_constructible<Abstract>();
    test_is_not_nothrow_default_constructible<AbstractTemplate<int>>();
    test_is_nothrow_default_constructible<AbstractTemplate<double>>();
    test_is_not_nothrow_default_constructible<AbstractTemplate<Class>>();
    test_is_nothrow_default_constructible<Enum>();
    test_is_nothrow_default_constructible<EnumSigned>();
    test_is_nothrow_default_constructible<EnumUnsigned>();
    test_is_nothrow_default_constructible<EnumClass>();
    test_is_nothrow_default_constructible<FunctionPtr>();
    test_is_nothrow_default_constructible<MemberObjectPtr>();
    test_is_nothrow_default_constructible<MemberFunctionPtr>();

    test_is_not_nothrow_default_constructible<void>();
    test_is_not_nothrow_default_constructible<int&>();
    test_is_not_nothrow_default_constructible<int&&>();
    test_is_not_nothrow_default_constructible<Function>();
    test_is_not_nothrow_default_constructible<A>();
    test_is_nothrow_default_constructible<B>();
    test_is_not_nothrow_default_constructible<DThrows>(); // This is LWG2116
}
