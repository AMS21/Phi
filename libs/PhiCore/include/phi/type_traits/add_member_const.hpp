#ifndef INCG_PHI_CORE_TYPE_TRAITS_ADD_MEMBER_CONST_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ADD_MEMBER_CONST_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/type_traits/is_function.hpp"
#include "phi/type_traits/is_member_function_pointer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT,
              bool = is_function<TypeT>::value || is_member_function_pointer<TypeT>::value>
    struct add_member_const_impl
    {
        using type = TypeT;
    };

    template <typename TypeT>
    struct add_member_const_impl<TypeT, true>
    {
        using type = const TypeT;
    };
} // namespace detail

template <typename TypeT>
struct add_member_const
{
    using type = typename detail::add_member_const_impl<TypeT>::type;
};

template <typename TypeT>
using add_member_const_t = typename add_member_const<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ADD_MEMBER_CONST_HPP
