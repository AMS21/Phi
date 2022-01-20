#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_reference.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_remove_reference_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_reference<T>::type, U);
    CHECK_SAME_TYPE(phi::remove_reference_t<T>, U);

    // Standard compatibililty
    CHECK_SAME_TYPE(typename std::remove_reference<T>::type, U);
}

template <typename T, typename U = T>
void test_remove_reference()
{
    test_remove_reference_impl<T, U>();
    test_remove_reference_impl<const T, const U>();
    test_remove_reference_impl<volatile T, volatile U>();
    test_remove_reference_impl<const volatile T, const volatile U>();
}

template <typename T, typename U>
void test_remove_reference_ref()
{
    test_remove_reference_impl<T, U>();
}

TEST_CASE("remove_reference")
{
    test_remove_reference<void>();
    test_remove_reference<phi::nullptr_t>();
    test_remove_reference<bool>();
    test_remove_reference<char>();
    test_remove_reference<signed char>();
    test_remove_reference<unsigned char>();
    test_remove_reference<short>();
    test_remove_reference<unsigned short>();
    test_remove_reference<int>();
    test_remove_reference<unsigned int>();
    test_remove_reference<long>();
    test_remove_reference<unsigned long>();
    test_remove_reference<long long>();
    test_remove_reference<unsigned long long>();
    test_remove_reference<float>();
    test_remove_reference<double>();
    test_remove_reference<long double>();
    test_remove_reference<char8_t>();
    test_remove_reference<char16_t>();
    test_remove_reference<char32_t>();
    test_remove_reference<wchar_t>();

    test_remove_reference<phi::boolean>();
    test_remove_reference<phi::integer<signed char>>();
    test_remove_reference<phi::integer<unsigned char>>();
    test_remove_reference<phi::integer<short>>();
    test_remove_reference<phi::integer<unsigned short>>();
    test_remove_reference<phi::integer<int>>();
    test_remove_reference<phi::integer<unsigned int>>();
    test_remove_reference<phi::integer<long>>();
    test_remove_reference<phi::integer<unsigned long>>();
    test_remove_reference<phi::integer<long long>>();
    test_remove_reference<phi::integer<unsigned long long>>();
    test_remove_reference<phi::floating_point<float>>();
    test_remove_reference<phi::floating_point<double>>();
    test_remove_reference<phi::floating_point<long double>>();

    test_remove_reference<std::vector<int>>();
    test_remove_reference<phi::scope_ptr<int>>();

    test_remove_reference_ref<int&, int>();
    test_remove_reference_ref<const int&, const int>();
    test_remove_reference_ref<volatile int&, volatile int>();
    test_remove_reference_ref<const volatile int&, const volatile int>();
    test_remove_reference_ref<int&&, int>();
    test_remove_reference_ref<const int&&, const int>();
    test_remove_reference_ref<volatile int&&, volatile int>();
    test_remove_reference_ref<const volatile int&&, const volatile int>();
    test_remove_reference<int*>();
    test_remove_reference<const int*>();
    test_remove_reference<volatile int*>();
    test_remove_reference<const volatile int*>();
    test_remove_reference<int**>();
    test_remove_reference<const int**>();
    test_remove_reference<volatile int**>();
    test_remove_reference<const volatile int**>();
    test_remove_reference_ref<int*&, int*>();
    test_remove_reference_ref<const int*&, const int*>();
    test_remove_reference_ref<volatile int*&, volatile int*>();
    test_remove_reference_ref<const volatile int*&, const volatile int*>();
    test_remove_reference_ref<int*&&, int*>();
    test_remove_reference_ref<const int*&&, const int*>();
    test_remove_reference_ref<volatile int*&&, volatile int*>();
    test_remove_reference_ref<const volatile int*&&, const volatile int*>();
    test_remove_reference<void*>();
    test_remove_reference<char[3]>();
    test_remove_reference<char[]>();
    test_remove_reference<char* [3]>();
    test_remove_reference<char*[]>();
    test_remove_reference<int(*)[3]>();
    test_remove_reference<int(*)[]>();
    test_remove_reference_ref<int(&)[3], int[3]>();
    test_remove_reference_ref<int(&)[], int[]>();
    test_remove_reference_ref<int(&&)[3], int[3]>();
    test_remove_reference_ref<int(&&)[], int[]>();
    test_remove_reference<char[3][2]>();
    test_remove_reference<char[][2]>();
    test_remove_reference<char* [3][2]>();
    test_remove_reference<char*[][2]>();
    test_remove_reference<int(*)[3][2]>();
    test_remove_reference<int(*)[][2]>();
    test_remove_reference_ref<int(&)[3][2], int[3][2]>();
    test_remove_reference_ref<int(&)[][2], int[][2]>();
    test_remove_reference_ref<int(&&)[3][2], int[3][2]>();
    test_remove_reference_ref<int(&&)[][2], int[][2]>();
    test_remove_reference<Class>();
    test_remove_reference<Class[]>();
    test_remove_reference<Class[2]>();
    test_remove_reference<Template<void>>();
    test_remove_reference<Template<int>>();
    test_remove_reference<Template<Class>>();
    test_remove_reference<Template<incomplete_type>>();
    test_remove_reference<VariadicTemplate<>>();
    test_remove_reference<VariadicTemplate<void>>();
    test_remove_reference<VariadicTemplate<int>>();
    test_remove_reference<VariadicTemplate<Class>>();
    test_remove_reference<VariadicTemplate<incomplete_type>>();
    test_remove_reference<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_reference<PublicDerviedFromTemplate<Base>>();
    test_remove_reference<PublicDerviedFromTemplate<Derived>>();
    test_remove_reference<PublicDerviedFromTemplate<Class>>();
    test_remove_reference<PrivateDerviedFromTemplate<Base>>();
    test_remove_reference<PrivateDerviedFromTemplate<Derived>>();
    test_remove_reference<PrivateDerviedFromTemplate<Class>>();
    test_remove_reference<ProtectedDerviedFromTemplate<Base>>();
    test_remove_reference<ProtectedDerviedFromTemplate<Derived>>();
    test_remove_reference<ProtectedDerviedFromTemplate<Class>>();
    test_remove_reference<Union>();
    test_remove_reference<NonEmptyUnion>();
    test_remove_reference<Empty>();
    test_remove_reference<NotEmpty>();
    test_remove_reference<bit_zero>();
    test_remove_reference<bit_one>();
    test_remove_reference<Base>();
    test_remove_reference<Derived>();
    test_remove_reference<Abstract>();
    test_remove_reference<PublicAbstract>();
    test_remove_reference<PrivateAbstract>();
    test_remove_reference<ProtectedAbstract>();
    test_remove_reference<AbstractTemplate<int>>();
    test_remove_reference<AbstractTemplate<double>>();
    test_remove_reference<AbstractTemplate<Class>>();
    test_remove_reference<AbstractTemplate<incomplete_type>>();
    test_remove_reference<Final>();
    test_remove_reference<PublicDestructor>();
    test_remove_reference<ProtectedDestructor>();
    test_remove_reference<PrivateDestructor>();
    test_remove_reference<VirtualPublicDestructor>();
    test_remove_reference<VirtualProtectedDestructor>();
    test_remove_reference<VirtualPrivateDestructor>();
    test_remove_reference<PurePublicDestructor>();
    test_remove_reference<PureProtectedDestructor>();
    test_remove_reference<PurePrivateDestructor>();
    test_remove_reference<DeletedPublicDestructor>();
    test_remove_reference<DeletedProtectedDestructor>();
    test_remove_reference<DeletedPrivateDestructor>();
    test_remove_reference<DeletedVirtualPublicDestructor>();
    test_remove_reference<DeletedVirtualProtectedDestructor>();
    test_remove_reference<DeletedVirtualPrivateDestructor>();
    test_remove_reference<Enum>();
    test_remove_reference<EnumSigned>();
    test_remove_reference<EnumUnsigned>();
    test_remove_reference<EnumClass>();
    test_remove_reference<EnumStruct>();
    test_remove_reference<Function>();
    test_remove_reference<FunctionPtr>();
    test_remove_reference<MemberObjectPtr>();
    test_remove_reference<MemberFunctionPtr>();
    test_remove_reference<incomplete_type>();
    test_remove_reference<IncompleteTemplate<void>>();
    test_remove_reference<IncompleteTemplate<int>>();
    test_remove_reference<IncompleteTemplate<Class>>();
    test_remove_reference<IncompleteTemplate<incomplete_type>>();
    test_remove_reference<IncompleteVariadicTemplate<>>();
    test_remove_reference<IncompleteVariadicTemplate<void>>();
    test_remove_reference<IncompleteVariadicTemplate<int>>();
    test_remove_reference<IncompleteVariadicTemplate<Class>>();
    test_remove_reference<IncompleteVariadicTemplate<incomplete_type>>();
    test_remove_reference<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_reference<int Class::*>();
    test_remove_reference<float Class::*>();
    test_remove_reference<void * Class::*>();
    test_remove_reference<int * Class::*>();
    test_remove_reference_ref<int Class::*&, int Class::*>();
    test_remove_reference_ref<float Class::*&, float Class::*>();
    test_remove_reference_ref<void * Class::*&, void * Class::*>();
    test_remove_reference_ref<int * Class::*&, int * Class::*>();
    test_remove_reference_ref<int Class::*&&, int Class::*>();
    test_remove_reference_ref<float Class::*&&, float Class::*>();
    test_remove_reference_ref<void * Class::*&&, void * Class::*>();
    test_remove_reference_ref<int * Class::*&&, int * Class::*>();
    test_remove_reference<int Class::*const>();
    test_remove_reference<float Class::*const>();
    test_remove_reference<void * Class::*const>();
    test_remove_reference_ref<int Class::*const&, int Class::*const>();
    test_remove_reference_ref<float Class::*const&, float Class::*const>();
    test_remove_reference_ref<void * Class::*const&, void * Class::*const>();
    test_remove_reference_ref<int Class::*const&&, int Class::*const>();
    test_remove_reference_ref<float Class::*const&&, float Class::*const>();
    test_remove_reference_ref<void * Class::*const&&, void * Class::*const>();
    test_remove_reference<int Class::*volatile>();
    test_remove_reference<float Class::*volatile>();
    test_remove_reference<void * Class::*volatile>();
    test_remove_reference_ref<int Class::*volatile&, int Class::*volatile>();
    test_remove_reference_ref<float Class::*volatile&, float Class::*volatile>();
    test_remove_reference_ref<void * Class::*volatile&, void * Class::*volatile>();
    test_remove_reference_ref<int Class::*volatile&&, int Class::*volatile>();
    test_remove_reference_ref<float Class::*volatile&&, float Class::*volatile>();
    test_remove_reference_ref<void * Class::*volatile&&, void * Class::*volatile>();
    test_remove_reference<int Class::*const volatile>();
    test_remove_reference<float Class::*const volatile>();
    test_remove_reference<void * Class::*const volatile>();
    test_remove_reference_ref<int Class::*const volatile&, int Class::*const volatile>();
    test_remove_reference_ref<float Class::*const volatile&, float Class::*const volatile>();
    test_remove_reference_ref<void * Class::*const volatile&, void * Class::*const volatile>();
    test_remove_reference_ref<int Class::*const volatile&&, int Class::*const volatile>();
    test_remove_reference_ref<float Class::*const volatile&&, float Class::*const volatile>();
    test_remove_reference_ref<void * Class::*const volatile&&, void * Class::*const volatile>();
    test_remove_reference<NonCopyable>();
    test_remove_reference<NonMoveable>();
    test_remove_reference<NonConstructible>();
    test_remove_reference<Tracked>();
    test_remove_reference<TrapConstructible>();
    test_remove_reference<TrapImplicitConversion>();
    test_remove_reference<TrapComma>();
    test_remove_reference<TrapCall>();
    test_remove_reference<TrapSelfAssign>();
    test_remove_reference<TrapDeref>();
    test_remove_reference<TrapArraySubscript>();

    test_remove_reference<void()>();
    test_remove_reference<void()&>();
    test_remove_reference<void() &&>();
    test_remove_reference<void() const>();
    test_remove_reference<void() const&>();
    test_remove_reference<void() const&&>();
    test_remove_reference<void() volatile>();
    test_remove_reference<void() volatile&>();
    test_remove_reference<void() volatile&&>();
    test_remove_reference<void() const volatile>();
    test_remove_reference<void() const volatile&>();
    test_remove_reference<void() const volatile&&>();
    test_remove_reference<void() noexcept>();
    test_remove_reference<void()& noexcept>();
    test_remove_reference<void()&& noexcept>();
    test_remove_reference<void() const noexcept>();
    test_remove_reference<void() const& noexcept>();
    test_remove_reference<void() const&& noexcept>();
    test_remove_reference<void() volatile noexcept>();
    test_remove_reference<void() volatile& noexcept>();
    test_remove_reference<void() volatile&& noexcept>();
    test_remove_reference<void() const volatile noexcept>();
    test_remove_reference<void() const volatile& noexcept>();
    test_remove_reference<void() const volatile&& noexcept>();

    test_remove_reference<void(int)>();
    test_remove_reference<void(int)&>();
    test_remove_reference<void(int) &&>();
    test_remove_reference<void(int) const>();
    test_remove_reference<void(int) const&>();
    test_remove_reference<void(int) const&&>();
    test_remove_reference<void(int) volatile>();
    test_remove_reference<void(int) volatile&>();
    test_remove_reference<void(int) volatile&&>();
    test_remove_reference<void(int) const volatile>();
    test_remove_reference<void(int) const volatile&>();
    test_remove_reference<void(int) const volatile&&>();
    test_remove_reference<void(int) noexcept>();
    test_remove_reference<void(int)& noexcept>();
    test_remove_reference<void(int)&& noexcept>();
    test_remove_reference<void(int) const noexcept>();
    test_remove_reference<void(int) const& noexcept>();
    test_remove_reference<void(int) const&& noexcept>();
    test_remove_reference<void(int) volatile noexcept>();
    test_remove_reference<void(int) volatile& noexcept>();
    test_remove_reference<void(int) volatile&& noexcept>();
    test_remove_reference<void(int) const volatile noexcept>();
    test_remove_reference<void(int) const volatile& noexcept>();
    test_remove_reference<void(int) const volatile&& noexcept>();

    test_remove_reference<void(...)>();
    test_remove_reference<void(...)&>();
    test_remove_reference<void(...) &&>();
    test_remove_reference<void(...) const>();
    test_remove_reference<void(...) const&>();
    test_remove_reference<void(...) const&&>();
    test_remove_reference<void(...) volatile>();
    test_remove_reference<void(...) volatile&>();
    test_remove_reference<void(...) volatile&&>();
    test_remove_reference<void(...) const volatile>();
    test_remove_reference<void(...) const volatile&>();
    test_remove_reference<void(...) const volatile&&>();
    test_remove_reference<void(...) noexcept>();
    test_remove_reference<void(...)& noexcept>();
    test_remove_reference<void(...)&& noexcept>();
    test_remove_reference<void(...) const noexcept>();
    test_remove_reference<void(...) const& noexcept>();
    test_remove_reference<void(...) const&& noexcept>();
    test_remove_reference<void(...) volatile noexcept>();
    test_remove_reference<void(...) volatile& noexcept>();
    test_remove_reference<void(...) volatile&& noexcept>();
    test_remove_reference<void(...) const volatile noexcept>();
    test_remove_reference<void(...) const volatile& noexcept>();
    test_remove_reference<void(...) const volatile&& noexcept>();

    test_remove_reference<void(int, ...)>();
    test_remove_reference<void(int, ...)&>();
    test_remove_reference<void(int, ...) &&>();
    test_remove_reference<void(int, ...) const>();
    test_remove_reference<void(int, ...) const&>();
    test_remove_reference<void(int, ...) const&&>();
    test_remove_reference<void(int, ...) volatile>();
    test_remove_reference<void(int, ...) volatile&>();
    test_remove_reference<void(int, ...) volatile&&>();
    test_remove_reference<void(int, ...) const volatile>();
    test_remove_reference<void(int, ...) const volatile&>();
    test_remove_reference<void(int, ...) const volatile&&>();
    test_remove_reference<void(int, ...) noexcept>();
    test_remove_reference<void(int, ...)& noexcept>();
    test_remove_reference<void(int, ...)&& noexcept>();
    test_remove_reference<void(int, ...) const noexcept>();
    test_remove_reference<void(int, ...) const& noexcept>();
    test_remove_reference<void(int, ...) const&& noexcept>();
    test_remove_reference<void(int, ...) volatile noexcept>();
    test_remove_reference<void(int, ...) volatile& noexcept>();
    test_remove_reference<void(int, ...) volatile&& noexcept>();
    test_remove_reference<void(int, ...) const volatile noexcept>();
    test_remove_reference<void(int, ...) const volatile& noexcept>();
    test_remove_reference<void(int, ...) const volatile&& noexcept>();

    test_remove_reference<int()>();
    test_remove_reference<int()&>();
    test_remove_reference<int() &&>();
    test_remove_reference<int() const>();
    test_remove_reference<int() const&>();
    test_remove_reference<int() const&&>();
    test_remove_reference<int() volatile>();
    test_remove_reference<int() volatile&>();
    test_remove_reference<int() volatile&&>();
    test_remove_reference<int() const volatile>();
    test_remove_reference<int() const volatile&>();
    test_remove_reference<int() const volatile&&>();
    test_remove_reference<int() noexcept>();
    test_remove_reference<int()& noexcept>();
    test_remove_reference<int()&& noexcept>();
    test_remove_reference<int() const noexcept>();
    test_remove_reference<int() const& noexcept>();
    test_remove_reference<int() const&& noexcept>();
    test_remove_reference<int() volatile noexcept>();
    test_remove_reference<int() volatile& noexcept>();
    test_remove_reference<int() volatile&& noexcept>();
    test_remove_reference<int() const volatile noexcept>();
    test_remove_reference<int() const volatile& noexcept>();
    test_remove_reference<int() const volatile&& noexcept>();

    test_remove_reference<int(int)>();
    test_remove_reference<int(int)&>();
    test_remove_reference<int(int) &&>();
    test_remove_reference<int(int) const>();
    test_remove_reference<int(int) const&>();
    test_remove_reference<int(int) const&&>();
    test_remove_reference<int(int) volatile>();
    test_remove_reference<int(int) volatile&>();
    test_remove_reference<int(int) volatile&&>();
    test_remove_reference<int(int) const volatile>();
    test_remove_reference<int(int) const volatile&>();
    test_remove_reference<int(int) const volatile&&>();
    test_remove_reference<int(int) noexcept>();
    test_remove_reference<int(int)& noexcept>();
    test_remove_reference<int(int)&& noexcept>();
    test_remove_reference<int(int) const noexcept>();
    test_remove_reference<int(int) const& noexcept>();
    test_remove_reference<int(int) const&& noexcept>();
    test_remove_reference<int(int) volatile noexcept>();
    test_remove_reference<int(int) volatile& noexcept>();
    test_remove_reference<int(int) volatile&& noexcept>();
    test_remove_reference<int(int) const volatile noexcept>();
    test_remove_reference<int(int) const volatile& noexcept>();
    test_remove_reference<int(int) const volatile&& noexcept>();

    test_remove_reference<int(...)>();
    test_remove_reference<int(...)&>();
    test_remove_reference<int(...) &&>();
    test_remove_reference<int(...) const>();
    test_remove_reference<int(...) const&>();
    test_remove_reference<int(...) const&&>();
    test_remove_reference<int(...) volatile>();
    test_remove_reference<int(...) volatile&>();
    test_remove_reference<int(...) volatile&&>();
    test_remove_reference<int(...) const volatile>();
    test_remove_reference<int(...) const volatile&>();
    test_remove_reference<int(...) const volatile&&>();
    test_remove_reference<int(...) noexcept>();
    test_remove_reference<int(...)& noexcept>();
    test_remove_reference<int(...)&& noexcept>();
    test_remove_reference<int(...) const noexcept>();
    test_remove_reference<int(...) const& noexcept>();
    test_remove_reference<int(...) const&& noexcept>();
    test_remove_reference<int(...) volatile noexcept>();
    test_remove_reference<int(...) volatile& noexcept>();
    test_remove_reference<int(...) volatile&& noexcept>();
    test_remove_reference<int(...) const volatile noexcept>();
    test_remove_reference<int(...) const volatile& noexcept>();
    test_remove_reference<int(...) const volatile&& noexcept>();

    test_remove_reference<int(int, ...)>();
    test_remove_reference<int(int, ...)&>();
    test_remove_reference<int(int, ...) &&>();
    test_remove_reference<int(int, ...) const>();
    test_remove_reference<int(int, ...) const&>();
    test_remove_reference<int(int, ...) const&&>();
    test_remove_reference<int(int, ...) volatile>();
    test_remove_reference<int(int, ...) volatile&>();
    test_remove_reference<int(int, ...) volatile&&>();
    test_remove_reference<int(int, ...) const volatile>();
    test_remove_reference<int(int, ...) const volatile&>();
    test_remove_reference<int(int, ...) const volatile&&>();
    test_remove_reference<int(int, ...) noexcept>();
    test_remove_reference<int(int, ...)& noexcept>();
    test_remove_reference<int(int, ...)&& noexcept>();
    test_remove_reference<int(int, ...) const noexcept>();
    test_remove_reference<int(int, ...) const& noexcept>();
    test_remove_reference<int(int, ...) const&& noexcept>();
    test_remove_reference<int(int, ...) volatile noexcept>();
    test_remove_reference<int(int, ...) volatile& noexcept>();
    test_remove_reference<int(int, ...) volatile&& noexcept>();
    test_remove_reference<int(int, ...) const volatile noexcept>();
    test_remove_reference<int(int, ...) const volatile& noexcept>();
    test_remove_reference<int(int, ...) const volatile&& noexcept>();

    test_remove_reference<void (*)()>();
    test_remove_reference<void (*)() noexcept>();

    test_remove_reference<void (*)(int)>();
    test_remove_reference<void (*)(int) noexcept>();

    test_remove_reference<void (*)(...)>();
    test_remove_reference<void (*)(...) noexcept>();

    test_remove_reference<void (*)(int, ...)>();
    test_remove_reference<void (*)(int, ...) noexcept>();

    test_remove_reference<int (*)()>();
    test_remove_reference<int (*)() noexcept>();

    test_remove_reference<int (*)(int)>();
    test_remove_reference<int (*)(int) noexcept>();

    test_remove_reference<int (*)(...)>();
    test_remove_reference<int (*)(...) noexcept>();

    test_remove_reference<int (*)(int, ...)>();
    test_remove_reference<int (*)(int, ...) noexcept>();

    test_remove_reference_ref<void (&)(), void()>();
    test_remove_reference_ref<void (&)() noexcept, void() noexcept>();

    test_remove_reference_ref<void (&)(int), void(int)>();
    test_remove_reference_ref<void (&)(int) noexcept, void(int) noexcept>();

    test_remove_reference_ref<void (&)(...), void(...)>();
    test_remove_reference_ref<void (&)(...) noexcept, void(...) noexcept>();

    test_remove_reference_ref<void (&)(int, ...), void(int, ...)>();
    test_remove_reference_ref<void (&)(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_reference_ref<int (&)(), int()>();
    test_remove_reference_ref<int (&)() noexcept, int() noexcept>();

    test_remove_reference_ref<int (&)(int), int(int)>();
    test_remove_reference_ref<int (&)(int) noexcept, int(int) noexcept>();

    test_remove_reference_ref<int (&)(...), int(...)>();
    test_remove_reference_ref<int (&)(...) noexcept, int(...) noexcept>();

    test_remove_reference_ref<int (&)(int, ...), int(int, ...)>();
    test_remove_reference_ref<int (&)(int, ...) noexcept, int(int, ...) noexcept>();

    test_remove_reference_ref<void(&&)(), void()>();
    test_remove_reference_ref<void(&&)() noexcept, void() noexcept>();

    test_remove_reference_ref<void(&&)(int), void(int)>();
    test_remove_reference_ref<void(&&)(int) noexcept, void(int) noexcept>();

    test_remove_reference_ref<void(&&)(...), void(...)>();
    test_remove_reference_ref<void(&&)(...) noexcept, void(...) noexcept>();

    test_remove_reference_ref<void(&&)(int, ...), void(int, ...)>();
    test_remove_reference_ref<void(&&)(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_reference_ref<int(&&)(), int()>();
    test_remove_reference_ref<int(&&)() noexcept, int() noexcept>();

    test_remove_reference_ref<int(&&)(int), int(int)>();
    test_remove_reference_ref<int(&&)(int) noexcept, int(int) noexcept>();

    test_remove_reference_ref<int(&&)(...), int(...)>();
    test_remove_reference_ref<int(&&)(...) noexcept, int(...) noexcept>();

    test_remove_reference_ref<int(&&)(int, ...), int(int, ...)>();
    test_remove_reference_ref<int(&&)(int, ...) noexcept, int(int, ...) noexcept>();

    test_remove_reference<void (Class::*)()>();
    test_remove_reference<void (Class::*)()&>();
    test_remove_reference<void (Class::*)() &&>();
    test_remove_reference<void (Class::*)() const>();
    test_remove_reference<void (Class::*)() const&>();
    test_remove_reference<void (Class::*)() const&&>();
    test_remove_reference<void (Class::*)() noexcept>();
    test_remove_reference<void (Class::*)()& noexcept>();
    test_remove_reference<void (Class::*)()&& noexcept>();
    test_remove_reference<void (Class::*)() const noexcept>();
    test_remove_reference<void (Class::*)() const& noexcept>();
    test_remove_reference<void (Class::*)() const&& noexcept>();

    test_remove_reference<void (Class::*)(int)>();
    test_remove_reference<void (Class::*)(int)&>();
    test_remove_reference<void (Class::*)(int) &&>();
    test_remove_reference<void (Class::*)(int) const>();
    test_remove_reference<void (Class::*)(int) const&>();
    test_remove_reference<void (Class::*)(int) const&&>();
    test_remove_reference<void (Class::*)(int) noexcept>();
    test_remove_reference<void (Class::*)(int)& noexcept>();
    test_remove_reference<void (Class::*)(int)&& noexcept>();
    test_remove_reference<void (Class::*)(int) const noexcept>();
    test_remove_reference<void (Class::*)(int) const& noexcept>();
    test_remove_reference<void (Class::*)(int) const&& noexcept>();

    test_remove_reference<void (Class::*)(...)>();
    test_remove_reference<void (Class::*)(...)&>();
    test_remove_reference<void (Class::*)(...) &&>();
    test_remove_reference<void (Class::*)(...) const>();
    test_remove_reference<void (Class::*)(...) const&>();
    test_remove_reference<void (Class::*)(...) const&&>();
    test_remove_reference<void (Class::*)(...) noexcept>();
    test_remove_reference<void (Class::*)(...)& noexcept>();
    test_remove_reference<void (Class::*)(...)&& noexcept>();
    test_remove_reference<void (Class::*)(...) const noexcept>();
    test_remove_reference<void (Class::*)(...) const& noexcept>();
    test_remove_reference<void (Class::*)(...) const&& noexcept>();

    test_remove_reference<void (Class::*)(int, ...)>();
    test_remove_reference<void (Class::*)(int, ...)&>();
    test_remove_reference<void (Class::*)(int, ...) &&>();
    test_remove_reference<void (Class::*)(int, ...) const>();
    test_remove_reference<void (Class::*)(int, ...) const&>();
    test_remove_reference<void (Class::*)(int, ...) const&&>();
    test_remove_reference<void (Class::*)(int, ...) noexcept>();
    test_remove_reference<void (Class::*)(int, ...)& noexcept>();
    test_remove_reference<void (Class::*)(int, ...)&& noexcept>();
    test_remove_reference<void (Class::*)(int, ...) const noexcept>();
    test_remove_reference<void (Class::*)(int, ...) const& noexcept>();
    test_remove_reference<void (Class::*)(int, ...) const&& noexcept>();

    test_remove_reference<int (Class::*)()>();
    test_remove_reference<int (Class::*)()&>();
    test_remove_reference<int (Class::*)() &&>();
    test_remove_reference<int (Class::*)() const>();
    test_remove_reference<int (Class::*)() const&>();
    test_remove_reference<int (Class::*)() const&&>();
    test_remove_reference<int (Class::*)() noexcept>();
    test_remove_reference<int (Class::*)()& noexcept>();
    test_remove_reference<int (Class::*)()&& noexcept>();
    test_remove_reference<int (Class::*)() const noexcept>();
    test_remove_reference<int (Class::*)() const& noexcept>();
    test_remove_reference<int (Class::*)() const&& noexcept>();

    test_remove_reference<int (Class::*)(int)>();
    test_remove_reference<int (Class::*)(int)&>();
    test_remove_reference<int (Class::*)(int) &&>();
    test_remove_reference<int (Class::*)(int) const>();
    test_remove_reference<int (Class::*)(int) const&>();
    test_remove_reference<int (Class::*)(int) const&&>();
    test_remove_reference<int (Class::*)(int) noexcept>();
    test_remove_reference<int (Class::*)(int)& noexcept>();
    test_remove_reference<int (Class::*)(int)&& noexcept>();
    test_remove_reference<int (Class::*)(int) const noexcept>();
    test_remove_reference<int (Class::*)(int) const& noexcept>();
    test_remove_reference<int (Class::*)(int) const&& noexcept>();

    test_remove_reference<int (Class::*)(...)>();
    test_remove_reference<int (Class::*)(...)&>();
    test_remove_reference<int (Class::*)(...) &&>();
    test_remove_reference<int (Class::*)(...) const>();
    test_remove_reference<int (Class::*)(...) const&>();
    test_remove_reference<int (Class::*)(...) const&&>();
    test_remove_reference<int (Class::*)(...) noexcept>();
    test_remove_reference<int (Class::*)(...)& noexcept>();
    test_remove_reference<int (Class::*)(...)&& noexcept>();
    test_remove_reference<int (Class::*)(...) const noexcept>();
    test_remove_reference<int (Class::*)(...) const& noexcept>();
    test_remove_reference<int (Class::*)(...) const&& noexcept>();

    test_remove_reference<int (Class::*)(int, ...)>();
    test_remove_reference<int (Class::*)(int, ...)&>();
    test_remove_reference<int (Class::*)(int, ...) &&>();
    test_remove_reference<int (Class::*)(int, ...) const>();
    test_remove_reference<int (Class::*)(int, ...) const&>();
    test_remove_reference<int (Class::*)(int, ...) const&&>();
    test_remove_reference<int (Class::*)(int, ...) noexcept>();
    test_remove_reference<int (Class::*)(int, ...)& noexcept>();
    test_remove_reference<int (Class::*)(int, ...)&& noexcept>();
    test_remove_reference<int (Class::*)(int, ...) const noexcept>();
    test_remove_reference<int (Class::*)(int, ...) const& noexcept>();
    test_remove_reference<int (Class::*)(int, ...) const&& noexcept>();
}
