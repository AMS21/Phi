#ifndef INCG_PHI_CORE_ITERATOR_END_HPP
#define INCG_PHI_CORE_ITERATOR_END_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/size_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ContainerT>
PHI_NODISCARD PHI_CONSTEXPR auto end(ContainerT& container)
        PHI_NOEXCEPT_EXPR(noexcept(container.end())) -> decltype(container.end())
{
    return container.end();
}

template <typename ContainerT>
PHI_NODISCARD PHI_CONSTEXPR auto end(const ContainerT& container)
        PHI_NOEXCEPT_EXPR(noexcept(container.end())) -> decltype(container.end())
{
    return container.end();
}

template <typename TypeT, size_t Size>
PHI_NODISCARD PHI_CONSTEXPR TypeT* end(TypeT (&array)[Size]) PHI_NOEXCEPT
{
    return array + Size;
}

template <typename ContainerT>
PHI_NODISCARD PHI_CONSTEXPR auto cend(const ContainerT& container)
        PHI_NOEXCEPT_EXPR(noexcept(end(container))) -> decltype(end(container))
{
    return end(container);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_END_HPP
