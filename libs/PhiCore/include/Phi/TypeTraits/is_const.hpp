#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CONST_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CONST_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_CONST()

template <typename TypeT>
struct is_const : public bool_constant<__is_const(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_const_v = __is_const(TypeT);

#else

template <typename TypeT>
struct is_const : public false_type
{};

template <typename TypeT>
struct is_const<const TypeT> : public true_type
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_const_v = is_const<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CONST_HPP
