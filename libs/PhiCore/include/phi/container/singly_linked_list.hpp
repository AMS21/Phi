#ifndef INCG_PHI_CORE_CONTAINER_SINGLY_LINKED_LIST_HPP
#define INCG_PHI_CORE_CONTAINER_SINGLY_LINKED_LIST_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/types.hpp"
#include "phi/iterator/iterator_tags.hpp"
#include "phi/type_traits/is_nothrow_constructible.hpp"
#include "phi/type_traits/is_nothrow_copy_constructible.hpp"
#include "phi/type_traits/is_nothrow_destructible.hpp"
#include "phi/type_traits/is_nothrow_move_assignable.hpp"
#include "phi/type_traits/is_nothrow_move_constructible.hpp"

PHI_EXTERNAL_HEADERS_BEGIN()
#include <initializer_list>
#include <new>
PHI_EXTERNAL_HEADERS_END()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class singly_linked_list;

template <typename ListTypeT>
class singly_linked_list_const_iterator;

template <typename TypeT>
class singly_linked_list_node
{
public:
    using this_type       = singly_linked_list_node<TypeT>;
    using value_type      = TypeT;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;

    explicit singly_linked_list_node(const TypeT& value) noexcept(
            is_nothrow_copy_constructible<TypeT>::value)
        : m_Value{value}
        , m_Next{nullptr}
    {}

    explicit singly_linked_list_node(TypeT&& value) noexcept(
            is_nothrow_move_constructible<TypeT>::value)
        : m_Value{value}
        , m_Next{nullptr}
    {}

    PHI_NODISCARD const_reference value() const noexcept
    {
        return m_Value;
    }

    PHI_NODISCARD boolean is_last() const noexcept
    {
        return m_Next == nullptr;
    }

    PHI_NODISCARD boolean has_next() const noexcept
    {
        return m_Next != nullptr;
    }

    PHI_NODISCARD this_type* next() const noexcept
    {
        return m_Next;
    }

private:
    friend singly_linked_list<TypeT>;

    value_type m_Value;
    this_type* m_Next;
};

template <typename ListTypeT>
class singly_linked_list_iterator
{
public:
    using this_type         = singly_linked_list_iterator<ListTypeT>;
    using iterator_category = forward_iterator_tag;
    using list_type         = ListTypeT;
    using node_type         = typename list_type::node_type;
    using value_type        = typename list_type::value_type;
    using size_type         = typename list_type::size_type;
    using difference_type   = typename list_type::difference_type;
    using reference         = value_type&;
    using const_reference   = const value_type&;
    using pointer           = value_type*;
    using const_pointer     = const value_type*;

    singly_linked_list_iterator() noexcept
        : m_Node{nullptr}
        , m_Next{nullptr}
        , m_WasRemoved{false}
    {}

    PHI_NODISCARD boolean operator==(const singly_linked_list_iterator& other) const noexcept
    {
        return m_Node == other.m_Node;
    }

    PHI_NODISCARD boolean
    operator==(const singly_linked_list_const_iterator<ListTypeT>& other) const noexcept
    {
        return m_Node == other.m_Node;
    }

    PHI_NODISCARD boolean operator!=(const singly_linked_list_iterator& other) const noexcept
    {
        return m_Node != other.m_Node;
    }

    PHI_NODISCARD boolean
    operator!=(const singly_linked_list_const_iterator<ListTypeT>& other) const noexcept
    {
        return m_Node != other.m_Node;
    }

    singly_linked_list_iterator& operator++() noexcept
    {
        if (m_WasRemoved)
        {
            m_WasRemoved = false;
        }

        m_Node = m_Next;
        if (m_Next != nullptr)
        {
            m_Next = m_Next->next();
        }

        return *this;
    }

    PHI_NODISCARD reference operator*() noexcept
    {
        PHI_ASSERT(!m_WasRemoved, "");
        PHI_ASSERT(m_Node != nullptr, "");

        return m_Node->value();
    }

    PHI_NODISCARD const_reference operator*() const noexcept
    {
        PHI_ASSERT(!m_WasRemoved, "");
        PHI_ASSERT(m_Node != nullptr, "");

        return m_Node->value();
    }

