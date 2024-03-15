#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_BOOL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_BOOL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/is_same_rcv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_unsafe_bool : public is_same_rcv<TypeT, bool>
{};

template <typename TypeT>
struct is_not_unsafe_bool : public bool_constant<!is_unsafe_bool<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_unsafe_bool_v = is_unsafe_bool<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_unsafe_bool_v = is_not_unsafe_bool<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_BOOL_HPP
