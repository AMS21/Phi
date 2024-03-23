#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_constructible.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()

#    include "phi/compiler_support/warning.hpp"

#    define PHI_HAS_WORKING_IS_CONSTRUCTIBLE() 1

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wignored-qualifiers")

template <typename TypeT, typename... ArgsT>
struct is_constructible : public integral_constant<bool, PHI_IS_CONSTRUCTIBLE(TypeT, ArgsT...)>
{};

template <typename TypeT, typename... ArgsT>
struct is_not_constructible : public integral_constant<bool, !PHI_IS_CONSTRUCTIBLE(TypeT, ArgsT...)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_constructible_v = PHI_IS_CONSTRUCTIBLE(TypeT, ArgsT...);

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_constructible_v =
        !PHI_IS_CONSTRUCTIBLE(TypeT, ArgsT...);

#    endif

PHI_GCC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#else

#    include "phi/core/declval.hpp"
#    include "phi/type_traits/conditional.hpp"
#    include "phi/type_traits/is_base_of.hpp"
#    include "phi/type_traits/is_default_constructible.hpp"
#    include "phi/type_traits/is_destructible.hpp"
#    include "phi/type_traits/is_lvalue_reference.hpp"
#    include "phi/type_traits/is_reference.hpp"
#    include "phi/type_traits/is_rvalue_reference.hpp"
#    include "phi/type_traits/is_static_castable_to.hpp"
#    include "phi/type_traits/is_void.hpp"
#    include "phi/type_traits/remove_cv.hpp"
#    include "phi/type_traits/remove_reference.hpp"

#    if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE() && PHI_HAS_WORKING_IS_BASE_OF()
#        define PHI_HAS_WORKING_IS_CONSTRUCTIBLE() 1
#    else
#        define PHI_HAS_WORKING_IS_CONSTRUCTIBLE() 0
#    endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename... ArgsT>
struct is_constructible;

namespace detail
{
    // Implementation for non-reference types. To meet the proper
    // variable definition semantics, we also need to test for
    // is_destructible in this case.
    struct do_is_direct_constructible_impl
    {
        template <typename ToT, typename ArgT, typename = decltype(::new ToT(declval<ArgT>()))>
        static true_type test(int);

        template <typename, typename>
        static false_type test(...);
    };

    template <typename ToT, typename ArgT>
    struct is_direct_constructible_impl : public do_is_direct_constructible_impl
    {
        using type = decltype(test<ToT, ArgT>(0));

        static PHI_CONSTEXPR_AND_CONST bool value = type::value;
    };

    template <typename ToT, typename ArgT>
    struct is_direct_constructible_new_safe
        : public integral_constant<bool, is_destructible<ToT>::value &&
                                                 is_direct_constructible_impl<ToT, ArgT>::value>
    {};

    template <typename FromT, typename ToT,
              bool = !(is_void<FromT>::value || is_function<FromT>::value)>
    struct is_base_to_derived_ref;

    // Detect whether we have a downcast situation during
    // reference binding.
    template <typename FromT, typename ToT>
    struct is_base_to_derived_ref<FromT, ToT, true>
    {
        using source_t      = typename remove_cv<typename remove_reference<FromT>::type>::type;
        using destination_t = typename remove_cv<typename remove_reference<ToT>::type>::type;

        using type =
                integral_constant<bool, is_not_same<source_t, destination_t>::value &&
                                                is_base_of<source_t, destination_t>::value &&
                                                !is_constructible<destination_t, FromT>::value>;

        static PHI_CONSTEXPR_AND_CONST bool value = type::value;
    };

    template <typename FromT, typename ToT>
    struct is_base_to_derived_ref<FromT, ToT, false> : public false_type
    {};

    template <typename FromT, typename ToT,
              bool = is_lvalue_reference<FromT>::value && is_rvalue_reference<ToT>::value>
    struct is_lvalue_to_rvalue_ref;

