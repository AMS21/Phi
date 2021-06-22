#ifndef INCG_PHI_WINDOW_WINDOW_IMPL_HPP
#define INCG_PHI_WINDOW_WINDOW_IMPL_HPP

#include "Phi/Math/Vector2.hpp"
#include "Phi/PhiConfig.hpp"
#include <string>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    class WindowImpl
    {
    public:
        static WindowImpl* create(const std::string& title);
    };
} // namespace detail

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_WINDOW_WINDOW_IMPL_HPP
