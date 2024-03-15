#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/unused.hpp>
#include <phi/core/move_if_noexcept.hpp>

struct A
{
    A()  = default;
    ~A() = default;

    A(A&&)            = default;
    A& operator=(A&&) = default;

    A(const A&)            = delete;
    A& operator=(const A&) = delete;
};

struct legacy
{
    legacy() = default;

    legacy(const legacy&);
};

struct noexcept_move_copy
{
    noexcept_move_copy() = default;

    noexcept_move_copy(noexcept_move_copy&& other) noexcept
    {
        other.m_Status = false;
    }

    noexcept_move_copy(const noexcept_move_copy&) = default;

    operator bool() const
    {
        return m_Status;
    }

private:
    bool m_Status{true};
};

struct noexcept_move_no_copy
{
    noexcept_move_no_copy() = default;

    noexcept_move_no_copy(noexcept_move_no_copy&& other) noexcept
    {
        other.m_Status = false;
    }

    noexcept_move_no_copy(const noexcept_move_no_copy&) = delete;

    operator bool() const
    {
        return m_Status;
    }

private:
    bool m_Status{true};
};

struct except_move_copy
{
    except_move_copy() = default;

    except_move_copy(except_move_copy&& other) noexcept(false)
    {
        other.m_Status = false;
    }

    except_move_copy(const except_move_copy&) = default;

    operator bool() const
    {
        return m_Status;
    }

private:
    bool m_Status{true};
};

struct except_move_no_copy
{
    except_move_no_copy() = default;

    except_move_no_copy(except_move_no_copy&& other) noexcept(false)
    {
        other.m_Status = false;
    }

    except_move_no_copy(const except_move_no_copy&) = delete;

    operator bool() const
    {
        return m_Status;
    }

private:
    bool m_Status{true};
};

struct simple
{
    int i;
};

TEST_CASE("move_if_noexcept")
{
    int       integer       = 0;
    const int const_integer = 0;

    legacy  legacy_class;
    A       a_class;
    const A const_a;

    CHECK_SAME_TYPE(decltype(phi::move_if_noexcept(integer)), int&&);
    CHECK_NOEXCEPT(phi::move_if_noexcept(integer));
    CHECK_SAME_TYPE(decltype(phi::move_if_noexcept(const_integer)), const int&&);
    CHECK_NOEXCEPT(phi::move_if_noexcept(const_integer));
    CHECK_SAME_TYPE(decltype(phi::move_if_noexcept(a_class)), A&&);
    CHECK_NOEXCEPT(phi::move_if_noexcept(a_class));
    CHECK_SAME_TYPE(decltype(phi::move_if_noexcept(const_a)), const A&&);
    CHECK_NOEXCEPT(phi::move_if_noexcept(const_a));
    CHECK_SAME_TYPE(decltype(phi::move_if_noexcept(legacy_class)), const legacy&);
    CHECK_NOEXCEPT(phi::move_if_noexcept(legacy_class));

    PHI_CONSTEXPR int integer1 = 23;
    PHI_CONSTEXPR int integer2 = phi::move_if_noexcept(integer1);
    CHECK_NOEXCEPT(phi::move_if_noexcept(integer1));
    PHI_UNUSED_VARIABLE(integer2);
    STATIC_REQUIRE(integer2 == 23);

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

    PHI_CONSTEXPR simple simple_class{5};
    PHI_CONSTEXPR simple simple_class2 = phi::move_if_noexcept(simple_class);
    CHECK_NOEXCEPT(phi::move_if_noexcept(simple_class2));
    PHI_UNUSED_VARIABLE(simple_class2);
}
