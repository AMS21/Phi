#ifndef INCG_PHI_CORE_FORWARD_HPP
#define INCG_PHI_CORE_FORWARD_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/Config/Inline.hpp"
#include "Phi/TypeTraits/is_lvalue_reference.hpp"
#include "Phi/TypeTraits/remove_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
PHI_ALWAYS_INLINE constexpr TypeT&& forward(remove_reference_t<TypeT>& t) noexcept
{
    return static_cast<TypeT&&>(t);
}

template <typename TypeT>
PHI_ALWAYS_INLINE constexpr TypeT&& forward(remove_reference_t<TypeT>&& t) noexcept
{
    static_assert(!is_lvalue_reference_v<TypeT>,
                  "phi::forward: Can not forward an rvalue as an lvalue");

    return static_cast<TypeT&&>(t);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_FORWARD_HPP
