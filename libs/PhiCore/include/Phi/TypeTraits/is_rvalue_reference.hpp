#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_RVALUE_REFERENCE()

template <typename TypeT>
struct is_rvalue_reference : public bool_constant<__is_rvalue_reference(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_rvalue_reference_v = __is_rvalue_reference(TypeT);

#else

template <typename TypeT>
struct is_rvalue_reference : false_type
{};

template <typename TypeT>
struct is_rvalue_reference<TypeT&&> : true_type
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_rvalue_reference_v = is_rvalue_reference<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP
