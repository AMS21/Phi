#ifndef INCG_PHI_TEST_TEST_MACROS_HPP
#define INCG_PHI_TEST_TEST_MACROS_HPP

#include <phi/phi_config.hpp>

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include <phi/compiler_support/counter.hpp>
#include <phi/compiler_support/noexcept.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/preprocessor/glue.hpp>
#include <phi/type_traits/is_same.hpp>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace test
{
    namespace detail
    {
        void CheckImpl(bool value, const char* expression, const char* file,
                       unsigned long long line_number, bool required, bool expected);

        struct register_test_case
        {
            explicit register_test_case(void (*func)()) PHI_NOEXCEPT;
        };

        void IncreaseSkipCount() PHI_NOEXCEPT;
    } // namespace detail
} // namespace test

DETAIL_PHI_END_NAMESPACE()

extern int main();

#define GET_TEST_CASE_NAME() PHI_GLUE(phi_test_function_, PHI_COUNTER())

#define DEFINE_TEST_CASE(name)                                                                     \
    /* NOLINTBEGIN */                                                                              \
    static void name();                                                                            \
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wglobal-constructors")                                  \
    static const ::phi::test::detail::register_test_case PHI_GLUE(name, _register){&(name)};       \
    PHI_CLANG_SUPPRESS_WARNING_POP()                                                               \
    static void name() /* NOLINTEND */

#define TEST_CASE(...) DEFINE_TEST_CASE(GET_TEST_CASE_NAME())

#define SECTION(...)

#define DETAIL_CALL_IMPL(required, expected, ...)                                                  \
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wuseless-cast")                                           \
    ::phi::test::detail::CheckImpl(static_cast<bool>(__VA_ARGS__), #__VA_ARGS__, __FILE__,         \
                                   __LINE__, required, expected);                                  \
    PHI_GCC_SUPPRESS_WARNING_POP()                                                                 \
    (void(0))

#define CHECK(...) DETAIL_CALL_IMPL(false, true, __VA_ARGS__)

#define CHECK_FALSE(...) DETAIL_CALL_IMPL(false, false, __VA_ARGS__)

#define REQUIRE(...) DETAIL_CALL_IMPL(true, true, __VA_ARGS__)

#define REQUIRE_FALSE(...) DETAIL_CALL_IMPL(true, false, __VA_ARGS__)

#define SKIP_CHECK() ::phi::test::detail::IncreaseSkipCount()

#define DETAIL_STATIC_REQUIRE_BEGIN()                                                              \
    PHI_GCC_SUPPRESS_WARNING_PUSH()                                                                \
    PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")                                                     \
    PHI_CLANG_SUPPRESS_WARNING_PUSH()                                                              \
    PHI_CLANG_SUPPRESS_WARNING("-Wunreachable-code")

#define DETAIL_STATIC_REQUIRE_END()                                                                \
    PHI_CLANG_SUPPRESS_WARNING_POP()                                                               \
    PHI_GCC_SUPPRESS_WARNING_POP()                                                                 \
    (void(0))

// Run all tests at runtime when gathering coverage data
#if defined(PHI_CONFIG_COVERAGE_BUILD)

#    define STATIC_REQUIRE(...) REQUIRE(__VA_ARGS__)

#    define STATIC_REQUIRE_FALSE(...) REQUIRE_FALSE(__VA_ARGS__)

#else

#    define STATIC_REQUIRE(...)                                                                    \
        DETAIL_STATIC_REQUIRE_BEGIN()                                                              \
        static_assert(static_cast<bool>(__VA_ARGS__), "PHI_STATIC_REQUIRE: " #__VA_ARGS__ " was "  \
                                                      "false");                                    \
        DETAIL_STATIC_REQUIRE_END()

#    define STATIC_REQUIRE_FALSE(...)                                                              \
        DETAIL_STATIC_REQUIRE_BEGIN()                                                              \
        static_assert(!static_cast<bool>(__VA_ARGS__),                                             \
                      "PHI_STATIC_REQUIRE_FALSE: " #__VA_ARGS__ " was true");                      \
        DETAIL_STATIC_REQUIRE_END()

#endif

#define CHECK_NOEXCEPT(...)                                                                        \
    DETAIL_STATIC_REQUIRE_BEGIN()                                                                  \
    static_assert(noexcept(__VA_ARGS__),                                                           \
                  "PHI_CHECK_NOEXCEPT: " #__VA_ARGS__ " should be declared noexcept but is not");  \
    DETAIL_STATIC_REQUIRE_END()

#define CHECK_NOT_NOEXCEPT(...)                                                                    \
    DETAIL_STATIC_REQUIRE_BEGIN()                                                                  \
    static_assert(!noexcept(__VA_ARGS__), "PHI_CHECK_NOT_NOEXCEPT: " #__VA_ARGS__                  \
                                          " should not be declared noexcept but is");              \
    DETAIL_STATIC_REQUIRE_END()

#define CHECK_SAME_TYPE(...)                                                                       \
    DETAIL_STATIC_REQUIRE_BEGIN()                                                                  \
    static_assert(::phi::is_same<__VA_ARGS__>::value,                                              \
                  "CHECK_SAME_TYPE: " #__VA_ARGS__ " should be the same type but aren't");         \
    DETAIL_STATIC_REQUIRE_END()

#define CHECK_NOT_SAME_TYPE(...)                                                                   \
    DETAIL_STATIC_REQUIRE_BEGIN()                                                                  \
    static_assert(::phi::is_not_same<__VA_ARGS__>::value,                                          \
                  "CHECK_NOT_SAME_TYPE: " #__VA_ARGS__ " should not be the same type but are");    \
    DETAIL_STATIC_REQUIRE_END()

#endif // INCG_PHI_TEST_TEST_MACROS_HPP
