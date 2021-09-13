#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_INTEGRAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_INTEGRAL_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_safe_type.hpp"
#include "Phi/TypeTraits/is_unsafe_integral.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool = is_safe_type_v<TypeT>>
    struct is_safe_integral_impl : public is_unsafe_integral<typename TypeT::value_type>
    {};

    template <typename TypeT>
    struct is_safe_integral_impl<TypeT, false> : public false_type
    {};
} // namespace detail

template <typename TypeT>
struct is_safe_integral : public detail ::is_safe_integral_impl<TypeT, is_safe_type_v<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_safe_integral_v = is_safe_integral<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_INTEGRAL_HPP
