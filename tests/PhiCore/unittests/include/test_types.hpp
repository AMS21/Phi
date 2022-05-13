#ifndef INCG_PHI_UNITTEST_TEST_TYPES_HPP
#define INCG_PHI_UNITTEST_TEST_TYPES_HPP

#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/unused.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/type_traits/false_t.hpp>
#include <cassert>

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wused-but-marked-unused")

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4624) // 'x': destructor was implicitly defined as deleted
PHI_MSVC_SUPPRESS_WARNING(
        5204) // 'x': class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly
PHI_MSVC_SUPPRESS_WARNING(
        4265) // 'x': class has virtual functions, but its non-trivial destructor is not virtual; instances of the class may not be destructed correctly

class class_type
{
public:
    ~class_type();
};

template <typename TypeT>
class template_type
{};

template <typename... TypesT>
class variadic_template
{};

template <typename TypeT>
struct public_derived_from : public TypeT
{};

template <typename TypeT>
struct private_derived_from : private TypeT
{};

template <typename TypeT>
struct protected_derived_from : protected TypeT
{};

template <typename TypeT>
struct virtual_derived_from : virtual TypeT
{};

class empty
{};

class not_empty
{
public:
    virtual ~not_empty();
};

struct non_trivial
{
    non_trivial();
    non_trivial(const non_trivial&);
    non_trivial& operator=(const non_trivial&);
    ~non_trivial();
};

union union_type
{};

union non_empty_union
{
    int      x;
    unsigned y;
};

union non_trivial_union
{
    int         i;
    non_trivial n;
};

struct bit_zero
{
    int : 0;
};

struct bit_one
{
    int : 1;
};

struct base
{};

struct derived : public base
{};

struct non_empty_base : public not_empty
{};

struct empty_base : public empty
{};

struct virtual_Base : virtual empty
{};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wnon-virtual-dtor")
PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnon-virtual-dtor")

class polymorphic
{
    virtual void rotate(int);
};

class derived_polymorphic : public polymorphic
{};

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

class abstract
{
    virtual ~abstract() = 0;
};

struct public_abstract
{
    virtual ~public_abstract() = default;

public:
    virtual void foo() = 0;
};

struct protected_abstract
{
    virtual ~protected_abstract() = default;

protected:
    virtual void foo() = 0;
};

struct private_abstract
{
    virtual ~private_abstract() = default;

private:
    virtual void foo() = 0;
};

template <typename>
struct abstract_template
{
    virtual ~abstract_template() = 0;

    virtual void test() = 0;
};

template <>
struct abstract_template<double>
{};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wnon-virtual-dtor")
PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnon-virtual-dtor")

struct public_abstract_deleted_destructor
{
    ~public_abstract_deleted_destructor() = delete;

public:
    virtual void foo() = 0;
};

struct protected_abstract_deleted_destructor
{
    ~protected_abstract_deleted_destructor() = delete;

protected:
    virtual void foo() = 0;
};

struct private_abstract_deleted_destructor
{
    ~private_abstract_deleted_destructor() = delete;

private:
    virtual void foo() = 0;
};

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

class final_type final
{};

class final_derived final : public base
{};

struct public_destructor
{
public:
    ~public_destructor() = default;
};

struct protected_destructor
{
protected:
    ~protected_destructor() = default;
};

struct private_destructor
{
private:
    ~private_destructor() = default;
};

struct virtual_public_destructor
{
public:
    virtual ~virtual_public_destructor() = default;
};

struct virtual_protected_destructor
{
protected:
    virtual ~virtual_protected_destructor() = default;
};

struct virtual_private_destructor
{
private:
    virtual ~virtual_private_destructor() = default;
};

struct pure_public_destructor
{
public:
    virtual ~pure_public_destructor() = 0;
};

struct pure_protected_destructor
{
protected:
    virtual ~pure_protected_destructor() = 0;
};

struct pure_private_destructor
{
private:
    virtual ~pure_private_destructor() = 0;
};

struct deleted_public_destructor
{
public:
    ~deleted_public_destructor() = delete;
};

