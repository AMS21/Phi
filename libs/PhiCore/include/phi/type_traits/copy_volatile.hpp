#ifndef INCG_PHI_CORE_TYPE_TRAITS_COPY_VOLATILE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_COPY_VOLATILE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/is_volatile.hpp"
#include "phi/type_traits/remove_volatile.hpp"

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
