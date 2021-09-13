#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_VOLATILE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_VOLATILE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_VOLATILE()

template <typename TypeT>
struct is_volatile : bool_constant<__is_volatile(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_volatile_v = __is_volatile(TypeT);

#else

template <typename TypeT>
struct is_volatile : false_type
{};

template <typename TypeT>
struct is_volatile<volatile TypeT> : true_type
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_volatile_v = is_volatile<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_VOLATILE_HPP
