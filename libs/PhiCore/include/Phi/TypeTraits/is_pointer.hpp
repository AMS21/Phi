#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename TypeT>
    struct is_pointer_impl : public false_type
    {};

    template <typename TypeT>
    struct is_pointer_impl<TypeT*> : public true_type
    {};
} // namespace detail
/// \endcond

template <typename TypeT>
struct is_pointer : public detail::is_pointer_impl<remove_cv_t<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_pointer_v = is_pointer<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_HPP
