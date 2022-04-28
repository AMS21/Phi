#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/type_traits/is_none_of_rc.hpp>

template <typename T, typename... Args>
void test_is_none_of_rc()
{
    STATIC_REQUIRE(phi::is_none_of_rc<T, Args...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_none_of_rc_v<T, Args...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_none_of_rc<T, Args...>);
}

template <typename T, typename... Args>
void test_is_not_none_of_rc()
{
    STATIC_REQUIRE_FALSE(phi::is_none_of_rc<T, Args...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_none_of_rc_v<T, Args...>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_none_of_rc<T, Args...>);
}

struct A
{};

TEST_CASE("is_none_of_rc")
{
    test_is_none_of_rc<int, void>();
    test_is_none_of_rc<int, unsigned, void>();
    test_is_none_of_rc<int, float, unsigned, void>();
    test_is_none_of_rc<int, A, float, unsigned, void>();

    test_is_not_none_of_rc<int, int, void>();
    test_is_not_none_of_rc<int, void, int>();
    test_is_not_none_of_rc<int, int, void, void>();
    test_is_not_none_of_rc<int, void, int, void>();
    test_is_not_none_of_rc<int, void, void, int>();
    test_is_not_none_of_rc<int, int, void, void, void>();
    test_is_not_none_of_rc<int, void, int, void, void>();
    test_is_not_none_of_rc<int, void, void, int, void>();
    test_is_not_none_of_rc<int, void, void, void, int>();

    test_is_none_of_rc<int, void>();
    test_is_none_of_rc<int, void, void>();
    test_is_none_of_rc<int, void, void, void>();

    // const
    test_is_not_none_of_rc<int, const int>();
    test_is_not_none_of_rc<float, const float>();
    test_is_not_none_of_rc<const int, int>();
    test_is_not_none_of_rc<volatile int, const volatile int>();

    // volatile, ref
    test_is_none_of_rc<int, volatile int, const volatile int, int&, int&&, const int&, const int&&,
                       volatile int&, volatile int&&, const volatile int&, const volatile int&&>();
}
