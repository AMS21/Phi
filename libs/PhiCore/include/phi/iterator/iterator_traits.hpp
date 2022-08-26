#ifndef INCG_PHI_CORE_ITERATOR_ITERATOR_TRAITS_HPP
#define INCG_PHI_CORE_ITERATOR_ITERATOR_TRAITS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/core/types.hpp"
#include "phi/iterator/iterator_tags.hpp"
#include "phi/type_traits/is_convertible.hpp"
#include "phi/type_traits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename IteratorT>
struct iterator_traits;

/// \cond detail
namespace detail
{
    template <typename TypeT>
    struct has_iterator_category
    {
        // clang-format off
    private:
        struct two { char lx; char lxx; };
        template <typename UpT> static two test(...);
        template <typename UpT> static char test(typename UpT::iterator_category* = 0);
    public:
        static const bool value = sizeof(test<TypeT>(nullptr)) == 1;
        // clang-format on
    };

    template <typename IteratorT, bool>
    struct iterator_traits_impl
    {};

    template <typename IteratorT>
    struct iterator_traits_impl<IteratorT, true>
    {
        using difference_type   = typename IteratorT::difference_type;
        using value_type        = typename IteratorT::value_type;
        using pointer           = typename IteratorT::pointer;
        using reference         = typename IteratorT::reference;
        using iterator_category = typename IteratorT::iterator_category;
    };

    template <typename IteratorT, bool>
    struct iterator_traits_impl2
    {};

    template <typename IteratorT>
    struct iterator_traits_impl2<IteratorT, true>
        : public iterator_traits_impl<IteratorT,
                                      (is_convertible<typename IteratorT::iterator_category,
                                                      input_iterator_tag>::value ||
                                       is_convertible<typename IteratorT::iterator_category,
                                                      output_iterator_tag>::value)>
    {};

    template <typename TypeT, typename OtherT,
              bool = has_iterator_category<iterator_traits<TypeT>>::value>
    struct has_iterator_category_convertible_to
        : public integral_constant<
                  bool,
                  is_convertible<typename iterator_traits<TypeT>::iterator_category, OtherT>::value>
    {};

    template <typename TypeT, typename OtherT>
    struct has_iterator_category_convertible_to<TypeT, OtherT, false> : public false_type
    {};

    template <typename TypeT>
    struct is_input_iterator
        : public has_iterator_category_convertible_to<TypeT, input_iterator_tag>
    {};

    template <typename TypeT>
    struct is_forward_iterator
        : public has_iterator_category_convertible_to<TypeT, forward_iterator_tag>
    {};

    template <typename TypeT>
    struct is_bidirectional_iterator
        : public has_iterator_category_convertible_to<TypeT, bidirectional_iterator_tag>
    {};

    template <typename TypeT>
    struct is_random_access_iterator
        : public has_iterator_category_convertible_to<TypeT, random_access_iterator_tag>
    {};

    template <typename TypeT>
    struct is_exactly_input_iterator
        : public integral_constant<
                  bool,
                  has_iterator_category_convertible_to<TypeT, input_iterator_tag>::value &&
                          !has_iterator_category_convertible_to<TypeT, forward_iterator_tag>::value>
    {};
} // namespace detail
/// \endcond

// iterator_traits<Iterator> will only have the nested types if
// Iterator::iterator_category
//    exists.  Else iterator_traits<Iterator> will be an empty class.  This is a
//    conforming extension which allows some programs to compile and behave as
//    the client expects instead of failing at compile time.

template <typename IteratorT>
struct iterator_traits
    : public detail::iterator_traits_impl2<IteratorT,
                                           detail::has_iterator_category<IteratorT>::value>
{};

template <typename TypeT>
struct iterator_traits<TypeT*>
{
    using difference_type   = ptrdiff;
    using value_type        = typename remove_cv<TypeT>::type;
    using pointer           = TypeT*;
    using reference         = TypeT&;
    using iterator_category = random_access_iterator_tag;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_ITERATOR_TRAITS_HPP