    PHI_NODISCARD pointer operator->() noexcept
    {
        PHI_ASSERT(!m_WasRemoved, "");
        PHI_ASSERT(m_Node != nullptr, "");

        return m_Node->value();
    }

    PHI_NODISCARD const_pointer operator->() const noexcept
    {
        PHI_ASSERT(!m_WasRemoved, "");
        PHI_ASSERT(m_Node != nullptr, "");

        return m_Node->value();
    }

    PHI_NODISCARD boolean is_valid() const noexcept
    {
        return m_Node != nullptr;
    }

    PHI_NODISCARD boolean has_next() const noexcept
    {
        return m_Next != nullptr;
    }

    void remove(ListTypeT& list)
    {
        m_WasRemoved = true;

        list.remove(*this);
    }

private:
    explicit singly_linked_list_iterator(node_type* node) noexcept
        : m_Node(node)
        , m_Next(node ? node->next : nullptr)
        , m_WasRemoved{false}
    {}

    friend ListTypeT;
    friend singly_linked_list_const_iterator<ListTypeT>;

    node_type* m_Node;
    node_type* m_Next;

    boolean m_WasRemoved;
};

template <typename ListTypeT>
class singly_linked_list_const_iterator
{
public:
    using this_type         = singly_linked_list_const_iterator<ListTypeT>;
    using iterator_category = forward_iterator_tag;
    using list_type         = ListTypeT;
    using node_type         = typename list_type::node_type;
    using value_type        = typename list_type::value_type;
    using size_type         = typename list_type::size_type;
    using difference_type   = typename list_type::difference_type;
    using reference         = value_type&;
    using const_reference   = const value_type&;
    using pointer           = value_type*;
    using const_pointer     = const value_type*;

    singly_linked_list_const_iterator() noexcept
        : m_Node{nullptr}
        , m_Next{nullptr}
    {}

    PHI_NODISCARD boolean operator==(const singly_linked_list_const_iterator& other) const noexcept
    {
        return m_Node == other.m_Node;
    }

    PHI_NODISCARD boolean
    operator==(const singly_linked_list_iterator<list_type>& other) const noexcept
    {
        return m_Node == other.m_Node;
    }

    PHI_NODISCARD boolean operator!=(const singly_linked_list_const_iterator& other) const noexcept
    {
        return m_Node != other.m_Node;
    }

    PHI_NODISCARD boolean
    operator!=(const singly_linked_list_iterator<list_type>& other) const noexcept
    {
        return m_Node != other.m_Node;
    }

    singly_linked_list_const_iterator& operator++() noexcept
    {
        m_Node = m_Next;
        if (m_Next != nullptr)
        {
            m_Next = m_Next->next();
        }

        return *this;
    }

    PHI_NODISCARD const_reference operator*() const noexcept
    {
        PHI_ASSERT(m_Node != nullptr, "");

        return m_Node->value();
    }

    PHI_NODISCARD const_pointer operator->() const noexcept
    {
        PHI_ASSERT(m_Node != nullptr, "");

        return m_Node->value();
    }

    PHI_NODISCARD boolean is_valid() const noexcept
    {
        return m_Node != nullptr;
    }

    PHI_NODISCARD boolean has_next() const noexcept
    {
        return m_Next != nullptr;
    }

private:
    explicit singly_linked_list_const_iterator(node_type* node) noexcept
        : m_Node(node)
        , m_Next(node ? node->next : nullptr)
    {}

    friend ListTypeT;
    friend singly_linked_list_iterator<ListTypeT>;

    node_type* m_Node;
    node_type* m_Next;
};

template <typename TypeT>
class singly_linked_list
{
public:
    // types
    using this_type       = singly_linked_list<TypeT>;
    using value_type      = TypeT;
    using node_type       = singly_linked_list_node<value_type>;
    using size_type       = usize;
    using difference_type = ptrdiff;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = singly_linked_list_iterator<this_type>;
    using const_iterator  = singly_linked_list_const_iterator<this_type>;

