#ifndef INCG_PHI_UNITTEST_CONSTEXPRHELPER_HPP
#define INCG_PHI_UNITTEST_CONSTEXPRHELPER_HPP

#include <phi/compiler_support/constexpr.hpp>
#include <phi/test/test_macros.hpp>

#if defined(CATCH_CONFIG_RUNTIME_STATIC_REQUIRE)
#    define CONSTEXPR_RUNTIME     /* Nothing */
#    define EXT_CONSTEXPR_RUNTIME /* Nothing */
#else
#    define CONSTEXPR_RUNTIME constexpr
#    if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
#        define EXT_CONSTEXPR_RUNTIME constexpr
#    else
#        define EXT_CONSTEXPR_RUNTIME /* Nothing */
#    endif
#endif

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
#    define EXT_STATIC_REQUIRE(...)       STATIC_REQUIRE(__VA_ARGS__)
#    define EXT_STATIC_REQUIRE_FALSE(...) STATIC_REQUIRE_FALSE(__VA_ARGS__)
#else
#    define EXT_STATIC_REQUIRE(...)       REQUIRE(__VA_ARGS__)
#    define EXT_STATIC_REQUIRE_FALSE(...) REQUIRE_FALSE(__VA_ARGS__)
#endif

// sanitizer functions in gcc are not constexpr
#if PHI_COMPILER_IS(GCC)
#    define CONSTEXPR_SAN           /* Nothing */
#    define STATIC_REQUIRE_SAN(...) REQUIRE(__VA_ARGS__)
#else
#    define CONSTEXPR_SAN           constexpr
#    define STATIC_REQUIRE_SAN(...) EXT_STATIC_REQUIRE(__VA_ARGS__)
#endif

#endif // INCG_PHI_UNITTEST_CONSTEXPRHELPER_HPP
