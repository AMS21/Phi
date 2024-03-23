#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_COPY_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_COPY_ASSIGNABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/add_const.hpp"
#include "phi/type_traits/add_lvalue_reference.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_assignable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_copy_assignable : public is_assignable<add_lvalue_reference_t<TypeT>,
                                                 add_lvalue_reference_t<add_const_t<TypeT>>>
{};

template <typename TypeT>
struct is_not_copy_assignable : public integral_constant<bool, !is_copy_assignable<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_copy_assignable_v = is_copy_assignable<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_copy_assignable_v =
        is_not_copy_assignable<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_COPY_ASSIGNABLE_HPP
