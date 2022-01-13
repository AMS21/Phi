#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_EMPTY_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_EMPTY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_empty.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_EMPTY()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_empty : public bool_constant<PHI_IS_EMPTY(TypeT)>
{};

template <typename TypeT>
struct is_not_empty : public bool_constant<!PHI_IS_EMPTY(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_empty_v = PHI_IS_EMPTY(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_empty_v = !PHI_IS_EMPTY(TypeT);

#    endif

#else

#    include "phi/compiler_support/intrinsics/is_final.hpp"
#    include "phi/type_traits/is_class.hpp"
#    include "phi/type_traits/is_final.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

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

    template <typename TypeT, bool = is_class<TypeT>::value>
    struct is_empty_impl
        : public bool_constant<sizeof(is_empty_test1<TypeT>) == sizeof(is_empty_test2)>
    {};

    template <typename TypeT>
    struct is_empty_impl<TypeT, false> : public false_type
    {};
} // namespace detail

template <typename TypeT>
struct is_empty : public detail::is_empty_impl<TypeT>
{
#    if PHI_SUPPORTS_IS_FINAL()
    static_assert(
            is_not_final<TypeT>::value,
            "phi::is_empty: The non intrinsic version cannot handle classes declared as final");
#    endif
};

template <typename TypeT>
struct is_not_empty : public bool_constant<!is_empty<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_empty_v = is_empty<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_empty_v = is_not_empty<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_EMPTY_HPP