struct deleted_protected_destructor
{
protected:
    ~deleted_protected_destructor() = delete;
};

struct deleted_private_destructor
{
private:
    ~deleted_private_destructor() = delete;
};

struct deleted_virtual_public_destructor
{
public:
    virtual ~deleted_virtual_public_destructor() = delete;
};

struct deleted_virtual_protected_destructor
{
protected:
    virtual ~deleted_virtual_protected_destructor() = delete;
};

struct deleted_virtual_private_destructor
{
private:
    virtual ~deleted_virtual_private_destructor() = delete;
};

struct explicit_class
{
    explicit_class(double&);
    explicit explicit_class(int&);
    explicit_class(double&, int&, double&);
};

struct nothrow_explicit_class
{
    nothrow_explicit_class(double&) noexcept;
    explicit nothrow_explicit_class(int&) noexcept;
    nothrow_explicit_class(double&, int&, double&) noexcept;
};

struct throw_explicit_class
{
    throw_explicit_class(double&) noexcept(false);
    explicit throw_explicit_class(int&) noexcept(false);
    throw_explicit_class(double&, int&, double&) noexcept(false);
};

struct throw_default_class
{
    throw_default_class() noexcept(false);
};

struct throw_copy_constructible_class
{
    throw_copy_constructible_class(const throw_copy_constructible_class&) noexcept(false);
};

struct throw_move_constructible_class
{
    throw_move_constructible_class(throw_move_constructible_class&&) noexcept(false);
};

struct throw_destructor
{
    ~throw_destructor() noexcept(false);
};

struct noexcept_explicit_class
{
    noexcept_explicit_class(double&) noexcept;
    explicit noexcept_explicit_class(int&) noexcept;
    noexcept_explicit_class(double&, int&, double&) noexcept;
};

struct except_explicit_class
{
    except_explicit_class(double&) noexcept(false);
    explicit except_explicit_class(int&) noexcept(false);
    except_explicit_class(double&, int&, double&) noexcept(false);
};

struct noexcept_default_class
{
    noexcept_default_class() noexcept;
};

struct except_default_class
{
    except_default_class() noexcept(false);
};

struct noexcept_copy_constructible_class
{
    noexcept_copy_constructible_class(const noexcept_copy_constructible_class&) noexcept;
};

struct except_copy_constructible_class
{
    except_copy_constructible_class(const except_copy_constructible_class&) noexcept(false);
};

struct noexcept_move_constructible_class
{
    noexcept_move_constructible_class(noexcept_move_constructible_class&&) noexcept;
    noexcept_move_constructible_class& operator=(noexcept_move_constructible_class&&) = default;
};

struct except_move_constructible_class
{
    except_move_constructible_class(except_move_constructible_class&&) noexcept(false);
};

struct noexcept_copy_assign_class
{
    noexcept_copy_assign_class& operator=(const noexcept_copy_assign_class&) noexcept;
};

struct except_copy_assign_class
{
    except_copy_assign_class& operator=(const except_copy_assign_class&) noexcept(false);
};

struct noexcept_move_assign_class
{
    noexcept_move_assign_class(noexcept_move_assign_class&&) = default;
    noexcept_move_assign_class& operator=(noexcept_move_assign_class&&) noexcept;
};

struct except_move_assign_class
{
    except_move_assign_class& operator=(except_move_assign_class&&) noexcept(false);
};

struct deleted_copy_assign_class
{
    deleted_copy_assign_class& operator=(const deleted_copy_assign_class&) = delete;
};

struct deleted_move_assign_class
{
    deleted_move_assign_class& operator=(deleted_move_assign_class&&) = delete;
};

struct noexcept_move_constructible_and_assignable_class
{
    noexcept_move_constructible_and_assignable_class(
            noexcept_move_constructible_and_assignable_class&&) noexcept;

    noexcept_move_constructible_and_assignable_class& operator=(
            noexcept_move_constructible_and_assignable_class&&) noexcept;
};

struct except_move_constructible_noexcept_move_assign_class
{
    except_move_constructible_noexcept_move_assign_class(
            except_move_constructible_noexcept_move_assign_class&&) noexcept(false);

