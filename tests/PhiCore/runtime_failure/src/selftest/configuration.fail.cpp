#include <phi/compiler_support/extended_attributes.hpp>
#include <phi/phi_config.hpp>

PHI_ATTRIBUTE_CONST int main()
{
    // Only return a failure status in debug mode
#if defined(PHI_DEBUG)
    return 1;
#else
    return 0;
#endif
}
