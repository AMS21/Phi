#ifndef INCG_PHI_CORE_TEXT_ASCII_CHAR_HPP
#define INCG_PHI_CORE_TEXT_ASCII_CHAR_HPP

#include "Phi/Core/FlatPtr.hpp"
#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

class ascii_char
{
public:
    using this_type  = ascii_char;
    using value_type = unsigned char;

    // Constructor
    ascii_char() = default;

    constexpr ascii_char(char c) noexcept
        : m_Char{static_cast<value_type>(c)}
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");
    }

    constexpr ascii_char(signed char c) noexcept
        : m_Char{static_cast<value_type>(c)}
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");
    }

    constexpr ascii_char(unsigned char c) noexcept
        : m_Char{static_cast<value_type>(c)}
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");
    }

#if PHI_HAS_FEATURE_CHAR8_T()
    constexpr ascii_char(char8_t c) noexcept
        : m_Char{static_cast<value_type>(c)}
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");
    }
#endif

    constexpr ascii_char(char16_t c) noexcept
        : m_Char{static_cast<value_type>(c)}
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");
    }

    constexpr ascii_char(char32_t c) noexcept
        : m_Char{static_cast<value_type>(c)}
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");
    }

    constexpr ascii_char(wchar_t c) noexcept
        : m_Char{static_cast<value_type>(c)}
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");
    }

    ascii_char(const ascii_char& other) = default;

    ascii_char(ascii_char&& other) = default;

    // Assignment operators
    constexpr ascii_char& operator=(char c) noexcept
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(c);

        return *this;
    }

    constexpr ascii_char& operator=(signed char c) noexcept
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(c);

        return *this;
    }

    constexpr ascii_char& operator=(unsigned char c) noexcept
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(c);

        return *this;
    }

#if PHI_HAS_FEATURE_CHAR8_T()
    constexpr ascii_char& operator=(char8_t c) noexcept
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(c);

        return *this;
    }
#endif

    constexpr ascii_char& operator=(char16_t c) noexcept
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(c);

        return *this;
    }

    constexpr ascii_char& operator=(char32_t c) noexcept
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(c);

        return *this;
    }

    constexpr ascii_char& operator=(wchar_t c) noexcept
    {
        PHI_DBG_ASSERT(c >= 0 && c <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(c);

        return *this;
    }

    ascii_char& operator=(const ascii_char& other) = default;

    ascii_char& operator=(ascii_char&& other) = default;

    // Conversion operators
    constexpr explicit operator bool() const noexcept
    {
        return m_Char != 0;
    }

    constexpr explicit operator Boolean() const noexcept
    {
        return m_Char != 0;
    }

    constexpr explicit operator char() const noexcept
    {
        return static_cast<char>(m_Char);
    }

    constexpr explicit operator signed char() const noexcept
    {
        return static_cast<signed char>(m_Char);
    }

    constexpr explicit operator unsigned char() const noexcept
    {
        return static_cast<unsigned char>(m_Char);
    }

#if PHI_HAS_FEATURE_CHAR8_T()
    constexpr explicit operator char8_t() const noexcept
    {
        return static_cast<char8_t>(m_Char);
    }
#endif

    constexpr explicit operator char16_t() const noexcept
    {
        return static_cast<char16_t>(m_Char);
    }

    constexpr explicit operator char32_t() const noexcept
    {
        return static_cast<char32_t>(m_Char);
    }

    constexpr explicit operator wchar_t() const noexcept
    {
        return static_cast<wchar_t>(m_Char);
    }

    // Arithmetic operators
    // Unary operators
    friend constexpr ascii_char operator+(const ascii_char& ac) noexcept
    {
        return ac;
    }

    friend ascii_char operator-(const ascii_char& ac) = delete;

    friend constexpr ascii_char& operator++(ascii_char& ac) noexcept
    {
        PHI_DBG_ASSERT(ac.m_Char < 127,
                       "Increment would result in unrepresentable ascii character");

        ac.m_Char += 1;
        return ac;
    }

    friend constexpr ascii_char& operator--(ascii_char& ac) noexcept
    {
        PHI_DBG_ASSERT(ac.m_Char > 0,
                       "Decrement would result in unrepresentable asci000i character");

        ac.m_Char -= 1;
        return ac;
    }

    // Binary operators

private:
    value_type m_Char;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_ASCII_CHAR_HPP
