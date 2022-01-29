#ifndef INCG_PHI_CORE_TYPE_TRAITS_MAKE_SIGNED_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_MAKE_SIGNED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/intrinsics/is_enum.hpp"
#include "phi/compiler_support/intrinsics/is_union.hpp"
#include "phi/type_traits/copy_cv.hpp"
#include "phi/type_traits/is_enum.hpp"
#include "phi/type_traits/is_integral.hpp"
#include "phi/type_traits/make_safe.hpp"
#include "phi/type_traits/make_unsafe.hpp"
#include "phi/type_traits/remove_cv.hpp"
#include "phi/type_traits/true_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
#if PHI_SUPPORTS_IS_ENUM() || PHI_SUPPORTS_IS_UNION()
    template <typename TypeT, bool = is_integral<TypeT>::value || is_enum<TypeT>::value>
    struct make_signed_impl_unsafe
    {
        using type = TypeT;
    };
#else
    template <typename TypeT, bool = true_t<>::value>
    struct make_signed_impl_unsafe
    {
        using type = TypeT;
    };
#endif

    template <>
    struct make_signed_impl_unsafe<bool, true>
    {
        using type = bool;
    };

    template <>
    struct make_signed_impl_unsafe<char, true>
    {
        using type = signed char;
    };

    template <>
    struct make_signed_impl_unsafe<unsigned char, true>
    {
        using type = signed char;
    };

    template <>
    struct make_signed_impl_unsafe<signed short, true>
    {
        using type = short;
    };

    template <>
    struct make_signed_impl_unsafe<unsigned short, true>
    {
        using type = short;
    };

    template <>
    struct make_signed_impl_unsafe<signed int, true>
    {
        using type = int;
    };

    template <>
    struct make_signed_impl_unsafe<unsigned int, true>
    {
        using type = int;
    };

    template <>
    struct make_signed_impl_unsafe<signed long, true>
    {
        using type = long;
    };

    template <>
    struct make_signed_impl_unsafe<unsigned long, true>
    {
        using type = long;
    };

    template <>
    struct make_signed_impl_unsafe<signed long long, true>
    {
        using type = long long;
    };

    template <>
    struct make_signed_impl_unsafe<unsigned long long, true>
    {
        using type = long long;
    };

    template <typename TypeT, bool = is_safe_integer<TypeT>::value>
    struct make_signed_impl
    {
        using type = typename make_signed_impl_unsafe<TypeT>::type;
    };

    template <typename TypeT>
    struct make_signed_impl<TypeT, true>
    {
        using type = make_safe_t<typename make_signed_impl_unsafe<make_unsafe_t<TypeT>>::type>;
    };
} // namespace detail

template <typename TypeT>
struct make_signed
{
    using type = copy_cv_t<TypeT, typename detail::make_signed_impl<remove_cv_t<TypeT>>::type>;
};

template <typename TypeT>
using make_signed_t = typename make_signed<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_MAKE_SIGNED_HPP
