#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_standard_layout.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_scalar.hpp"
#include "phi/type_traits/remove_all_extents.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_STANDARD_LAYOUT()

template <typename TypeT>
struct is_standard_layout : public bool_constant<PHI_IS_STANDARD_LAYOUT(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_standard_layout_v = PHI_IS_STANDARD_LAYOUT(TypeT);

#    endif

#else

template <typename TypeT>
struct is_standard_layout : public bool_constant<is_scalar_v<remove_all_extents_t<TypeT>>>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_standard_layout_v = is_standard_layout<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP
