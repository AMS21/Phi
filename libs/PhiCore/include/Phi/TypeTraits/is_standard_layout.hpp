#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_scalar.hpp"
#include "Phi/TypeTraits/remove_all_extents.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_STANDARD_LAYOUT()

template <typename TypeT>
struct is_standard_layout : public bool_constant<__is_standard_layout(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_standard_layout_v = __is_standard_layout(TypeT);

#else

template <typename TypeT>
struct is_standard_layout : public bool_constant<is_scalar_v<remove_all_extents_t<TypeT>>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_standard_layout_v = is_standard_layout<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP
