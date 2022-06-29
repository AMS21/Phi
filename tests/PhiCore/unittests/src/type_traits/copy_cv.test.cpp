#include <phi/test/test_macros.hpp>

#include <phi/type_traits/copy_cv.hpp>

template <typename Type1T, typename Type2T, typename Type3T>
void test_copy_cv_impl()
{
    CHECK_SAME_TYPE(typename phi::copy_cv<Type1T, Type2T>::type, Type3T);
    CHECK_SAME_TYPE(phi::copy_cv_t<Type1T, Type2T>, Type3T);
}

template <typename Type1T, typename Type2T>
void test_copy_cv()
{
    test_copy_cv_impl<Type1T, Type2T, Type2T>();
    test_copy_cv_impl<const Type1T, Type2T, const Type2T>();
    test_copy_cv_impl<volatile Type1T, Type2T, volatile Type2T>();
    test_copy_cv_impl<const volatile Type1T, Type2T, const volatile Type2T>();

    test_copy_cv_impl<Type1T, const Type2T, const Type2T>();
    test_copy_cv_impl<const Type1T, const Type2T, const Type2T>();
    test_copy_cv_impl<volatile Type1T, const Type2T, const volatile Type2T>();
    test_copy_cv_impl<const volatile Type1T, const Type2T, const volatile Type2T>();

    test_copy_cv_impl<Type1T, volatile Type2T, volatile Type2T>();
    test_copy_cv_impl<const Type1T, volatile Type2T, const volatile Type2T>();
    test_copy_cv_impl<volatile Type1T, volatile Type2T, volatile Type2T>();
    test_copy_cv_impl<const volatile Type1T, volatile Type2T, const volatile Type2T>();

    test_copy_cv_impl<Type1T, const volatile Type2T, const volatile Type2T>();
    test_copy_cv_impl<const Type1T, const volatile Type2T, const volatile Type2T>();
    test_copy_cv_impl<volatile Type1T, const volatile Type2T, const volatile Type2T>();
    test_copy_cv_impl<const volatile Type1T, const volatile Type2T, const volatile Type2T>();
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
