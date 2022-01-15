#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_abstract.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_abstract_impl()
{
#if PHI_HAS_WORKING_IS_ABSTRACT()
    STATIC_REQUIRE(phi::is_abstract<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_abstract<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_abstract_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_abstract_v<T>);
#    endif

    // Stndard compatbility
    STATIC_REQUIRE(std::is_abstract<T>::value);
#endif
}

template <typename T>
void test_is_abstract()
{
    test_is_abstract_impl<T>();
    test_is_abstract_impl<const T>();
    test_is_abstract_impl<volatile T>();
    test_is_abstract_impl<const volatile T>();
}

template <typename T>
void test_is_not_abstract_impl()
{
#if PHI_HAS_WORKING_IS_ABSTRACT()
    STATIC_REQUIRE_FALSE(phi::is_abstract<T>::value);
    STATIC_REQUIRE(phi::is_not_abstract<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_abstract_v<T>);
    STATIC_REQUIRE(phi::is_not_abstract_v<T>);
#    endif

    // Standard compatbility
    STATIC_REQUIRE_FALSE(std::is_abstract<T>::value);
#endif
}

template <typename T>
void test_is_not_abstract()
{
    test_is_not_abstract_impl<T>();
    test_is_not_abstract_impl<const T>();
    test_is_not_abstract_impl<volatile T>();
    test_is_not_abstract_impl<const volatile T>();
}

