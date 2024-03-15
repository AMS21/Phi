#ifndef INCG_PHI_CORE_FORWARD_STD_INITIALIZER_LIST_HPP
#define INCG_PHI_CORE_FORWARD_STD_INITIALIZER_LIST_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/standard_library.hpp"

// Both glibc and libstdc++ don't version the initializer_list header
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/initializer_list#L52
// https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/libsupc%2B%2B/initializer_list#L41
#if PHI_STANDARD_LIBRARY_MSVC()

DETAIL_PHI_BEGIN_STD_NAMESPACE()

#else

namespace std
{

#endif

template <typename TypeT>
class initializer_list;

#if PHI_STANDARD_LIBRARY_MSVC()

DETAIL_PHI_END_STD_NAMESPACE()

#else

} // namespace std

#endif

#endif // INCG_PHI_CORE_FORWARD_STD_INITIALIZER_LIST_HPP
