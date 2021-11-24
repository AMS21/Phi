#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_complete_or_unbounded.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_complete_or_unbounded_impl()
{
    STATIC_REQUIRE(phi::is_complete_or_unbounded<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_complete_or_unbounded<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_complete_or_unbounded_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_complete_or_unbounded_v<T>);
#endif
}

template <typename T>
void test_is_complete_or_unbounded()
{
    test_is_complete_or_unbounded_impl<T>();
    test_is_complete_or_unbounded_impl<const T>();
    test_is_complete_or_unbounded_impl<volatile T>();
    test_is_complete_or_unbounded_impl<const volatile T>();
}

template <typename T>
void test_is_not_complete_or_unbounded_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_complete_or_unbounded<T>::value);
    STATIC_REQUIRE(phi::is_not_complete_or_unbounded<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_complete_or_unbounded_v<T>);
    STATIC_REQUIRE(phi::is_not_complete_or_unbounded_v<T>);
#endif
}

template <typename T>
void test_is_not_complete_or_unbounded()
{
    test_is_not_complete_or_unbounded_impl<T>();
    test_is_not_complete_or_unbounded_impl<const T>();
    test_is_not_complete_or_unbounded_impl<volatile T>();
    test_is_not_complete_or_unbounded_impl<const volatile T>();
}

class A;

