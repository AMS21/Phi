#ifndef INCG_PHI_UNITTEST_TESTTYPES_HPP
#define INCG_PHI_UNITTEST_TESTTYPES_HPP

#include <Phi/CompilerSupport/Constexpr.hpp>
#include <Phi/CompilerSupport/Unused.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/always_false.hpp>
#include <cassert>

class Class
{
public:
    ~Class();
};

struct Struct
{
    ~Struct();
};

template <typename T>
class TemplateClass
{};

template <typename... Ts>
class VariadicTemplateClass
{};

template <typename T>
struct TemplateStruct
{};

template <typename... Ts>
struct VariadicTemplateStruct
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
        assert(m_State != State::MovedFrom);
        assert(m_State != State::Destroyed);
        assert(other.m_State != State::MovedFrom);
        assert(other.m_State != State::Destroyed);

        m_Value = other.m_Value;
        return *this;
    }

    PHI_EXTENDED_CONSTEXPR Tracked& operator=(Tracked&& other) noexcept
    {
        assert(m_State != State::MovedFrom);
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

private:
    int m_Value;
    // Use volatile to force the compiler to not optimize away any assignments
    volatile State m_State;
};

struct TrapConstructible
{
    TrapConstructible()                         = default;
    ~TrapConstructible()                        = default;
    TrapConstructible(const TrapConstructible&) = default;
    TrapConstructible(TrapConstructible&&)      = default;

    template <typename... ArgsT>
    constexpr TrapConstructible(ArgsT&&...) noexcept
    {
        static_assert(phi::always_false<ArgsT...>::value,
                      "TrapConstructible constructor must not be used");
    }
};

struct TrapImplicitConversion
{
    template <typename TypeT>
    constexpr operator TypeT() noexcept
    {
        static_assert(phi::always_false<TypeT>::value,
                      "TrapImplicitConversion::operator TypeT, must never be instantiated");
    }
};

struct TrapComma
{
    template <typename TypeT>
    friend constexpr void operator,(const TrapComma&, TypeT&&) noexcept
    {
        static_assert(phi::always_false<TypeT>::value,
                      "TrapComma::operator, must never be instantiated");
    }

    template <typename TypeT>
    friend constexpr void operator,(TypeT&&, const TrapComma&) noexcept
    {
        static_assert(phi::always_false<TypeT>::value,
                      "TrapComma::operator, must never be instantiated");
    }
};

struct TrapCall
{
    template <typename... ArgsT>
    constexpr void operator()(ArgsT&&...) noexcept
    {
        static_assert(phi::always_false<ArgsT...>::value,
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

#endif // INCG_PHI_UNITTEST_TESTTYPES_HPP
