#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/add_const.hpp"
#include "phi/type_traits/add_lvalue_reference.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_trivially_assignable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#define PHI_HAS_WORKING_IS_TRIVIALLY_COPY_ASSIGNABLE() PHI_HAS_WORKING_IS_TRIVIALLY_ASSIGNABLE()

template <typename TypeT>
struct is_trivially_copy_assignable
    : public is_trivially_assignable<
              typename add_lvalue_reference<TypeT>::type,
              typename add_lvalue_reference<typename add_const<TypeT>::type>::type>
{};

template <typename TypeT>
struct is_not_trivially_copy_assignable
    : public bool_constant<!is_trivially_copy_assignable<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_copy_assignable_v =
        is_trivially_copy_assignable<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_trivially_copy_assignable_v =
        is_not_trivially_copy_assignable<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP
