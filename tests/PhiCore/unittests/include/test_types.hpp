#ifndef INCG_PHI_UNITTEST_TESTTYPES_HPP
#define INCG_PHI_UNITTEST_TESTTYPES_HPP

#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/unused.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/type_traits/false_t.hpp>
#include <cassert>

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wused-but-marked-unused")

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
struct PublicDerivedFromTemplate : public T
{};

template <typename T>
struct PrivateDerivedFromTemplate : private T
{};

template <typename T>
struct ProtectedDerivedFromTemplate : protected T
{};

template <typename T>
struct VirtualDerivedFromTemplate : virtual T
{};

class Empty
{};

class NotEmpty
{
public:
    virtual ~NotEmpty();
};

struct NonTrivial
{
    NonTrivial();
    NonTrivial(const NonTrivial&);
    NonTrivial& operator=(const NonTrivial&);
    ~NonTrivial();
};

union Union
{};

union NonEmptyUnion
{
    int      x;
    unsigned y;
};

union NonTrivialUnion
{
    int        i;
    NonTrivial n;
};

struct BitZero
{
    int : 0;
};

struct BitOne
{
    int : 1;
};

struct Base
{};

struct Derived : public Base
{};

struct NotEmptyBase : public NotEmpty
{};

struct EmptyBase : public Empty
{};

struct VirtualBase : virtual Empty
{};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wnon-virtual-dtor")
PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnon-virtual-dtor")

class Polymorphic
{
    virtual void rotate(int);
};

class DerivedPolymorphic : public Polymorphic
{};

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

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

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wnon-virtual-dtor")
PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnon-virtual-dtor")

struct PublicAbstractDeletedDestructor
{
    ~PublicAbstractDeletedDestructor() = delete;

public:
    virtual void foo() = 0;
};

struct ProtectedAbstractDeletedDestructor
{
    ~ProtectedAbstractDeletedDestructor() = delete;

protected:
    virtual void foo() = 0;
};

struct PrivateAbstractDeletedDestructor
{
    ~PrivateAbstractDeletedDestructor() = delete;

private:
    virtual void foo() = 0;
};

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

class Final final
{};

class FinalDerived final : public Base
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

struct ExplicitClass
{
    ExplicitClass(double&);
    explicit ExplicitClass(int&);
    ExplicitClass(double&, int&, double&);
};

struct NothrowExplicitClass
{
    NothrowExplicitClass(double&) noexcept;
    explicit NothrowExplicitClass(int&) noexcept;
    NothrowExplicitClass(double&, int&, double&) noexcept;
};

struct ThrowExplicitClass
{
    ThrowExplicitClass(double&) noexcept(false);
    explicit ThrowExplicitClass(int&) noexcept(false);
    ThrowExplicitClass(double&, int&, double&) noexcept(false);
};

struct ThrowDefaultClass
{
    ThrowDefaultClass() noexcept(false);
};

struct ThrowCopyConsClass
{
    ThrowCopyConsClass(const ThrowCopyConsClass&) noexcept(false);
};

struct ThrowMoveConsClass
{
    ThrowMoveConsClass(ThrowMoveConsClass&&) noexcept(false);
};

struct ThrowDestructor
{
    ~ThrowDestructor() noexcept(false);
};

struct NoexceptExplicitClass
{
    NoexceptExplicitClass(double&) noexcept(true);
    explicit NoexceptExplicitClass(int&) noexcept(true);
    NoexceptExplicitClass(double&, int&, double&) noexcept(true);
};

struct ExceptExplicitClass
{
    ExceptExplicitClass(double&) noexcept(false);
    explicit ExceptExplicitClass(int&) noexcept(false);
    ExceptExplicitClass(double&, int&, double&) noexcept(false);
};

struct NoexceptDefaultClass
{
    NoexceptDefaultClass() noexcept(true);
};

struct ExceptDefaultClass
{
    ExceptDefaultClass() noexcept(false);
};

struct NoexceptCopyConsClass
{
    NoexceptCopyConsClass(const NoexceptCopyConsClass&) noexcept(true);
};

struct ExceptCopyConsClass
{
    ExceptCopyConsClass(const ExceptCopyConsClass&) noexcept(false);
};

struct NoexceptMoveConsClass
{
    NoexceptMoveConsClass(NoexceptMoveConsClass&&) noexcept(true);
    NoexceptMoveConsClass& operator=(NoexceptMoveConsClass&&) = default;
};

struct ExceptMoveConsClass
{
    ExceptMoveConsClass(ExceptMoveConsClass&&) noexcept(false);
};

struct NoexceptCopyAssignClass
{
    NoexceptCopyAssignClass& operator=(const NoexceptCopyAssignClass&) noexcept(true);
};

struct ExceptCopyAssignClass
{
    ExceptCopyAssignClass& operator=(const ExceptCopyAssignClass&) noexcept(false);
};

