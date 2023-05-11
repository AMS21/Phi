#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/intrinsics/address_of.hpp>
#include <phi/core/voidify.hpp>

PHI_EXTENDED_CONSTEXPR bool voiding_constexpr_test()
{
    int   integer{21};
    void* adr = phi::voidify(integer);

    return (&integer == adr);
}

TEST_CASE("core.voidify")
{
    int   integer{21};
    void* adr = phi::voidify(integer);

    CHECK(&integer == adr);
    CHECK_NOEXCEPT(phi::voidify(integer));

#if PHI_SUPPORTS_ADDRESS_OF()
    EXT_STATIC_REQUIRE(voiding_constexpr_test());
#endif
}
