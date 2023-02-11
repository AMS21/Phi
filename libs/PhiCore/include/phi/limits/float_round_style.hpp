#ifndef INCG_PHI_CORE_LIMITS_FLOAT_ROUND_STYLE_HPP
#define INCG_PHI_CORE_LIMITS_FLOAT_ROUND_STYLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

enum float_round_style
{
    round_indeterminate       = -1,
    round_toward_zero         = 0,
    round_to_nearest          = 1,
    round_toward_infinity     = 2,
    round_toward_neg_infinity = 3,
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_LIMITS_FLOAT_ROUND_STYLE_HPP
