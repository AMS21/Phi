#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/compiler_support/unused.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/forward.hpp>
#include <phi/type_traits/is_same.hpp>

struct A
{};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunneeded-internal-declaration")

static A source() noexcept
{
    return {};
}

// NOLINTNEXTLINE(readability-const-return-type)
static const A csource() noexcept
{
    return A();
}

PHI_CLANG_SUPPRESS_WARNING_POP()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

PHI_EXTENDED_CONSTEXPR bool test_constexpr_forward()
{
    int       integer       = 42;
    const int const_integer = 101;
    return phi::forward<int&>(integer) == 42 && phi::forward<int>(integer) == 42 &&
           phi::forward<const int&>(integer) == 42 && phi::forward<const int>(integer) == 42 &&
           phi::forward<int&&>(integer) == 42 && phi::forward<const int&&>(integer) == 42 &&
           phi::forward<const int&>(const_integer) == 101 &&
           phi::forward<const int>(const_integer) == 101;
}

TEST_CASE("forward")
{
    A       class_a;
    const A const_a = A();

    // Prevent unused warnings
    PHI_UNUSED_VARIABLE(class_a);
    PHI_UNUSED_VARIABLE(const_a);

    CHECK_SAME_TYPE(decltype(phi::forward<A&>(class_a)), A&);
    CHECK_SAME_TYPE(decltype(phi::forward<A>(class_a)), A&&);
    CHECK_SAME_TYPE(decltype(phi::forward<A>(source())), A&&);
    CHECK_NOEXCEPT(phi::forward<A&>(class_a));
    CHECK_NOEXCEPT(phi::forward<A>(class_a));
    CHECK_NOEXCEPT(phi::forward<A>(source()));

    CHECK_SAME_TYPE(decltype(phi::forward<const A&>(class_a)), const A&);
    CHECK_SAME_TYPE(decltype(phi::forward<const A>(class_a)), const A&&);
    CHECK_SAME_TYPE(decltype(phi::forward<const A>(source())), const A&&);
    CHECK_NOEXCEPT(phi::forward<const A&>(class_a));
    CHECK_NOEXCEPT(phi::forward<const A>(class_a));
    CHECK_NOEXCEPT(phi::forward<const A>(source()));

    CHECK_SAME_TYPE(decltype(phi::forward<const A&>(const_a)), const A&);
    CHECK_SAME_TYPE(decltype(phi::forward<const A>(const_a)), const A&&);
    CHECK_SAME_TYPE(decltype(phi::forward<const A>(csource())), const A&&);
    CHECK_NOEXCEPT(phi::forward<const A&>(const_a));
    CHECK_NOEXCEPT(phi::forward<const A>(const_a));
    CHECK_NOEXCEPT(phi::forward<const A>(csource()));

    constexpr int integer_2 = phi::forward<int>(42);
    STATIC_REQUIRE(phi::forward<int>(42) == 42);
    STATIC_REQUIRE(phi::forward<const int&>(integer_2) == 42);
    EXT_STATIC_REQUIRE(test_constexpr_forward());

    constexpr int integer_3 = phi::forward<int>(42);
    STATIC_REQUIRE(phi::forward<int>(42) == 42);
    STATIC_REQUIRE(phi::forward<const int&>(integer_3) == 42);
}

PHI_GCC_SUPPRESS_WARNING_POP()
