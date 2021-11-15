#ifndef INCG_PHI_CONTAINER_STRING_VIEW_HPP
#define INCG_PHI_CONTAINER_STRING_VIEW_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/Algorithm/StringLength.hpp"
#include "Phi/CompilerSupport/Char8_t.hpp"
#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Integer.hpp"
#include "Phi/Core/Nullptr.hpp"
#include "Phi/Core/SizeT.hpp"
#include "Phi/Core/Types.hpp"
#include "Phi/TypeTraits/is_array.hpp"
#include "Phi/TypeTraits/is_same.hpp"
#include "Phi/TypeTraits/is_standard_layout.hpp"
#include "Phi/TypeTraits/is_trivial.hpp"
#include <algorithm>
#include <iterator>
#include <limits>
#include <string>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT, typename TraitsT = std::char_traits<CharT>>
class BasicStringView
{
public:
    using this_type              = BasicStringView<CharT, TraitsT>;
    using value_type             = CharT;
    using traits_type            = TraitsT;
    using pointer                = CharT*;
    using const_pointer          = const CharT*;
    using reference              = CharT&;
    using const_reference        = const CharT&;
    using iterator               = const_pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<const_iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using size_type              = usize;
    using difference_type        = ptrdiff;

    // Static checks
    static_assert(!is_array<value_type>::value,
                  "phi::BasicStringView: Character type must not be an array");
    static_assert(is_standard_layout<value_type>::value,
                  "phi::BasicStringView: Character type must be standard-layout");
    static_assert(is_trivial<value_type>::value,
                  "phi::BasicStringView: Character type must be trivial");
    static_assert(is_same<value_type, typename traits_type::char_type>::value,
                  "phi::BasicStringView: CharT must be the same type as traits_type::char_type");

    // Constants
    // TODO: For some reason using size_type instead of size_t causes a linker error in StringView.test.cpp when compiling with GCC
    static constexpr size_t npos = std::numeric_limits<size_t>::max();

    // Constructors
    constexpr BasicStringView() noexcept
        : m_Data(nullptr)
        , m_Size(0u)
    {}

    constexpr BasicStringView(const BasicStringView& other) noexcept = default;

    constexpr BasicStringView(BasicStringView&& other) noexcept = default;

    PHI_EXTENDED_CONSTEXPR BasicStringView(const CharT* string) noexcept
        : m_Data(string)
        , m_Size(StringLength(string))
    {
        PHI_DBG_ASSERT(string != nullptr, "Do not construct a BasicStringView with nullptr");
    }

    PHI_EXTENDED_CONSTEXPR BasicStringView(const CharT* string, size_type count) noexcept
        : m_Data(string)
        , m_Size(count)
    {
        PHI_DBG_ASSERT(string != nullptr, "Do not construct a BasicStringView with nullptr");
        PHI_DBG_ASSERT(count > 0u, "Cannot construct with 0 size");
        PHI_DBG_ASSERT(StringLength(string, count) == count,
                       "The supplied string is shorter than the given count");
    }

    constexpr BasicStringView(nullptr_t) = delete;

    ~BasicStringView() = default;

    PHI_EXTENDED_CONSTEXPR BasicStringView& operator=(const BasicStringView& other) noexcept =
            default;

    PHI_EXTENDED_CONSTEXPR BasicStringView& operator=(BasicStringView&& other) noexcept = default;

    BasicStringView& operator=(nullptr_t) = delete;

    // Iterators

    PHI_NODISCARD constexpr iterator begin() const noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr iterator end() const noexcept
    {
        return m_Data + m_Size.get();
    }

    PHI_NODISCARD constexpr const_iterator cbegin() const noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr const_iterator cend() const noexcept
    {
        return m_Data + m_Size.get();
    }

    PHI_NODISCARD constexpr reverse_iterator rbegin() const noexcept
    {
        return reverse_iterator(end());
    }

    PHI_NODISCARD constexpr reverse_iterator rend() const noexcept
    {
        return reverse_iterator(begin());
    }

    PHI_NODISCARD constexpr const_reverse_iterator crbegin() const noexcept
    {
        return reverse_iterator(rbegin());
    }

    PHI_NODISCARD constexpr const_reverse_iterator crend() const noexcept
    {
        return reverse_iterator(rend());
    }

    // Capacity

    PHI_NODISCARD constexpr size_type size() const noexcept
    {
        return m_Size;
    }

    PHI_NODISCARD constexpr size_type length() const noexcept
    {
        return m_Size;
    }

