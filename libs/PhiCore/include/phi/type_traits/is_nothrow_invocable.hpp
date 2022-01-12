#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/detail/invoke_impl.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FunctionT, typename... ArgsT>
struct is_nothrow_invocable
    : public bool_constant<detail::nothrow_invokable<FunctionT, ArgsT...>::value>
{};

template <typename FunctionT, typename... ArgsT>
struct is_not_nothrow_invocable
    : public bool_constant<!is_nothrow_invocable<FunctionT, ArgsT...>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename FunctionT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_invocable_v =
        is_nothrow_invocable<FunctionT, ArgsT...>::value;

template <typename FunctionT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_not_nothrow_invocable_v =
        is_not_nothrow_invocable<FunctionT, ArgsT...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP
