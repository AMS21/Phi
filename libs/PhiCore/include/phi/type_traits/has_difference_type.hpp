#ifndef INCG_PHI_TYPE_TRAITS_HAS_DIFFERENCE_TYPE_HPP
#define INCG_PHI_TYPE_TRAITS_HAS_DIFFERENCE_TYPE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/void_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename = void>
struct has_difference_type : public false_type
{};

template <typename TypeT>
struct has_difference_type<TypeT, void_t<typename TypeT::difference_type>> : public true_type
{};

template <typename TypeT>
struct has_no_difference_type : public bool_constant<!has_difference_type<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool has_difference_type_v = has_difference_type<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool has_no_difference_type_v = has_no_difference_type<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_TYPE_TRAITS_HAS_DIFFERENCE_TYPE_HPP
