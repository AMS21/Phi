#include <phi/test/test_macros.hpp>

#include <phi/core/size_t.hpp>
#include <phi/forward/std/span.hpp>
#include <phi/generated/compiler_support/libraries.hpp>

TEST_CASE("forward.std.span.forward")
{
    std::span<int, static_cast<phi::size_t>(-1)>* pointer  = nullptr;
    std::span<int, 3>*                            pointer2 = nullptr;

    CHECK(pointer == nullptr);
    CHECK(pointer2 == nullptr);
}

#if PHI_HAS_LIB_SPAN()

#    include <span>

TEST_CASE("forward.std.span")
{
    int ints[] = {1, 2, 3};

    std::span<int>    span;
    std::span<int, 3> span2{ints};

    (void)span;
    (void)span2;
}

#endif
