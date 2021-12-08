#ifndef INCG_PHI_CORE_TEXT_CHAR_TRAITS_HPP
#define INCG_PHI_CORE_TEXT_CHAR_TRAITS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include <iosfwd>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT>
class char_traits
{
public:
    using this_type  = char_traits<CharT>;
    using char_type  = CharT;
    using int_type   = int;
    using off_type   = std::streamoff;
    using pos_type   = std::streampos;
    using state_type = mbstate_t;

    static constexpr inline void assign(char_type& lhs, const char_type& rhs) noexcept
    {
        lhs = rhs;
    }

    static constexpr inline bool eq(char_type lhs, char_type rhs) noexcept
    {
        return lhs == rhs;
    }

    static constexpr inline bool ne(char_type lhs, char_type rhs) noexcept
    {
        return lhs != rhs;
    }

    static constexpr inline bool lt(char_type lhs, char_type rhs) noexcept
    {
        return lhs < rhs;
    }

    static constexpr inline bool le(char_type lhs, char_type rhs) noexcept
    {
        return lhs <= rhs;
    }

    static constexpr inline bool gt(char_type lhs, char_type rhs) noexcept
    {
        return lhs > rhs;
    }

    static constexpr inline bool ge(char_type lhs, char_type rhs) noexcept
    {
        return lhs >= rhs;
    }
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_CHAR_TRAITS_HPP
