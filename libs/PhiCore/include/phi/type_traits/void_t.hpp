#ifndef INCG_PHI_CORE_TYPE_TRAITS_VOID_T_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_VOID_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename... TypesT>
    struct make_void
    {
        using type = void;
    };
} // namespace detail

template <typename... TypesT>
using void_t = typename detail::make_void<TypesT...>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_VOID_T_HPP
