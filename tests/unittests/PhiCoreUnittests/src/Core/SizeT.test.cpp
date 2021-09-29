#include <catch2/catch.hpp>

#include "SameType.hpp"
#include <Phi/Core/SizeT.hpp>
#include <cstddef> // std::size_t

TEST_CASE("size_t")
{
    CHECK_SAME_TYPE(phi::size_t, std::size_t);
    CHECK_SAME_TYPE(phi::size_t, decltype(sizeof(int)));
    CHECK_SAME_TYPE(phi::size_t, decltype(sizeof(long long)));
    CHECK_SAME_TYPE(phi::size_t, decltype(alignof(int)));
}
