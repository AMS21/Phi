#ifndef INCG_PHI_CORE_TEXT_BINARY_DIGIT_VALUE_HPP
#define INCG_PHI_CORE_TEXT_BINARY_DIGIT_VALUE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/types.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_NODISCARD PHI_CONSTEXPR u8 binary_digit_value(const char character) PHI_NOEXCEPT
{
    PHI_ASSERT(character >= '0' && character <= '1', "Character out of bounds");

    return static_cast<typename u8::value_type>(character - '0');
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_BINARY_DIGIT_VALUE_HPP
