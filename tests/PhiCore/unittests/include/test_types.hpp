#ifndef INCG_PHI_UNITTEST_TESTTYPES_HPP
#define INCG_PHI_UNITTEST_TESTTYPES_HPP

#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/unused.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/type_traits/false_t.hpp>
#include <cassert>

class Class
{
public:
    ~Class();
};

template <typename T>
class Template
{};

template <typename... Ts>
class VariadicTemplate
{};

template <typename T>
struct PublicDerviedFromTemplate : public T
{};

template <typename T>
struct PrivateDerviedFromTemplate : private T
{};

template <typename T>
struct ProtectedDerviedFromTemplate : protected T
{};

class Empty
{};

class NotEmpty
{
public:
    virtual ~NotEmpty();
};

union Union
{};

union NonEmptyUnion
{
    int      x;
    unsigned y;
};

struct bit_zero
{
    int : 0;
};

struct bit_one
{
    int : 1;
};

struct Base
{};

struct Derived : public Base
{};

class Abstract
{
    virtual ~Abstract() = 0;
};

struct PublicAbstract
{
    virtual ~PublicAbstract() = default;

public:
    virtual void foo() = 0;
};

struct ProtectedAbstract
{
    virtual ~ProtectedAbstract() = default;

protected:
    virtual void foo() = 0;
};

struct PrivateAbstract
{
    virtual ~PrivateAbstract() = default;

private:
    virtual void foo() = 0;
};

template <typename>
struct AbstractTemplate
{
    virtual ~AbstractTemplate() = 0;

    virtual void test() = 0;
};

template <>
struct AbstractTemplate<double>
{};

class Final final
{};

struct PublicDestructor
{
public:
    ~PublicDestructor() = default;
};

struct ProtectedDestructor
{
protected:
    ~ProtectedDestructor() = default;
};

struct PrivateDestructor
{
private:
    ~PrivateDestructor() = default;
};

struct VirtualPublicDestructor
{
public:
    virtual ~VirtualPublicDestructor() = default;
};

struct VirtualProtectedDestructor
{
protected:
    virtual ~VirtualProtectedDestructor() = default;
};

struct VirtualPrivateDestructor
{
private:
    virtual ~VirtualPrivateDestructor() = default;
};

struct PurePublicDestructor
{
public:
    virtual ~PurePublicDestructor() = 0;
};

struct PureProtectedDestructor
{
protected:
    virtual ~PureProtectedDestructor() = 0;
};

struct PurePrivateDestructor
{
private:
    virtual ~PurePrivateDestructor() = 0;
};

struct DeletedPublicDestructor
{
public:
    ~DeletedPublicDestructor() = delete;
};

struct DeletedProtectedDestructor
{
protected:
    ~DeletedProtectedDestructor() = delete;
};

struct DeletedPrivateDestructor
{
private:
    ~DeletedPrivateDestructor() = delete;
};

struct DeletedVirtualPublicDestructor
{
public:
    virtual ~DeletedVirtualPublicDestructor() = delete;
};

struct DeletedVirtualProtectedDestructor
{
protected:
    virtual ~DeletedVirtualProtectedDestructor() = delete;
};

struct DeletedVirtualPrivateDestructor
{
private:
    virtual ~DeletedVirtualPrivateDestructor() = delete;
};

enum Enum
{
    zero,
    one
};

enum EnumSigned : int
{
    two
};

enum EnumUnsigned : unsigned
{
    three
};

enum class EnumClass
{
    zero,
    one
};

enum struct EnumStruct
{
    zero,
    one
};

struct incomplete_type;

template <typename T>
struct IncompleteTemplate;

template <typename... Ts>
struct IncompleteVariadicTemplate;

using Function = void();

using FunctionPtr = void (*)();

using MemberObjectPtr = int Class::*;

using MemberFunctionPtr = void (Class::*)();

struct NonCopyable
{
    NonCopyable()                   = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&)      = default;

    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable& operator=(NonCopyable&&) = default;
};

struct NonMoveable
{
    NonMoveable()                   = default;
    NonMoveable(const NonMoveable&) = default;
    NonMoveable(NonMoveable&&)      = delete;

    NonMoveable& operator=(const NonMoveable&) = default;
    NonMoveable& operator=(NonMoveable&&) = delete;
};

struct NonConstructible
{
    NonConstructible()                        = delete;
    NonConstructible(const NonConstructible&) = delete;
    NonConstructible(NonConstructible&&)      = delete;

    NonConstructible& operator=(const NonConstructible&) = delete;
    NonConstructible& operator=(NonConstructible&&) = delete;
};

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wattributes")

class Tracked
{
    enum class State
    {
        Constructed,
        MovedFrom,
        Destroyed
    };

public:
    constexpr Tracked() noexcept
        : m_Value{0}
        , m_State{State::Constructed}
    {}

    constexpr explicit Tracked(int val) noexcept
        : m_Value{val}
        , m_State{State::Constructed}
    {}

    PHI_EXTENDED_CONSTEXPR Tracked(const Tracked& other) noexcept
        : m_Value{other.m_Value}
        , m_State{State::Constructed}
    {
        assert(other.m_State != State::MovedFrom);
        assert(other.m_State != State::Destroyed);
    }

