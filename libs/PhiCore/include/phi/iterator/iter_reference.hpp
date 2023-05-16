#ifndef INCG_PHI_ITERATOR_ITER_REFERENCE_HPP
#define INCG_PHI_ITERATOR_ITER_REFERENCE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/core/declval.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_referenceable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, enable_if_t<is_referenceable<TypeT>::value, int*> = nullptr>
using iter_reference_t = decltype(*declval<TypeT&>());

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_ITERATOR_ITER_REFERENCE_HPP