    PHI_NODISCARD constexpr size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max();
    }

    PHI_NODISCARD constexpr Boolean is_empty() const noexcept
    {
        return m_Size == 0u;
    }

    // Element access

    PHI_NODISCARD constexpr const_reference operator[](size_type pos) const noexcept
    {
        return data_at(pos);
    }

    PHI_NODISCARD constexpr const_reference at(size_type pos) const noexcept
    {
        return data_at(pos);
    }

    PHI_NODISCARD constexpr const_reference front() const noexcept
    {
        return data_at(0u);
    }

    PHI_NODISCARD constexpr const_reference back() const noexcept
    {
        return data_at(size() - 1u);
    }

    PHI_NODISCARD constexpr const_pointer data() const noexcept
    {
        return m_Data;
    }

    // Modifiers

    PHI_EXTENDED_CONSTEXPR BasicStringView& clear() noexcept
    {
        m_Data = nullptr;
        m_Size = 0u;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR BasicStringView& add_prefix(size_type count) noexcept
    {
        m_Data -= count.get();
        m_Size += count;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR BasicStringView& add_postfix(size_type count) noexcept
    {
        m_Size += count;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR BasicStringView& remove_prefix(size_type count) noexcept
    {
        PHI_DBG_ASSERT(count <= size(), "Cannot remove more than size");

        m_Data += count.get();
        m_Size -= count;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR BasicStringView& remove_suffix(size_type count) noexcept
    {
        PHI_DBG_ASSERT(count <= size(), "Cannot remove more than size");

        m_Size -= count;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR BasicStringView& resize(size_type new_size) noexcept
    {
        m_Size = new_size;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR void swap(BasicStringView& other) noexcept
    {
        const BasicStringView tmp(other);
        other = *this;
        *this = tmp;
    }

    // String operations

    PHI_EXTENDED_CONSTEXPR size_type copy(CharT* destination, size_type count,
                                          size_type pos = 0u) const noexcept
    {
        PHI_DBG_ASSERT(pos <= size(), "Invalid position");

        const size_type rlen = std::min(count, size() - pos);
        TraitsT::copy(destination, data() + pos.get(), rlen.get());

        return rlen;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR BasicStringView
    substr(size_type pos = 0u, size_type count = npos) const noexcept
    {
        PHI_DBG_ASSERT(pos <= size(), "Invalid position");

        return BasicStringView(data() + pos.get(), std::min(count, size() - pos));
    }

    // Comparing

    PHI_NODISCARD constexpr i32 compare(BasicStringView other) const noexcept
    {
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
        {
            const i32 result = TraitsT::compare(data(), other.data(),
                                                std::min(size().get(), other.size().get()));

            if (result != 0)
            {
                return result;
            }
        }

        return size() == other.size() ? 0 : size() < other.size() ? -1 : 1;

#else

        // Ugly C++-11 compatible version of the same code
        return TraitsT::compare(data(), other.data(), std::min(size().get(), other.size().get())) !=
                               0 ?
                                        TraitsT::compare(data(), other.data(),
                                        std::min(size().get(), other.size().get())) :
               size() == other.size() ? 0 :
               size() < other.size()  ? -1 :
                                        1;

#endif
    }

    PHI_NODISCARD constexpr i32 compare(size_type pos, size_type count,
                                        BasicStringView other) const noexcept
    {
        return substr(pos, count).compare(other);
    }

    PHI_NODISCARD constexpr i32 compare(size_type pos1, size_type count1, BasicStringView other,
                                        size_type pos2, size_type count2) const noexcept
    {
        return substr(pos1, count1).compare(other.substr(pos2, count2));
    }

    PHI_NODISCARD constexpr i32 compare(const CharT* string) const noexcept
    {
        return compare(BasicStringView(string));
    }

    PHI_NODISCARD constexpr i32 compare(size_type pos, size_type count,
                                        const CharT* string) const noexcept
    {
        return substr(pos, count).compare(BasicStringView(string));
    }

    PHI_NODISCARD constexpr i32 compare(size_type pos, size_type count1, const CharT* string,
                                        size_type count2) const noexcept
    {
        return substr(pos, count1).compare(BasicStringView(string, count2));
    }

    // Searching

    PHI_NODISCARD constexpr Boolean starts_with(BasicStringView view) const noexcept
    {
        return size() >= view.size() && compare(0u, view.size(), view) == 0;
    }

    PHI_NODISCARD constexpr Boolean starts_with(CharT c) const noexcept
    {
        return starts_with(BasicStringView(&c, 1u));
    }

    PHI_NODISCARD constexpr Boolean starts_with(const CharT* string) const noexcept
    {
        return starts_with(BasicStringView(string));
    }

    PHI_NODISCARD constexpr Boolean ends_with(BasicStringView view) const noexcept
    {
        return size() >= view.size() && compare(size() - view.size(), npos, view) == 0;
    }

    PHI_NODISCARD constexpr Boolean ends_with(CharT c) const noexcept
    {
        return ends_with(BasicStringView(&c, 1u));
    }

    PHI_NODISCARD constexpr Boolean ends_with(const CharT* string) const noexcept
    {
        return ends_with(BasicStringView(string));
    }

    // contains

    PHI_NODISCARD constexpr Boolean contains(BasicStringView view) const noexcept
    {
        return find(view) != npos;
    }

    PHI_NODISCARD constexpr Boolean contains(CharT c) const noexcept
    {
        return find(c) != npos;
    }

    PHI_NODISCARD constexpr Boolean contains(const CharT* string) const noexcept
    {
        return find(string) != npos;
    }

    // find

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type find(BasicStringView view,
                                                        size_type       pos = 0u) const noexcept
    {
        PHI_DBG_ASSERT(view.size() == 0u || view.data() != nullptr, "Invalid argument view");

        return pos >= size() ? npos :
                               to_pos(std::search(cbegin() + pos, cend(), view.cbegin(),
                                                  view.cend(), TraitsT::eq));
    }

    PHI_NODISCARD constexpr size_type find(CharT c, size_type pos = 0u) const noexcept
    {
        return find(BasicStringView(&c, 1u), pos);
    }

    PHI_NODISCARD constexpr size_type find(const CharT* string, size_type pos = 0u) const noexcept
    {
        return find(BasicStringView(string), pos);
    }

    PHI_NODISCARD constexpr size_type find(const CharT* string, size_type pos,
                                           size_type count) const noexcept
    {
        return find(BasicStringView(string, count), pos);
    }

    // rfind

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type rfind(BasicStringView view,
                                                         size_type       pos = npos) const noexcept
    {
        if (size() < view.size())
        {
            return npos;
        }

        if (view.empty())
        {
            return std::min(size(), pos);
        }

        const_iterator last = cbegin() + std::min(size() - view.size(), pos) + view.size();
        const_iterator result =
                std::find_end(cbegin(), last, view.cbegin(), view.cend(), TraitsT::eq);

        if (result != last)
        {
            return size_type(result - cbegin());
        }

        return npos;
    }

    PHI_NODISCARD constexpr size_type rfind(CharT c, size_type pos = npos) const noexcept
    {
        return rfind(BasicStringView(&c, 1u), pos);
    }

    PHI_NODISCARD constexpr size_type rfind(const CharT* string,
                                            size_type    pos = npos) const noexcept
    {
        return rfind(BasicStringView(string), pos);
    }

    PHI_NODISCARD constexpr size_type rfind(const CharT* string, size_type pos,
                                            size_type count) const noexcept
    {
        return rfind(BasicStringView(string, count), pos);
    }

    PHI_NODISCARD constexpr size_type find_first_of(BasicStringView view,
                                                    size_type       pos = 0u) const noexcept
    {
        return pos >= size() ? npos :
                               to_pos(std::find_first_of(cbegin() + pos, cend(), view.cbegin(),
                                                         view.cend(), TraitsT::eq));
    }

    PHI_NODISCARD constexpr size_type find_first_of(CharT c, size_type pos = 0u) const noexcept
    {
        return find_first_of(BasicStringView(&c, 1u), pos);
    }

    PHI_NODISCARD constexpr size_type find_first_of(const CharT* string,
                                                    size_type    pos = 0u) const noexcept
    {
        return find_first_of(BasicStringView(string), pos);
    }

    PHI_NODISCARD constexpr size_type find_first_of(const CharT* string, size_type pos,
                                                    size_type count) const noexcept
    {
        return find_first_of(BasicStringView(string, count), pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type find_last_of(BasicStringView view,
                                                                size_type pos = npos) const noexcept
    {
        if (is_empty())
        {
            return npos;
        }

        if (pos >= size())
        {
            return find_last_of(view, size() - 1);
        }

        return to_pos(std::find_first_of(const_reverse_iterator(cbegin() + pos + 1), crend(),
                                         view.cbegin(), view.cend(), TraitsT::eq));
    }

    PHI_NODISCARD constexpr size_type find_last_of(CharT c, size_type pos = npos) const noexcept
    {
        return find_last_of(BasicStringView(&c, 1u), pos);
    }

    PHI_NODISCARD constexpr size_type find_last_of(const CharT* string,
                                                   size_type    pos = npos) const noexcept
    {
        return find_last_of(BasicStringView(string), pos);
    }

    PHI_NODISCARD constexpr size_type find_last_of(const CharT* string, size_type pos,
                                                   size_type count) const noexcept
    {
        return find_last_of(BasicStringView(string, count), pos);
    }

    PHI_NODISCARD constexpr size_type find_first_not_of(BasicStringView view,
                                                        size_type       pos = 0u) const noexcept
    {
        return pos >= size() ? npos :
                               to_pos(std::find_if(cbegin() + pos, cend(), not_in_view(view)));
    }

    PHI_NODISCARD constexpr size_type find_first_not_of(CharT c, size_type pos = 0u) const noexcept
    {
        return find_first_not_of(BasicStringView(&c, 1u), pos);
    }

    PHI_NODISCARD constexpr size_type find_first_not_of(const CharT* string,
                                                        size_type    pos = 0u) const noexcept
    {
        return find_first_not_of(BasicStringView(string), pos);
    }

    PHI_NODISCARD constexpr size_type find_first_not_of(const CharT* string, size_type pos,
                                                        size_type count) const noexcept
    {
        return find_first_not_of(BasicStringView(string, count), pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type
    find_last_not_of(BasicStringView view, size_type pos = npos) const noexcept
    {
        if (is_empty())
        {
            return npos;
        }

        if (pos >= size())
        {
            return find_last_not_of(view, size() - 1u);
        }

        return to_pos(std::find_if(const_reverse_iterator(cbegin() + pos + 1), crend(),
                                   not_in_view(view)));
    }

    PHI_NODISCARD constexpr size_type find_last_not_of(CharT c, size_type pos = npos) const noexcept
    {
        return find_last_not_of(BasicStringView(&c, 1u), pos);
    }

    PHI_NODISCARD constexpr size_type find_last_not_of(const CharT* string,
                                                       size_type    pos = npos) const noexcept
    {
        return find_last_not_of(BasicStringView(string), pos);
    }

    PHI_NODISCARD constexpr size_type find_last_not_of(const CharT* string, size_type pos,
                                                       size_type count) const noexcept
    {
        return find_last_not_of(BasicStringView(string, count), pos);
    }

private:
    struct not_in_view
    {
        const BasicStringView view;

        constexpr explicit not_in_view(BasicStringView other) noexcept
            : view(other)
        {}

        constexpr bool operator()(CharT c) const noexcept
        {
            return npos == view.find_first_of(c);
        }
    };

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference data_at(size_type pos) const noexcept
    {
        PHI_DBG_ASSERT(pos < size(), "Index out of bounds!");

        return m_Data[pos.get()];
    }

    PHI_NODISCARD constexpr size_type to_pos(const_iterator it) const noexcept
    {
        return it == cend() ? npos : size_type(it - cbegin());
    }

    PHI_NODISCARD constexpr size_type to_pos(const_reverse_iterator it) const noexcept
    {
        return it == crend() ? npos : size_type(crend() - it - 1);
    }

    const CharT* m_Data;
    usize        m_Size;
};

// Comparision functions

template <typename CharT, typename TraitsT>
constexpr Boolean operator==(BasicStringView<CharT, TraitsT> lhs,
                             BasicStringView<CharT, TraitsT> rhs) noexcept
{
    return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator!=(BasicStringView<CharT, TraitsT> lhs,
                             BasicStringView<CharT, TraitsT> rhs) noexcept
{
    return !(lhs == rhs);
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator<(BasicStringView<CharT, TraitsT> lhs,
                            BasicStringView<CharT, TraitsT> rhs) noexcept
{
    return lhs.compare(rhs) < 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator<=(BasicStringView<CharT, TraitsT> lhs,
                             BasicStringView<CharT, TraitsT> rhs) noexcept
{
    return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator>(BasicStringView<CharT, TraitsT> lhs,
                            BasicStringView<CharT, TraitsT> rhs) noexcept
{
    return lhs.compare(rhs) > 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator>=(BasicStringView<CharT, TraitsT> lhs,
                             BasicStringView<CharT, TraitsT> rhs) noexcept
{
    return lhs.compare(rhs) >= 0;
}

// ==

template <typename CharT, typename TraitsT>
constexpr Boolean operator==(BasicStringView<CharT, TraitsT> lhs, CharT const* rhs) noexcept
{
    return lhs.size() == StringLength(rhs) && lhs.compare(rhs) == 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator==(CharT const* lhs, BasicStringView<CharT, TraitsT> rhs) noexcept
{
    return StringLength(lhs) == rhs.size() && rhs.compare(lhs) == 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator==(BasicStringView<CharT, TraitsT>   lhs,
                             std::basic_string<CharT, TraitsT> rhs) noexcept
{
    return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator==(std::basic_string<CharT, TraitsT> rhs,
                             BasicStringView<CharT, TraitsT>   lhs) noexcept
{
    return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

// !=

template <typename CharT, typename TraitsT>
constexpr Boolean operator!=(BasicStringView<CharT, TraitsT> lhs, CharT const* rhs) noexcept
{
    return !(lhs == rhs);
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator!=(CharT const* lhs, BasicStringView<CharT, TraitsT> rhs) noexcept
{
    return !(lhs == rhs);
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator!=(BasicStringView<CharT, TraitsT>   lhs,
                             std::basic_string<CharT, TraitsT> rhs) noexcept
{
    return !(lhs == rhs);
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator!=(std::basic_string<CharT, TraitsT> rhs,
                             BasicStringView<CharT, TraitsT>   lhs) noexcept
{
    return !(lhs == rhs);
}

// <

template <typename CharT, typename TraitsT>
constexpr Boolean operator<(BasicStringView<CharT, TraitsT> lhs, CharT const* rhs) noexcept
{
    return lhs.compare(rhs) < 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator<(CharT const* lhs, BasicStringView<CharT, TraitsT> rhs) noexcept
{
    return rhs.compare(lhs) > 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator<(BasicStringView<CharT, TraitsT>   lhs,
                            std::basic_string<CharT, TraitsT> rhs) noexcept
{
    return lhs.compare(rhs) < 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator<(std::basic_string<CharT, TraitsT> rhs,
                            BasicStringView<CharT, TraitsT>   lhs) noexcept
{
    return rhs.compare(lhs) > 0;
}

// <=

template <typename CharT, typename TraitsT>
constexpr Boolean operator<=(BasicStringView<CharT, TraitsT> lhs, CharT const* rhs) noexcept
{
    return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator<=(CharT const* lhs, BasicStringView<CharT, TraitsT> rhs) noexcept
{
    return rhs.compare(lhs) >= 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator<=(BasicStringView<CharT, TraitsT>   lhs,
                             std::basic_string<CharT, TraitsT> rhs) noexcept
{
    return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator<=(std::basic_string<CharT, TraitsT> rhs,
                             BasicStringView<CharT, TraitsT>   lhs) noexcept
{
    return rhs.compare(lhs) >= 0;
}

// >

template <typename CharT, typename TraitsT>
constexpr Boolean operator>(BasicStringView<CharT, TraitsT> lhs, CharT const* rhs) noexcept
{
    return lhs.compare(rhs) > 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator>(CharT const* lhs, BasicStringView<CharT, TraitsT> rhs) noexcept
{
    return rhs.compare(lhs) < 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator>(BasicStringView<CharT, TraitsT>   lhs,
                            std::basic_string<CharT, TraitsT> rhs) noexcept
{
    return lhs.compare(rhs) > 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator>(std::basic_string<CharT, TraitsT> rhs,
                            BasicStringView<CharT, TraitsT>   lhs) noexcept
{
    return rhs.compare(lhs) < 0;
}

// >=

template <typename CharT, typename TraitsT>
constexpr Boolean operator>=(BasicStringView<CharT, TraitsT> lhs, CharT const* rhs) noexcept
{
    return lhs.compare(rhs) >= 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator>=(CharT const* lhs, BasicStringView<CharT, TraitsT> rhs) noexcept
{
    return rhs.compare(lhs) <= 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator>=(BasicStringView<CharT, TraitsT>   lhs,
                             std::basic_string<CharT, TraitsT> rhs) noexcept
{
    return lhs.compare(rhs) >= 0;
}

template <typename CharT, typename TraitsT>
constexpr Boolean operator>=(std::basic_string<CharT, TraitsT> rhs,
                             BasicStringView<CharT, TraitsT>   lhs) noexcept
{
    return rhs.compare(lhs) <= 0;
}

// Typedefs

using StringView    = BasicStringView<char>;
using WStringView   = BasicStringView<wchar_t>;
using U8StringView  = BasicStringView<char8_t>;
using U16StringView = BasicStringView<char16_t>;
using U32StringView = BasicStringView<char32_t>;

template <typename CharT, typename TraitsT>
constexpr size_t BasicStringView<CharT, TraitsT>::npos;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CONTAINER_STRING_VIEW_HPP
