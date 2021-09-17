#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_WRAPPER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_WRAPPER_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"
#include <functional>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    struct is_reference_wrapper_impl : public false_type
    {};

    template <typename TypeT>
    struct is_reference_wrapper_impl<std::reference_wrapper<TypeT>> : public true_type
    {};
} // namespace detail

template <typename TypeT>
struct is_reference_wrapper
    : public detail::is_reference_wrapper_impl<typename remove_cv<TypeT>::type>
{};

template <typename TypeT>
constexpr PHI_INLINE_VARIABLE bool is_reference_wrapper_v = is_reference_wrapper<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_WRAPPER_HPP
