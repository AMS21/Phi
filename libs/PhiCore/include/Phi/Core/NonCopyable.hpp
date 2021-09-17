#ifndef INCG_PHI_CORE_NONCOPYABLE_HPP
#define INCG_PHI_CORE_NONCOPYABLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

class NonCopyable
{
protected:
    NonCopyable()  = default;
    ~NonCopyable() = default;

    NonCopyable(NonCopyable&&) = default;
    NonCopyable& operator=(NonCopyable&&) = default;

public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_NONCOPYABLE_HPP
