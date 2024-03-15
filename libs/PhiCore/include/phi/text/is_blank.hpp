#ifndef INCG_PHI_CORE_TEXT_IS_BLANK_HPP
#define INCG_PHI_CORE_TEXT_IS_BLANK_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_NODISCARD PHI_CONSTEXPR phi::boolean is_blank(const char character) noexcept
{
    // NOLINTNEXTLINE(readability-implicit-bool-conversion)
    return static_cast<bool>((character == '\t') | (character == ' '));
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_IS_BLANK_HPP
