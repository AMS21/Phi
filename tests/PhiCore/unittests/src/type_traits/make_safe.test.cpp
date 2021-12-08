#include <phi/test/test_macros.hpp>

#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/type_traits/is_safe_bool.hpp>
#include <phi/type_traits/make_safe.hpp>

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
    test_make_safe<signed char, phi::integer<signed char>>();
    test_make_safe<short, phi::integer<short>>();
    test_make_safe<int, phi::integer<int>>();
    test_make_safe<long, phi::integer<long>>();
    test_make_safe<long long, phi::integer<long long>>();

    test_make_safe<unsigned, phi::integer<unsigned>>();
    test_make_safe<unsigned char, phi::integer<unsigned char>>();
    test_make_safe<unsigned short, phi::integer<unsigned short>>();
    test_make_safe<unsigned int, phi::integer<unsigned int>>();
    test_make_safe<unsigned long, phi::integer<unsigned long>>();
    test_make_safe<unsigned long long, phi::integer<unsigned long long>>();

    // safe int types
    test_make_safe<phi::integer<signed char>, phi::integer<signed char>>();
    test_make_safe<phi::integer<short>, phi::integer<short>>();
    test_make_safe<phi::integer<int>, phi::integer<int>>();
    test_make_safe<phi::integer<long>, phi::integer<long>>();
    test_make_safe<phi::integer<long long>, phi::integer<long long>>();

    test_make_safe<phi::integer<unsigned>, phi::integer<unsigned>>();
    test_make_safe<phi::integer<unsigned char>, phi::integer<unsigned char>>();
    test_make_safe<phi::integer<unsigned short>, phi::integer<unsigned short>>();
    test_make_safe<phi::integer<unsigned int>, phi::integer<unsigned int>>();
    test_make_safe<phi::integer<unsigned long>, phi::integer<unsigned long>>();
    test_make_safe<phi::integer<unsigned long long>, phi::integer<unsigned long long>>();

    // unsafe float
    test_make_safe<float, phi::floating_point<float>>();
    test_make_safe<double, phi::floating_point<double>>();
    test_make_safe<long double, phi::floating_point<long double>>();

    // safe float
    test_make_safe<phi::floating_point<float>, phi::floating_point<float>>();
    test_make_safe<phi::floating_point<double>, phi::floating_point<double>>();
    test_make_safe<phi::floating_point<long double>, phi::floating_point<long double>>();

    test_make_safe<bool, phi::boolean>();
    test_make_safe<phi::boolean, phi::boolean>();
    test_make_safe<wchar_t, wchar_t>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_make_safe<char8_t, char8_t>();
#endif
    test_make_safe<char16_t, char16_t>();
    test_make_safe<char32_t, char32_t>();
}
