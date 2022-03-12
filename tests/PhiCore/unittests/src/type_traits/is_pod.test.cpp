#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(
        4647) // behavior change: __is_pod(x) has different value in previous versions
PHI_MSVC_SUPPRESS_WARNING(4996) // 'std::is_pod<T>': warning STL4025: std::is_pod and std::is_pod_v are deprecated in C++20. The std::is_trivially_copyable and/or std::is_standard_layout traits likely suit your use case. You can define _SILENCE_CXX20_IS_POD_DEPRECATION_WARNING or _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS to acknowledge that you have received this warning.

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_pod.hpp>
#include <type_traits>
#include <vector>

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_PUSH()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wdeprecated-declarations") // is_pod was deprecated in C++-20

template <typename T>
void test_is_pod_impl()
{
#if PHI_HAS_WORKING_IS_POD()
    STATIC_REQUIRE(phi::is_pod<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_pod<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_pod_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_pod_v<T>);
#    endif

    // Standard compatibililty
    STATIC_REQUIRE(std::is_pod<T>::value);
#endif
}

template <typename T>
void test_is_not_pod_impl()
{
#if PHI_HAS_WORKING_IS_POD()
    STATIC_REQUIRE_FALSE(phi::is_pod<T>::value);
    STATIC_REQUIRE(phi::is_not_pod<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_pod_v<T>);
    STATIC_REQUIRE(phi::is_not_pod_v<T>);
#    endif

    // Standard compatibililty
    STATIC_REQUIRE_FALSE(std::is_pod<T>::value);
#endif
}

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()

template <typename T>
void test_is_pod()
{
    test_is_pod_impl<T>();
    test_is_pod_impl<const T>();
    test_is_pod_impl<volatile T>();
    test_is_pod_impl<const volatile T>();
}

template <typename T>
void test_is_not_pod()
{
    test_is_not_pod_impl<T>();
    test_is_not_pod_impl<const T>();
    test_is_not_pod_impl<volatile T>();
    test_is_not_pod_impl<const volatile T>();
}

struct A
{
    int m;
};

struct B
{
    int m1;

private:
    int m2;
};

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnon-virtual-dtor")

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(5204) // 'name': class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly

struct C
{
    virtual void foo();
};

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_GCC_SUPPRESS_WARNING_POP()

template <typename T>
struct D
{
    D()
    {}
};

struct E
{
    const char* const foo;
    const char* const bar;
};

