#ifndef INCG_PHI_CORE_SIZED_TYPES_HPP
#define INCG_PHI_CORE_SIZED_TYPES_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/warning.hpp"
#include "phi/generated/compiler_support/type_system.hpp"

PHI_CLANG_SUPPRESS_WARNING_PUSH()
#if PHI_COMPILER_IS_ATLEAST(CLANG, 13, 0, 0)
PHI_CLANG_SUPPRESS_WARNING("-Wreserved-macro-identifier")
#else
PHI_CLANG_SUPPRESS_WARNING("-Wreserved-id-macro")
#endif

// Define '__STDC_WANT_SECURE_LIB__' macro to avoid warnings with MSVC's stl
#ifndef __STDC_WANT_SECURE_LIB__
#    define __STDC_WANT_SECURE_LIB__ 1
#endif

PHI_CLANG_SUPPRESS_WARNING_POP()

#include <climits> // CHAR_BIT

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    // int8
#if PHI_TYPE_SYSTEM_SIZEOF_CHAR() * CHAR_BIT == 8
    using signed_int8   = signed char;
    using unsigned_int8 = unsigned char;
#elif PHI_TYPE_SYSTEM_SIZEOF_SHORT() * CHAR_BIT == 8
    using signed_int8                        = signed short;
    using unsigned int8                      = unsigned short;
#elif PHI_TYPE_SYSTEM_SIZEOF_INT() * CHAR_BIT == 8
    using signed_int8                        = signed int;
    using unsigned int8                      = unsigned int;
#elif PHI_TYPE_SYSTEM_SIZEOF_LONG() * CHAR_BIT == 8
    using signed_int8                        = signed long;
    using unsigned_int8                      = unsigned long;
#elif PHI_TYPE_SYSTEM_SIZEOF_LONG_LONG() * CHAR_BIT == 8
    using signed_int8    = signed long long;
    using unsigned_int8  = unsigned long long;
#else
#    error "No integer of size 8 found!"
#endif

    // int16
#if PHI_TYPE_SYSTEM_SIZEOF_CHAR() * CHAR_BIT == 16
    using signed_int16   = signed char;
    using unsigned_int16 = unsigned char;
#elif PHI_TYPE_SYSTEM_SIZEOF_SHORT() * CHAR_BIT == 16
    using signed_int16                       = signed short;
    using unsigned_int16                     = unsigned short;
#elif PHI_TYPE_SYSTEM_SIZEOF_INT() * CHAR_BIT == 16
    using signed_int16                       = signed int;
    using unsigned int16                     = unsigned int;
#elif PHI_TYPE_SYSTEM_SIZEOF_LONG() * CHAR_BIT == 16
    using signed_int16                       = signed long;
    using unsigned_int16                     = unsigned long;
#elif PHI_TYPE_SYSTEM_SIZEOF_LONG_LONG() * CHAR_BIT == 16
    using signed_int16   = signed long long;
    using unsigned_int16 = unsigned long long;
#else
#    error "No integer of size 16 found!"
#endif

    // int32
#if PHI_TYPE_SYSTEM_SIZEOF_CHAR() * CHAR_BIT == 32
    using signed_int32   = signed char;
    using unsigned_int32 = unsigned char;
#elif PHI_TYPE_SYSTEM_SIZEOF_SHORT() * CHAR_BIT == 32
    using signed_int32                       = signed short;
    using unsigned_int32                     = unsigned short;
#elif PHI_TYPE_SYSTEM_SIZEOF_INT() * CHAR_BIT == 32
    using signed_int32                       = signed int;
    using unsigned_int32                     = unsigned int;
#elif PHI_TYPE_SYSTEM_SIZEOF_LONG() * CHAR_BIT == 32
    using signed_int32                       = signed long;
    using unsigned_int32                     = unsigned long;
#elif PHI_TYPE_SYSTEM_SIZEOF_LONG_LONG() * CHAR_BIT == 32
    using signed_int32   = signed long long;
    using unsigned_int32 = unsigned long long;
#else
#    error "No integer of size 32 found!"
#endif

    // int64
#if PHI_TYPE_SYSTEM_SIZEOF_CHAR() * CHAR_BIT == 64
    using signed_int64   = signed char;
    using unsigned_int64 = unsigned char;
#elif PHI_TYPE_SYSTEM_SIZEOF_SHORT() * CHAR_BIT == 64
    using signed_int64                       = signed short;
    using unsigned_int64                     = unsigned short;
#elif PHI_TYPE_SYSTEM_SIZEOF_INT() * CHAR_BIT == 64
    using signed_int64                       = signed int;
    using unsigned_int64                     = unsigned int;
#elif PHI_TYPE_SYSTEM_SIZEOF_LONG() * CHAR_BIT == 64
    using signed_int64                       = signed long;
    using unsigned_int64                     = unsigned long;
