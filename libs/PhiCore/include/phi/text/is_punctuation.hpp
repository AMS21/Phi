#ifndef INCG_PHI_CORE_TEXT_IS_PUNCTUATION_HPP
#define INCG_PHI_CORE_TEXT_IS_PUNCTUATION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_NODISCARD constexpr phi::boolean is_punctuation(const char c) noexcept
{
    // NOLINTBEGIN
    return (c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) ||
           (c >= 123 && c <= 126);
    // NOLINTEND
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_IS_PUNCTUATION_HPP
