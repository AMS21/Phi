#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unsafe_unsigned.hpp>
#include <vector>

template <typename T>
void test_is_unsafe_unsigned_impl()
{
    STATIC_REQUIRE(phi::is_unsafe_unsigned<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_unsigned<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_unsigned_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_unsigned_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_unsigned<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_unsigned<T>);
}

template <typename T>
void test_is_not_unsafe_unsigned_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_unsigned<T>::value);
    STATIC_REQUIRE(phi::is_not_unsafe_unsigned<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_unsigned_v<T>);
    STATIC_REQUIRE(phi::is_not_unsafe_unsigned_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_unsigned<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_unsigned<T>);
}

template <typename T>
void test_is_unsafe_unsigned()
{
    test_is_unsafe_unsigned_impl<T>();
    test_is_unsafe_unsigned_impl<const T>();
    test_is_unsafe_unsigned_impl<volatile T>();
    test_is_unsafe_unsigned_impl<const volatile T>();
}

template <typename T>
void test_is_not_unsafe_unsigned()
{
    test_is_not_unsafe_unsigned_impl<T>();
    test_is_not_unsafe_unsigned_impl<const T>();
    test_is_not_unsafe_unsigned_impl<volatile T>();
    test_is_not_unsafe_unsigned_impl<const volatile T>();
}

