#ifndef PHI_WINDOW_PLATFORM_X11_WINDOW_IMPL_X11_HPP
#define PHI_WINDOW_PLATFORM_X11_WINDOW_IMPL_X11_HPP

#include "Phi/Core/Boolean.hpp"
#include "Phi/Core/ObserverPtr.hpp"
#include "Phi/Core/Types.hpp"
#include "Phi/Math/Vector2.hpp"
#include "Phi/PhiConfig.hpp"
#include "Phi/Window/WindowHandle.hpp"
#include "WindowImpl.hpp"
#include "X11Display.hpp"
#include <X11/Xlib.h>

DETAIL_PHI_BEGIN_NAMESPACE()

class WindowImplX11 : public detail::WindowImpl
{
public:
    explicit WindowImplX11(WindowsHandle handle);

    WindowImplX11(phi::u32 width, phi::u32 height, const std::string& title);

    ~WindowImplX11();

    [[nodiscard]] WindowsHandle getOSHandle() const noexcept;

private:
    void initialize() noexcept;

    void shutdown() noexcept;

    ::Window   m_Window;
    X11Display m_Display;
    phi::i32   m_ScreenIdentifier;
};

DETAIL_PHI_END_NAMESPACE()

#endif // PHI_WINDOW_PLATFORM_X11_WINDOW_IMPL_X11_HPP
