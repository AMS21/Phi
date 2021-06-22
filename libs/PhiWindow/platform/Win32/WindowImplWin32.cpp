#include "Win32/WindowImplWin32.hpp"

#include <Phi/Core/Types.hpp>

namespace
{
    constexpr const char* ClassName = "Phi_Window";

    phi::u32 WindowCount = 0u;
} // namespace

DETAIL_PHI_BEGIN_NAMESPACE()

void WindowImplWin32::RegisterClassName()
{
    WNDCLASS windowClass{};

    windowClass.style         = 0;
    windowClass.lpfnWndProc   = &WindowImplWin32::GlobalWindowProcedure;
    windowClass.cbClsExtra    = 0;
    windowClass.cbWndExtra    = 0;
    windowClass.hInstance     = GetModuleHandle(nullptr);
    windowClass.hIcon         = nullptr;
    windowClass.hCursor       = 0;
    windowClass.hbrBackground = 0;
    windowClass.lpszMenuName  = nullptr;
    windowClass.lpszClassName = ClassName;

    RegisterClass(&windowClass);
}

LRESULT WindowImplWin32::GlobalWindowProcedure(HWND handle, UINT message, WPARAM wParam,
                                               LPARAM lParam)
{
    return DefWindowProc(handle, message, wParam, lParam);
}

DETAIL_PHI_END_NAMESPACE()
