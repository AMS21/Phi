#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include "phi/compiler_support/unused.hpp"
#include <phi/compiler_support/warning.hpp>
#include <phi/core/move.hpp>

class move_only
{
public:
    move_only(move_only&& /*other*/) noexcept
    {}
    move_only& operator=(move_only&& /*other*/) noexcept
    {
        return *this;
    }

    move_only(const move_only&)            = delete;
    move_only& operator=(const move_only&) = delete;

    move_only() = default;

    ~move_only() = default;
};

static move_only source()
{
    return {};
}

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunused-function")

// NOLINTNEXTLINE(readability-const-return-type)
static const move_only csource()
{
    return move_only();
}

PHI_CLANG_SUPPRESS_WARNING_POP()

void test(move_only /*type*/)
{}

static int        integer       = 42; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
static const int& const_integer = integer;

template <typename QualIntT>
QualIntT get() noexcept
{
    return static_cast<QualIntT>(integer);
}

static int copy_ctor = 0; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
static int move_ctor = 0; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

namespace move_test
{
    struct A
    {
        A()  = default;
        ~A() = default;
        A(const A& /*other*/)
        {
            ++copy_ctor;
        }

        A(A&& /*other*/) noexcept
        {
            ++move_ctor;
        }
        A& operator=(const A&) = delete;
        A& operator=(A&&)      = delete;
    };
} // namespace move_test

using namespace move_test;

PHI_EXTENDED_CONSTEXPR bool test_constexpr_move()
{
    int       local_integer       = 42;
    const int const_local_integer = local_integer;
    return phi::move(local_integer) == 42 && phi::move(const_local_integer) == 42 &&
           phi::move(static_cast<int&&>(local_integer)) == 42 &&
           phi::move(static_cast<int const&&>(local_integer)) == 42;
}

TEST_CASE("move")
{
    {
        // Test return type and noexcept.
        CHECK_SAME_TYPE(decltype(phi::move(integer)), int&&);
        CHECK_SAME_TYPE(decltype(phi::move(const_integer)), const int&&);
        CHECK_SAME_TYPE(decltype(phi::move(42)), int&&);
        CHECK_SAME_TYPE(decltype(phi::move(get<const int&&>())), const int&&);

        CHECK_NOEXCEPT(phi::move(integer));
        CHECK_NOEXCEPT(phi::move(const_integer));
        CHECK_NOEXCEPT(phi::move(42));
        CHECK_NOEXCEPT(phi::move(get<int const&&>()));
    }
    {
        // test copy and move semantics
        A       class_a;
        const A const_a = A();

        REQUIRE(copy_ctor == 0);
        REQUIRE(move_ctor == 0);

        A class_a2 = class_a;
        PHI_UNUSED_VARIABLE(class_a2);
        REQUIRE(copy_ctor == 1);
        REQUIRE(move_ctor == 0);

        A class_a3 = phi::move(class_a);
        PHI_UNUSED_VARIABLE(class_a3);
        REQUIRE(copy_ctor == 1);
        REQUIRE(move_ctor == 1);

        A class_a4 = const_a;
        PHI_UNUSED_VARIABLE(class_a4);
        REQUIRE(copy_ctor == 2);
        REQUIRE(move_ctor == 1);

        A class_a5 = phi::move(const_a);
        PHI_UNUSED_VARIABLE(class_a5);
        REQUIRE(copy_ctor == 3);
        REQUIRE(move_ctor == 1);
    }
    {
        // test on a move only type
        move_only mov;
        test(phi::move(mov));
        test(source());
    }
    {
        constexpr int integer2 = 42;
        STATIC_REQUIRE(phi::move(integer2) == 42);
        EXT_STATIC_REQUIRE(test_constexpr_move());
    }
    {
        constexpr int integer2 = 42;
        STATIC_REQUIRE(phi::move(integer2) == 42);
    }

    // Maximizing coverage data
    (void)source();
    (void)csource();
    (void)get<int>();
    (void)get<const int>();
}
