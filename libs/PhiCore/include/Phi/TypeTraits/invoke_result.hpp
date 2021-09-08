#ifndef INCG_PHI_CORE_TYPE_TRAITS_INVOKE_RESULT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_INVOKE_RESULT_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/Core/Invoke.hpp"
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename FnT, typename, typename... ArgsT>
    struct invoke_result_impl;

    template <typename FnT, typename... ArgsT>
    struct invoke_result_impl<
            FnT, decltype(invoke(std::declval<FnT>(), std::declval<ArgsT>()...), void()), ArgsT...>
    {
        using type = decltype(invoke(std::declval<FnT>(), std::declval<ArgsT>()...));
    };
} // namespace detail

template <typename FnT, typename... ArgsT>
using invoke_result = detail::invoke_result_impl<FnT, void, ArgsT...>;

template <typename FnT, typename... ArgsT>
using invoke_result_t = typename invoke_result<FnT, ArgsT...>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_INVOKE_RESULT_HPP
