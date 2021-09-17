#ifndef INCG_PHI_CORE_TYPE_TRAITS_COPY_CONST_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_COPY_CONST_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/TypeTraits/conditional.hpp"
#include "Phi/TypeTraits/is_const.hpp"
#include "Phi/TypeTraits/remove_const.hpp"

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
