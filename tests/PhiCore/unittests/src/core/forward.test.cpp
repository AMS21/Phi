#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/forward.hpp>
#include <phi/type_traits/is_same.hpp>

struct A
{};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunneeded-internal-declaration")

static A source() noexcept
{
    return A();
}

static const A csource() noexcept
{
    return A();
}

PHI_CLANG_SUPPRESS_WARNING_POP()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

PHI_EXTENDED_CONSTEXPR bool test_constexpr_forward()
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

    CHECK_SAME_TYPE(decltype(phi::forward<A&>(a)), A&);
    CHECK_SAME_TYPE(decltype(phi::forward<A>(a)), A &&);
    CHECK_SAME_TYPE(decltype(phi::forward<A>(source())), A &&);
    CHECK_NOEXCEPT(phi::forward<A&>(a));
    CHECK_NOEXCEPT(phi::forward<A>(a));
    CHECK_NOEXCEPT(phi::forward<A>(source()));

    CHECK_SAME_TYPE(decltype(phi::forward<const A&>(a)), const A&);
    CHECK_SAME_TYPE(decltype(phi::forward<const A>(a)), const A&&);
    CHECK_SAME_TYPE(decltype(phi::forward<const A>(source())), const A&&);
    CHECK_NOEXCEPT(phi::forward<const A&>(a));
    CHECK_NOEXCEPT(phi::forward<const A>(a));
    CHECK_NOEXCEPT(phi::forward<const A>(source()));

    CHECK_SAME_TYPE(decltype(phi::forward<const A&>(ca)), const A&);
    CHECK_SAME_TYPE(decltype(phi::forward<const A>(ca)), const A&&);
    CHECK_SAME_TYPE(decltype(phi::forward<const A>(csource())), const A&&);
    CHECK_NOEXCEPT(phi::forward<const A&>(ca));
    CHECK_NOEXCEPT(phi::forward<const A>(ca));
    CHECK_NOEXCEPT(phi::forward<const A>(csource()));

    constexpr int i2 = phi::forward<int>(42);
    STATIC_REQUIRE(phi::forward<int>(42) == 42);
    STATIC_REQUIRE(phi::forward<const int&>(i2) == 42);
    EXT_STATIC_REQUIRE(test_constexpr_forward());

    constexpr int i3 = phi::forward<int>(42);
    STATIC_REQUIRE(phi::forward<int>(42) == 42);
    STATIC_REQUIRE(phi::forward<const int&>(i3) == 42);
}

PHI_GCC_SUPPRESS_WARNING_POP()
