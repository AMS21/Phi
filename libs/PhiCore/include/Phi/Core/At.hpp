#ifndef INCG_PHI_UTILITY_AT_HPP
#define INCG_PHI_UTILITY_AT_HPP

#include "Phi/Core/Assert.hpp"
#include "Phi/PhiConfig.hpp"
#include <cstdint>
#include <initializer_list>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, std::size_t Size>
[[nodiscard]] constexpr TypeT& at(TypeT (&arr)[Size], std::size_t index) noexcept
{
    PHI_DBG_ASSERT(index < Size, "Index {} is out of bounds! Max value: {}", index, Size - 1);

    return arr[index];
}

template <typename ContainerT>
[[nodiscard]] constexpr auto at(ContainerT& container, std::size_t index)
#if !defined(PHI_DEBUG)
        noexcept
#endif
        -> decltype(container[container.size()])
{
    PHI_DBG_ASSERT(index < container.size(), "Index {} is out of bounds! Max value: {}", index,
                   container.size() - 1);

#if defined(PHI_DEBUG)
    return container.at(index);
#else
    return container[index];
#endif
}

template <typename TypeT>
[[nodiscard]] constexpr TypeT at(std::initializer_list<TypeT> list, std::size_t index) noexcept
{
    PHI_DBG_ASSERT(index < list.size(), "Index {} is out of bounds! Max value: {}", index,
                   list.size() - 1);

    return *(list.begin() + index);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_UTILITY_AT_HPP
