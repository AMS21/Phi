#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_safe_scalar.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_safe_scalar_impl()
{
#if PHI_HAS_WORKING_IS_SAFE_SCALAR()
    STATIC_REQUIRE(phi::is_safe_scalar<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_scalar<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_scalar_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_scalar_v<T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_safe_scalar<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_safe_scalar<T>);
#endif
}

template <typename T>
void test_is_not_safe_scalar_impl()
{
#if PHI_HAS_WORKING_IS_SAFE_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_safe_scalar<T>::value);
    STATIC_REQUIRE(phi::is_not_safe_scalar<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_scalar_v<T>);
    STATIC_REQUIRE(phi::is_not_safe_scalar_v<T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_safe_scalar<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_safe_scalar<T>);
#endif
}

template <typename T>
void test_is_safe_scalar()
{
    test_is_safe_scalar_impl<T>();
    test_is_safe_scalar_impl<const T>();
    test_is_safe_scalar_impl<volatile T>();
    test_is_safe_scalar_impl<const volatile T>();
}

template <typename T>
void test_is_not_safe_scalar()
{
    test_is_not_safe_scalar_impl<T>();
    test_is_not_safe_scalar_impl<const T>();
    test_is_not_safe_scalar_impl<volatile T>();
    test_is_not_safe_scalar_impl<const volatile T>();
}

