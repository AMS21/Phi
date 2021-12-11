#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/integral_constant.hpp>
#include <phi/type_traits/underlying_type.hpp>
#include <phi/type_traits/void_t.hpp>
#include <climits>
#include <type_traits>
#include <vector>

template <typename, class = phi::void_t<>>
struct has_type_member : public phi::false_type
{};

template <typename T>
struct has_type_member<T, phi::void_t<typename phi::underlying_type<T>::type>>
    : public phi::true_type
{};

template <typename T, typename U>
void test_underlying_type_impl()
{
    STATIC_REQUIRE(has_type_member<T>::value);

    CHECK_SAME_TYPE(typename phi::underlying_type<T>::type, U);
    CHECK_SAME_TYPE(phi::underlying_type_t<T>, U);

    // Standard compatbililty
    CHECK_SAME_TYPE(typename std::underlying_type<T>::type, U);
}

template <typename T, typename U>
void test_underlying_type()
{
    test_underlying_type_impl<T, U>();
    test_underlying_type_impl<const T, U>();
    test_underlying_type_impl<volatile T, U>();
    test_underlying_type_impl<const volatile T, U>();
}

template <typename T>
void test_no_underlying_type()
{
    STATIC_REQUIRE_FALSE(has_type_member<T>::value);
    STATIC_REQUIRE_FALSE(has_type_member<const T>::value);
    STATIC_REQUIRE_FALSE(has_type_member<volatile T>::value);
    STATIC_REQUIRE_FALSE(has_type_member<const volatile T>::value);
}

enum E
{
    V = INT_MIN
};

enum F
{
    W = UINT_MAX
};

enum G : char
{
};

enum class H
{
    red,
    green = 20,
    blue
};

enum class I : long
{
    red,
    green = 20,
    blue
};

enum struct J
{
    red,
    green = 20,
    blue
};

enum struct K : short
{
    red,
    green = 20,
    blue
};

