#ifndef INCG_PHI_CORE_ALGORITHM_EXCHANGE_HPP
#define INCG_PHI_CORE_ALGORITHM_EXCHANGE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/move.hpp"
#include "phi/type_traits/is_nothrow_assignable.hpp"
#include "phi/type_traits/is_nothrow_move_constructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename OtherT = TypeT>
PHI_EXTENDED_CONSTEXPR inline TypeT exchange(TypeT& obj, OtherT&& new_value) PHI_NOEXCEPT_EXPR(
        is_nothrow_move_constructible<TypeT>::value&& is_nothrow_assignable<TypeT, OtherT>::value)
{
    TypeT old_value = phi::move(obj);
    obj             = phi::forward<OtherT>(new_value);
    return old_value;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_EXCHANGE_HPP
