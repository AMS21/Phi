#ifndef INCG_PHI_CORE_TYPE_TRAITS_INVOKE_RESULT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_INVOKE_RESULT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/type_traits/detail/invoke_impl.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FunctionT, typename... ArgsT>
struct invoke_result : public detail::invoke_of<FunctionT, ArgsT...>
{};

template <typename FunctionT, typename... ArgsT>
using invoke_result_t = typename invoke_result<FunctionT, ArgsT...>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_INVOKE_RESULT_HPP
