#include <catch2/catch_test_macros.hpp>

#include "ConstexprHelper.hpp"
#include <Phi/Algorithm/StringEquals.hpp>
#include <Phi/Algorithm/StringLength.hpp>
#include <Phi/Container/StringView.hpp>
#include <Phi/Core/Types.hpp>
#include <limits>
#include <utility>

// Workaround for std::reverse_iterator not being constexpr until C++-17
// TODO: Remove once we added our own reverse_iterator implementation
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
#    define REQUIRE_17(...) STATIC_REQUIRE(__VA_ARGS__)
#else
#    define REQUIRE_17(...) CHECK(__VA_ARGS__)
#endif

TEST_CASE("BasicStringView", "[Container][StringView]")
{
    SECTION("default constructor")
    {
        CONSTEXPR_RUNTIME phi::StringView view;

        STATIC_REQUIRE(view.data() == nullptr);
        STATIC_REQUIRE(bool(view.size() == 0u));
    }

    SECTION("BasicStringView(CharT*)")
    {
        CONSTEXPR_RUNTIME phi::StringView view("Hello World");

        STATIC_REQUIRE(phi::StringEquals(view.data(), "Hello World"));
        STATIC_REQUIRE(bool(view.size() == 11u));
    }

    SECTION("BasicStringView(CharT*, size_type)")
    {
        CONSTEXPR_RUNTIME phi::StringView view("Hello World", 11u);

        STATIC_REQUIRE(phi::StringEquals(view.data(), "Hello World"));
        STATIC_REQUIRE(bool(view.size() == 11u));

        CONSTEXPR_RUNTIME phi::StringView view2("Hello World", 5u);
        STATIC_REQUIRE(bool(view2.size() == 5u));
        STATIC_REQUIRE(view2.back() == 'o');
    }

    SECTION("copy constructor")
    {
        CONSTEXPR_RUNTIME phi::StringView base_view;
        CONSTEXPR_RUNTIME phi::StringView copy_view(base_view);

        STATIC_REQUIRE(copy_view.data() == nullptr);
        STATIC_REQUIRE(bool(copy_view.size() == 0u));

        CONSTEXPR_RUNTIME phi::StringView base_view2("Hello World");
        CONSTEXPR_RUNTIME phi::StringView copy_view2(base_view2);

        STATIC_REQUIRE(phi::StringEquals(copy_view2.data(), "Hello World"));
        STATIC_REQUIRE(copy_view2.data() == base_view2.data());
        STATIC_REQUIRE(bool(copy_view2.size() == 11u));
        STATIC_REQUIRE(bool(copy_view2.size() == base_view2.size()));
    }

    SECTION("move constructor")
    {
        CONSTEXPR_RUNTIME phi::StringView base_view;
        CONSTEXPR_RUNTIME phi::StringView move_view(std::move(base_view));

        STATIC_REQUIRE(move_view.data() == nullptr);
        STATIC_REQUIRE(bool(move_view.size() == 0u));

        CONSTEXPR_RUNTIME phi::StringView base_view2("Hello World");
        CONSTEXPR_RUNTIME phi::StringView move_view2(std::move(base_view2));

        STATIC_REQUIRE(phi::StringEquals(move_view2.data(), "Hello World"));
        STATIC_REQUIRE(bool(move_view2.size() == 11u));
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

        move_view = std::move(base_view);

        CHECK(move_view.data() == nullptr);
        CHECK(bool(move_view.size() == 0u));

        phi::StringView base_view2("Hello World");
        phi::StringView move_view2;

        move_view2 = std::move(base_view2);

        CHECK(phi::StringEquals(move_view2.data(), "Hello World"));
        CHECK(bool(move_view2.size() == 11u));
    }

    SECTION("begin")
    {
        CONSTEXPR_RUNTIME static const char* str = "Test";
        CONSTEXPR_RUNTIME phi::StringView null_view;
        CONSTEXPR_RUNTIME phi::StringView test_view(str);

        STATIC_REQUIRE(null_view.begin() == nullptr);
        STATIC_REQUIRE(test_view.begin() == str);
    }

    SECTION("end")
    {
        CONSTEXPR_RUNTIME static const char* str = "Test";
        CONSTEXPR_RUNTIME phi::StringView null_view;
        CONSTEXPR_RUNTIME phi::StringView test_view(str);

        STATIC_REQUIRE(null_view.end() == nullptr);
        STATIC_REQUIRE(test_view.end() == (str + 4));
    }

    SECTION("cbegin")
    {
        CONSTEXPR_RUNTIME static const char* str = "Test";
        CONSTEXPR_RUNTIME phi::StringView null_view;
        CONSTEXPR_RUNTIME phi::StringView test_view(str);

        STATIC_REQUIRE(null_view.cbegin() == nullptr);
        STATIC_REQUIRE(test_view.cbegin() == str);
    }

    SECTION("cend")
    {
        CONSTEXPR_RUNTIME static const char* str = "Test";
        CONSTEXPR_RUNTIME phi::StringView null_view;
        CONSTEXPR_RUNTIME phi::StringView test_view(str);

        STATIC_REQUIRE(null_view.cend() == nullptr);
        STATIC_REQUIRE(test_view.cend() == (str + 4));
    }

    SECTION("rbegin")
    {
        CONSTEXPR_RUNTIME static const char* str = "Test";
        CONSTEXPR_RUNTIME phi::StringView null_view;
        CONSTEXPR_RUNTIME phi::StringView test_view(str);

        REQUIRE_17(null_view.rbegin() == std::reverse_iterator<const char*>(nullptr));
        REQUIRE_17(test_view.rbegin() == std::reverse_iterator<const char*>(str + 4));
    }

    SECTION("rend")
    {
        CONSTEXPR_RUNTIME static const char* str = "Test";
        CONSTEXPR_RUNTIME phi::StringView null_view;
        CONSTEXPR_RUNTIME phi::StringView test_view(str);

        REQUIRE_17(null_view.rend() == std::reverse_iterator<const char*>(nullptr));
        REQUIRE_17(test_view.rend() == std::reverse_iterator<const char*>(str));
    }

    SECTION("crbegin")
    {
        CONSTEXPR_RUNTIME static const char* str = "Test";
        CONSTEXPR_RUNTIME phi::StringView null_view;
        CONSTEXPR_RUNTIME phi::StringView test_view(str);

        REQUIRE_17(null_view.crbegin() == std::reverse_iterator<const char*>(nullptr));
        REQUIRE_17(test_view.crbegin() == std::reverse_iterator<const char*>(str + 4));
    }

    SECTION("crend")
    {
        CONSTEXPR_RUNTIME static const char* str = "Test";
        CONSTEXPR_RUNTIME phi::StringView null_view;
        CONSTEXPR_RUNTIME phi::StringView test_view(str);

        REQUIRE_17(bool(null_view.crend() == std::reverse_iterator<const char*>(nullptr)));
        REQUIRE_17(bool(test_view.crend() == std::reverse_iterator<const char*>(str)));
    }

    SECTION("size/length")
    {
        CONSTEXPR_RUNTIME phi::StringView null_view;
        CONSTEXPR_RUNTIME phi::StringView test_view("Test");
        CONSTEXPR_RUNTIME phi::StringView short_view("Hello World", 5u);

        STATIC_REQUIRE(bool(null_view.size() == 0u));
        STATIC_REQUIRE(bool(test_view.size() == 4u));
        STATIC_REQUIRE(bool(short_view.size() == 5u));

        STATIC_REQUIRE(bool(null_view.length() == 0u));
        STATIC_REQUIRE(bool(test_view.length() == 4u));
        STATIC_REQUIRE(bool(short_view.length() == 5u));
    }

    SECTION("max_size")
    {
        CONSTEXPR_RUNTIME phi::StringView view;
        STATIC_REQUIRE(bool(std::numeric_limits<phi::usize>::max() == view.max_size()));
    }

    SECTION("is_empty")
    {
        CONSTEXPR_RUNTIME phi::StringView null_view;
        CONSTEXPR_RUNTIME phi::StringView test_view("Hello World");

        STATIC_REQUIRE(null_view.is_empty());
        STATIC_REQUIRE_FALSE(test_view.is_empty());
    }

    SECTION("operator[]/at()")
    {
        CONSTEXPR_RUNTIME phi::StringView test_view("Test");

        STATIC_REQUIRE(test_view[0u] == 'T');
        STATIC_REQUIRE(test_view[1u] == 'e');
        STATIC_REQUIRE(test_view[2u] == 's');
        STATIC_REQUIRE(test_view[3u] == 't');

        STATIC_REQUIRE(test_view.at(0u) == 'T');
        STATIC_REQUIRE(test_view.at(1u) == 'e');
        STATIC_REQUIRE(test_view.at(2u) == 's');
        STATIC_REQUIRE(test_view.at(3u) == 't');
    }

    SECTION("front")
    {
        CONSTEXPR_RUNTIME phi::StringView test_view("Test");
        CONSTEXPR_RUNTIME phi::StringView test_view2("Hello World");

        STATIC_REQUIRE(test_view.front() == 'T');
        STATIC_REQUIRE(test_view2.front() == 'H');
    }

    SECTION("back")
    {
        CONSTEXPR_RUNTIME phi::StringView test_view("Test");
        CONSTEXPR_RUNTIME phi::StringView test_view2("Hello World");

        STATIC_REQUIRE(test_view.back() == 't');
        STATIC_REQUIRE(test_view2.back() == 'd');
    }

    SECTION("data")
    {
        constexpr static const char* str = "Hello World";

        CONSTEXPR_RUNTIME phi::StringView test_view(str);

        STATIC_REQUIRE(test_view.data() == str);
    }

    SECTION("clear")
    {
        phi::StringView view("Hello World");

        view.clear();

        CHECK(view.data() == nullptr);
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
        CONSTEXPR_RUNTIME phi::StringView base_view("Hello World");
        CONSTEXPR_RUNTIME phi::StringView sub_view = base_view.substr(6u);

        STATIC_REQUIRE(phi::StringEquals(sub_view.data(), "World"));
        STATIC_REQUIRE(bool(sub_view.size() == 5u));

        CONSTEXPR_RUNTIME phi::StringView sub_view2 = base_view.substr(0u, 5u);

        STATIC_REQUIRE(sub_view2.back() == 'o');
        STATIC_REQUIRE(bool(sub_view2.size() == 5u));
    }
}
