#ifndef INCG_PHI_FORWARD_STD_ARRAY_HPP
#define INCG_PHI_FORWARD_STD_ARRAY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/standard_library.hpp"
#include "phi/core/size_t.hpp"

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <typename TypeT, phi::size_t Size>
struct array;

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_FORWARD_STD_ARRAY_HPP
