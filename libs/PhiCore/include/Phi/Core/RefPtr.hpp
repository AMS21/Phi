#ifndef INCG_PHI_CORE_REFPTR_HPP
#define INCG_PHI_CORE_REFPTR_HPP

#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Types.hpp"
#include "Phi/PhiConfig.hpp"
#include <atomic>
#include <cstddef>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    class ControlBlock
    {
    public:
        Boolean should_delete() const noexcept
        {
            return m_NumRefPtrs.load() == 0u;
        }

        phi::u32 get_ref_use_count() const noexcept
        {
            return m_NumRefPtrs.load();
        }

        void increment_ref_count() noexcept
        {
            ++m_NumRefPtrs;
        }

        void decrement_ref_count() noexcept
        {
            --m_NumRefPtrs;
        }

    private:
        std::atomic<std::uint32_t> m_NumRefPtrs{1u};
    };
} // namespace detail

// forward declaration
template <typename TypeT>
class NotNullRefPtr;

// Reference counted smart pointer
template <typename TypeT>
class RefPtr
{
public:
    using this_type       = RefPtr<TypeT>;
    using not_null_type   = NotNullRefPtr<TypeT>;
    using value_type      = TypeT;
    using reference       = TypeT&;
    using const_reference = const TypeT&;
    using pointer         = TypeT*;
    using const_pointer   = const TypeT*;

    constexpr RefPtr() noexcept
        : m_Ptr(nullptr)
        , m_ControlBlock(nullptr)
    {}

    constexpr RefPtr(std::nullptr_t) noexcept
        : m_Ptr(nullptr)
        , m_ControlBlock(nullptr)
    {}

    constexpr RefPtr(TypeT* pointer)
        : m_Ptr(pointer)
        , m_ControlBlock(allocate_control_block())
    {}

    constexpr RefPtr(const RefPtr& other) noexcept
        : m_Ptr(other.m_Ptr)
        , m_ControlBlock(other.m_ControlBlock)
    {
        if (m_ControlBlock)
        {
            m_ControlBlock->increment_ref_count();
        }
    }

    constexpr RefPtr(RefPtr&& other) noexcept
        : m_Ptr(std::exchange(other.m_Ptr, nullptr))
        , m_ControlBlock(std::exchange(other.m_ControlBlock, nullptr))
    {}

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr RefPtr(const RefPtr<OtherT>& other) noexcept
        : m_Ptr(other.m_Ptr)
        , m_ControlBlock(other.m_ControlBlock)
    {
        if (m_ControlBlock)
        {
            m_ControlBlock->increment_ref_count();
        }
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr RefPtr(RefPtr<OtherT>&& other) noexcept
        : m_Ptr(std::exchange(other.m_Ptr, nullptr))
        , m_ControlBlock(std::exchange(other.m_ControlBlock, nullptr))
    {}

    constexpr RefPtr(const NotNullRefPtr<TypeT>& other) noexcept
        : m_Ptr(other.m_Ptr)
        , m_ControlBlock(other.m_ControlBlock)
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "NotNullRefPtr was null");
        PHI_DBG_ASSERT(m_ControlBlock != nullptr, "ControlBlock was null");

