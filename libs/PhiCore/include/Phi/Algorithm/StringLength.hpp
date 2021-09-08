#ifndef INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP
#define INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/CPlusPlus.hpp"
#include "Phi/Config/Compiler.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Types.hpp"
#include "Phi/Math/Common.hpp"
#include <cstddef>
#include <string>

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
#    if PHI_COMPILER_IS_ATLEAST(CLANG, 4, 0, 0) || PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 10, 0)
#        define PHI_HAS_LIB_STRING_VIEW() 1
#    else
#        define PHI_HAS_LIB_STRING_VIEW() 0
#    endif
#else
#    define PHI_HAS_LIB_STRING_VIEW() 0
#endif

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

template <typename CharT = std::nullptr_t>
PHI_NODISCARD constexpr usize StringLength(std::nullptr_t) noexcept = delete;

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

template <typename CharT = std::nullptr_t>
PHI_NODISCARD constexpr usize StringLength(std::nullptr_t, usize) noexcept = delete;

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

template <typename CharT = std::nullptr_t>
PHI_NODISCARD constexpr usize SafeStringLength(std::nullptr_t) noexcept
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

template <typename CharT = std::nullptr_t>
PHI_NODISCARD constexpr usize SafeStringLength(std::nullptr_t, usize length) noexcept
{
    PHI_UNUSED_PARAMETER(length);

    return 0u;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP
