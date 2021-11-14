#include <catch2/catch.hpp>

#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/decay.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U = T>
void test_decay()
{
    CHECK_SAME_TYPE(U, typename phi::decay<T>::type);
    CHECK_SAME_TYPE(U, phi::decay_t<T>);

    // Standard compatbility
    CHECK_SAME_TYPE(typename phi::decay<T>::type, typename std::decay<T>::type);
}

class A
{};

TEST_CASE("decay")
{
    test_decay<A>();
    test_decay<const int, int>();
    test_decay<volatile int, int>();
    test_decay<const volatile int, int>();

    test_decay<int*, int*>();
    test_decay<const int*, const int*>();
    test_decay<volatile int*, volatile int*>();
    test_decay<const volatile int*, const volatile int*>();
    test_decay<int[], int*>();
    test_decay<const int[], const int*>();
    test_decay<volatile int[], volatile int*>();
    test_decay<const volatile int[], const volatile int*>();
    test_decay<int[3], int*>();
    test_decay<const int[3], const int*>();
    test_decay<volatile int[3], volatile int*>();
    test_decay<const volatile int[3], const volatile int*>();

    test_decay<int**, int**>();
    test_decay<const int**, const int**>();
    test_decay<volatile int**, volatile int**>();
    test_decay<const volatile int**, const volatile int**>();
    test_decay<int[3][2], int(*)[2]>();
    test_decay<const int[3][2], int const(*)[2]>();
    test_decay<volatile int[3][2], volatile int(*)[2]>();
    test_decay<const volatile int[3][2], const volatile int(*)[2]>();

    test_decay<void>();
    test_decay<phi::nullptr_t>();
    test_decay<bool>();
    test_decay<char>();
    test_decay<signed char>();
    test_decay<unsigned char>();
    test_decay<short>();
    test_decay<unsigned short>();
    test_decay<int>();
    test_decay<unsigned int>();
    test_decay<long>();
    test_decay<unsigned long>();
    test_decay<long long>();
    test_decay<unsigned long long>();
    test_decay<float>();
    test_decay<double>();
    test_decay<long double>();
    test_decay<char8_t>();
    test_decay<char16_t>();
    test_decay<char32_t>();
    test_decay<wchar_t>();

    test_decay<phi::Boolean>();
    test_decay<phi::Integer<signed char>>();
    test_decay<phi::Integer<unsigned char>>();
    test_decay<phi::Integer<short>>();
    test_decay<phi::Integer<unsigned short>>();
    test_decay<phi::Integer<int>>();
    test_decay<phi::Integer<unsigned int>>();
    test_decay<phi::Integer<long>>();
    test_decay<phi::Integer<unsigned long>>();
    test_decay<phi::Integer<long long>>();
    test_decay<phi::Integer<unsigned long long>>();
    test_decay<phi::FloatingPoint<float>>();
    test_decay<phi::FloatingPoint<double>>();
    test_decay<phi::FloatingPoint<long double>>();

    test_decay<std::vector<int>>();
    test_decay<phi::ScopePtr<int>>();

    test_decay<int&, int>();
    test_decay<const int&, int>();
    test_decay<volatile int&, int>();
    test_decay<const volatile int&, int>();
    test_decay<int&&, int>();
    test_decay<const int&&, int>();
    test_decay<volatile int&&, int>();
    test_decay<const volatile int&&, int>();
    test_decay<int*>();
    test_decay<const int*>();
    test_decay<volatile int*>();
    test_decay<const volatile int*>();
    test_decay<int**>();
    test_decay<const int**>();
    test_decay<volatile int**>();
    test_decay<const volatile int**>();
    test_decay<int*&, int*>();
    test_decay<const int*&, const int*>();
    test_decay<volatile int*&, volatile int*>();
    test_decay<const volatile int*&, const volatile int*>();
    test_decay<int*&&, int*>();
    test_decay<const int*&&, const int*>();
    test_decay<volatile int*&&, volatile int*>();
    test_decay<const volatile int*&&, const volatile int*>();
    test_decay<void*>();
    test_decay<char[3], char*>();
    test_decay<char[], char*>();
    test_decay<char* [3], char**>();
    test_decay<char*[], char**>();
    test_decay<int(*)[3]>();
    test_decay<int(*)[]>();
    test_decay<int(&)[3], int*>();
    test_decay<int(&)[], int*>();
    test_decay<int(&&)[3], int*>();
    test_decay<int(&&)[], int*>();
    test_decay<char[3][2], char(*)[2]>();
    test_decay<char[][2], char(*)[2]>();
    test_decay<char* [3][2], char*(*)[2]>();
    test_decay<char*[][2], char*(*)[2]>();
    test_decay<int(*)[3][2]>();
    test_decay<int(*)[][2]>();
    test_decay<int(&)[3][2], int(*)[2]>();
    test_decay<int(&)[][2], int(*)[2]>();
    test_decay<int(&&)[3][2], int(*)[2]>();
    test_decay<int(&&)[][2], int(*)[2]>();
    test_decay<Class>();
    test_decay<Class[], Class*>();
    test_decay<Class[2], Class*>();
    test_decay<Template<void>>();
    test_decay<Template<int>>();
    test_decay<Template<Class>>();
    test_decay<Template<incomplete_type>>();
    test_decay<VariadicTemplate<>>();
    test_decay<VariadicTemplate<void>>();
    test_decay<VariadicTemplate<int>>();
    test_decay<VariadicTemplate<Class>>();
    test_decay<VariadicTemplate<incomplete_type>>();
    test_decay<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_decay<PublicDerviedFromTemplate<Base>>();
    test_decay<PublicDerviedFromTemplate<Derived>>();
    test_decay<PublicDerviedFromTemplate<Class>>();
    test_decay<PrivateDerviedFromTemplate<Base>>();
    test_decay<PrivateDerviedFromTemplate<Derived>>();
    test_decay<PrivateDerviedFromTemplate<Class>>();
    test_decay<ProtectedDerviedFromTemplate<Base>>();
    test_decay<ProtectedDerviedFromTemplate<Derived>>();
    test_decay<ProtectedDerviedFromTemplate<Class>>();
    test_decay<Union>();
    test_decay<NonEmptyUnion>();
    test_decay<Empty>();
    test_decay<NotEmpty>();
    test_decay<bit_zero>();
    test_decay<bit_one>();
    test_decay<Base>();
    test_decay<Derived>();
    test_decay<Abstract>();
    test_decay<PublicAbstract>();
    test_decay<PrivateAbstract>();
    test_decay<ProtectedAbstract>();
    test_decay<AbstractTemplate<int>>();
    test_decay<AbstractTemplate<double>>();
    test_decay<AbstractTemplate<Class>>();
    test_decay<AbstractTemplate<incomplete_type>>();
    test_decay<Final>();
    test_decay<PublicDestructor>();
    test_decay<ProtectedDestructor>();
    test_decay<PrivateDestructor>();
    test_decay<VirtualPublicDestructor>();
    test_decay<VirtualProtectedDestructor>();
    test_decay<VirtualPrivateDestructor>();
    test_decay<PurePublicDestructor>();
    test_decay<PureProtectedDestructor>();
    test_decay<PurePrivateDestructor>();
    test_decay<DeletedPublicDestructor>();
    test_decay<DeletedProtectedDestructor>();
    test_decay<DeletedPrivateDestructor>();
    test_decay<DeletedVirtualPublicDestructor>();
    test_decay<DeletedVirtualProtectedDestructor>();
    test_decay<DeletedVirtualPrivateDestructor>();
    test_decay<Enum>();
    test_decay<EnumSigned>();
    test_decay<EnumUnsigned>();
    test_decay<EnumClass>();
    test_decay<EnumStruct>();
    test_decay<Function, FunctionPtr>();
    test_decay<FunctionPtr>();
    test_decay<MemberObjectPtr>();
    test_decay<MemberFunctionPtr>();
    test_decay<incomplete_type>();
    test_decay<IncompleteTemplate<void>>();
    test_decay<IncompleteTemplate<int>>();
    test_decay<IncompleteTemplate<Class>>();
    test_decay<IncompleteTemplate<incomplete_type>>();
    test_decay<IncompleteVariadicTemplate<>>();
    test_decay<IncompleteVariadicTemplate<void>>();
    test_decay<IncompleteVariadicTemplate<int>>();
    test_decay<IncompleteVariadicTemplate<Class>>();
    test_decay<IncompleteVariadicTemplate<incomplete_type>>();
    test_decay<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_decay<int Class::*>();
    test_decay<float Class::*>();
    test_decay<void * Class::*>();
    test_decay<int * Class::*>();
    test_decay<int Class::*&, int Class::*>();
    test_decay<float Class::*&, float Class::*>();
    test_decay<void * Class::*&, void * Class::*>();
    test_decay<int * Class::*&, int * Class::*>();
    test_decay<int Class::*&&, int Class::*>();
    test_decay<float Class::*&&, float Class::*>();
    test_decay<void * Class::*&&, void * Class::*>();
    test_decay<int * Class::*&&, int * Class::*>();
    test_decay<int Class::*const, int Class::*>();
    test_decay<float Class::*const, float Class::*>();
    test_decay<void * Class::*const, void * Class::*>();
    test_decay<int Class::*const&, int Class::*>();
    test_decay<float Class::*const&, float Class::*>();
    test_decay<void * Class::*const&, void * Class::*>();
    test_decay<int Class::*const&&, int Class::*>();
    test_decay<float Class::*const&&, float Class::*>();
    test_decay<void * Class::*const&&, void * Class::*>();
    test_decay<int Class::*volatile, int Class::*>();
    test_decay<float Class::*volatile, float Class::*>();
    test_decay<void * Class::*volatile, void * Class::*>();
    test_decay<int Class::*volatile&, int Class::*>();
    test_decay<float Class::*volatile&, float Class::*>();
    test_decay<void * Class::*volatile&, void * Class::*>();
    test_decay<int Class::*volatile&&, int Class::*>();
    test_decay<float Class::*volatile&&, float Class::*>();
    test_decay<void * Class::*volatile&&, void * Class::*>();
    test_decay<int Class::*const volatile, int Class::*>();
    test_decay<float Class::*const volatile, float Class::*>();
    test_decay<void * Class::*const volatile, void * Class::*>();
    test_decay<int Class::*const volatile&, int Class::*>();
    test_decay<float Class::*const volatile&, float Class::*>();
    test_decay<void * Class::*const volatile&, void * Class::*>();
    test_decay<int Class::*const volatile&&, int Class::*>();
    test_decay<float Class::*const volatile&&, float Class::*>();
    test_decay<void * Class::*const volatile&&, void * Class::*>();
    test_decay<NonCopyable>();
    test_decay<NonMoveable>();
    test_decay<NonConstructible>();
    test_decay<Tracked>();
    test_decay<TrapConstructible>();
    test_decay<TrapImplicitConversion>();
    test_decay<TrapComma>();
    test_decay<TrapCall>();
    test_decay<TrapSelfAssign>();
    test_decay<TrapDeref>();
    test_decay<TrapArraySubscript>();

    test_decay<void(), void (*)()>();
    test_decay<void()&>();
    test_decay<void() &&>();
    test_decay<void() const>();
    test_decay<void() const&>();
    test_decay<void() const&&>();
    test_decay<void() volatile>();
    test_decay<void() volatile&>();
    test_decay<void() volatile&&>();
    test_decay<void() const volatile>();
    test_decay<void() const volatile&>();
    test_decay<void() const volatile&&>();
    test_decay<void() noexcept, void (*)() noexcept>();
    test_decay<void()& noexcept>();
    test_decay<void()&& noexcept>();
    test_decay<void() const noexcept>();
    test_decay<void() const& noexcept>();
    test_decay<void() const&& noexcept>();
    test_decay<void() volatile noexcept>();
    test_decay<void() volatile& noexcept>();
    test_decay<void() volatile&& noexcept>();
    test_decay<void() const volatile noexcept>();
    test_decay<void() const volatile& noexcept>();
    test_decay<void() const volatile&& noexcept>();

    test_decay<void(int), void (*)(int)>();
    test_decay<void(int)&>();
    test_decay<void(int) &&>();
    test_decay<void(int) const>();
    test_decay<void(int) const&>();
    test_decay<void(int) const&&>();
    test_decay<void(int) volatile>();
    test_decay<void(int) volatile&>();
    test_decay<void(int) volatile&&>();
    test_decay<void(int) const volatile>();
    test_decay<void(int) const volatile&>();
    test_decay<void(int) const volatile&&>();
    test_decay<void(int) noexcept, void (*)(int) noexcept>();
    test_decay<void(int)& noexcept>();
    test_decay<void(int)&& noexcept>();
    test_decay<void(int) const noexcept>();
    test_decay<void(int) const& noexcept>();
    test_decay<void(int) const&& noexcept>();
    test_decay<void(int) volatile noexcept>();
    test_decay<void(int) volatile& noexcept>();
    test_decay<void(int) volatile&& noexcept>();
    test_decay<void(int) const volatile noexcept>();
    test_decay<void(int) const volatile& noexcept>();
    test_decay<void(int) const volatile&& noexcept>();

    test_decay<void(...), void (*)(...)>();
    test_decay<void(...)&>();
    test_decay<void(...) &&>();
    test_decay<void(...) const>();
    test_decay<void(...) const&>();
    test_decay<void(...) const&&>();
    test_decay<void(...) volatile>();
    test_decay<void(...) volatile&>();
    test_decay<void(...) volatile&&>();
    test_decay<void(...) const volatile>();
    test_decay<void(...) const volatile&>();
    test_decay<void(...) const volatile&&>();
    test_decay<void(...) noexcept, void (*)(...) noexcept>();
    test_decay<void(...)& noexcept>();
    test_decay<void(...)&& noexcept>();
    test_decay<void(...) const noexcept>();
    test_decay<void(...) const& noexcept>();
    test_decay<void(...) const&& noexcept>();
    test_decay<void(...) volatile noexcept>();
    test_decay<void(...) volatile& noexcept>();
    test_decay<void(...) volatile&& noexcept>();
    test_decay<void(...) const volatile noexcept>();
    test_decay<void(...) const volatile& noexcept>();
    test_decay<void(...) const volatile&& noexcept>();

    test_decay<void(int, ...), void (*)(int, ...)>();
    test_decay<void(int, ...)&>();
    test_decay<void(int, ...) &&>();
    test_decay<void(int, ...) const>();
    test_decay<void(int, ...) const&>();
    test_decay<void(int, ...) const&&>();
    test_decay<void(int, ...) volatile>();
    test_decay<void(int, ...) volatile&>();
    test_decay<void(int, ...) volatile&&>();
    test_decay<void(int, ...) const volatile>();
    test_decay<void(int, ...) const volatile&>();
    test_decay<void(int, ...) const volatile&&>();
    test_decay<void(int, ...) noexcept, void (*)(int, ...) noexcept>();
    test_decay<void(int, ...)& noexcept>();
    test_decay<void(int, ...)&& noexcept>();
    test_decay<void(int, ...) const noexcept>();
    test_decay<void(int, ...) const& noexcept>();
    test_decay<void(int, ...) const&& noexcept>();
    test_decay<void(int, ...) volatile noexcept>();
    test_decay<void(int, ...) volatile& noexcept>();
    test_decay<void(int, ...) volatile&& noexcept>();
    test_decay<void(int, ...) const volatile noexcept>();
    test_decay<void(int, ...) const volatile& noexcept>();
    test_decay<void(int, ...) const volatile&& noexcept>();

    test_decay<int(), int (*)()>();
    test_decay<int()&>();
    test_decay<int() &&>();
    test_decay<int() const>();
    test_decay<int() const&>();
    test_decay<int() const&&>();
    test_decay<int() volatile>();
    test_decay<int() volatile&>();
    test_decay<int() volatile&&>();
    test_decay<int() const volatile>();
    test_decay<int() const volatile&>();
    test_decay<int() const volatile&&>();
    test_decay<int() noexcept, int (*)() noexcept>();
    test_decay<int()& noexcept>();
    test_decay<int()&& noexcept>();
    test_decay<int() const noexcept>();
    test_decay<int() const& noexcept>();
    test_decay<int() const&& noexcept>();
    test_decay<int() volatile noexcept>();
    test_decay<int() volatile& noexcept>();
    test_decay<int() volatile&& noexcept>();
    test_decay<int() const volatile noexcept>();
    test_decay<int() const volatile& noexcept>();
    test_decay<int() const volatile&& noexcept>();

    test_decay<int(int), int (*)(int)>();
    test_decay<int(int)&>();
    test_decay<int(int) &&>();
    test_decay<int(int) const>();
    test_decay<int(int) const&>();
    test_decay<int(int) const&&>();
    test_decay<int(int) volatile>();
    test_decay<int(int) volatile&>();
    test_decay<int(int) volatile&&>();
    test_decay<int(int) const volatile>();
    test_decay<int(int) const volatile&>();
    test_decay<int(int) const volatile&&>();
    test_decay<int(int) noexcept, int (*)(int) noexcept>();
    test_decay<int(int)& noexcept>();
    test_decay<int(int)&& noexcept>();
    test_decay<int(int) const noexcept>();
    test_decay<int(int) const& noexcept>();
    test_decay<int(int) const&& noexcept>();
    test_decay<int(int) volatile noexcept>();
    test_decay<int(int) volatile& noexcept>();
    test_decay<int(int) volatile&& noexcept>();
    test_decay<int(int) const volatile noexcept>();
    test_decay<int(int) const volatile& noexcept>();
    test_decay<int(int) const volatile&& noexcept>();

    test_decay<int(...), int (*)(...)>();
    test_decay<int(...)&>();
    test_decay<int(...) &&>();
    test_decay<int(...) const>();
    test_decay<int(...) const&>();
    test_decay<int(...) const&&>();
    test_decay<int(...) volatile>();
    test_decay<int(...) volatile&>();
    test_decay<int(...) volatile&&>();
    test_decay<int(...) const volatile>();
    test_decay<int(...) const volatile&>();
    test_decay<int(...) const volatile&&>();
    test_decay<int(...) noexcept, int (*)(...) noexcept>();
    test_decay<int(...)& noexcept>();
    test_decay<int(...)&& noexcept>();
    test_decay<int(...) const noexcept>();
    test_decay<int(...) const& noexcept>();
    test_decay<int(...) const&& noexcept>();
    test_decay<int(...) volatile noexcept>();
    test_decay<int(...) volatile& noexcept>();
    test_decay<int(...) volatile&& noexcept>();
    test_decay<int(...) const volatile noexcept>();
    test_decay<int(...) const volatile& noexcept>();
    test_decay<int(...) const volatile&& noexcept>();

    test_decay<int(int, ...), int (*)(int, ...)>();
    test_decay<int(int, ...)&>();
    test_decay<int(int, ...) &&>();
    test_decay<int(int, ...) const>();
    test_decay<int(int, ...) const&>();
    test_decay<int(int, ...) const&&>();
    test_decay<int(int, ...) volatile>();
    test_decay<int(int, ...) volatile&>();
    test_decay<int(int, ...) volatile&&>();
    test_decay<int(int, ...) const volatile>();
    test_decay<int(int, ...) const volatile&>();
    test_decay<int(int, ...) const volatile&&>();
    test_decay<int(int, ...) noexcept, int (*)(int, ...) noexcept>();
    test_decay<int(int, ...)& noexcept>();
    test_decay<int(int, ...)&& noexcept>();
    test_decay<int(int, ...) const noexcept>();
    test_decay<int(int, ...) const& noexcept>();
    test_decay<int(int, ...) const&& noexcept>();
    test_decay<int(int, ...) volatile noexcept>();
    test_decay<int(int, ...) volatile& noexcept>();
    test_decay<int(int, ...) volatile&& noexcept>();
    test_decay<int(int, ...) const volatile noexcept>();
    test_decay<int(int, ...) const volatile& noexcept>();
    test_decay<int(int, ...) const volatile&& noexcept>();

    test_decay<void (*)()>();
    test_decay<void (*)() noexcept>();

    test_decay<void (*)(int)>();
    test_decay<void (*)(int) noexcept>();

    test_decay<void (*)(...)>();
    test_decay<void (*)(...) noexcept>();

    test_decay<void (*)(int, ...)>();
    test_decay<void (*)(int, ...) noexcept>();

    test_decay<int (*)()>();
    test_decay<int (*)() noexcept>();

    test_decay<int (*)(int)>();
    test_decay<int (*)(int) noexcept>();

    test_decay<int (*)(...)>();
    test_decay<int (*)(...) noexcept>();

    test_decay<int (*)(int, ...)>();
    test_decay<int (*)(int, ...) noexcept>();

    test_decay<void (&)(), void (*)()>();
    test_decay<void (&)() noexcept, void (*)() noexcept>();

    test_decay<void (&)(int), void (*)(int)>();
    test_decay<void (&)(int) noexcept, void (*)(int) noexcept>();

    test_decay<void (&)(...), void (*)(...)>();
    test_decay<void (&)(...) noexcept, void (*)(...) noexcept>();

    test_decay<void (&)(int, ...), void (*)(int, ...)>();
    test_decay<void (&)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_decay<int (&)(), int (*)()>();
    test_decay<int (&)() noexcept, int (*)() noexcept>();

    test_decay<int (&)(int), int (*)(int)>();
    test_decay<int (&)(int) noexcept, int (*)(int) noexcept>();

    test_decay<int (&)(...), int (*)(...)>();
    test_decay<int (&)(...) noexcept, int (*)(...) noexcept>();

    test_decay<int (&)(int, ...), int (*)(int, ...)>();
    test_decay<int (&)(int, ...) noexcept, int (*)(int, ...) noexcept>();

    test_decay<void(&&)(), void (*)()>();
    test_decay<void(&&)() noexcept, void (*)() noexcept>();

    test_decay<void(&&)(int), void (*)(int)>();
    test_decay<void(&&)(int) noexcept, void (*)(int) noexcept>();

    test_decay<void(&&)(...), void (*)(...)>();
    test_decay<void(&&)(...) noexcept, void (*)(...) noexcept>();

    test_decay<void(&&)(int, ...), void (*)(int, ...)>();
    test_decay<void(&&)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_decay<int(&&)(), int (*)()>();
    test_decay<int(&&)() noexcept, int (*)() noexcept>();

    test_decay<int(&&)(int), int (*)(int)>();
    test_decay<int(&&)(int) noexcept, int (*)(int) noexcept>();

    test_decay<int(&&)(...), int (*)(...)>();
    test_decay<int(&&)(...) noexcept, int (*)(...) noexcept>();

    test_decay<int(&&)(int, ...), int (*)(int, ...)>();
    test_decay<int(&&)(int, ...) noexcept, int (*)(int, ...) noexcept>();

    test_decay<void (Class::*)()>();
    test_decay<void (Class::*)()&>();
    test_decay<void (Class::*)() &&>();
    test_decay<void (Class::*)() const>();
    test_decay<void (Class::*)() const&>();
    test_decay<void (Class::*)() const&&>();
    test_decay<void (Class::*)() noexcept>();
    test_decay<void (Class::*)()& noexcept>();
    test_decay<void (Class::*)()&& noexcept>();
    test_decay<void (Class::*)() const noexcept>();
    test_decay<void (Class::*)() const& noexcept>();
    test_decay<void (Class::*)() const&& noexcept>();

    test_decay<void (Class::*)(int)>();
    test_decay<void (Class::*)(int)&>();
    test_decay<void (Class::*)(int) &&>();
    test_decay<void (Class::*)(int) const>();
    test_decay<void (Class::*)(int) const&>();
    test_decay<void (Class::*)(int) const&&>();
    test_decay<void (Class::*)(int) noexcept>();
    test_decay<void (Class::*)(int)& noexcept>();
    test_decay<void (Class::*)(int)&& noexcept>();
    test_decay<void (Class::*)(int) const noexcept>();
    test_decay<void (Class::*)(int) const& noexcept>();
    test_decay<void (Class::*)(int) const&& noexcept>();

    test_decay<void (Class::*)(...)>();
    test_decay<void (Class::*)(...)&>();
    test_decay<void (Class::*)(...) &&>();
    test_decay<void (Class::*)(...) const>();
    test_decay<void (Class::*)(...) const&>();
    test_decay<void (Class::*)(...) const&&>();
    test_decay<void (Class::*)(...) noexcept>();
    test_decay<void (Class::*)(...)& noexcept>();
    test_decay<void (Class::*)(...)&& noexcept>();
    test_decay<void (Class::*)(...) const noexcept>();
    test_decay<void (Class::*)(...) const& noexcept>();
    test_decay<void (Class::*)(...) const&& noexcept>();

    test_decay<void (Class::*)(int, ...)>();
    test_decay<void (Class::*)(int, ...)&>();
    test_decay<void (Class::*)(int, ...) &&>();
    test_decay<void (Class::*)(int, ...) const>();
    test_decay<void (Class::*)(int, ...) const&>();
    test_decay<void (Class::*)(int, ...) const&&>();
    test_decay<void (Class::*)(int, ...) noexcept>();
    test_decay<void (Class::*)(int, ...)& noexcept>();
    test_decay<void (Class::*)(int, ...)&& noexcept>();
    test_decay<void (Class::*)(int, ...) const noexcept>();
    test_decay<void (Class::*)(int, ...) const& noexcept>();
    test_decay<void (Class::*)(int, ...) const&& noexcept>();

    test_decay<int (Class::*)()>();
    test_decay<int (Class::*)()&>();
    test_decay<int (Class::*)() &&>();
    test_decay<int (Class::*)() const>();
    test_decay<int (Class::*)() const&>();
    test_decay<int (Class::*)() const&&>();
    test_decay<int (Class::*)() noexcept>();
    test_decay<int (Class::*)()& noexcept>();
    test_decay<int (Class::*)()&& noexcept>();
    test_decay<int (Class::*)() const noexcept>();
    test_decay<int (Class::*)() const& noexcept>();
    test_decay<int (Class::*)() const&& noexcept>();

    test_decay<int (Class::*)(int)>();
    test_decay<int (Class::*)(int)&>();
    test_decay<int (Class::*)(int) &&>();
    test_decay<int (Class::*)(int) const>();
    test_decay<int (Class::*)(int) const&>();
    test_decay<int (Class::*)(int) const&&>();
    test_decay<int (Class::*)(int) noexcept>();
    test_decay<int (Class::*)(int)& noexcept>();
    test_decay<int (Class::*)(int)&& noexcept>();
    test_decay<int (Class::*)(int) const noexcept>();
    test_decay<int (Class::*)(int) const& noexcept>();
    test_decay<int (Class::*)(int) const&& noexcept>();

    test_decay<int (Class::*)(...)>();
    test_decay<int (Class::*)(...)&>();
    test_decay<int (Class::*)(...) &&>();
    test_decay<int (Class::*)(...) const>();
    test_decay<int (Class::*)(...) const&>();
    test_decay<int (Class::*)(...) const&&>();
    test_decay<int (Class::*)(...) noexcept>();
    test_decay<int (Class::*)(...)& noexcept>();
    test_decay<int (Class::*)(...)&& noexcept>();
    test_decay<int (Class::*)(...) const noexcept>();
    test_decay<int (Class::*)(...) const& noexcept>();
    test_decay<int (Class::*)(...) const&& noexcept>();

    test_decay<int (Class::*)(int, ...)>();
    test_decay<int (Class::*)(int, ...)&>();
    test_decay<int (Class::*)(int, ...) &&>();
    test_decay<int (Class::*)(int, ...) const>();
    test_decay<int (Class::*)(int, ...) const&>();
    test_decay<int (Class::*)(int, ...) const&&>();
    test_decay<int (Class::*)(int, ...) noexcept>();
    test_decay<int (Class::*)(int, ...)& noexcept>();
    test_decay<int (Class::*)(int, ...)&& noexcept>();
    test_decay<int (Class::*)(int, ...) const noexcept>();
    test_decay<int (Class::*)(int, ...) const& noexcept>();
    test_decay<int (Class::*)(int, ...) const&& noexcept>();
}
