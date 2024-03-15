#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_STATIC_CASTABLE_TO_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_STATIC_CASTABLE_TO_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/core/declval.hpp"
#include "phi/type_traits/bool_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    struct do_is_static_castable_impl
    {
        template <typename FromT, typename ToT,
                  typename = decltype(static_cast<ToT>(declval<FromT>()))>
        static true_type test(int);

        template <typename, typename>
        static false_type test(...);
    };

    template <typename FromT, typename ToT>
    struct is_static_castable_to_impl : public do_is_static_castable_impl
    {
        using type = decltype(test<FromT, ToT>(0));
    };
} // namespace detail

template <typename FromT, typename ToT>
struct is_static_castable_to : public detail::is_static_castable_to_impl<FromT, ToT>::type
{};

template <typename FromT, typename ToT>
struct is_not_static_castable_to : public bool_constant<!is_static_castable_to<FromT, ToT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_static_castable_to_v =
        is_static_castable_to<FromT, ToT>::value;

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_static_castable_to_v =
        is_not_static_castable_to<FromT, ToT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_STATIC_CASTABLE_TO_HPP
