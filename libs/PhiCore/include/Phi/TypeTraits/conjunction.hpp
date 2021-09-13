#ifndef INCG_PHI_CORE_TYPE_TRAITS_CONJUNCTION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_CONJUNCTION_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/conditional.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename...>
struct conjunction : public true_type
{};

template <typename B1>
struct conjunction<B1> : B1
{};

template <typename B1, typename... Bn>
struct conjunction<B1, Bn...> : conditional_t<bool(B1::value), conjunction<Bn...>, B1>
{};

template <typename... B>
PHI_INLINE_VARIABLE constexpr bool conjunction_v = conjunction<B...>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_CONJUNCTION_HPP
