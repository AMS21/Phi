#ifndef INCG_PHI_CORE_AS_CONST_HPP
#define INCG_PHI_CORE_AS_CONST_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/TypeTraits/add_const.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
PHI_NODISCARD constexpr add_const_t<TypeT>& as_const(TypeT& t) noexcept
{
    return t;
}

template <typename TypeT>
void as_const(const TypeT&&) = delete;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_AS_CONST_HPP
