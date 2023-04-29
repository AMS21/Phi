/**
 * @file accumulate.hpp
 * @brief Contains the implementation of the accumulate algorithm from the C++ standard library.
 *
 * @see https://en.cppreference.com/w/cpp/algorithm/accumulate
 */
#ifndef INCG_PHI_CORE_ALGORITHM_ACCUMULATE_HPP
#define INCG_PHI_CORE_ALGORITHM_ACCUMULATE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/move.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

/**
 * @brief Calculates the sum of values in the range [first, last), starting with the initial value `init`.
 *
 * This function performs a left fold on the input range.
 *
 * @tparam InputIteratorT The iterator type of the input range.
 * @tparam TypeT The type of the result.
 * @param first The first iterator of the input range.
 * @param last The end iterator of the input range.
 * @param init The initial value to start the sum.
 * @return The sum of all the values in the range.
 *
 * @note This function uses move semantics to avoid unnecessary copying of values.
 * @see https://en.cppreference.com/w/cpp/algorithm/accumulate
 */
// TODO: noexcept
template <typename InputIteratorT, typename TypeT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT accumulate(InputIteratorT first, InputIteratorT last,
                                                      TypeT init)
{
    for (; first != last; ++first)
    {
        init = move(init) + *first;
    }

    return init;
}

// TODO: noexcept
/**
 * @brief Calculates the sum of values in the range [first, last), using the binary operation `binary_operator`
 * to accumulate the values.
 *
 * This function performs a left fold on the input range.
 *
 * @tparam InputIteratorT The iterator type of the input range.
 * @tparam TypeT The type of the result.
 * @tparam BinaryOperationT The type of the binary operator used to accumulate the values.
 * @param first The first iterator of the input range.
 * @param last The end iterator of the input range.
 * @param init The initial value to start the sum.
 * @param binary_operator The binary operator used to accumulate the values.
 * @return The accumulated value of all the values in range.
 *
 * @note This function uses move semantics to avoid unnecessary copying of values.
 * @see https://en.cppreference.com/w/cpp/algorithm/accumulate
 */
template <typename InputIteratorT, typename TypeT, typename BinaryOperationT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT accumulate(InputIteratorT first, InputIteratorT last,
                                                      TypeT init, BinaryOperationT binary_operator)
{
    for (; first != last; ++first)
    {
        init = binary_operator(move(init), *first);
    }

    return init;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_ACCUMULATE_HPP
