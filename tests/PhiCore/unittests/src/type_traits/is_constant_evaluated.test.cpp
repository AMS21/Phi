#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/features.hpp>
#include <phi/compiler_support/warning.hpp>
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

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_PUSH()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wunused-const-variable")

#if PHI_HAS_FEATURE_CONSTINIT()
constinit const static bool constinit_value = phi::is_constant_evaluated();
#endif

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()

TEST_CASE("is_constant_evaluated")
{
    // Clang-14 seems to crashes when compiling this test case with coverage enabled
#if PHI_COMPILER_IS_ATLEAST(CLANG, 14, 0, 0) && (PHI_COMPILER_IS_BELOW(CLANG, 15, 0, 0)) &&        \
        defined(PHI_CONFIG_COVERAGE_BUILD)

    SKIP_CHECK();

#else

    CHECK_SAME_TYPE(decltype(phi::is_constant_evaluated()), bool);
    CHECK_NOEXCEPT(phi::is_constant_evaluated());

    bool boolean = phi::is_constant_evaluated();
    CHECK_FALSE(boolean);

    // Actual tests
#    if PHI_HAS_WORKING_IS_CONSTANT_EVALUATED()
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

#        if defined(PHI_CONFIG_COVERAGE_BUILD)
    REQUIRE_FALSE(constexpr_function());
#        else
    STATIC_REQUIRE(constexpr_function());
#        endif

    // Consteval function
#        if PHI_HAS_FEATURE_CONSTEVAL()
    bool consteval_function_result = consteval_function();

    // Test is broken in clang before 11, AppleClang before 12.5
#            if PHI_COMPILER_IS_BELOW(CLANG, 11, 0, 0) ||                                          \
                    PHI_COMPILER_IS_BELOW(APPLECLANG, 12, 5, 0)
    SKIP_CHECK();
    (void)consteval_function_result;
#            else
    CHECK(consteval_function_result);
#            endif

    STATIC_REQUIRE(consteval_function());
#        endif

    // Constinit
#        if PHI_HAS_FEATURE_CONSTINIT()
    STATIC_REQUIRE(constinit_value);
#        endif
#    endif

#endif
}
