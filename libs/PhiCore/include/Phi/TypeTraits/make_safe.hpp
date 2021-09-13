#ifndef INCG_PHI_CORE_TYPE_TRAITS_MAKE_SAFE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_MAKE_SAFE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/TypeTraits/conditional.hpp"
#include "Phi/TypeTraits/copy_cv.hpp"
#include "Phi/TypeTraits/is_unsafe_bool.hpp"
#include "Phi/TypeTraits/is_unsafe_floating_point.hpp"
#include "Phi/TypeTraits/is_unsafe_integer.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

class Boolean;

template <typename TypeT>
class FloatingPoint;

template <typename TypeT>
class Integer;

namespace detail
{
    template <typename TypeT>
    struct make_safe_impl
    {
        using type = conditional_t<
                is_unsafe_bool_v<TypeT>, Boolean,
                conditional_t<is_unsafe_floating_point_v<TypeT>, FloatingPoint<TypeT>,
                              conditional_t<is_unsafe_integer_v<TypeT>, Integer<TypeT>, TypeT>>>;
    };
} // namespace detail

template <typename TypeT>
struct make_safe
{
    using type = copy_cv_t<TypeT, typename detail::make_safe_impl<remove_cv_t<TypeT>>::type>;
};

template <typename TypeT>
using make_safe_t = typename make_safe<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_MAKE_SAFE_HPP
