#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_BOOL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_BOOL_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/is_same_rcv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_unsafe_bool : public is_same_rcv<TypeT, bool>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_unsafe_bool_v = is_unsafe_bool<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_BOOL_HPP
