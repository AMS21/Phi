#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/string_length.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/container/string_view.hpp>
#include <phi/generated/compiler_support/libraries.hpp>
#include <string>

#if PHI_HAS_LIB_STRING_VIEW()
#    include <string_view>
#endif

// TODO: Some tests don't work with MSVC
TEST_CASE("string_length char")
{
    constexpr const char* nullp = nullptr;
    EXT_STATIC_REQUIRE(phi::string_length(nullp) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const char*>(nullptr)) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length("") == 0u);
    EXT_STATIC_REQUIRE(phi::string_length("a") == 1u);
    EXT_STATIC_REQUIRE(phi::string_length("ab") == 2u);
    EXT_STATIC_REQUIRE(phi::string_length("abc") == 3u);
    EXT_STATIC_REQUIRE(phi::string_length("abcd") == 4u);
    EXT_STATIC_REQUIRE(phi::string_length("abcde") == 5u);

    EXT_STATIC_REQUIRE(phi::string_length(nullp, 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(nullp, 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(nullp, 2u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const char*>(nullptr), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const char*>(nullptr), 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const char*>(nullptr), 2u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length("a", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length("a", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length("a", 2u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length("ab", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length("ab", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length("ab", 2u) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length("ab", 3u) == 2u);
}

TEST_CASE("string_length wchar_t")
{
#if PHI_COMPILER_IS_NOT(MSVC)
    constexpr const wchar_t* nullp = nullptr;
    EXT_STATIC_REQUIRE(phi::string_length(nullp) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const wchar_t*>(nullptr)) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(L"") == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(L"ä") == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(L"äb") == 2u);
    EXT_STATIC_REQUIRE(phi::string_length(L"äbö") == 3u);
    EXT_STATIC_REQUIRE(phi::string_length(L"äböd") == 4u);
    EXT_STATIC_REQUIRE(phi::string_length(L"äbödü") == 5u);

    EXT_STATIC_REQUIRE(
            phi::string_length(
                    L"爆ぜろリアル！弾けろシナプス！パニッシュメントディス、ワールド！") == 32u);

    EXT_STATIC_REQUIRE(phi::string_length(nullp, 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(nullp, 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(nullp, 2u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const wchar_t*>(nullptr), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const wchar_t*>(nullptr), 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const wchar_t*>(nullptr), 2u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(L"ä", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(L"ä", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(L"ä", 2u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(L"äb", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(L"äb", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(L"äb", 2u) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length(L"äb", 3u) == 2u);
#endif
}

TEST_CASE("string_length char16_t")
{
#if PHI_COMPILER_IS_NOT(MSVC)
    constexpr const char16_t* nullp = nullptr;
    EXT_STATIC_REQUIRE(phi::string_length(nullp) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const char16_t*>(nullptr)) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(u"") == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(u"ä") == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(u"äb") == 2u);
    EXT_STATIC_REQUIRE(phi::string_length(u"äbö") == 3u);
    EXT_STATIC_REQUIRE(phi::string_length(u"äböd") == 4u);
    EXT_STATIC_REQUIRE(phi::string_length(u"äbödü") == 5u);

    EXT_STATIC_REQUIRE(phi::string_length(nullp, 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(nullp, 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(nullp, 2u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const char16_t*>(nullptr), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const char16_t*>(nullptr), 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const char16_t*>(nullptr), 2u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(u"ä", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(u"ä", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(u"ä", 2u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(u"äb", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(u"äb", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(u"äb", 2u) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length(u"äb", 3u) == 2u);
#endif
}

TEST_CASE("string_length char32_t")
{
#if PHI_COMPILER_IS_NOT(MSVC)
    constexpr const char32_t* nullp = nullptr;
    EXT_STATIC_REQUIRE(phi::string_length(nullp) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const char32_t*>(nullptr)) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(U"") == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(U"ä") == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(U"äb") == 2u);
    EXT_STATIC_REQUIRE(phi::string_length(U"äbö") == 3u);
    EXT_STATIC_REQUIRE(phi::string_length(U"äböd") == 4u);
    EXT_STATIC_REQUIRE(phi::string_length(U"äbödü") == 5u);

    EXT_STATIC_REQUIRE(phi::string_length(nullp, 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(nullp, 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(nullp, 2u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const char32_t*>(nullptr), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const char32_t*>(nullptr), 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(static_cast<const char32_t*>(nullptr), 2u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(U"ä", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(U"ä", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(U"ä", 2u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(U"äb", 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(U"äb", 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(U"äb", 2u) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length(U"äb", 3u) == 2u);
#endif
}

TEST_CASE("string_length phi::basic_string_view")
{
#if PHI_COMPILER_IS_NOT(MSVC)
    EXT_STATIC_REQUIRE(phi::string_length(phi::string_view()) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::wstring_view()) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::string_view("")) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::wstring_view(L"")) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::string_view("a")) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::wstring_view(L"a")) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::string_view("aa")) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::wstring_view(L"aa")) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::string_view("ccc")) == 3u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::wstring_view(L"ccc")) == 3u);

    EXT_STATIC_REQUIRE(phi::string_length(phi::string_view(), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::wstring_view(), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::string_view(""), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::wstring_view(L""), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::string_view(""), 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::wstring_view(L""), 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::string_view("a"), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::wstring_view(L"a"), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::string_view("a"), 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::wstring_view(L"a"), 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::string_view("a"), 2u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(phi::wstring_view(L"a"), 2u) == 1u);
#endif
}

TEST_CASE("string_length std::basic_string")
{
#if PHI_COMPILER_IS_NOT(MSVC)
    CHECK(phi::string_length(std::string()) == 0u);
    CHECK(phi::string_length(std::wstring()) == 0u);
    CHECK(phi::string_length(std::string("")) == 0u);
    CHECK(phi::string_length(std::wstring(L"")) == 0u);
    CHECK(phi::string_length(std::string("a")) == 1u);
    CHECK(phi::string_length(std::wstring(L"a")) == 1u);
    CHECK(phi::string_length(std::string("aa")) == 2u);
    CHECK(phi::string_length(std::wstring(L"aa")) == 2u);
    CHECK(phi::string_length(std::string("ccc")) == 3u);
    CHECK(phi::string_length(std::wstring(L"ccc")) == 3u);

    CHECK(phi::string_length(std::string(), 0u) == 0u);
    CHECK(phi::string_length(std::wstring(), 0u) == 0u);
    CHECK(phi::string_length(std::string(""), 0u) == 0u);
    CHECK(phi::string_length(std::wstring(L""), 0u) == 0u);
    CHECK(phi::string_length(std::string(""), 1u) == 0u);
    CHECK(phi::string_length(std::wstring(L""), 1u) == 0u);
    CHECK(phi::string_length(std::string("a"), 0u) == 0u);
    CHECK(phi::string_length(std::wstring(L"a"), 0u) == 0u);
    CHECK(phi::string_length(std::string("a"), 1u) == 1u);
    CHECK(phi::string_length(std::wstring(L"a"), 1u) == 1u);
    CHECK(phi::string_length(std::string("a"), 2u) == 1u);
    CHECK(phi::string_length(std::wstring(L"a"), 2u) == 1u);
#endif
}

#if PHI_HAS_LIB_STRING_VIEW()
TEST_CASE("string_length std::basic_string_view")
{
#    if PHI_COMPILER_IS_NOT(MSVC)
    EXT_STATIC_REQUIRE(phi::string_length(std::string_view()) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(std::wstring_view()) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(std::string_view("")) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(std::wstring_view(L"")) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(std::string_view("a")) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(std::wstring_view(L"a")) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(std::string_view("aa")) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length(std::wstring_view(L"aa")) == 2u);
    EXT_STATIC_REQUIRE(phi::string_length(std::string_view("ccc")) == 3u);
    EXT_STATIC_REQUIRE(phi::string_length(std::wstring_view(L"ccc")) == 3u);

    EXT_STATIC_REQUIRE(phi::string_length(std::string_view(), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(std::wstring_view(), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(std::string_view(""), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(std::wstring_view(L""), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(std::string_view(""), 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(std::wstring_view(L""), 1u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(std::string_view("a"), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(std::wstring_view(L"a"), 0u) == 0u);
    EXT_STATIC_REQUIRE(phi::string_length(std::string_view("a"), 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(std::wstring_view(L"a"), 1u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(std::string_view("a"), 2u) == 1u);
    EXT_STATIC_REQUIRE(phi::string_length(std::wstring_view(L"a"), 2u) == 1u);
#    endif
}
#endif
