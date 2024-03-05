#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/compiler.hpp>
#include <phi/forward/std/pair.hpp>

TEST_CASE("forward.std.pair.forward")
{
    std::pair<int, int>* pointer = nullptr;

    CHECK(pointer == nullptr);
}

// TODO: For some reason Mingw builds with '_GLIBCXX_DEBUG' defined produce the following compile error
// utility:212:10: error: '__glibcxx_assert_fail' is not a member of 'std'
// So we just undefine it to avoid this error
#if PHI_COMPILER_IS(MINGW) && defined(_GLIBCXX_DEBUG)
#    undef _GLIBCXX_DEBUG
#endif

#include <utility>

TEST_CASE("forward.std.pair")
{
    std::pair<int, int> pair;

    (void)pair;
}
