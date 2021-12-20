#ifndef INCG_PHI_TEST_TEST_MACROS_HPP
#define INCG_PHI_TEST_TEST_MACROS_HPP

#include <phi/phi_config.hpp>

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include <phi/compiler_support/counter.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/preprocessor/function_like_macro.hpp>
#include <phi/preprocessor/glue.hpp>
#include <phi/type_traits/is_same.hpp>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace test
{
    namespace detail
    {
        using TestSignature = void (*)();

        void CheckImpl(bool value, const char* expression, const char* file,
                       unsigned long long line_number);

        void CheckFalseImpl(bool value, const char* expression, const char* file,
                            unsigned long long line_number);

        void RequireImpl(bool value, const char* expression, const char* file,
                         unsigned long long line_number);

        void RequireFalseImpl(bool value, const char* expression, const char* file,
                              unsigned long long line_number);

        struct RegisterTestCase
        {
            explicit RegisterTestCase(TestSignature func) noexcept;
        };
    } // namespace detail
} // namespace test

DETAIL_PHI_END_NAMESPACE()

extern int main();

#define GET_TEST_CASE_NAME() PHI_GLUE(phi_test_function_, PHI_COUNTER())

#define DEFINE_TEST_CASE(name)                                                                     \
    static void name();                                                                            \
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wglobal-constructors")                                  \
    static ::phi::test::detail::RegisterTestCase PHI_GLUE(name, _register){&(name)};               \
    PHI_CLANG_SUPPRESS_WARNING_POP()                                                               \
    static void name()

#define TEST_CASE(...) DEFINE_TEST_CASE(GET_TEST_CASE_NAME())

#define SECTION(...)

#define DETAIL_CALL_IMPL(impl_name, ...)                                                           \
    PHI_BEGIN_MACRO()                                                                              \
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wuseless-cast")                                           \
    ::phi::test::detail::PHI_GLUE(, impl_name)(static_cast<bool>(__VA_ARGS__), #__VA_ARGS__,       \
                                               __FILE__, __LINE__);                                \
    PHI_GCC_SUPPRESS_WARNING_POP()                                                                 \
    PHI_END_MACRO()

#define CHECK(...) DETAIL_CALL_IMPL(CheckImpl, __VA_ARGS__)

#define CHECK_FALSE(...) DETAIL_CALL_IMPL(CheckFalseImpl, __VA_ARGS__)

#define REQUIRE(...) DETAIL_CALL_IMPL(RequireImpl, __VA_ARGS__)

#define REQUIRE_FALSE(...) DETAIL_CALL_IMPL(RequireFalseImpl, __VA_ARGS__)

#define STATIC_REQUIRE(...)                                                                        \
    PHI_BEGIN_MACRO()                                                                              \
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wuseless-cast")                                           \
    static_assert(static_cast<bool>(__VA_ARGS__), "PHI_STATIC_REQUIRE: " #__VA_ARGS__ " was "      \
                                                  "false");                                        \
    REQUIRE(__VA_ARGS__);                                                                          \
    PHI_GCC_SUPPRESS_WARNING_POP()                                                                 \
    PHI_END_MACRO()

#define STATIC_REQUIRE_FALSE(...)                                                                  \
    PHI_BEGIN_MACRO()                                                                              \
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wuseless-cast")                                           \
    static_assert(!static_cast<bool>(__VA_ARGS__),                                                 \
                  "PHI_STATIC_REQUIRE_FALSE: " #__VA_ARGS__ " was true");                          \
    REQUIRE_FALSE(__VA_ARGS__);                                                                    \
    PHI_GCC_SUPPRESS_WARNING_POP()                                                                 \
    PHI_END_MACRO()

#define CHECK_NOEXCEPT(...)                                                                        \
    PHI_BEGIN_MACRO()                                                                              \
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wuseless-cast")                                           \
    static_assert(noexcept(__VA_ARGS__),                                                           \
                  "PHI_CHECK_NOEXCEPT: " #__VA_ARGS__ " should be declared noexcept but is not");  \
    PHI_GCC_SUPPRESS_WARNING_POP()                                                                 \
    PHI_END_MACRO()

#define CHECK_NOT_NOEXCEPT(...)                                                                    \
    PHI_BEGIN_MACRO()                                                                              \
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wuseless-cast")                                           \
    static_assert(!noexcept(__VA_ARGS__), "PHI_CHECK_NOT_NOEXCEPT: " #__VA_ARGS__                  \
                                          " should not be declared noexcept but is");              \
    PHI_GCC_SUPPRESS_WARNING_POP()                                                                 \
    PHI_END_MACRO()

#define CHECK_SAME_TYPE(...) STATIC_REQUIRE(::phi::is_same<__VA_ARGS__>::value)

#define CHECK_NOT_SAME_TYPE(...) STATIC_REQUIRE_FALSE(::phi::is_same<__VA_ARGS__>::value)

#endif // INCG_PHI_TEST_TEST_MACROS_HPP
