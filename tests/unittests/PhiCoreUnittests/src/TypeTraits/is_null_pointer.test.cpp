#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_null_pointer.hpp>
#include <cstddef> // std::nullptr_t

template <typename T>
void test_is_null_pointer()
{
    STATIC_REQUIRE(phi::is_null_pointer<T>::value);
    STATIC_REQUIRE(phi::is_null_pointer<const T>::value);
    STATIC_REQUIRE(phi::is_null_pointer<volatile T>::value);
    STATIC_REQUIRE(phi::is_null_pointer<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_null_pointer_v<T>);
    STATIC_REQUIRE(phi::is_null_pointer_v<const T>);
    STATIC_REQUIRE(phi::is_null_pointer_v<volatile T>);
    STATIC_REQUIRE(phi::is_null_pointer_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_null_pointer()
{
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<const volatile T>);
#endif
}

TEST_CASE("is_null_pointer")
{
    test_is_null_pointer<phi::nullptr_t>();
    test_is_null_pointer<std::nullptr_t>();
    test_is_null_pointer<decltype(nullptr)>();

    test_is_not_null_pointer<void>();
    test_is_not_null_pointer<bool>();
    test_is_not_null_pointer<char>();
    test_is_not_null_pointer<signed char>();
    test_is_not_null_pointer<unsigned char>();
    test_is_not_null_pointer<short>();
    test_is_not_null_pointer<unsigned short>();
    test_is_not_null_pointer<int>();
    test_is_not_null_pointer<unsigned int>();
    test_is_not_null_pointer<long>();
    test_is_not_null_pointer<unsigned long>();
    test_is_not_null_pointer<long long>();
    test_is_not_null_pointer<unsigned long long>();
    test_is_not_null_pointer<float>();
    test_is_not_null_pointer<double>();
    test_is_not_null_pointer<long double>();
    test_is_not_null_pointer<char8_t>();
    test_is_not_null_pointer<char16_t>();
    test_is_not_null_pointer<char32_t>();
    test_is_not_null_pointer<wchar_t>();

    test_is_not_null_pointer<int&>();
    test_is_not_null_pointer<int&&>();
    test_is_not_null_pointer<int*>();
    test_is_not_null_pointer<const int*>();
    test_is_not_null_pointer<volatile int*>();
    test_is_not_null_pointer<const volatile int*>();
    test_is_not_null_pointer<int**>();
    test_is_not_null_pointer<char[3]>();
    test_is_not_null_pointer<char[]>();
    test_is_not_null_pointer<char[3][2]>();
    test_is_not_null_pointer<char[][2]>();
    test_is_not_null_pointer<Class>();
    test_is_not_null_pointer<Struct>();
    test_is_not_null_pointer<Empty>();
    test_is_not_null_pointer<NotEmpty>();
    test_is_not_null_pointer<Union>();
    test_is_not_null_pointer<NonEmptyUnion>();
    test_is_not_null_pointer<bit_zero>();
    test_is_not_null_pointer<bit_one>();
    test_is_not_null_pointer<Base>();
    test_is_not_null_pointer<Derived>();
    test_is_not_null_pointer<Abstract>();
    test_is_not_null_pointer<AbstractTemplate<int>>();
    test_is_not_null_pointer<AbstractTemplate<double>>();
    test_is_not_null_pointer<AbstractTemplate<Class>>();
    test_is_not_null_pointer<AbstractTemplate<incomplete_type>>();
    test_is_not_null_pointer<Enum>();
    test_is_not_null_pointer<EnumSigned>();
    test_is_not_null_pointer<EnumUnsigned>();
    test_is_not_null_pointer<EnumClass>();
    test_is_not_null_pointer<incomplete_type>();
    test_is_not_null_pointer<Function>();
    test_is_not_null_pointer<FunctionPtr>();
    test_is_not_null_pointer<MemberObjectPtr>();
    test_is_not_null_pointer<MemberFunctionPtr>();

    test_is_not_null_pointer<void*>();
    test_is_not_null_pointer<void * Class::*>();
}
