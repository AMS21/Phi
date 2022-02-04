#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_literal_type.hpp>
#include <type_traits>
#include <vector>

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_PUSH()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING(
        "-Wdeprecated-declarations") // is_literal_type was deprecated in C++-17 and removed in C++-20

template <typename T>
void test_is_literal_type_impl()
{
#if PHI_HAS_WORKING_IS_LITERAL_TYPE()
    STATIC_REQUIRE(phi::is_literal_type<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_literal_type<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_literal_type_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_literal_type_v<T>);
#    endif

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_BELOW(20)
    STATIC_REQUIRE(std::is_literal_type<T>::value);
#    endif
#endif
}

template <typename T>
void test_is_not_literal_type_impl()
{
#if PHI_HAS_WORKING_IS_LITERAL_TYPE()
    STATIC_REQUIRE_FALSE(phi::is_literal_type<T>::value);
    STATIC_REQUIRE(phi::is_not_literal_type<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_literal_type_v<T>);
    STATIC_REQUIRE(phi::is_not_literal_type_v<T>);
#    endif

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_BELOW(20)
    STATIC_REQUIRE_FALSE(std::is_literal_type<T>::value);
#    endif
#endif
}

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()

template <typename T>
void test_is_literal_type()
{
    test_is_literal_type_impl<T>();
    test_is_literal_type_impl<const T>();
    test_is_literal_type_impl<volatile T>();
    test_is_literal_type_impl<const volatile T>();
}

template <typename T>
void test_is_not_literal_type()
{
    test_is_not_literal_type_impl<T>();
    test_is_not_literal_type_impl<const T>();
    test_is_not_literal_type_impl<volatile T>();
    test_is_not_literal_type_impl<const volatile T>();
}

template <typename T>
void test_is_literal_type_cxx20()
{
#if PHI_CPP_STANDARD_IS_ATLEAST(20)
    test_is_literal_type<T>();
#else
    test_is_not_literal_type<T>();
#endif
}

template <typename T>
void test_is_literal_type_cxx17()
{
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    test_is_literal_type<T>();
#else
    test_is_not_literal_type<T>();
#endif
}

template <typename T>
void test_is_not_literal_type_cxx20()
{
#if PHI_CPP_STANDARD_IS_ATLEAST(20)
    test_is_not_literal_type<T>();
#else
    test_is_literal_type<T>();
#endif
}

struct A
{
    int m;
};

struct B
{
    virtual ~B();
};

