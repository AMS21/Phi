#ifndef INCG_PHI_CORE_FORWARD_HPP
#define INCG_PHI_CORE_FORWARD_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline.hpp"
#include "phi/type_traits/is_lvalue_reference.hpp"
#include "phi/type_traits/remove_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
PHI_ALWAYS_INLINE constexpr TypeT&& forward(remove_reference_t<TypeT>& t) noexcept
{
    return static_cast<TypeT&&>(t);
}

template <typename TypeT>
PHI_ALWAYS_INLINE constexpr TypeT&& forward(remove_reference_t<TypeT>&& t) noexcept
{
    static_assert(!is_lvalue_reference<TypeT>::value,
                  "phi::forward: Can not forward an rvalue as an lvalue");

    return static_cast<TypeT&&>(t);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_FORWARD_HPP
