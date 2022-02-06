#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/string_equals.hpp>
#include <phi/algorithm/string_length.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/container/string_view.hpp>
#include <phi/core/move.hpp>
#include <phi/core/types.hpp>
#include <phi/type_traits/is_trivially_copyable.hpp>
#include <limits>
#include <utility>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

// Workaround for std::reverse_iterator not being constexpr until C++-17
// TODO: Remove once we added our own reverse_iterator implementation
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
#    define REQUIRE_17(...) STATIC_REQUIRE(__VA_ARGS__)
#else
#    define REQUIRE_17(...) REQUIRE(__VA_ARGS__)
#endif

TEST_CASE("BasicStringView", "[Container][StringView]")
{
    SECTION("default constructor")
    {
        EXT_CONSTEXPR_RUNTIME phi::string_view view;

        EXT_STATIC_REQUIRE(view.data() == nullptr);
        EXT_STATIC_REQUIRE(view.length() == 0u);
        EXT_STATIC_REQUIRE(view.is_empty());
        EXT_STATIC_REQUIRE(view.is_null());
    }

    SECTION("BasicStringView(CharT*)")
    {
        EXT_CONSTEXPR_RUNTIME phi::string_view view("Hello World");

        EXT_STATIC_REQUIRE(phi::string_equals(view.data(), "Hello World"));
        EXT_STATIC_REQUIRE(view.length() == 11u);
        EXT_STATIC_REQUIRE_FALSE(view.is_empty());
        EXT_STATIC_REQUIRE_FALSE(view.is_null());
    }

    SECTION("BasicStringView(CharT*, length_type)")
    {
        EXT_CONSTEXPR_RUNTIME phi::string_view view("Hello World", 11u);

        EXT_STATIC_REQUIRE(phi::string_equals(view.data(), "Hello World"));
        EXT_STATIC_REQUIRE(view.length() == 11u);
        EXT_STATIC_REQUIRE_FALSE(view.is_empty());
        EXT_STATIC_REQUIRE_FALSE(view.is_null());

        EXT_CONSTEXPR_RUNTIME phi::string_view view2("Hello World", 5u);
        EXT_STATIC_REQUIRE(view2.length() == 5u);
        EXT_STATIC_REQUIRE(view2.back() == 'o');
        EXT_STATIC_REQUIRE_FALSE(view.is_empty());
        EXT_STATIC_REQUIRE_FALSE(view.is_null());
    }

    SECTION("copy constructor")
    {
        EXT_CONSTEXPR_RUNTIME phi::string_view base_view;
        EXT_CONSTEXPR_RUNTIME phi::string_view copy_view(base_view);

        EXT_STATIC_REQUIRE(copy_view.data() == nullptr);
        EXT_STATIC_REQUIRE(copy_view.length() == 0u);
        EXT_STATIC_REQUIRE(copy_view.is_empty());
        EXT_STATIC_REQUIRE(copy_view.is_null());

        EXT_CONSTEXPR_RUNTIME phi::string_view base_view2("Hello World");
        EXT_CONSTEXPR_RUNTIME phi::string_view copy_view2(base_view2);

        EXT_STATIC_REQUIRE(phi::string_equals(copy_view2.data(), "Hello World"));
#if PHI_COMPILER_IS_NOT(MSVC)
        // TODO: For some reason MSVC fails this tests at runtime
        EXT_STATIC_REQUIRE(copy_view2.data() == base_view2.data());
#endif
        EXT_STATIC_REQUIRE(copy_view2.length() == 11u);
        EXT_STATIC_REQUIRE(copy_view2.length() == base_view2.length());
    }

    SECTION("move constructor")
    {
        EXT_CONSTEXPR_RUNTIME phi::string_view base_view;
        EXT_CONSTEXPR_RUNTIME phi::string_view move_view(phi::move(base_view));

        EXT_STATIC_REQUIRE(move_view.data() == nullptr);
        EXT_STATIC_REQUIRE(move_view.length() == 0u);

        EXT_CONSTEXPR_RUNTIME phi::string_view base_view2("Hello World");
        EXT_CONSTEXPR_RUNTIME phi::string_view move_view2(phi::move(base_view2));

        EXT_STATIC_REQUIRE(phi::string_equals(move_view2.data(), "Hello World"));
        EXT_STATIC_REQUIRE(move_view2.length() == 11u);
    }

    SECTION("operator=(const BasicStringView&)")
    {
        phi::string_view base_view;
        phi::string_view copy_view;

        copy_view = base_view;

        CHECK(copy_view.data() == nullptr);
        CHECK(copy_view.length() == 0u);

        phi::string_view base_view2("Hello World");
        phi::string_view copy_view2;

        copy_view2 = base_view2;

        CHECK(phi::string_equals(copy_view2.data(), "Hello World"));
        CHECK(base_view2 == copy_view2);
        CHECK(copy_view2.length() == 11u);
    }

    SECTION("operator=(BasicStringView&&)")
    {
        phi::string_view base_view;
        phi::string_view move_view;

        move_view = phi::move(base_view);

        CHECK(move_view.data() == nullptr);
        CHECK(move_view.length() == 0u);

        phi::string_view base_view2("Hello World");
        phi::string_view move_view2;

        move_view2 = phi::move(base_view2);

        CHECK(phi::string_equals(move_view2.data(), "Hello World"));
        CHECK(move_view2.length() == 11u);
    }

    SECTION("begin")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::string_view null_view;
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(null_view.begin() == nullptr);
#if PHI_COMPILER_IS_NOT(MSVC)
        EXT_STATIC_REQUIRE(test_view.begin() == str);
#endif
    }

    SECTION("end")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::string_view null_view;
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(null_view.end() == nullptr);
#if PHI_COMPILER_IS_NOT(MSVC)
        EXT_STATIC_REQUIRE(test_view.end() == (str + 4));
