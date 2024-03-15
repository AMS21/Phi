#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_COMPLETE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_COMPLETE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_complete.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_IS_COMPLETE() && 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_complete : public bool_constant<PHI_IS_COMPLETE(TypeT)>
{};

template <typename TypeT>
struct is_not_complete : public bool_constant<!PHI_IS_COMPLETE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_complete_v = PHI_IS_COMPLETE(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_complete_v = !PHI_IS_COMPLETE(TypeT);

#    endif

#else

#    include "phi/compiler_support/warning.hpp"
#    include "phi/core/declval.hpp"
#    include "phi/type_traits/detail/yes_no_type.hpp"
#    include "phi/type_traits/is_function.hpp"
#    include "phi/type_traits/is_rvalue_reference.hpp"
#    include "phi/type_traits/remove_reference.hpp"

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

        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
        static PHI_CONSTEXPR_AND_CONST bool value =
                sizeof(check<TypeT>(nullptr)) == sizeof_yes_type;
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

template <typename TypeT>
struct is_not_complete : public bool_constant<!is_complete<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_complete_v = is_complete<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_complete_v = is_not_complete<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_COMPLETE_HPP
