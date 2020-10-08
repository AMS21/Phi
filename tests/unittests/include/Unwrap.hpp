#ifndef INCG_UNITTEST_UNWRAP_HPP
#define INCG_UNITTEST_UNWRAP_HPP

#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/Conversion.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <type_traits>

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

template <typename TypeT>
[[nodiscard]] constexpr unwrapped_t<TypeT> unwrap(TypeT&& source) noexcept
{
    if constexpr (phi::detail::is_floatingpoint_specialization<TypeT>::value ||
                  phi::detail::is_integer_specilization<TypeT>::value ||
                  std::is_same_v<phi::Boolean, std::remove_reference_t<std::remove_cv_t<TypeT>>>)
    {
        return source.get();
    }
    else
    {
        return source;
    }
}

#endif // INCG_UNITTEST_UNWRAP_HPP
