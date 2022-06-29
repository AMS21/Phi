#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/type_traits/is_assignable.hpp>
#include <type_traits>

struct A
{};

struct B
{
    // NOLINTNEXTLINE(misc-unconventional-assign-operator)
    void operator=(A);
};

template <typename TypeT, typename ArgT>
void test_is_assignable()
{
    STATIC_REQUIRE(phi::is_assignable<TypeT, ArgT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_assignable<TypeT, ArgT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_assignable_v<TypeT, ArgT>);
    STATIC_REQUIRE_FALSE(phi::is_not_assignable_v<TypeT, ArgT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_assignable<TypeT, ArgT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_assignable<TypeT, ArgT>);

    // Standard compatbilility
    STATIC_REQUIRE(std::is_assignable<TypeT, ArgT>::value);
}

template <typename TypeT, typename ArgT>
void test_is_not_assignable()
{
    STATIC_REQUIRE_FALSE(phi::is_assignable<TypeT, ArgT>::value);
    STATIC_REQUIRE(phi::is_not_assignable<TypeT, ArgT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_assignable_v<TypeT, ArgT>);
    STATIC_REQUIRE(phi::is_not_assignable_v<TypeT, ArgT>);
#endif

    // Standard compatbilility
    STATIC_REQUIRE_FALSE(std::is_assignable<TypeT, ArgT>::value);
}

struct D;

struct C
{
    template <typename OtherT>
    D operator,(OtherT&&);
};

struct E
{
    // NOLINTNEXTLINE(misc-unconventional-assign-operator)
    C operator=(int);
};

template <typename TypeT>
struct X
{
    TypeT t;
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
