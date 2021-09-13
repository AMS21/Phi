#include <catch2/catch_test_macros.hpp>

#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_void.hpp>

template <class T>
void test_is_void()
{
    STATIC_REQUIRE(phi::is_void<T>::value);
    STATIC_REQUIRE(phi::is_void<const T>::value);
    STATIC_REQUIRE(phi::is_void<volatile T>::value);
    STATIC_REQUIRE(phi::is_void<const volatile T>::value);

    STATIC_REQUIRE(phi::is_void_v<T>);
    STATIC_REQUIRE(phi::is_void_v<const T>);
    STATIC_REQUIRE(phi::is_void_v<volatile T>);
    STATIC_REQUIRE(phi::is_void_v<const volatile T>);
}

template <class T>
void test_is_not_void()
{
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<const volatile T>::value);

    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<const volatile T>);
}

class Class
{};

class Empty
{};

class NotEmpty
{
    virtual ~NotEmpty();
};

union Union
{};

struct bit_zero
{
    int : 0;
};

class Abstract
{
    virtual ~Abstract() = 0;
};

enum Enum
{
    zero,
    one
};
struct incomplete_type;

using FunctionPtr = void (*)();

TEST_CASE("is_void")
{
    test_is_void<void>();

    test_is_not_void<phi::nullptr_t>();
    test_is_not_void<int>();
    test_is_not_void<int*>();
    test_is_not_void<int&>();
    test_is_not_void<int&&>();
    test_is_not_void<double>();
    test_is_not_void<const int*>();
    test_is_not_void<volatile int*>();
    test_is_not_void<const volatile int*>();
    test_is_not_void<char[3]>();
    test_is_not_void<char[]>();
    test_is_not_void<Union>();
    test_is_not_void<Empty>();
    test_is_not_void<bit_zero>();
    test_is_not_void<NotEmpty>();
    test_is_not_void<Abstract>();
    test_is_not_void<Enum>();
    test_is_not_void<FunctionPtr>();
    test_is_not_void<incomplete_type>();
    test_is_not_void<int(Class::*)>();
    test_is_not_void<void (Class::*)()>();
}
