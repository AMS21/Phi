#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_nothrow_copy_assignable.hpp>

template <typename T>
void test_is_nothrow_copy_assignable()
{
    STATIC_REQUIRE(phi::is_nothrow_copy_assignable<T>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_copy_assignable_v<T>);
#endif
}

template <typename T>
void test_is_not_nothrow_copy_assignable()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_assignable<T>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_assignable_v<T>);
#endif
}

struct A
{
    A& operator=(const A&);
};

struct B
{
    B& operator=(const B&) noexcept;
};

TEST_CASE("is_nothrow_copy_assignable")
{
    test_is_nothrow_copy_assignable<phi::nullptr_t>();
    test_is_nothrow_copy_assignable<bool>();
    test_is_nothrow_copy_assignable<char>();
    test_is_nothrow_copy_assignable<signed char>();
    test_is_nothrow_copy_assignable<unsigned char>();
    test_is_nothrow_copy_assignable<short>();
    test_is_nothrow_copy_assignable<unsigned short>();
    test_is_nothrow_copy_assignable<int>();
    test_is_nothrow_copy_assignable<unsigned int>();
    test_is_nothrow_copy_assignable<long>();
    test_is_nothrow_copy_assignable<unsigned long>();
    test_is_nothrow_copy_assignable<long long>();
    test_is_nothrow_copy_assignable<unsigned long long>();
    test_is_nothrow_copy_assignable<float>();
    test_is_nothrow_copy_assignable<double>();
    test_is_nothrow_copy_assignable<long double>();
    test_is_nothrow_copy_assignable<char8_t>();
    test_is_nothrow_copy_assignable<char16_t>();
    test_is_nothrow_copy_assignable<char32_t>();
    test_is_nothrow_copy_assignable<wchar_t>();

    test_is_nothrow_copy_assignable<volatile int>();
    test_is_nothrow_copy_assignable<volatile int&>();
    test_is_nothrow_copy_assignable<volatile int&&>();

    test_is_nothrow_copy_assignable<int&>();
    test_is_nothrow_copy_assignable<int&&>();
    test_is_nothrow_copy_assignable<int*>();
    test_is_nothrow_copy_assignable<const int*>();
    test_is_nothrow_copy_assignable<volatile int*>();
    test_is_nothrow_copy_assignable<const volatile int*>();
    test_is_nothrow_copy_assignable<int**>();
    test_is_nothrow_copy_assignable<Class>();
    test_is_nothrow_copy_assignable<Union>();
    test_is_nothrow_copy_assignable<NonEmptyUnion>();
    test_is_nothrow_copy_assignable<Empty>();
    test_is_nothrow_copy_assignable<NotEmpty>();
    test_is_nothrow_copy_assignable<bit_zero>();
    test_is_nothrow_copy_assignable<bit_one>();
    test_is_nothrow_copy_assignable<Abstract>();
    test_is_nothrow_copy_assignable<AbstractTemplate<int>>();
    test_is_nothrow_copy_assignable<AbstractTemplate<double>>();
    test_is_nothrow_copy_assignable<AbstractTemplate<Class>>();
    test_is_nothrow_copy_assignable<Enum>();
    test_is_nothrow_copy_assignable<EnumSigned>();
    test_is_nothrow_copy_assignable<EnumUnsigned>();
    test_is_nothrow_copy_assignable<EnumClass>();
    test_is_nothrow_copy_assignable<FunctionPtr>();
    test_is_nothrow_copy_assignable<MemberObjectPtr>();
    test_is_nothrow_copy_assignable<MemberFunctionPtr>();

    test_is_not_nothrow_copy_assignable<const int>();
    test_is_not_nothrow_copy_assignable<const volatile int>();
    test_is_not_nothrow_copy_assignable<const int&>();
    test_is_not_nothrow_copy_assignable<const volatile int&>();
    test_is_not_nothrow_copy_assignable<const int&&>();
    test_is_not_nothrow_copy_assignable<const volatile int&&>();
    test_is_not_nothrow_copy_assignable<void>();
    test_is_not_nothrow_copy_assignable<const void>();
    test_is_not_nothrow_copy_assignable<volatile void>();
    test_is_not_nothrow_copy_assignable<const volatile void>();
    test_is_not_nothrow_copy_assignable<Function>();

    test_is_not_nothrow_copy_assignable<A>();
    test_is_nothrow_copy_assignable<B>();
    test_is_not_nothrow_copy_assignable<const A>();
    test_is_not_nothrow_copy_assignable<const B>();
}
