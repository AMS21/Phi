#include <catch2/catch_test_macros.hpp>

#include "Noexcept.hpp"
#include "SameType.hpp"
#include <Phi/CompilerSupport/Features.hpp>
#include <Phi/TypeTraits/is_constant_evaluated.hpp>

template <bool>
struct InTemplate
{};

#if PHI_HAS_INTRINSIC_BUILTIN_IS_CONSTANT_EVALUATED()
#    define TEST_SUPPORT_IS_CONSTANT_EVALUATED() 1
#else
#    define TEST_SUPPORT_IS_CONSTANT_EVALUATED() 0
#endif

TEST_CASE("is_constant_evaluated")
{
    CHECK_SAME_TYPE(decltype(phi::is_constant_evaluated()), bool);
    CHECK_NOEXCEPT(phi::is_constant_evaluated());

    bool b = phi::is_constant_evaluated();
    CHECK_FALSE(b);

    // Actual tests
#if TEST_SUPPORT_IS_CONSTANT_EVALUATED()
    static_assert(phi::is_constant_evaluated(), "is_constant_evulated");
    CHECK_SAME_TYPE(InTemplate<phi::is_constant_evaluated()>, InTemplate<true>);

    static int local_static = phi::is_constant_evaluated() ? 42 : -1;
    CHECK(local_static == 42);

    constexpr bool constexpr_val = phi::is_constant_evaluated();
    STATIC_REQUIRE(constexpr_val);
#endif
}
