#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_same_rc.hpp>
#include <vector>

template <typename T, typename U>
void test_is_same_rc_impl()
{
    STATIC_REQUIRE(phi::is_same_rc<T, U>::value);
    STATIC_REQUIRE(phi::is_same_rc<U, T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rc_v<T, U>);
    STATIC_REQUIRE(phi::is_same_rc_v<U, T>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_not_same_rc_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rc<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rc<T, U>);
}

template <typename T, typename U>
void test_is_not_same_rc()
{
    STATIC_REQUIRE_FALSE(phi::is_same_rc<T, U>::value);
    STATIC_REQUIRE_FALSE(phi::is_same_rc<U, T>::value);
    STATIC_REQUIRE(phi::is_not_same_rc<T, U>::value);
    STATIC_REQUIRE(phi::is_not_same_rc<U, T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_same_rc_v<T, U>);
    STATIC_REQUIRE_FALSE(phi::is_same_rc_v<U, T>);
    STATIC_REQUIRE(phi::is_not_same_rc_v<T, U>);
    STATIC_REQUIRE(phi::is_not_same_rc_v<U, T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_same_rc<T, U>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_same_rc<T, U>);
}

template <typename T, typename U = T>
void test_is_same_rc()
{
    // is_same_rc
    test_is_same_rc_impl<T, U>();
    test_is_same_rc_impl<T, const U>();
    test_is_not_same_rc<T, volatile U>();
    test_is_not_same_rc<T, const volatile U>();

    test_is_same_rc_impl<const T, U>();
    test_is_same_rc_impl<const T, const U>();
    test_is_not_same_rc<const T, volatile U>();
    test_is_not_same_rc<const T, const volatile U>();

    test_is_not_same_rc<volatile T, U>();
    test_is_not_same_rc<volatile T, const U>();
    test_is_same_rc_impl<volatile T, volatile U>();
    test_is_same_rc_impl<volatile T, const volatile U>();

    test_is_not_same_rc<const volatile T, U>();
    test_is_not_same_rc<const volatile T, const U>();
    test_is_same_rc_impl<const volatile T, volatile U>();
    test_is_same_rc_impl<const volatile T, const volatile U>();
}

template <typename T, typename U = T>
void test_is_same_rc_ref()
{
    test_is_same_rc_impl<T, U>();
    test_is_same_rc_impl<T, const U>();
    test_is_same_rc_impl<T, volatile U>();
    test_is_same_rc_impl<T, const volatile U>();

    test_is_same_rc_impl<const T, U>();
    test_is_same_rc_impl<const T, const U>();
    test_is_same_rc_impl<const T, volatile U>();
    test_is_same_rc_impl<const T, const volatile U>();

    test_is_same_rc_impl<volatile T, U>();
    test_is_same_rc_impl<volatile T, const U>();
    test_is_same_rc_impl<volatile T, volatile U>();
    test_is_same_rc_impl<volatile T, const volatile U>();

    test_is_same_rc_impl<const volatile T, U>();
    test_is_same_rc_impl<const volatile T, const U>();
    test_is_same_rc_impl<const volatile T, volatile U>();
    test_is_same_rc_impl<const volatile T, const volatile U>();
}

template <typename T>
struct OverloadTest
{
    void fn(phi::is_same_rc<T, int>)
    {}

    void fn(phi::false_type)
    {}

    void x()
    {
        fn(phi::false_type());
    }
};

struct A; // incomplete

