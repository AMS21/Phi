#ifndef INCG_PHI_CORE_CONTAINER_ARRAY_HPP
#define INCG_PHI_CORE_CONTAINER_ARRAY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/equal.hpp"
#include "phi/algorithm/lexicographical_compare.hpp"
#include "phi/algorithm/swap_ranges.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/compiler_support/unreachable.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/narrow_cast.hpp"
#include "phi/core/size_t.hpp"
#include "phi/core/types.hpp"
#include "phi/iterator/reverse_iterator.hpp"
#include "phi/type_traits/is_const.hpp"
#include "phi/type_traits/is_nothrow_swappable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// Invalid warning from older gcc versions
#if PHI_COMPILER_IS_BELOW(GCC, 8, 0, 0)
PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wunsafe-loop-optimizations")
#endif

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

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference at(size_type pos) PHI_NOEXCEPT
    {
        PHI_ASSERT(pos < Size, "Index out of range");

        return elements[pos.unsafe()];
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference at(size_type pos) const PHI_NOEXCEPT
    {
        PHI_ASSERT(pos < Size, "Index out of range");

        return elements[pos.unsafe()];
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference operator[](size_type pos) PHI_NOEXCEPT
    {
        return at(pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference
    operator[](size_type pos) const PHI_NOEXCEPT
    {
        return at(pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference front() PHI_NOEXCEPT
    {
        return at(0u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference front() const PHI_NOEXCEPT
    {
        return at(0u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference back() PHI_NOEXCEPT
    {
        return at(Size - 1u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference back() const PHI_NOEXCEPT
    {
        return at(Size - 1u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR pointer data() PHI_NOEXCEPT
    {
        return elements;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_pointer data() const PHI_NOEXCEPT
    {
        return elements;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator begin() PHI_NOEXCEPT
    {
        return iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator begin() const PHI_NOEXCEPT
    {
        return const_iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator cbegin() const PHI_NOEXCEPT
    {
        return const_iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator end() PHI_NOEXCEPT
    {
        return iterator(data() + Size);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator end() const PHI_NOEXCEPT
    {
        return const_iterator(data() + Size);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator cend() const PHI_NOEXCEPT
    {
        return const_iterator(data() + Size);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reverse_iterator rbegin() PHI_NOEXCEPT
    {
        return reverse_iterator(end());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator rbegin() const PHI_NOEXCEPT
    {
        return const_reverse_iterator(end());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator crbegin() const PHI_NOEXCEPT
    {
        return const_reverse_iterator(end());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reverse_iterator rend() PHI_NOEXCEPT
    {
        return reverse_iterator(begin());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator rend() const PHI_NOEXCEPT
    {
        return const_reverse_iterator(begin());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator crend() const PHI_NOEXCEPT
    {
        return const_reverse_iterator(begin());
    }

    PHI_NODISCARD PHI_CONSTEXPR bool is_empty() const PHI_NOEXCEPT
    {
        return begin() == end();
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type size() const PHI_NOEXCEPT
    {
        return Size;
    }

    PHI_NODISCARD PHI_CONSTEXPR isize ssize() const PHI_NOEXCEPT
    {
        return narrow_cast<isize>(Size);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type max_size() const PHI_NOEXCEPT
    {
        return Size;
    }

    PHI_NODISCARD PHI_CONSTEXPR isize max_ssize() const PHI_NOEXCEPT
    {
        return narrow_cast<isize>(Size);
    }

    PHI_EXTENDED_CONSTEXPR void fill(const TypeT& value) PHI_NOEXCEPT
    {
        for (size_type index{0u}; index < Size; ++index)
        {
            elements[index.unsafe()] = value;
        }
    }

    PHI_EXTENDED_CONSTEXPR void swap(array& other)
            PHI_NOEXCEPT_EXPR(is_nothrow_swappable<TypeT>::value)
    {
        swap_ranges(elements, elements + Size, other.elements);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT max() const PHI_NOEXCEPT
    {
        TypeT max_value = at(0u);
        for (size_type index{1u}; index < Size; ++index)
        {
            max_value = (max_value > at(index)) ? max_value : at(index);
        }

        return max_value;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator max_index() PHI_NOEXCEPT
    {
        iterator max_index = begin();
        for (iterator index = begin(); index != end(); ++index)
        {
            max_index = (*max_index > *index) ? max_index : index;
        }

        return max_index;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator max_index() const PHI_NOEXCEPT
    {
        const_iterator max_index = begin();
        for (const_iterator index = begin(); index < end(); ++index)
        {
            max_index = (*max_index > *index) ? max_index : index;
        }

        return max_index;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT min() const PHI_NOEXCEPT
    {
        TypeT min_value = at(0u);
        for (size_type index{1u}; index < Size; ++index)
        {
            min_value = (min_value < at(index)) ? min_value : at(index);
        }

        return min_value;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator min_index() PHI_NOEXCEPT
    {
        iterator min_index = begin();
        for (iterator index = begin(); index < end(); ++index)
        {
            min_index = (*min_index < *index) ? min_index : index;
        }

        return min_index;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator min_index() const PHI_NOEXCEPT
    {
        const_iterator min_index = begin();
        for (const_iterator index = begin(); index < end(); ++index)
        {
            min_index = (*min_index < *index) ? min_index : index;
        }

        return min_index;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator find(const TypeT& value)
            PHI_NOEXCEPT_EXPR(noexcept(value == value))
    {
        for (iterator itr = begin(); itr != end(); ++itr)
        {
            if (*itr == value)
            {
                return itr;
            }
        }

        return end();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator find(const TypeT& value) const
            PHI_NOEXCEPT_EXPR(noexcept(value == value))
    {
        for (const_iterator itr = begin(); itr != end(); ++itr)
        {
            if (*itr == value)
            {
                return itr;
            }
        }

        return end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator find_if(UnaryPredicateT predicate)
            PHI_NOEXCEPT_EXPR(noexcept(predicate(front())))
    {
        for (iterator itr = begin(); itr != end(); ++itr)
        {
            if (predicate(*itr))
            {
                return itr;
            }
        }

        return end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator find_if(UnaryPredicateT predicate) const
            PHI_NOEXCEPT_EXPR(noexcept(predicate(front())))
    {
        for (const_iterator itr = begin(); itr != end(); ++itr)
        {
            if (predicate(*itr))
            {
                return itr;
            }
        }

        return end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator find_if_not(UnaryPredicateT predicate)
            PHI_NOEXCEPT_EXPR(noexcept(predicate(front())))
    {
        for (iterator itr = begin(); itr != end(); ++itr)
        {
            if (!(predicate(*itr)))
            {
                return itr;
            }
        }

        return end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator find_if_not(UnaryPredicateT predicate) const
            PHI_NOEXCEPT_EXPR(noexcept(predicate(front())))
    {
        for (const_iterator itr = begin(); itr != end(); ++itr)
        {
            if (!(predicate(*itr)))
            {
                return itr;
            }
        }

        return end();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator find_last(const TypeT& value)
            PHI_NOEXCEPT_EXPR(noexcept(value == value))
    {
        for (iterator itr = &back(); itr > begin(); --itr)
        {
            if (*itr == value)
            {
                return itr;
            }
        }

        return front() == value ? &front() : end();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator find_last(const TypeT& value) const
            PHI_NOEXCEPT_EXPR(noexcept(value == value))
    {
        for (const_iterator itr = &back(); itr > begin(); --itr)
        {
            if (*itr == value)
            {
                return itr;
            }
        }

        return front() == value ? &front() : end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator find_last_if(UnaryPredicateT predicate)
            PHI_NOEXCEPT_EXPR(noexcept(predicate(front())))
    {
        for (iterator itr = &back(); itr > begin(); --itr)
        {
            if (predicate(*itr))
            {
                return itr;
            }
        }

        return predicate(front()) ? &front() : end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator
    find_last_if(UnaryPredicateT predicate) const PHI_NOEXCEPT_EXPR(noexcept(predicate(front())))
    {
        for (const_iterator itr = &back(); itr > begin(); --itr)
        {
            if (predicate(*itr))
            {
                return itr;
            }
        }

        return predicate(front()) ? &front() : end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator find_last_if_not(UnaryPredicateT predicate)
            PHI_NOEXCEPT_EXPR(noexcept(predicate(front())))
    {
        for (iterator itr = &back(); itr > begin(); --itr)
        {
            if (!predicate(*itr))
            {
                return itr;
            }
        }

        return predicate(front()) ? end() : &front();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator
    find_last_if_not(UnaryPredicateT predicate) const
            PHI_NOEXCEPT_EXPR(noexcept(predicate(front())))
    {
        for (const_iterator itr = &back(); itr > begin(); --itr)
        {
            if (!predicate(*itr))
            {
                return itr;
            }
        }

        return predicate(front()) ? end() : &front();
    }

    PHI_EXTENDED_CONSTEXPR void reverse() PHI_NOEXCEPT
    {
        for (size_t index = 0u; index != Size / 2u; ++index)
        {
            const size_t other_index = Size - index - 1u;

            const TypeT temp_value = elements[index];

            elements[index]       = elements[other_index];
            elements[other_index] = temp_value;
        }
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR array<TypeT, Size> to_reversed() const PHI_NOEXCEPT
    {
        array<TypeT, Size> copy_of_this = *this;

        copy_of_this.reverse();

        return copy_of_this;
    }

    TypeT elements[Size];
};

#if PHI_COMPILER_IS_BELOW(GCC, 8, 0, 0)
PHI_GCC_SUPPRESS_WARNING_POP()
#endif

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(
        4702) // C4702: unreachable code (https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4702)

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

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference at(size_type /*pos*/) PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::at() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference at(size_type /*pos*/) const PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::at() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference operator[](size_type /*pos*/) PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::operator[] on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference
    operator[](size_type /*pos*/) const PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::operator[] on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_CONSTEXPR reference front() PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::front() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_CONSTEXPR const_reference front() const PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::front() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_CONSTEXPR reference back() PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::back() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_CONSTEXPR const_reference back() const PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::back() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_CONSTEXPR pointer data() PHI_NOEXCEPT
    {
        return nullptr;
    }

    PHI_NODISCARD PHI_CONSTEXPR const_pointer data() const PHI_NOEXCEPT
    {
        return nullptr;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator begin() PHI_NOEXCEPT
    {
        return iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator begin() const PHI_NOEXCEPT
    {
        return const_iterator(data());
    }

    PHI_NODISCARD PHI_CONSTEXPR const_iterator cbegin() const PHI_NOEXCEPT
    {
        return const_iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator end() PHI_NOEXCEPT
    {
        return iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator end() const PHI_NOEXCEPT
    {
        return const_iterator(data());
    }

    PHI_NODISCARD PHI_CONSTEXPR const_iterator cend() const PHI_NOEXCEPT
    {
        return const_iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reverse_iterator rbegin() PHI_NOEXCEPT
    {
        return reverse_iterator(end());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator rbegin() const PHI_NOEXCEPT
    {
        return const_reverse_iterator(end());
    }

    PHI_NODISCARD PHI_CONSTEXPR const_reverse_iterator crbegin() const PHI_NOEXCEPT
    {
        return const_reverse_iterator(end());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reverse_iterator rend() PHI_NOEXCEPT
    {
        return reverse_iterator(begin());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator rend() const PHI_NOEXCEPT
    {
        return const_reverse_iterator(begin());
    }

    PHI_NODISCARD PHI_CONSTEXPR const_reverse_iterator crend() const PHI_NOEXCEPT
    {
        return const_reverse_iterator(begin());
    }

    PHI_NODISCARD PHI_CONSTEXPR bool is_empty() const PHI_NOEXCEPT
    {
        return true;
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type size() const PHI_NOEXCEPT
    {
        return 0u;
    }

    PHI_NODISCARD PHI_CONSTEXPR isize ssize() const PHI_NOEXCEPT
    {
        return 0;
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type max_size() const PHI_NOEXCEPT
    {
        return 0u;
    }

    PHI_NODISCARD PHI_CONSTEXPR isize max_ssize() const PHI_NOEXCEPT
    {
        return 0;
    }

    PHI_CONSTEXPR void fill(const TypeT& /*value*/) PHI_NOEXCEPT
    {
        static_assert(!is_const<TypeT>::value, "Cannot fill zero-sized array of type 'const T'");
    }

    PHI_CONSTEXPR void swap(array& /*other*/) PHI_NOEXCEPT
    {
        static_assert(!is_const<TypeT>::value, "Cannot swap zero-sized array of type 'const T'");
    }

    PHI_NODISCARD PHI_CONSTEXPR TypeT max() const PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::max() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_CONSTEXPR TypeT min() const PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::min() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator max_index() PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::max_index() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator max_index() const PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::max_index() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator min_index() PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::min_index() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator min_index() const PHI_NOEXCEPT
    {
        PHI_ASSERT(false, "Cannot call array<T, 0>::min_index() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD PHI_CONSTEXPR iterator find(const TypeT& /*value*/) PHI_NOEXCEPT
    {
        return end();
    }

    PHI_NODISCARD PHI_CONSTEXPR const_iterator find(const TypeT& /*value*/) const PHI_NOEXCEPT
    {
        return end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_CONSTEXPR iterator find_if(UnaryPredicateT /*predicate*/) PHI_NOEXCEPT
    {
        return end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_CONSTEXPR const_iterator
    find_if(UnaryPredicateT /*predicate*/) const PHI_NOEXCEPT
    {
        return end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_CONSTEXPR iterator find_if_not(UnaryPredicateT /*predicate*/) PHI_NOEXCEPT
    {
        return end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_CONSTEXPR const_iterator
    find_if_not(UnaryPredicateT /*predicate*/) const PHI_NOEXCEPT
    {
        return end();
    }

    PHI_NODISCARD PHI_CONSTEXPR iterator find_last(const TypeT& /*value*/) PHI_NOEXCEPT
    {
        return end();
    }

    PHI_NODISCARD PHI_CONSTEXPR const_iterator find_last(const TypeT& /*value*/) const PHI_NOEXCEPT
    {
        return end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_CONSTEXPR iterator find_last_if(UnaryPredicateT /*predicate*/) PHI_NOEXCEPT
    {
        return end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_CONSTEXPR const_iterator
    find_last_if(UnaryPredicateT /*predicate*/) const PHI_NOEXCEPT
    {
        return end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_CONSTEXPR iterator find_last_if_not(UnaryPredicateT /*predicate*/)
            PHI_NOEXCEPT
    {
        return end();
    }

    template <typename UnaryPredicateT>
    PHI_NODISCARD PHI_CONSTEXPR const_iterator
    find_last_if_not(UnaryPredicateT /*predicate*/) const PHI_NOEXCEPT
    {
        return end();
    }

    PHI_CONSTEXPR void reverse() PHI_NOEXCEPT
    {}

    PHI_NODISCARD PHI_CONSTEXPR array<TypeT, 0u> to_reversed() const PHI_NOEXCEPT
    {
        return array<TypeT, 0u>{};
    }
};

PHI_MSVC_SUPPRESS_WARNING_POP()

template <typename TypeT, size_t Size>
PHI_EXTENDED_CONSTEXPR boolean operator==(const array<TypeT, Size>& lhs,
                                          const array<TypeT, Size>& rhs)
        PHI_NOEXCEPT_EXPR(noexcept(equal(lhs.begin(), lhs.end(), rhs.begin())))
{
    return equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename TypeT, size_t Size>
PHI_EXTENDED_CONSTEXPR boolean operator!=(const array<TypeT, Size>& lhs,
                                          const array<TypeT, Size>& rhs)
        PHI_NOEXCEPT_EXPR(noexcept(!(lhs == rhs)))
{
    return !(lhs == rhs);
}

template <typename TypeT, size_t Size>
PHI_EXTENDED_CONSTEXPR boolean operator<(const array<TypeT, Size>& lhs,
                                         const array<TypeT, Size>& rhs)
        PHI_NOEXCEPT_EXPR(noexcept(lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                                           rhs.end())))
{
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename TypeT, size_t Size>
PHI_EXTENDED_CONSTEXPR boolean operator<=(const array<TypeT, Size>& lhs,
                                          const array<TypeT, Size>& rhs)
        PHI_NOEXCEPT_EXPR(noexcept(!(rhs < lhs)))
{
    return !(rhs < lhs);
}

template <typename TypeT, size_t Size>
PHI_EXTENDED_CONSTEXPR boolean operator>(const array<TypeT, Size>& lhs,
                                         const array<TypeT, Size>& rhs)
        PHI_NOEXCEPT_EXPR(noexcept(rhs < lhs))
{
    return rhs < lhs;
}

template <typename TypeT, size_t Size>
PHI_EXTENDED_CONSTEXPR boolean operator>=(const array<TypeT, Size>& lhs,
                                          const array<TypeT, Size>& rhs)
        PHI_NOEXCEPT_EXPR(noexcept(!(lhs < rhs)))
{
    return !(lhs < rhs);
}

template <typename TypeT, size_t Size>
PHI_EXTENDED_CONSTEXPR_OR_INLINE void swap(array<TypeT, Size>& lhs, array<TypeT, Size>& rhs)
        PHI_NOEXCEPT_EXPR(noexcept(lhs.swap(rhs)))
{
    lhs.swap(rhs);
}

#if PHI_HAS_FEATURE_DEDUCTION_GUIDES()
template <typename TypeT, typename... ArgsT>
array(TypeT, ArgsT...) -> array<TypeT, 1 + sizeof...(ArgsT)>;
#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CONTAINER_ARRAY_HPP
