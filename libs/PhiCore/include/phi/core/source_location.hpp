#ifndef INCG_PHI_CORE_SOURCE_LOCATION_HPP
#define INCG_PHI_CORE_SOURCE_LOCATION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/container/string_view.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/sized_types.hpp"
#include "phi/generated/compiler_support/features.hpp"
#include "phi/type_traits/false_t.hpp"

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

    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    constexpr source_location(const char* file, const char* function, uint_least32_t line,
                              uint_least32_t column) noexcept
        : m_FileName(file)
        , m_FunctionName(function)
        , m_LineNumber(line)
        , m_Column(column)
    {
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
        PHI_ASSERT(file != nullptr, "Don't pass nullptr to phi::source_location");
        PHI_ASSERT(function != nullptr, "Don't pass nullptr to phi::source_location");
#endif
    }

#if PHI_HAS_INTRINSIC_BUILTIN_FILE() && PHI_HAS_INTRINSIC_BUILTIN_FUNCTION() &&                    \
        PHI_HAS_INTRINSIC_BUILTIN_LINE()
    static constexpr source_location current(const char*    file     = __builtin_FILE(),
                                             const char*    function = __builtin_FUNCTION(),
                                             uint_least32_t line     = __builtin_LINE()
#    if PHI_HAS_INTRINSIC_BUILTIN_COLUMN()
                                                     ,
                                             uint_least32_t column = __builtin_COLUMN()
#    endif
                                                     ) noexcept
    {
        return source_location
        {
            file, function, line,
#    if PHI_HAS_INTRINSIC_BUILTIN_COLUMN()
                    column
#    else
                    0
#    endif
        };
    }
#else
    template <typename TypeT = void>
    static constexpr source_location current() noexcept
    {
        static_assert(false_t<TypeT>::value,
                      "phi::source_location requires compiler support for current.");

        return {};
    }
#endif

    PHI_NODISCARD constexpr uint_least32_t line() const noexcept
    {
        return m_LineNumber;
    }

    PHI_NODISCARD constexpr uint_least32_t column() const noexcept
    {
        return m_Column;
    }

    PHI_NODISCARD constexpr const char* file_name() const noexcept
    {
        return m_FileName;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR string_view file_name_view() const noexcept
    {
        return m_FileName;
    }

    PHI_NODISCARD constexpr const char* function_name() const noexcept
    {
        return m_FunctionName;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR string_view function_name_view() const noexcept
    {
        return m_FunctionName;
    }

private:
    const char*    m_FileName;
    const char*    m_FunctionName;
    uint_least32_t m_LineNumber;
    uint_least32_t m_Column;
};

#if PHI_HAS_INTRINSIC_BUILTIN_FILE() && PHI_HAS_INTRINSIC_BUILTIN_FUNCTION() &&                    \
        PHI_HAS_INTRINSIC_BUILTIN_LINE()
#    define PHI_SOURCE_LOCATION_CURRENT() ::phi::source_location::current()
#else
#    define PHI_SOURCE_LOCATION_CURRENT()                                                          \
        ::phi::source_location(__FILE__, __FUNCTION__, __LINE__, 0u)
#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_SOURCE_LOCATION_HPP
