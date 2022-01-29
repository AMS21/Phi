#ifndef INCG_PHI_CORE_COMPARE_RESULT_HPP
#define INCG_PHI_CORE_COMPARE_RESULT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

enum class compare_result
{
    Equal       = 0,
    LessThan    = -1,
    GreaterThan = 1,
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_COMPARE_RESULT_HPP
