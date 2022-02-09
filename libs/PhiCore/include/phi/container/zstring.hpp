#ifndef INCG_PHI_CORE_CONTAINER_ZSTRING_HPP
#define INCG_PHI_CORE_CONTAINER_ZSTRING_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/min.hpp"
#include "phi/algorithm/string_length.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/types.hpp"
#include "phi/type_traits/is_array.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/is_standard_layout.hpp"
#include "phi/type_traits/is_trivial.hpp"
#include <string>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT, typename TraitsT = std::char_traits<CharT>>
class basic_zstring
{
public:
    using this_type              = basic_zstring<CharT, TraitsT>;
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
    static_assert(is_not_array<value_type>::value,
                  "phi::basic_zstring: Character type must not be an array");
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    static_assert(is_standard_layout<value_type>::value,
                  "phi::basic_zstring: Character type must be standard-layout");
#endif
#if PHI_HAS_WORKING_IS_TRIVIAL()
    static_assert(is_trivial<value_type>::value,
                  "phi::basic_zstring: Character type must be trivial");
#endif
    static_assert(is_same<value_type, typename traits_type::char_type>::value,
                  "phi::basic_zstring: CharT must be the same type as traits_type::char_type");

    static constexpr size_t npos = std::numeric_limits<size_t>::max();

    // Constructors
    constexpr basic_zstring() noexcept
        : m_Data(nullptr)
    {}

    constexpr basic_zstring(const basic_zstring& other) noexcept = default;

    constexpr basic_zstring(basic_zstring&& other) noexcept = default;

    PHI_EXTENDED_CONSTEXPR basic_zstring(const CharT* string) noexcept
        : m_Data(string)
    {
        PHI_DBG_ASSERT(string != nullptr, "Do not construct a basic_zstring with nullptr");
    }

    basic_zstring(nullptr_t) = delete;

    ~basic_zstring() = default;

    PHI_EXTENDED_CONSTEXPR basic_zstring& operator=(const basic_zstring& other) noexcept = default;

    PHI_EXTENDED_CONSTEXPR basic_zstring& operator=(basic_zstring&& other) noexcept = default;

    basic_zstring& operator=(nullptr_t) = delete;

    // Iterators

    PHI_NODISCARD constexpr iterator begin() const noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr iterator end() const noexcept
    {
        return m_Data + string_length(m_Data);
    }

    PHI_NODISCARD constexpr const_iterator cbegin() const noexcept
    {
        return m_Data;
    }

