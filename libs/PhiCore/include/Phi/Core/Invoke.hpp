#ifndef INCG_PHI_CORE_INVOKE_HPP
#define INCG_PHI_CORE_INVOKE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/Core/Forward.hpp"
#include "Phi/TypeTraits/invoke_result.hpp"
#include "Phi/TypeTraits/is_invocable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// invoke_impl resides in Phi/TypeTraits/invokecable.hpp

template <typename FunctionT, typename... ArgsT>
constexpr invoke_result_t<FunctionT, ArgsT...> invoke(
        FunctionT&& function,
        ArgsT&&... args) noexcept(is_nothrow_invocable<FunctionT, ArgsT...>::value)
{
    return detail::invoke_impl(phi::forward<FunctionT>(function), phi::forward<ArgsT>(args)...);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_INVOKE_HPP
