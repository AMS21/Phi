#ifndef INCG_UNITTEST_UNWRAP_HPP
#define INCG_UNITTEST_UNWRAP_HPP

#include "Phi/Config/Warning.hpp"
#include <Phi/CompilerSupport/Nodiscard.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/Conversion.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/TypeTraits/integral_constant.hpp>
#include <Phi/TypeTraits/is_safe_type.hpp>
#include <utility>

template <typename TypeT>
struct unwrapped
{
    using value_type = TypeT;
};

template <>
struct unwrapped<phi::Boolean>
{
    using value_type = bool;
};

template <typename FloatT>
struct unwrapped<phi::FloatingPoint<FloatT>>
{
    using value_type = FloatT;
};

template <typename IntegerT>
struct unwrapped<phi::Integer<IntegerT>>
{
    using value_type = IntegerT;
};

template <typename TypeT>
using unwrapped_t = typename unwrapped<TypeT>::value_type;

namespace detail
{
    template <typename TypeT>
    PHI_NODISCARD constexpr unwrapped_t<TypeT> unwrap_impl(TypeT          source,
                                                           phi::true_type is_safe_type) noexcept
    {
        PHI_UNUSED_PARAMETER(is_safe_type);

        return source.get();
    }

    template <typename TypeT>
    PHI_NODISCARD constexpr unwrapped_t<TypeT> unwrap_impl(TypeT           source,
                                                           phi::false_type is_safe_type) noexcept
    {
        PHI_UNUSED_PARAMETER(is_safe_type);

        return source;
    }
} // namespace detail

template <typename TypeT>
PHI_NODISCARD constexpr unwrapped_t<TypeT> unwrap(TypeT source) noexcept
{
    return detail::unwrap_impl(source, phi::is_safe_type<TypeT>{});
}

#endif // INCG_UNITTEST_UNWRAP_HPP
