#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_STATIC_CASTABLE_TO_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_STATIC_CASTABLE_TO_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/core/declval.hpp"
#include "phi/type_traits/bool_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename FromT, typename ToT, typename EnabledT>
    struct is_static_castable_to_impl : public false_type
    {};

    template <typename FromT, typename ToT>
    struct is_static_castable_to_impl<FromT, ToT,
                                      decltype(void(static_cast<ToT>(declval<FromT>())))>
        : public true_type
    {};
} // namespace detail

template <typename FromT, typename ToT>
struct is_static_castable_to : public detail::is_static_castable_to_impl<FromT, ToT, void>
{};

template <typename FromT, typename ToT>
struct is_not_static_castable_to : public bool_constant<!is_static_castable_to<FromT, ToT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE constexpr bool is_static_castable_to_v =
        is_static_castable_to<FromT, ToT>::value;

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE constexpr bool is_not_static_castable_to_v =
        is_not_static_castable_to<FromT, ToT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_STATIC_CASTABLE_TO_HPP
