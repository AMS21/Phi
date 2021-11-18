#ifndef INCG_PHI_UNITTEST_SAMETYPE_HPP
#define INCG_PHI_UNITTEST_SAMETYPE_HPP

#include <Phi/Test/TestMacros.hpp>
#include <Phi/TypeTraits/is_same.hpp>

#define CHECK_SAME_TYPE(...) STATIC_REQUIRE(phi::is_same<__VA_ARGS__>::value)

#define CHECK_NOT_SAME_TYPE(...) STATIC_REQUIRE_FALSE(phi::is_same<__VA_ARGS__>::value)

#endif // INCG_PHI_UNITTEST_SAMETYPE_HPP
