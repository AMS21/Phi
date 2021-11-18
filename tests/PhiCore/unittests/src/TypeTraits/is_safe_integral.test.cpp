#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_safe_integral.hpp>
#include <vector>

template <typename T>
void test_is_safe_integral_impl()
{
    STATIC_REQUIRE(phi::is_safe_integral<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_integral<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_integral_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_integral_v<T>);
#endif
}

template <typename T>
void test_is_safe_integral()
{
    test_is_safe_integral_impl<T>();
    test_is_safe_integral_impl<const T>();
    test_is_safe_integral_impl<volatile T>();
    test_is_safe_integral_impl<const volatile T>();
}

template <typename T>
void test_is_not_safe_integral_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_integral<T>::value);
    STATIC_REQUIRE(phi::is_not_safe_integral<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_integral_v<T>);
    STATIC_REQUIRE(phi::is_not_safe_integral_v<T>);
#endif
}

template <typename T>
void test_is_not_safe_integral()
{
    test_is_not_safe_integral_impl<T>();
    test_is_not_safe_integral_impl<const T>();
    test_is_not_safe_integral_impl<volatile T>();
    test_is_not_safe_integral_impl<const volatile T>();
}

TEST_CASE("is_safe_integral")
{
    test_is_safe_integral<phi::Boolean>();
    test_is_safe_integral<phi::Integer<signed char>>();
    test_is_safe_integral<phi::Integer<unsigned char>>();
    test_is_safe_integral<phi::Integer<short>>();
    test_is_safe_integral<phi::Integer<unsigned short>>();
    test_is_safe_integral<phi::Integer<int>>();
    test_is_safe_integral<phi::Integer<unsigned int>>();
    test_is_safe_integral<phi::Integer<long>>();
    test_is_safe_integral<phi::Integer<unsigned long>>();
    test_is_safe_integral<phi::Integer<long long>>();
    test_is_safe_integral<phi::Integer<unsigned long long>>();

    test_is_not_safe_integral<void>();
    test_is_not_safe_integral<phi::nullptr_t>();
    test_is_not_safe_integral<bool>();
    test_is_not_safe_integral<char>();
    test_is_not_safe_integral<signed char>();
    test_is_not_safe_integral<unsigned char>();
    test_is_not_safe_integral<short>();
    test_is_not_safe_integral<unsigned short>();
    test_is_not_safe_integral<int>();
    test_is_not_safe_integral<unsigned int>();
    test_is_not_safe_integral<long>();
    test_is_not_safe_integral<unsigned long>();
    test_is_not_safe_integral<long long>();
    test_is_not_safe_integral<unsigned long long>();
    test_is_not_safe_integral<float>();
    test_is_not_safe_integral<double>();
    test_is_not_safe_integral<long double>();
    test_is_not_safe_integral<char8_t>();
    test_is_not_safe_integral<char16_t>();
    test_is_not_safe_integral<char32_t>();
    test_is_not_safe_integral<wchar_t>();

    test_is_not_safe_integral<phi::FloatingPoint<float>>();
    test_is_not_safe_integral<phi::FloatingPoint<double>>();
    test_is_not_safe_integral<phi::FloatingPoint<long double>>();

    test_is_not_safe_integral<std::vector<int>>();
    test_is_not_safe_integral<phi::ScopePtr<int>>();

    test_is_not_safe_integral<int&>();
    test_is_not_safe_integral<const int&>();
    test_is_not_safe_integral<volatile int&>();
    test_is_not_safe_integral<const volatile int&>();
    test_is_not_safe_integral<int&&>();
    test_is_not_safe_integral<const int&&>();
    test_is_not_safe_integral<volatile int&&>();
    test_is_not_safe_integral<const volatile int&&>();
    test_is_not_safe_integral<int*>();
    test_is_not_safe_integral<const int*>();
    test_is_not_safe_integral<volatile int*>();
    test_is_not_safe_integral<const volatile int*>();
    test_is_not_safe_integral<int**>();
    test_is_not_safe_integral<const int**>();
    test_is_not_safe_integral<volatile int**>();
    test_is_not_safe_integral<const volatile int**>();
    test_is_not_safe_integral<int*&>();
    test_is_not_safe_integral<const int*&>();
    test_is_not_safe_integral<volatile int*&>();
    test_is_not_safe_integral<const volatile int*&>();
    test_is_not_safe_integral<int*&&>();
    test_is_not_safe_integral<const int*&&>();
    test_is_not_safe_integral<volatile int*&&>();
    test_is_not_safe_integral<const volatile int*&&>();
    test_is_not_safe_integral<void*>();
    test_is_not_safe_integral<char[3]>();
    test_is_not_safe_integral<char[]>();
    test_is_not_safe_integral<char* [3]>();
    test_is_not_safe_integral<char*[]>();
    test_is_not_safe_integral<int(*)[3]>();
    test_is_not_safe_integral<int(*)[]>();
    test_is_not_safe_integral<int(&)[3]>();
    test_is_not_safe_integral<int(&)[]>();
    test_is_not_safe_integral<int(&&)[3]>();
    test_is_not_safe_integral<int(&&)[]>();
    test_is_not_safe_integral<char[3][2]>();
    test_is_not_safe_integral<char[][2]>();
    test_is_not_safe_integral<char* [3][2]>();
    test_is_not_safe_integral<char*[][2]>();
    test_is_not_safe_integral<int(*)[3][2]>();
    test_is_not_safe_integral<int(*)[][2]>();
    test_is_not_safe_integral<int(&)[3][2]>();
    test_is_not_safe_integral<int(&)[][2]>();
    test_is_not_safe_integral<int(&&)[3][2]>();
    test_is_not_safe_integral<int(&&)[][2]>();
    test_is_not_safe_integral<Class>();
    test_is_not_safe_integral<Class[]>();
    test_is_not_safe_integral<Class[2]>();
    test_is_not_safe_integral<Template<void>>();
    test_is_not_safe_integral<Template<int>>();
    test_is_not_safe_integral<Template<Class>>();
    test_is_not_safe_integral<Template<incomplete_type>>();
    test_is_not_safe_integral<VariadicTemplate<>>();
    test_is_not_safe_integral<VariadicTemplate<void>>();
    test_is_not_safe_integral<VariadicTemplate<int>>();
    test_is_not_safe_integral<VariadicTemplate<Class>>();
    test_is_not_safe_integral<VariadicTemplate<incomplete_type>>();
    test_is_not_safe_integral<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_integral<PublicDerviedFromTemplate<Base>>();
    test_is_not_safe_integral<PublicDerviedFromTemplate<Derived>>();
    test_is_not_safe_integral<PublicDerviedFromTemplate<Class>>();
    test_is_not_safe_integral<PrivateDerviedFromTemplate<Base>>();
    test_is_not_safe_integral<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_safe_integral<PrivateDerviedFromTemplate<Class>>();
    test_is_not_safe_integral<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_safe_integral<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_safe_integral<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_safe_integral<Union>();
    test_is_not_safe_integral<NonEmptyUnion>();
    test_is_not_safe_integral<Empty>();
    test_is_not_safe_integral<NotEmpty>();
    test_is_not_safe_integral<bit_zero>();
    test_is_not_safe_integral<bit_one>();
    test_is_not_safe_integral<Base>();
    test_is_not_safe_integral<Derived>();
    test_is_not_safe_integral<Abstract>();
    test_is_not_safe_integral<PublicAbstract>();
    test_is_not_safe_integral<PrivateAbstract>();
    test_is_not_safe_integral<ProtectedAbstract>();
    test_is_not_safe_integral<AbstractTemplate<int>>();
    test_is_not_safe_integral<AbstractTemplate<double>>();
    test_is_not_safe_integral<AbstractTemplate<Class>>();
    test_is_not_safe_integral<AbstractTemplate<incomplete_type>>();
    test_is_not_safe_integral<Final>();
    test_is_not_safe_integral<PublicDestructor>();
    test_is_not_safe_integral<ProtectedDestructor>();
    test_is_not_safe_integral<PrivateDestructor>();
    test_is_not_safe_integral<VirtualPublicDestructor>();
    test_is_not_safe_integral<VirtualProtectedDestructor>();
    test_is_not_safe_integral<VirtualPrivateDestructor>();
    test_is_not_safe_integral<PurePublicDestructor>();
    test_is_not_safe_integral<PureProtectedDestructor>();
    test_is_not_safe_integral<PurePrivateDestructor>();
    test_is_not_safe_integral<DeletedPublicDestructor>();
    test_is_not_safe_integral<DeletedProtectedDestructor>();
    test_is_not_safe_integral<DeletedPrivateDestructor>();
    test_is_not_safe_integral<DeletedVirtualPublicDestructor>();
    test_is_not_safe_integral<DeletedVirtualProtectedDestructor>();
    test_is_not_safe_integral<DeletedVirtualPrivateDestructor>();
    test_is_not_safe_integral<Final>();
    test_is_not_safe_integral<Enum>();
    test_is_not_safe_integral<EnumSigned>();
    test_is_not_safe_integral<EnumUnsigned>();
    test_is_not_safe_integral<EnumClass>();
    test_is_not_safe_integral<EnumStruct>();
    test_is_not_safe_integral<Function>();
    test_is_not_safe_integral<FunctionPtr>();
    test_is_not_safe_integral<MemberObjectPtr>();
    test_is_not_safe_integral<MemberFunctionPtr>();
    test_is_not_safe_integral<incomplete_type>();
    test_is_not_safe_integral<IncompleteTemplate<void>>();
    test_is_not_safe_integral<IncompleteTemplate<int>>();
    test_is_not_safe_integral<IncompleteTemplate<Class>>();
    test_is_not_safe_integral<IncompleteTemplate<incomplete_type>>();
    test_is_not_safe_integral<IncompleteVariadicTemplate<>>();
    test_is_not_safe_integral<IncompleteVariadicTemplate<void>>();
    test_is_not_safe_integral<IncompleteVariadicTemplate<int>>();
    test_is_not_safe_integral<IncompleteVariadicTemplate<Class>>();
    test_is_not_safe_integral<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_safe_integral<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_safe_integral<int Class::*>();
    test_is_not_safe_integral<float Class::*>();
    test_is_not_safe_integral<void * Class::*>();
    test_is_not_safe_integral<int * Class::*>();
    test_is_not_safe_integral<int Class::*&>();
    test_is_not_safe_integral<float Class::*&>();
    test_is_not_safe_integral<void * Class::*&>();
    test_is_not_safe_integral<int * Class::*&>();
    test_is_not_safe_integral<int Class::*&&>();
    test_is_not_safe_integral<float Class::*&&>();
    test_is_not_safe_integral<void * Class::*&&>();
    test_is_not_safe_integral<int * Class::*&&>();
    test_is_not_safe_integral<int Class::*const>();
    test_is_not_safe_integral<float Class::*const>();
    test_is_not_safe_integral<void * Class::*const>();
    test_is_not_safe_integral<int Class::*const&>();
    test_is_not_safe_integral<float Class::*const&>();
    test_is_not_safe_integral<void * Class::*const&>();
    test_is_not_safe_integral<int Class::*const&&>();
    test_is_not_safe_integral<float Class::*const&&>();
    test_is_not_safe_integral<void * Class::*const&&>();
    test_is_not_safe_integral<int Class::*volatile>();
    test_is_not_safe_integral<float Class::*volatile>();
    test_is_not_safe_integral<void * Class::*volatile>();
    test_is_not_safe_integral<int Class::*volatile&>();
    test_is_not_safe_integral<float Class::*volatile&>();
    test_is_not_safe_integral<void * Class::*volatile&>();
    test_is_not_safe_integral<int Class::*volatile&&>();
    test_is_not_safe_integral<float Class::*volatile&&>();
    test_is_not_safe_integral<void * Class::*volatile&&>();
    test_is_not_safe_integral<int Class::*const volatile>();
    test_is_not_safe_integral<float Class::*const volatile>();
    test_is_not_safe_integral<void * Class::*const volatile>();
    test_is_not_safe_integral<int Class::*const volatile&>();
    test_is_not_safe_integral<float Class::*const volatile&>();
    test_is_not_safe_integral<void * Class::*const volatile&>();
    test_is_not_safe_integral<int Class::*const volatile&&>();
    test_is_not_safe_integral<float Class::*const volatile&&>();
    test_is_not_safe_integral<void * Class::*const volatile&&>();
    test_is_not_safe_integral<NonCopyable>();
    test_is_not_safe_integral<NonMoveable>();
    test_is_not_safe_integral<NonConstructible>();
    test_is_not_safe_integral<Tracked>();
    test_is_not_safe_integral<TrapConstructible>();
    test_is_not_safe_integral<TrapImplicitConversion>();
    test_is_not_safe_integral<TrapComma>();
    test_is_not_safe_integral<TrapCall>();
    test_is_not_safe_integral<TrapSelfAssign>();
    test_is_not_safe_integral<TrapDeref>();
    test_is_not_safe_integral<TrapArraySubscript>();

    test_is_not_safe_integral<void()>();
    test_is_not_safe_integral<void()&>();
    test_is_not_safe_integral<void() &&>();
    test_is_not_safe_integral<void() const>();
    test_is_not_safe_integral<void() const&>();
    test_is_not_safe_integral<void() const&&>();
    test_is_not_safe_integral<void() volatile>();
    test_is_not_safe_integral<void() volatile&>();
    test_is_not_safe_integral<void() volatile&&>();
    test_is_not_safe_integral<void() const volatile>();
    test_is_not_safe_integral<void() const volatile&>();
    test_is_not_safe_integral<void() const volatile&&>();
    test_is_not_safe_integral<void() noexcept>();
    test_is_not_safe_integral<void()& noexcept>();
    test_is_not_safe_integral<void()&& noexcept>();
    test_is_not_safe_integral<void() const noexcept>();
    test_is_not_safe_integral<void() const& noexcept>();
    test_is_not_safe_integral<void() const&& noexcept>();
    test_is_not_safe_integral<void() volatile noexcept>();
    test_is_not_safe_integral<void() volatile& noexcept>();
    test_is_not_safe_integral<void() volatile&& noexcept>();
    test_is_not_safe_integral<void() const volatile noexcept>();
    test_is_not_safe_integral<void() const volatile& noexcept>();
    test_is_not_safe_integral<void() const volatile&& noexcept>();

    test_is_not_safe_integral<void(int)>();
    test_is_not_safe_integral<void(int)&>();
    test_is_not_safe_integral<void(int) &&>();
    test_is_not_safe_integral<void(int) const>();
    test_is_not_safe_integral<void(int) const&>();
    test_is_not_safe_integral<void(int) const&&>();
    test_is_not_safe_integral<void(int) volatile>();
    test_is_not_safe_integral<void(int) volatile&>();
    test_is_not_safe_integral<void(int) volatile&&>();
    test_is_not_safe_integral<void(int) const volatile>();
    test_is_not_safe_integral<void(int) const volatile&>();
    test_is_not_safe_integral<void(int) const volatile&&>();
    test_is_not_safe_integral<void(int) noexcept>();
    test_is_not_safe_integral<void(int)& noexcept>();
    test_is_not_safe_integral<void(int)&& noexcept>();
    test_is_not_safe_integral<void(int) const noexcept>();
    test_is_not_safe_integral<void(int) const& noexcept>();
    test_is_not_safe_integral<void(int) const&& noexcept>();
    test_is_not_safe_integral<void(int) volatile noexcept>();
    test_is_not_safe_integral<void(int) volatile& noexcept>();
    test_is_not_safe_integral<void(int) volatile&& noexcept>();
    test_is_not_safe_integral<void(int) const volatile noexcept>();
    test_is_not_safe_integral<void(int) const volatile& noexcept>();
    test_is_not_safe_integral<void(int) const volatile&& noexcept>();

    test_is_not_safe_integral<void(...)>();
    test_is_not_safe_integral<void(...)&>();
    test_is_not_safe_integral<void(...) &&>();
    test_is_not_safe_integral<void(...) const>();
    test_is_not_safe_integral<void(...) const&>();
    test_is_not_safe_integral<void(...) const&&>();
    test_is_not_safe_integral<void(...) volatile>();
    test_is_not_safe_integral<void(...) volatile&>();
    test_is_not_safe_integral<void(...) volatile&&>();
    test_is_not_safe_integral<void(...) const volatile>();
    test_is_not_safe_integral<void(...) const volatile&>();
    test_is_not_safe_integral<void(...) const volatile&&>();
    test_is_not_safe_integral<void(...) noexcept>();
    test_is_not_safe_integral<void(...)& noexcept>();
    test_is_not_safe_integral<void(...)&& noexcept>();
    test_is_not_safe_integral<void(...) const noexcept>();
    test_is_not_safe_integral<void(...) const& noexcept>();
    test_is_not_safe_integral<void(...) const&& noexcept>();
    test_is_not_safe_integral<void(...) volatile noexcept>();
    test_is_not_safe_integral<void(...) volatile& noexcept>();
    test_is_not_safe_integral<void(...) volatile&& noexcept>();
    test_is_not_safe_integral<void(...) const volatile noexcept>();
    test_is_not_safe_integral<void(...) const volatile& noexcept>();
    test_is_not_safe_integral<void(...) const volatile&& noexcept>();

    test_is_not_safe_integral<void(int, ...)>();
    test_is_not_safe_integral<void(int, ...)&>();
    test_is_not_safe_integral<void(int, ...) &&>();
    test_is_not_safe_integral<void(int, ...) const>();
    test_is_not_safe_integral<void(int, ...) const&>();
    test_is_not_safe_integral<void(int, ...) const&&>();
    test_is_not_safe_integral<void(int, ...) volatile>();
    test_is_not_safe_integral<void(int, ...) volatile&>();
    test_is_not_safe_integral<void(int, ...) volatile&&>();
    test_is_not_safe_integral<void(int, ...) const volatile>();
    test_is_not_safe_integral<void(int, ...) const volatile&>();
    test_is_not_safe_integral<void(int, ...) const volatile&&>();
    test_is_not_safe_integral<void(int, ...) noexcept>();
    test_is_not_safe_integral<void(int, ...)& noexcept>();
    test_is_not_safe_integral<void(int, ...)&& noexcept>();
    test_is_not_safe_integral<void(int, ...) const noexcept>();
    test_is_not_safe_integral<void(int, ...) const& noexcept>();
    test_is_not_safe_integral<void(int, ...) const&& noexcept>();
    test_is_not_safe_integral<void(int, ...) volatile noexcept>();
    test_is_not_safe_integral<void(int, ...) volatile& noexcept>();
    test_is_not_safe_integral<void(int, ...) volatile&& noexcept>();
    test_is_not_safe_integral<void(int, ...) const volatile noexcept>();
    test_is_not_safe_integral<void(int, ...) const volatile& noexcept>();
    test_is_not_safe_integral<void(int, ...) const volatile&& noexcept>();

    test_is_not_safe_integral<int()>();
    test_is_not_safe_integral<int()&>();
    test_is_not_safe_integral<int() &&>();
    test_is_not_safe_integral<int() const>();
    test_is_not_safe_integral<int() const&>();
    test_is_not_safe_integral<int() const&&>();
    test_is_not_safe_integral<int() volatile>();
    test_is_not_safe_integral<int() volatile&>();
    test_is_not_safe_integral<int() volatile&&>();
    test_is_not_safe_integral<int() const volatile>();
    test_is_not_safe_integral<int() const volatile&>();
    test_is_not_safe_integral<int() const volatile&&>();
    test_is_not_safe_integral<int() noexcept>();
    test_is_not_safe_integral<int()& noexcept>();
    test_is_not_safe_integral<int()&& noexcept>();
    test_is_not_safe_integral<int() const noexcept>();
    test_is_not_safe_integral<int() const& noexcept>();
    test_is_not_safe_integral<int() const&& noexcept>();
    test_is_not_safe_integral<int() volatile noexcept>();
    test_is_not_safe_integral<int() volatile& noexcept>();
    test_is_not_safe_integral<int() volatile&& noexcept>();
    test_is_not_safe_integral<int() const volatile noexcept>();
    test_is_not_safe_integral<int() const volatile& noexcept>();
    test_is_not_safe_integral<int() const volatile&& noexcept>();

    test_is_not_safe_integral<int(int)>();
    test_is_not_safe_integral<int(int)&>();
    test_is_not_safe_integral<int(int) &&>();
    test_is_not_safe_integral<int(int) const>();
    test_is_not_safe_integral<int(int) const&>();
    test_is_not_safe_integral<int(int) const&&>();
    test_is_not_safe_integral<int(int) volatile>();
    test_is_not_safe_integral<int(int) volatile&>();
    test_is_not_safe_integral<int(int) volatile&&>();
    test_is_not_safe_integral<int(int) const volatile>();
    test_is_not_safe_integral<int(int) const volatile&>();
    test_is_not_safe_integral<int(int) const volatile&&>();
    test_is_not_safe_integral<int(int) noexcept>();
    test_is_not_safe_integral<int(int)& noexcept>();
    test_is_not_safe_integral<int(int)&& noexcept>();
    test_is_not_safe_integral<int(int) const noexcept>();
    test_is_not_safe_integral<int(int) const& noexcept>();
    test_is_not_safe_integral<int(int) const&& noexcept>();
    test_is_not_safe_integral<int(int) volatile noexcept>();
    test_is_not_safe_integral<int(int) volatile& noexcept>();
    test_is_not_safe_integral<int(int) volatile&& noexcept>();
    test_is_not_safe_integral<int(int) const volatile noexcept>();
    test_is_not_safe_integral<int(int) const volatile& noexcept>();
    test_is_not_safe_integral<int(int) const volatile&& noexcept>();

    test_is_not_safe_integral<int(...)>();
    test_is_not_safe_integral<int(...)&>();
    test_is_not_safe_integral<int(...) &&>();
    test_is_not_safe_integral<int(...) const>();
    test_is_not_safe_integral<int(...) const&>();
    test_is_not_safe_integral<int(...) const&&>();
    test_is_not_safe_integral<int(...) volatile>();
    test_is_not_safe_integral<int(...) volatile&>();
    test_is_not_safe_integral<int(...) volatile&&>();
    test_is_not_safe_integral<int(...) const volatile>();
    test_is_not_safe_integral<int(...) const volatile&>();
    test_is_not_safe_integral<int(...) const volatile&&>();
    test_is_not_safe_integral<int(...) noexcept>();
    test_is_not_safe_integral<int(...)& noexcept>();
    test_is_not_safe_integral<int(...)&& noexcept>();
    test_is_not_safe_integral<int(...) const noexcept>();
    test_is_not_safe_integral<int(...) const& noexcept>();
    test_is_not_safe_integral<int(...) const&& noexcept>();
    test_is_not_safe_integral<int(...) volatile noexcept>();
    test_is_not_safe_integral<int(...) volatile& noexcept>();
    test_is_not_safe_integral<int(...) volatile&& noexcept>();
    test_is_not_safe_integral<int(...) const volatile noexcept>();
    test_is_not_safe_integral<int(...) const volatile& noexcept>();
    test_is_not_safe_integral<int(...) const volatile&& noexcept>();

    test_is_not_safe_integral<int(int, ...)>();
    test_is_not_safe_integral<int(int, ...)&>();
    test_is_not_safe_integral<int(int, ...) &&>();
    test_is_not_safe_integral<int(int, ...) const>();
    test_is_not_safe_integral<int(int, ...) const&>();
    test_is_not_safe_integral<int(int, ...) const&&>();
    test_is_not_safe_integral<int(int, ...) volatile>();
    test_is_not_safe_integral<int(int, ...) volatile&>();
    test_is_not_safe_integral<int(int, ...) volatile&&>();
    test_is_not_safe_integral<int(int, ...) const volatile>();
    test_is_not_safe_integral<int(int, ...) const volatile&>();
    test_is_not_safe_integral<int(int, ...) const volatile&&>();
    test_is_not_safe_integral<int(int, ...) noexcept>();
    test_is_not_safe_integral<int(int, ...)& noexcept>();
    test_is_not_safe_integral<int(int, ...)&& noexcept>();
    test_is_not_safe_integral<int(int, ...) const noexcept>();
    test_is_not_safe_integral<int(int, ...) const& noexcept>();
    test_is_not_safe_integral<int(int, ...) const&& noexcept>();
    test_is_not_safe_integral<int(int, ...) volatile noexcept>();
    test_is_not_safe_integral<int(int, ...) volatile& noexcept>();
    test_is_not_safe_integral<int(int, ...) volatile&& noexcept>();
    test_is_not_safe_integral<int(int, ...) const volatile noexcept>();
    test_is_not_safe_integral<int(int, ...) const volatile& noexcept>();
    test_is_not_safe_integral<int(int, ...) const volatile&& noexcept>();

    test_is_not_safe_integral<void (*)()>();
    test_is_not_safe_integral<void (*)() noexcept>();

    test_is_not_safe_integral<void (*)(int)>();
    test_is_not_safe_integral<void (*)(int) noexcept>();

    test_is_not_safe_integral<void (*)(...)>();
    test_is_not_safe_integral<void (*)(...) noexcept>();

    test_is_not_safe_integral<void (*)(int, ...)>();
    test_is_not_safe_integral<void (*)(int, ...) noexcept>();

    test_is_not_safe_integral<int (*)()>();
    test_is_not_safe_integral<int (*)() noexcept>();

    test_is_not_safe_integral<int (*)(int)>();
    test_is_not_safe_integral<int (*)(int) noexcept>();

    test_is_not_safe_integral<int (*)(...)>();
    test_is_not_safe_integral<int (*)(...) noexcept>();

    test_is_not_safe_integral<int (*)(int, ...)>();
    test_is_not_safe_integral<int (*)(int, ...) noexcept>();

    test_is_not_safe_integral<void (&)()>();
    test_is_not_safe_integral<void (&)() noexcept>();

    test_is_not_safe_integral<void (&)(int)>();
    test_is_not_safe_integral<void (&)(int) noexcept>();

    test_is_not_safe_integral<void (&)(...)>();
    test_is_not_safe_integral<void (&)(...) noexcept>();

    test_is_not_safe_integral<void (&)(int, ...)>();
    test_is_not_safe_integral<void (&)(int, ...) noexcept>();

    test_is_not_safe_integral<int (&)()>();
    test_is_not_safe_integral<int (&)() noexcept>();

    test_is_not_safe_integral<int (&)(int)>();
    test_is_not_safe_integral<int (&)(int) noexcept>();

    test_is_not_safe_integral<int (&)(...)>();
    test_is_not_safe_integral<int (&)(...) noexcept>();

    test_is_not_safe_integral<int (&)(int, ...)>();
    test_is_not_safe_integral<int (&)(int, ...) noexcept>();

    test_is_not_safe_integral<void(&&)()>();
    test_is_not_safe_integral<void(&&)() noexcept>();

    test_is_not_safe_integral<void(&&)(int)>();
    test_is_not_safe_integral<void(&&)(int) noexcept>();

    test_is_not_safe_integral<void(&&)(...)>();
    test_is_not_safe_integral<void(&&)(...) noexcept>();

    test_is_not_safe_integral<void(&&)(int, ...)>();
    test_is_not_safe_integral<void(&&)(int, ...) noexcept>();

    test_is_not_safe_integral<int(&&)()>();
    test_is_not_safe_integral<int(&&)() noexcept>();

    test_is_not_safe_integral<int(&&)(int)>();
    test_is_not_safe_integral<int(&&)(int) noexcept>();

    test_is_not_safe_integral<int(&&)(...)>();
    test_is_not_safe_integral<int(&&)(...) noexcept>();

    test_is_not_safe_integral<int(&&)(int, ...)>();
    test_is_not_safe_integral<int(&&)(int, ...) noexcept>();

    test_is_not_safe_integral<void (Class::*)()>();
    test_is_not_safe_integral<void (Class::*)()&>();
    test_is_not_safe_integral<void (Class::*)() &&>();
    test_is_not_safe_integral<void (Class::*)() const>();
    test_is_not_safe_integral<void (Class::*)() const&>();
    test_is_not_safe_integral<void (Class::*)() const&&>();
    test_is_not_safe_integral<void (Class::*)() noexcept>();
    test_is_not_safe_integral<void (Class::*)()& noexcept>();
    test_is_not_safe_integral<void (Class::*)()&& noexcept>();
    test_is_not_safe_integral<void (Class::*)() const noexcept>();
    test_is_not_safe_integral<void (Class::*)() const& noexcept>();
    test_is_not_safe_integral<void (Class::*)() const&& noexcept>();

    test_is_not_safe_integral<void (Class::*)(int)>();
    test_is_not_safe_integral<void (Class::*)(int)&>();
    test_is_not_safe_integral<void (Class::*)(int) &&>();
    test_is_not_safe_integral<void (Class::*)(int) const>();
    test_is_not_safe_integral<void (Class::*)(int) const&>();
    test_is_not_safe_integral<void (Class::*)(int) const&&>();
    test_is_not_safe_integral<void (Class::*)(int) noexcept>();
    test_is_not_safe_integral<void (Class::*)(int)& noexcept>();
    test_is_not_safe_integral<void (Class::*)(int)&& noexcept>();
    test_is_not_safe_integral<void (Class::*)(int) const noexcept>();
    test_is_not_safe_integral<void (Class::*)(int) const& noexcept>();
    test_is_not_safe_integral<void (Class::*)(int) const&& noexcept>();

    test_is_not_safe_integral<void (Class::*)(...)>();
    test_is_not_safe_integral<void (Class::*)(...)&>();
    test_is_not_safe_integral<void (Class::*)(...) &&>();
    test_is_not_safe_integral<void (Class::*)(...) const>();
    test_is_not_safe_integral<void (Class::*)(...) const&>();
    test_is_not_safe_integral<void (Class::*)(...) const&&>();
    test_is_not_safe_integral<void (Class::*)(...) noexcept>();
    test_is_not_safe_integral<void (Class::*)(...)& noexcept>();
    test_is_not_safe_integral<void (Class::*)(...)&& noexcept>();
    test_is_not_safe_integral<void (Class::*)(...) const noexcept>();
    test_is_not_safe_integral<void (Class::*)(...) const& noexcept>();
    test_is_not_safe_integral<void (Class::*)(...) const&& noexcept>();

    test_is_not_safe_integral<void (Class::*)(int, ...)>();
    test_is_not_safe_integral<void (Class::*)(int, ...)&>();
    test_is_not_safe_integral<void (Class::*)(int, ...) &&>();
    test_is_not_safe_integral<void (Class::*)(int, ...) const>();
    test_is_not_safe_integral<void (Class::*)(int, ...) const&>();
    test_is_not_safe_integral<void (Class::*)(int, ...) const&&>();
    test_is_not_safe_integral<void (Class::*)(int, ...) noexcept>();
    test_is_not_safe_integral<void (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_integral<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_integral<void (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_integral<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_integral<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_safe_integral<int (Class::*)()>();
    test_is_not_safe_integral<int (Class::*)()&>();
    test_is_not_safe_integral<int (Class::*)() &&>();
    test_is_not_safe_integral<int (Class::*)() const>();
    test_is_not_safe_integral<int (Class::*)() const&>();
    test_is_not_safe_integral<int (Class::*)() const&&>();
    test_is_not_safe_integral<int (Class::*)() noexcept>();
    test_is_not_safe_integral<int (Class::*)()& noexcept>();
    test_is_not_safe_integral<int (Class::*)()&& noexcept>();
    test_is_not_safe_integral<int (Class::*)() const noexcept>();
    test_is_not_safe_integral<int (Class::*)() const& noexcept>();
    test_is_not_safe_integral<int (Class::*)() const&& noexcept>();

    test_is_not_safe_integral<int (Class::*)(int)>();
    test_is_not_safe_integral<int (Class::*)(int)&>();
    test_is_not_safe_integral<int (Class::*)(int) &&>();
    test_is_not_safe_integral<int (Class::*)(int) const>();
    test_is_not_safe_integral<int (Class::*)(int) const&>();
    test_is_not_safe_integral<int (Class::*)(int) const&&>();
    test_is_not_safe_integral<int (Class::*)(int) noexcept>();
    test_is_not_safe_integral<int (Class::*)(int)& noexcept>();
    test_is_not_safe_integral<int (Class::*)(int)&& noexcept>();
    test_is_not_safe_integral<int (Class::*)(int) const noexcept>();
    test_is_not_safe_integral<int (Class::*)(int) const& noexcept>();
    test_is_not_safe_integral<int (Class::*)(int) const&& noexcept>();

    test_is_not_safe_integral<int (Class::*)(...)>();
    test_is_not_safe_integral<int (Class::*)(...)&>();
    test_is_not_safe_integral<int (Class::*)(...) &&>();
    test_is_not_safe_integral<int (Class::*)(...) const>();
    test_is_not_safe_integral<int (Class::*)(...) const&>();
    test_is_not_safe_integral<int (Class::*)(...) const&&>();
    test_is_not_safe_integral<int (Class::*)(...) noexcept>();
    test_is_not_safe_integral<int (Class::*)(...)& noexcept>();
    test_is_not_safe_integral<int (Class::*)(...)&& noexcept>();
    test_is_not_safe_integral<int (Class::*)(...) const noexcept>();
    test_is_not_safe_integral<int (Class::*)(...) const& noexcept>();
    test_is_not_safe_integral<int (Class::*)(...) const&& noexcept>();

    test_is_not_safe_integral<int (Class::*)(int, ...)>();
    test_is_not_safe_integral<int (Class::*)(int, ...)&>();
    test_is_not_safe_integral<int (Class::*)(int, ...) &&>();
    test_is_not_safe_integral<int (Class::*)(int, ...) const>();
    test_is_not_safe_integral<int (Class::*)(int, ...) const&>();
    test_is_not_safe_integral<int (Class::*)(int, ...) const&&>();
    test_is_not_safe_integral<int (Class::*)(int, ...) noexcept>();
    test_is_not_safe_integral<int (Class::*)(int, ...)& noexcept>();
    test_is_not_safe_integral<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_safe_integral<int (Class::*)(int, ...) const noexcept>();
    test_is_not_safe_integral<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_safe_integral<int (Class::*)(int, ...) const&& noexcept>();
}
