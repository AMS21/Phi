#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/unused.hpp>
#include <phi/core/move_if_noexcept.hpp>

class A
{
    A(const A&);
    A& operator=(const A&);

public:
    A()
    {}

    A(A&&)
    {}
};

struct legacy
{
    legacy()
    {}

    legacy(const legacy&);
};

struct noexcept_move_copy
{
    noexcept_move_copy()
        : status(true)
    {}

    noexcept_move_copy(noexcept_move_copy&& r) noexcept
    {
        r.status = false;
    }

    noexcept_move_copy(const noexcept_move_copy&) = default;

    operator bool() const
    {
        return status;
    }

private:
    bool status;
};

struct noexcept_move_no_copy
{
    noexcept_move_no_copy()
        : status(true)
    {}

    noexcept_move_no_copy(noexcept_move_no_copy&& r) noexcept
    {
        r.status = false;
    }

    noexcept_move_no_copy(const noexcept_move_no_copy&) = delete;

    operator bool() const
    {
        return status;
    }

private:
    bool status;
};

struct except_move_copy
{
    except_move_copy()
        : status(true)
    {}

    except_move_copy(except_move_copy&& r) noexcept(false)
    {
        r.status = false;
    }

    except_move_copy(const except_move_copy&) = default;

    operator bool() const
    {
        return status;
    }

private:
    bool status;
};

struct except_move_no_copy
{
    except_move_no_copy()
        : status(true)
    {}

    except_move_no_copy(except_move_no_copy&& r) noexcept(false)
    {
        r.status = false;
    }

    except_move_no_copy(const except_move_no_copy&) = delete;

    operator bool() const
    {
        return status;
    }

private:
    bool status;
};

struct simple
{
    int i;
};

TEST_CASE("move_if_noexcept")
{
    int       i  = 0;
    const int ci = 0;

    legacy  l;
    A       a;
    const A ca;

    CHECK_SAME_TYPE(decltype(phi::move_if_noexcept(i)), int&&);
    CHECK_NOEXCEPT(phi::move_if_noexcept(i));
    CHECK_SAME_TYPE(decltype(phi::move_if_noexcept(ci)), const int&&);
    CHECK_NOEXCEPT(phi::move_if_noexcept(ci));
    CHECK_SAME_TYPE(decltype(phi::move_if_noexcept(a)), A &&);
    CHECK_NOEXCEPT(phi::move_if_noexcept(a));
    CHECK_SAME_TYPE(decltype(phi::move_if_noexcept(ca)), const A&&);
    CHECK_NOEXCEPT(phi::move_if_noexcept(ca));
    CHECK_SAME_TYPE(decltype(phi::move_if_noexcept(l)), const legacy&);
    CHECK_NOEXCEPT(phi::move_if_noexcept(l));

    constexpr int i1 = 23;
    constexpr int i2 = phi::move_if_noexcept(i1);
    CHECK_NOEXCEPT(phi::move_if_noexcept(i1));
    PHI_UNUSED_VARIABLE(i2);
    STATIC_REQUIRE(i2 == 23);

    noexcept_move_copy nemc1;
    noexcept_move_copy nemc2 = phi::move_if_noexcept(nemc1);
    CHECK_NOEXCEPT(phi::move_if_noexcept(nemc2));
    PHI_UNUSED_VARIABLE(nemc2);
    CHECK_FALSE(nemc1);

    noexcept_move_no_copy nemnc1;
    noexcept_move_no_copy nemnc2 = phi::move_if_noexcept(nemnc1);
    CHECK_NOEXCEPT(phi::move_if_noexcept(nemnc2));
    PHI_UNUSED_VARIABLE(nemnc2);
    CHECK_FALSE(nemnc1);

    except_move_copy emc1;
    except_move_copy emc2 = phi::move_if_noexcept(emc1);
    CHECK_NOEXCEPT(phi::move_if_noexcept(emc2));
    PHI_UNUSED_VARIABLE(emc2);
    CHECK(emc1);

    except_move_no_copy emnc1;
    except_move_no_copy emnc2 = phi::move_if_noexcept(emnc1);
    CHECK_NOEXCEPT(phi::move_if_noexcept(emnc2));
    PHI_UNUSED_VARIABLE(emnc2);
    CHECK_FALSE(emnc1);

    constexpr simple s{5};
    constexpr simple s2 = phi::move_if_noexcept(s);
    CHECK_NOEXCEPT(phi::move_if_noexcept(s2));
    PHI_UNUSED_VARIABLE(s2);
}
