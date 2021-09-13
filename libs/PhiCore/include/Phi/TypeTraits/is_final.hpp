#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_FINAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_FINAL_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_FINAL()

template <typename TypeT>
struct is_final : public bool_constant<__is_final(TypeT)>
{};

#else

template <typename TypeT>
struct is_final : public false_type
{
    static_assert(always_false<TypeT>,
                  "phi::is_final requires compiler support for intrinsic __is_final");
};

#endif

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_final_v = is_final<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_FINAL_HPP
