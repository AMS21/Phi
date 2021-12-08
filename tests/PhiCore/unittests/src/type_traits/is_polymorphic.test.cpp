#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/type_traits/is_polymorphic.hpp>

template <class T>
void test_is_polymorphic()
{
    STATIC_REQUIRE(phi::is_polymorphic<T>::value);
    STATIC_REQUIRE(phi::is_polymorphic<const T>::value);
    STATIC_REQUIRE(phi::is_polymorphic<volatile T>::value);
    STATIC_REQUIRE(phi::is_polymorphic<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_polymorphic_v<T>);
    STATIC_REQUIRE(phi::is_polymorphic_v<const T>);
    STATIC_REQUIRE(phi::is_polymorphic_v<volatile T>);
    STATIC_REQUIRE(phi::is_polymorphic_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_polymorphic()
{
    STATIC_REQUIRE_FALSE(phi::is_polymorphic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_polymorphic<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_polymorphic<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_polymorphic<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_polymorphic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_polymorphic_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_polymorphic_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_polymorphic_v<const volatile T>);
#endif
}

TEST_CASE("is_polymorphic")
{
    test_is_not_polymorphic<void>();
    test_is_not_polymorphic<int&>();
    test_is_not_polymorphic<int&&>();
    test_is_not_polymorphic<int>();
    test_is_not_polymorphic<double>();
    test_is_not_polymorphic<int*>();
    test_is_not_polymorphic<const int*>();
    test_is_not_polymorphic<char[3]>();
    test_is_not_polymorphic<char[]>();
    test_is_not_polymorphic<Union>();
    test_is_not_polymorphic<Empty>();
    test_is_not_polymorphic<bit_zero>();
    test_is_not_polymorphic<Final>();
    test_is_not_polymorphic<NotEmpty&>();
    test_is_not_polymorphic<Abstract&>();

    test_is_polymorphic<NotEmpty>();
    test_is_polymorphic<Abstract>();
}
