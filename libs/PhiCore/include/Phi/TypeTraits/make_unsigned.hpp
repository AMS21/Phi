#ifndef INCG_PHI_CORE_TYPE_TRAITS_MAKE_UNSIGNED_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_MAKE_UNSIGNED_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/TypeTraits/copy_cv.hpp"
#include "Phi/TypeTraits/is_enum.hpp"
#include "Phi/TypeTraits/is_integral.hpp"
#include "Phi/TypeTraits/is_safe_integer.hpp"
#include "Phi/TypeTraits/make_safe.hpp"
#include "Phi/TypeTraits/make_unsafe.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool = is_integral<TypeT>::value || is_enum<TypeT>::value>
    struct make_unsigned_impl_unsafe
    {
        using type = TypeT;
    };

    template <>
    struct make_unsigned_impl_unsafe<bool, true>
    {
        using type = bool;
    };

    template <>
    struct make_unsigned_impl_unsafe<char, true>
    {
        using type = unsigned char;
    };

    template <>
    struct make_unsigned_impl_unsafe<signed char, true>
    {
        using type = unsigned char;
    };

    template <>
    struct make_unsigned_impl_unsafe<unsigned char, true>
    {
        using type = unsigned char;
    };

    template <>
    struct make_unsigned_impl_unsafe<signed short, true>
    {
        using type = unsigned short;
    };

    template <>
    struct make_unsigned_impl_unsafe<unsigned short, true>
    {
        using type = unsigned short;
    };

    template <>
    struct make_unsigned_impl_unsafe<signed int, true>
    {
        using type = unsigned;
    };

    template <>
    struct make_unsigned_impl_unsafe<unsigned int, true>
    {
        using type = unsigned;
    };

    template <>
    struct make_unsigned_impl_unsafe<signed long, true>
    {
        using type = unsigned long;
    };

    template <>
    struct make_unsigned_impl_unsafe<unsigned long, true>
    {
        using type = unsigned long;
    };

    template <>
    struct make_unsigned_impl_unsafe<signed long long, true>
    {
        using type = unsigned long long;
    };

    template <>
    struct make_unsigned_impl_unsafe<unsigned long long, true>
    {
        using type = unsigned long long;
    };

    template <typename TypeT, bool = is_safe_integer<TypeT>::value>
    struct make_unsigned_impl
    {
        using type = typename make_unsigned_impl_unsafe<TypeT>::type;
    };

    template <typename TypeT>
    struct make_unsigned_impl<TypeT, true>
    {
        using type = make_safe_t<typename make_unsigned_impl_unsafe<make_unsafe_t<TypeT>>::type>;
    };
} // namespace detail

template <typename TypeT>
struct make_unsigned
{
    using type = copy_cv_t<TypeT, typename detail::make_unsigned_impl<remove_cv_t<TypeT>>::type>;
};

template <typename TypeT>
using make_unsigned_t = typename make_unsigned<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_MAKE_UNSIGNED_HPP
