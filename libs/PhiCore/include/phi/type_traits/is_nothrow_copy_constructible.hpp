#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_COPY_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_COPY_CONSTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/add_const.hpp"
#include "phi/type_traits/add_lvalue_reference.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/is_nothrow_constructible.hpp"

#if PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE()
#    define PHI_HAS_WORKING_IS_NOTHROW_COPY_CONSTRUCTIBLE() 1
#else
#    define PHI_HAS_WORKING_IS_NOTHROW_COPY_CONSTRUCTIBLE() 0
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_nothrow_copy_constructible
    : public is_nothrow_constructible<
              TypeT, typename add_lvalue_reference<typename add_const<TypeT>::type>::type>
{};

template <typename TypeT>
struct is_not_nothrow_copy_constructible
    : public bool_constant<!is_nothrow_copy_constructible<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_nothrow_copy_constructible_v =
        is_nothrow_copy_constructible<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_nothrow_copy_constructible_v =
        is_not_nothrow_copy_constructible<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_COPY_CONSTRUCTIBLE_HPP
