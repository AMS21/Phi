#include "SetupDebugReportMode.hpp"

int main()
{
    SetupDebugReportMode();

    throw "Exception which will not be caught";
}
