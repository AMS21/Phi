#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_trivially_assignable.hpp"
#include "phi/type_traits/false_t.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE()

#    define PHI_HAS_WORKING_IS_TRIVIALLY_ASSIGNABLE() 1

template <typename TypeT, typename ArgT>
struct is_trivially_assignable : public bool_constant<PHI_IS_TRIVIALLY_ASSIGNABLE(TypeT, ArgT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_assignable_v = PHI_IS_TRIVIALLY_ASSIGNABLE(TypeT,
                                                                                           ArgT);

#    endif

#else

#    define PHI_HAS_WORKING_IS_TRIVIALLY_ASSIGNABLE() 0

template <typename TypeT, typename ArgT>
struct is_trivially_assignable : public false_type
{
    static_assert(false_t<TypeT>::value,
                  "phi::is_trivially_assignable requires compiler support for "
                  "intrinsic __is_trivially_assignable");
};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_assignable_v =
        is_trivially_assignable<TypeT, ArgT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP
