#ifndef INCG_PHI_CORE_ITERATOR_IS_EMPTY_HPP
#define INCG_PHI_CORE_ITERATOR_IS_EMPTY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/size_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ContainerT>
PHI_NODISCARD constexpr auto empty(const ContainerT& container) -> decltype(container.empty())
{
    return container.empty();
}

template <typename TypeT, size_t Size>
PHI_NODISCARD constexpr bool empty(const TypeT (&array)[Size]) noexcept
{
    (void)array;
    return false;
}

/*
template <typename TypeT>
PHI_NODISCARD constexpr bool empty(initializer_list<TypeT> il) noexcept
{
    return il.size() == 0;
}
*/

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_IS_EMPTY_HPP
