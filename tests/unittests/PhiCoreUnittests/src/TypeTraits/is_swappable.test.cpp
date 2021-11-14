#include <catch2/catch.hpp>

#include <Phi/Algorithm/Swap.hpp>
#include <Phi/TypeTraits/is_swappable.hpp>

template <typename T>
void test_is_swappable()
{
    STATIC_REQUIRE(phi::is_swappable<T>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_swappable_v<T>);
#endif
}

template <typename T>
void test_is_not_swappable()
{
    STATIC_REQUIRE_FALSE(phi::is_swappable<T>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_swappable_v<T>);
#endif
}

namespace MyNS
{
    // Make the test types non-copyable so that generic std::swap is not valid.
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
    {
        M(M const&) = delete;
        M& operator=(M const&) = delete;
    };

    void swap(M&&, M&&)
    {}

    struct DeletedSwap
    {
        friend void swap(DeletedSwap&, DeletedSwap&) = delete;
    };
} // namespace MyNS

namespace MyNS2
{
    struct AmbiguousSwap
    {};

    template <typename T>
    void swap(T&, T&)
    {}

} // end namespace MyNS2

TEST_CASE("is_swappable")
{
    using namespace MyNS;

    // Test that is_swappable applies an lvalue reference to the type.
    test_is_swappable<A>();
    test_is_swappable<A&>();
    test_is_not_swappable<M>();
    test_is_not_swappable<M&&>();

    test_is_not_swappable<B>();
    test_is_swappable<C>();

    // test non-referencable types
    test_is_not_swappable<void>();
    test_is_not_swappable<int() const>();
    test_is_not_swappable<int()&>();

    // test that a deleted swap is correctly handled.
    test_is_not_swappable<DeletedSwap>();

    // test that a swap with ambiguous overloads is handled correctly.
    test_is_not_swappable<MyNS2::AmbiguousSwap>();
}
