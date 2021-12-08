#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCEABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCEABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/detail/yes_no_type.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_same.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    struct is_referenceable_impl
    {
        template <typename TypeT>
        static TypeT& test(int);

        template <typename TypeT>
        static no_type test(...);
    };
} // namespace detail

template <typename TypeT>
struct is_referenceable
    : bool_constant<is_not_same<decltype(detail::is_referenceable_impl::test<TypeT>(0)),
                                detail::no_type>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
constexpr PHI_INLINE_VARIABLE bool is_referenceable_v = is_referenceable<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCEABLE_HPP
