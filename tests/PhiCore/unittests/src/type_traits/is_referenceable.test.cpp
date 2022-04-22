#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_referenceable.hpp>
#include <vector>

template <typename T>
void test_is_referenceable_impl()
{
    STATIC_REQUIRE(phi::is_referenceable<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_referenceable<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_referenceable_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_referenceable_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_referenceable<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_referenceable<T>);
}

template <typename T>
void test_is_not_referenceable_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_referenceable<T>::value);
    STATIC_REQUIRE(phi::is_not_referenceable<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_referenceable_v<T>);
    STATIC_REQUIRE(phi::is_not_referenceable_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_referenceable<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_referenceable<T>);
}

template <typename T>
void test_is_referenceable()
{
    test_is_referenceable_impl<T>();
    test_is_referenceable_impl<const T>();
    test_is_referenceable_impl<volatile T>();
    test_is_referenceable_impl<const volatile T>();
}

template <typename T>
void test_is_not_referenceable()
{
    test_is_not_referenceable_impl<T>();
    test_is_not_referenceable_impl<const T>();
    test_is_not_referenceable_impl<volatile T>();
    test_is_not_referenceable_impl<const volatile T>();
}

TEST_CASE("is_referenceable")
{
    test_is_not_referenceable<void>();
    test_is_referenceable<phi::nullptr_t>();
    test_is_referenceable<bool>();
    test_is_referenceable<char>();
    test_is_referenceable<signed char>();
    test_is_referenceable<unsigned char>();
    test_is_referenceable<short>();
    test_is_referenceable<unsigned short>();
    test_is_referenceable<int>();
    test_is_referenceable<unsigned int>();
    test_is_referenceable<long>();
    test_is_referenceable<unsigned long>();
    test_is_referenceable<long long>();
    test_is_referenceable<unsigned long long>();
    test_is_referenceable<float>();
    test_is_referenceable<double>();
    test_is_referenceable<long double>();
    test_is_referenceable<char8_t>();
    test_is_referenceable<char16_t>();
    test_is_referenceable<char32_t>();
    test_is_referenceable<wchar_t>();

    test_is_referenceable<phi::boolean>();
    test_is_referenceable<phi::integer<signed char>>();
    test_is_referenceable<phi::integer<unsigned char>>();
    test_is_referenceable<phi::integer<short>>();
    test_is_referenceable<phi::integer<unsigned short>>();
    test_is_referenceable<phi::integer<int>>();
    test_is_referenceable<phi::integer<unsigned int>>();
    test_is_referenceable<phi::integer<long>>();
    test_is_referenceable<phi::integer<unsigned long>>();
    test_is_referenceable<phi::integer<long long>>();
    test_is_referenceable<phi::integer<unsigned long long>>();
    test_is_referenceable<phi::floating_point<float>>();
    test_is_referenceable<phi::floating_point<double>>();
    test_is_referenceable<phi::floating_point<long double>>();

    test_is_referenceable<std::vector<int>>();
    test_is_referenceable<phi::scope_ptr<int>>();

    test_is_referenceable<int&>();
    test_is_referenceable<const int&>();
    test_is_referenceable<volatile int&>();
    test_is_referenceable<const volatile int&>();
    test_is_referenceable<int&&>();
    test_is_referenceable<const int&&>();
    test_is_referenceable<volatile int&&>();
    test_is_referenceable<const volatile int&&>();
    test_is_referenceable<int*>();
    test_is_referenceable<const int*>();
    test_is_referenceable<volatile int*>();
    test_is_referenceable<const volatile int*>();
    test_is_referenceable<int**>();
    test_is_referenceable<const int**>();
    test_is_referenceable<volatile int**>();
    test_is_referenceable<const volatile int**>();
    test_is_referenceable<int*&>();
    test_is_referenceable<const int*&>();
    test_is_referenceable<volatile int*&>();
    test_is_referenceable<const volatile int*&>();
    test_is_referenceable<int*&&>();
    test_is_referenceable<const int*&&>();
    test_is_referenceable<volatile int*&&>();
    test_is_referenceable<const volatile int*&&>();
    test_is_referenceable<void*>();
    test_is_referenceable<char[3]>();
    test_is_referenceable<char[]>();
    test_is_referenceable<char* [3]>();
    test_is_referenceable<char*[]>();
    test_is_referenceable<int(*)[3]>();
    test_is_referenceable<int(*)[]>();
    test_is_referenceable<int(&)[3]>();
    test_is_referenceable<int(&)[]>();
    test_is_referenceable<int(&&)[3]>();
    test_is_referenceable<int(&&)[]>();
    test_is_referenceable<char[3][2]>();
    test_is_referenceable<char[][2]>();
    test_is_referenceable<char* [3][2]>();
    test_is_referenceable<char*[][2]>();
    test_is_referenceable<int(*)[3][2]>();
    test_is_referenceable<int(*)[][2]>();
    test_is_referenceable<int(&)[3][2]>();
    test_is_referenceable<int(&)[][2]>();
    test_is_referenceable<int(&&)[3][2]>();
    test_is_referenceable<int(&&)[][2]>();
    test_is_referenceable<Class>();
    test_is_referenceable<Class[]>();
    test_is_referenceable<Class[2]>();
    test_is_referenceable<Template<void>>();
    test_is_referenceable<Template<int>>();
    test_is_referenceable<Template<Class>>();
    test_is_referenceable<Template<IncompleteType>>();
    test_is_referenceable<VariadicTemplate<>>();
    test_is_referenceable<VariadicTemplate<void>>();
    test_is_referenceable<VariadicTemplate<int>>();
    test_is_referenceable<VariadicTemplate<Class>>();
    test_is_referenceable<VariadicTemplate<IncompleteType>>();
    test_is_referenceable<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_referenceable<PublicDerivedFromTemplate<Base>>();
    test_is_referenceable<PublicDerivedFromTemplate<Derived>>();
    test_is_referenceable<PublicDerivedFromTemplate<Class>>();
    test_is_referenceable<PrivateDerivedFromTemplate<Base>>();
    test_is_referenceable<PrivateDerivedFromTemplate<Derived>>();
    test_is_referenceable<PrivateDerivedFromTemplate<Class>>();
    test_is_referenceable<ProtectedDerivedFromTemplate<Base>>();
    test_is_referenceable<ProtectedDerivedFromTemplate<Derived>>();
    test_is_referenceable<ProtectedDerivedFromTemplate<Class>>();
    test_is_referenceable<VirtualDerivedFromTemplate<Base>>();
    test_is_referenceable<VirtualDerivedFromTemplate<Derived>>();
    test_is_referenceable<VirtualDerivedFromTemplate<Class>>();
    test_is_referenceable<Union>();
    test_is_referenceable<NonEmptyUnion>();
    test_is_referenceable<NonTrivialUnion>();
    test_is_referenceable<Empty>();
    test_is_referenceable<NotEmpty>();
    test_is_referenceable<NonTrivial>();
    test_is_referenceable<BitZero>();
    test_is_referenceable<BitOne>();
    test_is_referenceable<Base>();
    test_is_referenceable<Derived>();
    test_is_referenceable<NotEmptyBase>();
    test_is_referenceable<EmptyBase>();
    test_is_referenceable<VirtualBase>();
    test_is_referenceable<Polymorphic>();
    test_is_referenceable<DerivedPolymorphic>();
    test_is_referenceable<Abstract>();
    test_is_referenceable<PublicAbstract>();
    test_is_referenceable<PrivateAbstract>();
    test_is_referenceable<ProtectedAbstract>();
    test_is_referenceable<AbstractTemplate<int>>();
    test_is_referenceable<AbstractTemplate<double>>();
    test_is_referenceable<AbstractTemplate<Class>>();
    test_is_referenceable<AbstractTemplate<IncompleteType>>();
    test_is_referenceable<PublicAbstractDeletedDestructor>();
    test_is_referenceable<ProtectedAbstractDeletedDestructor>();
    test_is_referenceable<PrivateAbstractDeletedDestructor>();
    test_is_referenceable<Final>();
    test_is_referenceable<FinalDerived>();
    test_is_referenceable<PublicDestructor>();
    test_is_referenceable<ProtectedDestructor>();
    test_is_referenceable<PrivateDestructor>();
    test_is_referenceable<VirtualPublicDestructor>();
    test_is_referenceable<VirtualProtectedDestructor>();
    test_is_referenceable<VirtualPrivateDestructor>();
    test_is_referenceable<PurePublicDestructor>();
    test_is_referenceable<PureProtectedDestructor>();
    test_is_referenceable<PurePrivateDestructor>();
    test_is_referenceable<DeletedPublicDestructor>();
    test_is_referenceable<DeletedProtectedDestructor>();
    test_is_referenceable<DeletedPrivateDestructor>();
    test_is_referenceable<DeletedVirtualPublicDestructor>();
    test_is_referenceable<DeletedVirtualProtectedDestructor>();
    test_is_referenceable<DeletedVirtualPrivateDestructor>();
    test_is_referenceable<ExplicitClass>();
    test_is_referenceable<NothrowExplicitClass>();
    test_is_referenceable<ThrowExplicitClass>();
    test_is_referenceable<ThrowDefaultClass>();
    test_is_referenceable<ThrowCopyConsClass>();
    test_is_referenceable<ThrowMoveConsClass>();
    test_is_referenceable<ThrowDestructor>();
    test_is_referenceable<NoexceptExplicitClass>();
    test_is_referenceable<ExceptExplicitClass>();
    test_is_referenceable<NoexceptDefaultClass>();
    test_is_referenceable<ExceptDefaultClass>();
    test_is_referenceable<NoexceptCopyConsClass>();
    test_is_referenceable<ExceptCopyConsClass>();
    test_is_referenceable<NoexceptMoveConsClass>();
    test_is_referenceable<ExceptMoveConsClass>();
    test_is_referenceable<NoexceptCopyAssignClass>();
    test_is_referenceable<ExceptCopyAssignClass>();
    test_is_referenceable<NoexceptMoveAssignClass>();
    test_is_referenceable<ExceptMoveAssignClass>();
    test_is_referenceable<DeletedCopyAssignClass>();
    test_is_referenceable<DeletedMoveAssignClass>();
    test_is_referenceable<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_referenceable<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_referenceable<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_referenceable<ExceptMoveConsExceptMoveAssignClass>();
    test_is_referenceable<ImplicitTo<int>>();
    test_is_referenceable<ImplicitTo<float>>();
    test_is_referenceable<ImplicitTo<Class>>();
    test_is_referenceable<DeletedImplicitTo<int>>();
    test_is_referenceable<DeletedImplicitTo<float>>();
    test_is_referenceable<DeletedImplicitTo<Class>>();
    test_is_referenceable<ExplicitTo<int>>();
    test_is_referenceable<ExplicitTo<float>>();
    test_is_referenceable<ExplicitTo<Class>>();
    test_is_referenceable<DeletedExplicitTo<int>>();
    test_is_referenceable<DeletedExplicitTo<float>>();
    test_is_referenceable<DeletedExplicitTo<Class>>();
    test_is_referenceable<Ellipsis>();
    test_is_referenceable<DeletedEllipsis>();
    test_is_referenceable<CopyConsOnlyType>();
    test_is_referenceable<MoveConsOnlyType>();
    test_is_referenceable<OverloadedOperators>();
    test_is_referenceable<PublicIntMember>();
    test_is_referenceable<ProtectedIntMember>();
    test_is_referenceable<PrivateIntMember>();
    test_is_referenceable<PublicStaticIntMember>();
    test_is_referenceable<ProtectedStaticIntMember>();
    test_is_referenceable<PrivateStaticIntMember>();
    test_is_referenceable<PublicTemplateMember<int>>();
    test_is_referenceable<PublicTemplateMember<float>>();
    test_is_referenceable<PublicTemplateMember<Class>>();
    test_is_referenceable<ProtectedTemplateMember<int>>();
    test_is_referenceable<ProtectedTemplateMember<float>>();
    test_is_referenceable<ProtectedTemplateMember<Class>>();
    test_is_referenceable<PrivateTemplateMember<int>>();
    test_is_referenceable<PrivateTemplateMember<float>>();
    test_is_referenceable<PrivateTemplateMember<Class>>();
    test_is_referenceable<PublicStaticTemplateMember<int>>();
    test_is_referenceable<PublicStaticTemplateMember<float>>();
    test_is_referenceable<PublicStaticTemplateMember<Class>>();
    test_is_referenceable<ProtectedStaticTemplateMember<int>>();
    test_is_referenceable<ProtectedStaticTemplateMember<float>>();
    test_is_referenceable<ProtectedStaticTemplateMember<Class>>();
    test_is_referenceable<PrivateStaticTemplateMember<int>>();
    test_is_referenceable<PrivateStaticTemplateMember<float>>();
    test_is_referenceable<PrivateStaticTemplateMember<Class>>();
    test_is_referenceable<CannotInstantiate<int>>();
    test_is_referenceable<CannotInstantiate<float>>();
    test_is_referenceable<CannotInstantiate<Class>>();
    test_is_referenceable<Enum>();
    test_is_referenceable<EnumSigned>();
    test_is_referenceable<EnumUnsigned>();
    test_is_referenceable<EnumClass>();
    test_is_referenceable<EnumStruct>();
    test_is_referenceable<Function>();
    test_is_referenceable<FunctionPtr>();
    test_is_referenceable<MemberObjectPtr>();
    test_is_referenceable<MemberFunctionPtr>();
    test_is_referenceable<LambdaType>();
    test_is_referenceable<LambdaNoexceptType>();
    test_is_referenceable<LambdaThrowsType>();
    test_is_referenceable<IncompleteType>();
    test_is_referenceable<IncompleteTemplate<void>>();
    test_is_referenceable<IncompleteTemplate<int>>();
    test_is_referenceable<IncompleteTemplate<Class>>();
    test_is_referenceable<IncompleteTemplate<IncompleteType>>();
    test_is_referenceable<IncompleteVariadicTemplate<>>();
    test_is_referenceable<IncompleteVariadicTemplate<void>>();
    test_is_referenceable<IncompleteVariadicTemplate<int>>();
    test_is_referenceable<IncompleteVariadicTemplate<Class>>();
    test_is_referenceable<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_referenceable<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_referenceable<IncompleteUnion>();
    test_is_referenceable<IncompleteEnumSigned>();
    test_is_referenceable<IncompleteEnumUnsigned>();
    test_is_referenceable<IncompleteEnumClass>();
    test_is_referenceable<IncompleteEnumStruct>();
    test_is_referenceable<int Class::*>();
    test_is_referenceable<float Class::*>();
    test_is_referenceable<void * Class::*>();
    test_is_referenceable<int * Class::*>();
    test_is_referenceable<int Class::*&>();
    test_is_referenceable<float Class::*&>();
    test_is_referenceable<void * Class::*&>();
    test_is_referenceable<int * Class::*&>();
    test_is_referenceable<int Class::*&&>();
    test_is_referenceable<float Class::*&&>();
    test_is_referenceable<void * Class::*&&>();
    test_is_referenceable<int * Class::*&&>();
    test_is_referenceable<int Class::*const>();
    test_is_referenceable<float Class::*const>();
    test_is_referenceable<void * Class::*const>();
    test_is_referenceable<int Class::*const&>();
    test_is_referenceable<float Class::*const&>();
    test_is_referenceable<void * Class::*const&>();
    test_is_referenceable<int Class::*const&&>();
    test_is_referenceable<float Class::*const&&>();
    test_is_referenceable<void * Class::*const&&>();
    test_is_referenceable<int Class::*volatile>();
    test_is_referenceable<float Class::*volatile>();
    test_is_referenceable<void * Class::*volatile>();
    test_is_referenceable<int Class::*volatile&>();
    test_is_referenceable<float Class::*volatile&>();
    test_is_referenceable<void * Class::*volatile&>();
    test_is_referenceable<int Class::*volatile&&>();
    test_is_referenceable<float Class::*volatile&&>();
    test_is_referenceable<void * Class::*volatile&&>();
    test_is_referenceable<int Class::*const volatile>();
    test_is_referenceable<float Class::*const volatile>();
    test_is_referenceable<void * Class::*const volatile>();
    test_is_referenceable<int Class::*const volatile&>();
    test_is_referenceable<float Class::*const volatile&>();
    test_is_referenceable<void * Class::*const volatile&>();
    test_is_referenceable<int Class::*const volatile&&>();
    test_is_referenceable<float Class::*const volatile&&>();
    test_is_referenceable<void * Class::*const volatile&&>();
    test_is_referenceable<NonDefaultConstructible>();
    test_is_referenceable<NonCopyConstructible>();
    test_is_referenceable<NonMoveConstructible>();
    test_is_referenceable<NonCopyAssignable>();
    test_is_referenceable<NonMoveAssignable>();
    test_is_referenceable<NonAssignable>();
    test_is_referenceable<NonCopyable>();
    test_is_referenceable<NonMoveable>();
    test_is_referenceable<NonConstructible>();
    test_is_referenceable<NonDestructible>();
    test_is_referenceable<Tracked>();
    test_is_referenceable<TrapConstructible>();
    test_is_referenceable<TrapImplicitConversion>();
    test_is_referenceable<TrapComma>();
    test_is_referenceable<TrapCall>();
    test_is_referenceable<TrapSelfAssign>();
    test_is_referenceable<TrapDeref>();
    test_is_referenceable<TrapArraySubscript>();

    test_is_referenceable<void()>();
    test_is_not_referenceable<void()&>();
    test_is_not_referenceable<void() &&>();
    test_is_not_referenceable<void() const>();
    test_is_not_referenceable<void() const&>();
    test_is_not_referenceable<void() const&&>();
    test_is_not_referenceable<void() volatile>();
    test_is_not_referenceable<void() volatile&>();
    test_is_not_referenceable<void() volatile&&>();
    test_is_not_referenceable<void() const volatile>();
    test_is_not_referenceable<void() const volatile&>();
    test_is_not_referenceable<void() const volatile&&>();
    test_is_referenceable<void() noexcept>();
    test_is_not_referenceable<void()& noexcept>();
    test_is_not_referenceable<void()&& noexcept>();
    test_is_not_referenceable<void() const noexcept>();
    test_is_not_referenceable<void() const& noexcept>();
    test_is_not_referenceable<void() const&& noexcept>();
    test_is_not_referenceable<void() volatile noexcept>();
    test_is_not_referenceable<void() volatile& noexcept>();
    test_is_not_referenceable<void() volatile&& noexcept>();
    test_is_not_referenceable<void() const volatile noexcept>();
    test_is_not_referenceable<void() const volatile& noexcept>();
    test_is_not_referenceable<void() const volatile&& noexcept>();

    test_is_referenceable<void(int)>();
    test_is_not_referenceable<void(int)&>();
    test_is_not_referenceable<void(int) &&>();
    test_is_not_referenceable<void(int) const>();
    test_is_not_referenceable<void(int) const&>();
    test_is_not_referenceable<void(int) const&&>();
    test_is_not_referenceable<void(int) volatile>();
    test_is_not_referenceable<void(int) volatile&>();
    test_is_not_referenceable<void(int) volatile&&>();
    test_is_not_referenceable<void(int) const volatile>();
    test_is_not_referenceable<void(int) const volatile&>();
    test_is_not_referenceable<void(int) const volatile&&>();
    test_is_referenceable<void(int) noexcept>();
    test_is_not_referenceable<void(int)& noexcept>();
    test_is_not_referenceable<void(int)&& noexcept>();
    test_is_not_referenceable<void(int) const noexcept>();
    test_is_not_referenceable<void(int) const& noexcept>();
    test_is_not_referenceable<void(int) const&& noexcept>();
    test_is_not_referenceable<void(int) volatile noexcept>();
    test_is_not_referenceable<void(int) volatile& noexcept>();
    test_is_not_referenceable<void(int) volatile&& noexcept>();
    test_is_not_referenceable<void(int) const volatile noexcept>();
    test_is_not_referenceable<void(int) const volatile& noexcept>();
    test_is_not_referenceable<void(int) const volatile&& noexcept>();

    test_is_referenceable<void(...)>();
    test_is_not_referenceable<void(...)&>();
    test_is_not_referenceable<void(...) &&>();
    test_is_not_referenceable<void(...) const>();
    test_is_not_referenceable<void(...) const&>();
    test_is_not_referenceable<void(...) const&&>();
    test_is_not_referenceable<void(...) volatile>();
    test_is_not_referenceable<void(...) volatile&>();
    test_is_not_referenceable<void(...) volatile&&>();
    test_is_not_referenceable<void(...) const volatile>();
    test_is_not_referenceable<void(...) const volatile&>();
    test_is_not_referenceable<void(...) const volatile&&>();
    test_is_referenceable<void(...) noexcept>();
    test_is_not_referenceable<void(...)& noexcept>();
    test_is_not_referenceable<void(...)&& noexcept>();
    test_is_not_referenceable<void(...) const noexcept>();
    test_is_not_referenceable<void(...) const& noexcept>();
    test_is_not_referenceable<void(...) const&& noexcept>();
    test_is_not_referenceable<void(...) volatile noexcept>();
    test_is_not_referenceable<void(...) volatile& noexcept>();
    test_is_not_referenceable<void(...) volatile&& noexcept>();
    test_is_not_referenceable<void(...) const volatile noexcept>();
    test_is_not_referenceable<void(...) const volatile& noexcept>();
    test_is_not_referenceable<void(...) const volatile&& noexcept>();

    test_is_referenceable<void(int, ...)>();
    test_is_not_referenceable<void(int, ...)&>();
    test_is_not_referenceable<void(int, ...) &&>();
    test_is_not_referenceable<void(int, ...) const>();
    test_is_not_referenceable<void(int, ...) const&>();
    test_is_not_referenceable<void(int, ...) const&&>();
    test_is_not_referenceable<void(int, ...) volatile>();
    test_is_not_referenceable<void(int, ...) volatile&>();
    test_is_not_referenceable<void(int, ...) volatile&&>();
    test_is_not_referenceable<void(int, ...) const volatile>();
    test_is_not_referenceable<void(int, ...) const volatile&>();
    test_is_not_referenceable<void(int, ...) const volatile&&>();
    test_is_referenceable<void(int, ...) noexcept>();
    test_is_not_referenceable<void(int, ...)& noexcept>();
    test_is_not_referenceable<void(int, ...)&& noexcept>();
    test_is_not_referenceable<void(int, ...) const noexcept>();
    test_is_not_referenceable<void(int, ...) const& noexcept>();
    test_is_not_referenceable<void(int, ...) const&& noexcept>();
    test_is_not_referenceable<void(int, ...) volatile noexcept>();
    test_is_not_referenceable<void(int, ...) volatile& noexcept>();
    test_is_not_referenceable<void(int, ...) volatile&& noexcept>();
    test_is_not_referenceable<void(int, ...) const volatile noexcept>();
    test_is_not_referenceable<void(int, ...) const volatile& noexcept>();
    test_is_not_referenceable<void(int, ...) const volatile&& noexcept>();

    test_is_referenceable<int()>();
    test_is_not_referenceable<int()&>();
    test_is_not_referenceable<int() &&>();
    test_is_not_referenceable<int() const>();
    test_is_not_referenceable<int() const&>();
    test_is_not_referenceable<int() const&&>();
    test_is_not_referenceable<int() volatile>();
    test_is_not_referenceable<int() volatile&>();
    test_is_not_referenceable<int() volatile&&>();
    test_is_not_referenceable<int() const volatile>();
    test_is_not_referenceable<int() const volatile&>();
    test_is_not_referenceable<int() const volatile&&>();
    test_is_referenceable<int() noexcept>();
    test_is_not_referenceable<int()& noexcept>();
    test_is_not_referenceable<int()&& noexcept>();
    test_is_not_referenceable<int() const noexcept>();
    test_is_not_referenceable<int() const& noexcept>();
    test_is_not_referenceable<int() const&& noexcept>();
    test_is_not_referenceable<int() volatile noexcept>();
    test_is_not_referenceable<int() volatile& noexcept>();
    test_is_not_referenceable<int() volatile&& noexcept>();
    test_is_not_referenceable<int() const volatile noexcept>();
    test_is_not_referenceable<int() const volatile& noexcept>();
    test_is_not_referenceable<int() const volatile&& noexcept>();

    test_is_referenceable<int(int)>();
    test_is_not_referenceable<int(int)&>();
    test_is_not_referenceable<int(int) &&>();
    test_is_not_referenceable<int(int) const>();
    test_is_not_referenceable<int(int) const&>();
    test_is_not_referenceable<int(int) const&&>();
    test_is_not_referenceable<int(int) volatile>();
    test_is_not_referenceable<int(int) volatile&>();
    test_is_not_referenceable<int(int) volatile&&>();
    test_is_not_referenceable<int(int) const volatile>();
    test_is_not_referenceable<int(int) const volatile&>();
    test_is_not_referenceable<int(int) const volatile&&>();
    test_is_referenceable<int(int) noexcept>();
    test_is_not_referenceable<int(int)& noexcept>();
    test_is_not_referenceable<int(int)&& noexcept>();
    test_is_not_referenceable<int(int) const noexcept>();
    test_is_not_referenceable<int(int) const& noexcept>();
    test_is_not_referenceable<int(int) const&& noexcept>();
    test_is_not_referenceable<int(int) volatile noexcept>();
    test_is_not_referenceable<int(int) volatile& noexcept>();
    test_is_not_referenceable<int(int) volatile&& noexcept>();
    test_is_not_referenceable<int(int) const volatile noexcept>();
    test_is_not_referenceable<int(int) const volatile& noexcept>();
    test_is_not_referenceable<int(int) const volatile&& noexcept>();

    test_is_referenceable<int(...)>();
    test_is_not_referenceable<int(...)&>();
    test_is_not_referenceable<int(...) &&>();
    test_is_not_referenceable<int(...) const>();
    test_is_not_referenceable<int(...) const&>();
    test_is_not_referenceable<int(...) const&&>();
    test_is_not_referenceable<int(...) volatile>();
    test_is_not_referenceable<int(...) volatile&>();
    test_is_not_referenceable<int(...) volatile&&>();
    test_is_not_referenceable<int(...) const volatile>();
    test_is_not_referenceable<int(...) const volatile&>();
    test_is_not_referenceable<int(...) const volatile&&>();
    test_is_referenceable<int(...) noexcept>();
    test_is_not_referenceable<int(...)& noexcept>();
    test_is_not_referenceable<int(...)&& noexcept>();
    test_is_not_referenceable<int(...) const noexcept>();
    test_is_not_referenceable<int(...) const& noexcept>();
    test_is_not_referenceable<int(...) const&& noexcept>();
    test_is_not_referenceable<int(...) volatile noexcept>();
    test_is_not_referenceable<int(...) volatile& noexcept>();
    test_is_not_referenceable<int(...) volatile&& noexcept>();
    test_is_not_referenceable<int(...) const volatile noexcept>();
    test_is_not_referenceable<int(...) const volatile& noexcept>();
    test_is_not_referenceable<int(...) const volatile&& noexcept>();

    test_is_referenceable<int(int, ...)>();
    test_is_not_referenceable<int(int, ...)&>();
    test_is_not_referenceable<int(int, ...) &&>();
    test_is_not_referenceable<int(int, ...) const>();
    test_is_not_referenceable<int(int, ...) const&>();
    test_is_not_referenceable<int(int, ...) const&&>();
    test_is_not_referenceable<int(int, ...) volatile>();
    test_is_not_referenceable<int(int, ...) volatile&>();
    test_is_not_referenceable<int(int, ...) volatile&&>();
    test_is_not_referenceable<int(int, ...) const volatile>();
    test_is_not_referenceable<int(int, ...) const volatile&>();
    test_is_not_referenceable<int(int, ...) const volatile&&>();
    test_is_referenceable<int(int, ...) noexcept>();
    test_is_not_referenceable<int(int, ...)& noexcept>();
    test_is_not_referenceable<int(int, ...)&& noexcept>();
    test_is_not_referenceable<int(int, ...) const noexcept>();
    test_is_not_referenceable<int(int, ...) const& noexcept>();
    test_is_not_referenceable<int(int, ...) const&& noexcept>();
    test_is_not_referenceable<int(int, ...) volatile noexcept>();
    test_is_not_referenceable<int(int, ...) volatile& noexcept>();
    test_is_not_referenceable<int(int, ...) volatile&& noexcept>();
    test_is_not_referenceable<int(int, ...) const volatile noexcept>();
    test_is_not_referenceable<int(int, ...) const volatile& noexcept>();
    test_is_not_referenceable<int(int, ...) const volatile&& noexcept>();

    test_is_referenceable<void (*)()>();
    test_is_referenceable<void (*)() noexcept>();

    test_is_referenceable<void (*)(int)>();
    test_is_referenceable<void (*)(int) noexcept>();

    test_is_referenceable<void (*)(...)>();
    test_is_referenceable<void (*)(...) noexcept>();

    test_is_referenceable<void (*)(int, ...)>();
    test_is_referenceable<void (*)(int, ...) noexcept>();

    test_is_referenceable<int (*)()>();
    test_is_referenceable<int (*)() noexcept>();

    test_is_referenceable<int (*)(int)>();
    test_is_referenceable<int (*)(int) noexcept>();

    test_is_referenceable<int (*)(...)>();
    test_is_referenceable<int (*)(...) noexcept>();

    test_is_referenceable<int (*)(int, ...)>();
    test_is_referenceable<int (*)(int, ...) noexcept>();

    test_is_referenceable<void (&)()>();
    test_is_referenceable<void (&)() noexcept>();

    test_is_referenceable<void (&)(int)>();
    test_is_referenceable<void (&)(int) noexcept>();

    test_is_referenceable<void (&)(...)>();
    test_is_referenceable<void (&)(...) noexcept>();

    test_is_referenceable<void (&)(int, ...)>();
    test_is_referenceable<void (&)(int, ...) noexcept>();

    test_is_referenceable<int (&)()>();
    test_is_referenceable<int (&)() noexcept>();

    test_is_referenceable<int (&)(int)>();
    test_is_referenceable<int (&)(int) noexcept>();

    test_is_referenceable<int (&)(...)>();
    test_is_referenceable<int (&)(...) noexcept>();

    test_is_referenceable<int (&)(int, ...)>();
    test_is_referenceable<int (&)(int, ...) noexcept>();

    test_is_referenceable<void(&&)()>();
    test_is_referenceable<void(&&)() noexcept>();

    test_is_referenceable<void(&&)(int)>();
    test_is_referenceable<void(&&)(int) noexcept>();

    test_is_referenceable<void(&&)(...)>();
    test_is_referenceable<void(&&)(...) noexcept>();

    test_is_referenceable<void(&&)(int, ...)>();
    test_is_referenceable<void(&&)(int, ...) noexcept>();

    test_is_referenceable<int(&&)()>();
    test_is_referenceable<int(&&)() noexcept>();

    test_is_referenceable<int(&&)(int)>();
    test_is_referenceable<int(&&)(int) noexcept>();

    test_is_referenceable<int(&&)(...)>();
    test_is_referenceable<int(&&)(...) noexcept>();

    test_is_referenceable<int(&&)(int, ...)>();
    test_is_referenceable<int(&&)(int, ...) noexcept>();

    test_is_referenceable<void (Class::*)()>();
    test_is_referenceable<void (Class::*)()&>();
    test_is_referenceable<void (Class::*)() &&>();
    test_is_referenceable<void (Class::*)() const>();
    test_is_referenceable<void (Class::*)() const&>();
    test_is_referenceable<void (Class::*)() const&&>();
    test_is_referenceable<void (Class::*)() noexcept>();
    test_is_referenceable<void (Class::*)()& noexcept>();
    test_is_referenceable<void (Class::*)()&& noexcept>();
    test_is_referenceable<void (Class::*)() const noexcept>();
    test_is_referenceable<void (Class::*)() const& noexcept>();
    test_is_referenceable<void (Class::*)() const&& noexcept>();

    test_is_referenceable<void (Class::*)(int)>();
    test_is_referenceable<void (Class::*)(int)&>();
    test_is_referenceable<void (Class::*)(int) &&>();
    test_is_referenceable<void (Class::*)(int) const>();
    test_is_referenceable<void (Class::*)(int) const&>();
    test_is_referenceable<void (Class::*)(int) const&&>();
    test_is_referenceable<void (Class::*)(int) noexcept>();
    test_is_referenceable<void (Class::*)(int)& noexcept>();
    test_is_referenceable<void (Class::*)(int)&& noexcept>();
    test_is_referenceable<void (Class::*)(int) const noexcept>();
    test_is_referenceable<void (Class::*)(int) const& noexcept>();
    test_is_referenceable<void (Class::*)(int) const&& noexcept>();

    test_is_referenceable<void (Class::*)(...)>();
    test_is_referenceable<void (Class::*)(...)&>();
    test_is_referenceable<void (Class::*)(...) &&>();
    test_is_referenceable<void (Class::*)(...) const>();
    test_is_referenceable<void (Class::*)(...) const&>();
    test_is_referenceable<void (Class::*)(...) const&&>();
    test_is_referenceable<void (Class::*)(...) noexcept>();
    test_is_referenceable<void (Class::*)(...)& noexcept>();
    test_is_referenceable<void (Class::*)(...)&& noexcept>();
    test_is_referenceable<void (Class::*)(...) const noexcept>();
    test_is_referenceable<void (Class::*)(...) const& noexcept>();
    test_is_referenceable<void (Class::*)(...) const&& noexcept>();

    test_is_referenceable<void (Class::*)(int, ...)>();
    test_is_referenceable<void (Class::*)(int, ...)&>();
    test_is_referenceable<void (Class::*)(int, ...) &&>();
    test_is_referenceable<void (Class::*)(int, ...) const>();
    test_is_referenceable<void (Class::*)(int, ...) const&>();
    test_is_referenceable<void (Class::*)(int, ...) const&&>();
    test_is_referenceable<void (Class::*)(int, ...) noexcept>();
    test_is_referenceable<void (Class::*)(int, ...)& noexcept>();
    test_is_referenceable<void (Class::*)(int, ...)&& noexcept>();
    test_is_referenceable<void (Class::*)(int, ...) const noexcept>();
    test_is_referenceable<void (Class::*)(int, ...) const& noexcept>();
    test_is_referenceable<void (Class::*)(int, ...) const&& noexcept>();

    test_is_referenceable<int (Class::*)()>();
    test_is_referenceable<int (Class::*)()&>();
    test_is_referenceable<int (Class::*)() &&>();
    test_is_referenceable<int (Class::*)() const>();
    test_is_referenceable<int (Class::*)() const&>();
    test_is_referenceable<int (Class::*)() const&&>();
    test_is_referenceable<int (Class::*)() noexcept>();
    test_is_referenceable<int (Class::*)()& noexcept>();
    test_is_referenceable<int (Class::*)()&& noexcept>();
    test_is_referenceable<int (Class::*)() const noexcept>();
    test_is_referenceable<int (Class::*)() const& noexcept>();
    test_is_referenceable<int (Class::*)() const&& noexcept>();

    test_is_referenceable<int (Class::*)(int)>();
    test_is_referenceable<int (Class::*)(int)&>();
    test_is_referenceable<int (Class::*)(int) &&>();
    test_is_referenceable<int (Class::*)(int) const>();
    test_is_referenceable<int (Class::*)(int) const&>();
    test_is_referenceable<int (Class::*)(int) const&&>();
    test_is_referenceable<int (Class::*)(int) noexcept>();
    test_is_referenceable<int (Class::*)(int)& noexcept>();
    test_is_referenceable<int (Class::*)(int)&& noexcept>();
    test_is_referenceable<int (Class::*)(int) const noexcept>();
    test_is_referenceable<int (Class::*)(int) const& noexcept>();
    test_is_referenceable<int (Class::*)(int) const&& noexcept>();

    test_is_referenceable<int (Class::*)(...)>();
    test_is_referenceable<int (Class::*)(...)&>();
    test_is_referenceable<int (Class::*)(...) &&>();
    test_is_referenceable<int (Class::*)(...) const>();
    test_is_referenceable<int (Class::*)(...) const&>();
    test_is_referenceable<int (Class::*)(...) const&&>();
    test_is_referenceable<int (Class::*)(...) noexcept>();
    test_is_referenceable<int (Class::*)(...)& noexcept>();
    test_is_referenceable<int (Class::*)(...)&& noexcept>();
    test_is_referenceable<int (Class::*)(...) const noexcept>();
    test_is_referenceable<int (Class::*)(...) const& noexcept>();
    test_is_referenceable<int (Class::*)(...) const&& noexcept>();

    test_is_referenceable<int (Class::*)(int, ...)>();
    test_is_referenceable<int (Class::*)(int, ...)&>();
    test_is_referenceable<int (Class::*)(int, ...) &&>();
    test_is_referenceable<int (Class::*)(int, ...) const>();
    test_is_referenceable<int (Class::*)(int, ...) const&>();
    test_is_referenceable<int (Class::*)(int, ...) const&&>();
    test_is_referenceable<int (Class::*)(int, ...) noexcept>();
    test_is_referenceable<int (Class::*)(int, ...)& noexcept>();
    test_is_referenceable<int (Class::*)(int, ...)&& noexcept>();
    test_is_referenceable<int (Class::*)(int, ...) const noexcept>();
    test_is_referenceable<int (Class::*)(int, ...) const& noexcept>();
    test_is_referenceable<int (Class::*)(int, ...) const&& noexcept>();
}
