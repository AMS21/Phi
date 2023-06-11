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
        static char character;
        return character;
    }
};

static void function()
{}

TEST_CASE("address_of")
{
    {
        int    integer{0};
        double double_val{0.0};
        CHECK(phi::address_of(integer) == &integer);
        CHECK(phi::address_of(double_val) == &double_val);
    }

    {
        A*       pointer       = new A;
        const A* const_pointer = pointer;
        CHECK(phi::address_of(*pointer) == pointer);
        CHECK(phi::address_of(*const_pointer) == pointer);
        delete pointer;
    }

    {
        union
        {
            nothing nothing_val;
            int     integer{0};
        };
        CHECK(phi::address_of(nothing_val) == reinterpret_cast<void*>(phi::address_of(integer)));
    }

    {
        int  value = 0;
        int& ref   = value;

        CHECK(phi::address_of(ref) == &ref);
        CHECK(phi::address_of(function) == function);
    }

    // To maximize coverage
    function();
}

struct Pointer
{
    constexpr Pointer(void* new_value)
        : value(new_value)
    {}

    void* value;
};

struct B
{
    B() = default;

    void operator&() const
    {}

    int magic_value{42};
};

#if PHI_SUPPORTS_ADDRESS_OF()
#    define STATIC_REQUIRE_ADR(...) STATIC_REQUIRE(__VA_ARGS__)
#    define CONSTEXPR_ADR           constexpr
#else
#    define STATIC_REQUIRE_ADR(...) REQUIRE(__VA_ARGS__)
#    define CONSTEXPR_ADR
#endif

constexpr int    integer    = 0;
constexpr double double_val = 0.0;
constexpr B      class_value{};

TEST_CASE("address_of - constexpr")
{
    STATIC_REQUIRE_ADR(phi::address_of(integer) == &integer);
    STATIC_REQUIRE_ADR(phi::address_of(double_val) == &double_val);

    CONSTEXPR_ADR const B* address_of_class = phi::address_of(class_value);
    STATIC_REQUIRE_ADR(&address_of_class->magic_value == &class_value.magic_value);
}
