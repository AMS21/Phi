#ifndef INCG_PHI_UNITTEST_NOEXCEPT_HPP
#define INCG_PHI_UNITTEST_NOEXCEPT_HPP

#include <Phi/Test/TestMacros.hpp>

#define CHECK_NOEXCEPT(...) STATIC_REQUIRE(noexcept(__VA_ARGS__))

#define CHECK_NOT_NOEXCEPT(...) STATIC_REQUIRE_FALSE(noexcept(__VA_ARGS__))

#endif // INCG_PHI_UNITTEST_NOEXCEPT_HPP