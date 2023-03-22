#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_NODISCARD_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_NODISCARD_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_FEATURE_ATTRIBUTE_NODISCARD()
#    define PHI_NODISCARD       [[nodiscard]]
#    define PHI_NODISCARD_CLASS [[nodiscard]]
#elif PHI_HAS_EXTENSION_ATTRIBUTE_WARN_UNUSED_RESULT()
#    define PHI_NODISCARD       __attribute__((warn_unused_result))
#    define PHI_NODISCARD_CLASS __attribute__((warn_unused_result))
#elif PHI_HAS_EXTENSION_CHECK_RETURN()
#    define PHI_NODISCARD       _Check_return_
#    define PHI_NODISCARD_CLASS /* Nothing */
#else
#    define PHI_NODISCARD       /* Nothing */
#    define PHI_NODISCARD_CLASS /* Nothing */
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_NODISCARD_HPP
