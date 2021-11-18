#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/has_virtual_destructor.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_has_virtual_destructor_impl()
{
    STATIC_REQUIRE(phi::has_virtual_destructor<T>::value);
    STATIC_REQUIRE_FALSE(phi::has_no_virtual_destructor<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::has_virtual_destructor_v<T>);
    STATIC_REQUIRE_FALSE(phi::has_no_virtual_destructor_v<T>);
#endif

    // Standard compatibility
    STATIC_REQUIRE(std::has_virtual_destructor<T>::value);
}

template <typename T>
void test_has_virtual_destructor()
{
    test_has_virtual_destructor_impl<T>();
    test_has_virtual_destructor_impl<const T>();
    test_has_virtual_destructor_impl<volatile T>();
    test_has_virtual_destructor_impl<const volatile T>();
}

template <typename T>
void test_has_no_virtual_destructor_impl()
{
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor<T>::value);
    STATIC_REQUIRE(phi::has_no_virtual_destructor<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor_v<T>);
    STATIC_REQUIRE(phi::has_no_virtual_destructor_v<T>);
#endif

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::has_virtual_destructor<T>::value);
}

template <typename T>
void test_has_no_virtual_destructor()
{
    test_has_no_virtual_destructor_impl<T>();
    test_has_no_virtual_destructor_impl<const T>();
    test_has_no_virtual_destructor_impl<volatile T>();
    test_has_no_virtual_destructor_impl<const volatile T>();
}

struct A
{
    ~A();
};