    except_move_constructible_noexcept_move_assign_class& operator=(
            except_move_constructible_noexcept_move_assign_class&&) noexcept;
};

struct noexcept_move_constructible_except_move_assign_class
{
    noexcept_move_constructible_except_move_assign_class(
            noexcept_move_constructible_except_move_assign_class&&) noexcept;

    noexcept_move_constructible_except_move_assign_class& operator=(
            noexcept_move_constructible_except_move_assign_class&&) noexcept(false);
};

struct except_move_constructible_and_assign_class
{
    except_move_constructible_and_assign_class(
            except_move_constructible_and_assign_class&&) noexcept(false);

    except_move_constructible_and_assign_class& operator=(
            except_move_constructible_and_assign_class&&) noexcept(false);
};

template <typename To>
struct implicit_to
{
    operator To();
};

template <typename To>
struct deleted_implicit_to
{
    operator To() = delete;
};

template <typename To>
struct ExplicitTo
{
    explicit operator To();
};

template <typename To>
struct deleted_explicit_to
{
    explicit operator To() = delete;
};

struct ellipsis
{
    ellipsis(...)
    {}
};

struct deleted_ellipsis
{
    deleted_ellipsis(...) = delete;
};

struct copy_constructible_only_type
{
    copy_constructible_only_type(int)
    {}
    copy_constructible_only_type(copy_constructible_only_type&&)      = delete;
    copy_constructible_only_type(const copy_constructible_only_type&) = default;
    copy_constructible_only_type& operator=(const copy_constructible_only_type&) = delete;
    copy_constructible_only_type& operator=(copy_constructible_only_type&&) = delete;
};

struct move_constructible_only_type
{
    move_constructible_only_type(int)
    {}
    move_constructible_only_type(const move_constructible_only_type&) = delete;
    move_constructible_only_type(move_constructible_only_type&&)      = default;
    move_constructible_only_type& operator=(const move_constructible_only_type&) = delete;
    move_constructible_only_type& operator=(move_constructible_only_type&&) = delete;
};

struct overloaded_operators
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

struct public_int_member
{
public:
    int member;
};

struct protected_int_member
{
protected:
    int member;
};

struct private_int_member
{
private:
    int member;
};

struct public_static_int_member
{
public:
    static int member;
};

struct protected_static_int_member
{
protected:
    static int member;
};

struct private_static_int_member
{
private:
    static int member;
};

template <typename TypeT>
struct public_template_member
{
public:
    TypeT member;
};

template <typename TypeT>
struct protected_template_member
{
protected:
    TypeT member;
};

template <typename TypeT>
struct private_template_member
{
private:
    TypeT member;
};

template <typename TypeT>
struct public_static_tempalte_member
{
public:
    static TypeT member;
};

template <typename TypeT>
struct protected_static_template_member
{
protected:
    static TypeT member;
};

template <typename TypeT>
struct private_static_template_member
{
private:
    static TypeT member;
};

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename TypeT>
class cannot_instantiate
{
    enum
    {
        X = TypeT::ThisExpressionWillBlowUp
    };
};

struct natural_alignment
{
    long        t1;
    long long   t2;
    double      t3;
    long double t4;
};

enum enum_type
{
    zero,
    one
};

enum enum_signed : int
{
    two
};

enum enum_unsigned : unsigned
{
    three
};

enum class enum_class
{
    zero,
    one
};

enum struct enum_struct
{
    zero,
    one
};

using function_type = void();

using function_ptr = void (*)();

using member_object_ptr = int class_type::*;

using member_function_ptr = void (class_type::*)();

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")

static auto Lambda = []() {};

static auto LambdaNoexcept = []() noexcept {};

static auto LambdaThrows = []() noexcept(false) {};

PHI_CLANG_SUPPRESS_WARNING_POP()

using lambda_type = decltype(Lambda);

using lambda_noexcept_type = decltype(LambdaNoexcept);

using lambda_throws_type = decltype(LambdaThrows);

struct incomplete_type;

template <typename TypeT>
struct incomplete_template;

