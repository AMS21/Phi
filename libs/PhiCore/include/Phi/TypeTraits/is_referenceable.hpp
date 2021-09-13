#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCEABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCEABLE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/internals.hpp"
#include "Phi/TypeTraits/is_not_same.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    struct is_referenceable_impl
    {
        template <class TypeT>
        static TypeT& test(int);

        template <class TypeT>
        static two test(...);
    };
} // namespace detail

template <typename TypeT>
struct is_referenceable
    : bool_constant<is_not_same<decltype(detail::is_referenceable_impl::test<TypeT>(0)),
                                detail::two>::value>
{};

template <typename TypeT>
constexpr PHI_INLINE_VARIABLE bool is_referenceable_v = is_referenceable<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCEABLE_HPP
