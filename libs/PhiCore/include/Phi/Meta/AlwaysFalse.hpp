#ifndef INCG_PHI_META_ALWAYS_FALSE_HPP
#define INCG_PHI_META_ALWAYS_FALSE_HPP

#include "Phi/PhiConfig.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename... TypesT>
constexpr inline bool always_false = false;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_META_ALWAYS_FALSE_HPP
