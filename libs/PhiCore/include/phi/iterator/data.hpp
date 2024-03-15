#ifndef INCG_PHI_CORE_ITERATOR_DATA_HPP
#define INCG_PHI_CORE_ITERATOR_DATA_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/size_t.hpp"
#include "phi/forward/std/initializer_list.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ContainerT>
PHI_NODISCARD constexpr auto data(ContainerT& container) noexcept(noexcept(container.data()))
        -> decltype(container.data())
{
    return container.data();
}

template <typename ContainerT>
PHI_NODISCARD constexpr auto data(const ContainerT& container) noexcept(noexcept(container.data()))
        -> decltype(container.data())
{
    return container.data();
}

template <typename TypeT, size_t Size>
PHI_NODISCARD constexpr TypeT* data(TypeT (&array)[Size]) noexcept
{
    return array;
}

template <typename TypeT>
PHI_NODISCARD constexpr const TypeT* data(std::initializer_list<TypeT> init_list) noexcept
{
    return init_list.begin();
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_DATA_HPP
