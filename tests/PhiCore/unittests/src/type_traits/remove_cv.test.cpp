#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_cv.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_remove_cv_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_cv<T>::type, U);
    CHECK_SAME_TYPE(phi::remove_cv_t<T>, U);

    // Standard compatibililty
    CHECK_SAME_TYPE(typename std::remove_cv<T>::type, U);
}

template <typename T, typename U = T>
void test_remove_cv()
{
    test_remove_cv_impl<T, U>();
    test_remove_cv_impl<const T, U>();
    test_remove_cv_impl<volatile T, U>();
    test_remove_cv_impl<const volatile T, U>();
}

TEST_CASE("remove_cv")
{
    test_remove_cv<void>();
    test_remove_cv<phi::nullptr_t>();
    test_remove_cv<bool>();
    test_remove_cv<char>();
    test_remove_cv<signed char>();
    test_remove_cv<unsigned char>();
    test_remove_cv<short>();
    test_remove_cv<unsigned short>();
    test_remove_cv<int>();
    test_remove_cv<unsigned int>();
    test_remove_cv<long>();
    test_remove_cv<unsigned long>();
    test_remove_cv<long long>();
    test_remove_cv<unsigned long long>();
    test_remove_cv<float>();
    test_remove_cv<double>();
    test_remove_cv<long double>();
    test_remove_cv<char8_t>();
    test_remove_cv<char16_t>();
    test_remove_cv<char32_t>();
    test_remove_cv<wchar_t>();

    test_remove_cv<phi::boolean>();
    test_remove_cv<phi::integer<signed char>>();
    test_remove_cv<phi::integer<unsigned char>>();
    test_remove_cv<phi::integer<short>>();
    test_remove_cv<phi::integer<unsigned short>>();
    test_remove_cv<phi::integer<int>>();
    test_remove_cv<phi::integer<unsigned int>>();
    test_remove_cv<phi::integer<long>>();
    test_remove_cv<phi::integer<unsigned long>>();
    test_remove_cv<phi::integer<long long>>();
    test_remove_cv<phi::integer<unsigned long long>>();
    test_remove_cv<phi::floating_point<float>>();
    test_remove_cv<phi::floating_point<double>>();
    test_remove_cv<phi::floating_point<long double>>();

    test_remove_cv<std::vector<int>>();
    test_remove_cv<phi::scope_ptr<int>>();

    test_remove_cv<int&>();
    test_remove_cv<const int&>();
    test_remove_cv<volatile int&>();
    test_remove_cv<const volatile int&>();
    test_remove_cv<int&&>();
    test_remove_cv<const int&&>();
    test_remove_cv<volatile int&&>();
    test_remove_cv<const volatile int&&>();
    test_remove_cv<int*>();
    test_remove_cv<const int*>();
    test_remove_cv<volatile int*>();
    test_remove_cv<const volatile int*>();
    test_remove_cv<int**>();
    test_remove_cv<const int**>();
    test_remove_cv<volatile int**>();
    test_remove_cv<const volatile int**>();
    test_remove_cv<int*&>();
    test_remove_cv<const int*&>();
    test_remove_cv<volatile int*&>();
    test_remove_cv<const volatile int*&>();
    test_remove_cv<int*&&>();
    test_remove_cv<const int*&&>();
    test_remove_cv<volatile int*&&>();
    test_remove_cv<const volatile int*&&>();
    test_remove_cv<void*>();
    test_remove_cv<char[3]>();
    test_remove_cv<char[]>();
    test_remove_cv<char* [3]>();
    test_remove_cv<char*[]>();
    test_remove_cv<int(*)[3]>();
    test_remove_cv<int(*)[]>();
    test_remove_cv<int(&)[3]>();
    test_remove_cv<int(&)[]>();
    test_remove_cv<int(&&)[3]>();
    test_remove_cv<int(&&)[]>();
    test_remove_cv<char[3][2]>();
    test_remove_cv<char[][2]>();
    test_remove_cv<char* [3][2]>();
    test_remove_cv<char*[][2]>();
    test_remove_cv<int(*)[3][2]>();
    test_remove_cv<int(*)[][2]>();
    test_remove_cv<int(&)[3][2]>();
    test_remove_cv<int(&)[][2]>();
    test_remove_cv<int(&&)[3][2]>();
    test_remove_cv<int(&&)[][2]>();
    test_remove_cv<Class>();
    test_remove_cv<Class[]>();
    test_remove_cv<Class[2]>();
    test_remove_cv<Template<void>>();
    test_remove_cv<Template<int>>();
    test_remove_cv<Template<Class>>();
    test_remove_cv<Template<incomplete_type>>();
    test_remove_cv<VariadicTemplate<>>();
    test_remove_cv<VariadicTemplate<void>>();
    test_remove_cv<VariadicTemplate<int>>();
    test_remove_cv<VariadicTemplate<Class>>();
    test_remove_cv<VariadicTemplate<incomplete_type>>();
    test_remove_cv<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_cv<PublicDerviedFromTemplate<Base>>();
    test_remove_cv<PublicDerviedFromTemplate<Derived>>();
    test_remove_cv<PublicDerviedFromTemplate<Class>>();
    test_remove_cv<PrivateDerviedFromTemplate<Base>>();
    test_remove_cv<PrivateDerviedFromTemplate<Derived>>();
    test_remove_cv<PrivateDerviedFromTemplate<Class>>();
    test_remove_cv<ProtectedDerviedFromTemplate<Base>>();
    test_remove_cv<ProtectedDerviedFromTemplate<Derived>>();
    test_remove_cv<ProtectedDerviedFromTemplate<Class>>();
    test_remove_cv<Union>();
    test_remove_cv<NonEmptyUnion>();
    test_remove_cv<Empty>();
    test_remove_cv<NotEmpty>();
    test_remove_cv<bit_zero>();
    test_remove_cv<bit_one>();
    test_remove_cv<Base>();
    test_remove_cv<Derived>();
    test_remove_cv<Abstract>();
    test_remove_cv<PublicAbstract>();
    test_remove_cv<PrivateAbstract>();
    test_remove_cv<ProtectedAbstract>();
    test_remove_cv<AbstractTemplate<int>>();
    test_remove_cv<AbstractTemplate<double>>();
    test_remove_cv<AbstractTemplate<Class>>();
    test_remove_cv<AbstractTemplate<incomplete_type>>();
    test_remove_cv<Final>();
    test_remove_cv<PublicDestructor>();
    test_remove_cv<ProtectedDestructor>();
    test_remove_cv<PrivateDestructor>();
    test_remove_cv<VirtualPublicDestructor>();
    test_remove_cv<VirtualProtectedDestructor>();
    test_remove_cv<VirtualPrivateDestructor>();
    test_remove_cv<PurePublicDestructor>();
    test_remove_cv<PureProtectedDestructor>();
    test_remove_cv<PurePrivateDestructor>();
    test_remove_cv<DeletedPublicDestructor>();
    test_remove_cv<DeletedProtectedDestructor>();
    test_remove_cv<DeletedPrivateDestructor>();
    test_remove_cv<DeletedVirtualPublicDestructor>();
    test_remove_cv<DeletedVirtualProtectedDestructor>();
    test_remove_cv<DeletedVirtualPrivateDestructor>();
    test_remove_cv<Enum>();
    test_remove_cv<EnumSigned>();
    test_remove_cv<EnumUnsigned>();
    test_remove_cv<EnumClass>();
    test_remove_cv<EnumStruct>();
    test_remove_cv<Function>();
    test_remove_cv<FunctionPtr>();
    test_remove_cv<MemberObjectPtr>();
    test_remove_cv<MemberFunctionPtr>();
    test_remove_cv<incomplete_type>();
    test_remove_cv<IncompleteTemplate<void>>();
    test_remove_cv<IncompleteTemplate<int>>();
    test_remove_cv<IncompleteTemplate<Class>>();
    test_remove_cv<IncompleteTemplate<incomplete_type>>();
    test_remove_cv<IncompleteVariadicTemplate<>>();
    test_remove_cv<IncompleteVariadicTemplate<void>>();
    test_remove_cv<IncompleteVariadicTemplate<int>>();
    test_remove_cv<IncompleteVariadicTemplate<Class>>();
    test_remove_cv<IncompleteVariadicTemplate<incomplete_type>>();
    test_remove_cv<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_cv<int Class::*>();
    test_remove_cv<float Class::*>();
    test_remove_cv<void * Class::*>();
    test_remove_cv<int * Class::*>();
    test_remove_cv<int Class::*&>();
    test_remove_cv<float Class::*&>();
    test_remove_cv<void * Class::*&>();
    test_remove_cv<int * Class::*&>();
    test_remove_cv<int Class::*&&>();
    test_remove_cv<float Class::*&&>();
    test_remove_cv<void * Class::*&&>();
    test_remove_cv<int * Class::*&&>();
    test_remove_cv<int Class::*const, int Class::*>();
    test_remove_cv<float Class::*const, float Class::*>();
    test_remove_cv<void * Class::*const, void * Class::*>();
    test_remove_cv<int Class::*const&>();
    test_remove_cv<float Class::*const&>();
    test_remove_cv<void * Class::*const&>();
    test_remove_cv<int Class::*const&&>();
    test_remove_cv<float Class::*const&&>();
    test_remove_cv<void * Class::*const&&>();
    test_remove_cv<int Class::*volatile, int Class::*>();
    test_remove_cv<float Class::*volatile, float Class::*>();
    test_remove_cv<void * Class::*volatile, void * Class::*>();
    test_remove_cv<int Class::*volatile&>();
    test_remove_cv<float Class::*volatile&>();
    test_remove_cv<void * Class::*volatile&>();
    test_remove_cv<int Class::*volatile&&>();
    test_remove_cv<float Class::*volatile&&>();
    test_remove_cv<void * Class::*volatile&&>();
    test_remove_cv<int Class::*const volatile, int Class::*>();
    test_remove_cv<float Class::*const volatile, float Class::*>();
    test_remove_cv<void * Class::*const volatile, void * Class::*>();
    test_remove_cv<int Class::*const volatile&>();
    test_remove_cv<float Class::*const volatile&>();
    test_remove_cv<void * Class::*const volatile&>();
    test_remove_cv<int Class::*const volatile&&>();
    test_remove_cv<float Class::*const volatile&&>();
    test_remove_cv<void * Class::*const volatile&&>();
    test_remove_cv<NonCopyable>();
    test_remove_cv<NonMoveable>();
    test_remove_cv<NonConstructible>();
    test_remove_cv<Tracked>();
    test_remove_cv<TrapConstructible>();
    test_remove_cv<TrapImplicitConversion>();
    test_remove_cv<TrapComma>();
    test_remove_cv<TrapCall>();
    test_remove_cv<TrapSelfAssign>();
    test_remove_cv<TrapDeref>();
    test_remove_cv<TrapArraySubscript>();

    test_remove_cv<void()>();
    test_remove_cv<void()&>();
    test_remove_cv<void() &&>();
    test_remove_cv<void() const>();
    test_remove_cv<void() const&>();
    test_remove_cv<void() const&&>();
    test_remove_cv<void() volatile>();
    test_remove_cv<void() volatile&>();
    test_remove_cv<void() volatile&&>();
    test_remove_cv<void() const volatile>();
    test_remove_cv<void() const volatile&>();
    test_remove_cv<void() const volatile&&>();
    test_remove_cv<void() noexcept>();
    test_remove_cv<void()& noexcept>();
    test_remove_cv<void()&& noexcept>();
    test_remove_cv<void() const noexcept>();
    test_remove_cv<void() const& noexcept>();
    test_remove_cv<void() const&& noexcept>();
    test_remove_cv<void() volatile noexcept>();
    test_remove_cv<void() volatile& noexcept>();
    test_remove_cv<void() volatile&& noexcept>();
    test_remove_cv<void() const volatile noexcept>();
    test_remove_cv<void() const volatile& noexcept>();
    test_remove_cv<void() const volatile&& noexcept>();

    test_remove_cv<void(int)>();
    test_remove_cv<void(int)&>();
    test_remove_cv<void(int) &&>();
    test_remove_cv<void(int) const>();
    test_remove_cv<void(int) const&>();
    test_remove_cv<void(int) const&&>();
    test_remove_cv<void(int) volatile>();
    test_remove_cv<void(int) volatile&>();
    test_remove_cv<void(int) volatile&&>();
    test_remove_cv<void(int) const volatile>();
    test_remove_cv<void(int) const volatile&>();
    test_remove_cv<void(int) const volatile&&>();
    test_remove_cv<void(int) noexcept>();
    test_remove_cv<void(int)& noexcept>();
    test_remove_cv<void(int)&& noexcept>();
    test_remove_cv<void(int) const noexcept>();
    test_remove_cv<void(int) const& noexcept>();
    test_remove_cv<void(int) const&& noexcept>();
    test_remove_cv<void(int) volatile noexcept>();
    test_remove_cv<void(int) volatile& noexcept>();
    test_remove_cv<void(int) volatile&& noexcept>();
    test_remove_cv<void(int) const volatile noexcept>();
    test_remove_cv<void(int) const volatile& noexcept>();
    test_remove_cv<void(int) const volatile&& noexcept>();

    test_remove_cv<void(...)>();
    test_remove_cv<void(...)&>();
    test_remove_cv<void(...) &&>();
    test_remove_cv<void(...) const>();
    test_remove_cv<void(...) const&>();
    test_remove_cv<void(...) const&&>();
    test_remove_cv<void(...) volatile>();
    test_remove_cv<void(...) volatile&>();
    test_remove_cv<void(...) volatile&&>();
    test_remove_cv<void(...) const volatile>();
    test_remove_cv<void(...) const volatile&>();
    test_remove_cv<void(...) const volatile&&>();
    test_remove_cv<void(...) noexcept>();
    test_remove_cv<void(...)& noexcept>();
    test_remove_cv<void(...)&& noexcept>();
    test_remove_cv<void(...) const noexcept>();
    test_remove_cv<void(...) const& noexcept>();
    test_remove_cv<void(...) const&& noexcept>();
    test_remove_cv<void(...) volatile noexcept>();
    test_remove_cv<void(...) volatile& noexcept>();
    test_remove_cv<void(...) volatile&& noexcept>();
    test_remove_cv<void(...) const volatile noexcept>();
    test_remove_cv<void(...) const volatile& noexcept>();
    test_remove_cv<void(...) const volatile&& noexcept>();

    test_remove_cv<void(int, ...)>();
    test_remove_cv<void(int, ...)&>();
    test_remove_cv<void(int, ...) &&>();
    test_remove_cv<void(int, ...) const>();
    test_remove_cv<void(int, ...) const&>();
    test_remove_cv<void(int, ...) const&&>();
    test_remove_cv<void(int, ...) volatile>();
    test_remove_cv<void(int, ...) volatile&>();
    test_remove_cv<void(int, ...) volatile&&>();
    test_remove_cv<void(int, ...) const volatile>();
    test_remove_cv<void(int, ...) const volatile&>();
    test_remove_cv<void(int, ...) const volatile&&>();
    test_remove_cv<void(int, ...) noexcept>();
    test_remove_cv<void(int, ...)& noexcept>();
    test_remove_cv<void(int, ...)&& noexcept>();
    test_remove_cv<void(int, ...) const noexcept>();
    test_remove_cv<void(int, ...) const& noexcept>();
    test_remove_cv<void(int, ...) const&& noexcept>();
    test_remove_cv<void(int, ...) volatile noexcept>();
    test_remove_cv<void(int, ...) volatile& noexcept>();
    test_remove_cv<void(int, ...) volatile&& noexcept>();
    test_remove_cv<void(int, ...) const volatile noexcept>();
    test_remove_cv<void(int, ...) const volatile& noexcept>();
    test_remove_cv<void(int, ...) const volatile&& noexcept>();

    test_remove_cv<int()>();
    test_remove_cv<int()&>();
    test_remove_cv<int() &&>();
    test_remove_cv<int() const>();
    test_remove_cv<int() const&>();
    test_remove_cv<int() const&&>();
    test_remove_cv<int() volatile>();
    test_remove_cv<int() volatile&>();
    test_remove_cv<int() volatile&&>();
    test_remove_cv<int() const volatile>();
    test_remove_cv<int() const volatile&>();
    test_remove_cv<int() const volatile&&>();
    test_remove_cv<int() noexcept>();
    test_remove_cv<int()& noexcept>();
    test_remove_cv<int()&& noexcept>();
    test_remove_cv<int() const noexcept>();
    test_remove_cv<int() const& noexcept>();
    test_remove_cv<int() const&& noexcept>();
    test_remove_cv<int() volatile noexcept>();
    test_remove_cv<int() volatile& noexcept>();
    test_remove_cv<int() volatile&& noexcept>();
    test_remove_cv<int() const volatile noexcept>();
    test_remove_cv<int() const volatile& noexcept>();
    test_remove_cv<int() const volatile&& noexcept>();

    test_remove_cv<int(int)>();
    test_remove_cv<int(int)&>();
    test_remove_cv<int(int) &&>();
    test_remove_cv<int(int) const>();
    test_remove_cv<int(int) const&>();
    test_remove_cv<int(int) const&&>();
    test_remove_cv<int(int) volatile>();
    test_remove_cv<int(int) volatile&>();
    test_remove_cv<int(int) volatile&&>();
    test_remove_cv<int(int) const volatile>();
    test_remove_cv<int(int) const volatile&>();
    test_remove_cv<int(int) const volatile&&>();
    test_remove_cv<int(int) noexcept>();
    test_remove_cv<int(int)& noexcept>();
    test_remove_cv<int(int)&& noexcept>();
    test_remove_cv<int(int) const noexcept>();
    test_remove_cv<int(int) const& noexcept>();
    test_remove_cv<int(int) const&& noexcept>();
    test_remove_cv<int(int) volatile noexcept>();
    test_remove_cv<int(int) volatile& noexcept>();
    test_remove_cv<int(int) volatile&& noexcept>();
    test_remove_cv<int(int) const volatile noexcept>();
    test_remove_cv<int(int) const volatile& noexcept>();
    test_remove_cv<int(int) const volatile&& noexcept>();

    test_remove_cv<int(...)>();
    test_remove_cv<int(...)&>();
    test_remove_cv<int(...) &&>();
    test_remove_cv<int(...) const>();
    test_remove_cv<int(...) const&>();
    test_remove_cv<int(...) const&&>();
    test_remove_cv<int(...) volatile>();
    test_remove_cv<int(...) volatile&>();
    test_remove_cv<int(...) volatile&&>();
    test_remove_cv<int(...) const volatile>();
    test_remove_cv<int(...) const volatile&>();
    test_remove_cv<int(...) const volatile&&>();
    test_remove_cv<int(...) noexcept>();
    test_remove_cv<int(...)& noexcept>();
    test_remove_cv<int(...)&& noexcept>();
    test_remove_cv<int(...) const noexcept>();
    test_remove_cv<int(...) const& noexcept>();
    test_remove_cv<int(...) const&& noexcept>();
    test_remove_cv<int(...) volatile noexcept>();
    test_remove_cv<int(...) volatile& noexcept>();
    test_remove_cv<int(...) volatile&& noexcept>();
    test_remove_cv<int(...) const volatile noexcept>();
    test_remove_cv<int(...) const volatile& noexcept>();
    test_remove_cv<int(...) const volatile&& noexcept>();

    test_remove_cv<int(int, ...)>();
    test_remove_cv<int(int, ...)&>();
    test_remove_cv<int(int, ...) &&>();
    test_remove_cv<int(int, ...) const>();
    test_remove_cv<int(int, ...) const&>();
    test_remove_cv<int(int, ...) const&&>();
    test_remove_cv<int(int, ...) volatile>();
    test_remove_cv<int(int, ...) volatile&>();
    test_remove_cv<int(int, ...) volatile&&>();
    test_remove_cv<int(int, ...) const volatile>();
    test_remove_cv<int(int, ...) const volatile&>();
    test_remove_cv<int(int, ...) const volatile&&>();
    test_remove_cv<int(int, ...) noexcept>();
    test_remove_cv<int(int, ...)& noexcept>();
    test_remove_cv<int(int, ...)&& noexcept>();
    test_remove_cv<int(int, ...) const noexcept>();
    test_remove_cv<int(int, ...) const& noexcept>();
    test_remove_cv<int(int, ...) const&& noexcept>();
    test_remove_cv<int(int, ...) volatile noexcept>();
    test_remove_cv<int(int, ...) volatile& noexcept>();
    test_remove_cv<int(int, ...) volatile&& noexcept>();
    test_remove_cv<int(int, ...) const volatile noexcept>();
    test_remove_cv<int(int, ...) const volatile& noexcept>();
    test_remove_cv<int(int, ...) const volatile&& noexcept>();

    test_remove_cv<void (*)()>();
    test_remove_cv<void (*)() noexcept>();

    test_remove_cv<void (*)(int)>();
    test_remove_cv<void (*)(int) noexcept>();

    test_remove_cv<void (*)(...)>();
    test_remove_cv<void (*)(...) noexcept>();

    test_remove_cv<void (*)(int, ...)>();
    test_remove_cv<void (*)(int, ...) noexcept>();

    test_remove_cv<int (*)()>();
    test_remove_cv<int (*)() noexcept>();

    test_remove_cv<int (*)(int)>();
    test_remove_cv<int (*)(int) noexcept>();

    test_remove_cv<int (*)(...)>();
    test_remove_cv<int (*)(...) noexcept>();

    test_remove_cv<int (*)(int, ...)>();
    test_remove_cv<int (*)(int, ...) noexcept>();

    test_remove_cv<void (&)()>();
    test_remove_cv<void (&)() noexcept>();

    test_remove_cv<void (&)(int)>();
    test_remove_cv<void (&)(int) noexcept>();

    test_remove_cv<void (&)(...)>();
    test_remove_cv<void (&)(...) noexcept>();

    test_remove_cv<void (&)(int, ...)>();
    test_remove_cv<void (&)(int, ...) noexcept>();

    test_remove_cv<int (&)()>();
    test_remove_cv<int (&)() noexcept>();

    test_remove_cv<int (&)(int)>();
    test_remove_cv<int (&)(int) noexcept>();

    test_remove_cv<int (&)(...)>();
    test_remove_cv<int (&)(...) noexcept>();

    test_remove_cv<int (&)(int, ...)>();
    test_remove_cv<int (&)(int, ...) noexcept>();

    test_remove_cv<void(&&)()>();
    test_remove_cv<void(&&)() noexcept>();

    test_remove_cv<void(&&)(int)>();
    test_remove_cv<void(&&)(int) noexcept>();

    test_remove_cv<void(&&)(...)>();
    test_remove_cv<void(&&)(...) noexcept>();

    test_remove_cv<void(&&)(int, ...)>();
    test_remove_cv<void(&&)(int, ...) noexcept>();

    test_remove_cv<int(&&)()>();
    test_remove_cv<int(&&)() noexcept>();

    test_remove_cv<int(&&)(int)>();
    test_remove_cv<int(&&)(int) noexcept>();

    test_remove_cv<int(&&)(...)>();
    test_remove_cv<int(&&)(...) noexcept>();

    test_remove_cv<int(&&)(int, ...)>();
    test_remove_cv<int(&&)(int, ...) noexcept>();

    test_remove_cv<void (Class::*)()>();
    test_remove_cv<void (Class::*)()&>();
    test_remove_cv<void (Class::*)() &&>();
    test_remove_cv<void (Class::*)() const>();
    test_remove_cv<void (Class::*)() const&>();
    test_remove_cv<void (Class::*)() const&&>();
    test_remove_cv<void (Class::*)() noexcept>();
    test_remove_cv<void (Class::*)()& noexcept>();
    test_remove_cv<void (Class::*)()&& noexcept>();
    test_remove_cv<void (Class::*)() const noexcept>();
    test_remove_cv<void (Class::*)() const& noexcept>();
    test_remove_cv<void (Class::*)() const&& noexcept>();

    test_remove_cv<void (Class::*)(int)>();
    test_remove_cv<void (Class::*)(int)&>();
    test_remove_cv<void (Class::*)(int) &&>();
    test_remove_cv<void (Class::*)(int) const>();
    test_remove_cv<void (Class::*)(int) const&>();
    test_remove_cv<void (Class::*)(int) const&&>();
    test_remove_cv<void (Class::*)(int) noexcept>();
    test_remove_cv<void (Class::*)(int)& noexcept>();
    test_remove_cv<void (Class::*)(int)&& noexcept>();
    test_remove_cv<void (Class::*)(int) const noexcept>();
    test_remove_cv<void (Class::*)(int) const& noexcept>();
    test_remove_cv<void (Class::*)(int) const&& noexcept>();

    test_remove_cv<void (Class::*)(...)>();
    test_remove_cv<void (Class::*)(...)&>();
    test_remove_cv<void (Class::*)(...) &&>();
    test_remove_cv<void (Class::*)(...) const>();
    test_remove_cv<void (Class::*)(...) const&>();
    test_remove_cv<void (Class::*)(...) const&&>();
    test_remove_cv<void (Class::*)(...) noexcept>();
    test_remove_cv<void (Class::*)(...)& noexcept>();
    test_remove_cv<void (Class::*)(...)&& noexcept>();
    test_remove_cv<void (Class::*)(...) const noexcept>();
    test_remove_cv<void (Class::*)(...) const& noexcept>();
    test_remove_cv<void (Class::*)(...) const&& noexcept>();

    test_remove_cv<void (Class::*)(int, ...)>();
    test_remove_cv<void (Class::*)(int, ...)&>();
    test_remove_cv<void (Class::*)(int, ...) &&>();
    test_remove_cv<void (Class::*)(int, ...) const>();
    test_remove_cv<void (Class::*)(int, ...) const&>();
    test_remove_cv<void (Class::*)(int, ...) const&&>();
    test_remove_cv<void (Class::*)(int, ...) noexcept>();
    test_remove_cv<void (Class::*)(int, ...)& noexcept>();
    test_remove_cv<void (Class::*)(int, ...)&& noexcept>();
    test_remove_cv<void (Class::*)(int, ...) const noexcept>();
    test_remove_cv<void (Class::*)(int, ...) const& noexcept>();
    test_remove_cv<void (Class::*)(int, ...) const&& noexcept>();

    test_remove_cv<int (Class::*)()>();
    test_remove_cv<int (Class::*)()&>();
    test_remove_cv<int (Class::*)() &&>();
    test_remove_cv<int (Class::*)() const>();
    test_remove_cv<int (Class::*)() const&>();
    test_remove_cv<int (Class::*)() const&&>();
    test_remove_cv<int (Class::*)() noexcept>();
    test_remove_cv<int (Class::*)()& noexcept>();
    test_remove_cv<int (Class::*)()&& noexcept>();
    test_remove_cv<int (Class::*)() const noexcept>();
    test_remove_cv<int (Class::*)() const& noexcept>();
    test_remove_cv<int (Class::*)() const&& noexcept>();

    test_remove_cv<int (Class::*)(int)>();
    test_remove_cv<int (Class::*)(int)&>();
    test_remove_cv<int (Class::*)(int) &&>();
    test_remove_cv<int (Class::*)(int) const>();
    test_remove_cv<int (Class::*)(int) const&>();
    test_remove_cv<int (Class::*)(int) const&&>();
    test_remove_cv<int (Class::*)(int) noexcept>();
    test_remove_cv<int (Class::*)(int)& noexcept>();
    test_remove_cv<int (Class::*)(int)&& noexcept>();
    test_remove_cv<int (Class::*)(int) const noexcept>();
    test_remove_cv<int (Class::*)(int) const& noexcept>();
    test_remove_cv<int (Class::*)(int) const&& noexcept>();

    test_remove_cv<int (Class::*)(...)>();
    test_remove_cv<int (Class::*)(...)&>();
    test_remove_cv<int (Class::*)(...) &&>();
    test_remove_cv<int (Class::*)(...) const>();
    test_remove_cv<int (Class::*)(...) const&>();
    test_remove_cv<int (Class::*)(...) const&&>();
    test_remove_cv<int (Class::*)(...) noexcept>();
    test_remove_cv<int (Class::*)(...)& noexcept>();
    test_remove_cv<int (Class::*)(...)&& noexcept>();
    test_remove_cv<int (Class::*)(...) const noexcept>();
    test_remove_cv<int (Class::*)(...) const& noexcept>();
    test_remove_cv<int (Class::*)(...) const&& noexcept>();

    test_remove_cv<int (Class::*)(int, ...)>();
    test_remove_cv<int (Class::*)(int, ...)&>();
    test_remove_cv<int (Class::*)(int, ...) &&>();
    test_remove_cv<int (Class::*)(int, ...) const>();
    test_remove_cv<int (Class::*)(int, ...) const&>();
    test_remove_cv<int (Class::*)(int, ...) const&&>();
    test_remove_cv<int (Class::*)(int, ...) noexcept>();
    test_remove_cv<int (Class::*)(int, ...)& noexcept>();
    test_remove_cv<int (Class::*)(int, ...)&& noexcept>();
    test_remove_cv<int (Class::*)(int, ...) const noexcept>();
    test_remove_cv<int (Class::*)(int, ...) const& noexcept>();
    test_remove_cv<int (Class::*)(int, ...) const&& noexcept>();
}
