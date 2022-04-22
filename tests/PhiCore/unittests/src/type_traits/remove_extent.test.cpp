#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_extent.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_remove_extent_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_extent<T>::type, U);
    CHECK_SAME_TYPE(phi::remove_extent_t<T>, U);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::remove_extent<T>::type, U);
}

template <typename T, typename U = T>
void test_remove_extent()
{
    test_remove_extent_impl<T, U>();
    test_remove_extent_impl<const T, const U>();
    test_remove_extent_impl<volatile T, volatile U>();
    test_remove_extent_impl<const volatile T, const volatile U>();
}

TEST_CASE("remove_extent")
{
    test_remove_extent<int[], int>();
    test_remove_extent<int[2], int>();
    test_remove_extent<int[][3], int[3]>();
    test_remove_extent<int[2][3], int[3]>();
    test_remove_extent<int[][3][4], int[3][4]>();
    test_remove_extent<int[2][3][4], int[3][4]>();
    test_remove_extent<float[], float>();
    test_remove_extent<float[2], float>();
    test_remove_extent<float[][3], float[3]>();
    test_remove_extent<float[2][3], float[3]>();
    test_remove_extent<float[][3][4], float[3][4]>();
    test_remove_extent<float[2][3][4], float[3][4]>();
    test_remove_extent<Class[], Class>();
    test_remove_extent<Class[2], Class>();
    test_remove_extent<Class[][3], Class[3]>();
    test_remove_extent<Class[2][3], Class[3]>();
    test_remove_extent<Class[][3][4], Class[3][4]>();
    test_remove_extent<Class[2][3][4], Class[3][4]>();

    test_remove_extent<void>();
    test_remove_extent<phi::nullptr_t>();
    test_remove_extent<bool>();
    test_remove_extent<char>();
    test_remove_extent<signed char>();
    test_remove_extent<unsigned char>();
    test_remove_extent<short>();
    test_remove_extent<unsigned short>();
    test_remove_extent<int>();
    test_remove_extent<unsigned int>();
    test_remove_extent<long>();
    test_remove_extent<unsigned long>();
    test_remove_extent<long long>();
    test_remove_extent<unsigned long long>();
    test_remove_extent<float>();
    test_remove_extent<double>();
    test_remove_extent<long double>();
    test_remove_extent<char8_t>();
    test_remove_extent<char16_t>();
    test_remove_extent<char32_t>();
    test_remove_extent<wchar_t>();

    test_remove_extent<phi::boolean>();
    test_remove_extent<phi::integer<signed char>>();
    test_remove_extent<phi::integer<unsigned char>>();
    test_remove_extent<phi::integer<short>>();
    test_remove_extent<phi::integer<unsigned short>>();
    test_remove_extent<phi::integer<int>>();
    test_remove_extent<phi::integer<unsigned int>>();
    test_remove_extent<phi::integer<long>>();
    test_remove_extent<phi::integer<unsigned long>>();
    test_remove_extent<phi::integer<long long>>();
    test_remove_extent<phi::integer<unsigned long long>>();
    test_remove_extent<phi::floating_point<float>>();
    test_remove_extent<phi::floating_point<double>>();
    test_remove_extent<phi::floating_point<long double>>();

    test_remove_extent<std::vector<int>>();
    test_remove_extent<phi::scope_ptr<int>>();

    test_remove_extent<int&>();
    test_remove_extent<const int&>();
    test_remove_extent<volatile int&>();
    test_remove_extent<const volatile int&>();
    test_remove_extent<int&&>();
    test_remove_extent<const int&&>();
    test_remove_extent<volatile int&&>();
    test_remove_extent<const volatile int&&>();
    test_remove_extent<int*>();
    test_remove_extent<const int*>();
    test_remove_extent<volatile int*>();
    test_remove_extent<const volatile int*>();
    test_remove_extent<int**>();
    test_remove_extent<const int**>();
    test_remove_extent<volatile int**>();
    test_remove_extent<const volatile int**>();
    test_remove_extent<int*&>();
    test_remove_extent<const int*&>();
    test_remove_extent<volatile int*&>();
    test_remove_extent<const volatile int*&>();
    test_remove_extent<int*&&>();
    test_remove_extent<const int*&&>();
    test_remove_extent<volatile int*&&>();
    test_remove_extent<const volatile int*&&>();
    test_remove_extent<void*>();
    test_remove_extent<char[3], char>();
    test_remove_extent<char[], char>();
    test_remove_extent<char* [3], char*>();
    test_remove_extent<char*[], char*>();
    test_remove_extent<int(*)[3]>();
    test_remove_extent<int(*)[]>();
    test_remove_extent<int(&)[3]>();
    test_remove_extent<int(&)[]>();
    test_remove_extent<int(&&)[3]>();
    test_remove_extent<int(&&)[]>();
    test_remove_extent<char[3][2], char[2]>();
    test_remove_extent<char[][2], char[2]>();
    test_remove_extent<char* [3][2], char* [2]>();
    test_remove_extent<char*[][2], char* [2]>();
    test_remove_extent<int(*)[3][2]>();
    test_remove_extent<int(*)[][2]>();
    test_remove_extent<int(&)[3][2]>();
    test_remove_extent<int(&)[][2]>();
    test_remove_extent<int(&&)[3][2]>();
    test_remove_extent<int(&&)[][2]>();
    test_remove_extent<Class>();
    test_remove_extent<Class[], Class>();
    test_remove_extent<Class[2], Class>();
    test_remove_extent<Template<void>>();
    test_remove_extent<Template<int>>();
    test_remove_extent<Template<Class>>();
    test_remove_extent<Template<IncompleteType>>();
    test_remove_extent<VariadicTemplate<>>();
    test_remove_extent<VariadicTemplate<void>>();
    test_remove_extent<VariadicTemplate<int>>();
    test_remove_extent<VariadicTemplate<Class>>();
    test_remove_extent<VariadicTemplate<IncompleteType>>();
    test_remove_extent<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_extent<PublicDerivedFromTemplate<Base>>();
    test_remove_extent<PublicDerivedFromTemplate<Derived>>();
    test_remove_extent<PublicDerivedFromTemplate<Class>>();
    test_remove_extent<PrivateDerivedFromTemplate<Base>>();
    test_remove_extent<PrivateDerivedFromTemplate<Derived>>();
    test_remove_extent<PrivateDerivedFromTemplate<Class>>();
    test_remove_extent<ProtectedDerivedFromTemplate<Base>>();
    test_remove_extent<ProtectedDerivedFromTemplate<Derived>>();
    test_remove_extent<ProtectedDerivedFromTemplate<Class>>();
    test_remove_extent<Union>();
    test_remove_extent<NonEmptyUnion>();
    test_remove_extent<Empty>();
    test_remove_extent<NotEmpty>();
    test_remove_extent<BitZero>();
    test_remove_extent<BitOne>();
    test_remove_extent<Base>();
    test_remove_extent<Derived>();
    test_remove_extent<Abstract>();
    test_remove_extent<PublicAbstract>();
    test_remove_extent<PrivateAbstract>();
    test_remove_extent<ProtectedAbstract>();
    test_remove_extent<AbstractTemplate<int>>();
    test_remove_extent<AbstractTemplate<double>>();
    test_remove_extent<AbstractTemplate<Class>>();
    test_remove_extent<AbstractTemplate<IncompleteType>>();
    test_remove_extent<Final>();
    test_remove_extent<PublicDestructor>();
    test_remove_extent<ProtectedDestructor>();
    test_remove_extent<PrivateDestructor>();
    test_remove_extent<VirtualPublicDestructor>();
    test_remove_extent<VirtualProtectedDestructor>();
    test_remove_extent<VirtualPrivateDestructor>();
    test_remove_extent<PurePublicDestructor>();
    test_remove_extent<PureProtectedDestructor>();
    test_remove_extent<PurePrivateDestructor>();
    test_remove_extent<DeletedPublicDestructor>();
    test_remove_extent<DeletedProtectedDestructor>();
    test_remove_extent<DeletedPrivateDestructor>();
    test_remove_extent<DeletedVirtualPublicDestructor>();
    test_remove_extent<DeletedVirtualProtectedDestructor>();
    test_remove_extent<DeletedVirtualPrivateDestructor>();
    test_remove_extent<Enum>();
    test_remove_extent<EnumSigned>();
    test_remove_extent<EnumUnsigned>();
    test_remove_extent<EnumClass>();
    test_remove_extent<EnumStruct>();
    test_remove_extent<Function>();
    test_remove_extent<FunctionPtr>();
    test_remove_extent<MemberObjectPtr>();
    test_remove_extent<MemberFunctionPtr>();
    test_remove_extent<IncompleteType>();
    test_remove_extent<IncompleteTemplate<void>>();
    test_remove_extent<IncompleteTemplate<int>>();
    test_remove_extent<IncompleteTemplate<Class>>();
    test_remove_extent<IncompleteTemplate<IncompleteType>>();
    test_remove_extent<IncompleteVariadicTemplate<>>();
    test_remove_extent<IncompleteVariadicTemplate<void>>();
    test_remove_extent<IncompleteVariadicTemplate<int>>();
    test_remove_extent<IncompleteVariadicTemplate<Class>>();
    test_remove_extent<IncompleteVariadicTemplate<IncompleteType>>();
    test_remove_extent<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_extent<int Class::*>();
    test_remove_extent<float Class::*>();
    test_remove_extent<void * Class::*>();
    test_remove_extent<int * Class::*>();
    test_remove_extent<int Class::*&>();
    test_remove_extent<float Class::*&>();
    test_remove_extent<void * Class::*&>();
    test_remove_extent<int * Class::*&>();
    test_remove_extent<int Class::*&&>();
    test_remove_extent<float Class::*&&>();
    test_remove_extent<void * Class::*&&>();
    test_remove_extent<int * Class::*&&>();
    test_remove_extent<int Class::*const>();
    test_remove_extent<float Class::*const>();
    test_remove_extent<void * Class::*const>();
    test_remove_extent<int Class::*const&>();
    test_remove_extent<float Class::*const&>();
    test_remove_extent<void * Class::*const&>();
    test_remove_extent<int Class::*const&&>();
    test_remove_extent<float Class::*const&&>();
    test_remove_extent<void * Class::*const&&>();
    test_remove_extent<int Class::*volatile>();
    test_remove_extent<float Class::*volatile>();
    test_remove_extent<void * Class::*volatile>();
    test_remove_extent<int Class::*volatile&>();
    test_remove_extent<float Class::*volatile&>();
    test_remove_extent<void * Class::*volatile&>();
    test_remove_extent<int Class::*volatile&&>();
    test_remove_extent<float Class::*volatile&&>();
    test_remove_extent<void * Class::*volatile&&>();
    test_remove_extent<int Class::*const volatile>();
    test_remove_extent<float Class::*const volatile>();
    test_remove_extent<void * Class::*const volatile>();
    test_remove_extent<int Class::*const volatile&>();
    test_remove_extent<float Class::*const volatile&>();
    test_remove_extent<void * Class::*const volatile&>();
    test_remove_extent<int Class::*const volatile&&>();
    test_remove_extent<float Class::*const volatile&&>();
    test_remove_extent<void * Class::*const volatile&&>();
    test_remove_extent<NonCopyable>();
    test_remove_extent<NonMoveable>();
    test_remove_extent<NonConstructible>();
    test_remove_extent<Tracked>();
    test_remove_extent<TrapConstructible>();
    test_remove_extent<TrapImplicitConversion>();
    test_remove_extent<TrapComma>();
    test_remove_extent<TrapCall>();
    test_remove_extent<TrapSelfAssign>();
    test_remove_extent<TrapDeref>();
    test_remove_extent<TrapArraySubscript>();

    test_remove_extent<void()>();
    test_remove_extent<void()&>();
    test_remove_extent<void() &&>();
    test_remove_extent<void() const>();
    test_remove_extent<void() const&>();
    test_remove_extent<void() const&&>();
    test_remove_extent<void() volatile>();
    test_remove_extent<void() volatile&>();
    test_remove_extent<void() volatile&&>();
    test_remove_extent<void() const volatile>();
    test_remove_extent<void() const volatile&>();
    test_remove_extent<void() const volatile&&>();
    test_remove_extent<void() noexcept>();
    test_remove_extent<void()& noexcept>();
    test_remove_extent<void()&& noexcept>();
    test_remove_extent<void() const noexcept>();
    test_remove_extent<void() const& noexcept>();
    test_remove_extent<void() const&& noexcept>();
    test_remove_extent<void() volatile noexcept>();
    test_remove_extent<void() volatile& noexcept>();
    test_remove_extent<void() volatile&& noexcept>();
    test_remove_extent<void() const volatile noexcept>();
    test_remove_extent<void() const volatile& noexcept>();
    test_remove_extent<void() const volatile&& noexcept>();

    test_remove_extent<void(int)>();
    test_remove_extent<void(int)&>();
    test_remove_extent<void(int) &&>();
    test_remove_extent<void(int) const>();
    test_remove_extent<void(int) const&>();
    test_remove_extent<void(int) const&&>();
    test_remove_extent<void(int) volatile>();
    test_remove_extent<void(int) volatile&>();
    test_remove_extent<void(int) volatile&&>();
    test_remove_extent<void(int) const volatile>();
    test_remove_extent<void(int) const volatile&>();
    test_remove_extent<void(int) const volatile&&>();
    test_remove_extent<void(int) noexcept>();
    test_remove_extent<void(int)& noexcept>();
    test_remove_extent<void(int)&& noexcept>();
    test_remove_extent<void(int) const noexcept>();
    test_remove_extent<void(int) const& noexcept>();
    test_remove_extent<void(int) const&& noexcept>();
    test_remove_extent<void(int) volatile noexcept>();
    test_remove_extent<void(int) volatile& noexcept>();
    test_remove_extent<void(int) volatile&& noexcept>();
    test_remove_extent<void(int) const volatile noexcept>();
    test_remove_extent<void(int) const volatile& noexcept>();
    test_remove_extent<void(int) const volatile&& noexcept>();

    test_remove_extent<void(...)>();
    test_remove_extent<void(...)&>();
    test_remove_extent<void(...) &&>();
    test_remove_extent<void(...) const>();
    test_remove_extent<void(...) const&>();
    test_remove_extent<void(...) const&&>();
    test_remove_extent<void(...) volatile>();
    test_remove_extent<void(...) volatile&>();
    test_remove_extent<void(...) volatile&&>();
    test_remove_extent<void(...) const volatile>();
    test_remove_extent<void(...) const volatile&>();
    test_remove_extent<void(...) const volatile&&>();
    test_remove_extent<void(...) noexcept>();
    test_remove_extent<void(...)& noexcept>();
    test_remove_extent<void(...)&& noexcept>();
    test_remove_extent<void(...) const noexcept>();
    test_remove_extent<void(...) const& noexcept>();
    test_remove_extent<void(...) const&& noexcept>();
    test_remove_extent<void(...) volatile noexcept>();
    test_remove_extent<void(...) volatile& noexcept>();
    test_remove_extent<void(...) volatile&& noexcept>();
    test_remove_extent<void(...) const volatile noexcept>();
    test_remove_extent<void(...) const volatile& noexcept>();
    test_remove_extent<void(...) const volatile&& noexcept>();

    test_remove_extent<void(int, ...)>();
    test_remove_extent<void(int, ...)&>();
    test_remove_extent<void(int, ...) &&>();
    test_remove_extent<void(int, ...) const>();
    test_remove_extent<void(int, ...) const&>();
    test_remove_extent<void(int, ...) const&&>();
    test_remove_extent<void(int, ...) volatile>();
    test_remove_extent<void(int, ...) volatile&>();
    test_remove_extent<void(int, ...) volatile&&>();
    test_remove_extent<void(int, ...) const volatile>();
    test_remove_extent<void(int, ...) const volatile&>();
    test_remove_extent<void(int, ...) const volatile&&>();
    test_remove_extent<void(int, ...) noexcept>();
    test_remove_extent<void(int, ...)& noexcept>();
    test_remove_extent<void(int, ...)&& noexcept>();
    test_remove_extent<void(int, ...) const noexcept>();
    test_remove_extent<void(int, ...) const& noexcept>();
    test_remove_extent<void(int, ...) const&& noexcept>();
    test_remove_extent<void(int, ...) volatile noexcept>();
    test_remove_extent<void(int, ...) volatile& noexcept>();
    test_remove_extent<void(int, ...) volatile&& noexcept>();
    test_remove_extent<void(int, ...) const volatile noexcept>();
    test_remove_extent<void(int, ...) const volatile& noexcept>();
    test_remove_extent<void(int, ...) const volatile&& noexcept>();

    test_remove_extent<int()>();
    test_remove_extent<int()&>();
    test_remove_extent<int() &&>();
    test_remove_extent<int() const>();
    test_remove_extent<int() const&>();
    test_remove_extent<int() const&&>();
    test_remove_extent<int() volatile>();
    test_remove_extent<int() volatile&>();
    test_remove_extent<int() volatile&&>();
    test_remove_extent<int() const volatile>();
    test_remove_extent<int() const volatile&>();
    test_remove_extent<int() const volatile&&>();
    test_remove_extent<int() noexcept>();
    test_remove_extent<int()& noexcept>();
    test_remove_extent<int()&& noexcept>();
    test_remove_extent<int() const noexcept>();
    test_remove_extent<int() const& noexcept>();
    test_remove_extent<int() const&& noexcept>();
    test_remove_extent<int() volatile noexcept>();
    test_remove_extent<int() volatile& noexcept>();
    test_remove_extent<int() volatile&& noexcept>();
    test_remove_extent<int() const volatile noexcept>();
    test_remove_extent<int() const volatile& noexcept>();
    test_remove_extent<int() const volatile&& noexcept>();

    test_remove_extent<int(int)>();
    test_remove_extent<int(int)&>();
    test_remove_extent<int(int) &&>();
    test_remove_extent<int(int) const>();
    test_remove_extent<int(int) const&>();
    test_remove_extent<int(int) const&&>();
    test_remove_extent<int(int) volatile>();
    test_remove_extent<int(int) volatile&>();
    test_remove_extent<int(int) volatile&&>();
    test_remove_extent<int(int) const volatile>();
    test_remove_extent<int(int) const volatile&>();
    test_remove_extent<int(int) const volatile&&>();
    test_remove_extent<int(int) noexcept>();
    test_remove_extent<int(int)& noexcept>();
    test_remove_extent<int(int)&& noexcept>();
    test_remove_extent<int(int) const noexcept>();
    test_remove_extent<int(int) const& noexcept>();
    test_remove_extent<int(int) const&& noexcept>();
    test_remove_extent<int(int) volatile noexcept>();
    test_remove_extent<int(int) volatile& noexcept>();
    test_remove_extent<int(int) volatile&& noexcept>();
    test_remove_extent<int(int) const volatile noexcept>();
    test_remove_extent<int(int) const volatile& noexcept>();
    test_remove_extent<int(int) const volatile&& noexcept>();

    test_remove_extent<int(...)>();
    test_remove_extent<int(...)&>();
    test_remove_extent<int(...) &&>();
    test_remove_extent<int(...) const>();
    test_remove_extent<int(...) const&>();
    test_remove_extent<int(...) const&&>();
    test_remove_extent<int(...) volatile>();
    test_remove_extent<int(...) volatile&>();
    test_remove_extent<int(...) volatile&&>();
    test_remove_extent<int(...) const volatile>();
    test_remove_extent<int(...) const volatile&>();
    test_remove_extent<int(...) const volatile&&>();
    test_remove_extent<int(...) noexcept>();
    test_remove_extent<int(...)& noexcept>();
    test_remove_extent<int(...)&& noexcept>();
    test_remove_extent<int(...) const noexcept>();
    test_remove_extent<int(...) const& noexcept>();
    test_remove_extent<int(...) const&& noexcept>();
    test_remove_extent<int(...) volatile noexcept>();
    test_remove_extent<int(...) volatile& noexcept>();
    test_remove_extent<int(...) volatile&& noexcept>();
    test_remove_extent<int(...) const volatile noexcept>();
    test_remove_extent<int(...) const volatile& noexcept>();
    test_remove_extent<int(...) const volatile&& noexcept>();

    test_remove_extent<int(int, ...)>();
    test_remove_extent<int(int, ...)&>();
    test_remove_extent<int(int, ...) &&>();
    test_remove_extent<int(int, ...) const>();
    test_remove_extent<int(int, ...) const&>();
    test_remove_extent<int(int, ...) const&&>();
    test_remove_extent<int(int, ...) volatile>();
    test_remove_extent<int(int, ...) volatile&>();
    test_remove_extent<int(int, ...) volatile&&>();
    test_remove_extent<int(int, ...) const volatile>();
    test_remove_extent<int(int, ...) const volatile&>();
    test_remove_extent<int(int, ...) const volatile&&>();
    test_remove_extent<int(int, ...) noexcept>();
    test_remove_extent<int(int, ...)& noexcept>();
    test_remove_extent<int(int, ...)&& noexcept>();
    test_remove_extent<int(int, ...) const noexcept>();
    test_remove_extent<int(int, ...) const& noexcept>();
    test_remove_extent<int(int, ...) const&& noexcept>();
    test_remove_extent<int(int, ...) volatile noexcept>();
    test_remove_extent<int(int, ...) volatile& noexcept>();
    test_remove_extent<int(int, ...) volatile&& noexcept>();
    test_remove_extent<int(int, ...) const volatile noexcept>();
    test_remove_extent<int(int, ...) const volatile& noexcept>();
    test_remove_extent<int(int, ...) const volatile&& noexcept>();

    test_remove_extent<void (*)()>();
    test_remove_extent<void (*)() noexcept>();

    test_remove_extent<void (*)(int)>();
    test_remove_extent<void (*)(int) noexcept>();

    test_remove_extent<void (*)(...)>();
    test_remove_extent<void (*)(...) noexcept>();

    test_remove_extent<void (*)(int, ...)>();
    test_remove_extent<void (*)(int, ...) noexcept>();

    test_remove_extent<int (*)()>();
    test_remove_extent<int (*)() noexcept>();

    test_remove_extent<int (*)(int)>();
    test_remove_extent<int (*)(int) noexcept>();

    test_remove_extent<int (*)(...)>();
    test_remove_extent<int (*)(...) noexcept>();

    test_remove_extent<int (*)(int, ...)>();
    test_remove_extent<int (*)(int, ...) noexcept>();

    test_remove_extent<void (&)()>();
    test_remove_extent<void (&)() noexcept>();

    test_remove_extent<void (&)(int)>();
    test_remove_extent<void (&)(int) noexcept>();

    test_remove_extent<void (&)(...)>();
    test_remove_extent<void (&)(...) noexcept>();

    test_remove_extent<void (&)(int, ...)>();
    test_remove_extent<void (&)(int, ...) noexcept>();

    test_remove_extent<int (&)()>();
    test_remove_extent<int (&)() noexcept>();

    test_remove_extent<int (&)(int)>();
    test_remove_extent<int (&)(int) noexcept>();

    test_remove_extent<int (&)(...)>();
    test_remove_extent<int (&)(...) noexcept>();

    test_remove_extent<int (&)(int, ...)>();
    test_remove_extent<int (&)(int, ...) noexcept>();

    test_remove_extent<void(&&)()>();
    test_remove_extent<void(&&)() noexcept>();

    test_remove_extent<void(&&)(int)>();
    test_remove_extent<void(&&)(int) noexcept>();

    test_remove_extent<void(&&)(...)>();
    test_remove_extent<void(&&)(...) noexcept>();

    test_remove_extent<void(&&)(int, ...)>();
    test_remove_extent<void(&&)(int, ...) noexcept>();

    test_remove_extent<int(&&)()>();
    test_remove_extent<int(&&)() noexcept>();

    test_remove_extent<int(&&)(int)>();
    test_remove_extent<int(&&)(int) noexcept>();

    test_remove_extent<int(&&)(...)>();
    test_remove_extent<int(&&)(...) noexcept>();

    test_remove_extent<int(&&)(int, ...)>();
    test_remove_extent<int(&&)(int, ...) noexcept>();

    test_remove_extent<void (Class::*)()>();
    test_remove_extent<void (Class::*)()&>();
    test_remove_extent<void (Class::*)() &&>();
    test_remove_extent<void (Class::*)() const>();
    test_remove_extent<void (Class::*)() const&>();
    test_remove_extent<void (Class::*)() const&&>();
    test_remove_extent<void (Class::*)() noexcept>();
    test_remove_extent<void (Class::*)()& noexcept>();
    test_remove_extent<void (Class::*)()&& noexcept>();
    test_remove_extent<void (Class::*)() const noexcept>();
    test_remove_extent<void (Class::*)() const& noexcept>();
    test_remove_extent<void (Class::*)() const&& noexcept>();

    test_remove_extent<void (Class::*)(int)>();
    test_remove_extent<void (Class::*)(int)&>();
    test_remove_extent<void (Class::*)(int) &&>();
    test_remove_extent<void (Class::*)(int) const>();
    test_remove_extent<void (Class::*)(int) const&>();
    test_remove_extent<void (Class::*)(int) const&&>();
    test_remove_extent<void (Class::*)(int) noexcept>();
    test_remove_extent<void (Class::*)(int)& noexcept>();
    test_remove_extent<void (Class::*)(int)&& noexcept>();
    test_remove_extent<void (Class::*)(int) const noexcept>();
    test_remove_extent<void (Class::*)(int) const& noexcept>();
    test_remove_extent<void (Class::*)(int) const&& noexcept>();

    test_remove_extent<void (Class::*)(...)>();
    test_remove_extent<void (Class::*)(...)&>();
    test_remove_extent<void (Class::*)(...) &&>();
    test_remove_extent<void (Class::*)(...) const>();
    test_remove_extent<void (Class::*)(...) const&>();
    test_remove_extent<void (Class::*)(...) const&&>();
    test_remove_extent<void (Class::*)(...) noexcept>();
    test_remove_extent<void (Class::*)(...)& noexcept>();
    test_remove_extent<void (Class::*)(...)&& noexcept>();
    test_remove_extent<void (Class::*)(...) const noexcept>();
    test_remove_extent<void (Class::*)(...) const& noexcept>();
    test_remove_extent<void (Class::*)(...) const&& noexcept>();

    test_remove_extent<void (Class::*)(int, ...)>();
    test_remove_extent<void (Class::*)(int, ...)&>();
    test_remove_extent<void (Class::*)(int, ...) &&>();
    test_remove_extent<void (Class::*)(int, ...) const>();
    test_remove_extent<void (Class::*)(int, ...) const&>();
    test_remove_extent<void (Class::*)(int, ...) const&&>();
    test_remove_extent<void (Class::*)(int, ...) noexcept>();
    test_remove_extent<void (Class::*)(int, ...)& noexcept>();
    test_remove_extent<void (Class::*)(int, ...)&& noexcept>();
    test_remove_extent<void (Class::*)(int, ...) const noexcept>();
    test_remove_extent<void (Class::*)(int, ...) const& noexcept>();
    test_remove_extent<void (Class::*)(int, ...) const&& noexcept>();

    test_remove_extent<int (Class::*)()>();
    test_remove_extent<int (Class::*)()&>();
    test_remove_extent<int (Class::*)() &&>();
    test_remove_extent<int (Class::*)() const>();
    test_remove_extent<int (Class::*)() const&>();
    test_remove_extent<int (Class::*)() const&&>();
    test_remove_extent<int (Class::*)() noexcept>();
    test_remove_extent<int (Class::*)()& noexcept>();
    test_remove_extent<int (Class::*)()&& noexcept>();
    test_remove_extent<int (Class::*)() const noexcept>();
    test_remove_extent<int (Class::*)() const& noexcept>();
    test_remove_extent<int (Class::*)() const&& noexcept>();

    test_remove_extent<int (Class::*)(int)>();
    test_remove_extent<int (Class::*)(int)&>();
    test_remove_extent<int (Class::*)(int) &&>();
    test_remove_extent<int (Class::*)(int) const>();
    test_remove_extent<int (Class::*)(int) const&>();
    test_remove_extent<int (Class::*)(int) const&&>();
    test_remove_extent<int (Class::*)(int) noexcept>();
    test_remove_extent<int (Class::*)(int)& noexcept>();
    test_remove_extent<int (Class::*)(int)&& noexcept>();
    test_remove_extent<int (Class::*)(int) const noexcept>();
    test_remove_extent<int (Class::*)(int) const& noexcept>();
    test_remove_extent<int (Class::*)(int) const&& noexcept>();

    test_remove_extent<int (Class::*)(...)>();
    test_remove_extent<int (Class::*)(...)&>();
    test_remove_extent<int (Class::*)(...) &&>();
    test_remove_extent<int (Class::*)(...) const>();
    test_remove_extent<int (Class::*)(...) const&>();
    test_remove_extent<int (Class::*)(...) const&&>();
    test_remove_extent<int (Class::*)(...) noexcept>();
    test_remove_extent<int (Class::*)(...)& noexcept>();
    test_remove_extent<int (Class::*)(...)&& noexcept>();
    test_remove_extent<int (Class::*)(...) const noexcept>();
    test_remove_extent<int (Class::*)(...) const& noexcept>();
    test_remove_extent<int (Class::*)(...) const&& noexcept>();

    test_remove_extent<int (Class::*)(int, ...)>();
    test_remove_extent<int (Class::*)(int, ...)&>();
    test_remove_extent<int (Class::*)(int, ...) &&>();
    test_remove_extent<int (Class::*)(int, ...) const>();
    test_remove_extent<int (Class::*)(int, ...) const&>();
    test_remove_extent<int (Class::*)(int, ...) const&&>();
    test_remove_extent<int (Class::*)(int, ...) noexcept>();
    test_remove_extent<int (Class::*)(int, ...)& noexcept>();
    test_remove_extent<int (Class::*)(int, ...)&& noexcept>();
    test_remove_extent<int (Class::*)(int, ...) const noexcept>();
    test_remove_extent<int (Class::*)(int, ...) const& noexcept>();
    test_remove_extent<int (Class::*)(int, ...) const&& noexcept>();
}
