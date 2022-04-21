#ifndef INCG_PHI_CORE_CONTAINER_DYNAMIC_ARRAY_HPP
#define INCG_PHI_CORE_CONTAINER_DYNAMIC_ARRAY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/exchange.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/types.hpp"
#include "phi/iterator/reverse_iterator.hpp"
#include <new>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class dynamic_array
{
public:
    using this_type              = dynamic_array<TypeT>;
    using value_type             = TypeT;
    using size_type              = usize;
    using difference_type        = ptrdiff;
    using reference              = TypeT&;
    using const_reference        = const TypeT&;
    using pointer                = TypeT*;
    using const_pointer          = const TypeT*;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = phi::reverse_iterator<pointer>;
    using const_reverse_iterator = phi::reverse_iterator<const_pointer>;

    explicit dynamic_array(size_type size) noexcept
        : m_Size{size}
        , m_Elements{new (std::nothrow) TypeT[size.unsafe()]}
    {
        PHI_DBG_ASSERT(size > 0u, "Allocating zero elements");
        PHI_DBG_ASSERT(m_Elements != nullptr, "Failed to allocate");
    }

    PHI_EXTENDED_CONSTEXPR dynamic_array(const dynamic_array& other) noexcept
        : m_Elements{new (std::nothrow) TypeT[other.m_Size]}
        , m_Size{other.m_Size}
    {
        // Copy elements
        for (usize i{0u}; i < other.m_Size; ++i)
        {
            m_Elements[i.unsafe()] = other.at(i);
        }
    }

    PHI_EXTENDED_CONSTEXPR dynamic_array(dynamic_array&& other) noexcept
        : m_Elements(exchange(other.m_Elements, nullptr))
        , m_Size(other.m_Size)
    {
        PHI_DBG_ASSERT(m_Elements != nullptr, "Assigned nullptr");
        PHI_DBG_ASSERT(m_Size > 0u, "Created zero sized array");
    }

    PHI_CONSTEXPR_DESTRUCTOR ~dynamic_array() noexcept
    {
        delete[] m_Elements;
    }

    PHI_EXTENDED_CONSTEXPR dynamic_array& operator=(const dynamic_array& other) noexcept
    {
        // Handle self assignment
        if (&other == this)
        {
            return *this;
        }

        m_Elements = new (std::nothrow) TypeT[other.m_Size];
        m_Size     = other.m_Size;

        PHI_DBG_ASSERT(m_Elements != nullptr, "Failed to allocate elements");
        PHI_DBG_ASSERT(m_Size > 0u, "Zero sized array");

        // Copy elements
        for (usize i{0u}; i < other.m_Size; ++i)
        {
            m_Elements[i.unsafe()] = other.at(i);
        }

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR dynamic_array& operator=(dynamic_array&& other) noexcept
    {
        m_Elements = exchange(other.m_Elements, nullptr);
        m_Size     = other.m_Size;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference at(size_type pos) noexcept
    {
        PHI_DBG_ASSERT(pos < m_Size, "Index out of range");
        PHI_DBG_ASSERT(m_Elements != nullptr, "Accessing nullptr");

        return m_Elements[pos.unsafe()];
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference at(size_type pos) const noexcept
    {
        PHI_DBG_ASSERT(pos < m_Size, "Index out of range");
        PHI_DBG_ASSERT(m_Elements != nullptr, "Accessing nullptr");

        return m_Elements[pos.unsafe()];
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference operator[](size_type pos) noexcept
    {
        return at(pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference operator[](size_type pos) const noexcept
    {
        return at(pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference front() noexcept
    {
        return at(0u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference front() const noexcept
    {
        return at(0u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference back() noexcept
    {
        return at(m_Size - 1u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference back() const noexcept
    {
        return at(m_Size - 1u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR pointer data() noexcept
    {
        PHI_DBG_ASSERT(m_Elements != nullptr, "Accessing nullptr");

        return m_Elements;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_pointer data() const noexcept
    {
        PHI_DBG_ASSERT(m_Elements != nullptr, "Accessing nullptr");

        return m_Elements;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator begin() noexcept
    {
        return iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator begin() const noexcept
    {
        return const_iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator cbegin() const noexcept
    {
        return const_iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator end() noexcept
    {
        return iterator(data() + m_Size);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator end() const noexcept
    {
        return const_iterator(data() + m_Size);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator cend() const noexcept
    {
        return const_iterator(data() + m_Size);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    PHI_NODISCARD constexpr size_type size() const noexcept
    {
        return m_Size;
    }

    PHI_NODISCARD constexpr size_type max_size() const noexcept
    {
        return size_type::max();
    }

    PHI_EXTENDED_CONSTEXPR void fill(const TypeT& value) noexcept
    {
        fill_n(m_Elements, m_Size, value);
    }

    PHI_EXTENDED_CONSTEXPR void clear() noexcept
    {
        delete[] m_Elements;
        m_Size = 0u;
    }

private:
    pointer   m_Elements;
    size_type m_Size;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CONTAINER_DYNAMIC_ARRAY_HPP
