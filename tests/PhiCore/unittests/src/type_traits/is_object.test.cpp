#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_lvalue_reference.hpp>
#include <phi/type_traits/is_object.hpp>
#include <phi/type_traits/is_reference.hpp>
#include <phi/type_traits/is_rvalue_reference.hpp>
#include <phi/type_traits/is_void.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_object_impl()
{
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_object<T>::value);

    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_object_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_object_v<T>);

    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);
#    endif

    // Standard compatibililty
    STATIC_REQUIRE(std::is_object<T>::value);
#endif
}

template <typename T>
void test_is_not_object_impl()
{
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE_FALSE(phi::is_object<T>::value);
    STATIC_REQUIRE(phi::is_not_object<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_object_v<T>);
    STATIC_REQUIRE(phi::is_not_object_v<T>);
#    endif

    // Standard compatibililty
    STATIC_REQUIRE_FALSE(std::is_object<T>::value);
#endif
}

template <typename T>
void test_is_object()
{
    test_is_object_impl<T>();
    test_is_object_impl<const T>();
    test_is_object_impl<volatile T>();
    test_is_object_impl<const volatile T>();
}

template <typename T>
void test_is_not_object()
{
    test_is_not_object_impl<T>();
    test_is_not_object_impl<const T>();
    test_is_not_object_impl<volatile T>();
    test_is_not_object_impl<const volatile T>();
}

