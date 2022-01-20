#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/declval.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/void_t.hpp>
#include <vector>

template <typename T>
void test_void_t()
{
    CHECK_SAME_TYPE(void, phi::void_t<T>);
    CHECK_SAME_TYPE(void, phi::void_t<const T>);
    CHECK_SAME_TYPE(void, phi::void_t<volatile T>);
    CHECK_SAME_TYPE(void, phi::void_t<const volatile T>);
}

template <typename T, typename U>
void test_void_t()
{
    CHECK_SAME_TYPE(void, phi::void_t<T, U>);
    CHECK_SAME_TYPE(void, phi::void_t<T, const U>);
    CHECK_SAME_TYPE(void, phi::void_t<T, volatile U>);
    CHECK_SAME_TYPE(void, phi::void_t<T, const volatile U>);

    CHECK_SAME_TYPE(void, phi::void_t<const T, U>);
    CHECK_SAME_TYPE(void, phi::void_t<const T, const U>);
    CHECK_SAME_TYPE(void, phi::void_t<const T, volatile U>);
    CHECK_SAME_TYPE(void, phi::void_t<const T, const volatile U>);

    CHECK_SAME_TYPE(void, phi::void_t<volatile T, U>);
    CHECK_SAME_TYPE(void, phi::void_t<volatile T, const U>);
    CHECK_SAME_TYPE(void, phi::void_t<volatile T, volatile U>);
    CHECK_SAME_TYPE(void, phi::void_t<volatile T, const volatile U>);

    CHECK_SAME_TYPE(void, phi::void_t<const volatile T, U>);
    CHECK_SAME_TYPE(void, phi::void_t<const volatile T, const U>);
    CHECK_SAME_TYPE(void, phi::void_t<const volatile T, volatile U>);
    CHECK_SAME_TYPE(void, phi::void_t<const volatile T, const volatile U>);
}

struct X
{};

X operator+(const X& x)
{
    return x;
}

template <typename T, typename U = phi::void_t<>>
struct has_unary_plus : phi::false_type
{};

template <typename T>
struct has_unary_plus<T, phi::void_t<decltype(+phi::declval<X>())>> : public phi::true_type
{};

