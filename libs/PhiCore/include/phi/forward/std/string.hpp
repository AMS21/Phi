#ifndef INCG_PHI_FORWARD_STD_STRING_HPP
#define INCG_PHI_FORWARD_STD_STRING_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/char8_t.hpp"
#include "phi/compiler_support/standard_library.hpp"
#include "phi/forward/std/allocator.hpp"
#include "phi/forward/std/char_traits.hpp"

DETAIL_PHI_BEGIN_STD_NAMESPACE()

#if PHI_STANDARD_LIBRARY_LIBSTDCXX()

// For some reason the '_GLIBCXX_BEGIN_NAMESPACE_CXX11' macro doesn't reopen the namespace as inline although it actually is
// We fix that manully here to avoid the gcc warning
// "inline namespace reopened as a non-inline namespace [-Winline-namespace-reopened-noninline]"
// See https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/c%2B%2Bconfig#L328
// And https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/c%2B%2Bconfig#L338
// for context.
#    if _GLIBCXX_USE_CXX11_ABI
inline
#    endif
        _GLIBCXX_BEGIN_NAMESPACE_CXX11

#endif

        // TODO: Figure out a good way to provide the default arguments here

        template <typename CharT, typename TraitsT /*= char_traits<CharT>*/,
                  typename AllocT /*= allocator<CharT>*/>
        class basic_string;

#if PHI_STANDARD_LIBRARY_LIBSTDCXX()

_GLIBCXX_END_NAMESPACE_CXX11

#endif

using string    = basic_string<char, char_traits<char>, allocator<char>>;
using wstring   = basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t>>;
using u8string  = basic_string<char8_t, char_traits<char8_t>, allocator<char8_t>>;
using u16string = basic_string<char16_t, char_traits<char16_t>, allocator<char16_t>>;
using u32string = basic_string<char32_t, char_traits<char32_t>, allocator<char32_t>>;

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_FORWARD_STD_STRING_HPP
