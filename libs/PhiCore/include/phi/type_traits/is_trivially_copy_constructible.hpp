#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/add_const.hpp"
#include "phi/type_traits/add_lvalue_reference.hpp"
#include "phi/type_traits/is_trivially_constructible.hpp"

#define PHI_HAS_WORKING_IS_TRIVIALLY_COPY_CONSTRUCTIBLE()                                          \
    PHI_HAS_WORKING_IS_TRIVIALLY_CONSTRUCTIBLE()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_trivially_copy_constructible
    : public is_trivially_constructible<
              TypeT, typename add_lvalue_reference<typename add_const<TypeT>::type>::type>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_copy_constructible_v =
        is_trivially_copy_constructible<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_HPP
