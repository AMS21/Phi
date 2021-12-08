#ifndef INCG_PHI_CORE_TYPE_TRAITS_COPY_CONST_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_COPY_CONST_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/is_const.hpp"
#include "phi/type_traits/remove_const.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FromT, typename ToT>
struct copy_const
{
    using type = typename conditional<is_const<FromT>::value,
                                      const typename remove_const<ToT>::type, ToT>::type;
};

template <typename FromT, typename ToT>
using copy_const_t = typename copy_const<FromT, ToT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_COPY_CONST_HPP
