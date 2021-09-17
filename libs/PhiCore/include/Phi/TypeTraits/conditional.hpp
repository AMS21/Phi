#ifndef INCG_PHI_CORE_TYPE_TRAITS_CONDITIONAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_CONDITIONAL_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <bool Bool, typename TrueT, typename FalseT>
struct conditional
{
    using type = TrueT;
};

template <typename TrueT, typename FalseT>
struct conditional<false, TrueT, FalseT>
{
    using type = FalseT;
};

template <bool Bool, typename TrueT, typename FalseT>
using conditional_t = typename conditional<Bool, TrueT, FalseT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_CONDITIONAL_HPP