        if (m_ControlBlock)
        {
            m_ControlBlock->increment_ref_count();
        }
    }

    constexpr RefPtr(NotNullRefPtr<TypeT>&& other) noexcept
        : m_Ptr(std::exchange(other.m_Ptr, nullptr))
        , m_ControlBlock(std::exchange(other.m_ControlBlock, nullptr))
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "NotNullRefPtr was null");
        PHI_DBG_ASSERT(m_ControlBlock != nullptr, "ControlBlock was null");
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr RefPtr(const NotNullRefPtr<OtherT>& other) noexcept
        : m_Ptr(other.m_Ptr)
        , m_ControlBlock(other.m_ControlBlock)
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "NotNullRefPtr was null");
        PHI_DBG_ASSERT(m_ControlBlock != nullptr, "ControlBlock was null");

        if (m_ControlBlock)
        {
            m_ControlBlock->increment_ref_count();
        }
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr RefPtr(NotNullRefPtr<OtherT>&& other) noexcept
        : m_Ptr(std::exchange(other.m_Ptr, nullptr))
        , m_ControlBlock(std::exchange(other.m_ControlBlock, nullptr))
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "NotNullRefPtr was null");
        PHI_DBG_ASSERT(m_ControlBlock != nullptr, "ControlBlock was null");
    }

    ~RefPtr() noexcept
    {
        clear();
    }

    constexpr RefPtr& operator=(std::nullptr_t) noexcept
    {
        clear();

        return *this;
    }

    constexpr RefPtr& operator=(TypeT* ptr)
    {
        if (m_ControlBlock)
        {
            m_ControlBlock->decrement_ref_count();
            if (m_ControlBlock->should_delete())
            {
                delete m_Ptr;
                delete m_ControlBlock;
            }
        }

        m_Ptr = ptr;
        allocate_control_block();

        return *this;
    }

    constexpr RefPtr& operator=(const RefPtr& other) noexcept
    {
        RefPtr<TypeT>(other).swap(*this);

        return *this;
    }

    constexpr RefPtr& operator=(RefPtr&& other) noexcept
    {
        RefPtr<TypeT>(std::move(other)).swap(*this);

        return *this;
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr RefPtr& operator=(const RefPtr<OtherT>& other) noexcept
    {
        RefPtr<TypeT>(other).swap(*this);

        return *this;
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr RefPtr& operator=(RefPtr<OtherT>&& other) noexcept
    {
        RefPtr<TypeT>(std::move(other)).swap(*this);

        return *this;
    }

    constexpr RefPtr& operator=(const NotNullRefPtr<TypeT>& other) noexcept
    {
        RefPtr<TypeT>(other).swap(*this);

        return *this;
    }

    constexpr RefPtr& operator=(NotNullRefPtr<TypeT>&& other) noexcept
    {
        RefPtr<TypeT>(std::move(other)).swap(*this);

        return *this;
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr RefPtr& operator=(const NotNullRefPtr<OtherT>& other) noexcept
    {
        RefPtr<TypeT>(other).swap(*this);

        return *this;
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr RefPtr& operator=(NotNullRefPtr<OtherT>&& other) noexcept
    {
        RefPtr<TypeT>(std::move(other)).swap(*this);

        return *this;
    }

    void clear() noexcept
    {
        if (m_ControlBlock)
        {
            m_ControlBlock->decrement_ref_count();
            if (m_ControlBlock->should_delete())
            {
                delete m_Ptr;
                delete m_ControlBlock;

                m_Ptr          = nullptr;
                m_ControlBlock = nullptr;
            }
        }
    }

    void reset(TypeT* ptr) noexcept
    {
        if (ptr == m_Ptr)
        {
            return;
        }

        if (m_ControlBlock)
        {
            m_ControlBlock->decrement_ref_count();
            if (m_ControlBlock->should_delete())
            {
                delete m_Ptr;
                delete m_ControlBlock;
            }
        }

        m_Ptr = ptr;
        if (ptr)
        {
            allocate_control_block();
        }
        else
        {
            m_ControlBlock = nullptr;
        }
    }

    constexpr void swap(RefPtr& other) noexcept
    {
        std::swap(m_Ptr, other.m_Ptr);
        std::swap(m_ControlBlock, other.m_ControlBlock);
    }

    [[nodiscard]] constexpr TypeT* get() noexcept
    {
        return m_Ptr;
    }

    [[nodiscard]] constexpr const TypeT* get() const noexcept
    {
        return m_Ptr;
    }

    [[nodiscard]] constexpr usize use_count() const noexcept
    {
        if (m_ControlBlock)
        {
            return m_ControlBlock->get_ref_use_count();
        }
        else
        {
            return 0u;
        }
    }

    constexpr explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }

    constexpr explicit operator Boolean() const noexcept
    {
        return get() != nullptr;
    }

    constexpr explicit operator const TypeT*() const noexcept
    {
        return get();
    }

    constexpr explicit operator TypeT*() noexcept
    {
        return get();
    }

    TypeT* operator->()
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");

        return get();
    }

    const TypeT* operator->() const
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");

        return get();
    }

    TypeT& operator*()
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");

        return *get();
    }

    const TypeT& operator*() const
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");

        return *get();
    }

private:
    detail::ControlBlock* allocate_control_block()
    {
        m_ControlBlock = new (std::nothrow) detail::ControlBlock();

        if (m_ControlBlock == nullptr)
        {
            delete m_Ptr;
            throw std::bad_alloc();
        }

        return m_ControlBlock;
    }

    TypeT*                m_Ptr;
    detail::ControlBlock* m_ControlBlock;
};

