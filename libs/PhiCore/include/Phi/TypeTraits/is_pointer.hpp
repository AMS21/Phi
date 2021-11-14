#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Config/Compiler.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

#if PHI_HAS_INTRINSIC_IS_POINTER() && PHI_HAS_KEYWORD(__is_pointer)

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_pointer : public bool_constant<__is_pointer(TypeT)>
{};

template <typename TypeT>
struct is_not_pointer : public bool_constant<!__is_pointer(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_pointer_v = __is_pointer(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_pointer_v = !__is_pointer(TypeT);

#    endif

#else

#    include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename TypeT>
    struct is_pointer_impl : public false_type
    {};

    template <typename TypeT>
    struct is_pointer_impl<TypeT*> : public true_type
    {};
} // namespace detail
/// \endcond

template <typename TypeT>
struct is_pointer : public detail::is_pointer_impl<remove_cv_t<TypeT>>
{};

template <typename TypeT>
struct is_not_pointer : public bool_constant<!is_pointer<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_pointer_v = is_pointer<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_pointer_v = is_not_pointer<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_HPP
