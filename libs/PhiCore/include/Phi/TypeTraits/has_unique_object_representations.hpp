#ifndef INCG_PHI_CORE_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/remove_all_extents.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_HAS_UNIQUE_OBJECT_REPRESENTATIONS()

template <typename TypeT>
struct has_unique_object_representations : public bool_constant<__has_unique_object_representations(
                                                   remove_cv_t<remove_all_extents_t<TypeT>>)>
{};

#else

template <typename TypeT>
struct has_unique_object_representations : public false_type
{
    static_assert(always_false<TypeT>, "phi::has_unique_object_representations requires compiler "
                                       "support for intrinsic has_unique_object_representations");
};

#endif

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool has_unique_object_representations_v =
        has_unique_object_representations<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
