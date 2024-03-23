#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_POD_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_POD_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_pod.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_POD()

#    define PHI_HAS_WORKING_IS_POD() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_pod : public phi::integral_constant<bool, PHI_IS_POD(TypeT)>
{};

template <typename TypeT>
struct is_not_pod : public phi::integral_constant<bool, !PHI_IS_POD(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_pod_v = PHI_IS_POD(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_pod_v = !PHI_IS_POD(TypeT);

#    endif

#else

#    include "phi/type_traits/is_trivially_copy_assignable.hpp"
#    include "phi/type_traits/is_trivially_copy_constructible.hpp"
#    include "phi/type_traits/is_trivially_default_constructible.hpp"
#    include "phi/type_traits/is_trivially_destructible.hpp"

#    define PHI_HAS_WORKING_IS_POD()                                                               \
        PHI_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE() && PHI_SUPPORTS_IS_TRIVIALLY_CONSTRUCTIBLE() &&     \
                PHI_SUPPORTS_IS_TRIVIALLY_DESTRUCTIBLE()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_pod
    : public integral_constant<bool, is_trivially_default_constructible<TypeT>::value &&
                                             is_trivially_copy_constructible<TypeT>::value &&
                                             is_trivially_copy_assignable<TypeT>::value &&
                                             is_trivially_destructible<TypeT>::value>
{};

template <typename TypeT>
struct is_not_pod : public integral_constant<bool, !is_pod<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_pod_v = is_pod<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_pod_v = is_not_pod<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_POD_HPP
