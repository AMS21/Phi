#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/extent.hpp>
#include <type_traits>
#include <vector>

template <typename T, unsigned A = 0>
void test_extent()
{
    STATIC_REQUIRE(phi::extent<T>::value == A);
    STATIC_REQUIRE(phi::extent<const T>::value == A);
    STATIC_REQUIRE(phi::extent<volatile T>::value == A);
    STATIC_REQUIRE(phi::extent<const volatile T>::value == A);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::extent_v<T> == A);
    STATIC_REQUIRE(phi::extent_v<const T> == A);
    STATIC_REQUIRE(phi::extent_v<volatile T> == A);
    STATIC_REQUIRE(phi::extent_v<const volatile T> == A);
#endif

    // Standard compatbility
    STATIC_REQUIRE(phi::extent<T>::value == std::extent<T>::value);
}

template <typename T, unsigned Val, unsigned A>
void test_extent_var()
{
    STATIC_REQUIRE(phi::extent<T, Val>::value == A);
    STATIC_REQUIRE(phi::extent<const T, Val>::value == A);
    STATIC_REQUIRE(phi::extent<volatile T, Val>::value == A);
    STATIC_REQUIRE(phi::extent<const volatile T, Val>::value == A);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::extent_v<T, Val> == A);
    STATIC_REQUIRE(phi::extent_v<const T, Val> == A);
    STATIC_REQUIRE(phi::extent_v<volatile T, Val> == A);
    STATIC_REQUIRE(phi::extent_v<const volatile T, Val> == A);
#endif

    // Standard compatbility
    STATIC_REQUIRE(phi::extent<T, Val>::value == std::extent<T, Val>::value);
}

