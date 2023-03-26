#ifndef INCG_PHI_CORE_TYPE_SYSTEM_MIN_HPP
#define INCG_PHI_CORE_TYPE_SYSTEM_MIN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

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
        struct signed_min_impl;

        template <typename TypeT>
        struct signed_min_impl<TypeT, 1u>
        {
            static constexpr TypeT value = TypeT(-128LL);
        };

        template <typename TypeT>
        struct signed_min_impl<TypeT, 2u>
        {
            static constexpr TypeT value = TypeT(-32768LL);
        };

        template <typename TypeT>
        struct signed_min_impl<TypeT, 4u>
        {
            static constexpr TypeT value = TypeT(-2147483648LL);
        };

        template <typename TypeT>
        struct signed_min_impl<TypeT, 8u>
        {
            static constexpr TypeT value = TypeT(-9223372036854775808ULL);
        };

        template <typename TypeT, size_t Size>
        struct float_min_impl;

        template <typename TypeT>
        struct float_min_impl<TypeT, 4u>
        {
            static constexpr TypeT value = TypeT(1.17549435e-38f);
        };

        template <typename TypeT>
        struct float_min_impl<TypeT, 8u>
        {
            static constexpr TypeT value = TypeT(2.2250738585072014e-308);
        };

#if PHI_TYPE_SYSTEM_SIZEOF_LONG_DOUBLE() >= 16

        template <typename TypeT>
        struct float_min_impl<TypeT, 16u>
        {
            static constexpr TypeT value = TypeT(3.3621031431120935062626778173217526026e-4932L);
        };

#endif

        // Base implementation
        template <typename TypeT>
        PHI_NODISCARD constexpr TypeT min_impl() noexcept
        {
            static_assert(false_t<TypeT>::value, "No specilization for the given type found.");
            return TypeT{};
        }

        template <>
        PHI_NODISCARD constexpr bool min_impl<bool>() noexcept
        {
            return false;
        }

        // Character types

        template <>
        PHI_NODISCARD constexpr char min_impl<char>() noexcept
        {
#if PHI_TYPE_SYSTEM_CHAR_SIGNED()
            return detail::signed_min_impl<char, PHI_TYPE_SYSTEM_SIZEOF_CHAR()>::value;
#else
            return 0u;
#endif
        }

        template <>
        PHI_NODISCARD constexpr wchar_t min_impl<wchar_t>() noexcept
        {
#if PHI_TYPE_SYSTEM_WCHAR_T_SIGNED()
            return detail::signed_min_impl<wchar_t, PHI_TYPE_SYSTEM_SIZEOF_WCHAR_T()>::value;
#else
            return 0u;
#endif
        }

#if PHI_HAS_FEATURE_CHAR8_T()

        template <>
        PHI_NODISCARD constexpr char8_t min_impl<char8_t>() noexcept
        {
            return 0u;
        }

#endif

        template <>
        PHI_NODISCARD constexpr char16_t min_impl<char16_t>() noexcept
        {
            return 0u;
        }

        template <>
        PHI_NODISCARD constexpr char32_t min_impl<char32_t>() noexcept
        {
            return 0u;
        }

        // Signed integer type
        template <>
        PHI_NODISCARD constexpr signed char min_impl<signed char>() noexcept
        {
            return detail::signed_min_impl<signed char, PHI_TYPE_SYSTEM_SIZEOF_CHAR()>::value;
        }

        template <>
        PHI_NODISCARD constexpr short min_impl<short>() noexcept
        {
            return detail::signed_min_impl<short, PHI_TYPE_SYSTEM_SIZEOF_SHORT()>::value;
        }

        template <>
        PHI_NODISCARD constexpr int min_impl<int>() noexcept
        {
            return detail::signed_min_impl<int, PHI_TYPE_SYSTEM_SIZEOF_INT()>::value;
        }

        template <>
        PHI_NODISCARD constexpr long min_impl<long>() noexcept
        {
            return detail::signed_min_impl<long, PHI_TYPE_SYSTEM_SIZEOF_LONG()>::value;
        }

        template <>
        PHI_NODISCARD constexpr long long min_impl<long long>() noexcept
        {
            return detail::signed_min_impl<long long, PHI_TYPE_SYSTEM_SIZEOF_LONG_LONG()>::value;
        }

        // Unsigned integer types

        template <>
        PHI_NODISCARD constexpr unsigned char min_impl<unsigned char>() noexcept
        {
            return 0;
        }

        template <>
        PHI_NODISCARD constexpr unsigned short min_impl<unsigned short>() noexcept
        {
            return 0;
        }

        template <>
        PHI_NODISCARD constexpr unsigned min_impl<unsigned>() noexcept
        {
            return 0;
        }

        template <>
        PHI_NODISCARD constexpr unsigned long min_impl<unsigned long>() noexcept
        {
            return 0;
        }

        template <>
        PHI_NODISCARD constexpr unsigned long long min_impl<unsigned long long>() noexcept
        {
            return 0;
        }

        // Floating point numbers

        template <>
        PHI_NODISCARD constexpr float min_impl<float>() noexcept
        {
            return detail::float_min_impl<float, PHI_TYPE_SYSTEM_SIZEOF_FLOAT()>::value;
        }

        template <>
        PHI_NODISCARD constexpr double min_impl<double>() noexcept
        {
            return detail::float_min_impl<double, PHI_TYPE_SYSTEM_SIZEOF_DOUBLE()>::value;
        }

        template <>
        PHI_NODISCARD constexpr long double min_impl<long double>() noexcept
        {
            return detail::float_min_impl<long double, PHI_TYPE_SYSTEM_SIZEOF_LONG_DOUBLE()>::value;
        }
    } // namespace detail

    template <typename TypeT>
    PHI_NODISCARD constexpr remove_cv_t<TypeT> min() noexcept
    {
        return detail::min_impl<remove_cv_t<make_unsafe_t<TypeT>>>();
    }

} // namespace type_system

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_SYSTEM_MIN_HPP
