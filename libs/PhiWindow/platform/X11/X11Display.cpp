#include "X11Display.hpp"

#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Log.hpp"
#include "Phi/Core/ObserverPtr.hpp"
#include "Phi/Core/Types.hpp"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <mutex>

namespace
{
    Display* shared_display = nullptr;
    phi::u32 reference_count{0u};

    std::mutex mutex;
} // namespace

[[nodiscard]] Display* OpenDisplay() noexcept
{
    std::unique_lock lock(mutex);

    if (reference_count == 0u)
    {
        shared_display = XOpenDisplay(nullptr);

        if (!shared_display)
        {
            PHI_LOG_CORE_ERROR("Failed to open X11 display");
            return nullptr;
        }
    }

    reference_count++;
    return shared_display;
}

void CloseDisplay(Display* display) noexcept
{
    std::unique_lock lock(mutex);

    PHI_ASSERT(display == shared_display);

    reference_count--;

    if (reference_count == 0u)
    {
        XCloseDisplay(display);
    }
}

DETAIL_PHI_BEGIN_NAMESPACE()

X11Display::X11Display() noexcept
    : m_Display(OpenDisplay())
{}

X11Display::~X11Display() noexcept
{
    CloseDisplay(get());
}

[[nodiscard]] ::Display* X11Display::get() const noexcept
{
    return m_Display;
}

DETAIL_PHI_END_NAMESPACE()
