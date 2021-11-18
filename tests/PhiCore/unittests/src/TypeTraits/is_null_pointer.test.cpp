#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_empty.hpp>
#include <Phi/TypeTraits/is_null_pointer.hpp>
#include <cstddef> // std::nullptr_t
#include <type_traits>
#include <vector>

template <typename T>
void test_is_null_pointer_impl()
{
    STATIC_REQUIRE(phi::is_null_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_null_pointer<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_null_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_null_pointer_v<T>);
#endif

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(14)
    STATIC_REQUIRE(std::is_null_pointer<T>::value);
#endif
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_null_pointer_v<T>);
#endif
}

template <typename T>
void test_is_null_pointer()
{
    test_is_null_pointer_impl<T>();
    test_is_null_pointer_impl<const T>();
    test_is_null_pointer_impl<volatile T>();
    test_is_null_pointer_impl<const volatile T>();
}

template <typename T>
void test_is_not_null_pointer_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<T>::value);
    STATIC_REQUIRE(phi::is_not_null_pointer<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<T>);
    STATIC_REQUIRE(phi::is_not_null_pointer_v<T>);
#endif

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(14)
    STATIC_REQUIRE_FALSE(std::is_null_pointer<T>::value);
#endif
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_null_pointer_v<T>);
#endif
}

template <typename T>
void test_is_not_null_pointer()
{
    test_is_not_null_pointer_impl<T>();
    test_is_not_null_pointer_impl<const T>();
    test_is_not_null_pointer_impl<volatile T>();
    test_is_not_null_pointer_impl<const volatile T>();
}

