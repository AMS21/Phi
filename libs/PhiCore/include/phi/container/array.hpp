#ifndef INCG_PHI_CORE_CONTAINER_ARRAY_HPP
#define INCG_PHI_CORE_CONTAINER_ARRAY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap_ranges.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/unreachable.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/size_t.hpp"
#include "phi/core/types.hpp"
#include "phi/iterator/reverse_iterator.hpp"
#include "phi/type_traits/is_const.hpp"
#include "phi/type_traits/is_nothrow_swappable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, size_t Size>
class array
{
public:
    using this_type              = array<TypeT, Size>;
    using value_type             = TypeT;
    using size_type              = usize;
    using difference_type        = ptrdiff;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = phi::reverse_iterator<iterator>;
    using const_reverse_iterator = phi::reverse_iterator<const_iterator>;

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference at(size_type pos) noexcept
    {
        PHI_DBG_ASSERT(pos < Size, "Index out of range");

        return m_Elements[pos.unsafe()];
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference at(size_type pos) const noexcept
    {
        PHI_DBG_ASSERT(pos < Size, "Index out of range");

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
        return at(Size - 1u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference back() const noexcept
    {
        return at(Size - 1u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR pointer data() noexcept
    {
        return m_Elements;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_pointer data() const noexcept
    {
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
        return iterator(data() + Size);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator end() const noexcept
    {
        return const_iterator(data() + Size);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator cend() const noexcept
    {
        return const_iterator(data() + Size);
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

    PHI_NODISCARD constexpr bool is_empty() const noexcept
    {
        return begin() == end();
    }

    PHI_NODISCARD constexpr size_type size() const noexcept
    {
        return Size;
    }

    PHI_NODISCARD constexpr size_type max_size() const noexcept
    {
        return Size;
    }

    PHI_EXTENDED_CONSTEXPR void fill(const TypeT& value) noexcept
    {
        for (size_type index{0u}; index < Size; ++index)
        {
            m_Elements[index.unsafe()] = value;
        }
    }

    PHI_EXTENDED_CONSTEXPR void swap(array& other) noexcept(is_nothrow_swappable<TypeT>::value)
    {
        swap_ranges(m_Elements, m_Elements + Size, other.m_Elements);
    }

    PHI_EXTENDED_CONSTEXPR TypeT max() const noexcept
    {
        TypeT max_value = at(0);
        for (size_type index{1u}; index < Size; ++index)
        {
            max_value = (max_value > at(index)) ? max_value : at(index);
        }

        return max_value;
    }

    template <typename UnaryFunctionT>
    PHI_EXTENDED_CONSTEXPR TypeT max_if(UnaryFunctionT function, TypeT default_value = {})
    {
        TypeT max_value = default_value;
        for (size_type index{0u}; index < Size; ++index)
        {
            TypeT test_value = at(index);

            if (function(test_value) && max_value < test_value)
            {
                max_value = test_value;
            }
        }

        return max_value;
    }

    PHI_EXTENDED_CONSTEXPR iterator max_index() noexcept
    {
        iterator max_index = begin();
        for (iterator index = ++begin(); index < Size; ++index)
        {
            max_index = (*max_index > *index) ? max_index : index;
        }

        return max_index;
    }

    PHI_EXTENDED_CONSTEXPR const_iterator max_index() const noexcept
    {
        const_iterator max_index = begin();
        for (const_iterator index = ++begin(); index < Size; ++index)
        {
            max_index = (*max_index > *index) ? max_index : index;
        }

        return max_index;
    }

    PHI_EXTENDED_CONSTEXPR TypeT min() const noexcept
    {
        TypeT min_value = at(0u);
        for (size_type index{1u}; index < Size; ++index)
        {
            min_value = (min_value < at(index)) ? min_value : at(index);
        }

        return min_value;
    }

    template <typename UnaryFunctionT>
    PHI_EXTENDED_CONSTEXPR TypeT min_if(UnaryFunctionT function,
                                        TypeT          default_value = {}) const noexcept
    {
        TypeT min_value = default_value;
        for (size_type index{0u}; index < Size; ++index)
        {
            TypeT test_value = at(index);
            if (function(test_value) && min_value > test_value)
            {
                min_value = test_value;
            }
        }

        return min_value;
    }

    PHI_EXTENDED_CONSTEXPR iterator min_index() noexcept
    {
        iterator min_index = begin();
        for (iterator index = ++begin(); index < Size; ++index)
        {
            min_index = (*min_index < *index) ? min_index : index;
        }

        return min_index;
    }

    PHI_EXTENDED_CONSTEXPR const_iterator min_index() const noexcept
    {
        const_iterator min_index = begin();
        for (const_iterator index = ++begin(); index < Size; ++index)
        {
            min_index = (*min_index < *index) ? min_index : index;
        }

        return min_index;
    }

    TypeT m_Elements[Size];
};

template <typename TypeT>
class array<TypeT, 0>
{
public:
    using this_type              = array<TypeT, 0>;
    using value_type             = TypeT;
    using size_type              = usize;
    using difference_type        = ptrdiff;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = phi::reverse_iterator<iterator>;
    using const_reverse_iterator = phi::reverse_iterator<const_iterator>;

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference at(size_type /*pos*/) noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::at() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference at(size_type /*pos*/) const noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::at() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference operator[](size_type /*pos*/) noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::operator[] on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference
    operator[](size_type /*pos*/) const noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::operator[] on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference front() noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::front() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference front() const noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::front() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference back() noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::back() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference back() const noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::back() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR pointer data() noexcept
    {
        return nullptr;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_pointer data() const noexcept
    {
        return nullptr;
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
        return iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator end() const noexcept
    {
        return const_iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator cend() const noexcept
    {
        return const_iterator(data());
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

    PHI_NODISCARD constexpr bool is_empty() const noexcept
    {
        return true;
    }

    PHI_NODISCARD constexpr size_type size() const noexcept
    {
        return 0u;
    }

    PHI_NODISCARD constexpr size_type max_size() const noexcept
    {
        return 0u;
    }

    PHI_EXTENDED_CONSTEXPR void fill(const TypeT& /*value*/) noexcept
    {
        static_assert(!is_const<TypeT>::value, "Cannot fill zero-sized array of type 'const T'");
    }

    PHI_EXTENDED_CONSTEXPR void swap(array& /*other*/) noexcept
    {
        static_assert(!is_const<TypeT>::value, "Cannot swap zero-sized array of type 'const T'");
    }

    PHI_EXTENDED_CONSTEXPR TypeT max() const noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::max() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_EXTENDED_CONSTEXPR TypeT min() const noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::min() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_EXTENDED_CONSTEXPR iterator max_index() noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::max_index() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_EXTENDED_CONSTEXPR const_iterator max_index() const noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::max_index() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_EXTENDED_CONSTEXPR iterator min_index() noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::min_index() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_EXTENDED_CONSTEXPR const_iterator min_index() const noexcept
    {
        PHI_DBG_ASSERT(false, "Cannot call array<T, 0>::min_index() on zero sized array");
        PHI_UNREACHABLE();
    }
};

template <typename TypeT, size_t Size>
constexpr boolean operator==(const array<TypeT, Size>& lhs, const array<TypeT, Size>& rhs)
{
    return equal(lhs.begin(), rhs.end(), lhs.begin());
}

template <typename TypeT, size_t Size>
constexpr boolean operator!=(const array<TypeT, Size>& lhs, const array<TypeT, Size>& rhs)
{
    return !(lhs == rhs);
}

template <typename TypeT, size_t Size>
constexpr boolean operator<(const array<TypeT, Size>& lhs, const array<TypeT, Size>& rhs)
{
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename TypeT, size_t Size>
constexpr boolean operator<=(const array<TypeT, Size>& lhs, const array<TypeT, Size>& rhs)
{
    return !(rhs < lhs);
}

template <typename TypeT, size_t Size>
constexpr boolean operator>(const array<TypeT, Size>& lhs, const array<TypeT, Size>& rhs)
{
    return rhs < lhs;
}

template <typename TypeT, size_t Size>
constexpr boolean operator>=(const array<TypeT, Size>& lhs, const array<TypeT, Size>& rhs)
{
    return !(lhs < rhs);
}

template <typename TypeT, size_t Size>
PHI_EXTENDED_CONSTEXPR_OR_INLINE void swap(
        array<TypeT, Size>& lhs,
        array<TypeT, Size>& rhs) noexcept(is_nothrow_swappable<TypeT>::value)
{
    lhs.swap(rhs);
}

#if PHI_HAS_FEATURE_DEDUCTION_GUIDES()
template <typename TypeT, typename... ArgsT>
array(TypeT, ArgsT...) -> array<TypeT, 1 + sizeof...(ArgsT)>;
#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CONTAINER_ARRAY_HPP
