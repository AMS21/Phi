#include <phi/phi_config.hpp>

int main()
{
    // Only return a failure status in debug mode
#if defined(PHI_DEBUG)
    return 1;
#else
    return 0;
#endif
}
