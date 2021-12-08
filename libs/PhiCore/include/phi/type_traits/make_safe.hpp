#ifndef INCG_PHI_CORE_TYPE_TRAITS_MAKE_SAFE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_MAKE_SAFE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/copy_cv.hpp"
#include "phi/type_traits/is_unsafe_bool.hpp"
#include "phi/type_traits/is_unsafe_floating_point.hpp"
#include "phi/type_traits/is_unsafe_integer.hpp"
#include "phi/type_traits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

class boolean;

template <typename TypeT>
class floating_point;

template <typename TypeT>
class integer;

namespace detail
{
    template <typename TypeT>
    struct make_safe_impl
    {
        using type = conditional_t<
                is_unsafe_bool<TypeT>::value, boolean,
                conditional_t<
                        is_unsafe_floating_point<TypeT>::value, floating_point<TypeT>,
                        conditional_t<is_unsafe_integer<TypeT>::value, integer<TypeT>, TypeT>>>;
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
