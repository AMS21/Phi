#ifndef INCG_PHI_CORE_TYPE_TRAITS_MAKE_UNSAFE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_MAKE_UNSAFE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/TypeTraits/copy_cv.hpp"
#include "Phi/TypeTraits/is_safe_type.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool = is_safe_type_v<TypeT>>
    struct make_unsafe_impl
    {
        using type = copy_cv_t<TypeT, typename TypeT::value_type>;
    };

    template <typename TypeT>
    struct make_unsafe_impl<TypeT, false>
    {
        using type = TypeT;
    };
} // namespace detail

template <typename TypeT>
struct make_unsafe : public detail::make_unsafe_impl<TypeT, is_safe_type_v<TypeT>>
{};

template <typename TypeT>
using make_unsafe_t = typename make_unsafe<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_MAKE_UNSAFE_HPP
