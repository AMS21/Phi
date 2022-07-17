#ifndef INCG_PHI_CORE_TEXT_ASCII_CHAR_HPP
#define INCG_PHI_CORE_TEXT_ASCII_CHAR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/sized_types.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wtautological-unsigned-zero-compare")
PHI_CLANG_SUPPRESS_WARNING("-Wtautological-type-limit-compare")

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wtype-limits")
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4296) // '>=': expression is always true

class ascii_char
{
public:
    using this_type  = ascii_char;
    using value_type = unsigned char;

    // Constructor
    ascii_char() = default;

    ~ascii_char() = default;

    constexpr ascii_char(char character) noexcept
        : m_Char{static_cast<value_type>(character)}
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");
    }

    constexpr ascii_char(signed char character) noexcept
        : m_Char{static_cast<value_type>(character)}
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");
    }

    constexpr ascii_char(unsigned char character) noexcept
        : m_Char{static_cast<value_type>(character)}
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");
    }

#if PHI_HAS_FEATURE_CHAR8_T()
    constexpr ascii_char(char8_t character) noexcept
        : m_Char{static_cast<value_type>(character)}
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");
    }
#endif

    constexpr ascii_char(char16_t character) noexcept
        : m_Char{static_cast<value_type>(character)}
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");
    }

    constexpr ascii_char(char32_t character) noexcept
        : m_Char{static_cast<value_type>(character)}
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");
    }

    constexpr ascii_char(wchar_t character) noexcept
        : m_Char{static_cast<value_type>(character)}
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");
    }

    ascii_char(const ascii_char& other) = default;

    ascii_char(ascii_char&& other) = default;

    // Assignment operators
    constexpr ascii_char& operator=(char character) noexcept
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(character);

        return *this;
    }

    constexpr ascii_char& operator=(signed char character) noexcept
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(character);

        return *this;
    }

    constexpr ascii_char& operator=(unsigned char character) noexcept
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(character);

        return *this;
    }

#if PHI_HAS_FEATURE_CHAR8_T()
    constexpr ascii_char& operator=(char8_t character) noexcept
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(character);

        return *this;
    }
#endif

    constexpr ascii_char& operator=(char16_t character) noexcept
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(character);

        return *this;
    }

    constexpr ascii_char& operator=(char32_t character) noexcept
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(character);

        return *this;
    }

    constexpr ascii_char& operator=(wchar_t character) noexcept
    {
        PHI_ASSERT(character >= 0 && character <= 127, "Unrepresentable ascii character");

        m_Char = static_cast<value_type>(character);

        return *this;
    }

    ascii_char& operator=(const ascii_char& other) = default;

    ascii_char& operator=(ascii_char&& other) = default;

    // Conversion operators
    constexpr explicit operator bool() const noexcept
    {
        return m_Char != 0;
    }

    constexpr explicit operator boolean() const noexcept
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
    friend constexpr ascii_char operator+(const ascii_char& ascii_character) noexcept
    {
        return ascii_character;
    }

    friend constexpr ascii_char operator-(const ascii_char& ascii_character) noexcept
    {
        return ascii_char{static_cast<ascii_char::value_type>(-ascii_character.m_Char)};
    }

    friend constexpr ascii_char& operator++(ascii_char& ascii_character) noexcept
    {
        PHI_ASSERT(ascii_character.m_Char < 127,
                   "Pre-increment would result in unrepresentable ascii character");

        ascii_character.m_Char = static_cast<value_type>(ascii_character.m_Char + 1u);
        return ascii_character;
    }

    // NOLINTNEXTLINE(cert-dcl21-cpp)
    friend constexpr ascii_char operator++(ascii_char& ascii_character, int) noexcept
    {
        PHI_ASSERT(ascii_character.m_Char < 127,
                   "Post-increment would result in unrepresentable ascii character");

        ascii_char old_val     = ascii_character;
        ascii_character.m_Char = static_cast<value_type>(ascii_character.m_Char + 1u);
        return old_val;
    }

    friend constexpr ascii_char& operator--(ascii_char& ascii_character) noexcept
    {
        PHI_ASSERT(ascii_character.m_Char > 0,
                   "Pre-decrement would result in unrepresentable ascii character");

        ascii_character.m_Char = static_cast<value_type>(ascii_character.m_Char - 1u);
        return ascii_character;
    }

    // NOLINTNEXTLINE(cert-dcl21-cpp)
    friend constexpr ascii_char operator--(ascii_char& ascii_character, int) noexcept
    {
        PHI_ASSERT(ascii_character.m_Char > 0,
                   "Post-decrement would result in unrepresentable ascii character");

        ascii_char old_val     = ascii_character;
        ascii_character.m_Char = static_cast<value_type>(ascii_character.m_Char - 1u);
        return old_val;
    }

    // Binary operators
    friend constexpr ascii_char operator+(const ascii_char& lhs, const ascii_char& rhs) noexcept
    {
        PHI_ASSERT(static_cast<uint32_t>(lhs.m_Char) + rhs.m_Char < 127,
                   "Addition would result in unrepresentable ascii character");

        return ascii_char{static_cast<ascii_char::value_type>(lhs.m_Char + rhs.m_Char)};
    }

    friend constexpr ascii_char& operator+=(ascii_char& lhs, const ascii_char& rhs) noexcept
    {
        PHI_ASSERT(static_cast<uint32_t>(lhs.m_Char) + rhs.m_Char < 127,
                   "Addition would result in unrepresentable ascii character");

        lhs.m_Char = static_cast<value_type>(lhs.m_Char + rhs.m_Char);
        return lhs;
    }

    friend constexpr ascii_char operator-(const ascii_char& lhs, const ascii_char& rhs) noexcept
    {
        PHI_ASSERT(static_cast<uint32_t>(lhs.m_Char) - rhs.m_Char < 127,
                   "Addition would result in unrepresentable ascii character");

        return ascii_char{static_cast<ascii_char::value_type>(lhs.m_Char - rhs.m_Char)};
    }

    friend constexpr ascii_char& operator-=(ascii_char& lhs, const ascii_char& rhs) noexcept
    {
        PHI_ASSERT(static_cast<uint32_t>(lhs.m_Char) - rhs.m_Char < 127,
                   "Addition would result in unrepresentable ascii character");

        lhs.m_Char = static_cast<value_type>(lhs.m_Char - rhs.m_Char);
        return lhs;
    }

    // Comparison operator
    friend constexpr boolean operator==(const ascii_char& lhs, const ascii_char& rhs) noexcept
    {
        return lhs.m_Char == rhs.m_Char;
    }

    friend constexpr boolean operator!=(const ascii_char& lhs, const ascii_char& rhs) noexcept
    {
        return lhs.m_Char != rhs.m_Char;
    }

    friend constexpr boolean operator<(const ascii_char& lhs, const ascii_char& rhs) noexcept
    {
        return lhs.m_Char < rhs.m_Char;
    }

    friend constexpr boolean operator<=(const ascii_char& lhs, const ascii_char& rhs) noexcept
    {
        return lhs.m_Char <= rhs.m_Char;
    }

    friend constexpr boolean operator>(const ascii_char& lhs, const ascii_char& rhs) noexcept
    {
        return lhs.m_Char > rhs.m_Char;
    }

    friend constexpr boolean operator>=(const ascii_char& lhs, const ascii_char& rhs) noexcept
    {
        return lhs.m_Char >= rhs.m_Char;
    }

private:
    value_type m_Char;
};

PHI_CLANG_SUPPRESS_WARNING_POP()
PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_GCC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_ASCII_CHAR_HPP
