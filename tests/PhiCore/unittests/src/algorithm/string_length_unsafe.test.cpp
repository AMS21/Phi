#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/string_length_unsafe.hpp>
#include <phi/container/string_view.hpp>
#include <phi/generated/compiler_support/libraries.hpp>
#include <string>

#if PHI_HAS_LIB_STRING_VIEW()
#    include <string_view>
#endif

TEST_CASE("string_length_unsafe char")
{
    EXT_STATIC_REQUIRE(phi::string_length_unsafe("") == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe("a") == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe("ab") == 2u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe("abc") == 3u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe("abcd") == 4u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe("abcde") == 5u);

    EXT_STATIC_REQUIRE(phi::string_length_unsafe("a", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe("a", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe("a", 2u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe("ab", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe("ab", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe("ab", 2u) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe("ab", 3u) == 2u);
}

TEST_CASE("string_length_unsafe wchar_t")
{
#if PHI_COMPILER_IS_NOT(MSVC)
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(L"") == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(L"ä") == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(L"äb") == 2u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(L"äbö") == 3u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(L"äböd") == 4u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(L"äbödü") == 5u);

    EXT_STATIC_REQUIRE(
            phi::string_length_unsafe(
                    L"爆ぜろリアル！弾けろシナプス！パニッシュメントディス、ワールド！") == 32u);

    EXT_STATIC_REQUIRE(phi::string_length_unsafe(L"ä", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(L"ä", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(L"ä", 2u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(L"äb", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(L"äb", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(L"äb", 2u) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(L"äb", 3u) == 2u);
#endif
}

TEST_CASE("string_length_unsafe char16_t")
{
#if PHI_COMPILER_IS_NOT(MSVC)
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(u"") == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(u"ä") == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(u"äb") == 2u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(u"äbö") == 3u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(u"äböd") == 4u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(u"äbödü") == 5u);

    EXT_STATIC_REQUIRE(phi::string_length_unsafe(u"ä", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(u"ä", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(u"ä", 2u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(u"äb", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(u"äb", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(u"äb", 2u) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(u"äb", 3u) == 2u);
#endif
}

TEST_CASE("string_length_unsafe char32_t")
{
#if PHI_COMPILER_IS_NOT(MSVC)
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(U"") == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(U"ä") == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(U"äb") == 2u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(U"äbö") == 3u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(U"äböd") == 4u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(U"äbödü") == 5u);

    EXT_STATIC_REQUIRE(phi::string_length_unsafe(U"ä", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(U"ä", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(U"ä", 2u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(U"äb", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(U"äb", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(U"äb", 2u) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(U"äb", 3u) == 2u);
#endif
}

TEST_CASE("string_length_unsafe phi::string_view")
{
#if PHI_COMPILER_IS_NOT(MSVC)
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::string_view()) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::wstring_view()) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::string_view("")) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::wstring_view(L"")) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::string_view("a")) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::wstring_view(L"a")) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::string_view("aa")) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::wstring_view(L"aa")) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::string_view("ccc")) == 3u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::wstring_view(L"ccc")) == 3u);

    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::string_view(), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::wstring_view(), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::string_view(""), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::wstring_view(L""), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::string_view(""), 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::wstring_view(L""), 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::string_view("a"), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::wstring_view(L"a"), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::string_view("a"), 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::wstring_view(L"a"), 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::string_view("a"), 2u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(phi::wstring_view(L"a"), 2u) == 1u);
#endif
}

TEST_CASE("string_length_unsafe std::basic_string")
{
    CHECK(phi::string_length_unsafe(std::string()) == 0u);
    CHECK(phi::string_length_unsafe(std::wstring()) == 0u);
    CHECK(phi::string_length_unsafe(std::string("")) == 0u);
    CHECK(phi::string_length_unsafe(std::wstring(L"")) == 0u);
    CHECK(phi::string_length_unsafe(std::string("a")) == 1u);
    CHECK(phi::string_length_unsafe(std::wstring(L"a")) == 1u);
    CHECK(phi::string_length_unsafe(std::string("aa")) == 2u);
    CHECK(phi::string_length_unsafe(std::wstring(L"aa")) == 2u);
    CHECK(phi::string_length_unsafe(std::string("ccc")) == 3u);
    CHECK(phi::string_length_unsafe(std::wstring(L"ccc")) == 3u);

    CHECK(phi::string_length_unsafe(std::string(), 0u) == 0u);
    CHECK(phi::string_length_unsafe(std::wstring(), 0u) == 0u);
    CHECK(phi::string_length_unsafe(std::string(""), 0u) == 0u);
    CHECK(phi::string_length_unsafe(std::wstring(L""), 0u) == 0u);
    CHECK(phi::string_length_unsafe(std::string(""), 1u) == 0u);
    CHECK(phi::string_length_unsafe(std::wstring(L""), 1u) == 0u);
    CHECK(phi::string_length_unsafe(std::string("a"), 0u) == 0u);
    CHECK(phi::string_length_unsafe(std::wstring(L"a"), 0u) == 0u);
    CHECK(phi::string_length_unsafe(std::string("a"), 1u) == 1u);
    CHECK(phi::string_length_unsafe(std::wstring(L"a"), 1u) == 1u);
    CHECK(phi::string_length_unsafe(std::string("a"), 2u) == 1u);
    CHECK(phi::string_length_unsafe(std::wstring(L"a"), 2u) == 1u);
}

#if PHI_HAS_LIB_STRING_VIEW()
TEST_CASE("string_length_unsafe std::basic_string_view")
{
#    if PHI_COMPILER_IS_NOT(MSVC)
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::string_view()) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::wstring_view()) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::string_view("")) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::wstring_view(L"")) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::string_view("a")) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::wstring_view(L"a")) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::string_view("aa")) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::wstring_view(L"aa")) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::string_view("ccc")) == 3u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::wstring_view(L"ccc")) == 3u);

    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::string_view(), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::wstring_view(), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::string_view(""), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::wstring_view(L""), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::string_view(""), 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::wstring_view(L""), 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::string_view("a"), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::wstring_view(L"a"), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::string_view("a"), 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::wstring_view(L"a"), 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::string_view("a"), 2u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length_unsafe(std::wstring_view(L"a"), 2u) == 1u);
#    endif
}
#endif
