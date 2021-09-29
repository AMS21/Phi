#include <catch2/catch.hpp>

#include "Phi/Core/Nullptr.hpp"
#include "TestTypes.hpp"
#include <Phi/TypeTraits/is_reference_wrapper.hpp>
#include <functional>

template <typename T>
void test_is_reference_wrapper()
{
    STATIC_REQUIRE(phi::is_reference_wrapper<T>::value);
    STATIC_REQUIRE(phi::is_reference_wrapper<const T>::value);
    STATIC_REQUIRE(phi::is_reference_wrapper<volatile T>::value);
    STATIC_REQUIRE(phi::is_reference_wrapper<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_reference_wrapper_v<T>);
    STATIC_REQUIRE(phi::is_reference_wrapper_v<const T>);
    STATIC_REQUIRE(phi::is_reference_wrapper_v<volatile T>);
    STATIC_REQUIRE(phi::is_reference_wrapper_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_reference_wrapper()
{
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper_v<const volatile T>);
#endif
}

TEST_CASE("is_refenrece_wrapper")
{
    test_is_reference_wrapper<std::reference_wrapper<int>>();
    test_is_reference_wrapper<std::reference_wrapper<float>>();
    test_is_reference_wrapper<std::reference_wrapper<void>>();

    test_is_not_reference_wrapper<phi::nullptr_t>();
    test_is_not_reference_wrapper<void>();
    test_is_not_reference_wrapper<int>();
    test_is_not_reference_wrapper<float>();
    test_is_not_reference_wrapper<int&>();
    test_is_not_reference_wrapper<int&&>();
    test_is_not_reference_wrapper<int*>();
    test_is_not_reference_wrapper<Class>();
    test_is_not_reference_wrapper<Struct>();
    test_is_not_reference_wrapper<Empty>();
    test_is_not_reference_wrapper<NotEmpty>();
    test_is_not_reference_wrapper<Union>();
    test_is_not_reference_wrapper<NonEmptyUnion>();
    test_is_not_reference_wrapper<Enum>();
    test_is_not_reference_wrapper<EnumSigned>();
    test_is_not_reference_wrapper<EnumUnsigned>();
    test_is_not_reference_wrapper<EnumClass>();
    test_is_not_reference_wrapper<Function>();
    test_is_not_reference_wrapper<FunctionPtr>();
    test_is_not_reference_wrapper<MemberObjectPtr>();
    test_is_not_reference_wrapper<MemberFunctionPtr>();
}