TEST_CASE("is_literal_type")
{
    test_is_literal_type<A>();
    test_is_not_literal_type<B>();

#if PHI_CPP_STANDARD_IS_ATLEAST(14)
    // In C++14, cv-void is a literal type
    test_is_literal_type<void>();
#else
    // Before C++-14, void was not a literal type
    test_is_not_literal_type<void>();
#endif
    test_is_literal_type<phi::nullptr_t>();
    test_is_literal_type<bool>();
    test_is_literal_type<char>();
    test_is_literal_type<signed char>();
    test_is_literal_type<unsigned char>();
    test_is_literal_type<short>();
    test_is_literal_type<unsigned short>();
    test_is_literal_type<int>();
    test_is_literal_type<unsigned int>();
    test_is_literal_type<long>();
    test_is_literal_type<unsigned long>();
    test_is_literal_type<long long>();
    test_is_literal_type<unsigned long long>();
    test_is_literal_type<float>();
    test_is_literal_type<double>();
    test_is_literal_type<long double>();
    test_is_literal_type<char8_t>();
    test_is_literal_type<char16_t>();
    test_is_literal_type<char32_t>();
    test_is_literal_type<wchar_t>();

    test_is_literal_type<phi::boolean>();
    test_is_literal_type<phi::integer<signed char>>();
    test_is_literal_type<phi::integer<unsigned char>>();
    test_is_literal_type<phi::integer<short>>();
    test_is_literal_type<phi::integer<unsigned short>>();
    test_is_literal_type<phi::integer<int>>();
    test_is_literal_type<phi::integer<unsigned int>>();
    test_is_literal_type<phi::integer<long>>();
    test_is_literal_type<phi::integer<unsigned long>>();
    test_is_literal_type<phi::integer<long long>>();
    test_is_literal_type<phi::integer<unsigned long long>>();
    test_is_literal_type<phi::floating_point<float>>();
    test_is_literal_type<phi::floating_point<double>>();
    test_is_literal_type<phi::floating_point<long double>>();

    test_is_not_literal_type<std::vector<int>>();
    test_is_literal_type_cxx20<phi::scope_ptr<int>>();

    test_is_literal_type<int&>();
    test_is_literal_type<const int&>();
    test_is_literal_type<volatile int&>();
    test_is_literal_type<const volatile int&>();
    test_is_literal_type<int&&>();
    test_is_literal_type<const int&&>();
    test_is_literal_type<volatile int&&>();
    test_is_literal_type<const volatile int&&>();
    test_is_literal_type<int*>();
    test_is_literal_type<const int*>();
    test_is_literal_type<volatile int*>();
    test_is_literal_type<const volatile int*>();
    test_is_literal_type<int**>();
    test_is_literal_type<const int**>();
    test_is_literal_type<volatile int**>();
    test_is_literal_type<const volatile int**>();
    test_is_literal_type<int*&>();
    test_is_literal_type<const int*&>();
    test_is_literal_type<volatile int*&>();
    test_is_literal_type<const volatile int*&>();
    test_is_literal_type<int*&&>();
    test_is_literal_type<const int*&&>();
    test_is_literal_type<volatile int*&&>();
    test_is_literal_type<const volatile int*&&>();
    test_is_literal_type<void*>();
    test_is_literal_type<char[3]>();
    test_is_literal_type<char[]>();
    test_is_literal_type<char* [3]>();
    test_is_literal_type<char*[]>();
    test_is_literal_type<int(*)[3]>();
    test_is_literal_type<int(*)[]>();
    test_is_literal_type<int(&)[3]>();
    test_is_literal_type<int(&)[]>();
    test_is_literal_type<int(&&)[3]>();
    test_is_literal_type<int(&&)[]>();
    test_is_literal_type<char[3][2]>();
    test_is_literal_type<char[][2]>();
    test_is_literal_type<char* [3][2]>();
    test_is_literal_type<char*[][2]>();
    test_is_literal_type<int(*)[3][2]>();
    test_is_literal_type<int(*)[][2]>();
    test_is_literal_type<int(&)[3][2]>();
    test_is_literal_type<int(&)[][2]>();
    test_is_literal_type<int(&&)[3][2]>();
    test_is_literal_type<int(&&)[][2]>();
    test_is_not_literal_type<Class>();
    test_is_not_literal_type<Class[]>();
    test_is_not_literal_type<Class[2]>();
    test_is_literal_type<Template<void>>();
    test_is_literal_type<Template<int>>();
    test_is_literal_type<Template<Class>>();
    test_is_literal_type<Template<IncompleteType>>();
    test_is_literal_type<VariadicTemplate<>>();
    test_is_literal_type<VariadicTemplate<void>>();
    test_is_literal_type<VariadicTemplate<int>>();
    test_is_literal_type<VariadicTemplate<Class>>();
    test_is_literal_type<VariadicTemplate<IncompleteType>>();
    test_is_literal_type<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_literal_type<PublicDerivedFromTemplate<Base>>();
    test_is_literal_type<PublicDerivedFromTemplate<Derived>>();
    test_is_not_literal_type<PublicDerivedFromTemplate<Class>>();
    test_is_literal_type<PrivateDerivedFromTemplate<Base>>();
    test_is_literal_type<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_literal_type<PrivateDerivedFromTemplate<Class>>();
    test_is_literal_type<ProtectedDerivedFromTemplate<Base>>();
    test_is_literal_type<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_literal_type<ProtectedDerivedFromTemplate<Class>>();
#if PHI_COMPILER_IS(GCC)
    test_is_literal_type<VirtualDerivedFromTemplate<Base>>();
    test_is_literal_type<VirtualDerivedFromTemplate<Derived>>();
#else
    test_is_not_literal_type<VirtualDerivedFromTemplate<Base>>();
    test_is_not_literal_type<VirtualDerivedFromTemplate<Derived>>();
#endif
    test_is_not_literal_type<VirtualDerivedFromTemplate<Class>>();
    test_is_literal_type<Union>();
    test_is_literal_type<NonEmptyUnion>();
#if PHI_COMPILER_IS(GCC)
    test_is_literal_type_cxx20<NonTrivialUnion>();
#else
    test_is_not_literal_type<NonTrivialUnion>();
#endif
    test_is_literal_type<Empty>();
    test_is_not_literal_type<NotEmpty>();
    test_is_not_literal_type<NonTrivial>();
    test_is_literal_type<BitZero>();
    test_is_literal_type<BitOne>();
    test_is_literal_type<Base>();
    test_is_literal_type<Derived>();
    test_is_not_literal_type<NotEmptyBase>();
    test_is_literal_type<EmptyBase>();
#if PHI_COMPILER_IS(GCC)
    test_is_literal_type<VirtualBase>();
#else
    test_is_not_literal_type<VirtualBase>();
#endif
    test_is_literal_type<Polymorphic>();
    test_is_literal_type<DerivedPolymorphic>();
    test_is_not_literal_type<Abstract>();
    test_is_literal_type_cxx20<PublicAbstract>();
    test_is_literal_type_cxx20<PrivateAbstract>();
    test_is_literal_type_cxx20<ProtectedAbstract>();
    test_is_not_literal_type<AbstractTemplate<int>>();
    test_is_literal_type<AbstractTemplate<double>>();
    test_is_not_literal_type<AbstractTemplate<Class>>();
    test_is_not_literal_type<AbstractTemplate<IncompleteType>>();
#if PHI_COMPILER_IS(GCC)
    test_is_literal_type<PublicAbstractDeletedDestructor>();
    test_is_literal_type<ProtectedAbstractDeletedDestructor>();
    test_is_literal_type<PrivateAbstractDeletedDestructor>();
#else
    test_is_not_literal_type_cxx20<PublicAbstractDeletedDestructor>();
    test_is_not_literal_type_cxx20<ProtectedAbstractDeletedDestructor>();
    test_is_not_literal_type_cxx20<PrivateAbstractDeletedDestructor>();
#endif
    test_is_literal_type<Final>();
    test_is_literal_type<FinalDerived>();
    test_is_literal_type<PublicDestructor>();
    test_is_literal_type<ProtectedDestructor>();
    test_is_literal_type<PrivateDestructor>();
    test_is_literal_type_cxx20<VirtualPublicDestructor>();
    test_is_literal_type_cxx20<VirtualProtectedDestructor>();
    test_is_literal_type_cxx20<VirtualPrivateDestructor>();
    test_is_not_literal_type<PurePublicDestructor>();
    test_is_not_literal_type<PureProtectedDestructor>();
    test_is_not_literal_type<PurePrivateDestructor>();
#if PHI_COMPILER_IS(GCC)
    test_is_literal_type<DeletedPublicDestructor>();
    test_is_literal_type<DeletedProtectedDestructor>();
    test_is_literal_type<DeletedPrivateDestructor>();
#else
    test_is_not_literal_type_cxx20<DeletedPublicDestructor>();
    test_is_not_literal_type_cxx20<DeletedProtectedDestructor>();
    test_is_not_literal_type_cxx20<DeletedPrivateDestructor>();
#endif
    test_is_not_literal_type<DeletedVirtualPublicDestructor>();
    test_is_not_literal_type<DeletedVirtualProtectedDestructor>();
    test_is_not_literal_type<DeletedVirtualPrivateDestructor>();
    test_is_not_literal_type<ExplicitClass>();
    test_is_not_literal_type<NothrowExplicitClass>();
    test_is_not_literal_type<ThrowExplicitClass>();
    test_is_not_literal_type<ThrowDefaultClass>();
    test_is_not_literal_type<ThrowCopyConsClass>();
    test_is_not_literal_type<ThrowMoveConsClass>();
    test_is_not_literal_type<ThrowDestructor>();
    test_is_not_literal_type<NoexceptExplicitClass>();
    test_is_not_literal_type<ExceptExplicitClass>();
    test_is_not_literal_type<NoexceptDefaultClass>();
    test_is_not_literal_type<ExceptDefaultClass>();
    test_is_not_literal_type<NoexceptCopyConsClass>();
    test_is_not_literal_type<ExceptCopyConsClass>();
    test_is_not_literal_type<NoexceptMoveConsClass>();
    test_is_not_literal_type<ExceptMoveConsClass>();
    test_is_literal_type<NoexceptCopyAssignClass>();
    test_is_literal_type<ExceptCopyAssignClass>();
    test_is_not_literal_type_cxx20<NoexceptMoveAssignClass>();
    test_is_literal_type<ExceptMoveAssignClass>();
    test_is_literal_type<DeletedCopyAssignClass>();
    test_is_literal_type<DeletedMoveAssignClass>();
    test_is_not_literal_type<NoexceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_literal_type<ExceptMoveConsNoexceptMoveAssignClass>();
    test_is_not_literal_type<NoexceptMoveConsExceptMoveAssignClass>();
    test_is_not_literal_type<ExceptMoveConsExceptMoveAssignClass>();
    test_is_literal_type<ImplicitTo<int>>();
    test_is_literal_type<ImplicitTo<float>>();
    test_is_literal_type<ImplicitTo<Class>>();
    test_is_literal_type<DeletedImplicitTo<int>>();
    test_is_literal_type<DeletedImplicitTo<float>>();
    test_is_literal_type<DeletedImplicitTo<Class>>();
    test_is_literal_type<ExplicitTo<int>>();
    test_is_literal_type<ExplicitTo<float>>();
    test_is_literal_type<ExplicitTo<Class>>();
    test_is_literal_type<DeletedExplicitTo<int>>();
    test_is_literal_type<DeletedExplicitTo<float>>();
    test_is_literal_type<DeletedExplicitTo<Class>>();
    test_is_not_literal_type<Ellipsis>();
#if PHI_COMPILER_IS(GCC)
    test_is_literal_type<DeletedEllipsis>();
#else
    test_is_not_literal_type_cxx20<DeletedEllipsis>();
#endif
    test_is_not_literal_type<CopyConsOnlyType>();
    test_is_not_literal_type<MoveConsOnlyType>();
    test_is_literal_type<OverloadedOperators>();
    test_is_literal_type<PublicIntMember>();
    test_is_literal_type<ProtectedIntMember>();
    test_is_literal_type<PrivateIntMember>();
    test_is_literal_type<PublicStaticIntMember>();
    test_is_literal_type<ProtectedStaticIntMember>();
    test_is_literal_type<PrivateStaticIntMember>();
    test_is_literal_type<PublicTemplateMember<int>>();
    test_is_literal_type<PublicTemplateMember<float>>();
    test_is_not_literal_type<PublicTemplateMember<Class>>();
    test_is_literal_type<ProtectedTemplateMember<int>>();
    test_is_literal_type<ProtectedTemplateMember<float>>();
    test_is_not_literal_type<ProtectedTemplateMember<Class>>();
    test_is_literal_type<PrivateTemplateMember<int>>();
    test_is_literal_type<PrivateTemplateMember<float>>();
    test_is_not_literal_type<PrivateTemplateMember<Class>>();
    test_is_literal_type<PublicStaticTemplateMember<int>>();
    test_is_literal_type<PublicStaticTemplateMember<float>>();
    test_is_literal_type<PublicStaticTemplateMember<Class>>();
    test_is_literal_type<ProtectedStaticTemplateMember<int>>();
    test_is_literal_type<ProtectedStaticTemplateMember<float>>();
    test_is_literal_type<ProtectedStaticTemplateMember<Class>>();
    test_is_literal_type<PrivateStaticTemplateMember<int>>();
    test_is_literal_type<PrivateStaticTemplateMember<float>>();
    test_is_literal_type<PrivateStaticTemplateMember<Class>>();
    test_is_literal_type<Enum>();
    test_is_literal_type<EnumSigned>();
    test_is_literal_type<EnumUnsigned>();
    test_is_literal_type<EnumClass>();
    test_is_literal_type<EnumStruct>();
    test_is_not_literal_type<Function>();
    test_is_literal_type<FunctionPtr>();
    test_is_literal_type<MemberObjectPtr>();
    test_is_literal_type<MemberFunctionPtr>();
    test_is_literal_type_cxx17<LambdaType>();
    test_is_literal_type_cxx17<LambdaNoexceptType>();
    test_is_literal_type_cxx17<LambdaThrowsType>();
    test_is_literal_type<IncompleteEnumSigned>();
    test_is_literal_type<IncompleteEnumUnsigned>();
    test_is_literal_type<IncompleteEnumClass>();
    test_is_literal_type<IncompleteEnumStruct>();
    test_is_literal_type<int Class::*>();
    test_is_literal_type<float Class::*>();
    test_is_literal_type<void * Class::*>();
    test_is_literal_type<int * Class::*>();
    test_is_literal_type<int Class::*&>();
    test_is_literal_type<float Class::*&>();
    test_is_literal_type<void * Class::*&>();
    test_is_literal_type<int * Class::*&>();
    test_is_literal_type<int Class::*&&>();
    test_is_literal_type<float Class::*&&>();
    test_is_literal_type<void * Class::*&&>();
    test_is_literal_type<int * Class::*&&>();
    test_is_literal_type<int Class::*const>();
    test_is_literal_type<float Class::*const>();
    test_is_literal_type<void * Class::*const>();
    test_is_literal_type<int Class::*const&>();
    test_is_literal_type<float Class::*const&>();
    test_is_literal_type<void * Class::*const&>();
    test_is_literal_type<int Class::*const&&>();
    test_is_literal_type<float Class::*const&&>();
    test_is_literal_type<void * Class::*const&&>();
    test_is_literal_type<int Class::*volatile>();
    test_is_literal_type<float Class::*volatile>();
    test_is_literal_type<void * Class::*volatile>();
    test_is_literal_type<int Class::*volatile&>();
    test_is_literal_type<float Class::*volatile&>();
    test_is_literal_type<void * Class::*volatile&>();
    test_is_literal_type<int Class::*volatile&&>();
    test_is_literal_type<float Class::*volatile&&>();
    test_is_literal_type<void * Class::*volatile&&>();
    test_is_literal_type<int Class::*const volatile>();
    test_is_literal_type<float Class::*const volatile>();
    test_is_literal_type<void * Class::*const volatile>();
    test_is_literal_type<int Class::*const volatile&>();
    test_is_literal_type<float Class::*const volatile&>();
    test_is_literal_type<void * Class::*const volatile&>();
    test_is_literal_type<int Class::*const volatile&&>();
    test_is_literal_type<float Class::*const volatile&&>();
    test_is_literal_type<void * Class::*const volatile&&>();
    test_is_literal_type<NonDefaultConstructible>();
    test_is_literal_type<NonCopyConstructible>();
    test_is_literal_type<NonMoveConstructible>();
    test_is_literal_type<NonCopyAssignable>();
    test_is_literal_type<NonMoveAssignable>();
    test_is_literal_type<NonAssignable>();
    test_is_literal_type<NonCopyable>();
    test_is_literal_type<NonMoveable>();
    test_is_literal_type<NonConstructible>();
#if PHI_COMPILER_IS(GCC)
    test_is_literal_type<NonDestructible>();
#else
    test_is_not_literal_type_cxx20<NonDestructible>();
#endif
    test_is_literal_type_cxx20<Tracked>();
    test_is_literal_type<TrapConstructible>();
    test_is_literal_type<TrapImplicitConversion>();
    test_is_literal_type<TrapComma>();
    test_is_literal_type<TrapCall>();
    test_is_literal_type<TrapSelfAssign>();
    test_is_literal_type<TrapDeref>();
    test_is_literal_type<TrapArraySubscript>();

    test_is_not_literal_type<void()>();
    test_is_not_literal_type<void()&>();
    test_is_not_literal_type<void() &&>();
    test_is_not_literal_type<void() const>();
    test_is_not_literal_type<void() const&>();
    test_is_not_literal_type<void() const&&>();
    test_is_not_literal_type<void() volatile>();
    test_is_not_literal_type<void() volatile&>();
    test_is_not_literal_type<void() volatile&&>();
    test_is_not_literal_type<void() const volatile>();
    test_is_not_literal_type<void() const volatile&>();
    test_is_not_literal_type<void() const volatile&&>();
    test_is_not_literal_type<void() noexcept>();
    test_is_not_literal_type<void()& noexcept>();
    test_is_not_literal_type<void()&& noexcept>();
    test_is_not_literal_type<void() const noexcept>();
    test_is_not_literal_type<void() const& noexcept>();
    test_is_not_literal_type<void() const&& noexcept>();
    test_is_not_literal_type<void() volatile noexcept>();
    test_is_not_literal_type<void() volatile& noexcept>();
    test_is_not_literal_type<void() volatile&& noexcept>();
    test_is_not_literal_type<void() const volatile noexcept>();
    test_is_not_literal_type<void() const volatile& noexcept>();
    test_is_not_literal_type<void() const volatile&& noexcept>();

    test_is_not_literal_type<void(int)>();
    test_is_not_literal_type<void(int)&>();
    test_is_not_literal_type<void(int) &&>();
    test_is_not_literal_type<void(int) const>();
    test_is_not_literal_type<void(int) const&>();
    test_is_not_literal_type<void(int) const&&>();
    test_is_not_literal_type<void(int) volatile>();
    test_is_not_literal_type<void(int) volatile&>();
    test_is_not_literal_type<void(int) volatile&&>();
    test_is_not_literal_type<void(int) const volatile>();
    test_is_not_literal_type<void(int) const volatile&>();
    test_is_not_literal_type<void(int) const volatile&&>();
    test_is_not_literal_type<void(int) noexcept>();
    test_is_not_literal_type<void(int)& noexcept>();
    test_is_not_literal_type<void(int)&& noexcept>();
    test_is_not_literal_type<void(int) const noexcept>();
    test_is_not_literal_type<void(int) const& noexcept>();
    test_is_not_literal_type<void(int) const&& noexcept>();
    test_is_not_literal_type<void(int) volatile noexcept>();
    test_is_not_literal_type<void(int) volatile& noexcept>();
    test_is_not_literal_type<void(int) volatile&& noexcept>();
    test_is_not_literal_type<void(int) const volatile noexcept>();
    test_is_not_literal_type<void(int) const volatile& noexcept>();
    test_is_not_literal_type<void(int) const volatile&& noexcept>();

    test_is_not_literal_type<void(...)>();
    test_is_not_literal_type<void(...)&>();
    test_is_not_literal_type<void(...) &&>();
    test_is_not_literal_type<void(...) const>();
    test_is_not_literal_type<void(...) const&>();
    test_is_not_literal_type<void(...) const&&>();
    test_is_not_literal_type<void(...) volatile>();
    test_is_not_literal_type<void(...) volatile&>();
    test_is_not_literal_type<void(...) volatile&&>();
    test_is_not_literal_type<void(...) const volatile>();
    test_is_not_literal_type<void(...) const volatile&>();
    test_is_not_literal_type<void(...) const volatile&&>();
    test_is_not_literal_type<void(...) noexcept>();
    test_is_not_literal_type<void(...)& noexcept>();
    test_is_not_literal_type<void(...)&& noexcept>();
    test_is_not_literal_type<void(...) const noexcept>();
    test_is_not_literal_type<void(...) const& noexcept>();
    test_is_not_literal_type<void(...) const&& noexcept>();
    test_is_not_literal_type<void(...) volatile noexcept>();
    test_is_not_literal_type<void(...) volatile& noexcept>();
    test_is_not_literal_type<void(...) volatile&& noexcept>();
    test_is_not_literal_type<void(...) const volatile noexcept>();
    test_is_not_literal_type<void(...) const volatile& noexcept>();
    test_is_not_literal_type<void(...) const volatile&& noexcept>();

    test_is_not_literal_type<void(int, ...)>();
    test_is_not_literal_type<void(int, ...)&>();
    test_is_not_literal_type<void(int, ...) &&>();
    test_is_not_literal_type<void(int, ...) const>();
    test_is_not_literal_type<void(int, ...) const&>();
    test_is_not_literal_type<void(int, ...) const&&>();
    test_is_not_literal_type<void(int, ...) volatile>();
    test_is_not_literal_type<void(int, ...) volatile&>();
    test_is_not_literal_type<void(int, ...) volatile&&>();
    test_is_not_literal_type<void(int, ...) const volatile>();
    test_is_not_literal_type<void(int, ...) const volatile&>();
    test_is_not_literal_type<void(int, ...) const volatile&&>();
    test_is_not_literal_type<void(int, ...) noexcept>();
    test_is_not_literal_type<void(int, ...)& noexcept>();
    test_is_not_literal_type<void(int, ...)&& noexcept>();
    test_is_not_literal_type<void(int, ...) const noexcept>();
    test_is_not_literal_type<void(int, ...) const& noexcept>();
    test_is_not_literal_type<void(int, ...) const&& noexcept>();
    test_is_not_literal_type<void(int, ...) volatile noexcept>();
    test_is_not_literal_type<void(int, ...) volatile& noexcept>();
    test_is_not_literal_type<void(int, ...) volatile&& noexcept>();
    test_is_not_literal_type<void(int, ...) const volatile noexcept>();
    test_is_not_literal_type<void(int, ...) const volatile& noexcept>();
    test_is_not_literal_type<void(int, ...) const volatile&& noexcept>();

    test_is_not_literal_type<int()>();
    test_is_not_literal_type<int()&>();
    test_is_not_literal_type<int() &&>();
    test_is_not_literal_type<int() const>();
    test_is_not_literal_type<int() const&>();
    test_is_not_literal_type<int() const&&>();
    test_is_not_literal_type<int() volatile>();
    test_is_not_literal_type<int() volatile&>();
    test_is_not_literal_type<int() volatile&&>();
    test_is_not_literal_type<int() const volatile>();
    test_is_not_literal_type<int() const volatile&>();
    test_is_not_literal_type<int() const volatile&&>();
    test_is_not_literal_type<int() noexcept>();
    test_is_not_literal_type<int()& noexcept>();
    test_is_not_literal_type<int()&& noexcept>();
    test_is_not_literal_type<int() const noexcept>();
    test_is_not_literal_type<int() const& noexcept>();
    test_is_not_literal_type<int() const&& noexcept>();
    test_is_not_literal_type<int() volatile noexcept>();
    test_is_not_literal_type<int() volatile& noexcept>();
    test_is_not_literal_type<int() volatile&& noexcept>();
    test_is_not_literal_type<int() const volatile noexcept>();
    test_is_not_literal_type<int() const volatile& noexcept>();
    test_is_not_literal_type<int() const volatile&& noexcept>();

    test_is_not_literal_type<int(int)>();
    test_is_not_literal_type<int(int)&>();
    test_is_not_literal_type<int(int) &&>();
    test_is_not_literal_type<int(int) const>();
    test_is_not_literal_type<int(int) const&>();
    test_is_not_literal_type<int(int) const&&>();
    test_is_not_literal_type<int(int) volatile>();
    test_is_not_literal_type<int(int) volatile&>();
    test_is_not_literal_type<int(int) volatile&&>();
    test_is_not_literal_type<int(int) const volatile>();
    test_is_not_literal_type<int(int) const volatile&>();
    test_is_not_literal_type<int(int) const volatile&&>();
    test_is_not_literal_type<int(int) noexcept>();
    test_is_not_literal_type<int(int)& noexcept>();
    test_is_not_literal_type<int(int)&& noexcept>();
    test_is_not_literal_type<int(int) const noexcept>();
    test_is_not_literal_type<int(int) const& noexcept>();
    test_is_not_literal_type<int(int) const&& noexcept>();
    test_is_not_literal_type<int(int) volatile noexcept>();
    test_is_not_literal_type<int(int) volatile& noexcept>();
    test_is_not_literal_type<int(int) volatile&& noexcept>();
    test_is_not_literal_type<int(int) const volatile noexcept>();
    test_is_not_literal_type<int(int) const volatile& noexcept>();
    test_is_not_literal_type<int(int) const volatile&& noexcept>();

    test_is_not_literal_type<int(...)>();
    test_is_not_literal_type<int(...)&>();
    test_is_not_literal_type<int(...) &&>();
    test_is_not_literal_type<int(...) const>();
    test_is_not_literal_type<int(...) const&>();
    test_is_not_literal_type<int(...) const&&>();
    test_is_not_literal_type<int(...) volatile>();
    test_is_not_literal_type<int(...) volatile&>();
    test_is_not_literal_type<int(...) volatile&&>();
    test_is_not_literal_type<int(...) const volatile>();
    test_is_not_literal_type<int(...) const volatile&>();
    test_is_not_literal_type<int(...) const volatile&&>();
    test_is_not_literal_type<int(...) noexcept>();
    test_is_not_literal_type<int(...)& noexcept>();
    test_is_not_literal_type<int(...)&& noexcept>();
    test_is_not_literal_type<int(...) const noexcept>();
    test_is_not_literal_type<int(...) const& noexcept>();
    test_is_not_literal_type<int(...) const&& noexcept>();
    test_is_not_literal_type<int(...) volatile noexcept>();
    test_is_not_literal_type<int(...) volatile& noexcept>();
    test_is_not_literal_type<int(...) volatile&& noexcept>();
    test_is_not_literal_type<int(...) const volatile noexcept>();
    test_is_not_literal_type<int(...) const volatile& noexcept>();
    test_is_not_literal_type<int(...) const volatile&& noexcept>();

    test_is_not_literal_type<int(int, ...)>();
    test_is_not_literal_type<int(int, ...)&>();
    test_is_not_literal_type<int(int, ...) &&>();
    test_is_not_literal_type<int(int, ...) const>();
    test_is_not_literal_type<int(int, ...) const&>();
    test_is_not_literal_type<int(int, ...) const&&>();
    test_is_not_literal_type<int(int, ...) volatile>();
    test_is_not_literal_type<int(int, ...) volatile&>();
    test_is_not_literal_type<int(int, ...) volatile&&>();
    test_is_not_literal_type<int(int, ...) const volatile>();
    test_is_not_literal_type<int(int, ...) const volatile&>();
    test_is_not_literal_type<int(int, ...) const volatile&&>();
    test_is_not_literal_type<int(int, ...) noexcept>();
    test_is_not_literal_type<int(int, ...)& noexcept>();
    test_is_not_literal_type<int(int, ...)&& noexcept>();
    test_is_not_literal_type<int(int, ...) const noexcept>();
    test_is_not_literal_type<int(int, ...) const& noexcept>();
    test_is_not_literal_type<int(int, ...) const&& noexcept>();
    test_is_not_literal_type<int(int, ...) volatile noexcept>();
    test_is_not_literal_type<int(int, ...) volatile& noexcept>();
    test_is_not_literal_type<int(int, ...) volatile&& noexcept>();
    test_is_not_literal_type<int(int, ...) const volatile noexcept>();
    test_is_not_literal_type<int(int, ...) const volatile& noexcept>();
    test_is_not_literal_type<int(int, ...) const volatile&& noexcept>();

    test_is_literal_type<void (*)()>();
    test_is_literal_type<void (*)() noexcept>();

    test_is_literal_type<void (*)(int)>();
    test_is_literal_type<void (*)(int) noexcept>();

    test_is_literal_type<void (*)(...)>();
    test_is_literal_type<void (*)(...) noexcept>();

    test_is_literal_type<void (*)(int, ...)>();
    test_is_literal_type<void (*)(int, ...) noexcept>();

    test_is_literal_type<int (*)()>();
    test_is_literal_type<int (*)() noexcept>();

    test_is_literal_type<int (*)(int)>();
    test_is_literal_type<int (*)(int) noexcept>();

    test_is_literal_type<int (*)(...)>();
    test_is_literal_type<int (*)(...) noexcept>();

    test_is_literal_type<int (*)(int, ...)>();
    test_is_literal_type<int (*)(int, ...) noexcept>();

    test_is_literal_type<void (&)()>();
    test_is_literal_type<void (&)() noexcept>();

    test_is_literal_type<void (&)(int)>();
    test_is_literal_type<void (&)(int) noexcept>();

    test_is_literal_type<void (&)(...)>();
    test_is_literal_type<void (&)(...) noexcept>();

    test_is_literal_type<void (&)(int, ...)>();
    test_is_literal_type<void (&)(int, ...) noexcept>();

    test_is_literal_type<int (&)()>();
    test_is_literal_type<int (&)() noexcept>();

    test_is_literal_type<int (&)(int)>();
    test_is_literal_type<int (&)(int) noexcept>();

    test_is_literal_type<int (&)(...)>();
    test_is_literal_type<int (&)(...) noexcept>();

    test_is_literal_type<int (&)(int, ...)>();
    test_is_literal_type<int (&)(int, ...) noexcept>();

    test_is_literal_type<void(&&)()>();
    test_is_literal_type<void(&&)() noexcept>();

    test_is_literal_type<void(&&)(int)>();
    test_is_literal_type<void(&&)(int) noexcept>();

    test_is_literal_type<void(&&)(...)>();
    test_is_literal_type<void(&&)(...) noexcept>();

    test_is_literal_type<void(&&)(int, ...)>();
    test_is_literal_type<void(&&)(int, ...) noexcept>();

    test_is_literal_type<int(&&)()>();
    test_is_literal_type<int(&&)() noexcept>();

    test_is_literal_type<int(&&)(int)>();
    test_is_literal_type<int(&&)(int) noexcept>();

    test_is_literal_type<int(&&)(...)>();
    test_is_literal_type<int(&&)(...) noexcept>();

    test_is_literal_type<int(&&)(int, ...)>();
    test_is_literal_type<int(&&)(int, ...) noexcept>();

    test_is_literal_type<void (Class::*)()>();
    test_is_literal_type<void (Class::*)()&>();
    test_is_literal_type<void (Class::*)() &&>();
    test_is_literal_type<void (Class::*)() const>();
    test_is_literal_type<void (Class::*)() const&>();
    test_is_literal_type<void (Class::*)() const&&>();
    test_is_literal_type<void (Class::*)() noexcept>();
    test_is_literal_type<void (Class::*)()& noexcept>();
    test_is_literal_type<void (Class::*)()&& noexcept>();
    test_is_literal_type<void (Class::*)() const noexcept>();
    test_is_literal_type<void (Class::*)() const& noexcept>();
    test_is_literal_type<void (Class::*)() const&& noexcept>();

    test_is_literal_type<void (Class::*)(int)>();
    test_is_literal_type<void (Class::*)(int)&>();
    test_is_literal_type<void (Class::*)(int) &&>();
    test_is_literal_type<void (Class::*)(int) const>();
    test_is_literal_type<void (Class::*)(int) const&>();
    test_is_literal_type<void (Class::*)(int) const&&>();
    test_is_literal_type<void (Class::*)(int) noexcept>();
    test_is_literal_type<void (Class::*)(int)& noexcept>();
    test_is_literal_type<void (Class::*)(int)&& noexcept>();
    test_is_literal_type<void (Class::*)(int) const noexcept>();
    test_is_literal_type<void (Class::*)(int) const& noexcept>();
    test_is_literal_type<void (Class::*)(int) const&& noexcept>();

    test_is_literal_type<void (Class::*)(...)>();
    test_is_literal_type<void (Class::*)(...)&>();
    test_is_literal_type<void (Class::*)(...) &&>();
    test_is_literal_type<void (Class::*)(...) const>();
    test_is_literal_type<void (Class::*)(...) const&>();
    test_is_literal_type<void (Class::*)(...) const&&>();
    test_is_literal_type<void (Class::*)(...) noexcept>();
    test_is_literal_type<void (Class::*)(...)& noexcept>();
    test_is_literal_type<void (Class::*)(...)&& noexcept>();
    test_is_literal_type<void (Class::*)(...) const noexcept>();
    test_is_literal_type<void (Class::*)(...) const& noexcept>();
    test_is_literal_type<void (Class::*)(...) const&& noexcept>();

    test_is_literal_type<void (Class::*)(int, ...)>();
    test_is_literal_type<void (Class::*)(int, ...)&>();
    test_is_literal_type<void (Class::*)(int, ...) &&>();
    test_is_literal_type<void (Class::*)(int, ...) const>();
    test_is_literal_type<void (Class::*)(int, ...) const&>();
    test_is_literal_type<void (Class::*)(int, ...) const&&>();
    test_is_literal_type<void (Class::*)(int, ...) noexcept>();
    test_is_literal_type<void (Class::*)(int, ...)& noexcept>();
    test_is_literal_type<void (Class::*)(int, ...)&& noexcept>();
    test_is_literal_type<void (Class::*)(int, ...) const noexcept>();
    test_is_literal_type<void (Class::*)(int, ...) const& noexcept>();
    test_is_literal_type<void (Class::*)(int, ...) const&& noexcept>();

    test_is_literal_type<int (Class::*)()>();
    test_is_literal_type<int (Class::*)()&>();
    test_is_literal_type<int (Class::*)() &&>();
    test_is_literal_type<int (Class::*)() const>();
    test_is_literal_type<int (Class::*)() const&>();
    test_is_literal_type<int (Class::*)() const&&>();
    test_is_literal_type<int (Class::*)() noexcept>();
    test_is_literal_type<int (Class::*)()& noexcept>();
    test_is_literal_type<int (Class::*)()&& noexcept>();
    test_is_literal_type<int (Class::*)() const noexcept>();
    test_is_literal_type<int (Class::*)() const& noexcept>();
    test_is_literal_type<int (Class::*)() const&& noexcept>();

    test_is_literal_type<int (Class::*)(int)>();
    test_is_literal_type<int (Class::*)(int)&>();
    test_is_literal_type<int (Class::*)(int) &&>();
    test_is_literal_type<int (Class::*)(int) const>();
    test_is_literal_type<int (Class::*)(int) const&>();
    test_is_literal_type<int (Class::*)(int) const&&>();
    test_is_literal_type<int (Class::*)(int) noexcept>();
    test_is_literal_type<int (Class::*)(int)& noexcept>();
    test_is_literal_type<int (Class::*)(int)&& noexcept>();
    test_is_literal_type<int (Class::*)(int) const noexcept>();
    test_is_literal_type<int (Class::*)(int) const& noexcept>();
    test_is_literal_type<int (Class::*)(int) const&& noexcept>();

    test_is_literal_type<int (Class::*)(...)>();
    test_is_literal_type<int (Class::*)(...)&>();
    test_is_literal_type<int (Class::*)(...) &&>();
    test_is_literal_type<int (Class::*)(...) const>();
    test_is_literal_type<int (Class::*)(...) const&>();
    test_is_literal_type<int (Class::*)(...) const&&>();
    test_is_literal_type<int (Class::*)(...) noexcept>();
    test_is_literal_type<int (Class::*)(...)& noexcept>();
    test_is_literal_type<int (Class::*)(...)&& noexcept>();
    test_is_literal_type<int (Class::*)(...) const noexcept>();
    test_is_literal_type<int (Class::*)(...) const& noexcept>();
    test_is_literal_type<int (Class::*)(...) const&& noexcept>();

    test_is_literal_type<int (Class::*)(int, ...)>();
    test_is_literal_type<int (Class::*)(int, ...)&>();
    test_is_literal_type<int (Class::*)(int, ...) &&>();
    test_is_literal_type<int (Class::*)(int, ...) const>();
    test_is_literal_type<int (Class::*)(int, ...) const&>();
    test_is_literal_type<int (Class::*)(int, ...) const&&>();
    test_is_literal_type<int (Class::*)(int, ...) noexcept>();
    test_is_literal_type<int (Class::*)(int, ...)& noexcept>();
    test_is_literal_type<int (Class::*)(int, ...)&& noexcept>();
    test_is_literal_type<int (Class::*)(int, ...) const noexcept>();
    test_is_literal_type<int (Class::*)(int, ...) const& noexcept>();
    test_is_literal_type<int (Class::*)(int, ...) const&& noexcept>();
}
