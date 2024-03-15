#ifndef INCG_PHI_CORE_TEXT_TO_LOWER_CASE_HPP
#define INCG_PHI_CORE_TEXT_TO_LOWER_CASE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// Implementation comparison: https://godbolt.org/z/1bEsG5nrE

PHI_NODISCARD PHI_CONSTEXPR char to_lower_case(const char character) PHI_NOEXCEPT
{
    // NOLINTNEXTLINE(bugprone-narrowing-conversions,readability,cppcoreguidelines-narrowing-conversions)
    return (character >= 'A' && character <= 'Z') ? static_cast<char>(character + 32) : character;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_TO_LOWER_CASE_HPP
