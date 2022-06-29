#ifndef INCG_PHI_CORE_ITERATOR_DISTANCE_HPP
#define INCG_PHI_CORE_ITERATOR_DISTANCE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/iterator/iterator_tags.hpp"
#include "phi/iterator/iterator_traits.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename InputIteratorT>
    PHI_EXTENDED_CONSTEXPR typename iterator_traits<InputIteratorT>::difference_type distance_impl(
            InputIteratorT first, InputIteratorT last,
            input_iterator_tag /*tag*/) noexcept(noexcept(first != last, ++first))
    {
        typename iterator_traits<InputIteratorT>::difference_type ret(0);
        for (; first != last; ++first)
        {
            ++ret;
        }

        return ret;
    }

    template <typename RandomAccessIteratorT>
    constexpr typename iterator_traits<RandomAccessIteratorT>::difference_type distance_impl(
            RandomAccessIteratorT first, RandomAccessIteratorT last,
            random_access_iterator_tag /*tag*/) noexcept(noexcept(last - first))
    {
        return last - first;
    }
} // namespace detail
/// \endcond

template <typename InputIteratorT>
inline constexpr typename iterator_traits<InputIteratorT>::difference_type distance(
        InputIteratorT first, InputIteratorT last)
{
    return detail::distance_impl(first, last,
                                 typename iterator_traits<InputIteratorT>::iterator_category());
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_DISTANCE_HPP
