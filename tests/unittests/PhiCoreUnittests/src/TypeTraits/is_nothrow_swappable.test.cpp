#include <catch2/catch.hpp>

#include <Phi/Algorithm/Swap.hpp>
#include <Phi/TypeTraits/is_nothrow_swappable.hpp>
#include <Phi/TypeTraits/is_swappable.hpp>

namespace MyNS
{
    // Make the test types non-copyable so that generic swap is not valid.
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

    void swap(A&, A&) noexcept
    {}

    void swap(B&, B&)
    {}

    struct M
    {
        M(M const&) = delete;
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
    STATIC_REQUIRE(phi::is_swappable<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_swappable_v<T>);
    STATIC_REQUIRE(phi::is_swappable_v<T>);
#endif
}

template <typename T>
void test_is_not_nothrow_swappable()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_swappable<T>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_swappable_v<T>);
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
