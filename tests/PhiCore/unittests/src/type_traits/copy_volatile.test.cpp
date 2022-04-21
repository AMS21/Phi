#include <phi/test/test_macros.hpp>

#include <phi/type_traits/copy_volatile.hpp>

template <typename T, typename U, typename V>
void test_copy_volatile_impl()
{
    CHECK_SAME_TYPE(typename phi::copy_volatile<T, U>::type, V);
    CHECK_SAME_TYPE(phi::copy_volatile_t<T, U>, V);
}

template <typename T, typename U>
void test_copy_volatile()
{
    test_copy_volatile_impl<T, U, U>();
    test_copy_volatile_impl<T, const U, const U>();
    test_copy_volatile_impl<T, volatile U, volatile U>();
    test_copy_volatile_impl<T, const volatile U, const volatile U>();

    test_copy_volatile_impl<const T, U, U>();
    test_copy_volatile_impl<const T, const U, const U>();
    test_copy_volatile_impl<const T, volatile U, volatile U>();
    test_copy_volatile_impl<const T, const volatile U, const volatile U>();

    test_copy_volatile_impl<volatile T, U, volatile U>();
    test_copy_volatile_impl<volatile T, const U, const volatile U>();
    test_copy_volatile_impl<volatile T, volatile U, volatile U>();
    test_copy_volatile_impl<volatile T, const volatile U, const volatile U>();

    test_copy_volatile_impl<const volatile T, U, volatile U>();
    test_copy_volatile_impl<const volatile T, const U, const volatile U>();
    test_copy_volatile_impl<const volatile T, volatile U, volatile U>();
    test_copy_volatile_impl<const volatile T, const volatile U, const volatile U>();
}

struct A
{};

TEST_CASE("copy_volatile")
{
    test_copy_volatile<void, void>();
    test_copy_volatile<void, int>();
    test_copy_volatile<int, void>();
    test_copy_volatile<int, int>();
    test_copy_volatile<int, float>();
    test_copy_volatile<float, int>();
    test_copy_volatile<float, float>();
    test_copy_volatile<A, A>();
    test_copy_volatile<A, int>();
    test_copy_volatile<int, A>();
}
