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
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_POINTER() && PHI_HAS_KEYWORD(__is_pointer)

template <typename TypeT>
struct is_pointer : public bool_constant<__is_pointer(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_pointer_v = __is_pointer(TypeT);

#else

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
PHI_INLINE_VARIABLE constexpr bool is_pointer_v = is_pointer<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_HPP