TEST_CASE("is_same_rc")
{
    test_is_same_rc<A, A>();

    test_is_not_same_rc<int, void>();
    test_is_not_same_rc<void, Class>();
    test_is_not_same_rc<Class, int*>();
    test_is_not_same_rc<int*, int&>();
    test_is_not_same_rc<int&, int>();

    test_is_not_same_rc<int, volatile int>();
    test_is_not_same_rc<int, const volatile int>();
    test_is_not_same_rc<int, int&>();
    test_is_not_same_rc<int, const int&>();
    test_is_not_same_rc<int, volatile int&>();
    test_is_not_same_rc<int, const volatile int&>();
    test_is_not_same_rc<int, int&&>();
    test_is_not_same_rc<int, const int&&>();
    test_is_not_same_rc<int, volatile int&&>();
    test_is_not_same_rc<int, const volatile int&&>();

    OverloadTest<char> t;
    (void)t;

    test_is_same_rc<void>();
    test_is_same_rc<phi::nullptr_t>();
    test_is_same_rc<bool>();
    test_is_same_rc<char>();
    test_is_same_rc<signed char>();
    test_is_same_rc<unsigned char>();
    test_is_same_rc<short>();
    test_is_same_rc<unsigned short>();
    test_is_same_rc<int>();
    test_is_same_rc<unsigned int>();
    test_is_same_rc<long>();
    test_is_same_rc<unsigned long>();
    test_is_same_rc<long long>();
    test_is_same_rc<unsigned long long>();
    test_is_same_rc<float>();
    test_is_same_rc<double>();
    test_is_same_rc<long double>();
    test_is_same_rc<char8_t>();
    test_is_same_rc<char16_t>();
    test_is_same_rc<char32_t>();
    test_is_same_rc<wchar_t>();

    test_is_same_rc<phi::boolean>();
    test_is_same_rc<phi::integer<signed char>>();
    test_is_same_rc<phi::integer<unsigned char>>();
    test_is_same_rc<phi::integer<short>>();
    test_is_same_rc<phi::integer<unsigned short>>();
    test_is_same_rc<phi::integer<int>>();
    test_is_same_rc<phi::integer<unsigned int>>();
    test_is_same_rc<phi::integer<long>>();
    test_is_same_rc<phi::integer<unsigned long>>();
    test_is_same_rc<phi::integer<long long>>();
    test_is_same_rc<phi::integer<unsigned long long>>();
    test_is_same_rc<phi::floating_point<float>>();
    test_is_same_rc<phi::floating_point<double>>();
    test_is_same_rc<phi::floating_point<long double>>();

    test_is_same_rc<std::vector<int>>();
    test_is_same_rc<phi::scope_ptr<int>>();

    test_is_same_rc_ref<int&>();
    test_is_same_rc_ref<const int&>();
    test_is_same_rc_ref<volatile int&>();
    test_is_same_rc_ref<const volatile int&>();
    test_is_same_rc_ref<int&&>();
    test_is_same_rc_ref<const int&&>();
    test_is_same_rc_ref<volatile int&&>();
    test_is_same_rc_ref<const volatile int&&>();
    test_is_same_rc<int*>();
    test_is_same_rc<const int*>();
    test_is_same_rc<volatile int*>();
    test_is_same_rc<const volatile int*>();
    test_is_same_rc<int**>();
    test_is_same_rc<const int**>();
    test_is_same_rc<volatile int**>();
    test_is_same_rc<const volatile int**>();
    test_is_same_rc_ref<int*&>();
    test_is_same_rc_ref<const int*&>();
    test_is_same_rc_ref<volatile int*&>();
    test_is_same_rc_ref<const volatile int*&>();
    test_is_same_rc_ref<int*&&>();
    test_is_same_rc_ref<const int*&&>();
    test_is_same_rc_ref<volatile int*&&>();
    test_is_same_rc_ref<const volatile int*&&>();
    test_is_same_rc<void*>();
    test_is_same_rc<char[3]>();
    test_is_same_rc<char[]>();
    test_is_same_rc<char* [3]>();
    test_is_same_rc<char*[]>();
    test_is_same_rc<int(*)[3]>();
    test_is_same_rc<int(*)[]>();
    test_is_same_rc_ref<int(&)[3]>();
    test_is_same_rc_ref<int(&)[]>();
    test_is_same_rc_ref<int(&&)[3]>();
    test_is_same_rc_ref<int(&&)[]>();
    test_is_same_rc<char[3][2]>();
    test_is_same_rc<char[][2]>();
    test_is_same_rc<char* [3][2]>();
    test_is_same_rc<char*[][2]>();
    test_is_same_rc<int(*)[3][2]>();
    test_is_same_rc<int(*)[][2]>();
    test_is_same_rc_ref<int(&)[3][2]>();
    test_is_same_rc_ref<int(&)[][2]>();
    test_is_same_rc_ref<int(&&)[3][2]>();
    test_is_same_rc_ref<int(&&)[][2]>();
    test_is_same_rc<Class>();
    test_is_same_rc<Class[]>();
    test_is_same_rc<Class[2]>();
    test_is_same_rc<Template<void>>();
    test_is_same_rc<Template<int>>();
    test_is_same_rc<Template<Class>>();
    test_is_same_rc<Template<IncompleteType>>();
    test_is_same_rc<VariadicTemplate<>>();
    test_is_same_rc<VariadicTemplate<void>>();
    test_is_same_rc<VariadicTemplate<int>>();
    test_is_same_rc<VariadicTemplate<Class>>();
    test_is_same_rc<VariadicTemplate<IncompleteType>>();
    test_is_same_rc<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_same_rc<PublicDerivedFromTemplate<Base>>();
    test_is_same_rc<PublicDerivedFromTemplate<Derived>>();
    test_is_same_rc<PublicDerivedFromTemplate<Class>>();
    test_is_same_rc<PrivateDerivedFromTemplate<Base>>();
    test_is_same_rc<PrivateDerivedFromTemplate<Derived>>();
    test_is_same_rc<PrivateDerivedFromTemplate<Class>>();
    test_is_same_rc<ProtectedDerivedFromTemplate<Base>>();
    test_is_same_rc<ProtectedDerivedFromTemplate<Derived>>();
    test_is_same_rc<ProtectedDerivedFromTemplate<Class>>();
    test_is_same_rc<VirtualDerivedFromTemplate<Base>>();
    test_is_same_rc<VirtualDerivedFromTemplate<Derived>>();
    test_is_same_rc<VirtualDerivedFromTemplate<Class>>();
    test_is_same_rc<Union>();
    test_is_same_rc<NonEmptyUnion>();
    test_is_same_rc<NonTrivialUnion>();
    test_is_same_rc<Empty>();
    test_is_same_rc<NotEmpty>();
    test_is_same_rc<NonTrivial>();
    test_is_same_rc<BitZero>();
    test_is_same_rc<BitOne>();
    test_is_same_rc<Base>();
    test_is_same_rc<Derived>();
    test_is_same_rc<NotEmptyBase>();
    test_is_same_rc<EmptyBase>();
    test_is_same_rc<VirtualBase>();
    test_is_same_rc<Polymorphic>();
    test_is_same_rc<DerivedPolymorphic>();
    test_is_same_rc<Abstract>();
    test_is_same_rc<PublicAbstract>();
    test_is_same_rc<PrivateAbstract>();
    test_is_same_rc<ProtectedAbstract>();
    test_is_same_rc<AbstractTemplate<int>>();
    test_is_same_rc<AbstractTemplate<double>>();
    test_is_same_rc<AbstractTemplate<Class>>();
    test_is_same_rc<AbstractTemplate<IncompleteType>>();
    test_is_same_rc<PublicAbstractDeletedDestructor>();
    test_is_same_rc<ProtectedAbstractDeletedDestructor>();
    test_is_same_rc<PrivateAbstractDeletedDestructor>();
    test_is_same_rc<Final>();
    test_is_same_rc<FinalDerived>();
    test_is_same_rc<PublicDestructor>();
    test_is_same_rc<ProtectedDestructor>();
    test_is_same_rc<PrivateDestructor>();
    test_is_same_rc<VirtualPublicDestructor>();
    test_is_same_rc<VirtualProtectedDestructor>();
    test_is_same_rc<VirtualPrivateDestructor>();
    test_is_same_rc<PurePublicDestructor>();
    test_is_same_rc<PureProtectedDestructor>();
    test_is_same_rc<PurePrivateDestructor>();
    test_is_same_rc<DeletedPublicDestructor>();
    test_is_same_rc<DeletedProtectedDestructor>();
    test_is_same_rc<DeletedPrivateDestructor>();
    test_is_same_rc<DeletedVirtualPublicDestructor>();
    test_is_same_rc<DeletedVirtualProtectedDestructor>();
    test_is_same_rc<DeletedVirtualPrivateDestructor>();
    test_is_same_rc<ExplicitClass>();
    test_is_same_rc<NothrowExplicitClass>();
    test_is_same_rc<ThrowExplicitClass>();
    test_is_same_rc<ThrowDefaultClass>();
    test_is_same_rc<ThrowCopyConsClass>();
    test_is_same_rc<ThrowMoveConsClass>();
    test_is_same_rc<ThrowDestructor>();
    test_is_same_rc<NoexceptExplicitClass>();
    test_is_same_rc<ExceptExplicitClass>();
    test_is_same_rc<NoexceptDefaultClass>();
    test_is_same_rc<ExceptDefaultClass>();
    test_is_same_rc<NoexceptCopyConsClass>();
    test_is_same_rc<ExceptCopyConsClass>();
    test_is_same_rc<NoexceptMoveConsClass>();
    test_is_same_rc<ExceptMoveConsClass>();
    test_is_same_rc<NoexceptCopyAssignClass>();
    test_is_same_rc<ExceptCopyAssignClass>();
    test_is_same_rc<NoexceptMoveAssignClass>();
    test_is_same_rc<ExceptMoveAssignClass>();
    test_is_same_rc<DeletedCopyAssignClass>();
    test_is_same_rc<DeletedMoveAssignClass>();
    test_is_same_rc<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_same_rc<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_same_rc<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_same_rc<ExceptMoveConsExceptMoveAssignClass>();
    test_is_same_rc<ImplicitTo<int>>();
    test_is_same_rc<ImplicitTo<float>>();
    test_is_same_rc<ImplicitTo<Class>>();
    test_is_same_rc<DeletedImplicitTo<int>>();
    test_is_same_rc<DeletedImplicitTo<float>>();
    test_is_same_rc<DeletedImplicitTo<Class>>();
    test_is_same_rc<ExplicitTo<int>>();
    test_is_same_rc<ExplicitTo<float>>();
    test_is_same_rc<ExplicitTo<Class>>();
    test_is_same_rc<DeletedExplicitTo<int>>();
    test_is_same_rc<DeletedExplicitTo<float>>();
    test_is_same_rc<DeletedExplicitTo<Class>>();
    test_is_same_rc<Ellipsis>();
    test_is_same_rc<DeletedEllipsis>();
    test_is_same_rc<CopyConsOnlyType>();
    test_is_same_rc<MoveConsOnlyType>();
    test_is_same_rc<OverloadedOperators>();
    test_is_same_rc<PublicIntMember>();
    test_is_same_rc<ProtectedIntMember>();
    test_is_same_rc<PrivateIntMember>();
    test_is_same_rc<PublicStaticIntMember>();
    test_is_same_rc<ProtectedStaticIntMember>();
    test_is_same_rc<PrivateStaticIntMember>();
    test_is_same_rc<PublicTemplateMember<int>>();
    test_is_same_rc<PublicTemplateMember<float>>();
    test_is_same_rc<PublicTemplateMember<Class>>();
    test_is_same_rc<ProtectedTemplateMember<int>>();
    test_is_same_rc<ProtectedTemplateMember<float>>();
    test_is_same_rc<ProtectedTemplateMember<Class>>();
    test_is_same_rc<PrivateTemplateMember<int>>();
    test_is_same_rc<PrivateTemplateMember<float>>();
    test_is_same_rc<PrivateTemplateMember<Class>>();
    test_is_same_rc<PublicStaticTemplateMember<int>>();
    test_is_same_rc<PublicStaticTemplateMember<float>>();
    test_is_same_rc<PublicStaticTemplateMember<Class>>();
    test_is_same_rc<ProtectedStaticTemplateMember<int>>();
    test_is_same_rc<ProtectedStaticTemplateMember<float>>();
    test_is_same_rc<ProtectedStaticTemplateMember<Class>>();
    test_is_same_rc<PrivateStaticTemplateMember<int>>();
    test_is_same_rc<PrivateStaticTemplateMember<float>>();
    test_is_same_rc<PrivateStaticTemplateMember<Class>>();
    test_is_same_rc<CannotInstantiate<int>>();
    test_is_same_rc<CannotInstantiate<float>>();
    test_is_same_rc<CannotInstantiate<Class>>();
    test_is_same_rc<natural_alignment>();
    test_is_same_rc<Enum>();
    test_is_same_rc<EnumSigned>();
    test_is_same_rc<EnumUnsigned>();
    test_is_same_rc<EnumClass>();
    test_is_same_rc<EnumStruct>();
    test_is_same_rc_ref<Function>();
    test_is_same_rc<FunctionPtr>();
    test_is_same_rc<MemberObjectPtr>();
    test_is_same_rc<MemberFunctionPtr>();
    test_is_same_rc<LambdaType>();
    test_is_same_rc<LambdaNoexceptType>();
    test_is_same_rc<LambdaThrowsType>();
    test_is_same_rc<IncompleteType>();
    test_is_same_rc<IncompleteTemplate<void>>();
    test_is_same_rc<IncompleteTemplate<int>>();
    test_is_same_rc<IncompleteTemplate<Class>>();
    test_is_same_rc<IncompleteTemplate<IncompleteType>>();
    test_is_same_rc<IncompleteVariadicTemplate<>>();
    test_is_same_rc<IncompleteVariadicTemplate<void>>();
    test_is_same_rc<IncompleteVariadicTemplate<int>>();
    test_is_same_rc<IncompleteVariadicTemplate<Class>>();
    test_is_same_rc<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_same_rc<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_same_rc<IncompleteUnion>();
    test_is_same_rc<IncompleteEnumSigned>();
    test_is_same_rc<IncompleteEnumUnsigned>();
    test_is_same_rc<IncompleteEnumClass>();
    test_is_same_rc<IncompleteEnumStruct>();
    test_is_same_rc<int Class::*>();
    test_is_same_rc<float Class::*>();
    test_is_same_rc<void * Class::*>();
    test_is_same_rc<int * Class::*>();
    test_is_same_rc<Enum Class::*>();
    test_is_same_rc<NotEmpty Class::*>();
    test_is_same_rc_ref<int Class::*&>();
    test_is_same_rc_ref<float Class::*&>();
    test_is_same_rc_ref<void * Class::*&>();
    test_is_same_rc_ref<int * Class::*&>();
    test_is_same_rc_ref<Enum Class::*&>();
    test_is_same_rc_ref<NotEmpty Class::*&>();
    test_is_same_rc_ref<int Class::*&&>();
    test_is_same_rc_ref<float Class::*&&>();
    test_is_same_rc_ref<void * Class::*&&>();
    test_is_same_rc_ref<int * Class::*&&>();
    test_is_same_rc_ref<Enum Class::*&&>();
    test_is_same_rc_ref<NotEmpty Class::*&&>();
    test_is_same_rc<NonDefaultConstructible>();
    test_is_same_rc<NonCopyConstructible>();
    test_is_same_rc<NonMoveConstructible>();
    test_is_same_rc<NonCopyAssignable>();
    test_is_same_rc<NonMoveAssignable>();
    test_is_same_rc<NonAssignable>();
    test_is_same_rc<NonCopyable>();
    test_is_same_rc<NonMoveable>();
    test_is_same_rc<NonConstructible>();
    test_is_same_rc<NonDestructible>();
    test_is_same_rc<Tracked>();
    test_is_same_rc<TrapConstructible>();
    test_is_same_rc<TrapImplicitConversion>();
    test_is_same_rc<TrapComma>();
    test_is_same_rc<TrapCall>();
    test_is_same_rc<TrapSelfAssign>();
    test_is_same_rc<TrapDeref>();
    test_is_same_rc<TrapArraySubscript>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY()
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_is_same_rc<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_is_same_rc_ref<void()>();
    test_is_same_rc_ref<void()&>();
    test_is_same_rc_ref<void() &&>();
    test_is_same_rc_ref<void() const>();
    test_is_same_rc_ref<void() const&>();
    test_is_same_rc_ref<void() const&&>();
    test_is_same_rc_ref<void() volatile>();
    test_is_same_rc_ref<void() volatile&>();
    test_is_same_rc_ref<void() volatile&&>();
    test_is_same_rc_ref<void() const volatile>();
    test_is_same_rc_ref<void() const volatile&>();
    test_is_same_rc_ref<void() const volatile&&>();
    test_is_same_rc_ref<void() noexcept>();
    test_is_same_rc_ref<void()& noexcept>();
    test_is_same_rc_ref<void()&& noexcept>();
    test_is_same_rc_ref<void() const noexcept>();
    test_is_same_rc_ref<void() const& noexcept>();
    test_is_same_rc_ref<void() const&& noexcept>();
    test_is_same_rc_ref<void() volatile noexcept>();
    test_is_same_rc_ref<void() volatile& noexcept>();
    test_is_same_rc_ref<void() volatile&& noexcept>();
    test_is_same_rc_ref<void() const volatile noexcept>();
    test_is_same_rc_ref<void() const volatile& noexcept>();
    test_is_same_rc_ref<void() const volatile&& noexcept>();

    test_is_same_rc_ref<void(int)>();
    test_is_same_rc_ref<void(int)&>();
    test_is_same_rc_ref<void(int) &&>();
    test_is_same_rc_ref<void(int) const>();
    test_is_same_rc_ref<void(int) const&>();
    test_is_same_rc_ref<void(int) const&&>();
    test_is_same_rc_ref<void(int) volatile>();
    test_is_same_rc_ref<void(int) volatile&>();
    test_is_same_rc_ref<void(int) volatile&&>();
    test_is_same_rc_ref<void(int) const volatile>();
    test_is_same_rc_ref<void(int) const volatile&>();
    test_is_same_rc_ref<void(int) const volatile&&>();
    test_is_same_rc_ref<void(int) noexcept>();
    test_is_same_rc_ref<void(int)& noexcept>();
    test_is_same_rc_ref<void(int)&& noexcept>();
    test_is_same_rc_ref<void(int) const noexcept>();
    test_is_same_rc_ref<void(int) const& noexcept>();
    test_is_same_rc_ref<void(int) const&& noexcept>();
    test_is_same_rc_ref<void(int) volatile noexcept>();
    test_is_same_rc_ref<void(int) volatile& noexcept>();
    test_is_same_rc_ref<void(int) volatile&& noexcept>();
    test_is_same_rc_ref<void(int) const volatile noexcept>();
    test_is_same_rc_ref<void(int) const volatile& noexcept>();
    test_is_same_rc_ref<void(int) const volatile&& noexcept>();

    test_is_same_rc_ref<void(...)>();
    test_is_same_rc_ref<void(...)&>();
    test_is_same_rc_ref<void(...) &&>();
    test_is_same_rc_ref<void(...) const>();
    test_is_same_rc_ref<void(...) const&>();
    test_is_same_rc_ref<void(...) const&&>();
    test_is_same_rc_ref<void(...) volatile>();
    test_is_same_rc_ref<void(...) volatile&>();
    test_is_same_rc_ref<void(...) volatile&&>();
    test_is_same_rc_ref<void(...) const volatile>();
    test_is_same_rc_ref<void(...) const volatile&>();
    test_is_same_rc_ref<void(...) const volatile&&>();
    test_is_same_rc_ref<void(...) noexcept>();
    test_is_same_rc_ref<void(...)& noexcept>();
    test_is_same_rc_ref<void(...)&& noexcept>();
    test_is_same_rc_ref<void(...) const noexcept>();
    test_is_same_rc_ref<void(...) const& noexcept>();
    test_is_same_rc_ref<void(...) const&& noexcept>();
    test_is_same_rc_ref<void(...) volatile noexcept>();
    test_is_same_rc_ref<void(...) volatile& noexcept>();
    test_is_same_rc_ref<void(...) volatile&& noexcept>();
    test_is_same_rc_ref<void(...) const volatile noexcept>();
    test_is_same_rc_ref<void(...) const volatile& noexcept>();
    test_is_same_rc_ref<void(...) const volatile&& noexcept>();

    test_is_same_rc_ref<void(int, ...)>();
    test_is_same_rc_ref<void(int, ...)&>();
    test_is_same_rc_ref<void(int, ...) &&>();
    test_is_same_rc_ref<void(int, ...) const>();
    test_is_same_rc_ref<void(int, ...) const&>();
    test_is_same_rc_ref<void(int, ...) const&&>();
    test_is_same_rc_ref<void(int, ...) volatile>();
    test_is_same_rc_ref<void(int, ...) volatile&>();
    test_is_same_rc_ref<void(int, ...) volatile&&>();
    test_is_same_rc_ref<void(int, ...) const volatile>();
    test_is_same_rc_ref<void(int, ...) const volatile&>();
    test_is_same_rc_ref<void(int, ...) const volatile&&>();
    test_is_same_rc_ref<void(int, ...) noexcept>();
    test_is_same_rc_ref<void(int, ...)& noexcept>();
    test_is_same_rc_ref<void(int, ...)&& noexcept>();
    test_is_same_rc_ref<void(int, ...) const noexcept>();
    test_is_same_rc_ref<void(int, ...) const& noexcept>();
    test_is_same_rc_ref<void(int, ...) const&& noexcept>();
    test_is_same_rc_ref<void(int, ...) volatile noexcept>();
    test_is_same_rc_ref<void(int, ...) volatile& noexcept>();
    test_is_same_rc_ref<void(int, ...) volatile&& noexcept>();
    test_is_same_rc_ref<void(int, ...) const volatile noexcept>();
    test_is_same_rc_ref<void(int, ...) const volatile& noexcept>();
    test_is_same_rc_ref<void(int, ...) const volatile&& noexcept>();

    test_is_same_rc_ref<int()>();
    test_is_same_rc_ref<int()&>();
    test_is_same_rc_ref<int() &&>();
    test_is_same_rc_ref<int() const>();
    test_is_same_rc_ref<int() const&>();
    test_is_same_rc_ref<int() const&&>();
    test_is_same_rc_ref<int() volatile>();
    test_is_same_rc_ref<int() volatile&>();
    test_is_same_rc_ref<int() volatile&&>();
    test_is_same_rc_ref<int() const volatile>();
    test_is_same_rc_ref<int() const volatile&>();
    test_is_same_rc_ref<int() const volatile&&>();
    test_is_same_rc_ref<int() noexcept>();
    test_is_same_rc_ref<int()& noexcept>();
    test_is_same_rc_ref<int()&& noexcept>();
    test_is_same_rc_ref<int() const noexcept>();
    test_is_same_rc_ref<int() const& noexcept>();
    test_is_same_rc_ref<int() const&& noexcept>();
    test_is_same_rc_ref<int() volatile noexcept>();
    test_is_same_rc_ref<int() volatile& noexcept>();
    test_is_same_rc_ref<int() volatile&& noexcept>();
    test_is_same_rc_ref<int() const volatile noexcept>();
    test_is_same_rc_ref<int() const volatile& noexcept>();
    test_is_same_rc_ref<int() const volatile&& noexcept>();

    test_is_same_rc_ref<int(int)>();
    test_is_same_rc_ref<int(int)&>();
    test_is_same_rc_ref<int(int) &&>();
    test_is_same_rc_ref<int(int) const>();
    test_is_same_rc_ref<int(int) const&>();
    test_is_same_rc_ref<int(int) const&&>();
    test_is_same_rc_ref<int(int) volatile>();
    test_is_same_rc_ref<int(int) volatile&>();
    test_is_same_rc_ref<int(int) volatile&&>();
    test_is_same_rc_ref<int(int) const volatile>();
    test_is_same_rc_ref<int(int) const volatile&>();
    test_is_same_rc_ref<int(int) const volatile&&>();
    test_is_same_rc_ref<int(int) noexcept>();
    test_is_same_rc_ref<int(int)& noexcept>();
    test_is_same_rc_ref<int(int)&& noexcept>();
    test_is_same_rc_ref<int(int) const noexcept>();
    test_is_same_rc_ref<int(int) const& noexcept>();
    test_is_same_rc_ref<int(int) const&& noexcept>();
    test_is_same_rc_ref<int(int) volatile noexcept>();
    test_is_same_rc_ref<int(int) volatile& noexcept>();
    test_is_same_rc_ref<int(int) volatile&& noexcept>();
    test_is_same_rc_ref<int(int) const volatile noexcept>();
    test_is_same_rc_ref<int(int) const volatile& noexcept>();
    test_is_same_rc_ref<int(int) const volatile&& noexcept>();

    test_is_same_rc_ref<int(...)>();
    test_is_same_rc_ref<int(...)&>();
    test_is_same_rc_ref<int(...) &&>();
    test_is_same_rc_ref<int(...) const>();
    test_is_same_rc_ref<int(...) const&>();
    test_is_same_rc_ref<int(...) const&&>();
    test_is_same_rc_ref<int(...) volatile>();
    test_is_same_rc_ref<int(...) volatile&>();
    test_is_same_rc_ref<int(...) volatile&&>();
    test_is_same_rc_ref<int(...) const volatile>();
    test_is_same_rc_ref<int(...) const volatile&>();
    test_is_same_rc_ref<int(...) const volatile&&>();
    test_is_same_rc_ref<int(...) noexcept>();
    test_is_same_rc_ref<int(...)& noexcept>();
    test_is_same_rc_ref<int(...)&& noexcept>();
    test_is_same_rc_ref<int(...) const noexcept>();
    test_is_same_rc_ref<int(...) const& noexcept>();
    test_is_same_rc_ref<int(...) const&& noexcept>();
    test_is_same_rc_ref<int(...) volatile noexcept>();
    test_is_same_rc_ref<int(...) volatile& noexcept>();
    test_is_same_rc_ref<int(...) volatile&& noexcept>();
    test_is_same_rc_ref<int(...) const volatile noexcept>();
    test_is_same_rc_ref<int(...) const volatile& noexcept>();
    test_is_same_rc_ref<int(...) const volatile&& noexcept>();

    test_is_same_rc_ref<int(int, ...)>();
    test_is_same_rc_ref<int(int, ...)&>();
    test_is_same_rc_ref<int(int, ...) &&>();
    test_is_same_rc_ref<int(int, ...) const>();
    test_is_same_rc_ref<int(int, ...) const&>();
    test_is_same_rc_ref<int(int, ...) const&&>();
    test_is_same_rc_ref<int(int, ...) volatile>();
    test_is_same_rc_ref<int(int, ...) volatile&>();
    test_is_same_rc_ref<int(int, ...) volatile&&>();
    test_is_same_rc_ref<int(int, ...) const volatile>();
    test_is_same_rc_ref<int(int, ...) const volatile&>();
    test_is_same_rc_ref<int(int, ...) const volatile&&>();
    test_is_same_rc_ref<int(int, ...) noexcept>();
    test_is_same_rc_ref<int(int, ...)& noexcept>();
    test_is_same_rc_ref<int(int, ...)&& noexcept>();
    test_is_same_rc_ref<int(int, ...) const noexcept>();
    test_is_same_rc_ref<int(int, ...) const& noexcept>();
    test_is_same_rc_ref<int(int, ...) const&& noexcept>();
    test_is_same_rc_ref<int(int, ...) volatile noexcept>();
    test_is_same_rc_ref<int(int, ...) volatile& noexcept>();
    test_is_same_rc_ref<int(int, ...) volatile&& noexcept>();
    test_is_same_rc_ref<int(int, ...) const volatile noexcept>();
    test_is_same_rc_ref<int(int, ...) const volatile& noexcept>();
    test_is_same_rc_ref<int(int, ...) const volatile&& noexcept>();

    test_is_same_rc<void (*)()>();
    test_is_same_rc<void (*)() noexcept>();

    test_is_same_rc<void (*)(int)>();
    test_is_same_rc<void (*)(int) noexcept>();

    test_is_same_rc<void (*)(...)>();
    test_is_same_rc<void (*)(...) noexcept>();

    test_is_same_rc<void (*)(int, ...)>();
    test_is_same_rc<void (*)(int, ...) noexcept>();

    test_is_same_rc<int (*)()>();
    test_is_same_rc<int (*)() noexcept>();

    test_is_same_rc<int (*)(int)>();
    test_is_same_rc<int (*)(int) noexcept>();

    test_is_same_rc<int (*)(...)>();
    test_is_same_rc<int (*)(...) noexcept>();

    test_is_same_rc<int (*)(int, ...)>();
    test_is_same_rc<int (*)(int, ...) noexcept>();

    test_is_same_rc_ref<void (&)()>();
    test_is_same_rc_ref<void (&)() noexcept>();

    test_is_same_rc_ref<void (&)(int)>();
    test_is_same_rc_ref<void (&)(int) noexcept>();

    test_is_same_rc_ref<void (&)(...)>();
    test_is_same_rc_ref<void (&)(...) noexcept>();

    test_is_same_rc_ref<void (&)(int, ...)>();
    test_is_same_rc_ref<void (&)(int, ...) noexcept>();

    test_is_same_rc_ref<int (&)()>();
    test_is_same_rc_ref<int (&)() noexcept>();

    test_is_same_rc_ref<int (&)(int)>();
    test_is_same_rc_ref<int (&)(int) noexcept>();

    test_is_same_rc_ref<int (&)(...)>();
    test_is_same_rc_ref<int (&)(...) noexcept>();

    test_is_same_rc_ref<int (&)(int, ...)>();
    test_is_same_rc_ref<int (&)(int, ...) noexcept>();

    test_is_same_rc_ref<void(&&)()>();
    test_is_same_rc_ref<void(&&)() noexcept>();

    test_is_same_rc_ref<void(&&)(int)>();
    test_is_same_rc_ref<void(&&)(int) noexcept>();

    test_is_same_rc_ref<void(&&)(...)>();
    test_is_same_rc_ref<void(&&)(...) noexcept>();

    test_is_same_rc_ref<void(&&)(int, ...)>();
    test_is_same_rc_ref<void(&&)(int, ...) noexcept>();

    test_is_same_rc_ref<int(&&)()>();
    test_is_same_rc_ref<int(&&)() noexcept>();

    test_is_same_rc_ref<int(&&)(int)>();
    test_is_same_rc_ref<int(&&)(int) noexcept>();

    test_is_same_rc_ref<int(&&)(...)>();
    test_is_same_rc_ref<int(&&)(...) noexcept>();

    test_is_same_rc_ref<int(&&)(int, ...)>();
    test_is_same_rc_ref<int(&&)(int, ...) noexcept>();

    test_is_same_rc<void (Class::*)()>();
    test_is_same_rc<void (Class::*)()&>();
    test_is_same_rc<void (Class::*)() &&>();
    test_is_same_rc<void (Class::*)() const>();
    test_is_same_rc<void (Class::*)() const&>();
    test_is_same_rc<void (Class::*)() const&&>();
    test_is_same_rc<void (Class::*)() noexcept>();
    test_is_same_rc<void (Class::*)()& noexcept>();
    test_is_same_rc<void (Class::*)()&& noexcept>();
    test_is_same_rc<void (Class::*)() const noexcept>();
    test_is_same_rc<void (Class::*)() const& noexcept>();
    test_is_same_rc<void (Class::*)() const&& noexcept>();

    test_is_same_rc<void (Class::*)(int)>();
    test_is_same_rc<void (Class::*)(int)&>();
    test_is_same_rc<void (Class::*)(int) &&>();
    test_is_same_rc<void (Class::*)(int) const>();
    test_is_same_rc<void (Class::*)(int) const&>();
    test_is_same_rc<void (Class::*)(int) const&&>();
    test_is_same_rc<void (Class::*)(int) noexcept>();
    test_is_same_rc<void (Class::*)(int)& noexcept>();
    test_is_same_rc<void (Class::*)(int)&& noexcept>();
    test_is_same_rc<void (Class::*)(int) const noexcept>();
    test_is_same_rc<void (Class::*)(int) const& noexcept>();
    test_is_same_rc<void (Class::*)(int) const&& noexcept>();

    test_is_same_rc<void (Class::*)(...)>();
    test_is_same_rc<void (Class::*)(...)&>();
    test_is_same_rc<void (Class::*)(...) &&>();
    test_is_same_rc<void (Class::*)(...) const>();
    test_is_same_rc<void (Class::*)(...) const&>();
    test_is_same_rc<void (Class::*)(...) const&&>();
    test_is_same_rc<void (Class::*)(...) noexcept>();
    test_is_same_rc<void (Class::*)(...)& noexcept>();
    test_is_same_rc<void (Class::*)(...)&& noexcept>();
    test_is_same_rc<void (Class::*)(...) const noexcept>();
    test_is_same_rc<void (Class::*)(...) const& noexcept>();
    test_is_same_rc<void (Class::*)(...) const&& noexcept>();

    test_is_same_rc<void (Class::*)(int, ...)>();
    test_is_same_rc<void (Class::*)(int, ...)&>();
    test_is_same_rc<void (Class::*)(int, ...) &&>();
    test_is_same_rc<void (Class::*)(int, ...) const>();
    test_is_same_rc<void (Class::*)(int, ...) const&>();
    test_is_same_rc<void (Class::*)(int, ...) const&&>();
    test_is_same_rc<void (Class::*)(int, ...) noexcept>();
    test_is_same_rc<void (Class::*)(int, ...)& noexcept>();
    test_is_same_rc<void (Class::*)(int, ...)&& noexcept>();
    test_is_same_rc<void (Class::*)(int, ...) const noexcept>();
    test_is_same_rc<void (Class::*)(int, ...) const& noexcept>();
    test_is_same_rc<void (Class::*)(int, ...) const&& noexcept>();

    test_is_same_rc<int (Class::*)()>();
    test_is_same_rc<int (Class::*)()&>();
    test_is_same_rc<int (Class::*)() &&>();
    test_is_same_rc<int (Class::*)() const>();
    test_is_same_rc<int (Class::*)() const&>();
    test_is_same_rc<int (Class::*)() const&&>();
    test_is_same_rc<int (Class::*)() noexcept>();
    test_is_same_rc<int (Class::*)()& noexcept>();
    test_is_same_rc<int (Class::*)()&& noexcept>();
    test_is_same_rc<int (Class::*)() const noexcept>();
    test_is_same_rc<int (Class::*)() const& noexcept>();
    test_is_same_rc<int (Class::*)() const&& noexcept>();

    test_is_same_rc<int (Class::*)(int)>();
    test_is_same_rc<int (Class::*)(int)&>();
    test_is_same_rc<int (Class::*)(int) &&>();
    test_is_same_rc<int (Class::*)(int) const>();
    test_is_same_rc<int (Class::*)(int) const&>();
    test_is_same_rc<int (Class::*)(int) const&&>();
    test_is_same_rc<int (Class::*)(int) noexcept>();
    test_is_same_rc<int (Class::*)(int)& noexcept>();
    test_is_same_rc<int (Class::*)(int)&& noexcept>();
    test_is_same_rc<int (Class::*)(int) const noexcept>();
    test_is_same_rc<int (Class::*)(int) const& noexcept>();
    test_is_same_rc<int (Class::*)(int) const&& noexcept>();

    test_is_same_rc<int (Class::*)(...)>();
    test_is_same_rc<int (Class::*)(...)&>();
    test_is_same_rc<int (Class::*)(...) &&>();
    test_is_same_rc<int (Class::*)(...) const>();
    test_is_same_rc<int (Class::*)(...) const&>();
    test_is_same_rc<int (Class::*)(...) const&&>();
    test_is_same_rc<int (Class::*)(...) noexcept>();
    test_is_same_rc<int (Class::*)(...)& noexcept>();
    test_is_same_rc<int (Class::*)(...)&& noexcept>();
    test_is_same_rc<int (Class::*)(...) const noexcept>();
    test_is_same_rc<int (Class::*)(...) const& noexcept>();
    test_is_same_rc<int (Class::*)(...) const&& noexcept>();

    test_is_same_rc<int (Class::*)(int, ...)>();
    test_is_same_rc<int (Class::*)(int, ...)&>();
    test_is_same_rc<int (Class::*)(int, ...) &&>();
    test_is_same_rc<int (Class::*)(int, ...) const>();
    test_is_same_rc<int (Class::*)(int, ...) const&>();
    test_is_same_rc<int (Class::*)(int, ...) const&&>();
    test_is_same_rc<int (Class::*)(int, ...) noexcept>();
    test_is_same_rc<int (Class::*)(int, ...)& noexcept>();
    test_is_same_rc<int (Class::*)(int, ...)&& noexcept>();
    test_is_same_rc<int (Class::*)(int, ...) const noexcept>();
    test_is_same_rc<int (Class::*)(int, ...) const& noexcept>();
    test_is_same_rc<int (Class::*)(int, ...) const&& noexcept>();
}
