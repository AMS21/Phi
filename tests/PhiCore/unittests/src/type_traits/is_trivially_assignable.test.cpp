#include <phi/test/test_macros.hpp>

#include <phi/type_traits/is_assignable.hpp>
#include <phi/type_traits/is_trivially_assignable.hpp>
#include <type_traits>

template <typename T, typename U>
void test_is_trivially_assignable()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_ASSIGNABLE()
    STATIC_REQUIRE(phi::is_trivially_assignable<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_assignable<T, U>::value);
    STATIC_REQUIRE(phi::is_assignable<T, U>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_assignable_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_assignable_v<T, U>);
    STATIC_REQUIRE(phi::is_assignable_v<T, U>);
#    endif

    STATIC_REQUIRE(std::is_trivially_assignable<T, U>::value);
#endif
}

template <typename T, typename U>
void test_is_not_trivially_assignable()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_ASSIGNABLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_assignable<T, U>::value);
    STATIC_REQUIRE(phi::is_not_trivially_assignable<T, U>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_assignable_v<T, U>);
    STATIC_REQUIRE(phi::is_not_trivially_assignable_v<T, U>);
#    endif

    STATIC_REQUIRE_FALSE(std::is_trivially_assignable<T, U>::value);
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
