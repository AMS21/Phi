#include "phi/core/assert.hpp"

#include <cstdio>
#include <cstdlib>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    PHI_NORETURN void phi_assert_failure_handler(const char* condition, const char* file,
                                                 int line_number, const char* function) noexcept
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
