#include <phi/test/test_macros.hpp>

#include <phi/type_traits/copy_const.hpp>

template <typename Type1T, typename Type2T, typename Type3T>
void test_copy_const_impl()
{
    CHECK_SAME_TYPE(typename phi::copy_const<Type1T, Type2T>::type, Type3T);
    CHECK_SAME_TYPE(phi::copy_const_t<Type1T, Type2T>, Type3T);
}

template <typename Type1T, typename Type2T>
void test_copy_const()
{
    test_copy_const_impl<Type1T, Type2T, Type2T>();
    test_copy_const_impl<Type1T, const Type2T, const Type2T>();
    test_copy_const_impl<Type1T, volatile Type2T, volatile Type2T>();
    test_copy_const_impl<Type1T, const volatile Type2T, const volatile Type2T>();

    test_copy_const_impl<const Type1T, Type2T, const Type2T>();
    test_copy_const_impl<const Type1T, const Type2T, const Type2T>();
    test_copy_const_impl<const Type1T, volatile Type2T, const volatile Type2T>();
    test_copy_const_impl<const Type1T, const volatile Type2T, const volatile Type2T>();

    test_copy_const_impl<volatile Type1T, Type2T, Type2T>();
    test_copy_const_impl<volatile Type1T, const Type2T, const Type2T>();
    test_copy_const_impl<volatile Type1T, volatile Type2T, volatile Type2T>();
    test_copy_const_impl<volatile Type1T, const volatile Type2T, const volatile Type2T>();

    test_copy_const_impl<const volatile Type1T, Type2T, const Type2T>();
    test_copy_const_impl<const volatile Type1T, const Type2T, const Type2T>();
    test_copy_const_impl<const volatile Type1T, volatile Type2T, const volatile Type2T>();
    test_copy_const_impl<const volatile Type1T, const volatile Type2T, const volatile Type2T>();
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
