#include <phi/test/test_macros.hpp>

#include <phi/algorithm/swap.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/type_traits/is_swappable_with.hpp>
#include <type_traits>

template <typename T, typename U>
void test_is_swappable_with()
{
    STATIC_REQUIRE(phi::is_swappable_with<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_swappable_with<T, U>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_swappable_with_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_swappable_with_v<T, U>);
#endif

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_swappable_with<T, U>::value);
#endif
}

template <typename T, typename U>
void test_is_not_swappable_with()
{
    STATIC_REQUIRE_FALSE(phi::is_swappable_with<T, U>::value);
    STATIC_REQUIRE(phi::is_not_swappable_with<T, U>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_swappable_with_v<T, U>);
    STATIC_REQUIRE(phi::is_not_swappable_with_v<T, U>);
#endif

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_swappable_with<T, U>::value);
#endif
}

namespace is_swappable_with_ns
{
    struct A
    {
        A(A const&) = delete;
        A& operator=(A const&) = delete;
    };

    struct B
    {
        B(B const&) = delete;
        B& operator=(B const&) = delete;
    };

    struct C
    {};
    struct D
    {};

    void swap(A&, A&)
    {}

    void swap(A&, B&)
    {}
    void swap(B&, A&)
    {}

    void swap(A&, C&)
    {} // missing swap(C, A)
    void swap(D&, C&)
    {}

    struct M
    {};

    void swap(M&&, M&&)
    {}

} // namespace is_swappable_with_ns

TEST_CASE("is_swappable_with")
{
    using namespace is_swappable_with_ns;
    {
        // Test that is_swappable_with doesn't apply an lvalue reference
        // to the type. Instead it is up to the user.
        test_is_not_swappable_with<int, int>();
        test_is_swappable_with<int&, int&>();
        test_is_swappable_with<M, M>();
        test_is_swappable_with<A&, A&>();
    }
    {
        // test that heterogeneous swap is allowed only if both 'swap(A, B)' and
        // 'swap(B, A)' are valid.
        test_is_swappable_with<A&, B&>();
        test_is_not_swappable_with<A&, C&>();
        test_is_not_swappable_with<D&, C&>();
    }
    {
        // test that cv void is guarded against as required.
        test_is_not_swappable_with<void, int>();
        test_is_not_swappable_with<const void, int>();
        test_is_not_swappable_with<volatile void, int>();
        test_is_not_swappable_with<const volatile void, int>();

        test_is_not_swappable_with<int, void>();
        test_is_not_swappable_with<int, const void>();
        test_is_not_swappable_with<int, volatile void>();
        test_is_not_swappable_with<int, const volatile void>();

        test_is_not_swappable_with<void, void>();
        test_is_not_swappable_with<void, const void>();
        test_is_not_swappable_with<void, volatile void>();
        test_is_not_swappable_with<void, const volatile void>();
        test_is_not_swappable_with<const void, void>();
        test_is_not_swappable_with<const void, const void>();
        test_is_not_swappable_with<const void, volatile void>();
        test_is_not_swappable_with<const void, const volatile void>();
        test_is_not_swappable_with<volatile void, void>();
        test_is_not_swappable_with<volatile void, const void>();
        test_is_not_swappable_with<volatile void, volatile void>();
        test_is_not_swappable_with<volatile void, const volatile void>();
        test_is_not_swappable_with<const volatile void, void>();
        test_is_not_swappable_with<const volatile void, const void>();
        test_is_not_swappable_with<const volatile void, volatile void>();
        test_is_not_swappable_with<const volatile void, const volatile void>();
    }
}
