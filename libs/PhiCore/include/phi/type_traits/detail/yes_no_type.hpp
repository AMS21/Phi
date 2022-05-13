#ifndef INCG_PHI_CORE_TYPE_TRAITS_DETAIL_YES_NO_TYPE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_DETAIL_YES_NO_TYPE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/size_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wunused-const-variable")

namespace detail
{
    // size == 1
    struct yes_type
    {
        char m_Padding;
    };

    PHI_INLINE_VARIABLE constexpr static phi::size_t sizeof_yes_type = sizeof(yes_type);

    // size == 8
    struct no_type
    {
        char m_Padding[8]; // NOLINT(readability-magic-numbers)
    };

    PHI_INLINE_VARIABLE constexpr static phi::size_t sizeof_no_type = sizeof(no_type);
} // namespace detail

PHI_GCC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_DETAIL_YES_NO_TYPE_HPP
