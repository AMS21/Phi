#ifndef INCG_PHI_CORE_ITERATOR_RBEGIN_HPP
#define INCG_PHI_CORE_ITERATOR_RBEGIN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/iterator/reverse_iterator.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ContainerT>
PHI_CONSTEXPR auto rbegin(ContainerT& container) -> decltype(container.rbegin())
{
    return container.rbegin();
}

template <typename ContainerT>
PHI_CONSTEXPR auto rbegin(const ContainerT& container) -> decltype(container.rbegin())
{
    return container.rbegin();
}

template <typename TypeT, size_t Size>
PHI_CONSTEXPR reverse_iterator<TypeT*> rbegin(TypeT (&array)[Size])
{
    return reverse_iterator<TypeT*>(array + Size);
}

// TODO: Support for initializer lists

template <typename ContainerT>
PHI_CONSTEXPR auto crbegin(const ContainerT& container) -> decltype(rbegin(container))
{
    return rbegin(container);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_RBEGIN_HPP