TEST_CASE("is_complete_or_unbounded")
{
    test_is_not_complete_or_unbounded<void>();
    test_is_complete_or_unbounded<phi::nullptr_t>();
    test_is_complete_or_unbounded<bool>();
    test_is_complete_or_unbounded<char>();
    test_is_complete_or_unbounded<signed char>();
    test_is_complete_or_unbounded<unsigned char>();
    test_is_complete_or_unbounded<short>();
    test_is_complete_or_unbounded<unsigned short>();
    test_is_complete_or_unbounded<int>();
    test_is_complete_or_unbounded<unsigned int>();
    test_is_complete_or_unbounded<long>();
    test_is_complete_or_unbounded<unsigned long>();
    test_is_complete_or_unbounded<long long>();
    test_is_complete_or_unbounded<unsigned long long>();
    test_is_complete_or_unbounded<float>();
    test_is_complete_or_unbounded<double>();
    test_is_complete_or_unbounded<long double>();
    test_is_complete_or_unbounded<char8_t>();
    test_is_complete_or_unbounded<char16_t>();
    test_is_complete_or_unbounded<char32_t>();
    test_is_complete_or_unbounded<wchar_t>();

    test_is_complete_or_unbounded<phi::Boolean>();
    test_is_complete_or_unbounded<phi::Integer<signed char>>();
    test_is_complete_or_unbounded<phi::Integer<unsigned char>>();
    test_is_complete_or_unbounded<phi::Integer<short>>();
    test_is_complete_or_unbounded<phi::Integer<unsigned short>>();
    test_is_complete_or_unbounded<phi::Integer<int>>();
    test_is_complete_or_unbounded<phi::Integer<unsigned int>>();
    test_is_complete_or_unbounded<phi::Integer<long>>();
    test_is_complete_or_unbounded<phi::Integer<unsigned long>>();
    test_is_complete_or_unbounded<phi::Integer<long long>>();
    test_is_complete_or_unbounded<phi::Integer<unsigned long long>>();
    test_is_complete_or_unbounded<phi::FloatingPoint<float>>();
    test_is_complete_or_unbounded<phi::FloatingPoint<double>>();
    test_is_complete_or_unbounded<phi::FloatingPoint<long double>>();

    test_is_complete_or_unbounded<std::vector<int>>();
    test_is_complete_or_unbounded<phi::ScopePtr<int>>();

    test_is_complete_or_unbounded<int&>();
    test_is_complete_or_unbounded<const int&>();
    test_is_complete_or_unbounded<volatile int&>();
    test_is_complete_or_unbounded<const volatile int&>();
    test_is_complete_or_unbounded<int&&>();
    test_is_complete_or_unbounded<const int&&>();
    test_is_complete_or_unbounded<volatile int&&>();
    test_is_complete_or_unbounded<const volatile int&&>();
    test_is_complete_or_unbounded<int*>();
    test_is_complete_or_unbounded<const int*>();
    test_is_complete_or_unbounded<volatile int*>();
    test_is_complete_or_unbounded<const volatile int*>();
    test_is_complete_or_unbounded<int**>();
    test_is_complete_or_unbounded<const int**>();
    test_is_complete_or_unbounded<volatile int**>();
    test_is_complete_or_unbounded<const volatile int**>();
    test_is_complete_or_unbounded<int*&>();
    test_is_complete_or_unbounded<const int*&>();
    test_is_complete_or_unbounded<volatile int*&>();
    test_is_complete_or_unbounded<const volatile int*&>();
    test_is_complete_or_unbounded<int*&&>();
    test_is_complete_or_unbounded<const int*&&>();
    test_is_complete_or_unbounded<volatile int*&&>();
    test_is_complete_or_unbounded<const volatile int*&&>();
    test_is_complete_or_unbounded<void*>();
    test_is_complete_or_unbounded<char[3]>();
    test_is_complete_or_unbounded<char[]>();
    test_is_complete_or_unbounded<char* [3]>();
    test_is_complete_or_unbounded<char*[]>();
    test_is_complete_or_unbounded<int(*)[3]>();
    test_is_complete_or_unbounded<int(*)[]>();
    test_is_complete_or_unbounded<int(&)[3]>();
    test_is_not_complete_or_unbounded<int(&)[]>();
    test_is_complete_or_unbounded<int(&&)[3]>();
    test_is_complete_or_unbounded<int(&&)[]>();
    test_is_complete_or_unbounded<char[3][2]>();
    test_is_complete_or_unbounded<char[][2]>();
    test_is_complete_or_unbounded<char* [3][2]>();
    test_is_complete_or_unbounded<char*[][2]>();
    test_is_complete_or_unbounded<int(*)[3][2]>();
    test_is_complete_or_unbounded<int(*)[][2]>();
    test_is_complete_or_unbounded<int(&)[3][2]>();
    test_is_not_complete_or_unbounded<int(&)[][2]>();
    test_is_complete_or_unbounded<int(&&)[3][2]>();
    test_is_complete_or_unbounded<int(&&)[][2]>();
    test_is_complete_or_unbounded<Class>();
    test_is_complete_or_unbounded<Class[]>();
    test_is_complete_or_unbounded<Class[2]>();
    test_is_complete_or_unbounded<Template<void>>();
    test_is_complete_or_unbounded<Template<int>>();
    test_is_complete_or_unbounded<Template<Class>>();
    test_is_complete_or_unbounded<Template<incomplete_type>>();
    test_is_complete_or_unbounded<VariadicTemplate<>>();
    test_is_complete_or_unbounded<VariadicTemplate<void>>();
    test_is_complete_or_unbounded<VariadicTemplate<int>>();
    test_is_complete_or_unbounded<VariadicTemplate<Class>>();
    test_is_complete_or_unbounded<VariadicTemplate<incomplete_type>>();
    test_is_complete_or_unbounded<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_complete_or_unbounded<PublicDerviedFromTemplate<Base>>();
    test_is_complete_or_unbounded<PublicDerviedFromTemplate<Derived>>();
    test_is_complete_or_unbounded<PublicDerviedFromTemplate<Class>>();
    test_is_complete_or_unbounded<PrivateDerviedFromTemplate<Base>>();
    test_is_complete_or_unbounded<PrivateDerviedFromTemplate<Derived>>();
    test_is_complete_or_unbounded<PrivateDerviedFromTemplate<Class>>();
    test_is_complete_or_unbounded<ProtectedDerviedFromTemplate<Base>>();
    test_is_complete_or_unbounded<ProtectedDerviedFromTemplate<Derived>>();
    test_is_complete_or_unbounded<ProtectedDerviedFromTemplate<Class>>();
    test_is_complete_or_unbounded<Union>();
    test_is_complete_or_unbounded<NonEmptyUnion>();
    test_is_complete_or_unbounded<Empty>();
    test_is_complete_or_unbounded<NotEmpty>();
    test_is_complete_or_unbounded<bit_zero>();
    test_is_complete_or_unbounded<bit_one>();
    test_is_complete_or_unbounded<Base>();
    test_is_complete_or_unbounded<Derived>();
    test_is_complete_or_unbounded<Abstract>();
    test_is_complete_or_unbounded<PublicAbstract>();
    test_is_complete_or_unbounded<PrivateAbstract>();
    test_is_complete_or_unbounded<ProtectedAbstract>();
    test_is_complete_or_unbounded<AbstractTemplate<int>>();
    test_is_complete_or_unbounded<AbstractTemplate<double>>();
    test_is_complete_or_unbounded<AbstractTemplate<Class>>();
    test_is_complete_or_unbounded<AbstractTemplate<incomplete_type>>();
    test_is_complete_or_unbounded<Final>();
    test_is_complete_or_unbounded<PublicDestructor>();
    test_is_complete_or_unbounded<ProtectedDestructor>();
    test_is_complete_or_unbounded<PrivateDestructor>();
    test_is_complete_or_unbounded<VirtualPublicDestructor>();
    test_is_complete_or_unbounded<VirtualProtectedDestructor>();
    test_is_complete_or_unbounded<VirtualPrivateDestructor>();
    test_is_complete_or_unbounded<PurePublicDestructor>();
    test_is_complete_or_unbounded<PureProtectedDestructor>();
    test_is_complete_or_unbounded<PurePrivateDestructor>();
    test_is_complete_or_unbounded<DeletedPublicDestructor>();
    test_is_complete_or_unbounded<DeletedProtectedDestructor>();
    test_is_complete_or_unbounded<DeletedPrivateDestructor>();
    test_is_complete_or_unbounded<DeletedVirtualPublicDestructor>();
    test_is_complete_or_unbounded<DeletedVirtualProtectedDestructor>();
    test_is_complete_or_unbounded<DeletedVirtualPrivateDestructor>();
    test_is_complete_or_unbounded<Enum>();
    test_is_complete_or_unbounded<EnumSigned>();
    test_is_complete_or_unbounded<EnumUnsigned>();
    test_is_complete_or_unbounded<EnumClass>();
    test_is_complete_or_unbounded<EnumStruct>();
    test_is_complete_or_unbounded<Function>();
    test_is_complete_or_unbounded<FunctionPtr>();
    test_is_complete_or_unbounded<MemberObjectPtr>();
    test_is_complete_or_unbounded<MemberFunctionPtr>();
    test_is_not_complete_or_unbounded<incomplete_type>();
    test_is_not_complete_or_unbounded<IncompleteTemplate<void>>();
    test_is_not_complete_or_unbounded<IncompleteTemplate<int>>();
    test_is_not_complete_or_unbounded<IncompleteTemplate<Class>>();
    test_is_not_complete_or_unbounded<IncompleteTemplate<incomplete_type>>();
    test_is_not_complete_or_unbounded<IncompleteVariadicTemplate<>>();
    test_is_not_complete_or_unbounded<IncompleteVariadicTemplate<void>>();
    test_is_not_complete_or_unbounded<IncompleteVariadicTemplate<int>>();
    test_is_not_complete_or_unbounded<IncompleteVariadicTemplate<Class>>();
    test_is_not_complete_or_unbounded<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_complete_or_unbounded<
            IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_complete_or_unbounded<int Class::*>();
    test_is_complete_or_unbounded<float Class::*>();
    test_is_complete_or_unbounded<void * Class::*>();
    test_is_complete_or_unbounded<int * Class::*>();
    test_is_complete_or_unbounded<int Class::*&>();
    test_is_complete_or_unbounded<float Class::*&>();
    test_is_complete_or_unbounded<void * Class::*&>();
    test_is_complete_or_unbounded<int * Class::*&>();
    test_is_complete_or_unbounded<int Class::*&&>();
    test_is_complete_or_unbounded<float Class::*&&>();
    test_is_complete_or_unbounded<void * Class::*&&>();
    test_is_complete_or_unbounded<int * Class::*&&>();
    test_is_complete_or_unbounded<int Class::*const>();
    test_is_complete_or_unbounded<float Class::*const>();
    test_is_complete_or_unbounded<void * Class::*const>();
    test_is_complete_or_unbounded<int Class::*const&>();
    test_is_complete_or_unbounded<float Class::*const&>();
    test_is_complete_or_unbounded<void * Class::*const&>();
    test_is_complete_or_unbounded<int Class::*const&&>();
    test_is_complete_or_unbounded<float Class::*const&&>();
    test_is_complete_or_unbounded<void * Class::*const&&>();
    test_is_complete_or_unbounded<int Class::*volatile>();
    test_is_complete_or_unbounded<float Class::*volatile>();
    test_is_complete_or_unbounded<void * Class::*volatile>();
    test_is_complete_or_unbounded<int Class::*volatile&>();
    test_is_complete_or_unbounded<float Class::*volatile&>();
    test_is_complete_or_unbounded<void * Class::*volatile&>();
    test_is_complete_or_unbounded<int Class::*volatile&&>();
    test_is_complete_or_unbounded<float Class::*volatile&&>();
    test_is_complete_or_unbounded<void * Class::*volatile&&>();
    test_is_complete_or_unbounded<int Class::*const volatile>();
    test_is_complete_or_unbounded<float Class::*const volatile>();
    test_is_complete_or_unbounded<void * Class::*const volatile>();
    test_is_complete_or_unbounded<int Class::*const volatile&>();
    test_is_complete_or_unbounded<float Class::*const volatile&>();
    test_is_complete_or_unbounded<void * Class::*const volatile&>();
    test_is_complete_or_unbounded<int Class::*const volatile&&>();
    test_is_complete_or_unbounded<float Class::*const volatile&&>();
    test_is_complete_or_unbounded<void * Class::*const volatile&&>();
    test_is_complete_or_unbounded<NonCopyable>();
    test_is_complete_or_unbounded<NonMoveable>();
    test_is_complete_or_unbounded<NonConstructible>();
    test_is_complete_or_unbounded<Tracked>();
    test_is_complete_or_unbounded<TrapConstructible>();
    test_is_complete_or_unbounded<TrapImplicitConversion>();
    test_is_complete_or_unbounded<TrapComma>();
    test_is_complete_or_unbounded<TrapCall>();
    test_is_complete_or_unbounded<TrapSelfAssign>();
    test_is_complete_or_unbounded<TrapDeref>();
    test_is_complete_or_unbounded<TrapArraySubscript>();

    test_is_complete_or_unbounded<void()>();
    test_is_complete_or_unbounded<void()&>();
    test_is_complete_or_unbounded<void() &&>();
    test_is_complete_or_unbounded<void() const>();
    test_is_complete_or_unbounded<void() const&>();
    test_is_complete_or_unbounded<void() const&&>();
    test_is_complete_or_unbounded<void() volatile>();
    test_is_complete_or_unbounded<void() volatile&>();
    test_is_complete_or_unbounded<void() volatile&&>();
    test_is_complete_or_unbounded<void() const volatile>();
    test_is_complete_or_unbounded<void() const volatile&>();
    test_is_complete_or_unbounded<void() const volatile&&>();
    test_is_complete_or_unbounded<void() noexcept>();
    test_is_complete_or_unbounded<void()& noexcept>();
    test_is_complete_or_unbounded<void()&& noexcept>();
    test_is_complete_or_unbounded<void() const noexcept>();
    test_is_complete_or_unbounded<void() const& noexcept>();
    test_is_complete_or_unbounded<void() const&& noexcept>();
    test_is_complete_or_unbounded<void() volatile noexcept>();
    test_is_complete_or_unbounded<void() volatile& noexcept>();
    test_is_complete_or_unbounded<void() volatile&& noexcept>();
    test_is_complete_or_unbounded<void() const volatile noexcept>();
    test_is_complete_or_unbounded<void() const volatile& noexcept>();
    test_is_complete_or_unbounded<void() const volatile&& noexcept>();

    test_is_complete_or_unbounded<void(int)>();
    test_is_complete_or_unbounded<void(int)&>();
    test_is_complete_or_unbounded<void(int) &&>();
    test_is_complete_or_unbounded<void(int) const>();
    test_is_complete_or_unbounded<void(int) const&>();
    test_is_complete_or_unbounded<void(int) const&&>();
    test_is_complete_or_unbounded<void(int) volatile>();
    test_is_complete_or_unbounded<void(int) volatile&>();
    test_is_complete_or_unbounded<void(int) volatile&&>();
    test_is_complete_or_unbounded<void(int) const volatile>();
    test_is_complete_or_unbounded<void(int) const volatile&>();
    test_is_complete_or_unbounded<void(int) const volatile&&>();
    test_is_complete_or_unbounded<void(int) noexcept>();
    test_is_complete_or_unbounded<void(int)& noexcept>();
    test_is_complete_or_unbounded<void(int)&& noexcept>();
    test_is_complete_or_unbounded<void(int) const noexcept>();
    test_is_complete_or_unbounded<void(int) const& noexcept>();
    test_is_complete_or_unbounded<void(int) const&& noexcept>();
    test_is_complete_or_unbounded<void(int) volatile noexcept>();
    test_is_complete_or_unbounded<void(int) volatile& noexcept>();
    test_is_complete_or_unbounded<void(int) volatile&& noexcept>();
    test_is_complete_or_unbounded<void(int) const volatile noexcept>();
    test_is_complete_or_unbounded<void(int) const volatile& noexcept>();
    test_is_complete_or_unbounded<void(int) const volatile&& noexcept>();

    test_is_complete_or_unbounded<void(...)>();
    test_is_complete_or_unbounded<void(...)&>();
    test_is_complete_or_unbounded<void(...) &&>();
    test_is_complete_or_unbounded<void(...) const>();
    test_is_complete_or_unbounded<void(...) const&>();
    test_is_complete_or_unbounded<void(...) const&&>();
    test_is_complete_or_unbounded<void(...) volatile>();
    test_is_complete_or_unbounded<void(...) volatile&>();
    test_is_complete_or_unbounded<void(...) volatile&&>();
    test_is_complete_or_unbounded<void(...) const volatile>();
    test_is_complete_or_unbounded<void(...) const volatile&>();
    test_is_complete_or_unbounded<void(...) const volatile&&>();
    test_is_complete_or_unbounded<void(...) noexcept>();
    test_is_complete_or_unbounded<void(...)& noexcept>();
    test_is_complete_or_unbounded<void(...)&& noexcept>();
    test_is_complete_or_unbounded<void(...) const noexcept>();
    test_is_complete_or_unbounded<void(...) const& noexcept>();
    test_is_complete_or_unbounded<void(...) const&& noexcept>();
    test_is_complete_or_unbounded<void(...) volatile noexcept>();
    test_is_complete_or_unbounded<void(...) volatile& noexcept>();
    test_is_complete_or_unbounded<void(...) volatile&& noexcept>();
    test_is_complete_or_unbounded<void(...) const volatile noexcept>();
    test_is_complete_or_unbounded<void(...) const volatile& noexcept>();
    test_is_complete_or_unbounded<void(...) const volatile&& noexcept>();

    test_is_complete_or_unbounded<void(int, ...)>();
    test_is_complete_or_unbounded<void(int, ...)&>();
    test_is_complete_or_unbounded<void(int, ...) &&>();
    test_is_complete_or_unbounded<void(int, ...) const>();
    test_is_complete_or_unbounded<void(int, ...) const&>();
    test_is_complete_or_unbounded<void(int, ...) const&&>();
    test_is_complete_or_unbounded<void(int, ...) volatile>();
    test_is_complete_or_unbounded<void(int, ...) volatile&>();
    test_is_complete_or_unbounded<void(int, ...) volatile&&>();
    test_is_complete_or_unbounded<void(int, ...) const volatile>();
    test_is_complete_or_unbounded<void(int, ...) const volatile&>();
    test_is_complete_or_unbounded<void(int, ...) const volatile&&>();
    test_is_complete_or_unbounded<void(int, ...) noexcept>();
    test_is_complete_or_unbounded<void(int, ...)& noexcept>();
    test_is_complete_or_unbounded<void(int, ...)&& noexcept>();
    test_is_complete_or_unbounded<void(int, ...) const noexcept>();
    test_is_complete_or_unbounded<void(int, ...) const& noexcept>();
    test_is_complete_or_unbounded<void(int, ...) const&& noexcept>();
    test_is_complete_or_unbounded<void(int, ...) volatile noexcept>();
    test_is_complete_or_unbounded<void(int, ...) volatile& noexcept>();
    test_is_complete_or_unbounded<void(int, ...) volatile&& noexcept>();
    test_is_complete_or_unbounded<void(int, ...) const volatile noexcept>();
    test_is_complete_or_unbounded<void(int, ...) const volatile& noexcept>();
    test_is_complete_or_unbounded<void(int, ...) const volatile&& noexcept>();

    test_is_complete_or_unbounded<int()>();
    test_is_complete_or_unbounded<int()&>();
    test_is_complete_or_unbounded<int() &&>();
    test_is_complete_or_unbounded<int() const>();
    test_is_complete_or_unbounded<int() const&>();
    test_is_complete_or_unbounded<int() const&&>();
    test_is_complete_or_unbounded<int() volatile>();
    test_is_complete_or_unbounded<int() volatile&>();
    test_is_complete_or_unbounded<int() volatile&&>();
    test_is_complete_or_unbounded<int() const volatile>();
    test_is_complete_or_unbounded<int() const volatile&>();
    test_is_complete_or_unbounded<int() const volatile&&>();
    test_is_complete_or_unbounded<int() noexcept>();
    test_is_complete_or_unbounded<int()& noexcept>();
    test_is_complete_or_unbounded<int()&& noexcept>();
    test_is_complete_or_unbounded<int() const noexcept>();
    test_is_complete_or_unbounded<int() const& noexcept>();
    test_is_complete_or_unbounded<int() const&& noexcept>();
    test_is_complete_or_unbounded<int() volatile noexcept>();
    test_is_complete_or_unbounded<int() volatile& noexcept>();
    test_is_complete_or_unbounded<int() volatile&& noexcept>();
    test_is_complete_or_unbounded<int() const volatile noexcept>();
    test_is_complete_or_unbounded<int() const volatile& noexcept>();
    test_is_complete_or_unbounded<int() const volatile&& noexcept>();

    test_is_complete_or_unbounded<int(int)>();
    test_is_complete_or_unbounded<int(int)&>();
    test_is_complete_or_unbounded<int(int) &&>();
    test_is_complete_or_unbounded<int(int) const>();
    test_is_complete_or_unbounded<int(int) const&>();
    test_is_complete_or_unbounded<int(int) const&&>();
    test_is_complete_or_unbounded<int(int) volatile>();
    test_is_complete_or_unbounded<int(int) volatile&>();
    test_is_complete_or_unbounded<int(int) volatile&&>();
    test_is_complete_or_unbounded<int(int) const volatile>();
    test_is_complete_or_unbounded<int(int) const volatile&>();
    test_is_complete_or_unbounded<int(int) const volatile&&>();
    test_is_complete_or_unbounded<int(int) noexcept>();
    test_is_complete_or_unbounded<int(int)& noexcept>();
    test_is_complete_or_unbounded<int(int)&& noexcept>();
    test_is_complete_or_unbounded<int(int) const noexcept>();
    test_is_complete_or_unbounded<int(int) const& noexcept>();
    test_is_complete_or_unbounded<int(int) const&& noexcept>();
    test_is_complete_or_unbounded<int(int) volatile noexcept>();
    test_is_complete_or_unbounded<int(int) volatile& noexcept>();
    test_is_complete_or_unbounded<int(int) volatile&& noexcept>();
    test_is_complete_or_unbounded<int(int) const volatile noexcept>();
    test_is_complete_or_unbounded<int(int) const volatile& noexcept>();
    test_is_complete_or_unbounded<int(int) const volatile&& noexcept>();

    test_is_complete_or_unbounded<int(...)>();
    test_is_complete_or_unbounded<int(...)&>();
    test_is_complete_or_unbounded<int(...) &&>();
    test_is_complete_or_unbounded<int(...) const>();
    test_is_complete_or_unbounded<int(...) const&>();
    test_is_complete_or_unbounded<int(...) const&&>();
    test_is_complete_or_unbounded<int(...) volatile>();
    test_is_complete_or_unbounded<int(...) volatile&>();
    test_is_complete_or_unbounded<int(...) volatile&&>();
    test_is_complete_or_unbounded<int(...) const volatile>();
    test_is_complete_or_unbounded<int(...) const volatile&>();
    test_is_complete_or_unbounded<int(...) const volatile&&>();
    test_is_complete_or_unbounded<int(...) noexcept>();
    test_is_complete_or_unbounded<int(...)& noexcept>();
    test_is_complete_or_unbounded<int(...)&& noexcept>();
    test_is_complete_or_unbounded<int(...) const noexcept>();
    test_is_complete_or_unbounded<int(...) const& noexcept>();
    test_is_complete_or_unbounded<int(...) const&& noexcept>();
    test_is_complete_or_unbounded<int(...) volatile noexcept>();
    test_is_complete_or_unbounded<int(...) volatile& noexcept>();
    test_is_complete_or_unbounded<int(...) volatile&& noexcept>();
    test_is_complete_or_unbounded<int(...) const volatile noexcept>();
    test_is_complete_or_unbounded<int(...) const volatile& noexcept>();
    test_is_complete_or_unbounded<int(...) const volatile&& noexcept>();

    test_is_complete_or_unbounded<int(int, ...)>();
    test_is_complete_or_unbounded<int(int, ...)&>();
    test_is_complete_or_unbounded<int(int, ...) &&>();
    test_is_complete_or_unbounded<int(int, ...) const>();
    test_is_complete_or_unbounded<int(int, ...) const&>();
    test_is_complete_or_unbounded<int(int, ...) const&&>();
    test_is_complete_or_unbounded<int(int, ...) volatile>();
    test_is_complete_or_unbounded<int(int, ...) volatile&>();
    test_is_complete_or_unbounded<int(int, ...) volatile&&>();
    test_is_complete_or_unbounded<int(int, ...) const volatile>();
    test_is_complete_or_unbounded<int(int, ...) const volatile&>();
    test_is_complete_or_unbounded<int(int, ...) const volatile&&>();
    test_is_complete_or_unbounded<int(int, ...) noexcept>();
    test_is_complete_or_unbounded<int(int, ...)& noexcept>();
    test_is_complete_or_unbounded<int(int, ...)&& noexcept>();
    test_is_complete_or_unbounded<int(int, ...) const noexcept>();
    test_is_complete_or_unbounded<int(int, ...) const& noexcept>();
    test_is_complete_or_unbounded<int(int, ...) const&& noexcept>();
    test_is_complete_or_unbounded<int(int, ...) volatile noexcept>();
    test_is_complete_or_unbounded<int(int, ...) volatile& noexcept>();
    test_is_complete_or_unbounded<int(int, ...) volatile&& noexcept>();
    test_is_complete_or_unbounded<int(int, ...) const volatile noexcept>();
    test_is_complete_or_unbounded<int(int, ...) const volatile& noexcept>();
    test_is_complete_or_unbounded<int(int, ...) const volatile&& noexcept>();

    test_is_complete_or_unbounded<void (*)()>();
    test_is_complete_or_unbounded<void (*)() noexcept>();

    test_is_complete_or_unbounded<void (*)(int)>();
    test_is_complete_or_unbounded<void (*)(int) noexcept>();

    test_is_complete_or_unbounded<void (*)(...)>();
    test_is_complete_or_unbounded<void (*)(...) noexcept>();

    test_is_complete_or_unbounded<void (*)(int, ...)>();
    test_is_complete_or_unbounded<void (*)(int, ...) noexcept>();

    test_is_complete_or_unbounded<int (*)()>();
    test_is_complete_or_unbounded<int (*)() noexcept>();

    test_is_complete_or_unbounded<int (*)(int)>();
    test_is_complete_or_unbounded<int (*)(int) noexcept>();

    test_is_complete_or_unbounded<int (*)(...)>();
    test_is_complete_or_unbounded<int (*)(...) noexcept>();

    test_is_complete_or_unbounded<int (*)(int, ...)>();
    test_is_complete_or_unbounded<int (*)(int, ...) noexcept>();

    test_is_complete_or_unbounded<void (&)()>();
    test_is_complete_or_unbounded<void (&)() noexcept>();

    test_is_complete_or_unbounded<void (&)(int)>();
    test_is_complete_or_unbounded<void (&)(int) noexcept>();

    test_is_complete_or_unbounded<void (&)(...)>();
    test_is_complete_or_unbounded<void (&)(...) noexcept>();

    test_is_complete_or_unbounded<void (&)(int, ...)>();
    test_is_complete_or_unbounded<void (&)(int, ...) noexcept>();

    test_is_complete_or_unbounded<int (&)()>();
    test_is_complete_or_unbounded<int (&)() noexcept>();

    test_is_complete_or_unbounded<int (&)(int)>();
    test_is_complete_or_unbounded<int (&)(int) noexcept>();

    test_is_complete_or_unbounded<int (&)(...)>();
    test_is_complete_or_unbounded<int (&)(...) noexcept>();

    test_is_complete_or_unbounded<int (&)(int, ...)>();
    test_is_complete_or_unbounded<int (&)(int, ...) noexcept>();

    test_is_complete_or_unbounded<void(&&)()>();
    test_is_complete_or_unbounded<void(&&)() noexcept>();

    test_is_complete_or_unbounded<void(&&)(int)>();
    test_is_complete_or_unbounded<void(&&)(int) noexcept>();

    test_is_complete_or_unbounded<void(&&)(...)>();
    test_is_complete_or_unbounded<void(&&)(...) noexcept>();

    test_is_complete_or_unbounded<void(&&)(int, ...)>();
    test_is_complete_or_unbounded<void(&&)(int, ...) noexcept>();

    test_is_complete_or_unbounded<int(&&)()>();
    test_is_complete_or_unbounded<int(&&)() noexcept>();

    test_is_complete_or_unbounded<int(&&)(int)>();
    test_is_complete_or_unbounded<int(&&)(int) noexcept>();

    test_is_complete_or_unbounded<int(&&)(...)>();
    test_is_complete_or_unbounded<int(&&)(...) noexcept>();

    test_is_complete_or_unbounded<int(&&)(int, ...)>();
    test_is_complete_or_unbounded<int(&&)(int, ...) noexcept>();

    test_is_complete_or_unbounded<void (Class::*)()>();
    test_is_complete_or_unbounded<void (Class::*)()&>();
    test_is_complete_or_unbounded<void (Class::*)() &&>();
    test_is_complete_or_unbounded<void (Class::*)() const>();
    test_is_complete_or_unbounded<void (Class::*)() const&>();
    test_is_complete_or_unbounded<void (Class::*)() const&&>();
    test_is_complete_or_unbounded<void (Class::*)() noexcept>();
    test_is_complete_or_unbounded<void (Class::*)()& noexcept>();
    test_is_complete_or_unbounded<void (Class::*)()&& noexcept>();
    test_is_complete_or_unbounded<void (Class::*)() const noexcept>();
    test_is_complete_or_unbounded<void (Class::*)() const& noexcept>();
    test_is_complete_or_unbounded<void (Class::*)() const&& noexcept>();

    test_is_complete_or_unbounded<void (Class::*)(int)>();
    test_is_complete_or_unbounded<void (Class::*)(int)&>();
    test_is_complete_or_unbounded<void (Class::*)(int) &&>();
    test_is_complete_or_unbounded<void (Class::*)(int) const>();
    test_is_complete_or_unbounded<void (Class::*)(int) const&>();
    test_is_complete_or_unbounded<void (Class::*)(int) const&&>();
    test_is_complete_or_unbounded<void (Class::*)(int) noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(int)& noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(int)&& noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(int) const noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(int) const& noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(int) const&& noexcept>();

    test_is_complete_or_unbounded<void (Class::*)(...)>();
    test_is_complete_or_unbounded<void (Class::*)(...)&>();
    test_is_complete_or_unbounded<void (Class::*)(...) &&>();
    test_is_complete_or_unbounded<void (Class::*)(...) const>();
    test_is_complete_or_unbounded<void (Class::*)(...) const&>();
    test_is_complete_or_unbounded<void (Class::*)(...) const&&>();
    test_is_complete_or_unbounded<void (Class::*)(...) noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(...)& noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(...)&& noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(...) const noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(...) const& noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(...) const&& noexcept>();

    test_is_complete_or_unbounded<void (Class::*)(int, ...)>();
    test_is_complete_or_unbounded<void (Class::*)(int, ...)&>();
    test_is_complete_or_unbounded<void (Class::*)(int, ...) &&>();
    test_is_complete_or_unbounded<void (Class::*)(int, ...) const>();
    test_is_complete_or_unbounded<void (Class::*)(int, ...) const&>();
    test_is_complete_or_unbounded<void (Class::*)(int, ...) const&&>();
    test_is_complete_or_unbounded<void (Class::*)(int, ...) noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(int, ...)& noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(int, ...)&& noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(int, ...) const noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(int, ...) const& noexcept>();
    test_is_complete_or_unbounded<void (Class::*)(int, ...) const&& noexcept>();

    test_is_complete_or_unbounded<int (Class::*)()>();
    test_is_complete_or_unbounded<int (Class::*)()&>();
    test_is_complete_or_unbounded<int (Class::*)() &&>();
    test_is_complete_or_unbounded<int (Class::*)() const>();
    test_is_complete_or_unbounded<int (Class::*)() const&>();
    test_is_complete_or_unbounded<int (Class::*)() const&&>();
    test_is_complete_or_unbounded<int (Class::*)() noexcept>();
    test_is_complete_or_unbounded<int (Class::*)()& noexcept>();
    test_is_complete_or_unbounded<int (Class::*)()&& noexcept>();
    test_is_complete_or_unbounded<int (Class::*)() const noexcept>();
    test_is_complete_or_unbounded<int (Class::*)() const& noexcept>();
    test_is_complete_or_unbounded<int (Class::*)() const&& noexcept>();

    test_is_complete_or_unbounded<int (Class::*)(int)>();
    test_is_complete_or_unbounded<int (Class::*)(int)&>();
    test_is_complete_or_unbounded<int (Class::*)(int) &&>();
    test_is_complete_or_unbounded<int (Class::*)(int) const>();
    test_is_complete_or_unbounded<int (Class::*)(int) const&>();
    test_is_complete_or_unbounded<int (Class::*)(int) const&&>();
    test_is_complete_or_unbounded<int (Class::*)(int) noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(int)& noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(int)&& noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(int) const noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(int) const& noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(int) const&& noexcept>();

    test_is_complete_or_unbounded<int (Class::*)(...)>();
    test_is_complete_or_unbounded<int (Class::*)(...)&>();
    test_is_complete_or_unbounded<int (Class::*)(...) &&>();
    test_is_complete_or_unbounded<int (Class::*)(...) const>();
    test_is_complete_or_unbounded<int (Class::*)(...) const&>();
    test_is_complete_or_unbounded<int (Class::*)(...) const&&>();
    test_is_complete_or_unbounded<int (Class::*)(...) noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(...)& noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(...)&& noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(...) const noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(...) const& noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(...) const&& noexcept>();

    test_is_complete_or_unbounded<int (Class::*)(int, ...)>();
    test_is_complete_or_unbounded<int (Class::*)(int, ...)&>();
    test_is_complete_or_unbounded<int (Class::*)(int, ...) &&>();
    test_is_complete_or_unbounded<int (Class::*)(int, ...) const>();
    test_is_complete_or_unbounded<int (Class::*)(int, ...) const&>();
    test_is_complete_or_unbounded<int (Class::*)(int, ...) const&&>();
    test_is_complete_or_unbounded<int (Class::*)(int, ...) noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(int, ...)& noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(int, ...)&& noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(int, ...) const noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(int, ...) const& noexcept>();
    test_is_complete_or_unbounded<int (Class::*)(int, ...) const&& noexcept>();
}