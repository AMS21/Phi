/*!
 * \file Platform.hpp
 * \brief Defines macros to determine the platform being used.
 *
**/
#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_PLATFORM_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_PLATFORM_HPP

#define PHI_PLATFORM_ANDROID()       0
#define PHI_PLATFORM_APPLE()         0
#define PHI_PLATFORM_BSD()           0
#define PHI_PLATFORM_DOS()           0
#define PHI_PLATFORM_FREEBSD()       0
#define PHI_PLATFORM_IOS()           0
#define PHI_PLATFORM_IOS_SIMULATOR() 0
#define PHI_PLATFORM_LINUX()         0
#define PHI_PLATFORM_MACOS()         0
#define PHI_PLATFORM_OPENBSD()       0
#define PHI_PLATFORM_SOLARIS()       0
#define PHI_PLATFORM_UNIX()          0
#define PHI_PLATFORM_WEB()           0
#define PHI_PLATFORM_WINDOWS()       0

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#    undef PHI_PLATFORM_WINDOWS
#    undef PHI_PLATFORM_DOS
#    define PHI_PLATFORM_DOS()     1
#    define PHI_PLATFORM_WINDOWS() 1
#    define PHI_PLATFORM_NAME()    "Windows"
#elif defined(__APPLE__) && defined(__MACH__)
#    undef PHI_PLATFORM_APPLE
#    undef PHI_PLATFORM_UNIX
#    define PHI_PLATFORM_APPLE() 1
#    define PHI_PLATFORM_UNIX()  1

// Apple platform, see which one it is
// Reference: https://opensource.apple.com/source/CarbonHeaders/CarbonHeaders-18.1/TargetConditionals.h.auto.html
#    include "TargetConditionals.h"
#    if defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR == 1
#        undef PHI_PLATFORM_IOS
#        undef PHI_PLATFORM_IOS_SIMULATOR
#        define PHI_PLATFORM_IOS()           1
#        define PHI_PLATFORM_IOS_SUMULATOR() 1
#        define PHI_PLATFORM_NAME()          "iOS Simulator"
#    elif defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE == 1
#        undef PHI_PLATFORM_IOS
#        define PHI_PLATFORM_IOS()  1
#        define PHI_PLATFORM_NAME() "iOS"
#    elif (defined(TARGET_OS_MAC) && TARGET_OS_MAC == 1) ||                                        \
            (defined(TARGET_OS_OSX) && TARGET_OS_OSX == 1)
#        undef PHI_PLATFORM_MACOS
#        define PHI_PLATFORM_MACOS() 1
#        define PHI_PLATFORM_NAME()  "MacOS"
#    else
#        warning "Unknown Apple based operating system"
#        define PHI_PLATFORM_NAME() "Unknown"
#    endif
#elif defined(unix) || defined(__unix__) || defined(__unix) // Unix based OS
#    undef PHI_PLATFORM_UNIX
#    define PHI_PLATFORM_UNIX() 1

#    if defined(__ANDROID__)
#        undef PHI_PLATFORM_ANDROID
#        define PHI_PLATFORM_ANDOIRD() 1
#        define PHI_PLATFORM_NAME()    "Android"
#    elif defined(linux) || defined(__linux) || defined(__linux__)
#        undef PHI_PLATFORM_LINUX
#        define PHI_PLATFORM_LINUX() 1
#        define PHI_PLATFORM_NAME()  "Linux"
#    elif defined(__FreeBSD__)
#        undef PHI_PLATFORM_BSD
#        undef PHI_PLATFORM_FREEBSD
#        define PHI_PLATFORM_BSD()     1
#        define PHI_PLATFORM_FREEBSD() 1
#        define PHI_PLATFORM_NAME()    "FreeBSD"
#    elif defined(__OpenBSD__)
#        undef PHI_PLATFORM_BSD
#        undef PHI_PLATFORM_OPENBSD
#        define PHI_PLATFORM_BSD()     1
#        define PHI_PLATFORM_OPENBSD() 1
#        define PHI_PLATFORM_NAME()    "OpenBSD"
#    elif defined(__EMSCRIPTEN__)
#        undef PHI_PLATFORM_WEB
#        define PHI_PLATFORM_WEB()  1
#        define PHI_PLATFORM_NAME() "Web"
#    else
#        define PHI_PLATFORM_NAME() "Unknown"
#        warning "Unknown Unix based operating system"
#    endif
#elif defined(__sun) && defined(__SVR4)
#    undef PHI_PLATFORM_UNIX
#    undef PHI_PLATFORM_SOLARIS
#    define PHI_PLATFORM_UNIX()    1
#    define PHI_PLATFORM_SOLARIS() 1
#    define PHI_PLATFORM_NAME()    "Solaris"
#else
#    define PHI_PLATFORM_NAME() "Unknown"
#    warning "Platform could not be detected"
#endif

#define PHI_PLATFORM_IS(platform) (PHI_PLATFORM_##platform())

#define PHI_PLATFORM_IS_NOT(platform) (!(PHI_PLATFORM_IS(platform)))

#endif // INCG_CPPBASE_OS_HPP
