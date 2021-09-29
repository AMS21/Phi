#include <catch2/catch.hpp>

#include "SameType.hpp"
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_safe_bool.hpp>
#include <Phi/TypeTraits/make_safe.hpp>

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
void test_make_safe()
{
    CHECK_SAME_TYPE(typename phi::make_safe<InT>::type, OutT);
    CHECK_SAME_TYPE(typename phi::make_safe<const InT>::type, const OutT);
    CHECK_SAME_TYPE(typename phi::make_safe<volatile InT>::type, volatile OutT);
    CHECK_SAME_TYPE(typename phi::make_safe<const volatile InT>::type, const volatile OutT);

    CHECK_SAME_TYPE(typename phi::make_safe_t<InT>, OutT);
    CHECK_SAME_TYPE(typename phi::make_safe_t<const InT>, const OutT);
    CHECK_SAME_TYPE(typename phi::make_safe_t<volatile InT>, volatile OutT);
    CHECK_SAME_TYPE(typename phi::make_safe_t<const volatile InT>, const volatile OutT);
}

TEST_CASE("make_safe", "[TypeTraits][make_safe]")
{
    test_make_safe<phi::nullptr_t, phi::nullptr_t>();
    test_make_safe<void, void>();
    test_make_safe<int&, int&>();
    test_make_safe<int&&, int&&>();
    test_make_safe<Class, Class>();
    test_make_safe<int*, int*>();
    test_make_safe<const int*, const int*>();
    test_make_safe<volatile int*, volatile int*>();
    test_make_safe<const volatile int*, const volatile int*>();
    test_make_safe<char[3], char[3]>();
    test_make_safe<char[], char[]>();
    test_make_safe<Union, Union>();
    test_make_safe<Enum, Enum>();
    test_make_safe<EnumSigned, EnumSigned>();
    test_make_safe<EnumUnsigned, EnumUnsigned>();
    test_make_safe<EnumClass, EnumClass>();
    test_make_safe<FunctionPtr, FunctionPtr>();
    test_make_safe<Empty, Empty>();
    test_make_safe<incomplete_type, incomplete_type>();
    test_make_safe<A, A>();
    test_make_safe<bit_zero, bit_zero>();
    test_make_safe<NotEmpty, NotEmpty>();
    test_make_safe<Abstract, Abstract>();

    // unsafe int types
    test_make_safe<signed char, phi::Integer<signed char>>();
    test_make_safe<short, phi::Integer<short>>();
    test_make_safe<int, phi::Integer<int>>();
    test_make_safe<long, phi::Integer<long>>();
    test_make_safe<long long, phi::Integer<long long>>();

    test_make_safe<unsigned, phi::Integer<unsigned>>();
    test_make_safe<unsigned char, phi::Integer<unsigned char>>();
    test_make_safe<unsigned short, phi::Integer<unsigned short>>();
    test_make_safe<unsigned int, phi::Integer<unsigned int>>();
    test_make_safe<unsigned long, phi::Integer<unsigned long>>();
    test_make_safe<unsigned long long, phi::Integer<unsigned long long>>();

    // safe int types
    test_make_safe<phi::Integer<signed char>, phi::Integer<signed char>>();
    test_make_safe<phi::Integer<short>, phi::Integer<short>>();
    test_make_safe<phi::Integer<int>, phi::Integer<int>>();
    test_make_safe<phi::Integer<long>, phi::Integer<long>>();
    test_make_safe<phi::Integer<long long>, phi::Integer<long long>>();

    test_make_safe<phi::Integer<unsigned>, phi::Integer<unsigned>>();
    test_make_safe<phi::Integer<unsigned char>, phi::Integer<unsigned char>>();
    test_make_safe<phi::Integer<unsigned short>, phi::Integer<unsigned short>>();
    test_make_safe<phi::Integer<unsigned int>, phi::Integer<unsigned int>>();
    test_make_safe<phi::Integer<unsigned long>, phi::Integer<unsigned long>>();
    test_make_safe<phi::Integer<unsigned long long>, phi::Integer<unsigned long long>>();

    // unsafe float
    test_make_safe<float, phi::FloatingPoint<float>>();
    test_make_safe<double, phi::FloatingPoint<double>>();
    test_make_safe<long double, phi::FloatingPoint<long double>>();

    // safe float
    test_make_safe<phi::FloatingPoint<float>, phi::FloatingPoint<float>>();
    test_make_safe<phi::FloatingPoint<double>, phi::FloatingPoint<double>>();
    test_make_safe<phi::FloatingPoint<long double>, phi::FloatingPoint<long double>>();

    test_make_safe<bool, phi::Boolean>();
    test_make_safe<phi::Boolean, phi::Boolean>();
    test_make_safe<wchar_t, wchar_t>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_make_safe<char8_t, char8_t>();
#endif
    test_make_safe<char16_t, char16_t>();
    test_make_safe<char32_t, char32_t>();
}
