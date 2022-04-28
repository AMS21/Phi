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
#include <phi/type_traits/is_same_rv.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_is_same_rv_impl()
{
    STATIC_REQUIRE(phi::is_same_rv<T, U>::value);
    STATIC_REQUIRE(phi::is_same_rv<U, T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rv_v<T, U>);
    STATIC_REQUIRE(phi::is_same_rv_v<U, T>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rv_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rv<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rv<T, U>);
}

template <typename T, typename U>
void test_is_not_same_rv()
{
    STATIC_REQUIRE_FALSE(phi::is_same_rv<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rv<U, T>::value);
    STATIC_REQUIRE(phi::is_not_same_rv<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rv<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_rv_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rv_v<U, T>);
    STATIC_REQUIRE(phi::is_not_same_rv_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_rv_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rv<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rv<T, U>);
}

template <typename T, typename U = T>
void test_is_same_rv()
{
    test_is_same_rv_impl<T, U>();
    test_is_not_same_rv<T, const U>();
    test_is_same_rv_impl<T, volatile U>();
    test_is_not_same_rv<T, const volatile U>();

    test_is_not_same_rv<const T, U>();
    test_is_same_rv_impl<const T, const U>();
    test_is_not_same_rv<const T, volatile U>();
    test_is_same_rv_impl<const T, const volatile U>();

    test_is_same_rv_impl<volatile T, U>();
    test_is_not_same_rv<volatile T, const U>();
    test_is_same_rv_impl<volatile T, volatile U>();
    test_is_not_same_rv<volatile T, const volatile U>();

    test_is_not_same_rv<const volatile T, U>();
    test_is_same_rv_impl<const volatile T, const U>();
    test_is_not_same_rv<const volatile T, volatile U>();
    test_is_same_rv_impl<const volatile T, const volatile U>();
}

template <typename T, typename U = T>
void test_is_same_rv_ref()
{
    test_is_same_rv_impl<T, U>();
    test_is_same_rv_impl<T, const U>();
    test_is_same_rv_impl<T, volatile U>();
    test_is_same_rv_impl<T, const volatile U>();

    test_is_same_rv_impl<const T, U>();
    test_is_same_rv_impl<const T, const U>();
    test_is_same_rv_impl<const T, volatile U>();
    test_is_same_rv_impl<const T, const volatile U>();

    test_is_same_rv_impl<volatile T, U>();
    test_is_same_rv_impl<volatile T, const U>();
    test_is_same_rv_impl<volatile T, volatile U>();
    test_is_same_rv_impl<volatile T, const volatile U>();

    test_is_same_rv_impl<const volatile T, U>();
    test_is_same_rv_impl<const volatile T, const U>();
    test_is_same_rv_impl<const volatile T, volatile U>();
    test_is_same_rv_impl<const volatile T, const volatile U>();
}