TEST_CASE("is_pod")
{
    test_is_pod<A>();
    test_is_not_pod<B>();
    test_is_not_pod<C>();
    test_is_not_pod<D<int>>();
    test_is_not_pod<D<double>>();

#if PHI_HAS_WORKING_IS_POD()
    int t[phi::is_pod<D<int>>::value ? -1 : 1];
    (void)t;
#endif

    #if PHI_COMPILER_IS(MSVC)
    test_is_not_pod<E>();
    #else
    test_is_pod<E>();
    #endif

    test_is_not_pod<void>();
    test_is_pod<phi::nullptr_t>();
    test_is_pod<bool>();
    test_is_pod<char>();
    test_is_pod<signed char>();
    test_is_pod<unsigned char>();
    test_is_pod<short>();
    test_is_pod<unsigned short>();
    test_is_pod<int>();
    test_is_pod<unsigned int>();
    test_is_pod<long>();
    test_is_pod<unsigned long>();
    test_is_pod<long long>();
    test_is_pod<unsigned long long>();
    test_is_pod<float>();
    test_is_pod<double>();
    test_is_pod<long double>();
    test_is_pod<char8_t>();
    test_is_pod<char16_t>();
    test_is_pod<char32_t>();
    test_is_pod<wchar_t>();

    #if PHI_COMPILER_IS(MSVC)
    test_is_not_pod<phi::boolean>();
    test_is_not_pod<phi::integer<signed char>>();
    test_is_not_pod<phi::integer<unsigned char>>();
    test_is_not_pod<phi::integer<short>>();
    test_is_not_pod<phi::integer<unsigned short>>();
    test_is_not_pod<phi::integer<int>>();
    test_is_not_pod<phi::integer<unsigned int>>();
    test_is_not_pod<phi::integer<long>>();
    test_is_not_pod<phi::integer<unsigned long>>();
    test_is_not_pod<phi::integer<long long>>();
    test_is_not_pod<phi::integer<unsigned long long>>();
    test_is_not_pod<phi::floating_point<float>>();
    test_is_not_pod<phi::floating_point<double>>();
    test_is_not_pod<phi::floating_point<long double>>();
    #else
    test_is_pod<phi::boolean>();
    test_is_pod<phi::integer<signed char>>();
    test_is_pod<phi::integer<unsigned char>>();
    test_is_pod<phi::integer<short>>();
    test_is_pod<phi::integer<unsigned short>>();
    test_is_pod<phi::integer<int>>();
    test_is_pod<phi::integer<unsigned int>>();
    test_is_pod<phi::integer<long>>();
    test_is_pod<phi::integer<unsigned long>>();
    test_is_pod<phi::integer<long long>>();
    test_is_pod<phi::integer<unsigned long long>>();
    test_is_pod<phi::floating_point<float>>();
    test_is_pod<phi::floating_point<double>>();
    test_is_pod<phi::floating_point<long double>>();
    #endif

    test_is_not_pod<std::vector<int>>();
    test_is_not_pod<phi::scope_ptr<int>>();

    test_is_not_pod<int&>();
    test_is_not_pod<const int&>();
    test_is_not_pod<volatile int&>();
    test_is_not_pod<const volatile int&>();
    test_is_not_pod<int&&>();
    test_is_not_pod<const int&&>();
    test_is_not_pod<volatile int&&>();
    test_is_not_pod<const volatile int&&>();
    test_is_pod<int*>();
    test_is_pod<const int*>();
    test_is_pod<volatile int*>();
    test_is_pod<const volatile int*>();
    test_is_pod<int**>();
    test_is_pod<const int**>();
    test_is_pod<volatile int**>();
    test_is_pod<const volatile int**>();
    test_is_not_pod<int*&>();
    test_is_not_pod<const int*&>();
    test_is_not_pod<volatile int*&>();
    test_is_not_pod<const volatile int*&>();
    test_is_not_pod<int*&&>();
    test_is_not_pod<const int*&&>();
    test_is_not_pod<volatile int*&&>();
    test_is_not_pod<const volatile int*&&>();
    test_is_pod<void*>();
    test_is_pod<char[3]>();
    test_is_pod<char[]>();
    test_is_pod<char* [3]>();
    test_is_pod<char*[]>();
    test_is_pod<int(*)[3]>();
    test_is_pod<int(*)[]>();
    test_is_not_pod<int(&)[3]>();
    test_is_not_pod<int(&)[]>();
    test_is_not_pod<int(&&)[3]>();
    test_is_not_pod<int(&&)[]>();
    test_is_pod<char[3][2]>();
    test_is_pod<char[][2]>();
    test_is_pod<char* [3][2]>();
    test_is_pod<char*[][2]>();
    test_is_pod<int(*)[3][2]>();
    test_is_pod<int(*)[][2]>();
    test_is_not_pod<int(&)[3][2]>();
    test_is_not_pod<int(&)[][2]>();
    test_is_not_pod<int(&&)[3][2]>();
    test_is_not_pod<int(&&)[][2]>();
    test_is_not_pod<Class>();
    test_is_not_pod<Class[]>();
    test_is_not_pod<Class[2]>();
    test_is_pod<Template<void>>();
    test_is_pod<Template<int>>();
    test_is_pod<Template<Class>>();
    test_is_pod<Template<IncompleteType>>();
    test_is_pod<VariadicTemplate<>>();
    test_is_pod<VariadicTemplate<void>>();
    test_is_pod<VariadicTemplate<int>>();
    test_is_pod<VariadicTemplate<Class>>();
    test_is_pod<VariadicTemplate<IncompleteType>>();
    test_is_pod<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_pod<PublicDerivedFromTemplate<Base>>();
    test_is_pod<PublicDerivedFromTemplate<Derived>>();
    test_is_not_pod<PublicDerivedFromTemplate<Class>>();
    test_is_pod<PrivateDerivedFromTemplate<Base>>();
    test_is_pod<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_pod<PrivateDerivedFromTemplate<Class>>();
    test_is_pod<ProtectedDerivedFromTemplate<Base>>();
    test_is_pod<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_pod<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_pod<VirtualDerivedFromTemplate<Base>>();
    test_is_not_pod<VirtualDerivedFromTemplate<Derived>>();
    test_is_not_pod<VirtualDerivedFromTemplate<Class>>();
    test_is_pod<Union>();
    test_is_pod<NonEmptyUnion>();
    test_is_not_pod<NonTrivialUnion>();
    test_is_pod<Empty>();
    test_is_not_pod<NotEmpty>();
    test_is_not_pod<NonTrivial>();
    test_is_pod<BitZero>();
    test_is_pod<BitOne>();
    test_is_pod<Base>();
    test_is_pod<Derived>();
    test_is_not_pod<NotEmptyBase>();
    test_is_pod<EmptyBase>();
    test_is_not_pod<VirtualBase>();
    test_is_not_pod<Polymorphic>();
    test_is_not_pod<DerivedPolymorphic>();
    test_is_not_pod<Abstract>();
    test_is_not_pod<PublicAbstract>();
    test_is_not_pod<PrivateAbstract>();
    test_is_not_pod<ProtectedAbstract>();
    test_is_not_pod<AbstractTemplate<int>>();
    test_is_pod<AbstractTemplate<double>>();
    test_is_not_pod<AbstractTemplate<Class>>();
    test_is_not_pod<AbstractTemplate<IncompleteType>>();
    test_is_not_pod<PublicAbstractDeletedDestructor>();
    test_is_not_pod<ProtectedAbstractDeletedDestructor>();
    test_is_not_pod<PrivateAbstractDeletedDestructor>();
    test_is_pod<Final>();
    test_is_pod<FinalDerived>();
    test_is_pod<PublicDestructor>();
    test_is_pod<ProtectedDestructor>();
    test_is_pod<PrivateDestructor>();
    test_is_not_pod<VirtualPublicDestructor>();
    test_is_not_pod<VirtualProtectedDestructor>();
    test_is_not_pod<VirtualPrivateDestructor>();
    test_is_not_pod<PurePublicDestructor>();
    test_is_not_pod<PureProtectedDestructor>();
    test_is_not_pod<PurePrivateDestructor>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_pod<DeletedPublicDestructor>();
    test_is_not_pod<DeletedProtectedDestructor>();
    test_is_not_pod<DeletedPrivateDestructor>();
    #else
    test_is_pod<DeletedPublicDestructor>();
    test_is_pod<DeletedProtectedDestructor>();
    test_is_pod<DeletedPrivateDestructor>();
    #endif
    test_is_not_pod<DeletedVirtualPublicDestructor>();
    test_is_not_pod<DeletedVirtualProtectedDestructor>();
    test_is_not_pod<DeletedVirtualPrivateDestructor>();
    test_is_not_pod<ExplicitClass>();
    test_is_not_pod<NothrowExplicitClass>();
    test_is_not_pod<ThrowExplicitClass>();
    test_is_not_pod<ThrowDefaultClass>();
    test_is_not_pod<ThrowCopyConsClass>();
    test_is_not_pod<ThrowMoveConsClass>();
    test_is_not_pod<ThrowDestructor>();
    test_is_not_pod<NoexceptExplicitClass>();
    test_is_not_pod<ExceptExplicitClass>();
    test_is_not_pod<NoexceptDefaultClass>();
    test_is_not_pod<ExceptDefaultClass>();
    test_is_not_pod<NoexceptCopyConsClass>();
    test_is_not_pod<ExceptCopyConsClass>();
    test_is_not_pod<NoexceptMoveConsClass>();
    test_is_not_pod<ExceptMoveConsClass>();
    test_is_not_pod<NoexceptCopyAssignClass>();
    test_is_not_pod<ExceptCopyAssignClass>();
    test_is_not_pod<NoexceptMoveAssignClass>();
    test_is_not_pod<ExceptMoveAssignClass>();
    test_is_pod<DeletedCopyAssignClass>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_pod<DeletedMoveAssignClass>();
    #else
    test_is_pod<DeletedMoveAssignClass>();
    #endif
    test_is_not_pod<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_pod<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_pod<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_not_pod<ExceptMoveConsExceptMoveAssignClass>();
    test_is_pod<ImplicitTo<int>>();
    test_is_pod<ImplicitTo<float>>();
    test_is_pod<ImplicitTo<Class>>();
    test_is_pod<DeletedImplicitTo<int>>();
    test_is_pod<DeletedImplicitTo<float>>();
    test_is_pod<DeletedImplicitTo<Class>>();
    test_is_pod<ExplicitTo<int>>();
    test_is_pod<ExplicitTo<float>>();
    test_is_pod<ExplicitTo<Class>>();
    test_is_pod<DeletedExplicitTo<int>>();
    test_is_pod<DeletedExplicitTo<float>>();
    test_is_pod<DeletedExplicitTo<Class>>();
    test_is_not_pod<Ellipsis>();
#if PHI_COMPILER_IS(CLANG) || PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(EMCC)
    test_is_not_pod<DeletedEllipsis>();
#else
    test_is_pod<DeletedEllipsis>();
#endif
    test_is_not_pod<CopyConsOnlyType>();
    test_is_not_pod<MoveConsOnlyType>();
    test_is_pod<OverloadedOperators>();
    test_is_pod<PublicIntMember>();
    test_is_pod<ProtectedIntMember>();
    test_is_pod<PrivateIntMember>();
    test_is_pod<PublicStaticIntMember>();
    test_is_pod<ProtectedStaticIntMember>();
    test_is_pod<PrivateStaticIntMember>();
    test_is_pod<PublicTemplateMember<int>>();
    test_is_pod<PublicTemplateMember<float>>();
    test_is_not_pod<PublicTemplateMember<Class>>();
    test_is_pod<ProtectedTemplateMember<int>>();
    test_is_pod<ProtectedTemplateMember<float>>();
    test_is_not_pod<ProtectedTemplateMember<Class>>();
    test_is_pod<PrivateTemplateMember<int>>();
    test_is_pod<PrivateTemplateMember<float>>();
    test_is_not_pod<PrivateTemplateMember<Class>>();
    test_is_pod<PublicStaticTemplateMember<int>>();
    test_is_pod<PublicStaticTemplateMember<float>>();
    test_is_pod<PublicStaticTemplateMember<Class>>();
    test_is_pod<ProtectedStaticTemplateMember<int>>();
    test_is_pod<ProtectedStaticTemplateMember<float>>();
    test_is_pod<ProtectedStaticTemplateMember<Class>>();
    test_is_pod<PrivateStaticTemplateMember<int>>();
    test_is_pod<PrivateStaticTemplateMember<float>>();
    test_is_pod<PrivateStaticTemplateMember<Class>>();
    test_is_pod<Enum>();
    test_is_pod<EnumSigned>();
    test_is_pod<EnumUnsigned>();
    test_is_pod<EnumClass>();
    test_is_pod<EnumStruct>();
    test_is_not_pod<Function>();
    test_is_pod<FunctionPtr>();
    test_is_pod<MemberObjectPtr>();
    test_is_pod<MemberFunctionPtr>();
#if (PHI_COMPILER_IS_ATLEAST(GCC, 9, 0, 0) || PHI_COMPILER_IS_NOT(GCC)) &&                         \
        PHI_CPP_STANDARD_IS_ATLEAST(20)
    test_is_pod<LambdaType>();
    test_is_pod<LambdaNoexceptType>();
    test_is_pod<LambdaThrowsType>();
#else
    test_is_not_pod<LambdaType>();
    test_is_not_pod<LambdaNoexceptType>();
    test_is_not_pod<LambdaThrowsType>();
#endif
    test_is_pod<IncompleteEnumSigned>();
    test_is_pod<IncompleteEnumUnsigned>();
    test_is_pod<IncompleteEnumClass>();
    test_is_pod<IncompleteEnumStruct>();
    test_is_pod<int Class::*>();
    test_is_pod<float Class::*>();
    test_is_pod<void * Class::*>();
    test_is_pod<int * Class::*>();
    test_is_not_pod<int Class::*&>();
    test_is_not_pod<float Class::*&>();
    test_is_not_pod<void * Class::*&>();
    test_is_not_pod<int * Class::*&>();
    test_is_not_pod<int Class::*&&>();
    test_is_not_pod<float Class::*&&>();
    test_is_not_pod<void * Class::*&&>();
    test_is_not_pod<int * Class::*&&>();
    test_is_pod<int Class::*const>();
    test_is_pod<float Class::*const>();
    test_is_pod<void * Class::*const>();
    test_is_not_pod<int Class::*const&>();
    test_is_not_pod<float Class::*const&>();
    test_is_not_pod<void * Class::*const&>();
    test_is_not_pod<int Class::*const&&>();
    test_is_not_pod<float Class::*const&&>();
    test_is_not_pod<void * Class::*const&&>();
    test_is_pod<int Class::*volatile>();
    test_is_pod<float Class::*volatile>();
    test_is_pod<void * Class::*volatile>();
    test_is_not_pod<int Class::*volatile&>();
    test_is_not_pod<float Class::*volatile&>();
    test_is_not_pod<void * Class::*volatile&>();
    test_is_not_pod<int Class::*volatile&&>();
    test_is_not_pod<float Class::*volatile&&>();
    test_is_not_pod<void * Class::*volatile&&>();
    test_is_pod<int Class::*const volatile>();
    test_is_pod<float Class::*const volatile>();
    test_is_pod<void * Class::*const volatile>();
    test_is_not_pod<int Class::*const volatile&>();
    test_is_not_pod<float Class::*const volatile&>();
    test_is_not_pod<void * Class::*const volatile&>();
    test_is_not_pod<int Class::*const volatile&&>();
    test_is_not_pod<float Class::*const volatile&&>();
    test_is_not_pod<void * Class::*const volatile&&>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_pod<NonDefaultConstructible>();
    #else
    test_is_pod<NonDefaultConstructible>();
    #endif
    test_is_pod<NonCopyConstructible>();
    test_is_pod<NonMoveConstructible>();
    test_is_pod<NonCopyAssignable>();
    test_is_pod<NonMoveAssignable>();
    test_is_pod<NonAssignable>();
    test_is_pod<NonCopyable>();
    test_is_pod<NonMoveable>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_pod<NonConstructible>();
    test_is_not_pod<NonDestructible>();
    #else
    test_is_pod<NonConstructible>();
    test_is_pod<NonDestructible>();
    #endif
    test_is_not_pod<Tracked>();
    test_is_pod<TrapConstructible>();
    test_is_pod<TrapImplicitConversion>();
    test_is_pod<TrapComma>();
    test_is_pod<TrapCall>();
    test_is_not_pod<TrapSelfAssign>();
    test_is_pod<TrapDeref>();
    test_is_pod<TrapArraySubscript>();

    test_is_not_pod<void()>();
    test_is_not_pod<void()&>();
    test_is_not_pod<void() &&>();
    test_is_not_pod<void() const>();
    test_is_not_pod<void() const&>();
    test_is_not_pod<void() const&&>();
    test_is_not_pod<void() volatile>();
    test_is_not_pod<void() volatile&>();
    test_is_not_pod<void() volatile&&>();
    test_is_not_pod<void() const volatile>();
    test_is_not_pod<void() const volatile&>();
    test_is_not_pod<void() const volatile&&>();
    test_is_not_pod<void() noexcept>();
    test_is_not_pod<void()& noexcept>();
    test_is_not_pod<void()&& noexcept>();
    test_is_not_pod<void() const noexcept>();
    test_is_not_pod<void() const& noexcept>();
    test_is_not_pod<void() const&& noexcept>();
    test_is_not_pod<void() volatile noexcept>();
    test_is_not_pod<void() volatile& noexcept>();
    test_is_not_pod<void() volatile&& noexcept>();
    test_is_not_pod<void() const volatile noexcept>();
    test_is_not_pod<void() const volatile& noexcept>();
    test_is_not_pod<void() const volatile&& noexcept>();

    test_is_not_pod<void(int)>();
    test_is_not_pod<void(int)&>();
    test_is_not_pod<void(int) &&>();
    test_is_not_pod<void(int) const>();
    test_is_not_pod<void(int) const&>();
    test_is_not_pod<void(int) const&&>();
    test_is_not_pod<void(int) volatile>();
    test_is_not_pod<void(int) volatile&>();
    test_is_not_pod<void(int) volatile&&>();
    test_is_not_pod<void(int) const volatile>();
    test_is_not_pod<void(int) const volatile&>();
    test_is_not_pod<void(int) const volatile&&>();
    test_is_not_pod<void(int) noexcept>();
    test_is_not_pod<void(int)& noexcept>();
    test_is_not_pod<void(int)&& noexcept>();
    test_is_not_pod<void(int) const noexcept>();
    test_is_not_pod<void(int) const& noexcept>();
    test_is_not_pod<void(int) const&& noexcept>();
    test_is_not_pod<void(int) volatile noexcept>();
    test_is_not_pod<void(int) volatile& noexcept>();
    test_is_not_pod<void(int) volatile&& noexcept>();
    test_is_not_pod<void(int) const volatile noexcept>();
    test_is_not_pod<void(int) const volatile& noexcept>();
    test_is_not_pod<void(int) const volatile&& noexcept>();

    test_is_not_pod<void(...)>();
    test_is_not_pod<void(...)&>();
    test_is_not_pod<void(...) &&>();
    test_is_not_pod<void(...) const>();
    test_is_not_pod<void(...) const&>();
    test_is_not_pod<void(...) const&&>();
    test_is_not_pod<void(...) volatile>();
    test_is_not_pod<void(...) volatile&>();
    test_is_not_pod<void(...) volatile&&>();
    test_is_not_pod<void(...) const volatile>();
    test_is_not_pod<void(...) const volatile&>();
    test_is_not_pod<void(...) const volatile&&>();
    test_is_not_pod<void(...) noexcept>();
    test_is_not_pod<void(...)& noexcept>();
    test_is_not_pod<void(...)&& noexcept>();
    test_is_not_pod<void(...) const noexcept>();
    test_is_not_pod<void(...) const& noexcept>();
    test_is_not_pod<void(...) const&& noexcept>();
    test_is_not_pod<void(...) volatile noexcept>();
    test_is_not_pod<void(...) volatile& noexcept>();
    test_is_not_pod<void(...) volatile&& noexcept>();
    test_is_not_pod<void(...) const volatile noexcept>();
    test_is_not_pod<void(...) const volatile& noexcept>();
    test_is_not_pod<void(...) const volatile&& noexcept>();

    test_is_not_pod<void(int, ...)>();
    test_is_not_pod<void(int, ...)&>();
    test_is_not_pod<void(int, ...) &&>();
    test_is_not_pod<void(int, ...) const>();
    test_is_not_pod<void(int, ...) const&>();
    test_is_not_pod<void(int, ...) const&&>();
    test_is_not_pod<void(int, ...) volatile>();
    test_is_not_pod<void(int, ...) volatile&>();
    test_is_not_pod<void(int, ...) volatile&&>();
    test_is_not_pod<void(int, ...) const volatile>();
    test_is_not_pod<void(int, ...) const volatile&>();
    test_is_not_pod<void(int, ...) const volatile&&>();
    test_is_not_pod<void(int, ...) noexcept>();
    test_is_not_pod<void(int, ...)& noexcept>();
    test_is_not_pod<void(int, ...)&& noexcept>();
    test_is_not_pod<void(int, ...) const noexcept>();
    test_is_not_pod<void(int, ...) const& noexcept>();
    test_is_not_pod<void(int, ...) const&& noexcept>();
    test_is_not_pod<void(int, ...) volatile noexcept>();
    test_is_not_pod<void(int, ...) volatile& noexcept>();
    test_is_not_pod<void(int, ...) volatile&& noexcept>();
    test_is_not_pod<void(int, ...) const volatile noexcept>();
    test_is_not_pod<void(int, ...) const volatile& noexcept>();
    test_is_not_pod<void(int, ...) const volatile&& noexcept>();

    test_is_not_pod<int()>();
    test_is_not_pod<int()&>();
    test_is_not_pod<int() &&>();
    test_is_not_pod<int() const>();
    test_is_not_pod<int() const&>();
    test_is_not_pod<int() const&&>();
    test_is_not_pod<int() volatile>();
    test_is_not_pod<int() volatile&>();
    test_is_not_pod<int() volatile&&>();
    test_is_not_pod<int() const volatile>();
    test_is_not_pod<int() const volatile&>();
    test_is_not_pod<int() const volatile&&>();
    test_is_not_pod<int() noexcept>();
    test_is_not_pod<int()& noexcept>();
    test_is_not_pod<int()&& noexcept>();
    test_is_not_pod<int() const noexcept>();
    test_is_not_pod<int() const& noexcept>();
    test_is_not_pod<int() const&& noexcept>();
    test_is_not_pod<int() volatile noexcept>();
    test_is_not_pod<int() volatile& noexcept>();
    test_is_not_pod<int() volatile&& noexcept>();
    test_is_not_pod<int() const volatile noexcept>();
    test_is_not_pod<int() const volatile& noexcept>();
    test_is_not_pod<int() const volatile&& noexcept>();

    test_is_not_pod<int(int)>();
    test_is_not_pod<int(int)&>();
    test_is_not_pod<int(int) &&>();
    test_is_not_pod<int(int) const>();
    test_is_not_pod<int(int) const&>();
    test_is_not_pod<int(int) const&&>();
    test_is_not_pod<int(int) volatile>();
    test_is_not_pod<int(int) volatile&>();
    test_is_not_pod<int(int) volatile&&>();
    test_is_not_pod<int(int) const volatile>();
    test_is_not_pod<int(int) const volatile&>();
    test_is_not_pod<int(int) const volatile&&>();
    test_is_not_pod<int(int) noexcept>();
    test_is_not_pod<int(int)& noexcept>();
    test_is_not_pod<int(int)&& noexcept>();
    test_is_not_pod<int(int) const noexcept>();
    test_is_not_pod<int(int) const& noexcept>();
    test_is_not_pod<int(int) const&& noexcept>();
    test_is_not_pod<int(int) volatile noexcept>();
    test_is_not_pod<int(int) volatile& noexcept>();
    test_is_not_pod<int(int) volatile&& noexcept>();
    test_is_not_pod<int(int) const volatile noexcept>();
    test_is_not_pod<int(int) const volatile& noexcept>();
    test_is_not_pod<int(int) const volatile&& noexcept>();

    test_is_not_pod<int(...)>();
    test_is_not_pod<int(...)&>();
    test_is_not_pod<int(...) &&>();
    test_is_not_pod<int(...) const>();
    test_is_not_pod<int(...) const&>();
    test_is_not_pod<int(...) const&&>();
    test_is_not_pod<int(...) volatile>();
    test_is_not_pod<int(...) volatile&>();
    test_is_not_pod<int(...) volatile&&>();
    test_is_not_pod<int(...) const volatile>();
    test_is_not_pod<int(...) const volatile&>();
    test_is_not_pod<int(...) const volatile&&>();
    test_is_not_pod<int(...) noexcept>();
    test_is_not_pod<int(...)& noexcept>();
    test_is_not_pod<int(...)&& noexcept>();
    test_is_not_pod<int(...) const noexcept>();
    test_is_not_pod<int(...) const& noexcept>();
    test_is_not_pod<int(...) const&& noexcept>();
    test_is_not_pod<int(...) volatile noexcept>();
    test_is_not_pod<int(...) volatile& noexcept>();
    test_is_not_pod<int(...) volatile&& noexcept>();
    test_is_not_pod<int(...) const volatile noexcept>();
    test_is_not_pod<int(...) const volatile& noexcept>();
    test_is_not_pod<int(...) const volatile&& noexcept>();

    test_is_not_pod<int(int, ...)>();
    test_is_not_pod<int(int, ...)&>();
    test_is_not_pod<int(int, ...) &&>();
    test_is_not_pod<int(int, ...) const>();
    test_is_not_pod<int(int, ...) const&>();
    test_is_not_pod<int(int, ...) const&&>();
    test_is_not_pod<int(int, ...) volatile>();
    test_is_not_pod<int(int, ...) volatile&>();
    test_is_not_pod<int(int, ...) volatile&&>();
    test_is_not_pod<int(int, ...) const volatile>();
    test_is_not_pod<int(int, ...) const volatile&>();
    test_is_not_pod<int(int, ...) const volatile&&>();
    test_is_not_pod<int(int, ...) noexcept>();
    test_is_not_pod<int(int, ...)& noexcept>();
    test_is_not_pod<int(int, ...)&& noexcept>();
    test_is_not_pod<int(int, ...) const noexcept>();
    test_is_not_pod<int(int, ...) const& noexcept>();
    test_is_not_pod<int(int, ...) const&& noexcept>();
    test_is_not_pod<int(int, ...) volatile noexcept>();
    test_is_not_pod<int(int, ...) volatile& noexcept>();
    test_is_not_pod<int(int, ...) volatile&& noexcept>();
    test_is_not_pod<int(int, ...) const volatile noexcept>();
    test_is_not_pod<int(int, ...) const volatile& noexcept>();
    test_is_not_pod<int(int, ...) const volatile&& noexcept>();

    test_is_pod<void (*)()>();
    test_is_pod<void (*)() noexcept>();

    test_is_pod<void (*)(int)>();
    test_is_pod<void (*)(int) noexcept>();

    test_is_pod<void (*)(...)>();
    test_is_pod<void (*)(...) noexcept>();

    test_is_pod<void (*)(int, ...)>();
    test_is_pod<void (*)(int, ...) noexcept>();

    test_is_pod<int (*)()>();
    test_is_pod<int (*)() noexcept>();

    test_is_pod<int (*)(int)>();
    test_is_pod<int (*)(int) noexcept>();

    test_is_pod<int (*)(...)>();
    test_is_pod<int (*)(...) noexcept>();

    test_is_pod<int (*)(int, ...)>();
    test_is_pod<int (*)(int, ...) noexcept>();

    test_is_not_pod<void (&)()>();
    test_is_not_pod<void (&)() noexcept>();

    test_is_not_pod<void (&)(int)>();
    test_is_not_pod<void (&)(int) noexcept>();

    test_is_not_pod<void (&)(...)>();
    test_is_not_pod<void (&)(...) noexcept>();

    test_is_not_pod<void (&)(int, ...)>();
    test_is_not_pod<void (&)(int, ...) noexcept>();

    test_is_not_pod<int (&)()>();
    test_is_not_pod<int (&)() noexcept>();

    test_is_not_pod<int (&)(int)>();
    test_is_not_pod<int (&)(int) noexcept>();

    test_is_not_pod<int (&)(...)>();
    test_is_not_pod<int (&)(...) noexcept>();

    test_is_not_pod<int (&)(int, ...)>();
    test_is_not_pod<int (&)(int, ...) noexcept>();

    test_is_not_pod<void(&&)()>();
    test_is_not_pod<void(&&)() noexcept>();

    test_is_not_pod<void(&&)(int)>();
    test_is_not_pod<void(&&)(int) noexcept>();

    test_is_not_pod<void(&&)(...)>();
    test_is_not_pod<void(&&)(...) noexcept>();

    test_is_not_pod<void(&&)(int, ...)>();
    test_is_not_pod<void(&&)(int, ...) noexcept>();

    test_is_not_pod<int(&&)()>();
    test_is_not_pod<int(&&)() noexcept>();

    test_is_not_pod<int(&&)(int)>();
    test_is_not_pod<int(&&)(int) noexcept>();

    test_is_not_pod<int(&&)(...)>();
    test_is_not_pod<int(&&)(...) noexcept>();

    test_is_not_pod<int(&&)(int, ...)>();
    test_is_not_pod<int(&&)(int, ...) noexcept>();

    test_is_pod<void (Class::*)()>();
    test_is_pod<void (Class::*)()&>();
    test_is_pod<void (Class::*)() &&>();
    test_is_pod<void (Class::*)() const>();
    test_is_pod<void (Class::*)() const&>();
    test_is_pod<void (Class::*)() const&&>();
    test_is_pod<void (Class::*)() noexcept>();
    test_is_pod<void (Class::*)()& noexcept>();
    test_is_pod<void (Class::*)()&& noexcept>();
    test_is_pod<void (Class::*)() const noexcept>();
    test_is_pod<void (Class::*)() const& noexcept>();
    test_is_pod<void (Class::*)() const&& noexcept>();

    test_is_pod<void (Class::*)(int)>();
    test_is_pod<void (Class::*)(int)&>();
    test_is_pod<void (Class::*)(int) &&>();
    test_is_pod<void (Class::*)(int) const>();
    test_is_pod<void (Class::*)(int) const&>();
    test_is_pod<void (Class::*)(int) const&&>();
    test_is_pod<void (Class::*)(int) noexcept>();
    test_is_pod<void (Class::*)(int)& noexcept>();
    test_is_pod<void (Class::*)(int)&& noexcept>();
    test_is_pod<void (Class::*)(int) const noexcept>();
    test_is_pod<void (Class::*)(int) const& noexcept>();
    test_is_pod<void (Class::*)(int) const&& noexcept>();

    test_is_pod<void (Class::*)(...)>();
    test_is_pod<void (Class::*)(...)&>();
    test_is_pod<void (Class::*)(...) &&>();
    test_is_pod<void (Class::*)(...) const>();
    test_is_pod<void (Class::*)(...) const&>();
    test_is_pod<void (Class::*)(...) const&&>();
    test_is_pod<void (Class::*)(...) noexcept>();
    test_is_pod<void (Class::*)(...)& noexcept>();
    test_is_pod<void (Class::*)(...)&& noexcept>();
    test_is_pod<void (Class::*)(...) const noexcept>();
    test_is_pod<void (Class::*)(...) const& noexcept>();
    test_is_pod<void (Class::*)(...) const&& noexcept>();

    test_is_pod<void (Class::*)(int, ...)>();
    test_is_pod<void (Class::*)(int, ...)&>();
    test_is_pod<void (Class::*)(int, ...) &&>();
    test_is_pod<void (Class::*)(int, ...) const>();
    test_is_pod<void (Class::*)(int, ...) const&>();
    test_is_pod<void (Class::*)(int, ...) const&&>();
    test_is_pod<void (Class::*)(int, ...) noexcept>();
    test_is_pod<void (Class::*)(int, ...)& noexcept>();
    test_is_pod<void (Class::*)(int, ...)&& noexcept>();
    test_is_pod<void (Class::*)(int, ...) const noexcept>();
    test_is_pod<void (Class::*)(int, ...) const& noexcept>();
    test_is_pod<void (Class::*)(int, ...) const&& noexcept>();

    test_is_pod<int (Class::*)()>();
    test_is_pod<int (Class::*)()&>();
    test_is_pod<int (Class::*)() &&>();
    test_is_pod<int (Class::*)() const>();
    test_is_pod<int (Class::*)() const&>();
    test_is_pod<int (Class::*)() const&&>();
    test_is_pod<int (Class::*)() noexcept>();
    test_is_pod<int (Class::*)()& noexcept>();
    test_is_pod<int (Class::*)()&& noexcept>();
    test_is_pod<int (Class::*)() const noexcept>();
    test_is_pod<int (Class::*)() const& noexcept>();
    test_is_pod<int (Class::*)() const&& noexcept>();

    test_is_pod<int (Class::*)(int)>();
    test_is_pod<int (Class::*)(int)&>();
    test_is_pod<int (Class::*)(int) &&>();
    test_is_pod<int (Class::*)(int) const>();
    test_is_pod<int (Class::*)(int) const&>();
    test_is_pod<int (Class::*)(int) const&&>();
    test_is_pod<int (Class::*)(int) noexcept>();
    test_is_pod<int (Class::*)(int)& noexcept>();
    test_is_pod<int (Class::*)(int)&& noexcept>();
    test_is_pod<int (Class::*)(int) const noexcept>();
    test_is_pod<int (Class::*)(int) const& noexcept>();
    test_is_pod<int (Class::*)(int) const&& noexcept>();

    test_is_pod<int (Class::*)(...)>();
    test_is_pod<int (Class::*)(...)&>();
    test_is_pod<int (Class::*)(...) &&>();
    test_is_pod<int (Class::*)(...) const>();
    test_is_pod<int (Class::*)(...) const&>();
    test_is_pod<int (Class::*)(...) const&&>();
    test_is_pod<int (Class::*)(...) noexcept>();
    test_is_pod<int (Class::*)(...)& noexcept>();
    test_is_pod<int (Class::*)(...)&& noexcept>();
    test_is_pod<int (Class::*)(...) const noexcept>();
    test_is_pod<int (Class::*)(...) const& noexcept>();
    test_is_pod<int (Class::*)(...) const&& noexcept>();

    test_is_pod<int (Class::*)(int, ...)>();
    test_is_pod<int (Class::*)(int, ...)&>();
    test_is_pod<int (Class::*)(int, ...) &&>();
    test_is_pod<int (Class::*)(int, ...) const>();
    test_is_pod<int (Class::*)(int, ...) const&>();
    test_is_pod<int (Class::*)(int, ...) const&&>();
    test_is_pod<int (Class::*)(int, ...) noexcept>();
    test_is_pod<int (Class::*)(int, ...)& noexcept>();
    test_is_pod<int (Class::*)(int, ...)&& noexcept>();
    test_is_pod<int (Class::*)(int, ...) const noexcept>();
    test_is_pod<int (Class::*)(int, ...) const& noexcept>();
    test_is_pod<int (Class::*)(int, ...) const&& noexcept>();
}
