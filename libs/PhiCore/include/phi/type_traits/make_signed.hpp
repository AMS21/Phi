#ifndef INCG_PHI_CORE_TYPE_TRAITS_MAKE_SIGNED_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_MAKE_SIGNED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/type_traits/copy_cv.hpp"
#include "phi/type_traits/is_enum.hpp"
#include "phi/type_traits/is_integral.hpp"
#include "phi/type_traits/remove_cv.hpp"

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

    template <typename TypeT>
    using make_signed_impl_t = typename make_signed_impl<TypeT>::type;
} // namespace detail

template <typename TypeT>
struct make_signed
{
    using type = typename copy_cv<
            TypeT, typename detail::make_signed_impl<typename remove_cv<TypeT>::type>::type>::type;
};

template <typename TypeT>
using make_signed_t = typename make_signed<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_MAKE_SIGNED_HPP
