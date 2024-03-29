#ifndef INCG_PHI_CORE_TYPE_TRAITS_COPY_CV_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_COPY_CV_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/type_traits/is_const.hpp"
#include "phi/type_traits/is_volatile.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FromT, typename ToT, bool = is_const<FromT>::value,
          bool = is_volatile<FromT>::value>
struct copy_cv
{
    using type = ToT;
};

template <typename FromT, typename ToT>
struct copy_cv<FromT, ToT, true, false>
{
    using type = const ToT;
};

template <typename FromT, typename ToT>
struct copy_cv<FromT, ToT, false, true>
{
    using type = volatile ToT;
};

template <typename FromT, typename ToT>
struct copy_cv<FromT, ToT, true, true>
{
    using type = const volatile ToT;
};

template <typename FromT, typename ToT>
using copy_cv_t = typename copy_cv<FromT, ToT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_COPY_CV_HPP
