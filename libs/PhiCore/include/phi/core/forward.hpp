#ifndef INCG_PHI_CORE_FORWARD_HPP
#define INCG_PHI_CORE_FORWARD_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/type_traits/is_lvalue_reference.hpp"
#include "phi/type_traits/remove_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
PHI_ALWAYS_INLINE PHI_CONSTEXPR TypeT&& forward(
        PHI_ATTRIBUTE_LIFETIMEBOUND remove_reference_t<TypeT>& type) PHI_NOEXCEPT
{
    return static_cast<TypeT&&>(type);
}

template <typename TypeT>
PHI_ALWAYS_INLINE PHI_CONSTEXPR TypeT&& forward(
        PHI_ATTRIBUTE_LIFETIMEBOUND remove_reference_t<TypeT>&& type) PHI_NOEXCEPT
{
    static_assert(!is_lvalue_reference<TypeT>::value,
                  "phi::forward: Can not forward an rvalue as an lvalue");

    return static_cast<TypeT&&>(type);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_FORWARD_HPP
