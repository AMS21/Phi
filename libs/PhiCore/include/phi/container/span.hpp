#ifndef INCG_PHI_CONTAINER_SPAN_HPP
#define INCG_PHI_CONTAINER_SPAN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/byte.hpp"
#include "phi/core/narrow_cast.hpp"
#include "phi/core/to_address.hpp"
#include "phi/core/types.hpp"
#include "phi/forward/array.hpp"
#include "phi/forward/span.hpp"
#include "phi/forward/std/array.hpp"
#include "phi/iterator/iter_reference.hpp"
#include "phi/iterator/reverse_iterator.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/remove_cv.hpp"

// TODO: Missing constructors: https://en.cppreference.com/w/cpp/container/span/span
// TODO: operator= https://en.cppreference.com/w/cpp/container/span/operator%3D

DETAIL_PHI_BEGIN_NAMESPACE()

// Static non-zero extent
template <typename TypeT, size_t Extent>
class span
{
public:
    using this_type              = span<TypeT, Extent>;
    using element_type           = TypeT;
    using value_type             = remove_cv_t<TypeT>;
    using size_type              = usize;
    using ssize_type             = isize;
    using difference_type        = ptrdiff;
    using pointer                = TypeT*;
    using const_pointer          = const TypeT*;
    using reference              = TypeT&;
    using const_reference        = const TypeT&;
    using iterator               = TypeT*;
    using const_iterator         = const TypeT*;
    using reverse_iterator       = phi::reverse_iterator<iterator>;
    using const_reverse_iterator = phi::reverse_iterator<const_iterator>;

    static constexpr size_t extent = Extent;

    // TODO: Missing compatibility checks for Iterator element_type
    template <typename IteratorT>
    constexpr explicit span(IteratorT first, size_type count) noexcept
        : m_Data{to_address(first)}
    {
        (void)count;
        PHI_ASSERT(count == Extent, "Mismatch for given count and Extent");
    }

    template <typename BeginIteratorT, typename EndIteratorT>
    constexpr explicit span(BeginIteratorT first, EndIteratorT last)
        : m_Data{to_address(first)}
    {
        auto distance = last - first;
        (void)distance;

        PHI_ASSERT(distance >= 0, "Invalid range, empty");
        PHI_ASSERT(distance == Extent, "Invalid range, mismatched count");
    }

    constexpr span(element_type (&array)[Extent]) noexcept
        : m_Data{array}
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT, TypeT>::value, int> = 0>
    constexpr span(array<OtherT, Extent>& array) noexcept
        : m_Data{array.data()}
    {}

    template <typename OtherT, enable_if_t<is_convertible<const OtherT, TypeT*>::value, int> = 0>
    constexpr span(const array<OtherT, Extent>& array) noexcept
        : m_Data{array.data()}
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT, TypeT>::value, int> = 0>
    constexpr span(std::array<OtherT, Extent>& array) noexcept
        : m_Data{array.data()}
    {}

    template <typename OtherT, enable_if_t<is_convertible<const OtherT, TypeT*>::value, int> = 0>
    constexpr span(const std::array<OtherT, Extent>& array) noexcept
        : m_Data{array.data()}
    {}

    // TODO: Support range constructor

    template <typename OtherT, enable_if_t<is_convertible<OtherT, TypeT>::value, int> = 0>
    constexpr span(const span<OtherT, Extent>& other)
        : m_Data{other.data()}
    {}

    template <typename OtherT, enable_if_t<is_convertible<OtherT, TypeT>::value, int> = 0>
    constexpr explicit span(const span<OtherT, dynamic_extent>& other) noexcept
        : m_Data{other.data()}
    {
        PHI_ASSERT(other.size() == Extent, "Mismatch for given count and Extent");
    }

    PHI_NODISCARD constexpr iterator begin() noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr const_iterator begin() const noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr const_iterator cbegin() const noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr iterator end() noexcept
    {
        return m_Data + Extent;
    }

    PHI_NODISCARD constexpr const_iterator end() const noexcept
    {
        return m_Data + Extent;
    }

    PHI_NODISCARD constexpr const_iterator cend() const noexcept
    {
        return m_Data + Extent;
    }

    PHI_NODISCARD constexpr reverse_iterator rbegin() noexcept
    {
        return reverse_iterator{end()};
    }

