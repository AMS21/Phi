#ifndef INCG_PHI_CORE_TEXT_IS_SPACE_HPP
#define INCG_PHI_CORE_TEXT_IS_SPACE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_NODISCARD constexpr phi::boolean is_space(const char c) noexcept
{
    // NOLINTNEXTLINE(readability-implicit-bool-conversion,readability-magic-numbers)
    return static_cast<bool>((c >= 9 && c <= 13) | (c == ' '));
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_IS_SPACE_HPP
