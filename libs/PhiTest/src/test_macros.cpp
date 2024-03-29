#include "phi/test/test_macros.hpp"

#include <phi/compiler_support/likely.hpp>
#include <phi/compiler_support/noexcept.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/types.hpp>
#include <phi/phi_config.hpp>
#include <cstdlib>
#include <forward_list>
#include <iostream>

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")
PHI_CLANG_SUPPRESS_WARNING("-Wexit-time-destructors")

static std::forward_list<void (*)()>& GetFunctionRegister() PHI_NOEXCEPT
{
    static std::forward_list<void (*)()> function_register;

    return function_register;
}

static int ReturnValue{0}; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

static phi::u64 AssertCount{0u}; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

static phi::u64 SkipCount{0u}; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

PHI_CLANG_SUPPRESS_WARNING_POP()

static void PrintFailure(const char* expression, const char* file, unsigned long long line_number)
{
    std::cerr << "[PHI_TEST]: CHECK FAILED!\n Expression: " << expression << "\n File: " << file
              << ":" << line_number << '\n';

    // Always flush cerr
    std::cerr.flush();
}

DETAIL_PHI_BEGIN_NAMESPACE()

namespace test
{
    namespace detail
    {
        void CheckImpl(bool value, const char* expression, const char* file,
                       unsigned long long line_number, bool required, bool expected)
        {
            AssertCount += 1u;

            if (PHI_UNLIKELY(value != expected))
            {
                PrintFailure(expression, file, line_number);

                if (required)
                {
                    std::exit(EXIT_FAILURE);
                }

                ReturnValue = 1;
            }
        }

        register_test_case::register_test_case(void (*func)()) PHI_NOEXCEPT
        {
            GetFunctionRegister().emplace_front(func);
        }

        void IncreaseSkipCount() PHI_NOEXCEPT
        {
            SkipCount += 1u;
        }
    } // namespace detail
} // namespace test

DETAIL_PHI_END_NAMESPACE()

int main()
{
    phi::u64 test_case_count{0u};

    // Run all registered tests
    const std::forward_list<void (*)()>& function_register = GetFunctionRegister();
    for (void (*test_func_pointer)() : function_register)
    {
        test_func_pointer();
        test_case_count += 1u;
    }

    std::cout << "Test cases: " << test_case_count.unsafe() << '\n';
    std::cout << "Asserts:    " << AssertCount.unsafe() << '\n';
    std::cout << "Skipped:    " << SkipCount.unsafe() << '\n';

    return ReturnValue;
}
