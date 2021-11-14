#ifndef INCG_PHI_CORE_TYPE_TRAITS_MAKE_SIGNED_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_MAKE_SIGNED_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/TypeTraits/copy_cv.hpp"
#include "Phi/TypeTraits/is_enum.hpp"
#include "Phi/TypeTraits/is_integral.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool = is_integral<TypeT>::value || is_enum<TypeT>::value>
    struct make_signed_impl
    {};

    template <>
    struct make_signed_impl<bool, true>
    {};

    template <>
    struct make_signed_impl<signed short, true>
    {
        using type = short;
    };

    template <>
    struct make_signed_impl<unsigned short, true>
    {
        using type = short;
    };

    template <>
    struct make_signed_impl<signed int, true>
    {
        using type = int;
    };

    template <>
    struct make_signed_impl<unsigned int, true>
    {
        using type = int;
    };

    template <>
    struct make_signed_impl<signed long, true>
    {
        using type = long;
    };

    template <>
    struct make_signed_impl<unsigned long, true>
    {
        using type = long;
    };

    template <>
    struct make_signed_impl<signed long long, true>
    {
        using type = long long;
    };

    template <>
    struct make_signed_impl<unsigned long long, true>
    {
        using type = long long;
    };
} // namespace detail

template <typename TypeT>
struct make_signed
{
    using type = copy_cv<TypeT, detail::make_signed_impl<remove_cv_t<TypeT>>>;
};

template <typename TypeT>
using make_signed_t = typename make_signed<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_MAKE_SIGNED_HPP
