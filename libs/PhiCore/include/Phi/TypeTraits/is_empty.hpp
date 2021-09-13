#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_EMPTY_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_EMPTY_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_class.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_EMPTY()

template <typename TypeT>
struct is_empty : public bool_constant<__is_empty(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_empty_v = __is_empty(TypeT);

#else

namespace detail
{
    template <typename TypeT>
    struct is_empty_test1 : public TypeT
    {
        double lx;
    };

    struct is_empty_test2
    {
        double lx;
    };

    template <typename TypeT, bool = is_class_v<TypeT>>
    struct is_empty_impl
        : public bool_constant<sizeof(is_empty_test1<TypeT>) == sizeof(is_empty_test2)>
    {};

    template <typename TypeT>
    struct is_empty_impl<TypeT, false> : public false_type
    {};
} // namespace detail

template <typename TypeT>
struct is_empty : public detail::is_empty_impl<TypeT>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_empty_v = is_empty<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_EMPTY_HPP
