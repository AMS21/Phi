#ifndef INCG_PHI_CORE_NONCOPYABLE_HPP
#define INCG_PHI_CORE_NONCOPYABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

class non_copyable
{
protected:
    non_copyable()  = default;
    ~non_copyable() = default;

    non_copyable(non_copyable&&) = default;
    non_copyable& operator=(non_copyable&&) = default;

public:
    non_copyable(const non_copyable&) = delete;
    non_copyable& operator=(const non_copyable&) = delete;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_NONCOPYABLE_HPP
