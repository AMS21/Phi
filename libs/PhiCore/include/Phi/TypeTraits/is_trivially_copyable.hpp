#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_TRIVIALLY_COPYABLE()

template <typename TypeT>
struct is_trivially_copyable : public bool_constant<__is_trivially_copyable(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_copyable_v = __is_trivially_copyable(TypeT);

#else

template <typename TypeT>
struct is_trivially_copyable : public false_type
{
    static_assert(always_false<TypeT>, "phi::is_trivially_copyable requires compiler support for "
                                       "instrinci __is_trivilly_copyable");
};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_copyable_v = is_trivially_copyable<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
