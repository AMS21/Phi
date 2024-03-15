#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_trivial.hpp"
#include "phi/compiler_support/intrinsics/is_trivially_constructible.hpp"
#include "phi/compiler_support/intrinsics/is_trivially_copyable.hpp"
#include "phi/type_traits/bool_constant.hpp"

// MSVC's implementation of is_trivial seems broken
#if PHI_SUPPORTS_IS_TRIVIAL() && PHI_COMPILER_IS_NOT(MSVC)

#    define PHI_HAS_WORKING_IS_TRIVIAL() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_trivial : public bool_constant<PHI_IS_TRIVIAL(TypeT)>
{};

template <typename TypeT>
struct is_not_trivial : public bool_constant<!PHI_IS_TRIVIAL(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_trivial_v = PHI_IS_TRIVIAL(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_trivial_v = !PHI_IS_TRIVIAL(TypeT);

#    endif

#elif PHI_SUPPORTS_IS_TRIVIALLY_CONSTRUCTIBLE() && PHI_SUPPORTS_IS_TRIVIALLY_COPYABLE()

#    define PHI_HAS_WORKING_IS_TRIVIAL() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_trivial : public bool_constant<PHI_IS_TRIVIALLY_CONSTRUCTIBLE(TypeT) &&
                                         PHI_IS_TRIVIALLY_COPYABLE(TypeT)>
{};

template <typename TypeT>
struct is_not_trivial : public bool_constant<!PHI_IS_TRIVIALLY_CONSTRUCTIBLE(TypeT) ||
                                             !PHI_IS_TRIVIALLY_COPYABLE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_trivial_v =
        PHI_IS_TRIVIALLY_CONSTRUCTIBLE(TypeT) && PHI_IS_TRIVIALLY_COPYABLE(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_trivial_v =
        !PHI_IS_TRIVIALLY_CONSTRUCTIBLE(TypeT) || !PHI_IS_TRIVIALLY_COPYABLE(TypeT);

#    endif

#else

#    include "phi/type_traits/is_trivially_copyable.hpp"
#    include "phi/type_traits/is_trivially_default_constructible.hpp"

#    if PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE() &&                                                 \
            PHI_HAS_WORKING_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE()
#        define PHI_HAS_WORKING_IS_TRIVIAL() 1
#    else
#        define PHI_HAS_WORKING_IS_TRIVIAL() 0
#    endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_trivial : public bool_constant<is_trivially_copyable<TypeT>::value &&
                                         is_trivially_default_constructible<TypeT>::value>
{};

template <typename TypeT>
struct is_not_trivial : public bool_constant<is_trivial<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_trivial_v = is_trivial<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_trivial_v = is_not_trivial<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIAL_HPP
