#ifndef INCG_PHI_CORE_ITERATOR_REVERSE_ITERATOR_HPP
#define INCG_PHI_CORE_ITERATOR_REVERSE_ITERATOR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/core/boolean.hpp"
#include "phi/iterator/iterator_traits.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename IteratorT>
class PHI_ATTRIBUTE_POINTER reverse_iterator
{
public:
    using value_type        = typename iterator_traits<IteratorT>::value_type;
    using difference_type   = typename iterator_traits<IteratorT>::difference_type;
    using pointer           = typename iterator_traits<IteratorT>::pointer;
    using reference         = typename iterator_traits<IteratorT>::reference;
    using iterator_category = typename iterator_traits<IteratorT>::iterator_category;
    using iterator_type     = IteratorT;

    constexpr reverse_iterator() noexcept
        : m_Current()
    {}

    constexpr explicit reverse_iterator(IteratorT value)
        : m_Current(value)
    {}

    template <typename TypeT>
    constexpr reverse_iterator(const reverse_iterator<TypeT>& other)
        : m_Current(other.base())
    {}

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR reverse_iterator& operator=(const reverse_iterator<TypeT>& other)
    {
        m_Current = other.base();
        return *this;
    }

    PHI_NODISCARD constexpr IteratorT base() const
    {
        return m_Current;
    }

    PHI_EXTENDED_CONSTEXPR
    reference operator*() const
    {
        IteratorT tmp = m_Current;
        return *--tmp;
    }

    PHI_EXTENDED_CONSTEXPR
    pointer operator->() const
    {
        return address_of(operator*());
    }

    PHI_EXTENDED_CONSTEXPR reference operator[](difference_type n) const
    {
        return *(*this + n);
    }

    // Extended constexpr is required here, because before C++-14 constexpr
    // implies const which will lead to an compile error here
    PHI_EXTENDED_CONSTEXPR
    reverse_iterator& operator++()
    {
        --m_Current;
        return *this;
    }

    // Extended constexpr is required here, because before C++-14 constexpr
    // implies const which will lead to an compile error here
    PHI_EXTENDED_CONSTEXPR
    reverse_iterator& operator--()
    {
        ++m_Current;
        return *this;
    }

    PHI_EXTENDED_CONSTEXPR
    // NOLINTNEXTLINE(cert-dcl21-cpp)
    reverse_iterator operator++(int)
    {
        reverse_iterator tmp(*this);
        --m_Current;
        return tmp;
    }

    PHI_EXTENDED_CONSTEXPR
    // NOLINTNEXTLINE(cert-dcl21-cpp)
    reverse_iterator operator--(int)
    {
        reverse_iterator tmp(*this);
        ++m_Current;
        return tmp;
    }

    PHI_EXTENDED_CONSTEXPR
    reverse_iterator operator+(difference_type n) const
    {
        return reverse_iterator(m_Current - n);
    }

    PHI_EXTENDED_CONSTEXPR
    reverse_iterator operator-(difference_type n) const
    {
        return reverse_iterator(m_Current + n);
    }

    PHI_EXTENDED_CONSTEXPR
    reverse_iterator& operator+=(difference_type n)
    {
        m_Current -= n;
        return *this;
    }

    PHI_EXTENDED_CONSTEXPR
    reverse_iterator& operator-=(difference_type n)
    {
        m_Current += n;
        return *this;
    }

protected:
    IteratorT m_Current;
};

template <typename IteratorT>
constexpr reverse_iterator<IteratorT> make_reverse_iterator(IteratorT iterator)
{
    return reverse_iterator<IteratorT>(iterator);
}

template <typename LhsIteratorT, typename RhsIteratorT>
constexpr boolean operator==(const reverse_iterator<LhsIteratorT>& lhs,
                             const reverse_iterator<RhsIteratorT>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename LhsIteratorT, typename RhsIteratorT>
constexpr boolean operator!=(const reverse_iterator<LhsIteratorT>& lhs,
                             const reverse_iterator<RhsIteratorT>& rhs)
{
    return lhs.base() != rhs.base();
}

template <typename LhsIteratorT, typename RhsIteratorT>
constexpr boolean operator<(const reverse_iterator<LhsIteratorT>& lhs,
                            const reverse_iterator<RhsIteratorT>& rhs)
{
    return lhs.base() > rhs.base();
}

template <typename LhsIteratorT, typename RhsIteratorT>
constexpr boolean operator<=(const reverse_iterator<LhsIteratorT>& lhs,
                             const reverse_iterator<RhsIteratorT>& rhs)
{
    return lhs.base() >= rhs.base();
}

template <typename LhsIteratorT, typename RhsIteratorT>
constexpr boolean operator>(const reverse_iterator<LhsIteratorT>& lhs,
                            const reverse_iterator<RhsIteratorT>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename LhsIteratorT, typename RhsIteratorT>
constexpr boolean operator>=(const reverse_iterator<LhsIteratorT>& lhs,
                             const reverse_iterator<RhsIteratorT>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <typename IteratorT>
constexpr reverse_iterator<IteratorT> operator+(
        typename reverse_iterator<IteratorT>::difference_type n,
        const reverse_iterator<IteratorT>&                    iterator)
{
    return reverse_iterator<IteratorT>(iterator.base() - n);
}

template <typename LhsIteratorT, typename RhsIteratorT>
constexpr auto operator-(const reverse_iterator<LhsIteratorT>& lhs,
                         const reverse_iterator<RhsIteratorT>& rhs) -> decltype(rhs.base() -
                                                                                lhs.base())
{
    return rhs.base() - lhs.base();
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_REVERSE_ITERATOR_HPP
