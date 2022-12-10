#ifndef INCG_PHI_FORWARD_STRING_VIEW_HPP
#define INCG_PHI_FORWARD_STRING_VIEW_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/char8_t.hpp"
#include "phi/forward/std/char_traits.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT, typename TraitsT = std::char_traits<CharT>>
class basic_string_view;

template <typename CharT, typename TraitsT = std::char_traits<CharT>>
class not_null_basic_string_view;

using string_view    = basic_string_view<char>;
using wstring_view   = basic_string_view<wchar_t>;
using u8string_view  = basic_string_view<char8_t>;
using u16string_view = basic_string_view<char16_t>;
using u32string_view = basic_string_view<char32_t>;

using not_null_string_view    = not_null_basic_string_view<char>;
using not_null_wstring_view   = not_null_basic_string_view<wchar_t>;
using not_null_u8string_view  = not_null_basic_string_view<char8_t>;
using not_null_u16string_view = not_null_basic_string_view<char16_t>;
using not_null_u32string_view = not_null_basic_string_view<char32_t>;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_FORWARD_STRING_VIEW_HPP
