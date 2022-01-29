#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_safe_unsigned.hpp>
#include <vector>

template <typename T>
void test_is_safe_unsigned_impl()
{
    STATIC_REQUIRE(phi::is_safe_unsigned<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_unsigned<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_unsigned_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_unsigned_v<T>);
#endif
}

template <typename T>
void test_is_not_safe_unsigned_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_unsigned<T>::value);
    STATIC_REQUIRE(phi::is_not_safe_unsigned<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_unsigned_v<T>);
    STATIC_REQUIRE(phi::is_not_safe_unsigned_v<T>);
#endif
}

template <typename T>
void test_is_safe_unsigned()
{
    test_is_safe_unsigned_impl<T>();
    test_is_safe_unsigned_impl<const T>();
    test_is_safe_unsigned_impl<volatile T>();
    test_is_safe_unsigned_impl<const volatile T>();
}

template <typename T>
void test_is_not_safe_unsigned()
{
    test_is_not_safe_unsigned_impl<T>();
    test_is_not_safe_unsigned_impl<const T>();
    test_is_not_safe_unsigned_impl<volatile T>();
    test_is_not_safe_unsigned_impl<const volatile T>();
}

TEST_CASE("is_safe_unsigned")
{
    test_is_not_safe_unsigned<void>();
    test_is_not_safe_unsigned<phi::nullptr_t>();
    test_is_not_safe_unsigned<bool>();
    test_is_not_safe_unsigned<char>();
    test_is_not_safe_unsigned<unsigned char>();
    test_is_not_safe_unsigned<unsigned char>();
    test_is_not_safe_unsigned<short>();
    test_is_not_safe_unsigned<unsigned short>();
    test_is_not_safe_unsigned<int>();
    test_is_not_safe_unsigned<unsigned int>();
    test_is_not_safe_unsigned<long>();
    test_is_not_safe_unsigned<unsigned long>();
    test_is_not_safe_unsigned<long long>();
    test_is_not_safe_unsigned<unsigned long long>();
    test_is_not_safe_unsigned<float>();
    test_is_not_safe_unsigned<double>();
    test_is_not_safe_unsigned<long double>();
    test_is_not_safe_unsigned<char8_t>();
    test_is_not_safe_unsigned<char16_t>();
    test_is_not_safe_unsigned<char32_t>();
    test_is_not_safe_unsigned<wchar_t>();

    test_is_safe_unsigned<phi::boolean>();
    test_is_not_safe_unsigned<phi::integer<signed char>>();
    test_is_safe_unsigned<phi::integer<unsigned char>>();
    test_is_not_safe_unsigned<phi::integer<short>>();
    test_is_safe_unsigned<phi::integer<unsigned short>>();
    test_is_not_safe_unsigned<phi::integer<int>>();
    test_is_safe_unsigned<phi::integer<unsigned int>>();
    test_is_not_safe_unsigned<phi::integer<long>>();
    test_is_safe_unsigned<phi::integer<unsigned long>>();
    test_is_not_safe_unsigned<phi::integer<long long>>();
    test_is_safe_unsigned<phi::integer<unsigned long long>>();
    test_is_not_safe_unsigned<phi::floating_point<float>>();
    test_is_not_safe_unsigned<phi::floating_point<double>>();
    test_is_not_safe_unsigned<phi::floating_point<long double>>();

    test_is_not_safe_unsigned<std::vector<int>>();
    test_is_not_safe_unsigned<phi::scope_ptr<int>>();

    test_is_not_safe_unsigned<int&>();
    test_is_not_safe_unsigned<const int&>();
    test_is_not_safe_unsigned<volatile int&>();
    test_is_not_safe_unsigned<const volatile int&>();
    test_is_not_safe_unsigned<int&&>();
    test_is_not_safe_unsigned<const int&&>();
    test_is_not_safe_unsigned<volatile int&&>();
    test_is_not_safe_unsigned<const volatile int&&>();
    test_is_not_safe_unsigned<int*>();
    test_is_not_safe_unsigned<const int*>();
    test_is_not_safe_unsigned<volatile int*>();
    test_is_not_safe_unsigned<const volatile int*>();
    test_is_not_safe_unsigned<int**>();
    test_is_not_safe_unsigned<const int**>();
    test_is_not_safe_unsigned<volatile int**>();
    test_is_not_safe_unsigned<const volatile int**>();
    test_is_not_safe_unsigned<int*&>();
    test_is_not_safe_unsigned<const int*&>();
    test_is_not_safe_unsigned<volatile int*&>();
    test_is_not_safe_unsigned<const volatile int*&>();
    test_is_not_safe_unsigned<int*&&>();
    test_is_not_safe_unsigned<const int*&&>();
    test_is_not_safe_unsigned<volatile int*&&>();
    test_is_not_safe_unsigned<const volatile int*&&>();
    test_is_not_safe_unsigned<void*>();
    test_is_not_safe_unsigned<char[3]>();
    test_is_not_safe_unsigned<char[]>();
    test_is_not_safe_unsigned<char* [3]>();
    test_is_not_safe_unsigned<char*[]>();
    test_is_not_safe_unsigned<int(*)[3]>();
    test_is_not_safe_unsigned<int(*)[]>();
    test_is_not_safe_unsigned<int(&)[3]>();
    test_is_not_safe_unsigned<int(&)[]>();
    test_is_not_safe_unsigned<int(&&)[3]>();
    test_is_not_safe_unsigned<int(&&)[]>();
    test_is_not_safe_unsigned<char[3][2]>();
    test_is_not_safe_unsigned<char[][2]>();
    test_is_not_safe_unsigned<char* [3][2]>();
    test_is_not_safe_unsigned<char*[][2]>();
    test_is_not_safe_unsigned<int(*)[3][2]>();
    test_is_not_safe_unsigned<int(*)[][2]>();
    test_is_not_safe_unsigned<int(&)[3][2]>();
    test_is_not_safe_unsigned<int(&)[][2]>();
    test_is_not_safe_unsigned<int(&&)[3][2]>();
    test_is_not_safe_unsigned<int(&&)[][2]>();
    test_is_not_safe_unsigned<Class>();
    test_is_not_safe_unsigned<Class[]>();
    test_is_not_safe_unsigned<Class[2]>();
    test_is_not_safe_unsigned<Template<void>>();
    test_is_not_safe_unsigned<Template<int>>();
    test_is_not_safe_unsigned<Template<Class>>();
    test_is_not_safe_unsigned<Template<IncompleteType>>();
    test_is_not_safe_unsigned<VariadicTemplate<>>();
    test_is_not_safe_unsigned<VariadicTemplate<void>>();
    test_is_not_safe_unsigned<VariadicTemplate<int>>();
    test_is_not_safe_unsigned<VariadicTemplate<Class>>();
    test_is_not_safe_unsigned<VariadicTemplate<IncompleteType>>();
    test_is_not_safe_unsigned<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_unsigned<PublicDerivedFromTemplate<Base>>();
    test_is_not_safe_unsigned<PublicDerivedFromTemplate<Derived>>();
    test_is_not_safe_unsigned<PublicDerivedFromTemplate<Class>>();
    test_is_not_safe_unsigned<PrivateDerivedFromTemplate<Base>>();
    test_is_not_safe_unsigned<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_safe_unsigned<PrivateDerivedFromTemplate<Class>>();
    test_is_not_safe_unsigned<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_safe_unsigned<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_safe_unsigned<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_safe_unsigned<VirtualDerivedFromTemplate<Base>>();
    test_is_not_safe_unsigned<VirtualDerivedFromTemplate<Derived>>();
    test_is_not_safe_unsigned<VirtualDerivedFromTemplate<Class>>();
    test_is_not_safe_unsigned<Union>();
    test_is_not_safe_unsigned<NonEmptyUnion>();
    test_is_not_safe_unsigned<NonTrivialUnion>();
    test_is_not_safe_unsigned<Empty>();
    test_is_not_safe_unsigned<NotEmpty>();
    test_is_not_safe_unsigned<NonTrivial>();
    test_is_not_safe_unsigned<BitZero>();
    test_is_not_safe_unsigned<BitOne>();
    test_is_not_safe_unsigned<Base>();
    test_is_not_safe_unsigned<Derived>();
    test_is_not_safe_unsigned<Polymorphic>();
    test_is_not_safe_unsigned<DerivedPolymorphic>();
    test_is_not_safe_unsigned<Abstract>();
    test_is_not_safe_unsigned<PublicAbstract>();
    test_is_not_safe_unsigned<PrivateAbstract>();
    test_is_not_safe_unsigned<ProtectedAbstract>();
    test_is_not_safe_unsigned<AbstractTemplate<int>>();
    test_is_not_safe_unsigned<AbstractTemplate<double>>();
    test_is_not_safe_unsigned<AbstractTemplate<Class>>();
    test_is_not_safe_unsigned<AbstractTemplate<IncompleteType>>();
    test_is_not_safe_unsigned<PublicAbstractDeletedDestructor>();
    test_is_not_safe_unsigned<ProtectedAbstractDeletedDestructor>();
    test_is_not_safe_unsigned<PrivateAbstractDeletedDestructor>();
    test_is_not_safe_unsigned<Final>();
    test_is_not_safe_unsigned<FinalDerived>();
    test_is_not_safe_unsigned<PublicDestructor>();
    test_is_not_safe_unsigned<ProtectedDestructor>();
    test_is_not_safe_unsigned<PrivateDestructor>();
    test_is_not_safe_unsigned<VirtualPublicDestructor>();
    test_is_not_safe_unsigned<VirtualProtectedDestructor>();
    test_is_not_safe_unsigned<VirtualPrivateDestructor>();
    test_is_not_safe_unsigned<PurePublicDestructor>();
    test_is_not_safe_unsigned<PureProtectedDestructor>();
    test_is_not_safe_unsigned<PurePrivateDestructor>();
    test_is_not_safe_unsigned<DeletedPublicDestructor>();
    test_is_not_safe_unsigned<DeletedProtectedDestructor>();
    test_is_not_safe_unsigned<DeletedPrivateDestructor>();
    test_is_not_safe_unsigned<DeletedVirtualPublicDestructor>();
    test_is_not_safe_unsigned<DeletedVirtualProtectedDestructor>();
    test_is_not_safe_unsigned<DeletedVirtualPrivateDestructor>();
    test_is_not_safe_unsigned<ExplicitClass>();
    test_is_not_safe_unsigned<NothrowExplicitClass>();
    test_is_not_safe_unsigned<ThrowExplicitClass>();
    test_is_not_safe_unsigned<ThrowDefaultClass>();
    test_is_not_safe_unsigned<ThrowCopyConsClass>();
    test_is_not_safe_unsigned<ThrowMoveConsClass>();
    test_is_not_safe_unsigned<NoexceptExplicitClass>();
    test_is_not_safe_unsigned<ExceptExplicitClass>();
    test_is_not_safe_unsigned<NoexceptDefaultClass>();
    test_is_not_safe_unsigned<ExceptDefaultClass>();
    test_is_not_safe_unsigned<NoexceptCopyConsClass>();
    test_is_not_safe_unsigned<ExceptCopyConsClass>();
    test_is_not_safe_unsigned<NoexceptMoveConsClass>();
    test_is_not_safe_unsigned<ExceptMoveConsClass>();
    test_is_not_safe_unsigned<NoexceptCopyAssignClass>();
    test_is_not_safe_unsigned<ExceptCopyAssignClass>();
    test_is_not_safe_unsigned<NoexceptMoveAssignClass>();
    test_is_not_safe_unsigned<ExceptMoveAssignClass>();
    test_is_not_safe_unsigned<DeletedCopyAssignClass>();
    test_is_not_safe_unsigned<DeletedMoveAssignClass>();
    test_is_not_safe_unsigned<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_safe_unsigned<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_safe_unsigned<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_not_safe_unsigned<ExceptMoveConsExceptMoveAssignClass>();
    test_is_not_safe_unsigned<ImplicitTo<int>>();
    test_is_not_safe_unsigned<ImplicitTo<float>>();
    test_is_not_safe_unsigned<ImplicitTo<Class>>();
    test_is_not_safe_unsigned<DeletedImplicitTo<int>>();
    test_is_not_safe_unsigned<DeletedImplicitTo<float>>();
    test_is_not_safe_unsigned<DeletedImplicitTo<Class>>();
    test_is_not_safe_unsigned<ExplicitTo<int>>();
    test_is_not_safe_unsigned<ExplicitTo<float>>();
    test_is_not_safe_unsigned<ExplicitTo<Class>>();
    test_is_not_safe_unsigned<DeletedExplicitTo<int>>();
    test_is_not_safe_unsigned<DeletedExplicitTo<float>>();
    test_is_not_safe_unsigned<DeletedExplicitTo<Class>>();
    test_is_not_safe_unsigned<Ellipsis>();
    test_is_not_safe_unsigned<DeletedEllipsis>();
    test_is_not_safe_unsigned<CopyConsOnlyType>();
    test_is_not_safe_unsigned<MoveConsOnlyType>();
    test_is_not_safe_unsigned<OverloadedOperators>();
    test_is_not_safe_unsigned<PublicIntMember>();
    test_is_not_safe_unsigned<ProtectedIntMember>();
    test_is_not_safe_unsigned<PrivateIntMember>();
    test_is_not_safe_unsigned<PublicStaticIntMember>();
    test_is_not_safe_unsigned<ProtectedStaticIntMember>();
    test_is_not_safe_unsigned<PrivateStaticIntMember>();
    test_is_not_safe_unsigned<PublicTemplateMember<int>>();
    test_is_not_safe_unsigned<PublicTemplateMember<float>>();
    test_is_not_safe_unsigned<PublicTemplateMember<Class>>();
    test_is_not_safe_unsigned<ProtectedTemplateMember<int>>();
    test_is_not_safe_unsigned<ProtectedTemplateMember<float>>();
    test_is_not_safe_unsigned<ProtectedTemplateMember<Class>>();
    test_is_not_safe_unsigned<PrivateTemplateMember<int>>();
    test_is_not_safe_unsigned<PrivateTemplateMember<float>>();
    test_is_not_safe_unsigned<PrivateTemplateMember<Class>>();
    test_is_not_safe_unsigned<PublicStaticTemplateMember<int>>();
    test_is_not_safe_unsigned<PublicStaticTemplateMember<float>>();
    test_is_not_safe_unsigned<PublicStaticTemplateMember<Class>>();
    test_is_not_safe_unsigned<ProtectedStaticTemplateMember<int>>();
    test_is_not_safe_unsigned<ProtectedStaticTemplateMember<float>>();
    test_is_not_safe_unsigned<ProtectedStaticTemplateMember<Class>>();
    test_is_not_safe_unsigned<PrivateStaticTemplateMember<int>>();
    test_is_not_safe_unsigned<PrivateStaticTemplateMember<float>>();
    test_is_not_safe_unsigned<PrivateStaticTemplateMember<Class>>();
    test_is_not_safe_unsigned<Enum>();
    test_is_not_safe_unsigned<EnumSigned>();
    test_is_not_safe_unsigned<EnumUnsigned>();
    test_is_not_safe_unsigned<EnumClass>();
    test_is_not_safe_unsigned<EnumStruct>();
    test_is_not_safe_unsigned<Function>();
    test_is_not_safe_unsigned<FunctionPtr>();
    test_is_not_safe_unsigned<MemberObjectPtr>();
    test_is_not_safe_unsigned<MemberFunctionPtr>();
    test_is_not_safe_unsigned<LambdaType>();
    test_is_not_safe_unsigned<LambdaNoexceptType>();
    test_is_not_safe_unsigned<LambdaThrowsType>();
    test_is_not_safe_unsigned<IncompleteType>();
    test_is_not_safe_unsigned<IncompleteTemplate<void>>();
    test_is_not_safe_unsigned<IncompleteTemplate<int>>();
    test_is_not_safe_unsigned<IncompleteTemplate<Class>>();
    test_is_not_safe_unsigned<IncompleteTemplate<IncompleteType>>();
    test_is_not_safe_unsigned<IncompleteVariadicTemplate<>>();
    test_is_not_safe_unsigned<IncompleteVariadicTemplate<void>>();
    test_is_not_safe_unsigned<IncompleteVariadicTemplate<int>>();
    test_is_not_safe_unsigned<IncompleteVariadicTemplate<Class>>();
    test_is_not_safe_unsigned<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_safe_unsigned<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_unsigned<IncompleteUnion>();
    test_is_not_safe_unsigned<IncompleteEnumSigned>();
    test_is_not_safe_unsigned<IncompleteEnumUnsigned>();
    test_is_not_safe_unsigned<IncompleteEnumClass>();
    test_is_not_safe_unsigned<IncompleteEnumStruct>();
    test_is_not_safe_unsigned<int Class::*>();
    test_is_not_safe_unsigned<float Class::*>();
    test_is_not_safe_unsigned<void * Class::*>();
    test_is_not_safe_unsigned<int * Class::*>();
    test_is_not_safe_unsigned<int Class::*&>();
    test_is_not_safe_unsigned<float Class::*&>();
    test_is_not_safe_unsigned<void * Class::*&>();
    test_is_not_safe_unsigned<int * Class::*&>();
    test_is_not_safe_unsigned<int Class::*&&>();
    test_is_not_safe_unsigned<float Class::*&&>();
    test_is_not_safe_unsigned<void * Class::*&&>();
    test_is_not_safe_unsigned<int * Class::*&&>();
    test_is_not_safe_unsigned<int Class::*const>();
    test_is_not_safe_unsigned<float Class::*const>();
    test_is_not_safe_unsigned<void * Class::*const>();
    test_is_not_safe_unsigned<int Class::*const&>();
    test_is_not_safe_unsigned<float Class::*const&>();
    test_is_not_safe_unsigned<void * Class::*const&>();
    test_is_not_safe_unsigned<int Class::*const&&>();
    test_is_not_safe_unsigned<float Class::*const&&>();
    test_is_not_safe_unsigned<void * Class::*const&&>();
    test_is_not_safe_unsigned<int Class::*volatile>();
    test_is_not_safe_unsigned<float Class::*volatile>();
    test_is_not_safe_unsigned<void * Class::*volatile>();
    test_is_not_safe_unsigned<int Class::*volatile&>();
    test_is_not_safe_unsigned<float Class::*volatile&>();
    test_is_not_safe_unsigned<void * Class::*volatile&>();
    test_is_not_safe_unsigned<int Class::*volatile&&>();
    test_is_not_safe_unsigned<float Class::*volatile&&>();
    test_is_not_safe_unsigned<void * Class::*volatile&&>();
    test_is_not_safe_unsigned<int Class::*const volatile>();
    test_is_not_safe_unsigned<float Class::*const volatile>();
    test_is_not_safe_unsigned<void * Class::*const volatile>();
    test_is_not_safe_unsigned<int Class::*const volatile&>();
    test_is_not_safe_unsigned<float Class::*const volatile&>();
    test_is_not_safe_unsigned<void * Class::*const volatile&>();
    test_is_not_safe_unsigned<int Class::*const volatile&&>();
    test_is_not_safe_unsigned<float Class::*const volatile&&>();
    test_is_not_safe_unsigned<void * Class::*const volatile&&>();
    test_is_not_safe_unsigned<NonCopyable>();
    test_is_not_safe_unsigned<NonMoveable>();
    test_is_not_safe_unsigned<NonConstructible>();
    test_is_not_safe_unsigned<NonDestructible>();
    test_is_not_safe_unsigned<Tracked>();
    test_is_not_safe_unsigned<TrapConstructible>();
    test_is_not_safe_unsigned<TrapImplicitConversion>();
    test_is_not_safe_unsigned<TrapComma>();
    test_is_not_safe_unsigned<TrapCall>();
    test_is_not_safe_unsigned<TrapSelfAssign>();
    test_is_not_safe_unsigned<TrapDeref>();
    test_is_not_safe_unsigned<TrapArraySubscript>();

    test_is_not_safe_unsigned<void()>();
    test_is_not_safe_unsigned<void()&>();
    test_is_not_safe_unsigned<void() &&>();
    test_is_not_safe_unsigned<void() const>();
    test_is_not_safe_unsigned<void() const&>();
    test_is_not_safe_unsigned<void() const&&>();
    test_is_not_safe_unsigned<void() volatile>();
    test_is_not_safe_unsigned<void() volatile&>();
    test_is_not_safe_unsigned<void() volatile&&>();
    test_is_not_safe_unsigned<void() const volatile>();
    test_is_not_safe_unsigned<void() const volatile&>();
    test_is_not_safe_unsigned<void() const volatile&&>();
    test_is_not_safe_unsigned<void() noexcept>();
    test_is_not_safe_unsigned<void()& noexcept>();
    test_is_not_safe_unsigned<void()&& noexcept>();
    test_is_not_safe_unsigned<void() const noexcept>();
    test_is_not_safe_unsigned<void() const& noexcept>();
    test_is_not_safe_unsigned<void() const&& noexcept>();
    test_is_not_safe_unsigned<void() volatile noexcept>();
    test_is_not_safe_unsigned<void() volatile& noexcept>();
    test_is_not_safe_unsigned<void() volatile&& noexcept>();
    test_is_not_safe_unsigned<void() const volatile noexcept>();
    test_is_not_safe_unsigned<void() const volatile& noexcept>();
    test_is_not_safe_unsigned<void() const volatile&& noexcept>();

    test_is_not_safe_unsigned<void(int)>();
    test_is_not_safe_unsigned<void(int)&>();
    test_is_not_safe_unsigned<void(int) &&>();
    test_is_not_safe_unsigned<void(int) const>();
    test_is_not_safe_unsigned<void(int) const&>();
    test_is_not_safe_unsigned<void(int) const&&>();
    test_is_not_safe_unsigned<void(int) volatile>();
    test_is_not_safe_unsigned<void(int) volatile&>();
    test_is_not_safe_unsigned<void(int) volatile&&>();
    test_is_not_safe_unsigned<void(int) const volatile>();
    test_is_not_safe_unsigned<void(int) const volatile&>();
    test_is_not_safe_unsigned<void(int) const volatile&&>();
    test_is_not_safe_unsigned<void(int) noexcept>();
    test_is_not_safe_unsigned<void(int)& noexcept>();
    test_is_not_safe_unsigned<void(int)&& noexcept>();
    test_is_not_safe_unsigned<void(int) const noexcept>();
    test_is_not_safe_unsigned<void(int) const& noexcept>();
    test_is_not_safe_unsigned<void(int) const&& noexcept>();
    test_is_not_safe_unsigned<void(int) volatile noexcept>();
    test_is_not_safe_unsigned<void(int) volatile& noexcept>();
    test_is_not_safe_unsigned<void(int) volatile&& noexcept>();
    test_is_not_safe_unsigned<void(int) const volatile noexcept>();
    test_is_not_safe_unsigned<void(int) const volatile& noexcept>();
    test_is_not_safe_unsigned<void(int) const volatile&& noexcept>();

    test_is_not_safe_unsigned<void(...)>();
    test_is_not_safe_unsigned<void(...)&>();
    test_is_not_safe_unsigned<void(...) &&>();
    test_is_not_safe_unsigned<void(...) const>();
    test_is_not_safe_unsigned<void(...) const&>();
    test_is_not_safe_unsigned<void(...) const&&>();
    test_is_not_safe_unsigned<void(...) volatile>();
    test_is_not_safe_unsigned<void(...) volatile&>();
    test_is_not_safe_unsigned<void(...) volatile&&>();
    test_is_not_safe_unsigned<void(...) const volatile>();
    test_is_not_safe_unsigned<void(...) const volatile&>();
    test_is_not_safe_unsigned<void(...) const volatile&&>();
    test_is_not_safe_unsigned<void(...) noexcept>();
    test_is_not_safe_unsigned<void(...)& noexcept>();
    test_is_not_safe_unsigned<void(...)&& noexcept>();
    test_is_not_safe_unsigned<void(...) const noexcept>();
    test_is_not_safe_unsigned<void(...) const& noexcept>();
    test_is_not_safe_unsigned<void(...) const&& noexcept>();
    test_is_not_safe_unsigned<void(...) volatile noexcept>();
    test_is_not_safe_unsigned<void(...) volatile& noexcept>();
    test_is_not_safe_unsigned<void(...) volatile&& noexcept>();
    test_is_not_safe_unsigned<void(...) const volatile noexcept>();
    test_is_not_safe_unsigned<void(...) const volatile& noexcept>();
    test_is_not_safe_unsigned<void(...) const volatile&& noexcept>();

    test_is_not_safe_unsigned<void(int, ...)>();
    test_is_not_safe_unsigned<void(int, ...)&>();
    test_is_not_safe_unsigned<void(int, ...) &&>();
    test_is_not_safe_unsigned<void(int, ...) const>();
    test_is_not_safe_unsigned<void(int, ...) const&>();
    test_is_not_safe_unsigned<void(int, ...) const&&>();
    test_is_not_safe_unsigned<void(int, ...) volatile>();
    test_is_not_safe_unsigned<void(int, ...) volatile&>();
    test_is_not_safe_unsigned<void(int, ...) volatile&&>();
    test_is_not_safe_unsigned<void(int, ...) const volatile>();
    test_is_not_safe_unsigned<void(int, ...) const volatile&>();
    test_is_not_safe_unsigned<void(int, ...) const volatile&&>();
    test_is_not_safe_unsigned<void(int, ...) noexcept>();
    test_is_not_safe_unsigned<void(int, ...)& noexcept>();
    test_is_not_safe_unsigned<void(int, ...)&& noexcept>();
    test_is_not_safe_unsigned<void(int, ...) const noexcept>();
    test_is_not_safe_unsigned<void(int, ...) const& noexcept>();
    test_is_not_safe_unsigned<void(int, ...) const&& noexcept>();
    test_is_not_safe_unsigned<void(int, ...) volatile noexcept>();
    test_is_not_safe_unsigned<void(int, ...) volatile& noexcept>();
    test_is_not_safe_unsigned<void(int, ...) volatile&& noexcept>();
    test_is_not_safe_unsigned<void(int, ...) const volatile noexcept>();
    test_is_not_safe_unsigned<void(int, ...) const volatile& noexcept>();
    test_is_not_safe_unsigned<void(int, ...) const volatile&& noexcept>();

    test_is_not_safe_unsigned<int()>();
    test_is_not_safe_unsigned<int()&>();
    test_is_not_safe_unsigned<int() &&>();
    test_is_not_safe_unsigned<int() const>();
    test_is_not_safe_unsigned<int() const&>();
    test_is_not_safe_unsigned<int() const&&>();
    test_is_not_safe_unsigned<int() volatile>();
    test_is_not_safe_unsigned<int() volatile&>();
    test_is_not_safe_unsigned<int() volatile&&>();
    test_is_not_safe_unsigned<int() const volatile>();
    test_is_not_safe_unsigned<int() const volatile&>();
    test_is_not_safe_unsigned<int() const volatile&&>();
    test_is_not_safe_unsigned<int() noexcept>();
    test_is_not_safe_unsigned<int()& noexcept>();
    test_is_not_safe_unsigned<int()&& noexcept>();
    test_is_not_safe_unsigned<int() const noexcept>();
    test_is_not_safe_unsigned<int() const& noexcept>();
    test_is_not_safe_unsigned<int() const&& noexcept>();
    test_is_not_safe_unsigned<int() volatile noexcept>();
    test_is_not_safe_unsigned<int() volatile& noexcept>();
    test_is_not_safe_unsigned<int() volatile&& noexcept>();
    test_is_not_safe_unsigned<int() const volatile noexcept>();
    test_is_not_safe_unsigned<int() const volatile& noexcept>();
    test_is_not_safe_unsigned<int() const volatile&& noexcept>();

    test_is_not_safe_unsigned<int(int)>();
    test_is_not_safe_unsigned<int(int)&>();
    test_is_not_safe_unsigned<int(int) &&>();
    test_is_not_safe_unsigned<int(int) const>();
    test_is_not_safe_unsigned<int(int) const&>();
    test_is_not_safe_unsigned<int(int) const&&>();
    test_is_not_safe_unsigned<int(int) volatile>();
    test_is_not_safe_unsigned<int(int) volatile&>();
    test_is_not_safe_unsigned<int(int) volatile&&>();
    test_is_not_safe_unsigned<int(int) const volatile>();
    test_is_not_safe_unsigned<int(int) const volatile&>();
    test_is_not_safe_unsigned<int(int) const volatile&&>();
    test_is_not_safe_unsigned<int(int) noexcept>();
    test_is_not_safe_unsigned<int(int)& noexcept>();
    test_is_not_safe_unsigned<int(int)&& noexcept>();
    test_is_not_safe_unsigned<int(int) const noexcept>();
    test_is_not_safe_unsigned<int(int) const& noexcept>();
    test_is_not_safe_unsigned<int(int) const&& noexcept>();
    test_is_not_safe_unsigned<int(int) volatile noexcept>();
    test_is_not_safe_unsigned<int(int) volatile& noexcept>();
    test_is_not_safe_unsigned<int(int) volatile&& noexcept>();
    test_is_not_safe_unsigned<int(int) const volatile noexcept>();
    test_is_not_safe_unsigned<int(int) const volatile& noexcept>();
    test_is_not_safe_unsigned<int(int) const volatile&& noexcept>();

    test_is_not_safe_unsigned<int(...)>();
    test_is_not_safe_unsigned<int(...)&>();
    test_is_not_safe_unsigned<int(...) &&>();
    test_is_not_safe_unsigned<int(...) const>();
    test_is_not_safe_unsigned<int(...) const&>();
    test_is_not_safe_unsigned<int(...) const&&>();
    test_is_not_safe_unsigned<int(...) volatile>();
    test_is_not_safe_unsigned<int(...) volatile&>();
    test_is_not_safe_unsigned<int(...) volatile&&>();
    test_is_not_safe_unsigned<int(...) const volatile>();
    test_is_not_safe_unsigned<int(...) const volatile&>();
    test_is_not_safe_unsigned<int(...) const volatile&&>();
    test_is_not_safe_unsigned<int(...) noexcept>();
    test_is_not_safe_unsigned<int(...)& noexcept>();
    test_is_not_safe_unsigned<int(...)&& noexcept>();
    test_is_not_safe_unsigned<int(...) const noexcept>();
    test_is_not_safe_unsigned<int(...) const& noexcept>();
    test_is_not_safe_unsigned<int(...) const&& noexcept>();
    test_is_not_safe_unsigned<int(...) volatile noexcept>();
    test_is_not_safe_unsigned<int(...) volatile& noexcept>();
    test_is_not_safe_unsigned<int(...) volatile&& noexcept>();
    test_is_not_safe_unsigned<int(...) const volatile noexcept>();
    test_is_not_safe_unsigned<int(...) const volatile& noexcept>();
    test_is_not_safe_unsigned<int(...) const volatile&& noexcept>();

    test_is_not_safe_unsigned<int(int, ...)>();
    test_is_not_safe_unsigned<int(int, ...)&>();
    test_is_not_safe_unsigned<int(int, ...) &&>();
    test_is_not_safe_unsigned<int(int, ...) const>();
    test_is_not_safe_unsigned<int(int, ...) const&>();
    test_is_not_safe_unsigned<int(int, ...) const&&>();
    test_is_not_safe_unsigned<int(int, ...) volatile>();
    test_is_not_safe_unsigned<int(int, ...) volatile&>();
    test_is_not_safe_unsigned<int(int, ...) volatile&&>();
    test_is_not_safe_unsigned<int(int, ...) const volatile>();
    test_is_not_safe_unsigned<int(int, ...) const volatile&>();
    test_is_not_safe_unsigned<int(int, ...) const volatile&&>();
    test_is_not_safe_unsigned<int(int, ...) noexcept>();
    test_is_not_safe_unsigned<int(int, ...)& noexcept>();
    test_is_not_safe_unsigned<int(int, ...)&& noexcept>();
    test_is_not_safe_unsigned<int(int, ...) const noexcept>();
    test_is_not_safe_unsigned<int(int, ...) const& noexcept>();
    test_is_not_safe_unsigned<int(int, ...) const&& noexcept>();
    test_is_not_safe_unsigned<int(int, ...) volatile noexcept>();
    test_is_not_safe_unsigned<int(int, ...) volatile& noexcept>();
    test_is_not_safe_unsigned<int(int, ...) volatile&& noexcept>();
    test_is_not_safe_unsigned<int(int, ...) const volatile noexcept>();
    test_is_not_safe_unsigned<int(int, ...) const volatile& noexcept>();
    test_is_not_safe_unsigned<int(int, ...) const volatile&& noexcept>();

    test_is_not_safe_unsigned<void (*)()>();
    test_is_not_safe_unsigned<void (*)() noexcept>();

    test_is_not_safe_unsigned<void (*)(int)>();
    test_is_not_safe_unsigned<void (*)(int) noexcept>();

    test_is_not_safe_unsigned<void (*)(...)>();
    test_is_not_safe_unsigned<void (*)(...) noexcept>();

    test_is_not_safe_unsigned<void (*)(int, ...)>();
    test_is_not_safe_unsigned<void (*)(int, ...) noexcept>();

    test_is_not_safe_unsigned<int (*)()>();
    test_is_not_safe_unsigned<int (*)() noexcept>();

    test_is_not_safe_unsigned<int (*)(int)>();
    test_is_not_safe_unsigned<int (*)(int) noexcept>();

    test_is_not_safe_unsigned<int (*)(...)>();
    test_is_not_safe_unsigned<int (*)(...) noexcept>();

    test_is_not_safe_unsigned<int (*)(int, ...)>();
    test_is_not_safe_unsigned<int (*)(int, ...) noexcept>();

    test_is_not_safe_unsigned<void (&)()>();
    test_is_not_safe_unsigned<void (&)() noexcept>();

    test_is_not_safe_unsigned<void (&)(int)>();
    test_is_not_safe_unsigned<void (&)(int) noexcept>();

    test_is_not_safe_unsigned<void (&)(...)>();
    test_is_not_safe_unsigned<void (&)(...) noexcept>();

    test_is_not_safe_unsigned<void (&)(int, ...)>();
    test_is_not_safe_unsigned<void (&)(int, ...) noexcept>();

    test_is_not_safe_unsigned<int (&)()>();
    test_is_not_safe_unsigned<int (&)() noexcept>();

    test_is_not_safe_unsigned<int (&)(int)>();
    test_is_not_safe_unsigned<int (&)(int) noexcept>();

    test_is_not_safe_unsigned<int (&)(...)>();
    test_is_not_safe_unsigned<int (&)(...) noexcept>();

    test_is_not_safe_unsigned<int (&)(int, ...)>();
    test_is_not_safe_unsigned<int (&)(int, ...) noexcept>();

    test_is_not_safe_unsigned<void(&&)()>();
    test_is_not_safe_unsigned<void(&&)() noexcept>();

    test_is_not_safe_unsigned<void(&&)(int)>();
    test_is_not_safe_unsigned<void(&&)(int) noexcept>();

    test_is_not_safe_unsigned<void(&&)(...)>();
    test_is_not_safe_unsigned<void(&&)(...) noexcept>();

    test_is_not_safe_unsigned<void(&&)(int, ...)>();
    test_is_not_safe_unsigned<void(&&)(int, ...) noexcept>();

    test_is_not_safe_unsigned<int(&&)()>();
    test_is_not_safe_unsigned<int(&&)() noexcept>();

    test_is_not_safe_unsigned<int(&&)(int)>();
    test_is_not_safe_unsigned<int(&&)(int) noexcept>();

    test_is_not_safe_unsigned<int(&&)(...)>();
    test_is_not_safe_unsigned<int(&&)(...) noexcept>();

    test_is_not_safe_unsigned<int(&&)(int, ...)>();
    test_is_not_safe_unsigned<int(&&)(int, ...) noexcept>();

    test_is_not_safe_unsigned<void (Class::*)()>();
    test_is_not_safe_unsigned<void (Class::*)()&>();
    test_is_not_safe_unsigned<void (Class::*)() &&>();
    test_is_not_safe_unsigned<void (Class::*)() const>();
    test_is_not_safe_unsigned<void (Class::*)() const&>();
    test_is_not_safe_unsigned<void (Class::*)() const&&>();
    test_is_not_safe_unsigned<void (Class::*)() noexcept>();
    test_is_not_safe_unsigned<void (Class::*)()& noexcept>();
    test_is_not_safe_unsigned<void (Class::*)()&& noexcept>();
    test_is_not_safe_unsigned<void (Class::*)() const noexcept>();
    test_is_not_safe_unsigned<void (Class::*)() const& noexcept>();
    test_is_not_safe_unsigned<void (Class::*)() const&& noexcept>();

    test_is_not_safe_unsigned<void (Class::*)(int)>();
    test_is_not_safe_unsigned<void (Class::*)(int)&>();
    test_is_not_safe_unsigned<void (Class::*)(int) &&>();
    test_is_not_safe_unsigned<void (Class::*)(int) const>();
    test_is_not_safe_unsigned<void (Class::*)(int) const&>();
    test_is_not_safe_unsigned<void (Class::*)(int) const&&>();
    test_is_not_safe_unsigned<void (Class::*)(int) noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(int)& noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(int)&& noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(int) const noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(int) const& noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(int) const&& noexcept>();

    test_is_not_safe_unsigned<void (Class::*)(...)>();
    test_is_not_safe_unsigned<void (Class::*)(...)&>();
    test_is_not_safe_unsigned<void (Class::*)(...) &&>();
    test_is_not_safe_unsigned<void (Class::*)(...) const>();
    test_is_not_safe_unsigned<void (Class::*)(...) const&>();
    test_is_not_safe_unsigned<void (Class::*)(...) const&&>();
    test_is_not_safe_unsigned<void (Class::*)(...) noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(...)& noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(...)&& noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(...) const noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(...) const& noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(...) const&& noexcept>();

    test_is_not_safe_unsigned<void (Class::*)(int, ...)>();
    test_is_not_safe_unsigned<void (Class::*)(int, ...)&>();
    test_is_not_safe_unsigned<void (Class::*)(int, ...) &&>();
    test_is_not_safe_unsigned<void (Class::*)(int, ...) const>();
    test_is_not_safe_unsigned<void (Class::*)(int, ...) const&>();
    test_is_not_safe_unsigned<void (Class::*)(int, ...) const&&>();
    test_is_not_safe_unsigned<void (Class::*)(int, ...) noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_unsigned<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_safe_unsigned<int (Class::*)()>();
    test_is_not_safe_unsigned<int (Class::*)()&>();
    test_is_not_safe_unsigned<int (Class::*)() &&>();
    test_is_not_safe_unsigned<int (Class::*)() const>();
    test_is_not_safe_unsigned<int (Class::*)() const&>();
    test_is_not_safe_unsigned<int (Class::*)() const&&>();
    test_is_not_safe_unsigned<int (Class::*)() noexcept>();
    test_is_not_safe_unsigned<int (Class::*)()& noexcept>();
    test_is_not_safe_unsigned<int (Class::*)()&& noexcept>();
    test_is_not_safe_unsigned<int (Class::*)() const noexcept>();
    test_is_not_safe_unsigned<int (Class::*)() const& noexcept>();
    test_is_not_safe_unsigned<int (Class::*)() const&& noexcept>();

    test_is_not_safe_unsigned<int (Class::*)(int)>();
    test_is_not_safe_unsigned<int (Class::*)(int)&>();
    test_is_not_safe_unsigned<int (Class::*)(int) &&>();
    test_is_not_safe_unsigned<int (Class::*)(int) const>();
    test_is_not_safe_unsigned<int (Class::*)(int) const&>();
    test_is_not_safe_unsigned<int (Class::*)(int) const&&>();
    test_is_not_safe_unsigned<int (Class::*)(int) noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(int)& noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(int)&& noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(int) const noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(int) const& noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(int) const&& noexcept>();

    test_is_not_safe_unsigned<int (Class::*)(...)>();
    test_is_not_safe_unsigned<int (Class::*)(...)&>();
    test_is_not_safe_unsigned<int (Class::*)(...) &&>();
    test_is_not_safe_unsigned<int (Class::*)(...) const>();
    test_is_not_safe_unsigned<int (Class::*)(...) const&>();
    test_is_not_safe_unsigned<int (Class::*)(...) const&&>();
    test_is_not_safe_unsigned<int (Class::*)(...) noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(...)& noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(...)&& noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(...) const noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(...) const& noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(...) const&& noexcept>();

    test_is_not_safe_unsigned<int (Class::*)(int, ...)>();
    test_is_not_safe_unsigned<int (Class::*)(int, ...)&>();
    test_is_not_safe_unsigned<int (Class::*)(int, ...) &&>();
    test_is_not_safe_unsigned<int (Class::*)(int, ...) const>();
    test_is_not_safe_unsigned<int (Class::*)(int, ...) const&>();
    test_is_not_safe_unsigned<int (Class::*)(int, ...) const&&>();
    test_is_not_safe_unsigned<int (Class::*)(int, ...) noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_unsigned<int (Class::*)(int, ...) const&& noexcept>();
}
