#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CV_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CV_HPP

#include "Phi/PhiConfig.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct remove_cv
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_cv<const TypeT>
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_cv<volatile TypeT>
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_cv<const volatile TypeT>
{
    using type = TypeT;
};

template <typename TypeT>
using remove_cv_t = typename remove_cv<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CV_HPP