template <typename LhsT, typename RhsT>
constexpr Boolean operator==(const RefPtr<LhsT>& lhs, const RefPtr<RhsT>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT>
constexpr Boolean operator==(const RefPtr<LhsT>& lhs, std::nullptr_t) noexcept
{
    return lhs.get() == nullptr;
}

template <typename RhsT>
constexpr Boolean operator==(std::nullptr_t, const RefPtr<RhsT>& rhs) noexcept
{
    return rhs.get() == nullptr;
}

template <typename LhsT, typename RhsT>
constexpr Boolean operator!=(const RefPtr<LhsT>& lhs, const RefPtr<RhsT>& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
constexpr Boolean operator!=(const RefPtr<LhsT>& lhs, std::nullptr_t) noexcept
{
    return lhs.get() != nullptr;
}

template <typename RhsT>
constexpr Boolean operator!=(std::nullptr_t, const RefPtr<RhsT>& rhs) noexcept
{
    return rhs.get() != nullptr;
}

template <typename LhsT, typename RhsT>
constexpr void swap(RefPtr<LhsT>& lhs, RefPtr<RhsT>& rhs)
{
    lhs.swap(rhs);
}

template <typename TypeT>
class NotNullRefPtr
{
public:
    using this_type       = NotNullRefPtr<TypeT>;
    using value_type      = TypeT;
    using reference       = TypeT&;
    using const_reference = const TypeT&;
    using pointer         = TypeT*;
    using const_pointer   = const TypeT*;

    NotNullRefPtr() = delete;

    NotNullRefPtr(std::nullptr_t) = delete;

    constexpr NotNullRefPtr(TypeT* ptr)
        : m_Ptr(ptr)
        , m_ControlBlock(allocate_control_block())
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to NotNullRefPtr");
    }

    constexpr NotNullRefPtr(const NotNullRefPtr& other) noexcept
        : m_Ptr(other.m_Ptr)
        , m_ControlBlock(other.m_ControlBlock)
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign nullptr to NotNullRefPtr");

        m_ControlBlock->increment_ref_count();
    }

    constexpr NotNullRefPtr(NotNullRefPtr&& other) noexcept
        : m_Ptr(std::exchange(other.m_Ptr, nullptr))
        , m_ControlBlock(std::exchange(other.m_ControlBlock, nullptr))
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign nullptr to NotNullRefPtr");
        PHI_DBG_ASSERT(m_ControlBlock != nullptr, "ControllBlock was null");
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr NotNullRefPtr(const NotNullRefPtr<OtherT>& other) noexcept
        : m_Ptr(other.m_Ptr)
        , m_ControlBlock(other.m_ControlBlock)
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign nullptr to NotNullRefPtr");
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr NotNullRefPtr(NotNullRefPtr<OtherT>&& other) noexcept
        : m_Ptr(std::exchange(other.m_Ptr, nullptr))
        , m_ControlBlock(std::exchange(other.m_ControlBlock, nullptr))
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign nullptr to NotNullRefPtr");
        PHI_DBG_ASSERT(m_ControlBlock != nullptr, "ControlBlock was null");
    }

    ~NotNullRefPtr() noexcept
    {
        clear();
    }

    NotNullRefPtr& operator=(std::nullptr_t) = delete;

    constexpr NotNullRefPtr& operator=(TypeT* ptr)
    {
        PHI_DBG_ASSERT(m_ControlBlock != nullptr, "ControlBlock was null!");

        m_ControlBlock->decrement_ref_count();
        if (m_ControlBlock->should_delete())
        {
            delete m_Ptr;
            delete m_ControlBlock;
        }

        m_Ptr = ptr;
        allocate_control_block();

        return *this;
    }

    constexpr NotNullRefPtr& operator=(const NotNullRefPtr& other) noexcept
    {
        NotNullRefPtr<TypeT>(other).swap(*this);

        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to NotNullRefPtr");

        return *this;
    }

    constexpr NotNullRefPtr& operator=(NotNullRefPtr&& other) noexcept
    {
        NotNullRefPtr<TypeT>(std::move(other)).swap(*this);

        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to NotNullRefPtr");

        return *this;
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr NotNullRefPtr& operator=(const NotNullRefPtr<OtherT>& other) noexcept
    {
        NotNullRefPtr<TypeT>(other).swap(*this);

        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to NotNullRefPtr");

        return *this;
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr NotNullRefPtr& operator=(NotNullRefPtr<OtherT>&& other) noexcept
    {
        NotNullRefPtr<TypeT>(std::move(other)).swap(*this);

        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to NotNullRefPtr");

        return *this;
    }

    void reset(std::nullptr_t) = delete;

    void reset(TypeT* ptr) noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign nullptr to NotNullRefPtr");

        if (ptr == m_Ptr)
        {
            return;
        }

        PHI_DBG_ASSERT(m_ControlBlock != nullptr, "ControlBlock was null");

        m_ControlBlock->decrement_ref_count();
        if (m_ControlBlock->should_delete())
        {
            delete m_Ptr;
            delete m_ControlBlock;
        }

        m_Ptr = ptr;
        allocate_control_block();
    }

    constexpr void swap(NotNullRefPtr& other) noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign nullptr to NotNullRefPtr");
        PHI_DBG_ASSERT(m_ControlBlock != nullptr, "ControlBlock was null");
        PHI_DBG_ASSERT(other.m_Ptr != nullptr, "Trying to assign nullptr to NotNullRefPtr");
        PHI_DBG_ASSERT(other.m_ControlBlock != nullptr, "ControlBlock was null");

        std::swap(m_Ptr, other.m_Ptr);
        std::swap(m_ControlBlock, other.m_ControlBlock);
    }

    [[nodiscard]] constexpr TypeT* get() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Using NotNullRefPtr after it was moved from");

        return m_Ptr;
    }

    [[nodiscard]] constexpr const TypeT* get() const noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Using NotNullRefPtr after it was moved from");

        return m_Ptr;
    }

    [[nodiscard]] constexpr usize use_count() const noexcept
    {
        PHI_DBG_ASSERT(m_ControlBlock != nullptr, "ControlBlock was null");

        return m_ControlBlock->get_ref_use_count();
    }

    operator bool() = delete;

    operator Boolean() = delete;

    constexpr explicit operator const TypeT*() const noexcept
    {
        return get();
    }

    constexpr explicit operator TypeT*() noexcept
    {
        return get();
    }

    TypeT* operator->()
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Using NotNullRefPtr after it was moved from");

        return get();
    }

    const TypeT* operator->() const
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Using NotNullRefPtr after it was moved from");

        return get();
    }

    TypeT& operator*()
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Using NotNullRefPtr after it was moved from");

        return *get();
    }

    const TypeT& operator*() const
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Using NotNullRefPtr after it was moved from");

        return *get();
    }

