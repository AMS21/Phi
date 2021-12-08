#ifndef INCG_PHI_CORE_TYPE_TRAITS_MAKE_UNSAFE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_MAKE_UNSAFE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/type_traits/copy_cv.hpp"
#include "phi/type_traits/is_safe_type.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool = is_safe_type<TypeT>::value>
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
struct make_unsafe : public detail::make_unsafe_impl<TypeT, is_safe_type<TypeT>::value>
{};

template <typename TypeT>
using make_unsafe_t = typename make_unsafe<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_MAKE_UNSAFE_HPP
