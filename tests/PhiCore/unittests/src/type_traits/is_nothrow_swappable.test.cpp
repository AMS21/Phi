#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/compiler_support/warning.hpp>
#include <type_traits>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

#include <phi/algorithm/swap.hpp>
#include <phi/type_traits/is_nothrow_swappable.hpp>
#include <phi/type_traits/is_swappable.hpp>

namespace MyNS
{
    // Make the test types non-copyable so that generic swap is not valid.
    struct A
    {
        A(A const&)            = delete;
        A& operator=(A const&) = delete;
    };

    struct B
    {
        B(B const&)            = delete;
        B& operator=(B const&) = delete;
    };

    void swap(A&, A&) noexcept
    {}

    void swap(B&, B&)
    {}

    struct M
    {
        M(M const&)            = delete;
        M& operator=(M const&) = delete;
    };

    void swap(M&&, M&&) noexcept
    {}

    struct ThrowingMove
    {
        ThrowingMove(ThrowingMove&&)
        {}

        ThrowingMove& operator=(ThrowingMove&&)
        {
            return *this;
        }
    };

} // namespace MyNS

template <typename T>
void test_is_nothrow_swappable()
{
    STATIC_REQUIRE(phi::is_nothrow_swappable<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_swappable<T>::value);
    STATIC_REQUIRE(phi::is_swappable<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_swappable_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_swappable_v<T>);
    STATIC_REQUIRE(phi::is_swappable_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_swappable<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_swappable<T>);

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_nothrow_swappable<T>::value);
    STATIC_REQUIRE(std::is_swappable<T>::value);
#endif
}

template <typename T>
void test_is_not_nothrow_swappable()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_swappable<T>::value);
    STATIC_REQUIRE(phi::is_not_nothrow_swappable<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_swappable_v<T>);
    STATIC_REQUIRE(phi::is_not_nothrow_swappable_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_swappable<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_swappable<T>);

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_nothrow_swappable<T>::value);
#endif
}

TEST_CASE("is_nothrow_swappable")
{
    using namespace MyNS;

    // Test that is_swappable applies an lvalue reference to the type.
    test_is_nothrow_swappable<int>();
    test_is_nothrow_swappable<int&>();
    test_is_not_nothrow_swappable<M>();
    test_is_not_nothrow_swappable<M&&>();

    // Test that it correctly deduces the noexcept of swap.
    test_is_nothrow_swappable<A>();
    test_is_not_nothrow_swappable<B>();
    STATIC_REQUIRE(phi::is_swappable<B>::value);
    test_is_not_nothrow_swappable<ThrowingMove>();
    STATIC_REQUIRE(phi::is_swappable<ThrowingMove>::value);

    // Test that it doesn't drop the qualifiers
    test_is_not_nothrow_swappable<const A>();

    // test non-referenceable types
    test_is_not_nothrow_swappable<void>();
    test_is_not_nothrow_swappable<const void>();
    test_is_not_nothrow_swappable<volatile void>();
    test_is_not_nothrow_swappable<const volatile void>();
    test_is_not_nothrow_swappable<int() const>();
    test_is_not_nothrow_swappable<int(int, ...) const&>();
}

PHI_GCC_SUPPRESS_WARNING_POP()
