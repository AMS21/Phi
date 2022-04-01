#ifndef INCG_PHI_CORE_TEXT_TO_LOWER_CASE_HPP
#define INCG_PHI_CORE_TEXT_TO_LOWER_CASE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// Implementation comparision: https://godbolt.org/z/1bEsG5nrE

PHI_NODISCARD constexpr char to_lower_case(const char c) noexcept
{
    // NOLINTNEXTLINE(bugprone-narrowing-conversions,readability-magic-numbers,cppcoreguidelines-narrowing-conversions)
    return (c >= 'A' && c <= 'Z') ? static_cast<char>(c + 32) : c;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_TO_LOWER_CASE_HPP