    // Detect whether we have an lvalue of non-function type
    // bound to a reference-compatible rvalue-reference.
    template <typename FromT, typename ToT>
    struct is_lvalue_to_rvalue_ref<FromT, ToT, true>
    {
        using source_t      = typename remove_cv<typename remove_reference<FromT>::type>::type;
        using destination_t = typename remove_cv<typename remove_reference<ToT>::type>::type;

        using type = integral_constant<bool, is_not_function<source_t>::value &&
                                                     (is_same<source_t, destination_t>::value ||
                                                      is_base_of<destination_t, source_t>::value)>;

        static PHI_CONSTEXPR_AND_CONST bool value = type::value;
    };

    template <typename FromT, typename ToT>
    struct is_lvalue_to_rvalue_ref<FromT, ToT, false> : public false_type
    {};

    // Here we handle direct-initialization to a reference type as
    // equivalent to a static_cast modulo overshooting conversions.
    // These are restricted to the following conversions:
    //    a) A base class value to a derived class reference
    //    b) An lvalue to an rvalue-reference of reference-compatible
    //       types that are not functions
    template <typename TypeT, typename ArgT>
    struct is_direct_constructible_ref_cast
        : public integral_constant<bool, is_static_castable_to<ArgT, TypeT>::value &&
                                                 !(is_base_to_derived_ref<ArgT, TypeT>::value ||
                                                   is_lvalue_to_rvalue_ref<ArgT, TypeT>::value)>
    {};

    template <typename TypeT, typename ArgT>
    struct is_direct_constructible_new
        : public conditional<is_reference<TypeT>::value,
                             is_direct_constructible_ref_cast<TypeT, ArgT>,
                             is_direct_constructible_new_safe<TypeT, ArgT>>::type
    {};

    template <typename TypeT, typename ArgT>
    struct is_direct_constructible : public is_direct_constructible_new<TypeT, ArgT>::type
    {};

    // Since default-construction and binary direct-initialization have
    // been handled separately, the implementation of the remaining
    // n-ary construction cases is rather straightforward. We can use
    // here a functional cast, because array types are excluded anyway
    // and this form is never interpreted as a C cast.
    struct do_is_nary_constructible_impl
    {
        template <typename TypeT, typename... ArgsT,
                  typename = decltype(TypeT(declval<ArgsT>()...))>
        static true_type test(int);

        template <typename, typename...>
        static false_type test(...);
    };

    template <typename TypeT, typename... ArgsT>
    struct is_nary_constructible_impl : public do_is_nary_constructible_impl
    {
        using type = decltype(test<TypeT, ArgsT...>(0));
    };

    template <typename TypeT, typename... ArgsT>
    struct is_nary_constructible : public is_nary_constructible_impl<TypeT, ArgsT...>::type
    {
        static_assert(sizeof...(ArgsT) > 1, "Only useful for > 1 arguments");
    };

    template <typename TypeT, typename... ArgsT>
    struct is_constructible_impl : public is_nary_constructible<TypeT, ArgsT...>
    {};

    template <typename TypeT, typename ArgT>
    struct is_constructible_impl<TypeT, ArgT> : public is_direct_constructible<TypeT, ArgT>
    {};

    template <>
    struct is_constructible_impl<void> : public false_type
    {};

    template <>
    struct is_constructible_impl<void const> : public false_type
    {};

    template <>
    struct is_constructible_impl<void volatile> : public false_type
    {};

    template <>
    struct is_constructible_impl<void const volatile> : public false_type
    {};

    template <typename TypeT>
    struct is_constructible_impl<TypeT> : public is_default_constructible<TypeT>
    {};
} // namespace detail

template <typename TypeT, typename... ArgsT>
struct is_constructible : public detail::is_constructible_impl<TypeT, ArgsT...>::type
{};

template <typename TypeT, typename... ArgsT>
struct is_not_constructible
    : public integral_constant<bool, !is_constructible<TypeT, ArgsT...>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_constructible_v =
        is_constructible<TypeT, ArgsT...>::value;

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_constructible_v =
        is_not_constructible<TypeT, ArgsT...>::value;

#    endif

DETAIL_PHI_END_NAMESPACE()

#endif

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