template <typename... Ts>
struct IncompleteVariadicTemplate;

union incomplete_union;

enum incomplete_enum_signed : int;

enum incomplete_enum_unsigned : unsigned int;

enum class incomplete_enum_class;

enum struct incomplete_enum_struct;

struct non_default_constructible
{
    non_default_constructible()                                 = delete;
    non_default_constructible(const non_default_constructible&) = default;
    non_default_constructible(non_default_constructible&&)      = default;

    non_default_constructible& operator=(const non_default_constructible&) = default;
    non_default_constructible& operator=(non_default_constructible&&) = default;
};

struct non_copy_constructible
{
    non_copy_constructible()                              = default;
    non_copy_constructible(const non_copy_constructible&) = delete;
    non_copy_constructible(non_copy_constructible&&)      = default;

    non_copy_constructible& operator=(const non_copy_constructible&) = default;
    non_copy_constructible& operator=(non_copy_constructible&&) = default;
};

struct non_move_constructible
{
    non_move_constructible()                              = default;
    non_move_constructible(const non_move_constructible&) = default;
    non_move_constructible(non_move_constructible&&)      = delete;

    non_move_constructible& operator=(const non_move_constructible&) = default;
    non_move_constructible& operator=(non_move_constructible&&) = default;
};

struct non_copy_assignable
{
    non_copy_assignable()                           = default;
    non_copy_assignable(const non_copy_assignable&) = default;
    non_copy_assignable(non_copy_assignable&&)      = default;

    non_copy_assignable& operator=(const non_copy_assignable&) = delete;
    non_copy_assignable& operator=(non_copy_assignable&&) = default;
};

struct non_move_assignable
{
    non_move_assignable()                           = default;
    non_move_assignable(const non_move_assignable&) = default;
    non_move_assignable(non_move_assignable&&)      = default;

    non_move_assignable& operator=(const non_move_assignable&) = default;
    non_move_assignable& operator=(non_move_assignable&&) = delete;
};

struct non_assignable
{
    non_assignable()                      = default;
    non_assignable(const non_assignable&) = default;
    non_assignable(non_assignable&&)      = default;

    non_assignable& operator=(const non_assignable&) = delete;
    non_assignable& operator=(non_assignable&&) = delete;
};

struct non_copyable
{
    non_copyable()                    = default;
    non_copyable(const non_copyable&) = delete;
    non_copyable(non_copyable&&)      = default;

    non_copyable& operator=(const non_copyable&) = delete;
    non_copyable& operator=(non_copyable&&) = default;
};

struct non_moveable
{
    non_moveable()                    = default;
    non_moveable(const non_moveable&) = default;
    non_moveable(non_moveable&&)      = delete;

    non_moveable& operator=(const non_moveable&) = default;
    non_moveable& operator=(non_moveable&&) = delete;
};

struct non_constructible
{
    non_constructible()                         = delete;
    non_constructible(const non_constructible&) = delete;
    non_constructible(non_constructible&&)      = delete;

    non_constructible& operator=(const non_constructible&) = delete;
    non_constructible& operator=(non_constructible&&) = delete;
};

struct non_destructible
{
    non_destructible()                        = default;
    ~non_destructible()                       = delete;
    non_destructible(const non_destructible&) = default;
    non_destructible(non_destructible&&)      = default;

    non_destructible& operator=(const non_destructible&) = default;
    non_destructible& operator=(non_destructible&&) = default;
};

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wattributes")

class tracked
{
    enum class State
    {
        Constructed,
        MovedFrom,
        Destroyed
    };

public:
    constexpr tracked() noexcept
        : m_Value{0}
        , m_State{State::Constructed}
    {}

    constexpr explicit tracked(int val) noexcept
        : m_Value{val}
        , m_State{State::Constructed}
    {}

    PHI_EXTENDED_CONSTEXPR tracked(const tracked& other) noexcept
        : m_Value{other.m_Value}
        , m_State{State::Constructed}
    {
        assert(other.m_State != State::MovedFrom);
        assert(other.m_State != State::Destroyed);
    }