TEST_CASE("is_safe_scalar")
{
    test_is_not_safe_scalar<void>();
    test_is_safe_scalar<phi::nullptr_t>();
    test_is_not_safe_scalar<bool>();
    test_is_not_safe_scalar<char>();
    test_is_not_safe_scalar<signed char>();
    test_is_not_safe_scalar<unsigned char>();
    test_is_not_safe_scalar<short>();
    test_is_not_safe_scalar<unsigned short>();
    test_is_not_safe_scalar<int>();
    test_is_not_safe_scalar<unsigned int>();
    test_is_not_safe_scalar<long>();
    test_is_not_safe_scalar<unsigned long>();
    test_is_not_safe_scalar<long long>();
    test_is_not_safe_scalar<unsigned long long>();
    test_is_not_safe_scalar<float>();
    test_is_not_safe_scalar<double>();
    test_is_not_safe_scalar<long double>();
    test_is_not_safe_scalar<char8_t>();
    test_is_not_safe_scalar<char16_t>();
    test_is_not_safe_scalar<char32_t>();
    test_is_not_safe_scalar<wchar_t>();

    test_is_safe_scalar<phi::boolean>();
    test_is_safe_scalar<phi::integer<signed char>>();
    test_is_safe_scalar<phi::integer<unsigned char>>();
    test_is_safe_scalar<phi::integer<short>>();
    test_is_safe_scalar<phi::integer<unsigned short>>();
    test_is_safe_scalar<phi::integer<int>>();
    test_is_safe_scalar<phi::integer<unsigned int>>();
    test_is_safe_scalar<phi::integer<long>>();
    test_is_safe_scalar<phi::integer<unsigned long>>();
    test_is_safe_scalar<phi::integer<long long>>();
    test_is_safe_scalar<phi::integer<unsigned long long>>();
    test_is_safe_scalar<phi::floating_point<float>>();
    test_is_safe_scalar<phi::floating_point<double>>();
    test_is_safe_scalar<phi::floating_point<long double>>();

    test_is_not_safe_scalar<std::vector<int>>();
    test_is_not_safe_scalar<phi::scope_ptr<int>>();

    test_is_not_safe_scalar<int&>();
    test_is_not_safe_scalar<const int&>();
    test_is_not_safe_scalar<volatile int&>();
    test_is_not_safe_scalar<const volatile int&>();
    test_is_not_safe_scalar<int&&>();
    test_is_not_safe_scalar<const int&&>();
    test_is_not_safe_scalar<volatile int&&>();
    test_is_not_safe_scalar<const volatile int&&>();
    test_is_safe_scalar<int*>();
    test_is_safe_scalar<const int*>();
    test_is_safe_scalar<volatile int*>();
    test_is_safe_scalar<const volatile int*>();
    test_is_safe_scalar<int**>();
    test_is_safe_scalar<const int**>();
    test_is_safe_scalar<volatile int**>();
    test_is_safe_scalar<const volatile int**>();
    test_is_not_safe_scalar<int*&>();
    test_is_not_safe_scalar<const int*&>();
    test_is_not_safe_scalar<volatile int*&>();
    test_is_not_safe_scalar<const volatile int*&>();
    test_is_not_safe_scalar<int*&&>();
    test_is_not_safe_scalar<const int*&&>();
    test_is_not_safe_scalar<volatile int*&&>();
    test_is_not_safe_scalar<const volatile int*&&>();
    test_is_safe_scalar<void*>();
    test_is_not_safe_scalar<char[3]>();
    test_is_not_safe_scalar<char[]>();
    test_is_not_safe_scalar<char* [3]>();
    test_is_not_safe_scalar<char*[]>();
    test_is_safe_scalar<int(*)[3]>();
    test_is_safe_scalar<int(*)[]>();
    test_is_not_safe_scalar<int(&)[3]>();
    test_is_not_safe_scalar<int(&)[]>();
    test_is_not_safe_scalar<int(&&)[3]>();
    test_is_not_safe_scalar<int(&&)[]>();
    test_is_not_safe_scalar<char[3][2]>();
    test_is_not_safe_scalar<char[][2]>();
    test_is_not_safe_scalar<char* [3][2]>();
    test_is_not_safe_scalar<char*[][2]>();
    test_is_safe_scalar<int(*)[3][2]>();
    test_is_safe_scalar<int(*)[][2]>();
    test_is_not_safe_scalar<int(&)[3][2]>();
    test_is_not_safe_scalar<int(&)[][2]>();
    test_is_not_safe_scalar<int(&&)[3][2]>();
    test_is_not_safe_scalar<int(&&)[][2]>();
    test_is_not_safe_scalar<Class>();
    test_is_not_safe_scalar<Class[]>();
    test_is_not_safe_scalar<Class[2]>();
    test_is_not_safe_scalar<Template<void>>();
    test_is_not_safe_scalar<Template<int>>();
    test_is_not_safe_scalar<Template<Class>>();
    test_is_not_safe_scalar<Template<IncompleteType>>();
    test_is_not_safe_scalar<VariadicTemplate<>>();
    test_is_not_safe_scalar<VariadicTemplate<void>>();
    test_is_not_safe_scalar<VariadicTemplate<int>>();
    test_is_not_safe_scalar<VariadicTemplate<Class>>();
    test_is_not_safe_scalar<VariadicTemplate<IncompleteType>>();
    test_is_not_safe_scalar<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_scalar<PublicDerivedFromTemplate<Base>>();
    test_is_not_safe_scalar<PublicDerivedFromTemplate<Derived>>();
    test_is_not_safe_scalar<PublicDerivedFromTemplate<Class>>();
    test_is_not_safe_scalar<PrivateDerivedFromTemplate<Base>>();
    test_is_not_safe_scalar<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_safe_scalar<PrivateDerivedFromTemplate<Class>>();
    test_is_not_safe_scalar<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_safe_scalar<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_safe_scalar<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_safe_scalar<VirtualDerivedFromTemplate<Base>>();
    test_is_not_safe_scalar<VirtualDerivedFromTemplate<Derived>>();
    test_is_not_safe_scalar<VirtualDerivedFromTemplate<Class>>();
    test_is_not_safe_scalar<Union>();
    test_is_not_safe_scalar<NonEmptyUnion>();
    test_is_not_safe_scalar<NonTrivialUnion>();
    test_is_not_safe_scalar<Empty>();
    test_is_not_safe_scalar<NotEmpty>();
    test_is_not_safe_scalar<NonTrivial>();
    test_is_not_safe_scalar<BitZero>();
    test_is_not_safe_scalar<BitOne>();
    test_is_not_safe_scalar<Base>();
    test_is_not_safe_scalar<Derived>();
    test_is_not_safe_scalar<Polymorphic>();
    test_is_not_safe_scalar<DerivedPolymorphic>();
    test_is_not_safe_scalar<Abstract>();
    test_is_not_safe_scalar<PublicAbstract>();
    test_is_not_safe_scalar<PrivateAbstract>();
    test_is_not_safe_scalar<ProtectedAbstract>();
    test_is_not_safe_scalar<AbstractTemplate<int>>();
    test_is_not_safe_scalar<AbstractTemplate<double>>();
    test_is_not_safe_scalar<AbstractTemplate<Class>>();
    test_is_not_safe_scalar<AbstractTemplate<IncompleteType>>();
    test_is_not_safe_scalar<PublicAbstractDeletedDestructor>();
    test_is_not_safe_scalar<ProtectedAbstractDeletedDestructor>();
    test_is_not_safe_scalar<PrivateAbstractDeletedDestructor>();
    test_is_not_safe_scalar<Final>();
    test_is_not_safe_scalar<FinalDerived>();
    test_is_not_safe_scalar<PublicDestructor>();
    test_is_not_safe_scalar<ProtectedDestructor>();
    test_is_not_safe_scalar<PrivateDestructor>();
    test_is_not_safe_scalar<VirtualPublicDestructor>();
    test_is_not_safe_scalar<VirtualProtectedDestructor>();
    test_is_not_safe_scalar<VirtualPrivateDestructor>();
    test_is_not_safe_scalar<PurePublicDestructor>();
    test_is_not_safe_scalar<PureProtectedDestructor>();
    test_is_not_safe_scalar<PurePrivateDestructor>();
    test_is_not_safe_scalar<DeletedPublicDestructor>();
    test_is_not_safe_scalar<DeletedProtectedDestructor>();
    test_is_not_safe_scalar<DeletedPrivateDestructor>();
    test_is_not_safe_scalar<DeletedVirtualPublicDestructor>();
    test_is_not_safe_scalar<DeletedVirtualProtectedDestructor>();
    test_is_not_safe_scalar<DeletedVirtualPrivateDestructor>();
    test_is_not_safe_scalar<ExplicitClass>();
    test_is_not_safe_scalar<NothrowExplicitClass>();
    test_is_not_safe_scalar<ThrowExplicitClass>();
    test_is_not_safe_scalar<ThrowDefaultClass>();
    test_is_not_safe_scalar<ThrowCopyConsClass>();
    test_is_not_safe_scalar<ThrowMoveConsClass>();
    test_is_not_safe_scalar<NoexceptExplicitClass>();
    test_is_not_safe_scalar<ExceptExplicitClass>();
    test_is_not_safe_scalar<NoexceptDefaultClass>();
    test_is_not_safe_scalar<ExceptDefaultClass>();
    test_is_not_safe_scalar<NoexceptCopyConsClass>();
    test_is_not_safe_scalar<ExceptCopyConsClass>();
    test_is_not_safe_scalar<NoexceptMoveConsClass>();
    test_is_not_safe_scalar<ExceptMoveConsClass>();
    test_is_not_safe_scalar<NoexceptCopyAssignClass>();
    test_is_not_safe_scalar<ExceptCopyAssignClass>();
    test_is_not_safe_scalar<NoexceptMoveAssignClass>();
    test_is_not_safe_scalar<ExceptMoveAssignClass>();
    test_is_not_safe_scalar<DeletedCopyAssignClass>();
    test_is_not_safe_scalar<DeletedMoveAssignClass>();
    test_is_not_safe_scalar<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_safe_scalar<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_safe_scalar<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_not_safe_scalar<ExceptMoveConsExceptMoveAssignClass>();
    test_is_not_safe_scalar<ImplicitTo<int>>();
    test_is_not_safe_scalar<ImplicitTo<float>>();
    test_is_not_safe_scalar<ImplicitTo<Class>>();
    test_is_not_safe_scalar<DeletedImplicitTo<int>>();
    test_is_not_safe_scalar<DeletedImplicitTo<float>>();
    test_is_not_safe_scalar<DeletedImplicitTo<Class>>();
    test_is_not_safe_scalar<ExplicitTo<int>>();
    test_is_not_safe_scalar<ExplicitTo<float>>();
    test_is_not_safe_scalar<ExplicitTo<Class>>();
    test_is_not_safe_scalar<DeletedExplicitTo<int>>();
    test_is_not_safe_scalar<DeletedExplicitTo<float>>();
    test_is_not_safe_scalar<DeletedExplicitTo<Class>>();
    test_is_not_safe_scalar<Ellipsis>();
    test_is_not_safe_scalar<DeletedEllipsis>();
    test_is_not_safe_scalar<CopyConsOnlyType>();
    test_is_not_safe_scalar<MoveConsOnlyType>();
    test_is_not_safe_scalar<OverloadedOperators>();
    test_is_not_safe_scalar<PublicIntMember>();
    test_is_not_safe_scalar<ProtectedIntMember>();
    test_is_not_safe_scalar<PrivateIntMember>();
    test_is_not_safe_scalar<PublicStaticIntMember>();
    test_is_not_safe_scalar<ProtectedStaticIntMember>();
    test_is_not_safe_scalar<PrivateStaticIntMember>();
    test_is_not_safe_scalar<PublicTemplateMember<int>>();
    test_is_not_safe_scalar<PublicTemplateMember<float>>();
    test_is_not_safe_scalar<PublicTemplateMember<Class>>();
    test_is_not_safe_scalar<ProtectedTemplateMember<int>>();
    test_is_not_safe_scalar<ProtectedTemplateMember<float>>();
    test_is_not_safe_scalar<ProtectedTemplateMember<Class>>();
    test_is_not_safe_scalar<PrivateTemplateMember<int>>();
    test_is_not_safe_scalar<PrivateTemplateMember<float>>();
    test_is_not_safe_scalar<PrivateTemplateMember<Class>>();
    test_is_not_safe_scalar<PublicStaticTemplateMember<int>>();
    test_is_not_safe_scalar<PublicStaticTemplateMember<float>>();
    test_is_not_safe_scalar<PublicStaticTemplateMember<Class>>();
    test_is_not_safe_scalar<ProtectedStaticTemplateMember<int>>();
    test_is_not_safe_scalar<ProtectedStaticTemplateMember<float>>();
    test_is_not_safe_scalar<ProtectedStaticTemplateMember<Class>>();
    test_is_not_safe_scalar<PrivateStaticTemplateMember<int>>();
    test_is_not_safe_scalar<PrivateStaticTemplateMember<float>>();
    test_is_not_safe_scalar<PrivateStaticTemplateMember<Class>>();
    test_is_safe_scalar<Enum>();
    test_is_safe_scalar<EnumSigned>();
    test_is_safe_scalar<EnumUnsigned>();
    test_is_safe_scalar<EnumClass>();
    test_is_safe_scalar<EnumStruct>();
    test_is_not_safe_scalar<Function>();
    test_is_safe_scalar<FunctionPtr>();
    test_is_safe_scalar<MemberObjectPtr>();
    test_is_safe_scalar<MemberFunctionPtr>();
    test_is_not_safe_scalar<LambdaType>();
    test_is_not_safe_scalar<LambdaNoexceptType>();
    test_is_not_safe_scalar<LambdaThrowsType>();
    test_is_not_safe_scalar<IncompleteType>();
    test_is_not_safe_scalar<IncompleteTemplate<void>>();
    test_is_not_safe_scalar<IncompleteTemplate<int>>();
    test_is_not_safe_scalar<IncompleteTemplate<Class>>();
    test_is_not_safe_scalar<IncompleteTemplate<IncompleteType>>();
    test_is_not_safe_scalar<IncompleteVariadicTemplate<>>();
    test_is_not_safe_scalar<IncompleteVariadicTemplate<void>>();
    test_is_not_safe_scalar<IncompleteVariadicTemplate<int>>();
    test_is_not_safe_scalar<IncompleteVariadicTemplate<Class>>();
    test_is_not_safe_scalar<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_safe_scalar<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_scalar<IncompleteUnion>();
    test_is_safe_scalar<IncompleteEnumSigned>();
    test_is_safe_scalar<IncompleteEnumUnsigned>();
    test_is_safe_scalar<IncompleteEnumClass>();
    test_is_safe_scalar<IncompleteEnumStruct>();
    test_is_safe_scalar<int Class::*>();
    test_is_safe_scalar<float Class::*>();
    test_is_safe_scalar<void * Class::*>();
    test_is_safe_scalar<int * Class::*>();
    test_is_not_safe_scalar<int Class::*&>();
    test_is_not_safe_scalar<float Class::*&>();
    test_is_not_safe_scalar<void * Class::*&>();
    test_is_not_safe_scalar<int * Class::*&>();
    test_is_not_safe_scalar<int Class::*&&>();
    test_is_not_safe_scalar<float Class::*&&>();
    test_is_not_safe_scalar<void * Class::*&&>();
    test_is_not_safe_scalar<int * Class::*&&>();
    test_is_safe_scalar<int Class::*const>();
    test_is_safe_scalar<float Class::*const>();
    test_is_safe_scalar<void * Class::*const>();
    test_is_not_safe_scalar<int Class::*const&>();
    test_is_not_safe_scalar<float Class::*const&>();
    test_is_not_safe_scalar<void * Class::*const&>();
    test_is_not_safe_scalar<int Class::*const&&>();
    test_is_not_safe_scalar<float Class::*const&&>();
    test_is_not_safe_scalar<void * Class::*const&&>();
    test_is_safe_scalar<int Class::*volatile>();
    test_is_safe_scalar<float Class::*volatile>();
    test_is_safe_scalar<void * Class::*volatile>();
    test_is_not_safe_scalar<int Class::*volatile&>();
    test_is_not_safe_scalar<float Class::*volatile&>();
    test_is_not_safe_scalar<void * Class::*volatile&>();
    test_is_not_safe_scalar<int Class::*volatile&&>();
    test_is_not_safe_scalar<float Class::*volatile&&>();
    test_is_not_safe_scalar<void * Class::*volatile&&>();
    test_is_safe_scalar<int Class::*const volatile>();
    test_is_safe_scalar<float Class::*const volatile>();
    test_is_safe_scalar<void * Class::*const volatile>();
    test_is_not_safe_scalar<int Class::*const volatile&>();
    test_is_not_safe_scalar<float Class::*const volatile&>();
    test_is_not_safe_scalar<void * Class::*const volatile&>();
    test_is_not_safe_scalar<int Class::*const volatile&&>();
    test_is_not_safe_scalar<float Class::*const volatile&&>();
    test_is_not_safe_scalar<void * Class::*const volatile&&>();
    test_is_not_safe_scalar<NonCopyable>();
    test_is_not_safe_scalar<NonMoveable>();
    test_is_not_safe_scalar<NonConstructible>();
    test_is_not_safe_scalar<NonDestructible>();
    test_is_not_safe_scalar<Tracked>();
    test_is_not_safe_scalar<TrapConstructible>();
    test_is_not_safe_scalar<TrapImplicitConversion>();
    test_is_not_safe_scalar<TrapComma>();
    test_is_not_safe_scalar<TrapCall>();
    test_is_not_safe_scalar<TrapSelfAssign>();
    test_is_not_safe_scalar<TrapDeref>();
    test_is_not_safe_scalar<TrapArraySubscript>();

    test_is_not_safe_scalar<void()>();
    test_is_not_safe_scalar<void()&>();
    test_is_not_safe_scalar<void() &&>();
    test_is_not_safe_scalar<void() const>();
    test_is_not_safe_scalar<void() const&>();
    test_is_not_safe_scalar<void() const&&>();
    test_is_not_safe_scalar<void() volatile>();
    test_is_not_safe_scalar<void() volatile&>();
    test_is_not_safe_scalar<void() volatile&&>();
    test_is_not_safe_scalar<void() const volatile>();
    test_is_not_safe_scalar<void() const volatile&>();
    test_is_not_safe_scalar<void() const volatile&&>();
    test_is_not_safe_scalar<void() noexcept>();
    test_is_not_safe_scalar<void()& noexcept>();
    test_is_not_safe_scalar<void()&& noexcept>();
    test_is_not_safe_scalar<void() const noexcept>();
    test_is_not_safe_scalar<void() const& noexcept>();
    test_is_not_safe_scalar<void() const&& noexcept>();
    test_is_not_safe_scalar<void() volatile noexcept>();
    test_is_not_safe_scalar<void() volatile& noexcept>();
    test_is_not_safe_scalar<void() volatile&& noexcept>();
    test_is_not_safe_scalar<void() const volatile noexcept>();
    test_is_not_safe_scalar<void() const volatile& noexcept>();
    test_is_not_safe_scalar<void() const volatile&& noexcept>();

    test_is_not_safe_scalar<void(int)>();
    test_is_not_safe_scalar<void(int)&>();
    test_is_not_safe_scalar<void(int) &&>();
    test_is_not_safe_scalar<void(int) const>();
    test_is_not_safe_scalar<void(int) const&>();
    test_is_not_safe_scalar<void(int) const&&>();
    test_is_not_safe_scalar<void(int) volatile>();
    test_is_not_safe_scalar<void(int) volatile&>();
    test_is_not_safe_scalar<void(int) volatile&&>();
    test_is_not_safe_scalar<void(int) const volatile>();
    test_is_not_safe_scalar<void(int) const volatile&>();
    test_is_not_safe_scalar<void(int) const volatile&&>();
    test_is_not_safe_scalar<void(int) noexcept>();
    test_is_not_safe_scalar<void(int)& noexcept>();
    test_is_not_safe_scalar<void(int)&& noexcept>();
    test_is_not_safe_scalar<void(int) const noexcept>();
    test_is_not_safe_scalar<void(int) const& noexcept>();
    test_is_not_safe_scalar<void(int) const&& noexcept>();
    test_is_not_safe_scalar<void(int) volatile noexcept>();
    test_is_not_safe_scalar<void(int) volatile& noexcept>();
    test_is_not_safe_scalar<void(int) volatile&& noexcept>();
    test_is_not_safe_scalar<void(int) const volatile noexcept>();
    test_is_not_safe_scalar<void(int) const volatile& noexcept>();
    test_is_not_safe_scalar<void(int) const volatile&& noexcept>();

    test_is_not_safe_scalar<void(...)>();
    test_is_not_safe_scalar<void(...)&>();
    test_is_not_safe_scalar<void(...) &&>();
    test_is_not_safe_scalar<void(...) const>();
    test_is_not_safe_scalar<void(...) const&>();
    test_is_not_safe_scalar<void(...) const&&>();
    test_is_not_safe_scalar<void(...) volatile>();
    test_is_not_safe_scalar<void(...) volatile&>();
    test_is_not_safe_scalar<void(...) volatile&&>();
    test_is_not_safe_scalar<void(...) const volatile>();
    test_is_not_safe_scalar<void(...) const volatile&>();
    test_is_not_safe_scalar<void(...) const volatile&&>();
    test_is_not_safe_scalar<void(...) noexcept>();
    test_is_not_safe_scalar<void(...)& noexcept>();
    test_is_not_safe_scalar<void(...)&& noexcept>();
    test_is_not_safe_scalar<void(...) const noexcept>();
    test_is_not_safe_scalar<void(...) const& noexcept>();
    test_is_not_safe_scalar<void(...) const&& noexcept>();
    test_is_not_safe_scalar<void(...) volatile noexcept>();
    test_is_not_safe_scalar<void(...) volatile& noexcept>();
    test_is_not_safe_scalar<void(...) volatile&& noexcept>();
    test_is_not_safe_scalar<void(...) const volatile noexcept>();
    test_is_not_safe_scalar<void(...) const volatile& noexcept>();
    test_is_not_safe_scalar<void(...) const volatile&& noexcept>();

    test_is_not_safe_scalar<void(int, ...)>();
    test_is_not_safe_scalar<void(int, ...)&>();
    test_is_not_safe_scalar<void(int, ...) &&>();
    test_is_not_safe_scalar<void(int, ...) const>();
    test_is_not_safe_scalar<void(int, ...) const&>();
    test_is_not_safe_scalar<void(int, ...) const&&>();
    test_is_not_safe_scalar<void(int, ...) volatile>();
    test_is_not_safe_scalar<void(int, ...) volatile&>();
    test_is_not_safe_scalar<void(int, ...) volatile&&>();
    test_is_not_safe_scalar<void(int, ...) const volatile>();
    test_is_not_safe_scalar<void(int, ...) const volatile&>();
    test_is_not_safe_scalar<void(int, ...) const volatile&&>();
    test_is_not_safe_scalar<void(int, ...) noexcept>();
    test_is_not_safe_scalar<void(int, ...)& noexcept>();
    test_is_not_safe_scalar<void(int, ...)&& noexcept>();
    test_is_not_safe_scalar<void(int, ...) const noexcept>();
    test_is_not_safe_scalar<void(int, ...) const& noexcept>();
    test_is_not_safe_scalar<void(int, ...) const&& noexcept>();
    test_is_not_safe_scalar<void(int, ...) volatile noexcept>();
    test_is_not_safe_scalar<void(int, ...) volatile& noexcept>();
    test_is_not_safe_scalar<void(int, ...) volatile&& noexcept>();
    test_is_not_safe_scalar<void(int, ...) const volatile noexcept>();
    test_is_not_safe_scalar<void(int, ...) const volatile& noexcept>();
    test_is_not_safe_scalar<void(int, ...) const volatile&& noexcept>();

    test_is_not_safe_scalar<int()>();
    test_is_not_safe_scalar<int()&>();
    test_is_not_safe_scalar<int() &&>();
    test_is_not_safe_scalar<int() const>();
    test_is_not_safe_scalar<int() const&>();
    test_is_not_safe_scalar<int() const&&>();
    test_is_not_safe_scalar<int() volatile>();
    test_is_not_safe_scalar<int() volatile&>();
    test_is_not_safe_scalar<int() volatile&&>();
    test_is_not_safe_scalar<int() const volatile>();
    test_is_not_safe_scalar<int() const volatile&>();
    test_is_not_safe_scalar<int() const volatile&&>();
    test_is_not_safe_scalar<int() noexcept>();
    test_is_not_safe_scalar<int()& noexcept>();
    test_is_not_safe_scalar<int()&& noexcept>();
    test_is_not_safe_scalar<int() const noexcept>();
    test_is_not_safe_scalar<int() const& noexcept>();
    test_is_not_safe_scalar<int() const&& noexcept>();
    test_is_not_safe_scalar<int() volatile noexcept>();
    test_is_not_safe_scalar<int() volatile& noexcept>();
    test_is_not_safe_scalar<int() volatile&& noexcept>();
    test_is_not_safe_scalar<int() const volatile noexcept>();
    test_is_not_safe_scalar<int() const volatile& noexcept>();
    test_is_not_safe_scalar<int() const volatile&& noexcept>();

    test_is_not_safe_scalar<int(int)>();
    test_is_not_safe_scalar<int(int)&>();
    test_is_not_safe_scalar<int(int) &&>();
    test_is_not_safe_scalar<int(int) const>();
    test_is_not_safe_scalar<int(int) const&>();
    test_is_not_safe_scalar<int(int) const&&>();
    test_is_not_safe_scalar<int(int) volatile>();
    test_is_not_safe_scalar<int(int) volatile&>();
    test_is_not_safe_scalar<int(int) volatile&&>();
    test_is_not_safe_scalar<int(int) const volatile>();
    test_is_not_safe_scalar<int(int) const volatile&>();
    test_is_not_safe_scalar<int(int) const volatile&&>();
    test_is_not_safe_scalar<int(int) noexcept>();
    test_is_not_safe_scalar<int(int)& noexcept>();
    test_is_not_safe_scalar<int(int)&& noexcept>();
    test_is_not_safe_scalar<int(int) const noexcept>();
    test_is_not_safe_scalar<int(int) const& noexcept>();
    test_is_not_safe_scalar<int(int) const&& noexcept>();
    test_is_not_safe_scalar<int(int) volatile noexcept>();
    test_is_not_safe_scalar<int(int) volatile& noexcept>();
    test_is_not_safe_scalar<int(int) volatile&& noexcept>();
    test_is_not_safe_scalar<int(int) const volatile noexcept>();
    test_is_not_safe_scalar<int(int) const volatile& noexcept>();
    test_is_not_safe_scalar<int(int) const volatile&& noexcept>();

    test_is_not_safe_scalar<int(...)>();
    test_is_not_safe_scalar<int(...)&>();
    test_is_not_safe_scalar<int(...) &&>();
    test_is_not_safe_scalar<int(...) const>();
    test_is_not_safe_scalar<int(...) const&>();
    test_is_not_safe_scalar<int(...) const&&>();
    test_is_not_safe_scalar<int(...) volatile>();
    test_is_not_safe_scalar<int(...) volatile&>();
    test_is_not_safe_scalar<int(...) volatile&&>();
    test_is_not_safe_scalar<int(...) const volatile>();
    test_is_not_safe_scalar<int(...) const volatile&>();
    test_is_not_safe_scalar<int(...) const volatile&&>();
    test_is_not_safe_scalar<int(...) noexcept>();
    test_is_not_safe_scalar<int(...)& noexcept>();
    test_is_not_safe_scalar<int(...)&& noexcept>();
    test_is_not_safe_scalar<int(...) const noexcept>();
    test_is_not_safe_scalar<int(...) const& noexcept>();
    test_is_not_safe_scalar<int(...) const&& noexcept>();
    test_is_not_safe_scalar<int(...) volatile noexcept>();
    test_is_not_safe_scalar<int(...) volatile& noexcept>();
    test_is_not_safe_scalar<int(...) volatile&& noexcept>();
    test_is_not_safe_scalar<int(...) const volatile noexcept>();
    test_is_not_safe_scalar<int(...) const volatile& noexcept>();
    test_is_not_safe_scalar<int(...) const volatile&& noexcept>();

    test_is_not_safe_scalar<int(int, ...)>();
    test_is_not_safe_scalar<int(int, ...)&>();
    test_is_not_safe_scalar<int(int, ...) &&>();
    test_is_not_safe_scalar<int(int, ...) const>();
    test_is_not_safe_scalar<int(int, ...) const&>();
    test_is_not_safe_scalar<int(int, ...) const&&>();
    test_is_not_safe_scalar<int(int, ...) volatile>();
    test_is_not_safe_scalar<int(int, ...) volatile&>();
    test_is_not_safe_scalar<int(int, ...) volatile&&>();
    test_is_not_safe_scalar<int(int, ...) const volatile>();
    test_is_not_safe_scalar<int(int, ...) const volatile&>();
    test_is_not_safe_scalar<int(int, ...) const volatile&&>();
    test_is_not_safe_scalar<int(int, ...) noexcept>();
    test_is_not_safe_scalar<int(int, ...)& noexcept>();
    test_is_not_safe_scalar<int(int, ...)&& noexcept>();
    test_is_not_safe_scalar<int(int, ...) const noexcept>();
    test_is_not_safe_scalar<int(int, ...) const& noexcept>();
    test_is_not_safe_scalar<int(int, ...) const&& noexcept>();
    test_is_not_safe_scalar<int(int, ...) volatile noexcept>();
    test_is_not_safe_scalar<int(int, ...) volatile& noexcept>();
    test_is_not_safe_scalar<int(int, ...) volatile&& noexcept>();
    test_is_not_safe_scalar<int(int, ...) const volatile noexcept>();
    test_is_not_safe_scalar<int(int, ...) const volatile& noexcept>();
    test_is_not_safe_scalar<int(int, ...) const volatile&& noexcept>();

    test_is_safe_scalar<void (*)()>();
    test_is_safe_scalar<void (*)() noexcept>();

    test_is_safe_scalar<void (*)(int)>();
    test_is_safe_scalar<void (*)(int) noexcept>();

    test_is_safe_scalar<void (*)(...)>();
    test_is_safe_scalar<void (*)(...) noexcept>();

    test_is_safe_scalar<void (*)(int, ...)>();
    test_is_safe_scalar<void (*)(int, ...) noexcept>();

    test_is_safe_scalar<int (*)()>();
    test_is_safe_scalar<int (*)() noexcept>();

    test_is_safe_scalar<int (*)(int)>();
    test_is_safe_scalar<int (*)(int) noexcept>();

    test_is_safe_scalar<int (*)(...)>();
    test_is_safe_scalar<int (*)(...) noexcept>();

    test_is_safe_scalar<int (*)(int, ...)>();
    test_is_safe_scalar<int (*)(int, ...) noexcept>();

    test_is_not_safe_scalar<void (&)()>();
    test_is_not_safe_scalar<void (&)() noexcept>();

    test_is_not_safe_scalar<void (&)(int)>();
    test_is_not_safe_scalar<void (&)(int) noexcept>();

    test_is_not_safe_scalar<void (&)(...)>();
    test_is_not_safe_scalar<void (&)(...) noexcept>();

    test_is_not_safe_scalar<void (&)(int, ...)>();
    test_is_not_safe_scalar<void (&)(int, ...) noexcept>();

    test_is_not_safe_scalar<int (&)()>();
    test_is_not_safe_scalar<int (&)() noexcept>();

    test_is_not_safe_scalar<int (&)(int)>();
    test_is_not_safe_scalar<int (&)(int) noexcept>();

    test_is_not_safe_scalar<int (&)(...)>();
    test_is_not_safe_scalar<int (&)(...) noexcept>();

    test_is_not_safe_scalar<int (&)(int, ...)>();
    test_is_not_safe_scalar<int (&)(int, ...) noexcept>();

    test_is_not_safe_scalar<void(&&)()>();
    test_is_not_safe_scalar<void(&&)() noexcept>();

    test_is_not_safe_scalar<void(&&)(int)>();
    test_is_not_safe_scalar<void(&&)(int) noexcept>();

    test_is_not_safe_scalar<void(&&)(...)>();
    test_is_not_safe_scalar<void(&&)(...) noexcept>();

    test_is_not_safe_scalar<void(&&)(int, ...)>();
    test_is_not_safe_scalar<void(&&)(int, ...) noexcept>();

    test_is_not_safe_scalar<int(&&)()>();
    test_is_not_safe_scalar<int(&&)() noexcept>();

    test_is_not_safe_scalar<int(&&)(int)>();
    test_is_not_safe_scalar<int(&&)(int) noexcept>();

    test_is_not_safe_scalar<int(&&)(...)>();
    test_is_not_safe_scalar<int(&&)(...) noexcept>();

    test_is_not_safe_scalar<int(&&)(int, ...)>();
    test_is_not_safe_scalar<int(&&)(int, ...) noexcept>();

    test_is_safe_scalar<void (Class::*)()>();
    test_is_safe_scalar<void (Class::*)()&>();
    test_is_safe_scalar<void (Class::*)() &&>();
    test_is_safe_scalar<void (Class::*)() const>();
    test_is_safe_scalar<void (Class::*)() const&>();
    test_is_safe_scalar<void (Class::*)() const&&>();
    test_is_safe_scalar<void (Class::*)() noexcept>();
    test_is_safe_scalar<void (Class::*)()& noexcept>();
    test_is_safe_scalar<void (Class::*)()&& noexcept>();
    test_is_safe_scalar<void (Class::*)() const noexcept>();
    test_is_safe_scalar<void (Class::*)() const& noexcept>();
    test_is_safe_scalar<void (Class::*)() const&& noexcept>();

    test_is_safe_scalar<void (Class::*)(int)>();
    test_is_safe_scalar<void (Class::*)(int)&>();
    test_is_safe_scalar<void (Class::*)(int) &&>();
    test_is_safe_scalar<void (Class::*)(int) const>();
    test_is_safe_scalar<void (Class::*)(int) const&>();
    test_is_safe_scalar<void (Class::*)(int) const&&>();
    test_is_safe_scalar<void (Class::*)(int) noexcept>();
    test_is_safe_scalar<void (Class::*)(int)& noexcept>();
    test_is_safe_scalar<void (Class::*)(int)&& noexcept>();
    test_is_safe_scalar<void (Class::*)(int) const noexcept>();
    test_is_safe_scalar<void (Class::*)(int) const& noexcept>();
    test_is_safe_scalar<void (Class::*)(int) const&& noexcept>();

    test_is_safe_scalar<void (Class::*)(...)>();
    test_is_safe_scalar<void (Class::*)(...)&>();
    test_is_safe_scalar<void (Class::*)(...) &&>();
    test_is_safe_scalar<void (Class::*)(...) const>();
    test_is_safe_scalar<void (Class::*)(...) const&>();
    test_is_safe_scalar<void (Class::*)(...) const&&>();
    test_is_safe_scalar<void (Class::*)(...) noexcept>();
    test_is_safe_scalar<void (Class::*)(...)& noexcept>();
    test_is_safe_scalar<void (Class::*)(...)&& noexcept>();
    test_is_safe_scalar<void (Class::*)(...) const noexcept>();
    test_is_safe_scalar<void (Class::*)(...) const& noexcept>();
    test_is_safe_scalar<void (Class::*)(...) const&& noexcept>();

    test_is_safe_scalar<void (Class::*)(int, ...)>();
    test_is_safe_scalar<void (Class::*)(int, ...)&>();
    test_is_safe_scalar<void (Class::*)(int, ...) &&>();
    test_is_safe_scalar<void (Class::*)(int, ...) const>();
    test_is_safe_scalar<void (Class::*)(int, ...) const&>();
    test_is_safe_scalar<void (Class::*)(int, ...) const&&>();
    test_is_safe_scalar<void (Class::*)(int, ...) noexcept>();
    test_is_safe_scalar<void (Class::*)(int, ...)& noexcept>();
    test_is_safe_scalar<void (Class::*)(int, ...)&& noexcept>();
    test_is_safe_scalar<void (Class::*)(int, ...) const noexcept>();
    test_is_safe_scalar<void (Class::*)(int, ...) const& noexcept>();
    test_is_safe_scalar<void (Class::*)(int, ...) const&& noexcept>();

    test_is_safe_scalar<int (Class::*)()>();
    test_is_safe_scalar<int (Class::*)()&>();
    test_is_safe_scalar<int (Class::*)() &&>();
    test_is_safe_scalar<int (Class::*)() const>();
    test_is_safe_scalar<int (Class::*)() const&>();
    test_is_safe_scalar<int (Class::*)() const&&>();
    test_is_safe_scalar<int (Class::*)() noexcept>();
    test_is_safe_scalar<int (Class::*)()& noexcept>();
    test_is_safe_scalar<int (Class::*)()&& noexcept>();
    test_is_safe_scalar<int (Class::*)() const noexcept>();
    test_is_safe_scalar<int (Class::*)() const& noexcept>();
    test_is_safe_scalar<int (Class::*)() const&& noexcept>();

    test_is_safe_scalar<int (Class::*)(int)>();
    test_is_safe_scalar<int (Class::*)(int)&>();
    test_is_safe_scalar<int (Class::*)(int) &&>();
    test_is_safe_scalar<int (Class::*)(int) const>();
    test_is_safe_scalar<int (Class::*)(int) const&>();
    test_is_safe_scalar<int (Class::*)(int) const&&>();
    test_is_safe_scalar<int (Class::*)(int) noexcept>();
    test_is_safe_scalar<int (Class::*)(int)& noexcept>();
    test_is_safe_scalar<int (Class::*)(int)&& noexcept>();
    test_is_safe_scalar<int (Class::*)(int) const noexcept>();
    test_is_safe_scalar<int (Class::*)(int) const& noexcept>();
    test_is_safe_scalar<int (Class::*)(int) const&& noexcept>();

    test_is_safe_scalar<int (Class::*)(...)>();
    test_is_safe_scalar<int (Class::*)(...)&>();
    test_is_safe_scalar<int (Class::*)(...) &&>();
    test_is_safe_scalar<int (Class::*)(...) const>();
    test_is_safe_scalar<int (Class::*)(...) const&>();
    test_is_safe_scalar<int (Class::*)(...) const&&>();
    test_is_safe_scalar<int (Class::*)(...) noexcept>();
    test_is_safe_scalar<int (Class::*)(...)& noexcept>();
    test_is_safe_scalar<int (Class::*)(...)&& noexcept>();
    test_is_safe_scalar<int (Class::*)(...) const noexcept>();
    test_is_safe_scalar<int (Class::*)(...) const& noexcept>();
    test_is_safe_scalar<int (Class::*)(...) const&& noexcept>();

    test_is_safe_scalar<int (Class::*)(int, ...)>();
    test_is_safe_scalar<int (Class::*)(int, ...)&>();
    test_is_safe_scalar<int (Class::*)(int, ...) &&>();
    test_is_safe_scalar<int (Class::*)(int, ...) const>();
    test_is_safe_scalar<int (Class::*)(int, ...) const&>();
    test_is_safe_scalar<int (Class::*)(int, ...) const&&>();
    test_is_safe_scalar<int (Class::*)(int, ...) noexcept>();
    test_is_safe_scalar<int (Class::*)(int, ...)& noexcept>();
    test_is_safe_scalar<int (Class::*)(int, ...)&& noexcept>();
    test_is_safe_scalar<int (Class::*)(int, ...) const noexcept>();
    test_is_safe_scalar<int (Class::*)(int, ...) const& noexcept>();
    test_is_safe_scalar<int (Class::*)(int, ...) const&& noexcept>();
}
