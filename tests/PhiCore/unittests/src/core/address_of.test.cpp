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

#if PHI_SUPPORTS_ADDRESS_OF()
#    define STATIC_REQUIRE_ADR(...) STATIC_REQUIRE(__VA_ARGS__)
#    define CONSTEXPR_ADR           constexpr
#else
#    define STATIC_REQUIRE_ADR(...) REQUIRE(__VA_ARGS__)
#    define CONSTEXPR_ADR
#endif

constexpr int    i = 0;
constexpr double d = 0.0;
constexpr B      a{};

TEST_CASE("address_of - constexpr")
{
    STATIC_REQUIRE_ADR(phi::address_of(i) == &i);
    STATIC_REQUIRE_ADR(phi::address_of(d) == &d);

    CONSTEXPR_ADR const B* ap = phi::address_of(a);
    STATIC_REQUIRE_ADR(&ap->n == &a.n);
}
