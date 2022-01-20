#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/type_traits/is_convertible.hpp>
#include <phi/type_traits/is_nothrow_convertible.hpp>
#include <type_traits>

template <typename FromT, typename ToT>
void test_is_nothrow_convertible()
{
    STATIC_REQUIRE(phi::is_nothrow_convertible<FromT, ToT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_convertible<FromT, ToT>::value);
    STATIC_REQUIRE(phi::is_convertible<FromT, ToT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_convertible_v<FromT, ToT>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_convertible_v<FromT, ToT>);
    STATIC_REQUIRE(phi::is_convertible_v<FromT, ToT>);
#endif

    // Standard compatbililty
#if PHI_CPP_STANDARD_IS_ATLEAST(20)
    STATIC_REQUIRE(std::is_convertible<FromT, ToT>::value);
    STATIC_REQUIRE(std::is_nothrow_convertible<FromT, ToT>::value);
#endif
}

template <typename FromT, typename ToT>
void test_is_not_nothrow_convertible()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_convertible<FromT, ToT>::value);
    STATIC_REQUIRE(phi::is_not_nothrow_convertible<FromT, ToT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_convertible_v<FromT, ToT>);
    STATIC_REQUIRE(phi::is_not_nothrow_convertible_v<FromT, ToT>);
#endif

    // Standard compatbililty
#if PHI_CPP_STANDARD_IS_ATLEAST(20)
    STATIC_REQUIRE_FALSE(std::is_nothrow_convertible<FromT, ToT>::value);
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

    using V = void();
    using I = int();
    test_is_not_nothrow_convertible<V, V>();
    test_is_not_nothrow_convertible<V, I>();
}
