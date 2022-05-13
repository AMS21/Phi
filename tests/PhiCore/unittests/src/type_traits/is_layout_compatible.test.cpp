#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_layout_compatible.hpp>
#include <vector>

template <typename T, typename U>
void test_is_layout_compatible_impl()
{
#if PHI_HAS_WORKING_IS_LAYOUT_COMPATIBLE()
    STATIC_REQUIRE(phi::is_layout_compatible<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_layout_compatible<T, U>::value);
    STATIC_REQUIRE(phi::is_layout_compatible<U, T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_layout_compatible<U, T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_layout_compatible_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_layout_compatible_v<T, U>);
    STATIC_REQUIRE(phi::is_layout_compatible_v<U, T>);
    STATIC_REQUIRE_FALSE(phi::is_not_layout_compatible_v<U, T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_layout_compatible<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_layout_compatible<U, T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_layout_compatible<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_layout_compatible<U, T>);

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_ATLEAST(20)
    STATIC_REQUIRE(std::is_layout_compatible<T, U>::value);
    STATIC_REQUIRE(std::is_layout_compatible<U, T>::value);
#    endif
#endif
}

template <typename T, typename U>
void test_is_not_layout_compatible_impl()
{
#if PHI_HAS_WORKING_IS_LAYOUT_COMPATIBLE()
    STATIC_REQUIRE_FALSE(phi::is_layout_compatible<T, U>::value);
    STATIC_REQUIRE(phi::is_not_layout_compatible<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_layout_compatible<U, T>::value);
    STATIC_REQUIRE(phi::is_not_layout_compatible<U, T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_layout_compatible_v<T, U>);
    STATIC_REQUIRE(phi::is_not_layout_compatible_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_layout_compatible_v<U, T>);
    STATIC_REQUIRE(phi::is_not_layout_compatible_v<U, T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_layout_compatible<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_layout_compatible<U, T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_layout_compatible<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_layout_compatible<U, T>);

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_ATLEAST(20)
    STATIC_REQUIRE_FALSE(std::is_layout_compatible<T, U>::value);
    STATIC_REQUIRE_FALSE(std::is_layout_compatible<U, T>::value);
#    endif
#endif
}

template <typename T, typename U>
void test_is_layout_compatible()
{
    test_is_layout_compatible_impl<T, U>();
    test_is_layout_compatible_impl<T, const U>();
    test_is_layout_compatible_impl<T, volatile U>();
    test_is_layout_compatible_impl<T, const volatile U>();

    test_is_layout_compatible_impl<const T, U>();
    test_is_layout_compatible_impl<const T, const U>();
    test_is_layout_compatible_impl<const T, volatile U>();
    test_is_layout_compatible_impl<const T, const volatile U>();

    test_is_layout_compatible_impl<volatile T, U>();
    test_is_layout_compatible_impl<volatile T, const U>();
    test_is_layout_compatible_impl<volatile T, volatile U>();
    test_is_layout_compatible_impl<volatile T, const volatile U>();

    test_is_layout_compatible_impl<const volatile T, U>();
    test_is_layout_compatible_impl<const volatile T, const U>();
    test_is_layout_compatible_impl<const volatile T, volatile U>();
    test_is_layout_compatible_impl<const volatile T, const volatile U>();
}

template <typename T, typename U>
void test_is_not_layout_compatible()
{
    test_is_not_layout_compatible_impl<T, U>();
    test_is_not_layout_compatible_impl<T, const U>();
    test_is_not_layout_compatible_impl<T, volatile U>();
    test_is_not_layout_compatible_impl<T, const volatile U>();

    test_is_not_layout_compatible_impl<const T, U>();
    test_is_not_layout_compatible_impl<const T, const U>();
    test_is_not_layout_compatible_impl<const T, volatile U>();
    test_is_not_layout_compatible_impl<const T, const volatile U>();

    test_is_not_layout_compatible_impl<volatile T, U>();
    test_is_not_layout_compatible_impl<volatile T, const U>();
    test_is_not_layout_compatible_impl<volatile T, volatile U>();
    test_is_not_layout_compatible_impl<volatile T, const volatile U>();

    test_is_not_layout_compatible_impl<const volatile T, U>();
    test_is_not_layout_compatible_impl<const volatile T, const U>();
    test_is_not_layout_compatible_impl<const volatile T, volatile U>();
    test_is_not_layout_compatible_impl<const volatile T, const volatile U>();
}

struct Incomplete;

enum E1 : int
{
};

enum E2 : int;

enum E3 : unsigned int;

enum E4 : char
{
};

enum E5 : signed char
{
};

enum E6 : unsigned char
{
};

enum class E7 : int
{
};

enum E8 : int
{
};

enum class E9 : int
{
};

struct A
{
    int a;
};

struct B
{
    const int b;
};

struct C : A
{};

struct D : B
{};

struct E : A
{
    int i;
}; // not standard-layout

struct Foo
{
    int  x;
    char y;
};

class Bar
{
    const int     u = 42;
    volatile char v = '*';
};

TEST_CASE("is_layout_compatible")
{
    test_is_layout_compatible<void, void>();

    test_is_layout_compatible<int, int>();
    test_is_not_layout_compatible<int, int[]>();
    test_is_not_layout_compatible<int, int[1]>();
    test_is_layout_compatible<int[], int[]>();
    test_is_layout_compatible<int[1], int[1]>();
    test_is_not_layout_compatible<int[1], int[]>();
    test_is_not_layout_compatible<int[1], int[2]>();

    // The standard says these are undefined, but they should work really:
    //test_is_layout_compatible<Incomplete, Incomplete>();
    //test_is_not_layout_compatible<Incomplete[], Incomplete>();
    test_is_layout_compatible<Incomplete[], Incomplete[]>();

    test_is_not_layout_compatible<int, E1>();

    test_is_layout_compatible<E1, E2>();
    test_is_not_layout_compatible<E1, E3>();

    test_is_not_layout_compatible<E4, E5>();
    test_is_not_layout_compatible<E4, E6>();
    test_is_not_layout_compatible<E5, E6>();

    test_is_layout_compatible<E1, E7>();

    test_is_layout_compatible<A, B>();
    test_is_layout_compatible<B, A>();

    test_is_layout_compatible<C, D>();

    test_is_not_layout_compatible<E, A>();

    test_is_layout_compatible<Foo, Bar>();
    test_is_not_layout_compatible<Foo[2], Bar[2]>();

    test_is_not_layout_compatible<int, E8>();
    test_is_layout_compatible<E8, E9>();

    test_is_not_layout_compatible<long, unsigned long>();
    test_is_not_layout_compatible<char*, const char*>();
    test_is_layout_compatible<char*, char* const>();

    test_is_not_layout_compatible<void*, int*>();
    test_is_not_layout_compatible<void*, unsigned*>();
    test_is_not_layout_compatible<void*, int>();

    test_is_not_layout_compatible<int*, void*>();
    test_is_not_layout_compatible<unsigned*, void*>();
    test_is_not_layout_compatible<int, void*>();

    test_is_not_layout_compatible<bit_zero, bit_one>();
}
