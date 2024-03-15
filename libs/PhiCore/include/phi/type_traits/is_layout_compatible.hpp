#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_LAYOUT_COMPATIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_LAYOUT_COMPATIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_layout_compatible.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_IS_LAYOUT_COMPATIBLE()

#    define PHI_HAS_WORKING_IS_LAYOUT_COMPATIBLE() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename WithT>
struct is_layout_compatible : public bool_constant<PHI_IS_LAYOUT_COMPATIBLE(TypeT, WithT)>
{};

template <typename TypeT, typename WithT>
struct is_not_layout_compatible : public bool_constant<!PHI_IS_LAYOUT_COMPATIBLE(TypeT, WithT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename WithT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_layout_compatible_v =
        PHI_IS_LAYOUT_COMPATIBLE(TypeT, WithT);

template <typename TypeT, typename WithT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_layout_compatible_v =
        !PHI_IS_LAYOUT_COMPATIBLE(TypeT, WithT);

#    endif

#else

#    include "phi/type_traits/false_t.hpp"

#    define PHI_HAS_WORKING_IS_LAYOUT_COMPATIBLE() 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename WithT>
struct is_layout_compatible : public false_type
{
    static_assert(phi::false_t<TypeT>::value,
                  "phi::is_layout_compatible require compiler support for __is_layout_compatible");
};

template <typename TypeT, typename WithT>
struct is_not_layout_compatible : public bool_constant<!is_layout_compatible<TypeT, WithT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename WithT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_layout_compatible_v =
        is_layout_compatible<TypeT, WithT>::value;

template <typename TypeT, typename WithT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_layout_compatible_v =
        is_not_layout_compatible<TypeT, WithT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_LAYOUT_COMPATIBLE_HPP
