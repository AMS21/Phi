#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_COMPOUND_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_COMPOUND_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_fundamental.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_COMPOUND()

template <typename TypeT>
struct is_compound : public bool_constant<__is_compound(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_compound_v = __is_compound(TypeT);

#    endif

#else

template <typename TypeT>
struct is_compound : public bool_constant<!is_fundamental_v<TypeT>>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_compound_v = is_compound<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_COMPOUND_HPP
