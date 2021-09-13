#ifndef INCG_PHI_CORE_TYPE_TRAITS_MAKE_UNSIGNED_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_MAKE_UNSIGNED_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/TypeTraits/copy_cv.hpp"
#include "Phi/TypeTraits/is_enum.hpp"
#include "Phi/TypeTraits/is_integral.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool = is_integral_v<TypeT> || is_enum_v<TypeT>>
    struct make_unsigned_impl
    {};

    template <>
    struct make_unsigned_impl<bool, true>
    {};

    template <>
    struct make_unsigned_impl<signed short, true>
    {
        using type = unsigned short;
    };

    template <>
    struct make_unsigned_impl<unsigned short, true>
    {
        using type = unsigned short;
    };

    template <>
    struct make_unsigned_impl<signed int, true>
    {
        using type = unsigned;
    };

    template <>
    struct make_unsigned_impl<unsigned int, true>
    {
        using type = unsigned;
    };

    template <>
    struct make_unsigned_impl<signed long, true>
    {
        using type = unsigned long;
    };

    template <>
    struct make_unsigned_impl<unsigned long, true>
    {
        using type = unsigned long;
    };

    template <>
    struct make_unsigned_impl<signed long long, true>
    {
        using type = unsigned long long;
    };

    template <>
    struct make_unsigned_impl<unsigned long long, true>
    {
        using type = unsigned long long;
    };
} // namespace detail

template <typename TypeT>
struct make_unsigned
{
    using type = copy_cv<TypeT, detail::make_unsigned_impl<remove_cv_t<TypeT>>>;
};

template <typename TypeT>
using make_unsigned_t = typename make_unsigned<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_MAKE_UNSIGNED_HPP