TEST_CASE("is_void")
{
    test_underlying_type<E, int>();
#if PHI_COMPILER_IS(MSVC)
    test_underlying_type<F, int>();
#else
    test_underlying_type<F, unsigned>();
#endif
    test_underlying_type<G, char>();
    test_underlying_type<H, int>();
    test_underlying_type<I, long>();
    test_underlying_type<J, int>();
    test_underlying_type<K, short>();

    test_no_underlying_type<void>();
    test_no_underlying_type<phi::nullptr_t>();
    test_no_underlying_type<bool>();
    test_no_underlying_type<char>();
    test_no_underlying_type<signed char>();
    test_no_underlying_type<unsigned char>();
    test_no_underlying_type<short>();
    test_no_underlying_type<unsigned short>();
    test_no_underlying_type<int>();
    test_no_underlying_type<unsigned int>();
    test_no_underlying_type<long>();
    test_no_underlying_type<unsigned long>();
    test_no_underlying_type<long long>();
    test_no_underlying_type<unsigned long long>();
    test_no_underlying_type<float>();
    test_no_underlying_type<double>();
    test_no_underlying_type<long double>();
    test_no_underlying_type<char8_t>();
    test_no_underlying_type<char16_t>();
    test_no_underlying_type<char32_t>();
    test_no_underlying_type<wchar_t>();

    test_no_underlying_type<phi::boolean>();
    test_no_underlying_type<phi::integer<signed char>>();
    test_no_underlying_type<phi::integer<unsigned char>>();
    test_no_underlying_type<phi::integer<short>>();
    test_no_underlying_type<phi::integer<unsigned short>>();
    test_no_underlying_type<phi::integer<int>>();
    test_no_underlying_type<phi::integer<unsigned int>>();
    test_no_underlying_type<phi::integer<long>>();
    test_no_underlying_type<phi::integer<unsigned long>>();
    test_no_underlying_type<phi::integer<long long>>();
    test_no_underlying_type<phi::integer<unsigned long long>>();
    test_no_underlying_type<phi::floating_point<float>>();
    test_no_underlying_type<phi::floating_point<double>>();
    test_no_underlying_type<phi::floating_point<long double>>();

    test_no_underlying_type<std::vector<int>>();
    test_no_underlying_type<phi::scope_ptr<int>>();

    test_no_underlying_type<int&>();
    test_no_underlying_type<const int&>();
    test_no_underlying_type<volatile int&>();
    test_no_underlying_type<const volatile int&>();
    test_no_underlying_type<int&&>();
    test_no_underlying_type<const int&&>();
    test_no_underlying_type<volatile int&&>();
    test_no_underlying_type<const volatile int&&>();
    test_no_underlying_type<int*>();
    test_no_underlying_type<const int*>();
    test_no_underlying_type<volatile int*>();
    test_no_underlying_type<const volatile int*>();
    test_no_underlying_type<int**>();
    test_no_underlying_type<const int**>();
    test_no_underlying_type<volatile int**>();
    test_no_underlying_type<const volatile int**>();
    test_no_underlying_type<int*&>();
    test_no_underlying_type<const int*&>();
    test_no_underlying_type<volatile int*&>();
    test_no_underlying_type<const volatile int*&>();
    test_no_underlying_type<int*&&>();
    test_no_underlying_type<const int*&&>();
    test_no_underlying_type<volatile int*&&>();
    test_no_underlying_type<const volatile int*&&>();
    test_no_underlying_type<void*>();
    test_no_underlying_type<char[3]>();
    test_no_underlying_type<char[]>();
    test_no_underlying_type<char* [3]>();
    test_no_underlying_type<char*[]>();
    test_no_underlying_type<int(*)[3]>();
    test_no_underlying_type<int(*)[]>();
    test_no_underlying_type<int(&)[3]>();
    test_no_underlying_type<int(&)[]>();
    test_no_underlying_type<int(&&)[3]>();
    test_no_underlying_type<int(&&)[]>();
    test_no_underlying_type<char[3][2]>();
    test_no_underlying_type<char[][2]>();
    test_no_underlying_type<char* [3][2]>();
    test_no_underlying_type<char*[][2]>();
    test_no_underlying_type<int(*)[3][2]>();
    test_no_underlying_type<int(*)[][2]>();
    test_no_underlying_type<int(&)[3][2]>();
    test_no_underlying_type<int(&)[][2]>();
    test_no_underlying_type<int(&&)[3][2]>();
    test_no_underlying_type<int(&&)[][2]>();
    test_no_underlying_type<Class>();
    test_no_underlying_type<Class[]>();
    test_no_underlying_type<Class[2]>();
    test_no_underlying_type<Template<void>>();
    test_no_underlying_type<Template<int>>();
    test_no_underlying_type<Template<Class>>();
    test_no_underlying_type<Template<incomplete_type>>();
    test_no_underlying_type<VariadicTemplate<>>();
    test_no_underlying_type<VariadicTemplate<void>>();
    test_no_underlying_type<VariadicTemplate<int>>();
    test_no_underlying_type<VariadicTemplate<Class>>();
    test_no_underlying_type<VariadicTemplate<incomplete_type>>();
    test_no_underlying_type<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_no_underlying_type<PublicDerviedFromTemplate<Base>>();
    test_no_underlying_type<PublicDerviedFromTemplate<Derived>>();
    test_no_underlying_type<PublicDerviedFromTemplate<Class>>();
    test_no_underlying_type<PrivateDerviedFromTemplate<Base>>();
    test_no_underlying_type<PrivateDerviedFromTemplate<Derived>>();
    test_no_underlying_type<PrivateDerviedFromTemplate<Class>>();
    test_no_underlying_type<ProtectedDerviedFromTemplate<Base>>();
    test_no_underlying_type<ProtectedDerviedFromTemplate<Derived>>();
    test_no_underlying_type<ProtectedDerviedFromTemplate<Class>>();
    test_no_underlying_type<Union>();
    test_no_underlying_type<NonEmptyUnion>();
    test_no_underlying_type<Empty>();
    test_no_underlying_type<NotEmpty>();
    test_no_underlying_type<bit_zero>();
    test_no_underlying_type<bit_one>();
    test_no_underlying_type<Base>();
    test_no_underlying_type<Derived>();
    test_no_underlying_type<Abstract>();
    test_no_underlying_type<PublicAbstract>();
    test_no_underlying_type<PrivateAbstract>();
    test_no_underlying_type<ProtectedAbstract>();
    test_no_underlying_type<AbstractTemplate<int>>();
    test_no_underlying_type<AbstractTemplate<double>>();
    test_no_underlying_type<AbstractTemplate<Class>>();
    test_no_underlying_type<AbstractTemplate<incomplete_type>>();
    test_no_underlying_type<Final>();
    test_no_underlying_type<PublicDestructor>();
    test_no_underlying_type<ProtectedDestructor>();
    test_no_underlying_type<PrivateDestructor>();
    test_no_underlying_type<VirtualPublicDestructor>();
    test_no_underlying_type<VirtualProtectedDestructor>();
    test_no_underlying_type<VirtualPrivateDestructor>();
    test_no_underlying_type<PurePublicDestructor>();
    test_no_underlying_type<PureProtectedDestructor>();
    test_no_underlying_type<PurePrivateDestructor>();
    test_no_underlying_type<DeletedPublicDestructor>();
    test_no_underlying_type<DeletedProtectedDestructor>();
    test_no_underlying_type<DeletedPrivateDestructor>();
    test_no_underlying_type<DeletedVirtualPublicDestructor>();
    test_no_underlying_type<DeletedVirtualProtectedDestructor>();
    test_no_underlying_type<DeletedVirtualPrivateDestructor>();
#if PHI_COMPILER_IS(MSVC)
    test_underlying_type<Enum, int>();
#else
    test_underlying_type<Enum, unsigned int>();
#endif
    test_underlying_type<EnumSigned, int>();
    test_underlying_type<EnumUnsigned, unsigned int>();
    test_underlying_type<EnumClass, int>();
    test_underlying_type<EnumStruct, int>();
    test_no_underlying_type<Function>();
    test_no_underlying_type<FunctionPtr>();
    test_no_underlying_type<MemberObjectPtr>();
    test_no_underlying_type<MemberFunctionPtr>();
    test_no_underlying_type<incomplete_type>();
    test_no_underlying_type<IncompleteTemplate<void>>();
    test_no_underlying_type<IncompleteTemplate<int>>();
    test_no_underlying_type<IncompleteTemplate<Class>>();
    test_no_underlying_type<IncompleteTemplate<incomplete_type>>();
    test_no_underlying_type<IncompleteVariadicTemplate<>>();
    test_no_underlying_type<IncompleteVariadicTemplate<void>>();
    test_no_underlying_type<IncompleteVariadicTemplate<int>>();
    test_no_underlying_type<IncompleteVariadicTemplate<Class>>();
    test_no_underlying_type<IncompleteVariadicTemplate<incomplete_type>>();
    test_no_underlying_type<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_no_underlying_type<int Class::*>();
    test_no_underlying_type<float Class::*>();
    test_no_underlying_type<void * Class::*>();
    test_no_underlying_type<int * Class::*>();
    test_no_underlying_type<int Class::*&>();
    test_no_underlying_type<float Class::*&>();
    test_no_underlying_type<void * Class::*&>();
    test_no_underlying_type<int * Class::*&>();
    test_no_underlying_type<int Class::*&&>();
    test_no_underlying_type<float Class::*&&>();
    test_no_underlying_type<void * Class::*&&>();
    test_no_underlying_type<int * Class::*&&>();
    test_no_underlying_type<int Class::*const>();
    test_no_underlying_type<float Class::*const>();
    test_no_underlying_type<void * Class::*const>();
    test_no_underlying_type<int Class::*const&>();
    test_no_underlying_type<float Class::*const&>();
    test_no_underlying_type<void * Class::*const&>();
    test_no_underlying_type<int Class::*const&&>();
    test_no_underlying_type<float Class::*const&&>();
    test_no_underlying_type<void * Class::*const&&>();
    test_no_underlying_type<int Class::*volatile>();
    test_no_underlying_type<float Class::*volatile>();
    test_no_underlying_type<void * Class::*volatile>();
    test_no_underlying_type<int Class::*volatile&>();
    test_no_underlying_type<float Class::*volatile&>();
    test_no_underlying_type<void * Class::*volatile&>();
    test_no_underlying_type<int Class::*volatile&&>();
    test_no_underlying_type<float Class::*volatile&&>();
    test_no_underlying_type<void * Class::*volatile&&>();
    test_no_underlying_type<int Class::*const volatile>();
    test_no_underlying_type<float Class::*const volatile>();
    test_no_underlying_type<void * Class::*const volatile>();
    test_no_underlying_type<int Class::*const volatile&>();
    test_no_underlying_type<float Class::*const volatile&>();
    test_no_underlying_type<void * Class::*const volatile&>();
    test_no_underlying_type<int Class::*const volatile&&>();
    test_no_underlying_type<float Class::*const volatile&&>();
    test_no_underlying_type<void * Class::*const volatile&&>();
    test_no_underlying_type<NonCopyable>();
    test_no_underlying_type<NonMoveable>();
    test_no_underlying_type<NonConstructible>();
    test_no_underlying_type<Tracked>();
    test_no_underlying_type<TrapConstructible>();
    test_no_underlying_type<TrapImplicitConversion>();
    test_no_underlying_type<TrapComma>();
    test_no_underlying_type<TrapCall>();
    test_no_underlying_type<TrapSelfAssign>();
    test_no_underlying_type<TrapDeref>();
    test_no_underlying_type<TrapArraySubscript>();

    test_no_underlying_type<void()>();
    test_no_underlying_type<void()&>();
    test_no_underlying_type<void() &&>();
    test_no_underlying_type<void() const>();
    test_no_underlying_type<void() const&>();
    test_no_underlying_type<void() const&&>();
    test_no_underlying_type<void() volatile>();
    test_no_underlying_type<void() volatile&>();
    test_no_underlying_type<void() volatile&&>();
    test_no_underlying_type<void() const volatile>();
    test_no_underlying_type<void() const volatile&>();
    test_no_underlying_type<void() const volatile&&>();
    test_no_underlying_type<void() noexcept>();
    test_no_underlying_type<void()& noexcept>();
    test_no_underlying_type<void()&& noexcept>();
    test_no_underlying_type<void() const noexcept>();
    test_no_underlying_type<void() const& noexcept>();
    test_no_underlying_type<void() const&& noexcept>();
    test_no_underlying_type<void() volatile noexcept>();
    test_no_underlying_type<void() volatile& noexcept>();
    test_no_underlying_type<void() volatile&& noexcept>();
    test_no_underlying_type<void() const volatile noexcept>();
    test_no_underlying_type<void() const volatile& noexcept>();
    test_no_underlying_type<void() const volatile&& noexcept>();

    test_no_underlying_type<void(int)>();
    test_no_underlying_type<void(int)&>();
    test_no_underlying_type<void(int) &&>();
    test_no_underlying_type<void(int) const>();
    test_no_underlying_type<void(int) const&>();
    test_no_underlying_type<void(int) const&&>();
    test_no_underlying_type<void(int) volatile>();
    test_no_underlying_type<void(int) volatile&>();
    test_no_underlying_type<void(int) volatile&&>();
    test_no_underlying_type<void(int) const volatile>();
    test_no_underlying_type<void(int) const volatile&>();
    test_no_underlying_type<void(int) const volatile&&>();
    test_no_underlying_type<void(int) noexcept>();
    test_no_underlying_type<void(int)& noexcept>();
    test_no_underlying_type<void(int)&& noexcept>();
    test_no_underlying_type<void(int) const noexcept>();
    test_no_underlying_type<void(int) const& noexcept>();
    test_no_underlying_type<void(int) const&& noexcept>();
    test_no_underlying_type<void(int) volatile noexcept>();
    test_no_underlying_type<void(int) volatile& noexcept>();
    test_no_underlying_type<void(int) volatile&& noexcept>();
    test_no_underlying_type<void(int) const volatile noexcept>();
    test_no_underlying_type<void(int) const volatile& noexcept>();
    test_no_underlying_type<void(int) const volatile&& noexcept>();

    test_no_underlying_type<void(...)>();
    test_no_underlying_type<void(...)&>();
    test_no_underlying_type<void(...) &&>();
    test_no_underlying_type<void(...) const>();
    test_no_underlying_type<void(...) const&>();
    test_no_underlying_type<void(...) const&&>();
    test_no_underlying_type<void(...) volatile>();
    test_no_underlying_type<void(...) volatile&>();
    test_no_underlying_type<void(...) volatile&&>();
    test_no_underlying_type<void(...) const volatile>();
    test_no_underlying_type<void(...) const volatile&>();
    test_no_underlying_type<void(...) const volatile&&>();
    test_no_underlying_type<void(...) noexcept>();
    test_no_underlying_type<void(...)& noexcept>();
    test_no_underlying_type<void(...)&& noexcept>();
    test_no_underlying_type<void(...) const noexcept>();
    test_no_underlying_type<void(...) const& noexcept>();
    test_no_underlying_type<void(...) const&& noexcept>();
    test_no_underlying_type<void(...) volatile noexcept>();
    test_no_underlying_type<void(...) volatile& noexcept>();
    test_no_underlying_type<void(...) volatile&& noexcept>();
    test_no_underlying_type<void(...) const volatile noexcept>();
    test_no_underlying_type<void(...) const volatile& noexcept>();
    test_no_underlying_type<void(...) const volatile&& noexcept>();

    test_no_underlying_type<void(int, ...)>();
    test_no_underlying_type<void(int, ...)&>();
    test_no_underlying_type<void(int, ...) &&>();
    test_no_underlying_type<void(int, ...) const>();
    test_no_underlying_type<void(int, ...) const&>();
    test_no_underlying_type<void(int, ...) const&&>();
    test_no_underlying_type<void(int, ...) volatile>();
    test_no_underlying_type<void(int, ...) volatile&>();
    test_no_underlying_type<void(int, ...) volatile&&>();
    test_no_underlying_type<void(int, ...) const volatile>();
    test_no_underlying_type<void(int, ...) const volatile&>();
    test_no_underlying_type<void(int, ...) const volatile&&>();
    test_no_underlying_type<void(int, ...) noexcept>();
    test_no_underlying_type<void(int, ...)& noexcept>();
    test_no_underlying_type<void(int, ...)&& noexcept>();
    test_no_underlying_type<void(int, ...) const noexcept>();
    test_no_underlying_type<void(int, ...) const& noexcept>();
    test_no_underlying_type<void(int, ...) const&& noexcept>();
    test_no_underlying_type<void(int, ...) volatile noexcept>();
    test_no_underlying_type<void(int, ...) volatile& noexcept>();
    test_no_underlying_type<void(int, ...) volatile&& noexcept>();
    test_no_underlying_type<void(int, ...) const volatile noexcept>();
    test_no_underlying_type<void(int, ...) const volatile& noexcept>();
    test_no_underlying_type<void(int, ...) const volatile&& noexcept>();

    test_no_underlying_type<int()>();
    test_no_underlying_type<int()&>();
    test_no_underlying_type<int() &&>();
    test_no_underlying_type<int() const>();
    test_no_underlying_type<int() const&>();
    test_no_underlying_type<int() const&&>();
    test_no_underlying_type<int() volatile>();
    test_no_underlying_type<int() volatile&>();
    test_no_underlying_type<int() volatile&&>();
    test_no_underlying_type<int() const volatile>();
    test_no_underlying_type<int() const volatile&>();
    test_no_underlying_type<int() const volatile&&>();
    test_no_underlying_type<int() noexcept>();
    test_no_underlying_type<int()& noexcept>();
    test_no_underlying_type<int()&& noexcept>();
    test_no_underlying_type<int() const noexcept>();
    test_no_underlying_type<int() const& noexcept>();
    test_no_underlying_type<int() const&& noexcept>();
    test_no_underlying_type<int() volatile noexcept>();
    test_no_underlying_type<int() volatile& noexcept>();
    test_no_underlying_type<int() volatile&& noexcept>();
    test_no_underlying_type<int() const volatile noexcept>();
    test_no_underlying_type<int() const volatile& noexcept>();
    test_no_underlying_type<int() const volatile&& noexcept>();

    test_no_underlying_type<int(int)>();
    test_no_underlying_type<int(int)&>();
    test_no_underlying_type<int(int) &&>();
    test_no_underlying_type<int(int) const>();
    test_no_underlying_type<int(int) const&>();
    test_no_underlying_type<int(int) const&&>();
    test_no_underlying_type<int(int) volatile>();
    test_no_underlying_type<int(int) volatile&>();
    test_no_underlying_type<int(int) volatile&&>();
    test_no_underlying_type<int(int) const volatile>();
    test_no_underlying_type<int(int) const volatile&>();
    test_no_underlying_type<int(int) const volatile&&>();
    test_no_underlying_type<int(int) noexcept>();
    test_no_underlying_type<int(int)& noexcept>();
    test_no_underlying_type<int(int)&& noexcept>();
    test_no_underlying_type<int(int) const noexcept>();
    test_no_underlying_type<int(int) const& noexcept>();
    test_no_underlying_type<int(int) const&& noexcept>();
    test_no_underlying_type<int(int) volatile noexcept>();
    test_no_underlying_type<int(int) volatile& noexcept>();
    test_no_underlying_type<int(int) volatile&& noexcept>();
    test_no_underlying_type<int(int) const volatile noexcept>();
    test_no_underlying_type<int(int) const volatile& noexcept>();
    test_no_underlying_type<int(int) const volatile&& noexcept>();

    test_no_underlying_type<int(...)>();
    test_no_underlying_type<int(...)&>();
    test_no_underlying_type<int(...) &&>();
    test_no_underlying_type<int(...) const>();
    test_no_underlying_type<int(...) const&>();
    test_no_underlying_type<int(...) const&&>();
    test_no_underlying_type<int(...) volatile>();
    test_no_underlying_type<int(...) volatile&>();
    test_no_underlying_type<int(...) volatile&&>();
    test_no_underlying_type<int(...) const volatile>();
    test_no_underlying_type<int(...) const volatile&>();
    test_no_underlying_type<int(...) const volatile&&>();
    test_no_underlying_type<int(...) noexcept>();
    test_no_underlying_type<int(...)& noexcept>();
    test_no_underlying_type<int(...)&& noexcept>();
    test_no_underlying_type<int(...) const noexcept>();
    test_no_underlying_type<int(...) const& noexcept>();
    test_no_underlying_type<int(...) const&& noexcept>();
    test_no_underlying_type<int(...) volatile noexcept>();
    test_no_underlying_type<int(...) volatile& noexcept>();
    test_no_underlying_type<int(...) volatile&& noexcept>();
    test_no_underlying_type<int(...) const volatile noexcept>();
    test_no_underlying_type<int(...) const volatile& noexcept>();
    test_no_underlying_type<int(...) const volatile&& noexcept>();

    test_no_underlying_type<int(int, ...)>();
    test_no_underlying_type<int(int, ...)&>();
    test_no_underlying_type<int(int, ...) &&>();
    test_no_underlying_type<int(int, ...) const>();
    test_no_underlying_type<int(int, ...) const&>();
    test_no_underlying_type<int(int, ...) const&&>();
    test_no_underlying_type<int(int, ...) volatile>();
    test_no_underlying_type<int(int, ...) volatile&>();
    test_no_underlying_type<int(int, ...) volatile&&>();
    test_no_underlying_type<int(int, ...) const volatile>();
    test_no_underlying_type<int(int, ...) const volatile&>();
    test_no_underlying_type<int(int, ...) const volatile&&>();
    test_no_underlying_type<int(int, ...) noexcept>();
    test_no_underlying_type<int(int, ...)& noexcept>();
    test_no_underlying_type<int(int, ...)&& noexcept>();
    test_no_underlying_type<int(int, ...) const noexcept>();
    test_no_underlying_type<int(int, ...) const& noexcept>();
    test_no_underlying_type<int(int, ...) const&& noexcept>();
    test_no_underlying_type<int(int, ...) volatile noexcept>();
    test_no_underlying_type<int(int, ...) volatile& noexcept>();
    test_no_underlying_type<int(int, ...) volatile&& noexcept>();
    test_no_underlying_type<int(int, ...) const volatile noexcept>();
    test_no_underlying_type<int(int, ...) const volatile& noexcept>();
    test_no_underlying_type<int(int, ...) const volatile&& noexcept>();

    test_no_underlying_type<void (*)()>();
    test_no_underlying_type<void (*)() noexcept>();

    test_no_underlying_type<void (*)(int)>();
    test_no_underlying_type<void (*)(int) noexcept>();

    test_no_underlying_type<void (*)(...)>();
    test_no_underlying_type<void (*)(...) noexcept>();

    test_no_underlying_type<void (*)(int, ...)>();
    test_no_underlying_type<void (*)(int, ...) noexcept>();

    test_no_underlying_type<int (*)()>();
    test_no_underlying_type<int (*)() noexcept>();

    test_no_underlying_type<int (*)(int)>();
    test_no_underlying_type<int (*)(int) noexcept>();

    test_no_underlying_type<int (*)(...)>();
    test_no_underlying_type<int (*)(...) noexcept>();

    test_no_underlying_type<int (*)(int, ...)>();
    test_no_underlying_type<int (*)(int, ...) noexcept>();

    test_no_underlying_type<void (&)()>();
    test_no_underlying_type<void (&)() noexcept>();

    test_no_underlying_type<void (&)(int)>();
    test_no_underlying_type<void (&)(int) noexcept>();

    test_no_underlying_type<void (&)(...)>();
    test_no_underlying_type<void (&)(...) noexcept>();

    test_no_underlying_type<void (&)(int, ...)>();
    test_no_underlying_type<void (&)(int, ...) noexcept>();

    test_no_underlying_type<int (&)()>();
    test_no_underlying_type<int (&)() noexcept>();

    test_no_underlying_type<int (&)(int)>();
    test_no_underlying_type<int (&)(int) noexcept>();

    test_no_underlying_type<int (&)(...)>();
    test_no_underlying_type<int (&)(...) noexcept>();

    test_no_underlying_type<int (&)(int, ...)>();
    test_no_underlying_type<int (&)(int, ...) noexcept>();

    test_no_underlying_type<void(&&)()>();
    test_no_underlying_type<void(&&)() noexcept>();

    test_no_underlying_type<void(&&)(int)>();
    test_no_underlying_type<void(&&)(int) noexcept>();

    test_no_underlying_type<void(&&)(...)>();
    test_no_underlying_type<void(&&)(...) noexcept>();

    test_no_underlying_type<void(&&)(int, ...)>();
    test_no_underlying_type<void(&&)(int, ...) noexcept>();

    test_no_underlying_type<int(&&)()>();
    test_no_underlying_type<int(&&)() noexcept>();

    test_no_underlying_type<int(&&)(int)>();
    test_no_underlying_type<int(&&)(int) noexcept>();

    test_no_underlying_type<int(&&)(...)>();
    test_no_underlying_type<int(&&)(...) noexcept>();

    test_no_underlying_type<int(&&)(int, ...)>();
    test_no_underlying_type<int(&&)(int, ...) noexcept>();

    test_no_underlying_type<void (Class::*)()>();
    test_no_underlying_type<void (Class::*)()&>();
    test_no_underlying_type<void (Class::*)() &&>();
    test_no_underlying_type<void (Class::*)() const>();
    test_no_underlying_type<void (Class::*)() const&>();
    test_no_underlying_type<void (Class::*)() const&&>();
    test_no_underlying_type<void (Class::*)() noexcept>();
    test_no_underlying_type<void (Class::*)()& noexcept>();
    test_no_underlying_type<void (Class::*)()&& noexcept>();
    test_no_underlying_type<void (Class::*)() const noexcept>();
    test_no_underlying_type<void (Class::*)() const& noexcept>();
    test_no_underlying_type<void (Class::*)() const&& noexcept>();

    test_no_underlying_type<void (Class::*)(int)>();
    test_no_underlying_type<void (Class::*)(int)&>();
    test_no_underlying_type<void (Class::*)(int) &&>();
    test_no_underlying_type<void (Class::*)(int) const>();
    test_no_underlying_type<void (Class::*)(int) const&>();
    test_no_underlying_type<void (Class::*)(int) const&&>();
    test_no_underlying_type<void (Class::*)(int) noexcept>();
    test_no_underlying_type<void (Class::*)(int)& noexcept>();
    test_no_underlying_type<void (Class::*)(int)&& noexcept>();
    test_no_underlying_type<void (Class::*)(int) const noexcept>();
    test_no_underlying_type<void (Class::*)(int) const& noexcept>();
    test_no_underlying_type<void (Class::*)(int) const&& noexcept>();

    test_no_underlying_type<void (Class::*)(...)>();
    test_no_underlying_type<void (Class::*)(...)&>();
    test_no_underlying_type<void (Class::*)(...) &&>();
    test_no_underlying_type<void (Class::*)(...) const>();
    test_no_underlying_type<void (Class::*)(...) const&>();
    test_no_underlying_type<void (Class::*)(...) const&&>();
    test_no_underlying_type<void (Class::*)(...) noexcept>();
    test_no_underlying_type<void (Class::*)(...)& noexcept>();
    test_no_underlying_type<void (Class::*)(...)&& noexcept>();
    test_no_underlying_type<void (Class::*)(...) const noexcept>();
    test_no_underlying_type<void (Class::*)(...) const& noexcept>();
    test_no_underlying_type<void (Class::*)(...) const&& noexcept>();

    test_no_underlying_type<void (Class::*)(int, ...)>();
    test_no_underlying_type<void (Class::*)(int, ...)&>();
    test_no_underlying_type<void (Class::*)(int, ...) &&>();
    test_no_underlying_type<void (Class::*)(int, ...) const>();
    test_no_underlying_type<void (Class::*)(int, ...) const&>();
    test_no_underlying_type<void (Class::*)(int, ...) const&&>();
    test_no_underlying_type<void (Class::*)(int, ...) noexcept>();
    test_no_underlying_type<void (Class::*)(int, ...)& noexcept>();
    test_no_underlying_type<void (Class::*)(int, ...)&& noexcept>();
    test_no_underlying_type<void (Class::*)(int, ...) const noexcept>();
    test_no_underlying_type<void (Class::*)(int, ...) const& noexcept>();
    test_no_underlying_type<void (Class::*)(int, ...) const&& noexcept>();

    test_no_underlying_type<int (Class::*)()>();
    test_no_underlying_type<int (Class::*)()&>();
    test_no_underlying_type<int (Class::*)() &&>();
    test_no_underlying_type<int (Class::*)() const>();
    test_no_underlying_type<int (Class::*)() const&>();
    test_no_underlying_type<int (Class::*)() const&&>();
    test_no_underlying_type<int (Class::*)() noexcept>();
    test_no_underlying_type<int (Class::*)()& noexcept>();
    test_no_underlying_type<int (Class::*)()&& noexcept>();
    test_no_underlying_type<int (Class::*)() const noexcept>();
    test_no_underlying_type<int (Class::*)() const& noexcept>();
    test_no_underlying_type<int (Class::*)() const&& noexcept>();

    test_no_underlying_type<int (Class::*)(int)>();
    test_no_underlying_type<int (Class::*)(int)&>();
    test_no_underlying_type<int (Class::*)(int) &&>();
    test_no_underlying_type<int (Class::*)(int) const>();
    test_no_underlying_type<int (Class::*)(int) const&>();
    test_no_underlying_type<int (Class::*)(int) const&&>();
    test_no_underlying_type<int (Class::*)(int) noexcept>();
    test_no_underlying_type<int (Class::*)(int)& noexcept>();
    test_no_underlying_type<int (Class::*)(int)&& noexcept>();
    test_no_underlying_type<int (Class::*)(int) const noexcept>();
    test_no_underlying_type<int (Class::*)(int) const& noexcept>();
    test_no_underlying_type<int (Class::*)(int) const&& noexcept>();

    test_no_underlying_type<int (Class::*)(...)>();
    test_no_underlying_type<int (Class::*)(...)&>();
    test_no_underlying_type<int (Class::*)(...) &&>();
    test_no_underlying_type<int (Class::*)(...) const>();
    test_no_underlying_type<int (Class::*)(...) const&>();
    test_no_underlying_type<int (Class::*)(...) const&&>();
    test_no_underlying_type<int (Class::*)(...) noexcept>();
    test_no_underlying_type<int (Class::*)(...)& noexcept>();
    test_no_underlying_type<int (Class::*)(...)&& noexcept>();
    test_no_underlying_type<int (Class::*)(...) const noexcept>();
    test_no_underlying_type<int (Class::*)(...) const& noexcept>();
    test_no_underlying_type<int (Class::*)(...) const&& noexcept>();

    test_no_underlying_type<int (Class::*)(int, ...)>();
    test_no_underlying_type<int (Class::*)(int, ...)&>();
    test_no_underlying_type<int (Class::*)(int, ...) &&>();
    test_no_underlying_type<int (Class::*)(int, ...) const>();
    test_no_underlying_type<int (Class::*)(int, ...) const&>();
    test_no_underlying_type<int (Class::*)(int, ...) const&&>();
    test_no_underlying_type<int (Class::*)(int, ...) noexcept>();
    test_no_underlying_type<int (Class::*)(int, ...)& noexcept>();
    test_no_underlying_type<int (Class::*)(int, ...)&& noexcept>();
    test_no_underlying_type<int (Class::*)(int, ...) const noexcept>();
    test_no_underlying_type<int (Class::*)(int, ...) const& noexcept>();
    test_no_underlying_type<int (Class::*)(int, ...) const&& noexcept>();
}
