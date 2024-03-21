#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>
#include <phi/core/assert.hpp>
#include <phi/core/declval.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/ptrdiff_t.hpp>
#include <phi/type_traits/integral_constant.hpp>
#include <phi/type_traits/is_null_pointer.hpp>
#include <phi/type_traits/void_t.hpp>
#include <cstddef> // std::nullptr_t

PHI_MSVC_SUPPRESS_WARNING(4127) // conditional expression is constant
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wzero-as-null-pointer-constant")

struct A
{
    A(phi::nullptr_t)
    {}
};

#if PHI_COMPILER_IS_BELOW(GCC, 8, 0, 0)
PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wunused-but-set-variable")
#endif

template <typename TypeT>
void test_conversions_impl()
{
    TypeT pointer_zero = 0;
    PHI_RELEASE_ASSERT(pointer_zero == nullptr, "pointer_zero == nullptr");

    TypeT pointer_nullptr = nullptr;
    PHI_RELEASE_ASSERT(pointer_nullptr == nullptr, "pointer_nullptr == nullptr");
    PHI_RELEASE_ASSERT(nullptr == pointer_nullptr, "nullptr == pointer_nullptr");
    PHI_RELEASE_ASSERT(!(pointer_nullptr != nullptr), "pointer_nullptr != nullptr");
    PHI_RELEASE_ASSERT(!(nullptr != pointer_nullptr), "nullptr != pointer_nullptr");
}

#if PHI_COMPILER_IS_BELOW(GCC, 8, 0, 0)
PHI_GCC_SUPPRESS_WARNING_POP()
#endif

template <typename TypeT>
void test_conversions()
{
    test_conversions_impl<TypeT>();
    test_conversions_impl<const TypeT>();
    test_conversions_impl<volatile TypeT>();
    test_conversions_impl<const volatile TypeT>();
}

template <typename TypeT, typename = void>
struct has_less : public phi::false_type
{};

template <typename TypeT>
struct has_less<TypeT, typename phi::void_t<decltype(phi::declval<TypeT>() < nullptr)>>
    : public phi::true_type
{};

#if PHI_COMPILER_IS_BELOW(GCC, 8, 0, 0)
PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wunused-but-set-variable")
#endif

template <typename TypeT>
void test_comparisons_impl()
{
    TypeT pointer = nullptr;

    PHI_RELEASE_ASSERT(pointer == nullptr, "pointer == nullptr");
    PHI_RELEASE_ASSERT(!(pointer != nullptr), "pointer != nullptr");
    PHI_RELEASE_ASSERT(nullptr == pointer, "nullptr == pointer");
    PHI_RELEASE_ASSERT(!(nullptr != pointer), "nullptr != pointer");
}

#if PHI_COMPILER_IS_BELOW(GCC, 8, 0, 0)
PHI_GCC_SUPPRESS_WARNING_POP()
#endif

template <typename TypeT>
void test_comparisons()
{
    test_comparisons_impl<TypeT>();
    test_comparisons_impl<const TypeT>();
    test_comparisons_impl<volatile TypeT>();
    test_comparisons_impl<const volatile TypeT>();
}

PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wnull-conversion")

void test_nullptr_conversions()
{
    bool boolean(nullptr); // NOLINT(readability-implicit-bool-conversion)
    PHI_RELEASE_ASSERT(!boolean, "!boolean");
}

PHI_CLANG_SUPPRESS_WARNING_POP()

TEST_CASE("core.nullptr_t")
{
    STATIC_REQUIRE(sizeof(phi::nullptr_t) == sizeof(void*));
    STATIC_REQUIRE(phi::is_null_pointer<phi::nullptr_t>::value);
    CHECK_SAME_TYPE(phi::nullptr_t, decltype(nullptr));

    // Standard compatibility
    CHECK_SAME_TYPE(phi::nullptr_t, std::nullptr_t);

    test_conversions<phi::nullptr_t>();
    test_conversions<void*>();
    test_conversions<int*>();
    test_conversions<A*>();
    test_conversions<void (*)()>();
    test_conversions<void (A::*)()>();
    test_conversions<int A::*>();

    // Test for http://wg21.link/CWG583
    // GCC implements this starting with version 12
#if PHI_COMPILER_WORKAROUND(GCC, 12, 0, 0)
    STATIC_REQUIRE_FALSE(has_less<phi::nullptr_t>::value);
#endif

    test_comparisons<phi::nullptr_t>();
    test_comparisons<void*>();
    test_comparisons<int*>();
    test_comparisons<A*>();
    test_comparisons<void (*)()>();
    test_comparisons<void (A::*)()>();
    test_comparisons<int A::*>();

    test_nullptr_conversions();

    phi::ptrdiff_t diff = reinterpret_cast<phi::ptrdiff_t>(nullptr);
    CHECK(diff == 0);
}
