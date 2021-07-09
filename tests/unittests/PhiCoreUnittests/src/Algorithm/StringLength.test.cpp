#include <catch2/catch_test_macros.hpp>

#include <Phi/Algorithm/StringLength.hpp>

TEST_CASE("StringLength char")
{
    STATIC_REQUIRE(bool(phi::StringLength("") == 0u));
    STATIC_REQUIRE(bool(phi::StringLength("a") == 1u));
    STATIC_REQUIRE(bool(phi::StringLength("ab") == 2u));
    STATIC_REQUIRE(bool(phi::StringLength("abc") == 3u));
    STATIC_REQUIRE(bool(phi::StringLength("abcd") == 4u));
    STATIC_REQUIRE(bool(phi::StringLength("abcde") == 5u));

    STATIC_REQUIRE(bool(phi::StringLength("a", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::StringLength("a", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::StringLength("a", 2u) == 1u));
    STATIC_REQUIRE(bool(phi::StringLength("ab", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::StringLength("ab", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::StringLength("ab", 2u) == 2u));
    STATIC_REQUIRE(bool(phi::StringLength("ab", 3u) == 2u));
}

TEST_CASE("StringLength wchar_t")
{
    STATIC_REQUIRE(bool(phi::StringLength(L"") == 0u));
    STATIC_REQUIRE(bool(phi::StringLength(L"ä") == 1u));
    STATIC_REQUIRE(bool(phi::StringLength(L"äb") == 2u));
    STATIC_REQUIRE(bool(phi::StringLength(L"äbö") == 3u));
    STATIC_REQUIRE(bool(phi::StringLength(L"äböd") == 4u));
    STATIC_REQUIRE(bool(phi::StringLength(L"äbödü") == 5u));

    STATIC_REQUIRE(bool(
            phi::StringLength(
                    L"爆ぜろリアル！弾けろシナプス！パニッシュメントディス、ワールド！") == 32u));

    STATIC_REQUIRE(bool(phi::StringLength(L"ä", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::StringLength(L"ä", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::StringLength(L"ä", 2u) == 1u));
    STATIC_REQUIRE(bool(phi::StringLength(L"äb", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::StringLength(L"äb", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::StringLength(L"äb", 2u) == 2u));
    STATIC_REQUIRE(bool(phi::StringLength(L"äb", 3u) == 2u));
}

TEST_CASE("StringLength char16_t")
{
    STATIC_REQUIRE(bool(phi::StringLength(u"") == 0u));
    STATIC_REQUIRE(bool(phi::StringLength(u"ä") == 1u));
    STATIC_REQUIRE(bool(phi::StringLength(u"äb") == 2u));
    STATIC_REQUIRE(bool(phi::StringLength(u"äbö") == 3u));
    STATIC_REQUIRE(bool(phi::StringLength(u"äböd") == 4u));
    STATIC_REQUIRE(bool(phi::StringLength(u"äbödü") == 5u));

    STATIC_REQUIRE(bool(phi::StringLength(u"ä", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::StringLength(u"ä", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::StringLength(u"ä", 2u) == 1u));
    STATIC_REQUIRE(bool(phi::StringLength(u"äb", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::StringLength(u"äb", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::StringLength(u"äb", 2u) == 2u));
    STATIC_REQUIRE(bool(phi::StringLength(u"äb", 3u) == 2u));
}

TEST_CASE("StringLength char32_t")
{
    STATIC_REQUIRE(bool(phi::StringLength(U"") == 0u));
    STATIC_REQUIRE(bool(phi::StringLength(U"ä") == 1u));
    STATIC_REQUIRE(bool(phi::StringLength(U"äb") == 2u));
    STATIC_REQUIRE(bool(phi::StringLength(U"äbö") == 3u));
    STATIC_REQUIRE(bool(phi::StringLength(U"äböd") == 4u));
    STATIC_REQUIRE(bool(phi::StringLength(U"äbödü") == 5u));

    STATIC_REQUIRE(bool(phi::StringLength(U"ä", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::StringLength(U"ä", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::StringLength(U"ä", 2u) == 1u));
    STATIC_REQUIRE(bool(phi::StringLength(U"äb", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::StringLength(U"äb", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::StringLength(U"äb", 2u) == 2u));
    STATIC_REQUIRE(bool(phi::StringLength(U"äb", 3u) == 2u));
}

// SafeStringLength

TEST_CASE("SafeStringLength char")
{
    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char*>(nullptr)) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength("") == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength("a") == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength("ab") == 2u));
    STATIC_REQUIRE(bool(phi::SafeStringLength("abc") == 3u));
    STATIC_REQUIRE(bool(phi::SafeStringLength("abcd") == 4u));
    STATIC_REQUIRE(bool(phi::SafeStringLength("abcde") == 5u));

    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char*>(nullptr), 0u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char*>(nullptr), 1u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char*>(nullptr), 2u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength("a", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength("a", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength("a", 2u) == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength("ab", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength("ab", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength("ab", 2u) == 2u));
    STATIC_REQUIRE(bool(phi::SafeStringLength("ab", 3u) == 2u));
}

TEST_CASE("SafeStringLength wchar_t")
{
    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const wchar_t*>(nullptr)) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(L"") == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(L"ä") == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(L"äb") == 2u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(L"äbö") == 3u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(L"äböd") == 4u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(L"äbödü") == 5u));

    STATIC_REQUIRE(bool(
            phi::SafeStringLength(
                    L"爆ぜろリアル！弾けろシナプス！パニッシュメントディス、ワールド！") == 32u));

    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const wchar_t*>(nullptr), 0u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const wchar_t*>(nullptr), 1u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const wchar_t*>(nullptr), 2u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(L"ä", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(L"ä", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(L"ä", 2u) == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(L"äb", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(L"äb", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(L"äb", 2u) == 2u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(L"äb", 3u) == 2u));
}

TEST_CASE("SafeStringLength char16_t")
{
    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char16_t*>(nullptr)) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(u"") == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(u"ä") == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(u"äb") == 2u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(u"äbö") == 3u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(u"äböd") == 4u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(u"äbödü") == 5u));

    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char16_t*>(nullptr), 0u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char16_t*>(nullptr), 1u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char16_t*>(nullptr), 2u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(u"ä", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(u"ä", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(u"ä", 2u) == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(u"äb", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(u"äb", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(u"äb", 2u) == 2u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(u"äb", 3u) == 2u));
}

TEST_CASE("SafeStringLength char32_t")
{
    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char32_t*>(nullptr)) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(U"") == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(U"ä") == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(U"äb") == 2u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(U"äbö") == 3u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(U"äböd") == 4u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(U"äbödü") == 5u));

    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char32_t*>(nullptr), 0u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char32_t*>(nullptr), 1u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(static_cast<const char32_t*>(nullptr), 2u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(U"ä", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(U"ä", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(U"ä", 2u) == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(U"äb", 0u) == 0u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(U"äb", 1u) == 1u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(U"äb", 2u) == 2u));
    STATIC_REQUIRE(bool(phi::SafeStringLength(U"äb", 3u) == 2u));
}
