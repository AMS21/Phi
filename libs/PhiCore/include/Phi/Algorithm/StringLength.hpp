#ifndef INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP
#define INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/CPlusPlus.hpp"
#include "Phi/Config/Compiler.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Nullptr.hpp"
#include "Phi/Core/Types.hpp"
#include "Phi/Math/Common.hpp"
#include <string>

#if PHI_HAS_LIB_STRING_VIEW()
#    include <string_view>
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT>
PHI_NODISCARD constexpr usize StringLength(CharT* string) noexcept
{
    PHI_DBG_ASSERT(string != nullptr, "Passing nullptr to StringLength is not allowed. Use "
                                      "SafeStringLength if you intended to pass a nullptr.");

    usize count = 0u;
    for (; *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr usize StringLength(
        std::basic_string<CharT, TraitsT, AllocatorT> string) noexcept
{
    return string.length();
}

#if PHI_HAS_LIB_STRING_VIEW()
template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr usize StringLength(std::basic_string_view<CharT, TraitsT> string) noexcept
{
    return string.length();
}
#endif

template <typename CharT = nullptr_t>
PHI_NODISCARD constexpr usize StringLength(nullptr_t) noexcept = delete;

template <typename CharT>
PHI_NODISCARD constexpr usize StringLength(CharT* string, usize length) noexcept
{
    PHI_DBG_ASSERT(string != nullptr, "Passing nullptr to StringLength is not allowed. Use "
                                      "SafeStringLength if you intended to pass a nullptr.");

    usize count = 0u;
    for (; count < length && *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr usize StringLength(std::basic_string<CharT, TraitsT, AllocatorT> string,
                                           usize length) noexcept
{
    return min(usize(string.length()), length);
}

#if PHI_HAS_LIB_STRING_VIEW()
template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr usize StringLength(std::basic_string_view<CharT, TraitsT> string,
                                           usize                                  length) noexcept
{
    return min(usize(string.length()), length);
}
#endif

template <typename CharT = nullptr_t>
PHI_NODISCARD constexpr usize StringLength(nullptr_t, usize) noexcept = delete;

template <typename CharT>
PHI_NODISCARD constexpr usize SafeStringLength(CharT* string) noexcept
{
    if (string == nullptr)
    {
        return 0u;
    }

    usize count = 0u;
    for (; *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr usize SafeStringLength(
        std::basic_string<CharT, TraitsT, AllocatorT> string) noexcept
{
    return string.length();
}

#if PHI_HAS_LIB_STRING_VIEW()
template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr usize SafeStringLength(
        std::basic_string_view<CharT, TraitsT> string) noexcept
{
    return string.length();
}
#endif

template <typename CharT = nullptr_t>
PHI_NODISCARD constexpr usize SafeStringLength(nullptr_t) noexcept
{
    return 0u;
}

template <typename CharT>
PHI_NODISCARD constexpr usize SafeStringLength(CharT* string, usize length) noexcept
{
    if (string == nullptr)
    {
        return 0u;
    }

    usize count = 0u;
    for (; count < length && *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD constexpr usize SafeStringLength(std::basic_string<CharT, TraitsT, AllocatorT> string,
                                               usize length) noexcept
{
    return min(usize(string.length()), length);
}

#if PHI_HAS_LIB_STRING_VIEW()
template <typename CharT, typename TraitsT>
PHI_NODISCARD constexpr usize SafeStringLength(std::basic_string_view<CharT, TraitsT> string,
                                               usize length) noexcept
{
    return min(usize(string.length()), length);
}
#endif

template <typename CharT = nullptr_t>
PHI_NODISCARD constexpr usize SafeStringLength(nullptr_t, usize length) noexcept
{
    PHI_UNUSED_PARAMETER(length);

    return 0u;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP
