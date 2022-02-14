#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_LITERAL_TYPE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_LITERAL_TYPE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_literal_type.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_IS_LITERAL_TYPE()

#    define PHI_HAS_WORKING_IS_LITERAL_TYPE() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_literal_type : public bool_constant<PHI_IS_LITERAL_TYPE(TypeT)>
{};

template <typename TypeT>
struct is_not_literal_type : public bool_constant<!PHI_IS_LITERAL_TYPE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_literal_type_v = PHI_IS_LITERAL_TYPE(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_literal_type_v = !PHI_IS_LITERAL_TYPE(TypeT);

#    endif

#else

#    include "phi/type_traits/false_t.hpp"

#    define PHI_HAS_WORKING_IS_LITERAL_TYPE() 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_literal_type : public false_type
{
    static_assert(false_t<TypeT>::value, "phi::is_literal_type requires compiler support");
};

template <typename TypeT>
struct is_not_literal_type : public bool_constant<!is_literal_type<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_literal_type_v = is_literal_type<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_literal_type_v = is_not_literal_type<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_LITERAL_TYPE_HPP
