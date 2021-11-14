#ifndef INCG_PHI_CORE_TYPE_TRAITS_ADD_CV_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ADD_CV_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct add_cv
{
    using type = const volatile TypeT;
};

template <typename TypeT>
using add_cv_t = typename add_cv<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ADD_CV_HPP