    PHI_NODISCARD constexpr const_reverse_iterator rbegin() const noexcept
    {
        return reverse_iterator{end()};
    }

    PHI_NODISCARD constexpr const_reverse_iterator crbegin() const noexcept
    {
        return reverse_iterator{end()};
    }

    PHI_NODISCARD constexpr reverse_iterator rend() noexcept
    {
        return reverse_iterator{begin()};
    }

    PHI_NODISCARD constexpr const_reverse_iterator rend() const noexcept
    {
        return reverse_iterator{begin()};
    }

    PHI_NODISCARD constexpr const_reverse_iterator crend() const noexcept
    {
        return reverse_iterator{begin()};
    }

    PHI_NODISCARD constexpr reference front() noexcept
    {
        return m_Data[0];
    }

    PHI_NODISCARD constexpr const_reference front() const noexcept
    {
        return m_Data[0];
    }

    PHI_NODISCARD constexpr reference back() noexcept
    {
        return m_Data[Extent - 1];
    }

    PHI_NODISCARD constexpr const_reference back() const noexcept
    {
        return m_Data[Extent - 1];
    }

    PHI_NODISCARD constexpr reference operator[](size_type index) noexcept
    {
        PHI_ASSERT(index < Extent, "Index out of bounds");

        return m_Data[index.unsafe()];
    }

    PHI_NODISCARD constexpr const_reference operator[](size_type index) const noexcept
    {
        PHI_ASSERT(index < Extent, "Index out of bounds");

        return m_Data[index.unsafe()];
    }

    PHI_NODISCARD constexpr reference at(size_type index) noexcept
    {
        PHI_ASSERT(index < Extent, "Index out of bounds");

        return m_Data[index.unsafe()];
    }

    PHI_NODISCARD constexpr const_reference at(size_type index) const noexcept
    {
        PHI_ASSERT(index < Extent, "Index out of bounds");

        return m_Data[index.unsafe()];
    }

    PHI_NODISCARD constexpr pointer data() noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr const_pointer data() const noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr size_type size() const noexcept
    {
        return Extent;
    }

    PHI_NODISCARD constexpr ssize_type ssize() const noexcept
    {
        return narrow_cast<ssize_type>(Extent);
    }

    PHI_NODISCARD constexpr size_type size_bytes() const noexcept
    {
        return Extent * sizeof(TypeT);
    }

    PHI_NODISCARD constexpr ssize_type ssize_bytes() const noexcept
    {
        return narrow_cast<ssize_type>(Extent * sizeof(TypeT));
    }

    PHI_NODISCARD constexpr boolean is_empty() const noexcept
    {
        return false;
    }

    PHI_NODISCARD constexpr span<const byte, Extent * sizeof(TypeT)> as_bytes() const noexcept
    {
        return {reinterpret_cast<const byte*>(data()), size_bytes()};
    }

    PHI_NODISCARD constexpr span<byte, Extent * sizeof(TypeT)> as_writable_bytes() noexcept
    {
        return {reinterpret_cast<byte*>(data()), size_bytes()};
    }

    template <size_t Count>
    PHI_NODISCARD constexpr span<element_type, Count> first() const noexcept
    {
        PHI_ASSERT(Count <= Extent, "Count out of range");

        return span<element_type, Count>{m_Data, Count};
    }

    PHI_NODISCARD constexpr span<element_type, dynamic_extent> first(size_type count) const noexcept
    {
        PHI_ASSERT(count <= Extent, "Count out of range");

        return span<element_type, dynamic_extent>{m_Data, count};
    }

    template <size_t Count>
    PHI_NODISCARD constexpr span<element_type, Count> last() const noexcept
    {
        PHI_ASSERT(Count <= Extent, "Count out of range");

        return span<element_type, Count>{m_Data + Extent - Count, Count};
    }

    PHI_NODISCARD constexpr span<element_type, dynamic_extent> last(size_type count) const noexcept
    {
        PHI_ASSERT(count <= Extent, "Count out of range");

        return span<element_type, dynamic_extent>{m_Data + Extent - count, count};
    }

