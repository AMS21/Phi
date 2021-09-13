#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CLASS_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CLASS_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/internals.hpp"
#include "Phi/TypeTraits/is_union.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_CLASS()

template <typename TypeT>
struct is_class : public bool_constant<__is_class(TypeT)>
{};

#else

namespace detail
{
    template <typename TypeT>
    char is_class_test(int TypeT::*);

    template <typename TypeT>
    two is_class_test(...);
} // namespace detail

template <typename TypeT>
struct is_class
    : public bool_constant<sizeof(detail::is_class_test<TypeT>(0)) == 1 && !is_union_v<TypeT>>
{};

#endif

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_class_v = is_class<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CLASS_HPP
