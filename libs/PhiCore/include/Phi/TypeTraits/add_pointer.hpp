#ifndef INCG_PHI_CORE_TYPE_TRAITS_ADD_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ADD_POINTER_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/TypeTraits/remove_reference.hpp"
#include "Phi/TypeTraits/type_identity.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    auto try_add_pointer(int) -> type_identity<remove_reference_t<TypeT>*>;

    template <typename TypeT>
    auto try_add_pointer(...) -> type_identity<TypeT>;

} // namespace detail

template <typename TypeT>
struct add_pointer : public decltype(detail::try_add_pointer<TypeT>(0))
{};

template <typename TypeT>
using add_pointer_t = typename add_pointer<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ADD_POINTER_HPP
