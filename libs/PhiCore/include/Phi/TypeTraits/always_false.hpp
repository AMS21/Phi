#ifndef INCG_PHI_CORE_TYPE_TRAITS_ALWAYS_FALSE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ALWAYS_FALSE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename... TypesT>
constexpr PHI_INLINE_VARIABLE bool always_false = false;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ALWAYS_FALSE_HPP
