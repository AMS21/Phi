#ifndef INCG_PHI_CORE_NARROW_CAST_HPP
#define INCG_PHI_CORE_NARROW_CAST_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/unsafe_cast.hpp"
#include "phi/type_traits/is_signed.hpp"
#include "phi/type_traits/make_unsafe.hpp"
#include "phi/type_traits/remove_reference.hpp"
#include "phi/type_traits/to_unsafe.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// Don't warn about float equal comparisons here since its a cast to ensure that your mixed float and int conversions are actually safe
PHI_CLANG_AND_GCC_SUPPRESS_WARNING_PUSH()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wfloat-equal")
PHI_GCC_SUPPRESS_WARNING("-Wsuggest-attribute=pure")

template <typename TargetT, typename SourceT>
PHI_NODISCARD
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR() || !defined(PHI_DEBUG)
        constexpr
#endif
        TargetT
        narrow_cast(SourceT&& source) noexcept
{
#if defined(PHI_DEBUG)
    using unsafe_target_t = make_unsafe_t<phi::remove_reference_t<TargetT>>;
    using unsafe_source_t = make_unsafe_t<phi::remove_reference_t<SourceT>>;

    PHI_CONSTEXPR_AND_CONST bool is_different_signedness =
            (is_signed<TargetT>::value != is_signed<SourceT>::value);

    const TargetT target = unsafe_cast<TargetT>(source);

    PHI_ASSERT(unsafe_cast<unsafe_source_t>(target) == to_unsafe(source) &&
                       (is_different_signedness ||
                        ((target < unsafe_target_t{0}) == (source < unsafe_source_t{0}))),
               "Invalid narrowing conversion. Source {}. Converted {}.", source, target);

    return target;
#else
    return unsafe_cast<TargetT>(source);
#endif
}

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_NARROW_CAST_HPP
