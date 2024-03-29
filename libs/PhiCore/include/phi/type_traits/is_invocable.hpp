#ifndef INCG_PHI_CORE_TYPE_TRAITS_INVOCABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_INVOCABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/detail/invoke_impl.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FunctionT, typename... ArgsT>
struct is_invocable
    : public integral_constant<bool, detail::invokable_impl<FunctionT, ArgsT...>::value>
{};

template <typename FunctionT, typename... ArgsT>
struct is_not_invocable : public integral_constant<bool, !is_invocable<FunctionT, ArgsT...>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename FunctionT, typename... ArgsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_invocable_v = is_invocable<FunctionT, ArgsT...>::value;

template <typename FunctionT, typename... ArgsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_invocable_v =
        is_not_invocable<FunctionT, ArgsT...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_INVOCABLE_HPP
