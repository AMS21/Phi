#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ARRAY_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ARRAY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/bool_constant.hpp"

// NOTE: We're no longer implementing `is_array` using the intrinsic `PHI_IS_ARRAY` due to its inconsistent and unwanted behavior regard zero sized arrays. Keep in mind that zero sized arrays themselves are an extension and according to the standard are malformed.
// See this LLVM issue for some more info: https://github.com/llvm/llvm-project/issues/54705

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_array : public false_type
{};

template <typename TypeT>
struct is_array<TypeT[]> : public true_type
{};

template <typename TypeT, size_t Size>
struct is_array<TypeT[Size]> : public true_type
{};

template <typename TypeT>
struct is_not_array : public bool_constant<!is_array<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_array_v = is_array<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_array_v = is_not_array<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ARRAY_HPP
