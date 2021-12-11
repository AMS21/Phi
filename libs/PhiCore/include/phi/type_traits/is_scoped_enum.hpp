#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SCOPED_ENUM_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SCOPED_ENUM_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_convertible.hpp"
#include "phi/type_traits/is_enum.hpp"
#include "phi/type_traits/to_underlying.hpp"

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