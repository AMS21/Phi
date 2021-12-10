#ifndef INCG_PHI_CORE_ITERATOR_BEGIN_HPP
#define INCG_PHI_CORE_ITERATOR_BEGIN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/core/size_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ContainerT>
constexpr inline auto begin(ContainerT& container) noexcept(noexcept(container.begin()))
        -> decltype(container.begin())
{
    return container.begin();
}

template <typename ContainerT>
constexpr inline auto begin(const ContainerT& container) noexcept(noexcept(container.begin()))
        -> decltype(container.begin())
{
    return container.begin();
}

template <typename TypeT, size_t Size>
constexpr inline TypeT* begin(TypeT (&array)[Size]) noexcept
{
    return array;
}

template <typename ContainerT>
constexpr inline auto cbegin(const ContainerT& container) noexcept(noexcept(begin(container)))
        -> decltype(begin(container))
{
    return begin(container);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_BEGIN_HPP
