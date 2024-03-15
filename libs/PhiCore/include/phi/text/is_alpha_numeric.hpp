#ifndef INCG_PHI_CORE_TEXT_IS_ALPHA_NUMERIC_HPP
#define INCG_PHI_CORE_TEXT_IS_ALPHA_NUMERIC_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// Comparison of implementations: https://godbolt.org/z/d33183nbh

PHI_NODISCARD PHI_CONSTEXPR phi::boolean is_alpha_numeric(const char character) PHI_NOEXCEPT
{
    return static_cast<bool>(static_cast<int>(character >= '0' && character <= '9') |
                             static_cast<int>(character >= 'a' && character <= 'z') |
                             static_cast<int>(character >= 'A' && character <= 'Z'));
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_IS_ALPHA_NUMERIC_HPP
