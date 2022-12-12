#ifndef INCG_PHI_TESTS_RUNTIME_FAILURE_SETUP_RUNTIME_FAILURE_HPP
#define INCG_PHI_TESTS_RUNTIME_FAILURE_SETUP_RUNTIME_FAILURE_HPP

#include "SetupDebugReportMode.hpp"
#include <phi/compiler_support/warning.hpp>
#include <csignal>
#include <cstdlib>

extern "C" [[noreturn]] inline void RuntimeFailureSignalHandler(int /*signal*/)
{
    // Change exit code to 1
    std::exit(1);
}

static void SetupRuntimeFailure()
{
    // Needed for windows to not open a message box in debug mode
    SetupDebugReportMode();

    // Register signal handlers
    (void)std::signal(SIGABRT, RuntimeFailureSignalHandler);
    (void)std::signal(SIGTERM, RuntimeFailureSignalHandler);
}

#endif // INCG_PHI_TESTS_RUNTIME_FAILURE_SETUP_RUNTIME_FAILURE_HPP
