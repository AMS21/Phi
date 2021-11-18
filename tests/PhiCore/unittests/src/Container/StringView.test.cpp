#include <Phi/Test/TestMacros.hpp>

#include "ConstexprHelper.hpp"
#include <Phi/Algorithm/StringEquals.hpp>
#include <Phi/Algorithm/StringLength.hpp>
#include <Phi/Config/Warning.hpp>
#include <Phi/Container/StringView.hpp>
#include <Phi/Core/Move.hpp>
#include <Phi/Core/Types.hpp>
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
        EXT_CONSTEXPR_RUNTIME phi::StringView view;

        EXT_STATIC_REQUIRE(view.data() == nullptr);
        EXT_STATIC_REQUIRE(bool(view.size() == 0u));
    }

    SECTION("BasicStringView(CharT*)")
    {
        EXT_CONSTEXPR_RUNTIME phi::StringView view("Hello World");

        EXT_STATIC_REQUIRE(phi::StringEquals(view.data(), "Hello World"));
        EXT_STATIC_REQUIRE(bool(view.size() == 11u));
    }

    SECTION("BasicStringView(CharT*, size_type)")
    {
        EXT_CONSTEXPR_RUNTIME phi::StringView view("Hello World", 11u);

        EXT_STATIC_REQUIRE(phi::StringEquals(view.data(), "Hello World"));
        EXT_STATIC_REQUIRE(bool(view.size() == 11u));

        EXT_CONSTEXPR_RUNTIME phi::StringView view2("Hello World", 5u);
        EXT_STATIC_REQUIRE(bool(view2.size() == 5u));
        EXT_STATIC_REQUIRE(view2.back() == 'o');
    }

    SECTION("copy constructor")
    {
        EXT_CONSTEXPR_RUNTIME phi::StringView base_view;
        EXT_CONSTEXPR_RUNTIME phi::StringView copy_view(base_view);

        EXT_STATIC_REQUIRE(copy_view.data() == nullptr);
        EXT_STATIC_REQUIRE(bool(copy_view.size() == 0u));

        EXT_CONSTEXPR_RUNTIME phi::StringView base_view2("Hello World");
        EXT_CONSTEXPR_RUNTIME phi::StringView copy_view2(base_view2);

        EXT_STATIC_REQUIRE(phi::StringEquals(copy_view2.data(), "Hello World"));
        EXT_STATIC_REQUIRE(copy_view2.data() == base_view2.data());
        EXT_STATIC_REQUIRE(bool(copy_view2.size() == 11u));
        EXT_STATIC_REQUIRE(bool(copy_view2.size() == base_view2.size()));
    }

    SECTION("move constructor")
    {
        EXT_CONSTEXPR_RUNTIME phi::StringView base_view;
        EXT_CONSTEXPR_RUNTIME phi::StringView move_view(phi::move(base_view));

        EXT_STATIC_REQUIRE(move_view.data() == nullptr);
        EXT_STATIC_REQUIRE(bool(move_view.size() == 0u));

        EXT_CONSTEXPR_RUNTIME phi::StringView base_view2("Hello World");
        EXT_CONSTEXPR_RUNTIME phi::StringView move_view2(phi::move(base_view2));

        EXT_STATIC_REQUIRE(phi::StringEquals(move_view2.data(), "Hello World"));
        EXT_STATIC_REQUIRE(bool(move_view2.size() == 11u));
    }

    SECTION("operator=(const BasicStringView&)")
    {
        phi::StringView base_view;
        phi::StringView copy_view;

        copy_view = base_view;

        CHECK(copy_view.data() == nullptr);
        CHECK(bool(copy_view.size() == 0u));

        phi::StringView base_view2("Hello World");
        phi::StringView copy_view2;

        copy_view2 = base_view2;

        CHECK(phi::StringEquals(copy_view2.data(), "Hello World"));
        CHECK(base_view2 == copy_view2);
        CHECK(bool(copy_view2.size() == 11u));
    }

    SECTION("operator=(BasicStringView&&)")
    {
        phi::StringView base_view;
        phi::StringView move_view;

        move_view = phi::move(base_view);

        CHECK(move_view.data() == nullptr);
        CHECK(bool(move_view.size() == 0u));

        phi::StringView base_view2("Hello World");
        phi::StringView move_view2;

        move_view2 = phi::move(base_view2);

        CHECK(phi::StringEquals(move_view2.data(), "Hello World"));
        CHECK(bool(move_view2.size() == 11u));
    }

    SECTION("begin")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::StringView null_view;
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view(str);

        EXT_STATIC_REQUIRE(null_view.begin() == nullptr);
        EXT_STATIC_REQUIRE(test_view.begin() == str);
    }

    SECTION("end")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::StringView null_view;
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view(str);

        EXT_STATIC_REQUIRE(null_view.end() == nullptr);
        EXT_STATIC_REQUIRE(test_view.end() == (str + 4));
    }

    SECTION("cbegin")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::StringView null_view;
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view(str);

        EXT_STATIC_REQUIRE(null_view.cbegin() == nullptr);
        EXT_STATIC_REQUIRE(test_view.cbegin() == str);
    }

    SECTION("cend")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::StringView null_view;
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view(str);

        EXT_STATIC_REQUIRE(null_view.cend() == nullptr);
        EXT_STATIC_REQUIRE(test_view.cend() == (str + 4));
    }

    SECTION("rbegin")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::StringView null_view;
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view(str);

        REQUIRE_17(null_view.rbegin() == std::reverse_iterator<const char*>(nullptr));
        REQUIRE_17(test_view.rbegin() == std::reverse_iterator<const char*>(str + 4));
    }

    SECTION("rend")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::StringView null_view;
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view(str);

        REQUIRE_17(null_view.rend() == std::reverse_iterator<const char*>(nullptr));
        REQUIRE_17(test_view.rend() == std::reverse_iterator<const char*>(str));
    }

    SECTION("crbegin")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::StringView null_view;
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view(str);

        REQUIRE_17(null_view.crbegin() == std::reverse_iterator<const char*>(nullptr));
        REQUIRE_17(test_view.crbegin() == std::reverse_iterator<const char*>(str + 4));
    }

    SECTION("crend")
    {
        EXT_CONSTEXPR_RUNTIME static const char* str = "Test";
        EXT_CONSTEXPR_RUNTIME phi::StringView null_view;
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view(str);

        REQUIRE_17(bool(null_view.crend() == std::reverse_iterator<const char*>(nullptr)));
        REQUIRE_17(bool(test_view.crend() == std::reverse_iterator<const char*>(str)));
    }

    SECTION("size/length")
    {
        EXT_CONSTEXPR_RUNTIME phi::StringView null_view;
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view("Test");
        EXT_CONSTEXPR_RUNTIME phi::StringView short_view("Hello World", 5u);

        EXT_STATIC_REQUIRE(bool(null_view.size() == 0u));
        EXT_STATIC_REQUIRE(bool(test_view.size() == 4u));
        EXT_STATIC_REQUIRE(bool(short_view.size() == 5u));

        EXT_STATIC_REQUIRE(bool(null_view.length() == 0u));
        EXT_STATIC_REQUIRE(bool(test_view.length() == 4u));
        EXT_STATIC_REQUIRE(bool(short_view.length() == 5u));
    }

    SECTION("max_size")
    {
        CONSTEXPR_RUNTIME phi::StringView view;
        STATIC_REQUIRE(bool(std::numeric_limits<phi::usize>::max() == view.max_size()));
    }

    SECTION("is_empty")
    {
        EXT_CONSTEXPR_RUNTIME phi::StringView null_view;
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view("Hello World");

        EXT_STATIC_REQUIRE(null_view.is_empty());
        EXT_STATIC_REQUIRE_FALSE(test_view.is_empty());
    }

    SECTION("operator[]/at()")
    {
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view("Test");

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
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view("Test");
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view2("Hello World");

        EXT_STATIC_REQUIRE(test_view.front() == 'T');
        EXT_STATIC_REQUIRE(test_view2.front() == 'H');
    }

    SECTION("back")
    {
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view("Test");
        EXT_CONSTEXPR_RUNTIME phi::StringView test_view2("Hello World");

        EXT_STATIC_REQUIRE(test_view.back() == 't');
        EXT_STATIC_REQUIRE(test_view2.back() == 'd');
    }

    SECTION("data")
    {
        constexpr static const char* str = "Hello World";

        EXT_CONSTEXPR_RUNTIME phi::StringView test_view(str);

        EXT_STATIC_REQUIRE(test_view.data() == str);
    }

    SECTION("clear")
    {
        phi::StringView view("Hello World");

        view.clear();

        CHECK(view.data() == nullptr);
        CHECK(view.is_empty());
        CHECK(bool(view.size() == 0u));
    }

    SECTION("add_prefix")
    {
        constexpr static const char* str = "Hello World";
        phi::StringView              view(str + 6);

        CHECK(phi::StringEquals(view.data(), "World"));
        CHECK(bool(view.size() == 5u));

        view.add_prefix(6u);

        CHECK(phi::StringEquals(view.data(), "Hello World"));
        CHECK(bool(view.size() == 11u));
    }

    SECTION("add_postfix")
    {
        constexpr static const char* str = "Hello World";
        phi::StringView              view(str, 5u);

        CHECK(view.back() == 'o');
        CHECK(bool(view.size() == 5u));

        view.add_postfix(6u);

        CHECK(phi::StringEquals(view.data(), "Hello World"));
        CHECK(bool(view.size() == 11u));
    }

    SECTION("remove_prefix")
    {
        constexpr static const char* str = "Hello World";
        phi::StringView              view(str);

        CHECK(phi::StringEquals(view.data(), "Hello World"));
        CHECK(bool(view.size() == 11u));

        view.remove_prefix(6u);

        CHECK(phi::StringEquals(view.data(), "World"));
        CHECK(bool(view.size() == 5u));
    }

    SECTION("remove_suffix")
    {
        constexpr static const char* str = "Hello World";
        phi::StringView              view(str);

        CHECK(phi::StringEquals(view.data(), "Hello World"));
        CHECK(bool(view.size() == 11u));

        view.remove_suffix(6u);

        CHECK(view.back() == 'o');
        CHECK(bool(view.size() == 5u));
    }

    SECTION("resize")
    {
        constexpr static const char* str = "Hello World";
        phi::StringView              view(str, 5u);

        view.resize(11u);

        CHECK(view.back() == 'd');
        CHECK(bool(view.size() == 11u));

        view.resize(5u);

        CHECK(view.back() == 'o');
        CHECK(bool(view.size() == 5u));
    }

    SECTION("swap")
    {
        phi::StringView view1("Hello");
        phi::StringView view2("World");

        view1.swap(view2);

        CHECK(phi::StringEquals(view1.data(), "World"));
        CHECK(phi::StringEquals(view2.data(), "Hello"));
    }

    SECTION("copy")
    {
        char dest[6u] = "";

        phi::StringView view("Hello World");

        view.copy(dest, 5u);
        dest[5u] = '\0';

        CHECK(phi::StringEquals(dest, "Hello"));
        CHECK(bool(phi::StringLength(dest) == 5u));

        view.copy(dest, 5u, 6u);
        dest[5u] = '\0';

        CHECK(phi::StringEquals(dest, "World"));
        CHECK(bool(phi::StringLength(dest) == 5u));
    }

    SECTION("substr")
    {
        EXT_CONSTEXPR_RUNTIME phi::StringView base_view("Hello World");
        EXT_CONSTEXPR_RUNTIME phi::StringView sub_view = base_view.substr(
                6u); // TODO: This line generates a linker error with GCC when npos is defined to be size_type instead of size_t

        EXT_STATIC_REQUIRE(phi::StringEquals(sub_view.data(), "World"));
        EXT_STATIC_REQUIRE(bool(sub_view.size() == 5u));

        EXT_CONSTEXPR_RUNTIME phi::StringView sub_view2 = base_view.substr(0u, 5u);

        EXT_STATIC_REQUIRE(sub_view2.back() == 'o');
        EXT_STATIC_REQUIRE(bool(sub_view2.size() == 5u));
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()
