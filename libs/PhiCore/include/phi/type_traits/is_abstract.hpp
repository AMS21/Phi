#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ABSTRACT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ABSTRACT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_abstract.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_IS_ABSTRACT()

#    define PHI_HAS_WORKING_IS_ABSTRACT() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_abstract : public bool_constant<PHI_IS_ABSTRACT(TypeT)>
{};

template <typename TypeT>
struct is_not_abstract : public bool_constant<!PHI_IS_ABSTRACT(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_abstract_v = PHI_IS_ABSTRACT(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_abstract_v = !PHI_IS_ABSTRACT(TypeT);

#    endif

#else

#    include "phi/type_traits/false_t.hpp"

#    define PHI_HAS_WORKING_IS_ABSTRACT() 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_abstract : public false_type
{
    static_assert(false_t<TypeT>::value, "phi::is_abstract requires compiler support");
};

template <typename TypeT>
struct is_not_abstract : public false_type
{
    static_assert(false_t<TypeT>::value, "phi::is_not_abstract requires compiler support");
};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_abstract_v = is_abstract<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_abstract_v = is_not_abstract<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ABSTRACT_HPP
