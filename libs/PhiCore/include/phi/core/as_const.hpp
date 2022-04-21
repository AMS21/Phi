#ifndef INCG_PHI_CORE_AS_CONST_HPP
#define INCG_PHI_CORE_AS_CONST_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/type_traits/add_const.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
PHI_NODISCARD constexpr add_const_t<TypeT>& as_const(TypeT& value) noexcept
{
    return value;
}

template <typename TypeT>
void as_const(const TypeT&&) = delete;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_AS_CONST_HPP
