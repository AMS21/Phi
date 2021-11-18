#include "Phi/Test/TestMacros.hpp"

#include <Phi/Config/Warning.hpp>
#include <Phi/PhiConfig.hpp>
#include <cstdlib>
#include <forward_list>
#include <iostream>
#include <memory>

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")
PHI_CLANG_SUPPRESS_WARNING("-Wexit-time-destructors")

static std::forward_list<phi::test::detail::TestSignature>& GetFunctionRegister() noexcept
{
    static std::forward_list<phi::test::detail::TestSignature> function_register;

    return function_register;
}

static int ReturnValue = 0;

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
            if (!value)
            {
                PrintFailure(expression, file, line_number);

                ReturnValue = 1;
            }
        }

        void CheckFalseImpl(bool value, const char* expression, const char* file,
                            unsigned long long line_number)
        {
            if (value)
            {
                PrintFailure(expression, file, line_number);

                ReturnValue = 1;
            }
        }

        void RequireImpl(bool value, const char* expression, const char* file,
                         unsigned long long line_number)
        {
            if (!value)
            {
                PrintFailure(expression, file, line_number);

                std::exit(1);
            }
        }

        void RequireFalseImpl(bool value, const char* expression, const char* file,
                              unsigned long long line_number)
        {
            if (value)
            {
                PrintFailure(expression, file, line_number);

                std::exit(1);
            }
        }

        RegisterTestCase::RegisterTestCase(TestSignature func) noexcept
        {
            GetFunctionRegister().emplace_front(func);
        }
    } // namespace detail
} // namespace test

DETAIL_PHI_END_NAMESPACE()

int main()
{
    // Run all registered tests
    for (phi::test::detail::TestSignature test_func_pointer : GetFunctionRegister())
    {
        test_func_pointer();
    }

    return ReturnValue;
}
