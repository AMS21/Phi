#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/add_lvalue_reference.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U = T&>
void test_add_lvalue_reference()
{
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<T>::type, U);
    CHECK_SAME_TYPE(const typename phi::add_lvalue_reference<T>::type, const U);
    CHECK_SAME_TYPE(volatile typename phi::add_lvalue_reference<T>::type, volatile U);
    CHECK_SAME_TYPE(const volatile typename phi::add_lvalue_reference<T>::type, const volatile U);

    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<T>, U);
    CHECK_SAME_TYPE(const phi::add_lvalue_reference_t<T>, const U);
    CHECK_SAME_TYPE(volatile phi::add_lvalue_reference_t<T>, volatile U);
    CHECK_SAME_TYPE(const volatile phi::add_lvalue_reference_t<T>, const volatile U);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<T>::type,
                    typename std::add_lvalue_reference<T>::type);
    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<T>, typename std::add_lvalue_reference<T>::type);
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<const T>::type,
                    typename std::add_lvalue_reference<const T>::type);
    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<const T>,
                    typename std::add_lvalue_reference<const T>::type);
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<volatile T>::type,
                    typename std::add_lvalue_reference<volatile T>::type);
    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<volatile T>,
                    typename std::add_lvalue_reference<volatile T>::type);
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<const volatile T>::type,
                    typename std::add_lvalue_reference<const volatile T>::type);
    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<const volatile T>,
                    typename std::add_lvalue_reference<const volatile T>::type);
}

template <typename F>
void test_add_lvalue_reference_function0()
{
    CHECK_SAME_TYPE(F&, typename phi::add_lvalue_reference<F>::type);
    CHECK_SAME_TYPE(F&, phi::add_lvalue_reference_t<F>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<F>::type,
                    typename std::add_lvalue_reference<F>::type);
    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<F>, typename std::add_lvalue_reference<F>::type);
}

template <typename F>
void test_add_lvalue_reference_function1()
{
    CHECK_SAME_TYPE(F, typename phi::add_lvalue_reference<F>::type);
    CHECK_SAME_TYPE(F, phi::add_lvalue_reference_t<F>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<F>::type,
                    typename std::add_lvalue_reference<F>::type);
    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<F>, typename std::add_lvalue_reference<F>::type);
}

struct A; // incomplete

struct Foo
{};

