#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CONVERTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CONVERTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_convertible.hpp"
#include "phi/core/declval.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_CONVERTIBLE()

template <typename FromT, typename ToT>
struct is_convertible : public bool_constant<PHI_IS_CONVERTIBLE(FromT, ToT)>
{};

template <typename FromT, typename ToT>
struct is_not_convertible : public bool_constant<!PHI_IS_CONVERTIBLE(FromT, ToT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE constexpr bool is_convertible_v = PHI_IS_CONVERTIBLE(FromT, ToT);

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE constexpr bool is_not_convertible_v = !PHI_IS_CONVERTIBLE(FromT, ToT);

#    endif

#else

namespace detail
{
    template <typename TypeT>
    auto test_returnable(int)
            -> decltype(static_cast<void>(static_cast<TypeT (*)()>(nullptr)), true_type{});

    template <typename>
    auto test_returnable(...) -> false_type;

    template <typename FromT, typename ToT>
    auto test_implicitly_convertible(int)
            -> decltype(static_cast<void>(declval<void (&)(ToT)>()(declval<FromT>())), true_type{});

    template <typename, typename>
    auto test_implicitly_convertible(...) -> false_type;

} // namespace detail

template <typename FromT, typename ToT>
struct is_convertible
    : public bool_constant<(decltype(detail::test_returnable<ToT>(0))::value &&
                            decltype(detail::test_implicitly_convertible<FromT, ToT>(0))::value) ||
                           (is_void<FromT>::value && is_void<ToT>::value)>
{};

template <typename FromT, typename ToT>
struct is_not_convertible : public bool_constant<!is_convertible<FromT, ToT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE constexpr bool is_convertible_v = is_convertible<FromT, ToT>::value;

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE constexpr bool is_not_convertible_v = is_not_convertible<FromT, ToT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CONVERTIBLE_HPP
