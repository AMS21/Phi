#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_reference.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_REFERENCE()

template <typename TypeT>
struct is_reference : public bool_constant<PHI_IS_REFERENCE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_reference_v = PHI_IS_REFERENCE(TypeT);

#    endif

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

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_reference_v = is_reference<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_HPP
