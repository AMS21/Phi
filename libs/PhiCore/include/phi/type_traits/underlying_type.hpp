#ifndef INCG_PHI_CORE_TYPE_TRAITS_UNDERLYING_TYPE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_UNDERLYING_TYPE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/intrinsics/underlying_type.hpp"
#include "phi/type_traits/false_t.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_enum.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_UNDERLYING_TYPE()

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
        using type = PHI_UNDERLYING_TYPE(TypeT);
    };
} // namespace detail

template <typename TypeT>
struct underlying_type : public detail::underlying_type_impl<TypeT, is_enum<TypeT>::value>
{};

#else

template <typename TypeT>
struct underlying_type
{
    static_assert(false_t<TypeT>,
                  "phi::underlying_type requires compiler support for intrinsic underlying_type");
};

#endif

template <typename TypeT>
using underlying_type_t = typename underlying_type<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_UNDERLYING_TYPE_HPP
