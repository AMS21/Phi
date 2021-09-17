#ifndef INCG_PHI_CORE_NULLPTR_HPP
#define INCG_PHI_CORE_NULLPTR_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

using nullptr_t = decltype(nullptr);

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_NULLPTR_HPP
