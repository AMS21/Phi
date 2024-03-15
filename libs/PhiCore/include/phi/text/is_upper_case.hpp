#ifndef INCG_PHI_CORE_TEXT_IS_UPPER_CASE_HPP
#define INCG_PHI_CORE_TEXT_IS_UPPER_CASE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_NODISCARD PHI_CONSTEXPR phi::boolean is_upper_case(const char character) PHI_NOEXCEPT
{
    return (character >= 'A' && character <= 'Z');
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_IS_UPPER_CASE_HPP
