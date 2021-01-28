#ifndef INCG_PHI_CORE_TYPETRAITS_HPP
#define INCG_PHI_CORE_TYPETRAITS_HPP

#include "Phi/PhiConfig.hpp"

#include <cstddef>
#include <type_traits>

DETAIL_PHI_BEGIN_NAMESPACE()

// is_bounded_array
template <typename TypeT>
struct is_bounded_array : std::false_type
{};

template <typename TypeT, std::size_t SizeT>
struct is_bounded_array<TypeT[SizeT]> : std::true_type
{};

template <typename TypeT>
inline constexpr bool is_bounded_array_v = is_bounded_array<TypeT>::value;

// is_unbounded_array
template <typename TypeT>
struct is_unbounded_array : std::false_type
{};

template <typename TypeT>
struct is_unbounded_array<TypeT[]> : std::true_type
{};

template <typename TypeT>
inline constexpr bool is_unbounded_array_v = is_unbounded_array<TypeT>::value;

// is_scoped_enum
namespace detail
{
    template <typename TypeT, bool IsEnum>
    struct is_scoped_enum_impl : std::false_type
    {};

    template <typename TypeT>
    struct is_scoped_enum_impl<TypeT, true>
        : std::bool_constant<!std::is_convertible_v<TypeT, std::underlying_type_t<TypeT>>>
    {};
} // namespace detail

template <typename TypeT>
struct is_scoped_enum : detail::is_scoped_enum_impl<TypeT, std::is_enum_v<TypeT>>
{};

template <typename TypeT>
inline constexpr bool is_scoped_enum_v = is_scoped_enum<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPETRAITS_HPP
