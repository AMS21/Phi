#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_INVOCABLE_R_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_INVOCABLE_R_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/detail/invoke_impl.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ReturnT, typename FunctionT, typename... ArgsT>
struct is_invocable_r
    : public bool_constant<detail::invokable_r_impl<ReturnT, FunctionT, ArgsT...>::value>
{};

template <typename ReturnT, typename FunctionT, typename... ArgsT>
struct is_not_invocable_r
    : public bool_constant<!is_invocable_r<ReturnT, FunctionT, ArgsT...>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename ReturnT, typename FunctionT, typename... ArgsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_invocable_r_v =
        is_invocable_r<ReturnT, FunctionT, ArgsT...>::value;

template <typename ReturnT, typename FunctionT, typename... ArgsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_invocable_r_v =
        is_not_invocable_r<ReturnT, FunctionT, ArgsT...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_INVOCABLE_R_HPP
