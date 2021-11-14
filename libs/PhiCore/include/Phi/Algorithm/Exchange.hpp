#ifndef INCG_PHI_CORE_ALGORITHM_EXCHANGE_HPP
#define INCG_PHI_CORE_ALGORITHM_EXCHANGE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/Core/Forward.hpp"
#include "Phi/Core/Move.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename OtherT = TypeT>
PHI_EXTENDED_CONSTEXPR inline TypeT exchange(TypeT& obj, OtherT&& new_value) // TODO: Noexcept?
{
    TypeT old_value = phi::move(obj);
    obj             = phi::forward<OtherT>(new_value);
    return old_value;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_EXCHANGE_HPP
