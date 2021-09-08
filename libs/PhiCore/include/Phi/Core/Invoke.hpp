// This file is heavily inspired by Matvey Cherevkos <blackmatov@gmail.com> invoke.hpp library https://github.com/BlackMATov/invoke.hpp
// licensed under the MIT license https://github.com/BlackMATov/invoke.hpp/blob/main/LICENSE.md
// Original file at https://github.com/BlackMATov/invoke.hpp/blob/main/headers/invoke.hpp/invoke.hpp
/* MIT License

Copyright (C) 2018-2021, by Matvey Cherevko (blackmatov@gmail.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef INCG_PHI_CORE_INVOKE_HPP
#define INCG_PHI_CORE_INVOKE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/TypeTraits/is_reference_wrapper.hpp"
#include <type_traits>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    //
    // invoke_member_object_impl
    //

    template <typename BaseT, typename FunctionT, typename DerivedT,
              typename std::enable_if<
                      std::is_base_of<BaseT, typename std::decay<DerivedT>::type>::value,
                      int>::type = 0>
    constexpr auto invoke_member_object_impl(FunctionT BaseT::*f, DerivedT&& ref) noexcept(
            noexcept(std ::forward<DerivedT>(ref).*f)) -> decltype(std ::forward<DerivedT>(ref).*f)
    {
        return std ::forward<DerivedT>(ref).*f;
    }

    template <typename BaseT, typename FunctionT, typename RefWrapT,
              typename std::enable_if<
                      is_reference_wrapper<typename std::decay<RefWrapT>::type>::value, int>::type =
                      0>
    constexpr auto invoke_member_object_impl(FunctionT BaseT::*f,
                                             RefWrapT&&        ref) noexcept(noexcept(ref.get().*f))
            -> decltype(ref.get().*f)
    {
        return ref.get().*f;
    }

    template <typename BaseT, typename FunctionT, typename PointerT,
              typename std::enable_if<
                      !std::is_base_of<BaseT, typename std::decay<PointerT>::type>::value &&
                              !is_reference_wrapper<typename std::decay<PointerT>::type>::value,
                      int>::type = 0>
    constexpr auto invoke_member_object_impl(FunctionT BaseT::*f, PointerT&& ptr) noexcept(noexcept(
            (*std ::forward<PointerT>(ptr)).*f)) -> decltype((*std ::forward<PointerT>(ptr)).*f)
    {
        return (*std ::forward<PointerT>(ptr)).*f;
    }

    //
    // invoke_member_function_impl
    //

    template <typename BaseT, typename FunctionT, typename DerivedT, typename... ArgsT,
              typename std::enable_if<
                      std::is_base_of<BaseT, typename std::decay<DerivedT>::type>::value,
                      int>::type = 0>
    constexpr auto invoke_member_function_impl(
            FunctionT BaseT::*f, DerivedT&& ref,
            ArgsT&&... args) noexcept(noexcept((std ::forward<DerivedT>(ref).*
                                                f)(std ::forward<ArgsT>(args)...)))
            -> decltype((std ::forward<DerivedT>(ref).*f)(std ::forward<ArgsT>(args)...))
    {
        return (std ::forward<DerivedT>(ref).*f)(std ::forward<ArgsT>(args)...);
    }

    template <typename BaseT, typename FunctionT, typename RefWrapT, typename... ArgsT,
              typename std::enable_if<
                      is_reference_wrapper<typename std::decay<RefWrapT>::type>::value, int>::type =
                      0>
    constexpr auto invoke_member_function_impl(
            FunctionT BaseT::*f, RefWrapT&& ref,
            ArgsT&&... args) noexcept(noexcept((ref.get().*f)(std ::forward<ArgsT>(args)...)))
            -> decltype((ref.get().*f)(std ::forward<ArgsT>(args)...))
    {
        return (ref.get().*f)(std ::forward<ArgsT>(args)...);
    }

    template <typename BaseT, typename FunctionT, typename PointerT, typename... ArgsT,
              typename std::enable_if<
                      !std::is_base_of<BaseT, typename std::decay<PointerT>::type>::value &&
                              !is_reference_wrapper<typename std::decay<PointerT>::type>::value,
                      int>::type = 0>
    constexpr auto invoke_member_function_impl(
            FunctionT BaseT::*f, PointerT&& ptr,
            ArgsT&&... args) noexcept(noexcept(((*std ::forward<PointerT>(ptr)).*
                                                f)(std ::forward<ArgsT>(args)...)))
            -> decltype(((*std ::forward<PointerT>(ptr)).*f)(std ::forward<ArgsT>(args)...))
    {
        return ((*std ::forward<PointerT>(ptr)).*f)(std ::forward<ArgsT>(args)...);
    }
} // namespace detail

template <typename FunctionT, typename... ArgsT,
          typename std::enable_if<
                  !std::is_member_pointer<typename std::decay<FunctionT>::type>::value, int>::type =
                  0>
constexpr auto invoke(FunctionT&& f, ArgsT&&... args) noexcept(
        noexcept(std ::forward<FunctionT>(f)(std ::forward<ArgsT>(args)...)))
        -> decltype(std ::forward<FunctionT>(f)(std ::forward<ArgsT>(args)...))
{
    return std ::forward<FunctionT>(f)(std ::forward<ArgsT>(args)...);
}

template <typename FunctionT, typename TypeT,
          typename std::enable_if<
                  std::is_member_object_pointer<typename std::decay<FunctionT>::type>::value,
                  int>::type = 0>
constexpr auto invoke(FunctionT&& f, TypeT&& t) noexcept(noexcept(
        detail::invoke_member_object_impl(std ::forward<FunctionT>(f), std ::forward<TypeT>(t))))
        -> decltype(detail ::invoke_member_object_impl(std ::forward<FunctionT>(f),
                                                       std ::forward<TypeT>(t)))
{
    return detail::invoke_member_object_impl(std ::forward<FunctionT>(f), std ::forward<TypeT>(t));
}

template <typename FunctionT, typename... ArgsT,
          typename std::enable_if<
                  std::is_member_function_pointer<typename std::decay<FunctionT>::type>::value,
                  int>::type = 0>
constexpr auto invoke(FunctionT&& f, ArgsT&&... args) noexcept(
        noexcept(detail ::invoke_member_function_impl(std ::forward<FunctionT>(f),
                                                      std ::forward<ArgsT>(args)...)))
        -> decltype(detail ::invoke_member_function_impl(std ::forward<FunctionT>(f),
                                                         std ::forward<ArgsT>(args)...))
{
    return detail ::invoke_member_function_impl(std ::forward<FunctionT>(f),
                                                std ::forward<ArgsT>(args)...);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_INVOKE_HPP