    singly_linked_list() noexcept
        : m_Head{nullptr}
        , m_Tail{nullptr}
    {}

    explicit singly_linked_list(size_type count);

    singly_linked_list(size_type count, const TypeT& value);

    template <typename InputIteratorT>
    singly_linked_list(InputIteratorT first, InputIteratorT last);

    singly_linked_list(const singly_linked_list& other);

    singly_linked_list(singly_linked_list&& other) noexcept
        : m_Head(other.m_Head)
        , m_Tail(other.m_Tail)
    {
        other.m_Head = nullptr;
        other.m_Tail = nullptr;
    }

    singly_linked_list(std::initializer_list<TypeT> init);

    ~singly_linked_list() noexcept
    {
        clear();
    }

    singly_linked_list& operator=(const singly_linked_list& other); // TODO: Noexcept

    singly_linked_list& operator=(singly_linked_list&& other) noexcept
    {
        m_Head = other.m_Head;
        m_Tail = other.m_Tail;

        other.m_Head = nullptr;
        other.m_Tail = nullptr;

        return *this;
    }

    // TODO: Operator= with initializer list

    void assign(size_type count, const TypeT& value); // TODO: Noexcept

    template <typename InputIteratorT>
    void assign(InputIteratorT first, InputIteratorT last); // TODO: Noexcept

    PHI_NODISCARD iterator before_begin() noexcept
    {
        return m_Head - sizeof(singly_linked_list_node<TypeT>);
    }

    PHI_NODISCARD const_iterator before_begin() const noexcept
    {
        return m_Head - sizeof(singly_linked_list_node<TypeT>);
    }

    PHI_NODISCARD const_iterator cbefore_begin() const noexcept
    {
        return before_begin();
    }

    PHI_NODISCARD iterator begin() noexcept
    {
        return m_Head;
    }

    PHI_NODISCARD const_iterator begin() const noexcept
    {
        return m_Head;
    }

    PHI_NODISCARD const_iterator cbegin() const noexcept
    {
        return m_Head;
    }

    PHI_NODISCARD iterator end() noexcept
    {
        return {};
    }

    PHI_NODISCARD const_iterator end() const noexcept
    {
        return {};
    }

    PHI_NODISCARD const_iterator cend() const noexcept
    {
        return {};
    }

    PHI_NODISCARD boolean is_empty() const noexcept
    {
        return m_Head == nullptr;
    }

    PHI_NODISCARD size_type max_size() const noexcept
    {
        return size_type::limits_type::max();
    }

    PHI_NODISCARD reference front() noexcept
    {
        PHI_ASSERT(!is_empty(), "");

        return m_Head->m_Value;
    }

    PHI_NODISCARD const_reference front() const noexcept
    {
        PHI_ASSERT(!is_empty(), "");

        return m_Head->m_Value;
    }

    PHI_NODISCARD reference back() noexcept
    {
        PHI_ASSERT(!is_empty(), "");

        return m_Tail->m_Value;
    }

    PHI_NODISCARD const_reference back() const noexcept
    {
        PHI_ASSERT(!is_empty(), "");

        return m_Tail->m_Value;
    }

    PHI_NODISCARD size_type length() const noexcept
    {
        size_type size{0u};
        for (node_type* node = m_Head; node != nullptr; node = node->next())
        {
            ++size;
        }

        return size;
    }

    template <typename... ArgsT>
    boolean try_emplace_front(ArgsT&&... args) noexcept(
            is_nothrow_constructible<TypeT, ArgsT...>::value)
    {
        node_type* node = new (std::nothrow) node_type{forward<ArgsT>(args)...};
        if (node == nullptr)
        {
            return false;
        }

        assign_front(node);
        return true;
    }

    template <typename... ArgsT>
    boolean try_emplace_back(ArgsT&&... args) noexcept(
            is_nothrow_constructible<TypeT, ArgsT...>::value)
    {
        node_type* node = new (std::nothrow) node_type{forward<ArgsT>(args)...};
        if (node == nullptr)
        {
            return false;
        }

        assign_back(node);
        return true;
    }