TEST_CASE("is_void")
{
    STATIC_REQUIRE(has_unary_plus<X>::value);
    CHECK_SAME_TYPE(void, phi::void_t<>);

    test_void_t<void, void>();
    test_void_t<void, void*>();
    test_void_t<void, int>();
    test_void_t<void, double>();
    test_void_t<int, void>();
    test_void_t<double, void>();
    test_void_t<double, int>();
    test_void_t<int&, void>();
    test_void_t<int&, void*>();
    test_void_t<int&, int>();
    test_void_t<int&&, void>();
    test_void_t<int&&, void*>();
    test_void_t<int&&, int>();
    test_void_t<Class, void>();
    test_void_t<Class, int>();
    test_void_t<Class&, void>();
    test_void_t<Class&, int>();
    test_void_t<Class&&, void>();
    test_void_t<Class&&, int>();
    test_void_t<Class[], void>();
    test_void_t<Class[], int>();
    test_void_t<Class[3], void>();
    test_void_t<Class[3], int>();
    test_void_t<void*, void>();
    test_void_t<void*, void*>();
    test_void_t<void*, int&>();
    test_void_t<void*, int&&>();

    CHECK_SAME_TYPE(void, phi::void_t<int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, int, int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, double const&, Class, volatile int[], void>);
    CHECK_SAME_TYPE(
            void,
            phi::void_t<int, double const&, Class, volatile int[], void, int (*)(double, float)>);

    test_void_t<void>();
    test_void_t<phi::nullptr_t>();
    test_void_t<bool>();
    test_void_t<char>();
    test_void_t<signed char>();
    test_void_t<unsigned char>();
    test_void_t<short>();
    test_void_t<unsigned short>();
    test_void_t<int>();
    test_void_t<unsigned int>();
    test_void_t<long>();
    test_void_t<unsigned long>();
    test_void_t<long long>();
    test_void_t<unsigned long long>();
    test_void_t<float>();
    test_void_t<double>();
    test_void_t<long double>();
    test_void_t<char8_t>();
    test_void_t<char16_t>();
    test_void_t<char32_t>();
    test_void_t<wchar_t>();

    test_void_t<phi::boolean>();
    test_void_t<phi::integer<signed char>>();
    test_void_t<phi::integer<unsigned char>>();
    test_void_t<phi::integer<short>>();
    test_void_t<phi::integer<unsigned short>>();
    test_void_t<phi::integer<int>>();
    test_void_t<phi::integer<unsigned int>>();
    test_void_t<phi::integer<long>>();
    test_void_t<phi::integer<unsigned long>>();
    test_void_t<phi::integer<long long>>();
    test_void_t<phi::integer<unsigned long long>>();
    test_void_t<phi::floating_point<float>>();
    test_void_t<phi::floating_point<double>>();
    test_void_t<phi::floating_point<long double>>();

    test_void_t<std::vector<int>>();
    test_void_t<phi::scope_ptr<int>>();

    test_void_t<int&>();
    test_void_t<const int&>();
    test_void_t<volatile int&>();
    test_void_t<const volatile int&>();
    test_void_t<int&&>();
    test_void_t<const int&&>();
    test_void_t<volatile int&&>();
    test_void_t<const volatile int&&>();
    test_void_t<int*>();
    test_void_t<const int*>();
    test_void_t<volatile int*>();
    test_void_t<const volatile int*>();
    test_void_t<int**>();
    test_void_t<const int**>();
    test_void_t<volatile int**>();
    test_void_t<const volatile int**>();
    test_void_t<int*&>();
    test_void_t<const int*&>();
    test_void_t<volatile int*&>();
    test_void_t<const volatile int*&>();
    test_void_t<int*&&>();
    test_void_t<const int*&&>();
    test_void_t<volatile int*&&>();
    test_void_t<const volatile int*&&>();
    test_void_t<void*>();
    test_void_t<char[3]>();
    test_void_t<char[]>();
    test_void_t<char* [3]>();
    test_void_t<char*[]>();
    test_void_t<int(*)[3]>();
    test_void_t<int(*)[]>();
    test_void_t<int(&)[3]>();
    test_void_t<int(&)[]>();
    test_void_t<int(&&)[3]>();
    test_void_t<int(&&)[]>();
    test_void_t<char[3][2]>();
    test_void_t<char[][2]>();
    test_void_t<char* [3][2]>();
    test_void_t<char*[][2]>();
    test_void_t<int(*)[3][2]>();
    test_void_t<int(*)[][2]>();
    test_void_t<int(&)[3][2]>();
    test_void_t<int(&)[][2]>();
    test_void_t<int(&&)[3][2]>();
    test_void_t<int(&&)[][2]>();
    test_void_t<Class>();
    test_void_t<Class[]>();
    test_void_t<Class[2]>();
    test_void_t<Template<void>>();
    test_void_t<Template<int>>();
    test_void_t<Template<Class>>();
    test_void_t<Template<incomplete_type>>();
    test_void_t<VariadicTemplate<>>();
    test_void_t<VariadicTemplate<void>>();
    test_void_t<VariadicTemplate<int>>();
    test_void_t<VariadicTemplate<Class>>();
    test_void_t<VariadicTemplate<incomplete_type>>();
    test_void_t<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_void_t<PublicDerviedFromTemplate<Base>>();
    test_void_t<PublicDerviedFromTemplate<Derived>>();
    test_void_t<PublicDerviedFromTemplate<Class>>();
    test_void_t<PrivateDerviedFromTemplate<Base>>();
    test_void_t<PrivateDerviedFromTemplate<Derived>>();
    test_void_t<PrivateDerviedFromTemplate<Class>>();
    test_void_t<ProtectedDerviedFromTemplate<Base>>();
    test_void_t<ProtectedDerviedFromTemplate<Derived>>();
    test_void_t<ProtectedDerviedFromTemplate<Class>>();
    test_void_t<Union>();
    test_void_t<NonEmptyUnion>();
    test_void_t<Empty>();
    test_void_t<NotEmpty>();
    test_void_t<bit_zero>();
    test_void_t<bit_one>();
    test_void_t<Base>();
    test_void_t<Derived>();
    test_void_t<Abstract>();
    test_void_t<PublicAbstract>();
    test_void_t<PrivateAbstract>();
    test_void_t<ProtectedAbstract>();
    test_void_t<AbstractTemplate<int>>();
    test_void_t<AbstractTemplate<double>>();
    test_void_t<AbstractTemplate<Class>>();
    test_void_t<AbstractTemplate<incomplete_type>>();
    test_void_t<Final>();
    test_void_t<PublicDestructor>();
    test_void_t<ProtectedDestructor>();
    test_void_t<PrivateDestructor>();
    test_void_t<VirtualPublicDestructor>();
    test_void_t<VirtualProtectedDestructor>();
    test_void_t<VirtualPrivateDestructor>();
    test_void_t<PurePublicDestructor>();
    test_void_t<PureProtectedDestructor>();
    test_void_t<PurePrivateDestructor>();
    test_void_t<DeletedPublicDestructor>();
    test_void_t<DeletedProtectedDestructor>();
    test_void_t<DeletedPrivateDestructor>();
    test_void_t<DeletedVirtualPublicDestructor>();
    test_void_t<DeletedVirtualProtectedDestructor>();
    test_void_t<DeletedVirtualPrivateDestructor>();
    test_void_t<Enum>();
    test_void_t<EnumSigned>();
    test_void_t<EnumUnsigned>();
    test_void_t<EnumClass>();
    test_void_t<EnumStruct>();
    test_void_t<Function>();
    test_void_t<FunctionPtr>();
    test_void_t<MemberObjectPtr>();
    test_void_t<MemberFunctionPtr>();
    test_void_t<incomplete_type>();
    test_void_t<IncompleteTemplate<void>>();
    test_void_t<IncompleteTemplate<int>>();
    test_void_t<IncompleteTemplate<Class>>();
    test_void_t<IncompleteTemplate<incomplete_type>>();
    test_void_t<IncompleteVariadicTemplate<>>();
    test_void_t<IncompleteVariadicTemplate<void>>();
    test_void_t<IncompleteVariadicTemplate<int>>();
    test_void_t<IncompleteVariadicTemplate<Class>>();
    test_void_t<IncompleteVariadicTemplate<incomplete_type>>();
    test_void_t<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_void_t<int Class::*>();
    test_void_t<float Class::*>();
    test_void_t<void * Class::*>();
    test_void_t<int * Class::*>();
    test_void_t<int Class::*&>();
    test_void_t<float Class::*&>();
    test_void_t<void * Class::*&>();
    test_void_t<int * Class::*&>();
    test_void_t<int Class::*&&>();
    test_void_t<float Class::*&&>();
    test_void_t<void * Class::*&&>();
    test_void_t<int * Class::*&&>();
    test_void_t<int Class::*const>();
    test_void_t<float Class::*const>();
    test_void_t<void * Class::*const>();
    test_void_t<int Class::*const&>();
    test_void_t<float Class::*const&>();
    test_void_t<void * Class::*const&>();
    test_void_t<int Class::*const&&>();
    test_void_t<float Class::*const&&>();
    test_void_t<void * Class::*const&&>();
    test_void_t<int Class::*volatile>();
    test_void_t<float Class::*volatile>();
    test_void_t<void * Class::*volatile>();
    test_void_t<int Class::*volatile&>();
    test_void_t<float Class::*volatile&>();
    test_void_t<void * Class::*volatile&>();
    test_void_t<int Class::*volatile&&>();
    test_void_t<float Class::*volatile&&>();
    test_void_t<void * Class::*volatile&&>();
    test_void_t<int Class::*const volatile>();
    test_void_t<float Class::*const volatile>();
    test_void_t<void * Class::*const volatile>();
    test_void_t<int Class::*const volatile&>();
    test_void_t<float Class::*const volatile&>();
    test_void_t<void * Class::*const volatile&>();
    test_void_t<int Class::*const volatile&&>();
    test_void_t<float Class::*const volatile&&>();
    test_void_t<void * Class::*const volatile&&>();
    test_void_t<NonCopyable>();
    test_void_t<NonMoveable>();
    test_void_t<NonConstructible>();
    test_void_t<Tracked>();
    test_void_t<TrapConstructible>();
    test_void_t<TrapImplicitConversion>();
    test_void_t<TrapComma>();
    test_void_t<TrapCall>();
    test_void_t<TrapSelfAssign>();
    test_void_t<TrapDeref>();
    test_void_t<TrapArraySubscript>();

    test_void_t<void()>();
    test_void_t<void()&>();
    test_void_t<void() &&>();
    test_void_t<void() const>();
    test_void_t<void() const&>();
    test_void_t<void() const&&>();
    test_void_t<void() volatile>();
    test_void_t<void() volatile&>();
    test_void_t<void() volatile&&>();
    test_void_t<void() const volatile>();
    test_void_t<void() const volatile&>();
    test_void_t<void() const volatile&&>();
    test_void_t<void() noexcept>();
    test_void_t<void()& noexcept>();
    test_void_t<void()&& noexcept>();
    test_void_t<void() const noexcept>();
    test_void_t<void() const& noexcept>();
    test_void_t<void() const&& noexcept>();
    test_void_t<void() volatile noexcept>();
    test_void_t<void() volatile& noexcept>();
    test_void_t<void() volatile&& noexcept>();
    test_void_t<void() const volatile noexcept>();
    test_void_t<void() const volatile& noexcept>();
    test_void_t<void() const volatile&& noexcept>();

    test_void_t<void(int)>();
    test_void_t<void(int)&>();
    test_void_t<void(int) &&>();
    test_void_t<void(int) const>();
    test_void_t<void(int) const&>();
    test_void_t<void(int) const&&>();
    test_void_t<void(int) volatile>();
    test_void_t<void(int) volatile&>();
    test_void_t<void(int) volatile&&>();
    test_void_t<void(int) const volatile>();
    test_void_t<void(int) const volatile&>();
    test_void_t<void(int) const volatile&&>();
    test_void_t<void(int) noexcept>();
    test_void_t<void(int)& noexcept>();
    test_void_t<void(int)&& noexcept>();
    test_void_t<void(int) const noexcept>();
    test_void_t<void(int) const& noexcept>();
    test_void_t<void(int) const&& noexcept>();
    test_void_t<void(int) volatile noexcept>();
    test_void_t<void(int) volatile& noexcept>();
    test_void_t<void(int) volatile&& noexcept>();
    test_void_t<void(int) const volatile noexcept>();
    test_void_t<void(int) const volatile& noexcept>();
    test_void_t<void(int) const volatile&& noexcept>();

    test_void_t<void(...)>();
    test_void_t<void(...)&>();
    test_void_t<void(...) &&>();
    test_void_t<void(...) const>();
    test_void_t<void(...) const&>();
    test_void_t<void(...) const&&>();
    test_void_t<void(...) volatile>();
    test_void_t<void(...) volatile&>();
    test_void_t<void(...) volatile&&>();
    test_void_t<void(...) const volatile>();
    test_void_t<void(...) const volatile&>();
    test_void_t<void(...) const volatile&&>();
    test_void_t<void(...) noexcept>();
    test_void_t<void(...)& noexcept>();
    test_void_t<void(...)&& noexcept>();
    test_void_t<void(...) const noexcept>();
    test_void_t<void(...) const& noexcept>();
    test_void_t<void(...) const&& noexcept>();
    test_void_t<void(...) volatile noexcept>();
    test_void_t<void(...) volatile& noexcept>();
    test_void_t<void(...) volatile&& noexcept>();
    test_void_t<void(...) const volatile noexcept>();
    test_void_t<void(...) const volatile& noexcept>();
    test_void_t<void(...) const volatile&& noexcept>();

    test_void_t<void(int, ...)>();
    test_void_t<void(int, ...)&>();
    test_void_t<void(int, ...) &&>();
    test_void_t<void(int, ...) const>();
    test_void_t<void(int, ...) const&>();
    test_void_t<void(int, ...) const&&>();
    test_void_t<void(int, ...) volatile>();
    test_void_t<void(int, ...) volatile&>();
    test_void_t<void(int, ...) volatile&&>();
    test_void_t<void(int, ...) const volatile>();
    test_void_t<void(int, ...) const volatile&>();
    test_void_t<void(int, ...) const volatile&&>();
    test_void_t<void(int, ...) noexcept>();
    test_void_t<void(int, ...)& noexcept>();
    test_void_t<void(int, ...)&& noexcept>();
    test_void_t<void(int, ...) const noexcept>();
    test_void_t<void(int, ...) const& noexcept>();
    test_void_t<void(int, ...) const&& noexcept>();
    test_void_t<void(int, ...) volatile noexcept>();
    test_void_t<void(int, ...) volatile& noexcept>();
    test_void_t<void(int, ...) volatile&& noexcept>();
    test_void_t<void(int, ...) const volatile noexcept>();
    test_void_t<void(int, ...) const volatile& noexcept>();
    test_void_t<void(int, ...) const volatile&& noexcept>();

    test_void_t<int()>();
    test_void_t<int()&>();
    test_void_t<int() &&>();
    test_void_t<int() const>();
    test_void_t<int() const&>();
    test_void_t<int() const&&>();
    test_void_t<int() volatile>();
    test_void_t<int() volatile&>();
    test_void_t<int() volatile&&>();
    test_void_t<int() const volatile>();
    test_void_t<int() const volatile&>();
    test_void_t<int() const volatile&&>();
    test_void_t<int() noexcept>();
    test_void_t<int()& noexcept>();
    test_void_t<int()&& noexcept>();
    test_void_t<int() const noexcept>();
    test_void_t<int() const& noexcept>();
    test_void_t<int() const&& noexcept>();
    test_void_t<int() volatile noexcept>();
    test_void_t<int() volatile& noexcept>();
    test_void_t<int() volatile&& noexcept>();
    test_void_t<int() const volatile noexcept>();
    test_void_t<int() const volatile& noexcept>();
    test_void_t<int() const volatile&& noexcept>();

    test_void_t<int(int)>();
    test_void_t<int(int)&>();
    test_void_t<int(int) &&>();
    test_void_t<int(int) const>();
    test_void_t<int(int) const&>();
    test_void_t<int(int) const&&>();
    test_void_t<int(int) volatile>();
    test_void_t<int(int) volatile&>();
    test_void_t<int(int) volatile&&>();
    test_void_t<int(int) const volatile>();
    test_void_t<int(int) const volatile&>();
    test_void_t<int(int) const volatile&&>();
    test_void_t<int(int) noexcept>();
    test_void_t<int(int)& noexcept>();
    test_void_t<int(int)&& noexcept>();
    test_void_t<int(int) const noexcept>();
    test_void_t<int(int) const& noexcept>();
    test_void_t<int(int) const&& noexcept>();
    test_void_t<int(int) volatile noexcept>();
    test_void_t<int(int) volatile& noexcept>();
    test_void_t<int(int) volatile&& noexcept>();
    test_void_t<int(int) const volatile noexcept>();
    test_void_t<int(int) const volatile& noexcept>();
    test_void_t<int(int) const volatile&& noexcept>();

    test_void_t<int(...)>();
    test_void_t<int(...)&>();
    test_void_t<int(...) &&>();
    test_void_t<int(...) const>();
    test_void_t<int(...) const&>();
    test_void_t<int(...) const&&>();
    test_void_t<int(...) volatile>();
    test_void_t<int(...) volatile&>();
    test_void_t<int(...) volatile&&>();
    test_void_t<int(...) const volatile>();
    test_void_t<int(...) const volatile&>();
    test_void_t<int(...) const volatile&&>();
    test_void_t<int(...) noexcept>();
    test_void_t<int(...)& noexcept>();
    test_void_t<int(...)&& noexcept>();
    test_void_t<int(...) const noexcept>();
    test_void_t<int(...) const& noexcept>();
    test_void_t<int(...) const&& noexcept>();
    test_void_t<int(...) volatile noexcept>();
    test_void_t<int(...) volatile& noexcept>();
    test_void_t<int(...) volatile&& noexcept>();
    test_void_t<int(...) const volatile noexcept>();
    test_void_t<int(...) const volatile& noexcept>();
    test_void_t<int(...) const volatile&& noexcept>();

    test_void_t<int(int, ...)>();
    test_void_t<int(int, ...)&>();
    test_void_t<int(int, ...) &&>();
    test_void_t<int(int, ...) const>();
    test_void_t<int(int, ...) const&>();
    test_void_t<int(int, ...) const&&>();
    test_void_t<int(int, ...) volatile>();
    test_void_t<int(int, ...) volatile&>();
    test_void_t<int(int, ...) volatile&&>();
    test_void_t<int(int, ...) const volatile>();
    test_void_t<int(int, ...) const volatile&>();
    test_void_t<int(int, ...) const volatile&&>();
    test_void_t<int(int, ...) noexcept>();
    test_void_t<int(int, ...)& noexcept>();
    test_void_t<int(int, ...)&& noexcept>();
    test_void_t<int(int, ...) const noexcept>();
    test_void_t<int(int, ...) const& noexcept>();
    test_void_t<int(int, ...) const&& noexcept>();
    test_void_t<int(int, ...) volatile noexcept>();
    test_void_t<int(int, ...) volatile& noexcept>();
    test_void_t<int(int, ...) volatile&& noexcept>();
    test_void_t<int(int, ...) const volatile noexcept>();
    test_void_t<int(int, ...) const volatile& noexcept>();
    test_void_t<int(int, ...) const volatile&& noexcept>();

    test_void_t<void (*)()>();
    test_void_t<void (*)() noexcept>();

    test_void_t<void (*)(int)>();
    test_void_t<void (*)(int) noexcept>();

    test_void_t<void (*)(...)>();
    test_void_t<void (*)(...) noexcept>();

    test_void_t<void (*)(int, ...)>();
    test_void_t<void (*)(int, ...) noexcept>();

    test_void_t<int (*)()>();
    test_void_t<int (*)() noexcept>();

    test_void_t<int (*)(int)>();
    test_void_t<int (*)(int) noexcept>();

    test_void_t<int (*)(...)>();
    test_void_t<int (*)(...) noexcept>();

    test_void_t<int (*)(int, ...)>();
    test_void_t<int (*)(int, ...) noexcept>();

    test_void_t<void (&)()>();
    test_void_t<void (&)() noexcept>();

    test_void_t<void (&)(int)>();
    test_void_t<void (&)(int) noexcept>();

    test_void_t<void (&)(...)>();
    test_void_t<void (&)(...) noexcept>();

    test_void_t<void (&)(int, ...)>();
    test_void_t<void (&)(int, ...) noexcept>();

    test_void_t<int (&)()>();
    test_void_t<int (&)() noexcept>();

    test_void_t<int (&)(int)>();
    test_void_t<int (&)(int) noexcept>();

    test_void_t<int (&)(...)>();
    test_void_t<int (&)(...) noexcept>();

    test_void_t<int (&)(int, ...)>();
    test_void_t<int (&)(int, ...) noexcept>();

    test_void_t<void(&&)()>();
    test_void_t<void(&&)() noexcept>();

    test_void_t<void(&&)(int)>();
    test_void_t<void(&&)(int) noexcept>();

    test_void_t<void(&&)(...)>();
    test_void_t<void(&&)(...) noexcept>();

    test_void_t<void(&&)(int, ...)>();
    test_void_t<void(&&)(int, ...) noexcept>();

    test_void_t<int(&&)()>();
    test_void_t<int(&&)() noexcept>();

    test_void_t<int(&&)(int)>();
    test_void_t<int(&&)(int) noexcept>();

    test_void_t<int(&&)(...)>();
    test_void_t<int(&&)(...) noexcept>();

    test_void_t<int(&&)(int, ...)>();
    test_void_t<int(&&)(int, ...) noexcept>();

    test_void_t<void (Class::*)()>();
    test_void_t<void (Class::*)()&>();
    test_void_t<void (Class::*)() &&>();
    test_void_t<void (Class::*)() const>();
    test_void_t<void (Class::*)() const&>();
    test_void_t<void (Class::*)() const&&>();
    test_void_t<void (Class::*)() noexcept>();
    test_void_t<void (Class::*)()& noexcept>();
    test_void_t<void (Class::*)()&& noexcept>();
    test_void_t<void (Class::*)() const noexcept>();
    test_void_t<void (Class::*)() const& noexcept>();
    test_void_t<void (Class::*)() const&& noexcept>();

    test_void_t<void (Class::*)(int)>();
    test_void_t<void (Class::*)(int)&>();
    test_void_t<void (Class::*)(int) &&>();
    test_void_t<void (Class::*)(int) const>();
    test_void_t<void (Class::*)(int) const&>();
    test_void_t<void (Class::*)(int) const&&>();
    test_void_t<void (Class::*)(int) noexcept>();
    test_void_t<void (Class::*)(int)& noexcept>();
    test_void_t<void (Class::*)(int)&& noexcept>();
    test_void_t<void (Class::*)(int) const noexcept>();
    test_void_t<void (Class::*)(int) const& noexcept>();
    test_void_t<void (Class::*)(int) const&& noexcept>();

    test_void_t<void (Class::*)(...)>();
    test_void_t<void (Class::*)(...)&>();
    test_void_t<void (Class::*)(...) &&>();
    test_void_t<void (Class::*)(...) const>();
    test_void_t<void (Class::*)(...) const&>();
    test_void_t<void (Class::*)(...) const&&>();
    test_void_t<void (Class::*)(...) noexcept>();
    test_void_t<void (Class::*)(...)& noexcept>();
    test_void_t<void (Class::*)(...)&& noexcept>();
    test_void_t<void (Class::*)(...) const noexcept>();
    test_void_t<void (Class::*)(...) const& noexcept>();
    test_void_t<void (Class::*)(...) const&& noexcept>();

    test_void_t<void (Class::*)(int, ...)>();
    test_void_t<void (Class::*)(int, ...)&>();
    test_void_t<void (Class::*)(int, ...) &&>();
    test_void_t<void (Class::*)(int, ...) const>();
    test_void_t<void (Class::*)(int, ...) const&>();
    test_void_t<void (Class::*)(int, ...) const&&>();
    test_void_t<void (Class::*)(int, ...) noexcept>();
    test_void_t<void (Class::*)(int, ...)& noexcept>();
    test_void_t<void (Class::*)(int, ...)&& noexcept>();
    test_void_t<void (Class::*)(int, ...) const noexcept>();
    test_void_t<void (Class::*)(int, ...) const& noexcept>();
    test_void_t<void (Class::*)(int, ...) const&& noexcept>();

    test_void_t<int (Class::*)()>();
    test_void_t<int (Class::*)()&>();
    test_void_t<int (Class::*)() &&>();
    test_void_t<int (Class::*)() const>();
    test_void_t<int (Class::*)() const&>();
    test_void_t<int (Class::*)() const&&>();
    test_void_t<int (Class::*)() noexcept>();
    test_void_t<int (Class::*)()& noexcept>();
    test_void_t<int (Class::*)()&& noexcept>();
    test_void_t<int (Class::*)() const noexcept>();
    test_void_t<int (Class::*)() const& noexcept>();
    test_void_t<int (Class::*)() const&& noexcept>();

    test_void_t<int (Class::*)(int)>();
    test_void_t<int (Class::*)(int)&>();
    test_void_t<int (Class::*)(int) &&>();
    test_void_t<int (Class::*)(int) const>();
    test_void_t<int (Class::*)(int) const&>();
    test_void_t<int (Class::*)(int) const&&>();
    test_void_t<int (Class::*)(int) noexcept>();
    test_void_t<int (Class::*)(int)& noexcept>();
    test_void_t<int (Class::*)(int)&& noexcept>();
    test_void_t<int (Class::*)(int) const noexcept>();
    test_void_t<int (Class::*)(int) const& noexcept>();
    test_void_t<int (Class::*)(int) const&& noexcept>();

    test_void_t<int (Class::*)(...)>();
    test_void_t<int (Class::*)(...)&>();
    test_void_t<int (Class::*)(...) &&>();
    test_void_t<int (Class::*)(...) const>();
    test_void_t<int (Class::*)(...) const&>();
    test_void_t<int (Class::*)(...) const&&>();
    test_void_t<int (Class::*)(...) noexcept>();
    test_void_t<int (Class::*)(...)& noexcept>();
    test_void_t<int (Class::*)(...)&& noexcept>();
    test_void_t<int (Class::*)(...) const noexcept>();
    test_void_t<int (Class::*)(...) const& noexcept>();
    test_void_t<int (Class::*)(...) const&& noexcept>();

    test_void_t<int (Class::*)(int, ...)>();
    test_void_t<int (Class::*)(int, ...)&>();
    test_void_t<int (Class::*)(int, ...) &&>();
    test_void_t<int (Class::*)(int, ...) const>();
    test_void_t<int (Class::*)(int, ...) const&>();
    test_void_t<int (Class::*)(int, ...) const&&>();
    test_void_t<int (Class::*)(int, ...) noexcept>();
    test_void_t<int (Class::*)(int, ...)& noexcept>();
    test_void_t<int (Class::*)(int, ...)&& noexcept>();
    test_void_t<int (Class::*)(int, ...) const noexcept>();
    test_void_t<int (Class::*)(int, ...) const& noexcept>();
    test_void_t<int (Class::*)(int, ...) const&& noexcept>();
}
