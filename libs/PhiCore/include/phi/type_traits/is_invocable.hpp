#ifndef INCG_PHI_CORE_TYPE_TRAITS_INVOCABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_INVOCABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/declval.hpp"
#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/decay.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_base_of.hpp"
#include "phi/type_traits/is_convertible.hpp"
#include "phi/type_traits/is_member_function_pointer.hpp"
#include "phi/type_traits/is_member_object_pointer.hpp"
#include "phi/type_traits/is_reference_wrapper.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/is_void.hpp"
#include "phi/type_traits/nat.hpp"

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    struct any
    {
        any(...);
    };

    template <typename DecayedFpT>
    struct member_pointer_class_type
    {};

    template <typename RetT, typename ClassTypeT>
    struct member_pointer_class_type<RetT ClassTypeT::*>
    {
        using type = ClassTypeT;
    };

    template <typename FunctionPointerT, typename Arg0T,
              typename DecayFpT   = typename decay<FunctionPointerT>::type,
              typename DecayArg0T = typename decay<Arg0T>::type,
              typename ClassT     = typename member_pointer_class_type<DecayFpT>::type>
    using enable_if_bullet1 = typename enable_if<is_member_function_pointer<DecayFpT>::value &&
                                                 is_base_of<ClassT, DecayArg0T>::value>::type;

    template <typename FunctionPointerT, typename Arg0T,
              typename DecayFpT   = typename decay<FunctionPointerT>::type,
              typename DecayArg0T = typename decay<Arg0T>::type>
    using enable_if_bullet2 = typename enable_if<is_member_function_pointer<DecayFpT>::value &&
                                                 is_reference_wrapper<DecayArg0T>::value>::type;

    template <typename FunctionPointerT, typename Arg0T,
              typename DecayFpT   = typename decay<FunctionPointerT>::type,
              typename DecayArg0T = typename decay<Arg0T>::type,
              typename ClassT     = typename member_pointer_class_type<DecayFpT>::type>
    using enable_if_bullet3 = typename enable_if<is_member_function_pointer<DecayFpT>::value &&
                                                 !is_base_of<ClassT, DecayArg0T>::value &&
                                                 !is_reference_wrapper<DecayArg0T>::value>::type;

    template <typename FunctionPointerT, typename Arg0T,
              typename DecayFpT   = typename decay<FunctionPointerT>::type,
              typename DecayArg0T = typename decay<Arg0T>::type,
              typename ClassT     = typename member_pointer_class_type<DecayFpT>::type>
    using enable_if_bullet4 = typename enable_if<is_member_object_pointer<DecayFpT>::value &&
                                                 is_base_of<ClassT, DecayArg0T>::value>::type;

    template <typename FunctionPointerT, typename Arg0T,
              typename DecayFpT   = typename decay<FunctionPointerT>::type,
              typename DecayArg0T = typename decay<Arg0T>::type>
    using enable_if_bullet5 = typename enable_if<is_member_object_pointer<DecayFpT>::value &&
                                                 is_reference_wrapper<DecayArg0T>::value>::type;

    template <typename FunctionPointerT, typename Arg0T,
              typename DecayFpT   = typename decay<FunctionPointerT>::type,
              typename DecayArg0T = typename decay<Arg0T>::type,
              typename ClassT     = typename member_pointer_class_type<DecayFpT>::type>
    using enable_if_bullet6 = typename enable_if<is_member_object_pointer<DecayFpT>::value &&
                                                 !is_base_of<ClassT, DecayArg0T>::value &&
                                                 !is_reference_wrapper<DecayArg0T>::value>::type;

    // invoke_impl forward declarations

    // fall back - none of the bullets

    template <typename... ArgsT>
    auto invoke_impl(any, ArgsT&&... args) -> nat;

    // bullets 1, 2 and 3

    template <typename FunctionPointerT, typename Arg0T, typename... ArgsT,
              typename = enable_if_bullet1<FunctionPointerT, Arg0T>>
    inline constexpr auto invoke_impl(FunctionPointerT&& f, Arg0T&& a0, ArgsT&&... args) noexcept(
            noexcept((static_cast<Arg0T&&>(a0).*f)(static_cast<ArgsT&&>(args)...)))
            -> decltype((static_cast<Arg0T&&>(a0).*f)(static_cast<ArgsT&&>(args)...))
    {
        return (static_cast<Arg0T&&>(a0).*f)(static_cast<ArgsT&&>(args)...);
    }

    template <typename FunctionPointerT, typename Arg0T, typename... ArgsT,
              typename = enable_if_bullet2<FunctionPointerT, Arg0T>>
    inline constexpr auto invoke_impl(FunctionPointerT&& f, Arg0T&& a0, ArgsT&&... args) noexcept(
            noexcept((a0.get().*f)(static_cast<ArgsT&&>(args)...)))
            -> decltype((a0.get().*f)(static_cast<ArgsT&&>(args)...))
    {
        return (a0.get().*f)(static_cast<ArgsT&&>(args)...);
    }

    template <typename FunctionPointerT, typename Arg0T, typename... ArgsT,
              typename = enable_if_bullet3<FunctionPointerT, Arg0T>>
    inline constexpr auto invoke_impl(FunctionPointerT&& f, Arg0T&& a0, ArgsT&&... args) noexcept(
            noexcept(((*static_cast<Arg0T&&>(a0)).*f)(static_cast<ArgsT&&>(args)...)))
            -> decltype(((*static_cast<Arg0T&&>(a0)).*f)(static_cast<ArgsT&&>(args)...))
    {
        return ((*static_cast<Arg0T&&>(a0)).*f)(static_cast<ArgsT&&>(args)...);
    }

    // bullets 4, 5 and 6

    template <typename FunctionPointerT, typename Arg0T,
              typename = enable_if_bullet4<FunctionPointerT, Arg0T>>
    inline constexpr auto invoke_impl(FunctionPointerT&& f,
                                      Arg0T&& a0) noexcept(noexcept(static_cast<Arg0T&&>(a0).*f))
            -> decltype(static_cast<Arg0T&&>(a0).*f)
    {
        return static_cast<Arg0T&&>(a0).*f;
    }

    template <typename FunctionPointerT, typename Arg0T,
              typename = enable_if_bullet5<FunctionPointerT, Arg0T>>
    inline constexpr auto invoke_impl(FunctionPointerT&& f,
                                      Arg0T&&            a0) noexcept(noexcept(a0.get().*f))
            -> decltype(a0.get().*f)
    {
        return a0.get().*f;
    }

    template <typename FunctionPointerT, typename Arg0T,
              typename = enable_if_bullet6<FunctionPointerT, Arg0T>>
    inline constexpr auto invoke_impl(FunctionPointerT&& f,
                                      Arg0T&& a0) noexcept(noexcept((*static_cast<Arg0T&&>(a0)).*f))
            -> decltype((*static_cast<Arg0T&&>(a0)).*f)
    {
        return (*static_cast<Arg0T&&>(a0)).*f;
    }

    // bullet 7

    template <typename FunctionPointerT, typename... ArgsT>
    inline constexpr auto invoke_impl(FunctionPointerT&& f, ArgsT&&... args) noexcept(
            noexcept(static_cast<FunctionPointerT&&>(f)(static_cast<ArgsT&&>(args)...)))
            -> decltype(static_cast<FunctionPointerT&&>(f)(static_cast<ArgsT&&>(args)...))
    {
        return static_cast<FunctionPointerT&&>(f)(static_cast<ArgsT&&>(args)...);
    }

    template <typename ReturnT, typename FunctionPointerT, typename... ArgsT>
    struct invokable_r_impl
    {
        template <typename XFunctionPointerT, typename... XArgsT>
        static auto try_call(int)
                -> decltype(invoke_impl(declval<XFunctionPointerT>(), declval<XArgsT>()...));

        template <typename XFunctionPointerT, typename... XArgsT>
        static nat try_call(...);

        // FIXME: Check that ReturnT, FunctionPointerT, and ArgsT... are all complete types, cv void,
        // or incomplete array types as required by the standard.
        using ResultT = decltype(try_call<FunctionPointerT, ArgsT...>(0));

        using type = conditional_t<
                is_not_same<ResultT, nat>::value,
                conditional_t<is_void<ReturnT>::value, true_type, is_convertible<ResultT, ReturnT>>,
                false_type>;
        static const bool value = type::value;
    };

    template <typename FunctionPointerT, typename... ArgsT>
    using invokable_impl = invokable_r_impl<void, FunctionPointerT, ArgsT...>;

    template <bool IsInvokable, bool IsCVVoid, typename ReturnT, typename FunctionPointerT,
              typename... ArgsT>
    struct nothrow_invokable_r_impl
    {
        static const bool value = false;
    };

    template <typename ReturnT, typename FunctionPointerT, typename... ArgsT>
    struct nothrow_invokable_r_impl<true, false, ReturnT, FunctionPointerT, ArgsT...>
    {
        using ThisT = nothrow_invokable_r_impl;

        template <typename TypeT>
        static void test_noexcept(TypeT) noexcept;

        static const bool value = noexcept(ThisT::test_noexcept<ReturnT>(
                invoke_impl(declval<FunctionPointerT>(), declval<ArgsT>()...)));
    };

    template <typename ReturnT, typename FunctionPointerT, typename... ArgsT>
    struct nothrow_invokable_r_impl<true, true, ReturnT, FunctionPointerT, ArgsT...>
    {
        static const bool value =
                noexcept(invoke_impl(declval<FunctionPointerT>(), declval<ArgsT>()...));
    };

    template <typename ReturnT, typename FunctionPointerT, typename... ArgsT>
    using nothrow_invokable_r =
            nothrow_invokable_r_impl<invokable_r_impl<ReturnT, FunctionPointerT, ArgsT...>::value,
                                     is_void<ReturnT>::value, ReturnT, FunctionPointerT, ArgsT...>;

    template <typename FunctionPointerT, typename... ArgsT>
    using nothrow_invokable =
            nothrow_invokable_r_impl<invokable_impl<FunctionPointerT, ArgsT...>::value, true, void,
                                     FunctionPointerT, ArgsT...>;

    template <typename FunctionPointerT, typename... ArgsT>
    struct invoke_of
        : public enable_if<invokable_impl<FunctionPointerT, ArgsT...>::value,
                           typename invokable_r_impl<void, FunctionPointerT, ArgsT...>::ResultT>
    {};
} // namespace detail

