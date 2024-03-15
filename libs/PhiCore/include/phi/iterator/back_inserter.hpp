#ifndef INCG_PHI_CORE_ITERATOR_BACK_INSERTER_HPP
#define INCG_PHI_CORE_ITERATOR_BACK_INSERTER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/iterator/back_insert_iterator.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ContainerT>
PHI_CONSTEXPR back_insert_iterator<ContainerT> back_inserter(ContainerT& container)
{
    return back_insert_iterator<ContainerT>(container);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_BACK_INSERTER_HPP
