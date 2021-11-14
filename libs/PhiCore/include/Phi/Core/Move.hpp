#ifndef INCG_PHI_CORE_MOVE_HPP
#define INCG_PHI_CORE_MOVE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/TypeTraits/remove_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
constexpr remove_reference_t<TypeT>&& move(TypeT&& arg) noexcept
{
    return static_cast<remove_reference_t<TypeT>&&>(arg);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MOVE_HPP
