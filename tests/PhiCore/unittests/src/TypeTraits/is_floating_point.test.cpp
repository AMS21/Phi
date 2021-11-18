#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_floating_point.hpp>
#include <vector>

template <typename T>
void test_is_floating_point_impl()
{
    STATIC_REQUIRE(phi::is_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_floating_point<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_floating_point_v<T>);
#endif
}

template <typename T>
void test_is_floating_point()
{
    test_is_floating_point_impl<T>();
    test_is_floating_point_impl<const T>();
    test_is_floating_point_impl<volatile T>();
    test_is_floating_point_impl<const volatile T>();
}

template <typename T>
void test_is_not_floating_point_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_floating_point<T>::value);
    STATIC_REQUIRE(phi::is_not_floating_point<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_floating_point_v<T>);
    STATIC_REQUIRE(phi::is_not_floating_point_v<T>);
#endif
}

template <typename T>
void test_is_not_floating_point()
{
    test_is_not_floating_point_impl<T>();
    test_is_not_floating_point_impl<const T>();
    test_is_not_floating_point_impl<volatile T>();
    test_is_not_floating_point_impl<const volatile T>();
}

TEST_CASE("is_floating_point")
{
    test_is_not_floating_point<void>();
    test_is_not_floating_point<phi::nullptr_t>();
    test_is_not_floating_point<bool>();
    test_is_not_floating_point<char>();
    test_is_not_floating_point<signed char>();
    test_is_not_floating_point<unsigned char>();
    test_is_not_floating_point<short>();
    test_is_not_floating_point<unsigned short>();
    test_is_not_floating_point<int>();
    test_is_not_floating_point<unsigned int>();
    test_is_not_floating_point<long>();
    test_is_not_floating_point<unsigned long>();
    test_is_not_floating_point<long long>();
    test_is_not_floating_point<unsigned long long>();
    test_is_floating_point<float>();
    test_is_floating_point<double>();
    test_is_floating_point<long double>();
    test_is_not_floating_point<char8_t>();
    test_is_not_floating_point<char16_t>();
    test_is_not_floating_point<char32_t>();
    test_is_not_floating_point<wchar_t>();

    test_is_not_floating_point<phi::Boolean>();
    test_is_not_floating_point<phi::Integer<signed char>>();
    test_is_not_floating_point<phi::Integer<unsigned char>>();
    test_is_not_floating_point<phi::Integer<short>>();
    test_is_not_floating_point<phi::Integer<unsigned short>>();
    test_is_not_floating_point<phi::Integer<int>>();
    test_is_not_floating_point<phi::Integer<unsigned int>>();
    test_is_not_floating_point<phi::Integer<long>>();
    test_is_not_floating_point<phi::Integer<unsigned long>>();
    test_is_not_floating_point<phi::Integer<long long>>();
    test_is_not_floating_point<phi::Integer<unsigned long long>>();
    test_is_floating_point<phi::FloatingPoint<float>>();
    test_is_floating_point<phi::FloatingPoint<double>>();
    test_is_floating_point<phi::FloatingPoint<long double>>();

    test_is_not_floating_point<std::vector<int>>();
    test_is_not_floating_point<phi::ScopePtr<int>>();

    test_is_not_floating_point<int&>();
    test_is_not_floating_point<const int&>();
    test_is_not_floating_point<volatile int&>();
    test_is_not_floating_point<const volatile int&>();
    test_is_not_floating_point<int&&>();
    test_is_not_floating_point<const int&&>();
    test_is_not_floating_point<volatile int&&>();
    test_is_not_floating_point<const volatile int&&>();
    test_is_not_floating_point<int*>();
    test_is_not_floating_point<const int*>();
    test_is_not_floating_point<volatile int*>();
    test_is_not_floating_point<const volatile int*>();
    test_is_not_floating_point<int**>();
    test_is_not_floating_point<const int**>();
    test_is_not_floating_point<volatile int**>();
    test_is_not_floating_point<const volatile int**>();
    test_is_not_floating_point<int*&>();
    test_is_not_floating_point<const int*&>();
    test_is_not_floating_point<volatile int*&>();
    test_is_not_floating_point<const volatile int*&>();
    test_is_not_floating_point<int*&&>();
    test_is_not_floating_point<const int*&&>();
    test_is_not_floating_point<volatile int*&&>();
    test_is_not_floating_point<const volatile int*&&>();
    test_is_not_floating_point<void*>();
    test_is_not_floating_point<char[3]>();
    test_is_not_floating_point<char[]>();
    test_is_not_floating_point<char* [3]>();
    test_is_not_floating_point<char*[]>();
    test_is_not_floating_point<int(*)[3]>();
    test_is_not_floating_point<int(*)[]>();
    test_is_not_floating_point<int(&)[3]>();
    test_is_not_floating_point<int(&)[]>();
    test_is_not_floating_point<int(&&)[3]>();
    test_is_not_floating_point<int(&&)[]>();
    test_is_not_floating_point<char[3][2]>();
    test_is_not_floating_point<char[][2]>();
    test_is_not_floating_point<char* [3][2]>();
    test_is_not_floating_point<char*[][2]>();
    test_is_not_floating_point<int(*)[3][2]>();
    test_is_not_floating_point<int(*)[][2]>();
    test_is_not_floating_point<int(&)[3][2]>();
    test_is_not_floating_point<int(&)[][2]>();
    test_is_not_floating_point<int(&&)[3][2]>();
    test_is_not_floating_point<int(&&)[][2]>();
    test_is_not_floating_point<Class>();
    test_is_not_floating_point<Class[]>();
    test_is_not_floating_point<Class[2]>();
    test_is_not_floating_point<Template<void>>();
    test_is_not_floating_point<Template<int>>();
    test_is_not_floating_point<Template<Class>>();
    test_is_not_floating_point<Template<incomplete_type>>();
    test_is_not_floating_point<VariadicTemplate<>>();
    test_is_not_floating_point<VariadicTemplate<void>>();
    test_is_not_floating_point<VariadicTemplate<int>>();
    test_is_not_floating_point<VariadicTemplate<Class>>();
    test_is_not_floating_point<VariadicTemplate<incomplete_type>>();
    test_is_not_floating_point<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_floating_point<PublicDerviedFromTemplate<Base>>();
    test_is_not_floating_point<PublicDerviedFromTemplate<Derived>>();
    test_is_not_floating_point<PublicDerviedFromTemplate<Class>>();
    test_is_not_floating_point<PrivateDerviedFromTemplate<Base>>();
    test_is_not_floating_point<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_floating_point<PrivateDerviedFromTemplate<Class>>();
    test_is_not_floating_point<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_floating_point<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_floating_point<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_floating_point<Union>();
    test_is_not_floating_point<NonEmptyUnion>();
    test_is_not_floating_point<Empty>();
    test_is_not_floating_point<NotEmpty>();
    test_is_not_floating_point<bit_zero>();
    test_is_not_floating_point<bit_one>();
    test_is_not_floating_point<Base>();
    test_is_not_floating_point<Derived>();
    test_is_not_floating_point<Abstract>();
    test_is_not_floating_point<PublicAbstract>();
    test_is_not_floating_point<PrivateAbstract>();
    test_is_not_floating_point<ProtectedAbstract>();
    test_is_not_floating_point<AbstractTemplate<int>>();
    test_is_not_floating_point<AbstractTemplate<double>>();
    test_is_not_floating_point<AbstractTemplate<Class>>();
    test_is_not_floating_point<AbstractTemplate<incomplete_type>>();
    test_is_not_floating_point<Final>();
    test_is_not_floating_point<PublicDestructor>();
    test_is_not_floating_point<ProtectedDestructor>();
    test_is_not_floating_point<PrivateDestructor>();
    test_is_not_floating_point<VirtualPublicDestructor>();
    test_is_not_floating_point<VirtualProtectedDestructor>();
    test_is_not_floating_point<VirtualPrivateDestructor>();
    test_is_not_floating_point<PurePublicDestructor>();
    test_is_not_floating_point<PureProtectedDestructor>();
    test_is_not_floating_point<PurePrivateDestructor>();
    test_is_not_floating_point<DeletedPublicDestructor>();
    test_is_not_floating_point<DeletedProtectedDestructor>();
    test_is_not_floating_point<DeletedPrivateDestructor>();
    test_is_not_floating_point<DeletedVirtualPublicDestructor>();
    test_is_not_floating_point<DeletedVirtualProtectedDestructor>();
    test_is_not_floating_point<DeletedVirtualPrivateDestructor>();
    test_is_not_floating_point<Final>();
    test_is_not_floating_point<Enum>();
    test_is_not_floating_point<EnumSigned>();
    test_is_not_floating_point<EnumUnsigned>();
    test_is_not_floating_point<EnumClass>();
    test_is_not_floating_point<EnumStruct>();
    test_is_not_floating_point<Function>();
    test_is_not_floating_point<FunctionPtr>();
    test_is_not_floating_point<MemberObjectPtr>();
    test_is_not_floating_point<MemberFunctionPtr>();
    test_is_not_floating_point<incomplete_type>();
    test_is_not_floating_point<IncompleteTemplate<void>>();
    test_is_not_floating_point<IncompleteTemplate<int>>();
    test_is_not_floating_point<IncompleteTemplate<Class>>();
    test_is_not_floating_point<IncompleteTemplate<incomplete_type>>();
    test_is_not_floating_point<IncompleteVariadicTemplate<>>();
    test_is_not_floating_point<IncompleteVariadicTemplate<void>>();
    test_is_not_floating_point<IncompleteVariadicTemplate<int>>();
    test_is_not_floating_point<IncompleteVariadicTemplate<Class>>();
    test_is_not_floating_point<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_floating_point<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_floating_point<int Class::*>();
    test_is_not_floating_point<float Class::*>();
    test_is_not_floating_point<void * Class::*>();
    test_is_not_floating_point<int * Class::*>();
    test_is_not_floating_point<int Class::*&>();
    test_is_not_floating_point<float Class::*&>();
    test_is_not_floating_point<void * Class::*&>();
    test_is_not_floating_point<int * Class::*&>();
    test_is_not_floating_point<int Class::*&&>();
    test_is_not_floating_point<float Class::*&&>();
    test_is_not_floating_point<void * Class::*&&>();
    test_is_not_floating_point<int * Class::*&&>();
    test_is_not_floating_point<int Class::*const>();
    test_is_not_floating_point<float Class::*const>();
    test_is_not_floating_point<void * Class::*const>();
    test_is_not_floating_point<int Class::*const&>();
    test_is_not_floating_point<float Class::*const&>();
    test_is_not_floating_point<void * Class::*const&>();
    test_is_not_floating_point<int Class::*const&&>();
    test_is_not_floating_point<float Class::*const&&>();
    test_is_not_floating_point<void * Class::*const&&>();
    test_is_not_floating_point<int Class::*volatile>();
    test_is_not_floating_point<float Class::*volatile>();
    test_is_not_floating_point<void * Class::*volatile>();
    test_is_not_floating_point<int Class::*volatile&>();
    test_is_not_floating_point<float Class::*volatile&>();
    test_is_not_floating_point<void * Class::*volatile&>();
    test_is_not_floating_point<int Class::*volatile&&>();
    test_is_not_floating_point<float Class::*volatile&&>();
    test_is_not_floating_point<void * Class::*volatile&&>();
    test_is_not_floating_point<int Class::*const volatile>();
    test_is_not_floating_point<float Class::*const volatile>();
    test_is_not_floating_point<void * Class::*const volatile>();
    test_is_not_floating_point<int Class::*const volatile&>();
    test_is_not_floating_point<float Class::*const volatile&>();
    test_is_not_floating_point<void * Class::*const volatile&>();
    test_is_not_floating_point<int Class::*const volatile&&>();
    test_is_not_floating_point<float Class::*const volatile&&>();
    test_is_not_floating_point<void * Class::*const volatile&&>();
    test_is_not_floating_point<NonCopyable>();
    test_is_not_floating_point<NonMoveable>();
    test_is_not_floating_point<NonConstructible>();
    test_is_not_floating_point<Tracked>();
    test_is_not_floating_point<TrapConstructible>();
    test_is_not_floating_point<TrapImplicitConversion>();
    test_is_not_floating_point<TrapComma>();
    test_is_not_floating_point<TrapCall>();
    test_is_not_floating_point<TrapSelfAssign>();
    test_is_not_floating_point<TrapDeref>();
    test_is_not_floating_point<TrapArraySubscript>();

    test_is_not_floating_point<void()>();
    test_is_not_floating_point<void()&>();
    test_is_not_floating_point<void() &&>();
    test_is_not_floating_point<void() const>();
    test_is_not_floating_point<void() const&>();
    test_is_not_floating_point<void() const&&>();
    test_is_not_floating_point<void() volatile>();
    test_is_not_floating_point<void() volatile&>();
    test_is_not_floating_point<void() volatile&&>();
    test_is_not_floating_point<void() const volatile>();
    test_is_not_floating_point<void() const volatile&>();
    test_is_not_floating_point<void() const volatile&&>();
    test_is_not_floating_point<void() noexcept>();
    test_is_not_floating_point<void()& noexcept>();
    test_is_not_floating_point<void()&& noexcept>();
    test_is_not_floating_point<void() const noexcept>();
    test_is_not_floating_point<void() const& noexcept>();
    test_is_not_floating_point<void() const&& noexcept>();
    test_is_not_floating_point<void() volatile noexcept>();
    test_is_not_floating_point<void() volatile& noexcept>();
    test_is_not_floating_point<void() volatile&& noexcept>();
    test_is_not_floating_point<void() const volatile noexcept>();
    test_is_not_floating_point<void() const volatile& noexcept>();
    test_is_not_floating_point<void() const volatile&& noexcept>();

    test_is_not_floating_point<void(int)>();
    test_is_not_floating_point<void(int)&>();
    test_is_not_floating_point<void(int) &&>();
    test_is_not_floating_point<void(int) const>();
    test_is_not_floating_point<void(int) const&>();
    test_is_not_floating_point<void(int) const&&>();
    test_is_not_floating_point<void(int) volatile>();
    test_is_not_floating_point<void(int) volatile&>();
    test_is_not_floating_point<void(int) volatile&&>();
    test_is_not_floating_point<void(int) const volatile>();
    test_is_not_floating_point<void(int) const volatile&>();
    test_is_not_floating_point<void(int) const volatile&&>();
    test_is_not_floating_point<void(int) noexcept>();
    test_is_not_floating_point<void(int)& noexcept>();
    test_is_not_floating_point<void(int)&& noexcept>();
    test_is_not_floating_point<void(int) const noexcept>();
    test_is_not_floating_point<void(int) const& noexcept>();
    test_is_not_floating_point<void(int) const&& noexcept>();
    test_is_not_floating_point<void(int) volatile noexcept>();
    test_is_not_floating_point<void(int) volatile& noexcept>();
    test_is_not_floating_point<void(int) volatile&& noexcept>();
    test_is_not_floating_point<void(int) const volatile noexcept>();
    test_is_not_floating_point<void(int) const volatile& noexcept>();
    test_is_not_floating_point<void(int) const volatile&& noexcept>();

    test_is_not_floating_point<void(...)>();
    test_is_not_floating_point<void(...)&>();
    test_is_not_floating_point<void(...) &&>();
    test_is_not_floating_point<void(...) const>();
    test_is_not_floating_point<void(...) const&>();
    test_is_not_floating_point<void(...) const&&>();
    test_is_not_floating_point<void(...) volatile>();
    test_is_not_floating_point<void(...) volatile&>();
    test_is_not_floating_point<void(...) volatile&&>();
    test_is_not_floating_point<void(...) const volatile>();
    test_is_not_floating_point<void(...) const volatile&>();
    test_is_not_floating_point<void(...) const volatile&&>();
    test_is_not_floating_point<void(...) noexcept>();
    test_is_not_floating_point<void(...)& noexcept>();
    test_is_not_floating_point<void(...)&& noexcept>();
    test_is_not_floating_point<void(...) const noexcept>();
    test_is_not_floating_point<void(...) const& noexcept>();
    test_is_not_floating_point<void(...) const&& noexcept>();
    test_is_not_floating_point<void(...) volatile noexcept>();
    test_is_not_floating_point<void(...) volatile& noexcept>();
    test_is_not_floating_point<void(...) volatile&& noexcept>();
    test_is_not_floating_point<void(...) const volatile noexcept>();
    test_is_not_floating_point<void(...) const volatile& noexcept>();
    test_is_not_floating_point<void(...) const volatile&& noexcept>();

    test_is_not_floating_point<void(int, ...)>();
    test_is_not_floating_point<void(int, ...)&>();
    test_is_not_floating_point<void(int, ...) &&>();
    test_is_not_floating_point<void(int, ...) const>();
    test_is_not_floating_point<void(int, ...) const&>();
    test_is_not_floating_point<void(int, ...) const&&>();
    test_is_not_floating_point<void(int, ...) volatile>();
    test_is_not_floating_point<void(int, ...) volatile&>();
    test_is_not_floating_point<void(int, ...) volatile&&>();
    test_is_not_floating_point<void(int, ...) const volatile>();
    test_is_not_floating_point<void(int, ...) const volatile&>();
    test_is_not_floating_point<void(int, ...) const volatile&&>();
    test_is_not_floating_point<void(int, ...) noexcept>();
    test_is_not_floating_point<void(int, ...)& noexcept>();
    test_is_not_floating_point<void(int, ...)&& noexcept>();
    test_is_not_floating_point<void(int, ...) const noexcept>();
    test_is_not_floating_point<void(int, ...) const& noexcept>();
    test_is_not_floating_point<void(int, ...) const&& noexcept>();
    test_is_not_floating_point<void(int, ...) volatile noexcept>();
    test_is_not_floating_point<void(int, ...) volatile& noexcept>();
    test_is_not_floating_point<void(int, ...) volatile&& noexcept>();
    test_is_not_floating_point<void(int, ...) const volatile noexcept>();
    test_is_not_floating_point<void(int, ...) const volatile& noexcept>();
    test_is_not_floating_point<void(int, ...) const volatile&& noexcept>();

    test_is_not_floating_point<int()>();
    test_is_not_floating_point<int()&>();
    test_is_not_floating_point<int() &&>();
    test_is_not_floating_point<int() const>();
    test_is_not_floating_point<int() const&>();
    test_is_not_floating_point<int() const&&>();
    test_is_not_floating_point<int() volatile>();
    test_is_not_floating_point<int() volatile&>();
    test_is_not_floating_point<int() volatile&&>();
    test_is_not_floating_point<int() const volatile>();
    test_is_not_floating_point<int() const volatile&>();
    test_is_not_floating_point<int() const volatile&&>();
    test_is_not_floating_point<int() noexcept>();
    test_is_not_floating_point<int()& noexcept>();
    test_is_not_floating_point<int()&& noexcept>();
    test_is_not_floating_point<int() const noexcept>();
    test_is_not_floating_point<int() const& noexcept>();
    test_is_not_floating_point<int() const&& noexcept>();
    test_is_not_floating_point<int() volatile noexcept>();
    test_is_not_floating_point<int() volatile& noexcept>();
    test_is_not_floating_point<int() volatile&& noexcept>();
    test_is_not_floating_point<int() const volatile noexcept>();
    test_is_not_floating_point<int() const volatile& noexcept>();
    test_is_not_floating_point<int() const volatile&& noexcept>();

    test_is_not_floating_point<int(int)>();
    test_is_not_floating_point<int(int)&>();
    test_is_not_floating_point<int(int) &&>();
    test_is_not_floating_point<int(int) const>();
    test_is_not_floating_point<int(int) const&>();
    test_is_not_floating_point<int(int) const&&>();
    test_is_not_floating_point<int(int) volatile>();
    test_is_not_floating_point<int(int) volatile&>();
    test_is_not_floating_point<int(int) volatile&&>();
    test_is_not_floating_point<int(int) const volatile>();
    test_is_not_floating_point<int(int) const volatile&>();
    test_is_not_floating_point<int(int) const volatile&&>();
    test_is_not_floating_point<int(int) noexcept>();
    test_is_not_floating_point<int(int)& noexcept>();
    test_is_not_floating_point<int(int)&& noexcept>();
    test_is_not_floating_point<int(int) const noexcept>();
    test_is_not_floating_point<int(int) const& noexcept>();
    test_is_not_floating_point<int(int) const&& noexcept>();
    test_is_not_floating_point<int(int) volatile noexcept>();
    test_is_not_floating_point<int(int) volatile& noexcept>();
    test_is_not_floating_point<int(int) volatile&& noexcept>();
    test_is_not_floating_point<int(int) const volatile noexcept>();
    test_is_not_floating_point<int(int) const volatile& noexcept>();
    test_is_not_floating_point<int(int) const volatile&& noexcept>();

    test_is_not_floating_point<int(...)>();
    test_is_not_floating_point<int(...)&>();
    test_is_not_floating_point<int(...) &&>();
    test_is_not_floating_point<int(...) const>();
    test_is_not_floating_point<int(...) const&>();
    test_is_not_floating_point<int(...) const&&>();
    test_is_not_floating_point<int(...) volatile>();
    test_is_not_floating_point<int(...) volatile&>();
    test_is_not_floating_point<int(...) volatile&&>();
    test_is_not_floating_point<int(...) const volatile>();
    test_is_not_floating_point<int(...) const volatile&>();
    test_is_not_floating_point<int(...) const volatile&&>();
    test_is_not_floating_point<int(...) noexcept>();
    test_is_not_floating_point<int(...)& noexcept>();
    test_is_not_floating_point<int(...)&& noexcept>();
    test_is_not_floating_point<int(...) const noexcept>();
    test_is_not_floating_point<int(...) const& noexcept>();
    test_is_not_floating_point<int(...) const&& noexcept>();
    test_is_not_floating_point<int(...) volatile noexcept>();
    test_is_not_floating_point<int(...) volatile& noexcept>();
    test_is_not_floating_point<int(...) volatile&& noexcept>();
    test_is_not_floating_point<int(...) const volatile noexcept>();
    test_is_not_floating_point<int(...) const volatile& noexcept>();
    test_is_not_floating_point<int(...) const volatile&& noexcept>();

    test_is_not_floating_point<int(int, ...)>();
    test_is_not_floating_point<int(int, ...)&>();
    test_is_not_floating_point<int(int, ...) &&>();
    test_is_not_floating_point<int(int, ...) const>();
    test_is_not_floating_point<int(int, ...) const&>();
    test_is_not_floating_point<int(int, ...) const&&>();
    test_is_not_floating_point<int(int, ...) volatile>();
    test_is_not_floating_point<int(int, ...) volatile&>();
    test_is_not_floating_point<int(int, ...) volatile&&>();
    test_is_not_floating_point<int(int, ...) const volatile>();
    test_is_not_floating_point<int(int, ...) const volatile&>();
    test_is_not_floating_point<int(int, ...) const volatile&&>();
    test_is_not_floating_point<int(int, ...) noexcept>();
    test_is_not_floating_point<int(int, ...)& noexcept>();
    test_is_not_floating_point<int(int, ...)&& noexcept>();
    test_is_not_floating_point<int(int, ...) const noexcept>();
    test_is_not_floating_point<int(int, ...) const& noexcept>();
    test_is_not_floating_point<int(int, ...) const&& noexcept>();
    test_is_not_floating_point<int(int, ...) volatile noexcept>();
    test_is_not_floating_point<int(int, ...) volatile& noexcept>();
    test_is_not_floating_point<int(int, ...) volatile&& noexcept>();
    test_is_not_floating_point<int(int, ...) const volatile noexcept>();
    test_is_not_floating_point<int(int, ...) const volatile& noexcept>();
    test_is_not_floating_point<int(int, ...) const volatile&& noexcept>();

    test_is_not_floating_point<void (*)()>();
    test_is_not_floating_point<void (*)() noexcept>();

    test_is_not_floating_point<void (*)(int)>();
    test_is_not_floating_point<void (*)(int) noexcept>();

    test_is_not_floating_point<void (*)(...)>();
    test_is_not_floating_point<void (*)(...) noexcept>();

    test_is_not_floating_point<void (*)(int, ...)>();
    test_is_not_floating_point<void (*)(int, ...) noexcept>();

    test_is_not_floating_point<int (*)()>();
    test_is_not_floating_point<int (*)() noexcept>();

    test_is_not_floating_point<int (*)(int)>();
    test_is_not_floating_point<int (*)(int) noexcept>();

    test_is_not_floating_point<int (*)(...)>();
    test_is_not_floating_point<int (*)(...) noexcept>();

    test_is_not_floating_point<int (*)(int, ...)>();
    test_is_not_floating_point<int (*)(int, ...) noexcept>();

    test_is_not_floating_point<void (&)()>();
    test_is_not_floating_point<void (&)() noexcept>();

    test_is_not_floating_point<void (&)(int)>();
    test_is_not_floating_point<void (&)(int) noexcept>();

    test_is_not_floating_point<void (&)(...)>();
    test_is_not_floating_point<void (&)(...) noexcept>();

    test_is_not_floating_point<void (&)(int, ...)>();
    test_is_not_floating_point<void (&)(int, ...) noexcept>();

    test_is_not_floating_point<int (&)()>();
    test_is_not_floating_point<int (&)() noexcept>();

    test_is_not_floating_point<int (&)(int)>();
    test_is_not_floating_point<int (&)(int) noexcept>();

    test_is_not_floating_point<int (&)(...)>();
    test_is_not_floating_point<int (&)(...) noexcept>();

    test_is_not_floating_point<int (&)(int, ...)>();
    test_is_not_floating_point<int (&)(int, ...) noexcept>();

    test_is_not_floating_point<void(&&)()>();
    test_is_not_floating_point<void(&&)() noexcept>();

    test_is_not_floating_point<void(&&)(int)>();
    test_is_not_floating_point<void(&&)(int) noexcept>();

    test_is_not_floating_point<void(&&)(...)>();
    test_is_not_floating_point<void(&&)(...) noexcept>();

    test_is_not_floating_point<void(&&)(int, ...)>();
    test_is_not_floating_point<void(&&)(int, ...) noexcept>();

    test_is_not_floating_point<int(&&)()>();
    test_is_not_floating_point<int(&&)() noexcept>();

    test_is_not_floating_point<int(&&)(int)>();
    test_is_not_floating_point<int(&&)(int) noexcept>();

    test_is_not_floating_point<int(&&)(...)>();
    test_is_not_floating_point<int(&&)(...) noexcept>();

    test_is_not_floating_point<int(&&)(int, ...)>();
    test_is_not_floating_point<int(&&)(int, ...) noexcept>();

    test_is_not_floating_point<void (Class::*)()>();
    test_is_not_floating_point<void (Class::*)()&>();
    test_is_not_floating_point<void (Class::*)() &&>();
    test_is_not_floating_point<void (Class::*)() const>();
    test_is_not_floating_point<void (Class::*)() const&>();
    test_is_not_floating_point<void (Class::*)() const&&>();
    test_is_not_floating_point<void (Class::*)() noexcept>();
    test_is_not_floating_point<void (Class::*)()& noexcept>();
    test_is_not_floating_point<void (Class::*)()&& noexcept>();
    test_is_not_floating_point<void (Class::*)() const noexcept>();
    test_is_not_floating_point<void (Class::*)() const& noexcept>();
    test_is_not_floating_point<void (Class::*)() const&& noexcept>();

    test_is_not_floating_point<void (Class::*)(int)>();
    test_is_not_floating_point<void (Class::*)(int)&>();
    test_is_not_floating_point<void (Class::*)(int) &&>();
    test_is_not_floating_point<void (Class::*)(int) const>();
    test_is_not_floating_point<void (Class::*)(int) const&>();
    test_is_not_floating_point<void (Class::*)(int) const&&>();
    test_is_not_floating_point<void (Class::*)(int) noexcept>();
    test_is_not_floating_point<void (Class::*)(int)& noexcept>();
    test_is_not_floating_point<void (Class::*)(int)&& noexcept>();
    test_is_not_floating_point<void (Class::*)(int) const noexcept>();
    test_is_not_floating_point<void (Class::*)(int) const& noexcept>();
    test_is_not_floating_point<void (Class::*)(int) const&& noexcept>();

    test_is_not_floating_point<void (Class::*)(...)>();
    test_is_not_floating_point<void (Class::*)(...)&>();
    test_is_not_floating_point<void (Class::*)(...) &&>();
    test_is_not_floating_point<void (Class::*)(...) const>();
    test_is_not_floating_point<void (Class::*)(...) const&>();
    test_is_not_floating_point<void (Class::*)(...) const&&>();
    test_is_not_floating_point<void (Class::*)(...) noexcept>();
    test_is_not_floating_point<void (Class::*)(...)& noexcept>();
    test_is_not_floating_point<void (Class::*)(...)&& noexcept>();
    test_is_not_floating_point<void (Class::*)(...) const noexcept>();
    test_is_not_floating_point<void (Class::*)(...) const& noexcept>();
    test_is_not_floating_point<void (Class::*)(...) const&& noexcept>();

    test_is_not_floating_point<void (Class::*)(int, ...)>();
    test_is_not_floating_point<void (Class::*)(int, ...)&>();
    test_is_not_floating_point<void (Class::*)(int, ...) &&>();
    test_is_not_floating_point<void (Class::*)(int, ...) const>();
    test_is_not_floating_point<void (Class::*)(int, ...) const&>();
    test_is_not_floating_point<void (Class::*)(int, ...) const&&>();
    test_is_not_floating_point<void (Class::*)(int, ...) noexcept>();
    test_is_not_floating_point<void (Class::*)(int, ...)& noexcept>();
    test_is_not_floating_point<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_floating_point<void (Class::*)(int, ...) const noexcept>();
    test_is_not_floating_point<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_floating_point<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_floating_point<int (Class::*)()>();
    test_is_not_floating_point<int (Class::*)()&>();
    test_is_not_floating_point<int (Class::*)() &&>();
    test_is_not_floating_point<int (Class::*)() const>();
    test_is_not_floating_point<int (Class::*)() const&>();
    test_is_not_floating_point<int (Class::*)() const&&>();
    test_is_not_floating_point<int (Class::*)() noexcept>();
    test_is_not_floating_point<int (Class::*)()& noexcept>();
    test_is_not_floating_point<int (Class::*)()&& noexcept>();
    test_is_not_floating_point<int (Class::*)() const noexcept>();
    test_is_not_floating_point<int (Class::*)() const& noexcept>();
    test_is_not_floating_point<int (Class::*)() const&& noexcept>();

    test_is_not_floating_point<int (Class::*)(int)>();
    test_is_not_floating_point<int (Class::*)(int)&>();
    test_is_not_floating_point<int (Class::*)(int) &&>();
    test_is_not_floating_point<int (Class::*)(int) const>();
    test_is_not_floating_point<int (Class::*)(int) const&>();
    test_is_not_floating_point<int (Class::*)(int) const&&>();
    test_is_not_floating_point<int (Class::*)(int) noexcept>();
    test_is_not_floating_point<int (Class::*)(int)& noexcept>();
    test_is_not_floating_point<int (Class::*)(int)&& noexcept>();
    test_is_not_floating_point<int (Class::*)(int) const noexcept>();
    test_is_not_floating_point<int (Class::*)(int) const& noexcept>();
    test_is_not_floating_point<int (Class::*)(int) const&& noexcept>();

    test_is_not_floating_point<int (Class::*)(...)>();
    test_is_not_floating_point<int (Class::*)(...)&>();
    test_is_not_floating_point<int (Class::*)(...) &&>();
    test_is_not_floating_point<int (Class::*)(...) const>();
    test_is_not_floating_point<int (Class::*)(...) const&>();
    test_is_not_floating_point<int (Class::*)(...) const&&>();
    test_is_not_floating_point<int (Class::*)(...) noexcept>();
    test_is_not_floating_point<int (Class::*)(...)& noexcept>();
    test_is_not_floating_point<int (Class::*)(...)&& noexcept>();
    test_is_not_floating_point<int (Class::*)(...) const noexcept>();
    test_is_not_floating_point<int (Class::*)(...) const& noexcept>();
    test_is_not_floating_point<int (Class::*)(...) const&& noexcept>();

    test_is_not_floating_point<int (Class::*)(int, ...)>();
    test_is_not_floating_point<int (Class::*)(int, ...)&>();
    test_is_not_floating_point<int (Class::*)(int, ...) &&>();
    test_is_not_floating_point<int (Class::*)(int, ...) const>();
    test_is_not_floating_point<int (Class::*)(int, ...) const&>();
    test_is_not_floating_point<int (Class::*)(int, ...) const&&>();
    test_is_not_floating_point<int (Class::*)(int, ...) noexcept>();
    test_is_not_floating_point<int (Class::*)(int, ...)& noexcept>();
    test_is_not_floating_point<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_floating_point<int (Class::*)(int, ...) const noexcept>();
    test_is_not_floating_point<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_floating_point<int (Class::*)(int, ...) const&& noexcept>();
}
