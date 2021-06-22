#include "WindowImpl.hpp"

#include "Phi/Config/Platform.hpp"
#include "Phi/Core/Boolean.hpp"

#if PHI_PLATFORM_IS(WINDOWS)

#    include "Win32/WindowImplWin32.hpp"
using WindowImplType = phi::WindowImplWin32;

#elif PHI_PLATFORM_IS(UNIX)

#    include "X11/WindowImplX11.hpp"
using WindowImplType = phi::WindowImplX11;

#else

#    error "No window implementation found for current platform"

#endif

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    WindowImpl* WindowImpl::create(const std::string& title)
    {
        return new WindowImplType(800u, 600u, title);
    }
} // namespace detail

DETAIL_PHI_END_NAMESPACE()
