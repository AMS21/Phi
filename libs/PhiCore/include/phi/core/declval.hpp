#ifndef INCG_PHI_CORE_DECLVAL_HPP
#define INCG_PHI_CORE_DECLVAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/type_traits/add_rvalue_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename TypeT>
    struct declval_protector
    {
        static constexpr bool                stop = false;
        static add_rvalue_reference_t<TypeT> delegate_type();
    };
} // namespace detail
/// \endcond

PHI_CLANG_SUPPRESS_WARNING_PUSH()
#if PHI_COMPILER_IS_ATLEAST(CLANG, 10, 0, 0)
PHI_CLANG_SUPPRESS_WARNING("-Wdeprecated-volatile")
#endif

template <typename TypeT>
PHI_ALWAYS_INLINE add_rvalue_reference_t<TypeT> declval() noexcept
{
    static_assert(detail::declval_protector<TypeT>::stop, "phi::declval() must not be used!");

    return detail::declval_protector<TypeT>::delegate_type();
}

PHI_CLANG_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_DECLVAL_HPP
