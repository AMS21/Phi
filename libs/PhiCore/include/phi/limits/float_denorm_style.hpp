#ifndef INCG_PHI_CORE_LIMITS_FLOAT_DENORM_STYLE_HPP
#define INCG_PHI_CORE_LIMITS_FLOAT_DENORM_STYLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

enum float_denorm_style
{
    denorm_indeterminate = -1,
    denorm_absent        = 0,
    denorm_present       = 1,
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_LIMITS_FLOAT_DENORM_STYLE_HPP