private:
    // Need to declare RefPtr as a friend to access the control block
    friend RefPtr<TypeT>;

    void clear() noexcept
    {
        if (m_ControlBlock)
        {
            m_ControlBlock->decrement_ref_count();
            if (m_ControlBlock->should_delete())
            {
                delete m_Ptr;
                delete m_ControlBlock;

                m_Ptr          = nullptr;
                m_ControlBlock = nullptr;
            }
        }
    }

    detail::ControlBlock* allocate_control_block()
    {
        m_ControlBlock = new (std::nothrow) detail::ControlBlock();

        if (m_ControlBlock == nullptr)
        {
            delete m_Ptr;
            throw std::bad_alloc();
        }

        return m_ControlBlock;
    }

    TypeT*                m_Ptr;
    detail::ControlBlock* m_ControlBlock;
};

template <typename LhsT, typename RhsT>
constexpr Boolean operator==(const NotNullRefPtr<LhsT>& lhs,
                             const NotNullRefPtr<RhsT>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT>
Boolean operator==(const NotNullRefPtr<LhsT>& lhs, std::nullptr_t) = delete;

template <typename RhsT>
Boolean operator==(std::nullptr_t, const NotNullRefPtr<RhsT>& rhs) = delete;

template <typename LhsT, typename RhsT>
constexpr Boolean operator!=(const NotNullRefPtr<LhsT>& lhs,
                             const NotNullRefPtr<RhsT>& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
Boolean operator!=(const NotNullRefPtr<LhsT>& lhs, std::nullptr_t) = delete;

template <typename RhsT>
Boolean operator!=(std::nullptr_t, const NotNullRefPtr<RhsT>& rhs) = delete;

template <typename LhsT, typename RhsT>
constexpr void swap(NotNullRefPtr<LhsT>& lhs, NotNullRefPtr<RhsT>& rhs)
{
    lhs.swap(rhs);
}

// make functions

template <typename TypeT, typename... ArgsT>
[[nodiscard]] std::enable_if_t<!std::is_array<TypeT>::value, RefPtr<TypeT>> make_ref(
        ArgsT&&... args)
{
    return RefPtr<TypeT>(new TypeT(std::forward<ArgsT>(args)...));
}

template <typename TypeT, typename... ArgsT>
[[nodiscard]] std::enable_if_t<!std::is_array<TypeT>::value, NotNullRefPtr<TypeT>>
make_not_null_ref(ArgsT&&... args)
{
    return NotNullRefPtr<TypeT>(new TypeT(std::forward<ArgsT>(args)...));
}

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    template <typename TypeT>
    struct hash<phi::RefPtr<TypeT>>
    {
        std::size_t operator()(phi::RefPtr<TypeT> pointer) const noexcept
        {
            return std::hash<TypeT*>()(pointer.get());
        }
    };

    template <typename TypeT>
    struct hash<phi::NotNullRefPtr<TypeT>>
    {
        std::size_t operator()(phi::NotNullRefPtr<TypeT> pointer) const noexcept
        {
            return std::hash<TypeT*>()(pointer.get());
        }
    };
} // namespace std

#endif // INCG_PHI_CORE_REFPTR_HPP
