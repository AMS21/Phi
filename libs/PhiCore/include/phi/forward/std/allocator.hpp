#ifndef INCG_PHI_FORWARD_STD_ALLOCATOR_HPP
#define INCG_PHI_FORWARD_STD_ALLOCATOR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/cpp_standard.hpp"
#include "phi/compiler_support/standard_library.hpp"

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <typename>
class allocator;

// allocator<void> has been deprecated in C++-17 and removed in C++-20
// See https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0174r0#2.4
#if PHI_CPP_STANDARD() <= PHI_CPLUSPLUS_17()
template <>
class allocator<void>;
#endif

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_FORWARD_STD_ALLOCATOR_HPP
