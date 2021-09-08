#ifndef INCG_PHI_CORE_TYPE_TRAITS_COPY_VOLATILE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_COPY_VOLATILE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/TypeTraits/conditional.hpp"
#include "Phi/TypeTraits/is_volatile.hpp"
#include "Phi/TypeTraits/remove_volatile.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FromT, typename ToT>
struct copy_volatile
{
    using type = typename conditional<is_volatile<FromT>::value,
                                      volatile typename remove_volatile<ToT>::type, ToT>::type;
};

template <typename FromT, typename ToT>
using copy_volatile_t = typename copy_volatile<FromT, ToT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_COPY_VOLATILE_HPP
