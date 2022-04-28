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
#include <phi/type_traits/is_same.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_is_same_impl()
{
    STATIC_REQUIRE(phi::is_same<T, U>::value);
    STATIC_REQUIRE(phi::is_same<U, T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_v<T, U>);
    STATIC_REQUIRE(phi::is_same_v<U, T>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same<T, U>);
}

template <typename T, typename U>
void test_is_not_same()
{
    STATIC_REQUIRE_FALSE(phi::is_same<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same<U, T>::value);
    STATIC_REQUIRE(phi::is_not_same<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_v<U, T>);
    STATIC_REQUIRE(phi::is_not_same_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same<T, U>);
}

template <typename T, typename U = T>
void test_is_same()
{
    test_is_same_impl<T, U>();
    test_is_not_same<T, const U>();
    test_is_not_same<T, volatile U>();
    test_is_not_same<T, const volatile U>();

    test_is_not_same<const T, U>();
    test_is_same_impl<const T, const U>();
    test_is_not_same<const T, volatile U>();
    test_is_not_same<const T, const volatile U>();

    test_is_not_same<volatile T, U>();
    test_is_not_same<volatile T, const U>();
    test_is_same_impl<volatile T, volatile U>();
    test_is_not_same<volatile T, const volatile U>();

    test_is_not_same<const volatile T, U>();
    test_is_not_same<const volatile T, const U>();
    test_is_not_same<const volatile T, volatile U>();
    test_is_same_impl<const volatile T, const volatile U>();
}

template <typename T, typename U = T>
void test_is_same_ref()
{
    test_is_same_impl<T, U>();
    test_is_same_impl<T, const U>();
    test_is_same_impl<T, volatile U>();
    test_is_same_impl<T, const volatile U>();

    test_is_same_impl<const T, U>();
    test_is_same_impl<const T, const U>();
    test_is_same_impl<const T, volatile U>();
    test_is_same_impl<const T, const volatile U>();

    test_is_same_impl<volatile T, U>();
    test_is_same_impl<volatile T, const U>();
    test_is_same_impl<volatile T, volatile U>();
    test_is_same_impl<volatile T, const volatile U>();

    test_is_same_impl<const volatile T, U>();
    test_is_same_impl<const volatile T, const U>();
    test_is_same_impl<const volatile T, volatile U>();
    test_is_same_impl<const volatile T, const volatile U>();
}