TEST_CASE("is_unsafe_unsigned")
{
    test_is_not_unsafe_unsigned<void>();
    test_is_not_unsafe_unsigned<phi::nullptr_t>();
    test_is_unsafe_unsigned<bool>();
    //test_is_not_unsafe_unsigned<char>();
    test_is_not_unsafe_unsigned<signed char>();
    test_is_unsafe_unsigned<unsigned char>();
    test_is_not_unsafe_unsigned<short>();
    test_is_unsafe_unsigned<unsigned short>();
    test_is_not_unsafe_unsigned<int>();
    test_is_unsafe_unsigned<unsigned int>();
    test_is_not_unsafe_unsigned<long>();
    test_is_unsafe_unsigned<unsigned long>();
    test_is_not_unsafe_unsigned<long long>();
    test_is_unsafe_unsigned<unsigned long long>();
    test_is_not_unsafe_unsigned<float>();
    test_is_not_unsafe_unsigned<double>();
    test_is_not_unsafe_unsigned<long double>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_is_unsafe_unsigned<char8_t>();
#endif
    test_is_unsafe_unsigned<char16_t>();
    test_is_unsafe_unsigned<char32_t>();
#if PHI_PLATFORM_IS(WINDOWS)
    test_is_unsafe_unsigned<wchar_t>();
#else
    test_is_not_unsafe_unsigned<wchar_t>();
#endif

    test_is_not_unsafe_unsigned<phi::boolean>();
    test_is_not_unsafe_unsigned<phi::integer<signed char>>();
    test_is_not_unsafe_unsigned<phi::integer<unsigned char>>();
    test_is_not_unsafe_unsigned<phi::integer<short>>();
    test_is_not_unsafe_unsigned<phi::integer<unsigned short>>();
    test_is_not_unsafe_unsigned<phi::integer<int>>();
    test_is_not_unsafe_unsigned<phi::integer<unsigned int>>();
    test_is_not_unsafe_unsigned<phi::integer<long>>();
    test_is_not_unsafe_unsigned<phi::integer<unsigned long>>();
    test_is_not_unsafe_unsigned<phi::integer<long long>>();
    test_is_not_unsafe_unsigned<phi::integer<unsigned long long>>();
    test_is_not_unsafe_unsigned<phi::floating_point<float>>();
    test_is_not_unsafe_unsigned<phi::floating_point<double>>();
    test_is_not_unsafe_unsigned<phi::floating_point<long double>>();

    test_is_not_unsafe_unsigned<std::vector<int>>();
    test_is_not_unsafe_unsigned<phi::scope_ptr<int>>();

    test_is_not_unsafe_unsigned<int&>();
    test_is_not_unsafe_unsigned<const int&>();
    test_is_not_unsafe_unsigned<volatile int&>();
    test_is_not_unsafe_unsigned<const volatile int&>();
    test_is_not_unsafe_unsigned<int&&>();
    test_is_not_unsafe_unsigned<const int&&>();
    test_is_not_unsafe_unsigned<volatile int&&>();
    test_is_not_unsafe_unsigned<const volatile int&&>();
    test_is_not_unsafe_unsigned<int*>();
    test_is_not_unsafe_unsigned<const int*>();
    test_is_not_unsafe_unsigned<volatile int*>();
    test_is_not_unsafe_unsigned<const volatile int*>();
    test_is_not_unsafe_unsigned<int**>();
    test_is_not_unsafe_unsigned<const int**>();
    test_is_not_unsafe_unsigned<volatile int**>();
    test_is_not_unsafe_unsigned<const volatile int**>();
    test_is_not_unsafe_unsigned<int*&>();
    test_is_not_unsafe_unsigned<const int*&>();
    test_is_not_unsafe_unsigned<volatile int*&>();
    test_is_not_unsafe_unsigned<const volatile int*&>();
    test_is_not_unsafe_unsigned<int*&&>();
    test_is_not_unsafe_unsigned<const int*&&>();
    test_is_not_unsafe_unsigned<volatile int*&&>();
    test_is_not_unsafe_unsigned<const volatile int*&&>();
    test_is_not_unsafe_unsigned<void*>();
    test_is_not_unsafe_unsigned<char[3]>();
    test_is_not_unsafe_unsigned<char[]>();
    test_is_not_unsafe_unsigned<char* [3]>();
    test_is_not_unsafe_unsigned<char*[]>();
    test_is_not_unsafe_unsigned<int(*)[3]>();
    test_is_not_unsafe_unsigned<int(*)[]>();
    test_is_not_unsafe_unsigned<int(&)[3]>();
    test_is_not_unsafe_unsigned<int(&)[]>();
    test_is_not_unsafe_unsigned<int(&&)[3]>();
    test_is_not_unsafe_unsigned<int(&&)[]>();
    test_is_not_unsafe_unsigned<char[3][2]>();
    test_is_not_unsafe_unsigned<char[][2]>();
    test_is_not_unsafe_unsigned<char* [3][2]>();
    test_is_not_unsafe_unsigned<char*[][2]>();
    test_is_not_unsafe_unsigned<int(*)[3][2]>();
    test_is_not_unsafe_unsigned<int(*)[][2]>();
    test_is_not_unsafe_unsigned<int(&)[3][2]>();
    test_is_not_unsafe_unsigned<int(&)[][2]>();
    test_is_not_unsafe_unsigned<int(&&)[3][2]>();
    test_is_not_unsafe_unsigned<int(&&)[][2]>();
    test_is_not_unsafe_unsigned<Class>();
    test_is_not_unsafe_unsigned<Class[]>();
    test_is_not_unsafe_unsigned<Class[2]>();
    test_is_not_unsafe_unsigned<Template<void>>();
    test_is_not_unsafe_unsigned<Template<int>>();
    test_is_not_unsafe_unsigned<Template<Class>>();
    test_is_not_unsafe_unsigned<Template<IncompleteType>>();
    test_is_not_unsafe_unsigned<VariadicTemplate<>>();
    test_is_not_unsafe_unsigned<VariadicTemplate<void>>();
    test_is_not_unsafe_unsigned<VariadicTemplate<int>>();
    test_is_not_unsafe_unsigned<VariadicTemplate<Class>>();
    test_is_not_unsafe_unsigned<VariadicTemplate<IncompleteType>>();
    test_is_not_unsafe_unsigned<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_unsigned<PublicDerivedFromTemplate<Base>>();
    test_is_not_unsafe_unsigned<PublicDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_unsigned<PublicDerivedFromTemplate<Class>>();
    test_is_not_unsafe_unsigned<PrivateDerivedFromTemplate<Base>>();
    test_is_not_unsafe_unsigned<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_unsigned<PrivateDerivedFromTemplate<Class>>();
    test_is_not_unsafe_unsigned<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_unsafe_unsigned<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_unsigned<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_unsafe_unsigned<VirtualDerivedFromTemplate<Base>>();
    test_is_not_unsafe_unsigned<VirtualDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_unsigned<VirtualDerivedFromTemplate<Class>>();
    test_is_not_unsafe_unsigned<Union>();
    test_is_not_unsafe_unsigned<NonEmptyUnion>();
    test_is_not_unsafe_unsigned<NonTrivialUnion>();
    test_is_not_unsafe_unsigned<Empty>();
    test_is_not_unsafe_unsigned<NotEmpty>();
    test_is_not_unsafe_unsigned<NonTrivial>();
    test_is_not_unsafe_unsigned<BitZero>();
    test_is_not_unsafe_unsigned<BitOne>();
    test_is_not_unsafe_unsigned<Base>();
    test_is_not_unsafe_unsigned<Derived>();
    test_is_not_unsafe_unsigned<Polymorphic>();
    test_is_not_unsafe_unsigned<DerivedPolymorphic>();
    test_is_not_unsafe_unsigned<Abstract>();
    test_is_not_unsafe_unsigned<PublicAbstract>();
    test_is_not_unsafe_unsigned<PrivateAbstract>();
    test_is_not_unsafe_unsigned<ProtectedAbstract>();
    test_is_not_unsafe_unsigned<AbstractTemplate<int>>();
    test_is_not_unsafe_unsigned<AbstractTemplate<double>>();
    test_is_not_unsafe_unsigned<AbstractTemplate<Class>>();
    test_is_not_unsafe_unsigned<AbstractTemplate<IncompleteType>>();
    test_is_not_unsafe_unsigned<PublicAbstractDeletedDestructor>();
    test_is_not_unsafe_unsigned<ProtectedAbstractDeletedDestructor>();
    test_is_not_unsafe_unsigned<PrivateAbstractDeletedDestructor>();
    test_is_not_unsafe_unsigned<Final>();
    test_is_not_unsafe_unsigned<FinalDerived>();
    test_is_not_unsafe_unsigned<PublicDestructor>();
    test_is_not_unsafe_unsigned<ProtectedDestructor>();
    test_is_not_unsafe_unsigned<PrivateDestructor>();
    test_is_not_unsafe_unsigned<VirtualPublicDestructor>();
    test_is_not_unsafe_unsigned<VirtualProtectedDestructor>();
    test_is_not_unsafe_unsigned<VirtualPrivateDestructor>();
    test_is_not_unsafe_unsigned<PurePublicDestructor>();
    test_is_not_unsafe_unsigned<PureProtectedDestructor>();
    test_is_not_unsafe_unsigned<PurePrivateDestructor>();
    test_is_not_unsafe_unsigned<DeletedPublicDestructor>();
    test_is_not_unsafe_unsigned<DeletedProtectedDestructor>();
    test_is_not_unsafe_unsigned<DeletedPrivateDestructor>();
    test_is_not_unsafe_unsigned<DeletedVirtualPublicDestructor>();
    test_is_not_unsafe_unsigned<DeletedVirtualProtectedDestructor>();
    test_is_not_unsafe_unsigned<DeletedVirtualPrivateDestructor>();
    test_is_not_unsafe_unsigned<ExplicitClass>();
    test_is_not_unsafe_unsigned<NothrowExplicitClass>();
    test_is_not_unsafe_unsigned<ThrowExplicitClass>();
    test_is_not_unsafe_unsigned<ThrowDefaultClass>();
    test_is_not_unsafe_unsigned<ThrowCopyConsClass>();
    test_is_not_unsafe_unsigned<ThrowMoveConsClass>();
    test_is_not_unsafe_unsigned<NoexceptExplicitClass>();
    test_is_not_unsafe_unsigned<ExceptExplicitClass>();
    test_is_not_unsafe_unsigned<NoexceptDefaultClass>();
    test_is_not_unsafe_unsigned<ExceptDefaultClass>();
    test_is_not_unsafe_unsigned<NoexceptCopyConsClass>();
    test_is_not_unsafe_unsigned<ExceptCopyConsClass>();
    test_is_not_unsafe_unsigned<NoexceptMoveConsClass>();
    test_is_not_unsafe_unsigned<ExceptMoveConsClass>();
    test_is_not_unsafe_unsigned<NoexceptCopyAssignClass>();
    test_is_not_unsafe_unsigned<ExceptCopyAssignClass>();
    test_is_not_unsafe_unsigned<NoexceptMoveAssignClass>();
    test_is_not_unsafe_unsigned<ExceptMoveAssignClass>();
    test_is_not_unsafe_unsigned<DeletedCopyAssignClass>();
    test_is_not_unsafe_unsigned<DeletedMoveAssignClass>();
    test_is_not_unsafe_unsigned<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_unsafe_unsigned<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_unsafe_unsigned<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_not_unsafe_unsigned<ExceptMoveConsExceptMoveAssignClass>();
    test_is_not_unsafe_unsigned<ImplicitTo<int>>();
    test_is_not_unsafe_unsigned<ImplicitTo<float>>();
    test_is_not_unsafe_unsigned<ImplicitTo<Class>>();
    test_is_not_unsafe_unsigned<DeletedImplicitTo<int>>();
    test_is_not_unsafe_unsigned<DeletedImplicitTo<float>>();
    test_is_not_unsafe_unsigned<DeletedImplicitTo<Class>>();
    test_is_not_unsafe_unsigned<ExplicitTo<int>>();
    test_is_not_unsafe_unsigned<ExplicitTo<float>>();
    test_is_not_unsafe_unsigned<ExplicitTo<Class>>();
    test_is_not_unsafe_unsigned<DeletedExplicitTo<int>>();
    test_is_not_unsafe_unsigned<DeletedExplicitTo<float>>();
    test_is_not_unsafe_unsigned<DeletedExplicitTo<Class>>();
    test_is_not_unsafe_unsigned<Ellipsis>();
    test_is_not_unsafe_unsigned<DeletedEllipsis>();
    test_is_not_unsafe_unsigned<CopyConsOnlyType>();
    test_is_not_unsafe_unsigned<MoveConsOnlyType>();
    test_is_not_unsafe_unsigned<OverloadedOperators>();
    test_is_not_unsafe_unsigned<PublicIntMember>();
    test_is_not_unsafe_unsigned<ProtectedIntMember>();
    test_is_not_unsafe_unsigned<PrivateIntMember>();
    test_is_not_unsafe_unsigned<PublicStaticIntMember>();
    test_is_not_unsafe_unsigned<ProtectedStaticIntMember>();
    test_is_not_unsafe_unsigned<PrivateStaticIntMember>();
    test_is_not_unsafe_unsigned<PublicTemplateMember<int>>();
    test_is_not_unsafe_unsigned<PublicTemplateMember<float>>();
    test_is_not_unsafe_unsigned<PublicTemplateMember<Class>>();
    test_is_not_unsafe_unsigned<ProtectedTemplateMember<int>>();
    test_is_not_unsafe_unsigned<ProtectedTemplateMember<float>>();
    test_is_not_unsafe_unsigned<ProtectedTemplateMember<Class>>();
    test_is_not_unsafe_unsigned<PrivateTemplateMember<int>>();
    test_is_not_unsafe_unsigned<PrivateTemplateMember<float>>();
    test_is_not_unsafe_unsigned<PrivateTemplateMember<Class>>();
    test_is_not_unsafe_unsigned<PublicStaticTemplateMember<int>>();
    test_is_not_unsafe_unsigned<PublicStaticTemplateMember<float>>();
    test_is_not_unsafe_unsigned<PublicStaticTemplateMember<Class>>();
    test_is_not_unsafe_unsigned<ProtectedStaticTemplateMember<int>>();
    test_is_not_unsafe_unsigned<ProtectedStaticTemplateMember<float>>();
    test_is_not_unsafe_unsigned<ProtectedStaticTemplateMember<Class>>();
    test_is_not_unsafe_unsigned<PrivateStaticTemplateMember<int>>();
    test_is_not_unsafe_unsigned<PrivateStaticTemplateMember<float>>();
    test_is_not_unsafe_unsigned<PrivateStaticTemplateMember<Class>>();
    test_is_not_unsafe_unsigned<Enum>();
    test_is_not_unsafe_unsigned<EnumSigned>();
    test_is_not_unsafe_unsigned<EnumUnsigned>();
    test_is_not_unsafe_unsigned<EnumClass>();
    test_is_not_unsafe_unsigned<EnumStruct>();
    test_is_not_unsafe_unsigned<Function>();
    test_is_not_unsafe_unsigned<FunctionPtr>();
    test_is_not_unsafe_unsigned<MemberObjectPtr>();
    test_is_not_unsafe_unsigned<MemberFunctionPtr>();
    test_is_not_unsafe_unsigned<LambdaType>();
    test_is_not_unsafe_unsigned<LambdaNoexceptType>();
    test_is_not_unsafe_unsigned<LambdaThrowsType>();
    test_is_not_unsafe_unsigned<IncompleteType>();
    test_is_not_unsafe_unsigned<IncompleteTemplate<void>>();
    test_is_not_unsafe_unsigned<IncompleteTemplate<int>>();
    test_is_not_unsafe_unsigned<IncompleteTemplate<Class>>();
    test_is_not_unsafe_unsigned<IncompleteTemplate<IncompleteType>>();
    test_is_not_unsafe_unsigned<IncompleteVariadicTemplate<>>();
    test_is_not_unsafe_unsigned<IncompleteVariadicTemplate<void>>();
    test_is_not_unsafe_unsigned<IncompleteVariadicTemplate<int>>();
    test_is_not_unsafe_unsigned<IncompleteVariadicTemplate<Class>>();
    test_is_not_unsafe_unsigned<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_unsafe_unsigned<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_unsigned<IncompleteUnion>();
    test_is_not_unsafe_unsigned<IncompleteEnumSigned>();
    test_is_not_unsafe_unsigned<IncompleteEnumUnsigned>();
    test_is_not_unsafe_unsigned<IncompleteEnumClass>();
    test_is_not_unsafe_unsigned<IncompleteEnumStruct>();
    test_is_not_unsafe_unsigned<int Class::*>();
    test_is_not_unsafe_unsigned<float Class::*>();
    test_is_not_unsafe_unsigned<void * Class::*>();
    test_is_not_unsafe_unsigned<int * Class::*>();
    test_is_not_unsafe_unsigned<int Class::*&>();
    test_is_not_unsafe_unsigned<float Class::*&>();
    test_is_not_unsafe_unsigned<void * Class::*&>();
    test_is_not_unsafe_unsigned<int * Class::*&>();
    test_is_not_unsafe_unsigned<int Class::*&&>();
    test_is_not_unsafe_unsigned<float Class::*&&>();
    test_is_not_unsafe_unsigned<void * Class::*&&>();
    test_is_not_unsafe_unsigned<int * Class::*&&>();
    test_is_not_unsafe_unsigned<int Class::*const>();
    test_is_not_unsafe_unsigned<float Class::*const>();
    test_is_not_unsafe_unsigned<void * Class::*const>();
    test_is_not_unsafe_unsigned<int Class::*const&>();
    test_is_not_unsafe_unsigned<float Class::*const&>();
    test_is_not_unsafe_unsigned<void * Class::*const&>();
    test_is_not_unsafe_unsigned<int Class::*const&&>();
    test_is_not_unsafe_unsigned<float Class::*const&&>();
    test_is_not_unsafe_unsigned<void * Class::*const&&>();
    test_is_not_unsafe_unsigned<int Class::*volatile>();
    test_is_not_unsafe_unsigned<float Class::*volatile>();
    test_is_not_unsafe_unsigned<void * Class::*volatile>();
    test_is_not_unsafe_unsigned<int Class::*volatile&>();
    test_is_not_unsafe_unsigned<float Class::*volatile&>();
    test_is_not_unsafe_unsigned<void * Class::*volatile&>();
    test_is_not_unsafe_unsigned<int Class::*volatile&&>();
    test_is_not_unsafe_unsigned<float Class::*volatile&&>();
    test_is_not_unsafe_unsigned<void * Class::*volatile&&>();
    test_is_not_unsafe_unsigned<int Class::*const volatile>();
    test_is_not_unsafe_unsigned<float Class::*const volatile>();
    test_is_not_unsafe_unsigned<void * Class::*const volatile>();
    test_is_not_unsafe_unsigned<int Class::*const volatile&>();
    test_is_not_unsafe_unsigned<float Class::*const volatile&>();
    test_is_not_unsafe_unsigned<void * Class::*const volatile&>();
    test_is_not_unsafe_unsigned<int Class::*const volatile&&>();
    test_is_not_unsafe_unsigned<float Class::*const volatile&&>();
    test_is_not_unsafe_unsigned<void * Class::*const volatile&&>();
    test_is_not_unsafe_unsigned<NonCopyable>();
    test_is_not_unsafe_unsigned<NonMoveable>();
    test_is_not_unsafe_unsigned<NonConstructible>();
    test_is_not_unsafe_unsigned<NonDestructible>();
    test_is_not_unsafe_unsigned<Tracked>();
    test_is_not_unsafe_unsigned<TrapConstructible>();
    test_is_not_unsafe_unsigned<TrapImplicitConversion>();
    test_is_not_unsafe_unsigned<TrapComma>();
    test_is_not_unsafe_unsigned<TrapCall>();
    test_is_not_unsafe_unsigned<TrapSelfAssign>();
    test_is_not_unsafe_unsigned<TrapDeref>();
    test_is_not_unsafe_unsigned<TrapArraySubscript>();

    test_is_not_unsafe_unsigned<void()>();
    test_is_not_unsafe_unsigned<void()&>();
    test_is_not_unsafe_unsigned<void() &&>();
    test_is_not_unsafe_unsigned<void() const>();
    test_is_not_unsafe_unsigned<void() const&>();
    test_is_not_unsafe_unsigned<void() const&&>();
    test_is_not_unsafe_unsigned<void() volatile>();
    test_is_not_unsafe_unsigned<void() volatile&>();
    test_is_not_unsafe_unsigned<void() volatile&&>();
    test_is_not_unsafe_unsigned<void() const volatile>();
    test_is_not_unsafe_unsigned<void() const volatile&>();
    test_is_not_unsafe_unsigned<void() const volatile&&>();
    test_is_not_unsafe_unsigned<void() noexcept>();
    test_is_not_unsafe_unsigned<void()& noexcept>();
    test_is_not_unsafe_unsigned<void()&& noexcept>();
    test_is_not_unsafe_unsigned<void() const noexcept>();
    test_is_not_unsafe_unsigned<void() const& noexcept>();
    test_is_not_unsafe_unsigned<void() const&& noexcept>();
    test_is_not_unsafe_unsigned<void() volatile noexcept>();
    test_is_not_unsafe_unsigned<void() volatile& noexcept>();
    test_is_not_unsafe_unsigned<void() volatile&& noexcept>();
    test_is_not_unsafe_unsigned<void() const volatile noexcept>();
    test_is_not_unsafe_unsigned<void() const volatile& noexcept>();
    test_is_not_unsafe_unsigned<void() const volatile&& noexcept>();

    test_is_not_unsafe_unsigned<void(int)>();
    test_is_not_unsafe_unsigned<void(int)&>();
    test_is_not_unsafe_unsigned<void(int) &&>();
    test_is_not_unsafe_unsigned<void(int) const>();
    test_is_not_unsafe_unsigned<void(int) const&>();
    test_is_not_unsafe_unsigned<void(int) const&&>();
    test_is_not_unsafe_unsigned<void(int) volatile>();
    test_is_not_unsafe_unsigned<void(int) volatile&>();
    test_is_not_unsafe_unsigned<void(int) volatile&&>();
    test_is_not_unsafe_unsigned<void(int) const volatile>();
    test_is_not_unsafe_unsigned<void(int) const volatile&>();
    test_is_not_unsafe_unsigned<void(int) const volatile&&>();
    test_is_not_unsafe_unsigned<void(int) noexcept>();
    test_is_not_unsafe_unsigned<void(int)& noexcept>();
    test_is_not_unsafe_unsigned<void(int)&& noexcept>();
    test_is_not_unsafe_unsigned<void(int) const noexcept>();
    test_is_not_unsafe_unsigned<void(int) const& noexcept>();
    test_is_not_unsafe_unsigned<void(int) const&& noexcept>();
    test_is_not_unsafe_unsigned<void(int) volatile noexcept>();
    test_is_not_unsafe_unsigned<void(int) volatile& noexcept>();
    test_is_not_unsafe_unsigned<void(int) volatile&& noexcept>();
    test_is_not_unsafe_unsigned<void(int) const volatile noexcept>();
    test_is_not_unsafe_unsigned<void(int) const volatile& noexcept>();
    test_is_not_unsafe_unsigned<void(int) const volatile&& noexcept>();

    test_is_not_unsafe_unsigned<void(...)>();
    test_is_not_unsafe_unsigned<void(...)&>();
    test_is_not_unsafe_unsigned<void(...) &&>();
    test_is_not_unsafe_unsigned<void(...) const>();
    test_is_not_unsafe_unsigned<void(...) const&>();
    test_is_not_unsafe_unsigned<void(...) const&&>();
    test_is_not_unsafe_unsigned<void(...) volatile>();
    test_is_not_unsafe_unsigned<void(...) volatile&>();
    test_is_not_unsafe_unsigned<void(...) volatile&&>();
    test_is_not_unsafe_unsigned<void(...) const volatile>();
    test_is_not_unsafe_unsigned<void(...) const volatile&>();
    test_is_not_unsafe_unsigned<void(...) const volatile&&>();
    test_is_not_unsafe_unsigned<void(...) noexcept>();
    test_is_not_unsafe_unsigned<void(...)& noexcept>();
    test_is_not_unsafe_unsigned<void(...)&& noexcept>();
    test_is_not_unsafe_unsigned<void(...) const noexcept>();
    test_is_not_unsafe_unsigned<void(...) const& noexcept>();
    test_is_not_unsafe_unsigned<void(...) const&& noexcept>();
    test_is_not_unsafe_unsigned<void(...) volatile noexcept>();
    test_is_not_unsafe_unsigned<void(...) volatile& noexcept>();
    test_is_not_unsafe_unsigned<void(...) volatile&& noexcept>();
    test_is_not_unsafe_unsigned<void(...) const volatile noexcept>();
    test_is_not_unsafe_unsigned<void(...) const volatile& noexcept>();
    test_is_not_unsafe_unsigned<void(...) const volatile&& noexcept>();

    test_is_not_unsafe_unsigned<void(int, ...)>();
    test_is_not_unsafe_unsigned<void(int, ...)&>();
    test_is_not_unsafe_unsigned<void(int, ...) &&>();
    test_is_not_unsafe_unsigned<void(int, ...) const>();
    test_is_not_unsafe_unsigned<void(int, ...) const&>();
    test_is_not_unsafe_unsigned<void(int, ...) const&&>();
    test_is_not_unsafe_unsigned<void(int, ...) volatile>();
    test_is_not_unsafe_unsigned<void(int, ...) volatile&>();
    test_is_not_unsafe_unsigned<void(int, ...) volatile&&>();
    test_is_not_unsafe_unsigned<void(int, ...) const volatile>();
    test_is_not_unsafe_unsigned<void(int, ...) const volatile&>();
    test_is_not_unsafe_unsigned<void(int, ...) const volatile&&>();
    test_is_not_unsafe_unsigned<void(int, ...) noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...)& noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...)&& noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) const noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) const& noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) const&& noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) volatile noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) volatile& noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) volatile&& noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) const volatile noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) const volatile& noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) const volatile&& noexcept>();

    test_is_not_unsafe_unsigned<int()>();
    test_is_not_unsafe_unsigned<int()&>();
    test_is_not_unsafe_unsigned<int() &&>();
    test_is_not_unsafe_unsigned<int() const>();
    test_is_not_unsafe_unsigned<int() const&>();
    test_is_not_unsafe_unsigned<int() const&&>();
    test_is_not_unsafe_unsigned<int() volatile>();
    test_is_not_unsafe_unsigned<int() volatile&>();
    test_is_not_unsafe_unsigned<int() volatile&&>();
    test_is_not_unsafe_unsigned<int() const volatile>();
    test_is_not_unsafe_unsigned<int() const volatile&>();
    test_is_not_unsafe_unsigned<int() const volatile&&>();
    test_is_not_unsafe_unsigned<int() noexcept>();
    test_is_not_unsafe_unsigned<int()& noexcept>();
    test_is_not_unsafe_unsigned<int()&& noexcept>();
    test_is_not_unsafe_unsigned<int() const noexcept>();
    test_is_not_unsafe_unsigned<int() const& noexcept>();
    test_is_not_unsafe_unsigned<int() const&& noexcept>();
    test_is_not_unsafe_unsigned<int() volatile noexcept>();
    test_is_not_unsafe_unsigned<int() volatile& noexcept>();
    test_is_not_unsafe_unsigned<int() volatile&& noexcept>();
    test_is_not_unsafe_unsigned<int() const volatile noexcept>();
    test_is_not_unsafe_unsigned<int() const volatile& noexcept>();
    test_is_not_unsafe_unsigned<int() const volatile&& noexcept>();

    test_is_not_unsafe_unsigned<int(int)>();
    test_is_not_unsafe_unsigned<int(int)&>();
    test_is_not_unsafe_unsigned<int(int) &&>();
    test_is_not_unsafe_unsigned<int(int) const>();
    test_is_not_unsafe_unsigned<int(int) const&>();
    test_is_not_unsafe_unsigned<int(int) const&&>();
    test_is_not_unsafe_unsigned<int(int) volatile>();
    test_is_not_unsafe_unsigned<int(int) volatile&>();
    test_is_not_unsafe_unsigned<int(int) volatile&&>();
    test_is_not_unsafe_unsigned<int(int) const volatile>();
    test_is_not_unsafe_unsigned<int(int) const volatile&>();
    test_is_not_unsafe_unsigned<int(int) const volatile&&>();
    test_is_not_unsafe_unsigned<int(int) noexcept>();
    test_is_not_unsafe_unsigned<int(int)& noexcept>();
    test_is_not_unsafe_unsigned<int(int)&& noexcept>();
    test_is_not_unsafe_unsigned<int(int) const noexcept>();
    test_is_not_unsafe_unsigned<int(int) const& noexcept>();
    test_is_not_unsafe_unsigned<int(int) const&& noexcept>();
    test_is_not_unsafe_unsigned<int(int) volatile noexcept>();
    test_is_not_unsafe_unsigned<int(int) volatile& noexcept>();
    test_is_not_unsafe_unsigned<int(int) volatile&& noexcept>();
    test_is_not_unsafe_unsigned<int(int) const volatile noexcept>();
    test_is_not_unsafe_unsigned<int(int) const volatile& noexcept>();
    test_is_not_unsafe_unsigned<int(int) const volatile&& noexcept>();

    test_is_not_unsafe_unsigned<int(...)>();
    test_is_not_unsafe_unsigned<int(...)&>();
    test_is_not_unsafe_unsigned<int(...) &&>();
    test_is_not_unsafe_unsigned<int(...) const>();
    test_is_not_unsafe_unsigned<int(...) const&>();
    test_is_not_unsafe_unsigned<int(...) const&&>();
    test_is_not_unsafe_unsigned<int(...) volatile>();
    test_is_not_unsafe_unsigned<int(...) volatile&>();
    test_is_not_unsafe_unsigned<int(...) volatile&&>();
    test_is_not_unsafe_unsigned<int(...) const volatile>();
    test_is_not_unsafe_unsigned<int(...) const volatile&>();
    test_is_not_unsafe_unsigned<int(...) const volatile&&>();
    test_is_not_unsafe_unsigned<int(...) noexcept>();
    test_is_not_unsafe_unsigned<int(...)& noexcept>();
    test_is_not_unsafe_unsigned<int(...)&& noexcept>();
    test_is_not_unsafe_unsigned<int(...) const noexcept>();
    test_is_not_unsafe_unsigned<int(...) const& noexcept>();
    test_is_not_unsafe_unsigned<int(...) const&& noexcept>();
    test_is_not_unsafe_unsigned<int(...) volatile noexcept>();
    test_is_not_unsafe_unsigned<int(...) volatile& noexcept>();
    test_is_not_unsafe_unsigned<int(...) volatile&& noexcept>();
    test_is_not_unsafe_unsigned<int(...) const volatile noexcept>();
    test_is_not_unsafe_unsigned<int(...) const volatile& noexcept>();
    test_is_not_unsafe_unsigned<int(...) const volatile&& noexcept>();

    test_is_not_unsafe_unsigned<int(int, ...)>();
    test_is_not_unsafe_unsigned<int(int, ...)&>();
    test_is_not_unsafe_unsigned<int(int, ...) &&>();
    test_is_not_unsafe_unsigned<int(int, ...) const>();
    test_is_not_unsafe_unsigned<int(int, ...) const&>();
    test_is_not_unsafe_unsigned<int(int, ...) const&&>();
    test_is_not_unsafe_unsigned<int(int, ...) volatile>();
    test_is_not_unsafe_unsigned<int(int, ...) volatile&>();
    test_is_not_unsafe_unsigned<int(int, ...) volatile&&>();
    test_is_not_unsafe_unsigned<int(int, ...) const volatile>();
    test_is_not_unsafe_unsigned<int(int, ...) const volatile&>();
    test_is_not_unsafe_unsigned<int(int, ...) const volatile&&>();
    test_is_not_unsafe_unsigned<int(int, ...) noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...)& noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...)&& noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) const noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) const& noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) const&& noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) volatile noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) volatile& noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) volatile&& noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) const volatile noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) const volatile& noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) const volatile&& noexcept>();

    test_is_not_unsafe_unsigned<void (*)()>();
    test_is_not_unsafe_unsigned<void (*)() noexcept>();

    test_is_not_unsafe_unsigned<void (*)(int)>();
    test_is_not_unsafe_unsigned<void (*)(int) noexcept>();

    test_is_not_unsafe_unsigned<void (*)(...)>();
    test_is_not_unsafe_unsigned<void (*)(...) noexcept>();

    test_is_not_unsafe_unsigned<void (*)(int, ...)>();
    test_is_not_unsafe_unsigned<void (*)(int, ...) noexcept>();

    test_is_not_unsafe_unsigned<int (*)()>();
    test_is_not_unsafe_unsigned<int (*)() noexcept>();

    test_is_not_unsafe_unsigned<int (*)(int)>();
    test_is_not_unsafe_unsigned<int (*)(int) noexcept>();

    test_is_not_unsafe_unsigned<int (*)(...)>();
    test_is_not_unsafe_unsigned<int (*)(...) noexcept>();

    test_is_not_unsafe_unsigned<int (*)(int, ...)>();
    test_is_not_unsafe_unsigned<int (*)(int, ...) noexcept>();

    test_is_not_unsafe_unsigned<void (&)()>();
    test_is_not_unsafe_unsigned<void (&)() noexcept>();

    test_is_not_unsafe_unsigned<void (&)(int)>();
    test_is_not_unsafe_unsigned<void (&)(int) noexcept>();

    test_is_not_unsafe_unsigned<void (&)(...)>();
    test_is_not_unsafe_unsigned<void (&)(...) noexcept>();

    test_is_not_unsafe_unsigned<void (&)(int, ...)>();
    test_is_not_unsafe_unsigned<void (&)(int, ...) noexcept>();

    test_is_not_unsafe_unsigned<int (&)()>();
    test_is_not_unsafe_unsigned<int (&)() noexcept>();

    test_is_not_unsafe_unsigned<int (&)(int)>();
    test_is_not_unsafe_unsigned<int (&)(int) noexcept>();

    test_is_not_unsafe_unsigned<int (&)(...)>();
    test_is_not_unsafe_unsigned<int (&)(...) noexcept>();

    test_is_not_unsafe_unsigned<int (&)(int, ...)>();
    test_is_not_unsafe_unsigned<int (&)(int, ...) noexcept>();

    test_is_not_unsafe_unsigned<void(&&)()>();
    test_is_not_unsafe_unsigned<void(&&)() noexcept>();

    test_is_not_unsafe_unsigned<void(&&)(int)>();
    test_is_not_unsafe_unsigned<void(&&)(int) noexcept>();

    test_is_not_unsafe_unsigned<void(&&)(...)>();
    test_is_not_unsafe_unsigned<void(&&)(...) noexcept>();

    test_is_not_unsafe_unsigned<void(&&)(int, ...)>();
    test_is_not_unsafe_unsigned<void(&&)(int, ...) noexcept>();

    test_is_not_unsafe_unsigned<int(&&)()>();
    test_is_not_unsafe_unsigned<int(&&)() noexcept>();

    test_is_not_unsafe_unsigned<int(&&)(int)>();
    test_is_not_unsafe_unsigned<int(&&)(int) noexcept>();

    test_is_not_unsafe_unsigned<int(&&)(...)>();
    test_is_not_unsafe_unsigned<int(&&)(...) noexcept>();

    test_is_not_unsafe_unsigned<int(&&)(int, ...)>();
    test_is_not_unsafe_unsigned<int(&&)(int, ...) noexcept>();

    test_is_not_unsafe_unsigned<void (Class::*)()>();
    test_is_not_unsafe_unsigned<void (Class::*)()&>();
    test_is_not_unsafe_unsigned<void (Class::*)() &&>();
    test_is_not_unsafe_unsigned<void (Class::*)() const>();
    test_is_not_unsafe_unsigned<void (Class::*)() const&>();
    test_is_not_unsafe_unsigned<void (Class::*)() const&&>();
    test_is_not_unsafe_unsigned<void (Class::*)() noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)()& noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)()&& noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)() const noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)() const& noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)() const&& noexcept>();

    test_is_not_unsafe_unsigned<void (Class::*)(int)>();
    test_is_not_unsafe_unsigned<void (Class::*)(int)&>();
    test_is_not_unsafe_unsigned<void (Class::*)(int) &&>();
    test_is_not_unsafe_unsigned<void (Class::*)(int) const>();
    test_is_not_unsafe_unsigned<void (Class::*)(int) const&>();
    test_is_not_unsafe_unsigned<void (Class::*)(int) const&&>();
    test_is_not_unsafe_unsigned<void (Class::*)(int) noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(int)& noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(int) const noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_unsigned<void (Class::*)(...)>();
    test_is_not_unsafe_unsigned<void (Class::*)(...)&>();
    test_is_not_unsafe_unsigned<void (Class::*)(...) &&>();
    test_is_not_unsafe_unsigned<void (Class::*)(...) const>();
    test_is_not_unsafe_unsigned<void (Class::*)(...) const&>();
    test_is_not_unsafe_unsigned<void (Class::*)(...) const&&>();
    test_is_not_unsafe_unsigned<void (Class::*)(...) noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(...)& noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(...) const noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(...) const&& noexcept>();

    test_is_not_unsafe_unsigned<void (Class::*)(int, ...)>();
    test_is_not_unsafe_unsigned<void (Class::*)(int, ...)&>();
    test_is_not_unsafe_unsigned<void (Class::*)(int, ...) &&>();
    test_is_not_unsafe_unsigned<void (Class::*)(int, ...) const>();
    test_is_not_unsafe_unsigned<void (Class::*)(int, ...) const&>();
    test_is_not_unsafe_unsigned<void (Class::*)(int, ...) const&&>();
    test_is_not_unsafe_unsigned<void (Class::*)(int, ...) noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(int, ...)& noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(int, ...) const noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsafe_unsigned<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_unsafe_unsigned<int (Class::*)()>();
    test_is_not_unsafe_unsigned<int (Class::*)()&>();
    test_is_not_unsafe_unsigned<int (Class::*)() &&>();
    test_is_not_unsafe_unsigned<int (Class::*)() const>();
    test_is_not_unsafe_unsigned<int (Class::*)() const&>();
    test_is_not_unsafe_unsigned<int (Class::*)() const&&>();
    test_is_not_unsafe_unsigned<int (Class::*)() noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)()& noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)()&& noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)() const noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)() const& noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)() const&& noexcept>();

    test_is_not_unsafe_unsigned<int (Class::*)(int)>();
    test_is_not_unsafe_unsigned<int (Class::*)(int)&>();
    test_is_not_unsafe_unsigned<int (Class::*)(int) &&>();
    test_is_not_unsafe_unsigned<int (Class::*)(int) const>();
    test_is_not_unsafe_unsigned<int (Class::*)(int) const&>();
    test_is_not_unsafe_unsigned<int (Class::*)(int) const&&>();
    test_is_not_unsafe_unsigned<int (Class::*)(int) noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(int)& noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(int) const noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_unsigned<int (Class::*)(...)>();
    test_is_not_unsafe_unsigned<int (Class::*)(...)&>();
    test_is_not_unsafe_unsigned<int (Class::*)(...) &&>();
    test_is_not_unsafe_unsigned<int (Class::*)(...) const>();
    test_is_not_unsafe_unsigned<int (Class::*)(...) const&>();
    test_is_not_unsafe_unsigned<int (Class::*)(...) const&&>();
    test_is_not_unsafe_unsigned<int (Class::*)(...) noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(...)& noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(...) const noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(...) const&& noexcept>();

    test_is_not_unsafe_unsigned<int (Class::*)(int, ...)>();
    test_is_not_unsafe_unsigned<int (Class::*)(int, ...)&>();
    test_is_not_unsafe_unsigned<int (Class::*)(int, ...) &&>();
    test_is_not_unsafe_unsigned<int (Class::*)(int, ...) const>();
    test_is_not_unsafe_unsigned<int (Class::*)(int, ...) const&>();
    test_is_not_unsafe_unsigned<int (Class::*)(int, ...) const&&>();
    test_is_not_unsafe_unsigned<int (Class::*)(int, ...) noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(int, ...)& noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(int, ...) const noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsafe_unsigned<int (Class::*)(int, ...) const&& noexcept>();
}