    template <size_t Offset, size_t Count = dynamic_extent>
    PHI_NODISCARD constexpr span<element_type, Count != dynamic_extent ? Count : Extent - Offset>
    subspan() const noexcept
    {
        static_assert(Offset <= Extent, "Offset out of range");
        static_assert(Count == dynamic_extent || Count <= Extent - Offset,
                      "Offset + Count out of range");

        using ReturnType = span<element_type, Count != dynamic_extent ? Count : Extent - Offset>;
        return ReturnType{data() + Offset, Count == dynamic_extent ? size() - Offset : Count};
    }

    PHI_NODISCARD constexpr span<element_type, dynamic_extent> subspan(
            size_type offset, size_type count = dynamic_extent) const noexcept
    {
        PHI_ASSERT(offset <= size(), "offset out of range");
        if (count == dynamic_extent)
        {
            return {data() + offset, size() - offset};
        }

        PHI_ASSERT(count <= size() - offset, "offset + count out of range");
        return {data() + offset, count};
    }

private:
    pointer m_Data;
};

// Zero extent
template <typename TypeT>
class span<TypeT, 0u>
{
public:
    using this_type              = span<TypeT, 0u>;
    using element_type           = TypeT;
    using value_type             = remove_cv_t<TypeT>;
    using size_type              = usize;
    using ssize_type             = isize;
    using difference_type        = ptrdiff;
    using pointer                = TypeT*;
    using const_pointer          = const TypeT*;
    using reference              = TypeT&;
    using const_reference        = const TypeT&;
    using iterator               = TypeT*;
    using const_iterator         = const TypeT*;
    using reverse_iterator       = phi::reverse_iterator<iterator>;
    using const_reverse_iterator = phi::reverse_iterator<const_iterator>;

    static constexpr size_t extent = 0u;

    constexpr span() noexcept = default;

    PHI_NODISCARD constexpr iterator begin() noexcept
    {
        return nullptr;
    }

    PHI_NODISCARD constexpr const_iterator begin() const noexcept
    {
        return nullptr;
    }

    PHI_NODISCARD constexpr const_iterator cbegin() const noexcept
    {
        return nullptr;
    }

    PHI_NODISCARD constexpr iterator end() noexcept
    {
        return nullptr;
    }

    PHI_NODISCARD constexpr const_iterator end() const noexcept
    {
        return nullptr;
    }

    PHI_NODISCARD constexpr const_iterator cend() const noexcept
    {
        return nullptr;
    }

    PHI_NODISCARD constexpr reverse_iterator rbegin() noexcept
    {
        return reverse_iterator{end()};
    }

    PHI_NODISCARD constexpr const_reverse_iterator rbegin() const noexcept
    {
        return reverse_iterator{end()};
    }

    PHI_NODISCARD constexpr const_reverse_iterator crbegin() const noexcept
    {
        return reverse_iterator{end()};
    }

    PHI_NODISCARD constexpr reverse_iterator rend() noexcept
    {
        return reverse_iterator{begin()};
    }

    PHI_NODISCARD constexpr const_reverse_iterator rend() const noexcept
    {
        return reverse_iterator{begin()};
    }

    PHI_NODISCARD constexpr const_reverse_iterator crend() const noexcept
    {
        return reverse_iterator{begin()};
    }

