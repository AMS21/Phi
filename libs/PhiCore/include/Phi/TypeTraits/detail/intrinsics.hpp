#ifndef INCG_PHI_CORE_TYPE_TRAITS_DETAIL_INTRINSICS_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_DETAIL_INTRINSICS_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/Config/Warning.hpp"

// is_assignable
// Note GCCs implementation of __is_assignable is bugged
// See: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=102305
#if PHI_HAS_INTRINSIC_IS_ASSIGNABLE() && !defined(PHI_CONFIG_NO_INTRINSICS)
#    define PHI_TYPE_TRAITS_USE_INTRINSIC_IS_ASSIGNABLE() 1
#    define PHI_IS_ASSIGNABLE(...)                        __is_assignable(__VA_ARGS__)
#else
#    define PHI_TYPE_TRAITS_USE_INTRINSIC_IS_ASSIGNABLE() 0
#    define PHI_IS_ASSIGNABLE(...)                        false
#endif

// GCCs implementation of __is_constructible is bugged
// See: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=102305
#if PHI_HAS_INTRINSIC_IS_CONSTRUCTIBLE() && !defined(PHI_CONFIG_NO_INTRINSICS)
#    define PHI_TYPE_TRAITS_USE_INTRINSIC_IS_CONSTRUCTIBLE() 1
#    define PHI_IS_CONSTRUCTIBLE(...)                        __is_constructible(__VA_ARGS__)
#else
#    define PHI_TYPE_TRAITS_USE_INTRINSIC_IS_CONSTRUCTIBLE() 0
#    define PHI_IS_CONSTRUCTIBLE(...))                       false
#endif

#endif // INCG_PHI_CORE_TYPE_TRAITS_DETAIL_INTRINSICS_HPP
