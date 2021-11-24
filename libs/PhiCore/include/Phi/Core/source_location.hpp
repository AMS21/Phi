#ifndef INCG_PHI_CORE_SOURCE_LOCATION_HPP
#define INCG_PHI_CORE_SOURCE_LOCATION_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/Container/StringView.hpp"
#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/TypeTraits/false_t.hpp"
#include <cstdint>

DETAIL_PHI_BEGIN_NAMESPACE()

struct source_location
{
    using this_type = source_location;

    constexpr source_location() noexcept
        : m_FileName{""}
        , m_FunctionName(m_FileName)
        , m_LineNumber(0)
        , m_Column(0)
    {}

    constexpr source_location(const char* file, const char* function, std::uint_least32_t line,
                              std::uint_least32_t column) noexcept
        : m_FileName(file)
        , m_FunctionName(function)
        , m_LineNumber(line)
        , m_Column(column)
    {
        PHI_DBG_ASSERT(file != nullptr, "Don't pass nullptr to phi::source_location");
        PHI_DBG_ASSERT(function != nullptr, "Don't pass nullptr to phi::source_location");
    }

#if PHI_HAS_INTRINSIC_BUILTIN_FILE() && PHI_HAS_INTRINSIC_BUILTIN_FUNCTION() &&                    \
        PHI_HAS_INTRINSIC_BUILTIN_LINE()
    static constexpr source_location current(const char*         file     = __builtin_FILE(),
                                             const char*         function = __builtin_FUNCTION(),
                                             std::uint_least32_t line     = __builtin_LINE()
#    if PHI_HAS_INTRINSIC_BUILTIN_COLUMN()
                                                     ,
                                             std::uint_least32_t column = __builtin_COLUMN()
#    endif
                                                     ) noexcept
    {
        source_location location
        {
            file, function, line,
#    if PHI_HAS_INTRINSIC_BUILTIN_COLUMN()
                    column
#    else
                    0
#    endif
        };

        return location;
    }
#else
    template <typename TypeT = void>
    static constexpr source_location current() noexcept
    {
        static_assert(false_t<TypeT>::value,
                      "phi::source_location requires compiler support for current.");

        source_location loc;
        return loc;
    }
#endif

    [[nodiscard]] constexpr uint_least32_t line() const noexcept
    {
        return m_LineNumber;
    }

    [[nodiscard]] constexpr uint_least32_t column() const noexcept
    {
        return m_Column;
    }

    [[nodiscard]] constexpr const char* file_name() const noexcept
    {
        return m_FileName;
    }

    [[nodiscard]] constexpr StringView file_name_view() const noexcept
    {
        return m_FileName;
    }

    [[nodiscard]] constexpr const char* function_name() const noexcept
    {
        return m_FunctionName;
    }

    [[nodiscard]] constexpr StringView function_name_view() const noexcept
    {
        return m_FunctionName;
    }

private:
    const char*         m_FileName;
    const char*         m_FunctionName;
    std::uint_least32_t m_LineNumber;
    std::uint_least32_t m_Column;
};

#if PHI_HAS_INTRINSIC_BUILTIN_FILE() && PHI_HAS_INTRINSIC_BUILTIN_FUNCTION() &&                    \
        PHI_HAS_INTRINSIC_BUILTIN_LINE()
#    define PHI_SOURCE_LOCATION_CURRENT() ::phi::source_location::current()
#else
#    define PHI_SOURCE_LOCATION_CURRENT()                                                          \
        ::phi::source_location(__FILE__, __FUNCTION__, __LINE__, 0)
#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_SOURCE_LOCATION_HPP
