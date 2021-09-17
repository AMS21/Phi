#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSIGNED_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSIGNED_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_unsafe_arithmetic.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename TypeT, bool = is_unsafe_arithmetic_v<TypeT>>
    struct is_unsigned_impl : public bool_constant<TypeT(0) < TypeT(-1)>
    {};

    template <typename TypeT>
    struct is_unsigned_impl<TypeT, false> : public false_type
    {};
} // namespace detail
/// \endcond

template <typename TypeT>
struct is_unsigned : public detail::is_unsigned_impl<remove_cv_t<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_unsigned_v = is_unsigned<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSIGNED_HPP
