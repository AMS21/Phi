#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/type_identity.hpp>
#include <vector>

template <typename T>
void test_type_identity()
{
    CHECK_SAME_TYPE(T, typename phi::type_identity<T>::type);
    CHECK_SAME_TYPE(const T, const typename phi::type_identity<T>::type);
    CHECK_SAME_TYPE(volatile T, volatile typename phi::type_identity<T>::type);
    CHECK_SAME_TYPE(const volatile T, const volatile typename phi::type_identity<T>::type);

    CHECK_SAME_TYPE(const T, typename phi::type_identity<const T>::type);
    CHECK_SAME_TYPE(volatile T, typename phi::type_identity<volatile T>::type);
    CHECK_SAME_TYPE(const volatile T, typename phi::type_identity<const volatile T>::type);

    CHECK_SAME_TYPE(T, phi::type_identity_t<T>);
    CHECK_SAME_TYPE(const T, const phi::type_identity_t<T>);
    CHECK_SAME_TYPE(volatile T, volatile phi::type_identity_t<T>);
    CHECK_SAME_TYPE(const volatile T, const volatile phi::type_identity_t<T>);

    CHECK_SAME_TYPE(const T, phi::type_identity_t<const T>);
    CHECK_SAME_TYPE(volatile T, phi::type_identity_t<volatile T>);
    CHECK_SAME_TYPE(const volatile T, phi::type_identity_t<const volatile T>);
}