struct NoexceptMoveAssignClass
{
    NoexceptMoveAssignClass(NoexceptMoveAssignClass&&) = default;
    NoexceptMoveAssignClass& operator                  =(NoexceptMoveAssignClass&&) noexcept(true);
};

struct ExceptMoveAssignClass
{
    ExceptMoveAssignClass& operator=(ExceptMoveAssignClass&&) noexcept(false);
};

struct DeletedCopyAssignClass
{
    DeletedCopyAssignClass& operator=(const DeletedCopyAssignClass&) = delete;
};

struct DeletedMoveAssignClass
{
    DeletedMoveAssignClass& operator=(DeletedMoveAssignClass&&) = delete;
};

struct NoexceptMoveConsNoexceptMoveAssignClass
{
    NoexceptMoveConsNoexceptMoveAssignClass(NoexceptMoveConsNoexceptMoveAssignClass&&) noexcept(
            true);

    NoexceptMoveConsNoexceptMoveAssignClass& operator=(
            NoexceptMoveConsNoexceptMoveAssignClass&&) noexcept(true);
};

struct ExceptMoveConsNoexceptMoveAssignClass
{
    ExceptMoveConsNoexceptMoveAssignClass(ExceptMoveConsNoexceptMoveAssignClass&&) noexcept(false);

    ExceptMoveConsNoexceptMoveAssignClass& operator=(
            ExceptMoveConsNoexceptMoveAssignClass&&) noexcept(true);
};

struct NoexceptMoveConsExceptMoveAssignClass
{
    NoexceptMoveConsExceptMoveAssignClass(NoexceptMoveConsExceptMoveAssignClass&&) noexcept(true);

    NoexceptMoveConsExceptMoveAssignClass& operator=(
            NoexceptMoveConsExceptMoveAssignClass&&) noexcept(false);
};

struct ExceptMoveConsExceptMoveAssignClass
{
    ExceptMoveConsExceptMoveAssignClass(ExceptMoveConsExceptMoveAssignClass&&) noexcept(false);

    ExceptMoveConsExceptMoveAssignClass& operator=(ExceptMoveConsExceptMoveAssignClass&&) noexcept(
            false);
};

template <typename To>
struct ImplicitTo
{
    operator To();
};

template <typename To>
struct DeletedImplicitTo
{
    operator To() = delete;
};

template <typename To>
struct ExplicitTo
{
    explicit operator To();
};

template <typename To>
struct DeletedExplicitTo
{
    explicit operator To() = delete;
};

struct Ellipsis
{
    Ellipsis(...)
    {}
};

struct DeletedEllipsis
{
    DeletedEllipsis(...) = delete;
};

struct CopyConsOnlyType
{
    CopyConsOnlyType(int)
    {}
    CopyConsOnlyType(CopyConsOnlyType&&)      = delete;
    CopyConsOnlyType(const CopyConsOnlyType&) = default;
    CopyConsOnlyType& operator=(const CopyConsOnlyType&) = delete;
    CopyConsOnlyType& operator=(CopyConsOnlyType&&) = delete;
};

struct MoveConsOnlyType
{
    MoveConsOnlyType(int)
    {}
    MoveConsOnlyType(const MoveConsOnlyType&) = delete;
    MoveConsOnlyType(MoveConsOnlyType&&)      = default;
    MoveConsOnlyType& operator=(const MoveConsOnlyType&) = delete;
    MoveConsOnlyType& operator=(MoveConsOnlyType&&) = delete;
};

struct OverloadedOperators
{
    int foo()
    {
        return 1;
    }

    int foo_c() const
    {
        return 2;
    }

    int foo_v() volatile
    {
        return 3;
    }

    int foo_cv() const volatile
    {
        return 4;
    }
};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunused-private-field")

struct PublicIntMember
{
public:
    int member;
};

struct ProtectedIntMember
{
protected:
    int member;
};

struct PrivateIntMember
{
private:
    int member;
};

struct PublicStaticIntMember
{
public:
    static int member;
};

struct ProtectedStaticIntMember
{
protected:
    static int member;
};

struct PrivateStaticIntMember
{
private:
    static int member;
};

template <typename T>
struct PublicTemplateMember
{
public:
    T member;
};

template <typename T>
struct ProtectedTemplateMember
{
protected:
    T member;
};

template <typename T>
struct PrivateTemplateMember
{
private:
    T member;
};

template <typename T>
struct PublicStaticTemplateMember
{
public:
    static T member;
};

template <typename T>
struct ProtectedStaticTemplateMember
{
protected:
    static T member;
};

