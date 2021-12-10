#ifndef INCG_PHI_CORE_ITERATOR_END_HPP
#define INCG_PHI_CORE_ITERATOR_END_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/size_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ContainerT>
PHI_NODISCARD constexpr auto end(ContainerT& container) noexcept(noexcept(container.end()))
        -> decltype(container.end())
{
    return container.end();
}

template <typename ContainerT>
PHI_NODISCARD constexpr auto end(const ContainerT& container) noexcept(noexcept(container.end()))
        -> decltype(container.end())
{
    return container.end();
}

template <typename TypeT, size_t Size>
PHI_NODISCARD constexpr TypeT* end(TypeT (&array)[Size]) noexcept
{
    return array + Size;
}

template <typename C>
PHI_NODISCARD constexpr auto cend(const C& c) noexcept(noexcept(end(c))) -> decltype(end(c))
{
    return end(c);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_END_HPP
