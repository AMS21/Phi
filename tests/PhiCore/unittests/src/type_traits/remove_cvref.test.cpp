#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_cvref.hpp>
#include <vector>

template <typename T, typename U>
void test_remove_cvref_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_cvref<T>::type, U);
    CHECK_SAME_TYPE(phi::remove_cvref_t<T>, U);

    // Standard compatibililty
#if PHI_CPP_STANDARD_IS_ATLEAST(20)
    CHECK_SAME_TYPE(typename std::remove_cvref<T>::type, U);
#endif
}

template <typename T, typename U = T>
void test_remove_cvref()
{
    test_remove_cvref_impl<T, U>();
    test_remove_cvref_impl<const T, U>();
    test_remove_cvref_impl<volatile T, U>();
    test_remove_cvref_impl<const volatile T, U>();
}

TEST_CASE("remove_cvref")
{
    test_remove_cvref<void>();
    test_remove_cvref<phi::nullptr_t>();
    test_remove_cvref<bool>();
    test_remove_cvref<char>();
    test_remove_cvref<signed char>();
    test_remove_cvref<unsigned char>();
    test_remove_cvref<short>();
    test_remove_cvref<unsigned short>();
    test_remove_cvref<int>();
    test_remove_cvref<unsigned int>();
    test_remove_cvref<long>();
    test_remove_cvref<unsigned long>();
    test_remove_cvref<long long>();
    test_remove_cvref<unsigned long long>();
    test_remove_cvref<float>();
    test_remove_cvref<double>();
    test_remove_cvref<long double>();
    test_remove_cvref<char8_t>();
    test_remove_cvref<char16_t>();
    test_remove_cvref<char32_t>();
    test_remove_cvref<wchar_t>();

    test_remove_cvref<phi::boolean>();
    test_remove_cvref<phi::integer<signed char>>();
    test_remove_cvref<phi::integer<unsigned char>>();
    test_remove_cvref<phi::integer<short>>();
    test_remove_cvref<phi::integer<unsigned short>>();
    test_remove_cvref<phi::integer<int>>();
    test_remove_cvref<phi::integer<unsigned int>>();
    test_remove_cvref<phi::integer<long>>();
    test_remove_cvref<phi::integer<unsigned long>>();
    test_remove_cvref<phi::integer<long long>>();
    test_remove_cvref<phi::integer<unsigned long long>>();
    test_remove_cvref<phi::floating_point<float>>();
    test_remove_cvref<phi::floating_point<double>>();
    test_remove_cvref<phi::floating_point<long double>>();

    test_remove_cvref<std::vector<int>>();
    test_remove_cvref<phi::scope_ptr<int>>();

    test_remove_cvref<int&, int>();
    test_remove_cvref<const int&, int>();
    test_remove_cvref<volatile int&, int>();
    test_remove_cvref<const volatile int&, int>();
    test_remove_cvref<int&&, int>();
    test_remove_cvref<const int&&, int>();
    test_remove_cvref<volatile int&&, int>();
    test_remove_cvref<const volatile int&&, int>();
    test_remove_cvref<int*>();
    test_remove_cvref<const int*>();
    test_remove_cvref<volatile int*>();
    test_remove_cvref<const volatile int*>();
    test_remove_cvref<int**>();
    test_remove_cvref<const int**>();
    test_remove_cvref<volatile int**>();
    test_remove_cvref<const volatile int**>();
    test_remove_cvref<int*&, int*>();
    test_remove_cvref<const int*&, const int*>();
    test_remove_cvref<volatile int*&, volatile int*>();
    test_remove_cvref<const volatile int*&, const volatile int*>();
    test_remove_cvref<int*&&, int*>();
    test_remove_cvref<const int*&&, const int*>();
    test_remove_cvref<volatile int*&&, volatile int*>();
    test_remove_cvref<const volatile int*&&, const volatile int*>();
    test_remove_cvref<void*>();
    test_remove_cvref<char[3]>();
    test_remove_cvref<char[]>();
    test_remove_cvref<char* [3]>();
    test_remove_cvref<char*[]>();
    test_remove_cvref<int(*)[3]>();
    test_remove_cvref<int(*)[]>();
    test_remove_cvref<int(&)[3], int[3]>();
    test_remove_cvref<int(&)[], int[]>();
    test_remove_cvref<int(&&)[3], int[3]>();
    test_remove_cvref<int(&&)[], int[]>();
    test_remove_cvref<char[3][2]>();
    test_remove_cvref<char[][2]>();
    test_remove_cvref<char* [3][2]>();
    test_remove_cvref<char*[][2]>();
    test_remove_cvref<int(*)[3][2]>();
    test_remove_cvref<int(*)[][2]>();
    test_remove_cvref<int(&)[3][2], int[3][2]>();
    test_remove_cvref<int(&)[][2], int[][2]>();
    test_remove_cvref<int(&&)[3][2], int[3][2]>();
    test_remove_cvref<int(&&)[][2], int[][2]>();
    test_remove_cvref<Class>();
    test_remove_cvref<Class[]>();
    test_remove_cvref<Class[2]>();
    test_remove_cvref<Template<void>>();
    test_remove_cvref<Template<int>>();
    test_remove_cvref<Template<Class>>();
    test_remove_cvref<Template<IncompleteType>>();
    test_remove_cvref<VariadicTemplate<>>();
    test_remove_cvref<VariadicTemplate<void>>();
    test_remove_cvref<VariadicTemplate<int>>();
    test_remove_cvref<VariadicTemplate<Class>>();
    test_remove_cvref<VariadicTemplate<IncompleteType>>();
    test_remove_cvref<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_cvref<PublicDerivedFromTemplate<Base>>();
    test_remove_cvref<PublicDerivedFromTemplate<Derived>>();
    test_remove_cvref<PublicDerivedFromTemplate<Class>>();
    test_remove_cvref<PrivateDerivedFromTemplate<Base>>();
    test_remove_cvref<PrivateDerivedFromTemplate<Derived>>();
    test_remove_cvref<PrivateDerivedFromTemplate<Class>>();
    test_remove_cvref<ProtectedDerivedFromTemplate<Base>>();
    test_remove_cvref<ProtectedDerivedFromTemplate<Derived>>();
    test_remove_cvref<ProtectedDerivedFromTemplate<Class>>();
    test_remove_cvref<Union>();
    test_remove_cvref<NonEmptyUnion>();
    test_remove_cvref<Empty>();
    test_remove_cvref<NotEmpty>();
    test_remove_cvref<BitZero>();
    test_remove_cvref<BitOne>();
    test_remove_cvref<Base>();
    test_remove_cvref<Derived>();
    test_remove_cvref<Abstract>();
    test_remove_cvref<PublicAbstract>();
    test_remove_cvref<PrivateAbstract>();
    test_remove_cvref<ProtectedAbstract>();
    test_remove_cvref<AbstractTemplate<int>>();
    test_remove_cvref<AbstractTemplate<double>>();
    test_remove_cvref<AbstractTemplate<Class>>();
    test_remove_cvref<AbstractTemplate<IncompleteType>>();
    test_remove_cvref<Final>();
    test_remove_cvref<PublicDestructor>();
    test_remove_cvref<ProtectedDestructor>();
    test_remove_cvref<PrivateDestructor>();
    test_remove_cvref<VirtualPublicDestructor>();
    test_remove_cvref<VirtualProtectedDestructor>();
    test_remove_cvref<VirtualPrivateDestructor>();
    test_remove_cvref<PurePublicDestructor>();
    test_remove_cvref<PureProtectedDestructor>();
    test_remove_cvref<PurePrivateDestructor>();
    test_remove_cvref<DeletedPublicDestructor>();
    test_remove_cvref<DeletedProtectedDestructor>();
    test_remove_cvref<DeletedPrivateDestructor>();
    test_remove_cvref<DeletedVirtualPublicDestructor>();
    test_remove_cvref<DeletedVirtualProtectedDestructor>();
    test_remove_cvref<DeletedVirtualPrivateDestructor>();
    test_remove_cvref<Enum>();
    test_remove_cvref<EnumSigned>();
    test_remove_cvref<EnumUnsigned>();
    test_remove_cvref<EnumClass>();
    test_remove_cvref<EnumStruct>();
    test_remove_cvref<Function>();
    test_remove_cvref<FunctionPtr>();
    test_remove_cvref<MemberObjectPtr>();
    test_remove_cvref<MemberFunctionPtr>();
    test_remove_cvref<IncompleteType>();
    test_remove_cvref<IncompleteTemplate<void>>();
    test_remove_cvref<IncompleteTemplate<int>>();
    test_remove_cvref<IncompleteTemplate<Class>>();
    test_remove_cvref<IncompleteTemplate<IncompleteType>>();
    test_remove_cvref<IncompleteVariadicTemplate<>>();
    test_remove_cvref<IncompleteVariadicTemplate<void>>();
    test_remove_cvref<IncompleteVariadicTemplate<int>>();
    test_remove_cvref<IncompleteVariadicTemplate<Class>>();
    test_remove_cvref<IncompleteVariadicTemplate<IncompleteType>>();
    test_remove_cvref<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_cvref<int Class::*>();
    test_remove_cvref<float Class::*>();
    test_remove_cvref<void * Class::*>();
    test_remove_cvref<int * Class::*>();
    test_remove_cvref<int Class::*&, int Class::*>();
    test_remove_cvref<float Class::*&, float Class::*>();
    test_remove_cvref<void * Class::*&, void * Class::*>();
    test_remove_cvref<int * Class::*&, int * Class::*>();
    test_remove_cvref<int Class::*&&, int Class::*>();
    test_remove_cvref<float Class::*&&, float Class::*>();
    test_remove_cvref<void * Class::*&&, void * Class::*>();
    test_remove_cvref<int * Class::*&&, int * Class::*>();
    test_remove_cvref<int Class::*const, int Class::*>();
    test_remove_cvref<float Class::*const, float Class::*>();
    test_remove_cvref<void * Class::*const, void * Class::*>();
    test_remove_cvref<int Class::*const&, int Class::*>();
    test_remove_cvref<float Class::*const&, float Class::*>();
    test_remove_cvref<void * Class::*const&, void * Class::*>();
    test_remove_cvref<int Class::*const&&, int Class::*>();
    test_remove_cvref<float Class::*const&&, float Class::*>();
    test_remove_cvref<void * Class::*const&&, void * Class::*>();
    test_remove_cvref<int Class::*volatile, int Class::*>();
    test_remove_cvref<float Class::*volatile, float Class::*>();
    test_remove_cvref<void * Class::*volatile, void * Class::*>();
    test_remove_cvref<int Class::*volatile&, int Class::*>();
    test_remove_cvref<float Class::*volatile&, float Class::*>();
    test_remove_cvref<void * Class::*volatile&, void * Class::*>();
    test_remove_cvref<int Class::*volatile&&, int Class::*>();
    test_remove_cvref<float Class::*volatile&&, float Class::*>();
    test_remove_cvref<void * Class::*volatile&&, void * Class::*>();
    test_remove_cvref<int Class::*const volatile, int Class::*>();
    test_remove_cvref<float Class::*const volatile, float Class::*>();
    test_remove_cvref<void * Class::*const volatile, void * Class::*>();
    test_remove_cvref<int Class::*const volatile&, int Class::*>();
    test_remove_cvref<float Class::*const volatile&, float Class::*>();
    test_remove_cvref<void * Class::*const volatile&, void * Class::*>();
    test_remove_cvref<int Class::*const volatile&&, int Class::*>();
    test_remove_cvref<float Class::*const volatile&&, float Class::*>();
    test_remove_cvref<void * Class::*const volatile&&, void * Class::*>();
    test_remove_cvref<NonCopyable>();
    test_remove_cvref<NonMoveable>();
    test_remove_cvref<NonConstructible>();
    test_remove_cvref<Tracked>();
    test_remove_cvref<TrapConstructible>();
    test_remove_cvref<TrapImplicitConversion>();
    test_remove_cvref<TrapComma>();
    test_remove_cvref<TrapCall>();
    test_remove_cvref<TrapSelfAssign>();
    test_remove_cvref<TrapDeref>();
    test_remove_cvref<TrapArraySubscript>();

    test_remove_cvref<void()>();
    test_remove_cvref<void()&>();
    test_remove_cvref<void() &&>();
    test_remove_cvref<void() const>();
    test_remove_cvref<void() const&>();
    test_remove_cvref<void() const&&>();
    test_remove_cvref<void() volatile>();
    test_remove_cvref<void() volatile&>();
    test_remove_cvref<void() volatile&&>();
    test_remove_cvref<void() const volatile>();
    test_remove_cvref<void() const volatile&>();
    test_remove_cvref<void() const volatile&&>();
    test_remove_cvref<void() noexcept>();
    test_remove_cvref<void()& noexcept>();
    test_remove_cvref<void()&& noexcept>();
    test_remove_cvref<void() const noexcept>();
    test_remove_cvref<void() const& noexcept>();
    test_remove_cvref<void() const&& noexcept>();
    test_remove_cvref<void() volatile noexcept>();
    test_remove_cvref<void() volatile& noexcept>();
    test_remove_cvref<void() volatile&& noexcept>();
    test_remove_cvref<void() const volatile noexcept>();
    test_remove_cvref<void() const volatile& noexcept>();
    test_remove_cvref<void() const volatile&& noexcept>();

    test_remove_cvref<void(int)>();
    test_remove_cvref<void(int)&>();
    test_remove_cvref<void(int) &&>();
    test_remove_cvref<void(int) const>();
    test_remove_cvref<void(int) const&>();
    test_remove_cvref<void(int) const&&>();
    test_remove_cvref<void(int) volatile>();
    test_remove_cvref<void(int) volatile&>();
    test_remove_cvref<void(int) volatile&&>();
    test_remove_cvref<void(int) const volatile>();
    test_remove_cvref<void(int) const volatile&>();
    test_remove_cvref<void(int) const volatile&&>();
    test_remove_cvref<void(int) noexcept>();
    test_remove_cvref<void(int)& noexcept>();
    test_remove_cvref<void(int)&& noexcept>();
    test_remove_cvref<void(int) const noexcept>();
    test_remove_cvref<void(int) const& noexcept>();
    test_remove_cvref<void(int) const&& noexcept>();
    test_remove_cvref<void(int) volatile noexcept>();
    test_remove_cvref<void(int) volatile& noexcept>();
    test_remove_cvref<void(int) volatile&& noexcept>();
    test_remove_cvref<void(int) const volatile noexcept>();
    test_remove_cvref<void(int) const volatile& noexcept>();
    test_remove_cvref<void(int) const volatile&& noexcept>();

    test_remove_cvref<void(...)>();
    test_remove_cvref<void(...)&>();
    test_remove_cvref<void(...) &&>();
    test_remove_cvref<void(...) const>();
    test_remove_cvref<void(...) const&>();
    test_remove_cvref<void(...) const&&>();
    test_remove_cvref<void(...) volatile>();
    test_remove_cvref<void(...) volatile&>();
    test_remove_cvref<void(...) volatile&&>();
    test_remove_cvref<void(...) const volatile>();
    test_remove_cvref<void(...) const volatile&>();
    test_remove_cvref<void(...) const volatile&&>();
    test_remove_cvref<void(...) noexcept>();
    test_remove_cvref<void(...)& noexcept>();
    test_remove_cvref<void(...)&& noexcept>();
    test_remove_cvref<void(...) const noexcept>();
    test_remove_cvref<void(...) const& noexcept>();
    test_remove_cvref<void(...) const&& noexcept>();
    test_remove_cvref<void(...) volatile noexcept>();
    test_remove_cvref<void(...) volatile& noexcept>();
    test_remove_cvref<void(...) volatile&& noexcept>();
    test_remove_cvref<void(...) const volatile noexcept>();
    test_remove_cvref<void(...) const volatile& noexcept>();
    test_remove_cvref<void(...) const volatile&& noexcept>();

    test_remove_cvref<void(int, ...)>();
    test_remove_cvref<void(int, ...)&>();
    test_remove_cvref<void(int, ...) &&>();
    test_remove_cvref<void(int, ...) const>();
    test_remove_cvref<void(int, ...) const&>();
    test_remove_cvref<void(int, ...) const&&>();
    test_remove_cvref<void(int, ...) volatile>();
    test_remove_cvref<void(int, ...) volatile&>();
    test_remove_cvref<void(int, ...) volatile&&>();
    test_remove_cvref<void(int, ...) const volatile>();
    test_remove_cvref<void(int, ...) const volatile&>();
    test_remove_cvref<void(int, ...) const volatile&&>();
    test_remove_cvref<void(int, ...) noexcept>();
    test_remove_cvref<void(int, ...)& noexcept>();
    test_remove_cvref<void(int, ...)&& noexcept>();
    test_remove_cvref<void(int, ...) const noexcept>();
    test_remove_cvref<void(int, ...) const& noexcept>();
    test_remove_cvref<void(int, ...) const&& noexcept>();
    test_remove_cvref<void(int, ...) volatile noexcept>();
    test_remove_cvref<void(int, ...) volatile& noexcept>();
    test_remove_cvref<void(int, ...) volatile&& noexcept>();
    test_remove_cvref<void(int, ...) const volatile noexcept>();
    test_remove_cvref<void(int, ...) const volatile& noexcept>();
    test_remove_cvref<void(int, ...) const volatile&& noexcept>();

    test_remove_cvref<int()>();
    test_remove_cvref<int()&>();
    test_remove_cvref<int() &&>();
    test_remove_cvref<int() const>();
    test_remove_cvref<int() const&>();
    test_remove_cvref<int() const&&>();
    test_remove_cvref<int() volatile>();
    test_remove_cvref<int() volatile&>();
    test_remove_cvref<int() volatile&&>();
    test_remove_cvref<int() const volatile>();
    test_remove_cvref<int() const volatile&>();
    test_remove_cvref<int() const volatile&&>();
    test_remove_cvref<int() noexcept>();
    test_remove_cvref<int()& noexcept>();
    test_remove_cvref<int()&& noexcept>();
    test_remove_cvref<int() const noexcept>();
    test_remove_cvref<int() const& noexcept>();
    test_remove_cvref<int() const&& noexcept>();
    test_remove_cvref<int() volatile noexcept>();
    test_remove_cvref<int() volatile& noexcept>();
    test_remove_cvref<int() volatile&& noexcept>();
    test_remove_cvref<int() const volatile noexcept>();
    test_remove_cvref<int() const volatile& noexcept>();
    test_remove_cvref<int() const volatile&& noexcept>();

    test_remove_cvref<int(int)>();
    test_remove_cvref<int(int)&>();
    test_remove_cvref<int(int) &&>();
    test_remove_cvref<int(int) const>();
    test_remove_cvref<int(int) const&>();
    test_remove_cvref<int(int) const&&>();
    test_remove_cvref<int(int) volatile>();
    test_remove_cvref<int(int) volatile&>();
    test_remove_cvref<int(int) volatile&&>();
    test_remove_cvref<int(int) const volatile>();
    test_remove_cvref<int(int) const volatile&>();
    test_remove_cvref<int(int) const volatile&&>();
    test_remove_cvref<int(int) noexcept>();
    test_remove_cvref<int(int)& noexcept>();
    test_remove_cvref<int(int)&& noexcept>();
    test_remove_cvref<int(int) const noexcept>();
    test_remove_cvref<int(int) const& noexcept>();
    test_remove_cvref<int(int) const&& noexcept>();
    test_remove_cvref<int(int) volatile noexcept>();
    test_remove_cvref<int(int) volatile& noexcept>();
    test_remove_cvref<int(int) volatile&& noexcept>();
    test_remove_cvref<int(int) const volatile noexcept>();
    test_remove_cvref<int(int) const volatile& noexcept>();
    test_remove_cvref<int(int) const volatile&& noexcept>();

    test_remove_cvref<int(...)>();
    test_remove_cvref<int(...)&>();
    test_remove_cvref<int(...) &&>();
    test_remove_cvref<int(...) const>();
    test_remove_cvref<int(...) const&>();
    test_remove_cvref<int(...) const&&>();
    test_remove_cvref<int(...) volatile>();
    test_remove_cvref<int(...) volatile&>();
    test_remove_cvref<int(...) volatile&&>();
    test_remove_cvref<int(...) const volatile>();
    test_remove_cvref<int(...) const volatile&>();
    test_remove_cvref<int(...) const volatile&&>();
    test_remove_cvref<int(...) noexcept>();
    test_remove_cvref<int(...)& noexcept>();
    test_remove_cvref<int(...)&& noexcept>();
    test_remove_cvref<int(...) const noexcept>();
    test_remove_cvref<int(...) const& noexcept>();
    test_remove_cvref<int(...) const&& noexcept>();
    test_remove_cvref<int(...) volatile noexcept>();
    test_remove_cvref<int(...) volatile& noexcept>();
    test_remove_cvref<int(...) volatile&& noexcept>();
    test_remove_cvref<int(...) const volatile noexcept>();
    test_remove_cvref<int(...) const volatile& noexcept>();
    test_remove_cvref<int(...) const volatile&& noexcept>();

    test_remove_cvref<int(int, ...)>();
    test_remove_cvref<int(int, ...)&>();
    test_remove_cvref<int(int, ...) &&>();
    test_remove_cvref<int(int, ...) const>();
    test_remove_cvref<int(int, ...) const&>();
    test_remove_cvref<int(int, ...) const&&>();
    test_remove_cvref<int(int, ...) volatile>();
    test_remove_cvref<int(int, ...) volatile&>();
    test_remove_cvref<int(int, ...) volatile&&>();
    test_remove_cvref<int(int, ...) const volatile>();
    test_remove_cvref<int(int, ...) const volatile&>();
    test_remove_cvref<int(int, ...) const volatile&&>();
    test_remove_cvref<int(int, ...) noexcept>();
    test_remove_cvref<int(int, ...)& noexcept>();
    test_remove_cvref<int(int, ...)&& noexcept>();
    test_remove_cvref<int(int, ...) const noexcept>();
    test_remove_cvref<int(int, ...) const& noexcept>();
    test_remove_cvref<int(int, ...) const&& noexcept>();
    test_remove_cvref<int(int, ...) volatile noexcept>();
    test_remove_cvref<int(int, ...) volatile& noexcept>();
    test_remove_cvref<int(int, ...) volatile&& noexcept>();
    test_remove_cvref<int(int, ...) const volatile noexcept>();
    test_remove_cvref<int(int, ...) const volatile& noexcept>();
    test_remove_cvref<int(int, ...) const volatile&& noexcept>();

    test_remove_cvref<void (*)()>();
    test_remove_cvref<void (*)() noexcept>();

    test_remove_cvref<void (*)(int)>();
    test_remove_cvref<void (*)(int) noexcept>();

    test_remove_cvref<void (*)(...)>();
    test_remove_cvref<void (*)(...) noexcept>();

    test_remove_cvref<void (*)(int, ...)>();
    test_remove_cvref<void (*)(int, ...) noexcept>();

    test_remove_cvref<int (*)()>();
    test_remove_cvref<int (*)() noexcept>();

    test_remove_cvref<int (*)(int)>();
    test_remove_cvref<int (*)(int) noexcept>();

    test_remove_cvref<int (*)(...)>();
    test_remove_cvref<int (*)(...) noexcept>();

    test_remove_cvref<int (*)(int, ...)>();
    test_remove_cvref<int (*)(int, ...) noexcept>();

    test_remove_cvref<void (&)(), void()>();
    test_remove_cvref<void (&)() noexcept, void() noexcept>();

    test_remove_cvref<void (&)(int), void(int)>();
    test_remove_cvref<void (&)(int) noexcept, void(int) noexcept>();

    test_remove_cvref<void (&)(...), void(...)>();
    test_remove_cvref<void (&)(...) noexcept, void(...) noexcept>();

    test_remove_cvref<void (&)(int, ...), void(int, ...)>();
    test_remove_cvref<void (&)(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_cvref<int (&)(), int()>();
    test_remove_cvref<int (&)() noexcept, int() noexcept>();

    test_remove_cvref<int (&)(int), int(int)>();
    test_remove_cvref<int (&)(int) noexcept, int(int) noexcept>();

    test_remove_cvref<int (&)(...), int(...)>();
    test_remove_cvref<int (&)(...) noexcept, int(...) noexcept>();

    test_remove_cvref<int (&)(int, ...), int(int, ...)>();
    test_remove_cvref<int (&)(int, ...) noexcept, int(int, ...) noexcept>();

    test_remove_cvref<void(&&)(), void()>();
    test_remove_cvref<void(&&)() noexcept, void() noexcept>();

    test_remove_cvref<void(&&)(int), void(int)>();
    test_remove_cvref<void(&&)(int) noexcept, void(int) noexcept>();

    test_remove_cvref<void(&&)(...), void(...)>();
    test_remove_cvref<void(&&)(...) noexcept, void(...) noexcept>();

    test_remove_cvref<void(&&)(int, ...), void(int, ...)>();
    test_remove_cvref<void(&&)(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_cvref<int(&&)(), int()>();
    test_remove_cvref<int(&&)() noexcept, int() noexcept>();

    test_remove_cvref<int(&&)(int), int(int)>();
    test_remove_cvref<int(&&)(int) noexcept, int(int) noexcept>();

    test_remove_cvref<int(&&)(...), int(...)>();
    test_remove_cvref<int(&&)(...) noexcept, int(...) noexcept>();

    test_remove_cvref<int(&&)(int, ...), int(int, ...)>();
    test_remove_cvref<int(&&)(int, ...) noexcept, int(int, ...) noexcept>();

    test_remove_cvref<void (Class::*)()>();
    test_remove_cvref<void (Class::*)()&>();
    test_remove_cvref<void (Class::*)() &&>();
    test_remove_cvref<void (Class::*)() const>();
    test_remove_cvref<void (Class::*)() const&>();
    test_remove_cvref<void (Class::*)() const&&>();
    test_remove_cvref<void (Class::*)() noexcept>();
    test_remove_cvref<void (Class::*)()& noexcept>();
    test_remove_cvref<void (Class::*)()&& noexcept>();
    test_remove_cvref<void (Class::*)() const noexcept>();
    test_remove_cvref<void (Class::*)() const& noexcept>();
    test_remove_cvref<void (Class::*)() const&& noexcept>();

    test_remove_cvref<void (Class::*)(int)>();
    test_remove_cvref<void (Class::*)(int)&>();
    test_remove_cvref<void (Class::*)(int) &&>();
    test_remove_cvref<void (Class::*)(int) const>();
    test_remove_cvref<void (Class::*)(int) const&>();
    test_remove_cvref<void (Class::*)(int) const&&>();
    test_remove_cvref<void (Class::*)(int) noexcept>();
    test_remove_cvref<void (Class::*)(int)& noexcept>();
    test_remove_cvref<void (Class::*)(int)&& noexcept>();
    test_remove_cvref<void (Class::*)(int) const noexcept>();
    test_remove_cvref<void (Class::*)(int) const& noexcept>();
    test_remove_cvref<void (Class::*)(int) const&& noexcept>();

    test_remove_cvref<void (Class::*)(...)>();
    test_remove_cvref<void (Class::*)(...)&>();
    test_remove_cvref<void (Class::*)(...) &&>();
    test_remove_cvref<void (Class::*)(...) const>();
    test_remove_cvref<void (Class::*)(...) const&>();
    test_remove_cvref<void (Class::*)(...) const&&>();
    test_remove_cvref<void (Class::*)(...) noexcept>();
    test_remove_cvref<void (Class::*)(...)& noexcept>();
    test_remove_cvref<void (Class::*)(...)&& noexcept>();
    test_remove_cvref<void (Class::*)(...) const noexcept>();
    test_remove_cvref<void (Class::*)(...) const& noexcept>();
    test_remove_cvref<void (Class::*)(...) const&& noexcept>();

    test_remove_cvref<void (Class::*)(int, ...)>();
    test_remove_cvref<void (Class::*)(int, ...)&>();
    test_remove_cvref<void (Class::*)(int, ...) &&>();
    test_remove_cvref<void (Class::*)(int, ...) const>();
    test_remove_cvref<void (Class::*)(int, ...) const&>();
    test_remove_cvref<void (Class::*)(int, ...) const&&>();
    test_remove_cvref<void (Class::*)(int, ...) noexcept>();
    test_remove_cvref<void (Class::*)(int, ...)& noexcept>();
    test_remove_cvref<void (Class::*)(int, ...)&& noexcept>();
    test_remove_cvref<void (Class::*)(int, ...) const noexcept>();
    test_remove_cvref<void (Class::*)(int, ...) const& noexcept>();
    test_remove_cvref<void (Class::*)(int, ...) const&& noexcept>();

    test_remove_cvref<int (Class::*)()>();
    test_remove_cvref<int (Class::*)()&>();
    test_remove_cvref<int (Class::*)() &&>();
    test_remove_cvref<int (Class::*)() const>();
    test_remove_cvref<int (Class::*)() const&>();
    test_remove_cvref<int (Class::*)() const&&>();
    test_remove_cvref<int (Class::*)() noexcept>();
    test_remove_cvref<int (Class::*)()& noexcept>();
    test_remove_cvref<int (Class::*)()&& noexcept>();
    test_remove_cvref<int (Class::*)() const noexcept>();
    test_remove_cvref<int (Class::*)() const& noexcept>();
    test_remove_cvref<int (Class::*)() const&& noexcept>();

    test_remove_cvref<int (Class::*)(int)>();
    test_remove_cvref<int (Class::*)(int)&>();
    test_remove_cvref<int (Class::*)(int) &&>();
    test_remove_cvref<int (Class::*)(int) const>();
    test_remove_cvref<int (Class::*)(int) const&>();
    test_remove_cvref<int (Class::*)(int) const&&>();
    test_remove_cvref<int (Class::*)(int) noexcept>();
    test_remove_cvref<int (Class::*)(int)& noexcept>();
    test_remove_cvref<int (Class::*)(int)&& noexcept>();
    test_remove_cvref<int (Class::*)(int) const noexcept>();
    test_remove_cvref<int (Class::*)(int) const& noexcept>();
    test_remove_cvref<int (Class::*)(int) const&& noexcept>();

    test_remove_cvref<int (Class::*)(...)>();
    test_remove_cvref<int (Class::*)(...)&>();
    test_remove_cvref<int (Class::*)(...) &&>();
    test_remove_cvref<int (Class::*)(...) const>();
    test_remove_cvref<int (Class::*)(...) const&>();
    test_remove_cvref<int (Class::*)(...) const&&>();
    test_remove_cvref<int (Class::*)(...) noexcept>();
    test_remove_cvref<int (Class::*)(...)& noexcept>();
    test_remove_cvref<int (Class::*)(...)&& noexcept>();
    test_remove_cvref<int (Class::*)(...) const noexcept>();
    test_remove_cvref<int (Class::*)(...) const& noexcept>();
    test_remove_cvref<int (Class::*)(...) const&& noexcept>();

    test_remove_cvref<int (Class::*)(int, ...)>();
    test_remove_cvref<int (Class::*)(int, ...)&>();
    test_remove_cvref<int (Class::*)(int, ...) &&>();
    test_remove_cvref<int (Class::*)(int, ...) const>();
    test_remove_cvref<int (Class::*)(int, ...) const&>();
    test_remove_cvref<int (Class::*)(int, ...) const&&>();
    test_remove_cvref<int (Class::*)(int, ...) noexcept>();
    test_remove_cvref<int (Class::*)(int, ...)& noexcept>();
    test_remove_cvref<int (Class::*)(int, ...)&& noexcept>();
    test_remove_cvref<int (Class::*)(int, ...) const noexcept>();
    test_remove_cvref<int (Class::*)(int, ...) const& noexcept>();
    test_remove_cvref<int (Class::*)(int, ...) const&& noexcept>();
}
