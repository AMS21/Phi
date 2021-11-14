#ifndef INCG_PHI_CORE_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/TypeTraits/is_referenceable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool = is_referenceable<TypeT>::value>
    struct add_rvalue_reference_impl
    {
        using type = TypeT;
    };

    template <typename TypeT>
    struct add_rvalue_reference_impl<TypeT, true>
    {
        using type = TypeT&&;
    };
} // namespace detail

template <typename TypeT>
struct add_rvalue_reference
{
    using type = typename detail::add_rvalue_reference_impl<TypeT>::type;
};

template <typename TypeT>
using add_rvalue_reference_t = typename add_rvalue_reference<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP
