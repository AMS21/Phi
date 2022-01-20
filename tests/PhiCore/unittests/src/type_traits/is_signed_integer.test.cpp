#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_integer.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/is_signed_integer.hpp>
#include <vector>

template <typename T>
void test_is_signed_integer_impl()
{
    STATIC_REQUIRE(phi::is_signed_integer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_signed_integer<T>::value);
    STATIC_REQUIRE(phi::is_integer<T>::value && phi::is_signed<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_signed_integer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_signed_integer_v<T>);
    STATIC_REQUIRE(phi::is_integer_v<T> && phi::is_signed_v<T>);
#endif
}

template <typename T>
void test_is_not_signed_integer_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_signed_integer<T>::value);
    STATIC_REQUIRE(phi::is_not_signed_integer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<T>::value && phi::is_signed<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_signed_integer_v<T>);
    STATIC_REQUIRE(phi::is_not_signed_integer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<T> && phi::is_signed_v<T>);
#endif
}

template <typename T>
void test_is_signed_integer()
{
    test_is_signed_integer_impl<T>();
    test_is_signed_integer_impl<const T>();
    test_is_signed_integer_impl<volatile T>();
    test_is_signed_integer_impl<const volatile T>();
}

template <typename T>
void test_is_not_signed_integer()
{
    test_is_not_signed_integer_impl<T>();
    test_is_not_signed_integer_impl<const T>();
    test_is_not_signed_integer_impl<volatile T>();
    test_is_not_signed_integer_impl<const volatile T>();
}

