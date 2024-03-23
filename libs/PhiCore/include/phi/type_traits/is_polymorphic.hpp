#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_POLYMORPHIC_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_POLYMORPHIC_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_polymorphic.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_POLYMORPHIC()

template <typename TypeT>
struct is_polymorphic : public integral_constant<bool, PHI_IS_POLYMORPHIC(TypeT)>
{};

template <typename TypeT>
struct is_not_polymorphic : public integral_constant<bool, !PHI_IS_POLYMORPHIC(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_polymorphic_v = PHI_IS_POLYMORPHIC(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_polymorphic_v = !PHI_IS_POLYMORPHIC(TypeT);

#    endif

#else

namespace detail
{
    template <typename TypeT>
    true_type detect_is_polymorphic(
            decltype(dynamic_cast<const volatile void*>(static_cast<TypeT*>(nullptr))));

    template <typename TypeT>
    false_type detect_is_polymorphic(...);

} // namespace detail

template <typename TypeT>
struct is_polymorphic : public decltype(detail::detect_is_polymorphic<TypeT>(nullptr))
{};

template <typename TypeT>
struct is_not_polymorphic : public integral_constant<bool, !is_polymorphic<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_polymorphic_v = is_polymorphic<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_polymorphic_v = is_not_polymorphic<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_POLYMORPHIC_HPP
