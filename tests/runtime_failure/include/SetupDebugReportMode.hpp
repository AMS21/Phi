#ifndef INCG_PHI_TESTS_RUNTIME_FAILURE_SETUP_DEBUG_REPORT_MODE_HPP
#define INCG_PHI_TESTS_RUNTIME_FAILURE_SETUP_DEBUG_REPORT_MODE_HPP

#if defined(_WIN32)
#    include <crtdbg.h>
#endif

// This function setups the windows crt debug mode to not open any message boxes
void SetupDebugReportMode()
{
#if defined(_WIN32)
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
#endif
}

#endif // INCG_PHI_TESTS_RUNTIME_FAILURE_SETUP_DEBUG_REPORT_MODE_HPP