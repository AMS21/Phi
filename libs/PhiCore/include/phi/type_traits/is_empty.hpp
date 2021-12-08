#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_EMPTY_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_EMPTY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_empty.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_class.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_EMPTY()

template <typename TypeT>
struct is_empty : public bool_constant<PHI_IS_EMPTY(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_empty_v = PHI_IS_EMPTY(TypeT);

#    endif

#else

namespace detail
{
    template <typename TypeT>
    struct is_empty_test1 : public TypeT
    {
        double lx;
    };

    struct is_empty_test2
    {
        double lx;
    };

    template <typename TypeT, bool = is_class_v<TypeT>>
    struct is_empty_impl
        : public bool_constant<sizeof(is_empty_test1<TypeT>) == sizeof(is_empty_test2)>
    {};

    template <typename TypeT>
    struct is_empty_impl<TypeT, false> : public false_type
    {};
} // namespace detail

template <typename TypeT>
struct is_empty : public detail::is_empty_impl<TypeT>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_empty_v = is_empty<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_EMPTY_HPP
