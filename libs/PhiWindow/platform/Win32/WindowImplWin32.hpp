#ifndef INCG_PHI_WINDOW_PLATFORM_WINDOW_IMPL_WIN32_HPP
#define INCG_PHI_WINDOW_PLATFORM_WINDOW_IMPL_WIN32_HPP

#include "Phi/PhiConfig.hpp"
#include "Phi/Window/WindowHandle.hpp"
#include "WindowImpl.hpp"
#include <Windows.h>

DETAIL_PHI_BEGIN_NAMESPACE()

class WindowImplWin32 : detail::WindowImpl
{
public:
    WindowImplWin32(WindowHandle handle);

    ~WindowImplWin32();

private:
    static void RegisterClassName();

    static LRESULT CALLBACK GlobalWindowProcedure(HWND handle, UINT message, WPARAM wParam,
                                                  LPARAM lParam);
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_WINDOW_PLATFORM_WINDOW_IMPL_WIN32_HPP
