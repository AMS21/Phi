#include <phi/test/test_macros.hpp>

#include <phi/forward/string_view.hpp>

TEST_CASE("forward.string_view.forward")
{
    {
        phi::basic_string_view<int>* pointer  = nullptr;
        phi::string_view*            pointer2 = nullptr;
        phi::wstring_view*           pointer3 = nullptr;
        phi::u8string_view*          pointer4 = nullptr;
        phi::u16string_view*         pointer5 = nullptr;
        phi::u32string_view*         pointer6 = nullptr;

        CHECK(pointer == nullptr);
        CHECK(pointer2 == nullptr);
        CHECK(pointer3 == nullptr);
        CHECK(pointer4 == nullptr);
        CHECK(pointer5 == nullptr);
        CHECK(pointer6 == nullptr);
    }
    {
        phi::not_null_basic_string_view<int>* pointer  = nullptr;
        phi::not_null_string_view*            pointer2 = nullptr;
        phi::not_null_wstring_view*           pointer3 = nullptr;
        phi::not_null_u8string_view*          pointer4 = nullptr;
        phi::not_null_u16string_view*         pointer5 = nullptr;
        phi::not_null_u32string_view*         pointer6 = nullptr;

        CHECK(pointer == nullptr);
        CHECK(pointer2 == nullptr);
        CHECK(pointer3 == nullptr);
        CHECK(pointer4 == nullptr);
        CHECK(pointer5 == nullptr);
        CHECK(pointer6 == nullptr);
    }
}

#include <phi/container/array.hpp>
#include <phi/container/string_view.hpp>

TEST_CASE("forward.string_view")
{
    {
        phi::basic_string_view<int> view;
        phi::string_view            view2;
        phi::wstring_view           view3;
        phi::u8string_view          view4;
        phi::u16string_view         view5;
        phi::u32string_view         view6;

        (void)view;
        (void)view2;
        (void)view3;
        (void)view4;
        (void)view5;
        (void)view6;
    }
    {
        phi::array<int, 3u> ints{1, 2, 3};

        phi::not_null_basic_string_view<int> view{ints};
        phi::not_null_string_view            view2{"str"};
        phi::not_null_wstring_view           view3{L"str"};
        phi::not_null_u8string_view          view4{u8"str"};
        phi::not_null_u16string_view         view5{u"str"};
        phi::not_null_u32string_view         view6{U"str"};

        (void)view;
        (void)view2;
        (void)view3;
        (void)view4;
        (void)view5;
        (void)view6;
    }
}
