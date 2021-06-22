#ifndef INCG_PHI_WINDOW_WINDOW_HPP
#define INCG_PHI_WINDOW_WINDOW_HPP

#include "Phi/Core/Boolean.hpp"
#include "Phi/PhiConfig.hpp"
#include <string>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    class WindowImpl;
}

class Window
{
public:
    Window();

    Window(const std::string& title);

    ~Window();

    void Create(const std::string& title);

private:
    detail::WindowImpl* m_WindowImpl;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_WINDOW_WINDOW_HPP
