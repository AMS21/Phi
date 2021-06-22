# PhiWindow
project(PhiWindow LANGUAGES CXX)

file(GLOB PHI_WINDOW_HEADERS "include/Phi/Window/Window.hpp" "include/Phi/Window/WindowHandle.hpp"
     "src/WindowImpl.hpp")

file(GLOB PHI_WINDOW_SOURCES "src/Window.cpp" "src/WindowImpl.cpp")

# Platform
add_library(phi_window_platform INTERFACE)
add_library(Phi::WindowPlatform ALIAS phi_window_platform)

file(GLOB PHI_WINDOW_PLATFORM_WIN32_FILES "platform/Win32/Win32WindowImpl.cpp"
     "platform/Win32/Win32WindowImpl.hpp")

file(GLOB PHI_WINDOW_PLATFORM_X11_FILES "platform/X11/WindowImplX11.cpp"
     "platform/X11/WindowImplX11.hpp" "platform/X11/X11Display.cpp" "platform/X11/X11Display.hpp")

if(PHI_PLATFORM_WINDOWS)
  set(PHI_WINDOW_PLATFORM_FILES ${PHI_WINDOW_PLATFORM_WIN32_FILES})
  phi_log("Using Win32 for window creation")
elseif(PHI_PLATFORM_UNIX)
  # Find X11
  find_package(X11 REQUIRED)

  target_link_libraries(phi_window_platform INTERFACE X11::X11 X11::Xrandr X11::Xinerama X11::Xi)

  set(PHI_WINDOW_PLATFORM_FILES ${PHI_WINDOW_PLATFORM_X11_FILES})
  phi_log("Using X11 for window creation")
else()
  phi_warn("Unsupported platform for PhiWindow")
endif()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PHI_WINDOW_HEADERS} ${PHI_WINDOW_SOURCES}
                                                    ${PHI_WINDOW_PLATFORM_FILES})

# PhiWindow library
add_library(${PROJECT_NAME} STATIC ${PHI_WINDOW_HEADERS} ${PHI_WINDOW_SOURCES}
                                   ${PHI_WINDOW_PLATFORM_FILES})

# Alias targets
add_library(Phi::Window ALIAS ${PROJECT_NAME})

phi_enable_static_analyzers(${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC "include"
  PRIVATE "src" "platform")

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC Phi::Core Phi::WindowPlatform
  PRIVATE Phi::InternalProjectOptions)
