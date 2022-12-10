#ifndef INCG_PHI_FORWARD_STD_STRING_VIEW_HPP
#define INCG_PHI_FORWARD_STD_STRING_VIEW_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/char8_t.hpp"
#include "phi/compiler_support/standard_library.hpp"
#include "phi/forward/std/char_traits.hpp"

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <typename CharT, typename TraitsT /*= char_traits<CharT>*/>
class basic_string_view;

// Type aliases
using string_view    = basic_string_view<char, char_traits<char>>;
using wstring_view   = basic_string_view<wchar_t, char_traits<wchar_t>>;
using u8string_view  = basic_string_view<char8_t, char_traits<char8_t>>;
using u16string_view = basic_string_view<char16_t, char_traits<char16_t>>;
using u32string_view = basic_string_view<char32_t, char_traits<char32_t>>;

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_FORWARD_STD_STRING_VIEW_HPP
