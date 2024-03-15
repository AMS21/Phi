#ifndef INCG_PHI_CORE_TEXT_IS_BINARY_DIGIT_HPP
#define INCG_PHI_CORE_TEXT_IS_BINARY_DIGIT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// Implementation comparison: https://godbolt.org/z/8G1EvYTGP

PHI_NODISCARD PHI_CONSTEXPR phi::boolean is_binary_digit(const char character) noexcept
{
    return (character == '0' || character == '1');
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_IS_BINARY_DIGIT_HPP