TEST_CASE("has_virtual_destructor")
{
    test_has_no_virtual_destructor<void>();
    test_has_no_virtual_destructor<phi::nullptr_t>();
    test_has_no_virtual_destructor<bool>();
    test_has_no_virtual_destructor<char>();
    test_has_no_virtual_destructor<signed char>();
    test_has_no_virtual_destructor<unsigned char>();
    test_has_no_virtual_destructor<short>();
    test_has_no_virtual_destructor<unsigned short>();
    test_has_no_virtual_destructor<int>();
    test_has_no_virtual_destructor<unsigned int>();
    test_has_no_virtual_destructor<long>();
    test_has_no_virtual_destructor<unsigned long>();
    test_has_no_virtual_destructor<long long>();
    test_has_no_virtual_destructor<unsigned long long>();
    test_has_no_virtual_destructor<float>();
    test_has_no_virtual_destructor<double>();
    test_has_no_virtual_destructor<long double>();
    test_has_no_virtual_destructor<char8_t>();
    test_has_no_virtual_destructor<char16_t>();
    test_has_no_virtual_destructor<char32_t>();
    test_has_no_virtual_destructor<wchar_t>();

    test_has_no_virtual_destructor<phi::Boolean>();
    test_has_no_virtual_destructor<phi::Integer<signed char>>();
    test_has_no_virtual_destructor<phi::Integer<unsigned char>>();
    test_has_no_virtual_destructor<phi::Integer<short>>();
    test_has_no_virtual_destructor<phi::Integer<unsigned short>>();
    test_has_no_virtual_destructor<phi::Integer<int>>();
    test_has_no_virtual_destructor<phi::Integer<unsigned int>>();
    test_has_no_virtual_destructor<phi::Integer<long>>();
    test_has_no_virtual_destructor<phi::Integer<unsigned long>>();
    test_has_no_virtual_destructor<phi::Integer<long long>>();
    test_has_no_virtual_destructor<phi::Integer<unsigned long long>>();
    test_has_no_virtual_destructor<phi::FloatingPoint<float>>();
    test_has_no_virtual_destructor<phi::FloatingPoint<double>>();
    test_has_no_virtual_destructor<phi::FloatingPoint<long double>>();

    test_has_no_virtual_destructor<std::vector<int>>();
    test_has_no_virtual_destructor<phi::ScopePtr<int>>();

    test_has_no_virtual_destructor<int&>();
    test_has_no_virtual_destructor<const int&>();
    test_has_no_virtual_destructor<volatile int&>();
    test_has_no_virtual_destructor<const volatile int&>();
    test_has_no_virtual_destructor<int&&>();
    test_has_no_virtual_destructor<const int&&>();
    test_has_no_virtual_destructor<volatile int&&>();
    test_has_no_virtual_destructor<const volatile int&&>();
    test_has_no_virtual_destructor<int*>();
    test_has_no_virtual_destructor<const int*>();
    test_has_no_virtual_destructor<volatile int*>();
    test_has_no_virtual_destructor<const volatile int*>();
    test_has_no_virtual_destructor<int**>();
    test_has_no_virtual_destructor<const int**>();
    test_has_no_virtual_destructor<volatile int**>();
    test_has_no_virtual_destructor<const volatile int**>();
    test_has_no_virtual_destructor<int*&>();
    test_has_no_virtual_destructor<const int*&>();
    test_has_no_virtual_destructor<volatile int*&>();
    test_has_no_virtual_destructor<const volatile int*&>();
    test_has_no_virtual_destructor<int*&&>();
    test_has_no_virtual_destructor<const int*&&>();
    test_has_no_virtual_destructor<volatile int*&&>();
    test_has_no_virtual_destructor<const volatile int*&&>();
    test_has_no_virtual_destructor<void*>();
    test_has_no_virtual_destructor<char[3]>();
    test_has_no_virtual_destructor<char[]>();
    test_has_no_virtual_destructor<char[3]>();
    test_has_no_virtual_destructor<char[]>();
    test_has_no_virtual_destructor<char* [3]>();
    test_has_no_virtual_destructor<char*[]>();
    test_has_no_virtual_destructor<int(*)[3]>();
    test_has_no_virtual_destructor<int(*)[]>();
    test_has_no_virtual_destructor<int(&)[3]>();
    test_has_no_virtual_destructor<int(&)[]>();
    test_has_no_virtual_destructor<int(&&)[3]>();
    test_has_no_virtual_destructor<int(&&)[]>();
    test_has_no_virtual_destructor<char[3][2]>();
    test_has_no_virtual_destructor<char[][2]>();
    test_has_no_virtual_destructor<char* [3][2]>();
    test_has_no_virtual_destructor<char*[][2]>();
    test_has_no_virtual_destructor<int(*)[3][2]>();
    test_has_no_virtual_destructor<int(*)[][2]>();
    test_has_no_virtual_destructor<int(&)[3][2]>();
    test_has_no_virtual_destructor<int(&)[][2]>();
    test_has_no_virtual_destructor<int(&&)[3][2]>();
    test_has_no_virtual_destructor<int(&&)[][2]>();
    test_has_no_virtual_destructor<Class>();
    test_has_no_virtual_destructor<Class[]>();
    test_has_no_virtual_destructor<Class[2]>();
    test_has_no_virtual_destructor<Template<void>>();
    test_has_no_virtual_destructor<Template<int>>();
    test_has_no_virtual_destructor<Template<Class>>();
    test_has_no_virtual_destructor<Template<incomplete_type>>();
    test_has_no_virtual_destructor<VariadicTemplate<>>();
    test_has_no_virtual_destructor<VariadicTemplate<void>>();
    test_has_no_virtual_destructor<VariadicTemplate<int>>();
    test_has_no_virtual_destructor<VariadicTemplate<Class>>();
    test_has_no_virtual_destructor<VariadicTemplate<incomplete_type>>();
    test_has_no_virtual_destructor<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_has_no_virtual_destructor<PublicDerviedFromTemplate<Base>>();
    test_has_no_virtual_destructor<PublicDerviedFromTemplate<Derived>>();
    test_has_no_virtual_destructor<PublicDerviedFromTemplate<Class>>();
    test_has_no_virtual_destructor<PrivateDerviedFromTemplate<Base>>();
    test_has_no_virtual_destructor<PrivateDerviedFromTemplate<Derived>>();
    test_has_no_virtual_destructor<PrivateDerviedFromTemplate<Class>>();
    test_has_no_virtual_destructor<ProtectedDerviedFromTemplate<Base>>();
    test_has_no_virtual_destructor<ProtectedDerviedFromTemplate<Derived>>();
    test_has_no_virtual_destructor<ProtectedDerviedFromTemplate<Class>>();
    test_has_no_virtual_destructor<Union>();
    test_has_no_virtual_destructor<NonEmptyUnion>();
    test_has_no_virtual_destructor<Empty>();
    test_has_virtual_destructor<NotEmpty>();
    test_has_no_virtual_destructor<bit_zero>();
    test_has_no_virtual_destructor<bit_one>();
    test_has_no_virtual_destructor<Base>();
    test_has_no_virtual_destructor<Derived>();
    test_has_virtual_destructor<Abstract>();
    test_has_virtual_destructor<PublicAbstract>();
    test_has_virtual_destructor<PrivateAbstract>();
    test_has_virtual_destructor<ProtectedAbstract>();
    test_has_virtual_destructor<AbstractTemplate<int>>();
    test_has_no_virtual_destructor<AbstractTemplate<double>>();
    test_has_virtual_destructor<AbstractTemplate<Class>>();
    test_has_virtual_destructor<AbstractTemplate<incomplete_type>>();
    test_has_no_virtual_destructor<Final>();
    test_has_no_virtual_destructor<PublicDestructor>();
    test_has_no_virtual_destructor<ProtectedDestructor>();
    test_has_no_virtual_destructor<PrivateDestructor>();
    test_has_virtual_destructor<VirtualPublicDestructor>();
    test_has_virtual_destructor<VirtualProtectedDestructor>();
    test_has_virtual_destructor<VirtualPrivateDestructor>();
    test_has_virtual_destructor<PurePublicDestructor>();
    test_has_virtual_destructor<PureProtectedDestructor>();
    test_has_virtual_destructor<PurePrivateDestructor>();
    test_has_no_virtual_destructor<DeletedPublicDestructor>();
    test_has_no_virtual_destructor<DeletedProtectedDestructor>();
    test_has_no_virtual_destructor<DeletedPrivateDestructor>();
    test_has_virtual_destructor<DeletedVirtualPublicDestructor>();
    test_has_virtual_destructor<DeletedVirtualProtectedDestructor>();
    test_has_virtual_destructor<DeletedVirtualPrivateDestructor>();
    test_has_no_virtual_destructor<Enum>();
    test_has_no_virtual_destructor<EnumSigned>();
    test_has_no_virtual_destructor<EnumUnsigned>();
    test_has_no_virtual_destructor<EnumClass>();
    test_has_no_virtual_destructor<EnumStruct>();
    test_has_no_virtual_destructor<Function>();
    test_has_no_virtual_destructor<FunctionPtr>();
    test_has_no_virtual_destructor<MemberObjectPtr>();
    test_has_no_virtual_destructor<MemberFunctionPtr>();
    test_has_no_virtual_destructor<int Class::*>();
    test_has_no_virtual_destructor<float Class::*>();
    test_has_no_virtual_destructor<void * Class::*>();
    test_has_no_virtual_destructor<int * Class::*>();
    test_has_no_virtual_destructor<int Class::*&>();
    test_has_no_virtual_destructor<float Class::*&>();
    test_has_no_virtual_destructor<void * Class::*&>();
    test_has_no_virtual_destructor<int * Class::*&>();
    test_has_no_virtual_destructor<int Class::*&&>();
    test_has_no_virtual_destructor<float Class::*&&>();
    test_has_no_virtual_destructor<void * Class::*&&>();
    test_has_no_virtual_destructor<int * Class::*&&>();
    test_has_no_virtual_destructor<int Class::*const>();
    test_has_no_virtual_destructor<float Class::*const>();
    test_has_no_virtual_destructor<void * Class::*const>();
    test_has_no_virtual_destructor<int Class::*const&>();
    test_has_no_virtual_destructor<float Class::*const&>();
    test_has_no_virtual_destructor<void * Class::*const&>();
    test_has_no_virtual_destructor<int Class::*const&&>();
    test_has_no_virtual_destructor<float Class::*const&&>();
    test_has_no_virtual_destructor<void * Class::*const&&>();
    test_has_no_virtual_destructor<int Class::*volatile>();
    test_has_no_virtual_destructor<float Class::*volatile>();
    test_has_no_virtual_destructor<void * Class::*volatile>();
    test_has_no_virtual_destructor<int Class::*volatile&>();
    test_has_no_virtual_destructor<float Class::*volatile&>();
    test_has_no_virtual_destructor<void * Class::*volatile&>();
    test_has_no_virtual_destructor<int Class::*volatile&&>();
    test_has_no_virtual_destructor<float Class::*volatile&&>();
    test_has_no_virtual_destructor<void * Class::*volatile&&>();
    test_has_no_virtual_destructor<int Class::*const volatile>();
    test_has_no_virtual_destructor<float Class::*const volatile>();
    test_has_no_virtual_destructor<void * Class::*const volatile>();
    test_has_no_virtual_destructor<int Class::*const volatile&>();
    test_has_no_virtual_destructor<float Class::*const volatile&>();
    test_has_no_virtual_destructor<void * Class::*const volatile&>();
    test_has_no_virtual_destructor<int Class::*const volatile&&>();
    test_has_no_virtual_destructor<float Class::*const volatile&&>();
    test_has_no_virtual_destructor<void * Class::*const volatile&&>();
    test_has_no_virtual_destructor<NonCopyable>();
    test_has_no_virtual_destructor<NonMoveable>();
    test_has_no_virtual_destructor<NonConstructible>();
    test_has_no_virtual_destructor<Tracked>();
    test_has_no_virtual_destructor<TrapConstructible>();
    test_has_no_virtual_destructor<TrapImplicitConversion>();
    test_has_no_virtual_destructor<TrapComma>();
    test_has_no_virtual_destructor<TrapCall>();
    test_has_no_virtual_destructor<TrapSelfAssign>();
    test_has_no_virtual_destructor<TrapDeref>();
    test_has_no_virtual_destructor<TrapArraySubscript>();

    test_has_no_virtual_destructor<void()>();
    test_has_no_virtual_destructor<void()&>();
    test_has_no_virtual_destructor<void() &&>();
    test_has_no_virtual_destructor<void() const>();
    test_has_no_virtual_destructor<void() const&>();
    test_has_no_virtual_destructor<void() const&&>();
    test_has_no_virtual_destructor<void() volatile>();
    test_has_no_virtual_destructor<void() volatile&>();
    test_has_no_virtual_destructor<void() volatile&&>();
    test_has_no_virtual_destructor<void() const volatile>();
    test_has_no_virtual_destructor<void() const volatile&>();
    test_has_no_virtual_destructor<void() const volatile&&>();
    test_has_no_virtual_destructor<void() noexcept>();
    test_has_no_virtual_destructor<void()& noexcept>();
    test_has_no_virtual_destructor<void()&& noexcept>();
    test_has_no_virtual_destructor<void() const noexcept>();
    test_has_no_virtual_destructor<void() const& noexcept>();
    test_has_no_virtual_destructor<void() const&& noexcept>();
    test_has_no_virtual_destructor<void() volatile noexcept>();
    test_has_no_virtual_destructor<void() volatile& noexcept>();
    test_has_no_virtual_destructor<void() volatile&& noexcept>();
    test_has_no_virtual_destructor<void() const volatile noexcept>();
    test_has_no_virtual_destructor<void() const volatile& noexcept>();
    test_has_no_virtual_destructor<void() const volatile&& noexcept>();

    test_has_no_virtual_destructor<void(int)>();
    test_has_no_virtual_destructor<void(int)&>();
    test_has_no_virtual_destructor<void(int) &&>();
    test_has_no_virtual_destructor<void(int) const>();
    test_has_no_virtual_destructor<void(int) const&>();
    test_has_no_virtual_destructor<void(int) const&&>();
    test_has_no_virtual_destructor<void(int) volatile>();
    test_has_no_virtual_destructor<void(int) volatile&>();
    test_has_no_virtual_destructor<void(int) volatile&&>();
    test_has_no_virtual_destructor<void(int) const volatile>();
    test_has_no_virtual_destructor<void(int) const volatile&>();
    test_has_no_virtual_destructor<void(int) const volatile&&>();
    test_has_no_virtual_destructor<void(int) noexcept>();
    test_has_no_virtual_destructor<void(int)& noexcept>();
    test_has_no_virtual_destructor<void(int)&& noexcept>();
    test_has_no_virtual_destructor<void(int) const noexcept>();
    test_has_no_virtual_destructor<void(int) const& noexcept>();
    test_has_no_virtual_destructor<void(int) const&& noexcept>();
    test_has_no_virtual_destructor<void(int) volatile noexcept>();
    test_has_no_virtual_destructor<void(int) volatile& noexcept>();
    test_has_no_virtual_destructor<void(int) volatile&& noexcept>();
    test_has_no_virtual_destructor<void(int) const volatile noexcept>();
    test_has_no_virtual_destructor<void(int) const volatile& noexcept>();
    test_has_no_virtual_destructor<void(int) const volatile&& noexcept>();

    test_has_no_virtual_destructor<void(...)>();
    test_has_no_virtual_destructor<void(...)&>();
    test_has_no_virtual_destructor<void(...) &&>();
    test_has_no_virtual_destructor<void(...) const>();
    test_has_no_virtual_destructor<void(...) const&>();
    test_has_no_virtual_destructor<void(...) const&&>();
    test_has_no_virtual_destructor<void(...) volatile>();
    test_has_no_virtual_destructor<void(...) volatile&>();
    test_has_no_virtual_destructor<void(...) volatile&&>();
    test_has_no_virtual_destructor<void(...) const volatile>();
    test_has_no_virtual_destructor<void(...) const volatile&>();
    test_has_no_virtual_destructor<void(...) const volatile&&>();
    test_has_no_virtual_destructor<void(...) noexcept>();
    test_has_no_virtual_destructor<void(...)& noexcept>();
    test_has_no_virtual_destructor<void(...)&& noexcept>();
    test_has_no_virtual_destructor<void(...) const noexcept>();
    test_has_no_virtual_destructor<void(...) const& noexcept>();
    test_has_no_virtual_destructor<void(...) const&& noexcept>();
    test_has_no_virtual_destructor<void(...) volatile noexcept>();
    test_has_no_virtual_destructor<void(...) volatile& noexcept>();
    test_has_no_virtual_destructor<void(...) volatile&& noexcept>();
    test_has_no_virtual_destructor<void(...) const volatile noexcept>();
    test_has_no_virtual_destructor<void(...) const volatile& noexcept>();
    test_has_no_virtual_destructor<void(...) const volatile&& noexcept>();

    test_has_no_virtual_destructor<void(int, ...)>();
    test_has_no_virtual_destructor<void(int, ...)&>();
    test_has_no_virtual_destructor<void(int, ...) &&>();
    test_has_no_virtual_destructor<void(int, ...) const>();
    test_has_no_virtual_destructor<void(int, ...) const&>();
    test_has_no_virtual_destructor<void(int, ...) const&&>();
    test_has_no_virtual_destructor<void(int, ...) volatile>();
    test_has_no_virtual_destructor<void(int, ...) volatile&>();
    test_has_no_virtual_destructor<void(int, ...) volatile&&>();
    test_has_no_virtual_destructor<void(int, ...) const volatile>();
    test_has_no_virtual_destructor<void(int, ...) const volatile&>();
    test_has_no_virtual_destructor<void(int, ...) const volatile&&>();
    test_has_no_virtual_destructor<void(int, ...) noexcept>();
    test_has_no_virtual_destructor<void(int, ...)& noexcept>();
    test_has_no_virtual_destructor<void(int, ...)&& noexcept>();
    test_has_no_virtual_destructor<void(int, ...) const noexcept>();
    test_has_no_virtual_destructor<void(int, ...) const& noexcept>();
    test_has_no_virtual_destructor<void(int, ...) const&& noexcept>();
    test_has_no_virtual_destructor<void(int, ...) volatile noexcept>();
    test_has_no_virtual_destructor<void(int, ...) volatile& noexcept>();
    test_has_no_virtual_destructor<void(int, ...) volatile&& noexcept>();
    test_has_no_virtual_destructor<void(int, ...) const volatile noexcept>();
    test_has_no_virtual_destructor<void(int, ...) const volatile& noexcept>();
    test_has_no_virtual_destructor<void(int, ...) const volatile&& noexcept>();

    test_has_no_virtual_destructor<int()>();
    test_has_no_virtual_destructor<int()&>();
    test_has_no_virtual_destructor<int() &&>();
    test_has_no_virtual_destructor<int() const>();
    test_has_no_virtual_destructor<int() const&>();
    test_has_no_virtual_destructor<int() const&&>();
    test_has_no_virtual_destructor<int() volatile>();
    test_has_no_virtual_destructor<int() volatile&>();
    test_has_no_virtual_destructor<int() volatile&&>();
    test_has_no_virtual_destructor<int() const volatile>();
    test_has_no_virtual_destructor<int() const volatile&>();
    test_has_no_virtual_destructor<int() const volatile&&>();
    test_has_no_virtual_destructor<int() noexcept>();
    test_has_no_virtual_destructor<int()& noexcept>();
    test_has_no_virtual_destructor<int()&& noexcept>();
    test_has_no_virtual_destructor<int() const noexcept>();
    test_has_no_virtual_destructor<int() const& noexcept>();
    test_has_no_virtual_destructor<int() const&& noexcept>();
    test_has_no_virtual_destructor<int() volatile noexcept>();
    test_has_no_virtual_destructor<int() volatile& noexcept>();
    test_has_no_virtual_destructor<int() volatile&& noexcept>();
    test_has_no_virtual_destructor<int() const volatile noexcept>();
    test_has_no_virtual_destructor<int() const volatile& noexcept>();
    test_has_no_virtual_destructor<int() const volatile&& noexcept>();

    test_has_no_virtual_destructor<int(int)>();
    test_has_no_virtual_destructor<int(int)&>();
    test_has_no_virtual_destructor<int(int) &&>();
    test_has_no_virtual_destructor<int(int) const>();
    test_has_no_virtual_destructor<int(int) const&>();
    test_has_no_virtual_destructor<int(int) const&&>();
    test_has_no_virtual_destructor<int(int) volatile>();
    test_has_no_virtual_destructor<int(int) volatile&>();
    test_has_no_virtual_destructor<int(int) volatile&&>();
    test_has_no_virtual_destructor<int(int) const volatile>();
    test_has_no_virtual_destructor<int(int) const volatile&>();
    test_has_no_virtual_destructor<int(int) const volatile&&>();
    test_has_no_virtual_destructor<int(int) noexcept>();
    test_has_no_virtual_destructor<int(int)& noexcept>();
    test_has_no_virtual_destructor<int(int)&& noexcept>();
    test_has_no_virtual_destructor<int(int) const noexcept>();
    test_has_no_virtual_destructor<int(int) const& noexcept>();
    test_has_no_virtual_destructor<int(int) const&& noexcept>();
    test_has_no_virtual_destructor<int(int) volatile noexcept>();
    test_has_no_virtual_destructor<int(int) volatile& noexcept>();
    test_has_no_virtual_destructor<int(int) volatile&& noexcept>();
    test_has_no_virtual_destructor<int(int) const volatile noexcept>();
    test_has_no_virtual_destructor<int(int) const volatile& noexcept>();
    test_has_no_virtual_destructor<int(int) const volatile&& noexcept>();

    test_has_no_virtual_destructor<int(...)>();
    test_has_no_virtual_destructor<int(...)&>();
    test_has_no_virtual_destructor<int(...) &&>();
    test_has_no_virtual_destructor<int(...) const>();
    test_has_no_virtual_destructor<int(...) const&>();
    test_has_no_virtual_destructor<int(...) const&&>();
    test_has_no_virtual_destructor<int(...) volatile>();
    test_has_no_virtual_destructor<int(...) volatile&>();
    test_has_no_virtual_destructor<int(...) volatile&&>();
    test_has_no_virtual_destructor<int(...) const volatile>();
    test_has_no_virtual_destructor<int(...) const volatile&>();
    test_has_no_virtual_destructor<int(...) const volatile&&>();
    test_has_no_virtual_destructor<int(...) noexcept>();
    test_has_no_virtual_destructor<int(...)& noexcept>();
    test_has_no_virtual_destructor<int(...)&& noexcept>();
    test_has_no_virtual_destructor<int(...) const noexcept>();
    test_has_no_virtual_destructor<int(...) const& noexcept>();
    test_has_no_virtual_destructor<int(...) const&& noexcept>();
    test_has_no_virtual_destructor<int(...) volatile noexcept>();
    test_has_no_virtual_destructor<int(...) volatile& noexcept>();
    test_has_no_virtual_destructor<int(...) volatile&& noexcept>();
    test_has_no_virtual_destructor<int(...) const volatile noexcept>();
    test_has_no_virtual_destructor<int(...) const volatile& noexcept>();
    test_has_no_virtual_destructor<int(...) const volatile&& noexcept>();

    test_has_no_virtual_destructor<int(int, ...)>();
    test_has_no_virtual_destructor<int(int, ...)&>();
    test_has_no_virtual_destructor<int(int, ...) &&>();
    test_has_no_virtual_destructor<int(int, ...) const>();
    test_has_no_virtual_destructor<int(int, ...) const&>();
    test_has_no_virtual_destructor<int(int, ...) const&&>();
    test_has_no_virtual_destructor<int(int, ...) volatile>();
    test_has_no_virtual_destructor<int(int, ...) volatile&>();
    test_has_no_virtual_destructor<int(int, ...) volatile&&>();
    test_has_no_virtual_destructor<int(int, ...) const volatile>();
    test_has_no_virtual_destructor<int(int, ...) const volatile&>();
    test_has_no_virtual_destructor<int(int, ...) const volatile&&>();
    test_has_no_virtual_destructor<int(int, ...) noexcept>();
    test_has_no_virtual_destructor<int(int, ...)& noexcept>();
    test_has_no_virtual_destructor<int(int, ...)&& noexcept>();
    test_has_no_virtual_destructor<int(int, ...) const noexcept>();
    test_has_no_virtual_destructor<int(int, ...) const& noexcept>();
    test_has_no_virtual_destructor<int(int, ...) const&& noexcept>();
    test_has_no_virtual_destructor<int(int, ...) volatile noexcept>();
    test_has_no_virtual_destructor<int(int, ...) volatile& noexcept>();
    test_has_no_virtual_destructor<int(int, ...) volatile&& noexcept>();
    test_has_no_virtual_destructor<int(int, ...) const volatile noexcept>();
    test_has_no_virtual_destructor<int(int, ...) const volatile& noexcept>();
    test_has_no_virtual_destructor<int(int, ...) const volatile&& noexcept>();

    test_has_no_virtual_destructor<void (*)()>();
    test_has_no_virtual_destructor<void (*)() noexcept>();

    test_has_no_virtual_destructor<void (*)(int)>();
    test_has_no_virtual_destructor<void (*)(int) noexcept>();

    test_has_no_virtual_destructor<void (*)(...)>();
    test_has_no_virtual_destructor<void (*)(...) noexcept>();

    test_has_no_virtual_destructor<void (*)(int, ...)>();
    test_has_no_virtual_destructor<void (*)(int, ...) noexcept>();

    test_has_no_virtual_destructor<int (*)()>();
    test_has_no_virtual_destructor<int (*)() noexcept>();

    test_has_no_virtual_destructor<int (*)(int)>();
    test_has_no_virtual_destructor<int (*)(int) noexcept>();

    test_has_no_virtual_destructor<int (*)(...)>();
    test_has_no_virtual_destructor<int (*)(...) noexcept>();

    test_has_no_virtual_destructor<int (*)(int, ...)>();
    test_has_no_virtual_destructor<int (*)(int, ...) noexcept>();

    test_has_no_virtual_destructor<void (&)()>();
    test_has_no_virtual_destructor<void (&)() noexcept>();

    test_has_no_virtual_destructor<void (&)(int)>();
    test_has_no_virtual_destructor<void (&)(int) noexcept>();

    test_has_no_virtual_destructor<void (&)(...)>();
    test_has_no_virtual_destructor<void (&)(...) noexcept>();

    test_has_no_virtual_destructor<void (&)(int, ...)>();
    test_has_no_virtual_destructor<void (&)(int, ...) noexcept>();

    test_has_no_virtual_destructor<int (&)()>();
    test_has_no_virtual_destructor<int (&)() noexcept>();

    test_has_no_virtual_destructor<int (&)(int)>();
    test_has_no_virtual_destructor<int (&)(int) noexcept>();

    test_has_no_virtual_destructor<int (&)(...)>();
    test_has_no_virtual_destructor<int (&)(...) noexcept>();

    test_has_no_virtual_destructor<int (&)(int, ...)>();
    test_has_no_virtual_destructor<int (&)(int, ...) noexcept>();

    test_has_no_virtual_destructor<void(&&)()>();
    test_has_no_virtual_destructor<void(&&)() noexcept>();

    test_has_no_virtual_destructor<void(&&)(int)>();
    test_has_no_virtual_destructor<void(&&)(int) noexcept>();

    test_has_no_virtual_destructor<void(&&)(...)>();
    test_has_no_virtual_destructor<void(&&)(...) noexcept>();

    test_has_no_virtual_destructor<void(&&)(int, ...)>();
    test_has_no_virtual_destructor<void(&&)(int, ...) noexcept>();

    test_has_no_virtual_destructor<int(&&)()>();
    test_has_no_virtual_destructor<int(&&)() noexcept>();

    test_has_no_virtual_destructor<int(&&)(int)>();
    test_has_no_virtual_destructor<int(&&)(int) noexcept>();

    test_has_no_virtual_destructor<int(&&)(...)>();
    test_has_no_virtual_destructor<int(&&)(...) noexcept>();

    test_has_no_virtual_destructor<int(&&)(int, ...)>();
    test_has_no_virtual_destructor<int(&&)(int, ...) noexcept>();

    test_has_no_virtual_destructor<void (Class::*)()>();
    test_has_no_virtual_destructor<void (Class::*)()&>();
    test_has_no_virtual_destructor<void (Class::*)() &&>();
    test_has_no_virtual_destructor<void (Class::*)() const>();
    test_has_no_virtual_destructor<void (Class::*)() const&>();
    test_has_no_virtual_destructor<void (Class::*)() const&&>();
    test_has_no_virtual_destructor<void (Class::*)() noexcept>();
    test_has_no_virtual_destructor<void (Class::*)()& noexcept>();
    test_has_no_virtual_destructor<void (Class::*)()&& noexcept>();
    test_has_no_virtual_destructor<void (Class::*)() const noexcept>();
    test_has_no_virtual_destructor<void (Class::*)() const& noexcept>();
    test_has_no_virtual_destructor<void (Class::*)() const&& noexcept>();

    test_has_no_virtual_destructor<void (Class::*)(int)>();
    test_has_no_virtual_destructor<void (Class::*)(int)&>();
    test_has_no_virtual_destructor<void (Class::*)(int) &&>();
    test_has_no_virtual_destructor<void (Class::*)(int) const>();
    test_has_no_virtual_destructor<void (Class::*)(int) const&>();
    test_has_no_virtual_destructor<void (Class::*)(int) const&&>();
    test_has_no_virtual_destructor<void (Class::*)(int) noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(int)& noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(int)&& noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(int) const noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(int) const& noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(int) const&& noexcept>();

    test_has_no_virtual_destructor<void (Class::*)(...)>();
    test_has_no_virtual_destructor<void (Class::*)(...)&>();
    test_has_no_virtual_destructor<void (Class::*)(...) &&>();
    test_has_no_virtual_destructor<void (Class::*)(...) const>();
    test_has_no_virtual_destructor<void (Class::*)(...) const&>();
    test_has_no_virtual_destructor<void (Class::*)(...) const&&>();
    test_has_no_virtual_destructor<void (Class::*)(...) noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(...)& noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(...)&& noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(...) const noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(...) const& noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(...) const&& noexcept>();

    test_has_no_virtual_destructor<void (Class::*)(int, ...)>();
    test_has_no_virtual_destructor<void (Class::*)(int, ...)&>();
    test_has_no_virtual_destructor<void (Class::*)(int, ...) &&>();
    test_has_no_virtual_destructor<void (Class::*)(int, ...) const>();
    test_has_no_virtual_destructor<void (Class::*)(int, ...) const&>();
    test_has_no_virtual_destructor<void (Class::*)(int, ...) const&&>();
    test_has_no_virtual_destructor<void (Class::*)(int, ...) noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(int, ...)& noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(int, ...)&& noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(int, ...) const noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(int, ...) const& noexcept>();
    test_has_no_virtual_destructor<void (Class::*)(int, ...) const&& noexcept>();

    test_has_no_virtual_destructor<int (Class::*)()>();
    test_has_no_virtual_destructor<int (Class::*)()&>();
    test_has_no_virtual_destructor<int (Class::*)() &&>();
    test_has_no_virtual_destructor<int (Class::*)() const>();
    test_has_no_virtual_destructor<int (Class::*)() const&>();
    test_has_no_virtual_destructor<int (Class::*)() const&&>();
    test_has_no_virtual_destructor<int (Class::*)() noexcept>();
    test_has_no_virtual_destructor<int (Class::*)()& noexcept>();
    test_has_no_virtual_destructor<int (Class::*)()&& noexcept>();
    test_has_no_virtual_destructor<int (Class::*)() const noexcept>();
    test_has_no_virtual_destructor<int (Class::*)() const& noexcept>();
    test_has_no_virtual_destructor<int (Class::*)() const&& noexcept>();

    test_has_no_virtual_destructor<int (Class::*)(int)>();
    test_has_no_virtual_destructor<int (Class::*)(int)&>();
    test_has_no_virtual_destructor<int (Class::*)(int) &&>();
    test_has_no_virtual_destructor<int (Class::*)(int) const>();
    test_has_no_virtual_destructor<int (Class::*)(int) const&>();
    test_has_no_virtual_destructor<int (Class::*)(int) const&&>();
    test_has_no_virtual_destructor<int (Class::*)(int) noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(int)& noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(int)&& noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(int) const noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(int) const& noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(int) const&& noexcept>();

    test_has_no_virtual_destructor<int (Class::*)(...)>();
    test_has_no_virtual_destructor<int (Class::*)(...)&>();
    test_has_no_virtual_destructor<int (Class::*)(...) &&>();
    test_has_no_virtual_destructor<int (Class::*)(...) const>();
    test_has_no_virtual_destructor<int (Class::*)(...) const&>();
    test_has_no_virtual_destructor<int (Class::*)(...) const&&>();
    test_has_no_virtual_destructor<int (Class::*)(...) noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(...)& noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(...)&& noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(...) const noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(...) const& noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(...) const&& noexcept>();

    test_has_no_virtual_destructor<int (Class::*)(int, ...)>();
    test_has_no_virtual_destructor<int (Class::*)(int, ...)&>();
    test_has_no_virtual_destructor<int (Class::*)(int, ...) &&>();
    test_has_no_virtual_destructor<int (Class::*)(int, ...) const>();
    test_has_no_virtual_destructor<int (Class::*)(int, ...) const&>();
    test_has_no_virtual_destructor<int (Class::*)(int, ...) const&&>();
    test_has_no_virtual_destructor<int (Class::*)(int, ...) noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(int, ...)& noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(int, ...)&& noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(int, ...) const noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(int, ...) const& noexcept>();
    test_has_no_virtual_destructor<int (Class::*)(int, ...) const&& noexcept>();
}
