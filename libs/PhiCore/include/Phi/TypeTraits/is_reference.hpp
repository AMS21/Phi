#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_REFERENCE()

template <typename TypeT>
struct is_reference : public bool_constant<__is_reference(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_reference_v = __is_reference(TypeT);

#else

template <typename TypeT>
struct is_reference : public false_type
{};

// l-value reference
template <typename TypeT>
struct is_reference<TypeT&> : public true_type
{};

// r-value reference
template <typename TypeT>
struct is_reference<TypeT&&> : public true_type
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_reference_v = is_reference<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_HPP
