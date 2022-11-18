#include <phi/test/test_macros.hpp>

#include <phi/generated/compiler_support/features.hpp>
#include <phi/type_traits/is_constant_evaluated.hpp>

template <bool>
struct InTemplate
{};

static constexpr bool constexpr_function() noexcept
{
    return phi::is_constant_evaluated();
}

#if PHI_HAS_FEATURE_CONSTEVAL()
static consteval bool consteval_function() noexcept
{
    return phi::is_constant_evaluated();
}
#endif

#if PHI_HAS_FEATURE_CONSTINIT()
constinit const static bool constinit_value = phi::is_constant_evaluated();
#endif

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

    // Static initialization
    static int local_static = phi::is_constant_evaluated() ? 42 : -1;
    CHECK(local_static == 42);

    // Constexpr initialization
    constexpr bool constexpr_val = phi::is_constant_evaluated();
    STATIC_REQUIRE(constexpr_val);

    // Constexpr function evoked at runtime
    bool constexpr_function_runtime_result = constexpr_function();
    CHECK_FALSE(constexpr_function_runtime_result);

    // Constexpr function evoked at compile time
    constexpr bool constexpr_function_constexpr_result = constexpr_function();
    STATIC_REQUIRE(constexpr_function_constexpr_result);

    STATIC_REQUIRE(constexpr_function());

    // Consteval function
#    if PHI_HAS_FEATURE_CONSTEVAL()
    bool consteval_function_result = consteval_function();
    CHECK(consteval_function_result);

    STATIC_REQUIRE(consteval_function());
#    endif

    // Constinit
#    if PHI_HAS_FEATURE_CONSTINIT()
    STATIC_REQUIRE(constinit_value);
#    endif
#endif
}
