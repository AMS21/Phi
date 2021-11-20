#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_complete_or_unbounded_void.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_complete_or_unbounded_void_impl()
{
    STATIC_REQUIRE(phi::is_complete_or_unbounded_void<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_complete_or_unbounded_void<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_complete_or_unbounded_void_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_complete_or_unbounded_void_v<T>);
#endif
}

template <typename T>
void test_is_complete_or_unbounded_void()
{
    test_is_complete_or_unbounded_void_impl<T>();
    test_is_complete_or_unbounded_void_impl<const T>();
    test_is_complete_or_unbounded_void_impl<volatile T>();
    test_is_complete_or_unbounded_void_impl<const volatile T>();
}

template <typename T>
void test_is_not_complete_or_unbounded_void_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_complete_or_unbounded_void<T>::value);
    STATIC_REQUIRE(phi::is_not_complete_or_unbounded_void<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_complete_or_unbounded_void_v<T>);
    STATIC_REQUIRE(phi::is_not_complete_or_unbounded_void_v<T>);
#endif
}

template <typename T>
void test_is_not_complete_or_unbounded_void()
{
    test_is_not_complete_or_unbounded_void_impl<T>();
    test_is_not_complete_or_unbounded_void_impl<const T>();
    test_is_not_complete_or_unbounded_void_impl<volatile T>();
    test_is_not_complete_or_unbounded_void_impl<const volatile T>();
}

class A;

