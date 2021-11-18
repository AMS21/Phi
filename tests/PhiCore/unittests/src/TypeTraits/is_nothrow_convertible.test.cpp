#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/TypeTraits/is_nothrow_convertible.hpp>

template <typename LhsT, typename RhsT>
void test_is_nothrow_convertible()
{
    STATIC_REQUIRE(phi::is_nothrow_convertible<LhsT, RhsT>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_convertible_v<LhsT, RhsT>);
#endif
}

template <typename LhsT, typename RhsT>
void test_is_not_nothrow_convertible()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_convertible<LhsT, RhsT>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_convertible_v<LhsT, RhsT>);
#endif
}

struct A
{};

struct B
{
public:
    operator A()
    {
        return a;
    }
    A a;
};

class C
{};

class D
{
public:
    operator C() noexcept
    {
        return c;
    }
    C c;
};

TEST_CASE("is_nothrow_convertible")
{
    test_is_nothrow_convertible<int, double>();
    test_is_not_nothrow_convertible<int, char*>();

    test_is_not_nothrow_convertible<A, B>();
    test_is_nothrow_convertible<D, C>();

    test_is_nothrow_convertible<int, double>();
    test_is_not_nothrow_convertible<int, char*>();

    test_is_not_nothrow_convertible<A, B>();
    test_is_nothrow_convertible<D, C>();

    test_is_nothrow_convertible<void, const void>();
    test_is_nothrow_convertible<void, volatile void>();
    test_is_nothrow_convertible<void, const volatile void>();
    test_is_nothrow_convertible<const void, void>();
    test_is_nothrow_convertible<const void, volatile void>();
    test_is_nothrow_convertible<const void, const volatile void>();
    test_is_nothrow_convertible<volatile void, void>();
    test_is_nothrow_convertible<volatile void, const void>();
    test_is_nothrow_convertible<volatile void, const volatile void>();
    test_is_nothrow_convertible<const volatile void, void>();
    test_is_nothrow_convertible<const volatile void, const void>();
    test_is_nothrow_convertible<const volatile void, volatile void>();

    test_is_not_nothrow_convertible<int[], double[]>();
    test_is_not_nothrow_convertible<int[], int[]>();
    test_is_not_nothrow_convertible<int[10], int[10]>();
    test_is_not_nothrow_convertible<int[10], double[10]>();
    test_is_not_nothrow_convertible<int[5], double[10]>();
    test_is_not_nothrow_convertible<int[10], A[10]>();

    typedef void V();
    typedef int  I();
    test_is_not_nothrow_convertible<V, V>();
    test_is_not_nothrow_convertible<V, I>();
}
