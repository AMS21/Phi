#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_WRAPPER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_WRAPPER_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

namespace std
{
    template <typename TypeT>
    class reference_wrapper;
}

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    struct is_reference_wrapper_impl : false_type
    {};

    template <typename TypeT>
    struct is_reference_wrapper_impl<std::reference_wrapper<TypeT>> : true_type
    {};
} // namespace detail

template <typename TypeT>
struct is_reference_wrapper : detail::is_reference_wrapper_impl<typename remove_cv<TypeT>::type>
{};

template <typename TypeT>
constexpr PHI_INLINE_VARIABLE bool is_reference_wrapper_v = is_reference_wrapper<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_WRAPPER_HPP
