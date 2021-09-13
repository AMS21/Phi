#include <catch2/catch_test_macros.hpp>

#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_same.hpp>
#include <Phi/TypeTraits/make_unsafe.hpp>

class Class
{
public:
    ~Class();
};

struct A; // incomplete

class incomplete_type;

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

enum EnumSigned : int
{
    two
};

enum EnumUnsigned : unsigned
{
    three
};

enum class EnumClass
{
    zero,
    one
};

using FunctionPtr = void (*)();

template <typename InT, typename OutT>
void test_make_unsafe()
{
    STATIC_REQUIRE(phi::is_same_v<typename phi::make_unsafe<InT>::type, OutT>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::make_unsafe<const InT>::type, const OutT>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::make_unsafe<volatile InT>::type, volatile OutT>);
    STATIC_REQUIRE(phi::is_same_v<typename phi::make_unsafe<const volatile InT>::type,
                                  const volatile OutT>);

    STATIC_REQUIRE(phi::is_same_v<phi::make_unsafe_t<InT>, OutT>);
    STATIC_REQUIRE(phi::is_same_v<phi::make_unsafe_t<const InT>, const OutT>);
    STATIC_REQUIRE(phi::is_same_v<phi::make_unsafe_t<volatile InT>, volatile OutT>);
    STATIC_REQUIRE(phi::is_same_v<phi::make_unsafe_t<const volatile InT>, const volatile OutT>);
}

TEST_CASE("make_unsafe", "[TypeTraits][make_unsafe]")
{
    test_make_unsafe<phi::nullptr_t, phi::nullptr_t>();
    test_make_unsafe<void, void>();
    test_make_unsafe<int&, int&>();
    test_make_unsafe<int&&, int&&>();
    test_make_unsafe<Class, Class>();
    test_make_unsafe<int*, int*>();
    test_make_unsafe<const int*, const int*>();
    test_make_unsafe<volatile int*, volatile int*>();
    test_make_unsafe<const volatile int*, const volatile int*>();
    test_make_unsafe<char[3], char[3]>();
    test_make_unsafe<char[], char[]>();
    test_make_unsafe<Union, Union>();
    test_make_unsafe<Enum, Enum>();
    test_make_unsafe<EnumSigned, EnumSigned>();
    test_make_unsafe<EnumUnsigned, EnumUnsigned>();
    test_make_unsafe<EnumClass, EnumClass>();
    test_make_unsafe<FunctionPtr, FunctionPtr>();
    test_make_unsafe<Empty, Empty>();
    test_make_unsafe<incomplete_type, incomplete_type>();
    test_make_unsafe<A, A>();
    test_make_unsafe<bit_zero, bit_zero>();
    test_make_unsafe<NotEmpty, NotEmpty>();
    test_make_unsafe<Abstract, Abstract>();

    // unsafe int types
    test_make_unsafe<signed char, signed char>();
    test_make_unsafe<short, short>();
    test_make_unsafe<int, int>();
    test_make_unsafe<long, long>();
    test_make_unsafe<long long, long long>();

    test_make_unsafe<unsigned, unsigned>();
    test_make_unsafe<unsigned char, unsigned char>();
    test_make_unsafe<unsigned short, unsigned short>();
    test_make_unsafe<unsigned int, unsigned int>();
    test_make_unsafe<unsigned long, unsigned long>();
    test_make_unsafe<unsigned long long, unsigned long long>();

    // safe int types
    test_make_unsafe<phi::Integer<signed char>, signed char>();
    test_make_unsafe<phi::Integer<short>, short>();
    test_make_unsafe<phi::Integer<int>, int>();
    test_make_unsafe<phi::Integer<long>, long>();
    test_make_unsafe<phi::Integer<long long>, long long>();

    test_make_unsafe<phi::Integer<unsigned>, unsigned>();
    test_make_unsafe<phi::Integer<unsigned char>, unsigned char>();
    test_make_unsafe<phi::Integer<unsigned short>, unsigned short>();
    test_make_unsafe<phi::Integer<unsigned int>, unsigned int>();
    test_make_unsafe<phi::Integer<unsigned long>, unsigned long>();
    test_make_unsafe<phi::Integer<unsigned long long>, unsigned long long>();

    // unsafe float
    test_make_unsafe<float, float>();
    test_make_unsafe<double, double>();
    test_make_unsafe<long double, long double>();

    // safe float
    test_make_unsafe<phi::FloatingPoint<float>, float>();
    test_make_unsafe<phi::FloatingPoint<double>, double>();
    test_make_unsafe<phi::FloatingPoint<long double>, long double>();

    test_make_unsafe<bool, bool>();
    test_make_unsafe<phi::Boolean, bool>();
    test_make_unsafe<wchar_t, wchar_t>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_make_unsafe<char8_t, char8_t>();
#endif
    test_make_unsafe<char16_t, char16_t>();
    test_make_unsafe<char32_t, char32_t>();
}
