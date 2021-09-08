#ifndef INCG_PHI_CORE_TYPE_TRAITS_ADD_REFERENCE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ADD_REFERENCE_HPP

#include "Phi/PhiConfig.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    struct add_reference_impl
    {
        using type = TypeT&;
    };

    template <typename TypeT>
    struct add_reference_impl<TypeT&&>
    {
        using type = TypeT&&;
    };
} // namespace detail

template <typename TypeT>
struct add_reference
{
    using type = typename detail::add_reference_impl<TypeT>::type;
};

template <typename TypeT>
struct add_reference<TypeT&>
{
    using type = TypeT&;
};

// these full specializations are always required:
template <>
struct add_reference<void>
{
    using type = void;
};

template <>
struct add_reference<const void>
{
    using type = const void;
};

template <>
struct add_reference<const volatile void>
{
    using type = const volatile void;
};

template <>
struct add_reference<volatile void>
{
    using type = volatile void;
};

template <typename TypeT>
using add_reference_t = typename add_reference<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ADD_REFERENCE_HPP
