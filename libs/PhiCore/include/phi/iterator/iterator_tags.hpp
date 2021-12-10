#ifndef INCG_PHI_CORE_ITERATOR_ITERATOR_TAGS_HPP
#define INCG_PHI_CORE_ITERATOR_ITERATOR_TAGS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

struct input_iterator_tag
{};

struct output_iterator_tag
{};

struct forward_iterator_tag : public input_iterator_tag
{};

struct bidirectional_iterator_tag : public forward_iterator_tag
{};

struct random_access_iterator_tag : public bidirectional_iterator_tag
{};

struct contiguous_iterator_tag : public random_access_iterator_tag
{};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ITERATOR_ITERATOR_TAGS_HPP
