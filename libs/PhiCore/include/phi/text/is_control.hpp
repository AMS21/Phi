#ifndef INCG_PHI_CORE_TEXT_IS_CONTROL_HPP
#define INCG_PHI_CORE_TEXT_IS_CONTROL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_NODISCARD constexpr phi::boolean is_control(const char character) noexcept
{
    // NOLINTNEXTLINE(readability-implicit-bool-conversion)
    return static_cast<bool>((character >= 0 && character <= 31) | (character == 127));
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_IS_CONTROL_HPP
