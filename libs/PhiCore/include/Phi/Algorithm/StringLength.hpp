#ifndef INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP
#define INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP

#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Types.hpp"
#include "Phi/PhiConfig.hpp"
#include <cstddef>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT>
[[nodiscard]] constexpr usize StringLength(CharT* string) noexcept
{
    PHI_DBG_ASSERT(string != nullptr, "Passing nullptr to StringLength is not allowed. Use "
                                      "SafeStringLength if you intende to pass a nullptr.");

    usize count = 0u;
    for (; *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

template <typename CharT>
[[nodiscard]] constexpr usize StringLength(CharT* string, usize length) noexcept
{
    PHI_DBG_ASSERT(string != nullptr, "Passing nullptr to StringLength is not allowed. Use "
                                      "SafeStringLength if you intende to pass a nullptr.");

    usize count = 0u;
    for (; count < length && *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

template <typename CharT>
[[nodiscard]] constexpr usize SafeStringLength(CharT* string) noexcept
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

template <typename CharT>
[[nodiscard]] constexpr usize SafeStringLength(CharT* string, usize length) noexcept
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

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_STRING_LENGTH_HPP
