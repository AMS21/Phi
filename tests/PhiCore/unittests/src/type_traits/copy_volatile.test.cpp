#include <phi/test/test_macros.hpp>

#include <phi/type_traits/copy_volatile.hpp>

template <typename Type1T, typename Type2T, typename Type3T>
void test_copy_volatile_impl()
{
    CHECK_SAME_TYPE(typename phi::copy_volatile<Type1T, Type2T>::type, Type3T);
    CHECK_SAME_TYPE(phi::copy_volatile_t<Type1T, Type2T>, Type3T);
}

template <typename Type1T, typename Type2T>
void test_copy_volatile()
{
    test_copy_volatile_impl<Type1T, Type2T, Type2T>();
    test_copy_volatile_impl<Type1T, const Type2T, const Type2T>();
    test_copy_volatile_impl<Type1T, volatile Type2T, volatile Type2T>();
    test_copy_volatile_impl<Type1T, const volatile Type2T, const volatile Type2T>();

    test_copy_volatile_impl<const Type1T, Type2T, Type2T>();
    test_copy_volatile_impl<const Type1T, const Type2T, const Type2T>();
    test_copy_volatile_impl<const Type1T, volatile Type2T, volatile Type2T>();
    test_copy_volatile_impl<const Type1T, const volatile Type2T, const volatile Type2T>();

    test_copy_volatile_impl<volatile Type1T, Type2T, volatile Type2T>();
    test_copy_volatile_impl<volatile Type1T, const Type2T, const volatile Type2T>();
    test_copy_volatile_impl<volatile Type1T, volatile Type2T, volatile Type2T>();
    test_copy_volatile_impl<volatile Type1T, const volatile Type2T, const volatile Type2T>();

    test_copy_volatile_impl<const volatile Type1T, Type2T, volatile Type2T>();
    test_copy_volatile_impl<const volatile Type1T, const Type2T, const volatile Type2T>();
    test_copy_volatile_impl<const volatile Type1T, volatile Type2T, volatile Type2T>();
    test_copy_volatile_impl<const volatile Type1T, const volatile Type2T, const volatile Type2T>();
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
