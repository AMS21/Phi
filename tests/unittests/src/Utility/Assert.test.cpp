#include <Phi/Utility/Assert.hpp>
#include <catch2/catch.hpp>

TEST_CASE("PHI_SIMPLE_ASSERT", "[Utility][Assert]")
{
    PHI_SIMPLE_ASSERT(true);
    PHI_SIMPLE_ASSERT(true, "Always passes");
}

TEST_CASE("PHI_DBG_SIMPLE_ASSERT", "[Utility][Assert]")
{
    PHI_DBG_SIMPLE_ASSERT(true);
    PHI_DBG_SIMPLE_ASSERT(true, "Always passes");

#if !PHI_DEBUG
    PHI_DBG_SIMPLE_ASSERT(false);
    PHI_DBG_SIMPLE_ASSERT(false, "Should be ignored");
#endif
}

TEST_CASE("PHI_ASSERT", "[Utility][Assert]")
{
    PHI_ASSERT(true);
    PHI_ASSERT(true, "Always passes");
}

TEST_CASE("PHI_DBG_ASSERT", "[Utility][Assert]")
{
    PHI_DBG_ASSERT(true);
    PHI_DBG_ASSERT(true, "Always passes");

#if !PHI_DEBUG
    PHI_DBG_ASSERT(false);
    PHI_DBG_ASSERT(false, "Should be ignored");
#endif
}
