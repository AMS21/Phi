#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unsafe_scalar.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_unsafe_scalar_impl()
{
#if PHI_HAS_WORKING_IS_UNSAFE_SCALAR()
    STATIC_REQUIRE(phi::is_unsafe_scalar<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_scalar<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_scalar_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_scalar_v<T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_scalar<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_scalar<T>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_scalar<T>::value);
#endif
}

template <typename T>
void test_is_not_unsafe_scalar_impl()
{
#if PHI_HAS_WORKING_IS_UNSAFE_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_scalar<T>::value);
    STATIC_REQUIRE(phi::is_not_unsafe_scalar<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_scalar_v<T>);
    STATIC_REQUIRE(phi::is_not_unsafe_scalar_v<T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_scalar<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_scalar<T>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_scalar<T>::value);
#endif
}

template <typename T>
void test_is_unsafe_scalar()
{
    test_is_unsafe_scalar_impl<T>();
    test_is_unsafe_scalar_impl<const T>();
    test_is_unsafe_scalar_impl<volatile T>();
    test_is_unsafe_scalar_impl<const volatile T>();
}

template <typename T>
void test_is_not_unsafe_scalar()
{
    test_is_not_unsafe_scalar_impl<T>();
    test_is_not_unsafe_scalar_impl<const T>();
    test_is_not_unsafe_scalar_impl<volatile T>();
    test_is_not_unsafe_scalar_impl<const volatile T>();
}

