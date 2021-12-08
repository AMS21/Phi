#ifndef INCG_PHI_CORE_PREPROCESSOR_IF_ELSE_HPP
#define INCG_PHI_CORE_PREPROCESSOR_IF_ELSE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/preprocessor/bool.hpp"

#define DETAIL_PHI_IF_ELSE_0(true_case, false_case) false_case
#define DETAIL_PHI_IF_ELSE_1(true_case, false_case) true_case

#define DETAIL_PHI_IF_ELSE_IMPL_2(bit, true_case, false_case)                                      \
    DETAIL_PHI_IF_ELSE_##bit(true_case, false_case)

#define DETAIL_PHI_IF_ELSE_IMPL(bit, true_case, false_case)                                        \
    DETAIL_PHI_IF_ELSE_IMPL_2(bit, true_case, false_case)

#define PHI_IF_ELSE(cond, true_case, false_case)                                                   \
    DETAIL_PHI_IF_ELSE_IMPL(PHI_BOOL(cond), true_case, false_case)

#endif // INCG_PHI_CORE_PREPROCESSOR_IF_ELSE_HPP