template <typename T>
struct OverloadTest
{
    void fn(phi::is_same_rv<T, int>)
    {}
    void fn(phi::false_type)
    {}
    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same_rv")
{
    test_is_not_same_rv<int, void>();
    test_is_not_same_rv<void, Class>();
    test_is_not_same_rv<Class, int*>();
    test_is_not_same_rv<int*, int&>();
    test_is_not_same_rv<int&, int>();

    test_is_not_same_rv<int, const int>();
    test_is_not_same_rv<int, const volatile int>();
    test_is_not_same_rv<int, int&>();
    test_is_not_same_rv<int, const int&>();
    test_is_not_same_rv<int, volatile int&>();
    test_is_not_same_rv<int, const volatile int&>();
    test_is_not_same_rv<int, int&&>();
    test_is_not_same_rv<int, const int&&>();
    test_is_not_same_rv<int, volatile int&&>();
    test_is_not_same_rv<int, const volatile int&&>();

    OverloadTest<char> t;
    (void)t;

    test_is_same_rv<void>();
    test_is_same_rv<phi::nullptr_t>();
    test_is_same_rv<bool>();
    test_is_same_rv<char>();
    test_is_same_rv<signed char>();
    test_is_same_rv<unsigned char>();
    test_is_same_rv<short>();
    test_is_same_rv<unsigned short>();
    test_is_same_rv<int>();
    test_is_same_rv<unsigned int>();
    test_is_same_rv<long>();
    test_is_same_rv<unsigned long>();
    test_is_same_rv<long long>();
    test_is_same_rv<unsigned long long>();
    test_is_same_rv<float>();
    test_is_same_rv<double>();
    test_is_same_rv<long double>();
    test_is_same_rv<char8_t>();
    test_is_same_rv<char16_t>();
    test_is_same_rv<char32_t>();
    test_is_same_rv<wchar_t>();

    test_is_same_rv<phi::boolean>();
    test_is_same_rv<phi::integer<signed char>>();
    test_is_same_rv<phi::integer<unsigned char>>();
    test_is_same_rv<phi::integer<short>>();
    test_is_same_rv<phi::integer<unsigned short>>();
    test_is_same_rv<phi::integer<int>>();
    test_is_same_rv<phi::integer<unsigned int>>();
    test_is_same_rv<phi::integer<long>>();
    test_is_same_rv<phi::integer<unsigned long>>();
    test_is_same_rv<phi::integer<long long>>();
    test_is_same_rv<phi::integer<unsigned long long>>();
    test_is_same_rv<phi::floating_point<float>>();
    test_is_same_rv<phi::floating_point<double>>();
    test_is_same_rv<phi::floating_point<long double>>();

    test_is_same_rv<std::vector<int>>();
    test_is_same_rv<phi::scope_ptr<int>>();

    test_is_same_rv_ref<int&>();
    test_is_same_rv_ref<const int&>();
    test_is_same_rv_ref<volatile int&>();
    test_is_same_rv_ref<const volatile int&>();
    test_is_same_rv_ref<int&&>();
    test_is_same_rv_ref<const int&&>();
    test_is_same_rv_ref<volatile int&&>();
    test_is_same_rv_ref<const volatile int&&>();
    test_is_same_rv<int*>();
    test_is_same_rv<const int*>();
    test_is_same_rv<volatile int*>();
    test_is_same_rv<const volatile int*>();
    test_is_same_rv<int**>();
    test_is_same_rv<const int**>();
    test_is_same_rv<volatile int**>();
    test_is_same_rv<const volatile int**>();
    test_is_same_rv_ref<int*&>();
    test_is_same_rv_ref<const int*&>();
    test_is_same_rv_ref<volatile int*&>();
    test_is_same_rv_ref<const volatile int*&>();
    test_is_same_rv_ref<int*&&>();
    test_is_same_rv_ref<const int*&&>();
    test_is_same_rv_ref<volatile int*&&>();
    test_is_same_rv_ref<const volatile int*&&>();
    test_is_same_rv<void*>();
    test_is_same_rv<char[3]>();
    test_is_same_rv<char[]>();
    test_is_same_rv<char* [3]>();
    test_is_same_rv<char*[]>();
    test_is_same_rv<int(*)[3]>();
    test_is_same_rv<int(*)[]>();
    test_is_same_rv_ref<int(&)[3]>();
    test_is_same_rv_ref<int(&)[]>();
    test_is_same_rv_ref<int(&&)[3]>();
    test_is_same_rv_ref<int(&&)[]>();
    test_is_same_rv<char[3][2]>();
    test_is_same_rv<char[][2]>();
    test_is_same_rv<char* [3][2]>();
    test_is_same_rv<char*[][2]>();
    test_is_same_rv<int(*)[3][2]>();
    test_is_same_rv<int(*)[][2]>();
    test_is_same_rv_ref<int(&)[3][2]>();
    test_is_same_rv_ref<int(&)[][2]>();
    test_is_same_rv_ref<int(&&)[3][2]>();
    test_is_same_rv_ref<int(&&)[][2]>();
    test_is_same_rv<Class>();
    test_is_same_rv<Class[]>();
    test_is_same_rv<Class[2]>();
    test_is_same_rv<Template<void>>();
    test_is_same_rv<Template<int>>();
    test_is_same_rv<Template<Class>>();
    test_is_same_rv<Template<IncompleteType>>();
    test_is_same_rv<VariadicTemplate<>>();
    test_is_same_rv<VariadicTemplate<void>>();
    test_is_same_rv<VariadicTemplate<int>>();
    test_is_same_rv<VariadicTemplate<Class>>();
    test_is_same_rv<VariadicTemplate<IncompleteType>>();
    test_is_same_rv<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_same_rv<PublicDerivedFromTemplate<Base>>();
    test_is_same_rv<PublicDerivedFromTemplate<Derived>>();
    test_is_same_rv<PublicDerivedFromTemplate<Class>>();
    test_is_same_rv<PrivateDerivedFromTemplate<Base>>();
    test_is_same_rv<PrivateDerivedFromTemplate<Derived>>();
    test_is_same_rv<PrivateDerivedFromTemplate<Class>>();
    test_is_same_rv<ProtectedDerivedFromTemplate<Base>>();
    test_is_same_rv<ProtectedDerivedFromTemplate<Derived>>();
    test_is_same_rv<ProtectedDerivedFromTemplate<Class>>();
    test_is_same_rv<VirtualDerivedFromTemplate<Base>>();
    test_is_same_rv<VirtualDerivedFromTemplate<Derived>>();
    test_is_same_rv<VirtualDerivedFromTemplate<Class>>();
    test_is_same_rv<Union>();
    test_is_same_rv<NonEmptyUnion>();
    test_is_same_rv<NonTrivialUnion>();
    test_is_same_rv<Empty>();
    test_is_same_rv<NotEmpty>();
    test_is_same_rv<NonTrivial>();
    test_is_same_rv<BitZero>();
    test_is_same_rv<BitOne>();
    test_is_same_rv<Base>();
    test_is_same_rv<Derived>();
    test_is_same_rv<NotEmptyBase>();
    test_is_same_rv<EmptyBase>();
    test_is_same_rv<VirtualBase>();
    test_is_same_rv<Polymorphic>();
    test_is_same_rv<DerivedPolymorphic>();
    test_is_same_rv<Abstract>();
    test_is_same_rv<PublicAbstract>();
    test_is_same_rv<PrivateAbstract>();
    test_is_same_rv<ProtectedAbstract>();
    test_is_same_rv<AbstractTemplate<int>>();
    test_is_same_rv<AbstractTemplate<double>>();
    test_is_same_rv<AbstractTemplate<Class>>();
    test_is_same_rv<AbstractTemplate<IncompleteType>>();
    test_is_same_rv<PublicAbstractDeletedDestructor>();
    test_is_same_rv<ProtectedAbstractDeletedDestructor>();
    test_is_same_rv<PrivateAbstractDeletedDestructor>();
    test_is_same_rv<Final>();
    test_is_same_rv<FinalDerived>();
    test_is_same_rv<PublicDestructor>();
    test_is_same_rv<ProtectedDestructor>();
    test_is_same_rv<PrivateDestructor>();
    test_is_same_rv<VirtualPublicDestructor>();
    test_is_same_rv<VirtualProtectedDestructor>();
    test_is_same_rv<VirtualPrivateDestructor>();
    test_is_same_rv<PurePublicDestructor>();
    test_is_same_rv<PureProtectedDestructor>();
    test_is_same_rv<PurePrivateDestructor>();
    test_is_same_rv<DeletedPublicDestructor>();
    test_is_same_rv<DeletedProtectedDestructor>();
    test_is_same_rv<DeletedPrivateDestructor>();
    test_is_same_rv<DeletedVirtualPublicDestructor>();
    test_is_same_rv<DeletedVirtualProtectedDestructor>();
    test_is_same_rv<DeletedVirtualPrivateDestructor>();
    test_is_same_rv<ExplicitClass>();
    test_is_same_rv<NothrowExplicitClass>();
    test_is_same_rv<ThrowExplicitClass>();
    test_is_same_rv<ThrowDefaultClass>();
    test_is_same_rv<ThrowCopyConsClass>();
    test_is_same_rv<ThrowMoveConsClass>();
    test_is_same_rv<ThrowDestructor>();
    test_is_same_rv<NoexceptExplicitClass>();
    test_is_same_rv<ExceptExplicitClass>();
    test_is_same_rv<NoexceptDefaultClass>();
    test_is_same_rv<ExceptDefaultClass>();
    test_is_same_rv<NoexceptCopyConsClass>();
    test_is_same_rv<ExceptCopyConsClass>();
    test_is_same_rv<NoexceptMoveConsClass>();
    test_is_same_rv<ExceptMoveConsClass>();
    test_is_same_rv<NoexceptCopyAssignClass>();
    test_is_same_rv<ExceptCopyAssignClass>();
    test_is_same_rv<NoexceptMoveAssignClass>();
    test_is_same_rv<ExceptMoveAssignClass>();
    test_is_same_rv<DeletedCopyAssignClass>();
    test_is_same_rv<DeletedMoveAssignClass>();
    test_is_same_rv<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_same_rv<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_same_rv<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_same_rv<ExceptMoveConsExceptMoveAssignClass>();
    test_is_same_rv<ImplicitTo<int>>();
    test_is_same_rv<ImplicitTo<float>>();
    test_is_same_rv<ImplicitTo<Class>>();
    test_is_same_rv<DeletedImplicitTo<int>>();
    test_is_same_rv<DeletedImplicitTo<float>>();
    test_is_same_rv<DeletedImplicitTo<Class>>();
    test_is_same_rv<ExplicitTo<int>>();
    test_is_same_rv<ExplicitTo<float>>();
    test_is_same_rv<ExplicitTo<Class>>();
    test_is_same_rv<DeletedExplicitTo<int>>();
    test_is_same_rv<DeletedExplicitTo<float>>();
    test_is_same_rv<DeletedExplicitTo<Class>>();
    test_is_same_rv<Ellipsis>();
    test_is_same_rv<DeletedEllipsis>();
    test_is_same_rv<CopyConsOnlyType>();
    test_is_same_rv<MoveConsOnlyType>();
    test_is_same_rv<OverloadedOperators>();
    test_is_same_rv<PublicIntMember>();
    test_is_same_rv<ProtectedIntMember>();
    test_is_same_rv<PrivateIntMember>();
    test_is_same_rv<PublicStaticIntMember>();
    test_is_same_rv<ProtectedStaticIntMember>();
    test_is_same_rv<PrivateStaticIntMember>();
    test_is_same_rv<PublicTemplateMember<int>>();
    test_is_same_rv<PublicTemplateMember<float>>();
    test_is_same_rv<PublicTemplateMember<Class>>();
    test_is_same_rv<ProtectedTemplateMember<int>>();
    test_is_same_rv<ProtectedTemplateMember<float>>();
    test_is_same_rv<ProtectedTemplateMember<Class>>();
    test_is_same_rv<PrivateTemplateMember<int>>();
    test_is_same_rv<PrivateTemplateMember<float>>();
    test_is_same_rv<PrivateTemplateMember<Class>>();
    test_is_same_rv<PublicStaticTemplateMember<int>>();
    test_is_same_rv<PublicStaticTemplateMember<float>>();
    test_is_same_rv<PublicStaticTemplateMember<Class>>();
    test_is_same_rv<ProtectedStaticTemplateMember<int>>();
    test_is_same_rv<ProtectedStaticTemplateMember<float>>();
    test_is_same_rv<ProtectedStaticTemplateMember<Class>>();
    test_is_same_rv<PrivateStaticTemplateMember<int>>();
    test_is_same_rv<PrivateStaticTemplateMember<float>>();
    test_is_same_rv<PrivateStaticTemplateMember<Class>>();
    test_is_same_rv<CannotInstantiate<int>>();
    test_is_same_rv<CannotInstantiate<float>>();
    test_is_same_rv<CannotInstantiate<Class>>();
    test_is_same_rv<natural_alignment>();
    test_is_same_rv<Enum>();
    test_is_same_rv<EnumSigned>();
    test_is_same_rv<EnumUnsigned>();
    test_is_same_rv<EnumClass>();
    test_is_same_rv<EnumStruct>();
    test_is_same_rv_ref<Function>();
    test_is_same_rv<FunctionPtr>();
    test_is_same_rv<MemberObjectPtr>();
    test_is_same_rv<MemberFunctionPtr>();
    test_is_same_rv<LambdaType>();
    test_is_same_rv<LambdaNoexceptType>();
    test_is_same_rv<LambdaThrowsType>();
    test_is_same_rv<IncompleteType>();
    test_is_same_rv<IncompleteTemplate<void>>();
    test_is_same_rv<IncompleteTemplate<int>>();
    test_is_same_rv<IncompleteTemplate<Class>>();
    test_is_same_rv<IncompleteTemplate<IncompleteType>>();
    test_is_same_rv<IncompleteVariadicTemplate<>>();
    test_is_same_rv<IncompleteVariadicTemplate<void>>();
    test_is_same_rv<IncompleteVariadicTemplate<int>>();
    test_is_same_rv<IncompleteVariadicTemplate<Class>>();
    test_is_same_rv<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_same_rv<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_same_rv<IncompleteUnion>();
    test_is_same_rv<IncompleteEnumSigned>();
    test_is_same_rv<IncompleteEnumUnsigned>();
    test_is_same_rv<IncompleteEnumClass>();
    test_is_same_rv<IncompleteEnumStruct>();
    test_is_same_rv<int Class::*>();
    test_is_same_rv<float Class::*>();
    test_is_same_rv<void * Class::*>();
    test_is_same_rv<int * Class::*>();
    test_is_same_rv<Enum Class::*>();
    test_is_same_rv<NotEmpty Class::*>();
    test_is_same_rv_ref<int Class::*&>();
    test_is_same_rv_ref<float Class::*&>();
    test_is_same_rv_ref<void * Class::*&>();
    test_is_same_rv_ref<int * Class::*&>();
    test_is_same_rv_ref<Enum Class::*&>();
    test_is_same_rv_ref<NotEmpty Class::*&>();
    test_is_same_rv_ref<int Class::*&&>();
    test_is_same_rv_ref<float Class::*&&>();
    test_is_same_rv_ref<void * Class::*&&>();
    test_is_same_rv_ref<int * Class::*&&>();
    test_is_same_rv_ref<Enum Class::*&&>();
    test_is_same_rv_ref<NotEmpty Class::*&&>();
    test_is_same_rv<NonDefaultConstructible>();
    test_is_same_rv<NonCopyConstructible>();
    test_is_same_rv<NonMoveConstructible>();
    test_is_same_rv<NonCopyAssignable>();
    test_is_same_rv<NonMoveAssignable>();
    test_is_same_rv<NonAssignable>();
    test_is_same_rv<NonCopyable>();
    test_is_same_rv<NonMoveable>();
    test_is_same_rv<NonConstructible>();
    test_is_same_rv<NonDestructible>();
    test_is_same_rv<Tracked>();
    test_is_same_rv<TrapConstructible>();
    test_is_same_rv<TrapImplicitConversion>();
    test_is_same_rv<TrapComma>();
    test_is_same_rv<TrapCall>();
    test_is_same_rv<TrapSelfAssign>();
    test_is_same_rv<TrapDeref>();
    test_is_same_rv<TrapArraySubscript>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY()
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_is_same_rv<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_is_same_rv_ref<void()>();
    test_is_same_rv_ref<void()&>();
    test_is_same_rv_ref<void() &&>();
    test_is_same_rv_ref<void() const>();
    test_is_same_rv_ref<void() const&>();
    test_is_same_rv_ref<void() const&&>();
    test_is_same_rv_ref<void() volatile>();
    test_is_same_rv_ref<void() volatile&>();
    test_is_same_rv_ref<void() volatile&&>();
    test_is_same_rv_ref<void() const volatile>();
    test_is_same_rv_ref<void() const volatile&>();
    test_is_same_rv_ref<void() const volatile&&>();
    test_is_same_rv_ref<void() noexcept>();
    test_is_same_rv_ref<void()& noexcept>();
    test_is_same_rv_ref<void()&& noexcept>();
    test_is_same_rv_ref<void() const noexcept>();
    test_is_same_rv_ref<void() const& noexcept>();
    test_is_same_rv_ref<void() const&& noexcept>();
    test_is_same_rv_ref<void() volatile noexcept>();
    test_is_same_rv_ref<void() volatile& noexcept>();
    test_is_same_rv_ref<void() volatile&& noexcept>();
    test_is_same_rv_ref<void() const volatile noexcept>();
    test_is_same_rv_ref<void() const volatile& noexcept>();
    test_is_same_rv_ref<void() const volatile&& noexcept>();

    test_is_same_rv_ref<void(int)>();
    test_is_same_rv_ref<void(int)&>();
    test_is_same_rv_ref<void(int) &&>();
    test_is_same_rv_ref<void(int) const>();
    test_is_same_rv_ref<void(int) const&>();
    test_is_same_rv_ref<void(int) const&&>();
    test_is_same_rv_ref<void(int) volatile>();
    test_is_same_rv_ref<void(int) volatile&>();
    test_is_same_rv_ref<void(int) volatile&&>();
    test_is_same_rv_ref<void(int) const volatile>();
    test_is_same_rv_ref<void(int) const volatile&>();
    test_is_same_rv_ref<void(int) const volatile&&>();
    test_is_same_rv_ref<void(int) noexcept>();
    test_is_same_rv_ref<void(int)& noexcept>();
    test_is_same_rv_ref<void(int)&& noexcept>();
    test_is_same_rv_ref<void(int) const noexcept>();
    test_is_same_rv_ref<void(int) const& noexcept>();
    test_is_same_rv_ref<void(int) const&& noexcept>();
    test_is_same_rv_ref<void(int) volatile noexcept>();
    test_is_same_rv_ref<void(int) volatile& noexcept>();
    test_is_same_rv_ref<void(int) volatile&& noexcept>();
    test_is_same_rv_ref<void(int) const volatile noexcept>();
    test_is_same_rv_ref<void(int) const volatile& noexcept>();
    test_is_same_rv_ref<void(int) const volatile&& noexcept>();

    test_is_same_rv_ref<void(...)>();
    test_is_same_rv_ref<void(...)&>();
    test_is_same_rv_ref<void(...) &&>();
    test_is_same_rv_ref<void(...) const>();
    test_is_same_rv_ref<void(...) const&>();
    test_is_same_rv_ref<void(...) const&&>();
    test_is_same_rv_ref<void(...) volatile>();
    test_is_same_rv_ref<void(...) volatile&>();
    test_is_same_rv_ref<void(...) volatile&&>();
    test_is_same_rv_ref<void(...) const volatile>();
    test_is_same_rv_ref<void(...) const volatile&>();
    test_is_same_rv_ref<void(...) const volatile&&>();
    test_is_same_rv_ref<void(...) noexcept>();
    test_is_same_rv_ref<void(...)& noexcept>();
    test_is_same_rv_ref<void(...)&& noexcept>();
    test_is_same_rv_ref<void(...) const noexcept>();
    test_is_same_rv_ref<void(...) const& noexcept>();
    test_is_same_rv_ref<void(...) const&& noexcept>();
    test_is_same_rv_ref<void(...) volatile noexcept>();
    test_is_same_rv_ref<void(...) volatile& noexcept>();
    test_is_same_rv_ref<void(...) volatile&& noexcept>();
    test_is_same_rv_ref<void(...) const volatile noexcept>();
    test_is_same_rv_ref<void(...) const volatile& noexcept>();
    test_is_same_rv_ref<void(...) const volatile&& noexcept>();

    test_is_same_rv_ref<void(int, ...)>();
    test_is_same_rv_ref<void(int, ...)&>();
    test_is_same_rv_ref<void(int, ...) &&>();
    test_is_same_rv_ref<void(int, ...) const>();
    test_is_same_rv_ref<void(int, ...) const&>();
    test_is_same_rv_ref<void(int, ...) const&&>();
    test_is_same_rv_ref<void(int, ...) volatile>();
    test_is_same_rv_ref<void(int, ...) volatile&>();
    test_is_same_rv_ref<void(int, ...) volatile&&>();
    test_is_same_rv_ref<void(int, ...) const volatile>();
    test_is_same_rv_ref<void(int, ...) const volatile&>();
    test_is_same_rv_ref<void(int, ...) const volatile&&>();
    test_is_same_rv_ref<void(int, ...) noexcept>();
    test_is_same_rv_ref<void(int, ...)& noexcept>();
    test_is_same_rv_ref<void(int, ...)&& noexcept>();
    test_is_same_rv_ref<void(int, ...) const noexcept>();
    test_is_same_rv_ref<void(int, ...) const& noexcept>();
    test_is_same_rv_ref<void(int, ...) const&& noexcept>();
    test_is_same_rv_ref<void(int, ...) volatile noexcept>();
    test_is_same_rv_ref<void(int, ...) volatile& noexcept>();
    test_is_same_rv_ref<void(int, ...) volatile&& noexcept>();
    test_is_same_rv_ref<void(int, ...) const volatile noexcept>();
    test_is_same_rv_ref<void(int, ...) const volatile& noexcept>();
    test_is_same_rv_ref<void(int, ...) const volatile&& noexcept>();

    test_is_same_rv_ref<int()>();
    test_is_same_rv_ref<int()&>();
    test_is_same_rv_ref<int() &&>();
    test_is_same_rv_ref<int() const>();
    test_is_same_rv_ref<int() const&>();
    test_is_same_rv_ref<int() const&&>();
    test_is_same_rv_ref<int() volatile>();
    test_is_same_rv_ref<int() volatile&>();
    test_is_same_rv_ref<int() volatile&&>();
    test_is_same_rv_ref<int() const volatile>();
    test_is_same_rv_ref<int() const volatile&>();
    test_is_same_rv_ref<int() const volatile&&>();
    test_is_same_rv_ref<int() noexcept>();
    test_is_same_rv_ref<int()& noexcept>();
    test_is_same_rv_ref<int()&& noexcept>();
    test_is_same_rv_ref<int() const noexcept>();
    test_is_same_rv_ref<int() const& noexcept>();
    test_is_same_rv_ref<int() const&& noexcept>();
    test_is_same_rv_ref<int() volatile noexcept>();
    test_is_same_rv_ref<int() volatile& noexcept>();
    test_is_same_rv_ref<int() volatile&& noexcept>();
    test_is_same_rv_ref<int() const volatile noexcept>();
    test_is_same_rv_ref<int() const volatile& noexcept>();
    test_is_same_rv_ref<int() const volatile&& noexcept>();

    test_is_same_rv_ref<int(int)>();
    test_is_same_rv_ref<int(int)&>();
    test_is_same_rv_ref<int(int) &&>();
    test_is_same_rv_ref<int(int) const>();
    test_is_same_rv_ref<int(int) const&>();
    test_is_same_rv_ref<int(int) const&&>();
    test_is_same_rv_ref<int(int) volatile>();
    test_is_same_rv_ref<int(int) volatile&>();
    test_is_same_rv_ref<int(int) volatile&&>();
    test_is_same_rv_ref<int(int) const volatile>();
    test_is_same_rv_ref<int(int) const volatile&>();
    test_is_same_rv_ref<int(int) const volatile&&>();
    test_is_same_rv_ref<int(int) noexcept>();
    test_is_same_rv_ref<int(int)& noexcept>();
    test_is_same_rv_ref<int(int)&& noexcept>();
    test_is_same_rv_ref<int(int) const noexcept>();
    test_is_same_rv_ref<int(int) const& noexcept>();
    test_is_same_rv_ref<int(int) const&& noexcept>();
    test_is_same_rv_ref<int(int) volatile noexcept>();
    test_is_same_rv_ref<int(int) volatile& noexcept>();
    test_is_same_rv_ref<int(int) volatile&& noexcept>();
    test_is_same_rv_ref<int(int) const volatile noexcept>();
    test_is_same_rv_ref<int(int) const volatile& noexcept>();
    test_is_same_rv_ref<int(int) const volatile&& noexcept>();

    test_is_same_rv_ref<int(...)>();
    test_is_same_rv_ref<int(...)&>();
    test_is_same_rv_ref<int(...) &&>();
    test_is_same_rv_ref<int(...) const>();
    test_is_same_rv_ref<int(...) const&>();
    test_is_same_rv_ref<int(...) const&&>();
    test_is_same_rv_ref<int(...) volatile>();
    test_is_same_rv_ref<int(...) volatile&>();
    test_is_same_rv_ref<int(...) volatile&&>();
    test_is_same_rv_ref<int(...) const volatile>();
    test_is_same_rv_ref<int(...) const volatile&>();
    test_is_same_rv_ref<int(...) const volatile&&>();
    test_is_same_rv_ref<int(...) noexcept>();
    test_is_same_rv_ref<int(...)& noexcept>();
    test_is_same_rv_ref<int(...)&& noexcept>();
    test_is_same_rv_ref<int(...) const noexcept>();
    test_is_same_rv_ref<int(...) const& noexcept>();
    test_is_same_rv_ref<int(...) const&& noexcept>();
    test_is_same_rv_ref<int(...) volatile noexcept>();
    test_is_same_rv_ref<int(...) volatile& noexcept>();
    test_is_same_rv_ref<int(...) volatile&& noexcept>();
    test_is_same_rv_ref<int(...) const volatile noexcept>();
    test_is_same_rv_ref<int(...) const volatile& noexcept>();
    test_is_same_rv_ref<int(...) const volatile&& noexcept>();

    test_is_same_rv_ref<int(int, ...)>();
    test_is_same_rv_ref<int(int, ...)&>();
    test_is_same_rv_ref<int(int, ...) &&>();
    test_is_same_rv_ref<int(int, ...) const>();
    test_is_same_rv_ref<int(int, ...) const&>();
    test_is_same_rv_ref<int(int, ...) const&&>();
    test_is_same_rv_ref<int(int, ...) volatile>();
    test_is_same_rv_ref<int(int, ...) volatile&>();
    test_is_same_rv_ref<int(int, ...) volatile&&>();
    test_is_same_rv_ref<int(int, ...) const volatile>();
    test_is_same_rv_ref<int(int, ...) const volatile&>();
    test_is_same_rv_ref<int(int, ...) const volatile&&>();
    test_is_same_rv_ref<int(int, ...) noexcept>();
    test_is_same_rv_ref<int(int, ...)& noexcept>();
    test_is_same_rv_ref<int(int, ...)&& noexcept>();
    test_is_same_rv_ref<int(int, ...) const noexcept>();
    test_is_same_rv_ref<int(int, ...) const& noexcept>();
    test_is_same_rv_ref<int(int, ...) const&& noexcept>();
    test_is_same_rv_ref<int(int, ...) volatile noexcept>();
    test_is_same_rv_ref<int(int, ...) volatile& noexcept>();
    test_is_same_rv_ref<int(int, ...) volatile&& noexcept>();
    test_is_same_rv_ref<int(int, ...) const volatile noexcept>();
    test_is_same_rv_ref<int(int, ...) const volatile& noexcept>();
    test_is_same_rv_ref<int(int, ...) const volatile&& noexcept>();

    test_is_same_rv<void (*)()>();
    test_is_same_rv<void (*)() noexcept>();

    test_is_same_rv<void (*)(int)>();
    test_is_same_rv<void (*)(int) noexcept>();

    test_is_same_rv<void (*)(...)>();
    test_is_same_rv<void (*)(...) noexcept>();

    test_is_same_rv<void (*)(int, ...)>();
    test_is_same_rv<void (*)(int, ...) noexcept>();

    test_is_same_rv<int (*)()>();
    test_is_same_rv<int (*)() noexcept>();

    test_is_same_rv<int (*)(int)>();
    test_is_same_rv<int (*)(int) noexcept>();

    test_is_same_rv<int (*)(...)>();
    test_is_same_rv<int (*)(...) noexcept>();

    test_is_same_rv<int (*)(int, ...)>();
    test_is_same_rv<int (*)(int, ...) noexcept>();

    test_is_same_rv_ref<void (&)()>();
    test_is_same_rv_ref<void (&)() noexcept>();

    test_is_same_rv_ref<void (&)(int)>();
    test_is_same_rv_ref<void (&)(int) noexcept>();

    test_is_same_rv_ref<void (&)(...)>();
    test_is_same_rv_ref<void (&)(...) noexcept>();

    test_is_same_rv_ref<void (&)(int, ...)>();
    test_is_same_rv_ref<void (&)(int, ...) noexcept>();

    test_is_same_rv_ref<int (&)()>();
    test_is_same_rv_ref<int (&)() noexcept>();

    test_is_same_rv_ref<int (&)(int)>();
    test_is_same_rv_ref<int (&)(int) noexcept>();

    test_is_same_rv_ref<int (&)(...)>();
    test_is_same_rv_ref<int (&)(...) noexcept>();

    test_is_same_rv_ref<int (&)(int, ...)>();
    test_is_same_rv_ref<int (&)(int, ...) noexcept>();

    test_is_same_rv_ref<void(&&)()>();
    test_is_same_rv_ref<void(&&)() noexcept>();

    test_is_same_rv_ref<void(&&)(int)>();
    test_is_same_rv_ref<void(&&)(int) noexcept>();

    test_is_same_rv_ref<void(&&)(...)>();
    test_is_same_rv_ref<void(&&)(...) noexcept>();

    test_is_same_rv_ref<void(&&)(int, ...)>();
    test_is_same_rv_ref<void(&&)(int, ...) noexcept>();

    test_is_same_rv_ref<int(&&)()>();
    test_is_same_rv_ref<int(&&)() noexcept>();

    test_is_same_rv_ref<int(&&)(int)>();
    test_is_same_rv_ref<int(&&)(int) noexcept>();

    test_is_same_rv_ref<int(&&)(...)>();
    test_is_same_rv_ref<int(&&)(...) noexcept>();

    test_is_same_rv_ref<int(&&)(int, ...)>();
    test_is_same_rv_ref<int(&&)(int, ...) noexcept>();

    test_is_same_rv<void (Class::*)()>();
    test_is_same_rv<void (Class::*)()&>();
    test_is_same_rv<void (Class::*)() &&>();
    test_is_same_rv<void (Class::*)() const>();
    test_is_same_rv<void (Class::*)() const&>();
    test_is_same_rv<void (Class::*)() const&&>();
    test_is_same_rv<void (Class::*)() noexcept>();
    test_is_same_rv<void (Class::*)()& noexcept>();
    test_is_same_rv<void (Class::*)()&& noexcept>();
    test_is_same_rv<void (Class::*)() const noexcept>();
    test_is_same_rv<void (Class::*)() const& noexcept>();
    test_is_same_rv<void (Class::*)() const&& noexcept>();

    test_is_same_rv<void (Class::*)(int)>();
    test_is_same_rv<void (Class::*)(int)&>();
    test_is_same_rv<void (Class::*)(int) &&>();
    test_is_same_rv<void (Class::*)(int) const>();
    test_is_same_rv<void (Class::*)(int) const&>();
    test_is_same_rv<void (Class::*)(int) const&&>();
    test_is_same_rv<void (Class::*)(int) noexcept>();
    test_is_same_rv<void (Class::*)(int)& noexcept>();
    test_is_same_rv<void (Class::*)(int)&& noexcept>();
    test_is_same_rv<void (Class::*)(int) const noexcept>();
    test_is_same_rv<void (Class::*)(int) const& noexcept>();
    test_is_same_rv<void (Class::*)(int) const&& noexcept>();

    test_is_same_rv<void (Class::*)(...)>();
    test_is_same_rv<void (Class::*)(...)&>();
    test_is_same_rv<void (Class::*)(...) &&>();
    test_is_same_rv<void (Class::*)(...) const>();
    test_is_same_rv<void (Class::*)(...) const&>();
    test_is_same_rv<void (Class::*)(...) const&&>();
    test_is_same_rv<void (Class::*)(...) noexcept>();
    test_is_same_rv<void (Class::*)(...)& noexcept>();
    test_is_same_rv<void (Class::*)(...)&& noexcept>();
    test_is_same_rv<void (Class::*)(...) const noexcept>();
    test_is_same_rv<void (Class::*)(...) const& noexcept>();
    test_is_same_rv<void (Class::*)(...) const&& noexcept>();

    test_is_same_rv<void (Class::*)(int, ...)>();
    test_is_same_rv<void (Class::*)(int, ...)&>();
    test_is_same_rv<void (Class::*)(int, ...) &&>();
    test_is_same_rv<void (Class::*)(int, ...) const>();
    test_is_same_rv<void (Class::*)(int, ...) const&>();
    test_is_same_rv<void (Class::*)(int, ...) const&&>();
    test_is_same_rv<void (Class::*)(int, ...) noexcept>();
    test_is_same_rv<void (Class::*)(int, ...)& noexcept>();
    test_is_same_rv<void (Class::*)(int, ...)&& noexcept>();
    test_is_same_rv<void (Class::*)(int, ...) const noexcept>();
    test_is_same_rv<void (Class::*)(int, ...) const& noexcept>();
    test_is_same_rv<void (Class::*)(int, ...) const&& noexcept>();

    test_is_same_rv<int (Class::*)()>();
    test_is_same_rv<int (Class::*)()&>();
    test_is_same_rv<int (Class::*)() &&>();
    test_is_same_rv<int (Class::*)() const>();
    test_is_same_rv<int (Class::*)() const&>();
    test_is_same_rv<int (Class::*)() const&&>();
    test_is_same_rv<int (Class::*)() noexcept>();
    test_is_same_rv<int (Class::*)()& noexcept>();
    test_is_same_rv<int (Class::*)()&& noexcept>();
    test_is_same_rv<int (Class::*)() const noexcept>();
    test_is_same_rv<int (Class::*)() const& noexcept>();
    test_is_same_rv<int (Class::*)() const&& noexcept>();

    test_is_same_rv<int (Class::*)(int)>();
    test_is_same_rv<int (Class::*)(int)&>();
    test_is_same_rv<int (Class::*)(int) &&>();
    test_is_same_rv<int (Class::*)(int) const>();
    test_is_same_rv<int (Class::*)(int) const&>();
    test_is_same_rv<int (Class::*)(int) const&&>();
    test_is_same_rv<int (Class::*)(int) noexcept>();
    test_is_same_rv<int (Class::*)(int)& noexcept>();
    test_is_same_rv<int (Class::*)(int)&& noexcept>();
    test_is_same_rv<int (Class::*)(int) const noexcept>();
    test_is_same_rv<int (Class::*)(int) const& noexcept>();
    test_is_same_rv<int (Class::*)(int) const&& noexcept>();

    test_is_same_rv<int (Class::*)(...)>();
    test_is_same_rv<int (Class::*)(...)&>();
    test_is_same_rv<int (Class::*)(...) &&>();
    test_is_same_rv<int (Class::*)(...) const>();
    test_is_same_rv<int (Class::*)(...) const&>();
    test_is_same_rv<int (Class::*)(...) const&&>();
    test_is_same_rv<int (Class::*)(...) noexcept>();
    test_is_same_rv<int (Class::*)(...)& noexcept>();
    test_is_same_rv<int (Class::*)(...)&& noexcept>();
    test_is_same_rv<int (Class::*)(...) const noexcept>();
    test_is_same_rv<int (Class::*)(...) const& noexcept>();
    test_is_same_rv<int (Class::*)(...) const&& noexcept>();

    test_is_same_rv<int (Class::*)(int, ...)>();
    test_is_same_rv<int (Class::*)(int, ...)&>();
    test_is_same_rv<int (Class::*)(int, ...) &&>();
    test_is_same_rv<int (Class::*)(int, ...) const>();
    test_is_same_rv<int (Class::*)(int, ...) const&>();
    test_is_same_rv<int (Class::*)(int, ...) const&&>();
    test_is_same_rv<int (Class::*)(int, ...) noexcept>();
    test_is_same_rv<int (Class::*)(int, ...)& noexcept>();
    test_is_same_rv<int (Class::*)(int, ...)&& noexcept>();
    test_is_same_rv<int (Class::*)(int, ...) const noexcept>();
    test_is_same_rv<int (Class::*)(int, ...) const& noexcept>();
    test_is_same_rv<int (Class::*)(int, ...) const&& noexcept>();
}
