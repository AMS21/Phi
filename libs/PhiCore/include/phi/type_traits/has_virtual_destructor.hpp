#ifndef INCG_PHI_CORE_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/has_virtual_destructor.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_HAS_VIRTUAL_DESTRUCTOR()

#    define PHI_HAS_WORKING_HAS_VIRTUAL_DESTRUCTOR() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct has_virtual_destructor : public bool_constant<PHI_HAS_VIRTUAL_DESTRUCTOR(TypeT)>
{};

template <typename TypeT>
struct has_no_virtual_destructor : public bool_constant<!PHI_HAS_VIRTUAL_DESTRUCTOR(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool has_virtual_destructor_v = PHI_HAS_VIRTUAL_DESTRUCTOR(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool has_no_virtual_destructor_v =
        !PHI_HAS_VIRTUAL_DESTRUCTOR(TypeT);

#    endif

#else

#    include "phi/type_traits/false_t.hpp"

#    define PHI_HAS_WORKING_HAS_VIRTUAL_DESTRUCTOR() 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct has_virtual_destructor : public false_type
{
    static_assert(false_t<TypeT>::value,
                  "phi::has_virtual_destructor requires compiler support for "
                  "intrinsic has_virtual_destructor");
};

template <typename TypeT>
struct has_no_virtual_destructor : public false_type
{
    static_assert(false_t<TypeT>::value,
                  "phi::has_no_virtual_destructor requires compiler support for "
                  "intrinsic has_virtual_destructor");
};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool has_virtual_destructor_v =
        has_virtual_destructor<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool has_no_virtual_destructor_v =
        has_no_virtual_destructor<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP
