#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/add_lvalue_reference.hpp>
#include <phi/type_traits/add_rvalue_reference.hpp>
#include <phi/type_traits/is_same_rcvref.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_is_same_rcvref_impl2()
{
    STATIC_REQUIRE(phi::is_same_rcvref<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref<T, U>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rcvref_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rcvref_v<T, U>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rcvref<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rcvref<T, U>);
}

template <typename T, typename U>
void test_is_same_rcvref_impl()
{
    test_is_same_rcvref_impl2<T, U>();
    test_is_same_rcvref_impl2<T, const U>();
    test_is_same_rcvref_impl2<T, volatile U>();
    test_is_same_rcvref_impl2<T, const volatile U>();

    test_is_same_rcvref_impl2<const T, U>();
    test_is_same_rcvref_impl2<const T, const U>();
    test_is_same_rcvref_impl2<const T, volatile U>();
    test_is_same_rcvref_impl2<const T, const volatile U>();

    test_is_same_rcvref_impl2<volatile T, U>();
    test_is_same_rcvref_impl2<volatile T, const U>();
    test_is_same_rcvref_impl2<volatile T, volatile U>();
    test_is_same_rcvref_impl2<volatile T, const volatile U>();

    test_is_same_rcvref_impl2<const volatile T, U>();
    test_is_same_rcvref_impl2<const volatile T, const U>();
    test_is_same_rcvref_impl2<const volatile T, volatile U>();
    test_is_same_rcvref_impl2<const volatile T, const volatile U>();
}

template <typename T, typename U = T>
void test_is_same_rcvref()
{
    test_is_same_rcvref_impl<T, U>();
    test_is_same_rcvref_impl<T, phi::add_lvalue_reference_t<U>>();
    test_is_same_rcvref_impl<T, phi::add_rvalue_reference_t<U>>();

    test_is_same_rcvref_impl<phi::add_lvalue_reference_t<T>, U>();
    test_is_same_rcvref_impl<phi::add_lvalue_reference_t<T>, phi::add_lvalue_reference_t<U>>();
    test_is_same_rcvref_impl<phi::add_lvalue_reference_t<T>, phi::add_rvalue_reference_t<U>>();

    test_is_same_rcvref_impl<phi::add_rvalue_reference_t<T>, U>();
    test_is_same_rcvref_impl<phi::add_rvalue_reference_t<T>, phi::add_lvalue_reference_t<U>>();
    test_is_same_rcvref_impl<phi::add_rvalue_reference_t<T>, phi::add_rvalue_reference_t<U>>();
}

template <typename T, typename U>
void test_is_not_same_rcvref()
{
    STATIC_REQUIRE_FALSE(phi::is_same_rcvref<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rcvref<T, U>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_rcvref_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_rcvref_v<T, U>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rcvref<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rcvref<T, U>);
}

