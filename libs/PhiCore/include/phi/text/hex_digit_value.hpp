#ifndef INCG_PHI_CORE_TEXT_HEX_DIGIT_VALUE_HPP
#define INCG_PHI_CORE_TEXT_HEX_DIGIT_VALUE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/types.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// Implementation comparison: https://godbolt.org/z/TejhY4nYW
// Stackoverflow https://stackoverflow.com/questions/34365746/whats-the-fastest-way-to-convert-hex-to-integer-in-c

namespace detail
{
    PHI_CLANG_SUPPRESS_WARNING_PUSH()
    PHI_CLANG_SUPPRESS_WARNING("-Wchar-subscripts")

    struct hex_digit_value_lookup_table
    {
        constexpr hex_digit_value_lookup_table() noexcept
            : m_Table{}
        {
            m_Table['0'] = 0;
            m_Table['1'] = 1;
            m_Table['2'] = 2;
            m_Table['3'] = 3;
            m_Table['4'] = 4;
            m_Table['5'] = 5;
            m_Table['6'] = 6;
            m_Table['7'] = 7;
            m_Table['8'] = 8;
            m_Table['9'] = 9;
            m_Table['a'] = 10;
            m_Table['A'] = 10;
            m_Table['b'] = 11;
            m_Table['B'] = 11;
            m_Table['c'] = 12;
            m_Table['C'] = 12;
            m_Table['d'] = 13;
            m_Table['D'] = 13;
            m_Table['e'] = 14;
            m_Table['E'] = 14;
            m_Table['f'] = 15;
            m_Table['F'] = 15;
        }

        PHI_CLANG_SUPPRESS_WARNING_POP()

        constexpr unsigned char operator[](char const index) const noexcept
        {
            // NOLINTNEXTLINE(bugprone-signed-char-misuse)
            return static_cast<unsigned char>(m_Table[static_cast<size_t>(index)]);
        }

    private:
        unsigned long long m_Table[103];
    };

    static constexpr hex_digit_value_lookup_table lookup_table;
} // namespace detail

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wsuggest-attribute=pure")

PHI_NODISCARD constexpr u8 hex_digit_value(const char character) noexcept
{
    PHI_ASSERT((character >= '0' && character <= '9') || (character >= 'a' && character <= 'f') ||
                       (character >= 'A' && character <= 'F'),
               "Character out of bounds");

    return detail::lookup_table[character];
}

PHI_GCC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // #ifndef INCG_PHI_CORE_TEXT_HEX_DIGIT_VALUE_HPP