TEST_CASE("extent")
{
    test_extent<int[1], 1>();
    test_extent<int[2], 2>();
    test_extent<int[3], 3>();
    test_extent<int[1][4], 1>();
    test_extent<int[2][4], 2>();
    test_extent<int[3][4], 3>();
    test_extent<int[1][4][9], 1>();
    test_extent<int[2][4][9], 2>();
    test_extent<int[3][4][9], 3>();

    test_extent<int[], 0>();
    test_extent<int[][4], 0>();
    test_extent<int[][4][9], 0>();

    // Extent 1
    test_extent_var<int, 1, 0>();
    test_extent_var<int[], 1, 0>();
    test_extent_var<int[1], 1, 0>();
    test_extent_var<int[2], 1, 0>();
    test_extent_var<int[3], 1, 0>();
    test_extent_var<int[1][4], 1, 4>();
    test_extent_var<int[2][4], 1, 4>();
    test_extent_var<int[3][4], 1, 4>();
    test_extent_var<int[2][3], 1, 3>();
    test_extent_var<int[][4], 1, 4>();
    test_extent_var<int[1][4][5], 1, 4>();
    test_extent_var<int[2][4][5], 1, 4>();
    test_extent_var<int[3][4][5], 1, 4>();
    test_extent_var<int[2][3][5], 1, 3>();
    test_extent_var<int[][4][5], 1, 4>();

    // Extent 2
    test_extent_var<int, 2, 0>();
    test_extent_var<int[], 2, 0>();
    test_extent_var<int[1], 2, 0>();
    test_extent_var<int[2], 2, 0>();
    test_extent_var<int[3], 2, 0>();
    test_extent_var<int[1][4], 2, 0>();
    test_extent_var<int[2][4], 2, 0>();
    test_extent_var<int[3][4], 2, 0>();
    test_extent_var<int[2][3], 2, 0>();
    test_extent_var<int[][4], 2, 0>();
    test_extent_var<int[1][1][3], 2, 3>();
    test_extent_var<int[1][1][4], 2, 4>();
    test_extent_var<int[][1][3], 2, 3>();
    test_extent_var<int[][1][3][4], 2, 3>();
    test_extent_var<int[][1][3][5], 2, 3>();

    // Extent 3
    test_extent_var<int, 3, 0>();
    test_extent_var<int[], 3, 0>();
    test_extent_var<int[1], 3, 0>();
    test_extent_var<int[2], 3, 0>();
    test_extent_var<int[3], 3, 0>();
    test_extent_var<int[1][4], 3, 0>();
    test_extent_var<int[2][4], 3, 0>();
    test_extent_var<int[3][4], 3, 0>();
    test_extent_var<int[2][3], 3, 0>();
    test_extent_var<int[][4], 3, 0>();
    test_extent_var<int[1][1][3], 3, 0>();
    test_extent_var<int[1][1][4], 3, 0>();
    test_extent_var<int[][1][3], 3, 0>();
    test_extent_var<int[][1][3][4], 3, 4>();
    test_extent_var<int[][1][3][5], 3, 5>();

    test_extent<void>();
    test_extent<phi::nullptr_t>();
    test_extent<bool>();
    test_extent<char>();
    test_extent<signed char>();
    test_extent<unsigned char>();
    test_extent<short>();
    test_extent<unsigned short>();
    test_extent<int>();
    test_extent<unsigned int>();
    test_extent<long>();
    test_extent<unsigned long>();
    test_extent<long long>();
    test_extent<unsigned long long>();
    test_extent<float>();
    test_extent<double>();
    test_extent<long double>();
    test_extent<char8_t>();
    test_extent<char16_t>();
    test_extent<char32_t>();
    test_extent<wchar_t>();

    test_extent<phi::Boolean>();
    test_extent<phi::Integer<signed char>>();
    test_extent<phi::Integer<unsigned char>>();
    test_extent<phi::Integer<short>>();
    test_extent<phi::Integer<unsigned short>>();
    test_extent<phi::Integer<int>>();
    test_extent<phi::Integer<unsigned int>>();
    test_extent<phi::Integer<long>>();
    test_extent<phi::Integer<unsigned long>>();
    test_extent<phi::Integer<long long>>();
    test_extent<phi::Integer<unsigned long long>>();
    test_extent<phi::FloatingPoint<float>>();
    test_extent<phi::FloatingPoint<double>>();
    test_extent<phi::FloatingPoint<long double>>();

    test_extent<std::vector<int>>();
    test_extent<phi::ScopePtr<int>>();

    test_extent<int&>();
    test_extent<const int&>();
    test_extent<volatile int&>();
    test_extent<const volatile int&>();
    test_extent<int&&>();
    test_extent<const int&&>();
    test_extent<volatile int&&>();
    test_extent<const volatile int&&>();
    test_extent<int*>();
    test_extent<const int*>();
    test_extent<volatile int*>();
    test_extent<const volatile int*>();
    test_extent<int**>();
    test_extent<const int**>();
    test_extent<volatile int**>();
    test_extent<const volatile int**>();
    test_extent<int*&>();
    test_extent<const int*&>();
    test_extent<volatile int*&>();
    test_extent<const volatile int*&>();
    test_extent<int*&&>();
    test_extent<const int*&&>();
    test_extent<volatile int*&&>();
    test_extent<const volatile int*&&>();
    test_extent<void*>();
    test_extent<char[3], 3>();
    test_extent<char[], 0>();
    test_extent<char[3], 3>();
    test_extent<char[], 0>();
    test_extent<char* [3], 3>();
    test_extent<char*[]>();
    test_extent<int(*)[3]>();
    test_extent<int(*)[]>();
    test_extent<int(&)[3]>();
    test_extent<int(&)[]>();
    test_extent<int(&&)[3]>();
    test_extent<int(&&)[]>();
    test_extent<char[3][2], 3>();
    test_extent<char[][2], 0>();
    test_extent<char* [3][2], 3>();
    test_extent<char*[][2], 0>();
    test_extent<int(*)[3][2]>();
    test_extent<int(*)[][2]>();
    test_extent<int(&)[3][2]>();
    test_extent<int(&)[][2]>();
    test_extent<int(&&)[3][2]>();
    test_extent<int(&&)[][2]>();
    test_extent<Class>();
    test_extent<Class[], 0>();
    test_extent<Class[2], 2>();
    test_extent<Template<void>>();
    test_extent<Template<int>>();
    test_extent<Template<Class>>();
    test_extent<Template<incomplete_type>>();
    test_extent<VariadicTemplate<>>();
    test_extent<VariadicTemplate<void>>();
    test_extent<VariadicTemplate<int>>();
    test_extent<VariadicTemplate<Class>>();
    test_extent<VariadicTemplate<incomplete_type>>();
    test_extent<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_extent<PublicDerviedFromTemplate<Base>>();
    test_extent<PublicDerviedFromTemplate<Derived>>();
    test_extent<PublicDerviedFromTemplate<Class>>();
    test_extent<PrivateDerviedFromTemplate<Base>>();
    test_extent<PrivateDerviedFromTemplate<Derived>>();
    test_extent<PrivateDerviedFromTemplate<Class>>();
    test_extent<ProtectedDerviedFromTemplate<Base>>();
    test_extent<ProtectedDerviedFromTemplate<Derived>>();
    test_extent<ProtectedDerviedFromTemplate<Class>>();
    test_extent<Union>();
    test_extent<NonEmptyUnion>();
    test_extent<Empty>();
    test_extent<NotEmpty>();
    test_extent<bit_zero>();
    test_extent<bit_one>();
    test_extent<Base>();
    test_extent<Derived>();
    test_extent<Abstract>();
    test_extent<PublicAbstract>();
    test_extent<PrivateAbstract>();
    test_extent<ProtectedAbstract>();
    test_extent<AbstractTemplate<int>>();
    test_extent<AbstractTemplate<double>>();
    test_extent<AbstractTemplate<Class>>();
    test_extent<AbstractTemplate<incomplete_type>>();
    test_extent<Final>();
    test_extent<PublicDestructor>();
    test_extent<ProtectedDestructor>();
    test_extent<PrivateDestructor>();
    test_extent<VirtualPublicDestructor>();
    test_extent<VirtualProtectedDestructor>();
    test_extent<VirtualPrivateDestructor>();
    test_extent<PurePublicDestructor>();
    test_extent<PureProtectedDestructor>();
    test_extent<PurePrivateDestructor>();
    test_extent<DeletedPublicDestructor>();
    test_extent<DeletedProtectedDestructor>();
    test_extent<DeletedPrivateDestructor>();
    test_extent<DeletedVirtualPublicDestructor>();
    test_extent<DeletedVirtualProtectedDestructor>();
    test_extent<DeletedVirtualPrivateDestructor>();
    test_extent<Enum>();
    test_extent<EnumSigned>();
    test_extent<EnumUnsigned>();
    test_extent<EnumClass>();
    test_extent<EnumStruct>();
    test_extent<Function>();
    test_extent<FunctionPtr>();
    test_extent<MemberObjectPtr>();
    test_extent<MemberFunctionPtr>();
    test_extent<incomplete_type>();
    test_extent<IncompleteTemplate<void>>();
    test_extent<IncompleteTemplate<int>>();
    test_extent<IncompleteTemplate<Class>>();
    test_extent<IncompleteTemplate<incomplete_type>>();
    test_extent<IncompleteVariadicTemplate<>>();
    test_extent<IncompleteVariadicTemplate<void>>();
    test_extent<IncompleteVariadicTemplate<int>>();
    test_extent<IncompleteVariadicTemplate<Class>>();
    test_extent<IncompleteVariadicTemplate<incomplete_type>>();
    test_extent<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_extent<int Class::*>();
    test_extent<float Class::*>();
    test_extent<void * Class::*>();
    test_extent<int * Class::*>();
    test_extent<int Class::*&>();
    test_extent<float Class::*&>();
    test_extent<void * Class::*&>();
    test_extent<int * Class::*&>();
    test_extent<int Class::*&&>();
    test_extent<float Class::*&&>();
    test_extent<void * Class::*&&>();
    test_extent<int * Class::*&&>();
    test_extent<int Class::*const>();
    test_extent<float Class::*const>();
    test_extent<void * Class::*const>();
    test_extent<int Class::*const&>();
    test_extent<float Class::*const&>();
    test_extent<void * Class::*const&>();
    test_extent<int Class::*const&&>();
    test_extent<float Class::*const&&>();
    test_extent<void * Class::*const&&>();
    test_extent<int Class::*volatile>();
    test_extent<float Class::*volatile>();
    test_extent<void * Class::*volatile>();
    test_extent<int Class::*volatile&>();
    test_extent<float Class::*volatile&>();
    test_extent<void * Class::*volatile&>();
    test_extent<int Class::*volatile&&>();
    test_extent<float Class::*volatile&&>();
    test_extent<void * Class::*volatile&&>();
    test_extent<int Class::*const volatile>();
    test_extent<float Class::*const volatile>();
    test_extent<void * Class::*const volatile>();
    test_extent<int Class::*const volatile&>();
    test_extent<float Class::*const volatile&>();
    test_extent<void * Class::*const volatile&>();
    test_extent<int Class::*const volatile&&>();
    test_extent<float Class::*const volatile&&>();
    test_extent<void * Class::*const volatile&&>();
    test_extent<NonCopyable>();
    test_extent<NonMoveable>();
    test_extent<NonConstructible>();
    test_extent<Tracked>();
    test_extent<TrapConstructible>();
    test_extent<TrapImplicitConversion>();
    test_extent<TrapComma>();
    test_extent<TrapCall>();
    test_extent<TrapSelfAssign>();
    test_extent<TrapDeref>();
    test_extent<TrapArraySubscript>();

    test_extent<void()>();
    test_extent<void()&>();
    test_extent<void() &&>();
    test_extent<void() const>();
    test_extent<void() const&>();
    test_extent<void() const&&>();
    test_extent<void() volatile>();
    test_extent<void() volatile&>();
    test_extent<void() volatile&&>();
    test_extent<void() const volatile>();
    test_extent<void() const volatile&>();
    test_extent<void() const volatile&&>();
    test_extent<void() noexcept>();
    test_extent<void()& noexcept>();
    test_extent<void()&& noexcept>();
    test_extent<void() const noexcept>();
    test_extent<void() const& noexcept>();
    test_extent<void() const&& noexcept>();
    test_extent<void() volatile noexcept>();
    test_extent<void() volatile& noexcept>();
    test_extent<void() volatile&& noexcept>();
    test_extent<void() const volatile noexcept>();
    test_extent<void() const volatile& noexcept>();
    test_extent<void() const volatile&& noexcept>();

    test_extent<void(int)>();
    test_extent<void(int)&>();
    test_extent<void(int) &&>();
    test_extent<void(int) const>();
    test_extent<void(int) const&>();
    test_extent<void(int) const&&>();
    test_extent<void(int) volatile>();
    test_extent<void(int) volatile&>();
    test_extent<void(int) volatile&&>();
    test_extent<void(int) const volatile>();
    test_extent<void(int) const volatile&>();
    test_extent<void(int) const volatile&&>();
    test_extent<void(int) noexcept>();
    test_extent<void(int)& noexcept>();
    test_extent<void(int)&& noexcept>();
    test_extent<void(int) const noexcept>();
    test_extent<void(int) const& noexcept>();
    test_extent<void(int) const&& noexcept>();
    test_extent<void(int) volatile noexcept>();
    test_extent<void(int) volatile& noexcept>();
    test_extent<void(int) volatile&& noexcept>();
    test_extent<void(int) const volatile noexcept>();
    test_extent<void(int) const volatile& noexcept>();
    test_extent<void(int) const volatile&& noexcept>();

    test_extent<void(...)>();
    test_extent<void(...)&>();
    test_extent<void(...) &&>();
    test_extent<void(...) const>();
    test_extent<void(...) const&>();
    test_extent<void(...) const&&>();
    test_extent<void(...) volatile>();
    test_extent<void(...) volatile&>();
    test_extent<void(...) volatile&&>();
    test_extent<void(...) const volatile>();
    test_extent<void(...) const volatile&>();
    test_extent<void(...) const volatile&&>();
    test_extent<void(...) noexcept>();
    test_extent<void(...)& noexcept>();
    test_extent<void(...)&& noexcept>();
    test_extent<void(...) const noexcept>();
    test_extent<void(...) const& noexcept>();
    test_extent<void(...) const&& noexcept>();
    test_extent<void(...) volatile noexcept>();
    test_extent<void(...) volatile& noexcept>();
    test_extent<void(...) volatile&& noexcept>();
    test_extent<void(...) const volatile noexcept>();
    test_extent<void(...) const volatile& noexcept>();
    test_extent<void(...) const volatile&& noexcept>();

    test_extent<void(int, ...)>();
    test_extent<void(int, ...)&>();
    test_extent<void(int, ...) &&>();
    test_extent<void(int, ...) const>();
    test_extent<void(int, ...) const&>();
    test_extent<void(int, ...) const&&>();
    test_extent<void(int, ...) volatile>();
    test_extent<void(int, ...) volatile&>();
    test_extent<void(int, ...) volatile&&>();
    test_extent<void(int, ...) const volatile>();
    test_extent<void(int, ...) const volatile&>();
    test_extent<void(int, ...) const volatile&&>();
    test_extent<void(int, ...) noexcept>();
    test_extent<void(int, ...)& noexcept>();
    test_extent<void(int, ...)&& noexcept>();
    test_extent<void(int, ...) const noexcept>();
    test_extent<void(int, ...) const& noexcept>();
    test_extent<void(int, ...) const&& noexcept>();
    test_extent<void(int, ...) volatile noexcept>();
    test_extent<void(int, ...) volatile& noexcept>();
    test_extent<void(int, ...) volatile&& noexcept>();
    test_extent<void(int, ...) const volatile noexcept>();
    test_extent<void(int, ...) const volatile& noexcept>();
    test_extent<void(int, ...) const volatile&& noexcept>();

    test_extent<int()>();
    test_extent<int()&>();
    test_extent<int() &&>();
    test_extent<int() const>();
    test_extent<int() const&>();
    test_extent<int() const&&>();
    test_extent<int() volatile>();
    test_extent<int() volatile&>();
    test_extent<int() volatile&&>();
    test_extent<int() const volatile>();
    test_extent<int() const volatile&>();
    test_extent<int() const volatile&&>();
    test_extent<int() noexcept>();
    test_extent<int()& noexcept>();
    test_extent<int()&& noexcept>();
    test_extent<int() const noexcept>();
    test_extent<int() const& noexcept>();
    test_extent<int() const&& noexcept>();
    test_extent<int() volatile noexcept>();
    test_extent<int() volatile& noexcept>();
    test_extent<int() volatile&& noexcept>();
    test_extent<int() const volatile noexcept>();
    test_extent<int() const volatile& noexcept>();
    test_extent<int() const volatile&& noexcept>();

    test_extent<int(int)>();
    test_extent<int(int)&>();
    test_extent<int(int) &&>();
    test_extent<int(int) const>();
    test_extent<int(int) const&>();
    test_extent<int(int) const&&>();
    test_extent<int(int) volatile>();
    test_extent<int(int) volatile&>();
    test_extent<int(int) volatile&&>();
    test_extent<int(int) const volatile>();
    test_extent<int(int) const volatile&>();
    test_extent<int(int) const volatile&&>();
    test_extent<int(int) noexcept>();
    test_extent<int(int)& noexcept>();
    test_extent<int(int)&& noexcept>();
    test_extent<int(int) const noexcept>();
    test_extent<int(int) const& noexcept>();
    test_extent<int(int) const&& noexcept>();
    test_extent<int(int) volatile noexcept>();
    test_extent<int(int) volatile& noexcept>();
    test_extent<int(int) volatile&& noexcept>();
    test_extent<int(int) const volatile noexcept>();
    test_extent<int(int) const volatile& noexcept>();
    test_extent<int(int) const volatile&& noexcept>();

    test_extent<int(...)>();
    test_extent<int(...)&>();
    test_extent<int(...) &&>();
    test_extent<int(...) const>();
    test_extent<int(...) const&>();
    test_extent<int(...) const&&>();
    test_extent<int(...) volatile>();
    test_extent<int(...) volatile&>();
    test_extent<int(...) volatile&&>();
    test_extent<int(...) const volatile>();
    test_extent<int(...) const volatile&>();
    test_extent<int(...) const volatile&&>();
    test_extent<int(...) noexcept>();
    test_extent<int(...)& noexcept>();
    test_extent<int(...)&& noexcept>();
    test_extent<int(...) const noexcept>();
    test_extent<int(...) const& noexcept>();
    test_extent<int(...) const&& noexcept>();
    test_extent<int(...) volatile noexcept>();
    test_extent<int(...) volatile& noexcept>();
    test_extent<int(...) volatile&& noexcept>();
    test_extent<int(...) const volatile noexcept>();
    test_extent<int(...) const volatile& noexcept>();
    test_extent<int(...) const volatile&& noexcept>();

    test_extent<int(int, ...)>();
    test_extent<int(int, ...)&>();
    test_extent<int(int, ...) &&>();
    test_extent<int(int, ...) const>();
    test_extent<int(int, ...) const&>();
    test_extent<int(int, ...) const&&>();
    test_extent<int(int, ...) volatile>();
    test_extent<int(int, ...) volatile&>();
    test_extent<int(int, ...) volatile&&>();
    test_extent<int(int, ...) const volatile>();
    test_extent<int(int, ...) const volatile&>();
    test_extent<int(int, ...) const volatile&&>();
    test_extent<int(int, ...) noexcept>();
    test_extent<int(int, ...)& noexcept>();
    test_extent<int(int, ...)&& noexcept>();
    test_extent<int(int, ...) const noexcept>();
    test_extent<int(int, ...) const& noexcept>();
    test_extent<int(int, ...) const&& noexcept>();
    test_extent<int(int, ...) volatile noexcept>();
    test_extent<int(int, ...) volatile& noexcept>();
    test_extent<int(int, ...) volatile&& noexcept>();
    test_extent<int(int, ...) const volatile noexcept>();
    test_extent<int(int, ...) const volatile& noexcept>();
    test_extent<int(int, ...) const volatile&& noexcept>();

    test_extent<void (*)()>();
    test_extent<void (*)() noexcept>();

    test_extent<void (*)(int)>();
    test_extent<void (*)(int) noexcept>();

    test_extent<void (*)(...)>();
    test_extent<void (*)(...) noexcept>();

    test_extent<void (*)(int, ...)>();
    test_extent<void (*)(int, ...) noexcept>();

    test_extent<int (*)()>();
    test_extent<int (*)() noexcept>();

    test_extent<int (*)(int)>();
    test_extent<int (*)(int) noexcept>();

    test_extent<int (*)(...)>();
    test_extent<int (*)(...) noexcept>();

    test_extent<int (*)(int, ...)>();
    test_extent<int (*)(int, ...) noexcept>();

    test_extent<void (&)()>();
    test_extent<void (&)() noexcept>();

    test_extent<void (&)(int)>();
    test_extent<void (&)(int) noexcept>();

    test_extent<void (&)(...)>();
    test_extent<void (&)(...) noexcept>();

    test_extent<void (&)(int, ...)>();
    test_extent<void (&)(int, ...) noexcept>();

    test_extent<int (&)()>();
    test_extent<int (&)() noexcept>();

    test_extent<int (&)(int)>();
    test_extent<int (&)(int) noexcept>();

    test_extent<int (&)(...)>();
    test_extent<int (&)(...) noexcept>();

    test_extent<int (&)(int, ...)>();
    test_extent<int (&)(int, ...) noexcept>();

    test_extent<void(&&)()>();
    test_extent<void(&&)() noexcept>();

    test_extent<void(&&)(int)>();
    test_extent<void(&&)(int) noexcept>();

    test_extent<void(&&)(...)>();
    test_extent<void(&&)(...) noexcept>();

    test_extent<void(&&)(int, ...)>();
    test_extent<void(&&)(int, ...) noexcept>();

    test_extent<int(&&)()>();
    test_extent<int(&&)() noexcept>();

    test_extent<int(&&)(int)>();
    test_extent<int(&&)(int) noexcept>();

    test_extent<int(&&)(...)>();
    test_extent<int(&&)(...) noexcept>();

    test_extent<int(&&)(int, ...)>();
    test_extent<int(&&)(int, ...) noexcept>();

    test_extent<void (Class::*)()>();
    test_extent<void (Class::*)()&>();
    test_extent<void (Class::*)() &&>();
    test_extent<void (Class::*)() const>();
    test_extent<void (Class::*)() const&>();
    test_extent<void (Class::*)() const&&>();
    test_extent<void (Class::*)() noexcept>();
    test_extent<void (Class::*)()& noexcept>();
    test_extent<void (Class::*)()&& noexcept>();
    test_extent<void (Class::*)() const noexcept>();
    test_extent<void (Class::*)() const& noexcept>();
    test_extent<void (Class::*)() const&& noexcept>();

    test_extent<void (Class::*)(int)>();
    test_extent<void (Class::*)(int)&>();
    test_extent<void (Class::*)(int) &&>();
    test_extent<void (Class::*)(int) const>();
    test_extent<void (Class::*)(int) const&>();
    test_extent<void (Class::*)(int) const&&>();
    test_extent<void (Class::*)(int) noexcept>();
    test_extent<void (Class::*)(int)& noexcept>();
    test_extent<void (Class::*)(int)&& noexcept>();
    test_extent<void (Class::*)(int) const noexcept>();
    test_extent<void (Class::*)(int) const& noexcept>();
    test_extent<void (Class::*)(int) const&& noexcept>();

    test_extent<void (Class::*)(...)>();
    test_extent<void (Class::*)(...)&>();
    test_extent<void (Class::*)(...) &&>();
    test_extent<void (Class::*)(...) const>();
    test_extent<void (Class::*)(...) const&>();
    test_extent<void (Class::*)(...) const&&>();
    test_extent<void (Class::*)(...) noexcept>();
    test_extent<void (Class::*)(...)& noexcept>();
    test_extent<void (Class::*)(...)&& noexcept>();
    test_extent<void (Class::*)(...) const noexcept>();
    test_extent<void (Class::*)(...) const& noexcept>();
    test_extent<void (Class::*)(...) const&& noexcept>();

    test_extent<void (Class::*)(int, ...)>();
    test_extent<void (Class::*)(int, ...)&>();
    test_extent<void (Class::*)(int, ...) &&>();
    test_extent<void (Class::*)(int, ...) const>();
    test_extent<void (Class::*)(int, ...) const&>();
    test_extent<void (Class::*)(int, ...) const&&>();
    test_extent<void (Class::*)(int, ...) noexcept>();
    test_extent<void (Class::*)(int, ...)& noexcept>();
    test_extent<void (Class::*)(int, ...)&& noexcept>();
    test_extent<void (Class::*)(int, ...) const noexcept>();
    test_extent<void (Class::*)(int, ...) const& noexcept>();
    test_extent<void (Class::*)(int, ...) const&& noexcept>();

    test_extent<int (Class::*)()>();
    test_extent<int (Class::*)()&>();
    test_extent<int (Class::*)() &&>();
    test_extent<int (Class::*)() const>();
    test_extent<int (Class::*)() const&>();
    test_extent<int (Class::*)() const&&>();
    test_extent<int (Class::*)() noexcept>();
    test_extent<int (Class::*)()& noexcept>();
    test_extent<int (Class::*)()&& noexcept>();
    test_extent<int (Class::*)() const noexcept>();
    test_extent<int (Class::*)() const& noexcept>();
    test_extent<int (Class::*)() const&& noexcept>();

    test_extent<int (Class::*)(int)>();
    test_extent<int (Class::*)(int)&>();
    test_extent<int (Class::*)(int) &&>();
    test_extent<int (Class::*)(int) const>();
    test_extent<int (Class::*)(int) const&>();
    test_extent<int (Class::*)(int) const&&>();
    test_extent<int (Class::*)(int) noexcept>();
    test_extent<int (Class::*)(int)& noexcept>();
    test_extent<int (Class::*)(int)&& noexcept>();
    test_extent<int (Class::*)(int) const noexcept>();
    test_extent<int (Class::*)(int) const& noexcept>();
    test_extent<int (Class::*)(int) const&& noexcept>();

    test_extent<int (Class::*)(...)>();
    test_extent<int (Class::*)(...)&>();
    test_extent<int (Class::*)(...) &&>();
    test_extent<int (Class::*)(...) const>();
    test_extent<int (Class::*)(...) const&>();
    test_extent<int (Class::*)(...) const&&>();
    test_extent<int (Class::*)(...) noexcept>();
    test_extent<int (Class::*)(...)& noexcept>();
    test_extent<int (Class::*)(...)&& noexcept>();
    test_extent<int (Class::*)(...) const noexcept>();
    test_extent<int (Class::*)(...) const& noexcept>();
    test_extent<int (Class::*)(...) const&& noexcept>();

    test_extent<int (Class::*)(int, ...)>();
    test_extent<int (Class::*)(int, ...)&>();
    test_extent<int (Class::*)(int, ...) &&>();
    test_extent<int (Class::*)(int, ...) const>();
    test_extent<int (Class::*)(int, ...) const&>();
    test_extent<int (Class::*)(int, ...) const&&>();
    test_extent<int (Class::*)(int, ...) noexcept>();
    test_extent<int (Class::*)(int, ...)& noexcept>();
    test_extent<int (Class::*)(int, ...)&& noexcept>();
    test_extent<int (Class::*)(int, ...) const noexcept>();
    test_extent<int (Class::*)(int, ...) const& noexcept>();
    test_extent<int (Class::*)(int, ...) const&& noexcept>();
}
