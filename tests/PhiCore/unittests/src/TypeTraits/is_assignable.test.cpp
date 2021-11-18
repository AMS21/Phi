#include <Phi/Test/TestMacros.hpp>

#include <Phi/TypeTraits/is_assignable.hpp>

struct A
{};

struct B
{
    void operator=(A);
};

template <typename T, typename U>
void test_is_assignable()
{
    STATIC_REQUIRE(phi::is_assignable<T, U>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_assignable_v<T, U>);
#endif
}

template <typename T, typename U>
void test_is_not_assignable()
{
    STATIC_REQUIRE_FALSE(phi::is_assignable<T, U>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_assignable_v<T, U>);
#endif
}

struct D;

struct C
{
    template <typename U>
    D operator,(U&&);
};

struct E
{
    C operator=(int);
};

template <typename T>
struct X
{
    T t;
};

TEST_CASE("is_assignable")
{
    test_is_assignable<int&, int&>();
    test_is_assignable<int&, int>();
    test_is_assignable<int&, double>();
    test_is_assignable<B, A>();
    test_is_assignable<void*&, void*>();

    test_is_assignable<E, int>();

    test_is_not_assignable<int, int&>();
    test_is_not_assignable<int, int>();

    test_is_not_assignable<A, B>();
    test_is_not_assignable<void, const void>();
    test_is_not_assignable<const void, const void>();
    test_is_not_assignable<int(), int>();

    // pointer to incomplete template type
    test_is_assignable<X<D>*&, X<D>*>();
}
