#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/declval.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_convertible.hpp"
#include "phi/type_traits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunused-template")

namespace detail
{
    template <typename TypeT>
    static void is_nothrow_convertible_test_noexcept(TypeT) noexcept;

    template <typename FromT, typename ToT>
    static bool_constant<noexcept(is_nothrow_convertible_test_noexcept<ToT>(declval<FromT>()))>
    is_nothrow_convertible_test();

    template <typename FromT, typename ToT>
    struct is_nothrow_convertible_impl_3
        : public decltype(is_nothrow_convertible_test<FromT, ToT>())
    {};

    template <typename FromT, typename ToT, bool = is_convertible<FromT, ToT>::value>
    struct is_nothrow_convertible_impl_2 : public is_nothrow_convertible_impl_3<FromT, ToT>
    {};

    template <typename FromT, typename ToT>
    struct is_nothrow_convertible_impl_2<FromT, ToT, false> : public false_type
    {};

    template <typename FromT, typename ToT, bool = is_void<FromT>::value&& is_void<ToT>::value>
    struct is_nothrow_convertible_impl : public is_nothrow_convertible_impl_2<FromT, ToT>
    {};

    template <typename FromT, typename ToT>
    struct is_nothrow_convertible_impl<FromT, ToT, true> : public true_type
    {};

} // namespace detail

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename FromT, typename ToT>
struct is_nothrow_convertible : public detail::is_nothrow_convertible_impl<FromT, ToT>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_convertible_v =
        is_nothrow_convertible<FromT, ToT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP
