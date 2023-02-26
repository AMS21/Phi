#ifndef INCG_PHI_CORE_ALGORITHM_FIND_IF_HPP
#define INCG_PHI_CORE_ALGORITHM_FIND_IF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/warning.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wsuggest-attribute=const")
PHI_GCC_SUPPRESS_WARNING("-Wsuggest-attribute=pure")

template <typename InputIteratorT, typename UnaryPredicateT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR InputIteratorT
find_if(InputIteratorT first, InputIteratorT last, UnaryPredicateT predicate) noexcept(
        noexcept(first != last) && noexcept(++first) && noexcept(predicate(*first)))
{
    for (; first != last; ++first)
    {
        if (predicate(*first))
        {
            return first;
        }
    }

    return last;
}

PHI_GCC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_FIND_IF_HPP
