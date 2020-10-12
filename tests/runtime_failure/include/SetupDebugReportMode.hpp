#ifndef INCG_PHI_TESTS_RUNTIME_FAILURE_SETUP_DEBUG_REPORT_MODE_HPP
#define INCG_PHI_TESTS_RUNTIME_FAILURE_SETUP_DEBUG_REPORT_MODE_HPP

#if defined(_WIN32)
#    include <crtdbg.h>
#endif

// This function setups the windows crt debug mode to not open any message boxes
void SetupDebugReportMode()
{
#if defined(_WIN32)
    // Crt errors
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);

    // Crt asserts
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
#endif
}

#endif // INCG_PHI_TESTS_RUNTIME_FAILURE_SETUP_DEBUG_REPORT_MODE_HPP