#elif PHI_TYPE_SYSTEM_SIZEOF_LONG_LONG() * CHAR_BIT == 64
    using signed_int64   = signed long long;
    using unsigned_int64 = unsigned long long;
#else
#    error "No integer of size 64 found!"
#endif

    // float32
#if PHI_TYPE_SYSTEM_SIZEOF_FLOAT() * CHAR_BIT == 32
    using float32 = float;
#elif PHI_TYPE_SYSTEM_SIZEOF_DOUBLE() * CHAR_BIT == 32
    using float32                            = double;
#elif PHI_TYPE_SYSTEM_SIZEOF_LONG_DOUBLE() * CHAR_BIT == 32
    using float32                            = long double;
#else
#    error "No float of size 32 found!"
#endif

    // float64
#if PHI_TYPE_SYSTEM_SIZEOF_FLOAT() * CHAR_BIT == 64
    using float64 = float;
#elif PHI_TYPE_SYSTEM_SIZEOF_DOUBLE() * CHAR_BIT == 64
    using float64                            = double;
#elif PHI_TYPE_SYSTEM_SIZEOF_LONG_DOUBLE() * CHAR_BIT == 64
    using float64                            = long double;
#else
#    error "No float of size 64 found!"
#endif

    PHI_GCC_SUPPRESS_WARNING_PUSH()
    PHI_GCC_SUPPRESS_WARNING("-Wunused-const-variable")

    // Optional float128
#if PHI_TYPE_SYSTEM_SIZEOF_FLOAT() * CHAR_BIT == 128
    static constexpr const bool has_float128 = true;
    using float128                           = float;
#elif PHI_TYPE_SYSTEM_SIZEOF_DOUBLE() * CHAR_BIT == 128
    static constexpr const bool has_float128 = true;
    using float128                           = double;
#elif PHI_TYPE_SYSTEM_SIZEOF_LONG_DOUBLE() * CHAR_BIT == 128
    static constexpr const bool has_float128 = true;
    using float128                           = long double;
#else
    static constexpr const bool has_float128 = false;
    using float128                           = void;
#endif

    PHI_GCC_SUPPRESS_WARNING_POP()

} // namespace detail

using int8_t  = detail::signed_int8;
using uint8_t = detail::unsigned_int8;

using int16_t  = detail::signed_int16;
using uint16_t = detail::unsigned_int16;

using int32_t  = detail::signed_int32;
using uint32_t = detail::unsigned_int32;

using int64_t  = detail::signed_int64;
using uint64_t = detail::unsigned_int64;

using intmax_t  = int64_t;
using uintmax_t = uint64_t;

using int_fast8_t  = detail::signed_int8;
using uint_fast8_t = detail::unsigned_int8;
#if PHI_TYPE_SYSTEM_SIZEOF_VOIDPTR() * CHAR_BIT == 8
using int_fast16_t  = detail::signed_int16;
using uint_fast16_t = detail::unsigned_int16;
using int_fast32_t  = detail::signed_int32;
using uint_fast32_t = detail::unsigned_int32;
using int_fast64_t  = detail::signed_int64;
using uint_fast64_t = detail::unsigned_int64;
#elif PHI_TYPE_SYSTEM_SIZEOF_VOIDPTR() * CHAR_BIT == 16
using int_fast16_t = detail::signed_int16;
using uint_fast16_t = detail::unsigned_int16;
using int_fast32_t = detail::signed_int32;
using uint_fast32_t = detail::unsigned_int32;
using int_fast64_t = detail::signed_int64;
using uint_fast64_t = detail::unsigned_int64;
#elif PHI_TYPE_SYSTEM_SIZEOF_VOIDPTR() * CHAR_BIT == 32
using int_fast16_t = detail::signed_int32;
using uint_fast16_t = detail::unsigned_int32;
using int_fast32_t = detail::signed_int32;
using uint_fast32_t = detail::unsigned_int32;
using int_fast64_t = detail::signed_int64;
using uint_fast64_t = detail::unsigned_int64;
#elif PHI_TYPE_SYSTEM_SIZEOF_VOIDPTR() * CHAR_BIT == 64
using int_fast16_t = detail::signed_int64;
using uint_fast16_t = detail::unsigned_int64;
using int_fast32_t = detail::signed_int64;
using uint_fast32_t = detail::unsigned_int64;
using int_fast64_t = detail::signed_int64;
using uint_fast64_t = detail::unsigned_int64;
#endif

using int_least8_t  = detail::signed_int8;
using uint_least8_t = detail::unsigned_int8;

using int_least16_t  = detail::signed_int16;
using uint_least16_t = detail::unsigned_int16;

using int_least32_t  = detail::signed_int32;
using uint_least32_t = detail::unsigned_int32;

using int_least64_t  = detail::signed_int64;
using uint_least64_t = detail::unsigned_int64;

using float32 = detail::float32;
using float64 = detail::float64;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_SIZED_TYPES_HPP