    PHI_NODISCARD constexpr reference front() noexcept
    {
        PHI_ASSERT(false, "Cannot call span<T, 0>::front() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD constexpr const_reference front() const noexcept
    {
        PHI_ASSERT(false, "Cannot call span<T, 0>::front() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD constexpr reference back() noexcept
    {
        PHI_ASSERT(false, "Cannot call span<T, 0>::back() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD constexpr const_reference back() const noexcept
    {
        PHI_ASSERT(false, "Cannot call span<T, 0>::back() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD constexpr reference operator[](size_type index) noexcept
    {
        PHI_ASSERT(false, "Cannot call span<T, 0>::operator[] on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD constexpr const_reference operator[](size_type index) const noexcept
    {
        PHI_ASSERT(false, "Cannot call span<T, 0>::operator[] on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD constexpr reference at(size_type index) noexcept
    {
        PHI_ASSERT(false, "Cannot call span<T, 0>::at() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD constexpr const_reference at(size_type index) const noexcept
    {
        PHI_ASSERT(false, "Cannot call span<T, 0>::at() on zero sized array");
        PHI_UNREACHABLE();
    }

    PHI_NODISCARD constexpr pointer data() noexcept
    {
        return nullptr;
    }

    PHI_NODISCARD constexpr const_pointer data() const noexcept
    {
        return nullptr;
    }

    PHI_NODISCARD constexpr size_type size() const noexcept
    {
        return 0u;
    }

    PHI_NODISCARD constexpr ssize_type ssize() const noexcept
    {
        return 0;
    }

    PHI_NODISCARD constexpr size_type size_bytes() const noexcept
    {
        return 0u;
    }

    PHI_NODISCARD constexpr ssize_type ssize_bytes() const noexcept
    {
        return 0;
    }

    PHI_NODISCARD constexpr boolean is_empty() const noexcept
    {
        return true;
    }

    PHI_NODISCARD constexpr span<const byte, 0u> as_bytes() const noexcept
    {
        return {reinterpret_cast<const byte*>(data()), size_bytes()};
    }

    PHI_NODISCARD constexpr span<byte, 0u> as_writable_bytes() noexcept
    {
        return {reinterpret_cast<byte*>(data()), size_bytes()};
    }
};

// Dynamic extent
template <typename TypeT>
class span<TypeT, dynamic_extent>
{
public:
    using this_type              = span<TypeT, dynamic_extent>;
    using element_type           = TypeT;
    using value_type             = remove_cv_t<TypeT>;
    using size_type              = usize;
    using ssize_type             = isize;
    using difference_type        = ptrdiff;
    using pointer                = TypeT*;
    using const_pointer          = const TypeT*;
    using reference              = TypeT&;
    using const_reference        = const TypeT&;
    using iterator               = TypeT*;
    using const_iterator         = const TypeT*;
    using reverse_iterator       = phi::reverse_iterator<iterator>;
    using const_reverse_iterator = phi::reverse_iterator<const_iterator>;

    static constexpr size_t extent = dynamic_extent;

    PHI_NODISCARD constexpr iterator begin() noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr const_iterator begin() const noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr const_iterator cbegin() const noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr iterator end() noexcept
    {
        return m_Data + m_Size;
    }

    PHI_NODISCARD constexpr const_iterator end() const noexcept
    {
        return m_Data + m_Size;
    }

    PHI_NODISCARD constexpr const_iterator cend() const noexcept
    {
        return m_Data + m_Size;
    }

    PHI_NODISCARD constexpr reverse_iterator rbegin() noexcept
    {
        return reverse_iterator{end()};
    }

    PHI_NODISCARD constexpr const_reverse_iterator rbegin() const noexcept
    {
        return reverse_iterator{end()};
    }

    PHI_NODISCARD constexpr const_reverse_iterator crbegin() const noexcept
    {
        return reverse_iterator{end()};
    }

    PHI_NODISCARD constexpr reverse_iterator rend() noexcept
    {
        return reverse_iterator{begin()};
    }

    PHI_NODISCARD constexpr const_reverse_iterator rend() const noexcept
    {
        return reverse_iterator{begin()};
    }

    PHI_NODISCARD constexpr const_reverse_iterator crend() const noexcept
    {
        return reverse_iterator{begin()};
    }

    PHI_NODISCARD constexpr reference front() noexcept
    {
        PHI_ASSERT(m_Size > 0u, "Index out of bounds");
        return m_Data[0];
    }

    PHI_NODISCARD constexpr const_reference front() const noexcept
    {
        PHI_ASSERT(m_Size > 0u, "Index out of bounds");
        return m_Data[0];
    }

    PHI_NODISCARD constexpr reference back() noexcept
    {
        PHI_ASSERT(m_Size > 0u, "Index out of bounds");
        return m_Data[m_Size.unsafe() - 1];
    }

    PHI_NODISCARD constexpr const_reference back() const noexcept
    {
        PHI_ASSERT(m_Size > 0u, "Index out of bounds");
        return m_Data[m_Size.unsafe() - 1];
    }

    PHI_NODISCARD constexpr reference operator[](size_type index) noexcept
    {
        PHI_ASSERT(index < m_Size, "Index out of bounds");

        return m_Data[index.unsafe()];
    }

    PHI_NODISCARD constexpr const_reference operator[](size_type index) const noexcept
    {
        PHI_ASSERT(index < m_Size, "Index out of bounds");

        return m_Data[index.unsafe()];
    }

    PHI_NODISCARD constexpr reference at(size_type index) noexcept
    {
        PHI_ASSERT(index < m_Size, "Index out of bounds");

        return m_Data[index.unsafe()];
    }

    PHI_NODISCARD constexpr const_reference at(size_type index) const noexcept
    {
        PHI_ASSERT(index < m_Size, "Index out of bounds");

        return m_Data[index.unsafe()];
    }

    PHI_NODISCARD constexpr pointer data() noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr const_pointer data() const noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr size_type size() const noexcept
    {
        return m_Size;
    }

    PHI_NODISCARD constexpr ssize_type ssize() const noexcept
    {
        return narrow_cast<ssize_type>(m_Size);
    }

    PHI_NODISCARD constexpr size_type size_bytes() const noexcept
    {
        return m_Data * sizeof(TypeT);
    }

    PHI_NODISCARD constexpr ssize_type ssize_bytes() const noexcept
    {
        return narrow_cast<ssize_type>(m_Data * sizeof(TypeT));
    }

    PHI_NODISCARD constexpr boolean is_empty() const noexcept
    {
        return m_Size == 0u;
    }

    PHI_NODISCARD constexpr span<const byte, dynamic_extent> as_bytes() const noexcept
    {
        return {reinterpret_cast<const byte*>(data()), size_bytes()};
    }

    PHI_NODISCARD constexpr span<byte, dynamic_extent> as_writable_bytes() noexcept
    {
        return {reinterpret_cast<byte*>(data()), size_bytes()};
    }

    template <size_t Offset, size_t Count = dynamic_extent>
    PHI_NODISCARD constexpr span<element_type, Count> subspan() const noexcept
    {
        PHI_ASSERT(Offset <= m_Size, "Offset out of range");
        PHI_ASSERT(Count == dynamic_extent || Count <= m_Size - Offset,
                   "Offset + Count out of range");

        return span<element_type, Count>{m_Data + Offset,
                                         Count == dynamic_extent ? m_Size - Offset : Count};
    }

    PHI_NODISCARD constexpr span<element_type, dynamic_extent> subspan(
            size_type offset, size_type count = dynamic_extent) const noexcept
    {
        PHI_ASSERT(offset <= m_Size, "Offset out of range");
        if (count == dynamic_extent)
        {
            return {m_Data + offset, m_Size - offset};
        }

        PHI_ASSERT(count <= m_Size - offset, "Offset + count out of range");

        return {m_Data + offset, count};
    }

private:
    pointer   m_Data;
    size_type m_Size;
};

template <typename TypeT, size_t Extent>
PHI_NODISCARD constexpr span<TypeT, Extent * sizeof(TypeT)> as_bytes(
        span<TypeT, Extent> arg) noexcept
{
    return arg.as_bytes();
}

template <typename TypeT>
PHI_NODISCARD constexpr span<TypeT, dynamic_extent> as_bytes(
        span<TypeT, dynamic_extent> arg) noexcept
{
    return arg.as_bytes();
}

template <typename TypeT, size_t Extent>
PHI_NODISCARD constexpr span<TypeT, Extent * sizeof(TypeT)> as_writable_bytes(
        span<TypeT, Extent> arg) noexcept
{
    return arg.as_writable_bytes();
}

template <typename TypeT>
PHI_NODISCARD constexpr span<TypeT, dynamic_extent> as_writable_bytes(
        span<TypeT, dynamic_extent> arg) noexcept
{
    return arg.as_writable_bytes();
}

#if PHI_HAS_FEATURE_DEDUCTION_GUIDES()

template <typename IteratorT, typename EndOrSizeT>
span(IteratorT, EndOrSizeT) -> span<remove_reference_t<iter_reference_t<IteratorT>>>;

template <typename TypeT, size_t Size>
span(TypeT (&)[Size]) -> span<TypeT, Size>;

template <typename TypeT, size_t Size>
span(std::array<TypeT, Size>&) -> span<TypeT, Size>;

template <typename TypeT, size_t Size>
span(const std::array<TypeT, Size>&) -> span<const TypeT, Size>;

template <typename TypeT, size_t Size>
span(array<TypeT, Size>&) -> span<TypeT, Size>;

template <typename TypeT, size_t Size>
span(const array<TypeT, Size>&) -> span<const TypeT, Size>;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CONTAINER_SPAN_HPP