TEST_CASE("is_abstract")
{
    test_is_not_abstract<void>();
    test_is_not_abstract<phi::nullptr_t>();
    test_is_not_abstract<bool>();
    test_is_not_abstract<char>();
    test_is_not_abstract<signed char>();
    test_is_not_abstract<unsigned char>();
    test_is_not_abstract<short>();
    test_is_not_abstract<unsigned short>();
    test_is_not_abstract<int>();
    test_is_not_abstract<unsigned int>();
    test_is_not_abstract<long>();
    test_is_not_abstract<unsigned long>();
    test_is_not_abstract<long long>();
    test_is_not_abstract<unsigned long long>();
    test_is_not_abstract<float>();
    test_is_not_abstract<double>();
    test_is_not_abstract<long double>();
    test_is_not_abstract<char8_t>();
    test_is_not_abstract<char16_t>();
    test_is_not_abstract<char32_t>();
    test_is_not_abstract<wchar_t>();

    test_is_not_abstract<phi::boolean>();
    test_is_not_abstract<phi::integer<signed char>>();
    test_is_not_abstract<phi::integer<unsigned char>>();
    test_is_not_abstract<phi::integer<short>>();
    test_is_not_abstract<phi::integer<unsigned short>>();
    test_is_not_abstract<phi::integer<int>>();
    test_is_not_abstract<phi::integer<unsigned int>>();
    test_is_not_abstract<phi::integer<long>>();
    test_is_not_abstract<phi::integer<unsigned long>>();
    test_is_not_abstract<phi::integer<long long>>();
    test_is_not_abstract<phi::integer<unsigned long long>>();
    test_is_not_abstract<phi::floating_point<float>>();
    test_is_not_abstract<phi::floating_point<double>>();
    test_is_not_abstract<phi::floating_point<long double>>();

    test_is_not_abstract<std::vector<int>>();
    test_is_not_abstract<phi::scope_ptr<int>>();

    test_is_not_abstract<int&>();
    test_is_not_abstract<const int&>();
    test_is_not_abstract<volatile int&>();
    test_is_not_abstract<const volatile int&>();
    test_is_not_abstract<int&&>();
    test_is_not_abstract<const int&&>();
    test_is_not_abstract<volatile int&&>();
    test_is_not_abstract<const volatile int&&>();
    test_is_not_abstract<int*>();
    test_is_not_abstract<const int*>();
    test_is_not_abstract<volatile int*>();
    test_is_not_abstract<const volatile int*>();
    test_is_not_abstract<int**>();
    test_is_not_abstract<const int**>();
    test_is_not_abstract<volatile int**>();
    test_is_not_abstract<const volatile int**>();
    test_is_not_abstract<int*&>();
    test_is_not_abstract<const int*&>();
    test_is_not_abstract<volatile int*&>();
    test_is_not_abstract<const volatile int*&>();
    test_is_not_abstract<int*&&>();
    test_is_not_abstract<const int*&&>();
    test_is_not_abstract<volatile int*&&>();
    test_is_not_abstract<const volatile int*&&>();
    test_is_not_abstract<void*>();
    test_is_not_abstract<char[3]>();
    test_is_not_abstract<char[]>();
    test_is_not_abstract<char[3]>();
    test_is_not_abstract<char[]>();
    test_is_not_abstract<char* [3]>();
    test_is_not_abstract<char*[]>();
    test_is_not_abstract<int(*)[3]>();
    test_is_not_abstract<int(*)[]>();
    test_is_not_abstract<int(&)[3]>();
    test_is_not_abstract<int(&)[]>();
    test_is_not_abstract<int(&&)[3]>();
    test_is_not_abstract<int(&&)[]>();
    test_is_not_abstract<char[3][2]>();
    test_is_not_abstract<char[][2]>();
    test_is_not_abstract<char* [3][2]>();
    test_is_not_abstract<char*[][2]>();
    test_is_not_abstract<int(*)[3][2]>();
    test_is_not_abstract<int(*)[][2]>();
    test_is_not_abstract<int(&)[3][2]>();
    test_is_not_abstract<int(&)[][2]>();
    test_is_not_abstract<int(&&)[3][2]>();
    test_is_not_abstract<int(&&)[][2]>();
    test_is_not_abstract<Class>();
    test_is_not_abstract<Class[]>();
    test_is_not_abstract<Class[2]>();
    test_is_not_abstract<Template<void>>();
    test_is_not_abstract<Template<int>>();
    test_is_not_abstract<Template<Class>>();
    test_is_not_abstract<Template<incomplete_type>>();
    test_is_not_abstract<VariadicTemplate<>>();
    test_is_not_abstract<VariadicTemplate<void>>();
    test_is_not_abstract<VariadicTemplate<int>>();
    test_is_not_abstract<VariadicTemplate<Class>>();
    test_is_not_abstract<VariadicTemplate<incomplete_type>>();
    test_is_not_abstract<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_abstract<PublicDerviedFromTemplate<Base>>();
    test_is_not_abstract<PublicDerviedFromTemplate<Derived>>();
    test_is_not_abstract<PublicDerviedFromTemplate<Class>>();
    test_is_not_abstract<PrivateDerviedFromTemplate<Base>>();
    test_is_not_abstract<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_abstract<PrivateDerviedFromTemplate<Class>>();
    test_is_not_abstract<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_abstract<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_abstract<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_abstract<Union>();
    test_is_not_abstract<NonEmptyUnion>();
    test_is_not_abstract<Empty>();
    test_is_not_abstract<NotEmpty>();
    test_is_not_abstract<bit_zero>();
    test_is_not_abstract<bit_one>();
    test_is_not_abstract<Base>();
    test_is_not_abstract<Derived>();
    test_is_abstract<Abstract>();
    test_is_abstract<PublicAbstract>();
    test_is_abstract<PrivateAbstract>();
    test_is_abstract<ProtectedAbstract>();
    test_is_abstract<AbstractTemplate<int>>();
    test_is_not_abstract<AbstractTemplate<double>>();
    test_is_abstract<AbstractTemplate<Class>>();
    test_is_abstract<AbstractTemplate<incomplete_type>>();
    test_is_not_abstract<Final>();
    test_is_not_abstract<PublicDestructor>();
    test_is_not_abstract<ProtectedDestructor>();
    test_is_not_abstract<PrivateDestructor>();
    test_is_not_abstract<VirtualPublicDestructor>();
    test_is_not_abstract<VirtualProtectedDestructor>();
    test_is_not_abstract<VirtualPrivateDestructor>();
    test_is_abstract<PurePublicDestructor>();
    test_is_abstract<PureProtectedDestructor>();
    test_is_abstract<PurePrivateDestructor>();
    test_is_not_abstract<DeletedPublicDestructor>();
    test_is_not_abstract<DeletedProtectedDestructor>();
    test_is_not_abstract<DeletedPrivateDestructor>();
    test_is_not_abstract<DeletedVirtualPublicDestructor>();
    test_is_not_abstract<DeletedVirtualProtectedDestructor>();
    test_is_not_abstract<DeletedVirtualPrivateDestructor>();
    test_is_not_abstract<Enum>();
    test_is_not_abstract<EnumSigned>();
    test_is_not_abstract<EnumUnsigned>();
    test_is_not_abstract<EnumClass>();
    test_is_not_abstract<EnumStruct>();
    test_is_not_abstract<Function>();
    test_is_not_abstract<FunctionPtr>();
    test_is_not_abstract<MemberObjectPtr>();
    test_is_not_abstract<MemberFunctionPtr>();
    test_is_not_abstract<int Class::*>();
    test_is_not_abstract<float Class::*>();
    test_is_not_abstract<void * Class::*>();
    test_is_not_abstract<int * Class::*>();
    test_is_not_abstract<int Class::*&>();
    test_is_not_abstract<float Class::*&>();
    test_is_not_abstract<void * Class::*&>();
    test_is_not_abstract<int * Class::*&>();
    test_is_not_abstract<int Class::*&&>();
    test_is_not_abstract<float Class::*&&>();
    test_is_not_abstract<void * Class::*&&>();
    test_is_not_abstract<int * Class::*&&>();
    test_is_not_abstract<int Class::*const>();
    test_is_not_abstract<float Class::*const>();
    test_is_not_abstract<void * Class::*const>();
    test_is_not_abstract<int Class::*const&>();
    test_is_not_abstract<float Class::*const&>();
    test_is_not_abstract<void * Class::*const&>();
    test_is_not_abstract<int Class::*const&&>();
    test_is_not_abstract<float Class::*const&&>();
    test_is_not_abstract<void * Class::*const&&>();
    test_is_not_abstract<int Class::*volatile>();
    test_is_not_abstract<float Class::*volatile>();
    test_is_not_abstract<void * Class::*volatile>();
    test_is_not_abstract<int Class::*volatile&>();
    test_is_not_abstract<float Class::*volatile&>();
    test_is_not_abstract<void * Class::*volatile&>();
    test_is_not_abstract<int Class::*volatile&&>();
    test_is_not_abstract<float Class::*volatile&&>();
    test_is_not_abstract<void * Class::*volatile&&>();
    test_is_not_abstract<int Class::*const volatile>();
    test_is_not_abstract<float Class::*const volatile>();
    test_is_not_abstract<void * Class::*const volatile>();
    test_is_not_abstract<int Class::*const volatile&>();
    test_is_not_abstract<float Class::*const volatile&>();
    test_is_not_abstract<void * Class::*const volatile&>();
    test_is_not_abstract<int Class::*const volatile&&>();
    test_is_not_abstract<float Class::*const volatile&&>();
    test_is_not_abstract<void * Class::*const volatile&&>();
    test_is_not_abstract<NonCopyable>();
    test_is_not_abstract<NonMoveable>();
    test_is_not_abstract<NonConstructible>();
    test_is_not_abstract<Tracked>();
    test_is_not_abstract<TrapConstructible>();
    test_is_not_abstract<TrapImplicitConversion>();
    test_is_not_abstract<TrapComma>();
    test_is_not_abstract<TrapCall>();
    test_is_not_abstract<TrapSelfAssign>();
    test_is_not_abstract<TrapDeref>();
    test_is_not_abstract<TrapArraySubscript>();

    test_is_not_abstract<void()>();
    test_is_not_abstract<void()&>();
    test_is_not_abstract<void() &&>();
    test_is_not_abstract<void() const>();
    test_is_not_abstract<void() const&>();
    test_is_not_abstract<void() const&&>();
    test_is_not_abstract<void() volatile>();
    test_is_not_abstract<void() volatile&>();
    test_is_not_abstract<void() volatile&&>();
    test_is_not_abstract<void() const volatile>();
    test_is_not_abstract<void() const volatile&>();
    test_is_not_abstract<void() const volatile&&>();
    test_is_not_abstract<void() noexcept>();
    test_is_not_abstract<void()& noexcept>();
    test_is_not_abstract<void()&& noexcept>();
    test_is_not_abstract<void() const noexcept>();
    test_is_not_abstract<void() const& noexcept>();
    test_is_not_abstract<void() const&& noexcept>();
    test_is_not_abstract<void() volatile noexcept>();
    test_is_not_abstract<void() volatile& noexcept>();
    test_is_not_abstract<void() volatile&& noexcept>();
    test_is_not_abstract<void() const volatile noexcept>();
    test_is_not_abstract<void() const volatile& noexcept>();
    test_is_not_abstract<void() const volatile&& noexcept>();

    test_is_not_abstract<void(int)>();
    test_is_not_abstract<void(int)&>();
    test_is_not_abstract<void(int) &&>();
    test_is_not_abstract<void(int) const>();
    test_is_not_abstract<void(int) const&>();
    test_is_not_abstract<void(int) const&&>();
    test_is_not_abstract<void(int) volatile>();
    test_is_not_abstract<void(int) volatile&>();
    test_is_not_abstract<void(int) volatile&&>();
    test_is_not_abstract<void(int) const volatile>();
    test_is_not_abstract<void(int) const volatile&>();
    test_is_not_abstract<void(int) const volatile&&>();
    test_is_not_abstract<void(int) noexcept>();
    test_is_not_abstract<void(int)& noexcept>();
    test_is_not_abstract<void(int)&& noexcept>();
    test_is_not_abstract<void(int) const noexcept>();
    test_is_not_abstract<void(int) const& noexcept>();
    test_is_not_abstract<void(int) const&& noexcept>();
    test_is_not_abstract<void(int) volatile noexcept>();
    test_is_not_abstract<void(int) volatile& noexcept>();
    test_is_not_abstract<void(int) volatile&& noexcept>();
    test_is_not_abstract<void(int) const volatile noexcept>();
    test_is_not_abstract<void(int) const volatile& noexcept>();
    test_is_not_abstract<void(int) const volatile&& noexcept>();

    test_is_not_abstract<void(...)>();
    test_is_not_abstract<void(...)&>();
    test_is_not_abstract<void(...) &&>();
    test_is_not_abstract<void(...) const>();
    test_is_not_abstract<void(...) const&>();
    test_is_not_abstract<void(...) const&&>();
    test_is_not_abstract<void(...) volatile>();
    test_is_not_abstract<void(...) volatile&>();
    test_is_not_abstract<void(...) volatile&&>();
    test_is_not_abstract<void(...) const volatile>();
    test_is_not_abstract<void(...) const volatile&>();
    test_is_not_abstract<void(...) const volatile&&>();
    test_is_not_abstract<void(...) noexcept>();
    test_is_not_abstract<void(...)& noexcept>();
    test_is_not_abstract<void(...)&& noexcept>();
    test_is_not_abstract<void(...) const noexcept>();
    test_is_not_abstract<void(...) const& noexcept>();
    test_is_not_abstract<void(...) const&& noexcept>();
    test_is_not_abstract<void(...) volatile noexcept>();
    test_is_not_abstract<void(...) volatile& noexcept>();
    test_is_not_abstract<void(...) volatile&& noexcept>();
    test_is_not_abstract<void(...) const volatile noexcept>();
    test_is_not_abstract<void(...) const volatile& noexcept>();
    test_is_not_abstract<void(...) const volatile&& noexcept>();

    test_is_not_abstract<void(int, ...)>();
    test_is_not_abstract<void(int, ...)&>();
    test_is_not_abstract<void(int, ...) &&>();
    test_is_not_abstract<void(int, ...) const>();
    test_is_not_abstract<void(int, ...) const&>();
    test_is_not_abstract<void(int, ...) const&&>();
    test_is_not_abstract<void(int, ...) volatile>();
    test_is_not_abstract<void(int, ...) volatile&>();
    test_is_not_abstract<void(int, ...) volatile&&>();
    test_is_not_abstract<void(int, ...) const volatile>();
    test_is_not_abstract<void(int, ...) const volatile&>();
    test_is_not_abstract<void(int, ...) const volatile&&>();
    test_is_not_abstract<void(int, ...) noexcept>();
    test_is_not_abstract<void(int, ...)& noexcept>();
    test_is_not_abstract<void(int, ...)&& noexcept>();
    test_is_not_abstract<void(int, ...) const noexcept>();
    test_is_not_abstract<void(int, ...) const& noexcept>();
    test_is_not_abstract<void(int, ...) const&& noexcept>();
    test_is_not_abstract<void(int, ...) volatile noexcept>();
    test_is_not_abstract<void(int, ...) volatile& noexcept>();
    test_is_not_abstract<void(int, ...) volatile&& noexcept>();
    test_is_not_abstract<void(int, ...) const volatile noexcept>();
    test_is_not_abstract<void(int, ...) const volatile& noexcept>();
    test_is_not_abstract<void(int, ...) const volatile&& noexcept>();

    test_is_not_abstract<int()>();
    test_is_not_abstract<int()&>();
    test_is_not_abstract<int() &&>();
    test_is_not_abstract<int() const>();
    test_is_not_abstract<int() const&>();
    test_is_not_abstract<int() const&&>();
    test_is_not_abstract<int() volatile>();
    test_is_not_abstract<int() volatile&>();
    test_is_not_abstract<int() volatile&&>();
    test_is_not_abstract<int() const volatile>();
    test_is_not_abstract<int() const volatile&>();
    test_is_not_abstract<int() const volatile&&>();
    test_is_not_abstract<int() noexcept>();
    test_is_not_abstract<int()& noexcept>();
    test_is_not_abstract<int()&& noexcept>();
    test_is_not_abstract<int() const noexcept>();
    test_is_not_abstract<int() const& noexcept>();
    test_is_not_abstract<int() const&& noexcept>();
    test_is_not_abstract<int() volatile noexcept>();
    test_is_not_abstract<int() volatile& noexcept>();
    test_is_not_abstract<int() volatile&& noexcept>();
    test_is_not_abstract<int() const volatile noexcept>();
    test_is_not_abstract<int() const volatile& noexcept>();
    test_is_not_abstract<int() const volatile&& noexcept>();

    test_is_not_abstract<int(int)>();
    test_is_not_abstract<int(int)&>();
    test_is_not_abstract<int(int) &&>();
    test_is_not_abstract<int(int) const>();
    test_is_not_abstract<int(int) const&>();
    test_is_not_abstract<int(int) const&&>();
    test_is_not_abstract<int(int) volatile>();
    test_is_not_abstract<int(int) volatile&>();
    test_is_not_abstract<int(int) volatile&&>();
    test_is_not_abstract<int(int) const volatile>();
    test_is_not_abstract<int(int) const volatile&>();
    test_is_not_abstract<int(int) const volatile&&>();
    test_is_not_abstract<int(int) noexcept>();
    test_is_not_abstract<int(int)& noexcept>();
    test_is_not_abstract<int(int)&& noexcept>();
    test_is_not_abstract<int(int) const noexcept>();
    test_is_not_abstract<int(int) const& noexcept>();
    test_is_not_abstract<int(int) const&& noexcept>();
    test_is_not_abstract<int(int) volatile noexcept>();
    test_is_not_abstract<int(int) volatile& noexcept>();
    test_is_not_abstract<int(int) volatile&& noexcept>();
    test_is_not_abstract<int(int) const volatile noexcept>();
    test_is_not_abstract<int(int) const volatile& noexcept>();
    test_is_not_abstract<int(int) const volatile&& noexcept>();

    test_is_not_abstract<int(...)>();
    test_is_not_abstract<int(...)&>();
    test_is_not_abstract<int(...) &&>();
    test_is_not_abstract<int(...) const>();
    test_is_not_abstract<int(...) const&>();
    test_is_not_abstract<int(...) const&&>();
    test_is_not_abstract<int(...) volatile>();
    test_is_not_abstract<int(...) volatile&>();
    test_is_not_abstract<int(...) volatile&&>();
    test_is_not_abstract<int(...) const volatile>();
    test_is_not_abstract<int(...) const volatile&>();
    test_is_not_abstract<int(...) const volatile&&>();
    test_is_not_abstract<int(...) noexcept>();
    test_is_not_abstract<int(...)& noexcept>();
    test_is_not_abstract<int(...)&& noexcept>();
    test_is_not_abstract<int(...) const noexcept>();
    test_is_not_abstract<int(...) const& noexcept>();
    test_is_not_abstract<int(...) const&& noexcept>();
    test_is_not_abstract<int(...) volatile noexcept>();
    test_is_not_abstract<int(...) volatile& noexcept>();
    test_is_not_abstract<int(...) volatile&& noexcept>();
    test_is_not_abstract<int(...) const volatile noexcept>();
    test_is_not_abstract<int(...) const volatile& noexcept>();
    test_is_not_abstract<int(...) const volatile&& noexcept>();

    test_is_not_abstract<int(int, ...)>();
    test_is_not_abstract<int(int, ...)&>();
    test_is_not_abstract<int(int, ...) &&>();
    test_is_not_abstract<int(int, ...) const>();
    test_is_not_abstract<int(int, ...) const&>();
    test_is_not_abstract<int(int, ...) const&&>();
    test_is_not_abstract<int(int, ...) volatile>();
    test_is_not_abstract<int(int, ...) volatile&>();
    test_is_not_abstract<int(int, ...) volatile&&>();
    test_is_not_abstract<int(int, ...) const volatile>();
    test_is_not_abstract<int(int, ...) const volatile&>();
    test_is_not_abstract<int(int, ...) const volatile&&>();
    test_is_not_abstract<int(int, ...) noexcept>();
    test_is_not_abstract<int(int, ...)& noexcept>();
    test_is_not_abstract<int(int, ...)&& noexcept>();
    test_is_not_abstract<int(int, ...) const noexcept>();
    test_is_not_abstract<int(int, ...) const& noexcept>();
    test_is_not_abstract<int(int, ...) const&& noexcept>();
    test_is_not_abstract<int(int, ...) volatile noexcept>();
    test_is_not_abstract<int(int, ...) volatile& noexcept>();
    test_is_not_abstract<int(int, ...) volatile&& noexcept>();
    test_is_not_abstract<int(int, ...) const volatile noexcept>();
    test_is_not_abstract<int(int, ...) const volatile& noexcept>();
    test_is_not_abstract<int(int, ...) const volatile&& noexcept>();

    test_is_not_abstract<void (*)()>();
    test_is_not_abstract<void (*)() noexcept>();

    test_is_not_abstract<void (*)(int)>();
    test_is_not_abstract<void (*)(int) noexcept>();

    test_is_not_abstract<void (*)(...)>();
    test_is_not_abstract<void (*)(...) noexcept>();

    test_is_not_abstract<void (*)(int, ...)>();
    test_is_not_abstract<void (*)(int, ...) noexcept>();

    test_is_not_abstract<int (*)()>();
    test_is_not_abstract<int (*)() noexcept>();

    test_is_not_abstract<int (*)(int)>();
    test_is_not_abstract<int (*)(int) noexcept>();

    test_is_not_abstract<int (*)(...)>();
    test_is_not_abstract<int (*)(...) noexcept>();

    test_is_not_abstract<int (*)(int, ...)>();
    test_is_not_abstract<int (*)(int, ...) noexcept>();

    test_is_not_abstract<void (&)()>();
    test_is_not_abstract<void (&)() noexcept>();

    test_is_not_abstract<void (&)(int)>();
    test_is_not_abstract<void (&)(int) noexcept>();

    test_is_not_abstract<void (&)(...)>();
    test_is_not_abstract<void (&)(...) noexcept>();

    test_is_not_abstract<void (&)(int, ...)>();
    test_is_not_abstract<void (&)(int, ...) noexcept>();

    test_is_not_abstract<int (&)()>();
    test_is_not_abstract<int (&)() noexcept>();

    test_is_not_abstract<int (&)(int)>();
    test_is_not_abstract<int (&)(int) noexcept>();

    test_is_not_abstract<int (&)(...)>();
    test_is_not_abstract<int (&)(...) noexcept>();

    test_is_not_abstract<int (&)(int, ...)>();
    test_is_not_abstract<int (&)(int, ...) noexcept>();

    test_is_not_abstract<void(&&)()>();
    test_is_not_abstract<void(&&)() noexcept>();

    test_is_not_abstract<void(&&)(int)>();
    test_is_not_abstract<void(&&)(int) noexcept>();

    test_is_not_abstract<void(&&)(...)>();
    test_is_not_abstract<void(&&)(...) noexcept>();

    test_is_not_abstract<void(&&)(int, ...)>();
    test_is_not_abstract<void(&&)(int, ...) noexcept>();

    test_is_not_abstract<int(&&)()>();
    test_is_not_abstract<int(&&)() noexcept>();

    test_is_not_abstract<int(&&)(int)>();
    test_is_not_abstract<int(&&)(int) noexcept>();

    test_is_not_abstract<int(&&)(...)>();
    test_is_not_abstract<int(&&)(...) noexcept>();

    test_is_not_abstract<int(&&)(int, ...)>();
    test_is_not_abstract<int(&&)(int, ...) noexcept>();

    test_is_not_abstract<void (Class::*)()>();
    test_is_not_abstract<void (Class::*)()&>();
    test_is_not_abstract<void (Class::*)() &&>();
    test_is_not_abstract<void (Class::*)() const>();
    test_is_not_abstract<void (Class::*)() const&>();
    test_is_not_abstract<void (Class::*)() const&&>();
    test_is_not_abstract<void (Class::*)() noexcept>();
    test_is_not_abstract<void (Class::*)()& noexcept>();
    test_is_not_abstract<void (Class::*)()&& noexcept>();
    test_is_not_abstract<void (Class::*)() const noexcept>();
    test_is_not_abstract<void (Class::*)() const& noexcept>();
    test_is_not_abstract<void (Class::*)() const&& noexcept>();

    test_is_not_abstract<void (Class::*)(int)>();
    test_is_not_abstract<void (Class::*)(int)&>();
    test_is_not_abstract<void (Class::*)(int) &&>();
    test_is_not_abstract<void (Class::*)(int) const>();
    test_is_not_abstract<void (Class::*)(int) const&>();
    test_is_not_abstract<void (Class::*)(int) const&&>();
    test_is_not_abstract<void (Class::*)(int) noexcept>();
    test_is_not_abstract<void (Class::*)(int)& noexcept>();
    test_is_not_abstract<void (Class::*)(int)&& noexcept>();
    test_is_not_abstract<void (Class::*)(int) const noexcept>();
    test_is_not_abstract<void (Class::*)(int) const& noexcept>();
    test_is_not_abstract<void (Class::*)(int) const&& noexcept>();

    test_is_not_abstract<void (Class::*)(...)>();
    test_is_not_abstract<void (Class::*)(...)&>();
    test_is_not_abstract<void (Class::*)(...) &&>();
    test_is_not_abstract<void (Class::*)(...) const>();
    test_is_not_abstract<void (Class::*)(...) const&>();
    test_is_not_abstract<void (Class::*)(...) const&&>();
    test_is_not_abstract<void (Class::*)(...) noexcept>();
    test_is_not_abstract<void (Class::*)(...)& noexcept>();
    test_is_not_abstract<void (Class::*)(...)&& noexcept>();
    test_is_not_abstract<void (Class::*)(...) const noexcept>();
    test_is_not_abstract<void (Class::*)(...) const& noexcept>();
    test_is_not_abstract<void (Class::*)(...) const&& noexcept>();

    test_is_not_abstract<void (Class::*)(int, ...)>();
    test_is_not_abstract<void (Class::*)(int, ...)&>();
    test_is_not_abstract<void (Class::*)(int, ...) &&>();
    test_is_not_abstract<void (Class::*)(int, ...) const>();
    test_is_not_abstract<void (Class::*)(int, ...) const&>();
    test_is_not_abstract<void (Class::*)(int, ...) const&&>();
    test_is_not_abstract<void (Class::*)(int, ...) noexcept>();
    test_is_not_abstract<void (Class::*)(int, ...)& noexcept>();
    test_is_not_abstract<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_abstract<void (Class::*)(int, ...) const noexcept>();
    test_is_not_abstract<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_abstract<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_abstract<int (Class::*)()>();
    test_is_not_abstract<int (Class::*)()&>();
    test_is_not_abstract<int (Class::*)() &&>();
    test_is_not_abstract<int (Class::*)() const>();
    test_is_not_abstract<int (Class::*)() const&>();
    test_is_not_abstract<int (Class::*)() const&&>();
    test_is_not_abstract<int (Class::*)() noexcept>();
    test_is_not_abstract<int (Class::*)()& noexcept>();
    test_is_not_abstract<int (Class::*)()&& noexcept>();
    test_is_not_abstract<int (Class::*)() const noexcept>();
    test_is_not_abstract<int (Class::*)() const& noexcept>();
    test_is_not_abstract<int (Class::*)() const&& noexcept>();

    test_is_not_abstract<int (Class::*)(int)>();
    test_is_not_abstract<int (Class::*)(int)&>();
    test_is_not_abstract<int (Class::*)(int) &&>();
    test_is_not_abstract<int (Class::*)(int) const>();
    test_is_not_abstract<int (Class::*)(int) const&>();
    test_is_not_abstract<int (Class::*)(int) const&&>();
    test_is_not_abstract<int (Class::*)(int) noexcept>();
    test_is_not_abstract<int (Class::*)(int)& noexcept>();
    test_is_not_abstract<int (Class::*)(int)&& noexcept>();
    test_is_not_abstract<int (Class::*)(int) const noexcept>();
    test_is_not_abstract<int (Class::*)(int) const& noexcept>();
    test_is_not_abstract<int (Class::*)(int) const&& noexcept>();

    test_is_not_abstract<int (Class::*)(...)>();
    test_is_not_abstract<int (Class::*)(...)&>();
    test_is_not_abstract<int (Class::*)(...) &&>();
    test_is_not_abstract<int (Class::*)(...) const>();
    test_is_not_abstract<int (Class::*)(...) const&>();
    test_is_not_abstract<int (Class::*)(...) const&&>();
    test_is_not_abstract<int (Class::*)(...) noexcept>();
    test_is_not_abstract<int (Class::*)(...)& noexcept>();
    test_is_not_abstract<int (Class::*)(...)&& noexcept>();
    test_is_not_abstract<int (Class::*)(...) const noexcept>();
    test_is_not_abstract<int (Class::*)(...) const& noexcept>();
    test_is_not_abstract<int (Class::*)(...) const&& noexcept>();

    test_is_not_abstract<int (Class::*)(int, ...)>();
    test_is_not_abstract<int (Class::*)(int, ...)&>();
    test_is_not_abstract<int (Class::*)(int, ...) &&>();
    test_is_not_abstract<int (Class::*)(int, ...) const>();
    test_is_not_abstract<int (Class::*)(int, ...) const&>();
    test_is_not_abstract<int (Class::*)(int, ...) const&&>();
    test_is_not_abstract<int (Class::*)(int, ...) noexcept>();
    test_is_not_abstract<int (Class::*)(int, ...)& noexcept>();
    test_is_not_abstract<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_abstract<int (Class::*)(int, ...) const noexcept>();
    test_is_not_abstract<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_abstract<int (Class::*)(int, ...) const&& noexcept>();
}
