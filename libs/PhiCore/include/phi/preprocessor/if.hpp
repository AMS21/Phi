#ifndef INCG_PHI_CORE_PREPROCESSOR_IF_HPP
#define INCG_PHI_CORE_PREPROCESSOR_IF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/preprocessor/bool.hpp"

#define DETAIL_PHI_IF_0(true_case) /* Nothing */
#define DETAIL_PHI_IF_1(true_case) true_case

#define DETAIL_PHI_IF_IMPL_2(bit, true_case) DETAIL_PHI_IF_##bit(true_case)

#define DETAIL_PHI_IF_IMPL(bit, true_case) DETAIL_PHI_IF_IMPL_2(bit, true_case)

#define PHI_IF(cond, true_case) DETAIL_PHI_IF_IMPL(PHI_BOOL(cond), true_case)

#endif // INCG_PHI_CORE_PREPROCESSOR_IF_HPP
