#ifndef INCG_PHI_CORE_TEXT_DIGIT_VALUE_HPP
#define INCG_PHI_CORE_TEXT_DIGIT_VALUE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/types.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wsuggest-attribute=pure")

PHI_NODISCARD constexpr u8 digit_value(const char character) noexcept
{
    PHI_ASSERT(character >= '0' && character <= '9', "Character out of bounds");

    return static_cast<typename u8::value_type>(character - '0');
}

PHI_GCC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_DIGIT_VALUE_HPP