#endif
    }

    SECTION("cbegin")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::string_view null_view;
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(null_view.cbegin() == nullptr);
#if PHI_COMPILER_IS_NOT(MSVC)
        EXT_STATIC_REQUIRE(test_view.cbegin() == str);
#endif
    }

    SECTION("cend")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::string_view null_view;
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(null_view.cend() == nullptr);
#if PHI_COMPILER_IS_NOT(MSVC)
        EXT_STATIC_REQUIRE(test_view.cend() == (str + 4));
#endif
    }

    SECTION("rbegin")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::string_view null_view;
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view(str);

        REQUIRE_17(null_view.rbegin() == std::reverse_iterator<const char*>(nullptr));
#if PHI_COMPILER_IS_NOT(MSVC)
        REQUIRE_17(test_view.rbegin() == std::reverse_iterator<const char*>(str + 4));
#endif
    }

    SECTION("rend")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::string_view null_view;
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view(str);

        REQUIRE_17(null_view.rend() == std::reverse_iterator<const char*>(nullptr));
#if PHI_COMPILER_IS_NOT(MSVC)
        REQUIRE_17(test_view.rend() == std::reverse_iterator<const char*>(str));
#endif
    }

    SECTION("crbegin")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::string_view null_view;
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view(str);

        REQUIRE_17(null_view.crbegin() == std::reverse_iterator<const char*>(nullptr));
#if PHI_COMPILER_IS_NOT(MSVC)
        REQUIRE_17(test_view.crbegin() == std::reverse_iterator<const char*>(str + 4));
#endif
    }

    SECTION("crend")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::string_view null_view;
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view(str);

        REQUIRE_17(null_view.crend() == std::reverse_iterator<const char*>(nullptr));
#if PHI_COMPILER_IS_NOT(MSVC)
        REQUIRE_17(test_view.crend() == std::reverse_iterator<const char*>(str));
