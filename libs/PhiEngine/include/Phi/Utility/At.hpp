#ifndef INCG_PHI_UTILITY_AT_HPP
#define INCG_PHI_UTILITY_AT_HPP

#include "Phi/PhiConfig.hpp"
#include "Phi/Utility/Assert.hpp"
#include <cstdint>
#include <initializer_list>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename Type, std::size_t Size>
[[nodiscard]] constexpr Type& at(Type (&arr)[Size], std::size_t index) noexcept
{
    PHI_DBG_ASSERT(index < Size, "Index {} is out of bounds! Max value: {}", index, Size - 1);

    return arr[index];
}

template <typename Container>
[[nodiscard]] constexpr auto at(Container& container, std::size_t index)
        -> decltype(container[container.size()])
#if !defined(PHI_DEBUG)
                noexcept
#endif
{
    PHI_DBG_ASSERT(index < container.size(), "Index {} is out of bounds! Max value: {}", index,
                   container.size() - 1);

#if defined(PHI_DEBUG)
    return container.at(index);
#else
    return container[index];
#endif
}

template <typename Type>
[[nodiscard]] constexpr Type at(std::initializer_list<Type> list, std::size_t index) noexcept
{
    PHI_DBG_ASSERT(index < list.size(), "Index {} is out of bounds! Max value: {}", index,
                   list.size() - 1);

    return *(list.begin() + index);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_UTILITY_AT_HPP