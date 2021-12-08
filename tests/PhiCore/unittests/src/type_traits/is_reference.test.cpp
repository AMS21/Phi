#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/type_traits/is_reference.hpp>

template <typename T>
void test_is_reference()
{
    STATIC_REQUIRE(phi::is_reference<T>::value);
    STATIC_REQUIRE(phi::is_reference<const T>::value);
    STATIC_REQUIRE(phi::is_reference<volatile T>::value);
    STATIC_REQUIRE(phi::is_reference<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_reference_v<T>);
    STATIC_REQUIRE(phi::is_reference_v<const T>);
    STATIC_REQUIRE(phi::is_reference_v<volatile T>);
    STATIC_REQUIRE(phi::is_reference_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_reference()
{
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<const volatile T>);
#endif
}

TEST_CASE("is_reference")
{
    test_is_reference<int&>();
    test_is_reference<int&&>();
    test_is_not_reference<phi::nullptr_t>();
    test_is_not_reference<void>();
    test_is_not_reference<int>();
    test_is_not_reference<double>();
    test_is_not_reference<char[3]>();
    test_is_not_reference<char[]>();
    test_is_not_reference<void*>();
    test_is_not_reference<FunctionPtr>();
    test_is_not_reference<Union>();
    test_is_not_reference<incomplete_type>();
    test_is_not_reference<Empty>();
    test_is_not_reference<bit_zero>();
    test_is_not_reference<int*>();
    test_is_not_reference<const int*>();
    test_is_not_reference<Enum>();
    test_is_not_reference<NotEmpty>();
    test_is_not_reference<Abstract>();
    test_is_not_reference<int(int)>();
    test_is_not_reference<int Empty::*>();
    test_is_not_reference<void (Empty::*)(int)>();
}