TEST_CASE("is_signed_integer")
{
    test_is_not_signed_integer<void>();
    test_is_not_signed_integer<phi::nullptr_t>();
    test_is_not_signed_integer<bool>();
    //test_is_not_signed_integer<char>();
    test_is_signed_integer<signed char>();
    test_is_not_signed_integer<unsigned char>();
    test_is_signed_integer<short>();
    test_is_not_signed_integer<unsigned short>();
    test_is_signed_integer<int>();
    test_is_not_signed_integer<unsigned int>();
    test_is_signed_integer<long>();
    test_is_not_signed_integer<unsigned long>();
    test_is_signed_integer<long long>();
    test_is_not_signed_integer<unsigned long long>();
    test_is_not_signed_integer<float>();
    test_is_not_signed_integer<double>();
    test_is_not_signed_integer<long double>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_is_not_signed_integer<char8_t>();
#endif
    test_is_not_signed_integer<char16_t>();
    test_is_not_signed_integer<char32_t>();
    test_is_not_signed_integer<wchar_t>();

    test_is_not_signed_integer<phi::boolean>();
    test_is_signed_integer<phi::integer<signed char>>();
    test_is_not_signed_integer<phi::integer<unsigned char>>();
    test_is_signed_integer<phi::integer<short>>();
    test_is_not_signed_integer<phi::integer<unsigned short>>();
    test_is_signed_integer<phi::integer<int>>();
    test_is_not_signed_integer<phi::integer<unsigned int>>();
    test_is_signed_integer<phi::integer<long>>();
    test_is_not_signed_integer<phi::integer<unsigned long>>();
    test_is_signed_integer<phi::integer<long long>>();
    test_is_not_signed_integer<phi::integer<unsigned long long>>();
    test_is_not_signed_integer<phi::floating_point<float>>();
    test_is_not_signed_integer<phi::floating_point<double>>();
    test_is_not_signed_integer<phi::floating_point<long double>>();

    test_is_not_signed_integer<std::vector<int>>();
    test_is_not_signed_integer<phi::scope_ptr<int>>();

    test_is_not_signed_integer<int&>();
    test_is_not_signed_integer<const int&>();
    test_is_not_signed_integer<volatile int&>();
    test_is_not_signed_integer<const volatile int&>();
    test_is_not_signed_integer<int&&>();
    test_is_not_signed_integer<const int&&>();
    test_is_not_signed_integer<volatile int&&>();
    test_is_not_signed_integer<const volatile int&&>();
    test_is_not_signed_integer<int*>();
    test_is_not_signed_integer<const int*>();
    test_is_not_signed_integer<volatile int*>();
    test_is_not_signed_integer<const volatile int*>();
    test_is_not_signed_integer<int**>();
    test_is_not_signed_integer<const int**>();
    test_is_not_signed_integer<volatile int**>();
    test_is_not_signed_integer<const volatile int**>();
    test_is_not_signed_integer<int*&>();
    test_is_not_signed_integer<const int*&>();
    test_is_not_signed_integer<volatile int*&>();
    test_is_not_signed_integer<const volatile int*&>();
    test_is_not_signed_integer<int*&&>();
    test_is_not_signed_integer<const int*&&>();
    test_is_not_signed_integer<volatile int*&&>();
    test_is_not_signed_integer<const volatile int*&&>();
    test_is_not_signed_integer<void*>();
    test_is_not_signed_integer<char[3]>();
    test_is_not_signed_integer<char[]>();
    test_is_not_signed_integer<char* [3]>();
    test_is_not_signed_integer<char*[]>();
    test_is_not_signed_integer<int(*)[3]>();
    test_is_not_signed_integer<int(*)[]>();
    test_is_not_signed_integer<int(&)[3]>();
    test_is_not_signed_integer<int(&)[]>();
    test_is_not_signed_integer<int(&&)[3]>();
    test_is_not_signed_integer<int(&&)[]>();
    test_is_not_signed_integer<char[3][2]>();
    test_is_not_signed_integer<char[][2]>();
    test_is_not_signed_integer<char* [3][2]>();
    test_is_not_signed_integer<char*[][2]>();
    test_is_not_signed_integer<int(*)[3][2]>();
    test_is_not_signed_integer<int(*)[][2]>();
    test_is_not_signed_integer<int(&)[3][2]>();
    test_is_not_signed_integer<int(&)[][2]>();
    test_is_not_signed_integer<int(&&)[3][2]>();
    test_is_not_signed_integer<int(&&)[][2]>();
    test_is_not_signed_integer<Class>();
    test_is_not_signed_integer<Class[]>();
    test_is_not_signed_integer<Class[2]>();
    test_is_not_signed_integer<Template<void>>();
    test_is_not_signed_integer<Template<int>>();
    test_is_not_signed_integer<Template<Class>>();
    test_is_not_signed_integer<Template<IncompleteType>>();
    test_is_not_signed_integer<VariadicTemplate<>>();
    test_is_not_signed_integer<VariadicTemplate<void>>();
    test_is_not_signed_integer<VariadicTemplate<int>>();
    test_is_not_signed_integer<VariadicTemplate<Class>>();
    test_is_not_signed_integer<VariadicTemplate<IncompleteType>>();
    test_is_not_signed_integer<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_signed_integer<PublicDerivedFromTemplate<Base>>();
    test_is_not_signed_integer<PublicDerivedFromTemplate<Derived>>();
    test_is_not_signed_integer<PublicDerivedFromTemplate<Class>>();
    test_is_not_signed_integer<PrivateDerivedFromTemplate<Base>>();
    test_is_not_signed_integer<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_signed_integer<PrivateDerivedFromTemplate<Class>>();
    test_is_not_signed_integer<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_signed_integer<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_signed_integer<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_signed_integer<VirtualDerivedFromTemplate<Base>>();
    test_is_not_signed_integer<VirtualDerivedFromTemplate<Derived>>();
    test_is_not_signed_integer<VirtualDerivedFromTemplate<Class>>();
    test_is_not_signed_integer<Union>();
    test_is_not_signed_integer<NonEmptyUnion>();
    test_is_not_signed_integer<NonTrivialUnion>();
    test_is_not_signed_integer<Empty>();
    test_is_not_signed_integer<NotEmpty>();
    test_is_not_signed_integer<NonTrivial>();
    test_is_not_signed_integer<BitZero>();
    test_is_not_signed_integer<BitOne>();
    test_is_not_signed_integer<Base>();
    test_is_not_signed_integer<Derived>();
    test_is_not_signed_integer<Polymorphic>();
    test_is_not_signed_integer<DerivedPolymorphic>();
    test_is_not_signed_integer<Abstract>();
    test_is_not_signed_integer<PublicAbstract>();
    test_is_not_signed_integer<PrivateAbstract>();
    test_is_not_signed_integer<ProtectedAbstract>();
    test_is_not_signed_integer<AbstractTemplate<int>>();
    test_is_not_signed_integer<AbstractTemplate<double>>();
    test_is_not_signed_integer<AbstractTemplate<Class>>();
    test_is_not_signed_integer<AbstractTemplate<IncompleteType>>();
    test_is_not_signed_integer<PublicAbstractDeletedDestructor>();
    test_is_not_signed_integer<ProtectedAbstractDeletedDestructor>();
    test_is_not_signed_integer<PrivateAbstractDeletedDestructor>();
    test_is_not_signed_integer<Final>();
    test_is_not_signed_integer<FinalDerived>();
    test_is_not_signed_integer<PublicDestructor>();
    test_is_not_signed_integer<ProtectedDestructor>();
    test_is_not_signed_integer<PrivateDestructor>();
    test_is_not_signed_integer<VirtualPublicDestructor>();
    test_is_not_signed_integer<VirtualProtectedDestructor>();
    test_is_not_signed_integer<VirtualPrivateDestructor>();
    test_is_not_signed_integer<PurePublicDestructor>();
    test_is_not_signed_integer<PureProtectedDestructor>();
    test_is_not_signed_integer<PurePrivateDestructor>();
    test_is_not_signed_integer<DeletedPublicDestructor>();
    test_is_not_signed_integer<DeletedProtectedDestructor>();
    test_is_not_signed_integer<DeletedPrivateDestructor>();
    test_is_not_signed_integer<DeletedVirtualPublicDestructor>();
    test_is_not_signed_integer<DeletedVirtualProtectedDestructor>();
    test_is_not_signed_integer<DeletedVirtualPrivateDestructor>();
    test_is_not_signed_integer<ExplicitClass>();
    test_is_not_signed_integer<NothrowExplicitClass>();
    test_is_not_signed_integer<ThrowExplicitClass>();
    test_is_not_signed_integer<ThrowDefaultClass>();
    test_is_not_signed_integer<ThrowCopyConsClass>();
    test_is_not_signed_integer<ThrowMoveConsClass>();
    test_is_not_signed_integer<NoexceptExplicitClass>();
    test_is_not_signed_integer<ExceptExplicitClass>();
    test_is_not_signed_integer<NoexceptDefaultClass>();
    test_is_not_signed_integer<ExceptDefaultClass>();
    test_is_not_signed_integer<NoexceptCopyConsClass>();
    test_is_not_signed_integer<ExceptCopyConsClass>();
    test_is_not_signed_integer<NoexceptMoveConsClass>();
    test_is_not_signed_integer<ExceptMoveConsClass>();
    test_is_not_signed_integer<NoexceptCopyAssignClass>();
    test_is_not_signed_integer<ExceptCopyAssignClass>();
    test_is_not_signed_integer<NoexceptMoveAssignClass>();
    test_is_not_signed_integer<ExceptMoveAssignClass>();
    test_is_not_signed_integer<DeletedCopyAssignClass>();
    test_is_not_signed_integer<DeletedMoveAssignClass>();
    test_is_not_signed_integer<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_signed_integer<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_signed_integer<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_not_signed_integer<ExceptMoveConsExceptMoveAssignClass>();
    test_is_not_signed_integer<ImplicitTo<int>>();
    test_is_not_signed_integer<ImplicitTo<float>>();
    test_is_not_signed_integer<ImplicitTo<Class>>();
    test_is_not_signed_integer<DeletedImplicitTo<int>>();
    test_is_not_signed_integer<DeletedImplicitTo<float>>();
    test_is_not_signed_integer<DeletedImplicitTo<Class>>();
    test_is_not_signed_integer<ExplicitTo<int>>();
    test_is_not_signed_integer<ExplicitTo<float>>();
    test_is_not_signed_integer<ExplicitTo<Class>>();
    test_is_not_signed_integer<DeletedExplicitTo<int>>();
    test_is_not_signed_integer<DeletedExplicitTo<float>>();
    test_is_not_signed_integer<DeletedExplicitTo<Class>>();
    test_is_not_signed_integer<Ellipsis>();
    test_is_not_signed_integer<DeletedEllipsis>();
    test_is_not_signed_integer<CopyConsOnlyType>();
    test_is_not_signed_integer<MoveConsOnlyType>();
    test_is_not_signed_integer<OverloadedOperators>();
    test_is_not_signed_integer<PublicIntMember>();
    test_is_not_signed_integer<ProtectedIntMember>();
    test_is_not_signed_integer<PrivateIntMember>();
    test_is_not_signed_integer<PublicStaticIntMember>();
    test_is_not_signed_integer<ProtectedStaticIntMember>();
    test_is_not_signed_integer<PrivateStaticIntMember>();
    test_is_not_signed_integer<PublicTemplateMember<int>>();
    test_is_not_signed_integer<PublicTemplateMember<float>>();
    test_is_not_signed_integer<PublicTemplateMember<Class>>();
    test_is_not_signed_integer<ProtectedTemplateMember<int>>();
    test_is_not_signed_integer<ProtectedTemplateMember<float>>();
    test_is_not_signed_integer<ProtectedTemplateMember<Class>>();
    test_is_not_signed_integer<PrivateTemplateMember<int>>();
    test_is_not_signed_integer<PrivateTemplateMember<float>>();
    test_is_not_signed_integer<PrivateTemplateMember<Class>>();
    test_is_not_signed_integer<PublicStaticTemplateMember<int>>();
    test_is_not_signed_integer<PublicStaticTemplateMember<float>>();
    test_is_not_signed_integer<PublicStaticTemplateMember<Class>>();
    test_is_not_signed_integer<ProtectedStaticTemplateMember<int>>();
    test_is_not_signed_integer<ProtectedStaticTemplateMember<float>>();
    test_is_not_signed_integer<ProtectedStaticTemplateMember<Class>>();
    test_is_not_signed_integer<PrivateStaticTemplateMember<int>>();
    test_is_not_signed_integer<PrivateStaticTemplateMember<float>>();
    test_is_not_signed_integer<PrivateStaticTemplateMember<Class>>();
    test_is_not_signed_integer<Enum>();
    test_is_not_signed_integer<EnumSigned>();
    test_is_not_signed_integer<EnumUnsigned>();
    test_is_not_signed_integer<EnumClass>();
    test_is_not_signed_integer<EnumStruct>();
    test_is_not_signed_integer<Function>();
    test_is_not_signed_integer<FunctionPtr>();
    test_is_not_signed_integer<MemberObjectPtr>();
    test_is_not_signed_integer<MemberFunctionPtr>();
    test_is_not_signed_integer<LambdaType>();
    test_is_not_signed_integer<LambdaNoexceptType>();
    test_is_not_signed_integer<LambdaThrowsType>();
    test_is_not_signed_integer<IncompleteType>();
    test_is_not_signed_integer<IncompleteTemplate<void>>();
    test_is_not_signed_integer<IncompleteTemplate<int>>();
    test_is_not_signed_integer<IncompleteTemplate<Class>>();
    test_is_not_signed_integer<IncompleteTemplate<IncompleteType>>();
    test_is_not_signed_integer<IncompleteVariadicTemplate<>>();
    test_is_not_signed_integer<IncompleteVariadicTemplate<void>>();
    test_is_not_signed_integer<IncompleteVariadicTemplate<int>>();
    test_is_not_signed_integer<IncompleteVariadicTemplate<Class>>();
    test_is_not_signed_integer<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_signed_integer<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_signed_integer<IncompleteUnion>();
    test_is_not_signed_integer<IncompleteEnumSigned>();
    test_is_not_signed_integer<IncompleteEnumUnsigned>();
    test_is_not_signed_integer<IncompleteEnumClass>();
    test_is_not_signed_integer<IncompleteEnumStruct>();
    test_is_not_signed_integer<int Class::*>();
    test_is_not_signed_integer<float Class::*>();
    test_is_not_signed_integer<void * Class::*>();
    test_is_not_signed_integer<int * Class::*>();
    test_is_not_signed_integer<int Class::*&>();
    test_is_not_signed_integer<float Class::*&>();
    test_is_not_signed_integer<void * Class::*&>();
    test_is_not_signed_integer<int * Class::*&>();
    test_is_not_signed_integer<int Class::*&&>();
    test_is_not_signed_integer<float Class::*&&>();
    test_is_not_signed_integer<void * Class::*&&>();
    test_is_not_signed_integer<int * Class::*&&>();
    test_is_not_signed_integer<int Class::*const>();
    test_is_not_signed_integer<float Class::*const>();
    test_is_not_signed_integer<void * Class::*const>();
    test_is_not_signed_integer<int Class::*const&>();
    test_is_not_signed_integer<float Class::*const&>();
    test_is_not_signed_integer<void * Class::*const&>();
    test_is_not_signed_integer<int Class::*const&&>();
    test_is_not_signed_integer<float Class::*const&&>();
    test_is_not_signed_integer<void * Class::*const&&>();
    test_is_not_signed_integer<int Class::*volatile>();
    test_is_not_signed_integer<float Class::*volatile>();
    test_is_not_signed_integer<void * Class::*volatile>();
    test_is_not_signed_integer<int Class::*volatile&>();
    test_is_not_signed_integer<float Class::*volatile&>();
    test_is_not_signed_integer<void * Class::*volatile&>();
    test_is_not_signed_integer<int Class::*volatile&&>();
    test_is_not_signed_integer<float Class::*volatile&&>();
    test_is_not_signed_integer<void * Class::*volatile&&>();
    test_is_not_signed_integer<int Class::*const volatile>();
    test_is_not_signed_integer<float Class::*const volatile>();
    test_is_not_signed_integer<void * Class::*const volatile>();
    test_is_not_signed_integer<int Class::*const volatile&>();
    test_is_not_signed_integer<float Class::*const volatile&>();
    test_is_not_signed_integer<void * Class::*const volatile&>();
    test_is_not_signed_integer<int Class::*const volatile&&>();
    test_is_not_signed_integer<float Class::*const volatile&&>();
    test_is_not_signed_integer<void * Class::*const volatile&&>();
    test_is_not_signed_integer<NonCopyable>();
    test_is_not_signed_integer<NonMoveable>();
    test_is_not_signed_integer<NonConstructible>();
    test_is_not_signed_integer<NonDestructible>();
    test_is_not_signed_integer<Tracked>();
    test_is_not_signed_integer<TrapConstructible>();
    test_is_not_signed_integer<TrapImplicitConversion>();
    test_is_not_signed_integer<TrapComma>();
    test_is_not_signed_integer<TrapCall>();
    test_is_not_signed_integer<TrapSelfAssign>();
    test_is_not_signed_integer<TrapDeref>();
    test_is_not_signed_integer<TrapArraySubscript>();

    test_is_not_signed_integer<void()>();
    test_is_not_signed_integer<void()&>();
    test_is_not_signed_integer<void() &&>();
    test_is_not_signed_integer<void() const>();
    test_is_not_signed_integer<void() const&>();
    test_is_not_signed_integer<void() const&&>();
    test_is_not_signed_integer<void() volatile>();
    test_is_not_signed_integer<void() volatile&>();
    test_is_not_signed_integer<void() volatile&&>();
    test_is_not_signed_integer<void() const volatile>();
    test_is_not_signed_integer<void() const volatile&>();
    test_is_not_signed_integer<void() const volatile&&>();
    test_is_not_signed_integer<void() noexcept>();
    test_is_not_signed_integer<void()& noexcept>();
    test_is_not_signed_integer<void()&& noexcept>();
    test_is_not_signed_integer<void() const noexcept>();
    test_is_not_signed_integer<void() const& noexcept>();
    test_is_not_signed_integer<void() const&& noexcept>();
    test_is_not_signed_integer<void() volatile noexcept>();
    test_is_not_signed_integer<void() volatile& noexcept>();
    test_is_not_signed_integer<void() volatile&& noexcept>();
    test_is_not_signed_integer<void() const volatile noexcept>();
    test_is_not_signed_integer<void() const volatile& noexcept>();
    test_is_not_signed_integer<void() const volatile&& noexcept>();

    test_is_not_signed_integer<void(int)>();
    test_is_not_signed_integer<void(int)&>();
    test_is_not_signed_integer<void(int) &&>();
    test_is_not_signed_integer<void(int) const>();
    test_is_not_signed_integer<void(int) const&>();
    test_is_not_signed_integer<void(int) const&&>();
    test_is_not_signed_integer<void(int) volatile>();
    test_is_not_signed_integer<void(int) volatile&>();
    test_is_not_signed_integer<void(int) volatile&&>();
    test_is_not_signed_integer<void(int) const volatile>();
    test_is_not_signed_integer<void(int) const volatile&>();
    test_is_not_signed_integer<void(int) const volatile&&>();
    test_is_not_signed_integer<void(int) noexcept>();
    test_is_not_signed_integer<void(int)& noexcept>();
    test_is_not_signed_integer<void(int)&& noexcept>();
    test_is_not_signed_integer<void(int) const noexcept>();
    test_is_not_signed_integer<void(int) const& noexcept>();
    test_is_not_signed_integer<void(int) const&& noexcept>();
    test_is_not_signed_integer<void(int) volatile noexcept>();
    test_is_not_signed_integer<void(int) volatile& noexcept>();
    test_is_not_signed_integer<void(int) volatile&& noexcept>();
    test_is_not_signed_integer<void(int) const volatile noexcept>();
    test_is_not_signed_integer<void(int) const volatile& noexcept>();
    test_is_not_signed_integer<void(int) const volatile&& noexcept>();

    test_is_not_signed_integer<void(...)>();
    test_is_not_signed_integer<void(...)&>();
    test_is_not_signed_integer<void(...) &&>();
    test_is_not_signed_integer<void(...) const>();
    test_is_not_signed_integer<void(...) const&>();
    test_is_not_signed_integer<void(...) const&&>();
    test_is_not_signed_integer<void(...) volatile>();
    test_is_not_signed_integer<void(...) volatile&>();
    test_is_not_signed_integer<void(...) volatile&&>();
    test_is_not_signed_integer<void(...) const volatile>();
    test_is_not_signed_integer<void(...) const volatile&>();
    test_is_not_signed_integer<void(...) const volatile&&>();
    test_is_not_signed_integer<void(...) noexcept>();
    test_is_not_signed_integer<void(...)& noexcept>();
    test_is_not_signed_integer<void(...)&& noexcept>();
    test_is_not_signed_integer<void(...) const noexcept>();
    test_is_not_signed_integer<void(...) const& noexcept>();
    test_is_not_signed_integer<void(...) const&& noexcept>();
    test_is_not_signed_integer<void(...) volatile noexcept>();
    test_is_not_signed_integer<void(...) volatile& noexcept>();
    test_is_not_signed_integer<void(...) volatile&& noexcept>();
    test_is_not_signed_integer<void(...) const volatile noexcept>();
    test_is_not_signed_integer<void(...) const volatile& noexcept>();
    test_is_not_signed_integer<void(...) const volatile&& noexcept>();

    test_is_not_signed_integer<void(int, ...)>();
    test_is_not_signed_integer<void(int, ...)&>();
    test_is_not_signed_integer<void(int, ...) &&>();
    test_is_not_signed_integer<void(int, ...) const>();
    test_is_not_signed_integer<void(int, ...) const&>();
    test_is_not_signed_integer<void(int, ...) const&&>();
    test_is_not_signed_integer<void(int, ...) volatile>();
    test_is_not_signed_integer<void(int, ...) volatile&>();
    test_is_not_signed_integer<void(int, ...) volatile&&>();
    test_is_not_signed_integer<void(int, ...) const volatile>();
    test_is_not_signed_integer<void(int, ...) const volatile&>();
    test_is_not_signed_integer<void(int, ...) const volatile&&>();
    test_is_not_signed_integer<void(int, ...) noexcept>();
    test_is_not_signed_integer<void(int, ...)& noexcept>();
    test_is_not_signed_integer<void(int, ...)&& noexcept>();
    test_is_not_signed_integer<void(int, ...) const noexcept>();
    test_is_not_signed_integer<void(int, ...) const& noexcept>();
    test_is_not_signed_integer<void(int, ...) const&& noexcept>();
    test_is_not_signed_integer<void(int, ...) volatile noexcept>();
    test_is_not_signed_integer<void(int, ...) volatile& noexcept>();
    test_is_not_signed_integer<void(int, ...) volatile&& noexcept>();
    test_is_not_signed_integer<void(int, ...) const volatile noexcept>();
    test_is_not_signed_integer<void(int, ...) const volatile& noexcept>();
    test_is_not_signed_integer<void(int, ...) const volatile&& noexcept>();

    test_is_not_signed_integer<int()>();
    test_is_not_signed_integer<int()&>();
    test_is_not_signed_integer<int() &&>();
    test_is_not_signed_integer<int() const>();
    test_is_not_signed_integer<int() const&>();
    test_is_not_signed_integer<int() const&&>();
    test_is_not_signed_integer<int() volatile>();
    test_is_not_signed_integer<int() volatile&>();
    test_is_not_signed_integer<int() volatile&&>();
    test_is_not_signed_integer<int() const volatile>();
    test_is_not_signed_integer<int() const volatile&>();
    test_is_not_signed_integer<int() const volatile&&>();
    test_is_not_signed_integer<int() noexcept>();
    test_is_not_signed_integer<int()& noexcept>();
    test_is_not_signed_integer<int()&& noexcept>();
    test_is_not_signed_integer<int() const noexcept>();
    test_is_not_signed_integer<int() const& noexcept>();
    test_is_not_signed_integer<int() const&& noexcept>();
    test_is_not_signed_integer<int() volatile noexcept>();
    test_is_not_signed_integer<int() volatile& noexcept>();
    test_is_not_signed_integer<int() volatile&& noexcept>();
    test_is_not_signed_integer<int() const volatile noexcept>();
    test_is_not_signed_integer<int() const volatile& noexcept>();
    test_is_not_signed_integer<int() const volatile&& noexcept>();

    test_is_not_signed_integer<int(int)>();
    test_is_not_signed_integer<int(int)&>();
    test_is_not_signed_integer<int(int) &&>();
    test_is_not_signed_integer<int(int) const>();
    test_is_not_signed_integer<int(int) const&>();
    test_is_not_signed_integer<int(int) const&&>();
    test_is_not_signed_integer<int(int) volatile>();
    test_is_not_signed_integer<int(int) volatile&>();
    test_is_not_signed_integer<int(int) volatile&&>();
    test_is_not_signed_integer<int(int) const volatile>();
    test_is_not_signed_integer<int(int) const volatile&>();
    test_is_not_signed_integer<int(int) const volatile&&>();
    test_is_not_signed_integer<int(int) noexcept>();
    test_is_not_signed_integer<int(int)& noexcept>();
    test_is_not_signed_integer<int(int)&& noexcept>();
    test_is_not_signed_integer<int(int) const noexcept>();
    test_is_not_signed_integer<int(int) const& noexcept>();
    test_is_not_signed_integer<int(int) const&& noexcept>();
    test_is_not_signed_integer<int(int) volatile noexcept>();
    test_is_not_signed_integer<int(int) volatile& noexcept>();
    test_is_not_signed_integer<int(int) volatile&& noexcept>();
    test_is_not_signed_integer<int(int) const volatile noexcept>();
    test_is_not_signed_integer<int(int) const volatile& noexcept>();
    test_is_not_signed_integer<int(int) const volatile&& noexcept>();

    test_is_not_signed_integer<int(...)>();
    test_is_not_signed_integer<int(...)&>();
    test_is_not_signed_integer<int(...) &&>();
    test_is_not_signed_integer<int(...) const>();
    test_is_not_signed_integer<int(...) const&>();
    test_is_not_signed_integer<int(...) const&&>();
    test_is_not_signed_integer<int(...) volatile>();
    test_is_not_signed_integer<int(...) volatile&>();
    test_is_not_signed_integer<int(...) volatile&&>();
    test_is_not_signed_integer<int(...) const volatile>();
    test_is_not_signed_integer<int(...) const volatile&>();
    test_is_not_signed_integer<int(...) const volatile&&>();
    test_is_not_signed_integer<int(...) noexcept>();
    test_is_not_signed_integer<int(...)& noexcept>();
    test_is_not_signed_integer<int(...)&& noexcept>();
    test_is_not_signed_integer<int(...) const noexcept>();
    test_is_not_signed_integer<int(...) const& noexcept>();
    test_is_not_signed_integer<int(...) const&& noexcept>();
    test_is_not_signed_integer<int(...) volatile noexcept>();
    test_is_not_signed_integer<int(...) volatile& noexcept>();
    test_is_not_signed_integer<int(...) volatile&& noexcept>();
    test_is_not_signed_integer<int(...) const volatile noexcept>();
    test_is_not_signed_integer<int(...) const volatile& noexcept>();
    test_is_not_signed_integer<int(...) const volatile&& noexcept>();

    test_is_not_signed_integer<int(int, ...)>();
    test_is_not_signed_integer<int(int, ...)&>();
    test_is_not_signed_integer<int(int, ...) &&>();
    test_is_not_signed_integer<int(int, ...) const>();
    test_is_not_signed_integer<int(int, ...) const&>();
    test_is_not_signed_integer<int(int, ...) const&&>();
    test_is_not_signed_integer<int(int, ...) volatile>();
    test_is_not_signed_integer<int(int, ...) volatile&>();
    test_is_not_signed_integer<int(int, ...) volatile&&>();
    test_is_not_signed_integer<int(int, ...) const volatile>();
    test_is_not_signed_integer<int(int, ...) const volatile&>();
    test_is_not_signed_integer<int(int, ...) const volatile&&>();
    test_is_not_signed_integer<int(int, ...) noexcept>();
    test_is_not_signed_integer<int(int, ...)& noexcept>();
    test_is_not_signed_integer<int(int, ...)&& noexcept>();
    test_is_not_signed_integer<int(int, ...) const noexcept>();
    test_is_not_signed_integer<int(int, ...) const& noexcept>();
    test_is_not_signed_integer<int(int, ...) const&& noexcept>();
    test_is_not_signed_integer<int(int, ...) volatile noexcept>();
    test_is_not_signed_integer<int(int, ...) volatile& noexcept>();
    test_is_not_signed_integer<int(int, ...) volatile&& noexcept>();
    test_is_not_signed_integer<int(int, ...) const volatile noexcept>();
    test_is_not_signed_integer<int(int, ...) const volatile& noexcept>();
    test_is_not_signed_integer<int(int, ...) const volatile&& noexcept>();

    test_is_not_signed_integer<void (*)()>();
    test_is_not_signed_integer<void (*)() noexcept>();

    test_is_not_signed_integer<void (*)(int)>();
    test_is_not_signed_integer<void (*)(int) noexcept>();

    test_is_not_signed_integer<void (*)(...)>();
    test_is_not_signed_integer<void (*)(...) noexcept>();

    test_is_not_signed_integer<void (*)(int, ...)>();
    test_is_not_signed_integer<void (*)(int, ...) noexcept>();

    test_is_not_signed_integer<int (*)()>();
    test_is_not_signed_integer<int (*)() noexcept>();

    test_is_not_signed_integer<int (*)(int)>();
    test_is_not_signed_integer<int (*)(int) noexcept>();

    test_is_not_signed_integer<int (*)(...)>();
    test_is_not_signed_integer<int (*)(...) noexcept>();

    test_is_not_signed_integer<int (*)(int, ...)>();
    test_is_not_signed_integer<int (*)(int, ...) noexcept>();

    test_is_not_signed_integer<void (&)()>();
    test_is_not_signed_integer<void (&)() noexcept>();

    test_is_not_signed_integer<void (&)(int)>();
    test_is_not_signed_integer<void (&)(int) noexcept>();

    test_is_not_signed_integer<void (&)(...)>();
    test_is_not_signed_integer<void (&)(...) noexcept>();

    test_is_not_signed_integer<void (&)(int, ...)>();
    test_is_not_signed_integer<void (&)(int, ...) noexcept>();

    test_is_not_signed_integer<int (&)()>();
    test_is_not_signed_integer<int (&)() noexcept>();

    test_is_not_signed_integer<int (&)(int)>();
    test_is_not_signed_integer<int (&)(int) noexcept>();

    test_is_not_signed_integer<int (&)(...)>();
    test_is_not_signed_integer<int (&)(...) noexcept>();

    test_is_not_signed_integer<int (&)(int, ...)>();
    test_is_not_signed_integer<int (&)(int, ...) noexcept>();

    test_is_not_signed_integer<void(&&)()>();
    test_is_not_signed_integer<void(&&)() noexcept>();

    test_is_not_signed_integer<void(&&)(int)>();
    test_is_not_signed_integer<void(&&)(int) noexcept>();

    test_is_not_signed_integer<void(&&)(...)>();
    test_is_not_signed_integer<void(&&)(...) noexcept>();

    test_is_not_signed_integer<void(&&)(int, ...)>();
    test_is_not_signed_integer<void(&&)(int, ...) noexcept>();

    test_is_not_signed_integer<int(&&)()>();
    test_is_not_signed_integer<int(&&)() noexcept>();

    test_is_not_signed_integer<int(&&)(int)>();
    test_is_not_signed_integer<int(&&)(int) noexcept>();

    test_is_not_signed_integer<int(&&)(...)>();
    test_is_not_signed_integer<int(&&)(...) noexcept>();

    test_is_not_signed_integer<int(&&)(int, ...)>();
    test_is_not_signed_integer<int(&&)(int, ...) noexcept>();

    test_is_not_signed_integer<void (Class::*)()>();
    test_is_not_signed_integer<void (Class::*)()&>();
    test_is_not_signed_integer<void (Class::*)() &&>();
    test_is_not_signed_integer<void (Class::*)() const>();
    test_is_not_signed_integer<void (Class::*)() const&>();
    test_is_not_signed_integer<void (Class::*)() const&&>();
    test_is_not_signed_integer<void (Class::*)() noexcept>();
    test_is_not_signed_integer<void (Class::*)()& noexcept>();
    test_is_not_signed_integer<void (Class::*)()&& noexcept>();
    test_is_not_signed_integer<void (Class::*)() const noexcept>();
    test_is_not_signed_integer<void (Class::*)() const& noexcept>();
    test_is_not_signed_integer<void (Class::*)() const&& noexcept>();

    test_is_not_signed_integer<void (Class::*)(int)>();
    test_is_not_signed_integer<void (Class::*)(int)&>();
    test_is_not_signed_integer<void (Class::*)(int) &&>();
    test_is_not_signed_integer<void (Class::*)(int) const>();
    test_is_not_signed_integer<void (Class::*)(int) const&>();
    test_is_not_signed_integer<void (Class::*)(int) const&&>();
    test_is_not_signed_integer<void (Class::*)(int) noexcept>();
    test_is_not_signed_integer<void (Class::*)(int)& noexcept>();
    test_is_not_signed_integer<void (Class::*)(int)&& noexcept>();
    test_is_not_signed_integer<void (Class::*)(int) const noexcept>();
    test_is_not_signed_integer<void (Class::*)(int) const& noexcept>();
    test_is_not_signed_integer<void (Class::*)(int) const&& noexcept>();

    test_is_not_signed_integer<void (Class::*)(...)>();
    test_is_not_signed_integer<void (Class::*)(...)&>();
    test_is_not_signed_integer<void (Class::*)(...) &&>();
    test_is_not_signed_integer<void (Class::*)(...) const>();
    test_is_not_signed_integer<void (Class::*)(...) const&>();
    test_is_not_signed_integer<void (Class::*)(...) const&&>();
    test_is_not_signed_integer<void (Class::*)(...) noexcept>();
    test_is_not_signed_integer<void (Class::*)(...)& noexcept>();
    test_is_not_signed_integer<void (Class::*)(...)&& noexcept>();
    test_is_not_signed_integer<void (Class::*)(...) const noexcept>();
    test_is_not_signed_integer<void (Class::*)(...) const& noexcept>();
    test_is_not_signed_integer<void (Class::*)(...) const&& noexcept>();

    test_is_not_signed_integer<void (Class::*)(int, ...)>();
    test_is_not_signed_integer<void (Class::*)(int, ...)&>();
    test_is_not_signed_integer<void (Class::*)(int, ...) &&>();
    test_is_not_signed_integer<void (Class::*)(int, ...) const>();
    test_is_not_signed_integer<void (Class::*)(int, ...) const&>();
    test_is_not_signed_integer<void (Class::*)(int, ...) const&&>();
    test_is_not_signed_integer<void (Class::*)(int, ...) noexcept>();
    test_is_not_signed_integer<void (Class::*)(int, ...)& noexcept>();
    test_is_not_signed_integer<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_signed_integer<void (Class::*)(int, ...) const noexcept>();
    test_is_not_signed_integer<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_signed_integer<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_signed_integer<int (Class::*)()>();
    test_is_not_signed_integer<int (Class::*)()&>();
    test_is_not_signed_integer<int (Class::*)() &&>();
    test_is_not_signed_integer<int (Class::*)() const>();
    test_is_not_signed_integer<int (Class::*)() const&>();
    test_is_not_signed_integer<int (Class::*)() const&&>();
    test_is_not_signed_integer<int (Class::*)() noexcept>();
    test_is_not_signed_integer<int (Class::*)()& noexcept>();
    test_is_not_signed_integer<int (Class::*)()&& noexcept>();
    test_is_not_signed_integer<int (Class::*)() const noexcept>();
    test_is_not_signed_integer<int (Class::*)() const& noexcept>();
    test_is_not_signed_integer<int (Class::*)() const&& noexcept>();

    test_is_not_signed_integer<int (Class::*)(int)>();
    test_is_not_signed_integer<int (Class::*)(int)&>();
    test_is_not_signed_integer<int (Class::*)(int) &&>();
    test_is_not_signed_integer<int (Class::*)(int) const>();
    test_is_not_signed_integer<int (Class::*)(int) const&>();
    test_is_not_signed_integer<int (Class::*)(int) const&&>();
    test_is_not_signed_integer<int (Class::*)(int) noexcept>();
    test_is_not_signed_integer<int (Class::*)(int)& noexcept>();
    test_is_not_signed_integer<int (Class::*)(int)&& noexcept>();
    test_is_not_signed_integer<int (Class::*)(int) const noexcept>();
    test_is_not_signed_integer<int (Class::*)(int) const& noexcept>();
    test_is_not_signed_integer<int (Class::*)(int) const&& noexcept>();

    test_is_not_signed_integer<int (Class::*)(...)>();
    test_is_not_signed_integer<int (Class::*)(...)&>();
    test_is_not_signed_integer<int (Class::*)(...) &&>();
    test_is_not_signed_integer<int (Class::*)(...) const>();
    test_is_not_signed_integer<int (Class::*)(...) const&>();
    test_is_not_signed_integer<int (Class::*)(...) const&&>();
    test_is_not_signed_integer<int (Class::*)(...) noexcept>();
    test_is_not_signed_integer<int (Class::*)(...)& noexcept>();
    test_is_not_signed_integer<int (Class::*)(...)&& noexcept>();
    test_is_not_signed_integer<int (Class::*)(...) const noexcept>();
    test_is_not_signed_integer<int (Class::*)(...) const& noexcept>();
    test_is_not_signed_integer<int (Class::*)(...) const&& noexcept>();

    test_is_not_signed_integer<int (Class::*)(int, ...)>();
    test_is_not_signed_integer<int (Class::*)(int, ...)&>();
    test_is_not_signed_integer<int (Class::*)(int, ...) &&>();
    test_is_not_signed_integer<int (Class::*)(int, ...) const>();
    test_is_not_signed_integer<int (Class::*)(int, ...) const&>();
    test_is_not_signed_integer<int (Class::*)(int, ...) const&&>();
    test_is_not_signed_integer<int (Class::*)(int, ...) noexcept>();
    test_is_not_signed_integer<int (Class::*)(int, ...)& noexcept>();
    test_is_not_signed_integer<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_signed_integer<int (Class::*)(int, ...) const noexcept>();
    test_is_not_signed_integer<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_signed_integer<int (Class::*)(int, ...) const&& noexcept>();
}