TEST_CASE("type_identity")
{
    test_type_identity<void>();
    test_type_identity<phi::nullptr_t>();
    test_type_identity<bool>();
    test_type_identity<char>();
    test_type_identity<signed char>();
    test_type_identity<unsigned char>();
    test_type_identity<short>();
    test_type_identity<unsigned short>();
    test_type_identity<int>();
    test_type_identity<unsigned int>();
    test_type_identity<long>();
    test_type_identity<unsigned long>();
    test_type_identity<long long>();
    test_type_identity<unsigned long long>();
    test_type_identity<float>();
    test_type_identity<double>();
    test_type_identity<long double>();
    test_type_identity<char8_t>();
    test_type_identity<char16_t>();
    test_type_identity<char32_t>();
    test_type_identity<wchar_t>();

    test_type_identity<phi::boolean>();
    test_type_identity<phi::integer<signed char>>();
    test_type_identity<phi::integer<unsigned char>>();
    test_type_identity<phi::integer<short>>();
    test_type_identity<phi::integer<unsigned short>>();
    test_type_identity<phi::integer<int>>();
    test_type_identity<phi::integer<unsigned int>>();
    test_type_identity<phi::integer<long>>();
    test_type_identity<phi::integer<unsigned long>>();
    test_type_identity<phi::integer<long long>>();
    test_type_identity<phi::integer<unsigned long long>>();
    test_type_identity<phi::floating_point<float>>();
    test_type_identity<phi::floating_point<double>>();
    test_type_identity<phi::floating_point<long double>>();

    test_type_identity<std::vector<int>>();
    test_type_identity<phi::scope_ptr<int>>();

    test_type_identity<int&>();
    test_type_identity<const int&>();
    test_type_identity<volatile int&>();
    test_type_identity<const volatile int&>();
    test_type_identity<int&&>();
    test_type_identity<const int&&>();
    test_type_identity<volatile int&&>();
    test_type_identity<const volatile int&&>();
    test_type_identity<int*>();
    test_type_identity<const int*>();
    test_type_identity<volatile int*>();
    test_type_identity<const volatile int*>();
    test_type_identity<int**>();
    test_type_identity<const int**>();
    test_type_identity<volatile int**>();
    test_type_identity<const volatile int**>();
    test_type_identity<int*&>();
    test_type_identity<const int*&>();
    test_type_identity<volatile int*&>();
    test_type_identity<const volatile int*&>();
    test_type_identity<int*&&>();
    test_type_identity<const int*&&>();
    test_type_identity<volatile int*&&>();
    test_type_identity<const volatile int*&&>();
    test_type_identity<void*>();
    test_type_identity<char[3]>();
    test_type_identity<char[]>();
    test_type_identity<char* [3]>();
    test_type_identity<char*[]>();
    test_type_identity<int(*)[3]>();
    test_type_identity<int(*)[]>();
    test_type_identity<int(&)[3]>();
    test_type_identity<int(&)[]>();
    test_type_identity<int(&&)[3]>();
    test_type_identity<int(&&)[]>();
    test_type_identity<char[3][2]>();
    test_type_identity<char[][2]>();
    test_type_identity<char* [3][2]>();
    test_type_identity<char*[][2]>();
    test_type_identity<int(*)[3][2]>();
    test_type_identity<int(*)[][2]>();
    test_type_identity<int(&)[3][2]>();
    test_type_identity<int(&)[][2]>();
    test_type_identity<int(&&)[3][2]>();
    test_type_identity<int(&&)[][2]>();
    test_type_identity<Class>();
    test_type_identity<Class[]>();
    test_type_identity<Class[2]>();
    test_type_identity<Template<void>>();
    test_type_identity<Template<int>>();
    test_type_identity<Template<Class>>();
    test_type_identity<Template<incomplete_type>>();
    test_type_identity<VariadicTemplate<>>();
    test_type_identity<VariadicTemplate<void>>();
    test_type_identity<VariadicTemplate<int>>();
    test_type_identity<VariadicTemplate<Class>>();
    test_type_identity<VariadicTemplate<incomplete_type>>();
    test_type_identity<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_type_identity<PublicDerviedFromTemplate<Base>>();
    test_type_identity<PublicDerviedFromTemplate<Derived>>();
    test_type_identity<PublicDerviedFromTemplate<Class>>();
    test_type_identity<PrivateDerviedFromTemplate<Base>>();
    test_type_identity<PrivateDerviedFromTemplate<Derived>>();
    test_type_identity<PrivateDerviedFromTemplate<Class>>();
    test_type_identity<ProtectedDerviedFromTemplate<Base>>();
    test_type_identity<ProtectedDerviedFromTemplate<Derived>>();
    test_type_identity<ProtectedDerviedFromTemplate<Class>>();
    test_type_identity<Union>();
    test_type_identity<NonEmptyUnion>();
    test_type_identity<Empty>();
    test_type_identity<NotEmpty>();
    test_type_identity<bit_zero>();
    test_type_identity<bit_one>();
    test_type_identity<Base>();
    test_type_identity<Derived>();
    test_type_identity<Abstract>();
    test_type_identity<PublicAbstract>();
    test_type_identity<PrivateAbstract>();
    test_type_identity<ProtectedAbstract>();
    test_type_identity<AbstractTemplate<int>>();
    test_type_identity<AbstractTemplate<double>>();
    test_type_identity<AbstractTemplate<Class>>();
    test_type_identity<AbstractTemplate<incomplete_type>>();
    test_type_identity<Final>();
    test_type_identity<PublicDestructor>();
    test_type_identity<ProtectedDestructor>();
    test_type_identity<PrivateDestructor>();
    test_type_identity<VirtualPublicDestructor>();
    test_type_identity<VirtualProtectedDestructor>();
    test_type_identity<VirtualPrivateDestructor>();
    test_type_identity<PurePublicDestructor>();
    test_type_identity<PureProtectedDestructor>();
    test_type_identity<PurePrivateDestructor>();
    test_type_identity<DeletedPublicDestructor>();
    test_type_identity<DeletedProtectedDestructor>();
    test_type_identity<DeletedPrivateDestructor>();
    test_type_identity<DeletedVirtualPublicDestructor>();
    test_type_identity<DeletedVirtualProtectedDestructor>();
    test_type_identity<DeletedVirtualPrivateDestructor>();
    test_type_identity<Enum>();
    test_type_identity<EnumSigned>();
    test_type_identity<EnumUnsigned>();
    test_type_identity<EnumClass>();
    test_type_identity<EnumStruct>();
    test_type_identity<Function>();
    test_type_identity<FunctionPtr>();
    test_type_identity<MemberObjectPtr>();
    test_type_identity<MemberFunctionPtr>();
    test_type_identity<incomplete_type>();
    test_type_identity<IncompleteTemplate<void>>();
    test_type_identity<IncompleteTemplate<int>>();
    test_type_identity<IncompleteTemplate<Class>>();
    test_type_identity<IncompleteTemplate<incomplete_type>>();
    test_type_identity<IncompleteVariadicTemplate<>>();
    test_type_identity<IncompleteVariadicTemplate<void>>();
    test_type_identity<IncompleteVariadicTemplate<int>>();
    test_type_identity<IncompleteVariadicTemplate<Class>>();
    test_type_identity<IncompleteVariadicTemplate<incomplete_type>>();
    test_type_identity<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_type_identity<int Class::*>();
    test_type_identity<float Class::*>();
    test_type_identity<void * Class::*>();
    test_type_identity<int * Class::*>();
    test_type_identity<int Class::*&>();
    test_type_identity<float Class::*&>();
    test_type_identity<void * Class::*&>();
    test_type_identity<int * Class::*&>();
    test_type_identity<int Class::*&&>();
    test_type_identity<float Class::*&&>();
    test_type_identity<void * Class::*&&>();
    test_type_identity<int * Class::*&&>();
    test_type_identity<int Class::*const>();
    test_type_identity<float Class::*const>();
    test_type_identity<void * Class::*const>();
    test_type_identity<int Class::*const&>();
    test_type_identity<float Class::*const&>();
    test_type_identity<void * Class::*const&>();
    test_type_identity<int Class::*const&&>();
    test_type_identity<float Class::*const&&>();
    test_type_identity<void * Class::*const&&>();
    test_type_identity<int Class::*volatile>();
    test_type_identity<float Class::*volatile>();
    test_type_identity<void * Class::*volatile>();
    test_type_identity<int Class::*volatile&>();
    test_type_identity<float Class::*volatile&>();
    test_type_identity<void * Class::*volatile&>();
    test_type_identity<int Class::*volatile&&>();
    test_type_identity<float Class::*volatile&&>();
    test_type_identity<void * Class::*volatile&&>();
    test_type_identity<int Class::*const volatile>();
    test_type_identity<float Class::*const volatile>();
    test_type_identity<void * Class::*const volatile>();
    test_type_identity<int Class::*const volatile&>();
    test_type_identity<float Class::*const volatile&>();
    test_type_identity<void * Class::*const volatile&>();
    test_type_identity<int Class::*const volatile&&>();
    test_type_identity<float Class::*const volatile&&>();
    test_type_identity<void * Class::*const volatile&&>();
    test_type_identity<NonCopyable>();
    test_type_identity<NonMoveable>();
    test_type_identity<NonConstructible>();
    test_type_identity<Tracked>();
    test_type_identity<TrapConstructible>();
    test_type_identity<TrapImplicitConversion>();
    test_type_identity<TrapComma>();
    test_type_identity<TrapCall>();
    test_type_identity<TrapSelfAssign>();
    test_type_identity<TrapDeref>();
    test_type_identity<TrapArraySubscript>();

    test_type_identity<void()>();
    test_type_identity<void()&>();
    test_type_identity<void() &&>();
    test_type_identity<void() const>();
    test_type_identity<void() const&>();
    test_type_identity<void() const&&>();
    test_type_identity<void() volatile>();
    test_type_identity<void() volatile&>();
    test_type_identity<void() volatile&&>();
    test_type_identity<void() const volatile>();
    test_type_identity<void() const volatile&>();
    test_type_identity<void() const volatile&&>();
    test_type_identity<void() noexcept>();
    test_type_identity<void()& noexcept>();
    test_type_identity<void()&& noexcept>();
    test_type_identity<void() const noexcept>();
    test_type_identity<void() const& noexcept>();
    test_type_identity<void() const&& noexcept>();
    test_type_identity<void() volatile noexcept>();
    test_type_identity<void() volatile& noexcept>();
    test_type_identity<void() volatile&& noexcept>();
    test_type_identity<void() const volatile noexcept>();
    test_type_identity<void() const volatile& noexcept>();
    test_type_identity<void() const volatile&& noexcept>();

    test_type_identity<void(int)>();
    test_type_identity<void(int)&>();
    test_type_identity<void(int) &&>();
    test_type_identity<void(int) const>();
    test_type_identity<void(int) const&>();
    test_type_identity<void(int) const&&>();
    test_type_identity<void(int) volatile>();
    test_type_identity<void(int) volatile&>();
    test_type_identity<void(int) volatile&&>();
    test_type_identity<void(int) const volatile>();
    test_type_identity<void(int) const volatile&>();
    test_type_identity<void(int) const volatile&&>();
    test_type_identity<void(int) noexcept>();
    test_type_identity<void(int)& noexcept>();
    test_type_identity<void(int)&& noexcept>();
    test_type_identity<void(int) const noexcept>();
    test_type_identity<void(int) const& noexcept>();
    test_type_identity<void(int) const&& noexcept>();
    test_type_identity<void(int) volatile noexcept>();
    test_type_identity<void(int) volatile& noexcept>();
    test_type_identity<void(int) volatile&& noexcept>();
    test_type_identity<void(int) const volatile noexcept>();
    test_type_identity<void(int) const volatile& noexcept>();
    test_type_identity<void(int) const volatile&& noexcept>();

    test_type_identity<void(...)>();
    test_type_identity<void(...)&>();
    test_type_identity<void(...) &&>();
    test_type_identity<void(...) const>();
    test_type_identity<void(...) const&>();
    test_type_identity<void(...) const&&>();
    test_type_identity<void(...) volatile>();
    test_type_identity<void(...) volatile&>();
    test_type_identity<void(...) volatile&&>();
    test_type_identity<void(...) const volatile>();
    test_type_identity<void(...) const volatile&>();
    test_type_identity<void(...) const volatile&&>();
    test_type_identity<void(...) noexcept>();
    test_type_identity<void(...)& noexcept>();
    test_type_identity<void(...)&& noexcept>();
    test_type_identity<void(...) const noexcept>();
    test_type_identity<void(...) const& noexcept>();
    test_type_identity<void(...) const&& noexcept>();
    test_type_identity<void(...) volatile noexcept>();
    test_type_identity<void(...) volatile& noexcept>();
    test_type_identity<void(...) volatile&& noexcept>();
    test_type_identity<void(...) const volatile noexcept>();
    test_type_identity<void(...) const volatile& noexcept>();
    test_type_identity<void(...) const volatile&& noexcept>();

    test_type_identity<void(int, ...)>();
    test_type_identity<void(int, ...)&>();
    test_type_identity<void(int, ...) &&>();
    test_type_identity<void(int, ...) const>();
    test_type_identity<void(int, ...) const&>();
    test_type_identity<void(int, ...) const&&>();
    test_type_identity<void(int, ...) volatile>();
    test_type_identity<void(int, ...) volatile&>();
    test_type_identity<void(int, ...) volatile&&>();
    test_type_identity<void(int, ...) const volatile>();
    test_type_identity<void(int, ...) const volatile&>();
    test_type_identity<void(int, ...) const volatile&&>();
    test_type_identity<void(int, ...) noexcept>();
    test_type_identity<void(int, ...)& noexcept>();
    test_type_identity<void(int, ...)&& noexcept>();
    test_type_identity<void(int, ...) const noexcept>();
    test_type_identity<void(int, ...) const& noexcept>();
    test_type_identity<void(int, ...) const&& noexcept>();
    test_type_identity<void(int, ...) volatile noexcept>();
    test_type_identity<void(int, ...) volatile& noexcept>();
    test_type_identity<void(int, ...) volatile&& noexcept>();
    test_type_identity<void(int, ...) const volatile noexcept>();
    test_type_identity<void(int, ...) const volatile& noexcept>();
    test_type_identity<void(int, ...) const volatile&& noexcept>();

    test_type_identity<int()>();
    test_type_identity<int()&>();
    test_type_identity<int() &&>();
    test_type_identity<int() const>();
    test_type_identity<int() const&>();
    test_type_identity<int() const&&>();
    test_type_identity<int() volatile>();
    test_type_identity<int() volatile&>();
    test_type_identity<int() volatile&&>();
    test_type_identity<int() const volatile>();
    test_type_identity<int() const volatile&>();
    test_type_identity<int() const volatile&&>();
    test_type_identity<int() noexcept>();
    test_type_identity<int()& noexcept>();
    test_type_identity<int()&& noexcept>();
    test_type_identity<int() const noexcept>();
    test_type_identity<int() const& noexcept>();
    test_type_identity<int() const&& noexcept>();
    test_type_identity<int() volatile noexcept>();
    test_type_identity<int() volatile& noexcept>();
    test_type_identity<int() volatile&& noexcept>();
    test_type_identity<int() const volatile noexcept>();
    test_type_identity<int() const volatile& noexcept>();
    test_type_identity<int() const volatile&& noexcept>();

    test_type_identity<int(int)>();
    test_type_identity<int(int)&>();
    test_type_identity<int(int) &&>();
    test_type_identity<int(int) const>();
    test_type_identity<int(int) const&>();
    test_type_identity<int(int) const&&>();
    test_type_identity<int(int) volatile>();
    test_type_identity<int(int) volatile&>();
    test_type_identity<int(int) volatile&&>();
    test_type_identity<int(int) const volatile>();
    test_type_identity<int(int) const volatile&>();
    test_type_identity<int(int) const volatile&&>();
    test_type_identity<int(int) noexcept>();
    test_type_identity<int(int)& noexcept>();
    test_type_identity<int(int)&& noexcept>();
    test_type_identity<int(int) const noexcept>();
    test_type_identity<int(int) const& noexcept>();
    test_type_identity<int(int) const&& noexcept>();
    test_type_identity<int(int) volatile noexcept>();
    test_type_identity<int(int) volatile& noexcept>();
    test_type_identity<int(int) volatile&& noexcept>();
    test_type_identity<int(int) const volatile noexcept>();
    test_type_identity<int(int) const volatile& noexcept>();
    test_type_identity<int(int) const volatile&& noexcept>();

    test_type_identity<int(...)>();
    test_type_identity<int(...)&>();
    test_type_identity<int(...) &&>();
    test_type_identity<int(...) const>();
    test_type_identity<int(...) const&>();
    test_type_identity<int(...) const&&>();
    test_type_identity<int(...) volatile>();
    test_type_identity<int(...) volatile&>();
    test_type_identity<int(...) volatile&&>();
    test_type_identity<int(...) const volatile>();
    test_type_identity<int(...) const volatile&>();
    test_type_identity<int(...) const volatile&&>();
    test_type_identity<int(...) noexcept>();
    test_type_identity<int(...)& noexcept>();
    test_type_identity<int(...)&& noexcept>();
    test_type_identity<int(...) const noexcept>();
    test_type_identity<int(...) const& noexcept>();
    test_type_identity<int(...) const&& noexcept>();
    test_type_identity<int(...) volatile noexcept>();
    test_type_identity<int(...) volatile& noexcept>();
    test_type_identity<int(...) volatile&& noexcept>();
    test_type_identity<int(...) const volatile noexcept>();
    test_type_identity<int(...) const volatile& noexcept>();
    test_type_identity<int(...) const volatile&& noexcept>();

    test_type_identity<int(int, ...)>();
    test_type_identity<int(int, ...)&>();
    test_type_identity<int(int, ...) &&>();
    test_type_identity<int(int, ...) const>();
    test_type_identity<int(int, ...) const&>();
    test_type_identity<int(int, ...) const&&>();
    test_type_identity<int(int, ...) volatile>();
    test_type_identity<int(int, ...) volatile&>();
    test_type_identity<int(int, ...) volatile&&>();
    test_type_identity<int(int, ...) const volatile>();
    test_type_identity<int(int, ...) const volatile&>();
    test_type_identity<int(int, ...) const volatile&&>();
    test_type_identity<int(int, ...) noexcept>();
    test_type_identity<int(int, ...)& noexcept>();
    test_type_identity<int(int, ...)&& noexcept>();
    test_type_identity<int(int, ...) const noexcept>();
    test_type_identity<int(int, ...) const& noexcept>();
    test_type_identity<int(int, ...) const&& noexcept>();
    test_type_identity<int(int, ...) volatile noexcept>();
    test_type_identity<int(int, ...) volatile& noexcept>();
    test_type_identity<int(int, ...) volatile&& noexcept>();
    test_type_identity<int(int, ...) const volatile noexcept>();
    test_type_identity<int(int, ...) const volatile& noexcept>();
    test_type_identity<int(int, ...) const volatile&& noexcept>();

    test_type_identity<void (*)()>();
    test_type_identity<void (*)() noexcept>();

    test_type_identity<void (*)(int)>();
    test_type_identity<void (*)(int) noexcept>();

    test_type_identity<void (*)(...)>();
    test_type_identity<void (*)(...) noexcept>();

    test_type_identity<void (*)(int, ...)>();
    test_type_identity<void (*)(int, ...) noexcept>();

    test_type_identity<int (*)()>();
    test_type_identity<int (*)() noexcept>();

    test_type_identity<int (*)(int)>();
    test_type_identity<int (*)(int) noexcept>();

    test_type_identity<int (*)(...)>();
    test_type_identity<int (*)(...) noexcept>();

    test_type_identity<int (*)(int, ...)>();
    test_type_identity<int (*)(int, ...) noexcept>();

    test_type_identity<void (&)()>();
    test_type_identity<void (&)() noexcept>();

    test_type_identity<void (&)(int)>();
    test_type_identity<void (&)(int) noexcept>();

    test_type_identity<void (&)(...)>();
    test_type_identity<void (&)(...) noexcept>();

    test_type_identity<void (&)(int, ...)>();
    test_type_identity<void (&)(int, ...) noexcept>();

    test_type_identity<int (&)()>();
    test_type_identity<int (&)() noexcept>();

    test_type_identity<int (&)(int)>();
    test_type_identity<int (&)(int) noexcept>();

    test_type_identity<int (&)(...)>();
    test_type_identity<int (&)(...) noexcept>();

    test_type_identity<int (&)(int, ...)>();
    test_type_identity<int (&)(int, ...) noexcept>();

    test_type_identity<void(&&)()>();
    test_type_identity<void(&&)() noexcept>();

    test_type_identity<void(&&)(int)>();
    test_type_identity<void(&&)(int) noexcept>();

    test_type_identity<void(&&)(...)>();
    test_type_identity<void(&&)(...) noexcept>();

    test_type_identity<void(&&)(int, ...)>();
    test_type_identity<void(&&)(int, ...) noexcept>();

    test_type_identity<int(&&)()>();
    test_type_identity<int(&&)() noexcept>();

    test_type_identity<int(&&)(int)>();
    test_type_identity<int(&&)(int) noexcept>();

    test_type_identity<int(&&)(...)>();
    test_type_identity<int(&&)(...) noexcept>();

    test_type_identity<int(&&)(int, ...)>();
    test_type_identity<int(&&)(int, ...) noexcept>();

    test_type_identity<void (Class::*)()>();
    test_type_identity<void (Class::*)()&>();
    test_type_identity<void (Class::*)() &&>();
    test_type_identity<void (Class::*)() const>();
    test_type_identity<void (Class::*)() const&>();
    test_type_identity<void (Class::*)() const&&>();
    test_type_identity<void (Class::*)() noexcept>();
    test_type_identity<void (Class::*)()& noexcept>();
    test_type_identity<void (Class::*)()&& noexcept>();
    test_type_identity<void (Class::*)() const noexcept>();
    test_type_identity<void (Class::*)() const& noexcept>();
    test_type_identity<void (Class::*)() const&& noexcept>();

    test_type_identity<void (Class::*)(int)>();
    test_type_identity<void (Class::*)(int)&>();
    test_type_identity<void (Class::*)(int) &&>();
    test_type_identity<void (Class::*)(int) const>();
    test_type_identity<void (Class::*)(int) const&>();
    test_type_identity<void (Class::*)(int) const&&>();
    test_type_identity<void (Class::*)(int) noexcept>();
    test_type_identity<void (Class::*)(int)& noexcept>();
    test_type_identity<void (Class::*)(int)&& noexcept>();
    test_type_identity<void (Class::*)(int) const noexcept>();
    test_type_identity<void (Class::*)(int) const& noexcept>();
    test_type_identity<void (Class::*)(int) const&& noexcept>();

    test_type_identity<void (Class::*)(...)>();
    test_type_identity<void (Class::*)(...)&>();
    test_type_identity<void (Class::*)(...) &&>();
    test_type_identity<void (Class::*)(...) const>();
    test_type_identity<void (Class::*)(...) const&>();
    test_type_identity<void (Class::*)(...) const&&>();
    test_type_identity<void (Class::*)(...) noexcept>();
    test_type_identity<void (Class::*)(...)& noexcept>();
    test_type_identity<void (Class::*)(...)&& noexcept>();
    test_type_identity<void (Class::*)(...) const noexcept>();
    test_type_identity<void (Class::*)(...) const& noexcept>();
    test_type_identity<void (Class::*)(...) const&& noexcept>();

    test_type_identity<void (Class::*)(int, ...)>();
    test_type_identity<void (Class::*)(int, ...)&>();
    test_type_identity<void (Class::*)(int, ...) &&>();
    test_type_identity<void (Class::*)(int, ...) const>();
    test_type_identity<void (Class::*)(int, ...) const&>();
    test_type_identity<void (Class::*)(int, ...) const&&>();
    test_type_identity<void (Class::*)(int, ...) noexcept>();
    test_type_identity<void (Class::*)(int, ...)& noexcept>();
    test_type_identity<void (Class::*)(int, ...)&& noexcept>();
    test_type_identity<void (Class::*)(int, ...) const noexcept>();
    test_type_identity<void (Class::*)(int, ...) const& noexcept>();
    test_type_identity<void (Class::*)(int, ...) const&& noexcept>();

    test_type_identity<int (Class::*)()>();
    test_type_identity<int (Class::*)()&>();
    test_type_identity<int (Class::*)() &&>();
    test_type_identity<int (Class::*)() const>();
    test_type_identity<int (Class::*)() const&>();
    test_type_identity<int (Class::*)() const&&>();
    test_type_identity<int (Class::*)() noexcept>();
    test_type_identity<int (Class::*)()& noexcept>();
    test_type_identity<int (Class::*)()&& noexcept>();
    test_type_identity<int (Class::*)() const noexcept>();
    test_type_identity<int (Class::*)() const& noexcept>();
    test_type_identity<int (Class::*)() const&& noexcept>();

    test_type_identity<int (Class::*)(int)>();
    test_type_identity<int (Class::*)(int)&>();
    test_type_identity<int (Class::*)(int) &&>();
    test_type_identity<int (Class::*)(int) const>();
    test_type_identity<int (Class::*)(int) const&>();
    test_type_identity<int (Class::*)(int) const&&>();
    test_type_identity<int (Class::*)(int) noexcept>();
    test_type_identity<int (Class::*)(int)& noexcept>();
    test_type_identity<int (Class::*)(int)&& noexcept>();
    test_type_identity<int (Class::*)(int) const noexcept>();
    test_type_identity<int (Class::*)(int) const& noexcept>();
    test_type_identity<int (Class::*)(int) const&& noexcept>();

    test_type_identity<int (Class::*)(...)>();
    test_type_identity<int (Class::*)(...)&>();
    test_type_identity<int (Class::*)(...) &&>();
    test_type_identity<int (Class::*)(...) const>();
    test_type_identity<int (Class::*)(...) const&>();
    test_type_identity<int (Class::*)(...) const&&>();
    test_type_identity<int (Class::*)(...) noexcept>();
    test_type_identity<int (Class::*)(...)& noexcept>();
    test_type_identity<int (Class::*)(...)&& noexcept>();
    test_type_identity<int (Class::*)(...) const noexcept>();
    test_type_identity<int (Class::*)(...) const& noexcept>();
    test_type_identity<int (Class::*)(...) const&& noexcept>();

    test_type_identity<int (Class::*)(int, ...)>();
    test_type_identity<int (Class::*)(int, ...)&>();
    test_type_identity<int (Class::*)(int, ...) &&>();
    test_type_identity<int (Class::*)(int, ...) const>();
    test_type_identity<int (Class::*)(int, ...) const&>();
    test_type_identity<int (Class::*)(int, ...) const&&>();
    test_type_identity<int (Class::*)(int, ...) noexcept>();
    test_type_identity<int (Class::*)(int, ...)& noexcept>();
    test_type_identity<int (Class::*)(int, ...)&& noexcept>();
    test_type_identity<int (Class::*)(int, ...) const noexcept>();
    test_type_identity<int (Class::*)(int, ...) const& noexcept>();
    test_type_identity<int (Class::*)(int, ...) const&& noexcept>();
}
