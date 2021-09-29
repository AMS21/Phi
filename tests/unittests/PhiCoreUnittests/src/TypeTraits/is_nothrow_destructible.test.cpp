#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_nothrow_destructible.hpp>

template <typename T>
void test_is_nothrow_destructible()
{
    STATIC_REQUIRE(phi::is_nothrow_destructible<T>::value);
    STATIC_REQUIRE(phi::is_nothrow_destructible<const T>::value);
    STATIC_REQUIRE(phi::is_nothrow_destructible<volatile T>::value);
    STATIC_REQUIRE(phi::is_nothrow_destructible<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_destructible_v<T>);
    STATIC_REQUIRE(phi::is_nothrow_destructible_v<const T>);
    STATIC_REQUIRE(phi::is_nothrow_destructible_v<volatile T>);
    STATIC_REQUIRE(phi::is_nothrow_destructible_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_nothrow_destructible()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_destructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_destructible<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_destructible<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_destructible<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_destructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_destructible_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_destructible_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_destructible_v<const volatile T>);
#endif
}

struct PublicDestructor
{
public:
    ~PublicDestructor() = default;
};
struct ProtectedDestructor
{
protected:
    ~ProtectedDestructor() = default;
};
struct PrivateDestructor
{
private:
    ~PrivateDestructor() = default;
};

struct VirtualPublicDestructor
{
public:
    virtual ~VirtualPublicDestructor() = default;
};
struct VirtualProtectedDestructor
{
protected:
    virtual ~VirtualProtectedDestructor() = default;
};
struct VirtualPrivateDestructor
{
private:
    virtual ~VirtualPrivateDestructor() = default;
};

struct PurePublicDestructor
{
public:
    virtual ~PurePublicDestructor() = 0;
};
struct PureProtectedDestructor
{
protected:
    virtual ~PureProtectedDestructor() = 0;
};
struct PurePrivateDestructor
{
private:
    virtual ~PurePrivateDestructor() = 0;
};

class A
{
    virtual void foo() = 0;
};

struct B
{
    ~B() noexcept(false);
};

struct C
{
    ~C() noexcept;
};

TEST_CASE("is_nothrow_destructible")
{
    test_is_not_nothrow_destructible<void>();
    test_is_not_nothrow_destructible<char[]>();
    test_is_not_nothrow_destructible<char[][3]>();

    test_is_nothrow_destructible<phi::nullptr_t>();
    test_is_nothrow_destructible<bool>();
    test_is_nothrow_destructible<char>();
    test_is_nothrow_destructible<signed char>();
    test_is_nothrow_destructible<unsigned char>();
    test_is_nothrow_destructible<short>();
    test_is_nothrow_destructible<unsigned short>();
    test_is_nothrow_destructible<int>();
    test_is_nothrow_destructible<unsigned int>();
    test_is_nothrow_destructible<long>();
    test_is_nothrow_destructible<unsigned long>();
    test_is_nothrow_destructible<long long>();
    test_is_nothrow_destructible<unsigned long long>();
    test_is_nothrow_destructible<float>();
    test_is_nothrow_destructible<double>();
    test_is_nothrow_destructible<long double>();
    test_is_nothrow_destructible<char8_t>();
    test_is_nothrow_destructible<char16_t>();
    test_is_nothrow_destructible<char32_t>();
    test_is_nothrow_destructible<wchar_t>();

    test_is_nothrow_destructible<int&>();
    test_is_nothrow_destructible<int&&>();
    test_is_nothrow_destructible<int*>();
    test_is_nothrow_destructible<const int*>();
    test_is_nothrow_destructible<volatile int*>();
    test_is_nothrow_destructible<const volatile int*>();
    test_is_nothrow_destructible<int**>();
    test_is_nothrow_destructible<char[3]>();
    test_is_not_nothrow_destructible<char[]>();
    test_is_nothrow_destructible<Class>();
    test_is_nothrow_destructible<Struct>();
    test_is_nothrow_destructible<Union>();
    test_is_nothrow_destructible<NonEmptyUnion>();
    test_is_nothrow_destructible<Empty>();
    test_is_nothrow_destructible<NotEmpty>();
    test_is_nothrow_destructible<bit_zero>();
    test_is_nothrow_destructible<bit_one>();
    test_is_not_nothrow_destructible<Abstract>();
    test_is_nothrow_destructible<AbstractTemplate<int>>();
    test_is_nothrow_destructible<AbstractTemplate<double>>();
    test_is_nothrow_destructible<AbstractTemplate<Class>>();
    test_is_nothrow_destructible<Enum>();
    test_is_nothrow_destructible<EnumSigned>();
    test_is_nothrow_destructible<EnumUnsigned>();
    test_is_nothrow_destructible<EnumClass>();
    test_is_not_nothrow_destructible<Function>();
    test_is_nothrow_destructible<FunctionPtr>();
    test_is_nothrow_destructible<MemberObjectPtr>();
    test_is_nothrow_destructible<MemberFunctionPtr>();

    // requires noexcept. These are all destructible.
    test_is_nothrow_destructible<PublicDestructor>();
    test_is_nothrow_destructible<VirtualPublicDestructor>();
    test_is_nothrow_destructible<PurePublicDestructor>();
    test_is_nothrow_destructible<A>();

    test_is_not_nothrow_destructible<B>();
    test_is_nothrow_destructible<C>();

    // requires access control
    test_is_not_nothrow_destructible<ProtectedDestructor>();
    test_is_not_nothrow_destructible<PrivateDestructor>();
    test_is_not_nothrow_destructible<VirtualProtectedDestructor>();
    test_is_not_nothrow_destructible<VirtualPrivateDestructor>();
    test_is_not_nothrow_destructible<PureProtectedDestructor>();
    test_is_not_nothrow_destructible<PurePrivateDestructor>();
}
