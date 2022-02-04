#ifndef INCG_PHI_CORE_TYPE_TRAITS_DETAIL_TYPE_LIST_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_DETAIL_TYPE_LIST_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/type_traits/detail/nat.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename HeadT, typename TailT>
    struct type_list
    {
        using Head = HeadT;
        using Tail = TailT;
    };
} // namespace detail

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_DETAIL_TYPE_LIST_HPP
