#include <phi/test/test_macros.hpp>

#include <phi/iterator/iter_reference.hpp>

TEST_CASE("iterator.iter_reference_t")
{
    CHECK_SAME_TYPE(phi::iter_reference_t<int*>, int&);
    CHECK_SAME_TYPE(phi::iter_reference_t<float*>, float&);
}
