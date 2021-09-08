#ifndef INCG_UNITTEST_UNWRAP_HPP
#define INCG_UNITTEST_UNWRAP_HPP

#include "Phi/Config/Warning.hpp"
#include <Phi/CompilerSupport/Nodiscard.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/Conversion.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <type_traits>
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
                                                           std::true_type is_safe_type) noexcept
    {
        PHI_UNUSED_PARAMETER(is_safe_type);

        return source.get();
    }

    template <typename TypeT>
    PHI_NODISCARD constexpr unwrapped_t<TypeT> unwrap_impl(TypeT           source,
                                                           std::false_type is_safe_type) noexcept
    {
        PHI_UNUSED_PARAMETER(is_safe_type);

        return source;
    }
} // namespace detail

template <typename TypeT>
PHI_NODISCARD constexpr unwrapped_t<TypeT> unwrap(TypeT source) noexcept
{
    using is_safe_type_t = typename std::integral_constant<
            bool, phi::detail::is_floatingpoint_specialization<TypeT>::value ||
                          phi::detail::is_integer_specilization<TypeT>::value ||
                          phi::detail::is_boolean_specilization<TypeT>::value>;

    return detail::unwrap_impl(source, is_safe_type_t{});
}

#endif // INCG_UNITTEST_UNWRAP_HPP
