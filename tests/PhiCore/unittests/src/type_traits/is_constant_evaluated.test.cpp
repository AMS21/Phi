#include <phi/test/test_macros.hpp>

#include <phi/generated/compiler_support/features.hpp>
#include <phi/type_traits/is_constant_evaluated.hpp>

template <bool>
struct InTemplate
{};

TEST_CASE("is_constant_evaluated")
{
    CHECK_SAME_TYPE(decltype(phi::is_constant_evaluated()), bool);
    CHECK_NOEXCEPT(phi::is_constant_evaluated());

    bool boolean = phi::is_constant_evaluated();
    CHECK_FALSE(boolean);

    // Actual tests
#if PHI_HAS_WORKING_IS_CONSTANT_EVALUATED()
    static_assert(phi::is_constant_evaluated(), "is_constant_evulated");
    CHECK_SAME_TYPE(InTemplate<phi::is_constant_evaluated()>, InTemplate<true>);

    static int local_static = phi::is_constant_evaluated() ? 42 : -1;
    CHECK(local_static == 42);

    constexpr bool constexpr_val = phi::is_constant_evaluated();
    STATIC_REQUIRE(constexpr_val);
#endif
}
