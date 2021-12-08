#include <phi/test/test_macros.hpp>

#include "phi/compiler_support/char8_t.hpp"
#include "test_types.hpp"
#include <phi/type_traits/is_object.hpp>

template <typename T>
void test_is_object()
{
    STATIC_REQUIRE(phi::is_object<T>::value);
    STATIC_REQUIRE(phi::is_object<const T>::value);
    STATIC_REQUIRE(phi::is_object<volatile T>::value);
    STATIC_REQUIRE(phi::is_object<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_object_v<T>);
    STATIC_REQUIRE(phi::is_object_v<const T>);
    STATIC_REQUIRE(phi::is_object_v<volatile T>);
    STATIC_REQUIRE(phi::is_object_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_object()
{
    STATIC_REQUIRE_FALSE(phi::is_object<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_object<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_object<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_object<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_object_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_object_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_object_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_object_v<const volatile T>);
#endif
}

TEST_CASE("is_object")
{
    test_is_object<phi::nullptr_t>();
    test_is_object<void*>();
    test_is_object<bool>();
    test_is_object<char>();
    test_is_object<signed char>();
    test_is_object<unsigned char>();
    test_is_object<short>();
    test_is_object<unsigned short>();
    test_is_object<int>();
    test_is_object<unsigned int>();
    test_is_object<long>();
    test_is_object<unsigned long>();
    test_is_object<long long>();
    test_is_object<unsigned long long>();
    test_is_object<float>();
    test_is_object<double>();
    test_is_object<long double>();
    test_is_object<char8_t>();
    test_is_object<char16_t>();
    test_is_object<char32_t>();
    test_is_object<wchar_t>();

    test_is_object<char[3]>();
    test_is_object<char[]>();
    test_is_object<int*>();
    test_is_object<const int*>();
    test_is_object<volatile int*>();
    test_is_object<const volatile int*>();
    test_is_object<int**>();
    test_is_object<Class>();
    test_is_object<Empty>();
    test_is_object<NotEmpty>();
    test_is_object<Union>();
    test_is_object<NonEmptyUnion>();
    test_is_object<bit_zero>();
    test_is_object<bit_one>();
    test_is_object<Base>();
    test_is_object<Derived>();
    test_is_object<Abstract>();
    test_is_object<AbstractTemplate<int>>();
    test_is_object<AbstractTemplate<double>>();
    test_is_object<AbstractTemplate<Class>>();
    test_is_object<AbstractTemplate<incomplete_type>>();
    test_is_object<Enum>();
    test_is_object<EnumSigned>();
    test_is_object<EnumUnsigned>();
    test_is_object<EnumClass>();
    test_is_object<incomplete_type>();
    test_is_object<FunctionPtr>();
    test_is_object<MemberObjectPtr>();
    test_is_object<MemberFunctionPtr>();
    test_is_object<int Empty::*>();
    test_is_object<void (Empty::*)(int)>();

    test_is_not_object<void>();
    test_is_not_object<Function>();
    test_is_not_object<int&>();
    test_is_not_object<int&&>();
    test_is_not_object<int(int)>();
}
