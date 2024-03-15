#include "phi/core/assert.hpp"

#include "phi/compiler_support/compiler.hpp"
#include <cstdio>
#include <cstdlib>

// NOTE: Cheerp defines stderr as a macro which causes a 'disabled expansion of recursive macro' warning
#if PHI_COMPILER_IS(CHEERP)
#    undef stderr
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    PHI_NORETURN void phi_assert_failure_handler(const char* condition, const char* file,
                                                 int line_number, const char* function) PHI_NOEXCEPT
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
        (void)std::fprintf(stderr,
                           "ASSERTION VIOLATION\n"
                           "condition: %s\n"
                           "file:      %s (%d)\n"
                           "function:  %s\n",
                           condition, file, line_number, function);

        // Flush stderr
        (void)std::fflush(stderr);

        std::abort();
    }
} // namespace detail

DETAIL_PHI_END_NAMESPACE()
