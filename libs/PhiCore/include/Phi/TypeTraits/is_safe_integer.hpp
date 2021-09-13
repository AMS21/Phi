#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_INTEGER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_INTEGER_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class Integer;

namespace detail
{
    template <typename TypeT>
    struct is_safe_integer_impl : public false_type
    {};

    template <typename TypeT>
    struct is_safe_integer_impl<Integer<TypeT>> : public true_type
    {};
} // namespace detail

template <typename TypeT>
struct is_safe_integer : public detail::is_safe_integer_impl<remove_cv_t<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_safe_integer_v = is_safe_integer<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_INTEGER_HPP
