#ifndef INCG_PHI_CORE_TYPE_TRAITS_COMMON_TYPE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_COMMON_TYPE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/core/declval.hpp"
#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/decay.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/remove_cvref.hpp"
#include "phi/type_traits/void_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename... TypesT>
struct common_type;

namespace detail
{
    // Let COND_RES(X, Y) be:
    template <typename TypeT, typename OtherT>
    using condition_type = decltype(false ? declval<TypeT>() : declval<OtherT>());

    template <typename TypeT, typename OtherT, typename = void>
    struct common_type3_impl
    {};

    // sub-bullet 4 - "if COND_RES(CREF(D1), CREF(D2)) denotes a type..."
    template <typename TypeT, typename OtherT>
    struct common_type3_impl<TypeT, OtherT, void_t<condition_type<const TypeT&, const OtherT&>>>
    {
        using type = remove_cvref_t<condition_type<const TypeT&, const OtherT&>>;
    };

    template <typename TypeT, typename OtherT, typename = void>
    struct common_type2_impl : public common_type3_impl<TypeT, OtherT>
    {};

    // sub-bullet 3 - "if decay_t<decltype(false ? declval<D1>() : declval<D2>())> ..."
    template <typename TypeT, typename OtherT>
    struct common_type2_impl<
            TypeT, OtherT,
            typename void_t<decltype(true ? declval<TypeT>() : declval<OtherT>())>::type>
    {
        using type = typename decay<decltype(true ? declval<TypeT>() : declval<OtherT>())>::type;
    };

    template <typename, typename = void>
    struct common_type_impl
    {};

    template <typename... TypeT>
    struct common_types;

    template <typename TypeT, typename OtherT>
    struct common_type_impl<common_types<TypeT, OtherT>,
                            typename void_t<typename common_type<TypeT, OtherT>::type>::type>
    {
        using type = typename common_type<TypeT, OtherT>::type;
    };

    template <typename TypeT, typename OtherT, typename ThirdT, typename... RestT>
    struct common_type_impl<common_types<TypeT, OtherT, ThirdT, RestT...>,
                            typename void_t<typename common_type<TypeT, OtherT>::type>::type>
        : public common_type_impl<
                  common_types<typename common_type<TypeT, OtherT>::type, ThirdT, RestT...>>
    {};
} // namespace detail

// bullet 1 - sizeof...(Tp) == 0

template <>
struct common_type<>
{};

// bullet 2 - sizeof...(Tp) == 1

template <typename TypeT>
struct common_type<TypeT> : public common_type<TypeT, TypeT>
{};

// bullet 3 - sizeof...(Tp) == 2

// sub-bullet 1 - "If is_same_v<T1, D1> is false or ..."
template <typename TypeT, typename OtherT>
struct common_type<TypeT, OtherT>
    : public conditional<
              is_same<TypeT, typename decay<TypeT>::type>::value &&
                      is_same<OtherT, typename decay<OtherT>::type>::value,
              detail::common_type2_impl<TypeT, OtherT>,
              common_type<typename decay<TypeT>::type, typename decay<OtherT>::type>>::type
{};

// bullet 4 - sizeof...(Tp) > 2

template <typename TypeT, typename OtherT, typename ThirdT, typename... RestT>
struct common_type<TypeT, OtherT, ThirdT, RestT...>
    : public detail::common_type_impl<detail::common_types<TypeT, OtherT, ThirdT, RestT...>>
{};

template <typename... TypeT>
using common_type_t = typename common_type<TypeT...>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_COMMON_TYPE_HPP
