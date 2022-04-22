#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unsafe_fundamental.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_unsafe_fundamental_impl()
{
    STATIC_REQUIRE(phi::is_unsafe_fundamental<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_fundamental<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_fundamental_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_fundamental_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_fundamental<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_fundamental<T>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_fundamental<T>::value);
}

template <typename T>
void test_is_not_unsafe_fundamental_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_fundamental<T>::value);
    STATIC_REQUIRE(phi::is_not_unsafe_fundamental<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_fundamental_v<T>);
    STATIC_REQUIRE(phi::is_not_unsafe_fundamental_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_fundamental<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_fundamental<T>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_fundamental<T>::value);
}

template <typename T>
void test_is_unsafe_fundamental()
{
    test_is_unsafe_fundamental_impl<T>();
    test_is_unsafe_fundamental_impl<const T>();
    test_is_unsafe_fundamental_impl<volatile T>();
    test_is_unsafe_fundamental_impl<const volatile T>();
}

template <typename T>
void test_is_not_unsafe_fundamental()
{
    test_is_not_unsafe_fundamental_impl<T>();
    test_is_not_unsafe_fundamental_impl<const T>();
    test_is_not_unsafe_fundamental_impl<volatile T>();
    test_is_not_unsafe_fundamental_impl<const volatile T>();
}

