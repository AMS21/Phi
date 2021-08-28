#ifndef INCG_PHI_CORE_ALGORITHM_STRING_COMPARE_HPP
#define INCG_PHI_CORE_ALGORITHM_STRING_COMPARE_HPP

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Types.hpp"
#include "Phi/PhiConfig.hpp"
#include <cstddef>
#include <functional>
#include <type_traits>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT>
PHI_NODISCARD constexpr i32 StringCompare(const CharT* lhs, const CharT* rhs) noexcept
{
    PHI_DBG_ASSERT(lhs != nullptr, "May not pass nullptr to StringCompare");
    PHI_DBG_ASSERT(rhs != nullptr, "May not pass nullptr to StringCompare");

    while (*lhs != CharT('\0') && (*lhs == *rhs))
    {
        ++lhs;
        ++rhs;
    }

    using SignedCharT = typename std::make_signed<CharT>::type;

    return static_cast<std::int32_t>(*static_cast<SignedCharT>(lhs) -
                                     *static_cast<SignedCharT>(rhs));
}

template <typename CharT>
PHI_NODISCARD constexpr i32 StringCompare(const CharT*, std::nullptr_t) noexcept = delete;

template <typename CharT>
PHI_NODISCARD constexpr i32 StringCompare(std::nullptr_t, const CharT*) noexcept = delete;

template <typename CharT>
PHI_NODISCARD constexpr i32 StringCompare(const CharT* lhs, const CharT* rhs, usize count) noexcept
{
    PHI_DBG_ASSERT(lhs != nullptr, "May not pass nullptr to StringCompare");
    PHI_DBG_ASSERT(rhs != nullptr, "May not pass nullptr to StringCompare");

    while (*lhs != CharT('\0') && (*lhs == *rhs) && (count-- > 0u))
    {
        ++lhs;
        ++rhs;
    }

    using SignedCharT = typename std::make_signed<CharT>::type;

    return static_cast<std::int32_t>(*static_cast<SignedCharT>(lhs) -
                                     *static_cast<SignedCharT>(rhs));
}

template <typename CharT>
PHI_NODISCARD constexpr i32 StringCompare(const CharT*, std::nullptr_t, usize) noexcept = delete;

template <typename CharT>
PHI_NODISCARD constexpr i32 StringCompare(std::nullptr_t, const CharT*, usize) noexcept = delete;

template <typename CharT>
PHI_NODISCARD constexpr i32 SafeStringCompare(const CharT* lhs, const CharT* rhs) noexcept
{
    if (lhs == nullptr)
    {
        if (rhs == nullptr)
        {
            return 0;
        }

        return -1;
    }
    if (rhs == nullptr)
    {
        return 1;
    }

    while (*lhs != CharT('\0') && (*lhs == *rhs))
    {
        ++lhs;
        ++rhs;
    }

    using SignedCharT = typename std::make_signed<CharT>::type;

    return static_cast<std::int32_t>(*static_cast<SignedCharT>(lhs) -
                                     *static_cast<SignedCharT>(rhs));
}

template <typename CharT>
PHI_NODISCARD constexpr i32 SafeStringCompare(const CharT* lhs, std::nullptr_t) noexcept
{
    if (lhs == nullptr)
    {
        return 0;
    }

    return -1;
}

template <typename CharT>
PHI_NODISCARD constexpr i32 SafeStringCompare(std::nullptr_t, const CharT* rhs) noexcept
{
    if (rhs == nullptr)
    {
        return 0;
    }

    return 1;
}

template <typename CharT>
PHI_NODISCARD constexpr i32 SafeStringCompare(const CharT* lhs, const CharT* rhs,
                                              usize count) noexcept
{
    if (lhs == nullptr)
    {
        if (rhs == nullptr)
        {
            return 0;
        }
        return -1;
    }
    if (rhs == nullptr)
    {
        return 1;
    }

    while (*lhs != CharT('\0') && (*lhs == *rhs) && (count-- > 0u))
    {
        ++lhs;
        ++rhs;
    }

    using SignedCharT = typename std::make_signed<CharT>::type;

    return static_cast<std::int32_t>(*static_cast<SignedCharT>(lhs) -
                                     *static_cast<SignedCharT>(rhs));
}

template <typename CharT>
PHI_NODISCARD constexpr i32 SafeStringCompare(const CharT* lhs, std::nullptr_t, usize size) noexcept
{
    PHI_UNUSED_PARAMETER(size);

    if (lhs == nullptr)
    {
        return 0;
    }

    return -1;
}

template <typename CharT>
PHI_NODISCARD constexpr i32 SafeStringCompare(std::nullptr_t, const CharT* rhs, usize size) noexcept
{
    PHI_UNUSED_PARAMETER(size);

    if (rhs == nullptr)
    {
        return 0;
    }

    return 1;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_STRING_COMPARE_HPP