TEST_CASE("is_complete_or_unbounded_void")
{
    test_is_complete_or_unbounded_void<void>();
    test_is_complete_or_unbounded_void<phi::nullptr_t>();
    test_is_complete_or_unbounded_void<bool>();
    test_is_complete_or_unbounded_void<char>();
    test_is_complete_or_unbounded_void<signed char>();
    test_is_complete_or_unbounded_void<unsigned char>();
    test_is_complete_or_unbounded_void<short>();
    test_is_complete_or_unbounded_void<unsigned short>();
    test_is_complete_or_unbounded_void<int>();
    test_is_complete_or_unbounded_void<unsigned int>();
    test_is_complete_or_unbounded_void<long>();
    test_is_complete_or_unbounded_void<unsigned long>();
    test_is_complete_or_unbounded_void<long long>();
    test_is_complete_or_unbounded_void<unsigned long long>();
    test_is_complete_or_unbounded_void<float>();
    test_is_complete_or_unbounded_void<double>();
    test_is_complete_or_unbounded_void<long double>();
    test_is_complete_or_unbounded_void<char8_t>();
    test_is_complete_or_unbounded_void<char16_t>();
    test_is_complete_or_unbounded_void<char32_t>();
    test_is_complete_or_unbounded_void<wchar_t>();

    test_is_complete_or_unbounded_void<phi::Boolean>();
    test_is_complete_or_unbounded_void<phi::Integer<signed char>>();
    test_is_complete_or_unbounded_void<phi::Integer<unsigned char>>();
    test_is_complete_or_unbounded_void<phi::Integer<short>>();
    test_is_complete_or_unbounded_void<phi::Integer<unsigned short>>();
    test_is_complete_or_unbounded_void<phi::Integer<int>>();
    test_is_complete_or_unbounded_void<phi::Integer<unsigned int>>();
    test_is_complete_or_unbounded_void<phi::Integer<long>>();
    test_is_complete_or_unbounded_void<phi::Integer<unsigned long>>();
    test_is_complete_or_unbounded_void<phi::Integer<long long>>();
    test_is_complete_or_unbounded_void<phi::Integer<unsigned long long>>();
    test_is_complete_or_unbounded_void<phi::FloatingPoint<float>>();
    test_is_complete_or_unbounded_void<phi::FloatingPoint<double>>();
    test_is_complete_or_unbounded_void<phi::FloatingPoint<long double>>();

    test_is_complete_or_unbounded_void<std::vector<int>>();
    test_is_complete_or_unbounded_void<phi::ScopePtr<int>>();

    test_is_complete_or_unbounded_void<int&>();
    test_is_complete_or_unbounded_void<const int&>();
    test_is_complete_or_unbounded_void<volatile int&>();
    test_is_complete_or_unbounded_void<const volatile int&>();
    test_is_complete_or_unbounded_void<int&&>();
    test_is_complete_or_unbounded_void<const int&&>();
    test_is_complete_or_unbounded_void<volatile int&&>();
    test_is_complete_or_unbounded_void<const volatile int&&>();
    test_is_complete_or_unbounded_void<int*>();
    test_is_complete_or_unbounded_void<const int*>();
    test_is_complete_or_unbounded_void<volatile int*>();
    test_is_complete_or_unbounded_void<const volatile int*>();
    test_is_complete_or_unbounded_void<int**>();
    test_is_complete_or_unbounded_void<const int**>();
    test_is_complete_or_unbounded_void<volatile int**>();
    test_is_complete_or_unbounded_void<const volatile int**>();
    test_is_complete_or_unbounded_void<int*&>();
    test_is_complete_or_unbounded_void<const int*&>();
    test_is_complete_or_unbounded_void<volatile int*&>();
    test_is_complete_or_unbounded_void<const volatile int*&>();
    test_is_complete_or_unbounded_void<int*&&>();
    test_is_complete_or_unbounded_void<const int*&&>();
    test_is_complete_or_unbounded_void<volatile int*&&>();
    test_is_complete_or_unbounded_void<const volatile int*&&>();
    test_is_complete_or_unbounded_void<void*>();
    test_is_complete_or_unbounded_void<char[3]>();
    test_is_complete_or_unbounded_void<char[]>();
    test_is_complete_or_unbounded_void<char* [3]>();
    test_is_complete_or_unbounded_void<char*[]>();
    test_is_complete_or_unbounded_void<int(*)[3]>();
    test_is_complete_or_unbounded_void<int(*)[]>();
    test_is_complete_or_unbounded_void<int(&)[3]>();
    test_is_not_complete_or_unbounded_void<int(&)[]>();
    test_is_complete_or_unbounded_void<int(&&)[3]>();
    test_is_complete_or_unbounded_void<int(&&)[]>();
    test_is_complete_or_unbounded_void<char[3][2]>();
    test_is_complete_or_unbounded_void<char[][2]>();
    test_is_complete_or_unbounded_void<char* [3][2]>();
    test_is_complete_or_unbounded_void<char*[][2]>();
    test_is_complete_or_unbounded_void<int(*)[3][2]>();
    test_is_complete_or_unbounded_void<int(*)[][2]>();
    test_is_complete_or_unbounded_void<int(&)[3][2]>();
    test_is_not_complete_or_unbounded_void<int(&)[][2]>();
    test_is_complete_or_unbounded_void<int(&&)[3][2]>();
    test_is_complete_or_unbounded_void<int(&&)[][2]>();
    test_is_complete_or_unbounded_void<Class>();
    test_is_complete_or_unbounded_void<Class[]>();
    test_is_complete_or_unbounded_void<Class[2]>();
    test_is_complete_or_unbounded_void<Template<void>>();
    test_is_complete_or_unbounded_void<Template<int>>();
    test_is_complete_or_unbounded_void<Template<Class>>();
    test_is_complete_or_unbounded_void<Template<incomplete_type>>();
    test_is_complete_or_unbounded_void<VariadicTemplate<>>();
    test_is_complete_or_unbounded_void<VariadicTemplate<void>>();
    test_is_complete_or_unbounded_void<VariadicTemplate<int>>();
    test_is_complete_or_unbounded_void<VariadicTemplate<Class>>();
    test_is_complete_or_unbounded_void<VariadicTemplate<incomplete_type>>();
    test_is_complete_or_unbounded_void<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_complete_or_unbounded_void<PublicDerviedFromTemplate<Base>>();
    test_is_complete_or_unbounded_void<PublicDerviedFromTemplate<Derived>>();
    test_is_complete_or_unbounded_void<PublicDerviedFromTemplate<Class>>();
    test_is_complete_or_unbounded_void<PrivateDerviedFromTemplate<Base>>();
    test_is_complete_or_unbounded_void<PrivateDerviedFromTemplate<Derived>>();
    test_is_complete_or_unbounded_void<PrivateDerviedFromTemplate<Class>>();
    test_is_complete_or_unbounded_void<ProtectedDerviedFromTemplate<Base>>();
    test_is_complete_or_unbounded_void<ProtectedDerviedFromTemplate<Derived>>();
    test_is_complete_or_unbounded_void<ProtectedDerviedFromTemplate<Class>>();
    test_is_complete_or_unbounded_void<Union>();
    test_is_complete_or_unbounded_void<NonEmptyUnion>();
    test_is_complete_or_unbounded_void<Empty>();
    test_is_complete_or_unbounded_void<NotEmpty>();
    test_is_complete_or_unbounded_void<bit_zero>();
    test_is_complete_or_unbounded_void<bit_one>();
    test_is_complete_or_unbounded_void<Base>();
    test_is_complete_or_unbounded_void<Derived>();
    test_is_complete_or_unbounded_void<Abstract>();
    test_is_complete_or_unbounded_void<PublicAbstract>();
    test_is_complete_or_unbounded_void<PrivateAbstract>();
    test_is_complete_or_unbounded_void<ProtectedAbstract>();
    test_is_complete_or_unbounded_void<AbstractTemplate<int>>();
    test_is_complete_or_unbounded_void<AbstractTemplate<double>>();
    test_is_complete_or_unbounded_void<AbstractTemplate<Class>>();
    test_is_complete_or_unbounded_void<AbstractTemplate<incomplete_type>>();
    test_is_complete_or_unbounded_void<Final>();
    test_is_complete_or_unbounded_void<PublicDestructor>();
    test_is_complete_or_unbounded_void<ProtectedDestructor>();
    test_is_complete_or_unbounded_void<PrivateDestructor>();
    test_is_complete_or_unbounded_void<VirtualPublicDestructor>();
    test_is_complete_or_unbounded_void<VirtualProtectedDestructor>();
    test_is_complete_or_unbounded_void<VirtualPrivateDestructor>();
    test_is_complete_or_unbounded_void<PurePublicDestructor>();
    test_is_complete_or_unbounded_void<PureProtectedDestructor>();
    test_is_complete_or_unbounded_void<PurePrivateDestructor>();
    test_is_complete_or_unbounded_void<DeletedPublicDestructor>();
    test_is_complete_or_unbounded_void<DeletedProtectedDestructor>();
    test_is_complete_or_unbounded_void<DeletedPrivateDestructor>();
    test_is_complete_or_unbounded_void<DeletedVirtualPublicDestructor>();
    test_is_complete_or_unbounded_void<DeletedVirtualProtectedDestructor>();
    test_is_complete_or_unbounded_void<DeletedVirtualPrivateDestructor>();
    test_is_complete_or_unbounded_void<Enum>();
    test_is_complete_or_unbounded_void<EnumSigned>();
    test_is_complete_or_unbounded_void<EnumUnsigned>();
    test_is_complete_or_unbounded_void<EnumClass>();
    test_is_complete_or_unbounded_void<EnumStruct>();
    test_is_complete_or_unbounded_void<Function>();
    test_is_complete_or_unbounded_void<FunctionPtr>();
    test_is_complete_or_unbounded_void<MemberObjectPtr>();
    test_is_complete_or_unbounded_void<MemberFunctionPtr>();
    test_is_not_complete_or_unbounded_void<incomplete_type>();
    test_is_not_complete_or_unbounded_void<IncompleteTemplate<void>>();
    test_is_not_complete_or_unbounded_void<IncompleteTemplate<int>>();
    test_is_not_complete_or_unbounded_void<IncompleteTemplate<Class>>();
    test_is_not_complete_or_unbounded_void<IncompleteTemplate<incomplete_type>>();
    test_is_not_complete_or_unbounded_void<IncompleteVariadicTemplate<>>();
    test_is_not_complete_or_unbounded_void<IncompleteVariadicTemplate<void>>();
    test_is_not_complete_or_unbounded_void<IncompleteVariadicTemplate<int>>();
    test_is_not_complete_or_unbounded_void<IncompleteVariadicTemplate<Class>>();
    test_is_not_complete_or_unbounded_void<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_complete_or_unbounded_void<
            IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_complete_or_unbounded_void<int Class::*>();
    test_is_complete_or_unbounded_void<float Class::*>();
    test_is_complete_or_unbounded_void<void * Class::*>();
    test_is_complete_or_unbounded_void<int * Class::*>();
    test_is_complete_or_unbounded_void<int Class::*&>();
    test_is_complete_or_unbounded_void<float Class::*&>();
    test_is_complete_or_unbounded_void<void * Class::*&>();
    test_is_complete_or_unbounded_void<int * Class::*&>();
    test_is_complete_or_unbounded_void<int Class::*&&>();
    test_is_complete_or_unbounded_void<float Class::*&&>();
    test_is_complete_or_unbounded_void<void * Class::*&&>();
    test_is_complete_or_unbounded_void<int * Class::*&&>();
    test_is_complete_or_unbounded_void<int Class::*const>();
    test_is_complete_or_unbounded_void<float Class::*const>();
    test_is_complete_or_unbounded_void<void * Class::*const>();
    test_is_complete_or_unbounded_void<int Class::*const&>();
    test_is_complete_or_unbounded_void<float Class::*const&>();
    test_is_complete_or_unbounded_void<void * Class::*const&>();
    test_is_complete_or_unbounded_void<int Class::*const&&>();
    test_is_complete_or_unbounded_void<float Class::*const&&>();
    test_is_complete_or_unbounded_void<void * Class::*const&&>();
    test_is_complete_or_unbounded_void<int Class::*volatile>();
    test_is_complete_or_unbounded_void<float Class::*volatile>();
    test_is_complete_or_unbounded_void<void * Class::*volatile>();
    test_is_complete_or_unbounded_void<int Class::*volatile&>();
    test_is_complete_or_unbounded_void<float Class::*volatile&>();
    test_is_complete_or_unbounded_void<void * Class::*volatile&>();
    test_is_complete_or_unbounded_void<int Class::*volatile&&>();
    test_is_complete_or_unbounded_void<float Class::*volatile&&>();
    test_is_complete_or_unbounded_void<void * Class::*volatile&&>();
    test_is_complete_or_unbounded_void<int Class::*const volatile>();
    test_is_complete_or_unbounded_void<float Class::*const volatile>();
    test_is_complete_or_unbounded_void<void * Class::*const volatile>();
    test_is_complete_or_unbounded_void<int Class::*const volatile&>();
    test_is_complete_or_unbounded_void<float Class::*const volatile&>();
    test_is_complete_or_unbounded_void<void * Class::*const volatile&>();
    test_is_complete_or_unbounded_void<int Class::*const volatile&&>();
    test_is_complete_or_unbounded_void<float Class::*const volatile&&>();
    test_is_complete_or_unbounded_void<void * Class::*const volatile&&>();
    test_is_complete_or_unbounded_void<NonCopyable>();
    test_is_complete_or_unbounded_void<NonMoveable>();
    test_is_complete_or_unbounded_void<NonConstructible>();
    test_is_complete_or_unbounded_void<Tracked>();
    test_is_complete_or_unbounded_void<TrapConstructible>();
    test_is_complete_or_unbounded_void<TrapImplicitConversion>();
    test_is_complete_or_unbounded_void<TrapComma>();
    test_is_complete_or_unbounded_void<TrapCall>();
    test_is_complete_or_unbounded_void<TrapSelfAssign>();
    test_is_complete_or_unbounded_void<TrapDeref>();
    test_is_complete_or_unbounded_void<TrapArraySubscript>();

    test_is_complete_or_unbounded_void<void()>();
    test_is_complete_or_unbounded_void<void()&>();
    test_is_complete_or_unbounded_void<void() &&>();
    test_is_complete_or_unbounded_void<void() const>();
    test_is_complete_or_unbounded_void<void() const&>();
    test_is_complete_or_unbounded_void<void() const&&>();
    test_is_complete_or_unbounded_void<void() volatile>();
    test_is_complete_or_unbounded_void<void() volatile&>();
    test_is_complete_or_unbounded_void<void() volatile&&>();
    test_is_complete_or_unbounded_void<void() const volatile>();
    test_is_complete_or_unbounded_void<void() const volatile&>();
    test_is_complete_or_unbounded_void<void() const volatile&&>();
    test_is_complete_or_unbounded_void<void() noexcept>();
    test_is_complete_or_unbounded_void<void()& noexcept>();
    test_is_complete_or_unbounded_void<void()&& noexcept>();
    test_is_complete_or_unbounded_void<void() const noexcept>();
    test_is_complete_or_unbounded_void<void() const& noexcept>();
    test_is_complete_or_unbounded_void<void() const&& noexcept>();
    test_is_complete_or_unbounded_void<void() volatile noexcept>();
    test_is_complete_or_unbounded_void<void() volatile& noexcept>();
    test_is_complete_or_unbounded_void<void() volatile&& noexcept>();
    test_is_complete_or_unbounded_void<void() const volatile noexcept>();
    test_is_complete_or_unbounded_void<void() const volatile& noexcept>();
    test_is_complete_or_unbounded_void<void() const volatile&& noexcept>();

    test_is_complete_or_unbounded_void<void(int)>();
    test_is_complete_or_unbounded_void<void(int)&>();
    test_is_complete_or_unbounded_void<void(int) &&>();
    test_is_complete_or_unbounded_void<void(int) const>();
    test_is_complete_or_unbounded_void<void(int) const&>();
    test_is_complete_or_unbounded_void<void(int) const&&>();
    test_is_complete_or_unbounded_void<void(int) volatile>();
    test_is_complete_or_unbounded_void<void(int) volatile&>();
    test_is_complete_or_unbounded_void<void(int) volatile&&>();
    test_is_complete_or_unbounded_void<void(int) const volatile>();
    test_is_complete_or_unbounded_void<void(int) const volatile&>();
    test_is_complete_or_unbounded_void<void(int) const volatile&&>();
    test_is_complete_or_unbounded_void<void(int) noexcept>();
    test_is_complete_or_unbounded_void<void(int)& noexcept>();
    test_is_complete_or_unbounded_void<void(int)&& noexcept>();
    test_is_complete_or_unbounded_void<void(int) const noexcept>();
    test_is_complete_or_unbounded_void<void(int) const& noexcept>();
    test_is_complete_or_unbounded_void<void(int) const&& noexcept>();
    test_is_complete_or_unbounded_void<void(int) volatile noexcept>();
    test_is_complete_or_unbounded_void<void(int) volatile& noexcept>();
    test_is_complete_or_unbounded_void<void(int) volatile&& noexcept>();
    test_is_complete_or_unbounded_void<void(int) const volatile noexcept>();
    test_is_complete_or_unbounded_void<void(int) const volatile& noexcept>();
    test_is_complete_or_unbounded_void<void(int) const volatile&& noexcept>();

    test_is_complete_or_unbounded_void<void(...)>();
    test_is_complete_or_unbounded_void<void(...)&>();
    test_is_complete_or_unbounded_void<void(...) &&>();
    test_is_complete_or_unbounded_void<void(...) const>();
    test_is_complete_or_unbounded_void<void(...) const&>();
    test_is_complete_or_unbounded_void<void(...) const&&>();
    test_is_complete_or_unbounded_void<void(...) volatile>();
    test_is_complete_or_unbounded_void<void(...) volatile&>();
    test_is_complete_or_unbounded_void<void(...) volatile&&>();
    test_is_complete_or_unbounded_void<void(...) const volatile>();
    test_is_complete_or_unbounded_void<void(...) const volatile&>();
    test_is_complete_or_unbounded_void<void(...) const volatile&&>();
    test_is_complete_or_unbounded_void<void(...) noexcept>();
    test_is_complete_or_unbounded_void<void(...)& noexcept>();
    test_is_complete_or_unbounded_void<void(...)&& noexcept>();
    test_is_complete_or_unbounded_void<void(...) const noexcept>();
    test_is_complete_or_unbounded_void<void(...) const& noexcept>();
    test_is_complete_or_unbounded_void<void(...) const&& noexcept>();
    test_is_complete_or_unbounded_void<void(...) volatile noexcept>();
    test_is_complete_or_unbounded_void<void(...) volatile& noexcept>();
    test_is_complete_or_unbounded_void<void(...) volatile&& noexcept>();
    test_is_complete_or_unbounded_void<void(...) const volatile noexcept>();
    test_is_complete_or_unbounded_void<void(...) const volatile& noexcept>();
    test_is_complete_or_unbounded_void<void(...) const volatile&& noexcept>();

    test_is_complete_or_unbounded_void<void(int, ...)>();
    test_is_complete_or_unbounded_void<void(int, ...)&>();
    test_is_complete_or_unbounded_void<void(int, ...) &&>();
    test_is_complete_or_unbounded_void<void(int, ...) const>();
    test_is_complete_or_unbounded_void<void(int, ...) const&>();
    test_is_complete_or_unbounded_void<void(int, ...) const&&>();
    test_is_complete_or_unbounded_void<void(int, ...) volatile>();
    test_is_complete_or_unbounded_void<void(int, ...) volatile&>();
    test_is_complete_or_unbounded_void<void(int, ...) volatile&&>();
    test_is_complete_or_unbounded_void<void(int, ...) const volatile>();
    test_is_complete_or_unbounded_void<void(int, ...) const volatile&>();
    test_is_complete_or_unbounded_void<void(int, ...) const volatile&&>();
    test_is_complete_or_unbounded_void<void(int, ...) noexcept>();
    test_is_complete_or_unbounded_void<void(int, ...)& noexcept>();
    test_is_complete_or_unbounded_void<void(int, ...)&& noexcept>();
    test_is_complete_or_unbounded_void<void(int, ...) const noexcept>();
    test_is_complete_or_unbounded_void<void(int, ...) const& noexcept>();
    test_is_complete_or_unbounded_void<void(int, ...) const&& noexcept>();
    test_is_complete_or_unbounded_void<void(int, ...) volatile noexcept>();
    test_is_complete_or_unbounded_void<void(int, ...) volatile& noexcept>();
    test_is_complete_or_unbounded_void<void(int, ...) volatile&& noexcept>();
    test_is_complete_or_unbounded_void<void(int, ...) const volatile noexcept>();
    test_is_complete_or_unbounded_void<void(int, ...) const volatile& noexcept>();
    test_is_complete_or_unbounded_void<void(int, ...) const volatile&& noexcept>();

    test_is_complete_or_unbounded_void<int()>();
    test_is_complete_or_unbounded_void<int()&>();
    test_is_complete_or_unbounded_void<int() &&>();
    test_is_complete_or_unbounded_void<int() const>();
    test_is_complete_or_unbounded_void<int() const&>();
    test_is_complete_or_unbounded_void<int() const&&>();
    test_is_complete_or_unbounded_void<int() volatile>();
    test_is_complete_or_unbounded_void<int() volatile&>();
    test_is_complete_or_unbounded_void<int() volatile&&>();
    test_is_complete_or_unbounded_void<int() const volatile>();
    test_is_complete_or_unbounded_void<int() const volatile&>();
    test_is_complete_or_unbounded_void<int() const volatile&&>();
    test_is_complete_or_unbounded_void<int() noexcept>();
    test_is_complete_or_unbounded_void<int()& noexcept>();
    test_is_complete_or_unbounded_void<int()&& noexcept>();
    test_is_complete_or_unbounded_void<int() const noexcept>();
    test_is_complete_or_unbounded_void<int() const& noexcept>();
    test_is_complete_or_unbounded_void<int() const&& noexcept>();
    test_is_complete_or_unbounded_void<int() volatile noexcept>();
    test_is_complete_or_unbounded_void<int() volatile& noexcept>();
    test_is_complete_or_unbounded_void<int() volatile&& noexcept>();
    test_is_complete_or_unbounded_void<int() const volatile noexcept>();
    test_is_complete_or_unbounded_void<int() const volatile& noexcept>();
    test_is_complete_or_unbounded_void<int() const volatile&& noexcept>();

    test_is_complete_or_unbounded_void<int(int)>();
    test_is_complete_or_unbounded_void<int(int)&>();
    test_is_complete_or_unbounded_void<int(int) &&>();
    test_is_complete_or_unbounded_void<int(int) const>();
    test_is_complete_or_unbounded_void<int(int) const&>();
    test_is_complete_or_unbounded_void<int(int) const&&>();
    test_is_complete_or_unbounded_void<int(int) volatile>();
    test_is_complete_or_unbounded_void<int(int) volatile&>();
    test_is_complete_or_unbounded_void<int(int) volatile&&>();
    test_is_complete_or_unbounded_void<int(int) const volatile>();
    test_is_complete_or_unbounded_void<int(int) const volatile&>();
    test_is_complete_or_unbounded_void<int(int) const volatile&&>();
    test_is_complete_or_unbounded_void<int(int) noexcept>();
    test_is_complete_or_unbounded_void<int(int)& noexcept>();
    test_is_complete_or_unbounded_void<int(int)&& noexcept>();
    test_is_complete_or_unbounded_void<int(int) const noexcept>();
    test_is_complete_or_unbounded_void<int(int) const& noexcept>();
    test_is_complete_or_unbounded_void<int(int) const&& noexcept>();
    test_is_complete_or_unbounded_void<int(int) volatile noexcept>();
    test_is_complete_or_unbounded_void<int(int) volatile& noexcept>();
    test_is_complete_or_unbounded_void<int(int) volatile&& noexcept>();
    test_is_complete_or_unbounded_void<int(int) const volatile noexcept>();
    test_is_complete_or_unbounded_void<int(int) const volatile& noexcept>();
    test_is_complete_or_unbounded_void<int(int) const volatile&& noexcept>();

    test_is_complete_or_unbounded_void<int(...)>();
    test_is_complete_or_unbounded_void<int(...)&>();
    test_is_complete_or_unbounded_void<int(...) &&>();
    test_is_complete_or_unbounded_void<int(...) const>();
    test_is_complete_or_unbounded_void<int(...) const&>();
    test_is_complete_or_unbounded_void<int(...) const&&>();
    test_is_complete_or_unbounded_void<int(...) volatile>();
    test_is_complete_or_unbounded_void<int(...) volatile&>();
    test_is_complete_or_unbounded_void<int(...) volatile&&>();
    test_is_complete_or_unbounded_void<int(...) const volatile>();
    test_is_complete_or_unbounded_void<int(...) const volatile&>();
    test_is_complete_or_unbounded_void<int(...) const volatile&&>();
    test_is_complete_or_unbounded_void<int(...) noexcept>();
    test_is_complete_or_unbounded_void<int(...)& noexcept>();
    test_is_complete_or_unbounded_void<int(...)&& noexcept>();
    test_is_complete_or_unbounded_void<int(...) const noexcept>();
    test_is_complete_or_unbounded_void<int(...) const& noexcept>();
    test_is_complete_or_unbounded_void<int(...) const&& noexcept>();
    test_is_complete_or_unbounded_void<int(...) volatile noexcept>();
    test_is_complete_or_unbounded_void<int(...) volatile& noexcept>();
    test_is_complete_or_unbounded_void<int(...) volatile&& noexcept>();
    test_is_complete_or_unbounded_void<int(...) const volatile noexcept>();
    test_is_complete_or_unbounded_void<int(...) const volatile& noexcept>();
    test_is_complete_or_unbounded_void<int(...) const volatile&& noexcept>();

    test_is_complete_or_unbounded_void<int(int, ...)>();
    test_is_complete_or_unbounded_void<int(int, ...)&>();
    test_is_complete_or_unbounded_void<int(int, ...) &&>();
    test_is_complete_or_unbounded_void<int(int, ...) const>();
    test_is_complete_or_unbounded_void<int(int, ...) const&>();
    test_is_complete_or_unbounded_void<int(int, ...) const&&>();
    test_is_complete_or_unbounded_void<int(int, ...) volatile>();
    test_is_complete_or_unbounded_void<int(int, ...) volatile&>();
    test_is_complete_or_unbounded_void<int(int, ...) volatile&&>();
    test_is_complete_or_unbounded_void<int(int, ...) const volatile>();
    test_is_complete_or_unbounded_void<int(int, ...) const volatile&>();
    test_is_complete_or_unbounded_void<int(int, ...) const volatile&&>();
    test_is_complete_or_unbounded_void<int(int, ...) noexcept>();
    test_is_complete_or_unbounded_void<int(int, ...)& noexcept>();
    test_is_complete_or_unbounded_void<int(int, ...)&& noexcept>();
    test_is_complete_or_unbounded_void<int(int, ...) const noexcept>();
    test_is_complete_or_unbounded_void<int(int, ...) const& noexcept>();
    test_is_complete_or_unbounded_void<int(int, ...) const&& noexcept>();
    test_is_complete_or_unbounded_void<int(int, ...) volatile noexcept>();
    test_is_complete_or_unbounded_void<int(int, ...) volatile& noexcept>();
    test_is_complete_or_unbounded_void<int(int, ...) volatile&& noexcept>();
    test_is_complete_or_unbounded_void<int(int, ...) const volatile noexcept>();
    test_is_complete_or_unbounded_void<int(int, ...) const volatile& noexcept>();
    test_is_complete_or_unbounded_void<int(int, ...) const volatile&& noexcept>();

    test_is_complete_or_unbounded_void<void (*)()>();
    test_is_complete_or_unbounded_void<void (*)() noexcept>();

    test_is_complete_or_unbounded_void<void (*)(int)>();
    test_is_complete_or_unbounded_void<void (*)(int) noexcept>();

    test_is_complete_or_unbounded_void<void (*)(...)>();
    test_is_complete_or_unbounded_void<void (*)(...) noexcept>();

    test_is_complete_or_unbounded_void<void (*)(int, ...)>();
    test_is_complete_or_unbounded_void<void (*)(int, ...) noexcept>();

    test_is_complete_or_unbounded_void<int (*)()>();
    test_is_complete_or_unbounded_void<int (*)() noexcept>();

    test_is_complete_or_unbounded_void<int (*)(int)>();
    test_is_complete_or_unbounded_void<int (*)(int) noexcept>();

    test_is_complete_or_unbounded_void<int (*)(...)>();
    test_is_complete_or_unbounded_void<int (*)(...) noexcept>();

    test_is_complete_or_unbounded_void<int (*)(int, ...)>();
    test_is_complete_or_unbounded_void<int (*)(int, ...) noexcept>();

    test_is_complete_or_unbounded_void<void (&)()>();
    test_is_complete_or_unbounded_void<void (&)() noexcept>();

    test_is_complete_or_unbounded_void<void (&)(int)>();
    test_is_complete_or_unbounded_void<void (&)(int) noexcept>();

    test_is_complete_or_unbounded_void<void (&)(...)>();
    test_is_complete_or_unbounded_void<void (&)(...) noexcept>();

    test_is_complete_or_unbounded_void<void (&)(int, ...)>();
    test_is_complete_or_unbounded_void<void (&)(int, ...) noexcept>();

    test_is_complete_or_unbounded_void<int (&)()>();
    test_is_complete_or_unbounded_void<int (&)() noexcept>();

    test_is_complete_or_unbounded_void<int (&)(int)>();
    test_is_complete_or_unbounded_void<int (&)(int) noexcept>();

    test_is_complete_or_unbounded_void<int (&)(...)>();
    test_is_complete_or_unbounded_void<int (&)(...) noexcept>();

    test_is_complete_or_unbounded_void<int (&)(int, ...)>();
    test_is_complete_or_unbounded_void<int (&)(int, ...) noexcept>();

    test_is_complete_or_unbounded_void<void(&&)()>();
    test_is_complete_or_unbounded_void<void(&&)() noexcept>();

    test_is_complete_or_unbounded_void<void(&&)(int)>();
    test_is_complete_or_unbounded_void<void(&&)(int) noexcept>();

    test_is_complete_or_unbounded_void<void(&&)(...)>();
    test_is_complete_or_unbounded_void<void(&&)(...) noexcept>();

    test_is_complete_or_unbounded_void<void(&&)(int, ...)>();
    test_is_complete_or_unbounded_void<void(&&)(int, ...) noexcept>();

    test_is_complete_or_unbounded_void<int(&&)()>();
    test_is_complete_or_unbounded_void<int(&&)() noexcept>();

    test_is_complete_or_unbounded_void<int(&&)(int)>();
    test_is_complete_or_unbounded_void<int(&&)(int) noexcept>();

    test_is_complete_or_unbounded_void<int(&&)(...)>();
    test_is_complete_or_unbounded_void<int(&&)(...) noexcept>();

    test_is_complete_or_unbounded_void<int(&&)(int, ...)>();
    test_is_complete_or_unbounded_void<int(&&)(int, ...) noexcept>();

    test_is_complete_or_unbounded_void<void (Class::*)()>();
    test_is_complete_or_unbounded_void<void (Class::*)()&>();
    test_is_complete_or_unbounded_void<void (Class::*)() &&>();
    test_is_complete_or_unbounded_void<void (Class::*)() const>();
    test_is_complete_or_unbounded_void<void (Class::*)() const&>();
    test_is_complete_or_unbounded_void<void (Class::*)() const&&>();
    test_is_complete_or_unbounded_void<void (Class::*)() noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)()& noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)()&& noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)() const noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)() const& noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)() const&& noexcept>();

    test_is_complete_or_unbounded_void<void (Class::*)(int)>();
    test_is_complete_or_unbounded_void<void (Class::*)(int)&>();
    test_is_complete_or_unbounded_void<void (Class::*)(int) &&>();
    test_is_complete_or_unbounded_void<void (Class::*)(int) const>();
    test_is_complete_or_unbounded_void<void (Class::*)(int) const&>();
    test_is_complete_or_unbounded_void<void (Class::*)(int) const&&>();
    test_is_complete_or_unbounded_void<void (Class::*)(int) noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(int)& noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(int)&& noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(int) const noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(int) const& noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(int) const&& noexcept>();

    test_is_complete_or_unbounded_void<void (Class::*)(...)>();
    test_is_complete_or_unbounded_void<void (Class::*)(...)&>();
    test_is_complete_or_unbounded_void<void (Class::*)(...) &&>();
    test_is_complete_or_unbounded_void<void (Class::*)(...) const>();
    test_is_complete_or_unbounded_void<void (Class::*)(...) const&>();
    test_is_complete_or_unbounded_void<void (Class::*)(...) const&&>();
    test_is_complete_or_unbounded_void<void (Class::*)(...) noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(...)& noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(...)&& noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(...) const noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(...) const& noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(...) const&& noexcept>();

    test_is_complete_or_unbounded_void<void (Class::*)(int, ...)>();
    test_is_complete_or_unbounded_void<void (Class::*)(int, ...)&>();
    test_is_complete_or_unbounded_void<void (Class::*)(int, ...) &&>();
    test_is_complete_or_unbounded_void<void (Class::*)(int, ...) const>();
    test_is_complete_or_unbounded_void<void (Class::*)(int, ...) const&>();
    test_is_complete_or_unbounded_void<void (Class::*)(int, ...) const&&>();
    test_is_complete_or_unbounded_void<void (Class::*)(int, ...) noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(int, ...)& noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(int, ...)&& noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(int, ...) const noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(int, ...) const& noexcept>();
    test_is_complete_or_unbounded_void<void (Class::*)(int, ...) const&& noexcept>();

    test_is_complete_or_unbounded_void<int (Class::*)()>();
    test_is_complete_or_unbounded_void<int (Class::*)()&>();
    test_is_complete_or_unbounded_void<int (Class::*)() &&>();
    test_is_complete_or_unbounded_void<int (Class::*)() const>();
    test_is_complete_or_unbounded_void<int (Class::*)() const&>();
    test_is_complete_or_unbounded_void<int (Class::*)() const&&>();
    test_is_complete_or_unbounded_void<int (Class::*)() noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)()& noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)()&& noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)() const noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)() const& noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)() const&& noexcept>();

    test_is_complete_or_unbounded_void<int (Class::*)(int)>();
    test_is_complete_or_unbounded_void<int (Class::*)(int)&>();
    test_is_complete_or_unbounded_void<int (Class::*)(int) &&>();
    test_is_complete_or_unbounded_void<int (Class::*)(int) const>();
    test_is_complete_or_unbounded_void<int (Class::*)(int) const&>();
    test_is_complete_or_unbounded_void<int (Class::*)(int) const&&>();
    test_is_complete_or_unbounded_void<int (Class::*)(int) noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(int)& noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(int)&& noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(int) const noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(int) const& noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(int) const&& noexcept>();

    test_is_complete_or_unbounded_void<int (Class::*)(...)>();
    test_is_complete_or_unbounded_void<int (Class::*)(...)&>();
    test_is_complete_or_unbounded_void<int (Class::*)(...) &&>();
    test_is_complete_or_unbounded_void<int (Class::*)(...) const>();
    test_is_complete_or_unbounded_void<int (Class::*)(...) const&>();
    test_is_complete_or_unbounded_void<int (Class::*)(...) const&&>();
    test_is_complete_or_unbounded_void<int (Class::*)(...) noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(...)& noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(...)&& noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(...) const noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(...) const& noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(...) const&& noexcept>();

    test_is_complete_or_unbounded_void<int (Class::*)(int, ...)>();
    test_is_complete_or_unbounded_void<int (Class::*)(int, ...)&>();
    test_is_complete_or_unbounded_void<int (Class::*)(int, ...) &&>();
    test_is_complete_or_unbounded_void<int (Class::*)(int, ...) const>();
    test_is_complete_or_unbounded_void<int (Class::*)(int, ...) const&>();
    test_is_complete_or_unbounded_void<int (Class::*)(int, ...) const&&>();
    test_is_complete_or_unbounded_void<int (Class::*)(int, ...) noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(int, ...)& noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(int, ...)&& noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(int, ...) const noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(int, ...) const& noexcept>();
    test_is_complete_or_unbounded_void<int (Class::*)(int, ...) const&& noexcept>();
}
