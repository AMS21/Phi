#ifndef INCG_PHI_WINDOW_PLATFORM_X11_X11DISPLAY_HPP
#define INCG_PHI_WINDOW_PLATFORM_X11_X11DISPLAY_HPP

#include "Phi/Core/NonCopyable.hpp"
#include "Phi/Core/ObserverPtr.hpp"
#include "Phi/PhiConfig.hpp"
#include <X11/Xlib.h>

DETAIL_PHI_BEGIN_NAMESPACE()

class X11Display : public NonCopyable
{
public:
    X11Display() noexcept;

    ~X11Display() noexcept;

    [[nodiscard]] ::Display* get() const noexcept;

private:
    ::Display* m_Display;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_WINDOW_PLATFORM_X11_X11DISPLAY_HPP