    PHI_EXTENDED_CONSTEXPR Tracked(Tracked&& other) noexcept
        : m_Value{other.m_Value}
        , m_State{State::Constructed}
    {
        assert(other.m_State != State::MovedFrom);
        assert(other.m_State != State::Destroyed);

        other.m_State = State::MovedFrom;
    }

    PHI_EXTENDED_CONSTEXPR Tracked& operator=(const Tracked& other) noexcept
    {
        assert(m_State != State::Destroyed);
        assert(other.m_State != State::MovedFrom);
        assert(other.m_State != State::Destroyed);

        m_Value = other.m_Value;
        return *this;
    }

    PHI_EXTENDED_CONSTEXPR Tracked& operator=(Tracked&& other) noexcept
    {
        assert(m_State != State::Destroyed);
        assert(other.m_State != State::MovedFrom);
        assert(other.m_State != State::Destroyed);

        m_Value       = other.m_Value;
        other.m_State = State::MovedFrom;

        return *this;
    }

    PHI_CONSTEXPR_DESTRUCTOR ~Tracked() noexcept
    {
        assert(m_State != State::Destroyed); // Double destroy

        m_State = State::Destroyed;
    }

    PHI_EXTENDED_CONSTEXPR void set_value(int new_val) noexcept
    {
        assert(m_State != State::Destroyed);
        assert(m_State != State::MovedFrom);

        m_Value = new_val;
    }

    [[nodiscard]] PHI_EXTENDED_CONSTEXPR int value() const noexcept
    {
        assert(m_State != State::Destroyed);
        assert(m_State != State::MovedFrom);

        return m_Value;
    }

private:
    int   m_Value;
    State m_State;
};

PHI_GCC_SUPPRESS_WARNING_POP()

struct TrapConstructible
{
    TrapConstructible()                         = default;
    ~TrapConstructible()                        = default;
    TrapConstructible(const TrapConstructible&) = default;
    TrapConstructible(TrapConstructible&&)      = default;

    TrapConstructible& operator=(const TrapConstructible&) = default;
    TrapConstructible& operator=(TrapConstructible&&) = default;

    template <typename... ArgsT>
    // GCC versions before 9.0.0 have a problems with [[maybe_unused]] and constructors with template parameter packs
#if PHI_COMPILER_IS_BELOW(GCC, 9, 0, 0)
#    if PHI_HAS_EXTENSION_ATTRIBUTE_UNUSED()
    constexpr TrapConstructible(__attribute((unused)) ArgsT&&... args) noexcept
#    else
    constexpr TrapConstructible(ArgsT&&... args) noexcept
#    endif
#else
    constexpr TrapConstructible(PHI_UNUSED ArgsT&&... args) noexcept
#endif
    {
        static_assert(phi::false_t<ArgsT...>::value,
                      "TrapConstructible constructor must not be used");
    }
};

struct TrapImplicitConversion
{
    template <typename TypeT>
    constexpr operator TypeT() noexcept
    {
        static_assert(phi::false_t<TypeT>::value,
                      "TrapImplicitConversion::operator TypeT, must never be instantiated");
    }
};

struct TrapComma
{
    template <typename TypeT>
    friend constexpr void operator,(const TrapComma&, TypeT&&) noexcept
    {
        static_assert(phi::false_t<TypeT>::value,
                      "TrapComma::operator, must never be instantiated");
    }

    template <typename TypeT>
    friend constexpr void operator,(TypeT&&, const TrapComma&) noexcept
    {
        static_assert(phi::false_t<TypeT>::value,
                      "TrapComma::operator, must never be instantiated");
    }
};

struct TrapCall
{
    template <typename... ArgsT>
    constexpr void operator()(ArgsT&&...) noexcept
    {
        static_assert(phi::false_t<ArgsT...>::value,
                      "TrapCall::operator() must never be instantiated");
    }
};

struct TrapSelfAssign
{
    TrapSelfAssign()                      = default;
    ~TrapSelfAssign()                     = default;
    TrapSelfAssign(const TrapSelfAssign&) = default;
    TrapSelfAssign(TrapSelfAssign&&)      = default;

    PHI_EXTENDED_CONSTEXPR TrapSelfAssign& operator=(
            PHI_UNUSED const TrapSelfAssign& other) noexcept
    {
        assert(&other != this);

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR TrapSelfAssign& operator=(PHI_UNUSED TrapSelfAssign&& other) noexcept
    {
        assert(&other != this);

        return *this;
    }
};

struct TrapDeref
{
    template <typename T>
    constexpr T operator*() noexcept
    {
        static_assert(phi::false_t<T>::value, "TrapDeref::operator*() must never be instantiated");
    }

    template <typename T>
    constexpr T* operator->() noexcept
    {
        static_assert(phi::false_t<T>::value, "TrapDeref::operator->() must never be instantiated");
    }
};

struct TrapArraySubscript
{
    template <typename T>
    constexpr void operator[](PHI_UNUSED T x) noexcept
    {
        static_assert(phi::false_t<T>::value,
                      "TrapArraySubscript::operator[] must never be instantiated");
    }
};

#endif // INCG_PHI_UNITTEST_TESTTYPES_HPP
