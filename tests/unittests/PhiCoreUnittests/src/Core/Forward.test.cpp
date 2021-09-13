#include <catch2/catch_test_macros.hpp>

#include <Phi/Core/Forward.hpp>
#include <Phi/TypeTraits/is_same.hpp>

struct A
{};

static A source() noexcept
{
    return A();
}

static const A csource() noexcept
{
    return A();
}

constexpr bool test_constexpr_forward()
{
    int       x  = 42;
    const int cx = 101;
    return phi::forward<int&>(x) == 42 && phi::forward<int>(x) == 42 &&
           phi::forward<const int&>(x) == 42 && phi::forward<const int>(x) == 42 &&
           phi::forward<int&&>(x) == 42 && phi::forward<const int&&>(x) == 42 &&
           phi::forward<const int&>(cx) == 101 && phi::forward<const int>(cx) == 101;
}

TEST_CASE("forward")
{
    A       a;
    const A ca = A();

    ((void)a);  // Prevent unused warning
    ((void)ca); // Prevent unused warning

    STATIC_REQUIRE(phi::is_same_v<decltype(phi::forward<A&>(a)), A&>);
    STATIC_REQUIRE(phi::is_same_v<decltype(phi::forward<A>(a)), A&&>);
    STATIC_REQUIRE(phi::is_same_v<decltype(phi::forward<A>(source())), A&&>);
    STATIC_REQUIRE(noexcept(phi::forward<A&>(a)));
    STATIC_REQUIRE(noexcept(phi::forward<A>(a)));
    STATIC_REQUIRE(noexcept(phi::forward<A>(source())));

    STATIC_REQUIRE(phi::is_same_v<decltype(phi::forward<const A&>(a)), const A&>);
    STATIC_REQUIRE(phi::is_same_v<decltype(phi::forward<const A>(a)), const A&&>);
    STATIC_REQUIRE(phi::is_same_v<decltype(phi::forward<const A>(source())), const A&&>);
    STATIC_REQUIRE(noexcept(phi::forward<const A&>(a)));
    STATIC_REQUIRE(noexcept(phi::forward<const A>(a)));
    STATIC_REQUIRE(noexcept(phi::forward<const A>(source())));

    STATIC_REQUIRE(phi::is_same_v<decltype(phi::forward<const A&>(ca)), const A&>);
    STATIC_REQUIRE(phi::is_same_v<decltype(phi::forward<const A>(ca)), const A&&>);
    STATIC_REQUIRE(phi::is_same_v<decltype(phi::forward<const A>(csource())), const A&&>);
    STATIC_REQUIRE(noexcept(phi::forward<const A&>(ca)));
    STATIC_REQUIRE(noexcept(phi::forward<const A>(ca)));
    STATIC_REQUIRE(noexcept(phi::forward<const A>(csource())));

    constexpr int i2 = phi::forward<int>(42);
    STATIC_REQUIRE(phi::forward<int>(42) == 42);
    STATIC_REQUIRE(phi::forward<const int&>(i2) == 42);
    STATIC_REQUIRE(test_constexpr_forward());

    constexpr int i3 = phi::forward<int>(42);
    STATIC_REQUIRE(phi::forward<int>(42) == 42);
    STATIC_REQUIRE(phi::forward<const int&>(i3) == 42);
}
