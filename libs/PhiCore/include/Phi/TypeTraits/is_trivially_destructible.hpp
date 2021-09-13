#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_destructible.hpp"
#include "Phi/TypeTraits/is_reference.hpp"
#include "Phi/TypeTraits/is_scalar.hpp"
#include "Phi/TypeTraits/remove_all_extents.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE()

template <typename TypeT>
struct is_trivially_destructible : public bool_constant<__is_trivially_destructible(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_destructible_v = __is_trivially_destructible(TypeT);

#elif PHI_HAS_INTRINSIC_HAS_TRIVIAL_DESTRUCTOR()

template <typename TypeT>
struct is_trivially_destructible
    : public bool_constant<is_destructible_v<TypeT>&& __has_trivial_destructor(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_destructible_v =
        is_trivially_destructible<TypeT>::value;

#else

namespace detail
{
    template <typename TypeT>
    struct is_trivially_destructible_impl
        : bool_constant<is_scalar_v<TypeT> || is_reference_v<TypeT>>
    {};
} // namespace detail

template <typename TypeT>
struct is_trivially_destructible
    : public detail::is_trivially_destructible_impl<remove_all_extents_t<TypeT>>
{};

template <typename TypeT>
struct is_trivially_destructible<TypeT[]> : public false_type
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_destructible_v =
        is_trivially_destructible<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
