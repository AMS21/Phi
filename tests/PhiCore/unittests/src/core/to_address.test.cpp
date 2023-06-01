#include <phi/test/test_macros.hpp>

#include <phi/core/assert.hpp>
#include <phi/core/to_address.hpp>
#include <memory>

struct Irrelevant;

struct P1
{
    using element_type = Irrelevant;

    constexpr explicit P1(int* ptr)
        : m_pointer(ptr)
    {}

    constexpr int* operator->() const
    {
        return m_pointer;
    }
    int* m_pointer;
};

struct P2
{
    using element_type = Irrelevant;

    constexpr explicit P2(int* ptr)
        : m_pointer(ptr)
    {}

    constexpr P1 operator->() const
    {
        return m_pointer;
    }

    P1 m_pointer;
};

struct P3
{
    constexpr explicit P3(int* ptr)
        : m_pointer(ptr)
    {}

    int* m_pointer;
};

template <>
struct phi::pointer_traits<P3>
{
    static constexpr int* to_address(const P3& pointer)
    {
        return pointer.m_pointer;
    }
};

struct P4
{
    constexpr explicit P4(int* pointer)
        : m_pointer(pointer)
    {}

    int* operator->() const; // should never be called

    int* m_pointer;
};

template <>
struct phi::pointer_traits<P4>
{
    static constexpr int* to_address(const P4& pointer)
    {
        return pointer.m_pointer;
    }
};

struct P5
{
    using element_type = Irrelevant;
    int const* const& operator->() const;
};

struct P6
{};

template <>
struct phi::pointer_traits<P6>
{
    static int const* const& to_address(const P6&);
};

// Taken from a build breakage caused in Clang
namespace P7
{
    template <typename TypeT>
    struct CanProxy;

    template <typename TypeT>
    struct CanQual
    {
        CanProxy<TypeT> operator->() const
        {
            return CanProxy<TypeT>();
        }
    };

    template <typename TypeT>
    struct CanProxy
    {
        const CanProxy<TypeT>* operator->() const
        {
            return nullptr;
        }
    };
} // namespace P7

namespace P8
{
    template <typename TypeT>
    struct FancyPtrA
    {
        using element_type = Irrelevant;

        constexpr FancyPtrA(TypeT* pointer)
            : m_pointer(pointer)
        {}

        TypeT& operator*() const;

        constexpr TypeT* operator->() const
        {
            return m_pointer;
        }

        TypeT* m_pointer;
    };
    template <typename TypeT>
    struct FancyPtrB
    {
        constexpr FancyPtrB(TypeT* pointer)
            : m_pointer(pointer)
        {}

        TypeT& operator*() const;

        TypeT* m_pointer;
    };
} // namespace P8

template <typename TypeT>
struct phi::pointer_traits<P8::FancyPtrB<TypeT>>
{
    static constexpr TypeT* to_address(const P8::FancyPtrB<TypeT>& pointer)
    {
        return pointer.m_pointer;
    }
};

struct Incomplete;

template <typename TypeT>
struct Holder
{
    TypeT* t;
};

constexpr bool test_to_address()
{
    int integer = 0;
    CHECK_NOEXCEPT(phi::to_address(&integer));
    PHI_RELEASE_ASSERT(phi::to_address(&integer) == &integer);

    P1 pointer1(&integer);
    CHECK_NOEXCEPT(phi::to_address(pointer1));
    PHI_RELEASE_ASSERT(phi::to_address(pointer1) == &integer);

    P2 pointer2(&integer);
    CHECK_NOEXCEPT(phi::to_address(pointer2));
    PHI_RELEASE_ASSERT(phi::to_address(pointer2) == &integer);

    P3 pointer3(&integer);
    CHECK_NOEXCEPT(phi::to_address(pointer3));
    PHI_RELEASE_ASSERT(phi::to_address(pointer3) == &integer);

    P4 pointer4(&integer);
    CHECK_NOEXCEPT(phi::to_address(pointer4));
    PHI_RELEASE_ASSERT(phi::to_address(pointer4) == &integer);

    CHECK_SAME_TYPE(decltype(phi::to_address(phi::declval<int const*>())), int const*);
    CHECK_SAME_TYPE(decltype(phi::to_address(phi::declval<P5>())), int const*);
    CHECK_SAME_TYPE(decltype(phi::to_address(phi::declval<P6>())), int const*);

    P7::CanQual<int>* pointer7 = nullptr;
    PHI_RELEASE_ASSERT(phi::to_address(pointer7) == nullptr);
    CHECK_SAME_TYPE(decltype(phi::to_address(pointer7)), P7::CanQual<int>*);

    Holder<Incomplete>*               pointer8_nil = nullptr; // for C++03 compatibility
    P8::FancyPtrA<Holder<Incomplete>> pointer_8a   = pointer8_nil;
    PHI_RELEASE_ASSERT(phi::to_address(pointer_8a) == pointer8_nil);
    CHECK_SAME_TYPE(decltype(phi::to_address(pointer_8a)), decltype(pointer8_nil));

    P8::FancyPtrB<Holder<Incomplete>> pointer_8b = pointer8_nil;
    PHI_RELEASE_ASSERT(phi::to_address(pointer_8b) == pointer8_nil);
    CHECK_SAME_TYPE(decltype(phi::to_address(pointer_8b)), decltype(pointer8_nil));

    int pointer9[2] = {};
    PHI_RELEASE_ASSERT(phi::to_address(pointer9) == pointer9);
    CHECK_SAME_TYPE(decltype(phi::to_address(pointer9)), int*);

    const int pointer10[2] = {};
    PHI_RELEASE_ASSERT(phi::to_address(pointer10) == pointer10);
    CHECK_SAME_TYPE(decltype(phi::to_address(pointer10)), const int*);

    int (*pointer11)() = nullptr;
    PHI_RELEASE_ASSERT(phi::to_address(&pointer11) == &pointer11);
    CHECK_SAME_TYPE(decltype(phi::to_address(&pointer11)), int (**)());

    return true;
}

TEST_CASE("core.to_address")
{
    test_to_address();
    STATIC_REQUIRE(test_to_address());
}
