#ifndef INCG_PHI_CORE_TYPE_TRAITS_UNDERLYING_TYPE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_UNDERLYING_TYPE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_enum.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_UNDERLYING_TYPE()

namespace detail
{
    template <typename TypeT, bool = is_enum<TypeT>::value>
    struct underlying_type_impl;

    template <typename TypeT>
    struct underlying_type_impl<TypeT, false>
    {};

    template <typename TypeT>
    struct underlying_type_impl<TypeT, true>
    {
        using type = __underlying_type(TypeT);
    };
} // namespace detail

template <typename TypeT>
struct underlying_type : public detail::underlying_type_impl<TypeT, is_enum<TypeT>::value>
{};

#else

template <typename TypeT>
struct underlying_type
{
    static_assert(always_false<TypeT>,
                  "phi::underlying_type requires compiler support for intrinsic underlying_type");
};

#endif

template <typename TypeT>
using underlying_type_t = typename underlying_type<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_UNDERLYING_TYPE_HPP