template <typename T>
struct PrivateStaticTemplateMember
{
private:
    static T member;
};

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename T>
class CannotInstantiate
{
    enum
    {
        X = T::ThisExpressionWillBlowUp
    };
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

using Function = void();

using FunctionPtr = void (*)();

using MemberObjectPtr = int Class::*;

using MemberFunctionPtr = void (Class::*)();

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")

static auto Lambda = []() {};

static auto LambdaNoexcept = []() noexcept {};

static auto LambdaThrows = []() noexcept(false) {};

PHI_CLANG_SUPPRESS_WARNING_POP()

using LambdaType = decltype(Lambda);

using LambdaNoexceptType = decltype(LambdaNoexcept);

using LambdaThrowsType = decltype(LambdaThrows);

struct IncompleteType;

template <typename T>
struct IncompleteTemplate;

template <typename... Ts>
struct IncompleteVariadicTemplate;

union IncompleteUnion;

enum IncompleteEnumSigned : int;

enum IncompleteEnumUnsigned : unsigned int;

enum class IncompleteEnumClass;

enum struct IncompleteEnumStruct;

struct NonDefaultConstructible
{
    NonDefaultConstructible()                               = delete;
    NonDefaultConstructible(const NonDefaultConstructible&) = default;
    NonDefaultConstructible(NonDefaultConstructible&&)      = default;

    NonDefaultConstructible& operator=(const NonDefaultConstructible&) = default;
    NonDefaultConstructible& operator=(NonDefaultConstructible&&) = default;
};

struct NonCopyConstructible
{
    NonCopyConstructible()                            = default;
    NonCopyConstructible(const NonCopyConstructible&) = delete;
    NonCopyConstructible(NonCopyConstructible&&)      = default;

    NonCopyConstructible& operator=(const NonCopyConstructible&) = default;
    NonCopyConstructible& operator=(NonCopyConstructible&&) = default;
};

struct NonMoveConstructible
{
    NonMoveConstructible()                            = default;
    NonMoveConstructible(const NonMoveConstructible&) = default;
    NonMoveConstructible(NonMoveConstructible&&)      = delete;

    NonMoveConstructible& operator=(const NonMoveConstructible&) = default;
    NonMoveConstructible& operator=(NonMoveConstructible&&) = default;
};

struct NonCopyAssignable
{
    NonCopyAssignable()                         = default;
    NonCopyAssignable(const NonCopyAssignable&) = default;
    NonCopyAssignable(NonCopyAssignable&&)      = default;

    NonCopyAssignable& operator=(const NonCopyAssignable&) = delete;
    NonCopyAssignable& operator=(NonCopyAssignable&&) = default;
};

struct NonMoveAssignable
{
    NonMoveAssignable()                         = default;
    NonMoveAssignable(const NonMoveAssignable&) = default;
    NonMoveAssignable(NonMoveAssignable&&)      = default;

    NonMoveAssignable& operator=(const NonMoveAssignable&) = default;
    NonMoveAssignable& operator=(NonMoveAssignable&&) = delete;
};

struct NonAssignable
{
    NonAssignable()                     = default;
    NonAssignable(const NonAssignable&) = default;
    NonAssignable(NonAssignable&&)      = default;

    NonAssignable& operator=(const NonAssignable&) = delete;
    NonAssignable& operator=(NonAssignable&&) = delete;
};

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

struct NonDestructible
{
    NonDestructible()                       = default;
    ~NonDestructible()                      = delete;
    NonDestructible(const NonDestructible&) = default;
    NonDestructible(NonDestructible&&)      = default;

    NonDestructible& operator=(const NonDestructible&) = default;
    NonDestructible& operator=(NonDestructible&&) = default;
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

        return TypeT{};
    }
};

struct TrapComma
{
    template <typename TypeT>
    friend constexpr bool operator,(const TrapComma&, TypeT&&) noexcept
    {
        static_assert(phi::false_t<TypeT>::value,
                      "TrapComma::operator, must never be instantiated");

        return false;
    }

    template <typename TypeT>
    friend constexpr bool operator,(TypeT&&, const TrapComma&) noexcept
    {
        static_assert(phi::false_t<TypeT>::value,
                      "TrapComma::operator, must never be instantiated");

        return false;
    }
};

struct TrapCall
{
    template <typename... ArgsT>
    constexpr bool operator()(ArgsT&&...) noexcept
    {
        static_assert(phi::false_t<ArgsT...>::value,
                      "TrapCall::operator() must never be instantiated");

        return false;
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
        return T{};
    }

    template <typename T>
    constexpr T* operator->() noexcept
    {
        static_assert(phi::false_t<T>::value, "TrapDeref::operator->() must never be instantiated");
        return T{};
    }
};

struct TrapArraySubscript
{
    template <typename T>
    constexpr bool operator[](PHI_UNUSED T x) noexcept
    {
        static_assert(phi::false_t<T>::value,
                      "TrapArraySubscript::operator[] must never be instantiated");
        return false;
    }
};

PHI_CLANG_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_UNITTEST_TESTTYPES_HPP
