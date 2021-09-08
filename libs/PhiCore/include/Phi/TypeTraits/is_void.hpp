#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/is_same.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_void : public is_same<void, typename remove_cv<TypeT>::type>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_void_v = is_void<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP
