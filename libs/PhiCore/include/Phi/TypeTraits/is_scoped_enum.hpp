#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SCOPED_ENUM_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SCOPED_ENUM_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include <type_traits>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool IsEnum>
    struct is_scoped_enum_impl : std::false_type
    {};

    template <typename TypeT>
    struct is_scoped_enum_impl<TypeT, true>
        : std::integral_constant<bool,
                                 !std::is_convertible<TypeT, std::underlying_type_t<TypeT>>::value>
    {};
} // namespace detail

template <typename TypeT>
struct is_scoped_enum : detail::is_scoped_enum_impl<TypeT, std::is_enum<TypeT>::value>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_scoped_enum_v = is_scoped_enum<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SCOPED_ENUM_HPP
