#ifndef INCG_PHI_CORE_ITERATOR_ADVANCE_HPP
#define INCG_PHI_CORE_ITERATOR_ADVANCE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/iterator/iterator_tags.hpp"
#include "phi/iterator/iterator_traits.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename InputIteratorT>
    inline PHI_EXTENDED_CONSTEXPR void advance_impl(
            InputIteratorT& iterator, typename iterator_traits<InputIteratorT>::difference_type n,
            input_iterator_tag /*tag*/)
    {
        for (; n > 0; --n)
        {
            ++iterator;
        }
    }

    template <typename BiDirectionalIteratorT>
    inline PHI_EXTENDED_CONSTEXPR void advance_impl(
            BiDirectionalIteratorT&                                           iterator,
            typename iterator_traits<BiDirectionalIteratorT>::difference_type n,
            bidirectional_iterator_tag /*tag*/)
    {
        if (n >= 0)
        {
            for (; n > 0; --n)
            {
                ++iterator;
            }
        }
        else
        {
            for (; n < 0; ++n)
            {
                --iterator;
            }
        }
    }

    template <typename RandomAccessIteratorT>
    inline PHI_EXTENDED_CONSTEXPR void advance_impl(
            RandomAccessIteratorT&                                           iterator,
            typename iterator_traits<RandomAccessIteratorT>::difference_type n,
            random_access_iterator_tag /*tag*/)
    {
        iterator += n;
    }
} // namespace detail
/// \endcond

template <typename InputIteratorT>
inline PHI_EXTENDED_CONSTEXPR void advance(
        InputIteratorT& iterator, typename iterator_traits<InputIteratorT>::difference_type n)
{
    detail::advance_impl(iterator, n,
                         typename iterator_traits<InputIteratorT>::iterator_category());
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_ADVANCE_HPP