    PHI_NODISCARD constexpr const_iterator cend() const noexcept
    {
        return m_Data + string_length(m_Data);
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

    PHI_NODISCARD constexpr size_type length() const noexcept
    {
        return string_length(m_Data);
    }

    PHI_NODISCARD constexpr size_type max_length() const noexcept
    {
        return std::numeric_limits<size_type>::max();
    }

    PHI_NODISCARD constexpr boolean is_empty() const noexcept
    {
        return m_Data != '\0';
    }

    PHI_NODISCARD constexpr boolean is_null() const noexcept
    {
        return m_Data == nullptr;
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
        return data_at(length() - 1u);
    }

    PHI_NODISCARD constexpr const_pointer data() const noexcept
    {
        return m_Data;
    }

    // Modifiers

    PHI_EXTENDED_CONSTEXPR basic_zstring& clear() noexcept
    {
        m_Data = nullptr;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR void swap(basic_zstring& other) noexcept
    {
        const basic_zstring tmp(other);
        other = *this;
        *this = tmp;
    }

    // String operations

    PHI_EXTENDED_CONSTEXPR size_type copy(CharT* destination, size_type count,
                                          size_type pos = 0u) const noexcept
    {
        PHI_DBG_ASSERT(pos <= length(), "Invalid position");

        const size_type rlen = min(count, length() - pos);
        TraitsT::copy(destination, data() + pos.get(), rlen.get());

        return rlen;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR basic_zstring substr(size_type pos   = 0u,
                                                              size_type count = npos) const noexcept
    {
        PHI_DBG_ASSERT(pos <= length(), "Invalid position");

        return basic_zstring(data() + pos.get(), min(count, length() - pos));
    }

    // Comparing

    PHI_NODISCARD constexpr i32 compare(basic_zstring other) const noexcept
    {
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
        {
            const i32 result = TraitsT::compare(data(), other.data(),
                                                min(length().get(), other.length().get()));

            if (result != 0)
            {
                return result;
            }
        }

        return length() == other.length() ? 0 : length() < other.length() ? -1 : 1;

#else

        // Ugly C++-11 compatible version of the same code
        return TraitsT::compare(data(), other.data(), min(length().get(), other.length().get())) !=
                               0 ?
                       TraitsT::compare(data(), other.data(),
                                        min(length().get(), other.length().get())) :
               length() == other.length() ? 0 :
               length() < other.length()  ? -1 :
                                            1;

#endif
    }

    PHI_NODISCARD constexpr i32 compare(size_type pos, size_type count,
                                        basic_zstring other) const noexcept
    {
        return substr(pos, count).compare(other);
    }

    PHI_NODISCARD constexpr i32 compare(size_type pos1, size_type count1, basic_zstring other,
                                        size_type pos2, size_type count2) const noexcept
    {
        return substr(pos1, count1).compare(other.substr(pos2, count2));
    }

    PHI_NODISCARD constexpr i32 compare(const CharT* string) const noexcept
    {
        return compare(basic_zstring(string));
    }

    PHI_NODISCARD constexpr i32 compare(size_type pos, size_type count,
                                        const CharT* string) const noexcept
    {
        return substr(pos, count).compare(basic_zstring(string));
    }

    PHI_NODISCARD constexpr i32 compare(size_type pos, size_type count1, const CharT* string,
                                        size_type count2) const noexcept
    {
        return substr(pos, count1).compare(basic_zstring(string, count2));
    }

    // Searching

    PHI_NODISCARD constexpr boolean starts_with(basic_zstring view) const noexcept
    {
        return length() >= view.length() && compare(0u, view.length(), view) == 0;
    }

    PHI_NODISCARD constexpr boolean starts_with(CharT c) const noexcept
    {
        return starts_with(basic_zstring(&c, 1u));
    }

    PHI_NODISCARD constexpr boolean starts_with(const CharT* string) const noexcept
    {
        return starts_with(basic_zstring(string));
    }

    PHI_NODISCARD constexpr boolean ends_with(basic_zstring view) const noexcept
    {
        return length() >= view.length() && compare(length() - view.length(), npos, view) == 0;
    }

    PHI_NODISCARD constexpr boolean ends_with(CharT c) const noexcept
    {
        return ends_with(basic_zstring(&c, 1u));
    }

    PHI_NODISCARD constexpr boolean ends_with(const CharT* string) const noexcept
    {
        return ends_with(basic_zstring(string));
    }

    // contains

    PHI_NODISCARD constexpr boolean contains(basic_zstring view) const noexcept
    {
        return find(view) != npos;
    }

    PHI_NODISCARD constexpr boolean contains(CharT c) const noexcept
    {
        return find(c) != npos;
    }

    PHI_NODISCARD constexpr boolean contains(const CharT* string) const noexcept
    {
        return find(string) != npos;
    }

    // find

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type find(basic_zstring view,
                                                        size_type     pos = 0u) const noexcept
    {
        PHI_DBG_ASSERT(view.length() == 0u || view.data() != nullptr, "Invalid argument view");

        return pos >= length() ? npos :
                                 to_pos(std::search(cbegin() + pos, cend(), view.cbegin(),
                                                    view.cend(), TraitsT::eq));
    }

    PHI_NODISCARD constexpr size_type find(CharT c, size_type pos = 0u) const noexcept
    {
        return find(basic_zstring(&c, 1u), pos);
    }

    PHI_NODISCARD constexpr size_type find(const CharT* string, size_type pos = 0u) const noexcept
    {
        return find(basic_zstring(string), pos);
    }

    PHI_NODISCARD constexpr size_type find(const CharT* string, size_type pos,
                                           size_type count) const noexcept
    {
        return find(basic_zstring(string, count), pos);
    }

    // rfind

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type rfind(basic_zstring view,
                                                         size_type     pos = npos) const noexcept
    {
        if (length() < view.length())
        {
            return npos;
        }

        if (view.empty())
        {
            return min(length(), pos);
        }

        const_iterator last = cbegin() + min(length() - view.length(), pos) + view.length();
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
        return rfind(basic_zstring(&c, 1u), pos);
    }

    PHI_NODISCARD constexpr size_type rfind(const CharT* string,
                                            size_type    pos = npos) const noexcept
    {
        return rfind(basic_zstring(string), pos);
    }

    PHI_NODISCARD constexpr size_type rfind(const CharT* string, size_type pos,
                                            size_type count) const noexcept
    {
        return rfind(basic_zstring(string, count), pos);
    }

    PHI_NODISCARD constexpr size_type find_first_of(basic_zstring view,
                                                    size_type     pos = 0u) const noexcept
    {
        return pos >= length() ? npos :
                                 to_pos(std::find_first_of(cbegin() + pos, cend(), view.cbegin(),
                                                           view.cend(), TraitsT::eq));
    }

    PHI_NODISCARD constexpr size_type find_first_of(CharT c, size_type pos = 0u) const noexcept
    {
        return find_first_of(basic_zstring(&c, 1u), pos);
    }

    PHI_NODISCARD constexpr size_type find_first_of(const CharT* string,
                                                    size_type    pos = 0u) const noexcept
    {
        return find_first_of(basic_zstring(string), pos);
    }

    PHI_NODISCARD constexpr size_type find_first_of(const CharT* string, size_type pos,
                                                    size_type count) const noexcept
    {
        return find_first_of(basic_zstring(string, count), pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type find_last_of(basic_zstring view,
                                                                size_type pos = npos) const noexcept
    {
        if (is_empty())
        {
            return npos;
        }

        if (pos >= length())
        {
            return find_last_of(view, length() - 1);
        }

        return to_pos(std::find_first_of(const_reverse_iterator(cbegin() + pos + 1), crend(),
                                         view.cbegin(), view.cend(), TraitsT::eq));
    }

    PHI_NODISCARD constexpr size_type find_last_of(CharT c, size_type pos = npos) const noexcept
    {
        return find_last_of(basic_zstring(&c, 1u), pos);
    }

    PHI_NODISCARD constexpr size_type find_last_of(const CharT* string,
                                                   size_type    pos = npos) const noexcept
    {
        return find_last_of(basic_zstring(string), pos);
    }

    PHI_NODISCARD constexpr size_type find_last_of(const CharT* string, size_type pos,
                                                   size_type count) const noexcept
    {
        return find_last_of(basic_zstring(string, count), pos);
    }

    PHI_NODISCARD constexpr size_type find_first_not_of(basic_zstring view,
                                                        size_type     pos = 0u) const noexcept
    {
        return pos >= length() ? npos :
                                 to_pos(std::find_if(cbegin() + pos, cend(), not_in_view(view)));
    }

    PHI_NODISCARD constexpr size_type find_first_not_of(CharT c, size_type pos = 0u) const noexcept
    {
        return find_first_not_of(basic_zstring(&c, 1u), pos);
    }

    PHI_NODISCARD constexpr size_type find_first_not_of(const CharT* string,
                                                        size_type    pos = 0u) const noexcept
    {
        return find_first_not_of(basic_zstring(string), pos);
    }

    PHI_NODISCARD constexpr size_type find_first_not_of(const CharT* string, size_type pos,
                                                        size_type count) const noexcept
    {
        return find_first_not_of(basic_zstring(string, count), pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type
    find_last_not_of(basic_zstring view, size_type pos = npos) const noexcept
    {
        if (is_empty())
        {
            return npos;
        }

        if (pos >= length())
        {
            return find_last_not_of(view, length() - 1u);
        }

        return to_pos(std::find_if(const_reverse_iterator(cbegin() + pos + 1), crend(),
                                   not_in_view(view)));
    }

    PHI_NODISCARD constexpr size_type find_last_not_of(CharT c, size_type pos = npos) const noexcept
    {
        return find_last_not_of(basic_zstring(&c, 1u), pos);
    }

    PHI_NODISCARD constexpr size_type find_last_not_of(const CharT* string,
                                                       size_type    pos = npos) const noexcept
    {
        return find_last_not_of(basic_zstring(string), pos);
    }

    PHI_NODISCARD constexpr size_type find_last_not_of(const CharT* string, size_type pos,
                                                       size_type count) const noexcept
    {
        return find_last_not_of(basic_zstring(string, count), pos);
    }

private:
    struct not_in_view
    {
        const basic_zstring view;

        constexpr explicit not_in_view(basic_zstring other) noexcept
            : view(other)
        {}

        constexpr bool operator()(CharT c) const noexcept
        {
            return npos == view.find_first_of(c);
        }
    };

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference data_at(size_type pos) const noexcept
    {
        PHI_DBG_ASSERT(pos < length(), "Index out of bounds!");

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

    CharT* m_Data;
};

using zstring    = basic_zstring<char>;
using wzstring   = basic_zstring<wchar_t>;
using u8zstring  = basic_zstring<char8_t>;
using u16zstring = basic_zstring<char16_t>;
using u32zstring = basic_zstring<char32_t>;

template <typename CharT, typename TraitsT>
constexpr size_t basic_zstring<CharT, TraitsT>::npos;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CONTAINER_ZSTRING_HPP