TEST_CASE("add_lvalue_reference")
{
    test_add_lvalue_reference<A, A&>();
    test_add_lvalue_reference<Foo, Foo&>();

    //  LWG 2101 specifically talks about add_lvalue_reference and functions.
    //  The term of art is "a referenceable type", which a cv- or ref-qualified function is not.
    test_add_lvalue_reference_function0<void()>();
    test_add_lvalue_reference_function1<void() const>();
    test_add_lvalue_reference_function1<void()&>();
    test_add_lvalue_reference_function1<void() &&>();
    test_add_lvalue_reference_function1<void() const&>();
    test_add_lvalue_reference_function1<void() const&&>();

    //  But a cv- or ref-qualified member function *is* "a referenceable type"
    test_add_lvalue_reference_function0<void (Foo::*)()>();
    test_add_lvalue_reference_function0<void (Foo::*)() const>();
    test_add_lvalue_reference_function0<void (Foo::*)()&>();
    test_add_lvalue_reference_function0<void (Foo::*)() &&>();
    test_add_lvalue_reference_function0<void (Foo::*)() const&>();
    test_add_lvalue_reference_function0<void (Foo::*)() const&&>();

    test_add_lvalue_reference<bool(int) const, bool(int) const>();
    test_add_lvalue_reference<bool(int)&, bool(int)&>();
    test_add_lvalue_reference<bool(int) const&, bool(int) const&>();
    test_add_lvalue_reference<bool(int)&&, bool(int) &&>();
    test_add_lvalue_reference<bool(int) const&&, bool(int) const&&>();
    test_add_lvalue_reference<bool(int)>();

    test_add_lvalue_reference<void, void>();
    test_add_lvalue_reference<phi::nullptr_t>();
    test_add_lvalue_reference<bool>();
    test_add_lvalue_reference<char>();
    test_add_lvalue_reference<signed char>();
    test_add_lvalue_reference<unsigned char>();
    test_add_lvalue_reference<short>();
    test_add_lvalue_reference<unsigned short>();
    test_add_lvalue_reference<int>();
    test_add_lvalue_reference<unsigned int>();
    test_add_lvalue_reference<long>();
    test_add_lvalue_reference<unsigned long>();
    test_add_lvalue_reference<long long>();
    test_add_lvalue_reference<unsigned long long>();
    test_add_lvalue_reference<float>();
    test_add_lvalue_reference<double>();
    test_add_lvalue_reference<long double>();
    test_add_lvalue_reference<char8_t>();
    test_add_lvalue_reference<char16_t>();
    test_add_lvalue_reference<char32_t>();
    test_add_lvalue_reference<wchar_t>();

    test_add_lvalue_reference<phi::boolean>();
    test_add_lvalue_reference<phi::integer<signed char>>();
    test_add_lvalue_reference<phi::integer<unsigned char>>();
    test_add_lvalue_reference<phi::integer<short>>();
    test_add_lvalue_reference<phi::integer<unsigned short>>();
    test_add_lvalue_reference<phi::integer<int>>();
    test_add_lvalue_reference<phi::integer<unsigned int>>();
    test_add_lvalue_reference<phi::integer<long>>();
    test_add_lvalue_reference<phi::integer<unsigned long>>();
    test_add_lvalue_reference<phi::integer<long long>>();
    test_add_lvalue_reference<phi::integer<unsigned long long>>();
    test_add_lvalue_reference<phi::floating_point<float>>();
    test_add_lvalue_reference<phi::floating_point<double>>();
    test_add_lvalue_reference<phi::floating_point<long double>>();

    test_add_lvalue_reference<std::vector<int>>();
    test_add_lvalue_reference<phi::scope_ptr<int>>();

    test_add_lvalue_reference<int&>();
    test_add_lvalue_reference<const int&>();
    test_add_lvalue_reference<volatile int&>();
    test_add_lvalue_reference<const volatile int&>();
    test_add_lvalue_reference<int&&>();
    test_add_lvalue_reference<const int&&>();
    test_add_lvalue_reference<volatile int&&>();
    test_add_lvalue_reference<const volatile int&&>();
    test_add_lvalue_reference<int*>();
    test_add_lvalue_reference<const int*>();
    test_add_lvalue_reference<volatile int*>();
    test_add_lvalue_reference<const volatile int*>();
    test_add_lvalue_reference<int**>();
    test_add_lvalue_reference<const int**>();
    test_add_lvalue_reference<volatile int**>();
    test_add_lvalue_reference<const volatile int**>();
    test_add_lvalue_reference<int*&>();
    test_add_lvalue_reference<const int*&>();
    test_add_lvalue_reference<volatile int*&>();
    test_add_lvalue_reference<const volatile int*&>();
    test_add_lvalue_reference<int*&&>();
    test_add_lvalue_reference<const int*&&>();
    test_add_lvalue_reference<volatile int*&&>();
    test_add_lvalue_reference<const volatile int*&&>();
    test_add_lvalue_reference<void*>();
    test_add_lvalue_reference<char[3]>();
    test_add_lvalue_reference<char[]>();
    test_add_lvalue_reference<char* [3]>();
    test_add_lvalue_reference<char*[]>();
    test_add_lvalue_reference<int(*)[3]>();
    test_add_lvalue_reference<int(*)[]>();
    test_add_lvalue_reference<int(&)[3]>();
    test_add_lvalue_reference<int(&)[]>();
    test_add_lvalue_reference<int(&&)[3]>();
    test_add_lvalue_reference<int(&&)[]>();
    test_add_lvalue_reference<char[3][2]>();
    test_add_lvalue_reference<char[][2]>();
    test_add_lvalue_reference<char* [3][2]>();
    test_add_lvalue_reference<char*[][2]>();
    test_add_lvalue_reference<int(*)[3][2]>();
    test_add_lvalue_reference<int(*)[][2]>();
    test_add_lvalue_reference<int(&)[3][2]>();
    test_add_lvalue_reference<int(&)[][2]>();
    test_add_lvalue_reference<int(&&)[3][2]>();
    test_add_lvalue_reference<int(&&)[][2]>();
    test_add_lvalue_reference<Class>();
    test_add_lvalue_reference<Class[]>();
    test_add_lvalue_reference<Class[2]>();
    test_add_lvalue_reference<Template<void>>();
    test_add_lvalue_reference<Template<int>>();
    test_add_lvalue_reference<Template<Class>>();
    test_add_lvalue_reference<Template<IncompleteType>>();
    test_add_lvalue_reference<VariadicTemplate<>>();
    test_add_lvalue_reference<VariadicTemplate<void>>();
    test_add_lvalue_reference<VariadicTemplate<int>>();
    test_add_lvalue_reference<VariadicTemplate<Class>>();
    test_add_lvalue_reference<VariadicTemplate<IncompleteType>>();
    test_add_lvalue_reference<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_add_lvalue_reference<PublicDerivedFromTemplate<Base>>();
    test_add_lvalue_reference<PublicDerivedFromTemplate<Derived>>();
    test_add_lvalue_reference<PublicDerivedFromTemplate<Class>>();
    test_add_lvalue_reference<PrivateDerivedFromTemplate<Base>>();
    test_add_lvalue_reference<PrivateDerivedFromTemplate<Derived>>();
    test_add_lvalue_reference<PrivateDerivedFromTemplate<Class>>();
    test_add_lvalue_reference<ProtectedDerivedFromTemplate<Base>>();
    test_add_lvalue_reference<ProtectedDerivedFromTemplate<Derived>>();
    test_add_lvalue_reference<ProtectedDerivedFromTemplate<Class>>();
    test_add_lvalue_reference<VirtualDerivedFromTemplate<Base>>();
    test_add_lvalue_reference<VirtualDerivedFromTemplate<Derived>>();
    test_add_lvalue_reference<VirtualDerivedFromTemplate<Class>>();
    test_add_lvalue_reference<Union>();
    test_add_lvalue_reference<NonEmptyUnion>();
    test_add_lvalue_reference<NonTrivialUnion>();
    test_add_lvalue_reference<Empty>();
    test_add_lvalue_reference<NotEmpty>();
    test_add_lvalue_reference<NonTrivial>();
    test_add_lvalue_reference<BitZero>();
    test_add_lvalue_reference<BitOne>();
    test_add_lvalue_reference<Base>();
    test_add_lvalue_reference<Derived>();
    test_add_lvalue_reference<NotEmptyBase>();
    test_add_lvalue_reference<EmptyBase>();
    test_add_lvalue_reference<VirtualBase>();
    test_add_lvalue_reference<Polymorphic>();
    test_add_lvalue_reference<DerivedPolymorphic>();
    test_add_lvalue_reference<Abstract>();
    test_add_lvalue_reference<PublicAbstract>();
    test_add_lvalue_reference<PrivateAbstract>();
    test_add_lvalue_reference<ProtectedAbstract>();
    test_add_lvalue_reference<AbstractTemplate<int>>();
    test_add_lvalue_reference<AbstractTemplate<double>>();
    test_add_lvalue_reference<AbstractTemplate<Class>>();
    test_add_lvalue_reference<AbstractTemplate<IncompleteType>>();
    test_add_lvalue_reference<PublicAbstractDeletedDestructor>();
    test_add_lvalue_reference<ProtectedAbstractDeletedDestructor>();
    test_add_lvalue_reference<PrivateAbstractDeletedDestructor>();
    test_add_lvalue_reference<Final>();
    test_add_lvalue_reference<FinalDerived>();
    test_add_lvalue_reference<PublicDestructor>();
    test_add_lvalue_reference<ProtectedDestructor>();
    test_add_lvalue_reference<PrivateDestructor>();
    test_add_lvalue_reference<VirtualPublicDestructor>();
    test_add_lvalue_reference<VirtualProtectedDestructor>();
    test_add_lvalue_reference<VirtualPrivateDestructor>();
    test_add_lvalue_reference<PurePublicDestructor>();
    test_add_lvalue_reference<PureProtectedDestructor>();
    test_add_lvalue_reference<PurePrivateDestructor>();
    test_add_lvalue_reference<DeletedPublicDestructor>();
    test_add_lvalue_reference<DeletedProtectedDestructor>();
    test_add_lvalue_reference<DeletedPrivateDestructor>();
    test_add_lvalue_reference<DeletedVirtualPublicDestructor>();
    test_add_lvalue_reference<DeletedVirtualProtectedDestructor>();
    test_add_lvalue_reference<DeletedVirtualPrivateDestructor>();
    test_add_lvalue_reference<ExplicitClass>();
    test_add_lvalue_reference<NothrowExplicitClass>();
    test_add_lvalue_reference<ThrowExplicitClass>();
    test_add_lvalue_reference<ThrowDefaultClass>();
    test_add_lvalue_reference<ThrowCopyConsClass>();
    test_add_lvalue_reference<ThrowMoveConsClass>();
    test_add_lvalue_reference<ThrowDestructor>();
    test_add_lvalue_reference<NoexceptExplicitClass>();
    test_add_lvalue_reference<ExceptExplicitClass>();
    test_add_lvalue_reference<NoexceptDefaultClass>();
    test_add_lvalue_reference<ExceptDefaultClass>();
    test_add_lvalue_reference<NoexceptCopyConsClass>();
    test_add_lvalue_reference<ExceptCopyConsClass>();
    test_add_lvalue_reference<NoexceptMoveConsClass>();
    test_add_lvalue_reference<ExceptMoveConsClass>();
    test_add_lvalue_reference<NoexceptCopyAssignClass>();
    test_add_lvalue_reference<ExceptCopyAssignClass>();
    test_add_lvalue_reference<NoexceptMoveAssignClass>();
    test_add_lvalue_reference<ExceptMoveAssignClass>();
    test_add_lvalue_reference<DeletedCopyAssignClass>();
    test_add_lvalue_reference<DeletedMoveAssignClass>();
    test_add_lvalue_reference<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_add_lvalue_reference<ExceptMoveConsNoexceptMoveAssignClass>();
    test_add_lvalue_reference<NoexceptMoveConsExceptMoveAssignClass>();
    test_add_lvalue_reference<ExceptMoveConsExceptMoveAssignClass>();
    test_add_lvalue_reference<ImplicitTo<int>>();
    test_add_lvalue_reference<ImplicitTo<float>>();
    test_add_lvalue_reference<ImplicitTo<Class>>();
    test_add_lvalue_reference<DeletedImplicitTo<int>>();
    test_add_lvalue_reference<DeletedImplicitTo<float>>();
    test_add_lvalue_reference<DeletedImplicitTo<Class>>();
    test_add_lvalue_reference<ExplicitTo<int>>();
    test_add_lvalue_reference<ExplicitTo<float>>();
    test_add_lvalue_reference<ExplicitTo<Class>>();
    test_add_lvalue_reference<DeletedExplicitTo<int>>();
    test_add_lvalue_reference<DeletedExplicitTo<float>>();
    test_add_lvalue_reference<DeletedExplicitTo<Class>>();
    test_add_lvalue_reference<Ellipsis>();
    test_add_lvalue_reference<DeletedEllipsis>();
    test_add_lvalue_reference<CopyConsOnlyType>();
    test_add_lvalue_reference<MoveConsOnlyType>();
    test_add_lvalue_reference<OverloadedOperators>();
    test_add_lvalue_reference<PublicIntMember>();
    test_add_lvalue_reference<ProtectedIntMember>();
    test_add_lvalue_reference<PrivateIntMember>();
    test_add_lvalue_reference<PublicStaticIntMember>();
    test_add_lvalue_reference<ProtectedStaticIntMember>();
    test_add_lvalue_reference<PrivateStaticIntMember>();
    test_add_lvalue_reference<PublicTemplateMember<int>>();
    test_add_lvalue_reference<PublicTemplateMember<float>>();
    test_add_lvalue_reference<PublicTemplateMember<Class>>();
    test_add_lvalue_reference<ProtectedTemplateMember<int>>();
    test_add_lvalue_reference<ProtectedTemplateMember<float>>();
    test_add_lvalue_reference<ProtectedTemplateMember<Class>>();
    test_add_lvalue_reference<PrivateTemplateMember<int>>();
    test_add_lvalue_reference<PrivateTemplateMember<float>>();
    test_add_lvalue_reference<PrivateTemplateMember<Class>>();
    test_add_lvalue_reference<PublicStaticTemplateMember<int>>();
    test_add_lvalue_reference<PublicStaticTemplateMember<float>>();
    test_add_lvalue_reference<PublicStaticTemplateMember<Class>>();
    test_add_lvalue_reference<ProtectedStaticTemplateMember<int>>();
    test_add_lvalue_reference<ProtectedStaticTemplateMember<float>>();
    test_add_lvalue_reference<ProtectedStaticTemplateMember<Class>>();
    test_add_lvalue_reference<PrivateStaticTemplateMember<int>>();
    test_add_lvalue_reference<PrivateStaticTemplateMember<float>>();
    test_add_lvalue_reference<PrivateStaticTemplateMember<Class>>();
    test_add_lvalue_reference<CannotInstantiate<int>>();
    test_add_lvalue_reference<CannotInstantiate<float>>();
    test_add_lvalue_reference<CannotInstantiate<Class>>();
    test_add_lvalue_reference<Enum>();
    test_add_lvalue_reference<EnumSigned>();
    test_add_lvalue_reference<EnumUnsigned>();
    test_add_lvalue_reference<EnumClass>();
    test_add_lvalue_reference<EnumStruct>();
    test_add_lvalue_reference<Function>();
    test_add_lvalue_reference<FunctionPtr>();
    test_add_lvalue_reference<MemberObjectPtr>();
    test_add_lvalue_reference<MemberFunctionPtr>();
    test_add_lvalue_reference<LambdaType>();
    test_add_lvalue_reference<LambdaNoexceptType>();
    test_add_lvalue_reference<LambdaThrowsType>();
    test_add_lvalue_reference<IncompleteType>();
    test_add_lvalue_reference<IncompleteTemplate<void>>();
    test_add_lvalue_reference<IncompleteTemplate<int>>();
    test_add_lvalue_reference<IncompleteTemplate<Class>>();
    test_add_lvalue_reference<IncompleteTemplate<IncompleteType>>();
    test_add_lvalue_reference<IncompleteVariadicTemplate<>>();
    test_add_lvalue_reference<IncompleteVariadicTemplate<void>>();
    test_add_lvalue_reference<IncompleteVariadicTemplate<int>>();
    test_add_lvalue_reference<IncompleteVariadicTemplate<Class>>();
    test_add_lvalue_reference<IncompleteVariadicTemplate<IncompleteType>>();
    test_add_lvalue_reference<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_add_lvalue_reference<IncompleteUnion>();
    test_add_lvalue_reference<IncompleteEnumSigned>();
    test_add_lvalue_reference<IncompleteEnumUnsigned>();
    test_add_lvalue_reference<IncompleteEnumClass>();
    test_add_lvalue_reference<IncompleteEnumStruct>();
    test_add_lvalue_reference<int Class::*>();
    test_add_lvalue_reference<float Class::*>();
    test_add_lvalue_reference<void * Class::*>();
    test_add_lvalue_reference<int * Class::*>();
    test_add_lvalue_reference<Enum Class::*>();
    test_add_lvalue_reference<NotEmpty Class::*>();
    test_add_lvalue_reference<int Class::*&>();
    test_add_lvalue_reference<float Class::*&>();
    test_add_lvalue_reference<void * Class::*&>();
    test_add_lvalue_reference<int * Class::*&>();
    test_add_lvalue_reference<Enum Class::*&>();
    test_add_lvalue_reference<NotEmpty Class::*&>();
    test_add_lvalue_reference<int Class::*&&>();
    test_add_lvalue_reference<float Class::*&&>();
    test_add_lvalue_reference<void * Class::*&&>();
    test_add_lvalue_reference<int * Class::*&&>();
    test_add_lvalue_reference<Enum Class::*&&>();
    test_add_lvalue_reference<NotEmpty Class::*&&>();
    test_add_lvalue_reference<NonDefaultConstructible>();
    test_add_lvalue_reference<NonCopyConstructible>();
    test_add_lvalue_reference<NonMoveConstructible>();
    test_add_lvalue_reference<NonCopyAssignable>();
    test_add_lvalue_reference<NonMoveAssignable>();
    test_add_lvalue_reference<NonAssignable>();
    test_add_lvalue_reference<NonCopyable>();
    test_add_lvalue_reference<NonMoveable>();
    test_add_lvalue_reference<NonConstructible>();
    test_add_lvalue_reference<NonDestructible>();
    test_add_lvalue_reference<Tracked>();
    test_add_lvalue_reference<TrapConstructible>();
    test_add_lvalue_reference<TrapImplicitConversion>();
    test_add_lvalue_reference<TrapComma>();
    test_add_lvalue_reference<TrapCall>();
    test_add_lvalue_reference<TrapSelfAssign>();
    test_add_lvalue_reference<TrapDeref>();
    test_add_lvalue_reference<TrapArraySubscript>();

    test_add_lvalue_reference<void()>();
    test_add_lvalue_reference_function1<void()&>();
    test_add_lvalue_reference_function1<void() &&>();
    test_add_lvalue_reference_function1<void() const>();
    test_add_lvalue_reference_function1<void() const&>();
    test_add_lvalue_reference_function1<void() const&&>();
    test_add_lvalue_reference_function1<void() volatile>();
    test_add_lvalue_reference_function1<void() volatile&>();
    test_add_lvalue_reference_function1<void() volatile&&>();
    test_add_lvalue_reference_function1<void() const volatile>();
    test_add_lvalue_reference_function1<void() const volatile&>();
    test_add_lvalue_reference_function1<void() const volatile&&>();
    test_add_lvalue_reference<void() noexcept>();
    test_add_lvalue_reference_function1<void()& noexcept>();
    test_add_lvalue_reference_function1<void()&& noexcept>();
    test_add_lvalue_reference_function1<void() const noexcept>();
    test_add_lvalue_reference_function1<void() const& noexcept>();
    test_add_lvalue_reference_function1<void() const&& noexcept>();
    test_add_lvalue_reference_function1<void() volatile noexcept>();
    test_add_lvalue_reference_function1<void() volatile& noexcept>();
    test_add_lvalue_reference_function1<void() volatile&& noexcept>();
    test_add_lvalue_reference_function1<void() const volatile noexcept>();
    test_add_lvalue_reference_function1<void() const volatile& noexcept>();
    test_add_lvalue_reference_function1<void() const volatile&& noexcept>();

    test_add_lvalue_reference<void(int)>();
    test_add_lvalue_reference_function1<void(int)&>();
    test_add_lvalue_reference_function1<void(int) &&>();
    test_add_lvalue_reference_function1<void(int) const>();
    test_add_lvalue_reference_function1<void(int) const&>();
    test_add_lvalue_reference_function1<void(int) const&&>();
    test_add_lvalue_reference_function1<void(int) volatile>();
    test_add_lvalue_reference_function1<void(int) volatile&>();
    test_add_lvalue_reference_function1<void(int) volatile&&>();
    test_add_lvalue_reference_function1<void(int) const volatile>();
    test_add_lvalue_reference_function1<void(int) const volatile&>();
    test_add_lvalue_reference_function1<void(int) const volatile&&>();
    test_add_lvalue_reference<void(int) noexcept>();
    test_add_lvalue_reference_function1<void(int)& noexcept>();
    test_add_lvalue_reference_function1<void(int)&& noexcept>();
    test_add_lvalue_reference_function1<void(int) const noexcept>();
    test_add_lvalue_reference_function1<void(int) const& noexcept>();
    test_add_lvalue_reference_function1<void(int) const&& noexcept>();
    test_add_lvalue_reference_function1<void(int) volatile noexcept>();
    test_add_lvalue_reference_function1<void(int) volatile& noexcept>();
    test_add_lvalue_reference_function1<void(int) volatile&& noexcept>();
    test_add_lvalue_reference_function1<void(int) const volatile noexcept>();
    test_add_lvalue_reference_function1<void(int) const volatile& noexcept>();
    test_add_lvalue_reference_function1<void(int) const volatile&& noexcept>();

    test_add_lvalue_reference<void(...)>();
    test_add_lvalue_reference_function1<void(...)&>();
    test_add_lvalue_reference_function1<void(...) &&>();
    test_add_lvalue_reference_function1<void(...) const>();
    test_add_lvalue_reference_function1<void(...) const&>();
    test_add_lvalue_reference_function1<void(...) const&&>();
    test_add_lvalue_reference_function1<void(...) volatile>();
    test_add_lvalue_reference_function1<void(...) volatile&>();
    test_add_lvalue_reference_function1<void(...) volatile&&>();
    test_add_lvalue_reference_function1<void(...) const volatile>();
    test_add_lvalue_reference_function1<void(...) const volatile&>();
    test_add_lvalue_reference_function1<void(...) const volatile&&>();
    test_add_lvalue_reference<void(...) noexcept>();
    test_add_lvalue_reference_function1<void(...)& noexcept>();
    test_add_lvalue_reference_function1<void(...)&& noexcept>();
    test_add_lvalue_reference_function1<void(...) const noexcept>();
    test_add_lvalue_reference_function1<void(...) const& noexcept>();
    test_add_lvalue_reference_function1<void(...) const&& noexcept>();
    test_add_lvalue_reference_function1<void(...) volatile noexcept>();
    test_add_lvalue_reference_function1<void(...) volatile& noexcept>();
    test_add_lvalue_reference_function1<void(...) volatile&& noexcept>();
    test_add_lvalue_reference_function1<void(...) const volatile noexcept>();
    test_add_lvalue_reference_function1<void(...) const volatile& noexcept>();
    test_add_lvalue_reference_function1<void(...) const volatile&& noexcept>();

    test_add_lvalue_reference<void(int, ...)>();
    test_add_lvalue_reference_function1<void(int, ...)&>();
    test_add_lvalue_reference_function1<void(int, ...) &&>();
    test_add_lvalue_reference_function1<void(int, ...) const>();
    test_add_lvalue_reference_function1<void(int, ...) const&>();
    test_add_lvalue_reference_function1<void(int, ...) const&&>();
    test_add_lvalue_reference_function1<void(int, ...) volatile>();
    test_add_lvalue_reference_function1<void(int, ...) volatile&>();
    test_add_lvalue_reference_function1<void(int, ...) volatile&&>();
    test_add_lvalue_reference_function1<void(int, ...) const volatile>();
    test_add_lvalue_reference_function1<void(int, ...) const volatile&>();
    test_add_lvalue_reference_function1<void(int, ...) const volatile&&>();
    test_add_lvalue_reference<void(int, ...) noexcept>();
    test_add_lvalue_reference_function1<void(int, ...)& noexcept>();
    test_add_lvalue_reference_function1<void(int, ...)&& noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) const noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) const& noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) const&& noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) volatile noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) volatile& noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) volatile&& noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) const volatile noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) const volatile& noexcept>();
    test_add_lvalue_reference_function1<void(int, ...) const volatile&& noexcept>();

    test_add_lvalue_reference<int()>();
    test_add_lvalue_reference_function1<int()&>();
    test_add_lvalue_reference_function1<int() &&>();
    test_add_lvalue_reference_function1<int() const>();
    test_add_lvalue_reference_function1<int() const&>();
    test_add_lvalue_reference_function1<int() const&&>();
    test_add_lvalue_reference_function1<int() volatile>();
    test_add_lvalue_reference_function1<int() volatile&>();
    test_add_lvalue_reference_function1<int() volatile&&>();
    test_add_lvalue_reference_function1<int() const volatile>();
    test_add_lvalue_reference_function1<int() const volatile&>();
    test_add_lvalue_reference_function1<int() const volatile&&>();
    test_add_lvalue_reference<int() noexcept>();
    test_add_lvalue_reference_function1<int()& noexcept>();
    test_add_lvalue_reference_function1<int()&& noexcept>();
    test_add_lvalue_reference_function1<int() const noexcept>();
    test_add_lvalue_reference_function1<int() const& noexcept>();
    test_add_lvalue_reference_function1<int() const&& noexcept>();
    test_add_lvalue_reference_function1<int() volatile noexcept>();
    test_add_lvalue_reference_function1<int() volatile& noexcept>();
    test_add_lvalue_reference_function1<int() volatile&& noexcept>();
    test_add_lvalue_reference_function1<int() const volatile noexcept>();
    test_add_lvalue_reference_function1<int() const volatile& noexcept>();
    test_add_lvalue_reference_function1<int() const volatile&& noexcept>();

    test_add_lvalue_reference<int(int)>();
    test_add_lvalue_reference_function1<int(int)&>();
    test_add_lvalue_reference_function1<int(int) &&>();
    test_add_lvalue_reference_function1<int(int) const>();
    test_add_lvalue_reference_function1<int(int) const&>();
    test_add_lvalue_reference_function1<int(int) const&&>();
    test_add_lvalue_reference_function1<int(int) volatile>();
    test_add_lvalue_reference_function1<int(int) volatile&>();
    test_add_lvalue_reference_function1<int(int) volatile&&>();
    test_add_lvalue_reference_function1<int(int) const volatile>();
    test_add_lvalue_reference_function1<int(int) const volatile&>();
    test_add_lvalue_reference_function1<int(int) const volatile&&>();
    test_add_lvalue_reference<int(int) noexcept>();
    test_add_lvalue_reference_function1<int(int)& noexcept>();
    test_add_lvalue_reference_function1<int(int)&& noexcept>();
    test_add_lvalue_reference_function1<int(int) const noexcept>();
    test_add_lvalue_reference_function1<int(int) const& noexcept>();
    test_add_lvalue_reference_function1<int(int) const&& noexcept>();
    test_add_lvalue_reference_function1<int(int) volatile noexcept>();
    test_add_lvalue_reference_function1<int(int) volatile& noexcept>();
    test_add_lvalue_reference_function1<int(int) volatile&& noexcept>();
    test_add_lvalue_reference_function1<int(int) const volatile noexcept>();
    test_add_lvalue_reference_function1<int(int) const volatile& noexcept>();
    test_add_lvalue_reference_function1<int(int) const volatile&& noexcept>();

    test_add_lvalue_reference<int(...)>();
    test_add_lvalue_reference_function1<int(...)&>();
    test_add_lvalue_reference_function1<int(...) &&>();
    test_add_lvalue_reference_function1<int(...) const>();
    test_add_lvalue_reference_function1<int(...) const&>();
    test_add_lvalue_reference_function1<int(...) const&&>();
    test_add_lvalue_reference_function1<int(...) volatile>();
    test_add_lvalue_reference_function1<int(...) volatile&>();
    test_add_lvalue_reference_function1<int(...) volatile&&>();
    test_add_lvalue_reference_function1<int(...) const volatile>();
    test_add_lvalue_reference_function1<int(...) const volatile&>();
    test_add_lvalue_reference_function1<int(...) const volatile&&>();
    test_add_lvalue_reference<int(...) noexcept>();
    test_add_lvalue_reference_function1<int(...)& noexcept>();
    test_add_lvalue_reference_function1<int(...)&& noexcept>();
    test_add_lvalue_reference_function1<int(...) const noexcept>();
    test_add_lvalue_reference_function1<int(...) const& noexcept>();
    test_add_lvalue_reference_function1<int(...) const&& noexcept>();
    test_add_lvalue_reference_function1<int(...) volatile noexcept>();
    test_add_lvalue_reference_function1<int(...) volatile& noexcept>();
    test_add_lvalue_reference_function1<int(...) volatile&& noexcept>();
    test_add_lvalue_reference_function1<int(...) const volatile noexcept>();
    test_add_lvalue_reference_function1<int(...) const volatile& noexcept>();
    test_add_lvalue_reference_function1<int(...) const volatile&& noexcept>();

    test_add_lvalue_reference<int(int, ...)>();
    test_add_lvalue_reference_function1<int(int, ...)&>();
    test_add_lvalue_reference_function1<int(int, ...) &&>();
    test_add_lvalue_reference_function1<int(int, ...) const>();
    test_add_lvalue_reference_function1<int(int, ...) const&>();
    test_add_lvalue_reference_function1<int(int, ...) const&&>();
    test_add_lvalue_reference_function1<int(int, ...) volatile>();
    test_add_lvalue_reference_function1<int(int, ...) volatile&>();
    test_add_lvalue_reference_function1<int(int, ...) volatile&&>();
    test_add_lvalue_reference_function1<int(int, ...) const volatile>();
    test_add_lvalue_reference_function1<int(int, ...) const volatile&>();
    test_add_lvalue_reference_function1<int(int, ...) const volatile&&>();
    test_add_lvalue_reference<int(int, ...) noexcept>();
    test_add_lvalue_reference_function1<int(int, ...)& noexcept>();
    test_add_lvalue_reference_function1<int(int, ...)&& noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) const noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) const& noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) const&& noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) volatile noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) volatile& noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) volatile&& noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) const volatile noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) const volatile& noexcept>();
    test_add_lvalue_reference_function1<int(int, ...) const volatile&& noexcept>();

    test_add_lvalue_reference<void (*)()>();
    test_add_lvalue_reference<void (*)() noexcept>();

    test_add_lvalue_reference<void (*)(int)>();
    test_add_lvalue_reference<void (*)(int) noexcept>();

    test_add_lvalue_reference<void (*)(...)>();
    test_add_lvalue_reference<void (*)(...) noexcept>();

    test_add_lvalue_reference<void (*)(int, ...)>();
    test_add_lvalue_reference<void (*)(int, ...) noexcept>();

    test_add_lvalue_reference<int (*)()>();
    test_add_lvalue_reference<int (*)() noexcept>();

    test_add_lvalue_reference<int (*)(int)>();
    test_add_lvalue_reference<int (*)(int) noexcept>();

    test_add_lvalue_reference<int (*)(...)>();
    test_add_lvalue_reference<int (*)(...) noexcept>();

    test_add_lvalue_reference<int (*)(int, ...)>();
    test_add_lvalue_reference<int (*)(int, ...) noexcept>();

    test_add_lvalue_reference<void (&)()>();
    test_add_lvalue_reference<void (&)() noexcept>();

    test_add_lvalue_reference<void (&)(int)>();
    test_add_lvalue_reference<void (&)(int) noexcept>();

    test_add_lvalue_reference<void (&)(...)>();
    test_add_lvalue_reference<void (&)(...) noexcept>();

    test_add_lvalue_reference<void (&)(int, ...)>();
    test_add_lvalue_reference<void (&)(int, ...) noexcept>();

    test_add_lvalue_reference<int (&)()>();
    test_add_lvalue_reference<int (&)() noexcept>();

    test_add_lvalue_reference<int (&)(int)>();
    test_add_lvalue_reference<int (&)(int) noexcept>();

    test_add_lvalue_reference<int (&)(...)>();
    test_add_lvalue_reference<int (&)(...) noexcept>();

    test_add_lvalue_reference<int (&)(int, ...)>();
    test_add_lvalue_reference<int (&)(int, ...) noexcept>();

    test_add_lvalue_reference<void(&&)()>();
    test_add_lvalue_reference<void(&&)() noexcept>();

    test_add_lvalue_reference<void(&&)(int)>();
    test_add_lvalue_reference<void(&&)(int) noexcept>();

    test_add_lvalue_reference<void(&&)(...)>();
    test_add_lvalue_reference<void(&&)(...) noexcept>();

    test_add_lvalue_reference<void(&&)(int, ...)>();
    test_add_lvalue_reference<void(&&)(int, ...) noexcept>();

    test_add_lvalue_reference<int(&&)()>();
    test_add_lvalue_reference<int(&&)() noexcept>();

    test_add_lvalue_reference<int(&&)(int)>();
    test_add_lvalue_reference<int(&&)(int) noexcept>();

    test_add_lvalue_reference<int(&&)(...)>();
    test_add_lvalue_reference<int(&&)(...) noexcept>();

    test_add_lvalue_reference<int(&&)(int, ...)>();
    test_add_lvalue_reference<int(&&)(int, ...) noexcept>();

    test_add_lvalue_reference<void (Class::*)()>();
    test_add_lvalue_reference<void (Class::*)()&>();
    test_add_lvalue_reference<void (Class::*)() &&>();
    test_add_lvalue_reference<void (Class::*)() const>();
    test_add_lvalue_reference<void (Class::*)() const&>();
    test_add_lvalue_reference<void (Class::*)() const&&>();
    test_add_lvalue_reference<void (Class::*)() noexcept>();
    test_add_lvalue_reference<void (Class::*)()& noexcept>();
    test_add_lvalue_reference<void (Class::*)()&& noexcept>();
    test_add_lvalue_reference<void (Class::*)() const noexcept>();
    test_add_lvalue_reference<void (Class::*)() const& noexcept>();
    test_add_lvalue_reference<void (Class::*)() const&& noexcept>();

    test_add_lvalue_reference<void (Class::*)(int)>();
    test_add_lvalue_reference<void (Class::*)(int)&>();
    test_add_lvalue_reference<void (Class::*)(int) &&>();
    test_add_lvalue_reference<void (Class::*)(int) const>();
    test_add_lvalue_reference<void (Class::*)(int) const&>();
    test_add_lvalue_reference<void (Class::*)(int) const&&>();
    test_add_lvalue_reference<void (Class::*)(int) noexcept>();
    test_add_lvalue_reference<void (Class::*)(int)& noexcept>();
    test_add_lvalue_reference<void (Class::*)(int)&& noexcept>();
    test_add_lvalue_reference<void (Class::*)(int) const noexcept>();
    test_add_lvalue_reference<void (Class::*)(int) const& noexcept>();
    test_add_lvalue_reference<void (Class::*)(int) const&& noexcept>();

    test_add_lvalue_reference<void (Class::*)(...)>();
    test_add_lvalue_reference<void (Class::*)(...)&>();
    test_add_lvalue_reference<void (Class::*)(...) &&>();
    test_add_lvalue_reference<void (Class::*)(...) const>();
    test_add_lvalue_reference<void (Class::*)(...) const&>();
    test_add_lvalue_reference<void (Class::*)(...) const&&>();
    test_add_lvalue_reference<void (Class::*)(...) noexcept>();
    test_add_lvalue_reference<void (Class::*)(...)& noexcept>();
    test_add_lvalue_reference<void (Class::*)(...)&& noexcept>();
    test_add_lvalue_reference<void (Class::*)(...) const noexcept>();
    test_add_lvalue_reference<void (Class::*)(...) const& noexcept>();
    test_add_lvalue_reference<void (Class::*)(...) const&& noexcept>();

    test_add_lvalue_reference<void (Class::*)(int, ...)>();
    test_add_lvalue_reference<void (Class::*)(int, ...)&>();
    test_add_lvalue_reference<void (Class::*)(int, ...) &&>();
    test_add_lvalue_reference<void (Class::*)(int, ...) const>();
    test_add_lvalue_reference<void (Class::*)(int, ...) const&>();
    test_add_lvalue_reference<void (Class::*)(int, ...) const&&>();
    test_add_lvalue_reference<void (Class::*)(int, ...) noexcept>();
    test_add_lvalue_reference<void (Class::*)(int, ...)& noexcept>();
    test_add_lvalue_reference<void (Class::*)(int, ...)&& noexcept>();
    test_add_lvalue_reference<void (Class::*)(int, ...) const noexcept>();
    test_add_lvalue_reference<void (Class::*)(int, ...) const& noexcept>();
    test_add_lvalue_reference<void (Class::*)(int, ...) const&& noexcept>();

    test_add_lvalue_reference<int (Class::*)()>();
    test_add_lvalue_reference<int (Class::*)()&>();
    test_add_lvalue_reference<int (Class::*)() &&>();
    test_add_lvalue_reference<int (Class::*)() const>();
    test_add_lvalue_reference<int (Class::*)() const&>();
    test_add_lvalue_reference<int (Class::*)() const&&>();
    test_add_lvalue_reference<int (Class::*)() noexcept>();
    test_add_lvalue_reference<int (Class::*)()& noexcept>();
    test_add_lvalue_reference<int (Class::*)()&& noexcept>();
    test_add_lvalue_reference<int (Class::*)() const noexcept>();
    test_add_lvalue_reference<int (Class::*)() const& noexcept>();
    test_add_lvalue_reference<int (Class::*)() const&& noexcept>();

    test_add_lvalue_reference<int (Class::*)(int)>();
    test_add_lvalue_reference<int (Class::*)(int)&>();
    test_add_lvalue_reference<int (Class::*)(int) &&>();
    test_add_lvalue_reference<int (Class::*)(int) const>();
    test_add_lvalue_reference<int (Class::*)(int) const&>();
    test_add_lvalue_reference<int (Class::*)(int) const&&>();
    test_add_lvalue_reference<int (Class::*)(int) noexcept>();
    test_add_lvalue_reference<int (Class::*)(int)& noexcept>();
    test_add_lvalue_reference<int (Class::*)(int)&& noexcept>();
    test_add_lvalue_reference<int (Class::*)(int) const noexcept>();
    test_add_lvalue_reference<int (Class::*)(int) const& noexcept>();
    test_add_lvalue_reference<int (Class::*)(int) const&& noexcept>();

    test_add_lvalue_reference<int (Class::*)(...)>();
    test_add_lvalue_reference<int (Class::*)(...)&>();
    test_add_lvalue_reference<int (Class::*)(...) &&>();
    test_add_lvalue_reference<int (Class::*)(...) const>();
    test_add_lvalue_reference<int (Class::*)(...) const&>();
    test_add_lvalue_reference<int (Class::*)(...) const&&>();
    test_add_lvalue_reference<int (Class::*)(...) noexcept>();
    test_add_lvalue_reference<int (Class::*)(...)& noexcept>();
    test_add_lvalue_reference<int (Class::*)(...)&& noexcept>();
    test_add_lvalue_reference<int (Class::*)(...) const noexcept>();
    test_add_lvalue_reference<int (Class::*)(...) const& noexcept>();
    test_add_lvalue_reference<int (Class::*)(...) const&& noexcept>();

    test_add_lvalue_reference<int (Class::*)(int, ...)>();
    test_add_lvalue_reference<int (Class::*)(int, ...)&>();
    test_add_lvalue_reference<int (Class::*)(int, ...) &&>();
    test_add_lvalue_reference<int (Class::*)(int, ...) const>();
    test_add_lvalue_reference<int (Class::*)(int, ...) const&>();
    test_add_lvalue_reference<int (Class::*)(int, ...) const&&>();
    test_add_lvalue_reference<int (Class::*)(int, ...) noexcept>();
    test_add_lvalue_reference<int (Class::*)(int, ...)& noexcept>();
    test_add_lvalue_reference<int (Class::*)(int, ...)&& noexcept>();
    test_add_lvalue_reference<int (Class::*)(int, ...) const noexcept>();
    test_add_lvalue_reference<int (Class::*)(int, ...) const& noexcept>();
    test_add_lvalue_reference<int (Class::*)(int, ...) const&& noexcept>();
}
