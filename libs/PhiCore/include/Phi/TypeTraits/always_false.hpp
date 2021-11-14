#ifndef INCG_PHI_CORE_TYPE_TRAITS_ALWAYS_FALSE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ALWAYS_FALSE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename... TypesT>
struct always_false : public bool_constant<false>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename... TypesT>
constexpr PHI_INLINE_VARIABLE bool always_false_v = false;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ALWAYS_FALSE_HPP
