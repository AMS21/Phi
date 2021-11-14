#ifndef INCG_PHI_CORE_TYPE_TRAITS_DECAY_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_DECAY_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/TypeTraits/add_pointer.hpp"
#include "Phi/TypeTraits/conditional.hpp"
#include "Phi/TypeTraits/is_array.hpp"
#include "Phi/TypeTraits/is_function.hpp"
#include "Phi/TypeTraits/is_referenceable.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"
#include "Phi/TypeTraits/remove_extent.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool>
    struct decay_impl
    {
        using type = remove_cv_t<TypeT>;
    };

    template <typename TypeT>
    struct decay_impl<TypeT, true>
    {
    public:
        using type = conditional_t<
                is_array<TypeT>::value, remove_extent_t<TypeT>*,
                conditional_t<is_function<TypeT>::value, add_pointer_t<TypeT>, remove_cv_t<TypeT>>>;
    };
} // namespace detail

template <typename TypeT>
struct decay
{
private:
    using NoRefT = typename remove_reference<TypeT>::type;

public:
    using type = typename detail::decay_impl<NoRefT, is_referenceable<NoRefT>::value>::type;
};

template <typename TypeT>
using decay_t = typename decay<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_DECAY_HPP