TEST_CASE("is_unsafe_fundamental")
{
    test_is_unsafe_fundamental<void>();
    test_is_unsafe_fundamental<phi::nullptr_t>();
    test_is_unsafe_fundamental<bool>();
    test_is_unsafe_fundamental<char>();
    test_is_unsafe_fundamental<signed char>();
    test_is_unsafe_fundamental<unsigned char>();
    test_is_unsafe_fundamental<short>();
    test_is_unsafe_fundamental<unsigned short>();
    test_is_unsafe_fundamental<int>();
    test_is_unsafe_fundamental<unsigned int>();
    test_is_unsafe_fundamental<long>();
    test_is_unsafe_fundamental<unsigned long>();
    test_is_unsafe_fundamental<long long>();
    test_is_unsafe_fundamental<unsigned long long>();
    test_is_unsafe_fundamental<float>();
    test_is_unsafe_fundamental<double>();
    test_is_unsafe_fundamental<long double>();
    test_is_unsafe_fundamental<char8_t>();
    test_is_unsafe_fundamental<char16_t>();
    test_is_unsafe_fundamental<char32_t>();
    test_is_unsafe_fundamental<wchar_t>();

    test_is_not_unsafe_fundamental<phi::boolean>();
    test_is_not_unsafe_fundamental<phi::integer<signed char>>();
    test_is_not_unsafe_fundamental<phi::integer<unsigned char>>();
    test_is_not_unsafe_fundamental<phi::integer<short>>();
    test_is_not_unsafe_fundamental<phi::integer<unsigned short>>();
    test_is_not_unsafe_fundamental<phi::integer<int>>();
    test_is_not_unsafe_fundamental<phi::integer<unsigned int>>();
    test_is_not_unsafe_fundamental<phi::integer<long>>();
    test_is_not_unsafe_fundamental<phi::integer<unsigned long>>();
    test_is_not_unsafe_fundamental<phi::integer<long long>>();
    test_is_not_unsafe_fundamental<phi::integer<unsigned long long>>();
    test_is_not_unsafe_fundamental<phi::floating_point<float>>();
    test_is_not_unsafe_fundamental<phi::floating_point<double>>();
    test_is_not_unsafe_fundamental<phi::floating_point<long double>>();

    test_is_not_unsafe_fundamental<std::vector<int>>();
    test_is_not_unsafe_fundamental<phi::scope_ptr<int>>();

    test_is_not_unsafe_fundamental<int&>();
    test_is_not_unsafe_fundamental<const int&>();
    test_is_not_unsafe_fundamental<volatile int&>();
    test_is_not_unsafe_fundamental<const volatile int&>();
    test_is_not_unsafe_fundamental<int&&>();
    test_is_not_unsafe_fundamental<const int&&>();
    test_is_not_unsafe_fundamental<volatile int&&>();
    test_is_not_unsafe_fundamental<const volatile int&&>();
    test_is_not_unsafe_fundamental<int*>();
    test_is_not_unsafe_fundamental<const int*>();
    test_is_not_unsafe_fundamental<volatile int*>();
    test_is_not_unsafe_fundamental<const volatile int*>();
    test_is_not_unsafe_fundamental<int**>();
    test_is_not_unsafe_fundamental<const int**>();
    test_is_not_unsafe_fundamental<volatile int**>();
    test_is_not_unsafe_fundamental<const volatile int**>();
    test_is_not_unsafe_fundamental<int*&>();
    test_is_not_unsafe_fundamental<const int*&>();
    test_is_not_unsafe_fundamental<volatile int*&>();
    test_is_not_unsafe_fundamental<const volatile int*&>();
    test_is_not_unsafe_fundamental<int*&&>();
    test_is_not_unsafe_fundamental<const int*&&>();
    test_is_not_unsafe_fundamental<volatile int*&&>();
    test_is_not_unsafe_fundamental<const volatile int*&&>();
    test_is_not_unsafe_fundamental<void*>();
    test_is_not_unsafe_fundamental<char[3]>();
    test_is_not_unsafe_fundamental<char[]>();
    test_is_not_unsafe_fundamental<char* [3]>();
    test_is_not_unsafe_fundamental<char*[]>();
    test_is_not_unsafe_fundamental<int(*)[3]>();
    test_is_not_unsafe_fundamental<int(*)[]>();
    test_is_not_unsafe_fundamental<int(&)[3]>();
    test_is_not_unsafe_fundamental<int(&)[]>();
    test_is_not_unsafe_fundamental<int(&&)[3]>();
    test_is_not_unsafe_fundamental<int(&&)[]>();
    test_is_not_unsafe_fundamental<char[3][2]>();
    test_is_not_unsafe_fundamental<char[][2]>();
    test_is_not_unsafe_fundamental<char* [3][2]>();
    test_is_not_unsafe_fundamental<char*[][2]>();
    test_is_not_unsafe_fundamental<int(*)[3][2]>();
    test_is_not_unsafe_fundamental<int(*)[][2]>();
    test_is_not_unsafe_fundamental<int(&)[3][2]>();
    test_is_not_unsafe_fundamental<int(&)[][2]>();
    test_is_not_unsafe_fundamental<int(&&)[3][2]>();
    test_is_not_unsafe_fundamental<int(&&)[][2]>();
    test_is_not_unsafe_fundamental<Class>();
    test_is_not_unsafe_fundamental<Class[]>();
    test_is_not_unsafe_fundamental<Class[2]>();
    test_is_not_unsafe_fundamental<Template<void>>();
    test_is_not_unsafe_fundamental<Template<int>>();
    test_is_not_unsafe_fundamental<Template<Class>>();
    test_is_not_unsafe_fundamental<Template<IncompleteType>>();
    test_is_not_unsafe_fundamental<VariadicTemplate<>>();
    test_is_not_unsafe_fundamental<VariadicTemplate<void>>();
    test_is_not_unsafe_fundamental<VariadicTemplate<int>>();
    test_is_not_unsafe_fundamental<VariadicTemplate<Class>>();
    test_is_not_unsafe_fundamental<VariadicTemplate<IncompleteType>>();
    test_is_not_unsafe_fundamental<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_fundamental<PublicDerivedFromTemplate<Base>>();
    test_is_not_unsafe_fundamental<PublicDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_fundamental<PublicDerivedFromTemplate<Class>>();
    test_is_not_unsafe_fundamental<PrivateDerivedFromTemplate<Base>>();
    test_is_not_unsafe_fundamental<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_fundamental<PrivateDerivedFromTemplate<Class>>();
    test_is_not_unsafe_fundamental<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_unsafe_fundamental<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_fundamental<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_unsafe_fundamental<VirtualDerivedFromTemplate<Base>>();
    test_is_not_unsafe_fundamental<VirtualDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_fundamental<VirtualDerivedFromTemplate<Class>>();
    test_is_not_unsafe_fundamental<Union>();
    test_is_not_unsafe_fundamental<NonEmptyUnion>();
    test_is_not_unsafe_fundamental<NonTrivialUnion>();
    test_is_not_unsafe_fundamental<Empty>();
    test_is_not_unsafe_fundamental<NotEmpty>();
    test_is_not_unsafe_fundamental<NonTrivial>();
    test_is_not_unsafe_fundamental<BitZero>();
    test_is_not_unsafe_fundamental<BitOne>();
    test_is_not_unsafe_fundamental<Base>();
    test_is_not_unsafe_fundamental<Derived>();
    test_is_not_unsafe_fundamental<Polymorphic>();
    test_is_not_unsafe_fundamental<DerivedPolymorphic>();
    test_is_not_unsafe_fundamental<Abstract>();
    test_is_not_unsafe_fundamental<PublicAbstract>();
    test_is_not_unsafe_fundamental<PrivateAbstract>();
    test_is_not_unsafe_fundamental<ProtectedAbstract>();
    test_is_not_unsafe_fundamental<AbstractTemplate<int>>();
    test_is_not_unsafe_fundamental<AbstractTemplate<double>>();
    test_is_not_unsafe_fundamental<AbstractTemplate<Class>>();
    test_is_not_unsafe_fundamental<AbstractTemplate<IncompleteType>>();
    test_is_not_unsafe_fundamental<PublicAbstractDeletedDestructor>();
    test_is_not_unsafe_fundamental<ProtectedAbstractDeletedDestructor>();
    test_is_not_unsafe_fundamental<PrivateAbstractDeletedDestructor>();
    test_is_not_unsafe_fundamental<Final>();
    test_is_not_unsafe_fundamental<FinalDerived>();
    test_is_not_unsafe_fundamental<PublicDestructor>();
    test_is_not_unsafe_fundamental<ProtectedDestructor>();
    test_is_not_unsafe_fundamental<PrivateDestructor>();
    test_is_not_unsafe_fundamental<VirtualPublicDestructor>();
    test_is_not_unsafe_fundamental<VirtualProtectedDestructor>();
    test_is_not_unsafe_fundamental<VirtualPrivateDestructor>();
    test_is_not_unsafe_fundamental<PurePublicDestructor>();
    test_is_not_unsafe_fundamental<PureProtectedDestructor>();
    test_is_not_unsafe_fundamental<PurePrivateDestructor>();
    test_is_not_unsafe_fundamental<DeletedPublicDestructor>();
    test_is_not_unsafe_fundamental<DeletedProtectedDestructor>();
    test_is_not_unsafe_fundamental<DeletedPrivateDestructor>();
    test_is_not_unsafe_fundamental<DeletedVirtualPublicDestructor>();
    test_is_not_unsafe_fundamental<DeletedVirtualProtectedDestructor>();
    test_is_not_unsafe_fundamental<DeletedVirtualPrivateDestructor>();
    test_is_not_unsafe_fundamental<ExplicitClass>();
    test_is_not_unsafe_fundamental<NothrowExplicitClass>();
    test_is_not_unsafe_fundamental<ThrowExplicitClass>();
    test_is_not_unsafe_fundamental<ThrowDefaultClass>();
    test_is_not_unsafe_fundamental<ThrowCopyConsClass>();
    test_is_not_unsafe_fundamental<ThrowMoveConsClass>();
    test_is_not_unsafe_fundamental<NoexceptExplicitClass>();
    test_is_not_unsafe_fundamental<ExceptExplicitClass>();
    test_is_not_unsafe_fundamental<NoexceptDefaultClass>();
    test_is_not_unsafe_fundamental<ExceptDefaultClass>();
    test_is_not_unsafe_fundamental<NoexceptCopyConsClass>();
    test_is_not_unsafe_fundamental<ExceptCopyConsClass>();
    test_is_not_unsafe_fundamental<NoexceptMoveConsClass>();
    test_is_not_unsafe_fundamental<ExceptMoveConsClass>();
    test_is_not_unsafe_fundamental<NoexceptCopyAssignClass>();
    test_is_not_unsafe_fundamental<ExceptCopyAssignClass>();
    test_is_not_unsafe_fundamental<NoexceptMoveAssignClass>();
    test_is_not_unsafe_fundamental<ExceptMoveAssignClass>();
    test_is_not_unsafe_fundamental<DeletedCopyAssignClass>();
    test_is_not_unsafe_fundamental<DeletedMoveAssignClass>();
    test_is_not_unsafe_fundamental<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_unsafe_fundamental<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_unsafe_fundamental<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_not_unsafe_fundamental<ExceptMoveConsExceptMoveAssignClass>();
    test_is_not_unsafe_fundamental<ImplicitTo<int>>();
    test_is_not_unsafe_fundamental<ImplicitTo<float>>();
    test_is_not_unsafe_fundamental<ImplicitTo<Class>>();
    test_is_not_unsafe_fundamental<DeletedImplicitTo<int>>();
    test_is_not_unsafe_fundamental<DeletedImplicitTo<float>>();
    test_is_not_unsafe_fundamental<DeletedImplicitTo<Class>>();
    test_is_not_unsafe_fundamental<ExplicitTo<int>>();
    test_is_not_unsafe_fundamental<ExplicitTo<float>>();
    test_is_not_unsafe_fundamental<ExplicitTo<Class>>();
    test_is_not_unsafe_fundamental<DeletedExplicitTo<int>>();
    test_is_not_unsafe_fundamental<DeletedExplicitTo<float>>();
    test_is_not_unsafe_fundamental<DeletedExplicitTo<Class>>();
    test_is_not_unsafe_fundamental<Ellipsis>();
    test_is_not_unsafe_fundamental<DeletedEllipsis>();
    test_is_not_unsafe_fundamental<CopyConsOnlyType>();
    test_is_not_unsafe_fundamental<MoveConsOnlyType>();
    test_is_not_unsafe_fundamental<OverloadedOperators>();
    test_is_not_unsafe_fundamental<PublicIntMember>();
    test_is_not_unsafe_fundamental<ProtectedIntMember>();
    test_is_not_unsafe_fundamental<PrivateIntMember>();
    test_is_not_unsafe_fundamental<PublicStaticIntMember>();
    test_is_not_unsafe_fundamental<ProtectedStaticIntMember>();
    test_is_not_unsafe_fundamental<PrivateStaticIntMember>();
    test_is_not_unsafe_fundamental<PublicTemplateMember<int>>();
    test_is_not_unsafe_fundamental<PublicTemplateMember<float>>();
    test_is_not_unsafe_fundamental<PublicTemplateMember<Class>>();
    test_is_not_unsafe_fundamental<ProtectedTemplateMember<int>>();
    test_is_not_unsafe_fundamental<ProtectedTemplateMember<float>>();
    test_is_not_unsafe_fundamental<ProtectedTemplateMember<Class>>();
    test_is_not_unsafe_fundamental<PrivateTemplateMember<int>>();
    test_is_not_unsafe_fundamental<PrivateTemplateMember<float>>();
    test_is_not_unsafe_fundamental<PrivateTemplateMember<Class>>();
    test_is_not_unsafe_fundamental<PublicStaticTemplateMember<int>>();
    test_is_not_unsafe_fundamental<PublicStaticTemplateMember<float>>();
    test_is_not_unsafe_fundamental<PublicStaticTemplateMember<Class>>();
    test_is_not_unsafe_fundamental<ProtectedStaticTemplateMember<int>>();
    test_is_not_unsafe_fundamental<ProtectedStaticTemplateMember<float>>();
    test_is_not_unsafe_fundamental<ProtectedStaticTemplateMember<Class>>();
    test_is_not_unsafe_fundamental<PrivateStaticTemplateMember<int>>();
    test_is_not_unsafe_fundamental<PrivateStaticTemplateMember<float>>();
    test_is_not_unsafe_fundamental<PrivateStaticTemplateMember<Class>>();
    test_is_not_unsafe_fundamental<Enum>();
    test_is_not_unsafe_fundamental<EnumSigned>();
    test_is_not_unsafe_fundamental<EnumUnsigned>();
    test_is_not_unsafe_fundamental<EnumClass>();
    test_is_not_unsafe_fundamental<EnumStruct>();
    test_is_not_unsafe_fundamental<Function>();
    test_is_not_unsafe_fundamental<FunctionPtr>();
    test_is_not_unsafe_fundamental<MemberObjectPtr>();
    test_is_not_unsafe_fundamental<MemberFunctionPtr>();
    test_is_not_unsafe_fundamental<LambdaType>();
    test_is_not_unsafe_fundamental<LambdaNoexceptType>();
    test_is_not_unsafe_fundamental<LambdaThrowsType>();
    test_is_not_unsafe_fundamental<IncompleteType>();
    test_is_not_unsafe_fundamental<IncompleteTemplate<void>>();
    test_is_not_unsafe_fundamental<IncompleteTemplate<int>>();
    test_is_not_unsafe_fundamental<IncompleteTemplate<Class>>();
    test_is_not_unsafe_fundamental<IncompleteTemplate<IncompleteType>>();
    test_is_not_unsafe_fundamental<IncompleteVariadicTemplate<>>();
    test_is_not_unsafe_fundamental<IncompleteVariadicTemplate<void>>();
    test_is_not_unsafe_fundamental<IncompleteVariadicTemplate<int>>();
    test_is_not_unsafe_fundamental<IncompleteVariadicTemplate<Class>>();
    test_is_not_unsafe_fundamental<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_unsafe_fundamental<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_fundamental<IncompleteUnion>();
    test_is_not_unsafe_fundamental<IncompleteEnumSigned>();
    test_is_not_unsafe_fundamental<IncompleteEnumUnsigned>();
    test_is_not_unsafe_fundamental<IncompleteEnumClass>();
    test_is_not_unsafe_fundamental<IncompleteEnumStruct>();
    test_is_not_unsafe_fundamental<int Class::*>();
    test_is_not_unsafe_fundamental<float Class::*>();
    test_is_not_unsafe_fundamental<void * Class::*>();
    test_is_not_unsafe_fundamental<int * Class::*>();
    test_is_not_unsafe_fundamental<int Class::*&>();
    test_is_not_unsafe_fundamental<float Class::*&>();
    test_is_not_unsafe_fundamental<void * Class::*&>();
    test_is_not_unsafe_fundamental<int * Class::*&>();
    test_is_not_unsafe_fundamental<int Class::*&&>();
    test_is_not_unsafe_fundamental<float Class::*&&>();
    test_is_not_unsafe_fundamental<void * Class::*&&>();
    test_is_not_unsafe_fundamental<int * Class::*&&>();
    test_is_not_unsafe_fundamental<int Class::*const>();
    test_is_not_unsafe_fundamental<float Class::*const>();
    test_is_not_unsafe_fundamental<void * Class::*const>();
    test_is_not_unsafe_fundamental<int Class::*const&>();
    test_is_not_unsafe_fundamental<float Class::*const&>();
    test_is_not_unsafe_fundamental<void * Class::*const&>();
    test_is_not_unsafe_fundamental<int Class::*const&&>();
    test_is_not_unsafe_fundamental<float Class::*const&&>();
    test_is_not_unsafe_fundamental<void * Class::*const&&>();
    test_is_not_unsafe_fundamental<int Class::*volatile>();
    test_is_not_unsafe_fundamental<float Class::*volatile>();
    test_is_not_unsafe_fundamental<void * Class::*volatile>();
    test_is_not_unsafe_fundamental<int Class::*volatile&>();
    test_is_not_unsafe_fundamental<float Class::*volatile&>();
    test_is_not_unsafe_fundamental<void * Class::*volatile&>();
    test_is_not_unsafe_fundamental<int Class::*volatile&&>();
    test_is_not_unsafe_fundamental<float Class::*volatile&&>();
    test_is_not_unsafe_fundamental<void * Class::*volatile&&>();
    test_is_not_unsafe_fundamental<int Class::*const volatile>();
    test_is_not_unsafe_fundamental<float Class::*const volatile>();
    test_is_not_unsafe_fundamental<void * Class::*const volatile>();
    test_is_not_unsafe_fundamental<int Class::*const volatile&>();
    test_is_not_unsafe_fundamental<float Class::*const volatile&>();
    test_is_not_unsafe_fundamental<void * Class::*const volatile&>();
    test_is_not_unsafe_fundamental<int Class::*const volatile&&>();
    test_is_not_unsafe_fundamental<float Class::*const volatile&&>();
    test_is_not_unsafe_fundamental<void * Class::*const volatile&&>();
    test_is_not_unsafe_fundamental<NonCopyable>();
    test_is_not_unsafe_fundamental<NonMoveable>();
    test_is_not_unsafe_fundamental<NonConstructible>();
    test_is_not_unsafe_fundamental<NonDestructible>();
    test_is_not_unsafe_fundamental<Tracked>();
    test_is_not_unsafe_fundamental<TrapConstructible>();
    test_is_not_unsafe_fundamental<TrapImplicitConversion>();
    test_is_not_unsafe_fundamental<TrapComma>();
    test_is_not_unsafe_fundamental<TrapCall>();
    test_is_not_unsafe_fundamental<TrapSelfAssign>();
    test_is_not_unsafe_fundamental<TrapDeref>();
    test_is_not_unsafe_fundamental<TrapArraySubscript>();

    test_is_not_unsafe_fundamental<void()>();
    test_is_not_unsafe_fundamental<void()&>();
    test_is_not_unsafe_fundamental<void() &&>();
    test_is_not_unsafe_fundamental<void() const>();
    test_is_not_unsafe_fundamental<void() const&>();
    test_is_not_unsafe_fundamental<void() const&&>();
    test_is_not_unsafe_fundamental<void() volatile>();
    test_is_not_unsafe_fundamental<void() volatile&>();
    test_is_not_unsafe_fundamental<void() volatile&&>();
    test_is_not_unsafe_fundamental<void() const volatile>();
    test_is_not_unsafe_fundamental<void() const volatile&>();
    test_is_not_unsafe_fundamental<void() const volatile&&>();
    test_is_not_unsafe_fundamental<void() noexcept>();
    test_is_not_unsafe_fundamental<void()& noexcept>();
    test_is_not_unsafe_fundamental<void()&& noexcept>();
    test_is_not_unsafe_fundamental<void() const noexcept>();
    test_is_not_unsafe_fundamental<void() const& noexcept>();
    test_is_not_unsafe_fundamental<void() const&& noexcept>();
    test_is_not_unsafe_fundamental<void() volatile noexcept>();
    test_is_not_unsafe_fundamental<void() volatile& noexcept>();
    test_is_not_unsafe_fundamental<void() volatile&& noexcept>();
    test_is_not_unsafe_fundamental<void() const volatile noexcept>();
    test_is_not_unsafe_fundamental<void() const volatile& noexcept>();
    test_is_not_unsafe_fundamental<void() const volatile&& noexcept>();

    test_is_not_unsafe_fundamental<void(int)>();
    test_is_not_unsafe_fundamental<void(int)&>();
    test_is_not_unsafe_fundamental<void(int) &&>();
    test_is_not_unsafe_fundamental<void(int) const>();
    test_is_not_unsafe_fundamental<void(int) const&>();
    test_is_not_unsafe_fundamental<void(int) const&&>();
    test_is_not_unsafe_fundamental<void(int) volatile>();
    test_is_not_unsafe_fundamental<void(int) volatile&>();
    test_is_not_unsafe_fundamental<void(int) volatile&&>();
    test_is_not_unsafe_fundamental<void(int) const volatile>();
    test_is_not_unsafe_fundamental<void(int) const volatile&>();
    test_is_not_unsafe_fundamental<void(int) const volatile&&>();
    test_is_not_unsafe_fundamental<void(int) noexcept>();
    test_is_not_unsafe_fundamental<void(int)& noexcept>();
    test_is_not_unsafe_fundamental<void(int)&& noexcept>();
    test_is_not_unsafe_fundamental<void(int) const noexcept>();
    test_is_not_unsafe_fundamental<void(int) const& noexcept>();
    test_is_not_unsafe_fundamental<void(int) const&& noexcept>();
    test_is_not_unsafe_fundamental<void(int) volatile noexcept>();
    test_is_not_unsafe_fundamental<void(int) volatile& noexcept>();
    test_is_not_unsafe_fundamental<void(int) volatile&& noexcept>();
    test_is_not_unsafe_fundamental<void(int) const volatile noexcept>();
    test_is_not_unsafe_fundamental<void(int) const volatile& noexcept>();
    test_is_not_unsafe_fundamental<void(int) const volatile&& noexcept>();

    test_is_not_unsafe_fundamental<void(...)>();
    test_is_not_unsafe_fundamental<void(...)&>();
    test_is_not_unsafe_fundamental<void(...) &&>();
    test_is_not_unsafe_fundamental<void(...) const>();
    test_is_not_unsafe_fundamental<void(...) const&>();
    test_is_not_unsafe_fundamental<void(...) const&&>();
    test_is_not_unsafe_fundamental<void(...) volatile>();
    test_is_not_unsafe_fundamental<void(...) volatile&>();
    test_is_not_unsafe_fundamental<void(...) volatile&&>();
    test_is_not_unsafe_fundamental<void(...) const volatile>();
    test_is_not_unsafe_fundamental<void(...) const volatile&>();
    test_is_not_unsafe_fundamental<void(...) const volatile&&>();
    test_is_not_unsafe_fundamental<void(...) noexcept>();
    test_is_not_unsafe_fundamental<void(...)& noexcept>();
    test_is_not_unsafe_fundamental<void(...)&& noexcept>();
    test_is_not_unsafe_fundamental<void(...) const noexcept>();
    test_is_not_unsafe_fundamental<void(...) const& noexcept>();
    test_is_not_unsafe_fundamental<void(...) const&& noexcept>();
    test_is_not_unsafe_fundamental<void(...) volatile noexcept>();
    test_is_not_unsafe_fundamental<void(...) volatile& noexcept>();
    test_is_not_unsafe_fundamental<void(...) volatile&& noexcept>();
    test_is_not_unsafe_fundamental<void(...) const volatile noexcept>();
    test_is_not_unsafe_fundamental<void(...) const volatile& noexcept>();
    test_is_not_unsafe_fundamental<void(...) const volatile&& noexcept>();

    test_is_not_unsafe_fundamental<void(int, ...)>();
    test_is_not_unsafe_fundamental<void(int, ...)&>();
    test_is_not_unsafe_fundamental<void(int, ...) &&>();
    test_is_not_unsafe_fundamental<void(int, ...) const>();
    test_is_not_unsafe_fundamental<void(int, ...) const&>();
    test_is_not_unsafe_fundamental<void(int, ...) const&&>();
    test_is_not_unsafe_fundamental<void(int, ...) volatile>();
    test_is_not_unsafe_fundamental<void(int, ...) volatile&>();
    test_is_not_unsafe_fundamental<void(int, ...) volatile&&>();
    test_is_not_unsafe_fundamental<void(int, ...) const volatile>();
    test_is_not_unsafe_fundamental<void(int, ...) const volatile&>();
    test_is_not_unsafe_fundamental<void(int, ...) const volatile&&>();
    test_is_not_unsafe_fundamental<void(int, ...) noexcept>();
    test_is_not_unsafe_fundamental<void(int, ...)& noexcept>();
    test_is_not_unsafe_fundamental<void(int, ...)&& noexcept>();
    test_is_not_unsafe_fundamental<void(int, ...) const noexcept>();
    test_is_not_unsafe_fundamental<void(int, ...) const& noexcept>();
    test_is_not_unsafe_fundamental<void(int, ...) const&& noexcept>();
    test_is_not_unsafe_fundamental<void(int, ...) volatile noexcept>();
    test_is_not_unsafe_fundamental<void(int, ...) volatile& noexcept>();
    test_is_not_unsafe_fundamental<void(int, ...) volatile&& noexcept>();
    test_is_not_unsafe_fundamental<void(int, ...) const volatile noexcept>();
    test_is_not_unsafe_fundamental<void(int, ...) const volatile& noexcept>();
    test_is_not_unsafe_fundamental<void(int, ...) const volatile&& noexcept>();

    test_is_not_unsafe_fundamental<int()>();
    test_is_not_unsafe_fundamental<int()&>();
    test_is_not_unsafe_fundamental<int() &&>();
    test_is_not_unsafe_fundamental<int() const>();
    test_is_not_unsafe_fundamental<int() const&>();
    test_is_not_unsafe_fundamental<int() const&&>();
    test_is_not_unsafe_fundamental<int() volatile>();
    test_is_not_unsafe_fundamental<int() volatile&>();
    test_is_not_unsafe_fundamental<int() volatile&&>();
    test_is_not_unsafe_fundamental<int() const volatile>();
    test_is_not_unsafe_fundamental<int() const volatile&>();
    test_is_not_unsafe_fundamental<int() const volatile&&>();
    test_is_not_unsafe_fundamental<int() noexcept>();
    test_is_not_unsafe_fundamental<int()& noexcept>();
    test_is_not_unsafe_fundamental<int()&& noexcept>();
    test_is_not_unsafe_fundamental<int() const noexcept>();
    test_is_not_unsafe_fundamental<int() const& noexcept>();
    test_is_not_unsafe_fundamental<int() const&& noexcept>();
    test_is_not_unsafe_fundamental<int() volatile noexcept>();
    test_is_not_unsafe_fundamental<int() volatile& noexcept>();
    test_is_not_unsafe_fundamental<int() volatile&& noexcept>();
    test_is_not_unsafe_fundamental<int() const volatile noexcept>();
    test_is_not_unsafe_fundamental<int() const volatile& noexcept>();
    test_is_not_unsafe_fundamental<int() const volatile&& noexcept>();

    test_is_not_unsafe_fundamental<int(int)>();
    test_is_not_unsafe_fundamental<int(int)&>();
    test_is_not_unsafe_fundamental<int(int) &&>();
    test_is_not_unsafe_fundamental<int(int) const>();
    test_is_not_unsafe_fundamental<int(int) const&>();
    test_is_not_unsafe_fundamental<int(int) const&&>();
    test_is_not_unsafe_fundamental<int(int) volatile>();
    test_is_not_unsafe_fundamental<int(int) volatile&>();
    test_is_not_unsafe_fundamental<int(int) volatile&&>();
    test_is_not_unsafe_fundamental<int(int) const volatile>();
    test_is_not_unsafe_fundamental<int(int) const volatile&>();
    test_is_not_unsafe_fundamental<int(int) const volatile&&>();
    test_is_not_unsafe_fundamental<int(int) noexcept>();
    test_is_not_unsafe_fundamental<int(int)& noexcept>();
    test_is_not_unsafe_fundamental<int(int)&& noexcept>();
    test_is_not_unsafe_fundamental<int(int) const noexcept>();
    test_is_not_unsafe_fundamental<int(int) const& noexcept>();
    test_is_not_unsafe_fundamental<int(int) const&& noexcept>();
    test_is_not_unsafe_fundamental<int(int) volatile noexcept>();
    test_is_not_unsafe_fundamental<int(int) volatile& noexcept>();
    test_is_not_unsafe_fundamental<int(int) volatile&& noexcept>();
    test_is_not_unsafe_fundamental<int(int) const volatile noexcept>();
    test_is_not_unsafe_fundamental<int(int) const volatile& noexcept>();
    test_is_not_unsafe_fundamental<int(int) const volatile&& noexcept>();

    test_is_not_unsafe_fundamental<int(...)>();
    test_is_not_unsafe_fundamental<int(...)&>();
    test_is_not_unsafe_fundamental<int(...) &&>();
    test_is_not_unsafe_fundamental<int(...) const>();
    test_is_not_unsafe_fundamental<int(...) const&>();
    test_is_not_unsafe_fundamental<int(...) const&&>();
    test_is_not_unsafe_fundamental<int(...) volatile>();
    test_is_not_unsafe_fundamental<int(...) volatile&>();
    test_is_not_unsafe_fundamental<int(...) volatile&&>();
    test_is_not_unsafe_fundamental<int(...) const volatile>();
    test_is_not_unsafe_fundamental<int(...) const volatile&>();
    test_is_not_unsafe_fundamental<int(...) const volatile&&>();
    test_is_not_unsafe_fundamental<int(...) noexcept>();
    test_is_not_unsafe_fundamental<int(...)& noexcept>();
    test_is_not_unsafe_fundamental<int(...)&& noexcept>();
    test_is_not_unsafe_fundamental<int(...) const noexcept>();
    test_is_not_unsafe_fundamental<int(...) const& noexcept>();
    test_is_not_unsafe_fundamental<int(...) const&& noexcept>();
    test_is_not_unsafe_fundamental<int(...) volatile noexcept>();
    test_is_not_unsafe_fundamental<int(...) volatile& noexcept>();
    test_is_not_unsafe_fundamental<int(...) volatile&& noexcept>();
    test_is_not_unsafe_fundamental<int(...) const volatile noexcept>();
    test_is_not_unsafe_fundamental<int(...) const volatile& noexcept>();
    test_is_not_unsafe_fundamental<int(...) const volatile&& noexcept>();

    test_is_not_unsafe_fundamental<int(int, ...)>();
    test_is_not_unsafe_fundamental<int(int, ...)&>();
    test_is_not_unsafe_fundamental<int(int, ...) &&>();
    test_is_not_unsafe_fundamental<int(int, ...) const>();
    test_is_not_unsafe_fundamental<int(int, ...) const&>();
    test_is_not_unsafe_fundamental<int(int, ...) const&&>();
    test_is_not_unsafe_fundamental<int(int, ...) volatile>();
    test_is_not_unsafe_fundamental<int(int, ...) volatile&>();
    test_is_not_unsafe_fundamental<int(int, ...) volatile&&>();
    test_is_not_unsafe_fundamental<int(int, ...) const volatile>();
    test_is_not_unsafe_fundamental<int(int, ...) const volatile&>();
    test_is_not_unsafe_fundamental<int(int, ...) const volatile&&>();
    test_is_not_unsafe_fundamental<int(int, ...) noexcept>();
    test_is_not_unsafe_fundamental<int(int, ...)& noexcept>();
    test_is_not_unsafe_fundamental<int(int, ...)&& noexcept>();
    test_is_not_unsafe_fundamental<int(int, ...) const noexcept>();
    test_is_not_unsafe_fundamental<int(int, ...) const& noexcept>();
    test_is_not_unsafe_fundamental<int(int, ...) const&& noexcept>();
    test_is_not_unsafe_fundamental<int(int, ...) volatile noexcept>();
    test_is_not_unsafe_fundamental<int(int, ...) volatile& noexcept>();
    test_is_not_unsafe_fundamental<int(int, ...) volatile&& noexcept>();
    test_is_not_unsafe_fundamental<int(int, ...) const volatile noexcept>();
    test_is_not_unsafe_fundamental<int(int, ...) const volatile& noexcept>();
    test_is_not_unsafe_fundamental<int(int, ...) const volatile&& noexcept>();

    test_is_not_unsafe_fundamental<void (*)()>();
    test_is_not_unsafe_fundamental<void (*)() noexcept>();

    test_is_not_unsafe_fundamental<void (*)(int)>();
    test_is_not_unsafe_fundamental<void (*)(int) noexcept>();

    test_is_not_unsafe_fundamental<void (*)(...)>();
    test_is_not_unsafe_fundamental<void (*)(...) noexcept>();

    test_is_not_unsafe_fundamental<void (*)(int, ...)>();
    test_is_not_unsafe_fundamental<void (*)(int, ...) noexcept>();

    test_is_not_unsafe_fundamental<int (*)()>();
    test_is_not_unsafe_fundamental<int (*)() noexcept>();

    test_is_not_unsafe_fundamental<int (*)(int)>();
    test_is_not_unsafe_fundamental<int (*)(int) noexcept>();

    test_is_not_unsafe_fundamental<int (*)(...)>();
    test_is_not_unsafe_fundamental<int (*)(...) noexcept>();

    test_is_not_unsafe_fundamental<int (*)(int, ...)>();
    test_is_not_unsafe_fundamental<int (*)(int, ...) noexcept>();

    test_is_not_unsafe_fundamental<void (&)()>();
    test_is_not_unsafe_fundamental<void (&)() noexcept>();

    test_is_not_unsafe_fundamental<void (&)(int)>();
    test_is_not_unsafe_fundamental<void (&)(int) noexcept>();

    test_is_not_unsafe_fundamental<void (&)(...)>();
    test_is_not_unsafe_fundamental<void (&)(...) noexcept>();

    test_is_not_unsafe_fundamental<void (&)(int, ...)>();
    test_is_not_unsafe_fundamental<void (&)(int, ...) noexcept>();

    test_is_not_unsafe_fundamental<int (&)()>();
    test_is_not_unsafe_fundamental<int (&)() noexcept>();

    test_is_not_unsafe_fundamental<int (&)(int)>();
    test_is_not_unsafe_fundamental<int (&)(int) noexcept>();

    test_is_not_unsafe_fundamental<int (&)(...)>();
    test_is_not_unsafe_fundamental<int (&)(...) noexcept>();

    test_is_not_unsafe_fundamental<int (&)(int, ...)>();
    test_is_not_unsafe_fundamental<int (&)(int, ...) noexcept>();

    test_is_not_unsafe_fundamental<void(&&)()>();
    test_is_not_unsafe_fundamental<void(&&)() noexcept>();

    test_is_not_unsafe_fundamental<void(&&)(int)>();
    test_is_not_unsafe_fundamental<void(&&)(int) noexcept>();

    test_is_not_unsafe_fundamental<void(&&)(...)>();
    test_is_not_unsafe_fundamental<void(&&)(...) noexcept>();

    test_is_not_unsafe_fundamental<void(&&)(int, ...)>();
    test_is_not_unsafe_fundamental<void(&&)(int, ...) noexcept>();

    test_is_not_unsafe_fundamental<int(&&)()>();
    test_is_not_unsafe_fundamental<int(&&)() noexcept>();

    test_is_not_unsafe_fundamental<int(&&)(int)>();
    test_is_not_unsafe_fundamental<int(&&)(int) noexcept>();

    test_is_not_unsafe_fundamental<int(&&)(...)>();
    test_is_not_unsafe_fundamental<int(&&)(...) noexcept>();

    test_is_not_unsafe_fundamental<int(&&)(int, ...)>();
    test_is_not_unsafe_fundamental<int(&&)(int, ...) noexcept>();

    test_is_not_unsafe_fundamental<void (Class::*)()>();
    test_is_not_unsafe_fundamental<void (Class::*)()&>();
    test_is_not_unsafe_fundamental<void (Class::*)() &&>();
    test_is_not_unsafe_fundamental<void (Class::*)() const>();
    test_is_not_unsafe_fundamental<void (Class::*)() const&>();
    test_is_not_unsafe_fundamental<void (Class::*)() const&&>();
    test_is_not_unsafe_fundamental<void (Class::*)() noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)()& noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)()&& noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)() const noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)() const& noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)() const&& noexcept>();

    test_is_not_unsafe_fundamental<void (Class::*)(int)>();
    test_is_not_unsafe_fundamental<void (Class::*)(int)&>();
    test_is_not_unsafe_fundamental<void (Class::*)(int) &&>();
    test_is_not_unsafe_fundamental<void (Class::*)(int) const>();
    test_is_not_unsafe_fundamental<void (Class::*)(int) const&>();
    test_is_not_unsafe_fundamental<void (Class::*)(int) const&&>();
    test_is_not_unsafe_fundamental<void (Class::*)(int) noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(int)& noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(int) const noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_fundamental<void (Class::*)(...)>();
    test_is_not_unsafe_fundamental<void (Class::*)(...)&>();
    test_is_not_unsafe_fundamental<void (Class::*)(...) &&>();
    test_is_not_unsafe_fundamental<void (Class::*)(...) const>();
    test_is_not_unsafe_fundamental<void (Class::*)(...) const&>();
    test_is_not_unsafe_fundamental<void (Class::*)(...) const&&>();
    test_is_not_unsafe_fundamental<void (Class::*)(...) noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(...)& noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(...) const noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(...) const&& noexcept>();

    test_is_not_unsafe_fundamental<void (Class::*)(int, ...)>();
    test_is_not_unsafe_fundamental<void (Class::*)(int, ...)&>();
    test_is_not_unsafe_fundamental<void (Class::*)(int, ...) &&>();
    test_is_not_unsafe_fundamental<void (Class::*)(int, ...) const>();
    test_is_not_unsafe_fundamental<void (Class::*)(int, ...) const&>();
    test_is_not_unsafe_fundamental<void (Class::*)(int, ...) const&&>();
    test_is_not_unsafe_fundamental<void (Class::*)(int, ...) noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(int, ...)& noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(int, ...) const noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsafe_fundamental<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_unsafe_fundamental<int (Class::*)()>();
    test_is_not_unsafe_fundamental<int (Class::*)()&>();
    test_is_not_unsafe_fundamental<int (Class::*)() &&>();
    test_is_not_unsafe_fundamental<int (Class::*)() const>();
    test_is_not_unsafe_fundamental<int (Class::*)() const&>();
    test_is_not_unsafe_fundamental<int (Class::*)() const&&>();
    test_is_not_unsafe_fundamental<int (Class::*)() noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)()& noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)()&& noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)() const noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)() const& noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)() const&& noexcept>();

    test_is_not_unsafe_fundamental<int (Class::*)(int)>();
    test_is_not_unsafe_fundamental<int (Class::*)(int)&>();
    test_is_not_unsafe_fundamental<int (Class::*)(int) &&>();
    test_is_not_unsafe_fundamental<int (Class::*)(int) const>();
    test_is_not_unsafe_fundamental<int (Class::*)(int) const&>();
    test_is_not_unsafe_fundamental<int (Class::*)(int) const&&>();
    test_is_not_unsafe_fundamental<int (Class::*)(int) noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(int)& noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(int) const noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_fundamental<int (Class::*)(...)>();
    test_is_not_unsafe_fundamental<int (Class::*)(...)&>();
    test_is_not_unsafe_fundamental<int (Class::*)(...) &&>();
    test_is_not_unsafe_fundamental<int (Class::*)(...) const>();
    test_is_not_unsafe_fundamental<int (Class::*)(...) const&>();
    test_is_not_unsafe_fundamental<int (Class::*)(...) const&&>();
    test_is_not_unsafe_fundamental<int (Class::*)(...) noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(...)& noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(...) const noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(...) const&& noexcept>();

    test_is_not_unsafe_fundamental<int (Class::*)(int, ...)>();
    test_is_not_unsafe_fundamental<int (Class::*)(int, ...)&>();
    test_is_not_unsafe_fundamental<int (Class::*)(int, ...) &&>();
    test_is_not_unsafe_fundamental<int (Class::*)(int, ...) const>();
    test_is_not_unsafe_fundamental<int (Class::*)(int, ...) const&>();
    test_is_not_unsafe_fundamental<int (Class::*)(int, ...) const&&>();
    test_is_not_unsafe_fundamental<int (Class::*)(int, ...) noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(int, ...)& noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(int, ...) const noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsafe_fundamental<int (Class::*)(int, ...) const&& noexcept>();
}
