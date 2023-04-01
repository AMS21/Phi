#include <phi/test/test_macros.hpp>

#include <phi/forward/std/string.hpp>
#include <phi/text/char_traits.hpp>

TEST_CASE("forward.std.string.forward")
{
    std::basic_string<int, std::char_traits<int>, std::allocator<int>>* pointer  = nullptr;
    std::string*                                                        pointer2 = nullptr;
    std::wstring*                                                       pointer3 = nullptr;
    std::u8string*                                                      pointer4 = nullptr;
    std::u16string*                                                     pointer5 = nullptr;
    std::u32string*                                                     pointer6 = nullptr;

    CHECK(pointer == nullptr);
    CHECK(pointer2 == nullptr);
    CHECK(pointer3 == nullptr);
    CHECK(pointer4 == nullptr);
    CHECK(pointer5 == nullptr);
    CHECK(pointer6 == nullptr);
}

#include <string>

TEST_CASE("forward.std.string")
{
    std::basic_string<int> string;
    std::string            string2;
    std::wstring           string3;
    std::u8string          string4;
    std::u16string         string5;
    std::u32string         string6;

    (void)string;
    (void)string2;
    (void)string3;
    (void)string4;
    (void)string5;
    (void)string6;
}
