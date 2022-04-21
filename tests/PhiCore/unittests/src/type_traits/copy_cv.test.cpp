#include <phi/test/test_macros.hpp>

#include <phi/type_traits/copy_cv.hpp>

template <typename T, typename U, typename V>
void test_copy_cv_impl()
{
    CHECK_SAME_TYPE(typename phi::copy_cv<T, U>::type, V);
    CHECK_SAME_TYPE(phi::copy_cv_t<T, U>, V);
}

template <typename T, typename U>
void test_copy_cv()
{
    test_copy_cv_impl<T, U, U>();
    test_copy_cv_impl<const T, U, const U>();
    test_copy_cv_impl<volatile T, U, volatile U>();
    test_copy_cv_impl<const volatile T, U, const volatile U>();

    test_copy_cv_impl<T, const U, const U>();
    test_copy_cv_impl<const T, const U, const U>();
    test_copy_cv_impl<volatile T, const U, const volatile U>();
    test_copy_cv_impl<const volatile T, const U, const volatile U>();

    test_copy_cv_impl<T, volatile U, volatile U>();
    test_copy_cv_impl<const T, volatile U, const volatile U>();
    test_copy_cv_impl<volatile T, volatile U, volatile U>();
    test_copy_cv_impl<const volatile T, volatile U, const volatile U>();

    test_copy_cv_impl<T, const volatile U, const volatile U>();
    test_copy_cv_impl<const T, const volatile U, const volatile U>();
    test_copy_cv_impl<volatile T, const volatile U, const volatile U>();
    test_copy_cv_impl<const volatile T, const volatile U, const volatile U>();
}

struct A
{};

TEST_CASE("copy_cv")
{
    test_copy_cv<void, void>();
    test_copy_cv<void, int>();
    test_copy_cv<int, void>();
    test_copy_cv<int, int>();
    test_copy_cv<int, float>();
    test_copy_cv<float, int>();
    test_copy_cv<float, float>();
    test_copy_cv<A, A>();
    test_copy_cv<int, A>();
    test_copy_cv<A, int>();
}
