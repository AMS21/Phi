#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/libraries.hpp>
#include <phi/core/size_t.hpp>
#include <phi/forward/std/span.hpp>

TEST_CASE("forward.std.span.forward")
{
    std::span<int, static_cast<phi::size_t>(-1)>* pointer  = nullptr;
    std::span<int, 3>*                            pointer2 = nullptr;

    CHECK(pointer == nullptr);
    CHECK(pointer2 == nullptr);
}

// TODO: This test seems to be broken with clang-9 atleast with CI. Can't reproduce it locally
#if PHI_SUPPORTS_STDLIB_SPAN() && PHI_COMPILER_WORKAROUND(CLANG, 10, 0, 0)

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
