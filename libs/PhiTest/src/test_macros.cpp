#include "phi/test/test_macros.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/types.hpp>
#include <phi/phi_config.hpp>
#include <cstdlib>
#include <forward_list>
#include <iostream>

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")
PHI_CLANG_SUPPRESS_WARNING("-Wexit-time-destructors")

static std::forward_list<phi::test::detail::TestSignature>& GetFunctionRegister() noexcept
{
    static std::forward_list<phi::test::detail::TestSignature> function_register;

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
                       unsigned long long line_number)
        {
            AssertCount += 1u;

            if (!value)
            {
                PrintFailure(expression, file, line_number);

                ReturnValue = 1;
            }
        }

        void CheckFalseImpl(bool value, const char* expression, const char* file,
                            unsigned long long line_number)
        {
            AssertCount += 1u;

            if (value)
            {
                PrintFailure(expression, file, line_number);

                ReturnValue = 1;
            }
        }

        void RequireImpl(bool value, const char* expression, const char* file,
                         unsigned long long line_number)
        {
            AssertCount += 1u;

            if (!value)
            {
                PrintFailure(expression, file, line_number);

                std::exit(1);
            }
        }

        void RequireFalseImpl(bool value, const char* expression, const char* file,
                              unsigned long long line_number)
        {
            AssertCount += 1u;

            if (value)
            {
                PrintFailure(expression, file, line_number);

                std::exit(1);
            }
        }

        register_test_case::register_test_case(TestSignature func) noexcept
        {
            GetFunctionRegister().emplace_front(func);
        }

        void IncreaseSkipCount() noexcept
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
    const std::forward_list<phi::test::detail::TestSignature>& function_register =
            GetFunctionRegister();
    for (phi::test::detail::TestSignature test_func_pointer : function_register)
    {
        test_func_pointer();
        test_case_count += 1u;
    }

    std::cout << "Test cases: " << test_case_count.unsafe() << '\n';
    std::cout << "Asserts:    " << AssertCount.unsafe() << '\n';
    std::cout << "Skipped:    " << SkipCount.unsafe() << '\n';

    return ReturnValue;
}
