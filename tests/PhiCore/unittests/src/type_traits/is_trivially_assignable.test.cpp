#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/type_traits/is_assignable.hpp>
#include <phi/type_traits/is_trivially_assignable.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <type_traits>
PHI_EXTERNAL_HEADERS_END()

template <typename TypeT, typename OtherT>
void test_is_trivially_assignable()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_ASSIGNABLE()
    STATIC_REQUIRE(phi::is_trivially_assignable<TypeT, OtherT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_assignable<TypeT, OtherT>::value);
    STATIC_REQUIRE(phi::is_assignable<TypeT, OtherT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_assignable_v<TypeT, OtherT>);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_assignable_v<TypeT, OtherT>);
    STATIC_REQUIRE(phi::is_assignable_v<TypeT, OtherT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivially_assignable<TypeT, OtherT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivially_assignable<TypeT, OtherT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_trivially_assignable<TypeT, OtherT>::value);
#endif
}

template <typename TypeT, typename OtherT>
void test_is_not_trivially_assignable()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_ASSIGNABLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_assignable<TypeT, OtherT>::value);
    STATIC_REQUIRE(phi::is_not_trivially_assignable<TypeT, OtherT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_assignable_v<TypeT, OtherT>);
    STATIC_REQUIRE(phi::is_not_trivially_assignable_v<TypeT, OtherT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivially_assignable<TypeT, OtherT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivially_assignable<TypeT, OtherT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_trivially_assignable<TypeT, OtherT>::value);
#endif
}

struct A
{};

struct B
{
    B& operator=(A);
};

struct C
{
    // NOLINTNEXTLINE(misc-unconventional-assign-operator)
    C& operator=(C&); // not const
};

struct D
{
    D& operator=(const D&) = default;
};

struct E
{
    E& operator=(const E&);
};

TEST_CASE("is_trivially_assignable")
{
    test_is_trivially_assignable<int&, int>();
    test_is_trivially_assignable<int&, int&>();
    test_is_trivially_assignable<int&, double>();

    test_is_not_trivially_assignable<int, int&>();
    test_is_not_trivially_assignable<int, int>();
    test_is_not_trivially_assignable<B, A>();
    test_is_not_trivially_assignable<A, B>();
    test_is_not_trivially_assignable<C&, C&>();
    test_is_trivially_assignable<D&, const D&>();
    test_is_not_trivially_assignable<E&, const E&>();
}
