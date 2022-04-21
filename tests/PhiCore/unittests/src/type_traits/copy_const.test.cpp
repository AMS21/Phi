#include <phi/test/test_macros.hpp>

#include <phi/type_traits/copy_const.hpp>

template <typename T, typename U, typename V>
void test_copy_const_impl()
{
    CHECK_SAME_TYPE(typename phi::copy_const<T, U>::type, V);
    CHECK_SAME_TYPE(phi::copy_const_t<T, U>, V);
}

template <typename T, typename U>
void test_copy_const()
{
    test_copy_const_impl<T, U, U>();
    test_copy_const_impl<T, const U, const U>();
    test_copy_const_impl<T, volatile U, volatile U>();
    test_copy_const_impl<T, const volatile U, const volatile U>();

    test_copy_const_impl<const T, U, const U>();
    test_copy_const_impl<const T, const U, const U>();
    test_copy_const_impl<const T, volatile U, const volatile U>();
    test_copy_const_impl<const T, const volatile U, const volatile U>();

    test_copy_const_impl<volatile T, U, U>();
    test_copy_const_impl<volatile T, const U, const U>();
    test_copy_const_impl<volatile T, volatile U, volatile U>();
    test_copy_const_impl<volatile T, const volatile U, const volatile U>();

    test_copy_const_impl<const volatile T, U, const U>();
    test_copy_const_impl<const volatile T, const U, const U>();
    test_copy_const_impl<const volatile T, volatile U, const volatile U>();
    test_copy_const_impl<const volatile T, const volatile U, const volatile U>();
}

struct A
{};

TEST_CASE("copy_const")
{
    test_copy_const<void, void>();
    test_copy_const<void, int>();
    test_copy_const<int, void>();
    test_copy_const<int, int>();
    test_copy_const<float, float>();
    test_copy_const<int, float>();
    test_copy_const<float, int>();
    test_copy_const<A, A>();
    test_copy_const<A, int>();
    test_copy_const<int, A>();
}
