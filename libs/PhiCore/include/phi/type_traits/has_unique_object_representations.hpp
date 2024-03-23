#ifndef INCG_PHI_CORE_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/has_unique_object_representations.hpp"
#include "phi/type_traits/false_t.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/remove_all_extents.hpp"
#include "phi/type_traits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_HAS_UNIQUE_OBJECT_REPRESENTATIONS()

#    define PHI_HAS_WORKING_HAS_UNIQUE_OBJECT_REPRESENTATIONS() 1

template <typename TypeT>
struct has_unique_object_representations
    : public integral_constant<bool, PHI_HAS_UNIQUE_OBJECT_REPRESENTATIONS(
                                             remove_cv_t<remove_all_extents_t<TypeT>>)>
{};

template <typename TypeT>
struct has_no_unique_object_representations
    : public integral_constant<bool, !PHI_HAS_UNIQUE_OBJECT_REPRESENTATIONS(
                                             remove_cv_t<remove_all_extents_t<TypeT>>)>
{};

#else

#    define PHI_HAS_WORKING_HAS_UNIQUE_OBJECT_REPRESENTATIONS() 0

template <typename TypeT>
struct has_unique_object_representations : public false_type
{
    static_assert(false_t<TypeT>::value, "phi::has_unique_object_representations requires compiler "
                                         "support for intrinsic has_unique_object_representations");
};

template <typename TypeT>
struct has_no_unique_object_representations : public false_type
{
    static_assert(false_t<TypeT>::value,
                  "phi::has_no_unique_object_representations requires compiler support for "
                  "intrinsic has_unique_object_representations");
};

#endif

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool has_unique_object_representations_v =
        has_unique_object_representations<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool has_no_unique_object_representations_v =
        has_no_unique_object_representations<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
