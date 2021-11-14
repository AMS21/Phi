#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CV_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CV_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Intrinsics/RemoveCV.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_REMOVE_CV()

template <typename TypeT>
struct remove_cv
{
    using type = PHI_REMOVE_CV(TypeT);
}

template <typename TypeT>
using remove_cv_t = PHI_REMOVE_CV(TypeT);

#else

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

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CV_HPP