    boolean try_push_front(const TypeT& value) noexcept(is_nothrow_copy_constructible<TypeT>::value)
    {
        node_type* node = new (std::nothrow) node_type(value);
        if (node == nullptr)
        {
            return false;
        }

        assign_front(node);
        return true;
    }

    boolean try_push_front(TypeT&& value) noexcept(is_nothrow_move_constructible<TypeT>::value)
    {
        node_type* node = new (std::nothrow) node_type(forward<TypeT>(value));
        if (node == nullptr)
        {
            return false;
        }

        assign_front(node);
        return true;
    }

    boolean try_push_back(const TypeT& value) noexcept(is_nothrow_copy_constructible<TypeT>::value)
    {
        node_type* node = new (std::nothrow) node_type(value);
        if (node == nullptr)
        {
            return false;
        }

        assign_back(node);
        return true;
    }

    boolean try_push_back(TypeT&& value) noexcept(is_nothrow_move_constructible<TypeT>::value)
    {
        node_type* node = new (std::nothrow) node_type(forward<TypeT>(value));
        if (node == nullptr)
        {
            return false;
        }

        assign_back(node);
        return true;
    }

    template <typename... ArgsT>
    reference emplace_front(ArgsT&&... args) noexcept(
            is_nothrow_constructible<TypeT, ArgsT...>::value)
    {
        node_type* node = new (std::nothrow) node_type{forward<ArgsT>(args)...};
        PHI_ASSERT(node != nullptr, "");

        assign_front(node);
    }

    template <typename... ArgsT>
    reference emplace_back(ArgsT&&... args) noexcept(
            is_nothrow_constructible<TypeT, ArgsT...>::value)
    {
        node_type* node = new (std::nothrow) node_type{forward<ArgsT>(args)...};
        PHI_ASSERT(node != nullptr, "");

        assign_back(node);
    }

    void push_front(const TypeT& value) noexcept(is_nothrow_copy_constructible<TypeT>::value)
    {
        node_type* node = new (std::nothrow) node_type(value);
        PHI_ASSERT(node != nullptr, "");

        assign_front(node);
    }

    void push_front(TypeT&& value) noexcept(is_nothrow_move_constructible<TypeT>::value)
    {
        node_type* node = new (std::nothrow) node_type(forward<TypeT>(value));
        PHI_ASSERT(node != nullptr, "");

        assign_front(node);
    }

    void push_back(const TypeT& value) noexcept(is_nothrow_copy_constructible<TypeT>::value)
    {
        node_type* node = new (std::nothrow) node_type(value);
        PHI_ASSERT(node != nullptr, "");

        assign_back(node);
    }

    void push_back(TypeT&& value) noexcept(is_nothrow_move_constructible<TypeT>::value)
    {
        node_type* node = new (std::nothrow) node_type(forward<TypeT>(value));
        PHI_ASSERT(node != nullptr, "");

        assign_back(node);
    }

    void pop_front() noexcept(is_nothrow_destructible<TypeT>::value)
    {
        PHI_ASSERT(m_Head != nullptr, "");

        node_type* prev_head = m_Head;
        if (m_Tail == m_Head)
        {
            m_Tail = nullptr;
        }

        m_Head = m_Head->next();
        delete prev_head;
    }

    PHI_NODISCARD value_type take_front() noexcept(
            is_nothrow_destructible<TypeT>::value&& is_nothrow_move_assignable<TypeT>::value)
    {
        PHI_ASSERT(m_Head != nullptr, "");

        node_type* prev_head = m_Head;
        TypeT      value     = move(front());

        if (m_Tail == m_Head)
        {
            m_Tail = nullptr;
        }

        m_Head = m_Head->next();
        delete prev_head;

        return value;
    }

    template <typename... ArgsT>
    iterator emplace_after(const_iterator position, ArgsT&&... args);
    iterator insert_after(const_iterator position, const TypeT& value);
    iterator insert_after(const_iterator position, TypeT&& value);

