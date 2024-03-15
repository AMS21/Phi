#ifndef INCG_PHI_CORE_ITERATOR_REND_HPP
#define INCG_PHI_CORE_ITERATOR_REND_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/iterator/reverse_iterator.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ContainerT>
PHI_CONSTEXPR auto rend(ContainerT& container) -> decltype(container.rend())
{
    return container.rend();
}

template <typename ContainerT>
PHI_CONSTEXPR auto rend(const ContainerT& container) -> decltype(container.rend())
{
    return container.rend();
}

template <typename TypeT, size_t Size>
PHI_CONSTEXPR reverse_iterator<TypeT*> rend(TypeT (&array)[Size])
{
    return reverse_iterator<TypeT*>(array + Size);
}

// TODO: Support for initializer lists

template <typename ContainerT>
PHI_CONSTEXPR auto crend(const ContainerT& container) -> decltype(rend(container))
{
    return rend(container);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_REND_HPP
