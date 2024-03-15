#ifndef INCG_PHI_CORE_TEXT_IS_GRAPHICAL_CHARACTER_HPP
#define INCG_PHI_CORE_TEXT_IS_GRAPHICAL_CHARACTER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_NODISCARD PHI_CONSTEXPR phi::boolean is_graphical_character(const char character) PHI_NOEXCEPT
{
    return (character >= 33 && character <= 126);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_IS_GRAPHICAL_CHARACTER_HPP