// is_invocable
template <typename FunctionT, typename... ArgsT>
struct is_invocable : public bool_constant<detail::invokable_impl<FunctionT, ArgsT...>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename FunctionT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_invocable_v = is_invocable<FunctionT, ArgsT...>::value;

#endif

// is_invocable_r
template <typename ReturnT, typename FunctionT, typename... ArgsT>
struct is_invocable_r
    : public bool_constant<detail::invokable_r_impl<ReturnT, FunctionT, ArgsT...>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename ReturnT, typename FunctionT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_invocable_r_v =
        is_invocable_r<ReturnT, FunctionT, ArgsT...>::value;

#endif

// is_nothrow_invocable
template <typename FunctionT, typename... ArgsT>
struct is_nothrow_invocable
    : public bool_constant<detail::nothrow_invokable<FunctionT, ArgsT...>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename FunctionT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_invocable_v =
        is_nothrow_invocable<FunctionT, ArgsT...>::value;

#endif

// is_nothrow_invocable_r
template <typename ReturnT, typename FunctionT, typename... ArgsT>
struct is_nothrow_invocable_r
    : public bool_constant<detail::nothrow_invokable_r<ReturnT, FunctionT, ArgsT...>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename ReturnT, typename FunctionT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_invocable_r_v =
        is_nothrow_invocable_r<ReturnT, FunctionT, ArgsT...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_TYPE_TRAITS_INVOCABLE_HPP
