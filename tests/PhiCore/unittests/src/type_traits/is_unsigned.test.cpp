#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unsigned.hpp>
#include <vector>

template <typename T>
void test_is_unsigned_impl()
{
    STATIC_REQUIRE(phi::is_unsigned<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unsigned<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsigned_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_unsigned_v<T>);
#endif
}

template <typename T>
void test_is_not_unsigned_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsigned<T>::value);
    STATIC_REQUIRE(phi::is_not_unsigned<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsigned_v<T>);
    STATIC_REQUIRE(phi::is_not_unsigned_v<T>);
#endif
}

template <typename T>
void test_is_unsigned()
{
    test_is_unsigned_impl<T>();
    test_is_unsigned_impl<const T>();
    test_is_unsigned_impl<volatile T>();
    test_is_unsigned_impl<const volatile T>();
}

template <typename T>
void test_is_not_unsigned()
{
    test_is_not_unsigned_impl<T>();
    test_is_not_unsigned_impl<const T>();
    test_is_not_unsigned_impl<volatile T>();
    test_is_not_unsigned_impl<const volatile T>();
}

TEST_CASE("is_unsigned")
{
    test_is_not_unsigned<void>();
    test_is_not_unsigned<phi::nullptr_t>();
    test_is_unsigned<bool>();
    //test_is_unsigned<char>();
    test_is_not_unsigned<signed char>();
    test_is_unsigned<unsigned char>();
    test_is_not_unsigned<short>();
    test_is_unsigned<unsigned short>();
    test_is_not_unsigned<int>();
    test_is_unsigned<unsigned int>();
    test_is_not_unsigned<long>();
    test_is_unsigned<unsigned long>();
    test_is_not_unsigned<long long>();
    test_is_unsigned<unsigned long long>();
    test_is_not_unsigned<float>();
    test_is_not_unsigned<double>();
    test_is_not_unsigned<long double>();
    test_is_unsigned<char8_t>();
    test_is_unsigned<char16_t>();
    test_is_unsigned<char32_t>();
#if PHI_COMPILER_IS(MSVC)
    test_is_unsigned<wchar_t>();
#else
    test_is_not_unsigned<wchar_t>();
#endif

    test_is_unsigned<phi::boolean>();
    test_is_not_unsigned<phi::integer<signed char>>();
    test_is_unsigned<phi::integer<unsigned char>>();
    test_is_not_unsigned<phi::integer<short>>();
    test_is_unsigned<phi::integer<unsigned short>>();
    test_is_not_unsigned<phi::integer<int>>();
    test_is_unsigned<phi::integer<unsigned int>>();
    test_is_not_unsigned<phi::integer<long>>();
    test_is_unsigned<phi::integer<unsigned long>>();
    test_is_not_unsigned<phi::integer<long long>>();
    test_is_unsigned<phi::integer<unsigned long long>>();
    test_is_not_unsigned<phi::floating_point<float>>();
    test_is_not_unsigned<phi::floating_point<double>>();
    test_is_not_unsigned<phi::floating_point<long double>>();

    test_is_not_unsigned<std::vector<int>>();
    test_is_not_unsigned<phi::scope_ptr<int>>();

    test_is_not_unsigned<int&>();
    test_is_not_unsigned<const int&>();
    test_is_not_unsigned<volatile int&>();
    test_is_not_unsigned<const volatile int&>();
    test_is_not_unsigned<int&&>();
    test_is_not_unsigned<const int&&>();
    test_is_not_unsigned<volatile int&&>();
    test_is_not_unsigned<const volatile int&&>();
    test_is_not_unsigned<int*>();
    test_is_not_unsigned<const int*>();
    test_is_not_unsigned<volatile int*>();
    test_is_not_unsigned<const volatile int*>();
    test_is_not_unsigned<int**>();
    test_is_not_unsigned<const int**>();
    test_is_not_unsigned<volatile int**>();
    test_is_not_unsigned<const volatile int**>();
    test_is_not_unsigned<int*&>();
    test_is_not_unsigned<const int*&>();
    test_is_not_unsigned<volatile int*&>();
    test_is_not_unsigned<const volatile int*&>();
    test_is_not_unsigned<int*&&>();
    test_is_not_unsigned<const int*&&>();
    test_is_not_unsigned<volatile int*&&>();
    test_is_not_unsigned<const volatile int*&&>();
    test_is_not_unsigned<void*>();
    test_is_not_unsigned<char[3]>();
    test_is_not_unsigned<char[]>();
    test_is_not_unsigned<char* [3]>();
    test_is_not_unsigned<char*[]>();
    test_is_not_unsigned<int(*)[3]>();
    test_is_not_unsigned<int(*)[]>();
    test_is_not_unsigned<int(&)[3]>();
    test_is_not_unsigned<int(&)[]>();
    test_is_not_unsigned<int(&&)[3]>();
    test_is_not_unsigned<int(&&)[]>();
    test_is_not_unsigned<char[3][2]>();
    test_is_not_unsigned<char[][2]>();
    test_is_not_unsigned<char* [3][2]>();
    test_is_not_unsigned<char*[][2]>();
    test_is_not_unsigned<int(*)[3][2]>();
    test_is_not_unsigned<int(*)[][2]>();
    test_is_not_unsigned<int(&)[3][2]>();
    test_is_not_unsigned<int(&)[][2]>();
    test_is_not_unsigned<int(&&)[3][2]>();
    test_is_not_unsigned<int(&&)[][2]>();
    test_is_not_unsigned<Class>();
    test_is_not_unsigned<Class[]>();
    test_is_not_unsigned<Class[2]>();
    test_is_not_unsigned<Template<void>>();
    test_is_not_unsigned<Template<int>>();
    test_is_not_unsigned<Template<Class>>();
    test_is_not_unsigned<Template<incomplete_type>>();
    test_is_not_unsigned<VariadicTemplate<>>();
    test_is_not_unsigned<VariadicTemplate<void>>();
    test_is_not_unsigned<VariadicTemplate<int>>();
    test_is_not_unsigned<VariadicTemplate<Class>>();
    test_is_not_unsigned<VariadicTemplate<incomplete_type>>();
    test_is_not_unsigned<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsigned<PublicDerviedFromTemplate<Base>>();
    test_is_not_unsigned<PublicDerviedFromTemplate<Derived>>();
    test_is_not_unsigned<PublicDerviedFromTemplate<Class>>();
    test_is_not_unsigned<PrivateDerviedFromTemplate<Base>>();
    test_is_not_unsigned<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_unsigned<PrivateDerviedFromTemplate<Class>>();
    test_is_not_unsigned<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_unsigned<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_unsigned<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_unsigned<Union>();
    test_is_not_unsigned<NonEmptyUnion>();
    test_is_not_unsigned<Empty>();
    test_is_not_unsigned<NotEmpty>();
    test_is_not_unsigned<bit_zero>();
    test_is_not_unsigned<bit_one>();
    test_is_not_unsigned<Base>();
    test_is_not_unsigned<Derived>();
    test_is_not_unsigned<Abstract>();
    test_is_not_unsigned<PublicAbstract>();
    test_is_not_unsigned<PrivateAbstract>();
    test_is_not_unsigned<ProtectedAbstract>();
    test_is_not_unsigned<AbstractTemplate<int>>();
    test_is_not_unsigned<AbstractTemplate<double>>();
    test_is_not_unsigned<AbstractTemplate<Class>>();
    test_is_not_unsigned<AbstractTemplate<incomplete_type>>();
    test_is_not_unsigned<Final>();
    test_is_not_unsigned<PublicDestructor>();
    test_is_not_unsigned<ProtectedDestructor>();
    test_is_not_unsigned<PrivateDestructor>();
    test_is_not_unsigned<VirtualPublicDestructor>();
    test_is_not_unsigned<VirtualProtectedDestructor>();
    test_is_not_unsigned<VirtualPrivateDestructor>();
    test_is_not_unsigned<PurePublicDestructor>();
    test_is_not_unsigned<PureProtectedDestructor>();
    test_is_not_unsigned<PurePrivateDestructor>();
    test_is_not_unsigned<DeletedPublicDestructor>();
    test_is_not_unsigned<DeletedProtectedDestructor>();
    test_is_not_unsigned<DeletedPrivateDestructor>();
    test_is_not_unsigned<DeletedVirtualPublicDestructor>();
    test_is_not_unsigned<DeletedVirtualProtectedDestructor>();
    test_is_not_unsigned<DeletedVirtualPrivateDestructor>();
    test_is_not_unsigned<Enum>();
    test_is_not_unsigned<EnumSigned>();
    test_is_not_unsigned<EnumUnsigned>();
    test_is_not_unsigned<EnumClass>();
    test_is_not_unsigned<EnumStruct>();
    test_is_not_unsigned<Function>();
    test_is_not_unsigned<FunctionPtr>();
    test_is_not_unsigned<MemberObjectPtr>();
    test_is_not_unsigned<MemberFunctionPtr>();
    test_is_not_unsigned<incomplete_type>();
    test_is_not_unsigned<IncompleteTemplate<void>>();
    test_is_not_unsigned<IncompleteTemplate<int>>();
    test_is_not_unsigned<IncompleteTemplate<Class>>();
    test_is_not_unsigned<IncompleteTemplate<incomplete_type>>();
    test_is_not_unsigned<IncompleteVariadicTemplate<>>();
    test_is_not_unsigned<IncompleteVariadicTemplate<void>>();
    test_is_not_unsigned<IncompleteVariadicTemplate<int>>();
    test_is_not_unsigned<IncompleteVariadicTemplate<Class>>();
    test_is_not_unsigned<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_unsigned<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsigned<int Class::*>();
    test_is_not_unsigned<float Class::*>();
    test_is_not_unsigned<void * Class::*>();
    test_is_not_unsigned<int * Class::*>();
    test_is_not_unsigned<int Class::*&>();
    test_is_not_unsigned<float Class::*&>();
    test_is_not_unsigned<void * Class::*&>();
    test_is_not_unsigned<int * Class::*&>();
    test_is_not_unsigned<int Class::*&&>();
    test_is_not_unsigned<float Class::*&&>();
    test_is_not_unsigned<void * Class::*&&>();
    test_is_not_unsigned<int * Class::*&&>();
    test_is_not_unsigned<int Class::*const>();
    test_is_not_unsigned<float Class::*const>();
    test_is_not_unsigned<void * Class::*const>();
    test_is_not_unsigned<int Class::*const&>();
    test_is_not_unsigned<float Class::*const&>();
    test_is_not_unsigned<void * Class::*const&>();
    test_is_not_unsigned<int Class::*const&&>();
    test_is_not_unsigned<float Class::*const&&>();
    test_is_not_unsigned<void * Class::*const&&>();
    test_is_not_unsigned<int Class::*volatile>();
    test_is_not_unsigned<float Class::*volatile>();
    test_is_not_unsigned<void * Class::*volatile>();
    test_is_not_unsigned<int Class::*volatile&>();
    test_is_not_unsigned<float Class::*volatile&>();
    test_is_not_unsigned<void * Class::*volatile&>();
    test_is_not_unsigned<int Class::*volatile&&>();
    test_is_not_unsigned<float Class::*volatile&&>();
    test_is_not_unsigned<void * Class::*volatile&&>();
    test_is_not_unsigned<int Class::*const volatile>();
    test_is_not_unsigned<float Class::*const volatile>();
    test_is_not_unsigned<void * Class::*const volatile>();
    test_is_not_unsigned<int Class::*const volatile&>();
    test_is_not_unsigned<float Class::*const volatile&>();
    test_is_not_unsigned<void * Class::*const volatile&>();
    test_is_not_unsigned<int Class::*const volatile&&>();
    test_is_not_unsigned<float Class::*const volatile&&>();
    test_is_not_unsigned<void * Class::*const volatile&&>();
    test_is_not_unsigned<NonCopyable>();
    test_is_not_unsigned<NonMoveable>();
    test_is_not_unsigned<NonConstructible>();
    test_is_not_unsigned<Tracked>();
    test_is_not_unsigned<TrapConstructible>();
    test_is_not_unsigned<TrapImplicitConversion>();
    test_is_not_unsigned<TrapComma>();
    test_is_not_unsigned<TrapCall>();
    test_is_not_unsigned<TrapSelfAssign>();
    test_is_not_unsigned<TrapDeref>();
    test_is_not_unsigned<TrapArraySubscript>();

    test_is_not_unsigned<void()>();
    test_is_not_unsigned<void()&>();
    test_is_not_unsigned<void() &&>();
    test_is_not_unsigned<void() const>();
    test_is_not_unsigned<void() const&>();
    test_is_not_unsigned<void() const&&>();
    test_is_not_unsigned<void() volatile>();
    test_is_not_unsigned<void() volatile&>();
    test_is_not_unsigned<void() volatile&&>();
    test_is_not_unsigned<void() const volatile>();
    test_is_not_unsigned<void() const volatile&>();
    test_is_not_unsigned<void() const volatile&&>();
    test_is_not_unsigned<void() noexcept>();
    test_is_not_unsigned<void()& noexcept>();
    test_is_not_unsigned<void()&& noexcept>();
    test_is_not_unsigned<void() const noexcept>();
    test_is_not_unsigned<void() const& noexcept>();
    test_is_not_unsigned<void() const&& noexcept>();
    test_is_not_unsigned<void() volatile noexcept>();
    test_is_not_unsigned<void() volatile& noexcept>();
    test_is_not_unsigned<void() volatile&& noexcept>();
    test_is_not_unsigned<void() const volatile noexcept>();
    test_is_not_unsigned<void() const volatile& noexcept>();
    test_is_not_unsigned<void() const volatile&& noexcept>();

    test_is_not_unsigned<void(int)>();
    test_is_not_unsigned<void(int)&>();
    test_is_not_unsigned<void(int) &&>();
    test_is_not_unsigned<void(int) const>();
    test_is_not_unsigned<void(int) const&>();
    test_is_not_unsigned<void(int) const&&>();
    test_is_not_unsigned<void(int) volatile>();
    test_is_not_unsigned<void(int) volatile&>();
    test_is_not_unsigned<void(int) volatile&&>();
    test_is_not_unsigned<void(int) const volatile>();
    test_is_not_unsigned<void(int) const volatile&>();
    test_is_not_unsigned<void(int) const volatile&&>();
    test_is_not_unsigned<void(int) noexcept>();
    test_is_not_unsigned<void(int)& noexcept>();
    test_is_not_unsigned<void(int)&& noexcept>();
    test_is_not_unsigned<void(int) const noexcept>();
    test_is_not_unsigned<void(int) const& noexcept>();
    test_is_not_unsigned<void(int) const&& noexcept>();
    test_is_not_unsigned<void(int) volatile noexcept>();
    test_is_not_unsigned<void(int) volatile& noexcept>();
    test_is_not_unsigned<void(int) volatile&& noexcept>();
    test_is_not_unsigned<void(int) const volatile noexcept>();
    test_is_not_unsigned<void(int) const volatile& noexcept>();
    test_is_not_unsigned<void(int) const volatile&& noexcept>();

    test_is_not_unsigned<void(...)>();
    test_is_not_unsigned<void(...)&>();
    test_is_not_unsigned<void(...) &&>();
    test_is_not_unsigned<void(...) const>();
    test_is_not_unsigned<void(...) const&>();
    test_is_not_unsigned<void(...) const&&>();
    test_is_not_unsigned<void(...) volatile>();
    test_is_not_unsigned<void(...) volatile&>();
    test_is_not_unsigned<void(...) volatile&&>();
    test_is_not_unsigned<void(...) const volatile>();
    test_is_not_unsigned<void(...) const volatile&>();
    test_is_not_unsigned<void(...) const volatile&&>();
    test_is_not_unsigned<void(...) noexcept>();
    test_is_not_unsigned<void(...)& noexcept>();
    test_is_not_unsigned<void(...)&& noexcept>();
    test_is_not_unsigned<void(...) const noexcept>();
    test_is_not_unsigned<void(...) const& noexcept>();
    test_is_not_unsigned<void(...) const&& noexcept>();
    test_is_not_unsigned<void(...) volatile noexcept>();
    test_is_not_unsigned<void(...) volatile& noexcept>();
    test_is_not_unsigned<void(...) volatile&& noexcept>();
    test_is_not_unsigned<void(...) const volatile noexcept>();
    test_is_not_unsigned<void(...) const volatile& noexcept>();
    test_is_not_unsigned<void(...) const volatile&& noexcept>();

    test_is_not_unsigned<void(int, ...)>();
    test_is_not_unsigned<void(int, ...)&>();
    test_is_not_unsigned<void(int, ...) &&>();
    test_is_not_unsigned<void(int, ...) const>();
    test_is_not_unsigned<void(int, ...) const&>();
    test_is_not_unsigned<void(int, ...) const&&>();
    test_is_not_unsigned<void(int, ...) volatile>();
    test_is_not_unsigned<void(int, ...) volatile&>();
    test_is_not_unsigned<void(int, ...) volatile&&>();
    test_is_not_unsigned<void(int, ...) const volatile>();
    test_is_not_unsigned<void(int, ...) const volatile&>();
    test_is_not_unsigned<void(int, ...) const volatile&&>();
    test_is_not_unsigned<void(int, ...) noexcept>();
    test_is_not_unsigned<void(int, ...)& noexcept>();
    test_is_not_unsigned<void(int, ...)&& noexcept>();
    test_is_not_unsigned<void(int, ...) const noexcept>();
    test_is_not_unsigned<void(int, ...) const& noexcept>();
    test_is_not_unsigned<void(int, ...) const&& noexcept>();
    test_is_not_unsigned<void(int, ...) volatile noexcept>();
    test_is_not_unsigned<void(int, ...) volatile& noexcept>();
    test_is_not_unsigned<void(int, ...) volatile&& noexcept>();
    test_is_not_unsigned<void(int, ...) const volatile noexcept>();
    test_is_not_unsigned<void(int, ...) const volatile& noexcept>();
    test_is_not_unsigned<void(int, ...) const volatile&& noexcept>();

    test_is_not_unsigned<int()>();
    test_is_not_unsigned<int()&>();
    test_is_not_unsigned<int() &&>();
    test_is_not_unsigned<int() const>();
    test_is_not_unsigned<int() const&>();
    test_is_not_unsigned<int() const&&>();
    test_is_not_unsigned<int() volatile>();
    test_is_not_unsigned<int() volatile&>();
    test_is_not_unsigned<int() volatile&&>();
    test_is_not_unsigned<int() const volatile>();
    test_is_not_unsigned<int() const volatile&>();
    test_is_not_unsigned<int() const volatile&&>();
    test_is_not_unsigned<int() noexcept>();
    test_is_not_unsigned<int()& noexcept>();
    test_is_not_unsigned<int()&& noexcept>();
    test_is_not_unsigned<int() const noexcept>();
    test_is_not_unsigned<int() const& noexcept>();
    test_is_not_unsigned<int() const&& noexcept>();
    test_is_not_unsigned<int() volatile noexcept>();
    test_is_not_unsigned<int() volatile& noexcept>();
    test_is_not_unsigned<int() volatile&& noexcept>();
    test_is_not_unsigned<int() const volatile noexcept>();
    test_is_not_unsigned<int() const volatile& noexcept>();
    test_is_not_unsigned<int() const volatile&& noexcept>();

    test_is_not_unsigned<int(int)>();
    test_is_not_unsigned<int(int)&>();
    test_is_not_unsigned<int(int) &&>();
    test_is_not_unsigned<int(int) const>();
    test_is_not_unsigned<int(int) const&>();
    test_is_not_unsigned<int(int) const&&>();
    test_is_not_unsigned<int(int) volatile>();
    test_is_not_unsigned<int(int) volatile&>();
    test_is_not_unsigned<int(int) volatile&&>();
    test_is_not_unsigned<int(int) const volatile>();
    test_is_not_unsigned<int(int) const volatile&>();
    test_is_not_unsigned<int(int) const volatile&&>();
    test_is_not_unsigned<int(int) noexcept>();
    test_is_not_unsigned<int(int)& noexcept>();
    test_is_not_unsigned<int(int)&& noexcept>();
    test_is_not_unsigned<int(int) const noexcept>();
    test_is_not_unsigned<int(int) const& noexcept>();
    test_is_not_unsigned<int(int) const&& noexcept>();
    test_is_not_unsigned<int(int) volatile noexcept>();
    test_is_not_unsigned<int(int) volatile& noexcept>();
    test_is_not_unsigned<int(int) volatile&& noexcept>();
    test_is_not_unsigned<int(int) const volatile noexcept>();
    test_is_not_unsigned<int(int) const volatile& noexcept>();
    test_is_not_unsigned<int(int) const volatile&& noexcept>();

    test_is_not_unsigned<int(...)>();
    test_is_not_unsigned<int(...)&>();
    test_is_not_unsigned<int(...) &&>();
    test_is_not_unsigned<int(...) const>();
    test_is_not_unsigned<int(...) const&>();
    test_is_not_unsigned<int(...) const&&>();
    test_is_not_unsigned<int(...) volatile>();
    test_is_not_unsigned<int(...) volatile&>();
    test_is_not_unsigned<int(...) volatile&&>();
    test_is_not_unsigned<int(...) const volatile>();
    test_is_not_unsigned<int(...) const volatile&>();
    test_is_not_unsigned<int(...) const volatile&&>();
    test_is_not_unsigned<int(...) noexcept>();
    test_is_not_unsigned<int(...)& noexcept>();
    test_is_not_unsigned<int(...)&& noexcept>();
    test_is_not_unsigned<int(...) const noexcept>();
    test_is_not_unsigned<int(...) const& noexcept>();
    test_is_not_unsigned<int(...) const&& noexcept>();
    test_is_not_unsigned<int(...) volatile noexcept>();
    test_is_not_unsigned<int(...) volatile& noexcept>();
    test_is_not_unsigned<int(...) volatile&& noexcept>();
    test_is_not_unsigned<int(...) const volatile noexcept>();
    test_is_not_unsigned<int(...) const volatile& noexcept>();
    test_is_not_unsigned<int(...) const volatile&& noexcept>();

    test_is_not_unsigned<int(int, ...)>();
    test_is_not_unsigned<int(int, ...)&>();
    test_is_not_unsigned<int(int, ...) &&>();
    test_is_not_unsigned<int(int, ...) const>();
    test_is_not_unsigned<int(int, ...) const&>();
    test_is_not_unsigned<int(int, ...) const&&>();
    test_is_not_unsigned<int(int, ...) volatile>();
    test_is_not_unsigned<int(int, ...) volatile&>();
    test_is_not_unsigned<int(int, ...) volatile&&>();
    test_is_not_unsigned<int(int, ...) const volatile>();
    test_is_not_unsigned<int(int, ...) const volatile&>();
    test_is_not_unsigned<int(int, ...) const volatile&&>();
    test_is_not_unsigned<int(int, ...) noexcept>();
    test_is_not_unsigned<int(int, ...)& noexcept>();
    test_is_not_unsigned<int(int, ...)&& noexcept>();
    test_is_not_unsigned<int(int, ...) const noexcept>();
    test_is_not_unsigned<int(int, ...) const& noexcept>();
    test_is_not_unsigned<int(int, ...) const&& noexcept>();
    test_is_not_unsigned<int(int, ...) volatile noexcept>();
    test_is_not_unsigned<int(int, ...) volatile& noexcept>();
    test_is_not_unsigned<int(int, ...) volatile&& noexcept>();
    test_is_not_unsigned<int(int, ...) const volatile noexcept>();
    test_is_not_unsigned<int(int, ...) const volatile& noexcept>();
    test_is_not_unsigned<int(int, ...) const volatile&& noexcept>();

    test_is_not_unsigned<void (*)()>();
    test_is_not_unsigned<void (*)() noexcept>();

    test_is_not_unsigned<void (*)(int)>();
    test_is_not_unsigned<void (*)(int) noexcept>();

    test_is_not_unsigned<void (*)(...)>();
    test_is_not_unsigned<void (*)(...) noexcept>();

    test_is_not_unsigned<void (*)(int, ...)>();
    test_is_not_unsigned<void (*)(int, ...) noexcept>();

    test_is_not_unsigned<int (*)()>();
    test_is_not_unsigned<int (*)() noexcept>();

    test_is_not_unsigned<int (*)(int)>();
    test_is_not_unsigned<int (*)(int) noexcept>();

    test_is_not_unsigned<int (*)(...)>();
    test_is_not_unsigned<int (*)(...) noexcept>();

    test_is_not_unsigned<int (*)(int, ...)>();
    test_is_not_unsigned<int (*)(int, ...) noexcept>();

    test_is_not_unsigned<void (&)()>();
    test_is_not_unsigned<void (&)() noexcept>();

    test_is_not_unsigned<void (&)(int)>();
    test_is_not_unsigned<void (&)(int) noexcept>();

    test_is_not_unsigned<void (&)(...)>();
    test_is_not_unsigned<void (&)(...) noexcept>();

    test_is_not_unsigned<void (&)(int, ...)>();
    test_is_not_unsigned<void (&)(int, ...) noexcept>();

    test_is_not_unsigned<int (&)()>();
    test_is_not_unsigned<int (&)() noexcept>();

    test_is_not_unsigned<int (&)(int)>();
    test_is_not_unsigned<int (&)(int) noexcept>();

    test_is_not_unsigned<int (&)(...)>();
    test_is_not_unsigned<int (&)(...) noexcept>();

    test_is_not_unsigned<int (&)(int, ...)>();
    test_is_not_unsigned<int (&)(int, ...) noexcept>();

    test_is_not_unsigned<void(&&)()>();
    test_is_not_unsigned<void(&&)() noexcept>();

    test_is_not_unsigned<void(&&)(int)>();
    test_is_not_unsigned<void(&&)(int) noexcept>();

    test_is_not_unsigned<void(&&)(...)>();
    test_is_not_unsigned<void(&&)(...) noexcept>();

    test_is_not_unsigned<void(&&)(int, ...)>();
    test_is_not_unsigned<void(&&)(int, ...) noexcept>();

    test_is_not_unsigned<int(&&)()>();
    test_is_not_unsigned<int(&&)() noexcept>();

    test_is_not_unsigned<int(&&)(int)>();
    test_is_not_unsigned<int(&&)(int) noexcept>();

    test_is_not_unsigned<int(&&)(...)>();
    test_is_not_unsigned<int(&&)(...) noexcept>();

    test_is_not_unsigned<int(&&)(int, ...)>();
    test_is_not_unsigned<int(&&)(int, ...) noexcept>();

    test_is_not_unsigned<void (Class::*)()>();
    test_is_not_unsigned<void (Class::*)()&>();
    test_is_not_unsigned<void (Class::*)() &&>();
    test_is_not_unsigned<void (Class::*)() const>();
    test_is_not_unsigned<void (Class::*)() const&>();
    test_is_not_unsigned<void (Class::*)() const&&>();
    test_is_not_unsigned<void (Class::*)() noexcept>();
    test_is_not_unsigned<void (Class::*)()& noexcept>();
    test_is_not_unsigned<void (Class::*)()&& noexcept>();
    test_is_not_unsigned<void (Class::*)() const noexcept>();
    test_is_not_unsigned<void (Class::*)() const& noexcept>();
    test_is_not_unsigned<void (Class::*)() const&& noexcept>();

    test_is_not_unsigned<void (Class::*)(int)>();
    test_is_not_unsigned<void (Class::*)(int)&>();
    test_is_not_unsigned<void (Class::*)(int) &&>();
    test_is_not_unsigned<void (Class::*)(int) const>();
    test_is_not_unsigned<void (Class::*)(int) const&>();
    test_is_not_unsigned<void (Class::*)(int) const&&>();
    test_is_not_unsigned<void (Class::*)(int) noexcept>();
    test_is_not_unsigned<void (Class::*)(int)& noexcept>();
    test_is_not_unsigned<void (Class::*)(int)&& noexcept>();
    test_is_not_unsigned<void (Class::*)(int) const noexcept>();
    test_is_not_unsigned<void (Class::*)(int) const& noexcept>();
    test_is_not_unsigned<void (Class::*)(int) const&& noexcept>();

    test_is_not_unsigned<void (Class::*)(...)>();
    test_is_not_unsigned<void (Class::*)(...)&>();
    test_is_not_unsigned<void (Class::*)(...) &&>();
    test_is_not_unsigned<void (Class::*)(...) const>();
    test_is_not_unsigned<void (Class::*)(...) const&>();
    test_is_not_unsigned<void (Class::*)(...) const&&>();
    test_is_not_unsigned<void (Class::*)(...) noexcept>();
    test_is_not_unsigned<void (Class::*)(...)& noexcept>();
    test_is_not_unsigned<void (Class::*)(...)&& noexcept>();
    test_is_not_unsigned<void (Class::*)(...) const noexcept>();
    test_is_not_unsigned<void (Class::*)(...) const& noexcept>();
    test_is_not_unsigned<void (Class::*)(...) const&& noexcept>();

    test_is_not_unsigned<void (Class::*)(int, ...)>();
    test_is_not_unsigned<void (Class::*)(int, ...)&>();
    test_is_not_unsigned<void (Class::*)(int, ...) &&>();
    test_is_not_unsigned<void (Class::*)(int, ...) const>();
    test_is_not_unsigned<void (Class::*)(int, ...) const&>();
    test_is_not_unsigned<void (Class::*)(int, ...) const&&>();
    test_is_not_unsigned<void (Class::*)(int, ...) noexcept>();
    test_is_not_unsigned<void (Class::*)(int, ...)& noexcept>();
    test_is_not_unsigned<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsigned<void (Class::*)(int, ...) const noexcept>();
    test_is_not_unsigned<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsigned<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_unsigned<int (Class::*)()>();
    test_is_not_unsigned<int (Class::*)()&>();
    test_is_not_unsigned<int (Class::*)() &&>();
    test_is_not_unsigned<int (Class::*)() const>();
    test_is_not_unsigned<int (Class::*)() const&>();
    test_is_not_unsigned<int (Class::*)() const&&>();
    test_is_not_unsigned<int (Class::*)() noexcept>();
    test_is_not_unsigned<int (Class::*)()& noexcept>();
    test_is_not_unsigned<int (Class::*)()&& noexcept>();
    test_is_not_unsigned<int (Class::*)() const noexcept>();
    test_is_not_unsigned<int (Class::*)() const& noexcept>();
    test_is_not_unsigned<int (Class::*)() const&& noexcept>();

    test_is_not_unsigned<int (Class::*)(int)>();
    test_is_not_unsigned<int (Class::*)(int)&>();
    test_is_not_unsigned<int (Class::*)(int) &&>();
    test_is_not_unsigned<int (Class::*)(int) const>();
    test_is_not_unsigned<int (Class::*)(int) const&>();
    test_is_not_unsigned<int (Class::*)(int) const&&>();
    test_is_not_unsigned<int (Class::*)(int) noexcept>();
    test_is_not_unsigned<int (Class::*)(int)& noexcept>();
    test_is_not_unsigned<int (Class::*)(int)&& noexcept>();
    test_is_not_unsigned<int (Class::*)(int) const noexcept>();
    test_is_not_unsigned<int (Class::*)(int) const& noexcept>();
    test_is_not_unsigned<int (Class::*)(int) const&& noexcept>();

    test_is_not_unsigned<int (Class::*)(...)>();
    test_is_not_unsigned<int (Class::*)(...)&>();
    test_is_not_unsigned<int (Class::*)(...) &&>();
    test_is_not_unsigned<int (Class::*)(...) const>();
    test_is_not_unsigned<int (Class::*)(...) const&>();
    test_is_not_unsigned<int (Class::*)(...) const&&>();
    test_is_not_unsigned<int (Class::*)(...) noexcept>();
    test_is_not_unsigned<int (Class::*)(...)& noexcept>();
    test_is_not_unsigned<int (Class::*)(...)&& noexcept>();
    test_is_not_unsigned<int (Class::*)(...) const noexcept>();
    test_is_not_unsigned<int (Class::*)(...) const& noexcept>();
    test_is_not_unsigned<int (Class::*)(...) const&& noexcept>();

    test_is_not_unsigned<int (Class::*)(int, ...)>();
    test_is_not_unsigned<int (Class::*)(int, ...)&>();
    test_is_not_unsigned<int (Class::*)(int, ...) &&>();
    test_is_not_unsigned<int (Class::*)(int, ...) const>();
    test_is_not_unsigned<int (Class::*)(int, ...) const&>();
    test_is_not_unsigned<int (Class::*)(int, ...) const&&>();
    test_is_not_unsigned<int (Class::*)(int, ...) noexcept>();
    test_is_not_unsigned<int (Class::*)(int, ...)& noexcept>();
    test_is_not_unsigned<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsigned<int (Class::*)(int, ...) const noexcept>();
    test_is_not_unsigned<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsigned<int (Class::*)(int, ...) const&& noexcept>();
}
