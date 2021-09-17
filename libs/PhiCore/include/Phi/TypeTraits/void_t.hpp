#ifndef INCG_PHI_CORE_TYPE_TRAITS_VOID_T_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_VOID_T_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename... Ts>
    struct make_void
    {
        using type = void;
    };
} // namespace detail

template <typename... Ts>
using void_t = typename detail::make_void<Ts...>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_VOID_T_HPP
