#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOT_SAME_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOT_SAME_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename OtherT>
struct is_not_same : public true_type
{};

template <typename TypeT>
struct is_not_same<TypeT, TypeT> : false_type
{};

template <typename TypeT, typename OtherT>
constexpr PHI_INLINE_VARIABLE bool is_not_same_v = is_not_same<TypeT, OtherT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOT_SAME_HPP
