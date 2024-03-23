#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_FINAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_FINAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_final.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_FINAL()

DETAIL_PHI_BEGIN_NAMESPACE()

#    define PHI_HAS_WORKING_IS_FINAL() 1

template <typename TypeT>
struct is_final : public integral_constant<bool, PHI_IS_FINAL(TypeT)>
{};

template <typename TypeT>
struct is_not_final : public integral_constant<bool, !PHI_IS_FINAL(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_final_v = PHI_IS_FINAL(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_final_v = !PHI_IS_FINAL(TypeT);

#    endif

#else

#    include "phi/type_traits/false_t.hpp"

#    define PHI_HAS_WORKING_IS_FINAL() 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_final : public false_type
{
    static_assert(false_t<TypeT>::value,
                  "phi::is_final requires compiler support for intrinsic __is_final");
};

template <typename TypeT>
struct is_not_final : public false_type
{
    static_assert(false_t<TypeT>::value,
                  "phi::is_not_final requires compiler support for intrinsic __is_final");
};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_final_v = is_final<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_final_v = is_not_final<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_FINAL_HPP
