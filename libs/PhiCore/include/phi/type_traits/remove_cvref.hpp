#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CVREF_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CVREF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/type_traits/remove_cv.hpp"
#include "phi/type_traits/remove_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct remove_cvref
{
    using type = typename remove_cv<typename remove_reference<TypeT>::type>::type;
};

template <typename TypeT>
using remove_cvref_t = typename remove_cvref<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CVREF_HPP
