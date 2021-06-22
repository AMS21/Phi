#include "WindowImplX11.hpp"

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xrandr.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <cstring>
#include <utility>
#include <vector>

DETAIL_PHI_BEGIN_NAMESPACE()

WindowImplX11::WindowImplX11(WindowsHandle handle)
    : m_Window(handle)
    , m_Display()
    , m_ScreenIdentifier(0)
{}

WindowImplX11::WindowImplX11(phi::u32 width, phi::u32 height, const std::string& title)
    : m_Window(0)
    , m_Display()
    , m_ScreenIdentifier(DefaultScreen(m_Display.get()))
{
    m_Window = XCreateSimpleWindow(
            m_Display.get(), RootWindow(m_Display.get(), m_ScreenIdentifier.get()), 10, 10, 100,
            100, 1, BlackPixel(m_Display.get(), m_ScreenIdentifier.get()),
            WhitePixel(m_Display.get(), m_ScreenIdentifier.get()));
}

WindowImplX11::~WindowImplX11()
{
    if (m_Window != 0)
    {
        XDestroyWindow(m_Display.get(), m_Window);
        XFlush(m_Display.get());
    }
}

[[nodiscard]] WindowsHandle WindowImplX11::getOSHandle() const noexcept
{
    return m_Window;
}

DETAIL_PHI_END_NAMESPACE()
