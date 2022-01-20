#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_safe_signed.hpp>
#include <vector>

template <typename T>
void test_is_safe_signed_impl()
{
    STATIC_REQUIRE(phi::is_safe_signed<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_signed<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_signed_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_signed_v<T>);
#endif
}

template <typename T>
void test_is_not_safe_signed_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_signed<T>::value);
    STATIC_REQUIRE(phi::is_not_safe_signed<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_signed_v<T>);
    STATIC_REQUIRE(phi::is_not_safe_signed_v<T>);
#endif
}

template <typename T>
void test_is_safe_signed()
{
    test_is_safe_signed_impl<T>();
    test_is_safe_signed_impl<const T>();
    test_is_safe_signed_impl<volatile T>();
    test_is_safe_signed_impl<const volatile T>();
}

template <typename T>
void test_is_not_safe_signed()
{
    test_is_not_safe_signed_impl<T>();
    test_is_not_safe_signed_impl<const T>();
    test_is_not_safe_signed_impl<volatile T>();
    test_is_not_safe_signed_impl<const volatile T>();
}

TEST_CASE("is_safe_signed")
{
    test_is_not_safe_signed<void>();
    test_is_not_safe_signed<phi::nullptr_t>();
    test_is_not_safe_signed<bool>();
    test_is_not_safe_signed<char>();
    test_is_not_safe_signed<signed char>();
    test_is_not_safe_signed<unsigned char>();
    test_is_not_safe_signed<short>();
    test_is_not_safe_signed<unsigned short>();
    test_is_not_safe_signed<int>();
    test_is_not_safe_signed<unsigned int>();
    test_is_not_safe_signed<long>();
    test_is_not_safe_signed<unsigned long>();
    test_is_not_safe_signed<long long>();
    test_is_not_safe_signed<unsigned long long>();
    test_is_not_safe_signed<float>();
    test_is_not_safe_signed<double>();
    test_is_not_safe_signed<long double>();
    test_is_not_safe_signed<char8_t>();
    test_is_not_safe_signed<char16_t>();
    test_is_not_safe_signed<char32_t>();
    test_is_not_safe_signed<wchar_t>();

    test_is_not_safe_signed<phi::boolean>();
    test_is_safe_signed<phi::integer<signed char>>();
    test_is_not_safe_signed<phi::integer<unsigned char>>();
    test_is_safe_signed<phi::integer<short>>();
    test_is_not_safe_signed<phi::integer<unsigned short>>();
    test_is_safe_signed<phi::integer<int>>();
    test_is_not_safe_signed<phi::integer<unsigned int>>();
    test_is_safe_signed<phi::integer<long>>();
    test_is_not_safe_signed<phi::integer<unsigned long>>();
    test_is_safe_signed<phi::integer<long long>>();
    test_is_not_safe_signed<phi::integer<unsigned long long>>();
    test_is_safe_signed<phi::floating_point<float>>();
    test_is_safe_signed<phi::floating_point<double>>();
    test_is_safe_signed<phi::floating_point<long double>>();

    test_is_not_safe_signed<std::vector<int>>();
    test_is_not_safe_signed<phi::scope_ptr<int>>();

    test_is_not_safe_signed<int&>();
    test_is_not_safe_signed<const int&>();
    test_is_not_safe_signed<volatile int&>();
    test_is_not_safe_signed<const volatile int&>();
    test_is_not_safe_signed<int&&>();
    test_is_not_safe_signed<const int&&>();
    test_is_not_safe_signed<volatile int&&>();
    test_is_not_safe_signed<const volatile int&&>();
    test_is_not_safe_signed<int*>();
    test_is_not_safe_signed<const int*>();
    test_is_not_safe_signed<volatile int*>();
    test_is_not_safe_signed<const volatile int*>();
    test_is_not_safe_signed<int**>();
    test_is_not_safe_signed<const int**>();
    test_is_not_safe_signed<volatile int**>();
    test_is_not_safe_signed<const volatile int**>();
    test_is_not_safe_signed<int*&>();
    test_is_not_safe_signed<const int*&>();
    test_is_not_safe_signed<volatile int*&>();
    test_is_not_safe_signed<const volatile int*&>();
    test_is_not_safe_signed<int*&&>();
    test_is_not_safe_signed<const int*&&>();
    test_is_not_safe_signed<volatile int*&&>();
    test_is_not_safe_signed<const volatile int*&&>();
    test_is_not_safe_signed<void*>();
    test_is_not_safe_signed<char[3]>();
    test_is_not_safe_signed<char[]>();
    test_is_not_safe_signed<char* [3]>();
    test_is_not_safe_signed<char*[]>();
    test_is_not_safe_signed<int(*)[3]>();
    test_is_not_safe_signed<int(*)[]>();
    test_is_not_safe_signed<int(&)[3]>();
    test_is_not_safe_signed<int(&)[]>();
    test_is_not_safe_signed<int(&&)[3]>();
    test_is_not_safe_signed<int(&&)[]>();
    test_is_not_safe_signed<char[3][2]>();
    test_is_not_safe_signed<char[][2]>();
    test_is_not_safe_signed<char* [3][2]>();
    test_is_not_safe_signed<char*[][2]>();
    test_is_not_safe_signed<int(*)[3][2]>();
    test_is_not_safe_signed<int(*)[][2]>();
    test_is_not_safe_signed<int(&)[3][2]>();
    test_is_not_safe_signed<int(&)[][2]>();
    test_is_not_safe_signed<int(&&)[3][2]>();
    test_is_not_safe_signed<int(&&)[][2]>();
    test_is_not_safe_signed<Class>();
    test_is_not_safe_signed<Class[]>();
    test_is_not_safe_signed<Class[2]>();
    test_is_not_safe_signed<Template<void>>();
    test_is_not_safe_signed<Template<int>>();
    test_is_not_safe_signed<Template<Class>>();
    test_is_not_safe_signed<Template<IncompleteType>>();
    test_is_not_safe_signed<VariadicTemplate<>>();
    test_is_not_safe_signed<VariadicTemplate<void>>();
    test_is_not_safe_signed<VariadicTemplate<int>>();
    test_is_not_safe_signed<VariadicTemplate<Class>>();
    test_is_not_safe_signed<VariadicTemplate<IncompleteType>>();
    test_is_not_safe_signed<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_signed<PublicDerivedFromTemplate<Base>>();
    test_is_not_safe_signed<PublicDerivedFromTemplate<Derived>>();
    test_is_not_safe_signed<PublicDerivedFromTemplate<Class>>();
    test_is_not_safe_signed<PrivateDerivedFromTemplate<Base>>();
    test_is_not_safe_signed<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_safe_signed<PrivateDerivedFromTemplate<Class>>();
    test_is_not_safe_signed<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_safe_signed<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_safe_signed<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_safe_signed<VirtualDerivedFromTemplate<Base>>();
    test_is_not_safe_signed<VirtualDerivedFromTemplate<Derived>>();
    test_is_not_safe_signed<VirtualDerivedFromTemplate<Class>>();
    test_is_not_safe_signed<Union>();
    test_is_not_safe_signed<NonEmptyUnion>();
    test_is_not_safe_signed<NonTrivialUnion>();
    test_is_not_safe_signed<Empty>();
    test_is_not_safe_signed<NotEmpty>();
    test_is_not_safe_signed<NonTrivial>();
    test_is_not_safe_signed<BitZero>();
    test_is_not_safe_signed<BitOne>();
    test_is_not_safe_signed<Base>();
    test_is_not_safe_signed<Derived>();
    test_is_not_safe_signed<Polymorphic>();
    test_is_not_safe_signed<DerivedPolymorphic>();
    test_is_not_safe_signed<Abstract>();
    test_is_not_safe_signed<PublicAbstract>();
    test_is_not_safe_signed<PrivateAbstract>();
    test_is_not_safe_signed<ProtectedAbstract>();
    test_is_not_safe_signed<AbstractTemplate<int>>();
    test_is_not_safe_signed<AbstractTemplate<double>>();
    test_is_not_safe_signed<AbstractTemplate<Class>>();
    test_is_not_safe_signed<AbstractTemplate<IncompleteType>>();
    test_is_not_safe_signed<PublicAbstractDeletedDestructor>();
    test_is_not_safe_signed<ProtectedAbstractDeletedDestructor>();
    test_is_not_safe_signed<PrivateAbstractDeletedDestructor>();
    test_is_not_safe_signed<Final>();
    test_is_not_safe_signed<FinalDerived>();
    test_is_not_safe_signed<PublicDestructor>();
    test_is_not_safe_signed<ProtectedDestructor>();
    test_is_not_safe_signed<PrivateDestructor>();
    test_is_not_safe_signed<VirtualPublicDestructor>();
    test_is_not_safe_signed<VirtualProtectedDestructor>();
    test_is_not_safe_signed<VirtualPrivateDestructor>();
    test_is_not_safe_signed<PurePublicDestructor>();
    test_is_not_safe_signed<PureProtectedDestructor>();
    test_is_not_safe_signed<PurePrivateDestructor>();
    test_is_not_safe_signed<DeletedPublicDestructor>();
    test_is_not_safe_signed<DeletedProtectedDestructor>();
    test_is_not_safe_signed<DeletedPrivateDestructor>();
    test_is_not_safe_signed<DeletedVirtualPublicDestructor>();
    test_is_not_safe_signed<DeletedVirtualProtectedDestructor>();
    test_is_not_safe_signed<DeletedVirtualPrivateDestructor>();
    test_is_not_safe_signed<ExplicitClass>();
    test_is_not_safe_signed<NothrowExplicitClass>();
    test_is_not_safe_signed<ThrowExplicitClass>();
    test_is_not_safe_signed<ThrowDefaultClass>();
    test_is_not_safe_signed<ThrowCopyConsClass>();
    test_is_not_safe_signed<ThrowMoveConsClass>();
    test_is_not_safe_signed<NoexceptExplicitClass>();
    test_is_not_safe_signed<ExceptExplicitClass>();
    test_is_not_safe_signed<NoexceptDefaultClass>();
    test_is_not_safe_signed<ExceptDefaultClass>();
    test_is_not_safe_signed<NoexceptCopyConsClass>();
    test_is_not_safe_signed<ExceptCopyConsClass>();
    test_is_not_safe_signed<NoexceptMoveConsClass>();
    test_is_not_safe_signed<ExceptMoveConsClass>();
    test_is_not_safe_signed<NoexceptCopyAssignClass>();
    test_is_not_safe_signed<ExceptCopyAssignClass>();
    test_is_not_safe_signed<NoexceptMoveAssignClass>();
    test_is_not_safe_signed<ExceptMoveAssignClass>();
    test_is_not_safe_signed<DeletedCopyAssignClass>();
    test_is_not_safe_signed<DeletedMoveAssignClass>();
    test_is_not_safe_signed<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_safe_signed<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_safe_signed<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_not_safe_signed<ExceptMoveConsExceptMoveAssignClass>();
    test_is_not_safe_signed<ImplicitTo<int>>();
    test_is_not_safe_signed<ImplicitTo<float>>();
    test_is_not_safe_signed<ImplicitTo<Class>>();
    test_is_not_safe_signed<DeletedImplicitTo<int>>();
    test_is_not_safe_signed<DeletedImplicitTo<float>>();
    test_is_not_safe_signed<DeletedImplicitTo<Class>>();
    test_is_not_safe_signed<ExplicitTo<int>>();
    test_is_not_safe_signed<ExplicitTo<float>>();
    test_is_not_safe_signed<ExplicitTo<Class>>();
    test_is_not_safe_signed<DeletedExplicitTo<int>>();
    test_is_not_safe_signed<DeletedExplicitTo<float>>();
    test_is_not_safe_signed<DeletedExplicitTo<Class>>();
    test_is_not_safe_signed<Ellipsis>();
    test_is_not_safe_signed<DeletedEllipsis>();
    test_is_not_safe_signed<CopyConsOnlyType>();
    test_is_not_safe_signed<MoveConsOnlyType>();
    test_is_not_safe_signed<OverloadedOperators>();
    test_is_not_safe_signed<PublicIntMember>();
    test_is_not_safe_signed<ProtectedIntMember>();
    test_is_not_safe_signed<PrivateIntMember>();
    test_is_not_safe_signed<PublicStaticIntMember>();
    test_is_not_safe_signed<ProtectedStaticIntMember>();
    test_is_not_safe_signed<PrivateStaticIntMember>();
    test_is_not_safe_signed<PublicTemplateMember<int>>();
    test_is_not_safe_signed<PublicTemplateMember<float>>();
    test_is_not_safe_signed<PublicTemplateMember<Class>>();
    test_is_not_safe_signed<ProtectedTemplateMember<int>>();
    test_is_not_safe_signed<ProtectedTemplateMember<float>>();
    test_is_not_safe_signed<ProtectedTemplateMember<Class>>();
    test_is_not_safe_signed<PrivateTemplateMember<int>>();
    test_is_not_safe_signed<PrivateTemplateMember<float>>();
    test_is_not_safe_signed<PrivateTemplateMember<Class>>();
    test_is_not_safe_signed<PublicStaticTemplateMember<int>>();
    test_is_not_safe_signed<PublicStaticTemplateMember<float>>();
    test_is_not_safe_signed<PublicStaticTemplateMember<Class>>();
    test_is_not_safe_signed<ProtectedStaticTemplateMember<int>>();
    test_is_not_safe_signed<ProtectedStaticTemplateMember<float>>();
    test_is_not_safe_signed<ProtectedStaticTemplateMember<Class>>();
    test_is_not_safe_signed<PrivateStaticTemplateMember<int>>();
    test_is_not_safe_signed<PrivateStaticTemplateMember<float>>();
    test_is_not_safe_signed<PrivateStaticTemplateMember<Class>>();
    test_is_not_safe_signed<Enum>();
    test_is_not_safe_signed<EnumSigned>();
    test_is_not_safe_signed<EnumUnsigned>();
    test_is_not_safe_signed<EnumClass>();
    test_is_not_safe_signed<EnumStruct>();
    test_is_not_safe_signed<Function>();
    test_is_not_safe_signed<FunctionPtr>();
    test_is_not_safe_signed<MemberObjectPtr>();
    test_is_not_safe_signed<MemberFunctionPtr>();
    test_is_not_safe_signed<LambdaType>();
    test_is_not_safe_signed<LambdaNoexceptType>();
    test_is_not_safe_signed<LambdaThrowsType>();
    test_is_not_safe_signed<IncompleteType>();
    test_is_not_safe_signed<IncompleteTemplate<void>>();
    test_is_not_safe_signed<IncompleteTemplate<int>>();
    test_is_not_safe_signed<IncompleteTemplate<Class>>();
    test_is_not_safe_signed<IncompleteTemplate<IncompleteType>>();
    test_is_not_safe_signed<IncompleteVariadicTemplate<>>();
    test_is_not_safe_signed<IncompleteVariadicTemplate<void>>();
    test_is_not_safe_signed<IncompleteVariadicTemplate<int>>();
    test_is_not_safe_signed<IncompleteVariadicTemplate<Class>>();
    test_is_not_safe_signed<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_safe_signed<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_signed<IncompleteUnion>();
    test_is_not_safe_signed<IncompleteEnumSigned>();
    test_is_not_safe_signed<IncompleteEnumUnsigned>();
    test_is_not_safe_signed<IncompleteEnumClass>();
    test_is_not_safe_signed<IncompleteEnumStruct>();
    test_is_not_safe_signed<int Class::*>();
    test_is_not_safe_signed<float Class::*>();
    test_is_not_safe_signed<void * Class::*>();
    test_is_not_safe_signed<int * Class::*>();
    test_is_not_safe_signed<int Class::*&>();
    test_is_not_safe_signed<float Class::*&>();
    test_is_not_safe_signed<void * Class::*&>();
    test_is_not_safe_signed<int * Class::*&>();
    test_is_not_safe_signed<int Class::*&&>();
    test_is_not_safe_signed<float Class::*&&>();
    test_is_not_safe_signed<void * Class::*&&>();
    test_is_not_safe_signed<int * Class::*&&>();
    test_is_not_safe_signed<int Class::*const>();
    test_is_not_safe_signed<float Class::*const>();
    test_is_not_safe_signed<void * Class::*const>();
    test_is_not_safe_signed<int Class::*const&>();
    test_is_not_safe_signed<float Class::*const&>();
    test_is_not_safe_signed<void * Class::*const&>();
    test_is_not_safe_signed<int Class::*const&&>();
    test_is_not_safe_signed<float Class::*const&&>();
    test_is_not_safe_signed<void * Class::*const&&>();
    test_is_not_safe_signed<int Class::*volatile>();
    test_is_not_safe_signed<float Class::*volatile>();
    test_is_not_safe_signed<void * Class::*volatile>();
    test_is_not_safe_signed<int Class::*volatile&>();
    test_is_not_safe_signed<float Class::*volatile&>();
    test_is_not_safe_signed<void * Class::*volatile&>();
    test_is_not_safe_signed<int Class::*volatile&&>();
    test_is_not_safe_signed<float Class::*volatile&&>();
    test_is_not_safe_signed<void * Class::*volatile&&>();
    test_is_not_safe_signed<int Class::*const volatile>();
    test_is_not_safe_signed<float Class::*const volatile>();
    test_is_not_safe_signed<void * Class::*const volatile>();
    test_is_not_safe_signed<int Class::*const volatile&>();
    test_is_not_safe_signed<float Class::*const volatile&>();
    test_is_not_safe_signed<void * Class::*const volatile&>();
    test_is_not_safe_signed<int Class::*const volatile&&>();
    test_is_not_safe_signed<float Class::*const volatile&&>();
    test_is_not_safe_signed<void * Class::*const volatile&&>();
    test_is_not_safe_signed<NonCopyable>();
    test_is_not_safe_signed<NonMoveable>();
    test_is_not_safe_signed<NonConstructible>();
    test_is_not_safe_signed<NonDestructible>();
    test_is_not_safe_signed<Tracked>();
    test_is_not_safe_signed<TrapConstructible>();
    test_is_not_safe_signed<TrapImplicitConversion>();
    test_is_not_safe_signed<TrapComma>();
    test_is_not_safe_signed<TrapCall>();
    test_is_not_safe_signed<TrapSelfAssign>();
    test_is_not_safe_signed<TrapDeref>();
    test_is_not_safe_signed<TrapArraySubscript>();

    test_is_not_safe_signed<void()>();
    test_is_not_safe_signed<void()&>();
    test_is_not_safe_signed<void() &&>();
    test_is_not_safe_signed<void() const>();
    test_is_not_safe_signed<void() const&>();
    test_is_not_safe_signed<void() const&&>();
    test_is_not_safe_signed<void() volatile>();
    test_is_not_safe_signed<void() volatile&>();
    test_is_not_safe_signed<void() volatile&&>();
    test_is_not_safe_signed<void() const volatile>();
    test_is_not_safe_signed<void() const volatile&>();
    test_is_not_safe_signed<void() const volatile&&>();
    test_is_not_safe_signed<void() noexcept>();
    test_is_not_safe_signed<void()& noexcept>();
    test_is_not_safe_signed<void()&& noexcept>();
    test_is_not_safe_signed<void() const noexcept>();
    test_is_not_safe_signed<void() const& noexcept>();
    test_is_not_safe_signed<void() const&& noexcept>();
    test_is_not_safe_signed<void() volatile noexcept>();
    test_is_not_safe_signed<void() volatile& noexcept>();
    test_is_not_safe_signed<void() volatile&& noexcept>();
    test_is_not_safe_signed<void() const volatile noexcept>();
    test_is_not_safe_signed<void() const volatile& noexcept>();
    test_is_not_safe_signed<void() const volatile&& noexcept>();

    test_is_not_safe_signed<void(int)>();
    test_is_not_safe_signed<void(int)&>();
    test_is_not_safe_signed<void(int) &&>();
    test_is_not_safe_signed<void(int) const>();
    test_is_not_safe_signed<void(int) const&>();
    test_is_not_safe_signed<void(int) const&&>();
    test_is_not_safe_signed<void(int) volatile>();
    test_is_not_safe_signed<void(int) volatile&>();
    test_is_not_safe_signed<void(int) volatile&&>();
    test_is_not_safe_signed<void(int) const volatile>();
    test_is_not_safe_signed<void(int) const volatile&>();
    test_is_not_safe_signed<void(int) const volatile&&>();
    test_is_not_safe_signed<void(int) noexcept>();
    test_is_not_safe_signed<void(int)& noexcept>();
    test_is_not_safe_signed<void(int)&& noexcept>();
    test_is_not_safe_signed<void(int) const noexcept>();
    test_is_not_safe_signed<void(int) const& noexcept>();
    test_is_not_safe_signed<void(int) const&& noexcept>();
    test_is_not_safe_signed<void(int) volatile noexcept>();
    test_is_not_safe_signed<void(int) volatile& noexcept>();
    test_is_not_safe_signed<void(int) volatile&& noexcept>();
    test_is_not_safe_signed<void(int) const volatile noexcept>();
    test_is_not_safe_signed<void(int) const volatile& noexcept>();
    test_is_not_safe_signed<void(int) const volatile&& noexcept>();

    test_is_not_safe_signed<void(...)>();
    test_is_not_safe_signed<void(...)&>();
    test_is_not_safe_signed<void(...) &&>();
    test_is_not_safe_signed<void(...) const>();
    test_is_not_safe_signed<void(...) const&>();
    test_is_not_safe_signed<void(...) const&&>();
    test_is_not_safe_signed<void(...) volatile>();
    test_is_not_safe_signed<void(...) volatile&>();
    test_is_not_safe_signed<void(...) volatile&&>();
    test_is_not_safe_signed<void(...) const volatile>();
    test_is_not_safe_signed<void(...) const volatile&>();
    test_is_not_safe_signed<void(...) const volatile&&>();
    test_is_not_safe_signed<void(...) noexcept>();
    test_is_not_safe_signed<void(...)& noexcept>();
    test_is_not_safe_signed<void(...)&& noexcept>();
    test_is_not_safe_signed<void(...) const noexcept>();
    test_is_not_safe_signed<void(...) const& noexcept>();
    test_is_not_safe_signed<void(...) const&& noexcept>();
    test_is_not_safe_signed<void(...) volatile noexcept>();
    test_is_not_safe_signed<void(...) volatile& noexcept>();
    test_is_not_safe_signed<void(...) volatile&& noexcept>();
    test_is_not_safe_signed<void(...) const volatile noexcept>();
    test_is_not_safe_signed<void(...) const volatile& noexcept>();
    test_is_not_safe_signed<void(...) const volatile&& noexcept>();

    test_is_not_safe_signed<void(int, ...)>();
    test_is_not_safe_signed<void(int, ...)&>();
    test_is_not_safe_signed<void(int, ...) &&>();
    test_is_not_safe_signed<void(int, ...) const>();
    test_is_not_safe_signed<void(int, ...) const&>();
    test_is_not_safe_signed<void(int, ...) const&&>();
    test_is_not_safe_signed<void(int, ...) volatile>();
    test_is_not_safe_signed<void(int, ...) volatile&>();
    test_is_not_safe_signed<void(int, ...) volatile&&>();
    test_is_not_safe_signed<void(int, ...) const volatile>();
    test_is_not_safe_signed<void(int, ...) const volatile&>();
    test_is_not_safe_signed<void(int, ...) const volatile&&>();
    test_is_not_safe_signed<void(int, ...) noexcept>();
    test_is_not_safe_signed<void(int, ...)& noexcept>();
    test_is_not_safe_signed<void(int, ...)&& noexcept>();
    test_is_not_safe_signed<void(int, ...) const noexcept>();
    test_is_not_safe_signed<void(int, ...) const& noexcept>();
    test_is_not_safe_signed<void(int, ...) const&& noexcept>();
    test_is_not_safe_signed<void(int, ...) volatile noexcept>();
    test_is_not_safe_signed<void(int, ...) volatile& noexcept>();
    test_is_not_safe_signed<void(int, ...) volatile&& noexcept>();
    test_is_not_safe_signed<void(int, ...) const volatile noexcept>();
    test_is_not_safe_signed<void(int, ...) const volatile& noexcept>();
    test_is_not_safe_signed<void(int, ...) const volatile&& noexcept>();

    test_is_not_safe_signed<int()>();
    test_is_not_safe_signed<int()&>();
    test_is_not_safe_signed<int() &&>();
    test_is_not_safe_signed<int() const>();
    test_is_not_safe_signed<int() const&>();
    test_is_not_safe_signed<int() const&&>();
    test_is_not_safe_signed<int() volatile>();
    test_is_not_safe_signed<int() volatile&>();
    test_is_not_safe_signed<int() volatile&&>();
    test_is_not_safe_signed<int() const volatile>();
    test_is_not_safe_signed<int() const volatile&>();
    test_is_not_safe_signed<int() const volatile&&>();
    test_is_not_safe_signed<int() noexcept>();
    test_is_not_safe_signed<int()& noexcept>();
    test_is_not_safe_signed<int()&& noexcept>();
    test_is_not_safe_signed<int() const noexcept>();
    test_is_not_safe_signed<int() const& noexcept>();
    test_is_not_safe_signed<int() const&& noexcept>();
    test_is_not_safe_signed<int() volatile noexcept>();
    test_is_not_safe_signed<int() volatile& noexcept>();
    test_is_not_safe_signed<int() volatile&& noexcept>();
    test_is_not_safe_signed<int() const volatile noexcept>();
    test_is_not_safe_signed<int() const volatile& noexcept>();
    test_is_not_safe_signed<int() const volatile&& noexcept>();

    test_is_not_safe_signed<int(int)>();
    test_is_not_safe_signed<int(int)&>();
    test_is_not_safe_signed<int(int) &&>();
    test_is_not_safe_signed<int(int) const>();
    test_is_not_safe_signed<int(int) const&>();
    test_is_not_safe_signed<int(int) const&&>();
    test_is_not_safe_signed<int(int) volatile>();
    test_is_not_safe_signed<int(int) volatile&>();
    test_is_not_safe_signed<int(int) volatile&&>();
    test_is_not_safe_signed<int(int) const volatile>();
    test_is_not_safe_signed<int(int) const volatile&>();
    test_is_not_safe_signed<int(int) const volatile&&>();
    test_is_not_safe_signed<int(int) noexcept>();
    test_is_not_safe_signed<int(int)& noexcept>();
    test_is_not_safe_signed<int(int)&& noexcept>();
    test_is_not_safe_signed<int(int) const noexcept>();
    test_is_not_safe_signed<int(int) const& noexcept>();
    test_is_not_safe_signed<int(int) const&& noexcept>();
    test_is_not_safe_signed<int(int) volatile noexcept>();
    test_is_not_safe_signed<int(int) volatile& noexcept>();
    test_is_not_safe_signed<int(int) volatile&& noexcept>();
    test_is_not_safe_signed<int(int) const volatile noexcept>();
    test_is_not_safe_signed<int(int) const volatile& noexcept>();
    test_is_not_safe_signed<int(int) const volatile&& noexcept>();

    test_is_not_safe_signed<int(...)>();
    test_is_not_safe_signed<int(...)&>();
    test_is_not_safe_signed<int(...) &&>();
    test_is_not_safe_signed<int(...) const>();
    test_is_not_safe_signed<int(...) const&>();
    test_is_not_safe_signed<int(...) const&&>();
    test_is_not_safe_signed<int(...) volatile>();
    test_is_not_safe_signed<int(...) volatile&>();
    test_is_not_safe_signed<int(...) volatile&&>();
    test_is_not_safe_signed<int(...) const volatile>();
    test_is_not_safe_signed<int(...) const volatile&>();
    test_is_not_safe_signed<int(...) const volatile&&>();
    test_is_not_safe_signed<int(...) noexcept>();
    test_is_not_safe_signed<int(...)& noexcept>();
    test_is_not_safe_signed<int(...)&& noexcept>();
    test_is_not_safe_signed<int(...) const noexcept>();
    test_is_not_safe_signed<int(...) const& noexcept>();
    test_is_not_safe_signed<int(...) const&& noexcept>();
    test_is_not_safe_signed<int(...) volatile noexcept>();
    test_is_not_safe_signed<int(...) volatile& noexcept>();
    test_is_not_safe_signed<int(...) volatile&& noexcept>();
    test_is_not_safe_signed<int(...) const volatile noexcept>();
    test_is_not_safe_signed<int(...) const volatile& noexcept>();
    test_is_not_safe_signed<int(...) const volatile&& noexcept>();

    test_is_not_safe_signed<int(int, ...)>();
    test_is_not_safe_signed<int(int, ...)&>();
    test_is_not_safe_signed<int(int, ...) &&>();
    test_is_not_safe_signed<int(int, ...) const>();
    test_is_not_safe_signed<int(int, ...) const&>();
    test_is_not_safe_signed<int(int, ...) const&&>();
    test_is_not_safe_signed<int(int, ...) volatile>();
    test_is_not_safe_signed<int(int, ...) volatile&>();
    test_is_not_safe_signed<int(int, ...) volatile&&>();
    test_is_not_safe_signed<int(int, ...) const volatile>();
    test_is_not_safe_signed<int(int, ...) const volatile&>();
    test_is_not_safe_signed<int(int, ...) const volatile&&>();
    test_is_not_safe_signed<int(int, ...) noexcept>();
    test_is_not_safe_signed<int(int, ...)& noexcept>();
    test_is_not_safe_signed<int(int, ...)&& noexcept>();
    test_is_not_safe_signed<int(int, ...) const noexcept>();
    test_is_not_safe_signed<int(int, ...) const& noexcept>();
    test_is_not_safe_signed<int(int, ...) const&& noexcept>();
    test_is_not_safe_signed<int(int, ...) volatile noexcept>();
    test_is_not_safe_signed<int(int, ...) volatile& noexcept>();
    test_is_not_safe_signed<int(int, ...) volatile&& noexcept>();
    test_is_not_safe_signed<int(int, ...) const volatile noexcept>();
    test_is_not_safe_signed<int(int, ...) const volatile& noexcept>();
    test_is_not_safe_signed<int(int, ...) const volatile&& noexcept>();

    test_is_not_safe_signed<void (*)()>();
    test_is_not_safe_signed<void (*)() noexcept>();

    test_is_not_safe_signed<void (*)(int)>();
    test_is_not_safe_signed<void (*)(int) noexcept>();

    test_is_not_safe_signed<void (*)(...)>();
    test_is_not_safe_signed<void (*)(...) noexcept>();

    test_is_not_safe_signed<void (*)(int, ...)>();
    test_is_not_safe_signed<void (*)(int, ...) noexcept>();

    test_is_not_safe_signed<int (*)()>();
    test_is_not_safe_signed<int (*)() noexcept>();

    test_is_not_safe_signed<int (*)(int)>();
    test_is_not_safe_signed<int (*)(int) noexcept>();

    test_is_not_safe_signed<int (*)(...)>();
    test_is_not_safe_signed<int (*)(...) noexcept>();

    test_is_not_safe_signed<int (*)(int, ...)>();
    test_is_not_safe_signed<int (*)(int, ...) noexcept>();

    test_is_not_safe_signed<void (&)()>();
    test_is_not_safe_signed<void (&)() noexcept>();

    test_is_not_safe_signed<void (&)(int)>();
    test_is_not_safe_signed<void (&)(int) noexcept>();

    test_is_not_safe_signed<void (&)(...)>();
    test_is_not_safe_signed<void (&)(...) noexcept>();

    test_is_not_safe_signed<void (&)(int, ...)>();
    test_is_not_safe_signed<void (&)(int, ...) noexcept>();

    test_is_not_safe_signed<int (&)()>();
    test_is_not_safe_signed<int (&)() noexcept>();

    test_is_not_safe_signed<int (&)(int)>();
    test_is_not_safe_signed<int (&)(int) noexcept>();

    test_is_not_safe_signed<int (&)(...)>();
    test_is_not_safe_signed<int (&)(...) noexcept>();

    test_is_not_safe_signed<int (&)(int, ...)>();
    test_is_not_safe_signed<int (&)(int, ...) noexcept>();

    test_is_not_safe_signed<void(&&)()>();
    test_is_not_safe_signed<void(&&)() noexcept>();

    test_is_not_safe_signed<void(&&)(int)>();
    test_is_not_safe_signed<void(&&)(int) noexcept>();

    test_is_not_safe_signed<void(&&)(...)>();
    test_is_not_safe_signed<void(&&)(...) noexcept>();

    test_is_not_safe_signed<void(&&)(int, ...)>();
    test_is_not_safe_signed<void(&&)(int, ...) noexcept>();

    test_is_not_safe_signed<int(&&)()>();
    test_is_not_safe_signed<int(&&)() noexcept>();

    test_is_not_safe_signed<int(&&)(int)>();
    test_is_not_safe_signed<int(&&)(int) noexcept>();

    test_is_not_safe_signed<int(&&)(...)>();
    test_is_not_safe_signed<int(&&)(...) noexcept>();

    test_is_not_safe_signed<int(&&)(int, ...)>();
    test_is_not_safe_signed<int(&&)(int, ...) noexcept>();

    test_is_not_safe_signed<void (Class::*)()>();
    test_is_not_safe_signed<void (Class::*)()&>();
    test_is_not_safe_signed<void (Class::*)() &&>();
    test_is_not_safe_signed<void (Class::*)() const>();
    test_is_not_safe_signed<void (Class::*)() const&>();
    test_is_not_safe_signed<void (Class::*)() const&&>();
    test_is_not_safe_signed<void (Class::*)() noexcept>();
    test_is_not_safe_signed<void (Class::*)()& noexcept>();
    test_is_not_safe_signed<void (Class::*)()&& noexcept>();
    test_is_not_safe_signed<void (Class::*)() const noexcept>();
    test_is_not_safe_signed<void (Class::*)() const& noexcept>();
    test_is_not_safe_signed<void (Class::*)() const&& noexcept>();

    test_is_not_safe_signed<void (Class::*)(int)>();
    test_is_not_safe_signed<void (Class::*)(int)&>();
    test_is_not_safe_signed<void (Class::*)(int) &&>();
    test_is_not_safe_signed<void (Class::*)(int) const>();
    test_is_not_safe_signed<void (Class::*)(int) const&>();
    test_is_not_safe_signed<void (Class::*)(int) const&&>();
    test_is_not_safe_signed<void (Class::*)(int) noexcept>();
    test_is_not_safe_signed<void (Class::*)(int)& noexcept>();
    test_is_not_safe_signed<void (Class::*)(int)&& noexcept>();
    test_is_not_safe_signed<void (Class::*)(int) const noexcept>();
    test_is_not_safe_signed<void (Class::*)(int) const& noexcept>();
    test_is_not_safe_signed<void (Class::*)(int) const&& noexcept>();

    test_is_not_safe_signed<void (Class::*)(...)>();
    test_is_not_safe_signed<void (Class::*)(...)&>();
    test_is_not_safe_signed<void (Class::*)(...) &&>();
    test_is_not_safe_signed<void (Class::*)(...) const>();
    test_is_not_safe_signed<void (Class::*)(...) const&>();
    test_is_not_safe_signed<void (Class::*)(...) const&&>();
    test_is_not_safe_signed<void (Class::*)(...) noexcept>();
    test_is_not_safe_signed<void (Class::*)(...)& noexcept>();
    test_is_not_safe_signed<void (Class::*)(...)&& noexcept>();
    test_is_not_safe_signed<void (Class::*)(...) const noexcept>();
    test_is_not_safe_signed<void (Class::*)(...) const& noexcept>();
    test_is_not_safe_signed<void (Class::*)(...) const&& noexcept>();

    test_is_not_safe_signed<void (Class::*)(int, ...)>();
    test_is_not_safe_signed<void (Class::*)(int, ...)&>();
    test_is_not_safe_signed<void (Class::*)(int, ...) &&>();
    test_is_not_safe_signed<void (Class::*)(int, ...) const>();
    test_is_not_safe_signed<void (Class::*)(int, ...) const&>();
    test_is_not_safe_signed<void (Class::*)(int, ...) const&&>();
    test_is_not_safe_signed<void (Class::*)(int, ...) noexcept>();
    test_is_not_safe_signed<void (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_signed<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_signed<void (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_signed<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_signed<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_safe_signed<int (Class::*)()>();
    test_is_not_safe_signed<int (Class::*)()&>();
    test_is_not_safe_signed<int (Class::*)() &&>();
    test_is_not_safe_signed<int (Class::*)() const>();
    test_is_not_safe_signed<int (Class::*)() const&>();
    test_is_not_safe_signed<int (Class::*)() const&&>();
    test_is_not_safe_signed<int (Class::*)() noexcept>();
    test_is_not_safe_signed<int (Class::*)()& noexcept>();
    test_is_not_safe_signed<int (Class::*)()&& noexcept>();
    test_is_not_safe_signed<int (Class::*)() const noexcept>();
    test_is_not_safe_signed<int (Class::*)() const& noexcept>();
    test_is_not_safe_signed<int (Class::*)() const&& noexcept>();

    test_is_not_safe_signed<int (Class::*)(int)>();
    test_is_not_safe_signed<int (Class::*)(int)&>();
    test_is_not_safe_signed<int (Class::*)(int) &&>();
    test_is_not_safe_signed<int (Class::*)(int) const>();
    test_is_not_safe_signed<int (Class::*)(int) const&>();
    test_is_not_safe_signed<int (Class::*)(int) const&&>();
    test_is_not_safe_signed<int (Class::*)(int) noexcept>();
    test_is_not_safe_signed<int (Class::*)(int)& noexcept>();
    test_is_not_safe_signed<int (Class::*)(int)&& noexcept>();
    test_is_not_safe_signed<int (Class::*)(int) const noexcept>();
    test_is_not_safe_signed<int (Class::*)(int) const& noexcept>();
    test_is_not_safe_signed<int (Class::*)(int) const&& noexcept>();

    test_is_not_safe_signed<int (Class::*)(...)>();
    test_is_not_safe_signed<int (Class::*)(...)&>();
    test_is_not_safe_signed<int (Class::*)(...) &&>();
    test_is_not_safe_signed<int (Class::*)(...) const>();
    test_is_not_safe_signed<int (Class::*)(...) const&>();
    test_is_not_safe_signed<int (Class::*)(...) const&&>();
    test_is_not_safe_signed<int (Class::*)(...) noexcept>();
    test_is_not_safe_signed<int (Class::*)(...)& noexcept>();
    test_is_not_safe_signed<int (Class::*)(...)&& noexcept>();
    test_is_not_safe_signed<int (Class::*)(...) const noexcept>();
    test_is_not_safe_signed<int (Class::*)(...) const& noexcept>();
    test_is_not_safe_signed<int (Class::*)(...) const&& noexcept>();

    test_is_not_safe_signed<int (Class::*)(int, ...)>();
    test_is_not_safe_signed<int (Class::*)(int, ...)&>();
    test_is_not_safe_signed<int (Class::*)(int, ...) &&>();
    test_is_not_safe_signed<int (Class::*)(int, ...) const>();
    test_is_not_safe_signed<int (Class::*)(int, ...) const&>();
    test_is_not_safe_signed<int (Class::*)(int, ...) const&&>();
    test_is_not_safe_signed<int (Class::*)(int, ...) noexcept>();
    test_is_not_safe_signed<int (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_signed<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_signed<int (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_signed<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_signed<int (Class::*)(int, ...) const&& noexcept>();
}
