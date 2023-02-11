#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/type_system/min.hpp>
#include <limits>

template <typename TypeT>
void type_system_min_std_impl()
{
    PHI_CLANG_AND_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wfloat-equal")

    STATIC_REQUIRE(phi::type_system::min<TypeT>() == std::numeric_limits<TypeT>::min());
    CHECK(phi::type_system::min<TypeT>() == std::numeric_limits<TypeT>::min());

    CHECK_NOEXCEPT(phi::type_system::min<TypeT>());

    PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()
}

template <typename TypeT>
void type_system_min_std()
{
    type_system_min_std_impl<TypeT>();
    type_system_min_std_impl<const TypeT>();
    type_system_min_std_impl<volatile TypeT>();
    type_system_min_std_impl<const volatile TypeT>();
}

template <typename TypeT>
void type_system_min_safe_impl()
{
    PHI_CLANG_AND_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wfloat-equal")

    STATIC_REQUIRE(phi::type_system::min<TypeT>().unsafe() ==
                   phi::type_system::min<typename TypeT::value_type>());
    CHECK(phi::type_system::min<TypeT>().unsafe() ==
          phi::type_system::min<typename TypeT::value_type>());

    CHECK_NOEXCEPT(phi::type_system::min<TypeT>());

    PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()
}

template <typename TypeT>
void type_system_min_safe()
{
    type_system_min_safe_impl<TypeT>();
    type_system_min_safe_impl<const TypeT>();
    type_system_min_safe_impl<volatile TypeT>();
    type_system_min_safe_impl<const volatile TypeT>();
}

TEST_CASE("type_system.min")
{
    type_system_min_std<bool>();

    // char types
    type_system_min_std<char>();
    type_system_min_std<wchar_t>();
    type_system_min_std<char8_t>();
    type_system_min_std<char16_t>();
    type_system_min_std<char32_t>();

    // Signed integer types
    type_system_min_std<signed char>();
    type_system_min_std<short>();
    type_system_min_std<int>();
    type_system_min_std<long>();
    type_system_min_std<long long>();

    // Unsigned integer types
    type_system_min_std<unsigned char>();
    type_system_min_std<unsigned short>();
    type_system_min_std<unsigned>();
    type_system_min_std<unsigned long>();
    type_system_min_std<unsigned long long>();

    // floating point types
    type_system_min_std<float>();
    type_system_min_std<double>();
    type_system_min_std<long double>();

    // Safe types

    type_system_min_safe<phi::boolean>();

    type_system_min_safe<phi::integer<signed char>>();
    type_system_min_safe<phi::integer<short>>();
    type_system_min_safe<phi::integer<int>>();
    type_system_min_safe<phi::integer<long>>();
    type_system_min_safe<phi::integer<long long>>();

    type_system_min_safe<phi::integer<unsigned char>>();
    type_system_min_safe<phi::integer<unsigned short>>();
    type_system_min_safe<phi::integer<unsigned>>();
    type_system_min_safe<phi::integer<unsigned long>>();
    type_system_min_safe<phi::integer<unsigned long long>>();

    type_system_min_safe<phi::floating_point<float>>();
    type_system_min_safe<phi::floating_point<double>>();
    type_system_min_safe<phi::floating_point<long double>>();
}
