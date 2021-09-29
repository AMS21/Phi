#include <catch2/catch.hpp>

#include "ConstexprHelper.hpp"
#include <Phi/Algorithm/StringLength.hpp>
#include <string>

#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_HAS_LIB_STRING_VIEW()
#    include <string_view>
#    define HAS_LIB_STRING_VIEW() 1
#else
#    define HAS_LIB_STRING_VIEW() 0
#endif

TEST_CASE("StringLength char")
{
    EXT_STATIC_REQUIRE(bool(phi::StringLength("") == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength("a") == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength("ab") == 2u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength("abc") == 3u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength("abcd") == 4u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength("abcde") == 5u));

    EXT_STATIC_REQUIRE(bool(phi::StringLength("a", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength("a", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength("a", 2u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength("ab", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength("ab", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength("ab", 2u) == 2u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength("ab", 3u) == 2u));
}

TEST_CASE("StringLength wchar_t")
{
    EXT_STATIC_REQUIRE(bool(phi::StringLength(L"") == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(L"ä") == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(L"äb") == 2u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(L"äbö") == 3u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(L"äböd") == 4u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(L"äbödü") == 5u));

    EXT_STATIC_REQUIRE(bool(
            phi::StringLength(
                    L"爆ぜろリアル！弾けろシナプス！パニッシュメントディス、ワールド！") == 32u));

    EXT_STATIC_REQUIRE(bool(phi::StringLength(L"ä", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(L"ä", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(L"ä", 2u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(L"äb", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(L"äb", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(L"äb", 2u) == 2u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(L"äb", 3u) == 2u));
}

TEST_CASE("StringLength char16_t")
{
    EXT_STATIC_REQUIRE(bool(phi::StringLength(u"") == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(u"ä") == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(u"äb") == 2u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(u"äbö") == 3u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(u"äböd") == 4u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(u"äbödü") == 5u));

    EXT_STATIC_REQUIRE(bool(phi::StringLength(u"ä", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(u"ä", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(u"ä", 2u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(u"äb", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(u"äb", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(u"äb", 2u) == 2u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(u"äb", 3u) == 2u));
}

TEST_CASE("StringLength char32_t")
{
    EXT_STATIC_REQUIRE(bool(phi::StringLength(U"") == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(U"ä") == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(U"äb") == 2u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(U"äbö") == 3u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(U"äböd") == 4u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(U"äbödü") == 5u));

    EXT_STATIC_REQUIRE(bool(phi::StringLength(U"ä", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(U"ä", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(U"ä", 2u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(U"äb", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(U"äb", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(U"äb", 2u) == 2u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(U"äb", 3u) == 2u));
}

TEST_CASE("StringLength basic_string")
{
    CHECK(bool(phi::StringLength(std::string()) == 0u));
    CHECK(bool(phi::StringLength(std::wstring()) == 0u));
    CHECK(bool(phi::StringLength(std::string("")) == 0u));
    CHECK(bool(phi::StringLength(std::wstring(L"")) == 0u));
    CHECK(bool(phi::StringLength(std::string("a")) == 1u));
    CHECK(bool(phi::StringLength(std::wstring(L"a")) == 1u));
    CHECK(bool(phi::StringLength(std::string("aa")) == 2u));
    CHECK(bool(phi::StringLength(std::wstring(L"aa")) == 2u));
    CHECK(bool(phi::StringLength(std::string("ccc")) == 3u));
    CHECK(bool(phi::StringLength(std::wstring(L"ccc")) == 3u));

    CHECK(bool(phi::StringLength(std::string(), 0u) == 0u));
    CHECK(bool(phi::StringLength(std::wstring(), 0u) == 0u));
    CHECK(bool(phi::StringLength(std::string(""), 0u) == 0u));
    CHECK(bool(phi::StringLength(std::wstring(L""), 0u) == 0u));
    CHECK(bool(phi::StringLength(std::string(""), 1u) == 0u));
    CHECK(bool(phi::StringLength(std::wstring(L""), 1u) == 0u));
    CHECK(bool(phi::StringLength(std::string("a"), 0u) == 0u));
    CHECK(bool(phi::StringLength(std::wstring(L"a"), 0u) == 0u));
    CHECK(bool(phi::StringLength(std::string("a"), 1u) == 1u));
    CHECK(bool(phi::StringLength(std::wstring(L"a"), 1u) == 1u));
    CHECK(bool(phi::StringLength(std::string("a"), 2u) == 1u));
    CHECK(bool(phi::StringLength(std::wstring(L"a"), 2u) == 1u));
}

#if HAS_LIB_STRING_VIEW()
TEST_CASE("StringLength basic_string_view")
{
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::string_view()) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::wstring_view()) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::string_view("")) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::wstring_view(L"")) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::string_view("a")) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::wstring_view(L"a")) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::string_view("aa")) == 2u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::wstring_view(L"aa")) == 2u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::string_view("ccc")) == 3u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::wstring_view(L"ccc")) == 3u));

    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::string_view(), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::wstring_view(), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::string_view(""), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::wstring_view(L""), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::string_view(""), 1u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::wstring_view(L""), 1u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::string_view("a"), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::wstring_view(L"a"), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::string_view("a"), 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::wstring_view(L"a"), 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::string_view("a"), 2u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::StringLength(std::wstring_view(L"a"), 2u) == 1u));
}
#endif

// SafeStringLength

TEST_CASE("SafeStringLength char")
{
    CONSTEXPR_RUNTIME const char* nullp = nullptr;
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char*>(nullptr)) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength("") == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength("a") == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength("ab") == 2u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength("abc") == 3u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength("abcd") == 4u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength("abcde") == 5u));

    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp, 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp, 1u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp, 2u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char*>(nullptr), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char*>(nullptr), 1u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char*>(nullptr), 2u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength("a", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength("a", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength("a", 2u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength("ab", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength("ab", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength("ab", 2u) == 2u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength("ab", 3u) == 2u));
}

TEST_CASE("SafeStringLength wchar_t")
{
    CONSTEXPR_RUNTIME const wchar_t* nullp = nullptr;
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const wchar_t*>(nullptr)) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(L"") == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(L"ä") == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(L"äb") == 2u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(L"äbö") == 3u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(L"äböd") == 4u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(L"äbödü") == 5u));

    EXT_STATIC_REQUIRE(bool(
            phi::SafeStringLength(
                    L"爆ぜろリアル！弾けろシナプス！パニッシュメントディス、ワールド！") == 32u));

    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp, 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp, 1u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp, 2u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const wchar_t*>(nullptr), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const wchar_t*>(nullptr), 1u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const wchar_t*>(nullptr), 2u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(L"ä", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(L"ä", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(L"ä", 2u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(L"äb", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(L"äb", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(L"äb", 2u) == 2u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(L"äb", 3u) == 2u));
}

TEST_CASE("SafeStringLength char16_t")
{
    CONSTEXPR_RUNTIME const char16_t* nullp = nullptr;
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char16_t*>(nullptr)) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(u"") == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(u"ä") == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(u"äb") == 2u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(u"äbö") == 3u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(u"äböd") == 4u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(u"äbödü") == 5u));

    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp, 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp, 1u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp, 2u) == 0u));
    EXT_STATIC_REQUIRE(
            bool(phi::SafeStringLength(static_cast<const char16_t*>(nullptr), 0u) == 0u));
    EXT_STATIC_REQUIRE(
            bool(phi::SafeStringLength(static_cast<const char16_t*>(nullptr), 1u) == 0u));
    EXT_STATIC_REQUIRE(
            bool(phi::SafeStringLength(static_cast<const char16_t*>(nullptr), 2u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(u"ä", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(u"ä", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(u"ä", 2u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(u"äb", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(u"äb", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(u"äb", 2u) == 2u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(u"äb", 3u) == 2u));
}

TEST_CASE("SafeStringLength char32_t")
{
    CONSTEXPR_RUNTIME const char32_t* nullp = nullptr;
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char32_t*>(nullptr)) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(U"") == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(U"ä") == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(U"äb") == 2u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(U"äbö") == 3u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(U"äböd") == 4u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(U"äbödü") == 5u));

    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp, 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp, 1u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(nullp, 2u) == 0u));
    EXT_STATIC_REQUIRE(
            bool(phi::SafeStringLength(static_cast<const char32_t*>(nullptr), 0u) == 0u));
    EXT_STATIC_REQUIRE(
            bool(phi::SafeStringLength(static_cast<const char32_t*>(nullptr), 1u) == 0u));
    EXT_STATIC_REQUIRE(
            bool(phi::SafeStringLength(static_cast<const char32_t*>(nullptr), 2u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(U"ä", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(U"ä", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(U"ä", 2u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(U"äb", 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(U"äb", 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(U"äb", 2u) == 2u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(U"äb", 3u) == 2u));
}

TEST_CASE("SafeStringLength basic_string")
{
    CHECK(bool(phi::SafeStringLength(std::string()) == 0u));
    CHECK(bool(phi::SafeStringLength(std::wstring()) == 0u));
    CHECK(bool(phi::SafeStringLength(std::string("")) == 0u));
    CHECK(bool(phi::SafeStringLength(std::wstring(L"")) == 0u));
    CHECK(bool(phi::SafeStringLength(std::string("a")) == 1u));
    CHECK(bool(phi::SafeStringLength(std::wstring(L"a")) == 1u));
    CHECK(bool(phi::SafeStringLength(std::string("aa")) == 2u));
    CHECK(bool(phi::SafeStringLength(std::wstring(L"aa")) == 2u));
    CHECK(bool(phi::SafeStringLength(std::string("ccc")) == 3u));
    CHECK(bool(phi::SafeStringLength(std::wstring(L"ccc")) == 3u));

    CHECK(bool(phi::SafeStringLength(std::string(), 0u) == 0u));
    CHECK(bool(phi::SafeStringLength(std::wstring(), 0u) == 0u));
    CHECK(bool(phi::SafeStringLength(std::string(""), 0u) == 0u));
    CHECK(bool(phi::SafeStringLength(std::wstring(L""), 0u) == 0u));
    CHECK(bool(phi::SafeStringLength(std::string(""), 1u) == 0u));
    CHECK(bool(phi::SafeStringLength(std::wstring(L""), 1u) == 0u));
    CHECK(bool(phi::SafeStringLength(std::string("a"), 0u) == 0u));
    CHECK(bool(phi::SafeStringLength(std::wstring(L"a"), 0u) == 0u));
    CHECK(bool(phi::SafeStringLength(std::string("a"), 1u) == 1u));
    CHECK(bool(phi::SafeStringLength(std::wstring(L"a"), 1u) == 1u));
    CHECK(bool(phi::SafeStringLength(std::string("a"), 2u) == 1u));
    CHECK(bool(phi::SafeStringLength(std::wstring(L"a"), 2u) == 1u));
}

#if HAS_LIB_STRING_VIEW()
TEST_CASE("SafeStringLength basic_string_view")
{
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::string_view()) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::wstring_view()) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::string_view("")) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::wstring_view(L"")) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::string_view("a")) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::wstring_view(L"a")) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::string_view("aa")) == 2u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::wstring_view(L"aa")) == 2u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::string_view("ccc")) == 3u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::wstring_view(L"ccc")) == 3u));

    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::string_view(), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::wstring_view(), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::string_view(""), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::wstring_view(L""), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::string_view(""), 1u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::wstring_view(L""), 1u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::string_view("a"), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::wstring_view(L"a"), 0u) == 0u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::string_view("a"), 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::wstring_view(L"a"), 1u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::string_view("a"), 2u) == 1u));
    EXT_STATIC_REQUIRE(bool(phi::SafeStringLength(std::wstring_view(L"a"), 2u) == 1u));
}
#endif
