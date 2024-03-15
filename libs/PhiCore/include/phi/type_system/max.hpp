#ifndef INCG_PHI_CORE_TYPE_SYSTEM_MAX_HPP
#define INCG_PHI_CORE_TYPE_SYSTEM_MAX_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/size_t.hpp"
#include "phi/generated/compiler_support/type_system.hpp"
#include "phi/type_traits/false_t.hpp"
#include "phi/type_traits/make_unsafe.hpp"
#include "phi/type_traits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace type_system
{
    namespace detail
    {
        template <typename TypeT, size_t Size>
        struct signed_int_max_impl;

        template <typename TypeT>
        struct signed_int_max_impl<TypeT, 1u>
        {
            static PHI_CONSTEXPR_AND_CONST TypeT value = TypeT(127LL);
        };

        template <typename TypeT>
        struct signed_int_max_impl<TypeT, 2u>
        {
            static PHI_CONSTEXPR_AND_CONST TypeT value = TypeT(32767LL);
        };

        template <typename TypeT>
        struct signed_int_max_impl<TypeT, 4u>
        {
            static PHI_CONSTEXPR_AND_CONST TypeT value = TypeT(2147483647LL);
        };

        template <typename TypeT>
        struct signed_int_max_impl<TypeT, 8u>
        {
            static PHI_CONSTEXPR_AND_CONST TypeT value = TypeT(9223372036854775807LL);
        };

        template <typename TypeT, size_t Size>
        struct unsigned_int_max_impl;

        template <typename TypeT>
        struct unsigned_int_max_impl<TypeT, 1u>
        {
            static PHI_CONSTEXPR_AND_CONST TypeT value = TypeT(255ULL);
        };

        template <typename TypeT>
        struct unsigned_int_max_impl<TypeT, 2u>
        {
            static PHI_CONSTEXPR_AND_CONST TypeT value = TypeT(65535ULL);
        };

        template <typename TypeT>
        struct unsigned_int_max_impl<TypeT, 4u>
        {
            static PHI_CONSTEXPR_AND_CONST TypeT value = TypeT(4294967295ULL);
        };

        template <typename TypeT>
        struct unsigned_int_max_impl<TypeT, 8u>
        {
            static PHI_CONSTEXPR_AND_CONST TypeT value = TypeT(18446744073709551615ULL);
        };

        template <typename TypeT, size_t Size>
        struct float_max_impl;

        template <typename TypeT>
        struct float_max_impl<TypeT, 4u>
        {
            static PHI_CONSTEXPR_AND_CONST TypeT value = TypeT(3.4028234e+38f);
        };

        template <typename TypeT>
        struct float_max_impl<TypeT, 8u>
        {
            static PHI_CONSTEXPR_AND_CONST TypeT value = TypeT(1.7976931348623157e+308);
        };

#if PHI_TYPE_SYSTEM_SIZEOF_LONG_DOUBLE() >= 16

        template <typename TypeT>
        struct float_max_impl<TypeT, 16u>
        {
#    if PHI_COMPILER_IS(EMCC)
            static PHI_CONSTEXPR_AND_CONST TypeT value =
                    TypeT(1.18973149535723176508575932662800702e+4932L);
#    else
            static PHI_CONSTEXPR_AND_CONST TypeT value = TypeT(1.18973149535723176502e+4932L);
#    endif
        };

#endif

        // Base implementation
        template <typename TypeT>
        PHI_NODISCARD PHI_CONSTEXPR TypeT max_impl() noexcept
        {
            static_assert(false_t<TypeT>::value, "No specialization for the given type found.");
            return TypeT{};
        }

        template <>
        PHI_NODISCARD PHI_CONSTEXPR bool max_impl<bool>() noexcept
        {
            return true;
        }

        // Character types

        template <>
        PHI_NODISCARD PHI_CONSTEXPR char max_impl<char>() noexcept
        {
#if PHI_TYPE_SYSTEM_CHAR_SIGNED()
            return detail::signed_int_max_impl<char, PHI_TYPE_SYSTEM_SIZEOF_CHAR()>::value;
#else
            return detail::unsigned_int_max_impl<char, PHI_TYPE_SYSTEM_SIZEOF_CHAR()>::value;
#endif
        }

        template <>
        PHI_NODISCARD PHI_CONSTEXPR wchar_t max_impl<wchar_t>() noexcept
        {
#if PHI_TYPE_SYSTEM_WCHAR_T_SIGNED()
            return detail::signed_int_max_impl<wchar_t, PHI_TYPE_SYSTEM_SIZEOF_WCHAR_T()>::value;
#else
            return detail::unsigned_int_max_impl<wchar_t, PHI_TYPE_SYSTEM_SIZEOF_WCHAR_T()>::value;
#endif
        }

#if PHI_HAS_FEATURE_CHAR8_T()

        template <>
        PHI_NODISCARD PHI_CONSTEXPR char8_t max_impl<char8_t>() noexcept
        {
            return detail::unsigned_int_max_impl<char8_t, 1u>::value;
        }

#endif

        template <>
        PHI_NODISCARD PHI_CONSTEXPR char16_t max_impl<char16_t>() noexcept
        {
            return detail::unsigned_int_max_impl<char16_t, 2u>::value;
        }

        template <>
        PHI_NODISCARD PHI_CONSTEXPR char32_t max_impl<char32_t>() noexcept
        {
            return detail::unsigned_int_max_impl<char32_t, 4u>::value;
        }

        // Signed integer type
        template <>
        PHI_NODISCARD PHI_CONSTEXPR signed char max_impl<signed char>() noexcept
        {
            return detail::signed_int_max_impl<signed char, PHI_TYPE_SYSTEM_SIZEOF_CHAR()>::value;
        }

        template <>
        PHI_NODISCARD PHI_CONSTEXPR short max_impl<short>() noexcept
        {
            return detail::signed_int_max_impl<short, PHI_TYPE_SYSTEM_SIZEOF_SHORT()>::value;
        }

        template <>
        PHI_NODISCARD PHI_CONSTEXPR int max_impl<int>() noexcept
        {
            return detail::signed_int_max_impl<int, PHI_TYPE_SYSTEM_SIZEOF_INT()>::value;
        }

        template <>
        PHI_NODISCARD PHI_CONSTEXPR long max_impl<long>() noexcept
        {
            return detail::signed_int_max_impl<long, PHI_TYPE_SYSTEM_SIZEOF_LONG()>::value;
        }

        template <>
        PHI_NODISCARD PHI_CONSTEXPR long long max_impl<long long>() noexcept
        {
            return detail::signed_int_max_impl<long long,
                                               PHI_TYPE_SYSTEM_SIZEOF_LONG_LONG()>::value;
        }

        // Unsigned integer types

        template <>
        PHI_NODISCARD PHI_CONSTEXPR unsigned char max_impl<unsigned char>() noexcept
        {
            return detail::unsigned_int_max_impl<unsigned char,
                                                 PHI_TYPE_SYSTEM_SIZEOF_CHAR()>::value;
        }

        template <>
        PHI_NODISCARD PHI_CONSTEXPR unsigned short max_impl<unsigned short>() noexcept
        {
            return detail::unsigned_int_max_impl<unsigned short,
                                                 PHI_TYPE_SYSTEM_SIZEOF_SHORT()>::value;
        }

        template <>
        PHI_NODISCARD PHI_CONSTEXPR unsigned max_impl<unsigned>() noexcept
        {
            return detail::unsigned_int_max_impl<unsigned, PHI_TYPE_SYSTEM_SIZEOF_INT()>::value;
        }

        template <>
        PHI_NODISCARD PHI_CONSTEXPR unsigned long max_impl<unsigned long>() noexcept
        {
            return detail::unsigned_int_max_impl<unsigned long,
                                                 PHI_TYPE_SYSTEM_SIZEOF_LONG()>::value;
        }

        template <>
        PHI_NODISCARD PHI_CONSTEXPR unsigned long long max_impl<unsigned long long>() noexcept
        {
            return detail::unsigned_int_max_impl<unsigned long long,
                                                 PHI_TYPE_SYSTEM_SIZEOF_LONG_LONG()>::value;
        }

        // Floating point numbers

        template <>
        PHI_NODISCARD PHI_CONSTEXPR float max_impl<float>() noexcept
        {
            return detail::float_max_impl<float, PHI_TYPE_SYSTEM_SIZEOF_FLOAT()>::value;
        }

        template <>
        PHI_NODISCARD PHI_CONSTEXPR double max_impl<double>() noexcept
        {
            return detail::float_max_impl<double, PHI_TYPE_SYSTEM_SIZEOF_DOUBLE()>::value;
        }

        template <>
        PHI_NODISCARD PHI_CONSTEXPR long double max_impl<long double>() noexcept
        {
            return detail::float_max_impl<long double, PHI_TYPE_SYSTEM_SIZEOF_LONG_DOUBLE()>::value;
        }
    } // namespace detail

    template <typename TypeT>
    PHI_NODISCARD PHI_CONSTEXPR remove_cv_t<TypeT> max() noexcept
    {
        return detail::max_impl<remove_cv_t<make_unsafe_t<TypeT>>>();
    }
} // namespace type_system

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_SYSTEM_MAX_HPP
