#ifndef INCG_PHI_CORE_INVOKE_HPP
#define INCG_PHI_CORE_INVOKE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/core/forward.hpp"
#include "phi/type_traits/detail/invoke_impl.hpp"
#include "phi/type_traits/invoke_result.hpp"
#include "phi/type_traits/is_nothrow_invocable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FunctionT, typename... ArgsT>
PHI_CONSTEXPR invoke_result_t<FunctionT, ArgsT...> invoke(
        FunctionT&& function,
        ArgsT&&... args) noexcept(is_nothrow_invocable<FunctionT, ArgsT...>::value)
{
    return detail::invoke_impl(phi::forward<FunctionT>(function), phi::forward<ArgsT>(args)...);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_INVOKE_HPP