template <typename T>
struct OverloadTest
{
    void fn(phi::is_same_rcvref<T, int>)
    {}
    void fn(phi::false_type)
    {}
    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same_rcvref")
{
    test_is_not_same_rcvref<int, void>();
    test_is_not_same_rcvref<void, Class>();
    test_is_not_same_rcvref<Class, int*>();
    test_is_not_same_rcvref<int*, int&>();

    OverloadTest<char> t;
    (void)t;

    test_is_same_rcvref<void>();
    test_is_same_rcvref<phi::nullptr_t>();
    test_is_same_rcvref<bool>();
    test_is_same_rcvref<char>();
    test_is_same_rcvref<signed char>();
    test_is_same_rcvref<unsigned char>();
    test_is_same_rcvref<short>();
    test_is_same_rcvref<unsigned short>();
    test_is_same_rcvref<int>();
    test_is_same_rcvref<unsigned int>();
    test_is_same_rcvref<long>();
    test_is_same_rcvref<unsigned long>();
    test_is_same_rcvref<long long>();
    test_is_same_rcvref<unsigned long long>();
    test_is_same_rcvref<float>();
    test_is_same_rcvref<double>();
    test_is_same_rcvref<long double>();
    test_is_same_rcvref<char8_t>();
    test_is_same_rcvref<char16_t>();
    test_is_same_rcvref<char32_t>();
    test_is_same_rcvref<wchar_t>();

    test_is_same_rcvref<phi::boolean>();
    test_is_same_rcvref<phi::integer<signed char>>();
    test_is_same_rcvref<phi::integer<unsigned char>>();
    test_is_same_rcvref<phi::integer<short>>();
    test_is_same_rcvref<phi::integer<unsigned short>>();
    test_is_same_rcvref<phi::integer<int>>();
    test_is_same_rcvref<phi::integer<unsigned int>>();
    test_is_same_rcvref<phi::integer<long>>();
    test_is_same_rcvref<phi::integer<unsigned long>>();
    test_is_same_rcvref<phi::integer<long long>>();
    test_is_same_rcvref<phi::integer<unsigned long long>>();
    test_is_same_rcvref<phi::floating_point<float>>();
    test_is_same_rcvref<phi::floating_point<double>>();
    test_is_same_rcvref<phi::floating_point<long double>>();

    test_is_same_rcvref<std::vector<int>>();
    test_is_same_rcvref<phi::scope_ptr<int>>();

    test_is_same_rcvref<int&>();
    test_is_same_rcvref<const int&>();
    test_is_same_rcvref<volatile int&>();
    test_is_same_rcvref<const volatile int&>();
    test_is_same_rcvref<int&&>();
    test_is_same_rcvref<const int&&>();
    test_is_same_rcvref<volatile int&&>();
    test_is_same_rcvref<const volatile int&&>();
    test_is_same_rcvref<int*>();
    test_is_same_rcvref<const int*>();
    test_is_same_rcvref<volatile int*>();
    test_is_same_rcvref<const volatile int*>();
    test_is_same_rcvref<int**>();
    test_is_same_rcvref<const int**>();
    test_is_same_rcvref<volatile int**>();
    test_is_same_rcvref<const volatile int**>();
    test_is_same_rcvref<int*&>();
    test_is_same_rcvref<const int*&>();
    test_is_same_rcvref<volatile int*&>();
    test_is_same_rcvref<const volatile int*&>();
    test_is_same_rcvref<int*&&>();
    test_is_same_rcvref<const int*&&>();
    test_is_same_rcvref<volatile int*&&>();
    test_is_same_rcvref<const volatile int*&&>();
    test_is_same_rcvref<void*>();
    test_is_same_rcvref<char[3]>();
    test_is_same_rcvref<char[]>();
    test_is_same_rcvref<char* [3]>();
    test_is_same_rcvref<char*[]>();
    test_is_same_rcvref<int(*)[3]>();
    test_is_same_rcvref<int(*)[]>();
    test_is_same_rcvref<int(&)[3]>();
    test_is_same_rcvref<int(&)[]>();
    test_is_same_rcvref<int(&&)[3]>();
    test_is_same_rcvref<int(&&)[]>();
    test_is_same_rcvref<char[3][2]>();
    test_is_same_rcvref<char[][2]>();
    test_is_same_rcvref<char* [3][2]>();
    test_is_same_rcvref<char*[][2]>();
    test_is_same_rcvref<int(*)[3][2]>();
    test_is_same_rcvref<int(*)[][2]>();
    test_is_same_rcvref<int(&)[3][2]>();
    test_is_same_rcvref<int(&)[][2]>();
    test_is_same_rcvref<int(&&)[3][2]>();
    test_is_same_rcvref<int(&&)[][2]>();
    test_is_same_rcvref<Class>();
    test_is_same_rcvref<Class[]>();
    test_is_same_rcvref<Class[2]>();
    test_is_same_rcvref<Template<void>>();
    test_is_same_rcvref<Template<int>>();
    test_is_same_rcvref<Template<Class>>();
    test_is_same_rcvref<Template<IncompleteType>>();
    test_is_same_rcvref<VariadicTemplate<>>();
    test_is_same_rcvref<VariadicTemplate<void>>();
    test_is_same_rcvref<VariadicTemplate<int>>();
    test_is_same_rcvref<VariadicTemplate<Class>>();
    test_is_same_rcvref<VariadicTemplate<IncompleteType>>();
    test_is_same_rcvref<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_same_rcvref<PublicDerivedFromTemplate<Base>>();
    test_is_same_rcvref<PublicDerivedFromTemplate<Derived>>();
    test_is_same_rcvref<PublicDerivedFromTemplate<Class>>();
    test_is_same_rcvref<PrivateDerivedFromTemplate<Base>>();
    test_is_same_rcvref<PrivateDerivedFromTemplate<Derived>>();
    test_is_same_rcvref<PrivateDerivedFromTemplate<Class>>();
    test_is_same_rcvref<ProtectedDerivedFromTemplate<Base>>();
    test_is_same_rcvref<ProtectedDerivedFromTemplate<Derived>>();
    test_is_same_rcvref<ProtectedDerivedFromTemplate<Class>>();
    test_is_same_rcvref<VirtualDerivedFromTemplate<Base>>();
    test_is_same_rcvref<VirtualDerivedFromTemplate<Derived>>();
    test_is_same_rcvref<VirtualDerivedFromTemplate<Class>>();
    test_is_same_rcvref<Union>();
    test_is_same_rcvref<NonEmptyUnion>();
    test_is_same_rcvref<NonTrivialUnion>();
    test_is_same_rcvref<Empty>();
    test_is_same_rcvref<NotEmpty>();
    test_is_same_rcvref<NonTrivial>();
    test_is_same_rcvref<BitZero>();
    test_is_same_rcvref<BitOne>();
    test_is_same_rcvref<Base>();
    test_is_same_rcvref<Derived>();
    test_is_same_rcvref<NotEmptyBase>();
    test_is_same_rcvref<EmptyBase>();
    test_is_same_rcvref<VirtualBase>();
    test_is_same_rcvref<Polymorphic>();
    test_is_same_rcvref<DerivedPolymorphic>();
    test_is_same_rcvref<Abstract>();
    test_is_same_rcvref<PublicAbstract>();
    test_is_same_rcvref<PrivateAbstract>();
    test_is_same_rcvref<ProtectedAbstract>();
    test_is_same_rcvref<AbstractTemplate<int>>();
    test_is_same_rcvref<AbstractTemplate<double>>();
    test_is_same_rcvref<AbstractTemplate<Class>>();
    test_is_same_rcvref<AbstractTemplate<IncompleteType>>();
    test_is_same_rcvref<PublicAbstractDeletedDestructor>();
    test_is_same_rcvref<ProtectedAbstractDeletedDestructor>();
    test_is_same_rcvref<PrivateAbstractDeletedDestructor>();
    test_is_same_rcvref<Final>();
    test_is_same_rcvref<FinalDerived>();
    test_is_same_rcvref<PublicDestructor>();
    test_is_same_rcvref<ProtectedDestructor>();
    test_is_same_rcvref<PrivateDestructor>();
    test_is_same_rcvref<VirtualPublicDestructor>();
    test_is_same_rcvref<VirtualProtectedDestructor>();
    test_is_same_rcvref<VirtualPrivateDestructor>();
    test_is_same_rcvref<PurePublicDestructor>();
    test_is_same_rcvref<PureProtectedDestructor>();
    test_is_same_rcvref<PurePrivateDestructor>();
    test_is_same_rcvref<DeletedPublicDestructor>();
    test_is_same_rcvref<DeletedProtectedDestructor>();
    test_is_same_rcvref<DeletedPrivateDestructor>();
    test_is_same_rcvref<DeletedVirtualPublicDestructor>();
    test_is_same_rcvref<DeletedVirtualProtectedDestructor>();
    test_is_same_rcvref<DeletedVirtualPrivateDestructor>();
    test_is_same_rcvref<ExplicitClass>();
    test_is_same_rcvref<NothrowExplicitClass>();
    test_is_same_rcvref<ThrowExplicitClass>();
    test_is_same_rcvref<ThrowDefaultClass>();
    test_is_same_rcvref<ThrowCopyConsClass>();
    test_is_same_rcvref<ThrowMoveConsClass>();
    test_is_same_rcvref<ThrowDestructor>();
    test_is_same_rcvref<NoexceptExplicitClass>();
    test_is_same_rcvref<ExceptExplicitClass>();
    test_is_same_rcvref<NoexceptDefaultClass>();
    test_is_same_rcvref<ExceptDefaultClass>();
    test_is_same_rcvref<NoexceptCopyConsClass>();
    test_is_same_rcvref<ExceptCopyConsClass>();
    test_is_same_rcvref<NoexceptMoveConsClass>();
    test_is_same_rcvref<ExceptMoveConsClass>();
    test_is_same_rcvref<NoexceptCopyAssignClass>();
    test_is_same_rcvref<ExceptCopyAssignClass>();
    test_is_same_rcvref<NoexceptMoveAssignClass>();
    test_is_same_rcvref<ExceptMoveAssignClass>();
    test_is_same_rcvref<DeletedCopyAssignClass>();
    test_is_same_rcvref<DeletedMoveAssignClass>();
    test_is_same_rcvref<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_same_rcvref<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_same_rcvref<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_same_rcvref<ExceptMoveConsExceptMoveAssignClass>();
    test_is_same_rcvref<ImplicitTo<int>>();
    test_is_same_rcvref<ImplicitTo<float>>();
    test_is_same_rcvref<ImplicitTo<Class>>();
    test_is_same_rcvref<DeletedImplicitTo<int>>();
    test_is_same_rcvref<DeletedImplicitTo<float>>();
    test_is_same_rcvref<DeletedImplicitTo<Class>>();
    test_is_same_rcvref<ExplicitTo<int>>();
    test_is_same_rcvref<ExplicitTo<float>>();
    test_is_same_rcvref<ExplicitTo<Class>>();
    test_is_same_rcvref<DeletedExplicitTo<int>>();
    test_is_same_rcvref<DeletedExplicitTo<float>>();
    test_is_same_rcvref<DeletedExplicitTo<Class>>();
    test_is_same_rcvref<Ellipsis>();
    test_is_same_rcvref<DeletedEllipsis>();
    test_is_same_rcvref<CopyConsOnlyType>();
    test_is_same_rcvref<MoveConsOnlyType>();
    test_is_same_rcvref<OverloadedOperators>();
    test_is_same_rcvref<PublicIntMember>();
    test_is_same_rcvref<ProtectedIntMember>();
    test_is_same_rcvref<PrivateIntMember>();
    test_is_same_rcvref<PublicStaticIntMember>();
    test_is_same_rcvref<ProtectedStaticIntMember>();
    test_is_same_rcvref<PrivateStaticIntMember>();
    test_is_same_rcvref<PublicTemplateMember<int>>();
    test_is_same_rcvref<PublicTemplateMember<float>>();
    test_is_same_rcvref<PublicTemplateMember<Class>>();
    test_is_same_rcvref<ProtectedTemplateMember<int>>();
    test_is_same_rcvref<ProtectedTemplateMember<float>>();
    test_is_same_rcvref<ProtectedTemplateMember<Class>>();
    test_is_same_rcvref<PrivateTemplateMember<int>>();
    test_is_same_rcvref<PrivateTemplateMember<float>>();
    test_is_same_rcvref<PrivateTemplateMember<Class>>();
    test_is_same_rcvref<PublicStaticTemplateMember<int>>();
    test_is_same_rcvref<PublicStaticTemplateMember<float>>();
    test_is_same_rcvref<PublicStaticTemplateMember<Class>>();
    test_is_same_rcvref<ProtectedStaticTemplateMember<int>>();
    test_is_same_rcvref<ProtectedStaticTemplateMember<float>>();
    test_is_same_rcvref<ProtectedStaticTemplateMember<Class>>();
    test_is_same_rcvref<PrivateStaticTemplateMember<int>>();
    test_is_same_rcvref<PrivateStaticTemplateMember<float>>();
    test_is_same_rcvref<PrivateStaticTemplateMember<Class>>();
    test_is_same_rcvref<CannotInstantiate<int>>();
    test_is_same_rcvref<CannotInstantiate<float>>();
    test_is_same_rcvref<CannotInstantiate<Class>>();
    test_is_same_rcvref<natural_alignment>();
    test_is_same_rcvref<Enum>();
    test_is_same_rcvref<EnumSigned>();
    test_is_same_rcvref<EnumUnsigned>();
    test_is_same_rcvref<EnumClass>();
    test_is_same_rcvref<EnumStruct>();
    test_is_same_rcvref<Function>();
    test_is_same_rcvref<FunctionPtr>();
    test_is_same_rcvref<MemberObjectPtr>();
    test_is_same_rcvref<MemberFunctionPtr>();
    test_is_same_rcvref<LambdaType>();
    test_is_same_rcvref<LambdaNoexceptType>();
    test_is_same_rcvref<LambdaThrowsType>();
    test_is_same_rcvref<IncompleteType>();
    test_is_same_rcvref<IncompleteTemplate<void>>();
    test_is_same_rcvref<IncompleteTemplate<int>>();
    test_is_same_rcvref<IncompleteTemplate<Class>>();
    test_is_same_rcvref<IncompleteTemplate<IncompleteType>>();
    test_is_same_rcvref<IncompleteVariadicTemplate<>>();
    test_is_same_rcvref<IncompleteVariadicTemplate<void>>();
    test_is_same_rcvref<IncompleteVariadicTemplate<int>>();
    test_is_same_rcvref<IncompleteVariadicTemplate<Class>>();
    test_is_same_rcvref<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_same_rcvref<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_same_rcvref<IncompleteUnion>();
    test_is_same_rcvref<IncompleteEnumSigned>();
    test_is_same_rcvref<IncompleteEnumUnsigned>();
    test_is_same_rcvref<IncompleteEnumClass>();
    test_is_same_rcvref<IncompleteEnumStruct>();
    test_is_same_rcvref<int Class::*>();
    test_is_same_rcvref<float Class::*>();
    test_is_same_rcvref<void * Class::*>();
    test_is_same_rcvref<int * Class::*>();
    test_is_same_rcvref<Enum Class::*>();
    test_is_same_rcvref<NotEmpty Class::*>();
    test_is_same_rcvref<int Class::*&>();
    test_is_same_rcvref<float Class::*&>();
    test_is_same_rcvref<void * Class::*&>();
    test_is_same_rcvref<int * Class::*&>();
    test_is_same_rcvref<Enum Class::*&>();
    test_is_same_rcvref<NotEmpty Class::*&>();
    test_is_same_rcvref<int Class::*&&>();
    test_is_same_rcvref<float Class::*&&>();
    test_is_same_rcvref<void * Class::*&&>();
    test_is_same_rcvref<int * Class::*&&>();
    test_is_same_rcvref<Enum Class::*&&>();
    test_is_same_rcvref<NotEmpty Class::*&&>();
    test_is_same_rcvref<NonDefaultConstructible>();
    test_is_same_rcvref<NonCopyConstructible>();
    test_is_same_rcvref<NonMoveConstructible>();
    test_is_same_rcvref<NonCopyAssignable>();
    test_is_same_rcvref<NonMoveAssignable>();
    test_is_same_rcvref<NonAssignable>();
    test_is_same_rcvref<NonCopyable>();
    test_is_same_rcvref<NonMoveable>();
    test_is_same_rcvref<NonConstructible>();
    test_is_same_rcvref<NonDestructible>();
    test_is_same_rcvref<Tracked>();
    test_is_same_rcvref<TrapConstructible>();
    test_is_same_rcvref<TrapImplicitConversion>();
    test_is_same_rcvref<TrapComma>();
    test_is_same_rcvref<TrapCall>();
    test_is_same_rcvref<TrapSelfAssign>();
    test_is_same_rcvref<TrapDeref>();
    test_is_same_rcvref<TrapArraySubscript>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY()
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_is_same_rcvref<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_is_same_rcvref<void()>();
    test_is_same_rcvref<void()&>();
    test_is_same_rcvref<void() &&>();
    test_is_same_rcvref<void() const>();
    test_is_same_rcvref<void() const&>();
    test_is_same_rcvref<void() const&&>();
    test_is_same_rcvref<void() volatile>();
    test_is_same_rcvref<void() volatile&>();
    test_is_same_rcvref<void() volatile&&>();
    test_is_same_rcvref<void() const volatile>();
    test_is_same_rcvref<void() const volatile&>();
    test_is_same_rcvref<void() const volatile&&>();
    test_is_same_rcvref<void() noexcept>();
    test_is_same_rcvref<void()& noexcept>();
    test_is_same_rcvref<void()&& noexcept>();
    test_is_same_rcvref<void() const noexcept>();
    test_is_same_rcvref<void() const& noexcept>();
    test_is_same_rcvref<void() const&& noexcept>();
    test_is_same_rcvref<void() volatile noexcept>();
    test_is_same_rcvref<void() volatile& noexcept>();
    test_is_same_rcvref<void() volatile&& noexcept>();
    test_is_same_rcvref<void() const volatile noexcept>();
    test_is_same_rcvref<void() const volatile& noexcept>();
    test_is_same_rcvref<void() const volatile&& noexcept>();

    test_is_same_rcvref<void(int)>();
    test_is_same_rcvref<void(int)&>();
    test_is_same_rcvref<void(int) &&>();
    test_is_same_rcvref<void(int) const>();
    test_is_same_rcvref<void(int) const&>();
    test_is_same_rcvref<void(int) const&&>();
    test_is_same_rcvref<void(int) volatile>();
    test_is_same_rcvref<void(int) volatile&>();
    test_is_same_rcvref<void(int) volatile&&>();
    test_is_same_rcvref<void(int) const volatile>();
    test_is_same_rcvref<void(int) const volatile&>();
    test_is_same_rcvref<void(int) const volatile&&>();
    test_is_same_rcvref<void(int) noexcept>();
    test_is_same_rcvref<void(int)& noexcept>();
    test_is_same_rcvref<void(int)&& noexcept>();
    test_is_same_rcvref<void(int) const noexcept>();
    test_is_same_rcvref<void(int) const& noexcept>();
    test_is_same_rcvref<void(int) const&& noexcept>();
    test_is_same_rcvref<void(int) volatile noexcept>();
    test_is_same_rcvref<void(int) volatile& noexcept>();
    test_is_same_rcvref<void(int) volatile&& noexcept>();
    test_is_same_rcvref<void(int) const volatile noexcept>();
    test_is_same_rcvref<void(int) const volatile& noexcept>();
    test_is_same_rcvref<void(int) const volatile&& noexcept>();

    test_is_same_rcvref<void(...)>();
    test_is_same_rcvref<void(...)&>();
    test_is_same_rcvref<void(...) &&>();
    test_is_same_rcvref<void(...) const>();
    test_is_same_rcvref<void(...) const&>();
    test_is_same_rcvref<void(...) const&&>();
    test_is_same_rcvref<void(...) volatile>();
    test_is_same_rcvref<void(...) volatile&>();
    test_is_same_rcvref<void(...) volatile&&>();
    test_is_same_rcvref<void(...) const volatile>();
    test_is_same_rcvref<void(...) const volatile&>();
    test_is_same_rcvref<void(...) const volatile&&>();
    test_is_same_rcvref<void(...) noexcept>();
    test_is_same_rcvref<void(...)& noexcept>();
    test_is_same_rcvref<void(...)&& noexcept>();
    test_is_same_rcvref<void(...) const noexcept>();
    test_is_same_rcvref<void(...) const& noexcept>();
    test_is_same_rcvref<void(...) const&& noexcept>();
    test_is_same_rcvref<void(...) volatile noexcept>();
    test_is_same_rcvref<void(...) volatile& noexcept>();
    test_is_same_rcvref<void(...) volatile&& noexcept>();
    test_is_same_rcvref<void(...) const volatile noexcept>();
    test_is_same_rcvref<void(...) const volatile& noexcept>();
    test_is_same_rcvref<void(...) const volatile&& noexcept>();

    test_is_same_rcvref<void(int, ...)>();
    test_is_same_rcvref<void(int, ...)&>();
    test_is_same_rcvref<void(int, ...) &&>();
    test_is_same_rcvref<void(int, ...) const>();
    test_is_same_rcvref<void(int, ...) const&>();
    test_is_same_rcvref<void(int, ...) const&&>();
    test_is_same_rcvref<void(int, ...) volatile>();
    test_is_same_rcvref<void(int, ...) volatile&>();
    test_is_same_rcvref<void(int, ...) volatile&&>();
    test_is_same_rcvref<void(int, ...) const volatile>();
    test_is_same_rcvref<void(int, ...) const volatile&>();
    test_is_same_rcvref<void(int, ...) const volatile&&>();
    test_is_same_rcvref<void(int, ...) noexcept>();
    test_is_same_rcvref<void(int, ...)& noexcept>();
    test_is_same_rcvref<void(int, ...)&& noexcept>();
    test_is_same_rcvref<void(int, ...) const noexcept>();
    test_is_same_rcvref<void(int, ...) const& noexcept>();
    test_is_same_rcvref<void(int, ...) const&& noexcept>();
    test_is_same_rcvref<void(int, ...) volatile noexcept>();
    test_is_same_rcvref<void(int, ...) volatile& noexcept>();
    test_is_same_rcvref<void(int, ...) volatile&& noexcept>();
    test_is_same_rcvref<void(int, ...) const volatile noexcept>();
    test_is_same_rcvref<void(int, ...) const volatile& noexcept>();
    test_is_same_rcvref<void(int, ...) const volatile&& noexcept>();

    test_is_same_rcvref<int()>();
    test_is_same_rcvref<int()&>();
    test_is_same_rcvref<int() &&>();
    test_is_same_rcvref<int() const>();
    test_is_same_rcvref<int() const&>();
    test_is_same_rcvref<int() const&&>();
    test_is_same_rcvref<int() volatile>();
    test_is_same_rcvref<int() volatile&>();
    test_is_same_rcvref<int() volatile&&>();
    test_is_same_rcvref<int() const volatile>();
    test_is_same_rcvref<int() const volatile&>();
    test_is_same_rcvref<int() const volatile&&>();
    test_is_same_rcvref<int() noexcept>();
    test_is_same_rcvref<int()& noexcept>();
    test_is_same_rcvref<int()&& noexcept>();
    test_is_same_rcvref<int() const noexcept>();
    test_is_same_rcvref<int() const& noexcept>();
    test_is_same_rcvref<int() const&& noexcept>();
    test_is_same_rcvref<int() volatile noexcept>();
    test_is_same_rcvref<int() volatile& noexcept>();
    test_is_same_rcvref<int() volatile&& noexcept>();
    test_is_same_rcvref<int() const volatile noexcept>();
    test_is_same_rcvref<int() const volatile& noexcept>();
    test_is_same_rcvref<int() const volatile&& noexcept>();

    test_is_same_rcvref<int(int)>();
    test_is_same_rcvref<int(int)&>();
    test_is_same_rcvref<int(int) &&>();
    test_is_same_rcvref<int(int) const>();
    test_is_same_rcvref<int(int) const&>();
    test_is_same_rcvref<int(int) const&&>();
    test_is_same_rcvref<int(int) volatile>();
    test_is_same_rcvref<int(int) volatile&>();
    test_is_same_rcvref<int(int) volatile&&>();
    test_is_same_rcvref<int(int) const volatile>();
    test_is_same_rcvref<int(int) const volatile&>();
    test_is_same_rcvref<int(int) const volatile&&>();
    test_is_same_rcvref<int(int) noexcept>();
    test_is_same_rcvref<int(int)& noexcept>();
    test_is_same_rcvref<int(int)&& noexcept>();
    test_is_same_rcvref<int(int) const noexcept>();
    test_is_same_rcvref<int(int) const& noexcept>();
    test_is_same_rcvref<int(int) const&& noexcept>();
    test_is_same_rcvref<int(int) volatile noexcept>();
    test_is_same_rcvref<int(int) volatile& noexcept>();
    test_is_same_rcvref<int(int) volatile&& noexcept>();
    test_is_same_rcvref<int(int) const volatile noexcept>();
    test_is_same_rcvref<int(int) const volatile& noexcept>();
    test_is_same_rcvref<int(int) const volatile&& noexcept>();

    test_is_same_rcvref<int(...)>();
    test_is_same_rcvref<int(...)&>();
    test_is_same_rcvref<int(...) &&>();
    test_is_same_rcvref<int(...) const>();
    test_is_same_rcvref<int(...) const&>();
    test_is_same_rcvref<int(...) const&&>();
    test_is_same_rcvref<int(...) volatile>();
    test_is_same_rcvref<int(...) volatile&>();
    test_is_same_rcvref<int(...) volatile&&>();
    test_is_same_rcvref<int(...) const volatile>();
    test_is_same_rcvref<int(...) const volatile&>();
    test_is_same_rcvref<int(...) const volatile&&>();
    test_is_same_rcvref<int(...) noexcept>();
    test_is_same_rcvref<int(...)& noexcept>();
    test_is_same_rcvref<int(...)&& noexcept>();
    test_is_same_rcvref<int(...) const noexcept>();
    test_is_same_rcvref<int(...) const& noexcept>();
    test_is_same_rcvref<int(...) const&& noexcept>();
    test_is_same_rcvref<int(...) volatile noexcept>();
    test_is_same_rcvref<int(...) volatile& noexcept>();
    test_is_same_rcvref<int(...) volatile&& noexcept>();
    test_is_same_rcvref<int(...) const volatile noexcept>();
    test_is_same_rcvref<int(...) const volatile& noexcept>();
    test_is_same_rcvref<int(...) const volatile&& noexcept>();

    test_is_same_rcvref<int(int, ...)>();
    test_is_same_rcvref<int(int, ...)&>();
    test_is_same_rcvref<int(int, ...) &&>();
    test_is_same_rcvref<int(int, ...) const>();
    test_is_same_rcvref<int(int, ...) const&>();
    test_is_same_rcvref<int(int, ...) const&&>();
    test_is_same_rcvref<int(int, ...) volatile>();
    test_is_same_rcvref<int(int, ...) volatile&>();
    test_is_same_rcvref<int(int, ...) volatile&&>();
    test_is_same_rcvref<int(int, ...) const volatile>();
    test_is_same_rcvref<int(int, ...) const volatile&>();
    test_is_same_rcvref<int(int, ...) const volatile&&>();
    test_is_same_rcvref<int(int, ...) noexcept>();
    test_is_same_rcvref<int(int, ...)& noexcept>();
    test_is_same_rcvref<int(int, ...)&& noexcept>();
    test_is_same_rcvref<int(int, ...) const noexcept>();
    test_is_same_rcvref<int(int, ...) const& noexcept>();
    test_is_same_rcvref<int(int, ...) const&& noexcept>();
    test_is_same_rcvref<int(int, ...) volatile noexcept>();
    test_is_same_rcvref<int(int, ...) volatile& noexcept>();
    test_is_same_rcvref<int(int, ...) volatile&& noexcept>();
    test_is_same_rcvref<int(int, ...) const volatile noexcept>();
    test_is_same_rcvref<int(int, ...) const volatile& noexcept>();
    test_is_same_rcvref<int(int, ...) const volatile&& noexcept>();

    test_is_same_rcvref<void (*)()>();
    test_is_same_rcvref<void (*)() noexcept>();

    test_is_same_rcvref<void (*)(int)>();
    test_is_same_rcvref<void (*)(int) noexcept>();

    test_is_same_rcvref<void (*)(...)>();
    test_is_same_rcvref<void (*)(...) noexcept>();

    test_is_same_rcvref<void (*)(int, ...)>();
    test_is_same_rcvref<void (*)(int, ...) noexcept>();

    test_is_same_rcvref<int (*)()>();
    test_is_same_rcvref<int (*)() noexcept>();

    test_is_same_rcvref<int (*)(int)>();
    test_is_same_rcvref<int (*)(int) noexcept>();

    test_is_same_rcvref<int (*)(...)>();
    test_is_same_rcvref<int (*)(...) noexcept>();

    test_is_same_rcvref<int (*)(int, ...)>();
    test_is_same_rcvref<int (*)(int, ...) noexcept>();

    test_is_same_rcvref<void (&)()>();
    test_is_same_rcvref<void (&)() noexcept>();

    test_is_same_rcvref<void (&)(int)>();
    test_is_same_rcvref<void (&)(int) noexcept>();

    test_is_same_rcvref<void (&)(...)>();
    test_is_same_rcvref<void (&)(...) noexcept>();

    test_is_same_rcvref<void (&)(int, ...)>();
    test_is_same_rcvref<void (&)(int, ...) noexcept>();

    test_is_same_rcvref<int (&)()>();
    test_is_same_rcvref<int (&)() noexcept>();

    test_is_same_rcvref<int (&)(int)>();
    test_is_same_rcvref<int (&)(int) noexcept>();

    test_is_same_rcvref<int (&)(...)>();
    test_is_same_rcvref<int (&)(...) noexcept>();

    test_is_same_rcvref<int (&)(int, ...)>();
    test_is_same_rcvref<int (&)(int, ...) noexcept>();

    test_is_same_rcvref<void(&&)()>();
    test_is_same_rcvref<void(&&)() noexcept>();

    test_is_same_rcvref<void(&&)(int)>();
    test_is_same_rcvref<void(&&)(int) noexcept>();

    test_is_same_rcvref<void(&&)(...)>();
    test_is_same_rcvref<void(&&)(...) noexcept>();

    test_is_same_rcvref<void(&&)(int, ...)>();
    test_is_same_rcvref<void(&&)(int, ...) noexcept>();

    test_is_same_rcvref<int(&&)()>();
    test_is_same_rcvref<int(&&)() noexcept>();

    test_is_same_rcvref<int(&&)(int)>();
    test_is_same_rcvref<int(&&)(int) noexcept>();

    test_is_same_rcvref<int(&&)(...)>();
    test_is_same_rcvref<int(&&)(...) noexcept>();

    test_is_same_rcvref<int(&&)(int, ...)>();
    test_is_same_rcvref<int(&&)(int, ...) noexcept>();

    test_is_same_rcvref<void (Class::*)()>();
    test_is_same_rcvref<void (Class::*)()&>();
    test_is_same_rcvref<void (Class::*)() &&>();
    test_is_same_rcvref<void (Class::*)() const>();
    test_is_same_rcvref<void (Class::*)() const&>();
    test_is_same_rcvref<void (Class::*)() const&&>();
    test_is_same_rcvref<void (Class::*)() noexcept>();
    test_is_same_rcvref<void (Class::*)()& noexcept>();
    test_is_same_rcvref<void (Class::*)()&& noexcept>();
    test_is_same_rcvref<void (Class::*)() const noexcept>();
    test_is_same_rcvref<void (Class::*)() const& noexcept>();
    test_is_same_rcvref<void (Class::*)() const&& noexcept>();

    test_is_same_rcvref<void (Class::*)(int)>();
    test_is_same_rcvref<void (Class::*)(int)&>();
    test_is_same_rcvref<void (Class::*)(int) &&>();
    test_is_same_rcvref<void (Class::*)(int) const>();
    test_is_same_rcvref<void (Class::*)(int) const&>();
    test_is_same_rcvref<void (Class::*)(int) const&&>();
    test_is_same_rcvref<void (Class::*)(int) noexcept>();
    test_is_same_rcvref<void (Class::*)(int)& noexcept>();
    test_is_same_rcvref<void (Class::*)(int)&& noexcept>();
    test_is_same_rcvref<void (Class::*)(int) const noexcept>();
    test_is_same_rcvref<void (Class::*)(int) const& noexcept>();
    test_is_same_rcvref<void (Class::*)(int) const&& noexcept>();

    test_is_same_rcvref<void (Class::*)(...)>();
    test_is_same_rcvref<void (Class::*)(...)&>();
    test_is_same_rcvref<void (Class::*)(...) &&>();
    test_is_same_rcvref<void (Class::*)(...) const>();
    test_is_same_rcvref<void (Class::*)(...) const&>();
    test_is_same_rcvref<void (Class::*)(...) const&&>();
    test_is_same_rcvref<void (Class::*)(...) noexcept>();
    test_is_same_rcvref<void (Class::*)(...)& noexcept>();
    test_is_same_rcvref<void (Class::*)(...)&& noexcept>();
    test_is_same_rcvref<void (Class::*)(...) const noexcept>();
    test_is_same_rcvref<void (Class::*)(...) const& noexcept>();
    test_is_same_rcvref<void (Class::*)(...) const&& noexcept>();

    test_is_same_rcvref<void (Class::*)(int, ...)>();
    test_is_same_rcvref<void (Class::*)(int, ...)&>();
    test_is_same_rcvref<void (Class::*)(int, ...) &&>();
    test_is_same_rcvref<void (Class::*)(int, ...) const>();
    test_is_same_rcvref<void (Class::*)(int, ...) const&>();
    test_is_same_rcvref<void (Class::*)(int, ...) const&&>();
    test_is_same_rcvref<void (Class::*)(int, ...) noexcept>();
    test_is_same_rcvref<void (Class::*)(int, ...)& noexcept>();
    test_is_same_rcvref<void (Class::*)(int, ...)&& noexcept>();
    test_is_same_rcvref<void (Class::*)(int, ...) const noexcept>();
    test_is_same_rcvref<void (Class::*)(int, ...) const& noexcept>();
    test_is_same_rcvref<void (Class::*)(int, ...) const&& noexcept>();

    test_is_same_rcvref<int (Class::*)()>();
    test_is_same_rcvref<int (Class::*)()&>();
    test_is_same_rcvref<int (Class::*)() &&>();
    test_is_same_rcvref<int (Class::*)() const>();
    test_is_same_rcvref<int (Class::*)() const&>();
    test_is_same_rcvref<int (Class::*)() const&&>();
    test_is_same_rcvref<int (Class::*)() noexcept>();
    test_is_same_rcvref<int (Class::*)()& noexcept>();
    test_is_same_rcvref<int (Class::*)()&& noexcept>();
    test_is_same_rcvref<int (Class::*)() const noexcept>();
    test_is_same_rcvref<int (Class::*)() const& noexcept>();
    test_is_same_rcvref<int (Class::*)() const&& noexcept>();

    test_is_same_rcvref<int (Class::*)(int)>();
    test_is_same_rcvref<int (Class::*)(int)&>();
    test_is_same_rcvref<int (Class::*)(int) &&>();
    test_is_same_rcvref<int (Class::*)(int) const>();
    test_is_same_rcvref<int (Class::*)(int) const&>();
    test_is_same_rcvref<int (Class::*)(int) const&&>();
    test_is_same_rcvref<int (Class::*)(int) noexcept>();
    test_is_same_rcvref<int (Class::*)(int)& noexcept>();
    test_is_same_rcvref<int (Class::*)(int)&& noexcept>();
    test_is_same_rcvref<int (Class::*)(int) const noexcept>();
    test_is_same_rcvref<int (Class::*)(int) const& noexcept>();
    test_is_same_rcvref<int (Class::*)(int) const&& noexcept>();

    test_is_same_rcvref<int (Class::*)(...)>();
    test_is_same_rcvref<int (Class::*)(...)&>();
    test_is_same_rcvref<int (Class::*)(...) &&>();
    test_is_same_rcvref<int (Class::*)(...) const>();
    test_is_same_rcvref<int (Class::*)(...) const&>();
    test_is_same_rcvref<int (Class::*)(...) const&&>();
    test_is_same_rcvref<int (Class::*)(...) noexcept>();
    test_is_same_rcvref<int (Class::*)(...)& noexcept>();
    test_is_same_rcvref<int (Class::*)(...)&& noexcept>();
    test_is_same_rcvref<int (Class::*)(...) const noexcept>();
    test_is_same_rcvref<int (Class::*)(...) const& noexcept>();
    test_is_same_rcvref<int (Class::*)(...) const&& noexcept>();

    test_is_same_rcvref<int (Class::*)(int, ...)>();
    test_is_same_rcvref<int (Class::*)(int, ...)&>();
    test_is_same_rcvref<int (Class::*)(int, ...) &&>();
    test_is_same_rcvref<int (Class::*)(int, ...) const>();
    test_is_same_rcvref<int (Class::*)(int, ...) const&>();
    test_is_same_rcvref<int (Class::*)(int, ...) const&&>();
    test_is_same_rcvref<int (Class::*)(int, ...) noexcept>();
    test_is_same_rcvref<int (Class::*)(int, ...)& noexcept>();
    test_is_same_rcvref<int (Class::*)(int, ...)&& noexcept>();
    test_is_same_rcvref<int (Class::*)(int, ...) const noexcept>();
    test_is_same_rcvref<int (Class::*)(int, ...) const& noexcept>();
    test_is_same_rcvref<int (Class::*)(int, ...) const&& noexcept>();
}