template <typename T>
struct OverloadTest
{
    void fn(phi::is_same<T, int>)
    {}
    void fn(phi::false_type)
    {}
    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same")
{
    test_is_not_same<int, void>();
    test_is_not_same<void, Class>();
    test_is_not_same<Class, int*>();
    test_is_not_same<int*, int&>();
    test_is_not_same<int&, int>();

    test_is_not_same<int, const int>();
    test_is_not_same<int, volatile int>();
    test_is_not_same<int, const volatile int>();
    test_is_not_same<int, int&>();
    test_is_not_same<int, const int&>();
    test_is_not_same<int, volatile int&>();
    test_is_not_same<int, const volatile int&>();
    test_is_not_same<int, int&&>();
    test_is_not_same<int, const int&&>();
    test_is_not_same<int, volatile int&&>();
    test_is_not_same<int, const volatile int&&>();

    OverloadTest<char> t;
    (void)t;

    test_is_same<void>();
    test_is_same<phi::nullptr_t>();
    test_is_same<bool>();
    test_is_same<char>();
    test_is_same<signed char>();
    test_is_same<unsigned char>();
    test_is_same<short>();
    test_is_same<unsigned short>();
    test_is_same<int>();
    test_is_same<unsigned int>();
    test_is_same<long>();
    test_is_same<unsigned long>();
    test_is_same<long long>();
    test_is_same<unsigned long long>();
    test_is_same<float>();
    test_is_same<double>();
    test_is_same<long double>();
    test_is_same<char8_t>();
    test_is_same<char16_t>();
    test_is_same<char32_t>();
    test_is_same<wchar_t>();

    test_is_same<phi::boolean>();
    test_is_same<phi::integer<signed char>>();
    test_is_same<phi::integer<unsigned char>>();
    test_is_same<phi::integer<short>>();
    test_is_same<phi::integer<unsigned short>>();
    test_is_same<phi::integer<int>>();
    test_is_same<phi::integer<unsigned int>>();
    test_is_same<phi::integer<long>>();
    test_is_same<phi::integer<unsigned long>>();
    test_is_same<phi::integer<long long>>();
    test_is_same<phi::integer<unsigned long long>>();
    test_is_same<phi::floating_point<float>>();
    test_is_same<phi::floating_point<double>>();
    test_is_same<phi::floating_point<long double>>();

    test_is_same<std::vector<int>>();
    test_is_same<phi::scope_ptr<int>>();

    test_is_same_ref<int&>();
    test_is_same_ref<const int&>();
    test_is_same_ref<volatile int&>();
    test_is_same_ref<const volatile int&>();
    test_is_same_ref<int&&>();
    test_is_same_ref<const int&&>();
    test_is_same_ref<volatile int&&>();
    test_is_same_ref<const volatile int&&>();
    test_is_same<int*>();
    test_is_same<const int*>();
    test_is_same<volatile int*>();
    test_is_same<const volatile int*>();
    test_is_same<int**>();
    test_is_same<const int**>();
    test_is_same<volatile int**>();
    test_is_same<const volatile int**>();
    test_is_same_ref<int*&>();
    test_is_same_ref<const int*&>();
    test_is_same_ref<volatile int*&>();
    test_is_same_ref<const volatile int*&>();
    test_is_same_ref<int*&&>();
    test_is_same_ref<const int*&&>();
    test_is_same_ref<volatile int*&&>();
    test_is_same_ref<const volatile int*&&>();
    test_is_same<void*>();
    test_is_same<char[3]>();
    test_is_same<char[]>();
    test_is_same<char* [3]>();
    test_is_same<char*[]>();
    test_is_same<int(*)[3]>();
    test_is_same<int(*)[]>();
    test_is_same_ref<int(&)[3]>();
    test_is_same_ref<int(&)[]>();
    test_is_same_ref<int(&&)[3]>();
    test_is_same_ref<int(&&)[]>();
    test_is_same<char[3][2]>();
    test_is_same<char[][2]>();
    test_is_same<char* [3][2]>();
    test_is_same<char*[][2]>();
    test_is_same<int(*)[3][2]>();
    test_is_same<int(*)[][2]>();
    test_is_same_ref<int(&)[3][2]>();
    test_is_same_ref<int(&)[][2]>();
    test_is_same_ref<int(&&)[3][2]>();
    test_is_same_ref<int(&&)[][2]>();
    test_is_same<Class>();
    test_is_same<Class[]>();
    test_is_same<Class[2]>();
    test_is_same<Template<void>>();
    test_is_same<Template<int>>();
    test_is_same<Template<Class>>();
    test_is_same<Template<IncompleteType>>();
    test_is_same<VariadicTemplate<>>();
    test_is_same<VariadicTemplate<void>>();
    test_is_same<VariadicTemplate<int>>();
    test_is_same<VariadicTemplate<Class>>();
    test_is_same<VariadicTemplate<IncompleteType>>();
    test_is_same<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_same<PublicDerivedFromTemplate<Base>>();
    test_is_same<PublicDerivedFromTemplate<Derived>>();
    test_is_same<PublicDerivedFromTemplate<Class>>();
    test_is_same<PrivateDerivedFromTemplate<Base>>();
    test_is_same<PrivateDerivedFromTemplate<Derived>>();
    test_is_same<PrivateDerivedFromTemplate<Class>>();
    test_is_same<ProtectedDerivedFromTemplate<Base>>();
    test_is_same<ProtectedDerivedFromTemplate<Derived>>();
    test_is_same<ProtectedDerivedFromTemplate<Class>>();
    test_is_same<VirtualDerivedFromTemplate<Base>>();
    test_is_same<VirtualDerivedFromTemplate<Derived>>();
    test_is_same<VirtualDerivedFromTemplate<Class>>();
    test_is_same<Union>();
    test_is_same<NonEmptyUnion>();
    test_is_same<NonTrivialUnion>();
    test_is_same<Empty>();
    test_is_same<NotEmpty>();
    test_is_same<NonTrivial>();
    test_is_same<BitZero>();
    test_is_same<BitOne>();
    test_is_same<Base>();
    test_is_same<Derived>();
    test_is_same<NotEmptyBase>();
    test_is_same<EmptyBase>();
    test_is_same<VirtualBase>();
    test_is_same<Polymorphic>();
    test_is_same<DerivedPolymorphic>();
    test_is_same<Abstract>();
    test_is_same<PublicAbstract>();
    test_is_same<PrivateAbstract>();
    test_is_same<ProtectedAbstract>();
    test_is_same<AbstractTemplate<int>>();
    test_is_same<AbstractTemplate<double>>();
    test_is_same<AbstractTemplate<Class>>();
    test_is_same<AbstractTemplate<IncompleteType>>();
    test_is_same<PublicAbstractDeletedDestructor>();
    test_is_same<ProtectedAbstractDeletedDestructor>();
    test_is_same<PrivateAbstractDeletedDestructor>();
    test_is_same<Final>();
    test_is_same<FinalDerived>();
    test_is_same<PublicDestructor>();
    test_is_same<ProtectedDestructor>();
    test_is_same<PrivateDestructor>();
    test_is_same<VirtualPublicDestructor>();
    test_is_same<VirtualProtectedDestructor>();
    test_is_same<VirtualPrivateDestructor>();
    test_is_same<PurePublicDestructor>();
    test_is_same<PureProtectedDestructor>();
    test_is_same<PurePrivateDestructor>();
    test_is_same<DeletedPublicDestructor>();
    test_is_same<DeletedProtectedDestructor>();
    test_is_same<DeletedPrivateDestructor>();
    test_is_same<DeletedVirtualPublicDestructor>();
    test_is_same<DeletedVirtualProtectedDestructor>();
    test_is_same<DeletedVirtualPrivateDestructor>();
    test_is_same<ExplicitClass>();
    test_is_same<NothrowExplicitClass>();
    test_is_same<ThrowExplicitClass>();
    test_is_same<ThrowDefaultClass>();
    test_is_same<ThrowCopyConsClass>();
    test_is_same<ThrowMoveConsClass>();
    test_is_same<ThrowDestructor>();
    test_is_same<NoexceptExplicitClass>();
    test_is_same<ExceptExplicitClass>();
    test_is_same<NoexceptDefaultClass>();
    test_is_same<ExceptDefaultClass>();
    test_is_same<NoexceptCopyConsClass>();
    test_is_same<ExceptCopyConsClass>();
    test_is_same<NoexceptMoveConsClass>();
    test_is_same<ExceptMoveConsClass>();
    test_is_same<NoexceptCopyAssignClass>();
    test_is_same<ExceptCopyAssignClass>();
    test_is_same<NoexceptMoveAssignClass>();
    test_is_same<ExceptMoveAssignClass>();
    test_is_same<DeletedCopyAssignClass>();
    test_is_same<DeletedMoveAssignClass>();
    test_is_same<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_same<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_same<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_same<ExceptMoveConsExceptMoveAssignClass>();
    test_is_same<ImplicitTo<int>>();
    test_is_same<ImplicitTo<float>>();
    test_is_same<ImplicitTo<Class>>();
    test_is_same<DeletedImplicitTo<int>>();
    test_is_same<DeletedImplicitTo<float>>();
    test_is_same<DeletedImplicitTo<Class>>();
    test_is_same<ExplicitTo<int>>();
    test_is_same<ExplicitTo<float>>();
    test_is_same<ExplicitTo<Class>>();
    test_is_same<DeletedExplicitTo<int>>();
    test_is_same<DeletedExplicitTo<float>>();
    test_is_same<DeletedExplicitTo<Class>>();
    test_is_same<Ellipsis>();
    test_is_same<DeletedEllipsis>();
    test_is_same<CopyConsOnlyType>();
    test_is_same<MoveConsOnlyType>();
    test_is_same<OverloadedOperators>();
    test_is_same<PublicIntMember>();
    test_is_same<ProtectedIntMember>();
    test_is_same<PrivateIntMember>();
    test_is_same<PublicStaticIntMember>();
    test_is_same<ProtectedStaticIntMember>();
    test_is_same<PrivateStaticIntMember>();
    test_is_same<PublicTemplateMember<int>>();
    test_is_same<PublicTemplateMember<float>>();
    test_is_same<PublicTemplateMember<Class>>();
    test_is_same<ProtectedTemplateMember<int>>();
    test_is_same<ProtectedTemplateMember<float>>();
    test_is_same<ProtectedTemplateMember<Class>>();
    test_is_same<PrivateTemplateMember<int>>();
    test_is_same<PrivateTemplateMember<float>>();
    test_is_same<PrivateTemplateMember<Class>>();
    test_is_same<PublicStaticTemplateMember<int>>();
    test_is_same<PublicStaticTemplateMember<float>>();
    test_is_same<PublicStaticTemplateMember<Class>>();
    test_is_same<ProtectedStaticTemplateMember<int>>();
    test_is_same<ProtectedStaticTemplateMember<float>>();
    test_is_same<ProtectedStaticTemplateMember<Class>>();
    test_is_same<PrivateStaticTemplateMember<int>>();
    test_is_same<PrivateStaticTemplateMember<float>>();
    test_is_same<PrivateStaticTemplateMember<Class>>();
    test_is_same<CannotInstantiate<int>>();
    test_is_same<CannotInstantiate<float>>();
    test_is_same<CannotInstantiate<Class>>();
    test_is_same<natural_alignment>();
    test_is_same<Enum>();
    test_is_same<EnumSigned>();
    test_is_same<EnumUnsigned>();
    test_is_same<EnumClass>();
    test_is_same<EnumStruct>();
    test_is_same_ref<Function>();
    test_is_same<FunctionPtr>();
    test_is_same<MemberObjectPtr>();
    test_is_same<MemberFunctionPtr>();
    test_is_same<LambdaType>();
    test_is_same<LambdaNoexceptType>();
    test_is_same<LambdaThrowsType>();
    test_is_same<IncompleteType>();
    test_is_same<IncompleteTemplate<void>>();
    test_is_same<IncompleteTemplate<int>>();
    test_is_same<IncompleteTemplate<Class>>();
    test_is_same<IncompleteTemplate<IncompleteType>>();
    test_is_same<IncompleteVariadicTemplate<>>();
    test_is_same<IncompleteVariadicTemplate<void>>();
    test_is_same<IncompleteVariadicTemplate<int>>();
    test_is_same<IncompleteVariadicTemplate<Class>>();
    test_is_same<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_same<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_same<IncompleteUnion>();
    test_is_same<IncompleteEnumSigned>();
    test_is_same<IncompleteEnumUnsigned>();
    test_is_same<IncompleteEnumClass>();
    test_is_same<IncompleteEnumStruct>();
    test_is_same<int Class::*>();
    test_is_same<float Class::*>();
    test_is_same<void * Class::*>();
    test_is_same<int * Class::*>();
    test_is_same<Enum Class::*>();
    test_is_same<NotEmpty Class::*>();
    test_is_same_ref<int Class::*&>();
    test_is_same_ref<float Class::*&>();
    test_is_same_ref<void * Class::*&>();
    test_is_same_ref<int * Class::*&>();
    test_is_same_ref<Enum Class::*&>();
    test_is_same_ref<NotEmpty Class::*&>();
    test_is_same_ref<int Class::*&&>();
    test_is_same_ref<float Class::*&&>();
    test_is_same_ref<void * Class::*&&>();
    test_is_same_ref<int * Class::*&&>();
    test_is_same_ref<Enum Class::*&&>();
    test_is_same_ref<NotEmpty Class::*&&>();
    test_is_same<NonDefaultConstructible>();
    test_is_same<NonCopyConstructible>();
    test_is_same<NonMoveConstructible>();
    test_is_same<NonCopyAssignable>();
    test_is_same<NonMoveAssignable>();
    test_is_same<NonAssignable>();
    test_is_same<NonCopyable>();
    test_is_same<NonMoveable>();
    test_is_same<NonConstructible>();
    test_is_same<NonDestructible>();
    test_is_same<Tracked>();
    test_is_same<TrapConstructible>();
    test_is_same<TrapImplicitConversion>();
    test_is_same<TrapComma>();
    test_is_same<TrapCall>();
    test_is_same<TrapSelfAssign>();
    test_is_same<TrapDeref>();
    test_is_same<TrapArraySubscript>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY()
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_is_same<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_is_same_ref<void()>();
    test_is_same_ref<void()&>();
    test_is_same_ref<void() &&>();
    test_is_same_ref<void() const>();
    test_is_same_ref<void() const&>();
    test_is_same_ref<void() const&&>();
    test_is_same_ref<void() volatile>();
    test_is_same_ref<void() volatile&>();
    test_is_same_ref<void() volatile&&>();
    test_is_same_ref<void() const volatile>();
    test_is_same_ref<void() const volatile&>();
    test_is_same_ref<void() const volatile&&>();
    test_is_same_ref<void() noexcept>();
    test_is_same_ref<void()& noexcept>();
    test_is_same_ref<void()&& noexcept>();
    test_is_same_ref<void() const noexcept>();
    test_is_same_ref<void() const& noexcept>();
    test_is_same_ref<void() const&& noexcept>();
    test_is_same_ref<void() volatile noexcept>();
    test_is_same_ref<void() volatile& noexcept>();
    test_is_same_ref<void() volatile&& noexcept>();
    test_is_same_ref<void() const volatile noexcept>();
    test_is_same_ref<void() const volatile& noexcept>();
    test_is_same_ref<void() const volatile&& noexcept>();

    test_is_same_ref<void(int)>();
    test_is_same_ref<void(int)&>();
    test_is_same_ref<void(int) &&>();
    test_is_same_ref<void(int) const>();
    test_is_same_ref<void(int) const&>();
    test_is_same_ref<void(int) const&&>();
    test_is_same_ref<void(int) volatile>();
    test_is_same_ref<void(int) volatile&>();
    test_is_same_ref<void(int) volatile&&>();
    test_is_same_ref<void(int) const volatile>();
    test_is_same_ref<void(int) const volatile&>();
    test_is_same_ref<void(int) const volatile&&>();
    test_is_same_ref<void(int) noexcept>();
    test_is_same_ref<void(int)& noexcept>();
    test_is_same_ref<void(int)&& noexcept>();
    test_is_same_ref<void(int) const noexcept>();
    test_is_same_ref<void(int) const& noexcept>();
    test_is_same_ref<void(int) const&& noexcept>();
    test_is_same_ref<void(int) volatile noexcept>();
    test_is_same_ref<void(int) volatile& noexcept>();
    test_is_same_ref<void(int) volatile&& noexcept>();
    test_is_same_ref<void(int) const volatile noexcept>();
    test_is_same_ref<void(int) const volatile& noexcept>();
    test_is_same_ref<void(int) const volatile&& noexcept>();

    test_is_same_ref<void(...)>();
    test_is_same_ref<void(...)&>();
    test_is_same_ref<void(...) &&>();
    test_is_same_ref<void(...) const>();
    test_is_same_ref<void(...) const&>();
    test_is_same_ref<void(...) const&&>();
    test_is_same_ref<void(...) volatile>();
    test_is_same_ref<void(...) volatile&>();
    test_is_same_ref<void(...) volatile&&>();
    test_is_same_ref<void(...) const volatile>();
    test_is_same_ref<void(...) const volatile&>();
    test_is_same_ref<void(...) const volatile&&>();
    test_is_same_ref<void(...) noexcept>();
    test_is_same_ref<void(...)& noexcept>();
    test_is_same_ref<void(...)&& noexcept>();
    test_is_same_ref<void(...) const noexcept>();
    test_is_same_ref<void(...) const& noexcept>();
    test_is_same_ref<void(...) const&& noexcept>();
    test_is_same_ref<void(...) volatile noexcept>();
    test_is_same_ref<void(...) volatile& noexcept>();
    test_is_same_ref<void(...) volatile&& noexcept>();
    test_is_same_ref<void(...) const volatile noexcept>();
    test_is_same_ref<void(...) const volatile& noexcept>();
    test_is_same_ref<void(...) const volatile&& noexcept>();

    test_is_same_ref<void(int, ...)>();
    test_is_same_ref<void(int, ...)&>();
    test_is_same_ref<void(int, ...) &&>();
    test_is_same_ref<void(int, ...) const>();
    test_is_same_ref<void(int, ...) const&>();
    test_is_same_ref<void(int, ...) const&&>();
    test_is_same_ref<void(int, ...) volatile>();
    test_is_same_ref<void(int, ...) volatile&>();
    test_is_same_ref<void(int, ...) volatile&&>();
    test_is_same_ref<void(int, ...) const volatile>();
    test_is_same_ref<void(int, ...) const volatile&>();
    test_is_same_ref<void(int, ...) const volatile&&>();
    test_is_same_ref<void(int, ...) noexcept>();
    test_is_same_ref<void(int, ...)& noexcept>();
    test_is_same_ref<void(int, ...)&& noexcept>();
    test_is_same_ref<void(int, ...) const noexcept>();
    test_is_same_ref<void(int, ...) const& noexcept>();
    test_is_same_ref<void(int, ...) const&& noexcept>();
    test_is_same_ref<void(int, ...) volatile noexcept>();
    test_is_same_ref<void(int, ...) volatile& noexcept>();
    test_is_same_ref<void(int, ...) volatile&& noexcept>();
    test_is_same_ref<void(int, ...) const volatile noexcept>();
    test_is_same_ref<void(int, ...) const volatile& noexcept>();
    test_is_same_ref<void(int, ...) const volatile&& noexcept>();

    test_is_same_ref<int()>();
    test_is_same_ref<int()&>();
    test_is_same_ref<int() &&>();
    test_is_same_ref<int() const>();
    test_is_same_ref<int() const&>();
    test_is_same_ref<int() const&&>();
    test_is_same_ref<int() volatile>();
    test_is_same_ref<int() volatile&>();
    test_is_same_ref<int() volatile&&>();
    test_is_same_ref<int() const volatile>();
    test_is_same_ref<int() const volatile&>();
    test_is_same_ref<int() const volatile&&>();
    test_is_same_ref<int() noexcept>();
    test_is_same_ref<int()& noexcept>();
    test_is_same_ref<int()&& noexcept>();
    test_is_same_ref<int() const noexcept>();
    test_is_same_ref<int() const& noexcept>();
    test_is_same_ref<int() const&& noexcept>();
    test_is_same_ref<int() volatile noexcept>();
    test_is_same_ref<int() volatile& noexcept>();
    test_is_same_ref<int() volatile&& noexcept>();
    test_is_same_ref<int() const volatile noexcept>();
    test_is_same_ref<int() const volatile& noexcept>();
    test_is_same_ref<int() const volatile&& noexcept>();

    test_is_same_ref<int(int)>();
    test_is_same_ref<int(int)&>();
    test_is_same_ref<int(int) &&>();
    test_is_same_ref<int(int) const>();
    test_is_same_ref<int(int) const&>();
    test_is_same_ref<int(int) const&&>();
    test_is_same_ref<int(int) volatile>();
    test_is_same_ref<int(int) volatile&>();
    test_is_same_ref<int(int) volatile&&>();
    test_is_same_ref<int(int) const volatile>();
    test_is_same_ref<int(int) const volatile&>();
    test_is_same_ref<int(int) const volatile&&>();
    test_is_same_ref<int(int) noexcept>();
    test_is_same_ref<int(int)& noexcept>();
    test_is_same_ref<int(int)&& noexcept>();
    test_is_same_ref<int(int) const noexcept>();
    test_is_same_ref<int(int) const& noexcept>();
    test_is_same_ref<int(int) const&& noexcept>();
    test_is_same_ref<int(int) volatile noexcept>();
    test_is_same_ref<int(int) volatile& noexcept>();
    test_is_same_ref<int(int) volatile&& noexcept>();
    test_is_same_ref<int(int) const volatile noexcept>();
    test_is_same_ref<int(int) const volatile& noexcept>();
    test_is_same_ref<int(int) const volatile&& noexcept>();

    test_is_same_ref<int(...)>();
    test_is_same_ref<int(...)&>();
    test_is_same_ref<int(...) &&>();
    test_is_same_ref<int(...) const>();
    test_is_same_ref<int(...) const&>();
    test_is_same_ref<int(...) const&&>();
    test_is_same_ref<int(...) volatile>();
    test_is_same_ref<int(...) volatile&>();
    test_is_same_ref<int(...) volatile&&>();
    test_is_same_ref<int(...) const volatile>();
    test_is_same_ref<int(...) const volatile&>();
    test_is_same_ref<int(...) const volatile&&>();
    test_is_same_ref<int(...) noexcept>();
    test_is_same_ref<int(...)& noexcept>();
    test_is_same_ref<int(...)&& noexcept>();
    test_is_same_ref<int(...) const noexcept>();
    test_is_same_ref<int(...) const& noexcept>();
    test_is_same_ref<int(...) const&& noexcept>();
    test_is_same_ref<int(...) volatile noexcept>();
    test_is_same_ref<int(...) volatile& noexcept>();
    test_is_same_ref<int(...) volatile&& noexcept>();
    test_is_same_ref<int(...) const volatile noexcept>();
    test_is_same_ref<int(...) const volatile& noexcept>();
    test_is_same_ref<int(...) const volatile&& noexcept>();

    test_is_same_ref<int(int, ...)>();
    test_is_same_ref<int(int, ...)&>();
    test_is_same_ref<int(int, ...) &&>();
    test_is_same_ref<int(int, ...) const>();
    test_is_same_ref<int(int, ...) const&>();
    test_is_same_ref<int(int, ...) const&&>();
    test_is_same_ref<int(int, ...) volatile>();
    test_is_same_ref<int(int, ...) volatile&>();
    test_is_same_ref<int(int, ...) volatile&&>();
    test_is_same_ref<int(int, ...) const volatile>();
    test_is_same_ref<int(int, ...) const volatile&>();
    test_is_same_ref<int(int, ...) const volatile&&>();
    test_is_same_ref<int(int, ...) noexcept>();
    test_is_same_ref<int(int, ...)& noexcept>();
    test_is_same_ref<int(int, ...)&& noexcept>();
    test_is_same_ref<int(int, ...) const noexcept>();
    test_is_same_ref<int(int, ...) const& noexcept>();
    test_is_same_ref<int(int, ...) const&& noexcept>();
    test_is_same_ref<int(int, ...) volatile noexcept>();
    test_is_same_ref<int(int, ...) volatile& noexcept>();
    test_is_same_ref<int(int, ...) volatile&& noexcept>();
    test_is_same_ref<int(int, ...) const volatile noexcept>();
    test_is_same_ref<int(int, ...) const volatile& noexcept>();
    test_is_same_ref<int(int, ...) const volatile&& noexcept>();

    test_is_same<void (*)()>();
    test_is_same<void (*)() noexcept>();

    test_is_same<void (*)(int)>();
    test_is_same<void (*)(int) noexcept>();

    test_is_same<void (*)(...)>();
    test_is_same<void (*)(...) noexcept>();

    test_is_same<void (*)(int, ...)>();
    test_is_same<void (*)(int, ...) noexcept>();

    test_is_same<int (*)()>();
    test_is_same<int (*)() noexcept>();

    test_is_same<int (*)(int)>();
    test_is_same<int (*)(int) noexcept>();

    test_is_same<int (*)(...)>();
    test_is_same<int (*)(...) noexcept>();

    test_is_same<int (*)(int, ...)>();
    test_is_same<int (*)(int, ...) noexcept>();

    test_is_same_ref<void (&)()>();
    test_is_same_ref<void (&)() noexcept>();

    test_is_same_ref<void (&)(int)>();
    test_is_same_ref<void (&)(int) noexcept>();

    test_is_same_ref<void (&)(...)>();
    test_is_same_ref<void (&)(...) noexcept>();

    test_is_same_ref<void (&)(int, ...)>();
    test_is_same_ref<void (&)(int, ...) noexcept>();

    test_is_same_ref<int (&)()>();
    test_is_same_ref<int (&)() noexcept>();

    test_is_same_ref<int (&)(int)>();
    test_is_same_ref<int (&)(int) noexcept>();

    test_is_same_ref<int (&)(...)>();
    test_is_same_ref<int (&)(...) noexcept>();

    test_is_same_ref<int (&)(int, ...)>();
    test_is_same_ref<int (&)(int, ...) noexcept>();

    test_is_same_ref<void(&&)()>();
    test_is_same_ref<void(&&)() noexcept>();

    test_is_same_ref<void(&&)(int)>();
    test_is_same_ref<void(&&)(int) noexcept>();

    test_is_same_ref<void(&&)(...)>();
    test_is_same_ref<void(&&)(...) noexcept>();

    test_is_same_ref<void(&&)(int, ...)>();
    test_is_same_ref<void(&&)(int, ...) noexcept>();

    test_is_same_ref<int(&&)()>();
    test_is_same_ref<int(&&)() noexcept>();

    test_is_same_ref<int(&&)(int)>();
    test_is_same_ref<int(&&)(int) noexcept>();

    test_is_same_ref<int(&&)(...)>();
    test_is_same_ref<int(&&)(...) noexcept>();

    test_is_same_ref<int(&&)(int, ...)>();
    test_is_same_ref<int(&&)(int, ...) noexcept>();

    test_is_same<void (Class::*)()>();
    test_is_same<void (Class::*)()&>();
    test_is_same<void (Class::*)() &&>();
    test_is_same<void (Class::*)() const>();
    test_is_same<void (Class::*)() const&>();
    test_is_same<void (Class::*)() const&&>();
    test_is_same<void (Class::*)() noexcept>();
    test_is_same<void (Class::*)()& noexcept>();
    test_is_same<void (Class::*)()&& noexcept>();
    test_is_same<void (Class::*)() const noexcept>();
    test_is_same<void (Class::*)() const& noexcept>();
    test_is_same<void (Class::*)() const&& noexcept>();

    test_is_same<void (Class::*)(int)>();
    test_is_same<void (Class::*)(int)&>();
    test_is_same<void (Class::*)(int) &&>();
    test_is_same<void (Class::*)(int) const>();
    test_is_same<void (Class::*)(int) const&>();
    test_is_same<void (Class::*)(int) const&&>();
    test_is_same<void (Class::*)(int) noexcept>();
    test_is_same<void (Class::*)(int)& noexcept>();
    test_is_same<void (Class::*)(int)&& noexcept>();
    test_is_same<void (Class::*)(int) const noexcept>();
    test_is_same<void (Class::*)(int) const& noexcept>();
    test_is_same<void (Class::*)(int) const&& noexcept>();

    test_is_same<void (Class::*)(...)>();
    test_is_same<void (Class::*)(...)&>();
    test_is_same<void (Class::*)(...) &&>();
    test_is_same<void (Class::*)(...) const>();
    test_is_same<void (Class::*)(...) const&>();
    test_is_same<void (Class::*)(...) const&&>();
    test_is_same<void (Class::*)(...) noexcept>();
    test_is_same<void (Class::*)(...)& noexcept>();
    test_is_same<void (Class::*)(...)&& noexcept>();
    test_is_same<void (Class::*)(...) const noexcept>();
    test_is_same<void (Class::*)(...) const& noexcept>();
    test_is_same<void (Class::*)(...) const&& noexcept>();

    test_is_same<void (Class::*)(int, ...)>();
    test_is_same<void (Class::*)(int, ...)&>();
    test_is_same<void (Class::*)(int, ...) &&>();
    test_is_same<void (Class::*)(int, ...) const>();
    test_is_same<void (Class::*)(int, ...) const&>();
    test_is_same<void (Class::*)(int, ...) const&&>();
    test_is_same<void (Class::*)(int, ...) noexcept>();
    test_is_same<void (Class::*)(int, ...)& noexcept>();
    test_is_same<void (Class::*)(int, ...)&& noexcept>();
    test_is_same<void (Class::*)(int, ...) const noexcept>();
    test_is_same<void (Class::*)(int, ...) const& noexcept>();
    test_is_same<void (Class::*)(int, ...) const&& noexcept>();

    test_is_same<int (Class::*)()>();
    test_is_same<int (Class::*)()&>();
    test_is_same<int (Class::*)() &&>();
    test_is_same<int (Class::*)() const>();
    test_is_same<int (Class::*)() const&>();
    test_is_same<int (Class::*)() const&&>();
    test_is_same<int (Class::*)() noexcept>();
    test_is_same<int (Class::*)()& noexcept>();
    test_is_same<int (Class::*)()&& noexcept>();
    test_is_same<int (Class::*)() const noexcept>();
    test_is_same<int (Class::*)() const& noexcept>();
    test_is_same<int (Class::*)() const&& noexcept>();

    test_is_same<int (Class::*)(int)>();
    test_is_same<int (Class::*)(int)&>();
    test_is_same<int (Class::*)(int) &&>();
    test_is_same<int (Class::*)(int) const>();
    test_is_same<int (Class::*)(int) const&>();
    test_is_same<int (Class::*)(int) const&&>();
    test_is_same<int (Class::*)(int) noexcept>();
    test_is_same<int (Class::*)(int)& noexcept>();
    test_is_same<int (Class::*)(int)&& noexcept>();
    test_is_same<int (Class::*)(int) const noexcept>();
    test_is_same<int (Class::*)(int) const& noexcept>();
    test_is_same<int (Class::*)(int) const&& noexcept>();

    test_is_same<int (Class::*)(...)>();
    test_is_same<int (Class::*)(...)&>();
    test_is_same<int (Class::*)(...) &&>();
    test_is_same<int (Class::*)(...) const>();
    test_is_same<int (Class::*)(...) const&>();
    test_is_same<int (Class::*)(...) const&&>();
    test_is_same<int (Class::*)(...) noexcept>();
    test_is_same<int (Class::*)(...)& noexcept>();
    test_is_same<int (Class::*)(...)&& noexcept>();
    test_is_same<int (Class::*)(...) const noexcept>();
    test_is_same<int (Class::*)(...) const& noexcept>();
    test_is_same<int (Class::*)(...) const&& noexcept>();

    test_is_same<int (Class::*)(int, ...)>();
    test_is_same<int (Class::*)(int, ...)&>();
    test_is_same<int (Class::*)(int, ...) &&>();
    test_is_same<int (Class::*)(int, ...) const>();
    test_is_same<int (Class::*)(int, ...) const&>();
    test_is_same<int (Class::*)(int, ...) const&&>();
    test_is_same<int (Class::*)(int, ...) noexcept>();
    test_is_same<int (Class::*)(int, ...)& noexcept>();
    test_is_same<int (Class::*)(int, ...)&& noexcept>();
    test_is_same<int (Class::*)(int, ...) const noexcept>();
    test_is_same<int (Class::*)(int, ...) const& noexcept>();
    test_is_same<int (Class::*)(int, ...) const&& noexcept>();
}
