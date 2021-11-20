#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_BASE_OF_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_BASE_OF_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsBaseOf.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_BASE_OF()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename BaseT, typename DerivedT>
struct is_base_of : public bool_constant<PHI_IS_BASE_OF(BaseT, DerivedT)>
{};

template <typename BaseT, typename DerivedT>
struct is_not_base_of : public bool_constant<!PHI_IS_BASE_OF(BaseT, DerivedT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename BaseT, typename DerivedT>
PHI_INLINE_VARIABLE constexpr bool is_base_of_v = PHI_IS_BASE_OF(BaseT, DerivedT);

template <typename BaseT, typename DerivedT>
PHI_INLINE_VARIABLE constexpr bool is_not_base_of_v = !PHI_IS_BASE_OF(BaseT, DerivedT);

#    endif

#else

#    include "Phi/TypeTraits/is_class.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename BaseT>
    true_type test_pre_ptr_convertible(const volatile BaseT*);

    template <typename>
    false_type test_pre_ptr_convertible(const volatile void*);

    template <typename, typename>
    auto test_pre_is_base_of(...) -> true_type;

    template <typename BaseT, typename DerivedT>
    auto test_pre_is_base_of(int)
            -> decltype(test_pre_ptr_convertible<BaseT>(static_cast<DerivedT*>(nullptr)));
} // namespace detail

template <typename BaseT, typename DerivedT>
struct is_base_of
    : public bool_constant<is_class_v<BaseT> &&
                           is_class_v<DerivedT>&& decltype(detail::test_pre_is_base_of<
                                                           BaseT, DerivedT>(0))::value>
{};

template <typename BaseT, typename DerivedT>
struct is_not_base_of : public bool_bool_constant<!is_base_of<BaseT, DerivedT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename BaseT, typename DerivedT>
PHI_INLINE_VARIABLE constexpr bool is_base_of_v = is_base_of<BaseT, DerivedT>::value;

template <typename BaseT, typename DerivedT>
PHI_INLINE_VARIABLE constexpr bool is_not_base_of_v = is_not_base_of<BaseT, DerivedT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_BASE_OF_HPP
