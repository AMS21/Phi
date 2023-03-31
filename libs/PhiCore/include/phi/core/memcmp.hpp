#ifndef INCG_PHI_CORE_MEMCMP_HPP
#define INCG_PHI_CORE_MEMCMP_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/intrinsics/memcmp.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/is_constant_evaluated.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

constexpr int memcmp(nullptr_t, nullptr_t, size_t /*count*/) noexcept
{
    return 0;
}

template <typename TypeT>
constexpr int memcmp(const TypeT* lhs, nullptr_t, size_t /*count*/) noexcept
{
    return lhs == nullptr ? 0 : 1;
}

template <typename TypeT>
constexpr int memcmp(nullptr_t, const TypeT* rhs, size_t /*count*/) noexcept
{
    return rhs == nullptr ? 0 : -1;
}

template <typename TypeT>
PHI_EXTENDED_CONSTEXPR int memcmp(const TypeT* lhs, const TypeT* rhs, size_t count) noexcept
{
#if PHI_SUPPORTS_MEMCMP_CONSTEXPR()
    return PHI_MEMCMP(lhs, rhs, count);
#elif PHI_SUPPORTS_MEMCMP() && (PHI_COMPILER_IS_ATLEAST(GCC, 9, 0, 0) || PHI_COMPILER_IS_NOT(GCC))
#    if PHI_HAS_WORKING_IS_CONSTANT_EVALUATED()
    if (is_constant_evaluated())
    {
        for (; count > 0; --count, ++lhs, ++rhs)
        {
            if (*lhs < *rhs)
            {
                return -1;
            }
            if (*rhs < *lhs)
            {
                return 1;
            }
        }

        return 0;
    }
#    endif

    return PHI_MEMCMP(lhs, rhs, count);
#else
    for (; count > 0; --count, ++lhs, ++rhs)
    {
        if (*lhs < *rhs)
        {
            return -1;
        }
        if (*rhs < *lhs)
        {
            return 1;
        }
    }

    return 0;
#endif
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MEMCMP_HPP
