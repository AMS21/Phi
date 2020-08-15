#include <Phi/PhiConfig.hpp>

int main()
{
    // Only return a failure status in debug mode
#if PHI_DEBUG
    return 1;
#else
    return 0;
#endif
}
