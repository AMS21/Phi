#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTANT_EVALUATED_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTANT_EVALUATED_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/Config/Inline.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_ALWAYS_INLINE constexpr bool is_constant_evaluated() noexcept
{
#if PHI_HAS_INTRINSIC_BUILTIN_IS_CONSTANT_EVALUATED()
    return __builtin_is_constant_evaluated();
#else
    return false;
#endif
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTANT_EVALUATED_HPP
