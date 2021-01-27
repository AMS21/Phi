#ifndef INCG_PHI_CORE_TYPES_HPP
#define INCG_PHI_CORE_TYPES_HPP

#include "Phi/Core/Boolean.hpp"
#include "Phi/Core/FloatingPoint.hpp"
#include "Phi/Core/Integer.hpp"
#include "Phi/PhiConfig.hpp"
#include <cstdint>
#include <type_traits>

DETAIL_PHI_BEGIN_NAMESPACE()

// Integer
using i8  = Integer<std::int8_t>;
using u8  = Integer<std::uint8_t>;
using i16 = Integer<std::int16_t>;
using u16 = Integer<std::uint16_t>;
using i32 = Integer<std::int32_t>;
using u32 = Integer<std::uint32_t>;
using i64 = Integer<std::int64_t>;
using u64 = Integer<std::uint64_t>;

using i8_fast  = Integer<std::int_fast8_t>;
using u8_fast  = Integer<std::uint_fast8_t>;
using i16_fast = Integer<std::int_fast16_t>;
using u16_fast = Integer<std::uint_fast16_t>;
using i32_fast = Integer<std::int_fast32_t>;
using u32_fast = Integer<std::uint_fast32_t>;
using i64_fast = Integer<std::int_fast64_t>;
using u64_fast = Integer<std::uint_fast64_t>;

using isize = Integer<std::make_signed<std::size_t>::type>;
using usize = Integer<std::size_t>;
using imax  = i64;
using umax  = u64;

// Floating point
using f32  = FloatingPoint<float>;
using f64  = FloatingPoint<double>;
using fmax = f64;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPES_HPP
