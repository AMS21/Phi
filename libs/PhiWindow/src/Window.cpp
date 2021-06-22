#include "Phi/Window/Window.hpp"

#include "Phi/Core/Assert.hpp"
#include "WindowImpl.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

Window::Window()
    : m_WindowImpl(nullptr)
{}

Window::Window(const std::string& title)
    : m_WindowImpl(nullptr)
{
    Create(title);
}

Window::~Window()
{}

void Window::Create(const std::string& title)
{
    m_WindowImpl = detail::WindowImpl::create(title);
}

DETAIL_PHI_END_NAMESPACE()
