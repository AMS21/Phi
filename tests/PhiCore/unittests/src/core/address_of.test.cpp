#include <phi/test/test_macros.hpp>

#include <phi/core/address_of.hpp>

struct A
{
    void operator&() const
    {}
};

struct nothing
{
    operator char&()
    {
        static char c;
        return c;
    }
};

TEST_CASE("address_of")
{
    {
        int    i;
        double d;
        CHECK(phi::address_of(i) == &i);
        CHECK(phi::address_of(d) == &d);
    }

    {
        A*       tp  = new A;
        const A* ctp = tp;
        CHECK(phi::address_of(*tp) == tp);
        CHECK(phi::address_of(*ctp) == tp);
        delete tp;
    }

    {
        union
        {
            nothing n;
            int     i;
        };
        CHECK(phi::address_of(n) == reinterpret_cast<void*>(phi::address_of(i)));
    }
}

struct Pointer
{
    constexpr Pointer(void* v)
        : value(v)
    {}
    void* value;
};

struct B
{
    constexpr B()
        : n(42)
    {}
    void operator&() const
    {}
    int n;
};

constexpr int    i = 0;
constexpr double d = 0.0;
constexpr B      a{};

TEST_CASE("address_of - constexpr")
{
    STATIC_REQUIRE(phi::address_of(i) == &i);
    STATIC_REQUIRE(phi::address_of(d) == &d);

    constexpr const B* ap = phi::address_of(a);
    STATIC_REQUIRE(&ap->n == &a.n);
}
