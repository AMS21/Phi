#ifndef INCG_PHI_WINDOW_WINDOW_HANDLE_HPP
#define INCG_PHI_WINDOW_WINDOW_HANDLE_HPP

#include "Phi/Config/Platform.hpp"
#include "Phi/PhiConfig.hpp"

#if PHI_PLATFORM_IS(WINDOWS)
struct HWND__;
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_PLATFORM_IS(WINDOWS)
using WindowHandle = HWND__*;
#elif PHI_PLATFORM_IS(UNIX)
using WindowsHandle = unsigned long;
#else
#    error "No WindowHandle defined for the current platform"
#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_WINDOW_WINDOW_HANDLE_HPP
