#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTANT_EVALUATED_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTANT_EVALUATED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/intrinsics/is_constant_evaluated.hpp"
#include "phi/compiler_support/nodiscard.hpp"

#if PHI_HAS_FEATURE_IF_CONSTEVAL() || PHI_SUPPORTS_IS_CONSTANT_EVALUATED()
#    define PHI_HAS_WORKING_IS_CONSTANT_EVALUATED() 1
#else
#    define PHI_HAS_WORKING_IS_CONSTANT_EVALUATED() 0
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_NODISCARD PHI_ALWAYS_INLINE constexpr bool is_constant_evaluated() noexcept
{
#if PHI_SUPPORTS_IS_CONSTANT_EVALUATED()
    return PHI_IS_CONSTANT_EVALUATED();
#elif PHI_HAS_FEATURE_IF_CONSTEVAL()
    if consteval
    {
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTANT_EVALUATED_HPP
