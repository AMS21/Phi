#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unsafe_signed.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_unsafe_signed_impl()
{
    STATIC_REQUIRE(phi::is_unsafe_signed<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_signed<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_signed_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_signed_v<T>);
#endif

    // Standard compatibililty
    STATIC_REQUIRE(std::is_signed<T>::value);
}

template <typename T>
void test_is_not_unsafe_signed_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_signed<T>::value);
    STATIC_REQUIRE(phi::is_not_unsafe_signed<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_signed_v<T>);
    STATIC_REQUIRE(phi::is_not_unsafe_signed_v<T>);
#endif

    STATIC_REQUIRE_FALSE(std::is_signed<T>::value);
}

template <typename T>
void test_is_unsafe_signed()
{
    test_is_unsafe_signed_impl<T>();
    test_is_unsafe_signed_impl<const T>();
    test_is_unsafe_signed_impl<volatile T>();
    test_is_unsafe_signed_impl<const volatile T>();
}

template <typename T>
void test_is_not_unsafe_signed()
{
    test_is_not_unsafe_signed_impl<T>();
    test_is_not_unsafe_signed_impl<const T>();
    test_is_not_unsafe_signed_impl<volatile T>();
    test_is_not_unsafe_signed_impl<const volatile T>();
}

TEST_CASE("is_unsafe_signed")
{
    test_is_not_unsafe_signed<void>();
    test_is_not_unsafe_signed<phi::nullptr_t>();
    test_is_not_unsafe_signed<bool>();
    //test_is_not_unsafe_signed<char>();
    test_is_unsafe_signed<signed char>();
    test_is_not_unsafe_signed<unsigned char>();
    test_is_unsafe_signed<short>();
    test_is_not_unsafe_signed<unsigned short>();
    test_is_unsafe_signed<int>();
    test_is_not_unsafe_signed<unsigned int>();
    test_is_unsafe_signed<long>();
    test_is_not_unsafe_signed<unsigned long>();
    test_is_unsafe_signed<long long>();
    test_is_not_unsafe_signed<unsigned long long>();
    test_is_unsafe_signed<float>();
    test_is_unsafe_signed<double>();
    test_is_unsafe_signed<long double>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_is_not_unsafe_signed<char8_t>();
#endif
    test_is_not_unsafe_signed<char16_t>();
    test_is_not_unsafe_signed<char32_t>();
#if PHI_PLATFORM_IS(WINDOWS)
    test_is_not_unsafe_signed<wchar_t>();
#else
    test_is_unsafe_signed<wchar_t>();
#endif

    test_is_not_unsafe_signed<phi::boolean>();
    test_is_not_unsafe_signed<phi::integer<signed char>>();
    test_is_not_unsafe_signed<phi::integer<unsigned char>>();
    test_is_not_unsafe_signed<phi::integer<short>>();
    test_is_not_unsafe_signed<phi::integer<unsigned short>>();
    test_is_not_unsafe_signed<phi::integer<int>>();
    test_is_not_unsafe_signed<phi::integer<unsigned int>>();
    test_is_not_unsafe_signed<phi::integer<long>>();
    test_is_not_unsafe_signed<phi::integer<unsigned long>>();
    test_is_not_unsafe_signed<phi::integer<long long>>();
    test_is_not_unsafe_signed<phi::integer<unsigned long long>>();
    test_is_not_unsafe_signed<phi::floating_point<float>>();
    test_is_not_unsafe_signed<phi::floating_point<double>>();
    test_is_not_unsafe_signed<phi::floating_point<long double>>();

    test_is_not_unsafe_signed<std::vector<int>>();
    test_is_not_unsafe_signed<phi::scope_ptr<int>>();

    test_is_not_unsafe_signed<int&>();
    test_is_not_unsafe_signed<const int&>();
    test_is_not_unsafe_signed<volatile int&>();
    test_is_not_unsafe_signed<const volatile int&>();
    test_is_not_unsafe_signed<int&&>();
    test_is_not_unsafe_signed<const int&&>();
    test_is_not_unsafe_signed<volatile int&&>();
    test_is_not_unsafe_signed<const volatile int&&>();
    test_is_not_unsafe_signed<int*>();
    test_is_not_unsafe_signed<const int*>();
    test_is_not_unsafe_signed<volatile int*>();
    test_is_not_unsafe_signed<const volatile int*>();
    test_is_not_unsafe_signed<int**>();
    test_is_not_unsafe_signed<const int**>();
    test_is_not_unsafe_signed<volatile int**>();
    test_is_not_unsafe_signed<const volatile int**>();
    test_is_not_unsafe_signed<int*&>();
    test_is_not_unsafe_signed<const int*&>();
    test_is_not_unsafe_signed<volatile int*&>();
    test_is_not_unsafe_signed<const volatile int*&>();
    test_is_not_unsafe_signed<int*&&>();
    test_is_not_unsafe_signed<const int*&&>();
    test_is_not_unsafe_signed<volatile int*&&>();
    test_is_not_unsafe_signed<const volatile int*&&>();
    test_is_not_unsafe_signed<void*>();
    test_is_not_unsafe_signed<char[3]>();
    test_is_not_unsafe_signed<char[]>();
    test_is_not_unsafe_signed<char* [3]>();
    test_is_not_unsafe_signed<char*[]>();
    test_is_not_unsafe_signed<int(*)[3]>();
    test_is_not_unsafe_signed<int(*)[]>();
    test_is_not_unsafe_signed<int(&)[3]>();
    test_is_not_unsafe_signed<int(&)[]>();
    test_is_not_unsafe_signed<int(&&)[3]>();
    test_is_not_unsafe_signed<int(&&)[]>();
    test_is_not_unsafe_signed<char[3][2]>();
    test_is_not_unsafe_signed<char[][2]>();
    test_is_not_unsafe_signed<char* [3][2]>();
    test_is_not_unsafe_signed<char*[][2]>();
    test_is_not_unsafe_signed<int(*)[3][2]>();
    test_is_not_unsafe_signed<int(*)[][2]>();
    test_is_not_unsafe_signed<int(&)[3][2]>();
    test_is_not_unsafe_signed<int(&)[][2]>();
    test_is_not_unsafe_signed<int(&&)[3][2]>();
    test_is_not_unsafe_signed<int(&&)[][2]>();
    test_is_not_unsafe_signed<Class>();
    test_is_not_unsafe_signed<Class[]>();
    test_is_not_unsafe_signed<Class[2]>();
    test_is_not_unsafe_signed<Template<void>>();
    test_is_not_unsafe_signed<Template<int>>();
    test_is_not_unsafe_signed<Template<Class>>();
    test_is_not_unsafe_signed<Template<IncompleteType>>();
    test_is_not_unsafe_signed<VariadicTemplate<>>();
    test_is_not_unsafe_signed<VariadicTemplate<void>>();
    test_is_not_unsafe_signed<VariadicTemplate<int>>();
    test_is_not_unsafe_signed<VariadicTemplate<Class>>();
    test_is_not_unsafe_signed<VariadicTemplate<IncompleteType>>();
    test_is_not_unsafe_signed<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_signed<PublicDerivedFromTemplate<Base>>();
    test_is_not_unsafe_signed<PublicDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_signed<PublicDerivedFromTemplate<Class>>();
    test_is_not_unsafe_signed<PrivateDerivedFromTemplate<Base>>();
    test_is_not_unsafe_signed<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_signed<PrivateDerivedFromTemplate<Class>>();
    test_is_not_unsafe_signed<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_unsafe_signed<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_signed<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_unsafe_signed<VirtualDerivedFromTemplate<Base>>();
    test_is_not_unsafe_signed<VirtualDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_signed<VirtualDerivedFromTemplate<Class>>();
    test_is_not_unsafe_signed<Union>();
    test_is_not_unsafe_signed<NonEmptyUnion>();
    test_is_not_unsafe_signed<NonTrivialUnion>();
    test_is_not_unsafe_signed<Empty>();
    test_is_not_unsafe_signed<NotEmpty>();
    test_is_not_unsafe_signed<NonTrivial>();
    test_is_not_unsafe_signed<BitZero>();
    test_is_not_unsafe_signed<BitOne>();
    test_is_not_unsafe_signed<Base>();
    test_is_not_unsafe_signed<Derived>();
    test_is_not_unsafe_signed<Polymorphic>();
    test_is_not_unsafe_signed<DerivedPolymorphic>();
    test_is_not_unsafe_signed<Abstract>();
    test_is_not_unsafe_signed<PublicAbstract>();
    test_is_not_unsafe_signed<PrivateAbstract>();
    test_is_not_unsafe_signed<ProtectedAbstract>();
    test_is_not_unsafe_signed<AbstractTemplate<int>>();
    test_is_not_unsafe_signed<AbstractTemplate<double>>();
    test_is_not_unsafe_signed<AbstractTemplate<Class>>();
    test_is_not_unsafe_signed<AbstractTemplate<IncompleteType>>();
    test_is_not_unsafe_signed<PublicAbstractDeletedDestructor>();
    test_is_not_unsafe_signed<ProtectedAbstractDeletedDestructor>();
    test_is_not_unsafe_signed<PrivateAbstractDeletedDestructor>();
    test_is_not_unsafe_signed<Final>();
    test_is_not_unsafe_signed<FinalDerived>();
    test_is_not_unsafe_signed<PublicDestructor>();
    test_is_not_unsafe_signed<ProtectedDestructor>();
    test_is_not_unsafe_signed<PrivateDestructor>();
    test_is_not_unsafe_signed<VirtualPublicDestructor>();
    test_is_not_unsafe_signed<VirtualProtectedDestructor>();
    test_is_not_unsafe_signed<VirtualPrivateDestructor>();
    test_is_not_unsafe_signed<PurePublicDestructor>();
    test_is_not_unsafe_signed<PureProtectedDestructor>();
    test_is_not_unsafe_signed<PurePrivateDestructor>();
    test_is_not_unsafe_signed<DeletedPublicDestructor>();
    test_is_not_unsafe_signed<DeletedProtectedDestructor>();
    test_is_not_unsafe_signed<DeletedPrivateDestructor>();
    test_is_not_unsafe_signed<DeletedVirtualPublicDestructor>();
    test_is_not_unsafe_signed<DeletedVirtualProtectedDestructor>();
    test_is_not_unsafe_signed<DeletedVirtualPrivateDestructor>();
    test_is_not_unsafe_signed<ExplicitClass>();
    test_is_not_unsafe_signed<NothrowExplicitClass>();
    test_is_not_unsafe_signed<ThrowExplicitClass>();
    test_is_not_unsafe_signed<ThrowDefaultClass>();
    test_is_not_unsafe_signed<ThrowCopyConsClass>();
    test_is_not_unsafe_signed<ThrowMoveConsClass>();
    test_is_not_unsafe_signed<NoexceptExplicitClass>();
    test_is_not_unsafe_signed<ExceptExplicitClass>();
    test_is_not_unsafe_signed<NoexceptDefaultClass>();
    test_is_not_unsafe_signed<ExceptDefaultClass>();
    test_is_not_unsafe_signed<NoexceptCopyConsClass>();
    test_is_not_unsafe_signed<ExceptCopyConsClass>();
    test_is_not_unsafe_signed<NoexceptMoveConsClass>();
    test_is_not_unsafe_signed<ExceptMoveConsClass>();
    test_is_not_unsafe_signed<NoexceptCopyAssignClass>();
    test_is_not_unsafe_signed<ExceptCopyAssignClass>();
    test_is_not_unsafe_signed<NoexceptMoveAssignClass>();
    test_is_not_unsafe_signed<ExceptMoveAssignClass>();
    test_is_not_unsafe_signed<DeletedCopyAssignClass>();
    test_is_not_unsafe_signed<DeletedMoveAssignClass>();
    test_is_not_unsafe_signed<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_unsafe_signed<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_unsafe_signed<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_not_unsafe_signed<ExceptMoveConsExceptMoveAssignClass>();
    test_is_not_unsafe_signed<ImplicitTo<int>>();
    test_is_not_unsafe_signed<ImplicitTo<float>>();
    test_is_not_unsafe_signed<ImplicitTo<Class>>();
    test_is_not_unsafe_signed<DeletedImplicitTo<int>>();
    test_is_not_unsafe_signed<DeletedImplicitTo<float>>();
    test_is_not_unsafe_signed<DeletedImplicitTo<Class>>();
    test_is_not_unsafe_signed<ExplicitTo<int>>();
    test_is_not_unsafe_signed<ExplicitTo<float>>();
    test_is_not_unsafe_signed<ExplicitTo<Class>>();
    test_is_not_unsafe_signed<DeletedExplicitTo<int>>();
    test_is_not_unsafe_signed<DeletedExplicitTo<float>>();
    test_is_not_unsafe_signed<DeletedExplicitTo<Class>>();
    test_is_not_unsafe_signed<Ellipsis>();
    test_is_not_unsafe_signed<DeletedEllipsis>();
    test_is_not_unsafe_signed<CopyConsOnlyType>();
    test_is_not_unsafe_signed<MoveConsOnlyType>();
    test_is_not_unsafe_signed<OverloadedOperators>();
    test_is_not_unsafe_signed<PublicIntMember>();
    test_is_not_unsafe_signed<ProtectedIntMember>();
    test_is_not_unsafe_signed<PrivateIntMember>();
    test_is_not_unsafe_signed<PublicStaticIntMember>();
    test_is_not_unsafe_signed<ProtectedStaticIntMember>();
    test_is_not_unsafe_signed<PrivateStaticIntMember>();
    test_is_not_unsafe_signed<PublicTemplateMember<int>>();
    test_is_not_unsafe_signed<PublicTemplateMember<float>>();
    test_is_not_unsafe_signed<PublicTemplateMember<Class>>();
    test_is_not_unsafe_signed<ProtectedTemplateMember<int>>();
    test_is_not_unsafe_signed<ProtectedTemplateMember<float>>();
    test_is_not_unsafe_signed<ProtectedTemplateMember<Class>>();
    test_is_not_unsafe_signed<PrivateTemplateMember<int>>();
    test_is_not_unsafe_signed<PrivateTemplateMember<float>>();
    test_is_not_unsafe_signed<PrivateTemplateMember<Class>>();
    test_is_not_unsafe_signed<PublicStaticTemplateMember<int>>();
    test_is_not_unsafe_signed<PublicStaticTemplateMember<float>>();
    test_is_not_unsafe_signed<PublicStaticTemplateMember<Class>>();
    test_is_not_unsafe_signed<ProtectedStaticTemplateMember<int>>();
    test_is_not_unsafe_signed<ProtectedStaticTemplateMember<float>>();
    test_is_not_unsafe_signed<ProtectedStaticTemplateMember<Class>>();
    test_is_not_unsafe_signed<PrivateStaticTemplateMember<int>>();
    test_is_not_unsafe_signed<PrivateStaticTemplateMember<float>>();
    test_is_not_unsafe_signed<PrivateStaticTemplateMember<Class>>();
    test_is_not_unsafe_signed<Enum>();
    test_is_not_unsafe_signed<EnumSigned>();
    test_is_not_unsafe_signed<EnumUnsigned>();
    test_is_not_unsafe_signed<EnumClass>();
    test_is_not_unsafe_signed<EnumStruct>();
    test_is_not_unsafe_signed<Function>();
    test_is_not_unsafe_signed<FunctionPtr>();
    test_is_not_unsafe_signed<MemberObjectPtr>();
    test_is_not_unsafe_signed<MemberFunctionPtr>();
    test_is_not_unsafe_signed<LambdaType>();
    test_is_not_unsafe_signed<LambdaNoexceptType>();
    test_is_not_unsafe_signed<LambdaThrowsType>();
    test_is_not_unsafe_signed<IncompleteType>();
    test_is_not_unsafe_signed<IncompleteTemplate<void>>();
    test_is_not_unsafe_signed<IncompleteTemplate<int>>();
    test_is_not_unsafe_signed<IncompleteTemplate<Class>>();
    test_is_not_unsafe_signed<IncompleteTemplate<IncompleteType>>();
    test_is_not_unsafe_signed<IncompleteVariadicTemplate<>>();
    test_is_not_unsafe_signed<IncompleteVariadicTemplate<void>>();
    test_is_not_unsafe_signed<IncompleteVariadicTemplate<int>>();
    test_is_not_unsafe_signed<IncompleteVariadicTemplate<Class>>();
    test_is_not_unsafe_signed<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_unsafe_signed<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_signed<IncompleteUnion>();
    test_is_not_unsafe_signed<IncompleteEnumSigned>();
    test_is_not_unsafe_signed<IncompleteEnumUnsigned>();
    test_is_not_unsafe_signed<IncompleteEnumClass>();
    test_is_not_unsafe_signed<IncompleteEnumStruct>();
    test_is_not_unsafe_signed<int Class::*>();
    test_is_not_unsafe_signed<float Class::*>();
    test_is_not_unsafe_signed<void * Class::*>();
    test_is_not_unsafe_signed<int * Class::*>();
    test_is_not_unsafe_signed<int Class::*&>();
    test_is_not_unsafe_signed<float Class::*&>();
    test_is_not_unsafe_signed<void * Class::*&>();
    test_is_not_unsafe_signed<int * Class::*&>();
    test_is_not_unsafe_signed<int Class::*&&>();
    test_is_not_unsafe_signed<float Class::*&&>();
    test_is_not_unsafe_signed<void * Class::*&&>();
    test_is_not_unsafe_signed<int * Class::*&&>();
    test_is_not_unsafe_signed<int Class::*const>();
    test_is_not_unsafe_signed<float Class::*const>();
    test_is_not_unsafe_signed<void * Class::*const>();
    test_is_not_unsafe_signed<int Class::*const&>();
    test_is_not_unsafe_signed<float Class::*const&>();
    test_is_not_unsafe_signed<void * Class::*const&>();
    test_is_not_unsafe_signed<int Class::*const&&>();
    test_is_not_unsafe_signed<float Class::*const&&>();
    test_is_not_unsafe_signed<void * Class::*const&&>();
    test_is_not_unsafe_signed<int Class::*volatile>();
    test_is_not_unsafe_signed<float Class::*volatile>();
    test_is_not_unsafe_signed<void * Class::*volatile>();
    test_is_not_unsafe_signed<int Class::*volatile&>();
    test_is_not_unsafe_signed<float Class::*volatile&>();
    test_is_not_unsafe_signed<void * Class::*volatile&>();
    test_is_not_unsafe_signed<int Class::*volatile&&>();
    test_is_not_unsafe_signed<float Class::*volatile&&>();
    test_is_not_unsafe_signed<void * Class::*volatile&&>();
    test_is_not_unsafe_signed<int Class::*const volatile>();
    test_is_not_unsafe_signed<float Class::*const volatile>();
    test_is_not_unsafe_signed<void * Class::*const volatile>();
    test_is_not_unsafe_signed<int Class::*const volatile&>();
    test_is_not_unsafe_signed<float Class::*const volatile&>();
    test_is_not_unsafe_signed<void * Class::*const volatile&>();
    test_is_not_unsafe_signed<int Class::*const volatile&&>();
    test_is_not_unsafe_signed<float Class::*const volatile&&>();
    test_is_not_unsafe_signed<void * Class::*const volatile&&>();
    test_is_not_unsafe_signed<NonCopyable>();
    test_is_not_unsafe_signed<NonMoveable>();
    test_is_not_unsafe_signed<NonConstructible>();
    test_is_not_unsafe_signed<NonDestructible>();
    test_is_not_unsafe_signed<Tracked>();
    test_is_not_unsafe_signed<TrapConstructible>();
    test_is_not_unsafe_signed<TrapImplicitConversion>();
    test_is_not_unsafe_signed<TrapComma>();
    test_is_not_unsafe_signed<TrapCall>();
    test_is_not_unsafe_signed<TrapSelfAssign>();
    test_is_not_unsafe_signed<TrapDeref>();
    test_is_not_unsafe_signed<TrapArraySubscript>();

    test_is_not_unsafe_signed<void()>();
    test_is_not_unsafe_signed<void()&>();
    test_is_not_unsafe_signed<void() &&>();
    test_is_not_unsafe_signed<void() const>();
    test_is_not_unsafe_signed<void() const&>();
    test_is_not_unsafe_signed<void() const&&>();
    test_is_not_unsafe_signed<void() volatile>();
    test_is_not_unsafe_signed<void() volatile&>();
    test_is_not_unsafe_signed<void() volatile&&>();
    test_is_not_unsafe_signed<void() const volatile>();
    test_is_not_unsafe_signed<void() const volatile&>();
    test_is_not_unsafe_signed<void() const volatile&&>();
    test_is_not_unsafe_signed<void() noexcept>();
    test_is_not_unsafe_signed<void()& noexcept>();
    test_is_not_unsafe_signed<void()&& noexcept>();
    test_is_not_unsafe_signed<void() const noexcept>();
    test_is_not_unsafe_signed<void() const& noexcept>();
    test_is_not_unsafe_signed<void() const&& noexcept>();
    test_is_not_unsafe_signed<void() volatile noexcept>();
    test_is_not_unsafe_signed<void() volatile& noexcept>();
    test_is_not_unsafe_signed<void() volatile&& noexcept>();
    test_is_not_unsafe_signed<void() const volatile noexcept>();
    test_is_not_unsafe_signed<void() const volatile& noexcept>();
    test_is_not_unsafe_signed<void() const volatile&& noexcept>();

    test_is_not_unsafe_signed<void(int)>();
    test_is_not_unsafe_signed<void(int)&>();
    test_is_not_unsafe_signed<void(int) &&>();
    test_is_not_unsafe_signed<void(int) const>();
    test_is_not_unsafe_signed<void(int) const&>();
    test_is_not_unsafe_signed<void(int) const&&>();
    test_is_not_unsafe_signed<void(int) volatile>();
    test_is_not_unsafe_signed<void(int) volatile&>();
    test_is_not_unsafe_signed<void(int) volatile&&>();
    test_is_not_unsafe_signed<void(int) const volatile>();
    test_is_not_unsafe_signed<void(int) const volatile&>();
    test_is_not_unsafe_signed<void(int) const volatile&&>();
    test_is_not_unsafe_signed<void(int) noexcept>();
    test_is_not_unsafe_signed<void(int)& noexcept>();
    test_is_not_unsafe_signed<void(int)&& noexcept>();
    test_is_not_unsafe_signed<void(int) const noexcept>();
    test_is_not_unsafe_signed<void(int) const& noexcept>();
    test_is_not_unsafe_signed<void(int) const&& noexcept>();
    test_is_not_unsafe_signed<void(int) volatile noexcept>();
    test_is_not_unsafe_signed<void(int) volatile& noexcept>();
    test_is_not_unsafe_signed<void(int) volatile&& noexcept>();
    test_is_not_unsafe_signed<void(int) const volatile noexcept>();
    test_is_not_unsafe_signed<void(int) const volatile& noexcept>();
    test_is_not_unsafe_signed<void(int) const volatile&& noexcept>();

    test_is_not_unsafe_signed<void(...)>();
    test_is_not_unsafe_signed<void(...)&>();
    test_is_not_unsafe_signed<void(...) &&>();
    test_is_not_unsafe_signed<void(...) const>();
    test_is_not_unsafe_signed<void(...) const&>();
    test_is_not_unsafe_signed<void(...) const&&>();
    test_is_not_unsafe_signed<void(...) volatile>();
    test_is_not_unsafe_signed<void(...) volatile&>();
    test_is_not_unsafe_signed<void(...) volatile&&>();
    test_is_not_unsafe_signed<void(...) const volatile>();
    test_is_not_unsafe_signed<void(...) const volatile&>();
    test_is_not_unsafe_signed<void(...) const volatile&&>();
    test_is_not_unsafe_signed<void(...) noexcept>();
    test_is_not_unsafe_signed<void(...)& noexcept>();
    test_is_not_unsafe_signed<void(...)&& noexcept>();
    test_is_not_unsafe_signed<void(...) const noexcept>();
    test_is_not_unsafe_signed<void(...) const& noexcept>();
    test_is_not_unsafe_signed<void(...) const&& noexcept>();
    test_is_not_unsafe_signed<void(...) volatile noexcept>();
    test_is_not_unsafe_signed<void(...) volatile& noexcept>();
    test_is_not_unsafe_signed<void(...) volatile&& noexcept>();
    test_is_not_unsafe_signed<void(...) const volatile noexcept>();
    test_is_not_unsafe_signed<void(...) const volatile& noexcept>();
    test_is_not_unsafe_signed<void(...) const volatile&& noexcept>();

    test_is_not_unsafe_signed<void(int, ...)>();
    test_is_not_unsafe_signed<void(int, ...)&>();
    test_is_not_unsafe_signed<void(int, ...) &&>();
    test_is_not_unsafe_signed<void(int, ...) const>();
    test_is_not_unsafe_signed<void(int, ...) const&>();
    test_is_not_unsafe_signed<void(int, ...) const&&>();
    test_is_not_unsafe_signed<void(int, ...) volatile>();
    test_is_not_unsafe_signed<void(int, ...) volatile&>();
    test_is_not_unsafe_signed<void(int, ...) volatile&&>();
    test_is_not_unsafe_signed<void(int, ...) const volatile>();
    test_is_not_unsafe_signed<void(int, ...) const volatile&>();
    test_is_not_unsafe_signed<void(int, ...) const volatile&&>();
    test_is_not_unsafe_signed<void(int, ...) noexcept>();
    test_is_not_unsafe_signed<void(int, ...)& noexcept>();
    test_is_not_unsafe_signed<void(int, ...)&& noexcept>();
    test_is_not_unsafe_signed<void(int, ...) const noexcept>();
    test_is_not_unsafe_signed<void(int, ...) const& noexcept>();
    test_is_not_unsafe_signed<void(int, ...) const&& noexcept>();
    test_is_not_unsafe_signed<void(int, ...) volatile noexcept>();
    test_is_not_unsafe_signed<void(int, ...) volatile& noexcept>();
    test_is_not_unsafe_signed<void(int, ...) volatile&& noexcept>();
    test_is_not_unsafe_signed<void(int, ...) const volatile noexcept>();
    test_is_not_unsafe_signed<void(int, ...) const volatile& noexcept>();
    test_is_not_unsafe_signed<void(int, ...) const volatile&& noexcept>();

    test_is_not_unsafe_signed<int()>();
    test_is_not_unsafe_signed<int()&>();
    test_is_not_unsafe_signed<int() &&>();
    test_is_not_unsafe_signed<int() const>();
    test_is_not_unsafe_signed<int() const&>();
    test_is_not_unsafe_signed<int() const&&>();
    test_is_not_unsafe_signed<int() volatile>();
    test_is_not_unsafe_signed<int() volatile&>();
    test_is_not_unsafe_signed<int() volatile&&>();
    test_is_not_unsafe_signed<int() const volatile>();
    test_is_not_unsafe_signed<int() const volatile&>();
    test_is_not_unsafe_signed<int() const volatile&&>();
    test_is_not_unsafe_signed<int() noexcept>();
    test_is_not_unsafe_signed<int()& noexcept>();
    test_is_not_unsafe_signed<int()&& noexcept>();
    test_is_not_unsafe_signed<int() const noexcept>();
    test_is_not_unsafe_signed<int() const& noexcept>();
    test_is_not_unsafe_signed<int() const&& noexcept>();
    test_is_not_unsafe_signed<int() volatile noexcept>();
    test_is_not_unsafe_signed<int() volatile& noexcept>();
    test_is_not_unsafe_signed<int() volatile&& noexcept>();
    test_is_not_unsafe_signed<int() const volatile noexcept>();
    test_is_not_unsafe_signed<int() const volatile& noexcept>();
    test_is_not_unsafe_signed<int() const volatile&& noexcept>();

    test_is_not_unsafe_signed<int(int)>();
    test_is_not_unsafe_signed<int(int)&>();
    test_is_not_unsafe_signed<int(int) &&>();
    test_is_not_unsafe_signed<int(int) const>();
    test_is_not_unsafe_signed<int(int) const&>();
    test_is_not_unsafe_signed<int(int) const&&>();
    test_is_not_unsafe_signed<int(int) volatile>();
    test_is_not_unsafe_signed<int(int) volatile&>();
    test_is_not_unsafe_signed<int(int) volatile&&>();
    test_is_not_unsafe_signed<int(int) const volatile>();
    test_is_not_unsafe_signed<int(int) const volatile&>();
    test_is_not_unsafe_signed<int(int) const volatile&&>();
    test_is_not_unsafe_signed<int(int) noexcept>();
    test_is_not_unsafe_signed<int(int)& noexcept>();
    test_is_not_unsafe_signed<int(int)&& noexcept>();
    test_is_not_unsafe_signed<int(int) const noexcept>();
    test_is_not_unsafe_signed<int(int) const& noexcept>();
    test_is_not_unsafe_signed<int(int) const&& noexcept>();
    test_is_not_unsafe_signed<int(int) volatile noexcept>();
    test_is_not_unsafe_signed<int(int) volatile& noexcept>();
    test_is_not_unsafe_signed<int(int) volatile&& noexcept>();
    test_is_not_unsafe_signed<int(int) const volatile noexcept>();
    test_is_not_unsafe_signed<int(int) const volatile& noexcept>();
    test_is_not_unsafe_signed<int(int) const volatile&& noexcept>();

    test_is_not_unsafe_signed<int(...)>();
    test_is_not_unsafe_signed<int(...)&>();
    test_is_not_unsafe_signed<int(...) &&>();
    test_is_not_unsafe_signed<int(...) const>();
    test_is_not_unsafe_signed<int(...) const&>();
    test_is_not_unsafe_signed<int(...) const&&>();
    test_is_not_unsafe_signed<int(...) volatile>();
    test_is_not_unsafe_signed<int(...) volatile&>();
    test_is_not_unsafe_signed<int(...) volatile&&>();
    test_is_not_unsafe_signed<int(...) const volatile>();
    test_is_not_unsafe_signed<int(...) const volatile&>();
    test_is_not_unsafe_signed<int(...) const volatile&&>();
    test_is_not_unsafe_signed<int(...) noexcept>();
    test_is_not_unsafe_signed<int(...)& noexcept>();
    test_is_not_unsafe_signed<int(...)&& noexcept>();
    test_is_not_unsafe_signed<int(...) const noexcept>();
    test_is_not_unsafe_signed<int(...) const& noexcept>();
    test_is_not_unsafe_signed<int(...) const&& noexcept>();
    test_is_not_unsafe_signed<int(...) volatile noexcept>();
    test_is_not_unsafe_signed<int(...) volatile& noexcept>();
    test_is_not_unsafe_signed<int(...) volatile&& noexcept>();
    test_is_not_unsafe_signed<int(...) const volatile noexcept>();
    test_is_not_unsafe_signed<int(...) const volatile& noexcept>();
    test_is_not_unsafe_signed<int(...) const volatile&& noexcept>();

    test_is_not_unsafe_signed<int(int, ...)>();
    test_is_not_unsafe_signed<int(int, ...)&>();
    test_is_not_unsafe_signed<int(int, ...) &&>();
    test_is_not_unsafe_signed<int(int, ...) const>();
    test_is_not_unsafe_signed<int(int, ...) const&>();
    test_is_not_unsafe_signed<int(int, ...) const&&>();
    test_is_not_unsafe_signed<int(int, ...) volatile>();
    test_is_not_unsafe_signed<int(int, ...) volatile&>();
    test_is_not_unsafe_signed<int(int, ...) volatile&&>();
    test_is_not_unsafe_signed<int(int, ...) const volatile>();
    test_is_not_unsafe_signed<int(int, ...) const volatile&>();
    test_is_not_unsafe_signed<int(int, ...) const volatile&&>();
    test_is_not_unsafe_signed<int(int, ...) noexcept>();
    test_is_not_unsafe_signed<int(int, ...)& noexcept>();
    test_is_not_unsafe_signed<int(int, ...)&& noexcept>();
    test_is_not_unsafe_signed<int(int, ...) const noexcept>();
    test_is_not_unsafe_signed<int(int, ...) const& noexcept>();
    test_is_not_unsafe_signed<int(int, ...) const&& noexcept>();
    test_is_not_unsafe_signed<int(int, ...) volatile noexcept>();
    test_is_not_unsafe_signed<int(int, ...) volatile& noexcept>();
    test_is_not_unsafe_signed<int(int, ...) volatile&& noexcept>();
    test_is_not_unsafe_signed<int(int, ...) const volatile noexcept>();
    test_is_not_unsafe_signed<int(int, ...) const volatile& noexcept>();
    test_is_not_unsafe_signed<int(int, ...) const volatile&& noexcept>();

    test_is_not_unsafe_signed<void (*)()>();
    test_is_not_unsafe_signed<void (*)() noexcept>();

    test_is_not_unsafe_signed<void (*)(int)>();
    test_is_not_unsafe_signed<void (*)(int) noexcept>();

    test_is_not_unsafe_signed<void (*)(...)>();
    test_is_not_unsafe_signed<void (*)(...) noexcept>();

    test_is_not_unsafe_signed<void (*)(int, ...)>();
    test_is_not_unsafe_signed<void (*)(int, ...) noexcept>();

    test_is_not_unsafe_signed<int (*)()>();
    test_is_not_unsafe_signed<int (*)() noexcept>();

    test_is_not_unsafe_signed<int (*)(int)>();
    test_is_not_unsafe_signed<int (*)(int) noexcept>();

    test_is_not_unsafe_signed<int (*)(...)>();
    test_is_not_unsafe_signed<int (*)(...) noexcept>();

    test_is_not_unsafe_signed<int (*)(int, ...)>();
    test_is_not_unsafe_signed<int (*)(int, ...) noexcept>();

    test_is_not_unsafe_signed<void (&)()>();
    test_is_not_unsafe_signed<void (&)() noexcept>();

    test_is_not_unsafe_signed<void (&)(int)>();
    test_is_not_unsafe_signed<void (&)(int) noexcept>();

    test_is_not_unsafe_signed<void (&)(...)>();
    test_is_not_unsafe_signed<void (&)(...) noexcept>();

    test_is_not_unsafe_signed<void (&)(int, ...)>();
    test_is_not_unsafe_signed<void (&)(int, ...) noexcept>();

    test_is_not_unsafe_signed<int (&)()>();
    test_is_not_unsafe_signed<int (&)() noexcept>();

    test_is_not_unsafe_signed<int (&)(int)>();
    test_is_not_unsafe_signed<int (&)(int) noexcept>();

    test_is_not_unsafe_signed<int (&)(...)>();
    test_is_not_unsafe_signed<int (&)(...) noexcept>();

    test_is_not_unsafe_signed<int (&)(int, ...)>();
    test_is_not_unsafe_signed<int (&)(int, ...) noexcept>();

    test_is_not_unsafe_signed<void(&&)()>();
    test_is_not_unsafe_signed<void(&&)() noexcept>();

    test_is_not_unsafe_signed<void(&&)(int)>();
    test_is_not_unsafe_signed<void(&&)(int) noexcept>();

    test_is_not_unsafe_signed<void(&&)(...)>();
    test_is_not_unsafe_signed<void(&&)(...) noexcept>();

    test_is_not_unsafe_signed<void(&&)(int, ...)>();
    test_is_not_unsafe_signed<void(&&)(int, ...) noexcept>();

    test_is_not_unsafe_signed<int(&&)()>();
    test_is_not_unsafe_signed<int(&&)() noexcept>();

    test_is_not_unsafe_signed<int(&&)(int)>();
    test_is_not_unsafe_signed<int(&&)(int) noexcept>();

    test_is_not_unsafe_signed<int(&&)(...)>();
    test_is_not_unsafe_signed<int(&&)(...) noexcept>();

    test_is_not_unsafe_signed<int(&&)(int, ...)>();
    test_is_not_unsafe_signed<int(&&)(int, ...) noexcept>();

    test_is_not_unsafe_signed<void (Class::*)()>();
    test_is_not_unsafe_signed<void (Class::*)()&>();
    test_is_not_unsafe_signed<void (Class::*)() &&>();
    test_is_not_unsafe_signed<void (Class::*)() const>();
    test_is_not_unsafe_signed<void (Class::*)() const&>();
    test_is_not_unsafe_signed<void (Class::*)() const&&>();
    test_is_not_unsafe_signed<void (Class::*)() noexcept>();
    test_is_not_unsafe_signed<void (Class::*)()& noexcept>();
    test_is_not_unsafe_signed<void (Class::*)()&& noexcept>();
    test_is_not_unsafe_signed<void (Class::*)() const noexcept>();
    test_is_not_unsafe_signed<void (Class::*)() const& noexcept>();
    test_is_not_unsafe_signed<void (Class::*)() const&& noexcept>();

    test_is_not_unsafe_signed<void (Class::*)(int)>();
    test_is_not_unsafe_signed<void (Class::*)(int)&>();
    test_is_not_unsafe_signed<void (Class::*)(int) &&>();
    test_is_not_unsafe_signed<void (Class::*)(int) const>();
    test_is_not_unsafe_signed<void (Class::*)(int) const&>();
    test_is_not_unsafe_signed<void (Class::*)(int) const&&>();
    test_is_not_unsafe_signed<void (Class::*)(int) noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(int)& noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(int) const noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_signed<void (Class::*)(...)>();
    test_is_not_unsafe_signed<void (Class::*)(...)&>();
    test_is_not_unsafe_signed<void (Class::*)(...) &&>();
    test_is_not_unsafe_signed<void (Class::*)(...) const>();
    test_is_not_unsafe_signed<void (Class::*)(...) const&>();
    test_is_not_unsafe_signed<void (Class::*)(...) const&&>();
    test_is_not_unsafe_signed<void (Class::*)(...) noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(...)& noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(...) const noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(...) const&& noexcept>();

    test_is_not_unsafe_signed<void (Class::*)(int, ...)>();
    test_is_not_unsafe_signed<void (Class::*)(int, ...)&>();
    test_is_not_unsafe_signed<void (Class::*)(int, ...) &&>();
    test_is_not_unsafe_signed<void (Class::*)(int, ...) const>();
    test_is_not_unsafe_signed<void (Class::*)(int, ...) const&>();
    test_is_not_unsafe_signed<void (Class::*)(int, ...) const&&>();
    test_is_not_unsafe_signed<void (Class::*)(int, ...) noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(int, ...)& noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(int, ...) const noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsafe_signed<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_unsafe_signed<int (Class::*)()>();
    test_is_not_unsafe_signed<int (Class::*)()&>();
    test_is_not_unsafe_signed<int (Class::*)() &&>();
    test_is_not_unsafe_signed<int (Class::*)() const>();
    test_is_not_unsafe_signed<int (Class::*)() const&>();
    test_is_not_unsafe_signed<int (Class::*)() const&&>();
    test_is_not_unsafe_signed<int (Class::*)() noexcept>();
    test_is_not_unsafe_signed<int (Class::*)()& noexcept>();
    test_is_not_unsafe_signed<int (Class::*)()&& noexcept>();
    test_is_not_unsafe_signed<int (Class::*)() const noexcept>();
    test_is_not_unsafe_signed<int (Class::*)() const& noexcept>();
    test_is_not_unsafe_signed<int (Class::*)() const&& noexcept>();

    test_is_not_unsafe_signed<int (Class::*)(int)>();
    test_is_not_unsafe_signed<int (Class::*)(int)&>();
    test_is_not_unsafe_signed<int (Class::*)(int) &&>();
    test_is_not_unsafe_signed<int (Class::*)(int) const>();
    test_is_not_unsafe_signed<int (Class::*)(int) const&>();
    test_is_not_unsafe_signed<int (Class::*)(int) const&&>();
    test_is_not_unsafe_signed<int (Class::*)(int) noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(int)& noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(int) const noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_signed<int (Class::*)(...)>();
    test_is_not_unsafe_signed<int (Class::*)(...)&>();
    test_is_not_unsafe_signed<int (Class::*)(...) &&>();
    test_is_not_unsafe_signed<int (Class::*)(...) const>();
    test_is_not_unsafe_signed<int (Class::*)(...) const&>();
    test_is_not_unsafe_signed<int (Class::*)(...) const&&>();
    test_is_not_unsafe_signed<int (Class::*)(...) noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(...)& noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(...) const noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(...) const&& noexcept>();

    test_is_not_unsafe_signed<int (Class::*)(int, ...)>();
    test_is_not_unsafe_signed<int (Class::*)(int, ...)&>();
    test_is_not_unsafe_signed<int (Class::*)(int, ...) &&>();
    test_is_not_unsafe_signed<int (Class::*)(int, ...) const>();
    test_is_not_unsafe_signed<int (Class::*)(int, ...) const&>();
    test_is_not_unsafe_signed<int (Class::*)(int, ...) const&&>();
    test_is_not_unsafe_signed<int (Class::*)(int, ...) noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(int, ...)& noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(int, ...) const noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsafe_signed<int (Class::*)(int, ...) const&& noexcept>();
}
