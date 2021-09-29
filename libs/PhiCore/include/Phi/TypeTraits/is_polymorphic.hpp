#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_POLYMORPHIC_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_POLYMORPHIC_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_POLYMORPHIC()

template <typename TypeT>
struct is_polymorphic : public bool_constant<__is_polymorphic(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_polymorphic_v = __is_polymorphic(TypeT);

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

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_polymorphic_v = is_polymorphic<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_POLYMORPHIC_HPP
