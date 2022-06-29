#include <phi/test/test_macros.hpp>

#include <phi/type_traits/aligned_union.hpp>
#include <phi/type_traits/alignment_of.hpp>
#include <phi/type_traits/is_standard_layout.hpp>
#include <phi/type_traits/is_trivial.hpp>

template <typename TypeT>
void test_aligned_union()
{
#if PHI_HAS_WORKING_IS_TRIVIAL()
    STATIC_REQUIRE(phi::is_trivial<TypeT>::value);
#endif
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    STATIC_REQUIRE(phi::is_standard_layout<TypeT>::value);
#endif
}

TEST_CASE("aligned_union")
{
    {
        using T1 = phi::aligned_union<10, char>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_union_t<10, char>);

        test_aligned_union<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 1);
        STATIC_REQUIRE(sizeof(T1) == 10);
    }
    {
        using T1 = phi::aligned_union<10, short>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_union_t<10, short>);

        test_aligned_union<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 2);
        STATIC_REQUIRE(sizeof(T1) == 10);
    }
    {
        using T1 = phi::aligned_union<10, int>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_union_t<10, int>);

        test_aligned_union<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 4);
        STATIC_REQUIRE(sizeof(T1) == 12);
    }
    {
        using T1 = phi::aligned_union<10, double>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_union_t<10, double>);

        test_aligned_union<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 8);
        STATIC_REQUIRE(sizeof(T1) == 16);
    }
    {
        using T1 = phi::aligned_union<10, short, char>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_union_t<10, short, char>);

        test_aligned_union<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 2);
        STATIC_REQUIRE(sizeof(T1) == 10);
    }
    {
        using T1 = phi::aligned_union<10, char, short>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_union_t<10, char, short>);

        test_aligned_union<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 2);
        STATIC_REQUIRE(sizeof(T1) == 10);
    }
    {
        using T1 = phi::aligned_union<2, int, char, short>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_union_t<2, int, char, short>);

        test_aligned_union<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 4);
        STATIC_REQUIRE(sizeof(T1) == 4);
    }
    {
        using T1 = phi::aligned_union<2, char, int, short>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_union_t<2, char, int, short>);

        test_aligned_union<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 4);
        STATIC_REQUIRE(sizeof(T1) == 4);
    }
    {
        using T1 = phi::aligned_union<2, char, short, int>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_union_t<2, char, short, int>);

        test_aligned_union<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 4);
        STATIC_REQUIRE(sizeof(T1) == 4);
    }
}
