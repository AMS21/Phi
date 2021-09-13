#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Declval.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_convertible.hpp"
#include "Phi/TypeTraits/is_void.hpp"

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
    struct is_nothrow_convertible_impl : decltype(is_nothrow_convertible_test<FromT, ToT>())
    {};
} // namespace detail

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename FromT, typename ToT>
struct is_nothrow_convertible
    : public bool_constant<(is_void_v<FromT> && is_void_v<ToT>) ||
                           (is_convertible_v<FromT, ToT> &&
                            detail::is_nothrow_convertible_impl<FromT, ToT>::value)>
{};

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_convertible_v =
        is_nothrow_convertible<FromT, ToT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP
