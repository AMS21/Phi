#ifndef INCG_PHI_CORE_ADDRESS_OF_HPP
#define INCG_PHI_CORE_ADDRESS_OF_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/TypeTraits/enable_if.hpp"
#include "Phi/TypeTraits/is_object.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
PHI_NODISCARD constexpr enable_if_t<is_object_v<TypeT>, TypeT*> addressof(TypeT& arg) noexcept
{
#if PHI_HAS_INTRINSIC_BUILTIN_ADDRESS_OF()
    return __builtin_addressof(arg);
#else
    return reinterpret_cast<TypeT*>(
            &const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
#endif
}

template <typename TypeT>
PHI_NODISCARD constexpr enable_if_t<!is_object_v<TypeT>, TypeT*> addressof(TypeT& arg) noexcept
{
    return &arg;
}

template <typename TypeT>
const TypeT* addressof(const TypeT&&) = delete;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ADDRESS_OF_HPP
