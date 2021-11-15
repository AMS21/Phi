#ifndef INCG_PHI_CORE_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/HasUniqueObjectRepresentations.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/remove_all_extents.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_HAS_UNIQUE_OBJECT_REPRESENTATIONS()

template <typename TypeT>
struct has_unique_object_representations
    : public bool_constant<PHI_HAS_UNIQUE_OBJECT_REPRESENTATIONS(
              remove_cv_t<remove_all_extents_t<TypeT>>)>
{};

template <typename TypeT>
struct has_no_unique_object_representations
    : public bool_constant<!PHI_HAS_UNIQUE_OBJECT_REPRESENTATIONS(
              remove_cv_t<remove_all_extents_t<TypeT>>)>
{};

#else

template <typename TypeT>
struct has_unique_object_representations : public false_type
{
    static_assert(always_false<TypeT>::value,
                  "phi::has_unique_object_representations requires compiler "
                  "support for intrinsic has_unique_object_representations");
};

template <typename TypeT>
struct has_no_unique_object_representations : public false_type
{
    static_assert(always_false<TypeT>::value,
                  "phi::has_no_unique_object_representations requires compiler "
                  "support for intrinsic has_unique_object_representations");
};

#endif

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool has_unique_object_representations_v =
        has_unique_object_representations<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool has_no_unique_object_representations_v =
        has_no_unique_object_representations<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
