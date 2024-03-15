
#ifndef INCG_PHI_CORE_ADDRESS_OF_HPP
#define INCG_PHI_CORE_ADDRESS_OF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/intrinsics/address_of.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_object.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_WORKING_IS_OBJECT()

template <typename TypeT>
PHI_NODISCARD PHI_CONSTEXPR typename enable_if<is_object<TypeT>::value, TypeT*>::type address_of(
        TypeT& arg) noexcept
{
#    if PHI_SUPPORTS_ADDRESS_OF()
    return PHI_ADDRESS_OF(arg);
#    else
    return reinterpret_cast<TypeT*>(
            &const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
#    endif
}

template <typename TypeT>
PHI_NODISCARD PHI_CONSTEXPR typename enable_if<!is_object<TypeT>::value, TypeT*>::type address_of(
        TypeT& arg) noexcept
{
    return &arg;
}

#else

template <typename TypeT>
PHI_NODISCARD PHI_CONSTEXPR TypeT* address_of(TypeT& arg) noexcept
{
#    if PHI_SUPPORTS_ADDRESS_OF()
    return PHI_ADDRESS_OF(arg);
#    else
    return reinterpret_cast<TypeT*>(
            &const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
#    endif
}

#endif

template <typename TypeT>
const TypeT* address_of(const TypeT&&) = delete;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ADDRESS_OF_HPP
