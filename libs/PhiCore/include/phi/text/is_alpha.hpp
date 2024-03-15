#ifndef INCG_PHI_CORE_TEXT_IS_ALPHA_HPP
#define INCG_PHI_CORE_TEXT_IS_ALPHA_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_NODISCARD PHI_CONSTEXPR phi::boolean is_alpha(const char character) noexcept
{
    return static_cast<bool>(static_cast<int>(character >= 'a' && character <= 'z') |
                             static_cast<int>(character >= 'A' && character <= 'Z'));
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_IS_ALPHA_HPP
