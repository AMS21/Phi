#ifndef INCG_PHI_UTILITY_AT_HPP
#define INCG_PHI_UTILITY_AT_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/SizeT.hpp"
#include <initializer_list>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, size_t Size>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT& at(TypeT (&arr)[Size], size_t index) noexcept
{
    PHI_DBG_ASSERT(index < Size, "Index {} is out of bounds! Max value: {}", index, Size - 1);

    return arr[index];
}

template <typename ContainerT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR auto at(ContainerT& container, size_t index)
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
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT at(std::initializer_list<TypeT> list,
                                              std::size_t                  index) noexcept
{
    PHI_DBG_ASSERT(index < list.size(), "Index {} is out of bounds! Max value: {}", index,
                   list.size() - 1);

    return *(list.begin() + index);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_UTILITY_AT_HPP
