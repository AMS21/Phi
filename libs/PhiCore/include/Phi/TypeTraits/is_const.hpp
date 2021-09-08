#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CONST_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CONST_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_const : false_type
{};

template <typename TypeT>
struct is_const<const TypeT> : true_type
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_const_v = is_const<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CONST_HPP
