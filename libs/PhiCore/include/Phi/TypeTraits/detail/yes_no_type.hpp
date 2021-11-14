#ifndef INCG_PHI_CORE_TYPE_TRAITS_DETAIL_YES_NO_TYPE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_DETAIL_YES_NO_TYPE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Core/SizeT.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    // size == 1
    struct yes_type
    {
        char padding;
    };

    PHI_INLINE_VARIABLE constexpr phi::size_t sizeof_yes_type = sizeof(yes_type);

    // size == 8
    struct no_type
    {
        char padding[8];
    };

    PHI_INLINE_VARIABLE constexpr phi::size_t sizeof_no_type = sizeof(no_type);
} // namespace detail

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_DETAIL_YES_NO_TYPE_HPP
