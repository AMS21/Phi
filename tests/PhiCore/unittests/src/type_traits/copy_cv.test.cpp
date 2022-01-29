#include <phi/test/test_macros.hpp>

#include <phi/type_traits/copy_cv.hpp>

template <typename T, typename U, typename V>
void test_copy_cv()
{
    CHECK_SAME_TYPE(typename phi::copy_cv<T, U>::type, V);
    CHECK_SAME_TYPE(phi::copy_cv_t<T, U>, V);
}

TEST_CASE("copy_cv")
{
    test_copy_cv<int, float, float>();
    test_copy_cv<int, const float, const float>();
    test_copy_cv<int, volatile float, volatile float>();
    test_copy_cv<int, const volatile float, const volatile float>();

    test_copy_cv<const int, float, const float>();
    test_copy_cv<const int, const float, const float>();
    test_copy_cv<const int, volatile float, const volatile float>();
    test_copy_cv<const int, const volatile float, const volatile float>();

    test_copy_cv<volatile int, float, volatile float>();
    test_copy_cv<volatile int, const float, const volatile float>();
    test_copy_cv<volatile int, volatile float, volatile float>();
    test_copy_cv<volatile int, const volatile float, const volatile float>();

    test_copy_cv<const volatile int, float, const volatile float>();
    test_copy_cv<const volatile int, const float, const volatile float>();
    test_copy_cv<const volatile int, volatile float, const volatile float>();
    test_copy_cv<const volatile int, const volatile float, const volatile float>();
}