    iterator insert_after(const_iterator position, size_type count, const TypeT& value);
    template <typename InputIteratorT>
    iterator insert_after(const_iterator position, InputIteratorT first, InputIteratorT last);
    //iterator insert_after(const_iterator position, initializer_list<TypeT> il);

    template <typename... ArgsT>
    iterator emplace_before(const_iterator position, ArgsT&&... args);
    iterator insert_before(const_iterator position, const TypeT& value);
    iterator insert_before(const_iterator position, TypeT&& value);

    iterator insert_before(const_iterator position, size_type count, const TypeT& value);
    template <typename InputIteratorT>
    iterator insert_before(const_iterator position, InputIteratorT first, InputIteratorT last);
    //iterator insert_before(const_iterator position, initializer_list<TypeT> il);

    iterator erase_after(const_iterator position);
    iterator erase_after(const_iterator position, const_iterator last);

    iterator erase_before(const_iterator position);
    iterator erase_before(const_iterator position, const_iterator last);

    void swap(singly_linked_list&); // TODO: NOEXCEPT

    void resize(size_type new_size);
    void resize(size_type new_size, const value_type& value);

    void clear() noexcept
    {
        for (node_type* node = m_Head; node != nullptr;)
        {
            node_type* next = node->next();
            delete node;
            node = next;
        }

        m_Head = nullptr;
        m_Tail = nullptr;
    }

    void splice_after(const_iterator position, singly_linked_list& other);
    void splice_after(const_iterator position, singly_linked_list&& other);
    void splice_after(const_iterator position, singly_linked_list& other, const_iterator iterator);
    void splice_after(const_iterator position, singly_linked_list&& other, const_iterator iterator);
    void splice_after(const_iterator position, singly_linked_list& other, const_iterator first,
                      const_iterator last);
    void splice_after(const_iterator position, singly_linked_list&& otheer, const_iterator first,
                      const_iterator last);

    size_type remove(const TypeT& value);
    template <typename PredicateT>
    size_type remove_if(PredicateT pred);

    size_type unique();
    template <typename BinaryPredicateT>
    size_type unique(BinaryPredicateT binary_pred);

    void merge(singly_linked_list& other);
    void merge(singly_linked_list&& other);
    template <typename CompareT>
    void merge(singly_linked_list& other, CompareT comp);
    template <typename CompareT>
    void merge(singly_linked_list&& other, CompareT comp);

    void sort();
    template <typename CompareT>
    void sort(CompareT comp);

    void reverse() noexcept;

    PHI_NODISCARD boolean contains(const TypeT& value) const;

    iterator                     find(const TypeT& value);
    PHI_NODISCARD const_iterator find(const TypeT& value) const;

    template <typename UnaryPredicateT>
    iterator find_if(UnaryPredicateT predicate);

    template <typename UnaryPredicateT>
    const_iterator find_if(UnaryPredicateT predicate) const;

    PHI_NODISCARD TypeT max() const noexcept;
    PHI_NODISCARD TypeT min() const noexcept;

    PHI_NODISCARD iterator       max_index() noexcept;
    PHI_NODISCARD const_iterator max_index() const noexcept;

    PHI_NODISCARD iterator       min_index() noexcept;
    PHI_NODISCARD const_iterator min_index() const noexcept;

private:
    void assign_back(node_type* node) noexcept
    {
        if (m_Head == nullptr)
        {
            m_Head = node;
            m_Tail = node;
            return;
        }

        m_Tail->m_Next = node;
        m_Tail         = node;
    }

    void assign_front(node_type* node) noexcept
    {
        if (m_Head == nullptr)
        {
            m_Head = node;
            m_Tail = node;
            return;
        }

        node->m_Next = m_Head;
        m_Head       = node;
    }

    node_type* m_Head;
    node_type* m_Tail;
};

#if PHI_HAS_FEATURE_DEDUCTION_GUIDES()
template <typename InputIteratorT>
singly_linked_list(InputIteratorT, InputIteratorT)
        -> singly_linked_list<typename std::iterator_traits<InputIteratorT>::value_type>;
#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CONTAINER_SINGLY_LINKED_LIST_HPP
