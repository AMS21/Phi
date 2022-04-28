#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/integral_constant.hpp>
#include <phi/type_traits/is_same_rcv.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_is_same_rcv_impl()
{
    STATIC_REQUIRE(phi::is_same_rcv<T, U>::value);
    STATIC_REQUIRE(phi::is_same_rcv<U, T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rcv_v<T, U>);
    STATIC_REQUIRE(phi::is_same_rcv_v<U, T>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcv_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rcv<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rcv<T, U>);
}

template <typename T, typename U>
void test_is_not_same_rcv()
{
    STATIC_REQUIRE_FALSE(phi::is_same_rcv<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rcv<U, T>::value);
    STATIC_REQUIRE(phi::is_not_same_rcv<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rcv<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_rcv_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rcv_v<U, T>);
    STATIC_REQUIRE(phi::is_not_same_rcv_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_rcv_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rcv<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rcv<T, U>);
}

template <typename T, typename U = T>
void test_is_same_rcv()
{
    test_is_same_rcv_impl<T, U>();
    test_is_same_rcv_impl<T, const U>();
    test_is_same_rcv_impl<T, volatile U>();
    test_is_same_rcv_impl<T, const volatile U>();

    test_is_same_rcv_impl<const T, U>();
    test_is_same_rcv_impl<const T, const U>();
    test_is_same_rcv_impl<const T, volatile U>();
    test_is_same_rcv_impl<const T, const volatile U>();

    test_is_same_rcv_impl<volatile T, U>();
    test_is_same_rcv_impl<volatile T, const U>();
    test_is_same_rcv_impl<volatile T, volatile U>();
    test_is_same_rcv_impl<volatile T, const volatile U>();

    test_is_same_rcv_impl<const volatile T, U>();
    test_is_same_rcv_impl<const volatile T, const U>();
    test_is_same_rcv_impl<const volatile T, volatile U>();
    test_is_same_rcv_impl<const volatile T, const volatile U>();
}

