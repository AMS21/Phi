#ifndef INCG_PHI_CORE_TYPE_TRAITS_TRUE_T_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_TRUE_T_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename... TypesT>
struct true_t : public bool_constant<true>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename... TypesT>
constexpr PHI_INLINE_VARIABLE bool true_v = true;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_TRUE_T_HPP
