#ifndef INCG_PHI_FORWARD_SPAN_HPP
#define INCG_PHI_FORWARD_SPAN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/core/size_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_INLINE_VARIABLE constexpr size_t dynamic_extent = size_t(-1);

template <typename TypeT, size_t Extent = dynamic_extent>
class span;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_FORWARD_SPAN_HPP
