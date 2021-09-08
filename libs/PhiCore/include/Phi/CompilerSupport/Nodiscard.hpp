#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_NODISCARD_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_NODISCARD_HPP

#include "Phi/Config/CPlusPlus.hpp"
#include "Phi/Config/Compiler.hpp"
#include "Phi/PhiConfig.hpp"

#if PHI_CPP_STANDARD_IS_ATLEAST(17) &&                                                             \
        (PHI_COMPILER_IS_ATLEAST(CLANG, 3, 9, 0) || PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) ||       \
         PHI_COMPILER_IS_ATLEAST(MSVC, 19, 11, 0))
// Compiler supports standard [[nodiscard]]
#    define PHI_NODISCARD [[nodiscard]]
#elif PHI_COMPILER_IS(CLANG) || PHI_COMPILER_IS(GCC)
#    define PHI_NODISCARD __attribute__((warn_unused_result))
#elif PHI_COMPILER_IS_ATLEAST(MSVC, 11, 0, 0) // MSVC 2012
#    define PHI_NODISCARD _Check_return_
#else
#    define PHI_NODISCARD /* Nothing */
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_NODISCARD_HPP
