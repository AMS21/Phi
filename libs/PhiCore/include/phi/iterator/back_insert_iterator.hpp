#ifndef INCG_PHI_CORE_ITERATOR_BACK_INSERT_ITERATOR_HPP
#define INCG_PHI_CORE_ITERATOR_BACK_INSERT_ITERATOR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/core/address_of.hpp"
#include "phi/iterator/iterator_tags.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ContainerT>
class back_insert_iterator
{
public:
    using this_type         = back_insert_iterator<ContainerT>;
    using container_type    = ContainerT;
    using value_type        = void;
    using difference_type   = void;
    using pointer           = void;
    using reference         = void;
    using iterator_category = output_iterator_tag;

    constexpr explicit back_insert_iterator(ContainerT& container) noexcept
        : m_Container(address_of(container))
    {}

    constexpr back_insert_iterator<ContainerT>& operator=(
            const typename ContainerT::value_type& value) noexcept
    {
        m_Container->push_back(value);
        return *this;
    }

    constexpr back_insert_iterator<ContainerT>& operator=(
            typename ContainerT::value_type&& value) noexcept
    {
        m_Container->push_back(move(value));
        return *this;
    }

    constexpr back_insert_iterator& operator*() noexcept
    {
        return *this;
    }

    constexpr back_insert_iterator& operator++() noexcept
    {
        return *this;
    }

    // NOLINTNEXTLINE(cert-dcl21-cpp)
    constexpr back_insert_iterator operator++(int) noexcept
    {
        return *this;
    }

protected:
    ContainerT* m_Container;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_BACK_INSERT_ITERATOR_HPP
