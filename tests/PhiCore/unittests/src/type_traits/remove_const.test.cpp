#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_const.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_remove_const_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_const<T>::type, U);
    CHECK_SAME_TYPE(phi::remove_const_t<T>, U);

    // Standard compatibililty
    CHECK_SAME_TYPE(typename std::remove_const<T>::type, U);
}

template <typename T, typename U = T>
void test_remove_const()
{
    test_remove_const_impl<T, U>();
    test_remove_const_impl<const T, U>();
    test_remove_const_impl<volatile T, volatile U>();
    test_remove_const_impl<const volatile T, volatile U>();
}

TEST_CASE("remove_const")
{
    test_remove_const<void>();
    test_remove_const<phi::nullptr_t>();
    test_remove_const<bool>();
    test_remove_const<char>();
    test_remove_const<signed char>();
    test_remove_const<unsigned char>();
    test_remove_const<short>();
    test_remove_const<unsigned short>();
    test_remove_const<int>();
    test_remove_const<unsigned int>();
    test_remove_const<long>();
    test_remove_const<unsigned long>();
    test_remove_const<long long>();
    test_remove_const<unsigned long long>();
    test_remove_const<float>();
    test_remove_const<double>();
    test_remove_const<long double>();
    test_remove_const<char8_t>();
    test_remove_const<char16_t>();
    test_remove_const<char32_t>();
    test_remove_const<wchar_t>();

    test_remove_const<phi::boolean>();
    test_remove_const<phi::integer<signed char>>();
    test_remove_const<phi::integer<unsigned char>>();
    test_remove_const<phi::integer<short>>();
    test_remove_const<phi::integer<unsigned short>>();
    test_remove_const<phi::integer<int>>();
    test_remove_const<phi::integer<unsigned int>>();
    test_remove_const<phi::integer<long>>();
    test_remove_const<phi::integer<unsigned long>>();
    test_remove_const<phi::integer<long long>>();
    test_remove_const<phi::integer<unsigned long long>>();
    test_remove_const<phi::floating_point<float>>();
    test_remove_const<phi::floating_point<double>>();
    test_remove_const<phi::floating_point<long double>>();

    test_remove_const<std::vector<int>>();
    test_remove_const<phi::scope_ptr<int>>();

    test_remove_const<int&>();
    test_remove_const<const int&>();
    test_remove_const<volatile int&>();
    test_remove_const<const volatile int&>();
    test_remove_const<int&&>();
    test_remove_const<const int&&>();
    test_remove_const<volatile int&&>();
    test_remove_const<const volatile int&&>();
    test_remove_const<int*>();
    test_remove_const<const int*>();
    test_remove_const<volatile int*>();
    test_remove_const<const volatile int*>();
    test_remove_const<int**>();
    test_remove_const<const int**>();
    test_remove_const<volatile int**>();
    test_remove_const<const volatile int**>();
    test_remove_const<int*&>();
    test_remove_const<const int*&>();
    test_remove_const<volatile int*&>();
    test_remove_const<const volatile int*&>();
    test_remove_const<int*&&>();
    test_remove_const<const int*&&>();
    test_remove_const<volatile int*&&>();
    test_remove_const<const volatile int*&&>();
    test_remove_const<void*>();
    test_remove_const<char[3]>();
    test_remove_const<char[]>();
    test_remove_const<char* [3]>();
    test_remove_const<char*[]>();
    test_remove_const<int(*)[3]>();
    test_remove_const<int(*)[]>();
    test_remove_const<int(&)[3]>();
    test_remove_const<int(&)[]>();
    test_remove_const<int(&&)[3]>();
    test_remove_const<int(&&)[]>();
    test_remove_const<char[3][2]>();
    test_remove_const<char[][2]>();
    test_remove_const<char* [3][2]>();
    test_remove_const<char*[][2]>();
    test_remove_const<int(*)[3][2]>();
    test_remove_const<int(*)[][2]>();
    test_remove_const<int(&)[3][2]>();
    test_remove_const<int(&)[][2]>();
    test_remove_const<int(&&)[3][2]>();
    test_remove_const<int(&&)[][2]>();
    test_remove_const<Class>();
    test_remove_const<Class[]>();
    test_remove_const<Class[2]>();
    test_remove_const<Template<void>>();
    test_remove_const<Template<int>>();
    test_remove_const<Template<Class>>();
    test_remove_const<Template<incomplete_type>>();
    test_remove_const<VariadicTemplate<>>();
    test_remove_const<VariadicTemplate<void>>();
    test_remove_const<VariadicTemplate<int>>();
    test_remove_const<VariadicTemplate<Class>>();
    test_remove_const<VariadicTemplate<incomplete_type>>();
    test_remove_const<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_const<PublicDerviedFromTemplate<Base>>();
    test_remove_const<PublicDerviedFromTemplate<Derived>>();
    test_remove_const<PublicDerviedFromTemplate<Class>>();
    test_remove_const<PrivateDerviedFromTemplate<Base>>();
    test_remove_const<PrivateDerviedFromTemplate<Derived>>();
    test_remove_const<PrivateDerviedFromTemplate<Class>>();
    test_remove_const<ProtectedDerviedFromTemplate<Base>>();
    test_remove_const<ProtectedDerviedFromTemplate<Derived>>();
    test_remove_const<ProtectedDerviedFromTemplate<Class>>();
    test_remove_const<Union>();
    test_remove_const<NonEmptyUnion>();
    test_remove_const<Empty>();
    test_remove_const<NotEmpty>();
    test_remove_const<bit_zero>();
    test_remove_const<bit_one>();
    test_remove_const<Base>();
    test_remove_const<Derived>();
    test_remove_const<Abstract>();
    test_remove_const<PublicAbstract>();
    test_remove_const<PrivateAbstract>();
    test_remove_const<ProtectedAbstract>();
    test_remove_const<AbstractTemplate<int>>();
    test_remove_const<AbstractTemplate<double>>();
    test_remove_const<AbstractTemplate<Class>>();
    test_remove_const<AbstractTemplate<incomplete_type>>();
    test_remove_const<Final>();
    test_remove_const<PublicDestructor>();
    test_remove_const<ProtectedDestructor>();
    test_remove_const<PrivateDestructor>();
    test_remove_const<VirtualPublicDestructor>();
    test_remove_const<VirtualProtectedDestructor>();
    test_remove_const<VirtualPrivateDestructor>();
    test_remove_const<PurePublicDestructor>();
    test_remove_const<PureProtectedDestructor>();
    test_remove_const<PurePrivateDestructor>();
    test_remove_const<DeletedPublicDestructor>();
    test_remove_const<DeletedProtectedDestructor>();
    test_remove_const<DeletedPrivateDestructor>();
    test_remove_const<DeletedVirtualPublicDestructor>();
    test_remove_const<DeletedVirtualProtectedDestructor>();
    test_remove_const<DeletedVirtualPrivateDestructor>();
    test_remove_const<Enum>();
    test_remove_const<EnumSigned>();
    test_remove_const<EnumUnsigned>();
    test_remove_const<EnumClass>();
    test_remove_const<EnumStruct>();
    test_remove_const<Function>();
    test_remove_const<FunctionPtr>();
    test_remove_const<MemberObjectPtr>();
    test_remove_const<MemberFunctionPtr>();
    test_remove_const<incomplete_type>();
    test_remove_const<IncompleteTemplate<void>>();
    test_remove_const<IncompleteTemplate<int>>();
    test_remove_const<IncompleteTemplate<Class>>();
    test_remove_const<IncompleteTemplate<incomplete_type>>();
    test_remove_const<IncompleteVariadicTemplate<>>();
    test_remove_const<IncompleteVariadicTemplate<void>>();
    test_remove_const<IncompleteVariadicTemplate<int>>();
    test_remove_const<IncompleteVariadicTemplate<Class>>();
    test_remove_const<IncompleteVariadicTemplate<incomplete_type>>();
    test_remove_const<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_const<int Class::*>();
    test_remove_const<float Class::*>();
    test_remove_const<void * Class::*>();
    test_remove_const<int * Class::*>();
    test_remove_const<int Class::*&>();
    test_remove_const<float Class::*&>();
    test_remove_const<void * Class::*&>();
    test_remove_const<int * Class::*&>();
    test_remove_const<int Class::*&&>();
    test_remove_const<float Class::*&&>();
    test_remove_const<void * Class::*&&>();
    test_remove_const<int * Class::*&&>();
    test_remove_const<int Class::*const, int Class::*>();
    test_remove_const<float Class::*const, float Class::*>();
    test_remove_const<void * Class::*const, void * Class::*>();
    test_remove_const<int Class::*const&>();
    test_remove_const<float Class::*const&>();
    test_remove_const<void * Class::*const&>();
    test_remove_const<int Class::*const&&>();
    test_remove_const<float Class::*const&&>();
    test_remove_const<void * Class::*const&&>();
    test_remove_const<int Class::*volatile>();
    test_remove_const<float Class::*volatile>();
    test_remove_const<void * Class::*volatile>();
    test_remove_const<int Class::*volatile&>();
    test_remove_const<float Class::*volatile&>();
    test_remove_const<void * Class::*volatile&>();
    test_remove_const<int Class::*volatile&&>();
    test_remove_const<float Class::*volatile&&>();
    test_remove_const<void * Class::*volatile&&>();
    test_remove_const<int Class::*const volatile, int Class::*volatile>();
    test_remove_const<float Class::*const volatile, float Class::*volatile>();
    test_remove_const<void * Class::*const volatile, void * Class::*volatile>();
    test_remove_const<int Class::*const volatile&>();
    test_remove_const<float Class::*const volatile&>();
    test_remove_const<void * Class::*const volatile&>();
    test_remove_const<int Class::*const volatile&&>();
    test_remove_const<float Class::*const volatile&&>();
    test_remove_const<void * Class::*const volatile&&>();
    test_remove_const<NonCopyable>();
    test_remove_const<NonMoveable>();
    test_remove_const<NonConstructible>();
    test_remove_const<Tracked>();
    test_remove_const<TrapConstructible>();
    test_remove_const<TrapImplicitConversion>();
    test_remove_const<TrapComma>();
    test_remove_const<TrapCall>();
    test_remove_const<TrapSelfAssign>();
    test_remove_const<TrapDeref>();
    test_remove_const<TrapArraySubscript>();

    test_remove_const<void()>();
    test_remove_const<void()&>();
    test_remove_const<void() &&>();
    test_remove_const<void() const>();
    test_remove_const<void() const&>();
    test_remove_const<void() const&&>();
    test_remove_const<void() volatile>();
    test_remove_const<void() volatile&>();
    test_remove_const<void() volatile&&>();
    test_remove_const<void() const volatile>();
    test_remove_const<void() const volatile&>();
    test_remove_const<void() const volatile&&>();
    test_remove_const<void() noexcept>();
    test_remove_const<void()& noexcept>();
    test_remove_const<void()&& noexcept>();
    test_remove_const<void() const noexcept>();
    test_remove_const<void() const& noexcept>();
    test_remove_const<void() const&& noexcept>();
    test_remove_const<void() volatile noexcept>();
    test_remove_const<void() volatile& noexcept>();
    test_remove_const<void() volatile&& noexcept>();
    test_remove_const<void() const volatile noexcept>();
    test_remove_const<void() const volatile& noexcept>();
    test_remove_const<void() const volatile&& noexcept>();

    test_remove_const<void(int)>();
    test_remove_const<void(int)&>();
    test_remove_const<void(int) &&>();
    test_remove_const<void(int) const>();
    test_remove_const<void(int) const&>();
    test_remove_const<void(int) const&&>();
    test_remove_const<void(int) volatile>();
    test_remove_const<void(int) volatile&>();
    test_remove_const<void(int) volatile&&>();
    test_remove_const<void(int) const volatile>();
    test_remove_const<void(int) const volatile&>();
    test_remove_const<void(int) const volatile&&>();
    test_remove_const<void(int) noexcept>();
    test_remove_const<void(int)& noexcept>();
    test_remove_const<void(int)&& noexcept>();
    test_remove_const<void(int) const noexcept>();
    test_remove_const<void(int) const& noexcept>();
    test_remove_const<void(int) const&& noexcept>();
    test_remove_const<void(int) volatile noexcept>();
    test_remove_const<void(int) volatile& noexcept>();
    test_remove_const<void(int) volatile&& noexcept>();
    test_remove_const<void(int) const volatile noexcept>();
    test_remove_const<void(int) const volatile& noexcept>();
    test_remove_const<void(int) const volatile&& noexcept>();

    test_remove_const<void(...)>();
    test_remove_const<void(...)&>();
    test_remove_const<void(...) &&>();
    test_remove_const<void(...) const>();
    test_remove_const<void(...) const&>();
    test_remove_const<void(...) const&&>();
    test_remove_const<void(...) volatile>();
    test_remove_const<void(...) volatile&>();
    test_remove_const<void(...) volatile&&>();
    test_remove_const<void(...) const volatile>();
    test_remove_const<void(...) const volatile&>();
    test_remove_const<void(...) const volatile&&>();
    test_remove_const<void(...) noexcept>();
    test_remove_const<void(...)& noexcept>();
    test_remove_const<void(...)&& noexcept>();
    test_remove_const<void(...) const noexcept>();
    test_remove_const<void(...) const& noexcept>();
    test_remove_const<void(...) const&& noexcept>();
    test_remove_const<void(...) volatile noexcept>();
    test_remove_const<void(...) volatile& noexcept>();
    test_remove_const<void(...) volatile&& noexcept>();
    test_remove_const<void(...) const volatile noexcept>();
    test_remove_const<void(...) const volatile& noexcept>();
    test_remove_const<void(...) const volatile&& noexcept>();

    test_remove_const<void(int, ...)>();
    test_remove_const<void(int, ...)&>();
    test_remove_const<void(int, ...) &&>();
    test_remove_const<void(int, ...) const>();
    test_remove_const<void(int, ...) const&>();
    test_remove_const<void(int, ...) const&&>();
    test_remove_const<void(int, ...) volatile>();
    test_remove_const<void(int, ...) volatile&>();
    test_remove_const<void(int, ...) volatile&&>();
    test_remove_const<void(int, ...) const volatile>();
    test_remove_const<void(int, ...) const volatile&>();
    test_remove_const<void(int, ...) const volatile&&>();
    test_remove_const<void(int, ...) noexcept>();
    test_remove_const<void(int, ...)& noexcept>();
    test_remove_const<void(int, ...)&& noexcept>();
    test_remove_const<void(int, ...) const noexcept>();
    test_remove_const<void(int, ...) const& noexcept>();
    test_remove_const<void(int, ...) const&& noexcept>();
    test_remove_const<void(int, ...) volatile noexcept>();
    test_remove_const<void(int, ...) volatile& noexcept>();
    test_remove_const<void(int, ...) volatile&& noexcept>();
    test_remove_const<void(int, ...) const volatile noexcept>();
    test_remove_const<void(int, ...) const volatile& noexcept>();
    test_remove_const<void(int, ...) const volatile&& noexcept>();

    test_remove_const<int()>();
    test_remove_const<int()&>();
    test_remove_const<int() &&>();
    test_remove_const<int() const>();
    test_remove_const<int() const&>();
    test_remove_const<int() const&&>();
    test_remove_const<int() volatile>();
    test_remove_const<int() volatile&>();
    test_remove_const<int() volatile&&>();
    test_remove_const<int() const volatile>();
    test_remove_const<int() const volatile&>();
    test_remove_const<int() const volatile&&>();
    test_remove_const<int() noexcept>();
    test_remove_const<int()& noexcept>();
    test_remove_const<int()&& noexcept>();
    test_remove_const<int() const noexcept>();
    test_remove_const<int() const& noexcept>();
    test_remove_const<int() const&& noexcept>();
    test_remove_const<int() volatile noexcept>();
    test_remove_const<int() volatile& noexcept>();
    test_remove_const<int() volatile&& noexcept>();
    test_remove_const<int() const volatile noexcept>();
    test_remove_const<int() const volatile& noexcept>();
    test_remove_const<int() const volatile&& noexcept>();

    test_remove_const<int(int)>();
    test_remove_const<int(int)&>();
    test_remove_const<int(int) &&>();
    test_remove_const<int(int) const>();
    test_remove_const<int(int) const&>();
    test_remove_const<int(int) const&&>();
    test_remove_const<int(int) volatile>();
    test_remove_const<int(int) volatile&>();
    test_remove_const<int(int) volatile&&>();
    test_remove_const<int(int) const volatile>();
    test_remove_const<int(int) const volatile&>();
    test_remove_const<int(int) const volatile&&>();
    test_remove_const<int(int) noexcept>();
    test_remove_const<int(int)& noexcept>();
    test_remove_const<int(int)&& noexcept>();
    test_remove_const<int(int) const noexcept>();
    test_remove_const<int(int) const& noexcept>();
    test_remove_const<int(int) const&& noexcept>();
    test_remove_const<int(int) volatile noexcept>();
    test_remove_const<int(int) volatile& noexcept>();
    test_remove_const<int(int) volatile&& noexcept>();
    test_remove_const<int(int) const volatile noexcept>();
    test_remove_const<int(int) const volatile& noexcept>();
    test_remove_const<int(int) const volatile&& noexcept>();

    test_remove_const<int(...)>();
    test_remove_const<int(...)&>();
    test_remove_const<int(...) &&>();
    test_remove_const<int(...) const>();
    test_remove_const<int(...) const&>();
    test_remove_const<int(...) const&&>();
    test_remove_const<int(...) volatile>();
    test_remove_const<int(...) volatile&>();
    test_remove_const<int(...) volatile&&>();
    test_remove_const<int(...) const volatile>();
    test_remove_const<int(...) const volatile&>();
    test_remove_const<int(...) const volatile&&>();
    test_remove_const<int(...) noexcept>();
    test_remove_const<int(...)& noexcept>();
    test_remove_const<int(...)&& noexcept>();
    test_remove_const<int(...) const noexcept>();
    test_remove_const<int(...) const& noexcept>();
    test_remove_const<int(...) const&& noexcept>();
    test_remove_const<int(...) volatile noexcept>();
    test_remove_const<int(...) volatile& noexcept>();
    test_remove_const<int(...) volatile&& noexcept>();
    test_remove_const<int(...) const volatile noexcept>();
    test_remove_const<int(...) const volatile& noexcept>();
    test_remove_const<int(...) const volatile&& noexcept>();

    test_remove_const<int(int, ...)>();
    test_remove_const<int(int, ...)&>();
    test_remove_const<int(int, ...) &&>();
    test_remove_const<int(int, ...) const>();
    test_remove_const<int(int, ...) const&>();
    test_remove_const<int(int, ...) const&&>();
    test_remove_const<int(int, ...) volatile>();
    test_remove_const<int(int, ...) volatile&>();
    test_remove_const<int(int, ...) volatile&&>();
    test_remove_const<int(int, ...) const volatile>();
    test_remove_const<int(int, ...) const volatile&>();
    test_remove_const<int(int, ...) const volatile&&>();
    test_remove_const<int(int, ...) noexcept>();
    test_remove_const<int(int, ...)& noexcept>();
    test_remove_const<int(int, ...)&& noexcept>();
    test_remove_const<int(int, ...) const noexcept>();
    test_remove_const<int(int, ...) const& noexcept>();
    test_remove_const<int(int, ...) const&& noexcept>();
    test_remove_const<int(int, ...) volatile noexcept>();
    test_remove_const<int(int, ...) volatile& noexcept>();
    test_remove_const<int(int, ...) volatile&& noexcept>();
    test_remove_const<int(int, ...) const volatile noexcept>();
    test_remove_const<int(int, ...) const volatile& noexcept>();
    test_remove_const<int(int, ...) const volatile&& noexcept>();

    test_remove_const<void (*)()>();
    test_remove_const<void (*)() noexcept>();

    test_remove_const<void (*)(int)>();
    test_remove_const<void (*)(int) noexcept>();

    test_remove_const<void (*)(...)>();
    test_remove_const<void (*)(...) noexcept>();

    test_remove_const<void (*)(int, ...)>();
    test_remove_const<void (*)(int, ...) noexcept>();

    test_remove_const<int (*)()>();
    test_remove_const<int (*)() noexcept>();

    test_remove_const<int (*)(int)>();
    test_remove_const<int (*)(int) noexcept>();

    test_remove_const<int (*)(...)>();
    test_remove_const<int (*)(...) noexcept>();

    test_remove_const<int (*)(int, ...)>();
    test_remove_const<int (*)(int, ...) noexcept>();

    test_remove_const<void (&)()>();
    test_remove_const<void (&)() noexcept>();

    test_remove_const<void (&)(int)>();
    test_remove_const<void (&)(int) noexcept>();

    test_remove_const<void (&)(...)>();
    test_remove_const<void (&)(...) noexcept>();

    test_remove_const<void (&)(int, ...)>();
    test_remove_const<void (&)(int, ...) noexcept>();

    test_remove_const<int (&)()>();
    test_remove_const<int (&)() noexcept>();

    test_remove_const<int (&)(int)>();
    test_remove_const<int (&)(int) noexcept>();

    test_remove_const<int (&)(...)>();
    test_remove_const<int (&)(...) noexcept>();

    test_remove_const<int (&)(int, ...)>();
    test_remove_const<int (&)(int, ...) noexcept>();

    test_remove_const<void(&&)()>();
    test_remove_const<void(&&)() noexcept>();

    test_remove_const<void(&&)(int)>();
    test_remove_const<void(&&)(int) noexcept>();

    test_remove_const<void(&&)(...)>();
    test_remove_const<void(&&)(...) noexcept>();

    test_remove_const<void(&&)(int, ...)>();
    test_remove_const<void(&&)(int, ...) noexcept>();

    test_remove_const<int(&&)()>();
    test_remove_const<int(&&)() noexcept>();

    test_remove_const<int(&&)(int)>();
    test_remove_const<int(&&)(int) noexcept>();

    test_remove_const<int(&&)(...)>();
    test_remove_const<int(&&)(...) noexcept>();

    test_remove_const<int(&&)(int, ...)>();
    test_remove_const<int(&&)(int, ...) noexcept>();

    test_remove_const<void (Class::*)()>();
    test_remove_const<void (Class::*)()&>();
    test_remove_const<void (Class::*)() &&>();
    test_remove_const<void (Class::*)() const>();
    test_remove_const<void (Class::*)() const&>();
    test_remove_const<void (Class::*)() const&&>();
    test_remove_const<void (Class::*)() noexcept>();
    test_remove_const<void (Class::*)()& noexcept>();
    test_remove_const<void (Class::*)()&& noexcept>();
    test_remove_const<void (Class::*)() const noexcept>();
    test_remove_const<void (Class::*)() const& noexcept>();
    test_remove_const<void (Class::*)() const&& noexcept>();

    test_remove_const<void (Class::*)(int)>();
    test_remove_const<void (Class::*)(int)&>();
    test_remove_const<void (Class::*)(int) &&>();
    test_remove_const<void (Class::*)(int) const>();
    test_remove_const<void (Class::*)(int) const&>();
    test_remove_const<void (Class::*)(int) const&&>();
    test_remove_const<void (Class::*)(int) noexcept>();
    test_remove_const<void (Class::*)(int)& noexcept>();
    test_remove_const<void (Class::*)(int)&& noexcept>();
    test_remove_const<void (Class::*)(int) const noexcept>();
    test_remove_const<void (Class::*)(int) const& noexcept>();
    test_remove_const<void (Class::*)(int) const&& noexcept>();

    test_remove_const<void (Class::*)(...)>();
    test_remove_const<void (Class::*)(...)&>();
    test_remove_const<void (Class::*)(...) &&>();
    test_remove_const<void (Class::*)(...) const>();
    test_remove_const<void (Class::*)(...) const&>();
    test_remove_const<void (Class::*)(...) const&&>();
    test_remove_const<void (Class::*)(...) noexcept>();
    test_remove_const<void (Class::*)(...)& noexcept>();
    test_remove_const<void (Class::*)(...)&& noexcept>();
    test_remove_const<void (Class::*)(...) const noexcept>();
    test_remove_const<void (Class::*)(...) const& noexcept>();
    test_remove_const<void (Class::*)(...) const&& noexcept>();

    test_remove_const<void (Class::*)(int, ...)>();
    test_remove_const<void (Class::*)(int, ...)&>();
    test_remove_const<void (Class::*)(int, ...) &&>();
    test_remove_const<void (Class::*)(int, ...) const>();
    test_remove_const<void (Class::*)(int, ...) const&>();
    test_remove_const<void (Class::*)(int, ...) const&&>();
    test_remove_const<void (Class::*)(int, ...) noexcept>();
    test_remove_const<void (Class::*)(int, ...)& noexcept>();
    test_remove_const<void (Class::*)(int, ...)&& noexcept>();
    test_remove_const<void (Class::*)(int, ...) const noexcept>();
    test_remove_const<void (Class::*)(int, ...) const& noexcept>();
    test_remove_const<void (Class::*)(int, ...) const&& noexcept>();

    test_remove_const<int (Class::*)()>();
    test_remove_const<int (Class::*)()&>();
    test_remove_const<int (Class::*)() &&>();
    test_remove_const<int (Class::*)() const>();
    test_remove_const<int (Class::*)() const&>();
    test_remove_const<int (Class::*)() const&&>();
    test_remove_const<int (Class::*)() noexcept>();
    test_remove_const<int (Class::*)()& noexcept>();
    test_remove_const<int (Class::*)()&& noexcept>();
    test_remove_const<int (Class::*)() const noexcept>();
    test_remove_const<int (Class::*)() const& noexcept>();
    test_remove_const<int (Class::*)() const&& noexcept>();

    test_remove_const<int (Class::*)(int)>();
    test_remove_const<int (Class::*)(int)&>();
    test_remove_const<int (Class::*)(int) &&>();
    test_remove_const<int (Class::*)(int) const>();
    test_remove_const<int (Class::*)(int) const&>();
    test_remove_const<int (Class::*)(int) const&&>();
    test_remove_const<int (Class::*)(int) noexcept>();
    test_remove_const<int (Class::*)(int)& noexcept>();
    test_remove_const<int (Class::*)(int)&& noexcept>();
    test_remove_const<int (Class::*)(int) const noexcept>();
    test_remove_const<int (Class::*)(int) const& noexcept>();
    test_remove_const<int (Class::*)(int) const&& noexcept>();

    test_remove_const<int (Class::*)(...)>();
    test_remove_const<int (Class::*)(...)&>();
    test_remove_const<int (Class::*)(...) &&>();
    test_remove_const<int (Class::*)(...) const>();
    test_remove_const<int (Class::*)(...) const&>();
    test_remove_const<int (Class::*)(...) const&&>();
    test_remove_const<int (Class::*)(...) noexcept>();
    test_remove_const<int (Class::*)(...)& noexcept>();
    test_remove_const<int (Class::*)(...)&& noexcept>();
    test_remove_const<int (Class::*)(...) const noexcept>();
    test_remove_const<int (Class::*)(...) const& noexcept>();
    test_remove_const<int (Class::*)(...) const&& noexcept>();

    test_remove_const<int (Class::*)(int, ...)>();
    test_remove_const<int (Class::*)(int, ...)&>();
    test_remove_const<int (Class::*)(int, ...) &&>();
    test_remove_const<int (Class::*)(int, ...) const>();
    test_remove_const<int (Class::*)(int, ...) const&>();
    test_remove_const<int (Class::*)(int, ...) const&&>();
    test_remove_const<int (Class::*)(int, ...) noexcept>();
    test_remove_const<int (Class::*)(int, ...)& noexcept>();
    test_remove_const<int (Class::*)(int, ...)&& noexcept>();
    test_remove_const<int (Class::*)(int, ...) const noexcept>();
    test_remove_const<int (Class::*)(int, ...) const& noexcept>();
    test_remove_const<int (Class::*)(int, ...) const&& noexcept>();
}
