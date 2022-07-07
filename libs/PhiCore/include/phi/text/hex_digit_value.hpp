#ifndef INCG_PHI_CORE_TEXT_HEX_DIGIT_VALUE_HPP
#define INCG_PHI_CORE_TEXT_HEX_DIGIT_VALUE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/types.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// Implementation comparision: https://godbolt.org/z/PvTjobbvb

PHI_NODISCARD constexpr u8 hex_digit_value(const char character) noexcept
{
    PHI_DBG_ASSERT((character >= '0' && character <= '9') ||
                           (character >= 'a' && character <= 'f') ||
                           (character >= 'A' && character <= 'F'),
                   "Character out of bounds");

    if (character >= '0' && character <= '9')
    {
        return static_cast<typename u8::value_type>(character - '0');
    }

    if (character >= 'a' && character <= 'f')
    {
        return static_cast<typename u8::value_type>(10 + character - 'a');
    }

    // character >= 'A' && character <= 'F'
    return static_cast<typename u8::value_type>(10 + character - 'A');
}

DETAIL_PHI_END_NAMESPACE()

#endif // #ifndef INCG_PHI_CORE_TEXT_HEX_DIGIT_VALUE_HPP