TEST_CASE("is_object")
{
    test_is_not_object<void>();
    test_is_object<phi::nullptr_t>();
    test_is_object<bool>();
    test_is_object<char>();
    test_is_object<signed char>();
    test_is_object<unsigned char>();
    test_is_object<short>();
    test_is_object<unsigned short>();
    test_is_object<int>();
    test_is_object<unsigned int>();
    test_is_object<long>();
    test_is_object<unsigned long>();
    test_is_object<long long>();
    test_is_object<unsigned long long>();
    test_is_object<float>();
    test_is_object<double>();
    test_is_object<long double>();
    test_is_object<char8_t>();
    test_is_object<char16_t>();
    test_is_object<char32_t>();
    test_is_object<wchar_t>();

    test_is_object<phi::boolean>();
    test_is_object<phi::integer<signed char>>();
    test_is_object<phi::integer<unsigned char>>();
    test_is_object<phi::integer<short>>();
    test_is_object<phi::integer<unsigned short>>();
    test_is_object<phi::integer<int>>();
    test_is_object<phi::integer<unsigned int>>();
    test_is_object<phi::integer<long>>();
    test_is_object<phi::integer<unsigned long>>();
    test_is_object<phi::integer<long long>>();
    test_is_object<phi::integer<unsigned long long>>();
    test_is_object<phi::floating_point<float>>();
    test_is_object<phi::floating_point<double>>();
    test_is_object<phi::floating_point<long double>>();

    test_is_object<std::vector<int>>();
    test_is_object<phi::scope_ptr<int>>();

    test_is_not_object<int&>();
    test_is_not_object<const int&>();
    test_is_not_object<volatile int&>();
    test_is_not_object<const volatile int&>();
    test_is_not_object<int&&>();
    test_is_not_object<const int&&>();
    test_is_not_object<volatile int&&>();
    test_is_not_object<const volatile int&&>();
    test_is_object<int*>();
    test_is_object<const int*>();
    test_is_object<volatile int*>();
    test_is_object<const volatile int*>();
    test_is_object<int**>();
    test_is_object<const int**>();
    test_is_object<volatile int**>();
    test_is_object<const volatile int**>();
    test_is_not_object<int*&>();
    test_is_not_object<const int*&>();
    test_is_not_object<volatile int*&>();
    test_is_not_object<const volatile int*&>();
    test_is_not_object<int*&&>();
    test_is_not_object<const int*&&>();
    test_is_not_object<volatile int*&&>();
    test_is_not_object<const volatile int*&&>();
    test_is_object<void*>();
    test_is_object<char[3]>();
    test_is_object<char[]>();
    test_is_object<char* [3]>();
    test_is_object<char*[]>();
    test_is_object<int(*)[3]>();
    test_is_object<int(*)[]>();
    test_is_not_object<int(&)[3]>();
    test_is_not_object<int(&)[]>();
    test_is_not_object<int(&&)[3]>();
    test_is_not_object<int(&&)[]>();
    test_is_object<char[3][2]>();
    test_is_object<char[][2]>();
    test_is_object<char* [3][2]>();
    test_is_object<char*[][2]>();
    test_is_object<int(*)[3][2]>();
    test_is_object<int(*)[][2]>();
    test_is_not_object<int(&)[3][2]>();
    test_is_not_object<int(&)[][2]>();
    test_is_not_object<int(&&)[3][2]>();
    test_is_not_object<int(&&)[][2]>();
    test_is_object<Class>();
    test_is_object<Class[]>();
    test_is_object<Class[2]>();
    test_is_object<Template<void>>();
    test_is_object<Template<int>>();
    test_is_object<Template<Class>>();
    test_is_object<Template<IncompleteType>>();
    test_is_object<VariadicTemplate<>>();
    test_is_object<VariadicTemplate<void>>();
    test_is_object<VariadicTemplate<int>>();
    test_is_object<VariadicTemplate<Class>>();
    test_is_object<VariadicTemplate<IncompleteType>>();
    test_is_object<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_object<PublicDerivedFromTemplate<Base>>();
    test_is_object<PublicDerivedFromTemplate<Derived>>();
    test_is_object<PublicDerivedFromTemplate<Class>>();
    test_is_object<PrivateDerivedFromTemplate<Base>>();
    test_is_object<PrivateDerivedFromTemplate<Derived>>();
    test_is_object<PrivateDerivedFromTemplate<Class>>();
    test_is_object<ProtectedDerivedFromTemplate<Base>>();
    test_is_object<ProtectedDerivedFromTemplate<Derived>>();
    test_is_object<ProtectedDerivedFromTemplate<Class>>();
    test_is_object<Union>();
    test_is_object<NonEmptyUnion>();
    test_is_object<Empty>();
    test_is_object<NotEmpty>();
    test_is_object<BitZero>();
    test_is_object<BitOne>();
    test_is_object<Base>();
    test_is_object<Derived>();
    test_is_object<Abstract>();
    test_is_object<PublicAbstract>();
    test_is_object<PrivateAbstract>();
    test_is_object<ProtectedAbstract>();
    test_is_object<AbstractTemplate<int>>();
    test_is_object<AbstractTemplate<double>>();
    test_is_object<AbstractTemplate<Class>>();
    test_is_object<AbstractTemplate<IncompleteType>>();
    test_is_object<Final>();
    test_is_object<PublicDestructor>();
    test_is_object<ProtectedDestructor>();
    test_is_object<PrivateDestructor>();
    test_is_object<VirtualPublicDestructor>();
    test_is_object<VirtualProtectedDestructor>();
    test_is_object<VirtualPrivateDestructor>();
    test_is_object<PurePublicDestructor>();
    test_is_object<PureProtectedDestructor>();
    test_is_object<PurePrivateDestructor>();
    test_is_object<DeletedPublicDestructor>();
    test_is_object<DeletedProtectedDestructor>();
    test_is_object<DeletedPrivateDestructor>();
    test_is_object<DeletedVirtualPublicDestructor>();
    test_is_object<DeletedVirtualProtectedDestructor>();
    test_is_object<DeletedVirtualPrivateDestructor>();
    test_is_object<Enum>();
    test_is_object<EnumSigned>();
    test_is_object<EnumUnsigned>();
    test_is_object<EnumClass>();
    test_is_object<EnumStruct>();
    test_is_not_object<Function>();
    test_is_object<FunctionPtr>();
    test_is_object<MemberObjectPtr>();
    test_is_object<MemberFunctionPtr>();
    test_is_object<IncompleteType>();
    test_is_object<IncompleteTemplate<void>>();
    test_is_object<IncompleteTemplate<int>>();
    test_is_object<IncompleteTemplate<Class>>();
    test_is_object<IncompleteTemplate<IncompleteType>>();
    test_is_object<IncompleteVariadicTemplate<>>();
    test_is_object<IncompleteVariadicTemplate<void>>();
    test_is_object<IncompleteVariadicTemplate<int>>();
    test_is_object<IncompleteVariadicTemplate<Class>>();
    test_is_object<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_object<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_object<int Class::*>();
    test_is_object<float Class::*>();
    test_is_object<void * Class::*>();
    test_is_object<int * Class::*>();
    test_is_not_object<int Class::*&>();
    test_is_not_object<float Class::*&>();
    test_is_not_object<void * Class::*&>();
    test_is_not_object<int * Class::*&>();
    test_is_not_object<int Class::*&&>();
    test_is_not_object<float Class::*&&>();
    test_is_not_object<void * Class::*&&>();
    test_is_not_object<int * Class::*&&>();
    test_is_object<int Class::*const>();
    test_is_object<float Class::*const>();
    test_is_object<void * Class::*const>();
    test_is_not_object<int Class::*const&>();
    test_is_not_object<float Class::*const&>();
    test_is_not_object<void * Class::*const&>();
    test_is_not_object<int Class::*const&&>();
    test_is_not_object<float Class::*const&&>();
    test_is_not_object<void * Class::*const&&>();
    test_is_object<int Class::*volatile>();
    test_is_object<float Class::*volatile>();
    test_is_object<void * Class::*volatile>();
    test_is_not_object<int Class::*volatile&>();
    test_is_not_object<float Class::*volatile&>();
    test_is_not_object<void * Class::*volatile&>();
    test_is_not_object<int Class::*volatile&&>();
    test_is_not_object<float Class::*volatile&&>();
    test_is_not_object<void * Class::*volatile&&>();
    test_is_object<int Class::*const volatile>();
    test_is_object<float Class::*const volatile>();
    test_is_object<void * Class::*const volatile>();
    test_is_not_object<int Class::*const volatile&>();
    test_is_not_object<float Class::*const volatile&>();
    test_is_not_object<void * Class::*const volatile&>();
    test_is_not_object<int Class::*const volatile&&>();
    test_is_not_object<float Class::*const volatile&&>();
    test_is_not_object<void * Class::*const volatile&&>();
    test_is_object<NonCopyable>();
    test_is_object<NonMoveable>();
    test_is_object<NonConstructible>();
    test_is_object<Tracked>();
    test_is_object<TrapConstructible>();
    test_is_object<TrapImplicitConversion>();
    test_is_object<TrapComma>();
    test_is_object<TrapCall>();
    test_is_object<TrapSelfAssign>();
    test_is_object<TrapDeref>();
    test_is_object<TrapArraySubscript>();

    test_is_not_object<void()>();
    test_is_not_object<void()&>();
    test_is_not_object<void() &&>();
    test_is_not_object<void() const>();
    test_is_not_object<void() const&>();
    test_is_not_object<void() const&&>();
    test_is_not_object<void() volatile>();
    test_is_not_object<void() volatile&>();
    test_is_not_object<void() volatile&&>();
    test_is_not_object<void() const volatile>();
    test_is_not_object<void() const volatile&>();
    test_is_not_object<void() const volatile&&>();
    test_is_not_object<void() noexcept>();
    test_is_not_object<void()& noexcept>();
    test_is_not_object<void()&& noexcept>();
    test_is_not_object<void() const noexcept>();
    test_is_not_object<void() const& noexcept>();
    test_is_not_object<void() const&& noexcept>();
    test_is_not_object<void() volatile noexcept>();
    test_is_not_object<void() volatile& noexcept>();
    test_is_not_object<void() volatile&& noexcept>();
    test_is_not_object<void() const volatile noexcept>();
    test_is_not_object<void() const volatile& noexcept>();
    test_is_not_object<void() const volatile&& noexcept>();

    test_is_not_object<void(int)>();
    test_is_not_object<void(int)&>();
    test_is_not_object<void(int) &&>();
    test_is_not_object<void(int) const>();
    test_is_not_object<void(int) const&>();
    test_is_not_object<void(int) const&&>();
    test_is_not_object<void(int) volatile>();
    test_is_not_object<void(int) volatile&>();
    test_is_not_object<void(int) volatile&&>();
    test_is_not_object<void(int) const volatile>();
    test_is_not_object<void(int) const volatile&>();
    test_is_not_object<void(int) const volatile&&>();
    test_is_not_object<void(int) noexcept>();
    test_is_not_object<void(int)& noexcept>();
    test_is_not_object<void(int)&& noexcept>();
    test_is_not_object<void(int) const noexcept>();
    test_is_not_object<void(int) const& noexcept>();
    test_is_not_object<void(int) const&& noexcept>();
    test_is_not_object<void(int) volatile noexcept>();
    test_is_not_object<void(int) volatile& noexcept>();
    test_is_not_object<void(int) volatile&& noexcept>();
    test_is_not_object<void(int) const volatile noexcept>();
    test_is_not_object<void(int) const volatile& noexcept>();
    test_is_not_object<void(int) const volatile&& noexcept>();

    test_is_not_object<void(...)>();
    test_is_not_object<void(...)&>();
    test_is_not_object<void(...) &&>();
    test_is_not_object<void(...) const>();
    test_is_not_object<void(...) const&>();
    test_is_not_object<void(...) const&&>();
    test_is_not_object<void(...) volatile>();
    test_is_not_object<void(...) volatile&>();
    test_is_not_object<void(...) volatile&&>();
    test_is_not_object<void(...) const volatile>();
    test_is_not_object<void(...) const volatile&>();
    test_is_not_object<void(...) const volatile&&>();
    test_is_not_object<void(...) noexcept>();
    test_is_not_object<void(...)& noexcept>();
    test_is_not_object<void(...)&& noexcept>();
    test_is_not_object<void(...) const noexcept>();
    test_is_not_object<void(...) const& noexcept>();
    test_is_not_object<void(...) const&& noexcept>();
    test_is_not_object<void(...) volatile noexcept>();
    test_is_not_object<void(...) volatile& noexcept>();
    test_is_not_object<void(...) volatile&& noexcept>();
    test_is_not_object<void(...) const volatile noexcept>();
    test_is_not_object<void(...) const volatile& noexcept>();
    test_is_not_object<void(...) const volatile&& noexcept>();

    test_is_not_object<void(int, ...)>();
    test_is_not_object<void(int, ...)&>();
    test_is_not_object<void(int, ...) &&>();
    test_is_not_object<void(int, ...) const>();
    test_is_not_object<void(int, ...) const&>();
    test_is_not_object<void(int, ...) const&&>();
    test_is_not_object<void(int, ...) volatile>();
    test_is_not_object<void(int, ...) volatile&>();
    test_is_not_object<void(int, ...) volatile&&>();
    test_is_not_object<void(int, ...) const volatile>();
    test_is_not_object<void(int, ...) const volatile&>();
    test_is_not_object<void(int, ...) const volatile&&>();
    test_is_not_object<void(int, ...) noexcept>();
    test_is_not_object<void(int, ...)& noexcept>();
    test_is_not_object<void(int, ...)&& noexcept>();
    test_is_not_object<void(int, ...) const noexcept>();
    test_is_not_object<void(int, ...) const& noexcept>();
    test_is_not_object<void(int, ...) const&& noexcept>();
    test_is_not_object<void(int, ...) volatile noexcept>();
    test_is_not_object<void(int, ...) volatile& noexcept>();
    test_is_not_object<void(int, ...) volatile&& noexcept>();
    test_is_not_object<void(int, ...) const volatile noexcept>();
    test_is_not_object<void(int, ...) const volatile& noexcept>();
    test_is_not_object<void(int, ...) const volatile&& noexcept>();

    test_is_not_object<int()>();
    test_is_not_object<int()&>();
    test_is_not_object<int() &&>();
    test_is_not_object<int() const>();
    test_is_not_object<int() const&>();
    test_is_not_object<int() const&&>();
    test_is_not_object<int() volatile>();
    test_is_not_object<int() volatile&>();
    test_is_not_object<int() volatile&&>();
    test_is_not_object<int() const volatile>();
    test_is_not_object<int() const volatile&>();
    test_is_not_object<int() const volatile&&>();
    test_is_not_object<int() noexcept>();
    test_is_not_object<int()& noexcept>();
    test_is_not_object<int()&& noexcept>();
    test_is_not_object<int() const noexcept>();
    test_is_not_object<int() const& noexcept>();
    test_is_not_object<int() const&& noexcept>();
    test_is_not_object<int() volatile noexcept>();
    test_is_not_object<int() volatile& noexcept>();
    test_is_not_object<int() volatile&& noexcept>();
    test_is_not_object<int() const volatile noexcept>();
    test_is_not_object<int() const volatile& noexcept>();
    test_is_not_object<int() const volatile&& noexcept>();

    test_is_not_object<int(int)>();
    test_is_not_object<int(int)&>();
    test_is_not_object<int(int) &&>();
    test_is_not_object<int(int) const>();
    test_is_not_object<int(int) const&>();
    test_is_not_object<int(int) const&&>();
    test_is_not_object<int(int) volatile>();
    test_is_not_object<int(int) volatile&>();
    test_is_not_object<int(int) volatile&&>();
    test_is_not_object<int(int) const volatile>();
    test_is_not_object<int(int) const volatile&>();
    test_is_not_object<int(int) const volatile&&>();
    test_is_not_object<int(int) noexcept>();
    test_is_not_object<int(int)& noexcept>();
    test_is_not_object<int(int)&& noexcept>();
    test_is_not_object<int(int) const noexcept>();
    test_is_not_object<int(int) const& noexcept>();
    test_is_not_object<int(int) const&& noexcept>();
    test_is_not_object<int(int) volatile noexcept>();
    test_is_not_object<int(int) volatile& noexcept>();
    test_is_not_object<int(int) volatile&& noexcept>();
    test_is_not_object<int(int) const volatile noexcept>();
    test_is_not_object<int(int) const volatile& noexcept>();
    test_is_not_object<int(int) const volatile&& noexcept>();

    test_is_not_object<int(...)>();
    test_is_not_object<int(...)&>();
    test_is_not_object<int(...) &&>();
    test_is_not_object<int(...) const>();
    test_is_not_object<int(...) const&>();
    test_is_not_object<int(...) const&&>();
    test_is_not_object<int(...) volatile>();
    test_is_not_object<int(...) volatile&>();
    test_is_not_object<int(...) volatile&&>();
    test_is_not_object<int(...) const volatile>();
    test_is_not_object<int(...) const volatile&>();
    test_is_not_object<int(...) const volatile&&>();
    test_is_not_object<int(...) noexcept>();
    test_is_not_object<int(...)& noexcept>();
    test_is_not_object<int(...)&& noexcept>();
    test_is_not_object<int(...) const noexcept>();
    test_is_not_object<int(...) const& noexcept>();
    test_is_not_object<int(...) const&& noexcept>();
    test_is_not_object<int(...) volatile noexcept>();
    test_is_not_object<int(...) volatile& noexcept>();
    test_is_not_object<int(...) volatile&& noexcept>();
    test_is_not_object<int(...) const volatile noexcept>();
    test_is_not_object<int(...) const volatile& noexcept>();
    test_is_not_object<int(...) const volatile&& noexcept>();

    test_is_not_object<int(int, ...)>();
    test_is_not_object<int(int, ...)&>();
    test_is_not_object<int(int, ...) &&>();
    test_is_not_object<int(int, ...) const>();
    test_is_not_object<int(int, ...) const&>();
    test_is_not_object<int(int, ...) const&&>();
    test_is_not_object<int(int, ...) volatile>();
    test_is_not_object<int(int, ...) volatile&>();
    test_is_not_object<int(int, ...) volatile&&>();
    test_is_not_object<int(int, ...) const volatile>();
    test_is_not_object<int(int, ...) const volatile&>();
    test_is_not_object<int(int, ...) const volatile&&>();
    test_is_not_object<int(int, ...) noexcept>();
    test_is_not_object<int(int, ...)& noexcept>();
    test_is_not_object<int(int, ...)&& noexcept>();
    test_is_not_object<int(int, ...) const noexcept>();
    test_is_not_object<int(int, ...) const& noexcept>();
    test_is_not_object<int(int, ...) const&& noexcept>();
    test_is_not_object<int(int, ...) volatile noexcept>();
    test_is_not_object<int(int, ...) volatile& noexcept>();
    test_is_not_object<int(int, ...) volatile&& noexcept>();
    test_is_not_object<int(int, ...) const volatile noexcept>();
    test_is_not_object<int(int, ...) const volatile& noexcept>();
    test_is_not_object<int(int, ...) const volatile&& noexcept>();

    test_is_object<void (*)()>();
    test_is_object<void (*)() noexcept>();

    test_is_object<void (*)(int)>();
    test_is_object<void (*)(int) noexcept>();

    test_is_object<void (*)(...)>();
    test_is_object<void (*)(...) noexcept>();

    test_is_object<void (*)(int, ...)>();
    test_is_object<void (*)(int, ...) noexcept>();

    test_is_object<int (*)()>();
    test_is_object<int (*)() noexcept>();

    test_is_object<int (*)(int)>();
    test_is_object<int (*)(int) noexcept>();

    test_is_object<int (*)(...)>();
    test_is_object<int (*)(...) noexcept>();

    test_is_object<int (*)(int, ...)>();
    test_is_object<int (*)(int, ...) noexcept>();

    test_is_not_object<void (&)()>();
    test_is_not_object<void (&)() noexcept>();

    test_is_not_object<void (&)(int)>();
    test_is_not_object<void (&)(int) noexcept>();

    test_is_not_object<void (&)(...)>();
    test_is_not_object<void (&)(...) noexcept>();

    test_is_not_object<void (&)(int, ...)>();
    test_is_not_object<void (&)(int, ...) noexcept>();

    test_is_not_object<int (&)()>();
    test_is_not_object<int (&)() noexcept>();

    test_is_not_object<int (&)(int)>();
    test_is_not_object<int (&)(int) noexcept>();

    test_is_not_object<int (&)(...)>();
    test_is_not_object<int (&)(...) noexcept>();

    test_is_not_object<int (&)(int, ...)>();
    test_is_not_object<int (&)(int, ...) noexcept>();

    test_is_not_object<void(&&)()>();
    test_is_not_object<void(&&)() noexcept>();

    test_is_not_object<void(&&)(int)>();
    test_is_not_object<void(&&)(int) noexcept>();

    test_is_not_object<void(&&)(...)>();
    test_is_not_object<void(&&)(...) noexcept>();

    test_is_not_object<void(&&)(int, ...)>();
    test_is_not_object<void(&&)(int, ...) noexcept>();

    test_is_not_object<int(&&)()>();
    test_is_not_object<int(&&)() noexcept>();

    test_is_not_object<int(&&)(int)>();
    test_is_not_object<int(&&)(int) noexcept>();

    test_is_not_object<int(&&)(...)>();
    test_is_not_object<int(&&)(...) noexcept>();

    test_is_not_object<int(&&)(int, ...)>();
    test_is_not_object<int(&&)(int, ...) noexcept>();

    test_is_object<void (Class::*)()>();
    test_is_object<void (Class::*)()&>();
    test_is_object<void (Class::*)() &&>();
    test_is_object<void (Class::*)() const>();
    test_is_object<void (Class::*)() const&>();
    test_is_object<void (Class::*)() const&&>();
    test_is_object<void (Class::*)() noexcept>();
    test_is_object<void (Class::*)()& noexcept>();
    test_is_object<void (Class::*)()&& noexcept>();
    test_is_object<void (Class::*)() const noexcept>();
    test_is_object<void (Class::*)() const& noexcept>();
    test_is_object<void (Class::*)() const&& noexcept>();

    test_is_object<void (Class::*)(int)>();
    test_is_object<void (Class::*)(int)&>();
    test_is_object<void (Class::*)(int) &&>();
    test_is_object<void (Class::*)(int) const>();
    test_is_object<void (Class::*)(int) const&>();
    test_is_object<void (Class::*)(int) const&&>();
    test_is_object<void (Class::*)(int) noexcept>();
    test_is_object<void (Class::*)(int)& noexcept>();
    test_is_object<void (Class::*)(int)&& noexcept>();
    test_is_object<void (Class::*)(int) const noexcept>();
    test_is_object<void (Class::*)(int) const& noexcept>();
    test_is_object<void (Class::*)(int) const&& noexcept>();

    test_is_object<void (Class::*)(...)>();
    test_is_object<void (Class::*)(...)&>();
    test_is_object<void (Class::*)(...) &&>();
    test_is_object<void (Class::*)(...) const>();
    test_is_object<void (Class::*)(...) const&>();
    test_is_object<void (Class::*)(...) const&&>();
    test_is_object<void (Class::*)(...) noexcept>();
    test_is_object<void (Class::*)(...)& noexcept>();
    test_is_object<void (Class::*)(...)&& noexcept>();
    test_is_object<void (Class::*)(...) const noexcept>();
    test_is_object<void (Class::*)(...) const& noexcept>();
    test_is_object<void (Class::*)(...) const&& noexcept>();

    test_is_object<void (Class::*)(int, ...)>();
    test_is_object<void (Class::*)(int, ...)&>();
    test_is_object<void (Class::*)(int, ...) &&>();
    test_is_object<void (Class::*)(int, ...) const>();
    test_is_object<void (Class::*)(int, ...) const&>();
    test_is_object<void (Class::*)(int, ...) const&&>();
    test_is_object<void (Class::*)(int, ...) noexcept>();
    test_is_object<void (Class::*)(int, ...)& noexcept>();
    test_is_object<void (Class::*)(int, ...)&& noexcept>();
    test_is_object<void (Class::*)(int, ...) const noexcept>();
    test_is_object<void (Class::*)(int, ...) const& noexcept>();
    test_is_object<void (Class::*)(int, ...) const&& noexcept>();

    test_is_object<int (Class::*)()>();
    test_is_object<int (Class::*)()&>();
    test_is_object<int (Class::*)() &&>();
    test_is_object<int (Class::*)() const>();
    test_is_object<int (Class::*)() const&>();
    test_is_object<int (Class::*)() const&&>();
    test_is_object<int (Class::*)() noexcept>();
    test_is_object<int (Class::*)()& noexcept>();
    test_is_object<int (Class::*)()&& noexcept>();
    test_is_object<int (Class::*)() const noexcept>();
    test_is_object<int (Class::*)() const& noexcept>();
    test_is_object<int (Class::*)() const&& noexcept>();

    test_is_object<int (Class::*)(int)>();
    test_is_object<int (Class::*)(int)&>();
    test_is_object<int (Class::*)(int) &&>();
    test_is_object<int (Class::*)(int) const>();
    test_is_object<int (Class::*)(int) const&>();
    test_is_object<int (Class::*)(int) const&&>();
    test_is_object<int (Class::*)(int) noexcept>();
    test_is_object<int (Class::*)(int)& noexcept>();
    test_is_object<int (Class::*)(int)&& noexcept>();
    test_is_object<int (Class::*)(int) const noexcept>();
    test_is_object<int (Class::*)(int) const& noexcept>();
    test_is_object<int (Class::*)(int) const&& noexcept>();

    test_is_object<int (Class::*)(...)>();
    test_is_object<int (Class::*)(...)&>();
    test_is_object<int (Class::*)(...) &&>();
    test_is_object<int (Class::*)(...) const>();
    test_is_object<int (Class::*)(...) const&>();
    test_is_object<int (Class::*)(...) const&&>();
    test_is_object<int (Class::*)(...) noexcept>();
    test_is_object<int (Class::*)(...)& noexcept>();
    test_is_object<int (Class::*)(...)&& noexcept>();
    test_is_object<int (Class::*)(...) const noexcept>();
    test_is_object<int (Class::*)(...) const& noexcept>();
    test_is_object<int (Class::*)(...) const&& noexcept>();

    test_is_object<int (Class::*)(int, ...)>();
    test_is_object<int (Class::*)(int, ...)&>();
    test_is_object<int (Class::*)(int, ...) &&>();
    test_is_object<int (Class::*)(int, ...) const>();
    test_is_object<int (Class::*)(int, ...) const&>();
    test_is_object<int (Class::*)(int, ...) const&&>();
    test_is_object<int (Class::*)(int, ...) noexcept>();
    test_is_object<int (Class::*)(int, ...)& noexcept>();
    test_is_object<int (Class::*)(int, ...)&& noexcept>();
    test_is_object<int (Class::*)(int, ...) const noexcept>();
    test_is_object<int (Class::*)(int, ...) const& noexcept>();
    test_is_object<int (Class::*)(int, ...) const&& noexcept>();
}
