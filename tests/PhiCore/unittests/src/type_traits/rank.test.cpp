#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/rank.hpp>
#include <phi/type_traits/remove_all_extents.hpp>
#include <type_traits>
#include <vector>

template <typename T, unsigned A>
void test_rank_impl()
{
    STATIC_REQUIRE(phi::rank<T>::value == A);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::rank_v<T> == A);
#endif

    // Standard compatibililty
    STATIC_REQUIRE(std::rank<T>::value == A);
}
template <typename T, unsigned A = 0>
void test_rank()
{
    test_rank_impl<T, A>();
    test_rank_impl<const T, A>();
    test_rank_impl<volatile T, A>();
    test_rank_impl<const volatile T, A>();

    test_rank_impl<phi::remove_all_extents_t<T>, 0>();
    test_rank_impl<phi::remove_all_extents_t<const T>, 0>();
    test_rank_impl<phi::remove_all_extents_t<volatile T>, 0>();
    test_rank_impl<phi::remove_all_extents_t<const volatile T>, 0>();
}

TEST_CASE("rank")
{
    test_rank<char[], 1>();
    test_rank<char[3], 1>();
    test_rank<char[1], 1>();
    test_rank<char[][3], 2>();
    test_rank<char[2][3], 2>();
    test_rank<char[][4][3], 3>();
    test_rank<char[2][4][3], 3>();
    test_rank<char[][2][4][3], 4>();
    test_rank<char[1][2][4][3], 4>();
    test_rank<char[][1][2][4][3], 5>();
    test_rank<char[5][1][2][4][3], 5>();
    test_rank<Class[], 1>();
    test_rank<Class[1], 1>();
    test_rank<Class[][1], 2>();
    test_rank<Class[2][1], 2>();
    test_rank<Class[][2][1], 3>();
    test_rank<Class[3][2][1], 3>();
    test_rank<Class[][3][2][1], 4>();
    test_rank<Class[4][3][2][1], 4>();
    test_rank<Class[][4][3][2][1], 5>();
    test_rank<Class[5][4][3][2][1], 5>();

    test_rank<void>();
    test_rank<phi::nullptr_t>();
    test_rank<bool>();
    test_rank<char>();
    test_rank<signed char>();
    test_rank<unsigned char>();
    test_rank<short>();
    test_rank<unsigned short>();
    test_rank<int>();
    test_rank<unsigned int>();
    test_rank<long>();
    test_rank<unsigned long>();
    test_rank<long long>();
    test_rank<unsigned long long>();
    test_rank<float>();
    test_rank<double>();
    test_rank<long double>();
    test_rank<char8_t>();
    test_rank<char16_t>();
    test_rank<char32_t>();
    test_rank<wchar_t>();

    test_rank<phi::boolean>();
    test_rank<phi::integer<signed char>>();
    test_rank<phi::integer<unsigned char>>();
    test_rank<phi::integer<short>>();
    test_rank<phi::integer<unsigned short>>();
    test_rank<phi::integer<int>>();
    test_rank<phi::integer<unsigned int>>();
    test_rank<phi::integer<long>>();
    test_rank<phi::integer<unsigned long>>();
    test_rank<phi::integer<long long>>();
    test_rank<phi::integer<unsigned long long>>();
    test_rank<phi::floating_point<float>>();
    test_rank<phi::floating_point<double>>();
    test_rank<phi::floating_point<long double>>();

    test_rank<std::vector<int>>();
    test_rank<phi::scope_ptr<int>>();

    test_rank<int&>();
    test_rank<const int&>();
    test_rank<volatile int&>();
    test_rank<const volatile int&>();
    test_rank<int&&>();
    test_rank<const int&&>();
    test_rank<volatile int&&>();
    test_rank<const volatile int&&>();
    test_rank<int*>();
    test_rank<const int*>();
    test_rank<volatile int*>();
    test_rank<const volatile int*>();
    test_rank<int**>();
    test_rank<const int**>();
    test_rank<volatile int**>();
    test_rank<const volatile int**>();
    test_rank<int*&>();
    test_rank<const int*&>();
    test_rank<volatile int*&>();
    test_rank<const volatile int*&>();
    test_rank<int*&&>();
    test_rank<const int*&&>();
    test_rank<volatile int*&&>();
    test_rank<const volatile int*&&>();
    test_rank<void*>();
    test_rank<char[3], 1>();
    test_rank<char[], 1>();
    test_rank<char* [3], 1>();
    test_rank<char*[], 1>();
    test_rank<int(*)[3]>();
    test_rank<int(*)[]>();
    test_rank<int(&)[3]>();
    test_rank<int(&)[]>();
    test_rank<int(&&)[3]>();
    test_rank<int(&&)[]>();
    test_rank<char[3][2], 2>();
    test_rank<char[][2], 2>();
    test_rank<char* [3][2], 2>();
    test_rank<char*[][2], 2>();
    test_rank<int(*)[3][2]>();
    test_rank<int(*)[][2]>();
    test_rank<int(&)[3][2]>();
    test_rank<int(&)[][2]>();
    test_rank<int(&&)[3][2]>();
    test_rank<int(&&)[][2]>();
    test_rank<Class>();
    test_rank<Class[], 1>();
    test_rank<Class[2], 1>();
    test_rank<Template<void>>();
    test_rank<Template<int>>();
    test_rank<Template<Class>>();
    test_rank<Template<IncompleteType>>();
    test_rank<VariadicTemplate<>>();
    test_rank<VariadicTemplate<void>>();
    test_rank<VariadicTemplate<int>>();
    test_rank<VariadicTemplate<Class>>();
    test_rank<VariadicTemplate<IncompleteType>>();
    test_rank<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_rank<PublicDerivedFromTemplate<Base>>();
    test_rank<PublicDerivedFromTemplate<Derived>>();
    test_rank<PublicDerivedFromTemplate<Class>>();
    test_rank<PrivateDerivedFromTemplate<Base>>();
    test_rank<PrivateDerivedFromTemplate<Derived>>();
    test_rank<PrivateDerivedFromTemplate<Class>>();
    test_rank<ProtectedDerivedFromTemplate<Base>>();
    test_rank<ProtectedDerivedFromTemplate<Derived>>();
    test_rank<ProtectedDerivedFromTemplate<Class>>();
    test_rank<Union>();
    test_rank<NonEmptyUnion>();
    test_rank<Empty>();
    test_rank<NotEmpty>();
    test_rank<BitZero>();
    test_rank<BitOne>();
    test_rank<Base>();
    test_rank<Derived>();
    test_rank<Abstract>();
    test_rank<PublicAbstract>();
    test_rank<PrivateAbstract>();
    test_rank<ProtectedAbstract>();
    test_rank<AbstractTemplate<int>>();
    test_rank<AbstractTemplate<double>>();
    test_rank<AbstractTemplate<Class>>();
    test_rank<AbstractTemplate<IncompleteType>>();
    test_rank<Final>();
    test_rank<PublicDestructor>();
    test_rank<ProtectedDestructor>();
    test_rank<PrivateDestructor>();
    test_rank<VirtualPublicDestructor>();
    test_rank<VirtualProtectedDestructor>();
    test_rank<VirtualPrivateDestructor>();
    test_rank<PurePublicDestructor>();
    test_rank<PureProtectedDestructor>();
    test_rank<PurePrivateDestructor>();
    test_rank<DeletedPublicDestructor>();
    test_rank<DeletedProtectedDestructor>();
    test_rank<DeletedPrivateDestructor>();
    test_rank<DeletedVirtualPublicDestructor>();
    test_rank<DeletedVirtualProtectedDestructor>();
    test_rank<DeletedVirtualPrivateDestructor>();
    test_rank<Enum>();
    test_rank<EnumSigned>();
    test_rank<EnumUnsigned>();
    test_rank<EnumClass>();
    test_rank<EnumStruct>();
    test_rank<Function>();
    test_rank<FunctionPtr>();
    test_rank<MemberObjectPtr>();
    test_rank<MemberFunctionPtr>();
    test_rank<IncompleteType>();
    test_rank<IncompleteTemplate<void>>();
    test_rank<IncompleteTemplate<int>>();
    test_rank<IncompleteTemplate<Class>>();
    test_rank<IncompleteTemplate<IncompleteType>>();
    test_rank<IncompleteVariadicTemplate<>>();
    test_rank<IncompleteVariadicTemplate<void>>();
    test_rank<IncompleteVariadicTemplate<int>>();
    test_rank<IncompleteVariadicTemplate<Class>>();
    test_rank<IncompleteVariadicTemplate<IncompleteType>>();
    test_rank<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_rank<int Class::*>();
    test_rank<float Class::*>();
    test_rank<void * Class::*>();
    test_rank<int * Class::*>();
    test_rank<int Class::*&>();
    test_rank<float Class::*&>();
    test_rank<void * Class::*&>();
    test_rank<int * Class::*&>();
    test_rank<int Class::*&&>();
    test_rank<float Class::*&&>();
    test_rank<void * Class::*&&>();
    test_rank<int * Class::*&&>();
    test_rank<int Class::*const>();
    test_rank<float Class::*const>();
    test_rank<void * Class::*const>();
    test_rank<int Class::*const&>();
    test_rank<float Class::*const&>();
    test_rank<void * Class::*const&>();
    test_rank<int Class::*const&&>();
    test_rank<float Class::*const&&>();
    test_rank<void * Class::*const&&>();
    test_rank<int Class::*volatile>();
    test_rank<float Class::*volatile>();
    test_rank<void * Class::*volatile>();
    test_rank<int Class::*volatile&>();
    test_rank<float Class::*volatile&>();
    test_rank<void * Class::*volatile&>();
    test_rank<int Class::*volatile&&>();
    test_rank<float Class::*volatile&&>();
    test_rank<void * Class::*volatile&&>();
    test_rank<int Class::*const volatile>();
    test_rank<float Class::*const volatile>();
    test_rank<void * Class::*const volatile>();
    test_rank<int Class::*const volatile&>();
    test_rank<float Class::*const volatile&>();
    test_rank<void * Class::*const volatile&>();
    test_rank<int Class::*const volatile&&>();
    test_rank<float Class::*const volatile&&>();
    test_rank<void * Class::*const volatile&&>();
    test_rank<NonCopyable>();
    test_rank<NonMoveable>();
    test_rank<NonConstructible>();
    test_rank<Tracked>();
    test_rank<TrapConstructible>();
    test_rank<TrapImplicitConversion>();
    test_rank<TrapComma>();
    test_rank<TrapCall>();
    test_rank<TrapSelfAssign>();
    test_rank<TrapDeref>();
    test_rank<TrapArraySubscript>();

    test_rank<void()>();
    test_rank<void()&>();
    test_rank<void() &&>();
    test_rank<void() const>();
    test_rank<void() const&>();
    test_rank<void() const&&>();
    test_rank<void() volatile>();
    test_rank<void() volatile&>();
    test_rank<void() volatile&&>();
    test_rank<void() const volatile>();
    test_rank<void() const volatile&>();
    test_rank<void() const volatile&&>();
    test_rank<void() noexcept>();
    test_rank<void()& noexcept>();
    test_rank<void()&& noexcept>();
    test_rank<void() const noexcept>();
    test_rank<void() const& noexcept>();
    test_rank<void() const&& noexcept>();
    test_rank<void() volatile noexcept>();
    test_rank<void() volatile& noexcept>();
    test_rank<void() volatile&& noexcept>();
    test_rank<void() const volatile noexcept>();
    test_rank<void() const volatile& noexcept>();
    test_rank<void() const volatile&& noexcept>();

    test_rank<void(int)>();
    test_rank<void(int)&>();
    test_rank<void(int) &&>();
    test_rank<void(int) const>();
    test_rank<void(int) const&>();
    test_rank<void(int) const&&>();
    test_rank<void(int) volatile>();
    test_rank<void(int) volatile&>();
    test_rank<void(int) volatile&&>();
    test_rank<void(int) const volatile>();
    test_rank<void(int) const volatile&>();
    test_rank<void(int) const volatile&&>();
    test_rank<void(int) noexcept>();
    test_rank<void(int)& noexcept>();
    test_rank<void(int)&& noexcept>();
    test_rank<void(int) const noexcept>();
    test_rank<void(int) const& noexcept>();
    test_rank<void(int) const&& noexcept>();
    test_rank<void(int) volatile noexcept>();
    test_rank<void(int) volatile& noexcept>();
    test_rank<void(int) volatile&& noexcept>();
    test_rank<void(int) const volatile noexcept>();
    test_rank<void(int) const volatile& noexcept>();
    test_rank<void(int) const volatile&& noexcept>();

    test_rank<void(...)>();
    test_rank<void(...)&>();
    test_rank<void(...) &&>();
    test_rank<void(...) const>();
    test_rank<void(...) const&>();
    test_rank<void(...) const&&>();
    test_rank<void(...) volatile>();
    test_rank<void(...) volatile&>();
    test_rank<void(...) volatile&&>();
    test_rank<void(...) const volatile>();
    test_rank<void(...) const volatile&>();
    test_rank<void(...) const volatile&&>();
    test_rank<void(...) noexcept>();
    test_rank<void(...)& noexcept>();
    test_rank<void(...)&& noexcept>();
    test_rank<void(...) const noexcept>();
    test_rank<void(...) const& noexcept>();
    test_rank<void(...) const&& noexcept>();
    test_rank<void(...) volatile noexcept>();
    test_rank<void(...) volatile& noexcept>();
    test_rank<void(...) volatile&& noexcept>();
    test_rank<void(...) const volatile noexcept>();
    test_rank<void(...) const volatile& noexcept>();
    test_rank<void(...) const volatile&& noexcept>();

    test_rank<void(int, ...)>();
    test_rank<void(int, ...)&>();
    test_rank<void(int, ...) &&>();
    test_rank<void(int, ...) const>();
    test_rank<void(int, ...) const&>();
    test_rank<void(int, ...) const&&>();
    test_rank<void(int, ...) volatile>();
    test_rank<void(int, ...) volatile&>();
    test_rank<void(int, ...) volatile&&>();
    test_rank<void(int, ...) const volatile>();
    test_rank<void(int, ...) const volatile&>();
    test_rank<void(int, ...) const volatile&&>();
    test_rank<void(int, ...) noexcept>();
    test_rank<void(int, ...)& noexcept>();
    test_rank<void(int, ...)&& noexcept>();
    test_rank<void(int, ...) const noexcept>();
    test_rank<void(int, ...) const& noexcept>();
    test_rank<void(int, ...) const&& noexcept>();
    test_rank<void(int, ...) volatile noexcept>();
    test_rank<void(int, ...) volatile& noexcept>();
    test_rank<void(int, ...) volatile&& noexcept>();
    test_rank<void(int, ...) const volatile noexcept>();
    test_rank<void(int, ...) const volatile& noexcept>();
    test_rank<void(int, ...) const volatile&& noexcept>();

    test_rank<int()>();
    test_rank<int()&>();
    test_rank<int() &&>();
    test_rank<int() const>();
    test_rank<int() const&>();
    test_rank<int() const&&>();
    test_rank<int() volatile>();
    test_rank<int() volatile&>();
    test_rank<int() volatile&&>();
    test_rank<int() const volatile>();
    test_rank<int() const volatile&>();
    test_rank<int() const volatile&&>();
    test_rank<int() noexcept>();
    test_rank<int()& noexcept>();
    test_rank<int()&& noexcept>();
    test_rank<int() const noexcept>();
    test_rank<int() const& noexcept>();
    test_rank<int() const&& noexcept>();
    test_rank<int() volatile noexcept>();
    test_rank<int() volatile& noexcept>();
    test_rank<int() volatile&& noexcept>();
    test_rank<int() const volatile noexcept>();
    test_rank<int() const volatile& noexcept>();
    test_rank<int() const volatile&& noexcept>();

    test_rank<int(int)>();
    test_rank<int(int)&>();
    test_rank<int(int) &&>();
    test_rank<int(int) const>();
    test_rank<int(int) const&>();
    test_rank<int(int) const&&>();
    test_rank<int(int) volatile>();
    test_rank<int(int) volatile&>();
    test_rank<int(int) volatile&&>();
    test_rank<int(int) const volatile>();
    test_rank<int(int) const volatile&>();
    test_rank<int(int) const volatile&&>();
    test_rank<int(int) noexcept>();
    test_rank<int(int)& noexcept>();
    test_rank<int(int)&& noexcept>();
    test_rank<int(int) const noexcept>();
    test_rank<int(int) const& noexcept>();
    test_rank<int(int) const&& noexcept>();
    test_rank<int(int) volatile noexcept>();
    test_rank<int(int) volatile& noexcept>();
    test_rank<int(int) volatile&& noexcept>();
    test_rank<int(int) const volatile noexcept>();
    test_rank<int(int) const volatile& noexcept>();
    test_rank<int(int) const volatile&& noexcept>();

    test_rank<int(...)>();
    test_rank<int(...)&>();
    test_rank<int(...) &&>();
    test_rank<int(...) const>();
    test_rank<int(...) const&>();
    test_rank<int(...) const&&>();
    test_rank<int(...) volatile>();
    test_rank<int(...) volatile&>();
    test_rank<int(...) volatile&&>();
    test_rank<int(...) const volatile>();
    test_rank<int(...) const volatile&>();
    test_rank<int(...) const volatile&&>();
    test_rank<int(...) noexcept>();
    test_rank<int(...)& noexcept>();
    test_rank<int(...)&& noexcept>();
    test_rank<int(...) const noexcept>();
    test_rank<int(...) const& noexcept>();
    test_rank<int(...) const&& noexcept>();
    test_rank<int(...) volatile noexcept>();
    test_rank<int(...) volatile& noexcept>();
    test_rank<int(...) volatile&& noexcept>();
    test_rank<int(...) const volatile noexcept>();
    test_rank<int(...) const volatile& noexcept>();
    test_rank<int(...) const volatile&& noexcept>();

    test_rank<int(int, ...)>();
    test_rank<int(int, ...)&>();
    test_rank<int(int, ...) &&>();
    test_rank<int(int, ...) const>();
    test_rank<int(int, ...) const&>();
    test_rank<int(int, ...) const&&>();
    test_rank<int(int, ...) volatile>();
    test_rank<int(int, ...) volatile&>();
    test_rank<int(int, ...) volatile&&>();
    test_rank<int(int, ...) const volatile>();
    test_rank<int(int, ...) const volatile&>();
    test_rank<int(int, ...) const volatile&&>();
    test_rank<int(int, ...) noexcept>();
    test_rank<int(int, ...)& noexcept>();
    test_rank<int(int, ...)&& noexcept>();
    test_rank<int(int, ...) const noexcept>();
    test_rank<int(int, ...) const& noexcept>();
    test_rank<int(int, ...) const&& noexcept>();
    test_rank<int(int, ...) volatile noexcept>();
    test_rank<int(int, ...) volatile& noexcept>();
    test_rank<int(int, ...) volatile&& noexcept>();
    test_rank<int(int, ...) const volatile noexcept>();
    test_rank<int(int, ...) const volatile& noexcept>();
    test_rank<int(int, ...) const volatile&& noexcept>();

    test_rank<void (*)()>();
    test_rank<void (*)() noexcept>();

    test_rank<void (*)(int)>();
    test_rank<void (*)(int) noexcept>();

    test_rank<void (*)(...)>();
    test_rank<void (*)(...) noexcept>();

    test_rank<void (*)(int, ...)>();
    test_rank<void (*)(int, ...) noexcept>();

    test_rank<int (*)()>();
    test_rank<int (*)() noexcept>();

    test_rank<int (*)(int)>();
    test_rank<int (*)(int) noexcept>();

    test_rank<int (*)(...)>();
    test_rank<int (*)(...) noexcept>();

    test_rank<int (*)(int, ...)>();
    test_rank<int (*)(int, ...) noexcept>();

    test_rank<void (&)()>();
    test_rank<void (&)() noexcept>();

    test_rank<void (&)(int)>();
    test_rank<void (&)(int) noexcept>();

    test_rank<void (&)(...)>();
    test_rank<void (&)(...) noexcept>();

    test_rank<void (&)(int, ...)>();
    test_rank<void (&)(int, ...) noexcept>();

    test_rank<int (&)()>();
    test_rank<int (&)() noexcept>();

    test_rank<int (&)(int)>();
    test_rank<int (&)(int) noexcept>();

    test_rank<int (&)(...)>();
    test_rank<int (&)(...) noexcept>();

    test_rank<int (&)(int, ...)>();
    test_rank<int (&)(int, ...) noexcept>();

    test_rank<void(&&)()>();
    test_rank<void(&&)() noexcept>();

    test_rank<void(&&)(int)>();
    test_rank<void(&&)(int) noexcept>();

    test_rank<void(&&)(...)>();
    test_rank<void(&&)(...) noexcept>();

    test_rank<void(&&)(int, ...)>();
    test_rank<void(&&)(int, ...) noexcept>();

    test_rank<int(&&)()>();
    test_rank<int(&&)() noexcept>();

    test_rank<int(&&)(int)>();
    test_rank<int(&&)(int) noexcept>();

    test_rank<int(&&)(...)>();
    test_rank<int(&&)(...) noexcept>();

    test_rank<int(&&)(int, ...)>();
    test_rank<int(&&)(int, ...) noexcept>();

    test_rank<void (Class::*)()>();
    test_rank<void (Class::*)()&>();
    test_rank<void (Class::*)() &&>();
    test_rank<void (Class::*)() const>();
    test_rank<void (Class::*)() const&>();
    test_rank<void (Class::*)() const&&>();
    test_rank<void (Class::*)() noexcept>();
    test_rank<void (Class::*)()& noexcept>();
    test_rank<void (Class::*)()&& noexcept>();
    test_rank<void (Class::*)() const noexcept>();
    test_rank<void (Class::*)() const& noexcept>();
    test_rank<void (Class::*)() const&& noexcept>();

    test_rank<void (Class::*)(int)>();
    test_rank<void (Class::*)(int)&>();
    test_rank<void (Class::*)(int) &&>();
    test_rank<void (Class::*)(int) const>();
    test_rank<void (Class::*)(int) const&>();
    test_rank<void (Class::*)(int) const&&>();
    test_rank<void (Class::*)(int) noexcept>();
    test_rank<void (Class::*)(int)& noexcept>();
    test_rank<void (Class::*)(int)&& noexcept>();
    test_rank<void (Class::*)(int) const noexcept>();
    test_rank<void (Class::*)(int) const& noexcept>();
    test_rank<void (Class::*)(int) const&& noexcept>();

    test_rank<void (Class::*)(...)>();
    test_rank<void (Class::*)(...)&>();
    test_rank<void (Class::*)(...) &&>();
    test_rank<void (Class::*)(...) const>();
    test_rank<void (Class::*)(...) const&>();
    test_rank<void (Class::*)(...) const&&>();
    test_rank<void (Class::*)(...) noexcept>();
    test_rank<void (Class::*)(...)& noexcept>();
    test_rank<void (Class::*)(...)&& noexcept>();
    test_rank<void (Class::*)(...) const noexcept>();
    test_rank<void (Class::*)(...) const& noexcept>();
    test_rank<void (Class::*)(...) const&& noexcept>();

    test_rank<void (Class::*)(int, ...)>();
    test_rank<void (Class::*)(int, ...)&>();
    test_rank<void (Class::*)(int, ...) &&>();
    test_rank<void (Class::*)(int, ...) const>();
    test_rank<void (Class::*)(int, ...) const&>();
    test_rank<void (Class::*)(int, ...) const&&>();
    test_rank<void (Class::*)(int, ...) noexcept>();
    test_rank<void (Class::*)(int, ...)& noexcept>();
    test_rank<void (Class::*)(int, ...)&& noexcept>();
    test_rank<void (Class::*)(int, ...) const noexcept>();
    test_rank<void (Class::*)(int, ...) const& noexcept>();
    test_rank<void (Class::*)(int, ...) const&& noexcept>();

    test_rank<int (Class::*)()>();
    test_rank<int (Class::*)()&>();
    test_rank<int (Class::*)() &&>();
    test_rank<int (Class::*)() const>();
    test_rank<int (Class::*)() const&>();
    test_rank<int (Class::*)() const&&>();
    test_rank<int (Class::*)() noexcept>();
    test_rank<int (Class::*)()& noexcept>();
    test_rank<int (Class::*)()&& noexcept>();
    test_rank<int (Class::*)() const noexcept>();
    test_rank<int (Class::*)() const& noexcept>();
    test_rank<int (Class::*)() const&& noexcept>();

    test_rank<int (Class::*)(int)>();
    test_rank<int (Class::*)(int)&>();
    test_rank<int (Class::*)(int) &&>();
    test_rank<int (Class::*)(int) const>();
    test_rank<int (Class::*)(int) const&>();
    test_rank<int (Class::*)(int) const&&>();
    test_rank<int (Class::*)(int) noexcept>();
    test_rank<int (Class::*)(int)& noexcept>();
    test_rank<int (Class::*)(int)&& noexcept>();
    test_rank<int (Class::*)(int) const noexcept>();
    test_rank<int (Class::*)(int) const& noexcept>();
    test_rank<int (Class::*)(int) const&& noexcept>();

    test_rank<int (Class::*)(...)>();
    test_rank<int (Class::*)(...)&>();
    test_rank<int (Class::*)(...) &&>();
    test_rank<int (Class::*)(...) const>();
    test_rank<int (Class::*)(...) const&>();
    test_rank<int (Class::*)(...) const&&>();
    test_rank<int (Class::*)(...) noexcept>();
    test_rank<int (Class::*)(...)& noexcept>();
    test_rank<int (Class::*)(...)&& noexcept>();
    test_rank<int (Class::*)(...) const noexcept>();
    test_rank<int (Class::*)(...) const& noexcept>();
    test_rank<int (Class::*)(...) const&& noexcept>();

    test_rank<int (Class::*)(int, ...)>();
    test_rank<int (Class::*)(int, ...)&>();
    test_rank<int (Class::*)(int, ...) &&>();
    test_rank<int (Class::*)(int, ...) const>();
    test_rank<int (Class::*)(int, ...) const&>();
    test_rank<int (Class::*)(int, ...) const&&>();
    test_rank<int (Class::*)(int, ...) noexcept>();
    test_rank<int (Class::*)(int, ...)& noexcept>();
    test_rank<int (Class::*)(int, ...)&& noexcept>();
    test_rank<int (Class::*)(int, ...) const noexcept>();
    test_rank<int (Class::*)(int, ...) const& noexcept>();
    test_rank<int (Class::*)(int, ...) const&& noexcept>();
}
