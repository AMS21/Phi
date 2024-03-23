#ifndef INCG_PHI_CORE_TYPE_TRAITS_VOID_T_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_VOID_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{

#if PHI_HAS_FEATURE_VARIADIC_TEMPLATES()

    template <typename... TypesT>
    struct make_void
    {
        using type = void;
    };

#else

    template <typename Type0T, typename Type1T, typename Type2T, typename Type3T, typename Type4T,
              typename Type5T, typename Type6T, typename Type7T, typename Type8T, typename Type9T>
    struct make_void
    {
        using type = void;
    };

#endif

} // namespace detail

#if PHI_HAS_FEATURE_VARIADIC_TEMPLATES()

template <typename... TypesT>
using void_t = typename detail::make_void<TypesT...>::type;

#else

template <typename Type0T = void, typename Type1T = void, typename Type2T = void,
          typename Type3T = void, typename Type4T = void, typename Type5T = void,
          typename Type6T = void, typename Type7T = void, typename Type8T = void,
          typename Type9T = void>
using void_t = typename detail::make_void<Type0T, Type1T, Type2T, Type3T, Type4T, Type5T, Type6T,
                                          Type7T, Type8T, Type9T>::type;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_VOID_T_HPP
