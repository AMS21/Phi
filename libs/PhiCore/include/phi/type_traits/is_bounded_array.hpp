#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_bounded_array.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/bool_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_BOUNDED_ARRAY()

template <typename TypeT>
struct is_bounded_array : public bool_constant<PHI_IS_BOUNDED_ARRAY(TypeT)>
{};

template <typename TypeT>
struct is_not_bounded_array : public bool_constant<!PHI_IS_BOUNDED_ARRAY(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_bounded_array_v = PHI_IS_BOUNDED_ARRAY(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_bounded_array_v = !PHI_IS_BOUNDED_ARRAY(TypeT);

#    endif

#else

template <typename TypeT>
struct is_bounded_array : public false_type
{};

template <typename TypeT, size_t Dimension>
struct is_bounded_array<TypeT[Dimension]> : public true_type
{};

template <typename TypeT>
struct is_not_bounded_array : public bool_constant<!is_bounded_array<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_bounded_array_v = is_bounded_array<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_bounded_array_v = is_not_bounded_array<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP
