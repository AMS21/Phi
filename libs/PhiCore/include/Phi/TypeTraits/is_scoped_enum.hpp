#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SCOPED_ENUM_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SCOPED_ENUM_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_convertible.hpp"
#include "Phi/TypeTraits/is_enum.hpp"
#include "Phi/TypeTraits/to_underlying.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool IsEnum>
    struct is_scoped_enum_impl : false_type
    {};

    template <typename TypeT>
    struct is_scoped_enum_impl<TypeT, true>
        : public bool_constant<!is_convertible<TypeT, underlying_type_t<TypeT>>::value>
    {};
} // namespace detail

template <typename TypeT>
struct is_scoped_enum : public detail::is_scoped_enum_impl<TypeT, is_enum<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_scoped_enum_v = is_scoped_enum<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SCOPED_ENUM_HPP
