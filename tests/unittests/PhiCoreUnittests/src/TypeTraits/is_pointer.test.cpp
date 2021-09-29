#include <catch2/catch.hpp>

#include "Phi/CompilerSupport/Char8_t.hpp"
#include "TestTypes.hpp"
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_pointer.hpp>

template <typename T>
void test_is_pointer()
{
    STATIC_REQUIRE(phi::is_pointer<T>::value);
    STATIC_REQUIRE(phi::is_pointer<const T>::value);
    STATIC_REQUIRE(phi::is_pointer<volatile T>::value);
    STATIC_REQUIRE(phi::is_pointer<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_pointer_v<T>);
    STATIC_REQUIRE(phi::is_pointer_v<const T>);
    STATIC_REQUIRE(phi::is_pointer_v<volatile T>);
    STATIC_REQUIRE(phi::is_pointer_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_pointer()
{
    STATIC_REQUIRE_FALSE(phi::is_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_pointer<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_pointer<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_pointer<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<const volatile T>);
#endif
}

TEST_CASE("is_pointer")
{
    test_is_pointer<void*>();
    test_is_pointer<int*>();
    test_is_pointer<const int*>();
    test_is_pointer<volatile int*>();
    test_is_pointer<const volatile int*>();
    test_is_pointer<int**>();
    test_is_pointer<Class*>();
    test_is_pointer<Class**>();
    test_is_pointer<Abstract*>();
    test_is_pointer<incomplete_type*>();
    test_is_pointer<FunctionPtr>();

    test_is_not_pointer<phi::nullptr_t>();
    test_is_not_pointer<bool>();
    test_is_not_pointer<char>();
    test_is_not_pointer<signed char>();
    test_is_not_pointer<unsigned char>();
    test_is_not_pointer<short>();
    test_is_not_pointer<unsigned short>();
    test_is_not_pointer<int>();
    test_is_not_pointer<unsigned int>();
    test_is_not_pointer<long>();
    test_is_not_pointer<unsigned long>();
    test_is_not_pointer<long long>();
    test_is_not_pointer<unsigned long long>();
    test_is_not_pointer<float>();
    test_is_not_pointer<double>();
    test_is_not_pointer<long double>();
    test_is_not_pointer<char8_t>();
    test_is_not_pointer<char16_t>();
    test_is_not_pointer<char32_t>();
    test_is_not_pointer<wchar_t>();

    test_is_not_pointer<Class>();
    test_is_not_pointer<Struct>();
    test_is_not_pointer<Empty>();
    test_is_not_pointer<NotEmpty>();
    test_is_not_pointer<Union>();
    test_is_not_pointer<NonEmptyUnion>();
    test_is_not_pointer<bit_zero>();
    test_is_not_pointer<bit_one>();
    test_is_not_pointer<Base>();
    test_is_not_pointer<Derived>();
    test_is_not_pointer<Abstract>();
    test_is_not_pointer<AbstractTemplate<int>>();
    test_is_not_pointer<AbstractTemplate<double>>();
    test_is_not_pointer<AbstractTemplate<Class>>();
    test_is_not_pointer<AbstractTemplate<incomplete_type>>();
    test_is_not_pointer<Enum>();
    test_is_not_pointer<EnumSigned>();
    test_is_not_pointer<EnumUnsigned>();
    test_is_not_pointer<EnumClass>();
    test_is_not_pointer<incomplete_type>();
    test_is_not_pointer<Function>();
    test_is_not_pointer<MemberObjectPtr>();
    test_is_not_pointer<MemberFunctionPtr>();
}
