#ifndef INCG_PHI_CORE_TEXT_IS_PUNCTUATION_HPP
#define INCG_PHI_CORE_TEXT_IS_PUNCTUATION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_NODISCARD PHI_CONSTEXPR phi::boolean is_punctuation(const char character) PHI_NOEXCEPT
{
    // NOLINTBEGIN
    return (character >= 33 && character <= 47) || (character >= 58 && character <= 64) ||
           (character >= 91 && character <= 96) || (character >= 123 && character <= 126);
    // NOLINTEND
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_IS_PUNCTUATION_HPP
