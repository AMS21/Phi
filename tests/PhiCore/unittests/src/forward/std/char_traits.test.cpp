#include <phi/test/test_macros.hpp>

#include <phi/forward/std/char_traits.hpp>
#include <phi/text/char_traits.hpp>

TEST_CASE("forward.std.char_traits.forward")
{
    std::char_traits<char>*     pointer  = nullptr;
    std::char_traits<wchar_t>*  pointer2 = nullptr;
    std::char_traits<char8_t>*  pointer3 = nullptr;
    std::char_traits<char16_t>* pointer4 = nullptr;
    std::char_traits<char32_t>* pointer5 = nullptr;

    CHECK(pointer == nullptr);
    CHECK(pointer2 == nullptr);
    CHECK(pointer3 == nullptr);
    CHECK(pointer4 == nullptr);
    CHECK(pointer5 == nullptr);
}

#include <string>

TEST_CASE("forward.std.char_traits")
{
    std::char_traits<char>     traits;
    std::char_traits<wchar_t>  traits2;
    std::char_traits<char8_t>  traits3;
    std::char_traits<char16_t> traits4;
    std::char_traits<char32_t> traits5;

    (void)traits;
    (void)traits2;
    (void)traits3;
    (void)traits4;
    (void)traits5;
}
