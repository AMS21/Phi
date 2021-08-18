#ifndef INCG_PHI_CORE_MATH_SIGNUM_HPP
#define INCG_PHI_CORE_MATH_SIGNUM_HPP

#include "Phi/Config/Inline.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Types.hpp"
#include "Phi/PhiConfig.hpp"
#include <type_traits>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    [[nodiscard]] PHI_ALWAYS_INLINE constexpr i32 signum_impl(TypeT           value,
                                                              std::false_type is_signed) noexcept
    {
        PHI_UNUSED_PARAMETER(is_signed);

        return static_cast<std::int32_t>(TypeT(0) < value);
    }

    template <typename TypeT>
    [[nodiscard]] PHI_ALWAYS_INLINE constexpr i32 signum_impl(TypeT          value,
                                                              std::true_type is_signed) noexcept
    {
        PHI_UNUSED_PARAMETER(is_signed);

        return static_cast<std::int32_t>((TypeT(0) < value) - (value < TypeT(0)));
    }
} // namespace detail

template <typename TypeT>
[[nodiscard]] PHI_ALWAYS_INLINE constexpr i32 signum(TypeT value) noexcept
{
    return detail::signum_impl(value, std::is_signed<TypeT>());
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_SIGNUM_HPP