template <typename T>
struct OverloadTest
{
    void fn(phi::is_same_rcv<T, int>)
    {}
    void fn(phi::false_type)
    {}
    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same_rcv")
{
    test_is_not_same_rcv<int, void>();
    test_is_not_same_rcv<void, Class>();
    test_is_not_same_rcv<Class, int*>();
    test_is_not_same_rcv<int*, int&>();
    test_is_not_same_rcv<int&, int>();

    test_is_not_same_rcv<int, int&>();
    test_is_not_same_rcv<int, const int&>();
    test_is_not_same_rcv<int, volatile int&>();
    test_is_not_same_rcv<int, const volatile int&>();
    test_is_not_same_rcv<int, int&&>();
    test_is_not_same_rcv<int, const int&&>();
    test_is_not_same_rcv<int, volatile int&&>();
    test_is_not_same_rcv<int, const volatile int&&>();

    OverloadTest<char> t;
    (void)t;

    test_is_same_rcv<void>();
    test_is_same_rcv<phi::nullptr_t>();
    test_is_same_rcv<bool>();
    test_is_same_rcv<char>();
    test_is_same_rcv<signed char>();
    test_is_same_rcv<unsigned char>();
    test_is_same_rcv<short>();
    test_is_same_rcv<unsigned short>();
    test_is_same_rcv<int>();
    test_is_same_rcv<unsigned int>();
    test_is_same_rcv<long>();
    test_is_same_rcv<unsigned long>();
    test_is_same_rcv<long long>();
    test_is_same_rcv<unsigned long long>();
    test_is_same_rcv<float>();
    test_is_same_rcv<double>();
    test_is_same_rcv<long double>();
    test_is_same_rcv<char8_t>();
    test_is_same_rcv<char16_t>();
    test_is_same_rcv<char32_t>();
    test_is_same_rcv<wchar_t>();

    test_is_same_rcv<phi::boolean>();
    test_is_same_rcv<phi::integer<signed char>>();
    test_is_same_rcv<phi::integer<unsigned char>>();
    test_is_same_rcv<phi::integer<short>>();
    test_is_same_rcv<phi::integer<unsigned short>>();
    test_is_same_rcv<phi::integer<int>>();
    test_is_same_rcv<phi::integer<unsigned int>>();
    test_is_same_rcv<phi::integer<long>>();
    test_is_same_rcv<phi::integer<unsigned long>>();
    test_is_same_rcv<phi::integer<long long>>();
    test_is_same_rcv<phi::integer<unsigned long long>>();
    test_is_same_rcv<phi::floating_point<float>>();
    test_is_same_rcv<phi::floating_point<double>>();
    test_is_same_rcv<phi::floating_point<long double>>();

    test_is_same_rcv<std::vector<int>>();
    test_is_same_rcv<phi::scope_ptr<int>>();

    test_is_same_rcv<int&>();
    test_is_same_rcv<const int&>();
    test_is_same_rcv<volatile int&>();
    test_is_same_rcv<const volatile int&>();
    test_is_same_rcv<int&&>();
    test_is_same_rcv<const int&&>();
    test_is_same_rcv<volatile int&&>();
    test_is_same_rcv<const volatile int&&>();
    test_is_same_rcv<int*>();
    test_is_same_rcv<const int*>();
    test_is_same_rcv<volatile int*>();
    test_is_same_rcv<const volatile int*>();
    test_is_same_rcv<int**>();
    test_is_same_rcv<const int**>();
    test_is_same_rcv<volatile int**>();
    test_is_same_rcv<const volatile int**>();
    test_is_same_rcv<int*&>();
    test_is_same_rcv<const int*&>();
    test_is_same_rcv<volatile int*&>();
    test_is_same_rcv<const volatile int*&>();
    test_is_same_rcv<int*&&>();
    test_is_same_rcv<const int*&&>();
    test_is_same_rcv<volatile int*&&>();
    test_is_same_rcv<const volatile int*&&>();
    test_is_same_rcv<void*>();
    test_is_same_rcv<char[3]>();
    test_is_same_rcv<char[]>();
    test_is_same_rcv<char* [3]>();
    test_is_same_rcv<char*[]>();
    test_is_same_rcv<int(*)[3]>();
    test_is_same_rcv<int(*)[]>();
    test_is_same_rcv<int(&)[3]>();
    test_is_same_rcv<int(&)[]>();
    test_is_same_rcv<int(&&)[3]>();
    test_is_same_rcv<int(&&)[]>();
    test_is_same_rcv<char[3][2]>();
    test_is_same_rcv<char[][2]>();
    test_is_same_rcv<char* [3][2]>();
    test_is_same_rcv<char*[][2]>();
    test_is_same_rcv<int(*)[3][2]>();
    test_is_same_rcv<int(*)[][2]>();
    test_is_same_rcv<int(&)[3][2]>();
    test_is_same_rcv<int(&)[][2]>();
    test_is_same_rcv<int(&&)[3][2]>();
    test_is_same_rcv<int(&&)[][2]>();
    test_is_same_rcv<Class>();
    test_is_same_rcv<Class[]>();
    test_is_same_rcv<Class[2]>();
    test_is_same_rcv<Template<void>>();
    test_is_same_rcv<Template<int>>();
    test_is_same_rcv<Template<Class>>();
    test_is_same_rcv<Template<IncompleteType>>();
    test_is_same_rcv<VariadicTemplate<>>();
    test_is_same_rcv<VariadicTemplate<void>>();
    test_is_same_rcv<VariadicTemplate<int>>();
    test_is_same_rcv<VariadicTemplate<Class>>();
    test_is_same_rcv<VariadicTemplate<IncompleteType>>();
    test_is_same_rcv<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_same_rcv<PublicDerivedFromTemplate<Base>>();
    test_is_same_rcv<PublicDerivedFromTemplate<Derived>>();
    test_is_same_rcv<PublicDerivedFromTemplate<Class>>();
    test_is_same_rcv<PrivateDerivedFromTemplate<Base>>();
    test_is_same_rcv<PrivateDerivedFromTemplate<Derived>>();
    test_is_same_rcv<PrivateDerivedFromTemplate<Class>>();
    test_is_same_rcv<ProtectedDerivedFromTemplate<Base>>();
    test_is_same_rcv<ProtectedDerivedFromTemplate<Derived>>();
    test_is_same_rcv<ProtectedDerivedFromTemplate<Class>>();
    test_is_same_rcv<VirtualDerivedFromTemplate<Base>>();
    test_is_same_rcv<VirtualDerivedFromTemplate<Derived>>();
    test_is_same_rcv<VirtualDerivedFromTemplate<Class>>();
    test_is_same_rcv<Union>();
    test_is_same_rcv<NonEmptyUnion>();
    test_is_same_rcv<NonTrivialUnion>();
    test_is_same_rcv<Empty>();
    test_is_same_rcv<NotEmpty>();
    test_is_same_rcv<NonTrivial>();
    test_is_same_rcv<BitZero>();
    test_is_same_rcv<BitOne>();
    test_is_same_rcv<Base>();
    test_is_same_rcv<Derived>();
    test_is_same_rcv<NotEmptyBase>();
    test_is_same_rcv<EmptyBase>();
    test_is_same_rcv<VirtualBase>();
    test_is_same_rcv<Polymorphic>();
    test_is_same_rcv<DerivedPolymorphic>();
    test_is_same_rcv<Abstract>();
    test_is_same_rcv<PublicAbstract>();
    test_is_same_rcv<PrivateAbstract>();
    test_is_same_rcv<ProtectedAbstract>();
    test_is_same_rcv<AbstractTemplate<int>>();
    test_is_same_rcv<AbstractTemplate<double>>();
    test_is_same_rcv<AbstractTemplate<Class>>();
    test_is_same_rcv<AbstractTemplate<IncompleteType>>();
    test_is_same_rcv<PublicAbstractDeletedDestructor>();
    test_is_same_rcv<ProtectedAbstractDeletedDestructor>();
    test_is_same_rcv<PrivateAbstractDeletedDestructor>();
    test_is_same_rcv<Final>();
    test_is_same_rcv<FinalDerived>();
    test_is_same_rcv<PublicDestructor>();
    test_is_same_rcv<ProtectedDestructor>();
    test_is_same_rcv<PrivateDestructor>();
    test_is_same_rcv<VirtualPublicDestructor>();
    test_is_same_rcv<VirtualProtectedDestructor>();
    test_is_same_rcv<VirtualPrivateDestructor>();
    test_is_same_rcv<PurePublicDestructor>();
    test_is_same_rcv<PureProtectedDestructor>();
    test_is_same_rcv<PurePrivateDestructor>();
    test_is_same_rcv<DeletedPublicDestructor>();
    test_is_same_rcv<DeletedProtectedDestructor>();
    test_is_same_rcv<DeletedPrivateDestructor>();
    test_is_same_rcv<DeletedVirtualPublicDestructor>();
    test_is_same_rcv<DeletedVirtualProtectedDestructor>();
    test_is_same_rcv<DeletedVirtualPrivateDestructor>();
    test_is_same_rcv<ExplicitClass>();
    test_is_same_rcv<NothrowExplicitClass>();
    test_is_same_rcv<ThrowExplicitClass>();
    test_is_same_rcv<ThrowDefaultClass>();
    test_is_same_rcv<ThrowCopyConsClass>();
    test_is_same_rcv<ThrowMoveConsClass>();
    test_is_same_rcv<ThrowDestructor>();
    test_is_same_rcv<NoexceptExplicitClass>();
    test_is_same_rcv<ExceptExplicitClass>();
    test_is_same_rcv<NoexceptDefaultClass>();
    test_is_same_rcv<ExceptDefaultClass>();
    test_is_same_rcv<NoexceptCopyConsClass>();
    test_is_same_rcv<ExceptCopyConsClass>();
    test_is_same_rcv<NoexceptMoveConsClass>();
    test_is_same_rcv<ExceptMoveConsClass>();
    test_is_same_rcv<NoexceptCopyAssignClass>();
    test_is_same_rcv<ExceptCopyAssignClass>();
    test_is_same_rcv<NoexceptMoveAssignClass>();
    test_is_same_rcv<ExceptMoveAssignClass>();
    test_is_same_rcv<DeletedCopyAssignClass>();
    test_is_same_rcv<DeletedMoveAssignClass>();
    test_is_same_rcv<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_same_rcv<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_same_rcv<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_same_rcv<ExceptMoveConsExceptMoveAssignClass>();
    test_is_same_rcv<ImplicitTo<int>>();
    test_is_same_rcv<ImplicitTo<float>>();
    test_is_same_rcv<ImplicitTo<Class>>();
    test_is_same_rcv<DeletedImplicitTo<int>>();
    test_is_same_rcv<DeletedImplicitTo<float>>();
    test_is_same_rcv<DeletedImplicitTo<Class>>();
    test_is_same_rcv<ExplicitTo<int>>();
    test_is_same_rcv<ExplicitTo<float>>();
    test_is_same_rcv<ExplicitTo<Class>>();
    test_is_same_rcv<DeletedExplicitTo<int>>();
    test_is_same_rcv<DeletedExplicitTo<float>>();
    test_is_same_rcv<DeletedExplicitTo<Class>>();
    test_is_same_rcv<Ellipsis>();
    test_is_same_rcv<DeletedEllipsis>();
    test_is_same_rcv<CopyConsOnlyType>();
    test_is_same_rcv<MoveConsOnlyType>();
    test_is_same_rcv<OverloadedOperators>();
    test_is_same_rcv<PublicIntMember>();
    test_is_same_rcv<ProtectedIntMember>();
    test_is_same_rcv<PrivateIntMember>();
    test_is_same_rcv<PublicStaticIntMember>();
    test_is_same_rcv<ProtectedStaticIntMember>();
    test_is_same_rcv<PrivateStaticIntMember>();
    test_is_same_rcv<PublicTemplateMember<int>>();
    test_is_same_rcv<PublicTemplateMember<float>>();
    test_is_same_rcv<PublicTemplateMember<Class>>();
    test_is_same_rcv<ProtectedTemplateMember<int>>();
    test_is_same_rcv<ProtectedTemplateMember<float>>();
    test_is_same_rcv<ProtectedTemplateMember<Class>>();
    test_is_same_rcv<PrivateTemplateMember<int>>();
    test_is_same_rcv<PrivateTemplateMember<float>>();
    test_is_same_rcv<PrivateTemplateMember<Class>>();
    test_is_same_rcv<PublicStaticTemplateMember<int>>();
    test_is_same_rcv<PublicStaticTemplateMember<float>>();
    test_is_same_rcv<PublicStaticTemplateMember<Class>>();
    test_is_same_rcv<ProtectedStaticTemplateMember<int>>();
    test_is_same_rcv<ProtectedStaticTemplateMember<float>>();
    test_is_same_rcv<ProtectedStaticTemplateMember<Class>>();
    test_is_same_rcv<PrivateStaticTemplateMember<int>>();
    test_is_same_rcv<PrivateStaticTemplateMember<float>>();
    test_is_same_rcv<PrivateStaticTemplateMember<Class>>();
    test_is_same_rcv<CannotInstantiate<int>>();
    test_is_same_rcv<CannotInstantiate<float>>();
    test_is_same_rcv<CannotInstantiate<Class>>();
    test_is_same_rcv<natural_alignment>();
    test_is_same_rcv<Enum>();
    test_is_same_rcv<EnumSigned>();
    test_is_same_rcv<EnumUnsigned>();
    test_is_same_rcv<EnumClass>();
    test_is_same_rcv<EnumStruct>();
    test_is_same_rcv<Function>();
    test_is_same_rcv<FunctionPtr>();
    test_is_same_rcv<MemberObjectPtr>();
    test_is_same_rcv<MemberFunctionPtr>();
    test_is_same_rcv<LambdaType>();
    test_is_same_rcv<LambdaNoexceptType>();
    test_is_same_rcv<LambdaThrowsType>();
    test_is_same_rcv<IncompleteType>();
    test_is_same_rcv<IncompleteTemplate<void>>();
    test_is_same_rcv<IncompleteTemplate<int>>();
    test_is_same_rcv<IncompleteTemplate<Class>>();
    test_is_same_rcv<IncompleteTemplate<IncompleteType>>();
    test_is_same_rcv<IncompleteVariadicTemplate<>>();
    test_is_same_rcv<IncompleteVariadicTemplate<void>>();
    test_is_same_rcv<IncompleteVariadicTemplate<int>>();
    test_is_same_rcv<IncompleteVariadicTemplate<Class>>();
    test_is_same_rcv<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_same_rcv<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_same_rcv<IncompleteUnion>();
    test_is_same_rcv<IncompleteEnumSigned>();
    test_is_same_rcv<IncompleteEnumUnsigned>();
    test_is_same_rcv<IncompleteEnumClass>();
    test_is_same_rcv<IncompleteEnumStruct>();
    test_is_same_rcv<int Class::*>();
    test_is_same_rcv<float Class::*>();
    test_is_same_rcv<void * Class::*>();
    test_is_same_rcv<int * Class::*>();
    test_is_same_rcv<Enum Class::*>();
    test_is_same_rcv<NotEmpty Class::*>();
    test_is_same_rcv<int Class::*&>();
    test_is_same_rcv<float Class::*&>();
    test_is_same_rcv<void * Class::*&>();
    test_is_same_rcv<int * Class::*&>();
    test_is_same_rcv<Enum Class::*&>();
    test_is_same_rcv<NotEmpty Class::*&>();
    test_is_same_rcv<int Class::*&&>();
    test_is_same_rcv<float Class::*&&>();
    test_is_same_rcv<void * Class::*&&>();
    test_is_same_rcv<int * Class::*&&>();
    test_is_same_rcv<Enum Class::*&&>();
    test_is_same_rcv<NotEmpty Class::*&&>();
    test_is_same_rcv<NonDefaultConstructible>();
    test_is_same_rcv<NonCopyConstructible>();
    test_is_same_rcv<NonMoveConstructible>();
    test_is_same_rcv<NonCopyAssignable>();
    test_is_same_rcv<NonMoveAssignable>();
    test_is_same_rcv<NonAssignable>();
    test_is_same_rcv<NonCopyable>();
    test_is_same_rcv<NonMoveable>();
    test_is_same_rcv<NonConstructible>();
    test_is_same_rcv<NonDestructible>();
    test_is_same_rcv<Tracked>();
    test_is_same_rcv<TrapConstructible>();
    test_is_same_rcv<TrapImplicitConversion>();
    test_is_same_rcv<TrapComma>();
    test_is_same_rcv<TrapCall>();
    test_is_same_rcv<TrapSelfAssign>();
    test_is_same_rcv<TrapDeref>();
    test_is_same_rcv<TrapArraySubscript>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY()
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_is_same_rcv<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_is_same_rcv<void()>();
    test_is_same_rcv<void()&>();
    test_is_same_rcv<void() &&>();
    test_is_same_rcv<void() const>();
    test_is_same_rcv<void() const&>();
    test_is_same_rcv<void() const&&>();
    test_is_same_rcv<void() volatile>();
    test_is_same_rcv<void() volatile&>();
    test_is_same_rcv<void() volatile&&>();
    test_is_same_rcv<void() const volatile>();
    test_is_same_rcv<void() const volatile&>();
    test_is_same_rcv<void() const volatile&&>();
    test_is_same_rcv<void() noexcept>();
    test_is_same_rcv<void()& noexcept>();
    test_is_same_rcv<void()&& noexcept>();
    test_is_same_rcv<void() const noexcept>();
    test_is_same_rcv<void() const& noexcept>();
    test_is_same_rcv<void() const&& noexcept>();
    test_is_same_rcv<void() volatile noexcept>();
    test_is_same_rcv<void() volatile& noexcept>();
    test_is_same_rcv<void() volatile&& noexcept>();
    test_is_same_rcv<void() const volatile noexcept>();
    test_is_same_rcv<void() const volatile& noexcept>();
    test_is_same_rcv<void() const volatile&& noexcept>();

    test_is_same_rcv<void(int)>();
    test_is_same_rcv<void(int)&>();
    test_is_same_rcv<void(int) &&>();
    test_is_same_rcv<void(int) const>();
    test_is_same_rcv<void(int) const&>();
    test_is_same_rcv<void(int) const&&>();
    test_is_same_rcv<void(int) volatile>();
    test_is_same_rcv<void(int) volatile&>();
    test_is_same_rcv<void(int) volatile&&>();
    test_is_same_rcv<void(int) const volatile>();
    test_is_same_rcv<void(int) const volatile&>();
    test_is_same_rcv<void(int) const volatile&&>();
    test_is_same_rcv<void(int) noexcept>();
    test_is_same_rcv<void(int)& noexcept>();
    test_is_same_rcv<void(int)&& noexcept>();
    test_is_same_rcv<void(int) const noexcept>();
    test_is_same_rcv<void(int) const& noexcept>();
    test_is_same_rcv<void(int) const&& noexcept>();
    test_is_same_rcv<void(int) volatile noexcept>();
    test_is_same_rcv<void(int) volatile& noexcept>();
    test_is_same_rcv<void(int) volatile&& noexcept>();
    test_is_same_rcv<void(int) const volatile noexcept>();
    test_is_same_rcv<void(int) const volatile& noexcept>();
    test_is_same_rcv<void(int) const volatile&& noexcept>();

    test_is_same_rcv<void(...)>();
    test_is_same_rcv<void(...)&>();
    test_is_same_rcv<void(...) &&>();
    test_is_same_rcv<void(...) const>();
    test_is_same_rcv<void(...) const&>();
    test_is_same_rcv<void(...) const&&>();
    test_is_same_rcv<void(...) volatile>();
    test_is_same_rcv<void(...) volatile&>();
    test_is_same_rcv<void(...) volatile&&>();
    test_is_same_rcv<void(...) const volatile>();
    test_is_same_rcv<void(...) const volatile&>();
    test_is_same_rcv<void(...) const volatile&&>();
    test_is_same_rcv<void(...) noexcept>();
    test_is_same_rcv<void(...)& noexcept>();
    test_is_same_rcv<void(...)&& noexcept>();
    test_is_same_rcv<void(...) const noexcept>();
    test_is_same_rcv<void(...) const& noexcept>();
    test_is_same_rcv<void(...) const&& noexcept>();
    test_is_same_rcv<void(...) volatile noexcept>();
    test_is_same_rcv<void(...) volatile& noexcept>();
    test_is_same_rcv<void(...) volatile&& noexcept>();
    test_is_same_rcv<void(...) const volatile noexcept>();
    test_is_same_rcv<void(...) const volatile& noexcept>();
    test_is_same_rcv<void(...) const volatile&& noexcept>();

    test_is_same_rcv<void(int, ...)>();
    test_is_same_rcv<void(int, ...)&>();
    test_is_same_rcv<void(int, ...) &&>();
    test_is_same_rcv<void(int, ...) const>();
    test_is_same_rcv<void(int, ...) const&>();
    test_is_same_rcv<void(int, ...) const&&>();
    test_is_same_rcv<void(int, ...) volatile>();
    test_is_same_rcv<void(int, ...) volatile&>();
    test_is_same_rcv<void(int, ...) volatile&&>();
    test_is_same_rcv<void(int, ...) const volatile>();
    test_is_same_rcv<void(int, ...) const volatile&>();
    test_is_same_rcv<void(int, ...) const volatile&&>();
    test_is_same_rcv<void(int, ...) noexcept>();
    test_is_same_rcv<void(int, ...)& noexcept>();
    test_is_same_rcv<void(int, ...)&& noexcept>();
    test_is_same_rcv<void(int, ...) const noexcept>();
    test_is_same_rcv<void(int, ...) const& noexcept>();
    test_is_same_rcv<void(int, ...) const&& noexcept>();
    test_is_same_rcv<void(int, ...) volatile noexcept>();
    test_is_same_rcv<void(int, ...) volatile& noexcept>();
    test_is_same_rcv<void(int, ...) volatile&& noexcept>();
    test_is_same_rcv<void(int, ...) const volatile noexcept>();
    test_is_same_rcv<void(int, ...) const volatile& noexcept>();
    test_is_same_rcv<void(int, ...) const volatile&& noexcept>();

    test_is_same_rcv<int()>();
    test_is_same_rcv<int()&>();
    test_is_same_rcv<int() &&>();
    test_is_same_rcv<int() const>();
    test_is_same_rcv<int() const&>();
    test_is_same_rcv<int() const&&>();
    test_is_same_rcv<int() volatile>();
    test_is_same_rcv<int() volatile&>();
    test_is_same_rcv<int() volatile&&>();
    test_is_same_rcv<int() const volatile>();
    test_is_same_rcv<int() const volatile&>();
    test_is_same_rcv<int() const volatile&&>();
    test_is_same_rcv<int() noexcept>();
    test_is_same_rcv<int()& noexcept>();
    test_is_same_rcv<int()&& noexcept>();
    test_is_same_rcv<int() const noexcept>();
    test_is_same_rcv<int() const& noexcept>();
    test_is_same_rcv<int() const&& noexcept>();
    test_is_same_rcv<int() volatile noexcept>();
    test_is_same_rcv<int() volatile& noexcept>();
    test_is_same_rcv<int() volatile&& noexcept>();
    test_is_same_rcv<int() const volatile noexcept>();
    test_is_same_rcv<int() const volatile& noexcept>();
    test_is_same_rcv<int() const volatile&& noexcept>();

    test_is_same_rcv<int(int)>();
    test_is_same_rcv<int(int)&>();
    test_is_same_rcv<int(int) &&>();
    test_is_same_rcv<int(int) const>();
    test_is_same_rcv<int(int) const&>();
    test_is_same_rcv<int(int) const&&>();
    test_is_same_rcv<int(int) volatile>();
    test_is_same_rcv<int(int) volatile&>();
    test_is_same_rcv<int(int) volatile&&>();
    test_is_same_rcv<int(int) const volatile>();
    test_is_same_rcv<int(int) const volatile&>();
    test_is_same_rcv<int(int) const volatile&&>();
    test_is_same_rcv<int(int) noexcept>();
    test_is_same_rcv<int(int)& noexcept>();
    test_is_same_rcv<int(int)&& noexcept>();
    test_is_same_rcv<int(int) const noexcept>();
    test_is_same_rcv<int(int) const& noexcept>();
    test_is_same_rcv<int(int) const&& noexcept>();
    test_is_same_rcv<int(int) volatile noexcept>();
    test_is_same_rcv<int(int) volatile& noexcept>();
    test_is_same_rcv<int(int) volatile&& noexcept>();
    test_is_same_rcv<int(int) const volatile noexcept>();
    test_is_same_rcv<int(int) const volatile& noexcept>();
    test_is_same_rcv<int(int) const volatile&& noexcept>();

    test_is_same_rcv<int(...)>();
    test_is_same_rcv<int(...)&>();
    test_is_same_rcv<int(...) &&>();
    test_is_same_rcv<int(...) const>();
    test_is_same_rcv<int(...) const&>();
    test_is_same_rcv<int(...) const&&>();
    test_is_same_rcv<int(...) volatile>();
    test_is_same_rcv<int(...) volatile&>();
    test_is_same_rcv<int(...) volatile&&>();
    test_is_same_rcv<int(...) const volatile>();
    test_is_same_rcv<int(...) const volatile&>();
    test_is_same_rcv<int(...) const volatile&&>();
    test_is_same_rcv<int(...) noexcept>();
    test_is_same_rcv<int(...)& noexcept>();
    test_is_same_rcv<int(...)&& noexcept>();
    test_is_same_rcv<int(...) const noexcept>();
    test_is_same_rcv<int(...) const& noexcept>();
    test_is_same_rcv<int(...) const&& noexcept>();
    test_is_same_rcv<int(...) volatile noexcept>();
    test_is_same_rcv<int(...) volatile& noexcept>();
    test_is_same_rcv<int(...) volatile&& noexcept>();
    test_is_same_rcv<int(...) const volatile noexcept>();
    test_is_same_rcv<int(...) const volatile& noexcept>();
    test_is_same_rcv<int(...) const volatile&& noexcept>();

    test_is_same_rcv<int(int, ...)>();
    test_is_same_rcv<int(int, ...)&>();
    test_is_same_rcv<int(int, ...) &&>();
    test_is_same_rcv<int(int, ...) const>();
    test_is_same_rcv<int(int, ...) const&>();
    test_is_same_rcv<int(int, ...) const&&>();
    test_is_same_rcv<int(int, ...) volatile>();
    test_is_same_rcv<int(int, ...) volatile&>();
    test_is_same_rcv<int(int, ...) volatile&&>();
    test_is_same_rcv<int(int, ...) const volatile>();
    test_is_same_rcv<int(int, ...) const volatile&>();
    test_is_same_rcv<int(int, ...) const volatile&&>();
    test_is_same_rcv<int(int, ...) noexcept>();
    test_is_same_rcv<int(int, ...)& noexcept>();
    test_is_same_rcv<int(int, ...)&& noexcept>();
    test_is_same_rcv<int(int, ...) const noexcept>();
    test_is_same_rcv<int(int, ...) const& noexcept>();
    test_is_same_rcv<int(int, ...) const&& noexcept>();
    test_is_same_rcv<int(int, ...) volatile noexcept>();
    test_is_same_rcv<int(int, ...) volatile& noexcept>();
    test_is_same_rcv<int(int, ...) volatile&& noexcept>();
    test_is_same_rcv<int(int, ...) const volatile noexcept>();
    test_is_same_rcv<int(int, ...) const volatile& noexcept>();
    test_is_same_rcv<int(int, ...) const volatile&& noexcept>();

    test_is_same_rcv<void (*)()>();
    test_is_same_rcv<void (*)() noexcept>();

    test_is_same_rcv<void (*)(int)>();
    test_is_same_rcv<void (*)(int) noexcept>();

    test_is_same_rcv<void (*)(...)>();
    test_is_same_rcv<void (*)(...) noexcept>();

    test_is_same_rcv<void (*)(int, ...)>();
    test_is_same_rcv<void (*)(int, ...) noexcept>();

    test_is_same_rcv<int (*)()>();
    test_is_same_rcv<int (*)() noexcept>();

    test_is_same_rcv<int (*)(int)>();
    test_is_same_rcv<int (*)(int) noexcept>();

    test_is_same_rcv<int (*)(...)>();
    test_is_same_rcv<int (*)(...) noexcept>();

    test_is_same_rcv<int (*)(int, ...)>();
    test_is_same_rcv<int (*)(int, ...) noexcept>();

    test_is_same_rcv<void (&)()>();
    test_is_same_rcv<void (&)() noexcept>();

    test_is_same_rcv<void (&)(int)>();
    test_is_same_rcv<void (&)(int) noexcept>();

    test_is_same_rcv<void (&)(...)>();
    test_is_same_rcv<void (&)(...) noexcept>();

    test_is_same_rcv<void (&)(int, ...)>();
    test_is_same_rcv<void (&)(int, ...) noexcept>();

    test_is_same_rcv<int (&)()>();
    test_is_same_rcv<int (&)() noexcept>();

    test_is_same_rcv<int (&)(int)>();
    test_is_same_rcv<int (&)(int) noexcept>();

    test_is_same_rcv<int (&)(...)>();
    test_is_same_rcv<int (&)(...) noexcept>();

    test_is_same_rcv<int (&)(int, ...)>();
    test_is_same_rcv<int (&)(int, ...) noexcept>();

    test_is_same_rcv<void (&&)()>();
    test_is_same_rcv<void (&&)() noexcept>();

    test_is_same_rcv<void (&&)(int)>();
    test_is_same_rcv<void (&&)(int) noexcept>();

    test_is_same_rcv<void (&&)(...)>();
    test_is_same_rcv<void (&&)(...) noexcept>();

    test_is_same_rcv<void (&&)(int, ...)>();
    test_is_same_rcv<void (&&)(int, ...) noexcept>();

    test_is_same_rcv<int (&&)()>();
    test_is_same_rcv<int (&&)() noexcept>();

    test_is_same_rcv<int (&&)(int)>();
    test_is_same_rcv<int (&&)(int) noexcept>();

    test_is_same_rcv<int (&&)(...)>();
    test_is_same_rcv<int (&&)(...) noexcept>();

    test_is_same_rcv<int (&&)(int, ...)>();
    test_is_same_rcv<int (&&)(int, ...) noexcept>();

    test_is_same_rcv<void (Class::*)()>();
    test_is_same_rcv<void (Class::*)()&>();
    test_is_same_rcv<void (Class::*)() &&>();
    test_is_same_rcv<void (Class::*)() const>();
    test_is_same_rcv<void (Class::*)() const&>();
    test_is_same_rcv<void (Class::*)() const&&>();
    test_is_same_rcv<void (Class::*)() noexcept>();
    test_is_same_rcv<void (Class::*)()& noexcept>();
    test_is_same_rcv<void (Class::*)()&& noexcept>();
    test_is_same_rcv<void (Class::*)() const noexcept>();
    test_is_same_rcv<void (Class::*)() const& noexcept>();
    test_is_same_rcv<void (Class::*)() const&& noexcept>();

    test_is_same_rcv<void (Class::*)(int)>();
    test_is_same_rcv<void (Class::*)(int)&>();
    test_is_same_rcv<void (Class::*)(int) &&>();
    test_is_same_rcv<void (Class::*)(int) const>();
    test_is_same_rcv<void (Class::*)(int) const&>();
    test_is_same_rcv<void (Class::*)(int) const&&>();
    test_is_same_rcv<void (Class::*)(int) noexcept>();
    test_is_same_rcv<void (Class::*)(int)& noexcept>();
    test_is_same_rcv<void (Class::*)(int)&& noexcept>();
    test_is_same_rcv<void (Class::*)(int) const noexcept>();
    test_is_same_rcv<void (Class::*)(int) const& noexcept>();
    test_is_same_rcv<void (Class::*)(int) const&& noexcept>();

    test_is_same_rcv<void (Class::*)(...)>();
    test_is_same_rcv<void (Class::*)(...)&>();
    test_is_same_rcv<void (Class::*)(...) &&>();
    test_is_same_rcv<void (Class::*)(...) const>();
    test_is_same_rcv<void (Class::*)(...) const&>();
    test_is_same_rcv<void (Class::*)(...) const&&>();
    test_is_same_rcv<void (Class::*)(...) noexcept>();
    test_is_same_rcv<void (Class::*)(...)& noexcept>();
    test_is_same_rcv<void (Class::*)(...)&& noexcept>();
    test_is_same_rcv<void (Class::*)(...) const noexcept>();
    test_is_same_rcv<void (Class::*)(...) const& noexcept>();
    test_is_same_rcv<void (Class::*)(...) const&& noexcept>();

    test_is_same_rcv<void (Class::*)(int, ...)>();
    test_is_same_rcv<void (Class::*)(int, ...)&>();
    test_is_same_rcv<void (Class::*)(int, ...) &&>();
    test_is_same_rcv<void (Class::*)(int, ...) const>();
    test_is_same_rcv<void (Class::*)(int, ...) const&>();
    test_is_same_rcv<void (Class::*)(int, ...) const&&>();
    test_is_same_rcv<void (Class::*)(int, ...) noexcept>();
    test_is_same_rcv<void (Class::*)(int, ...)& noexcept>();
    test_is_same_rcv<void (Class::*)(int, ...)&& noexcept>();
    test_is_same_rcv<void (Class::*)(int, ...) const noexcept>();
    test_is_same_rcv<void (Class::*)(int, ...) const& noexcept>();
    test_is_same_rcv<void (Class::*)(int, ...) const&& noexcept>();

    test_is_same_rcv<int (Class::*)()>();
    test_is_same_rcv<int (Class::*)()&>();
    test_is_same_rcv<int (Class::*)() &&>();
    test_is_same_rcv<int (Class::*)() const>();
    test_is_same_rcv<int (Class::*)() const&>();
    test_is_same_rcv<int (Class::*)() const&&>();
    test_is_same_rcv<int (Class::*)() noexcept>();
    test_is_same_rcv<int (Class::*)()& noexcept>();
    test_is_same_rcv<int (Class::*)()&& noexcept>();
    test_is_same_rcv<int (Class::*)() const noexcept>();
    test_is_same_rcv<int (Class::*)() const& noexcept>();
    test_is_same_rcv<int (Class::*)() const&& noexcept>();

    test_is_same_rcv<int (Class::*)(int)>();
    test_is_same_rcv<int (Class::*)(int)&>();
    test_is_same_rcv<int (Class::*)(int) &&>();
    test_is_same_rcv<int (Class::*)(int) const>();
    test_is_same_rcv<int (Class::*)(int) const&>();
    test_is_same_rcv<int (Class::*)(int) const&&>();
    test_is_same_rcv<int (Class::*)(int) noexcept>();
    test_is_same_rcv<int (Class::*)(int)& noexcept>();
    test_is_same_rcv<int (Class::*)(int)&& noexcept>();
    test_is_same_rcv<int (Class::*)(int) const noexcept>();
    test_is_same_rcv<int (Class::*)(int) const& noexcept>();
    test_is_same_rcv<int (Class::*)(int) const&& noexcept>();

    test_is_same_rcv<int (Class::*)(...)>();
    test_is_same_rcv<int (Class::*)(...)&>();
    test_is_same_rcv<int (Class::*)(...) &&>();
    test_is_same_rcv<int (Class::*)(...) const>();
    test_is_same_rcv<int (Class::*)(...) const&>();
    test_is_same_rcv<int (Class::*)(...) const&&>();
    test_is_same_rcv<int (Class::*)(...) noexcept>();
    test_is_same_rcv<int (Class::*)(...)& noexcept>();
    test_is_same_rcv<int (Class::*)(...)&& noexcept>();
    test_is_same_rcv<int (Class::*)(...) const noexcept>();
    test_is_same_rcv<int (Class::*)(...) const& noexcept>();
    test_is_same_rcv<int (Class::*)(...) const&& noexcept>();

    test_is_same_rcv<int (Class::*)(int, ...)>();
    test_is_same_rcv<int (Class::*)(int, ...)&>();
    test_is_same_rcv<int (Class::*)(int, ...) &&>();
    test_is_same_rcv<int (Class::*)(int, ...) const>();
    test_is_same_rcv<int (Class::*)(int, ...) const&>();
    test_is_same_rcv<int (Class::*)(int, ...) const&&>();
    test_is_same_rcv<int (Class::*)(int, ...) noexcept>();
    test_is_same_rcv<int (Class::*)(int, ...)& noexcept>();
    test_is_same_rcv<int (Class::*)(int, ...)&& noexcept>();
    test_is_same_rcv<int (Class::*)(int, ...) const noexcept>();
    test_is_same_rcv<int (Class::*)(int, ...) const& noexcept>();
    test_is_same_rcv<int (Class::*)(int, ...) const&& noexcept>();
}
