#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_COMPELTE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_COMPELTE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Declval.hpp"
#include "Phi/TypeTraits/detail/yes_no_type.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_function.hpp"
#include "Phi/TypeTraits/is_rvalue_reference.hpp"
#include "Phi/TypeTraits/remove_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wzero-as-null-pointer-constant")

namespace detail
{
    template <typename TypeT>
    struct is_complete_imp
    {
        template <typename OtherT, typename = decltype(sizeof(declval<OtherT>()))>
        static yes_type check(OtherT*);

        template <typename OtherT>
        static no_type check(...);

        static const bool value = sizeof(check<TypeT>(0)) == sizeof_yes_type;
    };
} // namespace detail

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename TypeT>
struct is_complete
    : public bool_constant<is_function<typename remove_reference<TypeT>::type>::value ||
                           is_rvalue_reference<TypeT>::value ||
                           detail::is_complete_imp<TypeT>::value>
{};

template <typename TypeT>
struct is_complete<TypeT&> : public is_complete<TypeT>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_complete_v = is_complete<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_COMPELTE_HPP
