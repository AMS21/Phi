#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/TypeTraits/is_function.hpp>

template <typename T>
void test_is_function()
{
    STATIC_REQUIRE(phi::is_function<T>::value);
    STATIC_REQUIRE(phi::is_function<const T>::value);
    STATIC_REQUIRE(phi::is_function<volatile T>::value);
    STATIC_REQUIRE(phi::is_function<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_function_v<T>);
    STATIC_REQUIRE(phi::is_function_v<const T>);
    STATIC_REQUIRE(phi::is_function_v<volatile T>);
    STATIC_REQUIRE(phi::is_function_v<const volatile T>);
#endif
};

template <typename T>
void test_is_not_function()
{
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<const volatile T>);
#endif
};

TEST_CASE("is_function")
{
    test_is_function<void(void)>();
    test_is_function<int(int)>();
    test_is_function<int(int, double)>();
    test_is_function<int(int, double, float, char, bool)>();
    test_is_function<int(Abstract*)>();
    test_is_function<void(...)>();
    test_is_function<bool(...)>();
    test_is_function<Function>();

    test_is_function<void()>();
    test_is_function<void()&>();
    test_is_function<void() &&>();
    test_is_function<void() const>();
    test_is_function<void() const&>();
    test_is_function<void() const&&>();
    test_is_function<void() volatile>();
    test_is_function<void() volatile&>();
    test_is_function<void() volatile&&>();
    test_is_function<void() const volatile>();
    test_is_function<void() const volatile&>();
    test_is_function<void() const volatile&&>();

    test_is_function<void() noexcept>();
    test_is_function<void()& noexcept>();
    test_is_function<void()&& noexcept>();
    test_is_function<void() const noexcept>();
    test_is_function<void() const& noexcept>();
    test_is_function<void() const&& noexcept>();
    test_is_function<void() volatile noexcept>();
    test_is_function<void() volatile& noexcept>();
    test_is_function<void() volatile&& noexcept>();
    test_is_function<void() const volatile noexcept>();
    test_is_function<void() const volatile& noexcept>();
    test_is_function<void() const volatile&& noexcept>();

    test_is_not_function<phi::nullptr_t>();
    test_is_not_function<void>();
    test_is_not_function<int>();
    test_is_not_function<short>();
    test_is_not_function<float>();
    test_is_not_function<double>();
    test_is_not_function<int&>();
    test_is_not_function<int&&>();
    test_is_not_function<int*>();
    test_is_not_function<const int*>();
    test_is_not_function<volatile int*>();
    test_is_not_function<const volatile int*>();
    test_is_not_function<int**>();
    test_is_not_function<char[3]>();
    test_is_not_function<char[]>();
    test_is_not_function<Class>();
    test_is_not_function<Struct>();
    test_is_not_function<Union>();
    test_is_not_function<NonEmptyUnion>();
    test_is_not_function<Enum>();
    test_is_not_function<Empty>();
    test_is_not_function<bit_zero>();
    test_is_not_function<bit_one>();
    test_is_not_function<NotEmpty>();
    test_is_not_function<Abstract>();
    test_is_not_function<Abstract*>();
    test_is_not_function<AbstractTemplate<int>>();
    test_is_not_function<AbstractTemplate<double>>();
    test_is_not_function<Enum>();
    test_is_not_function<EnumSigned>();
    test_is_not_function<EnumUnsigned>();
    test_is_not_function<EnumClass>();
    test_is_not_function<incomplete_type>();
    test_is_not_function<FunctionPtr>(); // function pointer is not a function
    test_is_not_function<MemberObjectPtr>();
    test_is_not_function<MemberFunctionPtr>();
}
