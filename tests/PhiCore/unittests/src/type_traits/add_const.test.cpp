#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/add_const.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_add_const_impl()
{
    CHECK_SAME_TYPE(typename phi::add_const<T>::type, U);
    CHECK_SAME_TYPE(phi::add_const_t<T>, U);

    CHECK_SAME_TYPE(typename phi::add_const<T>::type, phi::add_const_t<T>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::add_const<T>::type, U);
    CHECK_SAME_TYPE(typename phi::add_const<T>::type, typename std::add_const<T>::type);
    CHECK_SAME_TYPE(typename phi::add_const_t<T>, typename std::add_const<T>::type);
}

template <typename T>
void test_add_const()
{
    test_add_const_impl<T, const T>();
    test_add_const_impl<const T, const T>();
    test_add_const_impl<volatile T, const volatile T>();
    test_add_const_impl<const volatile T, const volatile T>();
}

TEST_CASE("type_traits.add_const")
{
    test_add_const<void>();
    test_add_const<phi::nullptr_t>();
    test_add_const<bool>();
    test_add_const<char>();
    test_add_const<signed char>();
    test_add_const<unsigned char>();
    test_add_const<short>();
    test_add_const<unsigned short>();
    test_add_const<int>();
    test_add_const<unsigned int>();
    test_add_const<long>();
    test_add_const<unsigned long>();
    test_add_const<long long>();
    test_add_const<unsigned long long>();
    test_add_const<float>();
    test_add_const<double>();
    test_add_const<long double>();
    test_add_const<char8_t>();
    test_add_const<char16_t>();
    test_add_const<char32_t>();
    test_add_const<wchar_t>();

    test_add_const<phi::boolean>();
    test_add_const<phi::integer<signed char>>();
    test_add_const<phi::integer<unsigned char>>();
    test_add_const<phi::integer<short>>();
    test_add_const<phi::integer<unsigned short>>();
    test_add_const<phi::integer<int>>();
    test_add_const<phi::integer<unsigned int>>();
    test_add_const<phi::integer<long>>();
    test_add_const<phi::integer<unsigned long>>();
    test_add_const<phi::integer<long long>>();
    test_add_const<phi::integer<unsigned long long>>();
    test_add_const<phi::floating_point<float>>();
    test_add_const<phi::floating_point<double>>();
    test_add_const<phi::floating_point<long double>>();

    test_add_const<std::vector<int>>();
    test_add_const<phi::scope_ptr<int>>();

    test_add_const<int&>();
    test_add_const<const int&>();
    test_add_const<volatile int&>();
    test_add_const<const volatile int&>();
    test_add_const<int&&>();
    test_add_const<const int&&>();
    test_add_const<volatile int&&>();
    test_add_const<const volatile int&&>();
    test_add_const<int*>();
    test_add_const<const int*>();
    test_add_const<volatile int*>();
    test_add_const<const volatile int*>();
    test_add_const<int**>();
    test_add_const<const int**>();
    test_add_const<volatile int**>();
    test_add_const<const volatile int**>();
    test_add_const<int*&>();
    test_add_const<const int*&>();
    test_add_const<volatile int*&>();
    test_add_const<const volatile int*&>();
    test_add_const<int*&&>();
    test_add_const<const int*&&>();
    test_add_const<volatile int*&&>();
    test_add_const<const volatile int*&&>();
    test_add_const<void*>();
    test_add_const<char[3]>();
    test_add_const<char[]>();
    test_add_const<char* [3]>();
    test_add_const<char*[]>();
    test_add_const<int(*)[3]>();
    test_add_const<int(*)[]>();
    test_add_const<int(&)[3]>();
    test_add_const<int(&)[]>();
    test_add_const<int(&&)[3]>();
    test_add_const<int(&&)[]>();
    test_add_const<char[3][2]>();
    test_add_const<char[][2]>();
    test_add_const<char* [3][2]>();
    test_add_const<char*[][2]>();
    test_add_const<int(*)[3][2]>();
    test_add_const<int(*)[][2]>();
    test_add_const<int(&)[3][2]>();
    test_add_const<int(&)[][2]>();
    test_add_const<int(&&)[3][2]>();
    test_add_const<int(&&)[][2]>();
    test_add_const<Class>();
    test_add_const<Class[]>();
    test_add_const<Class[2]>();
    test_add_const<Template<void>>();
    test_add_const<Template<int>>();
    test_add_const<Template<Class>>();
    test_add_const<Template<IncompleteType>>();
    test_add_const<VariadicTemplate<>>();
    test_add_const<VariadicTemplate<void>>();
    test_add_const<VariadicTemplate<int>>();
    test_add_const<VariadicTemplate<Class>>();
    test_add_const<VariadicTemplate<IncompleteType>>();
    test_add_const<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_add_const<PublicDerivedFromTemplate<Base>>();
    test_add_const<PublicDerivedFromTemplate<Derived>>();
    test_add_const<PublicDerivedFromTemplate<Class>>();
    test_add_const<PrivateDerivedFromTemplate<Base>>();
    test_add_const<PrivateDerivedFromTemplate<Derived>>();
    test_add_const<PrivateDerivedFromTemplate<Class>>();
    test_add_const<ProtectedDerivedFromTemplate<Base>>();
    test_add_const<ProtectedDerivedFromTemplate<Derived>>();
    test_add_const<ProtectedDerivedFromTemplate<Class>>();
    test_add_const<VirtualDerivedFromTemplate<Base>>();
    test_add_const<VirtualDerivedFromTemplate<Derived>>();
    test_add_const<VirtualDerivedFromTemplate<Class>>();
    test_add_const<Union>();
    test_add_const<NonEmptyUnion>();
    test_add_const<NonTrivialUnion>();
    test_add_const<Empty>();
    test_add_const<NotEmpty>();
    test_add_const<NonTrivial>();
    test_add_const<BitZero>();
    test_add_const<BitOne>();
    test_add_const<Base>();
    test_add_const<Derived>();
    test_add_const<NotEmptyBase>();
    test_add_const<EmptyBase>();
    test_add_const<VirtualBase>();
    test_add_const<Polymorphic>();
    test_add_const<DerivedPolymorphic>();
    test_add_const<Abstract>();
    test_add_const<PublicAbstract>();
    test_add_const<PrivateAbstract>();
    test_add_const<ProtectedAbstract>();
    test_add_const<AbstractTemplate<int>>();
    test_add_const<AbstractTemplate<double>>();
    test_add_const<AbstractTemplate<Class>>();
    test_add_const<AbstractTemplate<IncompleteType>>();
    test_add_const<PublicAbstractDeletedDestructor>();
    test_add_const<ProtectedAbstractDeletedDestructor>();
    test_add_const<PrivateAbstractDeletedDestructor>();
    test_add_const<Final>();
    test_add_const<FinalDerived>();
    test_add_const<PublicDestructor>();
    test_add_const<ProtectedDestructor>();
    test_add_const<PrivateDestructor>();
    test_add_const<VirtualPublicDestructor>();
    test_add_const<VirtualProtectedDestructor>();
    test_add_const<VirtualPrivateDestructor>();
    test_add_const<PurePublicDestructor>();
    test_add_const<PureProtectedDestructor>();
    test_add_const<PurePrivateDestructor>();
    test_add_const<DeletedPublicDestructor>();
    test_add_const<DeletedProtectedDestructor>();
    test_add_const<DeletedPrivateDestructor>();
    test_add_const<DeletedVirtualPublicDestructor>();
    test_add_const<DeletedVirtualProtectedDestructor>();
    test_add_const<DeletedVirtualPrivateDestructor>();
    test_add_const<ExplicitClass>();
    test_add_const<NothrowExplicitClass>();
    test_add_const<ThrowExplicitClass>();
    test_add_const<ThrowDefaultClass>();
    test_add_const<ThrowCopyConsClass>();
    test_add_const<ThrowMoveConsClass>();
    test_add_const<ThrowDestructor>();
    test_add_const<NoexceptExplicitClass>();
    test_add_const<ExceptExplicitClass>();
    test_add_const<NoexceptDefaultClass>();
    test_add_const<ExceptDefaultClass>();
    test_add_const<NoexceptCopyConsClass>();
    test_add_const<ExceptCopyConsClass>();
    test_add_const<NoexceptMoveConsClass>();
    test_add_const<ExceptMoveConsClass>();
    test_add_const<NoexceptCopyAssignClass>();
    test_add_const<ExceptCopyAssignClass>();
    test_add_const<NoexceptMoveAssignClass>();
    test_add_const<ExceptMoveAssignClass>();
    test_add_const<DeletedCopyAssignClass>();
    test_add_const<DeletedMoveAssignClass>();
    test_add_const<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_add_const<ExceptMoveConsNoexceptMoveAssignClass>();
    test_add_const<NoexceptMoveConsExceptMoveAssignClass>();
    test_add_const<ExceptMoveConsExceptMoveAssignClass>();
    test_add_const<ImplicitTo<int>>();
    test_add_const<ImplicitTo<float>>();
    test_add_const<ImplicitTo<Class>>();
    test_add_const<DeletedImplicitTo<int>>();
    test_add_const<DeletedImplicitTo<float>>();
    test_add_const<DeletedImplicitTo<Class>>();
    test_add_const<ExplicitTo<int>>();
    test_add_const<ExplicitTo<float>>();
    test_add_const<ExplicitTo<Class>>();
    test_add_const<DeletedExplicitTo<int>>();
    test_add_const<DeletedExplicitTo<float>>();
    test_add_const<DeletedExplicitTo<Class>>();
    test_add_const<Ellipsis>();
    test_add_const<DeletedEllipsis>();
    test_add_const<CopyConsOnlyType>();
    test_add_const<MoveConsOnlyType>();
    test_add_const<OverloadedOperators>();
    test_add_const<PublicIntMember>();
    test_add_const<ProtectedIntMember>();
    test_add_const<PrivateIntMember>();
    test_add_const<PublicStaticIntMember>();
    test_add_const<ProtectedStaticIntMember>();
    test_add_const<PrivateStaticIntMember>();
    test_add_const<PublicTemplateMember<int>>();
    test_add_const<PublicTemplateMember<float>>();
    test_add_const<PublicTemplateMember<Class>>();
    test_add_const<ProtectedTemplateMember<int>>();
    test_add_const<ProtectedTemplateMember<float>>();
    test_add_const<ProtectedTemplateMember<Class>>();
    test_add_const<PrivateTemplateMember<int>>();
    test_add_const<PrivateTemplateMember<float>>();
    test_add_const<PrivateTemplateMember<Class>>();
    test_add_const<PublicStaticTemplateMember<int>>();
    test_add_const<PublicStaticTemplateMember<float>>();
    test_add_const<PublicStaticTemplateMember<Class>>();
    test_add_const<ProtectedStaticTemplateMember<int>>();
    test_add_const<ProtectedStaticTemplateMember<float>>();
    test_add_const<ProtectedStaticTemplateMember<Class>>();
    test_add_const<PrivateStaticTemplateMember<int>>();
    test_add_const<PrivateStaticTemplateMember<float>>();
    test_add_const<PrivateStaticTemplateMember<Class>>();
    test_add_const<CannotInstantiate<int>>();
    test_add_const<CannotInstantiate<float>>();
    test_add_const<CannotInstantiate<Class>>();
    test_add_const<Enum>();
    test_add_const<EnumSigned>();
    test_add_const<EnumUnsigned>();
    test_add_const<EnumClass>();
    test_add_const<EnumStruct>();
    test_add_const<Function>();
    test_add_const<FunctionPtr>();
    test_add_const<MemberObjectPtr>();
    test_add_const<MemberFunctionPtr>();
    test_add_const<LambdaType>();
    test_add_const<LambdaNoexceptType>();
    test_add_const<LambdaThrowsType>();
    test_add_const<IncompleteType>();
    test_add_const<IncompleteTemplate<void>>();
    test_add_const<IncompleteTemplate<int>>();
    test_add_const<IncompleteTemplate<Class>>();
    test_add_const<IncompleteTemplate<IncompleteType>>();
    test_add_const<IncompleteVariadicTemplate<>>();
    test_add_const<IncompleteVariadicTemplate<void>>();
    test_add_const<IncompleteVariadicTemplate<int>>();
    test_add_const<IncompleteVariadicTemplate<Class>>();
    test_add_const<IncompleteVariadicTemplate<IncompleteType>>();
    test_add_const<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_add_const<IncompleteUnion>();
    test_add_const<IncompleteEnumSigned>();
    test_add_const<IncompleteEnumUnsigned>();
    test_add_const<IncompleteEnumClass>();
    test_add_const<IncompleteEnumStruct>();
    test_add_const<int Class::*>();
    test_add_const<float Class::*>();
    test_add_const<void * Class::*>();
    test_add_const<int * Class::*>();
    test_add_const<Enum Class::*>();
    test_add_const<NotEmpty Class::*>();
    test_add_const<int Class::*&>();
    test_add_const<float Class::*&>();
    test_add_const<void * Class::*&>();
    test_add_const<int * Class::*&>();
    test_add_const<Enum Class::*&>();
    test_add_const<NotEmpty Class::*&>();
    test_add_const<int Class::*&&>();
    test_add_const<float Class::*&&>();
    test_add_const<void * Class::*&&>();
    test_add_const<int * Class::*&&>();
    test_add_const<Enum Class::*&&>();
    test_add_const<NotEmpty Class::*&&>();
    test_add_const<NonDefaultConstructible>();
    test_add_const<NonCopyConstructible>();
    test_add_const<NonMoveConstructible>();
    test_add_const<NonCopyAssignable>();
    test_add_const<NonMoveAssignable>();
    test_add_const<NonAssignable>();
    test_add_const<NonCopyable>();
    test_add_const<NonMoveable>();
    test_add_const<NonConstructible>();
    test_add_const<NonDestructible>();
    test_add_const<Tracked>();
    test_add_const<TrapConstructible>();
    test_add_const<TrapImplicitConversion>();
    test_add_const<TrapComma>();
    test_add_const<TrapCall>();
    test_add_const<TrapSelfAssign>();
    test_add_const<TrapDeref>();
    test_add_const<TrapArraySubscript>();

    test_add_const<void()>();
    test_add_const<void()&>();
    test_add_const<void() &&>();
    test_add_const<void() const>();
    test_add_const<void() const&>();
    test_add_const<void() const&&>();
    test_add_const<void() volatile>();
    test_add_const<void() volatile&>();
    test_add_const<void() volatile&&>();
    test_add_const<void() const volatile>();
    test_add_const<void() const volatile&>();
    test_add_const<void() const volatile&&>();
    test_add_const<void() noexcept>();
    test_add_const<void()& noexcept>();
    test_add_const<void()&& noexcept>();
    test_add_const<void() const noexcept>();
    test_add_const<void() const& noexcept>();
    test_add_const<void() const&& noexcept>();
    test_add_const<void() volatile noexcept>();
    test_add_const<void() volatile& noexcept>();
    test_add_const<void() volatile&& noexcept>();
    test_add_const<void() const volatile noexcept>();
    test_add_const<void() const volatile& noexcept>();
    test_add_const<void() const volatile&& noexcept>();

    test_add_const<void(int)>();
    test_add_const<void(int)&>();
    test_add_const<void(int) &&>();
    test_add_const<void(int) const>();
    test_add_const<void(int) const&>();
    test_add_const<void(int) const&&>();
    test_add_const<void(int) volatile>();
    test_add_const<void(int) volatile&>();
    test_add_const<void(int) volatile&&>();
    test_add_const<void(int) const volatile>();
    test_add_const<void(int) const volatile&>();
    test_add_const<void(int) const volatile&&>();
    test_add_const<void(int) noexcept>();
    test_add_const<void(int)& noexcept>();
    test_add_const<void(int)&& noexcept>();
    test_add_const<void(int) const noexcept>();
    test_add_const<void(int) const& noexcept>();
    test_add_const<void(int) const&& noexcept>();
    test_add_const<void(int) volatile noexcept>();
    test_add_const<void(int) volatile& noexcept>();
    test_add_const<void(int) volatile&& noexcept>();
    test_add_const<void(int) const volatile noexcept>();
    test_add_const<void(int) const volatile& noexcept>();
    test_add_const<void(int) const volatile&& noexcept>();

    test_add_const<void(...)>();
    test_add_const<void(...)&>();
    test_add_const<void(...) &&>();
    test_add_const<void(...) const>();
    test_add_const<void(...) const&>();
    test_add_const<void(...) const&&>();
    test_add_const<void(...) volatile>();
    test_add_const<void(...) volatile&>();
    test_add_const<void(...) volatile&&>();
    test_add_const<void(...) const volatile>();
    test_add_const<void(...) const volatile&>();
    test_add_const<void(...) const volatile&&>();
    test_add_const<void(...) noexcept>();
    test_add_const<void(...)& noexcept>();
    test_add_const<void(...)&& noexcept>();
    test_add_const<void(...) const noexcept>();
    test_add_const<void(...) const& noexcept>();
    test_add_const<void(...) const&& noexcept>();
    test_add_const<void(...) volatile noexcept>();
    test_add_const<void(...) volatile& noexcept>();
    test_add_const<void(...) volatile&& noexcept>();
    test_add_const<void(...) const volatile noexcept>();
    test_add_const<void(...) const volatile& noexcept>();
    test_add_const<void(...) const volatile&& noexcept>();

    test_add_const<void(int, ...)>();
    test_add_const<void(int, ...)&>();
    test_add_const<void(int, ...) &&>();
    test_add_const<void(int, ...) const>();
    test_add_const<void(int, ...) const&>();
    test_add_const<void(int, ...) const&&>();
    test_add_const<void(int, ...) volatile>();
    test_add_const<void(int, ...) volatile&>();
    test_add_const<void(int, ...) volatile&&>();
    test_add_const<void(int, ...) const volatile>();
    test_add_const<void(int, ...) const volatile&>();
    test_add_const<void(int, ...) const volatile&&>();
    test_add_const<void(int, ...) noexcept>();
    test_add_const<void(int, ...)& noexcept>();
    test_add_const<void(int, ...)&& noexcept>();
    test_add_const<void(int, ...) const noexcept>();
    test_add_const<void(int, ...) const& noexcept>();
    test_add_const<void(int, ...) const&& noexcept>();
    test_add_const<void(int, ...) volatile noexcept>();
    test_add_const<void(int, ...) volatile& noexcept>();
    test_add_const<void(int, ...) volatile&& noexcept>();
    test_add_const<void(int, ...) const volatile noexcept>();
    test_add_const<void(int, ...) const volatile& noexcept>();
    test_add_const<void(int, ...) const volatile&& noexcept>();

    test_add_const<int()>();
    test_add_const<int()&>();
    test_add_const<int() &&>();
    test_add_const<int() const>();
    test_add_const<int() const&>();
    test_add_const<int() const&&>();
    test_add_const<int() volatile>();
    test_add_const<int() volatile&>();
    test_add_const<int() volatile&&>();
    test_add_const<int() const volatile>();
    test_add_const<int() const volatile&>();
    test_add_const<int() const volatile&&>();
    test_add_const<int() noexcept>();
    test_add_const<int()& noexcept>();
    test_add_const<int()&& noexcept>();
    test_add_const<int() const noexcept>();
    test_add_const<int() const& noexcept>();
    test_add_const<int() const&& noexcept>();
    test_add_const<int() volatile noexcept>();
    test_add_const<int() volatile& noexcept>();
    test_add_const<int() volatile&& noexcept>();
    test_add_const<int() const volatile noexcept>();
    test_add_const<int() const volatile& noexcept>();
    test_add_const<int() const volatile&& noexcept>();

    test_add_const<int(int)>();
    test_add_const<int(int)&>();
    test_add_const<int(int) &&>();
    test_add_const<int(int) const>();
    test_add_const<int(int) const&>();
    test_add_const<int(int) const&&>();
    test_add_const<int(int) volatile>();
    test_add_const<int(int) volatile&>();
    test_add_const<int(int) volatile&&>();
    test_add_const<int(int) const volatile>();
    test_add_const<int(int) const volatile&>();
    test_add_const<int(int) const volatile&&>();
    test_add_const<int(int) noexcept>();
    test_add_const<int(int)& noexcept>();
    test_add_const<int(int)&& noexcept>();
    test_add_const<int(int) const noexcept>();
    test_add_const<int(int) const& noexcept>();
    test_add_const<int(int) const&& noexcept>();
    test_add_const<int(int) volatile noexcept>();
    test_add_const<int(int) volatile& noexcept>();
    test_add_const<int(int) volatile&& noexcept>();
    test_add_const<int(int) const volatile noexcept>();
    test_add_const<int(int) const volatile& noexcept>();
    test_add_const<int(int) const volatile&& noexcept>();

    test_add_const<int(...)>();
    test_add_const<int(...)&>();
    test_add_const<int(...) &&>();
    test_add_const<int(...) const>();
    test_add_const<int(...) const&>();
    test_add_const<int(...) const&&>();
    test_add_const<int(...) volatile>();
    test_add_const<int(...) volatile&>();
    test_add_const<int(...) volatile&&>();
    test_add_const<int(...) const volatile>();
    test_add_const<int(...) const volatile&>();
    test_add_const<int(...) const volatile&&>();
    test_add_const<int(...) noexcept>();
    test_add_const<int(...)& noexcept>();
    test_add_const<int(...)&& noexcept>();
    test_add_const<int(...) const noexcept>();
    test_add_const<int(...) const& noexcept>();
    test_add_const<int(...) const&& noexcept>();
    test_add_const<int(...) volatile noexcept>();
    test_add_const<int(...) volatile& noexcept>();
    test_add_const<int(...) volatile&& noexcept>();
    test_add_const<int(...) const volatile noexcept>();
    test_add_const<int(...) const volatile& noexcept>();
    test_add_const<int(...) const volatile&& noexcept>();

    test_add_const<int(int, ...)>();
    test_add_const<int(int, ...)&>();
    test_add_const<int(int, ...) &&>();
    test_add_const<int(int, ...) const>();
    test_add_const<int(int, ...) const&>();
    test_add_const<int(int, ...) const&&>();
    test_add_const<int(int, ...) volatile>();
    test_add_const<int(int, ...) volatile&>();
    test_add_const<int(int, ...) volatile&&>();
    test_add_const<int(int, ...) const volatile>();
    test_add_const<int(int, ...) const volatile&>();
    test_add_const<int(int, ...) const volatile&&>();
    test_add_const<int(int, ...) noexcept>();
    test_add_const<int(int, ...)& noexcept>();
    test_add_const<int(int, ...)&& noexcept>();
    test_add_const<int(int, ...) const noexcept>();
    test_add_const<int(int, ...) const& noexcept>();
    test_add_const<int(int, ...) const&& noexcept>();
    test_add_const<int(int, ...) volatile noexcept>();
    test_add_const<int(int, ...) volatile& noexcept>();
    test_add_const<int(int, ...) volatile&& noexcept>();
    test_add_const<int(int, ...) const volatile noexcept>();
    test_add_const<int(int, ...) const volatile& noexcept>();
    test_add_const<int(int, ...) const volatile&& noexcept>();

    test_add_const<void (*)()>();
    test_add_const<void (*)() noexcept>();

    test_add_const<void (*)(int)>();
    test_add_const<void (*)(int) noexcept>();

    test_add_const<void (*)(...)>();
    test_add_const<void (*)(...) noexcept>();

    test_add_const<void (*)(int, ...)>();
    test_add_const<void (*)(int, ...) noexcept>();

    test_add_const<int (*)()>();
    test_add_const<int (*)() noexcept>();

    test_add_const<int (*)(int)>();
    test_add_const<int (*)(int) noexcept>();

    test_add_const<int (*)(...)>();
    test_add_const<int (*)(...) noexcept>();

    test_add_const<int (*)(int, ...)>();
    test_add_const<int (*)(int, ...) noexcept>();

    test_add_const<void (&)()>();
    test_add_const<void (&)() noexcept>();

    test_add_const<void (&)(int)>();
    test_add_const<void (&)(int) noexcept>();

    test_add_const<void (&)(...)>();
    test_add_const<void (&)(...) noexcept>();

    test_add_const<void (&)(int, ...)>();
    test_add_const<void (&)(int, ...) noexcept>();

    test_add_const<int (&)()>();
    test_add_const<int (&)() noexcept>();

    test_add_const<int (&)(int)>();
    test_add_const<int (&)(int) noexcept>();

    test_add_const<int (&)(...)>();
    test_add_const<int (&)(...) noexcept>();

    test_add_const<int (&)(int, ...)>();
    test_add_const<int (&)(int, ...) noexcept>();

    test_add_const<void(&&)()>();
    test_add_const<void(&&)() noexcept>();

    test_add_const<void(&&)(int)>();
    test_add_const<void(&&)(int) noexcept>();

    test_add_const<void(&&)(...)>();
    test_add_const<void(&&)(...) noexcept>();

    test_add_const<void(&&)(int, ...)>();
    test_add_const<void(&&)(int, ...) noexcept>();

    test_add_const<int(&&)()>();
    test_add_const<int(&&)() noexcept>();

    test_add_const<int(&&)(int)>();
    test_add_const<int(&&)(int) noexcept>();

    test_add_const<int(&&)(...)>();
    test_add_const<int(&&)(...) noexcept>();

    test_add_const<int(&&)(int, ...)>();
    test_add_const<int(&&)(int, ...) noexcept>();

    test_add_const<void (Class::*)()>();
    test_add_const<void (Class::*)()&>();
    test_add_const<void (Class::*)() &&>();
    test_add_const<void (Class::*)() const>();
    test_add_const<void (Class::*)() const&>();
    test_add_const<void (Class::*)() const&&>();
    test_add_const<void (Class::*)() noexcept>();
    test_add_const<void (Class::*)()& noexcept>();
    test_add_const<void (Class::*)()&& noexcept>();
    test_add_const<void (Class::*)() const noexcept>();
    test_add_const<void (Class::*)() const& noexcept>();
    test_add_const<void (Class::*)() const&& noexcept>();

    test_add_const<void (Class::*)(int)>();
    test_add_const<void (Class::*)(int)&>();
    test_add_const<void (Class::*)(int) &&>();
    test_add_const<void (Class::*)(int) const>();
    test_add_const<void (Class::*)(int) const&>();
    test_add_const<void (Class::*)(int) const&&>();
    test_add_const<void (Class::*)(int) noexcept>();
    test_add_const<void (Class::*)(int)& noexcept>();
    test_add_const<void (Class::*)(int)&& noexcept>();
    test_add_const<void (Class::*)(int) const noexcept>();
    test_add_const<void (Class::*)(int) const& noexcept>();
    test_add_const<void (Class::*)(int) const&& noexcept>();

    test_add_const<void (Class::*)(...)>();
    test_add_const<void (Class::*)(...)&>();
    test_add_const<void (Class::*)(...) &&>();
    test_add_const<void (Class::*)(...) const>();
    test_add_const<void (Class::*)(...) const&>();
    test_add_const<void (Class::*)(...) const&&>();
    test_add_const<void (Class::*)(...) noexcept>();
    test_add_const<void (Class::*)(...)& noexcept>();
    test_add_const<void (Class::*)(...)&& noexcept>();
    test_add_const<void (Class::*)(...) const noexcept>();
    test_add_const<void (Class::*)(...) const& noexcept>();
    test_add_const<void (Class::*)(...) const&& noexcept>();

    test_add_const<void (Class::*)(int, ...)>();
    test_add_const<void (Class::*)(int, ...)&>();
    test_add_const<void (Class::*)(int, ...) &&>();
    test_add_const<void (Class::*)(int, ...) const>();
    test_add_const<void (Class::*)(int, ...) const&>();
    test_add_const<void (Class::*)(int, ...) const&&>();
    test_add_const<void (Class::*)(int, ...) noexcept>();
    test_add_const<void (Class::*)(int, ...)& noexcept>();
    test_add_const<void (Class::*)(int, ...)&& noexcept>();
    test_add_const<void (Class::*)(int, ...) const noexcept>();
    test_add_const<void (Class::*)(int, ...) const& noexcept>();
    test_add_const<void (Class::*)(int, ...) const&& noexcept>();

    test_add_const<int (Class::*)()>();
    test_add_const<int (Class::*)()&>();
    test_add_const<int (Class::*)() &&>();
    test_add_const<int (Class::*)() const>();
    test_add_const<int (Class::*)() const&>();
    test_add_const<int (Class::*)() const&&>();
    test_add_const<int (Class::*)() noexcept>();
    test_add_const<int (Class::*)()& noexcept>();
    test_add_const<int (Class::*)()&& noexcept>();
    test_add_const<int (Class::*)() const noexcept>();
    test_add_const<int (Class::*)() const& noexcept>();
    test_add_const<int (Class::*)() const&& noexcept>();

    test_add_const<int (Class::*)(int)>();
    test_add_const<int (Class::*)(int)&>();
    test_add_const<int (Class::*)(int) &&>();
    test_add_const<int (Class::*)(int) const>();
    test_add_const<int (Class::*)(int) const&>();
    test_add_const<int (Class::*)(int) const&&>();
    test_add_const<int (Class::*)(int) noexcept>();
    test_add_const<int (Class::*)(int)& noexcept>();
    test_add_const<int (Class::*)(int)&& noexcept>();
    test_add_const<int (Class::*)(int) const noexcept>();
    test_add_const<int (Class::*)(int) const& noexcept>();
    test_add_const<int (Class::*)(int) const&& noexcept>();

    test_add_const<int (Class::*)(...)>();
    test_add_const<int (Class::*)(...)&>();
    test_add_const<int (Class::*)(...) &&>();
    test_add_const<int (Class::*)(...) const>();
    test_add_const<int (Class::*)(...) const&>();
    test_add_const<int (Class::*)(...) const&&>();
    test_add_const<int (Class::*)(...) noexcept>();
    test_add_const<int (Class::*)(...)& noexcept>();
    test_add_const<int (Class::*)(...)&& noexcept>();
    test_add_const<int (Class::*)(...) const noexcept>();
    test_add_const<int (Class::*)(...) const& noexcept>();
    test_add_const<int (Class::*)(...) const&& noexcept>();

    test_add_const<int (Class::*)(int, ...)>();
    test_add_const<int (Class::*)(int, ...)&>();
    test_add_const<int (Class::*)(int, ...) &&>();
    test_add_const<int (Class::*)(int, ...) const>();
    test_add_const<int (Class::*)(int, ...) const&>();
    test_add_const<int (Class::*)(int, ...) const&&>();
    test_add_const<int (Class::*)(int, ...) noexcept>();
    test_add_const<int (Class::*)(int, ...)& noexcept>();
    test_add_const<int (Class::*)(int, ...)&& noexcept>();
    test_add_const<int (Class::*)(int, ...) const noexcept>();
    test_add_const<int (Class::*)(int, ...) const& noexcept>();
    test_add_const<int (Class::*)(int, ...) const&& noexcept>();
}