    PHI_EXTENDED_CONSTEXPR tracked(tracked&& other) noexcept
        : m_Value{other.m_Value}
        , m_State{State::Constructed}
    {
        assert(other.m_State != State::MovedFrom);
        assert(other.m_State != State::Destroyed);

        other.m_State = State::MovedFrom;
    }

    PHI_EXTENDED_CONSTEXPR tracked& operator=(const tracked& other) noexcept
    {
        assert(m_State != State::Destroyed);
        assert(other.m_State != State::MovedFrom);
        assert(other.m_State != State::Destroyed);

        m_Value = other.m_Value;
        return *this;
    }

    PHI_EXTENDED_CONSTEXPR tracked& operator=(tracked&& other) noexcept
    {
        assert(m_State != State::Destroyed);
        assert(other.m_State != State::MovedFrom);
        assert(other.m_State != State::Destroyed);

        m_Value       = other.m_Value;
        other.m_State = State::MovedFrom;

        return *this;
    }

    PHI_CONSTEXPR_DESTRUCTOR ~tracked() noexcept
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

struct trap_constructible
{
    trap_constructible()                          = default;
    ~trap_constructible()                         = default;
    trap_constructible(const trap_constructible&) = default;
    trap_constructible(trap_constructible&&)      = default;

    trap_constructible& operator=(const trap_constructible&) = default;
    trap_constructible& operator=(trap_constructible&&) = default;

    template <typename... ArgsT>
    constexpr trap_constructible(ArgsT&&... /*args*/) noexcept
    {
        static_assert(phi::false_t<ArgsT...>::value,
                      "trap_constructible constructor must not be used");
    }
};

struct trap_implicit_conversion
{
    template <typename TypeT>
    constexpr operator TypeT() noexcept
    {
        static_assert(phi::false_t<TypeT>::value,
                      "trap_implicit_conversion::operator TypeT, must never be instantiated");

        return TypeT{};
    }
};

struct trap_comma
{
    template <typename TypeT>
    friend constexpr bool operator,(const trap_comma&, TypeT&&) noexcept
    {
        static_assert(phi::false_t<TypeT>::value,
                      "trap_comma::operator, must never be instantiated");

        return false;
    }

    template <typename TypeT>
    friend constexpr bool operator,(TypeT&&, const trap_comma&) noexcept
    {
        static_assert(phi::false_t<TypeT>::value,
                      "trap_comma::operator, must never be instantiated");

        return false;
    }
};

struct trap_call
{
    template <typename... ArgsT>
    constexpr bool operator()(ArgsT&&...) noexcept
    {
        static_assert(phi::false_t<ArgsT...>::value,
                      "trap_call::operator() must never be instantiated");

        return false;
    }
};

struct trap_self_assign
{
    trap_self_assign()                        = default;
    ~trap_self_assign()                       = default;
    trap_self_assign(const trap_self_assign&) = default;
    trap_self_assign(trap_self_assign&&)      = default;

    PHI_EXTENDED_CONSTEXPR trap_self_assign& operator=(const trap_self_assign& other) noexcept
    {
        PHI_UNUSED_PARAMETER(other);
        assert(&other != this);

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR trap_self_assign& operator=(trap_self_assign&& other) noexcept
    {
        PHI_UNUSED_PARAMETER(other);
        assert(&other != this);

        return *this;
    }
};

struct trap_deref
{
    template <typename TypeT>
    constexpr TypeT operator*() noexcept
    {
        static_assert(phi::false_t<TypeT>::value,
                      "trap_deref::operator*() must never be instantiated");
        return TypeT{};
    }

    template <typename TypeT>
    constexpr TypeT* operator->() noexcept
    {
        static_assert(phi::false_t<TypeT>::value,
                      "trap_deref::operator->() must never be instantiated");
        return TypeT{};
    }
};

struct trap_array_subscript
{
    template <typename TypeT>
    constexpr bool operator[](TypeT /*index*/) noexcept
    {
        static_assert(phi::false_t<TypeT>::value,
                      "trap_array_subscript::operator[] must never be instantiated");
        return false;
    }
};

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_UNITTEST_TEST_TYPES_HPP
