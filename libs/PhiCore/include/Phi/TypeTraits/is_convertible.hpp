#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CONVERTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CONVERTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_void.hpp"
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_CONVERTIBLE_TO()

template <typename FromT, typename ToT>
struct is_convertible : public bool_constant<__is_convertible_to(FromT, ToT)>
{};

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE constexpr bool is_convertible_v = __is_convertible_to(FromT, ToT);

#else

namespace detail
{
    template <typename TypeT>
    auto test_returnable(int) -> decltype(void(static_cast<TypeT (*)()>(nullptr)), true_type{});

    template <typename>
    auto test_returnable(...) -> false_type;

    template <typename FromT, typename ToT>
    auto test_implicitly_convertible(int)
            -> decltype(void(std::declval<void (&)(ToT)>()(std::declval<FromT>())), true_type{});

    template <typename, typename>
    auto test_implicitly_convertible(...) -> false_type;

} // namespace detail

template <typename FromT, typename ToT>
struct is_convertible
    : bool_constant<(decltype(detail::test_returnable<ToT>(0))::
                             value&& decltype(detail::test_implicitly_convertible<FromT, ToT>(
                                     0))::value) ||
                    (is_void_v<FromT> && is_void_v<ToT>)>
{};

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE constexpr bool is_convertible_v = is_convertible<FromT, ToT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CONVERTIBLE_HPP
