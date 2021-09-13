#ifndef INCG_PHI_CORE_TYPE_TRAITS_ALIGNMENT_OF_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ALIGNMENT_OF_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include <cstdint>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct alignment_of : integral_constant<std::size_t, alignof(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr std::size_t alignment_of_v = alignment_of<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ALIGNMENT_OF_HPP
