#ifndef INCG_PHI_UNITTEST_CONSTEXPRHELPER_HPP
#define INCG_PHI_UNITTEST_CONSTEXPRHELPER_HPP

#include <Phi/CompilerSupport/Constexpr.hpp>
#include <catch2/catch.hpp>

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

#endif // INCG_PHI_UNITTEST_CONSTEXPRHELPER_HPP
