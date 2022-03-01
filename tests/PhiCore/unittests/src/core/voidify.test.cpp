#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/extended_attributes.hpp>
#include <phi/compiler_support/intrinsics/address_of.hpp>
#include <phi/core/voidify.hpp>

PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_CONST bool voidify_constexpr_test()
{
    int   a{21};
    void* adr = phi::voidify(a);

    return (&a == adr);
}

TEST_CASE("core.voidify")
{
    int   a{21};
    void* adr = phi::voidify(a);

    CHECK(&a == adr);
    CHECK_NOEXCEPT(phi::voidify(a));

#if PHI_SUPPORTS_ADDRESS_OF()
    EXT_STATIC_REQUIRE(voidify_constexpr_test());
#endif
}
