#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_MEMBER_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_MEMBER_POINTER_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsMemberPointer.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_MEMBER_POINTER()

template <typename TypeT>
struct is_member_pointer : public bool_constant<PHI_IS_MEMBER_POINTER(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_member_pointer_v = PHI_IS_MEMBER_POINTER(TypeT);

#    endif

#else

namespace detail
{
    template <typename TypeT>
    struct is_member_pointer_impl : false_type
    {};

    template <typename TypeT, typename OtherT>
    struct is_member_pointer_impl<TypeT OtherT::*> : true_type
    {};
} // namespace detail

template <typename TypeT>
struct is_member_pointer : public detail::is_member_pointer_impl<remove_cv_t<TypeT>>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_member_pointer_v = is_member_pointer<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_MEMBER_POINTER_HPP
