#ifndef INCG_PHI_CORE_TYPETRAITS_HPP
#define INCG_PHI_CORE_TYPETRAITS_HPP

#include "Phi/PhiConfig.hpp"

#include <cstddef>
#include <functional>
#include <type_traits>
#include <utility>

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

// copy_const
template <typename FromT, typename ToT>
struct copy_const
{
    using type = typename std::conditional<std::is_const<FromT>::value,
                                           const typename std::remove_const<ToT>::type, ToT>::type;
};

template <typename FromT, typename ToT>
using copy_const_v = typename copy_const<FromT, ToT>::type;

// invoke
template <typename FnT, typename... ArgsT,
          typename = std::enable_if_t<std::is_member_pointer<std::decay_t<FnT>>::value>, int = 0>
constexpr auto invoke(FnT&& f, ArgsT&&... args) noexcept(
        noexcept(std::mem_fn(f)(std::forward<ArgsT>(args)...)))
        -> decltype(std::mem_fn(f)(std::forward<ArgsT>(args)...))
{
    return std::mem_fn(f)(std::forward<ArgsT>(args)...);
}

template <typename FnT, typename... ArgsT,
          typename = std::enable_if_t<!std::is_member_pointer<std::decay_t<FnT>>::value>>
constexpr auto invoke(FnT&& f, ArgsT&&... args) noexcept(
        noexcept(std::forward<FnT>(f)(std::forward<ArgsT>(args)...)))
        -> decltype(std::forward<FnT>(f)(std::forward<ArgsT>(args)...))
{
    return std::forward<FnT>(f)(std::forward<ArgsT>(args)...);
}

// std::invoke_result
namespace detail
{
    template <typename FnT, typename, typename... ArgsT>
    struct invoke_result_impl;

    template <typename FnT, typename... ArgsT>
    struct invoke_result_impl<
            FnT, decltype(invoke(std::declval<FnT>(), std::declval<ArgsT>()...), void()), ArgsT...>
    {
        using type = decltype(invoke(std::declval<FnT>(), std::declval<ArgsT>()...));
    };
} // namespace detail

template <typename FnT, typename... ArgsT>
using invoke_result = detail::invoke_result_impl<FnT, void, ArgsT...>;

template <typename FnT, typename... ArgsT>
using invoke_result_t = typename invoke_result<FnT, ArgsT...>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPETRAITS_HPP
