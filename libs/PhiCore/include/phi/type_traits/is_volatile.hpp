#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_VOLATILE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_VOLATILE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_volatile.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_VOLATILE()

template <typename TypeT>
struct is_volatile : public bool_constant<PHI_IS_VOLATILE(TypeT)>
{};

template <typename TypeT>
struct is_not_volatile : public bool_constant<!PHI_IS_VOLATILE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_volatile_v = PHI_IS_VOLATILE(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_volatile_v = !PHI_IS_VOLATILE(TypeT);

#    endif

#else

template <typename TypeT>
struct is_volatile : public false_type
{};

template <typename TypeT>
struct is_volatile<volatile TypeT> : public true_type
{};

template <typename TypeT>
struct is_not_volatile : public bool_constant<!is_volatile<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_volatile_v = is_volatile<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_volatile_v = is_not_volatile<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_VOLATILE_HPP
