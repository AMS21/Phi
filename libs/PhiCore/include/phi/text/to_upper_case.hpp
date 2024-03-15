#ifndef INCG_PHI_CORE_TEXT_TO_UPPER_CASE_HPP
#define INCG_PHI_CORE_TEXT_TO_UPPER_CASE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// Implementation comparison: https://godbolt.org/z/1bEsG5nrE

PHI_NODISCARD PHI_CONSTEXPR char to_upper_case(const char character) PHI_NOEXCEPT
{
    // NOLINTNEXTLINE(bugprone-narrowing-conversions,cppcoreguidelines-narrowing-conversions)
    return (character >= 'a' && character <= 'z') ? static_cast<char>(character - 32) : character;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_TO_UPPER_CASE_HPP
