#ifndef INCG_PHI_FORWARD_STD_CHAR_TRAITS_HPP
#define INCG_PHI_FORWARD_STD_CHAR_TRAITS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/char8_t.hpp"
#include "phi/compiler_support/standard_library.hpp"

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <typename CharT>
struct char_traits;

template <>
struct char_traits<char>;
template <>
struct char_traits<wchar_t>;
template <>
struct char_traits<char8_t>;
template <>
struct char_traits<char16_t>;
template <>
struct char_traits<char32_t>;

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_FORWARD_STD_CHAR_TRAITS_HPP
