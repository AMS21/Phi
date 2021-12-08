#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"

#include "phi/compiler_support/warning.hpp"

#include <phi/core/move.hpp>

class move_only
{
    move_only(const move_only&);
    move_only& operator=(const move_only&);

public:
    move_only(move_only&&)
    {}
    move_only& operator=(move_only&&)
    {
        return *this;
    }

    move_only()
    {}
};

static move_only source()
{
    return move_only();
}

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunused-function")

static const move_only csource()
{
    return move_only();
}

PHI_CLANG_SUPPRESS_WARNING_POP()

void test(move_only)
{}

static int        x  = 42;
static const int& cx = x;

template <class QualInt>
QualInt get() noexcept
{
    return static_cast<QualInt>(x);
}

static int copy_ctor = 0;
static int move_ctor = 0;

struct A
{
    A()
    {}
    A(const A&)
    {
        ++copy_ctor;
    }
    A(A&&)
    {
        ++move_ctor;
    }
    A& operator=(const A&) = delete;
};

PHI_EXTENDED_CONSTEXPR bool test_constexpr_move()
{
    int       y  = 42;
    const int cy = y;
    return phi::move(y) == 42 && phi::move(cy) == 42 && phi::move(static_cast<int&&>(y)) == 42 &&
           phi::move(static_cast<int const&&>(y)) == 42;
}

TEST_CASE("move")
{
    {
        // Test return type and noexcept.
        CHECK_SAME_TYPE(decltype(phi::move(x)), int&&);
        CHECK_SAME_TYPE(decltype(phi::move(cx)), const int&&);
        CHECK_SAME_TYPE(decltype(phi::move(42)), int&&);
        CHECK_SAME_TYPE(decltype(phi::move(get<const int&&>())), const int&&);

        CHECK_NOEXCEPT(phi::move(x));
        CHECK_NOEXCEPT(phi::move(cx));
        CHECK_NOEXCEPT(phi::move(42));
        CHECK_NOEXCEPT(phi::move(get<int const&&>()));
    }
    {
        // test copy and move semantics
        A       a;
        const A ca = A();

        REQUIRE(copy_ctor == 0);
        REQUIRE(move_ctor == 0);

        A a2 = a;
        (void)a2;
        REQUIRE(copy_ctor == 1);
        REQUIRE(move_ctor == 0);

        A a3 = phi::move(a);
        (void)a3;
        REQUIRE(copy_ctor == 1);
        REQUIRE(move_ctor == 1);

        A a4 = ca;
        (void)a4;
        REQUIRE(copy_ctor == 2);
        REQUIRE(move_ctor == 1);

        A a5 = phi::move(ca);
        (void)a5;
        REQUIRE(copy_ctor == 3);
        REQUIRE(move_ctor == 1);
    }
    {
        // test on a move only type
        move_only mo;
        test(phi::move(mo));
        test(source());
    }
    {
        constexpr int y = 42;
        STATIC_REQUIRE(phi::move(y) == 42);
        EXT_STATIC_REQUIRE(test_constexpr_move());
    }
    {
        constexpr int y = 42;
        STATIC_REQUIRE(phi::move(y) == 42);
    }
}
