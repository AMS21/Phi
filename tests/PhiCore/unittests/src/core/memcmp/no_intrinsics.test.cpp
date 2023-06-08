#define PHI_SUPPORTS_MEMCMP_CONSTEXPR() 0
#define PHI_SUPPORTS_MEMCMP()           0

#include "phi/type_traits/is_constant_evaluated.hpp"

#undef PHI_HAS_WORKING_IS_CONSTANT_EVALUATED
#define PHI_HAS_WORKING_IS_CONSTANT_EVALUATED() 0

#include "value.test.cpp" // NOLINT(bugprone-suspicious-include)
