#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/type_system/max.hpp>
#include <limits>

template <typename TypeT>
void type_system_max_std_impl()
{
    PHI_CLANG_AND_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wfloat-equal")

    STATIC_REQUIRE(phi::type_system::max<TypeT>() == std::numeric_limits<TypeT>::max());

    // NOTE: Needed as a workaround for glibcxx's max causing the `implicit-signed-integer-truncation` to fire
    // see: https://godbolt.org/z/8Yqff34P4
    static constexpr TypeT max_value = std::numeric_limits<TypeT>::max();
    CHECK(phi::type_system::max<TypeT>() == max_value);

    CHECK_NOEXCEPT(phi::type_system::max<TypeT>());

    PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()
}

template <typename TypeT>
void type_system_max_std()
{
    type_system_max_std_impl<TypeT>();
    type_system_max_std_impl<const TypeT>();
    type_system_max_std_impl<volatile TypeT>();
    type_system_max_std_impl<const volatile TypeT>();
}

template <typename TypeT>
void type_system_max_safe_impl()
{
    PHI_CLANG_AND_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wfloat-equal")

    STATIC_REQUIRE(phi::type_system::max<TypeT>().unsafe() ==
                   phi::type_system::max<typename TypeT::value_type>());
    CHECK(phi::type_system::max<TypeT>().unsafe() ==
          phi::type_system::max<typename TypeT::value_type>());

    CHECK_NOEXCEPT(phi::type_system::max<TypeT>());

    PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()
}

template <typename TypeT>
void type_system_max_safe()
{
    type_system_max_safe_impl<TypeT>();
    type_system_max_safe_impl<const TypeT>();
    type_system_max_safe_impl<volatile TypeT>();
    type_system_max_safe_impl<const volatile TypeT>();
}

TEST_CASE("type_system.max")
{
    type_system_max_std<bool>();

    // char types
    type_system_max_std<char>();
    type_system_max_std<wchar_t>();
    type_system_max_std<char8_t>();
    type_system_max_std<char16_t>();
    type_system_max_std<char32_t>();

    // Signed integer types
    type_system_max_std<signed char>();
    type_system_max_std<short>();
    type_system_max_std<int>();
    type_system_max_std<long>();
    type_system_max_std<long long>();

    // Unsigned integer types
    type_system_max_std<unsigned char>();
    type_system_max_std<unsigned short>();
    type_system_max_std<unsigned>();
    type_system_max_std<unsigned long>();
    type_system_max_std<unsigned long long>();

    // floating point types
    type_system_max_std<float>();
    type_system_max_std<double>();
    type_system_max_std<long double>();
    //static_assert(__LDBL_MAX__ < 0.0f, "");

    // Safe types

    type_system_max_safe<phi::boolean>();

    type_system_max_safe<phi::integer<signed char>>();
    type_system_max_safe<phi::integer<short>>();
    type_system_max_safe<phi::integer<int>>();
    type_system_max_safe<phi::integer<long>>();
    type_system_max_safe<phi::integer<long long>>();

    type_system_max_safe<phi::integer<unsigned char>>();
    type_system_max_safe<phi::integer<unsigned short>>();
    type_system_max_safe<phi::integer<unsigned>>();
    type_system_max_safe<phi::integer<unsigned long>>();
    type_system_max_safe<phi::integer<unsigned long long>>();

    type_system_max_safe<phi::floating_point<float>>();
    type_system_max_safe<phi::floating_point<double>>();
    type_system_max_safe<phi::floating_point<long double>>();
}