TEST_CASE("is_unsafe_scalar")
{
    test_is_not_unsafe_scalar<void>();
    test_is_unsafe_scalar<phi::nullptr_t>();
    test_is_unsafe_scalar<bool>();
    test_is_unsafe_scalar<char>();
    test_is_unsafe_scalar<signed char>();
    test_is_unsafe_scalar<unsigned char>();
    test_is_unsafe_scalar<short>();
    test_is_unsafe_scalar<unsigned short>();
    test_is_unsafe_scalar<int>();
    test_is_unsafe_scalar<unsigned int>();
    test_is_unsafe_scalar<long>();
    test_is_unsafe_scalar<unsigned long>();
    test_is_unsafe_scalar<long long>();
    test_is_unsafe_scalar<unsigned long long>();
    test_is_unsafe_scalar<float>();
    test_is_unsafe_scalar<double>();
    test_is_unsafe_scalar<long double>();
    test_is_unsafe_scalar<char8_t>();
    test_is_unsafe_scalar<char16_t>();
    test_is_unsafe_scalar<char32_t>();
    test_is_unsafe_scalar<wchar_t>();

    test_is_not_unsafe_scalar<phi::boolean>();
    test_is_not_unsafe_scalar<phi::integer<signed char>>();
    test_is_not_unsafe_scalar<phi::integer<unsigned char>>();
    test_is_not_unsafe_scalar<phi::integer<short>>();
    test_is_not_unsafe_scalar<phi::integer<unsigned short>>();
    test_is_not_unsafe_scalar<phi::integer<int>>();
    test_is_not_unsafe_scalar<phi::integer<unsigned int>>();
    test_is_not_unsafe_scalar<phi::integer<long>>();
    test_is_not_unsafe_scalar<phi::integer<unsigned long>>();
    test_is_not_unsafe_scalar<phi::integer<long long>>();
    test_is_not_unsafe_scalar<phi::integer<unsigned long long>>();
    test_is_not_unsafe_scalar<phi::floating_point<float>>();
    test_is_not_unsafe_scalar<phi::floating_point<double>>();
    test_is_not_unsafe_scalar<phi::floating_point<long double>>();

    test_is_not_unsafe_scalar<std::vector<int>>();
    test_is_not_unsafe_scalar<phi::scope_ptr<int>>();

    test_is_not_unsafe_scalar<int&>();
    test_is_not_unsafe_scalar<const int&>();
    test_is_not_unsafe_scalar<volatile int&>();
    test_is_not_unsafe_scalar<const volatile int&>();
    test_is_not_unsafe_scalar<int&&>();
    test_is_not_unsafe_scalar<const int&&>();
    test_is_not_unsafe_scalar<volatile int&&>();
    test_is_not_unsafe_scalar<const volatile int&&>();
    test_is_unsafe_scalar<int*>();
    test_is_unsafe_scalar<const int*>();
    test_is_unsafe_scalar<volatile int*>();
    test_is_unsafe_scalar<const volatile int*>();
    test_is_unsafe_scalar<int**>();
    test_is_unsafe_scalar<const int**>();
    test_is_unsafe_scalar<volatile int**>();
    test_is_unsafe_scalar<const volatile int**>();
    test_is_not_unsafe_scalar<int*&>();
    test_is_not_unsafe_scalar<const int*&>();
    test_is_not_unsafe_scalar<volatile int*&>();
    test_is_not_unsafe_scalar<const volatile int*&>();
    test_is_not_unsafe_scalar<int*&&>();
    test_is_not_unsafe_scalar<const int*&&>();
    test_is_not_unsafe_scalar<volatile int*&&>();
    test_is_not_unsafe_scalar<const volatile int*&&>();
    test_is_unsafe_scalar<void*>();
    test_is_not_unsafe_scalar<char[3]>();
    test_is_not_unsafe_scalar<char[]>();
    test_is_not_unsafe_scalar<char* [3]>();
    test_is_not_unsafe_scalar<char*[]>();
    test_is_unsafe_scalar<int(*)[3]>();
    test_is_unsafe_scalar<int(*)[]>();
    test_is_not_unsafe_scalar<int(&)[3]>();
    test_is_not_unsafe_scalar<int(&)[]>();
    test_is_not_unsafe_scalar<int(&&)[3]>();
    test_is_not_unsafe_scalar<int(&&)[]>();
    test_is_not_unsafe_scalar<char[3][2]>();
    test_is_not_unsafe_scalar<char[][2]>();
    test_is_not_unsafe_scalar<char* [3][2]>();
    test_is_not_unsafe_scalar<char*[][2]>();
    test_is_unsafe_scalar<int(*)[3][2]>();
    test_is_unsafe_scalar<int(*)[][2]>();
    test_is_not_unsafe_scalar<int(&)[3][2]>();
    test_is_not_unsafe_scalar<int(&)[][2]>();
    test_is_not_unsafe_scalar<int(&&)[3][2]>();
    test_is_not_unsafe_scalar<int(&&)[][2]>();
    test_is_not_unsafe_scalar<Class>();
    test_is_not_unsafe_scalar<Class[]>();
    test_is_not_unsafe_scalar<Class[2]>();
    test_is_not_unsafe_scalar<Template<void>>();
    test_is_not_unsafe_scalar<Template<int>>();
    test_is_not_unsafe_scalar<Template<Class>>();
    test_is_not_unsafe_scalar<Template<IncompleteType>>();
    test_is_not_unsafe_scalar<VariadicTemplate<>>();
    test_is_not_unsafe_scalar<VariadicTemplate<void>>();
    test_is_not_unsafe_scalar<VariadicTemplate<int>>();
    test_is_not_unsafe_scalar<VariadicTemplate<Class>>();
    test_is_not_unsafe_scalar<VariadicTemplate<IncompleteType>>();
    test_is_not_unsafe_scalar<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_scalar<PublicDerivedFromTemplate<Base>>();
    test_is_not_unsafe_scalar<PublicDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_scalar<PublicDerivedFromTemplate<Class>>();
    test_is_not_unsafe_scalar<PrivateDerivedFromTemplate<Base>>();
    test_is_not_unsafe_scalar<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_scalar<PrivateDerivedFromTemplate<Class>>();
    test_is_not_unsafe_scalar<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_unsafe_scalar<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_scalar<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_unsafe_scalar<VirtualDerivedFromTemplate<Base>>();
    test_is_not_unsafe_scalar<VirtualDerivedFromTemplate<Derived>>();
    test_is_not_unsafe_scalar<VirtualDerivedFromTemplate<Class>>();
    test_is_not_unsafe_scalar<Union>();
    test_is_not_unsafe_scalar<NonEmptyUnion>();
    test_is_not_unsafe_scalar<NonTrivialUnion>();
    test_is_not_unsafe_scalar<Empty>();
    test_is_not_unsafe_scalar<NotEmpty>();
    test_is_not_unsafe_scalar<NonTrivial>();
    test_is_not_unsafe_scalar<BitZero>();
    test_is_not_unsafe_scalar<BitOne>();
    test_is_not_unsafe_scalar<Base>();
    test_is_not_unsafe_scalar<Derived>();
    test_is_not_unsafe_scalar<Polymorphic>();
    test_is_not_unsafe_scalar<DerivedPolymorphic>();
    test_is_not_unsafe_scalar<Abstract>();
    test_is_not_unsafe_scalar<PublicAbstract>();
    test_is_not_unsafe_scalar<PrivateAbstract>();
    test_is_not_unsafe_scalar<ProtectedAbstract>();
    test_is_not_unsafe_scalar<AbstractTemplate<int>>();
    test_is_not_unsafe_scalar<AbstractTemplate<double>>();
    test_is_not_unsafe_scalar<AbstractTemplate<Class>>();
    test_is_not_unsafe_scalar<AbstractTemplate<IncompleteType>>();
    test_is_not_unsafe_scalar<PublicAbstractDeletedDestructor>();
    test_is_not_unsafe_scalar<ProtectedAbstractDeletedDestructor>();
    test_is_not_unsafe_scalar<PrivateAbstractDeletedDestructor>();
    test_is_not_unsafe_scalar<Final>();
    test_is_not_unsafe_scalar<FinalDerived>();
    test_is_not_unsafe_scalar<PublicDestructor>();
    test_is_not_unsafe_scalar<ProtectedDestructor>();
    test_is_not_unsafe_scalar<PrivateDestructor>();
    test_is_not_unsafe_scalar<VirtualPublicDestructor>();
    test_is_not_unsafe_scalar<VirtualProtectedDestructor>();
    test_is_not_unsafe_scalar<VirtualPrivateDestructor>();
    test_is_not_unsafe_scalar<PurePublicDestructor>();
    test_is_not_unsafe_scalar<PureProtectedDestructor>();
    test_is_not_unsafe_scalar<PurePrivateDestructor>();
    test_is_not_unsafe_scalar<DeletedPublicDestructor>();
    test_is_not_unsafe_scalar<DeletedProtectedDestructor>();
    test_is_not_unsafe_scalar<DeletedPrivateDestructor>();
    test_is_not_unsafe_scalar<DeletedVirtualPublicDestructor>();
    test_is_not_unsafe_scalar<DeletedVirtualProtectedDestructor>();
    test_is_not_unsafe_scalar<DeletedVirtualPrivateDestructor>();
    test_is_not_unsafe_scalar<ExplicitClass>();
    test_is_not_unsafe_scalar<NothrowExplicitClass>();
    test_is_not_unsafe_scalar<ThrowExplicitClass>();
    test_is_not_unsafe_scalar<ThrowDefaultClass>();
    test_is_not_unsafe_scalar<ThrowCopyConsClass>();
    test_is_not_unsafe_scalar<ThrowMoveConsClass>();
    test_is_not_unsafe_scalar<NoexceptExplicitClass>();
    test_is_not_unsafe_scalar<ExceptExplicitClass>();
    test_is_not_unsafe_scalar<NoexceptDefaultClass>();
    test_is_not_unsafe_scalar<ExceptDefaultClass>();
    test_is_not_unsafe_scalar<NoexceptCopyConsClass>();
    test_is_not_unsafe_scalar<ExceptCopyConsClass>();
    test_is_not_unsafe_scalar<NoexceptMoveConsClass>();
    test_is_not_unsafe_scalar<ExceptMoveConsClass>();
    test_is_not_unsafe_scalar<NoexceptCopyAssignClass>();
    test_is_not_unsafe_scalar<ExceptCopyAssignClass>();
    test_is_not_unsafe_scalar<NoexceptMoveAssignClass>();
    test_is_not_unsafe_scalar<ExceptMoveAssignClass>();
    test_is_not_unsafe_scalar<DeletedCopyAssignClass>();
    test_is_not_unsafe_scalar<DeletedMoveAssignClass>();
    test_is_not_unsafe_scalar<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_unsafe_scalar<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_unsafe_scalar<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_not_unsafe_scalar<ExceptMoveConsExceptMoveAssignClass>();
    test_is_not_unsafe_scalar<ImplicitTo<int>>();
    test_is_not_unsafe_scalar<ImplicitTo<float>>();
    test_is_not_unsafe_scalar<ImplicitTo<Class>>();
    test_is_not_unsafe_scalar<DeletedImplicitTo<int>>();
    test_is_not_unsafe_scalar<DeletedImplicitTo<float>>();
    test_is_not_unsafe_scalar<DeletedImplicitTo<Class>>();
    test_is_not_unsafe_scalar<ExplicitTo<int>>();
    test_is_not_unsafe_scalar<ExplicitTo<float>>();
    test_is_not_unsafe_scalar<ExplicitTo<Class>>();
    test_is_not_unsafe_scalar<DeletedExplicitTo<int>>();
    test_is_not_unsafe_scalar<DeletedExplicitTo<float>>();
    test_is_not_unsafe_scalar<DeletedExplicitTo<Class>>();
    test_is_not_unsafe_scalar<Ellipsis>();
    test_is_not_unsafe_scalar<DeletedEllipsis>();
    test_is_not_unsafe_scalar<CopyConsOnlyType>();
    test_is_not_unsafe_scalar<MoveConsOnlyType>();
    test_is_not_unsafe_scalar<OverloadedOperators>();
    test_is_not_unsafe_scalar<PublicIntMember>();
    test_is_not_unsafe_scalar<ProtectedIntMember>();
    test_is_not_unsafe_scalar<PrivateIntMember>();
    test_is_not_unsafe_scalar<PublicStaticIntMember>();
    test_is_not_unsafe_scalar<ProtectedStaticIntMember>();
    test_is_not_unsafe_scalar<PrivateStaticIntMember>();
    test_is_not_unsafe_scalar<PublicTemplateMember<int>>();
    test_is_not_unsafe_scalar<PublicTemplateMember<float>>();
    test_is_not_unsafe_scalar<PublicTemplateMember<Class>>();
    test_is_not_unsafe_scalar<ProtectedTemplateMember<int>>();
    test_is_not_unsafe_scalar<ProtectedTemplateMember<float>>();
    test_is_not_unsafe_scalar<ProtectedTemplateMember<Class>>();
    test_is_not_unsafe_scalar<PrivateTemplateMember<int>>();
    test_is_not_unsafe_scalar<PrivateTemplateMember<float>>();
    test_is_not_unsafe_scalar<PrivateTemplateMember<Class>>();
    test_is_not_unsafe_scalar<PublicStaticTemplateMember<int>>();
    test_is_not_unsafe_scalar<PublicStaticTemplateMember<float>>();
    test_is_not_unsafe_scalar<PublicStaticTemplateMember<Class>>();
    test_is_not_unsafe_scalar<ProtectedStaticTemplateMember<int>>();
    test_is_not_unsafe_scalar<ProtectedStaticTemplateMember<float>>();
    test_is_not_unsafe_scalar<ProtectedStaticTemplateMember<Class>>();
    test_is_not_unsafe_scalar<PrivateStaticTemplateMember<int>>();
    test_is_not_unsafe_scalar<PrivateStaticTemplateMember<float>>();
    test_is_not_unsafe_scalar<PrivateStaticTemplateMember<Class>>();
    test_is_unsafe_scalar<Enum>();
    test_is_unsafe_scalar<EnumSigned>();
    test_is_unsafe_scalar<EnumUnsigned>();
    test_is_unsafe_scalar<EnumClass>();
    test_is_unsafe_scalar<EnumStruct>();
    test_is_not_unsafe_scalar<Function>();
    test_is_unsafe_scalar<FunctionPtr>();
    test_is_unsafe_scalar<MemberObjectPtr>();
    test_is_unsafe_scalar<MemberFunctionPtr>();
    test_is_not_unsafe_scalar<LambdaType>();
    test_is_not_unsafe_scalar<LambdaNoexceptType>();
    test_is_not_unsafe_scalar<LambdaThrowsType>();
    test_is_not_unsafe_scalar<IncompleteType>();
    test_is_not_unsafe_scalar<IncompleteTemplate<void>>();
    test_is_not_unsafe_scalar<IncompleteTemplate<int>>();
    test_is_not_unsafe_scalar<IncompleteTemplate<Class>>();
    test_is_not_unsafe_scalar<IncompleteTemplate<IncompleteType>>();
    test_is_not_unsafe_scalar<IncompleteVariadicTemplate<>>();
    test_is_not_unsafe_scalar<IncompleteVariadicTemplate<void>>();
    test_is_not_unsafe_scalar<IncompleteVariadicTemplate<int>>();
    test_is_not_unsafe_scalar<IncompleteVariadicTemplate<Class>>();
    test_is_not_unsafe_scalar<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_unsafe_scalar<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_scalar<IncompleteUnion>();
    test_is_unsafe_scalar<IncompleteEnumSigned>();
    test_is_unsafe_scalar<IncompleteEnumUnsigned>();
    test_is_unsafe_scalar<IncompleteEnumClass>();
    test_is_unsafe_scalar<IncompleteEnumStruct>();
    test_is_unsafe_scalar<int Class::*>();
    test_is_unsafe_scalar<float Class::*>();
    test_is_unsafe_scalar<void * Class::*>();
    test_is_unsafe_scalar<int * Class::*>();
    test_is_not_unsafe_scalar<int Class::*&>();
    test_is_not_unsafe_scalar<float Class::*&>();
    test_is_not_unsafe_scalar<void * Class::*&>();
    test_is_not_unsafe_scalar<int * Class::*&>();
    test_is_not_unsafe_scalar<int Class::*&&>();
    test_is_not_unsafe_scalar<float Class::*&&>();
    test_is_not_unsafe_scalar<void * Class::*&&>();
    test_is_not_unsafe_scalar<int * Class::*&&>();
    test_is_unsafe_scalar<int Class::*const>();
    test_is_unsafe_scalar<float Class::*const>();
    test_is_unsafe_scalar<void * Class::*const>();
    test_is_not_unsafe_scalar<int Class::*const&>();
    test_is_not_unsafe_scalar<float Class::*const&>();
    test_is_not_unsafe_scalar<void * Class::*const&>();
    test_is_not_unsafe_scalar<int Class::*const&&>();
    test_is_not_unsafe_scalar<float Class::*const&&>();
    test_is_not_unsafe_scalar<void * Class::*const&&>();
    test_is_unsafe_scalar<int Class::*volatile>();
    test_is_unsafe_scalar<float Class::*volatile>();
    test_is_unsafe_scalar<void * Class::*volatile>();
    test_is_not_unsafe_scalar<int Class::*volatile&>();
    test_is_not_unsafe_scalar<float Class::*volatile&>();
    test_is_not_unsafe_scalar<void * Class::*volatile&>();
    test_is_not_unsafe_scalar<int Class::*volatile&&>();
    test_is_not_unsafe_scalar<float Class::*volatile&&>();
    test_is_not_unsafe_scalar<void * Class::*volatile&&>();
    test_is_unsafe_scalar<int Class::*const volatile>();
    test_is_unsafe_scalar<float Class::*const volatile>();
    test_is_unsafe_scalar<void * Class::*const volatile>();
    test_is_not_unsafe_scalar<int Class::*const volatile&>();
    test_is_not_unsafe_scalar<float Class::*const volatile&>();
    test_is_not_unsafe_scalar<void * Class::*const volatile&>();
    test_is_not_unsafe_scalar<int Class::*const volatile&&>();
    test_is_not_unsafe_scalar<float Class::*const volatile&&>();
    test_is_not_unsafe_scalar<void * Class::*const volatile&&>();
    test_is_not_unsafe_scalar<NonCopyable>();
    test_is_not_unsafe_scalar<NonMoveable>();
    test_is_not_unsafe_scalar<NonConstructible>();
    test_is_not_unsafe_scalar<NonDestructible>();
    test_is_not_unsafe_scalar<Tracked>();
    test_is_not_unsafe_scalar<TrapConstructible>();
    test_is_not_unsafe_scalar<TrapImplicitConversion>();
    test_is_not_unsafe_scalar<TrapComma>();
    test_is_not_unsafe_scalar<TrapCall>();
    test_is_not_unsafe_scalar<TrapSelfAssign>();
    test_is_not_unsafe_scalar<TrapDeref>();
    test_is_not_unsafe_scalar<TrapArraySubscript>();

    test_is_not_unsafe_scalar<void()>();
    test_is_not_unsafe_scalar<void()&>();
    test_is_not_unsafe_scalar<void() &&>();
    test_is_not_unsafe_scalar<void() const>();
    test_is_not_unsafe_scalar<void() const&>();
    test_is_not_unsafe_scalar<void() const&&>();
    test_is_not_unsafe_scalar<void() volatile>();
    test_is_not_unsafe_scalar<void() volatile&>();
    test_is_not_unsafe_scalar<void() volatile&&>();
    test_is_not_unsafe_scalar<void() const volatile>();
    test_is_not_unsafe_scalar<void() const volatile&>();
    test_is_not_unsafe_scalar<void() const volatile&&>();
    test_is_not_unsafe_scalar<void() noexcept>();
    test_is_not_unsafe_scalar<void()& noexcept>();
    test_is_not_unsafe_scalar<void()&& noexcept>();
    test_is_not_unsafe_scalar<void() const noexcept>();
    test_is_not_unsafe_scalar<void() const& noexcept>();
    test_is_not_unsafe_scalar<void() const&& noexcept>();
    test_is_not_unsafe_scalar<void() volatile noexcept>();
    test_is_not_unsafe_scalar<void() volatile& noexcept>();
    test_is_not_unsafe_scalar<void() volatile&& noexcept>();
    test_is_not_unsafe_scalar<void() const volatile noexcept>();
    test_is_not_unsafe_scalar<void() const volatile& noexcept>();
    test_is_not_unsafe_scalar<void() const volatile&& noexcept>();

    test_is_not_unsafe_scalar<void(int)>();
    test_is_not_unsafe_scalar<void(int)&>();
    test_is_not_unsafe_scalar<void(int) &&>();
    test_is_not_unsafe_scalar<void(int) const>();
    test_is_not_unsafe_scalar<void(int) const&>();
    test_is_not_unsafe_scalar<void(int) const&&>();
    test_is_not_unsafe_scalar<void(int) volatile>();
    test_is_not_unsafe_scalar<void(int) volatile&>();
    test_is_not_unsafe_scalar<void(int) volatile&&>();
    test_is_not_unsafe_scalar<void(int) const volatile>();
    test_is_not_unsafe_scalar<void(int) const volatile&>();
    test_is_not_unsafe_scalar<void(int) const volatile&&>();
    test_is_not_unsafe_scalar<void(int) noexcept>();
    test_is_not_unsafe_scalar<void(int)& noexcept>();
    test_is_not_unsafe_scalar<void(int)&& noexcept>();
    test_is_not_unsafe_scalar<void(int) const noexcept>();
    test_is_not_unsafe_scalar<void(int) const& noexcept>();
    test_is_not_unsafe_scalar<void(int) const&& noexcept>();
    test_is_not_unsafe_scalar<void(int) volatile noexcept>();
    test_is_not_unsafe_scalar<void(int) volatile& noexcept>();
    test_is_not_unsafe_scalar<void(int) volatile&& noexcept>();
    test_is_not_unsafe_scalar<void(int) const volatile noexcept>();
    test_is_not_unsafe_scalar<void(int) const volatile& noexcept>();
    test_is_not_unsafe_scalar<void(int) const volatile&& noexcept>();

    test_is_not_unsafe_scalar<void(...)>();
    test_is_not_unsafe_scalar<void(...)&>();
    test_is_not_unsafe_scalar<void(...) &&>();
    test_is_not_unsafe_scalar<void(...) const>();
    test_is_not_unsafe_scalar<void(...) const&>();
    test_is_not_unsafe_scalar<void(...) const&&>();
    test_is_not_unsafe_scalar<void(...) volatile>();
    test_is_not_unsafe_scalar<void(...) volatile&>();
    test_is_not_unsafe_scalar<void(...) volatile&&>();
    test_is_not_unsafe_scalar<void(...) const volatile>();
    test_is_not_unsafe_scalar<void(...) const volatile&>();
    test_is_not_unsafe_scalar<void(...) const volatile&&>();
    test_is_not_unsafe_scalar<void(...) noexcept>();
    test_is_not_unsafe_scalar<void(...)& noexcept>();
    test_is_not_unsafe_scalar<void(...)&& noexcept>();
    test_is_not_unsafe_scalar<void(...) const noexcept>();
    test_is_not_unsafe_scalar<void(...) const& noexcept>();
    test_is_not_unsafe_scalar<void(...) const&& noexcept>();
    test_is_not_unsafe_scalar<void(...) volatile noexcept>();
    test_is_not_unsafe_scalar<void(...) volatile& noexcept>();
    test_is_not_unsafe_scalar<void(...) volatile&& noexcept>();
    test_is_not_unsafe_scalar<void(...) const volatile noexcept>();
    test_is_not_unsafe_scalar<void(...) const volatile& noexcept>();
    test_is_not_unsafe_scalar<void(...) const volatile&& noexcept>();

    test_is_not_unsafe_scalar<void(int, ...)>();
    test_is_not_unsafe_scalar<void(int, ...)&>();
    test_is_not_unsafe_scalar<void(int, ...) &&>();
    test_is_not_unsafe_scalar<void(int, ...) const>();
    test_is_not_unsafe_scalar<void(int, ...) const&>();
    test_is_not_unsafe_scalar<void(int, ...) const&&>();
    test_is_not_unsafe_scalar<void(int, ...) volatile>();
    test_is_not_unsafe_scalar<void(int, ...) volatile&>();
    test_is_not_unsafe_scalar<void(int, ...) volatile&&>();
    test_is_not_unsafe_scalar<void(int, ...) const volatile>();
    test_is_not_unsafe_scalar<void(int, ...) const volatile&>();
    test_is_not_unsafe_scalar<void(int, ...) const volatile&&>();
    test_is_not_unsafe_scalar<void(int, ...) noexcept>();
    test_is_not_unsafe_scalar<void(int, ...)& noexcept>();
    test_is_not_unsafe_scalar<void(int, ...)&& noexcept>();
    test_is_not_unsafe_scalar<void(int, ...) const noexcept>();
    test_is_not_unsafe_scalar<void(int, ...) const& noexcept>();
    test_is_not_unsafe_scalar<void(int, ...) const&& noexcept>();
    test_is_not_unsafe_scalar<void(int, ...) volatile noexcept>();
    test_is_not_unsafe_scalar<void(int, ...) volatile& noexcept>();
    test_is_not_unsafe_scalar<void(int, ...) volatile&& noexcept>();
    test_is_not_unsafe_scalar<void(int, ...) const volatile noexcept>();
    test_is_not_unsafe_scalar<void(int, ...) const volatile& noexcept>();
    test_is_not_unsafe_scalar<void(int, ...) const volatile&& noexcept>();

    test_is_not_unsafe_scalar<int()>();
    test_is_not_unsafe_scalar<int()&>();
    test_is_not_unsafe_scalar<int() &&>();
    test_is_not_unsafe_scalar<int() const>();
    test_is_not_unsafe_scalar<int() const&>();
    test_is_not_unsafe_scalar<int() const&&>();
    test_is_not_unsafe_scalar<int() volatile>();
    test_is_not_unsafe_scalar<int() volatile&>();
    test_is_not_unsafe_scalar<int() volatile&&>();
    test_is_not_unsafe_scalar<int() const volatile>();
    test_is_not_unsafe_scalar<int() const volatile&>();
    test_is_not_unsafe_scalar<int() const volatile&&>();
    test_is_not_unsafe_scalar<int() noexcept>();
    test_is_not_unsafe_scalar<int()& noexcept>();
    test_is_not_unsafe_scalar<int()&& noexcept>();
    test_is_not_unsafe_scalar<int() const noexcept>();
    test_is_not_unsafe_scalar<int() const& noexcept>();
    test_is_not_unsafe_scalar<int() const&& noexcept>();
    test_is_not_unsafe_scalar<int() volatile noexcept>();
    test_is_not_unsafe_scalar<int() volatile& noexcept>();
    test_is_not_unsafe_scalar<int() volatile&& noexcept>();
    test_is_not_unsafe_scalar<int() const volatile noexcept>();
    test_is_not_unsafe_scalar<int() const volatile& noexcept>();
    test_is_not_unsafe_scalar<int() const volatile&& noexcept>();

    test_is_not_unsafe_scalar<int(int)>();
    test_is_not_unsafe_scalar<int(int)&>();
    test_is_not_unsafe_scalar<int(int) &&>();
    test_is_not_unsafe_scalar<int(int) const>();
    test_is_not_unsafe_scalar<int(int) const&>();
    test_is_not_unsafe_scalar<int(int) const&&>();
    test_is_not_unsafe_scalar<int(int) volatile>();
    test_is_not_unsafe_scalar<int(int) volatile&>();
    test_is_not_unsafe_scalar<int(int) volatile&&>();
    test_is_not_unsafe_scalar<int(int) const volatile>();
    test_is_not_unsafe_scalar<int(int) const volatile&>();
    test_is_not_unsafe_scalar<int(int) const volatile&&>();
    test_is_not_unsafe_scalar<int(int) noexcept>();
    test_is_not_unsafe_scalar<int(int)& noexcept>();
    test_is_not_unsafe_scalar<int(int)&& noexcept>();
    test_is_not_unsafe_scalar<int(int) const noexcept>();
    test_is_not_unsafe_scalar<int(int) const& noexcept>();
    test_is_not_unsafe_scalar<int(int) const&& noexcept>();
    test_is_not_unsafe_scalar<int(int) volatile noexcept>();
    test_is_not_unsafe_scalar<int(int) volatile& noexcept>();
    test_is_not_unsafe_scalar<int(int) volatile&& noexcept>();
    test_is_not_unsafe_scalar<int(int) const volatile noexcept>();
    test_is_not_unsafe_scalar<int(int) const volatile& noexcept>();
    test_is_not_unsafe_scalar<int(int) const volatile&& noexcept>();

    test_is_not_unsafe_scalar<int(...)>();
    test_is_not_unsafe_scalar<int(...)&>();
    test_is_not_unsafe_scalar<int(...) &&>();
    test_is_not_unsafe_scalar<int(...) const>();
    test_is_not_unsafe_scalar<int(...) const&>();
    test_is_not_unsafe_scalar<int(...) const&&>();
    test_is_not_unsafe_scalar<int(...) volatile>();
    test_is_not_unsafe_scalar<int(...) volatile&>();
    test_is_not_unsafe_scalar<int(...) volatile&&>();
    test_is_not_unsafe_scalar<int(...) const volatile>();
    test_is_not_unsafe_scalar<int(...) const volatile&>();
    test_is_not_unsafe_scalar<int(...) const volatile&&>();
    test_is_not_unsafe_scalar<int(...) noexcept>();
    test_is_not_unsafe_scalar<int(...)& noexcept>();
    test_is_not_unsafe_scalar<int(...)&& noexcept>();
    test_is_not_unsafe_scalar<int(...) const noexcept>();
    test_is_not_unsafe_scalar<int(...) const& noexcept>();
    test_is_not_unsafe_scalar<int(...) const&& noexcept>();
    test_is_not_unsafe_scalar<int(...) volatile noexcept>();
    test_is_not_unsafe_scalar<int(...) volatile& noexcept>();
    test_is_not_unsafe_scalar<int(...) volatile&& noexcept>();
    test_is_not_unsafe_scalar<int(...) const volatile noexcept>();
    test_is_not_unsafe_scalar<int(...) const volatile& noexcept>();
    test_is_not_unsafe_scalar<int(...) const volatile&& noexcept>();

    test_is_not_unsafe_scalar<int(int, ...)>();
    test_is_not_unsafe_scalar<int(int, ...)&>();
    test_is_not_unsafe_scalar<int(int, ...) &&>();
    test_is_not_unsafe_scalar<int(int, ...) const>();
    test_is_not_unsafe_scalar<int(int, ...) const&>();
    test_is_not_unsafe_scalar<int(int, ...) const&&>();
    test_is_not_unsafe_scalar<int(int, ...) volatile>();
    test_is_not_unsafe_scalar<int(int, ...) volatile&>();
    test_is_not_unsafe_scalar<int(int, ...) volatile&&>();
    test_is_not_unsafe_scalar<int(int, ...) const volatile>();
    test_is_not_unsafe_scalar<int(int, ...) const volatile&>();
    test_is_not_unsafe_scalar<int(int, ...) const volatile&&>();
    test_is_not_unsafe_scalar<int(int, ...) noexcept>();
    test_is_not_unsafe_scalar<int(int, ...)& noexcept>();
    test_is_not_unsafe_scalar<int(int, ...)&& noexcept>();
    test_is_not_unsafe_scalar<int(int, ...) const noexcept>();
    test_is_not_unsafe_scalar<int(int, ...) const& noexcept>();
    test_is_not_unsafe_scalar<int(int, ...) const&& noexcept>();
    test_is_not_unsafe_scalar<int(int, ...) volatile noexcept>();
    test_is_not_unsafe_scalar<int(int, ...) volatile& noexcept>();
    test_is_not_unsafe_scalar<int(int, ...) volatile&& noexcept>();
    test_is_not_unsafe_scalar<int(int, ...) const volatile noexcept>();
    test_is_not_unsafe_scalar<int(int, ...) const volatile& noexcept>();
    test_is_not_unsafe_scalar<int(int, ...) const volatile&& noexcept>();

    test_is_unsafe_scalar<void (*)()>();
    test_is_unsafe_scalar<void (*)() noexcept>();

    test_is_unsafe_scalar<void (*)(int)>();
    test_is_unsafe_scalar<void (*)(int) noexcept>();

    test_is_unsafe_scalar<void (*)(...)>();
    test_is_unsafe_scalar<void (*)(...) noexcept>();

    test_is_unsafe_scalar<void (*)(int, ...)>();
    test_is_unsafe_scalar<void (*)(int, ...) noexcept>();

    test_is_unsafe_scalar<int (*)()>();
    test_is_unsafe_scalar<int (*)() noexcept>();

    test_is_unsafe_scalar<int (*)(int)>();
    test_is_unsafe_scalar<int (*)(int) noexcept>();

    test_is_unsafe_scalar<int (*)(...)>();
    test_is_unsafe_scalar<int (*)(...) noexcept>();

    test_is_unsafe_scalar<int (*)(int, ...)>();
    test_is_unsafe_scalar<int (*)(int, ...) noexcept>();

    test_is_not_unsafe_scalar<void (&)()>();
    test_is_not_unsafe_scalar<void (&)() noexcept>();

    test_is_not_unsafe_scalar<void (&)(int)>();
    test_is_not_unsafe_scalar<void (&)(int) noexcept>();

    test_is_not_unsafe_scalar<void (&)(...)>();
    test_is_not_unsafe_scalar<void (&)(...) noexcept>();

    test_is_not_unsafe_scalar<void (&)(int, ...)>();
    test_is_not_unsafe_scalar<void (&)(int, ...) noexcept>();

    test_is_not_unsafe_scalar<int (&)()>();
    test_is_not_unsafe_scalar<int (&)() noexcept>();

    test_is_not_unsafe_scalar<int (&)(int)>();
    test_is_not_unsafe_scalar<int (&)(int) noexcept>();

    test_is_not_unsafe_scalar<int (&)(...)>();
    test_is_not_unsafe_scalar<int (&)(...) noexcept>();

    test_is_not_unsafe_scalar<int (&)(int, ...)>();
    test_is_not_unsafe_scalar<int (&)(int, ...) noexcept>();

    test_is_not_unsafe_scalar<void(&&)()>();
    test_is_not_unsafe_scalar<void(&&)() noexcept>();

    test_is_not_unsafe_scalar<void(&&)(int)>();
    test_is_not_unsafe_scalar<void(&&)(int) noexcept>();

    test_is_not_unsafe_scalar<void(&&)(...)>();
    test_is_not_unsafe_scalar<void(&&)(...) noexcept>();

    test_is_not_unsafe_scalar<void(&&)(int, ...)>();
    test_is_not_unsafe_scalar<void(&&)(int, ...) noexcept>();

    test_is_not_unsafe_scalar<int(&&)()>();
    test_is_not_unsafe_scalar<int(&&)() noexcept>();

    test_is_not_unsafe_scalar<int(&&)(int)>();
    test_is_not_unsafe_scalar<int(&&)(int) noexcept>();

    test_is_not_unsafe_scalar<int(&&)(...)>();
    test_is_not_unsafe_scalar<int(&&)(...) noexcept>();

    test_is_not_unsafe_scalar<int(&&)(int, ...)>();
    test_is_not_unsafe_scalar<int(&&)(int, ...) noexcept>();

    test_is_unsafe_scalar<void (Class::*)()>();
    test_is_unsafe_scalar<void (Class::*)()&>();
    test_is_unsafe_scalar<void (Class::*)() &&>();
    test_is_unsafe_scalar<void (Class::*)() const>();
    test_is_unsafe_scalar<void (Class::*)() const&>();
    test_is_unsafe_scalar<void (Class::*)() const&&>();
    test_is_unsafe_scalar<void (Class::*)() noexcept>();
    test_is_unsafe_scalar<void (Class::*)()& noexcept>();
    test_is_unsafe_scalar<void (Class::*)()&& noexcept>();
    test_is_unsafe_scalar<void (Class::*)() const noexcept>();
    test_is_unsafe_scalar<void (Class::*)() const& noexcept>();
    test_is_unsafe_scalar<void (Class::*)() const&& noexcept>();

    test_is_unsafe_scalar<void (Class::*)(int)>();
    test_is_unsafe_scalar<void (Class::*)(int)&>();
    test_is_unsafe_scalar<void (Class::*)(int) &&>();
    test_is_unsafe_scalar<void (Class::*)(int) const>();
    test_is_unsafe_scalar<void (Class::*)(int) const&>();
    test_is_unsafe_scalar<void (Class::*)(int) const&&>();
    test_is_unsafe_scalar<void (Class::*)(int) noexcept>();
    test_is_unsafe_scalar<void (Class::*)(int)& noexcept>();
    test_is_unsafe_scalar<void (Class::*)(int)&& noexcept>();
    test_is_unsafe_scalar<void (Class::*)(int) const noexcept>();
    test_is_unsafe_scalar<void (Class::*)(int) const& noexcept>();
    test_is_unsafe_scalar<void (Class::*)(int) const&& noexcept>();

    test_is_unsafe_scalar<void (Class::*)(...)>();
    test_is_unsafe_scalar<void (Class::*)(...)&>();
    test_is_unsafe_scalar<void (Class::*)(...) &&>();
    test_is_unsafe_scalar<void (Class::*)(...) const>();
    test_is_unsafe_scalar<void (Class::*)(...) const&>();
    test_is_unsafe_scalar<void (Class::*)(...) const&&>();
    test_is_unsafe_scalar<void (Class::*)(...) noexcept>();
    test_is_unsafe_scalar<void (Class::*)(...)& noexcept>();
    test_is_unsafe_scalar<void (Class::*)(...)&& noexcept>();
    test_is_unsafe_scalar<void (Class::*)(...) const noexcept>();
    test_is_unsafe_scalar<void (Class::*)(...) const& noexcept>();
    test_is_unsafe_scalar<void (Class::*)(...) const&& noexcept>();

    test_is_unsafe_scalar<void (Class::*)(int, ...)>();
    test_is_unsafe_scalar<void (Class::*)(int, ...)&>();
    test_is_unsafe_scalar<void (Class::*)(int, ...) &&>();
    test_is_unsafe_scalar<void (Class::*)(int, ...) const>();
    test_is_unsafe_scalar<void (Class::*)(int, ...) const&>();
    test_is_unsafe_scalar<void (Class::*)(int, ...) const&&>();
    test_is_unsafe_scalar<void (Class::*)(int, ...) noexcept>();
    test_is_unsafe_scalar<void (Class::*)(int, ...)& noexcept>();
    test_is_unsafe_scalar<void (Class::*)(int, ...)&& noexcept>();
    test_is_unsafe_scalar<void (Class::*)(int, ...) const noexcept>();
    test_is_unsafe_scalar<void (Class::*)(int, ...) const& noexcept>();
    test_is_unsafe_scalar<void (Class::*)(int, ...) const&& noexcept>();

    test_is_unsafe_scalar<int (Class::*)()>();
    test_is_unsafe_scalar<int (Class::*)()&>();
    test_is_unsafe_scalar<int (Class::*)() &&>();
    test_is_unsafe_scalar<int (Class::*)() const>();
    test_is_unsafe_scalar<int (Class::*)() const&>();
    test_is_unsafe_scalar<int (Class::*)() const&&>();
    test_is_unsafe_scalar<int (Class::*)() noexcept>();
    test_is_unsafe_scalar<int (Class::*)()& noexcept>();
    test_is_unsafe_scalar<int (Class::*)()&& noexcept>();
    test_is_unsafe_scalar<int (Class::*)() const noexcept>();
    test_is_unsafe_scalar<int (Class::*)() const& noexcept>();
    test_is_unsafe_scalar<int (Class::*)() const&& noexcept>();

    test_is_unsafe_scalar<int (Class::*)(int)>();
    test_is_unsafe_scalar<int (Class::*)(int)&>();
    test_is_unsafe_scalar<int (Class::*)(int) &&>();
    test_is_unsafe_scalar<int (Class::*)(int) const>();
    test_is_unsafe_scalar<int (Class::*)(int) const&>();
    test_is_unsafe_scalar<int (Class::*)(int) const&&>();
    test_is_unsafe_scalar<int (Class::*)(int) noexcept>();
    test_is_unsafe_scalar<int (Class::*)(int)& noexcept>();
    test_is_unsafe_scalar<int (Class::*)(int)&& noexcept>();
    test_is_unsafe_scalar<int (Class::*)(int) const noexcept>();
    test_is_unsafe_scalar<int (Class::*)(int) const& noexcept>();
    test_is_unsafe_scalar<int (Class::*)(int) const&& noexcept>();

    test_is_unsafe_scalar<int (Class::*)(...)>();
    test_is_unsafe_scalar<int (Class::*)(...)&>();
    test_is_unsafe_scalar<int (Class::*)(...) &&>();
    test_is_unsafe_scalar<int (Class::*)(...) const>();
    test_is_unsafe_scalar<int (Class::*)(...) const&>();
    test_is_unsafe_scalar<int (Class::*)(...) const&&>();
    test_is_unsafe_scalar<int (Class::*)(...) noexcept>();
    test_is_unsafe_scalar<int (Class::*)(...)& noexcept>();
    test_is_unsafe_scalar<int (Class::*)(...)&& noexcept>();
    test_is_unsafe_scalar<int (Class::*)(...) const noexcept>();
    test_is_unsafe_scalar<int (Class::*)(...) const& noexcept>();
    test_is_unsafe_scalar<int (Class::*)(...) const&& noexcept>();

    test_is_unsafe_scalar<int (Class::*)(int, ...)>();
    test_is_unsafe_scalar<int (Class::*)(int, ...)&>();
    test_is_unsafe_scalar<int (Class::*)(int, ...) &&>();
    test_is_unsafe_scalar<int (Class::*)(int, ...) const>();
    test_is_unsafe_scalar<int (Class::*)(int, ...) const&>();
    test_is_unsafe_scalar<int (Class::*)(int, ...) const&&>();
    test_is_unsafe_scalar<int (Class::*)(int, ...) noexcept>();
    test_is_unsafe_scalar<int (Class::*)(int, ...)& noexcept>();
    test_is_unsafe_scalar<int (Class::*)(int, ...)&& noexcept>();
    test_is_unsafe_scalar<int (Class::*)(int, ...) const noexcept>();
    test_is_unsafe_scalar<int (Class::*)(int, ...) const& noexcept>();
    test_is_unsafe_scalar<int (Class::*)(int, ...) const&& noexcept>();
}
