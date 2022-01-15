#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_trivially_copyable.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_TRIVIALLY_COPYABLE()

#    define PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_trivially_copyable : public bool_constant<PHI_IS_TRIVIALLY_COPYABLE(TypeT)>
{};

template <typename TypeT>
struct is_not_trivially_copyable : public bool_constant<!PHI_IS_TRIVIALLY_COPYABLE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_copyable_v = PHI_IS_TRIVIALLY_COPYABLE(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_trivially_copyable_v = !PHI_IS_TRIVIALLY_COPYABLE(TypeT);

#    endif

#else

#    include "phi/type_traits/is_copy_assignable.hpp"
#    include "phi/type_traits/is_copy_constructible.hpp"
#    include "phi/type_traits/is_move_assignable.hpp"
#    include "phi/type_traits/is_move_constructible.hpp"
#    include "phi/type_traits/is_trivially_copy_assignable.hpp"
#    include "phi/type_traits/is_trivially_copy_constructible.hpp"
#    include "phi/type_traits/is_trivially_destructible.hpp"
#    include "phi/type_traits/is_trivially_move_assignable.hpp"
#    include "phi/type_traits/is_trivially_move_constructible.hpp"
#    include "phi/type_traits/remove_all_extents.hpp"
#    include "phi/type_traits/remove_const.hpp"

#    if PHI_HAS_WORKING_IS_COPY_CONSTRUCTIBLE() && PHI_HAS_WORKING_IS_MOVE_CONSTRUCTIBLE() &&      \
            PHI_HAS_WORKING_IS_TRIVIALLY_COPY_ASSIGNABLE() &&                                      \
            PHI_HAS_WORKING_IS_TRIVIALLY_COPY_CONSTRUCTIBLE() &&                                   \
            PHI_HAS_WORKING_IS_TRIVIALLY_DESTRUCTIBLE() &&                                         \
            PHI_HAS_WORKING_IS_TRIVIALLY_MOVE_ASSIGNABLE() &&                                      \
            PHI_HAS_WORKING_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE()
#        define PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE() 1
#    else
#        define PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE() 0
#    endif

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    struct is_trivially_copyable_impl
        : public bool_constant<
                  (is_trivially_copy_assignable<TypeT>::value ||
                   !is_copy_assignable<TypeT>::value) &&
                  (is_trivially_copy_constructible<TypeT>::value ||
                   !is_copy_constructible<TypeT>::value) &&
                  (is_trivially_move_assignable<TypeT>::value ||
                   !is_move_assignable<TypeT>::value) &&
                  (is_trivially_move_constructible<TypeT>::value ||
                   !is_move_constructible<TypeT>::value) &&
                  (is_copy_assignable<TypeT>::value || is_copy_constructible<TypeT>::value ||
                   is_move_assignable<TypeT>::value || is_move_constructible<TypeT>::value) &&
                  (is_trivially_destructible<TypeT>::value)>
    {};
} // namespace detail

template <typename TypeT>
struct is_trivially_copyable
    : public detail::is_trivially_copyable_impl<remove_all_extents_t<remove_const_t<TypeT>>>
{};

template <typename TypeT>
struct is_not_trivially_copyable : public bool_constant<!is_trivially_copyable<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_copyable_v = is_trivially_copyable<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_trivially_copyable_v =
        is_not_trivially_copyable<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
