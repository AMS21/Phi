#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_constructible.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()

#    include "phi/compiler_support/warning.hpp"

#    define PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE() 1

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wignored-qualifiers")

template <typename TypeT>
struct is_default_constructible : public bool_constant<PHI_IS_CONSTRUCTIBLE(TypeT)>
{};

template <typename TypeT>
struct is_not_default_constructible : public bool_constant<!PHI_IS_CONSTRUCTIBLE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_default_constructible_v = PHI_IS_CONSTRUCTIBLE(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_default_constructible_v = !PHI_IS_CONSTRUCTIBLE(TypeT);

#    endif

PHI_GCC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#else

#    include "phi/core/size_t.hpp"
#    include "phi/forward/std/pair.hpp"
#    include "phi/type_traits/detail/yes_no_type.hpp"
#    include "phi/type_traits/is_abstract.hpp"
#    include "phi/type_traits/is_complete.hpp"

#    if PHI_HAS_WORKING_IS_ABSTRACT()
#        define PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE() 1
#    else
#        define PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE() 0
#    endif

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    struct is_default_constructible_imp
    {
        template <typename TypeT, typename = decltype(TypeT())>
        static yes_type test(int);

        template <typename>
        static no_type test(...);
    };

    template <typename TypeT, bool Boolean>
    struct is_default_constructible_abstract_filter
    {
        static constexpr const bool value =
                sizeof(is_default_constructible_imp::test<TypeT>(0)) == detail::sizeof_yes_type;
    };

    template <typename TypeT>
    struct is_default_constructible_abstract_filter<TypeT, true>
    {
        static constexpr const bool value = false;
    };
} // namespace detail

template <typename TypeT>
struct is_default_constructible
    : public bool_constant<detail::is_default_constructible_abstract_filter<
              TypeT, is_abstract<TypeT>::value>::value>
{
    static_assert(is_complete<TypeT>::value,
                  "Arguments to is_default_constructible must be complete types");
};

template <typename TypeT, size_t Size>
struct is_default_constructible<TypeT[Size]> : public is_default_constructible<TypeT>
{};

template <typename TypeT>
struct is_default_constructible<TypeT[]> : public is_default_constructible<TypeT>
{};

template <typename TypeT>
struct is_default_constructible<TypeT&> : public false_type
{};

template <typename TypeT, typename OtherT>
struct is_default_constructible<std::pair<TypeT, OtherT>>
    : public bool_constant<is_default_constructible<TypeT>::value &&
                           is_default_constructible<OtherT>::value>
{};

template <typename TypeT>
struct is_default_constructible<TypeT&&> : public false_type
{};

template <>
struct is_default_constructible<void> : public false_type
{};

template <>
struct is_default_constructible<void const> : public false_type
{};

template <>
struct is_default_constructible<void volatile> : public false_type
{};

template <>
struct is_default_constructible<void const volatile> : public false_type
{};

template <typename TypeT>
struct is_not_default_constructible : public bool_constant<!is_default_constructible<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_default_constructible_v =
        is_default_constructible<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_default_constructible_v =
        is_not_default_constructible<TypeT>::value;

#    endif

DETAIL_PHI_END_NAMESPACE()

#endif

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
