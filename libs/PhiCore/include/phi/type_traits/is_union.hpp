#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_union.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_IS_UNION()

#    define PHI_HAS_WORKING_IS_UNION() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_union : public bool_constant<PHI_IS_UNION(TypeT)>
{};

template <typename TypeT>
struct is_not_union : public bool_constant<!PHI_IS_UNION(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_union_v = PHI_IS_UNION(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_union_v = !PHI_IS_UNION(TypeT);

#    endif

#else

#    include "phi/type_traits/false_t.hpp"

#    define PHI_HAS_WORKING_IS_UNION() 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_union : public false_type
{
    static_assert(false_t<TypeT>::value,
                  "phi::is_union requires compiler support to properly work.");
};

template <typename TypeT>
struct is_not_union : public bool_constant<!is_union<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_union_v = is_union<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_union_v = is_not_union<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNION_HPP
