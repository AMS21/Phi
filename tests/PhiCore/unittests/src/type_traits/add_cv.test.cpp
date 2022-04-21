#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/add_cv.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_add_cv_impl()
{
    CHECK_SAME_TYPE(typename phi::add_cv<T>::type, U);
    CHECK_SAME_TYPE(phi::add_cv_t<T>, U);
    CHECK_SAME_TYPE(typename phi::add_cv<T>::type, phi::add_cv_t<T>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::add_cv<T>::type, U);
    CHECK_SAME_TYPE(typename phi::add_cv<T>::type, typename std::add_cv<T>::type);
    CHECK_SAME_TYPE(phi::add_cv_t<T>, typename std::add_cv<T>::type);
}

template <typename T>
void test_add_cv()
{
    test_add_cv_impl<T, const volatile T>();
    test_add_cv_impl<const T, const volatile T>();
    test_add_cv_impl<volatile T, const volatile T>();
    test_add_cv_impl<const volatile T, const volatile T>();
}

TEST_CASE("type_traits.add_cv")
{
    test_add_cv<void>();
    test_add_cv<phi::nullptr_t>();
    test_add_cv<bool>();
    test_add_cv<char>();
    test_add_cv<signed char>();
    test_add_cv<unsigned char>();
    test_add_cv<short>();
    test_add_cv<unsigned short>();
    test_add_cv<int>();
    test_add_cv<unsigned int>();
    test_add_cv<long>();
    test_add_cv<unsigned long>();
    test_add_cv<long long>();
    test_add_cv<unsigned long long>();
    test_add_cv<float>();
    test_add_cv<double>();
    test_add_cv<long double>();
    test_add_cv<char8_t>();
    test_add_cv<char16_t>();
    test_add_cv<char32_t>();
    test_add_cv<wchar_t>();

    test_add_cv<phi::boolean>();
    test_add_cv<phi::integer<signed char>>();
    test_add_cv<phi::integer<unsigned char>>();
    test_add_cv<phi::integer<short>>();
    test_add_cv<phi::integer<unsigned short>>();
    test_add_cv<phi::integer<int>>();
    test_add_cv<phi::integer<unsigned int>>();
    test_add_cv<phi::integer<long>>();
    test_add_cv<phi::integer<unsigned long>>();
    test_add_cv<phi::integer<long long>>();
    test_add_cv<phi::integer<unsigned long long>>();
    test_add_cv<phi::floating_point<float>>();
    test_add_cv<phi::floating_point<double>>();
    test_add_cv<phi::floating_point<long double>>();

    test_add_cv<std::vector<int>>();
    test_add_cv<phi::scope_ptr<int>>();

    test_add_cv<int&>();
    test_add_cv<const int&>();
    test_add_cv<volatile int&>();
    test_add_cv<const volatile int&>();
    test_add_cv<int&&>();
    test_add_cv<const int&&>();
    test_add_cv<volatile int&&>();
    test_add_cv<const volatile int&&>();
    test_add_cv<int*>();
    test_add_cv<const int*>();
    test_add_cv<volatile int*>();
    test_add_cv<const volatile int*>();
    test_add_cv<int**>();
    test_add_cv<const int**>();
    test_add_cv<volatile int**>();
    test_add_cv<const volatile int**>();
    test_add_cv<int*&>();
    test_add_cv<const int*&>();
    test_add_cv<volatile int*&>();
    test_add_cv<const volatile int*&>();
    test_add_cv<int*&&>();
    test_add_cv<const int*&&>();
    test_add_cv<volatile int*&&>();
    test_add_cv<const volatile int*&&>();
    test_add_cv<void*>();
    test_add_cv<char[3]>();
    test_add_cv<char[]>();
    test_add_cv<char* [3]>();
    test_add_cv<char*[]>();
    test_add_cv<int(*)[3]>();
    test_add_cv<int(*)[]>();
    test_add_cv<int(&)[3]>();
    test_add_cv<int(&)[]>();
    test_add_cv<int(&&)[3]>();
    test_add_cv<int(&&)[]>();
    test_add_cv<char[3][2]>();
    test_add_cv<char[][2]>();
    test_add_cv<char* [3][2]>();
    test_add_cv<char*[][2]>();
    test_add_cv<int(*)[3][2]>();
    test_add_cv<int(*)[][2]>();
    test_add_cv<int(&)[3][2]>();
    test_add_cv<int(&)[][2]>();
    test_add_cv<int(&&)[3][2]>();
    test_add_cv<int(&&)[][2]>();
    test_add_cv<Class>();
    test_add_cv<Class[]>();
    test_add_cv<Class[2]>();
    test_add_cv<Template<void>>();
    test_add_cv<Template<int>>();
    test_add_cv<Template<Class>>();
    test_add_cv<Template<IncompleteType>>();
    test_add_cv<VariadicTemplate<>>();
    test_add_cv<VariadicTemplate<void>>();
    test_add_cv<VariadicTemplate<int>>();
    test_add_cv<VariadicTemplate<Class>>();
    test_add_cv<VariadicTemplate<IncompleteType>>();
    test_add_cv<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_add_cv<PublicDerivedFromTemplate<Base>>();
    test_add_cv<PublicDerivedFromTemplate<Derived>>();
    test_add_cv<PublicDerivedFromTemplate<Class>>();
    test_add_cv<PrivateDerivedFromTemplate<Base>>();
    test_add_cv<PrivateDerivedFromTemplate<Derived>>();
    test_add_cv<PrivateDerivedFromTemplate<Class>>();
    test_add_cv<ProtectedDerivedFromTemplate<Base>>();
    test_add_cv<ProtectedDerivedFromTemplate<Derived>>();
    test_add_cv<ProtectedDerivedFromTemplate<Class>>();
    test_add_cv<VirtualDerivedFromTemplate<Base>>();
    test_add_cv<VirtualDerivedFromTemplate<Derived>>();
    test_add_cv<VirtualDerivedFromTemplate<Class>>();
    test_add_cv<Union>();
    test_add_cv<NonEmptyUnion>();
    test_add_cv<NonTrivialUnion>();
    test_add_cv<Empty>();
    test_add_cv<NotEmpty>();
    test_add_cv<NonTrivial>();
    test_add_cv<BitZero>();
    test_add_cv<BitOne>();
    test_add_cv<Base>();
    test_add_cv<Derived>();
    test_add_cv<NotEmptyBase>();
    test_add_cv<EmptyBase>();
    test_add_cv<VirtualBase>();
    test_add_cv<Polymorphic>();
    test_add_cv<DerivedPolymorphic>();
    test_add_cv<Abstract>();
    test_add_cv<PublicAbstract>();
    test_add_cv<PrivateAbstract>();
    test_add_cv<ProtectedAbstract>();
    test_add_cv<AbstractTemplate<int>>();
    test_add_cv<AbstractTemplate<double>>();
    test_add_cv<AbstractTemplate<Class>>();
    test_add_cv<AbstractTemplate<IncompleteType>>();
    test_add_cv<PublicAbstractDeletedDestructor>();
    test_add_cv<ProtectedAbstractDeletedDestructor>();
    test_add_cv<PrivateAbstractDeletedDestructor>();
    test_add_cv<Final>();
    test_add_cv<FinalDerived>();
    test_add_cv<PublicDestructor>();
    test_add_cv<ProtectedDestructor>();
    test_add_cv<PrivateDestructor>();
    test_add_cv<VirtualPublicDestructor>();
    test_add_cv<VirtualProtectedDestructor>();
    test_add_cv<VirtualPrivateDestructor>();
    test_add_cv<PurePublicDestructor>();
    test_add_cv<PureProtectedDestructor>();
    test_add_cv<PurePrivateDestructor>();
    test_add_cv<DeletedPublicDestructor>();
    test_add_cv<DeletedProtectedDestructor>();
    test_add_cv<DeletedPrivateDestructor>();
    test_add_cv<DeletedVirtualPublicDestructor>();
    test_add_cv<DeletedVirtualProtectedDestructor>();
    test_add_cv<DeletedVirtualPrivateDestructor>();
    test_add_cv<ExplicitClass>();
    test_add_cv<NothrowExplicitClass>();
    test_add_cv<ThrowExplicitClass>();
    test_add_cv<ThrowDefaultClass>();
    test_add_cv<ThrowCopyConsClass>();
    test_add_cv<ThrowMoveConsClass>();
    test_add_cv<ThrowDestructor>();
    test_add_cv<NoexceptExplicitClass>();
    test_add_cv<ExceptExplicitClass>();
    test_add_cv<NoexceptDefaultClass>();
    test_add_cv<ExceptDefaultClass>();
    test_add_cv<NoexceptCopyConsClass>();
    test_add_cv<ExceptCopyConsClass>();
    test_add_cv<NoexceptMoveConsClass>();
    test_add_cv<ExceptMoveConsClass>();
    test_add_cv<NoexceptCopyAssignClass>();
    test_add_cv<ExceptCopyAssignClass>();
    test_add_cv<NoexceptMoveAssignClass>();
    test_add_cv<ExceptMoveAssignClass>();
    test_add_cv<DeletedCopyAssignClass>();
    test_add_cv<DeletedMoveAssignClass>();
    test_add_cv<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_add_cv<ExceptMoveConsNoexceptMoveAssignClass>();
    test_add_cv<NoexceptMoveConsExceptMoveAssignClass>();
    test_add_cv<ExceptMoveConsExceptMoveAssignClass>();
    test_add_cv<ImplicitTo<int>>();
    test_add_cv<ImplicitTo<float>>();
    test_add_cv<ImplicitTo<Class>>();
    test_add_cv<DeletedImplicitTo<int>>();
    test_add_cv<DeletedImplicitTo<float>>();
    test_add_cv<DeletedImplicitTo<Class>>();
    test_add_cv<ExplicitTo<int>>();
    test_add_cv<ExplicitTo<float>>();
    test_add_cv<ExplicitTo<Class>>();
    test_add_cv<DeletedExplicitTo<int>>();
    test_add_cv<DeletedExplicitTo<float>>();
    test_add_cv<DeletedExplicitTo<Class>>();
    test_add_cv<Ellipsis>();
    test_add_cv<DeletedEllipsis>();
    test_add_cv<CopyConsOnlyType>();
    test_add_cv<MoveConsOnlyType>();
    test_add_cv<OverloadedOperators>();
    test_add_cv<PublicIntMember>();
    test_add_cv<ProtectedIntMember>();
    test_add_cv<PrivateIntMember>();
    test_add_cv<PublicStaticIntMember>();
    test_add_cv<ProtectedStaticIntMember>();
    test_add_cv<PrivateStaticIntMember>();
    test_add_cv<PublicTemplateMember<int>>();
    test_add_cv<PublicTemplateMember<float>>();
    test_add_cv<PublicTemplateMember<Class>>();
    test_add_cv<ProtectedTemplateMember<int>>();
    test_add_cv<ProtectedTemplateMember<float>>();
    test_add_cv<ProtectedTemplateMember<Class>>();
    test_add_cv<PrivateTemplateMember<int>>();
    test_add_cv<PrivateTemplateMember<float>>();
    test_add_cv<PrivateTemplateMember<Class>>();
    test_add_cv<PublicStaticTemplateMember<int>>();
    test_add_cv<PublicStaticTemplateMember<float>>();
    test_add_cv<PublicStaticTemplateMember<Class>>();
    test_add_cv<ProtectedStaticTemplateMember<int>>();
    test_add_cv<ProtectedStaticTemplateMember<float>>();
    test_add_cv<ProtectedStaticTemplateMember<Class>>();
    test_add_cv<PrivateStaticTemplateMember<int>>();
    test_add_cv<PrivateStaticTemplateMember<float>>();
    test_add_cv<PrivateStaticTemplateMember<Class>>();
    test_add_cv<CannotInstantiate<int>>();
    test_add_cv<CannotInstantiate<float>>();
    test_add_cv<CannotInstantiate<Class>>();
    test_add_cv<natural_alignment>();
    test_add_cv<Enum>();
    test_add_cv<EnumSigned>();
    test_add_cv<EnumUnsigned>();
    test_add_cv<EnumClass>();
    test_add_cv<EnumStruct>();
    test_add_cv<Function>();
    test_add_cv<FunctionPtr>();
    test_add_cv<MemberObjectPtr>();
    test_add_cv<MemberFunctionPtr>();
    test_add_cv<LambdaType>();
    test_add_cv<LambdaNoexceptType>();
    test_add_cv<LambdaThrowsType>();
    test_add_cv<IncompleteType>();
    test_add_cv<IncompleteTemplate<void>>();
    test_add_cv<IncompleteTemplate<int>>();
    test_add_cv<IncompleteTemplate<Class>>();
    test_add_cv<IncompleteTemplate<IncompleteType>>();
    test_add_cv<IncompleteVariadicTemplate<>>();
    test_add_cv<IncompleteVariadicTemplate<void>>();
    test_add_cv<IncompleteVariadicTemplate<int>>();
    test_add_cv<IncompleteVariadicTemplate<Class>>();
    test_add_cv<IncompleteVariadicTemplate<IncompleteType>>();
    test_add_cv<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_add_cv<IncompleteUnion>();
    test_add_cv<IncompleteEnumSigned>();
    test_add_cv<IncompleteEnumUnsigned>();
    test_add_cv<IncompleteEnumClass>();
    test_add_cv<IncompleteEnumStruct>();
    test_add_cv<int Class::*>();
    test_add_cv<float Class::*>();
    test_add_cv<void * Class::*>();
    test_add_cv<int * Class::*>();
    test_add_cv<Enum Class::*>();
    test_add_cv<NotEmpty Class::*>();
    test_add_cv<int Class::*&>();
    test_add_cv<float Class::*&>();
    test_add_cv<void * Class::*&>();
    test_add_cv<int * Class::*&>();
    test_add_cv<Enum Class::*&>();
    test_add_cv<NotEmpty Class::*&>();
    test_add_cv<int Class::*&&>();
    test_add_cv<float Class::*&&>();
    test_add_cv<void * Class::*&&>();
    test_add_cv<int * Class::*&&>();
    test_add_cv<Enum Class::*&&>();
    test_add_cv<NotEmpty Class::*&&>();
    test_add_cv<NonDefaultConstructible>();
    test_add_cv<NonCopyConstructible>();
    test_add_cv<NonMoveConstructible>();
    test_add_cv<NonCopyAssignable>();
    test_add_cv<NonMoveAssignable>();
    test_add_cv<NonAssignable>();
    test_add_cv<NonCopyable>();
    test_add_cv<NonMoveable>();
    test_add_cv<NonConstructible>();
    test_add_cv<NonDestructible>();
    test_add_cv<Tracked>();
    test_add_cv<TrapConstructible>();
    test_add_cv<TrapImplicitConversion>();
    test_add_cv<TrapComma>();
    test_add_cv<TrapCall>();
    test_add_cv<TrapSelfAssign>();
    test_add_cv<TrapDeref>();
    test_add_cv<TrapArraySubscript>();

    test_add_cv<void()>();
    test_add_cv<void()&>();
    test_add_cv<void() &&>();
    test_add_cv<void() const>();
    test_add_cv<void() const&>();
    test_add_cv<void() const&&>();
    test_add_cv<void() volatile>();
    test_add_cv<void() volatile&>();
    test_add_cv<void() volatile&&>();
    test_add_cv<void() const volatile>();
    test_add_cv<void() const volatile&>();
    test_add_cv<void() const volatile&&>();
    test_add_cv<void() noexcept>();
    test_add_cv<void()& noexcept>();
    test_add_cv<void()&& noexcept>();
    test_add_cv<void() const noexcept>();
    test_add_cv<void() const& noexcept>();
    test_add_cv<void() const&& noexcept>();
    test_add_cv<void() volatile noexcept>();
    test_add_cv<void() volatile& noexcept>();
    test_add_cv<void() volatile&& noexcept>();
    test_add_cv<void() const volatile noexcept>();
    test_add_cv<void() const volatile& noexcept>();
    test_add_cv<void() const volatile&& noexcept>();

    test_add_cv<void(int)>();
    test_add_cv<void(int)&>();
    test_add_cv<void(int) &&>();
    test_add_cv<void(int) const>();
    test_add_cv<void(int) const&>();
    test_add_cv<void(int) const&&>();
    test_add_cv<void(int) volatile>();
    test_add_cv<void(int) volatile&>();
    test_add_cv<void(int) volatile&&>();
    test_add_cv<void(int) const volatile>();
    test_add_cv<void(int) const volatile&>();
    test_add_cv<void(int) const volatile&&>();
    test_add_cv<void(int) noexcept>();
    test_add_cv<void(int)& noexcept>();
    test_add_cv<void(int)&& noexcept>();
    test_add_cv<void(int) const noexcept>();
    test_add_cv<void(int) const& noexcept>();
    test_add_cv<void(int) const&& noexcept>();
    test_add_cv<void(int) volatile noexcept>();
    test_add_cv<void(int) volatile& noexcept>();
    test_add_cv<void(int) volatile&& noexcept>();
    test_add_cv<void(int) const volatile noexcept>();
    test_add_cv<void(int) const volatile& noexcept>();
    test_add_cv<void(int) const volatile&& noexcept>();

    test_add_cv<void(...)>();
    test_add_cv<void(...)&>();
    test_add_cv<void(...) &&>();
    test_add_cv<void(...) const>();
    test_add_cv<void(...) const&>();
    test_add_cv<void(...) const&&>();
    test_add_cv<void(...) volatile>();
    test_add_cv<void(...) volatile&>();
    test_add_cv<void(...) volatile&&>();
    test_add_cv<void(...) const volatile>();
    test_add_cv<void(...) const volatile&>();
    test_add_cv<void(...) const volatile&&>();
    test_add_cv<void(...) noexcept>();
    test_add_cv<void(...)& noexcept>();
    test_add_cv<void(...)&& noexcept>();
    test_add_cv<void(...) const noexcept>();
    test_add_cv<void(...) const& noexcept>();
    test_add_cv<void(...) const&& noexcept>();
    test_add_cv<void(...) volatile noexcept>();
    test_add_cv<void(...) volatile& noexcept>();
    test_add_cv<void(...) volatile&& noexcept>();
    test_add_cv<void(...) const volatile noexcept>();
    test_add_cv<void(...) const volatile& noexcept>();
    test_add_cv<void(...) const volatile&& noexcept>();

    test_add_cv<void(int, ...)>();
    test_add_cv<void(int, ...)&>();
    test_add_cv<void(int, ...) &&>();
    test_add_cv<void(int, ...) const>();
    test_add_cv<void(int, ...) const&>();
    test_add_cv<void(int, ...) const&&>();
    test_add_cv<void(int, ...) volatile>();
    test_add_cv<void(int, ...) volatile&>();
    test_add_cv<void(int, ...) volatile&&>();
    test_add_cv<void(int, ...) const volatile>();
    test_add_cv<void(int, ...) const volatile&>();
    test_add_cv<void(int, ...) const volatile&&>();
    test_add_cv<void(int, ...) noexcept>();
    test_add_cv<void(int, ...)& noexcept>();
    test_add_cv<void(int, ...)&& noexcept>();
    test_add_cv<void(int, ...) const noexcept>();
    test_add_cv<void(int, ...) const& noexcept>();
    test_add_cv<void(int, ...) const&& noexcept>();
    test_add_cv<void(int, ...) volatile noexcept>();
    test_add_cv<void(int, ...) volatile& noexcept>();
    test_add_cv<void(int, ...) volatile&& noexcept>();
    test_add_cv<void(int, ...) const volatile noexcept>();
    test_add_cv<void(int, ...) const volatile& noexcept>();
    test_add_cv<void(int, ...) const volatile&& noexcept>();

    test_add_cv<int()>();
    test_add_cv<int()&>();
    test_add_cv<int() &&>();
    test_add_cv<int() const>();
    test_add_cv<int() const&>();
    test_add_cv<int() const&&>();
    test_add_cv<int() volatile>();
    test_add_cv<int() volatile&>();
    test_add_cv<int() volatile&&>();
    test_add_cv<int() const volatile>();
    test_add_cv<int() const volatile&>();
    test_add_cv<int() const volatile&&>();
    test_add_cv<int() noexcept>();
    test_add_cv<int()& noexcept>();
    test_add_cv<int()&& noexcept>();
    test_add_cv<int() const noexcept>();
    test_add_cv<int() const& noexcept>();
    test_add_cv<int() const&& noexcept>();
    test_add_cv<int() volatile noexcept>();
    test_add_cv<int() volatile& noexcept>();
    test_add_cv<int() volatile&& noexcept>();
    test_add_cv<int() const volatile noexcept>();
    test_add_cv<int() const volatile& noexcept>();
    test_add_cv<int() const volatile&& noexcept>();

    test_add_cv<int(int)>();
    test_add_cv<int(int)&>();
    test_add_cv<int(int) &&>();
    test_add_cv<int(int) const>();
    test_add_cv<int(int) const&>();
    test_add_cv<int(int) const&&>();
    test_add_cv<int(int) volatile>();
    test_add_cv<int(int) volatile&>();
    test_add_cv<int(int) volatile&&>();
    test_add_cv<int(int) const volatile>();
    test_add_cv<int(int) const volatile&>();
    test_add_cv<int(int) const volatile&&>();
    test_add_cv<int(int) noexcept>();
    test_add_cv<int(int)& noexcept>();
    test_add_cv<int(int)&& noexcept>();
    test_add_cv<int(int) const noexcept>();
    test_add_cv<int(int) const& noexcept>();
    test_add_cv<int(int) const&& noexcept>();
    test_add_cv<int(int) volatile noexcept>();
    test_add_cv<int(int) volatile& noexcept>();
    test_add_cv<int(int) volatile&& noexcept>();
    test_add_cv<int(int) const volatile noexcept>();
    test_add_cv<int(int) const volatile& noexcept>();
    test_add_cv<int(int) const volatile&& noexcept>();

    test_add_cv<int(...)>();
    test_add_cv<int(...)&>();
    test_add_cv<int(...) &&>();
    test_add_cv<int(...) const>();
    test_add_cv<int(...) const&>();
    test_add_cv<int(...) const&&>();
    test_add_cv<int(...) volatile>();
    test_add_cv<int(...) volatile&>();
    test_add_cv<int(...) volatile&&>();
    test_add_cv<int(...) const volatile>();
    test_add_cv<int(...) const volatile&>();
    test_add_cv<int(...) const volatile&&>();
    test_add_cv<int(...) noexcept>();
    test_add_cv<int(...)& noexcept>();
    test_add_cv<int(...)&& noexcept>();
    test_add_cv<int(...) const noexcept>();
    test_add_cv<int(...) const& noexcept>();
    test_add_cv<int(...) const&& noexcept>();
    test_add_cv<int(...) volatile noexcept>();
    test_add_cv<int(...) volatile& noexcept>();
    test_add_cv<int(...) volatile&& noexcept>();
    test_add_cv<int(...) const volatile noexcept>();
    test_add_cv<int(...) const volatile& noexcept>();
    test_add_cv<int(...) const volatile&& noexcept>();

    test_add_cv<int(int, ...)>();
    test_add_cv<int(int, ...)&>();
    test_add_cv<int(int, ...) &&>();
    test_add_cv<int(int, ...) const>();
    test_add_cv<int(int, ...) const&>();
    test_add_cv<int(int, ...) const&&>();
    test_add_cv<int(int, ...) volatile>();
    test_add_cv<int(int, ...) volatile&>();
    test_add_cv<int(int, ...) volatile&&>();
    test_add_cv<int(int, ...) const volatile>();
    test_add_cv<int(int, ...) const volatile&>();
    test_add_cv<int(int, ...) const volatile&&>();
    test_add_cv<int(int, ...) noexcept>();
    test_add_cv<int(int, ...)& noexcept>();
    test_add_cv<int(int, ...)&& noexcept>();
    test_add_cv<int(int, ...) const noexcept>();
    test_add_cv<int(int, ...) const& noexcept>();
    test_add_cv<int(int, ...) const&& noexcept>();
    test_add_cv<int(int, ...) volatile noexcept>();
    test_add_cv<int(int, ...) volatile& noexcept>();
    test_add_cv<int(int, ...) volatile&& noexcept>();
    test_add_cv<int(int, ...) const volatile noexcept>();
    test_add_cv<int(int, ...) const volatile& noexcept>();
    test_add_cv<int(int, ...) const volatile&& noexcept>();

    test_add_cv<void (*)()>();
    test_add_cv<void (*)() noexcept>();

    test_add_cv<void (*)(int)>();
    test_add_cv<void (*)(int) noexcept>();

    test_add_cv<void (*)(...)>();
    test_add_cv<void (*)(...) noexcept>();

    test_add_cv<void (*)(int, ...)>();
    test_add_cv<void (*)(int, ...) noexcept>();

    test_add_cv<int (*)()>();
    test_add_cv<int (*)() noexcept>();

    test_add_cv<int (*)(int)>();
    test_add_cv<int (*)(int) noexcept>();

    test_add_cv<int (*)(...)>();
    test_add_cv<int (*)(...) noexcept>();

    test_add_cv<int (*)(int, ...)>();
    test_add_cv<int (*)(int, ...) noexcept>();

    test_add_cv<void (&)()>();
    test_add_cv<void (&)() noexcept>();

    test_add_cv<void (&)(int)>();
    test_add_cv<void (&)(int) noexcept>();

    test_add_cv<void (&)(...)>();
    test_add_cv<void (&)(...) noexcept>();

    test_add_cv<void (&)(int, ...)>();
    test_add_cv<void (&)(int, ...) noexcept>();

    test_add_cv<int (&)()>();
    test_add_cv<int (&)() noexcept>();

    test_add_cv<int (&)(int)>();
    test_add_cv<int (&)(int) noexcept>();

    test_add_cv<int (&)(...)>();
    test_add_cv<int (&)(...) noexcept>();

    test_add_cv<int (&)(int, ...)>();
    test_add_cv<int (&)(int, ...) noexcept>();

    test_add_cv<void(&&)()>();
    test_add_cv<void(&&)() noexcept>();

    test_add_cv<void(&&)(int)>();
    test_add_cv<void(&&)(int) noexcept>();

    test_add_cv<void(&&)(...)>();
    test_add_cv<void(&&)(...) noexcept>();

    test_add_cv<void(&&)(int, ...)>();
    test_add_cv<void(&&)(int, ...) noexcept>();

    test_add_cv<int(&&)()>();
    test_add_cv<int(&&)() noexcept>();

    test_add_cv<int(&&)(int)>();
    test_add_cv<int(&&)(int) noexcept>();

    test_add_cv<int(&&)(...)>();
    test_add_cv<int(&&)(...) noexcept>();

    test_add_cv<int(&&)(int, ...)>();
    test_add_cv<int(&&)(int, ...) noexcept>();

    test_add_cv<void (Class::*)()>();
    test_add_cv<void (Class::*)()&>();
    test_add_cv<void (Class::*)() &&>();
    test_add_cv<void (Class::*)() const>();
    test_add_cv<void (Class::*)() const&>();
    test_add_cv<void (Class::*)() const&&>();
    test_add_cv<void (Class::*)() noexcept>();
    test_add_cv<void (Class::*)()& noexcept>();
    test_add_cv<void (Class::*)()&& noexcept>();
    test_add_cv<void (Class::*)() const noexcept>();
    test_add_cv<void (Class::*)() const& noexcept>();
    test_add_cv<void (Class::*)() const&& noexcept>();

    test_add_cv<void (Class::*)(int)>();
    test_add_cv<void (Class::*)(int)&>();
    test_add_cv<void (Class::*)(int) &&>();
    test_add_cv<void (Class::*)(int) const>();
    test_add_cv<void (Class::*)(int) const&>();
    test_add_cv<void (Class::*)(int) const&&>();
    test_add_cv<void (Class::*)(int) noexcept>();
    test_add_cv<void (Class::*)(int)& noexcept>();
    test_add_cv<void (Class::*)(int)&& noexcept>();
    test_add_cv<void (Class::*)(int) const noexcept>();
    test_add_cv<void (Class::*)(int) const& noexcept>();
    test_add_cv<void (Class::*)(int) const&& noexcept>();

    test_add_cv<void (Class::*)(...)>();
    test_add_cv<void (Class::*)(...)&>();
    test_add_cv<void (Class::*)(...) &&>();
    test_add_cv<void (Class::*)(...) const>();
    test_add_cv<void (Class::*)(...) const&>();
    test_add_cv<void (Class::*)(...) const&&>();
    test_add_cv<void (Class::*)(...) noexcept>();
    test_add_cv<void (Class::*)(...)& noexcept>();
    test_add_cv<void (Class::*)(...)&& noexcept>();
    test_add_cv<void (Class::*)(...) const noexcept>();
    test_add_cv<void (Class::*)(...) const& noexcept>();
    test_add_cv<void (Class::*)(...) const&& noexcept>();

    test_add_cv<void (Class::*)(int, ...)>();
    test_add_cv<void (Class::*)(int, ...)&>();
    test_add_cv<void (Class::*)(int, ...) &&>();
    test_add_cv<void (Class::*)(int, ...) const>();
    test_add_cv<void (Class::*)(int, ...) const&>();
    test_add_cv<void (Class::*)(int, ...) const&&>();
    test_add_cv<void (Class::*)(int, ...) noexcept>();
    test_add_cv<void (Class::*)(int, ...)& noexcept>();
    test_add_cv<void (Class::*)(int, ...)&& noexcept>();
    test_add_cv<void (Class::*)(int, ...) const noexcept>();
    test_add_cv<void (Class::*)(int, ...) const& noexcept>();
    test_add_cv<void (Class::*)(int, ...) const&& noexcept>();

    test_add_cv<int (Class::*)()>();
    test_add_cv<int (Class::*)()&>();
    test_add_cv<int (Class::*)() &&>();
    test_add_cv<int (Class::*)() const>();
    test_add_cv<int (Class::*)() const&>();
    test_add_cv<int (Class::*)() const&&>();
    test_add_cv<int (Class::*)() noexcept>();
    test_add_cv<int (Class::*)()& noexcept>();
    test_add_cv<int (Class::*)()&& noexcept>();
    test_add_cv<int (Class::*)() const noexcept>();
    test_add_cv<int (Class::*)() const& noexcept>();
    test_add_cv<int (Class::*)() const&& noexcept>();

    test_add_cv<int (Class::*)(int)>();
    test_add_cv<int (Class::*)(int)&>();
    test_add_cv<int (Class::*)(int) &&>();
    test_add_cv<int (Class::*)(int) const>();
    test_add_cv<int (Class::*)(int) const&>();
    test_add_cv<int (Class::*)(int) const&&>();
    test_add_cv<int (Class::*)(int) noexcept>();
    test_add_cv<int (Class::*)(int)& noexcept>();
    test_add_cv<int (Class::*)(int)&& noexcept>();
    test_add_cv<int (Class::*)(int) const noexcept>();
    test_add_cv<int (Class::*)(int) const& noexcept>();
    test_add_cv<int (Class::*)(int) const&& noexcept>();

    test_add_cv<int (Class::*)(...)>();
    test_add_cv<int (Class::*)(...)&>();
    test_add_cv<int (Class::*)(...) &&>();
    test_add_cv<int (Class::*)(...) const>();
    test_add_cv<int (Class::*)(...) const&>();
    test_add_cv<int (Class::*)(...) const&&>();
    test_add_cv<int (Class::*)(...) noexcept>();
    test_add_cv<int (Class::*)(...)& noexcept>();
    test_add_cv<int (Class::*)(...)&& noexcept>();
    test_add_cv<int (Class::*)(...) const noexcept>();
    test_add_cv<int (Class::*)(...) const& noexcept>();
    test_add_cv<int (Class::*)(...) const&& noexcept>();

    test_add_cv<int (Class::*)(int, ...)>();
    test_add_cv<int (Class::*)(int, ...)&>();
    test_add_cv<int (Class::*)(int, ...) &&>();
    test_add_cv<int (Class::*)(int, ...) const>();
    test_add_cv<int (Class::*)(int, ...) const&>();
    test_add_cv<int (Class::*)(int, ...) const&&>();
    test_add_cv<int (Class::*)(int, ...) noexcept>();
    test_add_cv<int (Class::*)(int, ...)& noexcept>();
    test_add_cv<int (Class::*)(int, ...)&& noexcept>();
    test_add_cv<int (Class::*)(int, ...) const noexcept>();
    test_add_cv<int (Class::*)(int, ...) const& noexcept>();
    test_add_cv<int (Class::*)(int, ...) const&& noexcept>();
}
