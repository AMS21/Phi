#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_pointer.hpp>
#include <vector>

template <typename T, typename U>
void test_remove_pointer_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_pointer<T>::type, U);
    CHECK_SAME_TYPE(phi::remove_pointer_t<T>, U);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::remove_pointer<T>::type, U);
}

template <typename T, typename U = T>
void test_remove_pointer()
{
    test_remove_pointer_impl<T, U>();
    test_remove_pointer_impl<const T, const U>();
    test_remove_pointer_impl<volatile T, volatile U>();
    test_remove_pointer_impl<const volatile T, const volatile U>();
}

template <typename T, typename U>
void test_remove_pointer_ptr()
{
    CHECK_SAME_TYPE(typename phi::remove_pointer<T>::type, U);
    CHECK_SAME_TYPE(phi::remove_pointer_t<T>, U);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::remove_pointer<T>::type, U);
}

TEST_CASE("remove_pointer")
{
    test_remove_pointer_ptr<int* const, int>();
    test_remove_pointer_ptr<int* volatile, int>();
    test_remove_pointer_ptr<int* const volatile, int>();
    test_remove_pointer_ptr<int** const, int*>();
    test_remove_pointer_ptr<int** volatile, int*>();
    test_remove_pointer_ptr<int** const volatile, int*>();
    test_remove_pointer_ptr<int* const*, int* const>();
    test_remove_pointer_ptr<int* volatile*, int* volatile>();
    test_remove_pointer_ptr<int* const volatile*, int* const volatile>();

    test_remove_pointer<void>();
    test_remove_pointer<phi::nullptr_t>();
    test_remove_pointer<bool>();
    test_remove_pointer<char>();
    test_remove_pointer<signed char>();
    test_remove_pointer<unsigned char>();
    test_remove_pointer<short>();
    test_remove_pointer<unsigned short>();
    test_remove_pointer<int>();
    test_remove_pointer<unsigned int>();
    test_remove_pointer<long>();
    test_remove_pointer<unsigned long>();
    test_remove_pointer<long long>();
    test_remove_pointer<unsigned long long>();
    test_remove_pointer<float>();
    test_remove_pointer<double>();
    test_remove_pointer<long double>();
    test_remove_pointer<char8_t>();
    test_remove_pointer<char16_t>();
    test_remove_pointer<char32_t>();
    test_remove_pointer<wchar_t>();

    test_remove_pointer<phi::boolean>();
    test_remove_pointer<phi::integer<signed char>>();
    test_remove_pointer<phi::integer<unsigned char>>();
    test_remove_pointer<phi::integer<short>>();
    test_remove_pointer<phi::integer<unsigned short>>();
    test_remove_pointer<phi::integer<int>>();
    test_remove_pointer<phi::integer<unsigned int>>();
    test_remove_pointer<phi::integer<long>>();
    test_remove_pointer<phi::integer<unsigned long>>();
    test_remove_pointer<phi::integer<long long>>();
    test_remove_pointer<phi::integer<unsigned long long>>();
    test_remove_pointer<phi::floating_point<float>>();
    test_remove_pointer<phi::floating_point<double>>();
    test_remove_pointer<phi::floating_point<long double>>();

    test_remove_pointer<std::vector<int>>();
    test_remove_pointer<phi::scope_ptr<int>>();

    test_remove_pointer<int&>();
    test_remove_pointer<const int&>();
    test_remove_pointer<volatile int&>();
    test_remove_pointer<const volatile int&>();
    test_remove_pointer<int&&>();
    test_remove_pointer<const int&&>();
    test_remove_pointer<volatile int&&>();
    test_remove_pointer<const volatile int&&>();
    test_remove_pointer_ptr<int*, int>();
    test_remove_pointer_ptr<const int*, const int>();
    test_remove_pointer_ptr<volatile int*, volatile int>();
    test_remove_pointer_ptr<const volatile int*, const volatile int>();
    test_remove_pointer_ptr<int**, int*>();
    test_remove_pointer_ptr<const int**, const int*>();
    test_remove_pointer_ptr<volatile int**, volatile int*>();
    test_remove_pointer_ptr<const volatile int**, const volatile int*>();
    test_remove_pointer<int*&>();
    test_remove_pointer<const int*&>();
    test_remove_pointer<volatile int*&>();
    test_remove_pointer<const volatile int*&>();
    test_remove_pointer<int*&&>();
    test_remove_pointer<const int*&&>();
    test_remove_pointer<volatile int*&&>();
    test_remove_pointer<const volatile int*&&>();
    test_remove_pointer_ptr<void*, void>();
    test_remove_pointer<char[3]>();
    test_remove_pointer<char[]>();
    test_remove_pointer<char* [3]>();
    test_remove_pointer<char*[]>();
    test_remove_pointer_ptr<int(*)[3], int[3]>();
    test_remove_pointer_ptr<int(*)[], int[]>();
    test_remove_pointer<int(&)[3]>();
    test_remove_pointer<int(&)[]>();
    test_remove_pointer<int(&&)[3]>();
    test_remove_pointer<int(&&)[]>();
    test_remove_pointer<char[3][2]>();
    test_remove_pointer<char[][2]>();
    test_remove_pointer<char* [3][2]>();
    test_remove_pointer<char*[][2]>();
    test_remove_pointer_ptr<int(*)[3][2], int[3][2]>();
    test_remove_pointer_ptr<int(*)[][2], int[][2]>();
    test_remove_pointer<int(&)[3][2]>();
    test_remove_pointer<int(&)[][2]>();
    test_remove_pointer<int(&&)[3][2]>();
    test_remove_pointer<int(&&)[][2]>();
    test_remove_pointer<Class>();
    test_remove_pointer<Class[]>();
    test_remove_pointer<Class[2]>();
    test_remove_pointer<Template<void>>();
    test_remove_pointer<Template<int>>();
    test_remove_pointer<Template<Class>>();
    test_remove_pointer<Template<IncompleteType>>();
    test_remove_pointer<VariadicTemplate<>>();
    test_remove_pointer<VariadicTemplate<void>>();
    test_remove_pointer<VariadicTemplate<int>>();
    test_remove_pointer<VariadicTemplate<Class>>();
    test_remove_pointer<VariadicTemplate<IncompleteType>>();
    test_remove_pointer<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_pointer<PublicDerivedFromTemplate<Base>>();
    test_remove_pointer<PublicDerivedFromTemplate<Derived>>();
    test_remove_pointer<PublicDerivedFromTemplate<Class>>();
    test_remove_pointer<PrivateDerivedFromTemplate<Base>>();
    test_remove_pointer<PrivateDerivedFromTemplate<Derived>>();
    test_remove_pointer<PrivateDerivedFromTemplate<Class>>();
    test_remove_pointer<ProtectedDerivedFromTemplate<Base>>();
    test_remove_pointer<ProtectedDerivedFromTemplate<Derived>>();
    test_remove_pointer<ProtectedDerivedFromTemplate<Class>>();
    test_remove_pointer<Union>();
    test_remove_pointer<NonEmptyUnion>();
    test_remove_pointer<Empty>();
    test_remove_pointer<NotEmpty>();
    test_remove_pointer<BitZero>();
    test_remove_pointer<BitOne>();
    test_remove_pointer<Base>();
    test_remove_pointer<Derived>();
    test_remove_pointer<Abstract>();
    test_remove_pointer<PublicAbstract>();
    test_remove_pointer<PrivateAbstract>();
    test_remove_pointer<ProtectedAbstract>();
    test_remove_pointer<AbstractTemplate<int>>();
    test_remove_pointer<AbstractTemplate<double>>();
    test_remove_pointer<AbstractTemplate<Class>>();
    test_remove_pointer<AbstractTemplate<IncompleteType>>();
    test_remove_pointer<Final>();
    test_remove_pointer<PublicDestructor>();
    test_remove_pointer<ProtectedDestructor>();
    test_remove_pointer<PrivateDestructor>();
    test_remove_pointer<VirtualPublicDestructor>();
    test_remove_pointer<VirtualProtectedDestructor>();
    test_remove_pointer<VirtualPrivateDestructor>();
    test_remove_pointer<PurePublicDestructor>();
    test_remove_pointer<PureProtectedDestructor>();
    test_remove_pointer<PurePrivateDestructor>();
    test_remove_pointer<DeletedPublicDestructor>();
    test_remove_pointer<DeletedProtectedDestructor>();
    test_remove_pointer<DeletedPrivateDestructor>();
    test_remove_pointer<DeletedVirtualPublicDestructor>();
    test_remove_pointer<DeletedVirtualProtectedDestructor>();
    test_remove_pointer<DeletedVirtualPrivateDestructor>();
    test_remove_pointer<Enum>();
    test_remove_pointer<EnumSigned>();
    test_remove_pointer<EnumUnsigned>();
    test_remove_pointer<EnumClass>();
    test_remove_pointer<EnumStruct>();
    test_remove_pointer<Function>();
    test_remove_pointer_ptr<FunctionPtr, Function>();
    test_remove_pointer<MemberObjectPtr>();
    test_remove_pointer<MemberFunctionPtr>();
    test_remove_pointer<IncompleteType>();
    test_remove_pointer<IncompleteTemplate<void>>();
    test_remove_pointer<IncompleteTemplate<int>>();
    test_remove_pointer<IncompleteTemplate<Class>>();
    test_remove_pointer<IncompleteTemplate<IncompleteType>>();
    test_remove_pointer<IncompleteVariadicTemplate<>>();
    test_remove_pointer<IncompleteVariadicTemplate<void>>();
    test_remove_pointer<IncompleteVariadicTemplate<int>>();
    test_remove_pointer<IncompleteVariadicTemplate<Class>>();
    test_remove_pointer<IncompleteVariadicTemplate<IncompleteType>>();
    test_remove_pointer<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_pointer<int Class::*>();
    test_remove_pointer<float Class::*>();
    test_remove_pointer<void * Class::*>();
    test_remove_pointer<int * Class::*>();
    test_remove_pointer<int Class::*&>();
    test_remove_pointer<float Class::*&>();
    test_remove_pointer<void * Class::*&>();
    test_remove_pointer<int * Class::*&>();
    test_remove_pointer<int Class::*&&>();
    test_remove_pointer<float Class::*&&>();
    test_remove_pointer<void * Class::*&&>();
    test_remove_pointer<int * Class::*&&>();
    test_remove_pointer<int Class::*const>();
    test_remove_pointer<float Class::*const>();
    test_remove_pointer<void * Class::*const>();
    test_remove_pointer<int Class::*const&>();
    test_remove_pointer<float Class::*const&>();
    test_remove_pointer<void * Class::*const&>();
    test_remove_pointer<int Class::*const&&>();
    test_remove_pointer<float Class::*const&&>();
    test_remove_pointer<void * Class::*const&&>();
    test_remove_pointer<int Class::*volatile>();
    test_remove_pointer<float Class::*volatile>();
    test_remove_pointer<void * Class::*volatile>();
    test_remove_pointer<int Class::*volatile&>();
    test_remove_pointer<float Class::*volatile&>();
    test_remove_pointer<void * Class::*volatile&>();
    test_remove_pointer<int Class::*volatile&&>();
    test_remove_pointer<float Class::*volatile&&>();
    test_remove_pointer<void * Class::*volatile&&>();
    test_remove_pointer<int Class::*const volatile>();
    test_remove_pointer<float Class::*const volatile>();
    test_remove_pointer<void * Class::*const volatile>();
    test_remove_pointer<int Class::*const volatile&>();
    test_remove_pointer<float Class::*const volatile&>();
    test_remove_pointer<void * Class::*const volatile&>();
    test_remove_pointer<int Class::*const volatile&&>();
    test_remove_pointer<float Class::*const volatile&&>();
    test_remove_pointer<void * Class::*const volatile&&>();
    test_remove_pointer<NonCopyable>();
    test_remove_pointer<NonMoveable>();
    test_remove_pointer<NonConstructible>();
    test_remove_pointer<Tracked>();
    test_remove_pointer<TrapConstructible>();
    test_remove_pointer<TrapImplicitConversion>();
    test_remove_pointer<TrapComma>();
    test_remove_pointer<TrapCall>();
    test_remove_pointer<TrapSelfAssign>();
    test_remove_pointer<TrapDeref>();
    test_remove_pointer<TrapArraySubscript>();

    test_remove_pointer<void()>();
    test_remove_pointer<void()&>();
    test_remove_pointer<void() &&>();
    test_remove_pointer<void() const>();
    test_remove_pointer<void() const&>();
    test_remove_pointer<void() const&&>();
    test_remove_pointer<void() volatile>();
    test_remove_pointer<void() volatile&>();
    test_remove_pointer<void() volatile&&>();
    test_remove_pointer<void() const volatile>();
    test_remove_pointer<void() const volatile&>();
    test_remove_pointer<void() const volatile&&>();
    test_remove_pointer<void() noexcept>();
    test_remove_pointer<void()& noexcept>();
    test_remove_pointer<void()&& noexcept>();
    test_remove_pointer<void() const noexcept>();
    test_remove_pointer<void() const& noexcept>();
    test_remove_pointer<void() const&& noexcept>();
    test_remove_pointer<void() volatile noexcept>();
    test_remove_pointer<void() volatile& noexcept>();
    test_remove_pointer<void() volatile&& noexcept>();
    test_remove_pointer<void() const volatile noexcept>();
    test_remove_pointer<void() const volatile& noexcept>();
    test_remove_pointer<void() const volatile&& noexcept>();

    test_remove_pointer<void(int)>();
    test_remove_pointer<void(int)&>();
    test_remove_pointer<void(int) &&>();
    test_remove_pointer<void(int) const>();
    test_remove_pointer<void(int) const&>();
    test_remove_pointer<void(int) const&&>();
    test_remove_pointer<void(int) volatile>();
    test_remove_pointer<void(int) volatile&>();
    test_remove_pointer<void(int) volatile&&>();
    test_remove_pointer<void(int) const volatile>();
    test_remove_pointer<void(int) const volatile&>();
    test_remove_pointer<void(int) const volatile&&>();
    test_remove_pointer<void(int) noexcept>();
    test_remove_pointer<void(int)& noexcept>();
    test_remove_pointer<void(int)&& noexcept>();
    test_remove_pointer<void(int) const noexcept>();
    test_remove_pointer<void(int) const& noexcept>();
    test_remove_pointer<void(int) const&& noexcept>();
    test_remove_pointer<void(int) volatile noexcept>();
    test_remove_pointer<void(int) volatile& noexcept>();
    test_remove_pointer<void(int) volatile&& noexcept>();
    test_remove_pointer<void(int) const volatile noexcept>();
    test_remove_pointer<void(int) const volatile& noexcept>();
    test_remove_pointer<void(int) const volatile&& noexcept>();

    test_remove_pointer<void(...)>();
    test_remove_pointer<void(...)&>();
    test_remove_pointer<void(...) &&>();
    test_remove_pointer<void(...) const>();
    test_remove_pointer<void(...) const&>();
    test_remove_pointer<void(...) const&&>();
    test_remove_pointer<void(...) volatile>();
    test_remove_pointer<void(...) volatile&>();
    test_remove_pointer<void(...) volatile&&>();
    test_remove_pointer<void(...) const volatile>();
    test_remove_pointer<void(...) const volatile&>();
    test_remove_pointer<void(...) const volatile&&>();
    test_remove_pointer<void(...) noexcept>();
    test_remove_pointer<void(...)& noexcept>();
    test_remove_pointer<void(...)&& noexcept>();
    test_remove_pointer<void(...) const noexcept>();
    test_remove_pointer<void(...) const& noexcept>();
    test_remove_pointer<void(...) const&& noexcept>();
    test_remove_pointer<void(...) volatile noexcept>();
    test_remove_pointer<void(...) volatile& noexcept>();
    test_remove_pointer<void(...) volatile&& noexcept>();
    test_remove_pointer<void(...) const volatile noexcept>();
    test_remove_pointer<void(...) const volatile& noexcept>();
    test_remove_pointer<void(...) const volatile&& noexcept>();

    test_remove_pointer<void(int, ...)>();
    test_remove_pointer<void(int, ...)&>();
    test_remove_pointer<void(int, ...) &&>();
    test_remove_pointer<void(int, ...) const>();
    test_remove_pointer<void(int, ...) const&>();
    test_remove_pointer<void(int, ...) const&&>();
    test_remove_pointer<void(int, ...) volatile>();
    test_remove_pointer<void(int, ...) volatile&>();
    test_remove_pointer<void(int, ...) volatile&&>();
    test_remove_pointer<void(int, ...) const volatile>();
    test_remove_pointer<void(int, ...) const volatile&>();
    test_remove_pointer<void(int, ...) const volatile&&>();
    test_remove_pointer<void(int, ...) noexcept>();
    test_remove_pointer<void(int, ...)& noexcept>();
    test_remove_pointer<void(int, ...)&& noexcept>();
    test_remove_pointer<void(int, ...) const noexcept>();
    test_remove_pointer<void(int, ...) const& noexcept>();
    test_remove_pointer<void(int, ...) const&& noexcept>();
    test_remove_pointer<void(int, ...) volatile noexcept>();
    test_remove_pointer<void(int, ...) volatile& noexcept>();
    test_remove_pointer<void(int, ...) volatile&& noexcept>();
    test_remove_pointer<void(int, ...) const volatile noexcept>();
    test_remove_pointer<void(int, ...) const volatile& noexcept>();
    test_remove_pointer<void(int, ...) const volatile&& noexcept>();

    test_remove_pointer<int()>();
    test_remove_pointer<int()&>();
    test_remove_pointer<int() &&>();
    test_remove_pointer<int() const>();
    test_remove_pointer<int() const&>();
    test_remove_pointer<int() const&&>();
    test_remove_pointer<int() volatile>();
    test_remove_pointer<int() volatile&>();
    test_remove_pointer<int() volatile&&>();
    test_remove_pointer<int() const volatile>();
    test_remove_pointer<int() const volatile&>();
    test_remove_pointer<int() const volatile&&>();
    test_remove_pointer<int() noexcept>();
    test_remove_pointer<int()& noexcept>();
    test_remove_pointer<int()&& noexcept>();
    test_remove_pointer<int() const noexcept>();
    test_remove_pointer<int() const& noexcept>();
    test_remove_pointer<int() const&& noexcept>();
    test_remove_pointer<int() volatile noexcept>();
    test_remove_pointer<int() volatile& noexcept>();
    test_remove_pointer<int() volatile&& noexcept>();
    test_remove_pointer<int() const volatile noexcept>();
    test_remove_pointer<int() const volatile& noexcept>();
    test_remove_pointer<int() const volatile&& noexcept>();

    test_remove_pointer<int(int)>();
    test_remove_pointer<int(int)&>();
    test_remove_pointer<int(int) &&>();
    test_remove_pointer<int(int) const>();
    test_remove_pointer<int(int) const&>();
    test_remove_pointer<int(int) const&&>();
    test_remove_pointer<int(int) volatile>();
    test_remove_pointer<int(int) volatile&>();
    test_remove_pointer<int(int) volatile&&>();
    test_remove_pointer<int(int) const volatile>();
    test_remove_pointer<int(int) const volatile&>();
    test_remove_pointer<int(int) const volatile&&>();
    test_remove_pointer<int(int) noexcept>();
    test_remove_pointer<int(int)& noexcept>();
    test_remove_pointer<int(int)&& noexcept>();
    test_remove_pointer<int(int) const noexcept>();
    test_remove_pointer<int(int) const& noexcept>();
    test_remove_pointer<int(int) const&& noexcept>();
    test_remove_pointer<int(int) volatile noexcept>();
    test_remove_pointer<int(int) volatile& noexcept>();
    test_remove_pointer<int(int) volatile&& noexcept>();
    test_remove_pointer<int(int) const volatile noexcept>();
    test_remove_pointer<int(int) const volatile& noexcept>();
    test_remove_pointer<int(int) const volatile&& noexcept>();

    test_remove_pointer<int(...)>();
    test_remove_pointer<int(...)&>();
    test_remove_pointer<int(...) &&>();
    test_remove_pointer<int(...) const>();
    test_remove_pointer<int(...) const&>();
    test_remove_pointer<int(...) const&&>();
    test_remove_pointer<int(...) volatile>();
    test_remove_pointer<int(...) volatile&>();
    test_remove_pointer<int(...) volatile&&>();
    test_remove_pointer<int(...) const volatile>();
    test_remove_pointer<int(...) const volatile&>();
    test_remove_pointer<int(...) const volatile&&>();
    test_remove_pointer<int(...) noexcept>();
    test_remove_pointer<int(...)& noexcept>();
    test_remove_pointer<int(...)&& noexcept>();
    test_remove_pointer<int(...) const noexcept>();
    test_remove_pointer<int(...) const& noexcept>();
    test_remove_pointer<int(...) const&& noexcept>();
    test_remove_pointer<int(...) volatile noexcept>();
    test_remove_pointer<int(...) volatile& noexcept>();
    test_remove_pointer<int(...) volatile&& noexcept>();
    test_remove_pointer<int(...) const volatile noexcept>();
    test_remove_pointer<int(...) const volatile& noexcept>();
    test_remove_pointer<int(...) const volatile&& noexcept>();

    test_remove_pointer<int(int, ...)>();
    test_remove_pointer<int(int, ...)&>();
    test_remove_pointer<int(int, ...) &&>();
    test_remove_pointer<int(int, ...) const>();
    test_remove_pointer<int(int, ...) const&>();
    test_remove_pointer<int(int, ...) const&&>();
    test_remove_pointer<int(int, ...) volatile>();
    test_remove_pointer<int(int, ...) volatile&>();
    test_remove_pointer<int(int, ...) volatile&&>();
    test_remove_pointer<int(int, ...) const volatile>();
    test_remove_pointer<int(int, ...) const volatile&>();
    test_remove_pointer<int(int, ...) const volatile&&>();
    test_remove_pointer<int(int, ...) noexcept>();
    test_remove_pointer<int(int, ...)& noexcept>();
    test_remove_pointer<int(int, ...)&& noexcept>();
    test_remove_pointer<int(int, ...) const noexcept>();
    test_remove_pointer<int(int, ...) const& noexcept>();
    test_remove_pointer<int(int, ...) const&& noexcept>();
    test_remove_pointer<int(int, ...) volatile noexcept>();
    test_remove_pointer<int(int, ...) volatile& noexcept>();
    test_remove_pointer<int(int, ...) volatile&& noexcept>();
    test_remove_pointer<int(int, ...) const volatile noexcept>();
    test_remove_pointer<int(int, ...) const volatile& noexcept>();
    test_remove_pointer<int(int, ...) const volatile&& noexcept>();

    test_remove_pointer<void (*)(), void()>();
    test_remove_pointer<void (*)() noexcept, void() noexcept>();

    test_remove_pointer<void (*)(int), void(int)>();
    test_remove_pointer<void (*)(int) noexcept, void(int) noexcept>();

    test_remove_pointer<void (*)(...), void(...)>();
    test_remove_pointer<void (*)(...) noexcept, void(...) noexcept>();

    test_remove_pointer<void (*)(int, ...), void(int, ...)>();
    test_remove_pointer<void (*)(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_pointer<int (*)(), int()>();
    test_remove_pointer<int (*)() noexcept, int() noexcept>();

    test_remove_pointer<int (*)(int), int(int)>();
    test_remove_pointer<int (*)(int) noexcept, int(int) noexcept>();

    test_remove_pointer<int (*)(...), int(...)>();
    test_remove_pointer<int (*)(...) noexcept, int(...) noexcept>();

    test_remove_pointer<int (*)(int, ...), int(int, ...)>();
    test_remove_pointer<int (*)(int, ...) noexcept, int(int, ...) noexcept>();

    test_remove_pointer<void (&)()>();
    test_remove_pointer<void (&)() noexcept>();

    test_remove_pointer<void (&)(int)>();
    test_remove_pointer<void (&)(int) noexcept>();

    test_remove_pointer<void (&)(...)>();
    test_remove_pointer<void (&)(...) noexcept>();

    test_remove_pointer<void (&)(int, ...)>();
    test_remove_pointer<void (&)(int, ...) noexcept>();

    test_remove_pointer<int (&)()>();
    test_remove_pointer<int (&)() noexcept>();

    test_remove_pointer<int (&)(int)>();
    test_remove_pointer<int (&)(int) noexcept>();

    test_remove_pointer<int (&)(...)>();
    test_remove_pointer<int (&)(...) noexcept>();

    test_remove_pointer<int (&)(int, ...)>();
    test_remove_pointer<int (&)(int, ...) noexcept>();

    test_remove_pointer<void(&&)()>();
    test_remove_pointer<void(&&)() noexcept>();

    test_remove_pointer<void(&&)(int)>();
    test_remove_pointer<void(&&)(int) noexcept>();

    test_remove_pointer<void(&&)(...)>();
    test_remove_pointer<void(&&)(...) noexcept>();

    test_remove_pointer<void(&&)(int, ...)>();
    test_remove_pointer<void(&&)(int, ...) noexcept>();

    test_remove_pointer<int(&&)()>();
    test_remove_pointer<int(&&)() noexcept>();

    test_remove_pointer<int(&&)(int)>();
    test_remove_pointer<int(&&)(int) noexcept>();

    test_remove_pointer<int(&&)(...)>();
    test_remove_pointer<int(&&)(...) noexcept>();

    test_remove_pointer<int(&&)(int, ...)>();
    test_remove_pointer<int(&&)(int, ...) noexcept>();

    test_remove_pointer<void (Class::*)()>();
    test_remove_pointer<void (Class::*)()&>();
    test_remove_pointer<void (Class::*)() &&>();
    test_remove_pointer<void (Class::*)() const>();
    test_remove_pointer<void (Class::*)() const&>();
    test_remove_pointer<void (Class::*)() const&&>();
    test_remove_pointer<void (Class::*)() noexcept>();
    test_remove_pointer<void (Class::*)()& noexcept>();
    test_remove_pointer<void (Class::*)()&& noexcept>();
    test_remove_pointer<void (Class::*)() const noexcept>();
    test_remove_pointer<void (Class::*)() const& noexcept>();
    test_remove_pointer<void (Class::*)() const&& noexcept>();

    test_remove_pointer<void (Class::*)(int)>();
    test_remove_pointer<void (Class::*)(int)&>();
    test_remove_pointer<void (Class::*)(int) &&>();
    test_remove_pointer<void (Class::*)(int) const>();
    test_remove_pointer<void (Class::*)(int) const&>();
    test_remove_pointer<void (Class::*)(int) const&&>();
    test_remove_pointer<void (Class::*)(int) noexcept>();
    test_remove_pointer<void (Class::*)(int)& noexcept>();
    test_remove_pointer<void (Class::*)(int)&& noexcept>();
    test_remove_pointer<void (Class::*)(int) const noexcept>();
    test_remove_pointer<void (Class::*)(int) const& noexcept>();
    test_remove_pointer<void (Class::*)(int) const&& noexcept>();

    test_remove_pointer<void (Class::*)(...)>();
    test_remove_pointer<void (Class::*)(...)&>();
    test_remove_pointer<void (Class::*)(...) &&>();
    test_remove_pointer<void (Class::*)(...) const>();
    test_remove_pointer<void (Class::*)(...) const&>();
    test_remove_pointer<void (Class::*)(...) const&&>();
    test_remove_pointer<void (Class::*)(...) noexcept>();
    test_remove_pointer<void (Class::*)(...)& noexcept>();
    test_remove_pointer<void (Class::*)(...)&& noexcept>();
    test_remove_pointer<void (Class::*)(...) const noexcept>();
    test_remove_pointer<void (Class::*)(...) const& noexcept>();
    test_remove_pointer<void (Class::*)(...) const&& noexcept>();

    test_remove_pointer<void (Class::*)(int, ...)>();
    test_remove_pointer<void (Class::*)(int, ...)&>();
    test_remove_pointer<void (Class::*)(int, ...) &&>();
    test_remove_pointer<void (Class::*)(int, ...) const>();
    test_remove_pointer<void (Class::*)(int, ...) const&>();
    test_remove_pointer<void (Class::*)(int, ...) const&&>();
    test_remove_pointer<void (Class::*)(int, ...) noexcept>();
    test_remove_pointer<void (Class::*)(int, ...)& noexcept>();
    test_remove_pointer<void (Class::*)(int, ...)&& noexcept>();
    test_remove_pointer<void (Class::*)(int, ...) const noexcept>();
    test_remove_pointer<void (Class::*)(int, ...) const& noexcept>();
    test_remove_pointer<void (Class::*)(int, ...) const&& noexcept>();

    test_remove_pointer<int (Class::*)()>();
    test_remove_pointer<int (Class::*)()&>();
    test_remove_pointer<int (Class::*)() &&>();
    test_remove_pointer<int (Class::*)() const>();
    test_remove_pointer<int (Class::*)() const&>();
    test_remove_pointer<int (Class::*)() const&&>();
    test_remove_pointer<int (Class::*)() noexcept>();
    test_remove_pointer<int (Class::*)()& noexcept>();
    test_remove_pointer<int (Class::*)()&& noexcept>();
    test_remove_pointer<int (Class::*)() const noexcept>();
    test_remove_pointer<int (Class::*)() const& noexcept>();
    test_remove_pointer<int (Class::*)() const&& noexcept>();

    test_remove_pointer<int (Class::*)(int)>();
    test_remove_pointer<int (Class::*)(int)&>();
    test_remove_pointer<int (Class::*)(int) &&>();
    test_remove_pointer<int (Class::*)(int) const>();
    test_remove_pointer<int (Class::*)(int) const&>();
    test_remove_pointer<int (Class::*)(int) const&&>();
    test_remove_pointer<int (Class::*)(int) noexcept>();
    test_remove_pointer<int (Class::*)(int)& noexcept>();
    test_remove_pointer<int (Class::*)(int)&& noexcept>();
    test_remove_pointer<int (Class::*)(int) const noexcept>();
    test_remove_pointer<int (Class::*)(int) const& noexcept>();
    test_remove_pointer<int (Class::*)(int) const&& noexcept>();

    test_remove_pointer<int (Class::*)(...)>();
    test_remove_pointer<int (Class::*)(...)&>();
    test_remove_pointer<int (Class::*)(...) &&>();
    test_remove_pointer<int (Class::*)(...) const>();
    test_remove_pointer<int (Class::*)(...) const&>();
    test_remove_pointer<int (Class::*)(...) const&&>();
    test_remove_pointer<int (Class::*)(...) noexcept>();
    test_remove_pointer<int (Class::*)(...)& noexcept>();
    test_remove_pointer<int (Class::*)(...)&& noexcept>();
    test_remove_pointer<int (Class::*)(...) const noexcept>();
    test_remove_pointer<int (Class::*)(...) const& noexcept>();
    test_remove_pointer<int (Class::*)(...) const&& noexcept>();

    test_remove_pointer<int (Class::*)(int, ...)>();
    test_remove_pointer<int (Class::*)(int, ...)&>();
    test_remove_pointer<int (Class::*)(int, ...) &&>();
    test_remove_pointer<int (Class::*)(int, ...) const>();
    test_remove_pointer<int (Class::*)(int, ...) const&>();
    test_remove_pointer<int (Class::*)(int, ...) const&&>();
    test_remove_pointer<int (Class::*)(int, ...) noexcept>();
    test_remove_pointer<int (Class::*)(int, ...)& noexcept>();
    test_remove_pointer<int (Class::*)(int, ...)&& noexcept>();
    test_remove_pointer<int (Class::*)(int, ...) const noexcept>();
    test_remove_pointer<int (Class::*)(int, ...) const& noexcept>();
    test_remove_pointer<int (Class::*)(int, ...) const&& noexcept>();
}
