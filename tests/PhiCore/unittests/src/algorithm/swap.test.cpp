#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/algorithm/swap.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_same.hpp>

struct CopyOnly
{
    CopyOnly()
    {}
    CopyOnly(CopyOnly const&) noexcept
    {}
    CopyOnly& operator=(CopyOnly const&)
    {
        return *this;
    }
};

struct MoveOnly
{
    MoveOnly()
    {}
    MoveOnly(MoveOnly&&)
    {}
    MoveOnly& operator=(MoveOnly&&) noexcept
    {
        return *this;
    }
};

struct NoexceptMoveOnly
{
    NoexceptMoveOnly()
    {}
    NoexceptMoveOnly(NoexceptMoveOnly&&) noexcept
    {}
    NoexceptMoveOnly& operator=(NoexceptMoveOnly&&) noexcept
    {
        return *this;
    }
};

struct NotMoveConstructible
{
    NotMoveConstructible& operator=(NotMoveConstructible&&)
    {
        return *this;
    }

private:
    NotMoveConstructible(NotMoveConstructible&&);
};

struct NotMoveAssignable
{
    NotMoveAssignable(NotMoveAssignable&&);

private:
    NotMoveAssignable& operator=(NotMoveAssignable&&);
};

template <typename TypeT>
auto can_swap_test(int) -> decltype(phi::swap(phi::declval<TypeT>(), phi::declval<TypeT>()));

template <typename TypeT>
auto can_swap_test(...) -> phi::false_type;

template <typename TypeT>
constexpr bool can_swap()
{
    return phi::is_same<decltype(can_swap_test<TypeT>(0)), void>::value;
}

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
constexpr bool test_swap_constexpr()
{
    int i = 1;
    int j = 2;
    phi::swap(i, j);
    return i == 2 && j == 1;
}
#endif

TEST_CASE("swap")
{
    {
        int i = 1;
        int j = 2;
        phi::swap(i, j);
        CHECK(i == 2);
        CHECK(j == 1);
    }

    // phi::scope_ptr
    {
        phi::scope_ptr<int> i(new int(1));
        phi::scope_ptr<int> j(new int(2));
        phi::swap(i, j);
        CHECK(*i == 2);
        CHECK(*j == 1);
    }
    {
        // test that the swap
        STATIC_REQUIRE(can_swap<CopyOnly&>());
        STATIC_REQUIRE(can_swap<MoveOnly&>());
        STATIC_REQUIRE(can_swap<NoexceptMoveOnly&>());

        STATIC_REQUIRE(!can_swap<NotMoveConstructible&>());
        STATIC_REQUIRE(!can_swap<NotMoveAssignable&>());

        CopyOnly         c;
        MoveOnly         m;
        NoexceptMoveOnly nm;
        STATIC_REQUIRE(!noexcept(phi::swap(c, c)));
        STATIC_REQUIRE(!noexcept(phi::swap(m, m)));
        STATIC_REQUIRE(noexcept(phi::swap(nm, nm)));
    }

    {
        // Check that swap does not call any copy constructor
        NonCopyable a;
        NonCopyable b;

        phi::swap(a, b);
    }

    {
        Tracked a;
        Tracked b;

        phi::swap(a, b);
    }

    {
        TrapConstructible a;
        TrapConstructible b;

        phi::swap(a, b);
    }

    {
        TrapImplicitConversion a;
        TrapImplicitConversion b;

        phi::swap(a, b);
    }

    {
        TrapComma a;
        TrapComma b;

        phi::swap(a, b);
    }

    {
        TrapCall a;
        TrapCall b;

        phi::swap(a, b);
    }

    {
        TrapSelfAssign a;
        TrapSelfAssign b;

        phi::swap(a, b);
    }

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(test_swap_constexpr());
#endif
}
