#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_arithmetic.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_arithmetic_impl()
{
    STATIC_REQUIRE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_arithmetic<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_arithmetic_v<T>);
#endif
}

template <typename T>
void test_is_arithmetic()
{
    test_is_arithmetic_impl<T>();
    test_is_arithmetic_impl<const T>();
    test_is_arithmetic_impl<volatile T>();
    test_is_arithmetic_impl<const volatile T>();
}

template <typename T>
void test_is_not_arithmetic_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE(phi::is_not_arithmetic<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE(phi::is_not_arithmetic_v<T>);
#endif
}

template <typename T>
void test_is_not_arithmetic()
{
    test_is_not_arithmetic_impl<T>();
    test_is_not_arithmetic_impl<const T>();
    test_is_not_arithmetic_impl<volatile T>();
    test_is_not_arithmetic_impl<const volatile T>();
}

TEST_CASE("is_arithmetic")
{
    test_is_not_arithmetic<void>();
    test_is_not_arithmetic<phi::nullptr_t>();
    test_is_arithmetic<bool>();
    test_is_arithmetic<char>();
    test_is_arithmetic<signed char>();
    test_is_arithmetic<unsigned char>();
    test_is_arithmetic<short>();
    test_is_arithmetic<unsigned short>();
    test_is_arithmetic<int>();
    test_is_arithmetic<unsigned int>();
    test_is_arithmetic<long>();
    test_is_arithmetic<unsigned long>();
    test_is_arithmetic<long long>();
    test_is_arithmetic<unsigned long long>();
    test_is_arithmetic<float>();
    test_is_arithmetic<double>();
    test_is_arithmetic<long double>();
    test_is_arithmetic<char8_t>();
    test_is_arithmetic<char16_t>();
    test_is_arithmetic<char32_t>();
    test_is_arithmetic<wchar_t>();

    test_is_arithmetic<phi::Boolean>();
    test_is_arithmetic<phi::Integer<signed char>>();
    test_is_arithmetic<phi::Integer<unsigned char>>();
    test_is_arithmetic<phi::Integer<short>>();
    test_is_arithmetic<phi::Integer<unsigned short>>();
    test_is_arithmetic<phi::Integer<int>>();
    test_is_arithmetic<phi::Integer<unsigned int>>();
    test_is_arithmetic<phi::Integer<long>>();
    test_is_arithmetic<phi::Integer<unsigned long>>();
    test_is_arithmetic<phi::Integer<long long>>();
    test_is_arithmetic<phi::Integer<unsigned long long>>();
    test_is_arithmetic<phi::FloatingPoint<float>>();
    test_is_arithmetic<phi::FloatingPoint<double>>();
    test_is_arithmetic<phi::FloatingPoint<long double>>();

    test_is_not_arithmetic<std::vector<int>>();
    test_is_not_arithmetic<phi::ScopePtr<int>>();

    test_is_not_arithmetic<int&>();
    test_is_not_arithmetic<const int&>();
    test_is_not_arithmetic<volatile int&>();
    test_is_not_arithmetic<const volatile int&>();
    test_is_not_arithmetic<int&&>();
    test_is_not_arithmetic<const int&&>();
    test_is_not_arithmetic<volatile int&&>();
    test_is_not_arithmetic<const volatile int&&>();
    test_is_not_arithmetic<int*>();
    test_is_not_arithmetic<const int*>();
    test_is_not_arithmetic<volatile int*>();
    test_is_not_arithmetic<const volatile int*>();
    test_is_not_arithmetic<int**>();
    test_is_not_arithmetic<const int**>();
    test_is_not_arithmetic<volatile int**>();
    test_is_not_arithmetic<const volatile int**>();
    test_is_not_arithmetic<int*&>();
    test_is_not_arithmetic<const int*&>();
    test_is_not_arithmetic<volatile int*&>();
    test_is_not_arithmetic<const volatile int*&>();
    test_is_not_arithmetic<int*&&>();
    test_is_not_arithmetic<const int*&&>();
    test_is_not_arithmetic<volatile int*&&>();
    test_is_not_arithmetic<const volatile int*&&>();
    test_is_not_arithmetic<void*>();
    test_is_not_arithmetic<char[3]>();
    test_is_not_arithmetic<char[]>();
    test_is_not_arithmetic<char[3]>();
    test_is_not_arithmetic<char[]>();
    test_is_not_arithmetic<char* [3]>();
    test_is_not_arithmetic<char*[]>();
    test_is_not_arithmetic<int(*)[3]>();
    test_is_not_arithmetic<int(*)[]>();
    test_is_not_arithmetic<int(&)[3]>();
    test_is_not_arithmetic<int(&)[]>();
    test_is_not_arithmetic<int(&&)[3]>();
    test_is_not_arithmetic<int(&&)[]>();
    test_is_not_arithmetic<char[3][2]>();
    test_is_not_arithmetic<char[][2]>();
    test_is_not_arithmetic<char* [3][2]>();
    test_is_not_arithmetic<char*[][2]>();
    test_is_not_arithmetic<int(*)[3][2]>();
    test_is_not_arithmetic<int(*)[][2]>();
    test_is_not_arithmetic<int(&)[3][2]>();
    test_is_not_arithmetic<int(&)[][2]>();
    test_is_not_arithmetic<int(&&)[3][2]>();
    test_is_not_arithmetic<int(&&)[][2]>();
    test_is_not_arithmetic<Class>();
    test_is_not_arithmetic<Class[]>();
    test_is_not_arithmetic<Class[2]>();
    test_is_not_arithmetic<Template<void>>();
    test_is_not_arithmetic<Template<int>>();
    test_is_not_arithmetic<Template<Class>>();
    test_is_not_arithmetic<Template<incomplete_type>>();
    test_is_not_arithmetic<VariadicTemplate<>>();
    test_is_not_arithmetic<VariadicTemplate<void>>();
    test_is_not_arithmetic<VariadicTemplate<int>>();
    test_is_not_arithmetic<VariadicTemplate<Class>>();
    test_is_not_arithmetic<VariadicTemplate<incomplete_type>>();
    test_is_not_arithmetic<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_arithmetic<PublicDerviedFromTemplate<Base>>();
    test_is_not_arithmetic<PublicDerviedFromTemplate<Derived>>();
    test_is_not_arithmetic<PublicDerviedFromTemplate<Class>>();
    test_is_not_arithmetic<PrivateDerviedFromTemplate<Base>>();
    test_is_not_arithmetic<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_arithmetic<PrivateDerviedFromTemplate<Class>>();
    test_is_not_arithmetic<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_arithmetic<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_arithmetic<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_arithmetic<Union>();
    test_is_not_arithmetic<NonEmptyUnion>();
    test_is_not_arithmetic<Empty>();
    test_is_not_arithmetic<NotEmpty>();
    test_is_not_arithmetic<bit_zero>();
    test_is_not_arithmetic<bit_one>();
    test_is_not_arithmetic<Base>();
    test_is_not_arithmetic<Derived>();
    test_is_not_arithmetic<Abstract>();
    test_is_not_arithmetic<PublicAbstract>();
    test_is_not_arithmetic<PrivateAbstract>();
    test_is_not_arithmetic<ProtectedAbstract>();
    test_is_not_arithmetic<AbstractTemplate<int>>();
    test_is_not_arithmetic<AbstractTemplate<double>>();
    test_is_not_arithmetic<AbstractTemplate<Class>>();
    test_is_not_arithmetic<AbstractTemplate<incomplete_type>>();
    test_is_not_arithmetic<Final>();
    test_is_not_arithmetic<PublicDestructor>();
    test_is_not_arithmetic<ProtectedDestructor>();
    test_is_not_arithmetic<PrivateDestructor>();
    test_is_not_arithmetic<VirtualPublicDestructor>();
    test_is_not_arithmetic<VirtualProtectedDestructor>();
    test_is_not_arithmetic<VirtualPrivateDestructor>();
    test_is_not_arithmetic<PurePublicDestructor>();
    test_is_not_arithmetic<PureProtectedDestructor>();
    test_is_not_arithmetic<PurePrivateDestructor>();
    test_is_not_arithmetic<DeletedPublicDestructor>();
    test_is_not_arithmetic<DeletedProtectedDestructor>();
    test_is_not_arithmetic<DeletedPrivateDestructor>();
    test_is_not_arithmetic<DeletedVirtualPublicDestructor>();
    test_is_not_arithmetic<DeletedVirtualProtectedDestructor>();
    test_is_not_arithmetic<DeletedVirtualPrivateDestructor>();
    test_is_not_arithmetic<Enum>();
    test_is_not_arithmetic<EnumSigned>();
    test_is_not_arithmetic<EnumUnsigned>();
    test_is_not_arithmetic<EnumClass>();
    test_is_not_arithmetic<EnumStruct>();
    test_is_not_arithmetic<Function>();
    test_is_not_arithmetic<FunctionPtr>();
    test_is_not_arithmetic<MemberObjectPtr>();
    test_is_not_arithmetic<MemberFunctionPtr>();
    test_is_not_arithmetic<incomplete_type>();
    test_is_not_arithmetic<IncompleteTemplate<void>>();
    test_is_not_arithmetic<IncompleteTemplate<int>>();
    test_is_not_arithmetic<IncompleteTemplate<Class>>();
    test_is_not_arithmetic<IncompleteTemplate<incomplete_type>>();
    test_is_not_arithmetic<IncompleteVariadicTemplate<>>();
    test_is_not_arithmetic<IncompleteVariadicTemplate<void>>();
    test_is_not_arithmetic<IncompleteVariadicTemplate<int>>();
    test_is_not_arithmetic<IncompleteVariadicTemplate<Class>>();
    test_is_not_arithmetic<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_arithmetic<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_arithmetic<int Class::*>();
    test_is_not_arithmetic<float Class::*>();
    test_is_not_arithmetic<void * Class::*>();
    test_is_not_arithmetic<int * Class::*>();
    test_is_not_arithmetic<int Class::*&>();
    test_is_not_arithmetic<float Class::*&>();
    test_is_not_arithmetic<void * Class::*&>();
    test_is_not_arithmetic<int * Class::*&>();
    test_is_not_arithmetic<int Class::*&&>();
    test_is_not_arithmetic<float Class::*&&>();
    test_is_not_arithmetic<void * Class::*&&>();
    test_is_not_arithmetic<int * Class::*&&>();
    test_is_not_arithmetic<int Class::*const>();
    test_is_not_arithmetic<float Class::*const>();
    test_is_not_arithmetic<void * Class::*const>();
    test_is_not_arithmetic<int Class::*const&>();
    test_is_not_arithmetic<float Class::*const&>();
    test_is_not_arithmetic<void * Class::*const&>();
    test_is_not_arithmetic<int Class::*const&&>();
    test_is_not_arithmetic<float Class::*const&&>();
    test_is_not_arithmetic<void * Class::*const&&>();
    test_is_not_arithmetic<int Class::*volatile>();
    test_is_not_arithmetic<float Class::*volatile>();
    test_is_not_arithmetic<void * Class::*volatile>();
    test_is_not_arithmetic<int Class::*volatile&>();
    test_is_not_arithmetic<float Class::*volatile&>();
    test_is_not_arithmetic<void * Class::*volatile&>();
    test_is_not_arithmetic<int Class::*volatile&&>();
    test_is_not_arithmetic<float Class::*volatile&&>();
    test_is_not_arithmetic<void * Class::*volatile&&>();
    test_is_not_arithmetic<int Class::*const volatile>();
    test_is_not_arithmetic<float Class::*const volatile>();
    test_is_not_arithmetic<void * Class::*const volatile>();
    test_is_not_arithmetic<int Class::*const volatile&>();
    test_is_not_arithmetic<float Class::*const volatile&>();
    test_is_not_arithmetic<void * Class::*const volatile&>();
    test_is_not_arithmetic<int Class::*const volatile&&>();
    test_is_not_arithmetic<float Class::*const volatile&&>();
    test_is_not_arithmetic<void * Class::*const volatile&&>();
    test_is_not_arithmetic<NonCopyable>();
    test_is_not_arithmetic<NonMoveable>();
    test_is_not_arithmetic<NonConstructible>();
    test_is_not_arithmetic<Tracked>();
    test_is_not_arithmetic<TrapConstructible>();
    test_is_not_arithmetic<TrapImplicitConversion>();
    test_is_not_arithmetic<TrapComma>();
    test_is_not_arithmetic<TrapCall>();
    test_is_not_arithmetic<TrapSelfAssign>();
    test_is_not_arithmetic<TrapDeref>();
    test_is_not_arithmetic<TrapArraySubscript>();

    test_is_not_arithmetic<void()>();
    test_is_not_arithmetic<void()&>();
    test_is_not_arithmetic<void() &&>();
    test_is_not_arithmetic<void() const>();
    test_is_not_arithmetic<void() const&>();
    test_is_not_arithmetic<void() const&&>();
    test_is_not_arithmetic<void() volatile>();
    test_is_not_arithmetic<void() volatile&>();
    test_is_not_arithmetic<void() volatile&&>();
    test_is_not_arithmetic<void() const volatile>();
    test_is_not_arithmetic<void() const volatile&>();
    test_is_not_arithmetic<void() const volatile&&>();
    test_is_not_arithmetic<void() noexcept>();
    test_is_not_arithmetic<void()& noexcept>();
    test_is_not_arithmetic<void()&& noexcept>();
    test_is_not_arithmetic<void() const noexcept>();
    test_is_not_arithmetic<void() const& noexcept>();
    test_is_not_arithmetic<void() const&& noexcept>();
    test_is_not_arithmetic<void() volatile noexcept>();
    test_is_not_arithmetic<void() volatile& noexcept>();
    test_is_not_arithmetic<void() volatile&& noexcept>();
    test_is_not_arithmetic<void() const volatile noexcept>();
    test_is_not_arithmetic<void() const volatile& noexcept>();
    test_is_not_arithmetic<void() const volatile&& noexcept>();

    test_is_not_arithmetic<void(int)>();
    test_is_not_arithmetic<void(int)&>();
    test_is_not_arithmetic<void(int) &&>();
    test_is_not_arithmetic<void(int) const>();
    test_is_not_arithmetic<void(int) const&>();
    test_is_not_arithmetic<void(int) const&&>();
    test_is_not_arithmetic<void(int) volatile>();
    test_is_not_arithmetic<void(int) volatile&>();
    test_is_not_arithmetic<void(int) volatile&&>();
    test_is_not_arithmetic<void(int) const volatile>();
    test_is_not_arithmetic<void(int) const volatile&>();
    test_is_not_arithmetic<void(int) const volatile&&>();
    test_is_not_arithmetic<void(int) noexcept>();
    test_is_not_arithmetic<void(int)& noexcept>();
    test_is_not_arithmetic<void(int)&& noexcept>();
    test_is_not_arithmetic<void(int) const noexcept>();
    test_is_not_arithmetic<void(int) const& noexcept>();
    test_is_not_arithmetic<void(int) const&& noexcept>();
    test_is_not_arithmetic<void(int) volatile noexcept>();
    test_is_not_arithmetic<void(int) volatile& noexcept>();
    test_is_not_arithmetic<void(int) volatile&& noexcept>();
    test_is_not_arithmetic<void(int) const volatile noexcept>();
    test_is_not_arithmetic<void(int) const volatile& noexcept>();
    test_is_not_arithmetic<void(int) const volatile&& noexcept>();

    test_is_not_arithmetic<void(...)>();
    test_is_not_arithmetic<void(...)&>();
    test_is_not_arithmetic<void(...) &&>();
    test_is_not_arithmetic<void(...) const>();
    test_is_not_arithmetic<void(...) const&>();
    test_is_not_arithmetic<void(...) const&&>();
    test_is_not_arithmetic<void(...) volatile>();
    test_is_not_arithmetic<void(...) volatile&>();
    test_is_not_arithmetic<void(...) volatile&&>();
    test_is_not_arithmetic<void(...) const volatile>();
    test_is_not_arithmetic<void(...) const volatile&>();
    test_is_not_arithmetic<void(...) const volatile&&>();
    test_is_not_arithmetic<void(...) noexcept>();
    test_is_not_arithmetic<void(...)& noexcept>();
    test_is_not_arithmetic<void(...)&& noexcept>();
    test_is_not_arithmetic<void(...) const noexcept>();
    test_is_not_arithmetic<void(...) const& noexcept>();
    test_is_not_arithmetic<void(...) const&& noexcept>();
    test_is_not_arithmetic<void(...) volatile noexcept>();
    test_is_not_arithmetic<void(...) volatile& noexcept>();
    test_is_not_arithmetic<void(...) volatile&& noexcept>();
    test_is_not_arithmetic<void(...) const volatile noexcept>();
    test_is_not_arithmetic<void(...) const volatile& noexcept>();
    test_is_not_arithmetic<void(...) const volatile&& noexcept>();

    test_is_not_arithmetic<void(int, ...)>();
    test_is_not_arithmetic<void(int, ...)&>();
    test_is_not_arithmetic<void(int, ...) &&>();
    test_is_not_arithmetic<void(int, ...) const>();
    test_is_not_arithmetic<void(int, ...) const&>();
    test_is_not_arithmetic<void(int, ...) const&&>();
    test_is_not_arithmetic<void(int, ...) volatile>();
    test_is_not_arithmetic<void(int, ...) volatile&>();
    test_is_not_arithmetic<void(int, ...) volatile&&>();
    test_is_not_arithmetic<void(int, ...) const volatile>();
    test_is_not_arithmetic<void(int, ...) const volatile&>();
    test_is_not_arithmetic<void(int, ...) const volatile&&>();
    test_is_not_arithmetic<void(int, ...) noexcept>();
    test_is_not_arithmetic<void(int, ...)& noexcept>();
    test_is_not_arithmetic<void(int, ...)&& noexcept>();
    test_is_not_arithmetic<void(int, ...) const noexcept>();
    test_is_not_arithmetic<void(int, ...) const& noexcept>();
    test_is_not_arithmetic<void(int, ...) const&& noexcept>();
    test_is_not_arithmetic<void(int, ...) volatile noexcept>();
    test_is_not_arithmetic<void(int, ...) volatile& noexcept>();
    test_is_not_arithmetic<void(int, ...) volatile&& noexcept>();
    test_is_not_arithmetic<void(int, ...) const volatile noexcept>();
    test_is_not_arithmetic<void(int, ...) const volatile& noexcept>();
    test_is_not_arithmetic<void(int, ...) const volatile&& noexcept>();

    test_is_not_arithmetic<int()>();
    test_is_not_arithmetic<int()&>();
    test_is_not_arithmetic<int() &&>();
    test_is_not_arithmetic<int() const>();
    test_is_not_arithmetic<int() const&>();
    test_is_not_arithmetic<int() const&&>();
    test_is_not_arithmetic<int() volatile>();
    test_is_not_arithmetic<int() volatile&>();
    test_is_not_arithmetic<int() volatile&&>();
    test_is_not_arithmetic<int() const volatile>();
    test_is_not_arithmetic<int() const volatile&>();
    test_is_not_arithmetic<int() const volatile&&>();
    test_is_not_arithmetic<int() noexcept>();
    test_is_not_arithmetic<int()& noexcept>();
    test_is_not_arithmetic<int()&& noexcept>();
    test_is_not_arithmetic<int() const noexcept>();
    test_is_not_arithmetic<int() const& noexcept>();
    test_is_not_arithmetic<int() const&& noexcept>();
    test_is_not_arithmetic<int() volatile noexcept>();
    test_is_not_arithmetic<int() volatile& noexcept>();
    test_is_not_arithmetic<int() volatile&& noexcept>();
    test_is_not_arithmetic<int() const volatile noexcept>();
    test_is_not_arithmetic<int() const volatile& noexcept>();
    test_is_not_arithmetic<int() const volatile&& noexcept>();

    test_is_not_arithmetic<int(int)>();
    test_is_not_arithmetic<int(int)&>();
    test_is_not_arithmetic<int(int) &&>();
    test_is_not_arithmetic<int(int) const>();
    test_is_not_arithmetic<int(int) const&>();
    test_is_not_arithmetic<int(int) const&&>();
    test_is_not_arithmetic<int(int) volatile>();
    test_is_not_arithmetic<int(int) volatile&>();
    test_is_not_arithmetic<int(int) volatile&&>();
    test_is_not_arithmetic<int(int) const volatile>();
    test_is_not_arithmetic<int(int) const volatile&>();
    test_is_not_arithmetic<int(int) const volatile&&>();
    test_is_not_arithmetic<int(int) noexcept>();
    test_is_not_arithmetic<int(int)& noexcept>();
    test_is_not_arithmetic<int(int)&& noexcept>();
    test_is_not_arithmetic<int(int) const noexcept>();
    test_is_not_arithmetic<int(int) const& noexcept>();
    test_is_not_arithmetic<int(int) const&& noexcept>();
    test_is_not_arithmetic<int(int) volatile noexcept>();
    test_is_not_arithmetic<int(int) volatile& noexcept>();
    test_is_not_arithmetic<int(int) volatile&& noexcept>();
    test_is_not_arithmetic<int(int) const volatile noexcept>();
    test_is_not_arithmetic<int(int) const volatile& noexcept>();
    test_is_not_arithmetic<int(int) const volatile&& noexcept>();

    test_is_not_arithmetic<int(...)>();
    test_is_not_arithmetic<int(...)&>();
    test_is_not_arithmetic<int(...) &&>();
    test_is_not_arithmetic<int(...) const>();
    test_is_not_arithmetic<int(...) const&>();
    test_is_not_arithmetic<int(...) const&&>();
    test_is_not_arithmetic<int(...) volatile>();
    test_is_not_arithmetic<int(...) volatile&>();
    test_is_not_arithmetic<int(...) volatile&&>();
    test_is_not_arithmetic<int(...) const volatile>();
    test_is_not_arithmetic<int(...) const volatile&>();
    test_is_not_arithmetic<int(...) const volatile&&>();
    test_is_not_arithmetic<int(...) noexcept>();
    test_is_not_arithmetic<int(...)& noexcept>();
    test_is_not_arithmetic<int(...)&& noexcept>();
    test_is_not_arithmetic<int(...) const noexcept>();
    test_is_not_arithmetic<int(...) const& noexcept>();
    test_is_not_arithmetic<int(...) const&& noexcept>();
    test_is_not_arithmetic<int(...) volatile noexcept>();
    test_is_not_arithmetic<int(...) volatile& noexcept>();
    test_is_not_arithmetic<int(...) volatile&& noexcept>();
    test_is_not_arithmetic<int(...) const volatile noexcept>();
    test_is_not_arithmetic<int(...) const volatile& noexcept>();
    test_is_not_arithmetic<int(...) const volatile&& noexcept>();

    test_is_not_arithmetic<int(int, ...)>();
    test_is_not_arithmetic<int(int, ...)&>();
    test_is_not_arithmetic<int(int, ...) &&>();
    test_is_not_arithmetic<int(int, ...) const>();
    test_is_not_arithmetic<int(int, ...) const&>();
    test_is_not_arithmetic<int(int, ...) const&&>();
    test_is_not_arithmetic<int(int, ...) volatile>();
    test_is_not_arithmetic<int(int, ...) volatile&>();
    test_is_not_arithmetic<int(int, ...) volatile&&>();
    test_is_not_arithmetic<int(int, ...) const volatile>();
    test_is_not_arithmetic<int(int, ...) const volatile&>();
    test_is_not_arithmetic<int(int, ...) const volatile&&>();
    test_is_not_arithmetic<int(int, ...) noexcept>();
    test_is_not_arithmetic<int(int, ...)& noexcept>();
    test_is_not_arithmetic<int(int, ...)&& noexcept>();
    test_is_not_arithmetic<int(int, ...) const noexcept>();
    test_is_not_arithmetic<int(int, ...) const& noexcept>();
    test_is_not_arithmetic<int(int, ...) const&& noexcept>();
    test_is_not_arithmetic<int(int, ...) volatile noexcept>();
    test_is_not_arithmetic<int(int, ...) volatile& noexcept>();
    test_is_not_arithmetic<int(int, ...) volatile&& noexcept>();
    test_is_not_arithmetic<int(int, ...) const volatile noexcept>();
    test_is_not_arithmetic<int(int, ...) const volatile& noexcept>();
    test_is_not_arithmetic<int(int, ...) const volatile&& noexcept>();

    test_is_not_arithmetic<void (*)()>();
    test_is_not_arithmetic<void (*)() noexcept>();

    test_is_not_arithmetic<void (*)(int)>();
    test_is_not_arithmetic<void (*)(int) noexcept>();

    test_is_not_arithmetic<void (*)(...)>();
    test_is_not_arithmetic<void (*)(...) noexcept>();

    test_is_not_arithmetic<void (*)(int, ...)>();
    test_is_not_arithmetic<void (*)(int, ...) noexcept>();

    test_is_not_arithmetic<int (*)()>();
    test_is_not_arithmetic<int (*)() noexcept>();

    test_is_not_arithmetic<int (*)(int)>();
    test_is_not_arithmetic<int (*)(int) noexcept>();

    test_is_not_arithmetic<int (*)(...)>();
    test_is_not_arithmetic<int (*)(...) noexcept>();

    test_is_not_arithmetic<int (*)(int, ...)>();
    test_is_not_arithmetic<int (*)(int, ...) noexcept>();

    test_is_not_arithmetic<void (&)()>();
    test_is_not_arithmetic<void (&)() noexcept>();

    test_is_not_arithmetic<void (&)(int)>();
    test_is_not_arithmetic<void (&)(int) noexcept>();

    test_is_not_arithmetic<void (&)(...)>();
    test_is_not_arithmetic<void (&)(...) noexcept>();

    test_is_not_arithmetic<void (&)(int, ...)>();
    test_is_not_arithmetic<void (&)(int, ...) noexcept>();

    test_is_not_arithmetic<int (&)()>();
    test_is_not_arithmetic<int (&)() noexcept>();

    test_is_not_arithmetic<int (&)(int)>();
    test_is_not_arithmetic<int (&)(int) noexcept>();

    test_is_not_arithmetic<int (&)(...)>();
    test_is_not_arithmetic<int (&)(...) noexcept>();

    test_is_not_arithmetic<int (&)(int, ...)>();
    test_is_not_arithmetic<int (&)(int, ...) noexcept>();

    test_is_not_arithmetic<void(&&)()>();
    test_is_not_arithmetic<void(&&)() noexcept>();

    test_is_not_arithmetic<void(&&)(int)>();
    test_is_not_arithmetic<void(&&)(int) noexcept>();

    test_is_not_arithmetic<void(&&)(...)>();
    test_is_not_arithmetic<void(&&)(...) noexcept>();

    test_is_not_arithmetic<void(&&)(int, ...)>();
    test_is_not_arithmetic<void(&&)(int, ...) noexcept>();

    test_is_not_arithmetic<int(&&)()>();
    test_is_not_arithmetic<int(&&)() noexcept>();

    test_is_not_arithmetic<int(&&)(int)>();
    test_is_not_arithmetic<int(&&)(int) noexcept>();

    test_is_not_arithmetic<int(&&)(...)>();
    test_is_not_arithmetic<int(&&)(...) noexcept>();

    test_is_not_arithmetic<int(&&)(int, ...)>();
    test_is_not_arithmetic<int(&&)(int, ...) noexcept>();

    test_is_not_arithmetic<void (Class::*)()>();
    test_is_not_arithmetic<void (Class::*)()&>();
    test_is_not_arithmetic<void (Class::*)() &&>();
    test_is_not_arithmetic<void (Class::*)() const>();
    test_is_not_arithmetic<void (Class::*)() const&>();
    test_is_not_arithmetic<void (Class::*)() const&&>();
    test_is_not_arithmetic<void (Class::*)() noexcept>();
    test_is_not_arithmetic<void (Class::*)()& noexcept>();
    test_is_not_arithmetic<void (Class::*)()&& noexcept>();
    test_is_not_arithmetic<void (Class::*)() const noexcept>();
    test_is_not_arithmetic<void (Class::*)() const& noexcept>();
    test_is_not_arithmetic<void (Class::*)() const&& noexcept>();

    test_is_not_arithmetic<void (Class::*)(int)>();
    test_is_not_arithmetic<void (Class::*)(int)&>();
    test_is_not_arithmetic<void (Class::*)(int) &&>();
    test_is_not_arithmetic<void (Class::*)(int) const>();
    test_is_not_arithmetic<void (Class::*)(int) const&>();
    test_is_not_arithmetic<void (Class::*)(int) const&&>();
    test_is_not_arithmetic<void (Class::*)(int) noexcept>();
    test_is_not_arithmetic<void (Class::*)(int)& noexcept>();
    test_is_not_arithmetic<void (Class::*)(int)&& noexcept>();
    test_is_not_arithmetic<void (Class::*)(int) const noexcept>();
    test_is_not_arithmetic<void (Class::*)(int) const& noexcept>();
    test_is_not_arithmetic<void (Class::*)(int) const&& noexcept>();

    test_is_not_arithmetic<void (Class::*)(...)>();
    test_is_not_arithmetic<void (Class::*)(...)&>();
    test_is_not_arithmetic<void (Class::*)(...) &&>();
    test_is_not_arithmetic<void (Class::*)(...) const>();
    test_is_not_arithmetic<void (Class::*)(...) const&>();
    test_is_not_arithmetic<void (Class::*)(...) const&&>();
    test_is_not_arithmetic<void (Class::*)(...) noexcept>();
    test_is_not_arithmetic<void (Class::*)(...)& noexcept>();
    test_is_not_arithmetic<void (Class::*)(...)&& noexcept>();
    test_is_not_arithmetic<void (Class::*)(...) const noexcept>();
    test_is_not_arithmetic<void (Class::*)(...) const& noexcept>();
    test_is_not_arithmetic<void (Class::*)(...) const&& noexcept>();

    test_is_not_arithmetic<void (Class::*)(int, ...)>();
    test_is_not_arithmetic<void (Class::*)(int, ...)&>();
    test_is_not_arithmetic<void (Class::*)(int, ...) &&>();
    test_is_not_arithmetic<void (Class::*)(int, ...) const>();
    test_is_not_arithmetic<void (Class::*)(int, ...) const&>();
    test_is_not_arithmetic<void (Class::*)(int, ...) const&&>();
    test_is_not_arithmetic<void (Class::*)(int, ...) noexcept>();
    test_is_not_arithmetic<void (Class::*)(int, ...)& noexcept>();
    test_is_not_arithmetic<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_arithmetic<void (Class::*)(int, ...) const noexcept>();
    test_is_not_arithmetic<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_arithmetic<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_arithmetic<int (Class::*)()>();
    test_is_not_arithmetic<int (Class::*)()&>();
    test_is_not_arithmetic<int (Class::*)() &&>();
    test_is_not_arithmetic<int (Class::*)() const>();
    test_is_not_arithmetic<int (Class::*)() const&>();
    test_is_not_arithmetic<int (Class::*)() const&&>();
    test_is_not_arithmetic<int (Class::*)() noexcept>();
    test_is_not_arithmetic<int (Class::*)()& noexcept>();
    test_is_not_arithmetic<int (Class::*)()&& noexcept>();
    test_is_not_arithmetic<int (Class::*)() const noexcept>();
    test_is_not_arithmetic<int (Class::*)() const& noexcept>();
    test_is_not_arithmetic<int (Class::*)() const&& noexcept>();

    test_is_not_arithmetic<int (Class::*)(int)>();
    test_is_not_arithmetic<int (Class::*)(int)&>();
    test_is_not_arithmetic<int (Class::*)(int) &&>();
    test_is_not_arithmetic<int (Class::*)(int) const>();
    test_is_not_arithmetic<int (Class::*)(int) const&>();
    test_is_not_arithmetic<int (Class::*)(int) const&&>();
    test_is_not_arithmetic<int (Class::*)(int) noexcept>();
    test_is_not_arithmetic<int (Class::*)(int)& noexcept>();
    test_is_not_arithmetic<int (Class::*)(int)&& noexcept>();
    test_is_not_arithmetic<int (Class::*)(int) const noexcept>();
    test_is_not_arithmetic<int (Class::*)(int) const& noexcept>();
    test_is_not_arithmetic<int (Class::*)(int) const&& noexcept>();

    test_is_not_arithmetic<int (Class::*)(...)>();
    test_is_not_arithmetic<int (Class::*)(...)&>();
    test_is_not_arithmetic<int (Class::*)(...) &&>();
    test_is_not_arithmetic<int (Class::*)(...) const>();
    test_is_not_arithmetic<int (Class::*)(...) const&>();
    test_is_not_arithmetic<int (Class::*)(...) const&&>();
    test_is_not_arithmetic<int (Class::*)(...) noexcept>();
    test_is_not_arithmetic<int (Class::*)(...)& noexcept>();
    test_is_not_arithmetic<int (Class::*)(...)&& noexcept>();
    test_is_not_arithmetic<int (Class::*)(...) const noexcept>();
    test_is_not_arithmetic<int (Class::*)(...) const& noexcept>();
    test_is_not_arithmetic<int (Class::*)(...) const&& noexcept>();

    test_is_not_arithmetic<int (Class::*)(int, ...)>();
    test_is_not_arithmetic<int (Class::*)(int, ...)&>();
    test_is_not_arithmetic<int (Class::*)(int, ...) &&>();
    test_is_not_arithmetic<int (Class::*)(int, ...) const>();
    test_is_not_arithmetic<int (Class::*)(int, ...) const&>();
    test_is_not_arithmetic<int (Class::*)(int, ...) const&&>();
    test_is_not_arithmetic<int (Class::*)(int, ...) noexcept>();
    test_is_not_arithmetic<int (Class::*)(int, ...)& noexcept>();
    test_is_not_arithmetic<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_arithmetic<int (Class::*)(int, ...) const noexcept>();
    test_is_not_arithmetic<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_arithmetic<int (Class::*)(int, ...) const&& noexcept>();
}