TEST_CASE("is_null_pointer")
{
    test_is_null_pointer<phi::nullptr_t>();
    test_is_null_pointer<std::nullptr_t>();
    test_is_null_pointer<decltype(nullptr)>();

    test_is_not_null_pointer<void>();
    test_is_not_null_pointer<bool>();
    test_is_not_null_pointer<char>();
    test_is_not_null_pointer<signed char>();
    test_is_not_null_pointer<unsigned char>();
    test_is_not_null_pointer<short>();
    test_is_not_null_pointer<unsigned short>();
    test_is_not_null_pointer<int>();
    test_is_not_null_pointer<unsigned int>();
    test_is_not_null_pointer<long>();
    test_is_not_null_pointer<unsigned long>();
    test_is_not_null_pointer<long long>();
    test_is_not_null_pointer<unsigned long long>();
    test_is_not_null_pointer<float>();
    test_is_not_null_pointer<double>();
    test_is_not_null_pointer<long double>();
    test_is_not_null_pointer<char8_t>();
    test_is_not_null_pointer<char16_t>();
    test_is_not_null_pointer<char32_t>();
    test_is_not_null_pointer<wchar_t>();

    test_is_not_null_pointer<phi::Boolean>();
    test_is_not_null_pointer<phi::Integer<signed char>>();
    test_is_not_null_pointer<phi::Integer<unsigned char>>();
    test_is_not_null_pointer<phi::Integer<short>>();
    test_is_not_null_pointer<phi::Integer<unsigned short>>();
    test_is_not_null_pointer<phi::Integer<int>>();
    test_is_not_null_pointer<phi::Integer<unsigned int>>();
    test_is_not_null_pointer<phi::Integer<long>>();
    test_is_not_null_pointer<phi::Integer<unsigned long>>();
    test_is_not_null_pointer<phi::Integer<long long>>();
    test_is_not_null_pointer<phi::Integer<unsigned long long>>();
    test_is_not_null_pointer<phi::FloatingPoint<float>>();
    test_is_not_null_pointer<phi::FloatingPoint<double>>();
    test_is_not_null_pointer<phi::FloatingPoint<long double>>();

    test_is_not_null_pointer<std::vector<int>>();
    test_is_not_null_pointer<phi::ScopePtr<int>>();

    test_is_not_null_pointer<int&>();
    test_is_not_null_pointer<const int&>();
    test_is_not_null_pointer<volatile int&>();
    test_is_not_null_pointer<const volatile int&>();
    test_is_not_null_pointer<int&&>();
    test_is_not_null_pointer<const int&&>();
    test_is_not_null_pointer<volatile int&&>();
    test_is_not_null_pointer<const volatile int&&>();
    test_is_not_null_pointer<int*>();
    test_is_not_null_pointer<const int*>();
    test_is_not_null_pointer<volatile int*>();
    test_is_not_null_pointer<const volatile int*>();
    test_is_not_null_pointer<int**>();
    test_is_not_null_pointer<const int**>();
    test_is_not_null_pointer<volatile int**>();
    test_is_not_null_pointer<const volatile int**>();
    test_is_not_null_pointer<int*&>();
    test_is_not_null_pointer<const int*&>();
    test_is_not_null_pointer<volatile int*&>();
    test_is_not_null_pointer<const volatile int*&>();
    test_is_not_null_pointer<int*&&>();
    test_is_not_null_pointer<const int*&&>();
    test_is_not_null_pointer<volatile int*&&>();
    test_is_not_null_pointer<const volatile int*&&>();
    test_is_not_null_pointer<void*>();
    test_is_not_null_pointer<char[3]>();
    test_is_not_null_pointer<char[]>();
    test_is_not_null_pointer<char* [3]>();
    test_is_not_null_pointer<char*[]>();
    test_is_not_null_pointer<int(*)[3]>();
    test_is_not_null_pointer<int(*)[]>();
    test_is_not_null_pointer<int(&)[3]>();
    test_is_not_null_pointer<int(&)[]>();
    test_is_not_null_pointer<int(&&)[3]>();
    test_is_not_null_pointer<int(&&)[]>();
    test_is_not_null_pointer<char[3][2]>();
    test_is_not_null_pointer<char[][2]>();
    test_is_not_null_pointer<char* [3][2]>();
    test_is_not_null_pointer<char*[][2]>();
    test_is_not_null_pointer<int(*)[3][2]>();
    test_is_not_null_pointer<int(*)[][2]>();
    test_is_not_null_pointer<int(&)[3][2]>();
    test_is_not_null_pointer<int(&)[][2]>();
    test_is_not_null_pointer<int(&&)[3][2]>();
    test_is_not_null_pointer<int(&&)[][2]>();
    test_is_not_null_pointer<Class>();
    test_is_not_null_pointer<Class[]>();
    test_is_not_null_pointer<Class[2]>();
    test_is_not_null_pointer<Template<void>>();
    test_is_not_null_pointer<Template<int>>();
    test_is_not_null_pointer<Template<Class>>();
    test_is_not_null_pointer<Template<incomplete_type>>();
    test_is_not_null_pointer<VariadicTemplate<>>();
    test_is_not_null_pointer<VariadicTemplate<void>>();
    test_is_not_null_pointer<VariadicTemplate<int>>();
    test_is_not_null_pointer<VariadicTemplate<Class>>();
    test_is_not_null_pointer<VariadicTemplate<incomplete_type>>();
    test_is_not_null_pointer<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_null_pointer<PublicDerviedFromTemplate<Base>>();
    test_is_not_null_pointer<PublicDerviedFromTemplate<Derived>>();
    test_is_not_null_pointer<PublicDerviedFromTemplate<Class>>();
    test_is_not_null_pointer<PrivateDerviedFromTemplate<Base>>();
    test_is_not_null_pointer<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_null_pointer<PrivateDerviedFromTemplate<Class>>();
    test_is_not_null_pointer<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_null_pointer<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_null_pointer<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_null_pointer<Union>();
    test_is_not_null_pointer<NonEmptyUnion>();
    test_is_not_null_pointer<Empty>();
    test_is_not_null_pointer<NotEmpty>();
    test_is_not_null_pointer<bit_zero>();
    test_is_not_null_pointer<bit_one>();
    test_is_not_null_pointer<Base>();
    test_is_not_null_pointer<Derived>();
    test_is_not_null_pointer<Abstract>();
    test_is_not_null_pointer<PublicAbstract>();
    test_is_not_null_pointer<PrivateAbstract>();
    test_is_not_null_pointer<ProtectedAbstract>();
    test_is_not_null_pointer<AbstractTemplate<int>>();
    test_is_not_null_pointer<AbstractTemplate<double>>();
    test_is_not_null_pointer<AbstractTemplate<Class>>();
    test_is_not_null_pointer<AbstractTemplate<incomplete_type>>();
    test_is_not_null_pointer<Final>();
    test_is_not_null_pointer<PublicDestructor>();
    test_is_not_null_pointer<ProtectedDestructor>();
    test_is_not_null_pointer<PrivateDestructor>();
    test_is_not_null_pointer<VirtualPublicDestructor>();
    test_is_not_null_pointer<VirtualProtectedDestructor>();
    test_is_not_null_pointer<VirtualPrivateDestructor>();
    test_is_not_null_pointer<PurePublicDestructor>();
    test_is_not_null_pointer<PureProtectedDestructor>();
    test_is_not_null_pointer<PurePrivateDestructor>();
    test_is_not_null_pointer<DeletedPublicDestructor>();
    test_is_not_null_pointer<DeletedProtectedDestructor>();
    test_is_not_null_pointer<DeletedPrivateDestructor>();
    test_is_not_null_pointer<DeletedVirtualPublicDestructor>();
    test_is_not_null_pointer<DeletedVirtualProtectedDestructor>();
    test_is_not_null_pointer<DeletedVirtualPrivateDestructor>();
    test_is_not_null_pointer<Final>();
    test_is_not_null_pointer<Enum>();
    test_is_not_null_pointer<EnumSigned>();
    test_is_not_null_pointer<EnumUnsigned>();
    test_is_not_null_pointer<EnumClass>();
    test_is_not_null_pointer<EnumStruct>();
    test_is_not_null_pointer<Function>();
    test_is_not_null_pointer<FunctionPtr>();
    test_is_not_null_pointer<MemberObjectPtr>();
    test_is_not_null_pointer<MemberFunctionPtr>();
    test_is_not_null_pointer<incomplete_type>();
    test_is_not_null_pointer<IncompleteTemplate<void>>();
    test_is_not_null_pointer<IncompleteTemplate<int>>();
    test_is_not_null_pointer<IncompleteTemplate<Class>>();
    test_is_not_null_pointer<IncompleteTemplate<incomplete_type>>();
    test_is_not_null_pointer<IncompleteVariadicTemplate<>>();
    test_is_not_null_pointer<IncompleteVariadicTemplate<void>>();
    test_is_not_null_pointer<IncompleteVariadicTemplate<int>>();
    test_is_not_null_pointer<IncompleteVariadicTemplate<Class>>();
    test_is_not_null_pointer<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_null_pointer<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_null_pointer<int Class::*>();
    test_is_not_null_pointer<float Class::*>();
    test_is_not_null_pointer<void * Class::*>();
    test_is_not_null_pointer<int * Class::*>();
    test_is_not_null_pointer<int Class::*&>();
    test_is_not_null_pointer<float Class::*&>();
    test_is_not_null_pointer<void * Class::*&>();
    test_is_not_null_pointer<int * Class::*&>();
    test_is_not_null_pointer<int Class::*&&>();
    test_is_not_null_pointer<float Class::*&&>();
    test_is_not_null_pointer<void * Class::*&&>();
    test_is_not_null_pointer<int * Class::*&&>();
    test_is_not_null_pointer<int Class::*const>();
    test_is_not_null_pointer<float Class::*const>();
    test_is_not_null_pointer<void * Class::*const>();
    test_is_not_null_pointer<int Class::*const&>();
    test_is_not_null_pointer<float Class::*const&>();
    test_is_not_null_pointer<void * Class::*const&>();
    test_is_not_null_pointer<int Class::*const&&>();
    test_is_not_null_pointer<float Class::*const&&>();
    test_is_not_null_pointer<void * Class::*const&&>();
    test_is_not_null_pointer<int Class::*volatile>();
    test_is_not_null_pointer<float Class::*volatile>();
    test_is_not_null_pointer<void * Class::*volatile>();
    test_is_not_null_pointer<int Class::*volatile&>();
    test_is_not_null_pointer<float Class::*volatile&>();
    test_is_not_null_pointer<void * Class::*volatile&>();
    test_is_not_null_pointer<int Class::*volatile&&>();
    test_is_not_null_pointer<float Class::*volatile&&>();
    test_is_not_null_pointer<void * Class::*volatile&&>();
    test_is_not_null_pointer<int Class::*const volatile>();
    test_is_not_null_pointer<float Class::*const volatile>();
    test_is_not_null_pointer<void * Class::*const volatile>();
    test_is_not_null_pointer<int Class::*const volatile&>();
    test_is_not_null_pointer<float Class::*const volatile&>();
    test_is_not_null_pointer<void * Class::*const volatile&>();
    test_is_not_null_pointer<int Class::*const volatile&&>();
    test_is_not_null_pointer<float Class::*const volatile&&>();
    test_is_not_null_pointer<void * Class::*const volatile&&>();
    test_is_not_null_pointer<NonCopyable>();
    test_is_not_null_pointer<NonMoveable>();
    test_is_not_null_pointer<NonConstructible>();
    test_is_not_null_pointer<Tracked>();
    test_is_not_null_pointer<TrapConstructible>();
    test_is_not_null_pointer<TrapImplicitConversion>();
    test_is_not_null_pointer<TrapComma>();
    test_is_not_null_pointer<TrapCall>();
    test_is_not_null_pointer<TrapSelfAssign>();
    test_is_not_null_pointer<TrapDeref>();
    test_is_not_null_pointer<TrapArraySubscript>();

    test_is_not_null_pointer<void()>();
    test_is_not_null_pointer<void()&>();
    test_is_not_null_pointer<void() &&>();
    test_is_not_null_pointer<void() const>();
    test_is_not_null_pointer<void() const&>();
    test_is_not_null_pointer<void() const&&>();
    test_is_not_null_pointer<void() volatile>();
    test_is_not_null_pointer<void() volatile&>();
    test_is_not_null_pointer<void() volatile&&>();
    test_is_not_null_pointer<void() const volatile>();
    test_is_not_null_pointer<void() const volatile&>();
    test_is_not_null_pointer<void() const volatile&&>();
    test_is_not_null_pointer<void() noexcept>();
    test_is_not_null_pointer<void()& noexcept>();
    test_is_not_null_pointer<void()&& noexcept>();
    test_is_not_null_pointer<void() const noexcept>();
    test_is_not_null_pointer<void() const& noexcept>();
    test_is_not_null_pointer<void() const&& noexcept>();
    test_is_not_null_pointer<void() volatile noexcept>();
    test_is_not_null_pointer<void() volatile& noexcept>();
    test_is_not_null_pointer<void() volatile&& noexcept>();
    test_is_not_null_pointer<void() const volatile noexcept>();
    test_is_not_null_pointer<void() const volatile& noexcept>();
    test_is_not_null_pointer<void() const volatile&& noexcept>();

    test_is_not_null_pointer<void(int)>();
    test_is_not_null_pointer<void(int)&>();
    test_is_not_null_pointer<void(int) &&>();
    test_is_not_null_pointer<void(int) const>();
    test_is_not_null_pointer<void(int) const&>();
    test_is_not_null_pointer<void(int) const&&>();
    test_is_not_null_pointer<void(int) volatile>();
    test_is_not_null_pointer<void(int) volatile&>();
    test_is_not_null_pointer<void(int) volatile&&>();
    test_is_not_null_pointer<void(int) const volatile>();
    test_is_not_null_pointer<void(int) const volatile&>();
    test_is_not_null_pointer<void(int) const volatile&&>();
    test_is_not_null_pointer<void(int) noexcept>();
    test_is_not_null_pointer<void(int)& noexcept>();
    test_is_not_null_pointer<void(int)&& noexcept>();
    test_is_not_null_pointer<void(int) const noexcept>();
    test_is_not_null_pointer<void(int) const& noexcept>();
    test_is_not_null_pointer<void(int) const&& noexcept>();
    test_is_not_null_pointer<void(int) volatile noexcept>();
    test_is_not_null_pointer<void(int) volatile& noexcept>();
    test_is_not_null_pointer<void(int) volatile&& noexcept>();
    test_is_not_null_pointer<void(int) const volatile noexcept>();
    test_is_not_null_pointer<void(int) const volatile& noexcept>();
    test_is_not_null_pointer<void(int) const volatile&& noexcept>();

    test_is_not_null_pointer<void(...)>();
    test_is_not_null_pointer<void(...)&>();
    test_is_not_null_pointer<void(...) &&>();
    test_is_not_null_pointer<void(...) const>();
    test_is_not_null_pointer<void(...) const&>();
    test_is_not_null_pointer<void(...) const&&>();
    test_is_not_null_pointer<void(...) volatile>();
    test_is_not_null_pointer<void(...) volatile&>();
    test_is_not_null_pointer<void(...) volatile&&>();
    test_is_not_null_pointer<void(...) const volatile>();
    test_is_not_null_pointer<void(...) const volatile&>();
    test_is_not_null_pointer<void(...) const volatile&&>();
    test_is_not_null_pointer<void(...) noexcept>();
    test_is_not_null_pointer<void(...)& noexcept>();
    test_is_not_null_pointer<void(...)&& noexcept>();
    test_is_not_null_pointer<void(...) const noexcept>();
    test_is_not_null_pointer<void(...) const& noexcept>();
    test_is_not_null_pointer<void(...) const&& noexcept>();
    test_is_not_null_pointer<void(...) volatile noexcept>();
    test_is_not_null_pointer<void(...) volatile& noexcept>();
    test_is_not_null_pointer<void(...) volatile&& noexcept>();
    test_is_not_null_pointer<void(...) const volatile noexcept>();
    test_is_not_null_pointer<void(...) const volatile& noexcept>();
    test_is_not_null_pointer<void(...) const volatile&& noexcept>();

    test_is_not_null_pointer<void(int, ...)>();
    test_is_not_null_pointer<void(int, ...)&>();
    test_is_not_null_pointer<void(int, ...) &&>();
    test_is_not_null_pointer<void(int, ...) const>();
    test_is_not_null_pointer<void(int, ...) const&>();
    test_is_not_null_pointer<void(int, ...) const&&>();
    test_is_not_null_pointer<void(int, ...) volatile>();
    test_is_not_null_pointer<void(int, ...) volatile&>();
    test_is_not_null_pointer<void(int, ...) volatile&&>();
    test_is_not_null_pointer<void(int, ...) const volatile>();
    test_is_not_null_pointer<void(int, ...) const volatile&>();
    test_is_not_null_pointer<void(int, ...) const volatile&&>();
    test_is_not_null_pointer<void(int, ...) noexcept>();
    test_is_not_null_pointer<void(int, ...)& noexcept>();
    test_is_not_null_pointer<void(int, ...)&& noexcept>();
    test_is_not_null_pointer<void(int, ...) const noexcept>();
    test_is_not_null_pointer<void(int, ...) const& noexcept>();
    test_is_not_null_pointer<void(int, ...) const&& noexcept>();
    test_is_not_null_pointer<void(int, ...) volatile noexcept>();
    test_is_not_null_pointer<void(int, ...) volatile& noexcept>();
    test_is_not_null_pointer<void(int, ...) volatile&& noexcept>();
    test_is_not_null_pointer<void(int, ...) const volatile noexcept>();
    test_is_not_null_pointer<void(int, ...) const volatile& noexcept>();
    test_is_not_null_pointer<void(int, ...) const volatile&& noexcept>();

    test_is_not_null_pointer<int()>();
    test_is_not_null_pointer<int()&>();
    test_is_not_null_pointer<int() &&>();
    test_is_not_null_pointer<int() const>();
    test_is_not_null_pointer<int() const&>();
    test_is_not_null_pointer<int() const&&>();
    test_is_not_null_pointer<int() volatile>();
    test_is_not_null_pointer<int() volatile&>();
    test_is_not_null_pointer<int() volatile&&>();
    test_is_not_null_pointer<int() const volatile>();
    test_is_not_null_pointer<int() const volatile&>();
    test_is_not_null_pointer<int() const volatile&&>();
    test_is_not_null_pointer<int() noexcept>();
    test_is_not_null_pointer<int()& noexcept>();
    test_is_not_null_pointer<int()&& noexcept>();
    test_is_not_null_pointer<int() const noexcept>();
    test_is_not_null_pointer<int() const& noexcept>();
    test_is_not_null_pointer<int() const&& noexcept>();
    test_is_not_null_pointer<int() volatile noexcept>();
    test_is_not_null_pointer<int() volatile& noexcept>();
    test_is_not_null_pointer<int() volatile&& noexcept>();
    test_is_not_null_pointer<int() const volatile noexcept>();
    test_is_not_null_pointer<int() const volatile& noexcept>();
    test_is_not_null_pointer<int() const volatile&& noexcept>();

    test_is_not_null_pointer<int(int)>();
    test_is_not_null_pointer<int(int)&>();
    test_is_not_null_pointer<int(int) &&>();
    test_is_not_null_pointer<int(int) const>();
    test_is_not_null_pointer<int(int) const&>();
    test_is_not_null_pointer<int(int) const&&>();
    test_is_not_null_pointer<int(int) volatile>();
    test_is_not_null_pointer<int(int) volatile&>();
    test_is_not_null_pointer<int(int) volatile&&>();
    test_is_not_null_pointer<int(int) const volatile>();
    test_is_not_null_pointer<int(int) const volatile&>();
    test_is_not_null_pointer<int(int) const volatile&&>();
    test_is_not_null_pointer<int(int) noexcept>();
    test_is_not_null_pointer<int(int)& noexcept>();
    test_is_not_null_pointer<int(int)&& noexcept>();
    test_is_not_null_pointer<int(int) const noexcept>();
    test_is_not_null_pointer<int(int) const& noexcept>();
    test_is_not_null_pointer<int(int) const&& noexcept>();
    test_is_not_null_pointer<int(int) volatile noexcept>();
    test_is_not_null_pointer<int(int) volatile& noexcept>();
    test_is_not_null_pointer<int(int) volatile&& noexcept>();
    test_is_not_null_pointer<int(int) const volatile noexcept>();
    test_is_not_null_pointer<int(int) const volatile& noexcept>();
    test_is_not_null_pointer<int(int) const volatile&& noexcept>();

    test_is_not_null_pointer<int(...)>();
    test_is_not_null_pointer<int(...)&>();
    test_is_not_null_pointer<int(...) &&>();
    test_is_not_null_pointer<int(...) const>();
    test_is_not_null_pointer<int(...) const&>();
    test_is_not_null_pointer<int(...) const&&>();
    test_is_not_null_pointer<int(...) volatile>();
    test_is_not_null_pointer<int(...) volatile&>();
    test_is_not_null_pointer<int(...) volatile&&>();
    test_is_not_null_pointer<int(...) const volatile>();
    test_is_not_null_pointer<int(...) const volatile&>();
    test_is_not_null_pointer<int(...) const volatile&&>();
    test_is_not_null_pointer<int(...) noexcept>();
    test_is_not_null_pointer<int(...)& noexcept>();
    test_is_not_null_pointer<int(...)&& noexcept>();
    test_is_not_null_pointer<int(...) const noexcept>();
    test_is_not_null_pointer<int(...) const& noexcept>();
    test_is_not_null_pointer<int(...) const&& noexcept>();
    test_is_not_null_pointer<int(...) volatile noexcept>();
    test_is_not_null_pointer<int(...) volatile& noexcept>();
    test_is_not_null_pointer<int(...) volatile&& noexcept>();
    test_is_not_null_pointer<int(...) const volatile noexcept>();
    test_is_not_null_pointer<int(...) const volatile& noexcept>();
    test_is_not_null_pointer<int(...) const volatile&& noexcept>();

    test_is_not_null_pointer<int(int, ...)>();
    test_is_not_null_pointer<int(int, ...)&>();
    test_is_not_null_pointer<int(int, ...) &&>();
    test_is_not_null_pointer<int(int, ...) const>();
    test_is_not_null_pointer<int(int, ...) const&>();
    test_is_not_null_pointer<int(int, ...) const&&>();
    test_is_not_null_pointer<int(int, ...) volatile>();
    test_is_not_null_pointer<int(int, ...) volatile&>();
    test_is_not_null_pointer<int(int, ...) volatile&&>();
    test_is_not_null_pointer<int(int, ...) const volatile>();
    test_is_not_null_pointer<int(int, ...) const volatile&>();
    test_is_not_null_pointer<int(int, ...) const volatile&&>();
    test_is_not_null_pointer<int(int, ...) noexcept>();
    test_is_not_null_pointer<int(int, ...)& noexcept>();
    test_is_not_null_pointer<int(int, ...)&& noexcept>();
    test_is_not_null_pointer<int(int, ...) const noexcept>();
    test_is_not_null_pointer<int(int, ...) const& noexcept>();
    test_is_not_null_pointer<int(int, ...) const&& noexcept>();
    test_is_not_null_pointer<int(int, ...) volatile noexcept>();
    test_is_not_null_pointer<int(int, ...) volatile& noexcept>();
    test_is_not_null_pointer<int(int, ...) volatile&& noexcept>();
    test_is_not_null_pointer<int(int, ...) const volatile noexcept>();
    test_is_not_null_pointer<int(int, ...) const volatile& noexcept>();
    test_is_not_null_pointer<int(int, ...) const volatile&& noexcept>();

    test_is_not_null_pointer<void (*)()>();
    test_is_not_null_pointer<void (*)() noexcept>();

    test_is_not_null_pointer<void (*)(int)>();
    test_is_not_null_pointer<void (*)(int) noexcept>();

    test_is_not_null_pointer<void (*)(...)>();
    test_is_not_null_pointer<void (*)(...) noexcept>();

    test_is_not_null_pointer<void (*)(int, ...)>();
    test_is_not_null_pointer<void (*)(int, ...) noexcept>();

    test_is_not_null_pointer<int (*)()>();
    test_is_not_null_pointer<int (*)() noexcept>();

    test_is_not_null_pointer<int (*)(int)>();
    test_is_not_null_pointer<int (*)(int) noexcept>();

    test_is_not_null_pointer<int (*)(...)>();
    test_is_not_null_pointer<int (*)(...) noexcept>();

    test_is_not_null_pointer<int (*)(int, ...)>();
    test_is_not_null_pointer<int (*)(int, ...) noexcept>();

    test_is_not_null_pointer<void (&)()>();
    test_is_not_null_pointer<void (&)() noexcept>();

    test_is_not_null_pointer<void (&)(int)>();
    test_is_not_null_pointer<void (&)(int) noexcept>();

    test_is_not_null_pointer<void (&)(...)>();
    test_is_not_null_pointer<void (&)(...) noexcept>();

    test_is_not_null_pointer<void (&)(int, ...)>();
    test_is_not_null_pointer<void (&)(int, ...) noexcept>();

    test_is_not_null_pointer<int (&)()>();
    test_is_not_null_pointer<int (&)() noexcept>();

    test_is_not_null_pointer<int (&)(int)>();
    test_is_not_null_pointer<int (&)(int) noexcept>();

    test_is_not_null_pointer<int (&)(...)>();
    test_is_not_null_pointer<int (&)(...) noexcept>();

    test_is_not_null_pointer<int (&)(int, ...)>();
    test_is_not_null_pointer<int (&)(int, ...) noexcept>();

    test_is_not_null_pointer<void(&&)()>();
    test_is_not_null_pointer<void(&&)() noexcept>();

    test_is_not_null_pointer<void(&&)(int)>();
    test_is_not_null_pointer<void(&&)(int) noexcept>();

    test_is_not_null_pointer<void(&&)(...)>();
    test_is_not_null_pointer<void(&&)(...) noexcept>();

    test_is_not_null_pointer<void(&&)(int, ...)>();
    test_is_not_null_pointer<void(&&)(int, ...) noexcept>();

    test_is_not_null_pointer<int(&&)()>();
    test_is_not_null_pointer<int(&&)() noexcept>();

    test_is_not_null_pointer<int(&&)(int)>();
    test_is_not_null_pointer<int(&&)(int) noexcept>();

    test_is_not_null_pointer<int(&&)(...)>();
    test_is_not_null_pointer<int(&&)(...) noexcept>();

    test_is_not_null_pointer<int(&&)(int, ...)>();
    test_is_not_null_pointer<int(&&)(int, ...) noexcept>();

    test_is_not_null_pointer<void (Class::*)()>();
    test_is_not_null_pointer<void (Class::*)()&>();
    test_is_not_null_pointer<void (Class::*)() &&>();
    test_is_not_null_pointer<void (Class::*)() const>();
    test_is_not_null_pointer<void (Class::*)() const&>();
    test_is_not_null_pointer<void (Class::*)() const&&>();
    test_is_not_null_pointer<void (Class::*)() noexcept>();
    test_is_not_null_pointer<void (Class::*)()& noexcept>();
    test_is_not_null_pointer<void (Class::*)()&& noexcept>();
    test_is_not_null_pointer<void (Class::*)() const noexcept>();
    test_is_not_null_pointer<void (Class::*)() const& noexcept>();
    test_is_not_null_pointer<void (Class::*)() const&& noexcept>();

    test_is_not_null_pointer<void (Class::*)(int)>();
    test_is_not_null_pointer<void (Class::*)(int)&>();
    test_is_not_null_pointer<void (Class::*)(int) &&>();
    test_is_not_null_pointer<void (Class::*)(int) const>();
    test_is_not_null_pointer<void (Class::*)(int) const&>();
    test_is_not_null_pointer<void (Class::*)(int) const&&>();
    test_is_not_null_pointer<void (Class::*)(int) noexcept>();
    test_is_not_null_pointer<void (Class::*)(int)& noexcept>();
    test_is_not_null_pointer<void (Class::*)(int)&& noexcept>();
    test_is_not_null_pointer<void (Class::*)(int) const noexcept>();
    test_is_not_null_pointer<void (Class::*)(int) const& noexcept>();
    test_is_not_null_pointer<void (Class::*)(int) const&& noexcept>();

    test_is_not_null_pointer<void (Class::*)(...)>();
    test_is_not_null_pointer<void (Class::*)(...)&>();
    test_is_not_null_pointer<void (Class::*)(...) &&>();
    test_is_not_null_pointer<void (Class::*)(...) const>();
    test_is_not_null_pointer<void (Class::*)(...) const&>();
    test_is_not_null_pointer<void (Class::*)(...) const&&>();
    test_is_not_null_pointer<void (Class::*)(...) noexcept>();
    test_is_not_null_pointer<void (Class::*)(...)& noexcept>();
    test_is_not_null_pointer<void (Class::*)(...)&& noexcept>();
    test_is_not_null_pointer<void (Class::*)(...) const noexcept>();
    test_is_not_null_pointer<void (Class::*)(...) const& noexcept>();
    test_is_not_null_pointer<void (Class::*)(...) const&& noexcept>();

    test_is_not_null_pointer<void (Class::*)(int, ...)>();
    test_is_not_null_pointer<void (Class::*)(int, ...)&>();
    test_is_not_null_pointer<void (Class::*)(int, ...) &&>();
    test_is_not_null_pointer<void (Class::*)(int, ...) const>();
    test_is_not_null_pointer<void (Class::*)(int, ...) const&>();
    test_is_not_null_pointer<void (Class::*)(int, ...) const&&>();
    test_is_not_null_pointer<void (Class::*)(int, ...) noexcept>();
    test_is_not_null_pointer<void (Class::*)(int, ...)& noexcept>();
    test_is_not_null_pointer<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_null_pointer<void (Class::*)(int, ...) const noexcept>();
    test_is_not_null_pointer<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_null_pointer<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_null_pointer<int (Class::*)()>();
    test_is_not_null_pointer<int (Class::*)()&>();
    test_is_not_null_pointer<int (Class::*)() &&>();
    test_is_not_null_pointer<int (Class::*)() const>();
    test_is_not_null_pointer<int (Class::*)() const&>();
    test_is_not_null_pointer<int (Class::*)() const&&>();
    test_is_not_null_pointer<int (Class::*)() noexcept>();
    test_is_not_null_pointer<int (Class::*)()& noexcept>();
    test_is_not_null_pointer<int (Class::*)()&& noexcept>();
    test_is_not_null_pointer<int (Class::*)() const noexcept>();
    test_is_not_null_pointer<int (Class::*)() const& noexcept>();
    test_is_not_null_pointer<int (Class::*)() const&& noexcept>();

    test_is_not_null_pointer<int (Class::*)(int)>();
    test_is_not_null_pointer<int (Class::*)(int)&>();
    test_is_not_null_pointer<int (Class::*)(int) &&>();
    test_is_not_null_pointer<int (Class::*)(int) const>();
    test_is_not_null_pointer<int (Class::*)(int) const&>();
    test_is_not_null_pointer<int (Class::*)(int) const&&>();
    test_is_not_null_pointer<int (Class::*)(int) noexcept>();
    test_is_not_null_pointer<int (Class::*)(int)& noexcept>();
    test_is_not_null_pointer<int (Class::*)(int)&& noexcept>();
    test_is_not_null_pointer<int (Class::*)(int) const noexcept>();
    test_is_not_null_pointer<int (Class::*)(int) const& noexcept>();
    test_is_not_null_pointer<int (Class::*)(int) const&& noexcept>();

    test_is_not_null_pointer<int (Class::*)(...)>();
    test_is_not_null_pointer<int (Class::*)(...)&>();
    test_is_not_null_pointer<int (Class::*)(...) &&>();
    test_is_not_null_pointer<int (Class::*)(...) const>();
    test_is_not_null_pointer<int (Class::*)(...) const&>();
    test_is_not_null_pointer<int (Class::*)(...) const&&>();
    test_is_not_null_pointer<int (Class::*)(...) noexcept>();
    test_is_not_null_pointer<int (Class::*)(...)& noexcept>();
    test_is_not_null_pointer<int (Class::*)(...)&& noexcept>();
    test_is_not_null_pointer<int (Class::*)(...) const noexcept>();
    test_is_not_null_pointer<int (Class::*)(...) const& noexcept>();
    test_is_not_null_pointer<int (Class::*)(...) const&& noexcept>();

    test_is_not_null_pointer<int (Class::*)(int, ...)>();
    test_is_not_null_pointer<int (Class::*)(int, ...)&>();
    test_is_not_null_pointer<int (Class::*)(int, ...) &&>();
    test_is_not_null_pointer<int (Class::*)(int, ...) const>();
    test_is_not_null_pointer<int (Class::*)(int, ...) const&>();
    test_is_not_null_pointer<int (Class::*)(int, ...) const&&>();
    test_is_not_null_pointer<int (Class::*)(int, ...) noexcept>();
    test_is_not_null_pointer<int (Class::*)(int, ...)& noexcept>();
    test_is_not_null_pointer<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_null_pointer<int (Class::*)(int, ...) const noexcept>();
    test_is_not_null_pointer<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_null_pointer<int (Class::*)(int, ...) const&& noexcept>();
}