#endif
    }

    SECTION("length")
    {
        EXT_CONSTEXPR_RUNTIME phi::string_view null_view;
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view("Test");
        EXT_CONSTEXPR_RUNTIME phi::string_view short_view("Hello World", 5u);

        EXT_STATIC_REQUIRE(null_view.length() == 0u);
        EXT_STATIC_REQUIRE(test_view.length() == 4u);
        EXT_STATIC_REQUIRE(short_view.length() == 5u);
    }

    SECTION("max_length")
    {
        CONSTEXPR_RUNTIME phi::string_view view;
        STATIC_REQUIRE(std::numeric_limits<phi::usize>::max() == view.max_length());
    }

    SECTION("is_empty")
    {
        EXT_CONSTEXPR_RUNTIME phi::string_view null_view;
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view("Hello World");

        EXT_STATIC_REQUIRE(null_view.is_empty());
        EXT_STATIC_REQUIRE_FALSE(test_view.is_empty());
    }

    SECTION("is_null")
    {
        EXT_CONSTEXPR_RUNTIME phi::string_view null_view;
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view("Hello World");

        EXT_STATIC_REQUIRE(null_view.is_null());
        EXT_STATIC_REQUIRE_FALSE(test_view.is_null());
    }

    SECTION("operator[]/at()")
    {
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view("Test");

        EXT_STATIC_REQUIRE(test_view[0u] == 'T');
        EXT_STATIC_REQUIRE(test_view[1u] == 'e');
        EXT_STATIC_REQUIRE(test_view[2u] == 's');
        EXT_STATIC_REQUIRE(test_view[3u] == 't');

        EXT_STATIC_REQUIRE(test_view.at(0u) == 'T');
        EXT_STATIC_REQUIRE(test_view.at(1u) == 'e');
        EXT_STATIC_REQUIRE(test_view.at(2u) == 's');
        EXT_STATIC_REQUIRE(test_view.at(3u) == 't');
    }

    SECTION("front")
    {
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view("Test");
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view2("Hello World");

        EXT_STATIC_REQUIRE(test_view.front() == 'T');
        EXT_STATIC_REQUIRE(test_view2.front() == 'H');
    }

    SECTION("back")
    {
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view("Test");
        EXT_CONSTEXPR_RUNTIME phi::string_view test_view2("Hello World");

        EXT_STATIC_REQUIRE(test_view.back() == 't');
        EXT_STATIC_REQUIRE(test_view2.back() == 'd');
    }

    SECTION("data")
    {
        constexpr static const char* str = "Hello World";

        EXT_CONSTEXPR_RUNTIME phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(test_view.data() == str);
    }

    SECTION("clear")
    {
        phi::string_view view("Hello World");

        view.clear();

        CHECK(view.data() == nullptr);
        CHECK(view.is_empty());
        CHECK(view.is_null());
        CHECK(view.length() == 0u);
    }

    SECTION("add_prefix")
    {
        constexpr static const char* str = "Hello World";
        phi::string_view             view(str + 6);

        CHECK(phi::string_equals(view.data(), "World"));
        CHECK(view.length() == 5u);

        view.add_prefix(6u);

        CHECK(phi::string_equals(view.data(), "Hello World"));
        CHECK(view.length() == 11u);
    }

    SECTION("add_postfix")
    {
        constexpr static const char* str = "Hello World";
        phi::string_view             view(str, 5u);

        CHECK(view.back() == 'o');
        CHECK(view.length() == 5u);

        view.add_postfix(6u);

        CHECK(phi::string_equals(view.data(), "Hello World"));
        CHECK(view.length() == 11u);
    }

    SECTION("remove_prefix")
    {
        constexpr static const char* str = "Hello World";
        phi::string_view             view(str);

        CHECK(phi::string_equals(view.data(), "Hello World"));
        CHECK(view.length() == 11u);

        view.remove_prefix(6u);

        CHECK(phi::string_equals(view.data(), "World"));
        CHECK(view.length() == 5u);
    }

    SECTION("remove_suffix")
    {
        constexpr static const char* str = "Hello World";
        phi::string_view             view(str);

        CHECK(phi::string_equals(view.data(), "Hello World"));
        CHECK(view.length() == 11u);

        view.remove_suffix(6u);

        CHECK(view.back() == 'o');
        CHECK(view.length() == 5u);
    }

    SECTION("resize")
    {
        constexpr static const char* str = "Hello World";
        phi::string_view             view(str, 5u);

        view.resize(11u);

        CHECK(view.back() == 'd');
        CHECK(view.length() == 11u);

        view.resize(5u);

        CHECK(view.back() == 'o');
        CHECK(view.length() == 5u);
    }

    SECTION("swap")
    {
        phi::string_view view1("Hello");
        phi::string_view view2("World");

        view1.swap(view2);

        CHECK(phi::string_equals(view1.data(), "World"));
        CHECK(phi::string_equals(view2.data(), "Hello"));
    }

    SECTION("copy")
    {
        char dest[6u] = "";

        phi::string_view view("Hello World");

        view.copy(dest, 5u);
        dest[5u] = '\0';

        CHECK(phi::string_equals(dest, "Hello"));
        CHECK(phi::string_length(dest) == 5u);

        view.copy(dest, 5u, 6u);
        dest[5u] = '\0';

        CHECK(phi::string_equals(dest, "World"));
        CHECK(phi::string_length(dest) == 5u);
    }

    SECTION("substring_view")
    {
        EXT_CONSTEXPR_RUNTIME phi::string_view base_view("Hello World");
        EXT_CONSTEXPR_RUNTIME phi::string_view sub_view = base_view.substring_view(
                6u); // TODO: This line generates a linker error with GCC when npos is defined to be size_type instead of size_t

        EXT_STATIC_REQUIRE(phi::string_equals(sub_view.data(), "World"));
        EXT_STATIC_REQUIRE(sub_view.length() == 5u);

        EXT_CONSTEXPR_RUNTIME phi::string_view sub_view2 = base_view.substring_view(0u, 5u);

        EXT_STATIC_REQUIRE(sub_view2.back() == 'o');
        EXT_STATIC_REQUIRE(sub_view2.length() == 5u);
    }

    SECTION("explicit specilizations")
    {
        CHECK_SAME_TYPE(phi::string_view, phi::basic_string_view<char>);
        CHECK_SAME_TYPE(phi::wstring_view, phi::basic_string_view<wchar_t>);
        CHECK_SAME_TYPE(phi::u8string_view, phi::basic_string_view<char8_t>);
        CHECK_SAME_TYPE(phi::u16string_view, phi::basic_string_view<char16_t>);
        CHECK_SAME_TYPE(phi::u32string_view, phi::basic_string_view<char32_t>);

#if PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE()
        STATIC_REQUIRE(phi::is_trivially_copyable<phi::string_view>::value);
        STATIC_REQUIRE(phi::is_trivially_copyable<phi::wstring_view>::value);
        STATIC_REQUIRE(phi::is_trivially_copyable<phi::u8string_view>::value);
        STATIC_REQUIRE(phi::is_trivially_copyable<phi::u16string_view>::value);
        STATIC_REQUIRE(phi::is_trivially_copyable<phi::u32string_view>::value);
#endif
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()
