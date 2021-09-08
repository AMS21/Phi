#ifndef INCG_PHI_CORE_TYPE_TRAITS_COPY_CV_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_COPY_CV_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/TypeTraits/is_const.hpp"
#include "Phi/TypeTraits/is_volatile.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FromT, typename ToT, bool = is_const_v<FromT>, bool = is_volatile_v<FromT>>
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

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_COPY_CV_HPP
