#ifndef INCG_PHI_CORE_SSIZE_T_HPP
#define INCG_PHI_CORE_SSIZE_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/core/size_t.hpp"
#include "phi/type_traits/make_signed.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

using ssize_t = make_signed_t<size_t>;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_SSIZE_T_HPP
