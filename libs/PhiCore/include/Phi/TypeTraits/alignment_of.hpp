#ifndef INCG_PHI_CORE_TYPE_TRAITS_ALIGNMENT_OF_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ALIGNMENT_OF_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Core/SizeT.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct alignment_of : public integral_constant<size_t, alignof(TypeT)>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr size_t alignment_of_v = alignment_of<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ALIGNMENT_OF_HPP
