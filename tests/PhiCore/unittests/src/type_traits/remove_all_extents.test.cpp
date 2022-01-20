#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_all_extents.hpp>
#include <type_traits>
#include <vector>

template <typename T, typename U>
void test_remove_all_extents_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_all_extents<T>::type, U);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    CHECK_SAME_TYPE(phi::remove_all_extents_t<T>, U);
#endif

    // Standard compatibililty
    CHECK_SAME_TYPE(typename std::remove_all_extents<T>::type, U);
}

template <typename T, typename U = T>
void test_remove_all_extents()
{
    test_remove_all_extents_impl<T, U>();
    test_remove_all_extents_impl<const T, const U>();
    test_remove_all_extents_impl<volatile T, volatile U>();
    test_remove_all_extents_impl<const volatile T, const volatile U>();
}

TEST_CASE("remove_all_extents")
{
    test_remove_all_extents<int[], int>();
    test_remove_all_extents<int[2], int>();
    test_remove_all_extents<int[][3], int>();
    test_remove_all_extents<int[2][3], int>();
    test_remove_all_extents<int[][3][4], int>();
    test_remove_all_extents<int[2][3][4], int>();
    test_remove_all_extents<float[], float>();
    test_remove_all_extents<float[2], float>();
    test_remove_all_extents<float[][3], float>();
    test_remove_all_extents<float[2][3], float>();
    test_remove_all_extents<float[][3][4], float>();
    test_remove_all_extents<float[2][3][4], float>();
    test_remove_all_extents<Class[], Class>();
    test_remove_all_extents<Class[2], Class>();
    test_remove_all_extents<Class[][3], Class>();
    test_remove_all_extents<Class[2][3], Class>();
    test_remove_all_extents<Class[][3][4], Class>();
    test_remove_all_extents<Class[2][3][4], Class>();

    test_remove_all_extents<void>();
    test_remove_all_extents<phi::nullptr_t>();
    test_remove_all_extents<bool>();
    test_remove_all_extents<char>();
    test_remove_all_extents<signed char>();
    test_remove_all_extents<unsigned char>();
    test_remove_all_extents<short>();
    test_remove_all_extents<unsigned short>();
    test_remove_all_extents<int>();
    test_remove_all_extents<unsigned int>();
    test_remove_all_extents<long>();
    test_remove_all_extents<unsigned long>();
    test_remove_all_extents<long long>();
    test_remove_all_extents<unsigned long long>();
    test_remove_all_extents<float>();
    test_remove_all_extents<double>();
    test_remove_all_extents<long double>();
    test_remove_all_extents<char8_t>();
    test_remove_all_extents<char16_t>();
    test_remove_all_extents<char32_t>();
    test_remove_all_extents<wchar_t>();

    test_remove_all_extents<phi::boolean>();
    test_remove_all_extents<phi::integer<signed char>>();
    test_remove_all_extents<phi::integer<unsigned char>>();
    test_remove_all_extents<phi::integer<short>>();
    test_remove_all_extents<phi::integer<unsigned short>>();
    test_remove_all_extents<phi::integer<int>>();
    test_remove_all_extents<phi::integer<unsigned int>>();
    test_remove_all_extents<phi::integer<long>>();
    test_remove_all_extents<phi::integer<unsigned long>>();
    test_remove_all_extents<phi::integer<long long>>();
    test_remove_all_extents<phi::integer<unsigned long long>>();
    test_remove_all_extents<phi::floating_point<float>>();
    test_remove_all_extents<phi::floating_point<double>>();
    test_remove_all_extents<phi::floating_point<long double>>();

    test_remove_all_extents<std::vector<int>>();
    test_remove_all_extents<phi::scope_ptr<int>>();

    test_remove_all_extents<int&>();
    test_remove_all_extents<const int&>();
    test_remove_all_extents<volatile int&>();
    test_remove_all_extents<const volatile int&>();
    test_remove_all_extents<int&&>();
    test_remove_all_extents<const int&&>();
    test_remove_all_extents<volatile int&&>();
    test_remove_all_extents<const volatile int&&>();
    test_remove_all_extents<int*>();
    test_remove_all_extents<const int*>();
    test_remove_all_extents<volatile int*>();
    test_remove_all_extents<const volatile int*>();
    test_remove_all_extents<int**>();
    test_remove_all_extents<const int**>();
    test_remove_all_extents<volatile int**>();
    test_remove_all_extents<const volatile int**>();
    test_remove_all_extents<int*&>();
    test_remove_all_extents<const int*&>();
    test_remove_all_extents<volatile int*&>();
    test_remove_all_extents<const volatile int*&>();
    test_remove_all_extents<int*&&>();
    test_remove_all_extents<const int*&&>();
    test_remove_all_extents<volatile int*&&>();
    test_remove_all_extents<const volatile int*&&>();
    test_remove_all_extents<void*>();
    test_remove_all_extents<char[3], char>();
    test_remove_all_extents<char[], char>();
    test_remove_all_extents<char* [3], char*>();
    test_remove_all_extents<char*[], char*>();
    test_remove_all_extents<int(*)[3]>();
    test_remove_all_extents<int(*)[]>();
    test_remove_all_extents<int(&)[3]>();
    test_remove_all_extents<int(&)[]>();
    test_remove_all_extents<int(&&)[3]>();
    test_remove_all_extents<int(&&)[]>();
    test_remove_all_extents<char[3][2], char>();
    test_remove_all_extents<char[][2], char>();
    test_remove_all_extents<char* [3][2], char*>();
    test_remove_all_extents<char*[][2], char*>();
    test_remove_all_extents<int(*)[3][2]>();
    test_remove_all_extents<int(*)[][2]>();
    test_remove_all_extents<int(&)[3][2]>();
    test_remove_all_extents<int(&)[][2]>();
    test_remove_all_extents<int(&&)[3][2]>();
    test_remove_all_extents<int(&&)[][2]>();
    test_remove_all_extents<Class>();
    test_remove_all_extents<Class[], Class>();
    test_remove_all_extents<Class[2], Class>();
    test_remove_all_extents<Template<void>>();
    test_remove_all_extents<Template<int>>();
    test_remove_all_extents<Template<Class>>();
    test_remove_all_extents<Template<incomplete_type>>();
    test_remove_all_extents<VariadicTemplate<>>();
    test_remove_all_extents<VariadicTemplate<void>>();
    test_remove_all_extents<VariadicTemplate<int>>();
    test_remove_all_extents<VariadicTemplate<Class>>();
    test_remove_all_extents<VariadicTemplate<incomplete_type>>();
    test_remove_all_extents<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_all_extents<PublicDerviedFromTemplate<Base>>();
    test_remove_all_extents<PublicDerviedFromTemplate<Derived>>();
    test_remove_all_extents<PublicDerviedFromTemplate<Class>>();
    test_remove_all_extents<PrivateDerviedFromTemplate<Base>>();
    test_remove_all_extents<PrivateDerviedFromTemplate<Derived>>();
    test_remove_all_extents<PrivateDerviedFromTemplate<Class>>();
    test_remove_all_extents<ProtectedDerviedFromTemplate<Base>>();
    test_remove_all_extents<ProtectedDerviedFromTemplate<Derived>>();
    test_remove_all_extents<ProtectedDerviedFromTemplate<Class>>();
    test_remove_all_extents<Union>();
    test_remove_all_extents<NonEmptyUnion>();
    test_remove_all_extents<Empty>();
    test_remove_all_extents<NotEmpty>();
    test_remove_all_extents<bit_zero>();
    test_remove_all_extents<bit_one>();
    test_remove_all_extents<Base>();
    test_remove_all_extents<Derived>();
    test_remove_all_extents<Abstract>();
    test_remove_all_extents<PublicAbstract>();
    test_remove_all_extents<PrivateAbstract>();
    test_remove_all_extents<ProtectedAbstract>();
    test_remove_all_extents<AbstractTemplate<int>>();
    test_remove_all_extents<AbstractTemplate<double>>();
    test_remove_all_extents<AbstractTemplate<Class>>();
    test_remove_all_extents<AbstractTemplate<incomplete_type>>();
    test_remove_all_extents<Final>();
    test_remove_all_extents<PublicDestructor>();
    test_remove_all_extents<ProtectedDestructor>();
    test_remove_all_extents<PrivateDestructor>();
    test_remove_all_extents<VirtualPublicDestructor>();
    test_remove_all_extents<VirtualProtectedDestructor>();
    test_remove_all_extents<VirtualPrivateDestructor>();
    test_remove_all_extents<PurePublicDestructor>();
    test_remove_all_extents<PureProtectedDestructor>();
    test_remove_all_extents<PurePrivateDestructor>();
    test_remove_all_extents<DeletedPublicDestructor>();
    test_remove_all_extents<DeletedProtectedDestructor>();
    test_remove_all_extents<DeletedPrivateDestructor>();
    test_remove_all_extents<DeletedVirtualPublicDestructor>();
    test_remove_all_extents<DeletedVirtualProtectedDestructor>();
    test_remove_all_extents<DeletedVirtualPrivateDestructor>();
    test_remove_all_extents<Enum>();
    test_remove_all_extents<EnumSigned>();
    test_remove_all_extents<EnumUnsigned>();
    test_remove_all_extents<EnumClass>();
    test_remove_all_extents<EnumStruct>();
    test_remove_all_extents<Function>();
    test_remove_all_extents<FunctionPtr>();
    test_remove_all_extents<MemberObjectPtr>();
    test_remove_all_extents<MemberFunctionPtr>();
    test_remove_all_extents<incomplete_type>();
    test_remove_all_extents<IncompleteTemplate<void>>();
    test_remove_all_extents<IncompleteTemplate<int>>();
    test_remove_all_extents<IncompleteTemplate<Class>>();
    test_remove_all_extents<IncompleteTemplate<incomplete_type>>();
    test_remove_all_extents<IncompleteVariadicTemplate<>>();
    test_remove_all_extents<IncompleteVariadicTemplate<void>>();
    test_remove_all_extents<IncompleteVariadicTemplate<int>>();
    test_remove_all_extents<IncompleteVariadicTemplate<Class>>();
    test_remove_all_extents<IncompleteVariadicTemplate<incomplete_type>>();
    test_remove_all_extents<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_remove_all_extents<int Class::*>();
    test_remove_all_extents<float Class::*>();
    test_remove_all_extents<void * Class::*>();
    test_remove_all_extents<int * Class::*>();
    test_remove_all_extents<int Class::*&>();
    test_remove_all_extents<float Class::*&>();
    test_remove_all_extents<void * Class::*&>();
    test_remove_all_extents<int * Class::*&>();
    test_remove_all_extents<int Class::*&&>();
    test_remove_all_extents<float Class::*&&>();
    test_remove_all_extents<void * Class::*&&>();
    test_remove_all_extents<int * Class::*&&>();
    test_remove_all_extents<int Class::*const>();
    test_remove_all_extents<float Class::*const>();
    test_remove_all_extents<void * Class::*const>();
    test_remove_all_extents<int Class::*const&>();
    test_remove_all_extents<float Class::*const&>();
    test_remove_all_extents<void * Class::*const&>();
    test_remove_all_extents<int Class::*const&&>();
    test_remove_all_extents<float Class::*const&&>();
    test_remove_all_extents<void * Class::*const&&>();
    test_remove_all_extents<int Class::*volatile>();
    test_remove_all_extents<float Class::*volatile>();
    test_remove_all_extents<void * Class::*volatile>();
    test_remove_all_extents<int Class::*volatile&>();
    test_remove_all_extents<float Class::*volatile&>();
    test_remove_all_extents<void * Class::*volatile&>();
    test_remove_all_extents<int Class::*volatile&&>();
    test_remove_all_extents<float Class::*volatile&&>();
    test_remove_all_extents<void * Class::*volatile&&>();
    test_remove_all_extents<int Class::*const volatile>();
    test_remove_all_extents<float Class::*const volatile>();
    test_remove_all_extents<void * Class::*const volatile>();
    test_remove_all_extents<int Class::*const volatile&>();
    test_remove_all_extents<float Class::*const volatile&>();
    test_remove_all_extents<void * Class::*const volatile&>();
    test_remove_all_extents<int Class::*const volatile&&>();
    test_remove_all_extents<float Class::*const volatile&&>();
    test_remove_all_extents<void * Class::*const volatile&&>();
    test_remove_all_extents<NonCopyable>();
    test_remove_all_extents<NonMoveable>();
    test_remove_all_extents<NonConstructible>();
    test_remove_all_extents<Tracked>();
    test_remove_all_extents<TrapConstructible>();
    test_remove_all_extents<TrapImplicitConversion>();
    test_remove_all_extents<TrapComma>();
    test_remove_all_extents<TrapCall>();
    test_remove_all_extents<TrapSelfAssign>();
    test_remove_all_extents<TrapDeref>();
    test_remove_all_extents<TrapArraySubscript>();

    test_remove_all_extents<void()>();
    test_remove_all_extents<void()&>();
    test_remove_all_extents<void() &&>();
    test_remove_all_extents<void() const>();
    test_remove_all_extents<void() const&>();
    test_remove_all_extents<void() const&&>();
    test_remove_all_extents<void() volatile>();
    test_remove_all_extents<void() volatile&>();
    test_remove_all_extents<void() volatile&&>();
    test_remove_all_extents<void() const volatile>();
    test_remove_all_extents<void() const volatile&>();
    test_remove_all_extents<void() const volatile&&>();
    test_remove_all_extents<void() noexcept>();
    test_remove_all_extents<void()& noexcept>();
    test_remove_all_extents<void()&& noexcept>();
    test_remove_all_extents<void() const noexcept>();
    test_remove_all_extents<void() const& noexcept>();
    test_remove_all_extents<void() const&& noexcept>();
    test_remove_all_extents<void() volatile noexcept>();
    test_remove_all_extents<void() volatile& noexcept>();
    test_remove_all_extents<void() volatile&& noexcept>();
    test_remove_all_extents<void() const volatile noexcept>();
    test_remove_all_extents<void() const volatile& noexcept>();
    test_remove_all_extents<void() const volatile&& noexcept>();

    test_remove_all_extents<void(int)>();
    test_remove_all_extents<void(int)&>();
    test_remove_all_extents<void(int) &&>();
    test_remove_all_extents<void(int) const>();
    test_remove_all_extents<void(int) const&>();
    test_remove_all_extents<void(int) const&&>();
    test_remove_all_extents<void(int) volatile>();
    test_remove_all_extents<void(int) volatile&>();
    test_remove_all_extents<void(int) volatile&&>();
    test_remove_all_extents<void(int) const volatile>();
    test_remove_all_extents<void(int) const volatile&>();
    test_remove_all_extents<void(int) const volatile&&>();
    test_remove_all_extents<void(int) noexcept>();
    test_remove_all_extents<void(int)& noexcept>();
    test_remove_all_extents<void(int)&& noexcept>();
    test_remove_all_extents<void(int) const noexcept>();
    test_remove_all_extents<void(int) const& noexcept>();
    test_remove_all_extents<void(int) const&& noexcept>();
    test_remove_all_extents<void(int) volatile noexcept>();
    test_remove_all_extents<void(int) volatile& noexcept>();
    test_remove_all_extents<void(int) volatile&& noexcept>();
    test_remove_all_extents<void(int) const volatile noexcept>();
    test_remove_all_extents<void(int) const volatile& noexcept>();
    test_remove_all_extents<void(int) const volatile&& noexcept>();

    test_remove_all_extents<void(...)>();
    test_remove_all_extents<void(...)&>();
    test_remove_all_extents<void(...) &&>();
    test_remove_all_extents<void(...) const>();
    test_remove_all_extents<void(...) const&>();
    test_remove_all_extents<void(...) const&&>();
    test_remove_all_extents<void(...) volatile>();
    test_remove_all_extents<void(...) volatile&>();
    test_remove_all_extents<void(...) volatile&&>();
    test_remove_all_extents<void(...) const volatile>();
    test_remove_all_extents<void(...) const volatile&>();
    test_remove_all_extents<void(...) const volatile&&>();
    test_remove_all_extents<void(...) noexcept>();
    test_remove_all_extents<void(...)& noexcept>();
    test_remove_all_extents<void(...)&& noexcept>();
    test_remove_all_extents<void(...) const noexcept>();
    test_remove_all_extents<void(...) const& noexcept>();
    test_remove_all_extents<void(...) const&& noexcept>();
    test_remove_all_extents<void(...) volatile noexcept>();
    test_remove_all_extents<void(...) volatile& noexcept>();
    test_remove_all_extents<void(...) volatile&& noexcept>();
    test_remove_all_extents<void(...) const volatile noexcept>();
    test_remove_all_extents<void(...) const volatile& noexcept>();
    test_remove_all_extents<void(...) const volatile&& noexcept>();

    test_remove_all_extents<void(int, ...)>();
    test_remove_all_extents<void(int, ...)&>();
    test_remove_all_extents<void(int, ...) &&>();
    test_remove_all_extents<void(int, ...) const>();
    test_remove_all_extents<void(int, ...) const&>();
    test_remove_all_extents<void(int, ...) const&&>();
    test_remove_all_extents<void(int, ...) volatile>();
    test_remove_all_extents<void(int, ...) volatile&>();
    test_remove_all_extents<void(int, ...) volatile&&>();
    test_remove_all_extents<void(int, ...) const volatile>();
    test_remove_all_extents<void(int, ...) const volatile&>();
    test_remove_all_extents<void(int, ...) const volatile&&>();
    test_remove_all_extents<void(int, ...) noexcept>();
    test_remove_all_extents<void(int, ...)& noexcept>();
    test_remove_all_extents<void(int, ...)&& noexcept>();
    test_remove_all_extents<void(int, ...) const noexcept>();
    test_remove_all_extents<void(int, ...) const& noexcept>();
    test_remove_all_extents<void(int, ...) const&& noexcept>();
    test_remove_all_extents<void(int, ...) volatile noexcept>();
    test_remove_all_extents<void(int, ...) volatile& noexcept>();
    test_remove_all_extents<void(int, ...) volatile&& noexcept>();
    test_remove_all_extents<void(int, ...) const volatile noexcept>();
    test_remove_all_extents<void(int, ...) const volatile& noexcept>();
    test_remove_all_extents<void(int, ...) const volatile&& noexcept>();

    test_remove_all_extents<int()>();
    test_remove_all_extents<int()&>();
    test_remove_all_extents<int() &&>();
    test_remove_all_extents<int() const>();
    test_remove_all_extents<int() const&>();
    test_remove_all_extents<int() const&&>();
    test_remove_all_extents<int() volatile>();
    test_remove_all_extents<int() volatile&>();
    test_remove_all_extents<int() volatile&&>();
    test_remove_all_extents<int() const volatile>();
    test_remove_all_extents<int() const volatile&>();
    test_remove_all_extents<int() const volatile&&>();
    test_remove_all_extents<int() noexcept>();
    test_remove_all_extents<int()& noexcept>();
    test_remove_all_extents<int()&& noexcept>();
    test_remove_all_extents<int() const noexcept>();
    test_remove_all_extents<int() const& noexcept>();
    test_remove_all_extents<int() const&& noexcept>();
    test_remove_all_extents<int() volatile noexcept>();
    test_remove_all_extents<int() volatile& noexcept>();
    test_remove_all_extents<int() volatile&& noexcept>();
    test_remove_all_extents<int() const volatile noexcept>();
    test_remove_all_extents<int() const volatile& noexcept>();
    test_remove_all_extents<int() const volatile&& noexcept>();

    test_remove_all_extents<int(int)>();
    test_remove_all_extents<int(int)&>();
    test_remove_all_extents<int(int) &&>();
    test_remove_all_extents<int(int) const>();
    test_remove_all_extents<int(int) const&>();
    test_remove_all_extents<int(int) const&&>();
    test_remove_all_extents<int(int) volatile>();
    test_remove_all_extents<int(int) volatile&>();
    test_remove_all_extents<int(int) volatile&&>();
    test_remove_all_extents<int(int) const volatile>();
    test_remove_all_extents<int(int) const volatile&>();
    test_remove_all_extents<int(int) const volatile&&>();
    test_remove_all_extents<int(int) noexcept>();
    test_remove_all_extents<int(int)& noexcept>();
    test_remove_all_extents<int(int)&& noexcept>();
    test_remove_all_extents<int(int) const noexcept>();
    test_remove_all_extents<int(int) const& noexcept>();
    test_remove_all_extents<int(int) const&& noexcept>();
    test_remove_all_extents<int(int) volatile noexcept>();
    test_remove_all_extents<int(int) volatile& noexcept>();
    test_remove_all_extents<int(int) volatile&& noexcept>();
    test_remove_all_extents<int(int) const volatile noexcept>();
    test_remove_all_extents<int(int) const volatile& noexcept>();
    test_remove_all_extents<int(int) const volatile&& noexcept>();

    test_remove_all_extents<int(...)>();
    test_remove_all_extents<int(...)&>();
    test_remove_all_extents<int(...) &&>();
    test_remove_all_extents<int(...) const>();
    test_remove_all_extents<int(...) const&>();
    test_remove_all_extents<int(...) const&&>();
    test_remove_all_extents<int(...) volatile>();
    test_remove_all_extents<int(...) volatile&>();
    test_remove_all_extents<int(...) volatile&&>();
    test_remove_all_extents<int(...) const volatile>();
    test_remove_all_extents<int(...) const volatile&>();
    test_remove_all_extents<int(...) const volatile&&>();
    test_remove_all_extents<int(...) noexcept>();
    test_remove_all_extents<int(...)& noexcept>();
    test_remove_all_extents<int(...)&& noexcept>();
    test_remove_all_extents<int(...) const noexcept>();
    test_remove_all_extents<int(...) const& noexcept>();
    test_remove_all_extents<int(...) const&& noexcept>();
    test_remove_all_extents<int(...) volatile noexcept>();
    test_remove_all_extents<int(...) volatile& noexcept>();
    test_remove_all_extents<int(...) volatile&& noexcept>();
    test_remove_all_extents<int(...) const volatile noexcept>();
    test_remove_all_extents<int(...) const volatile& noexcept>();
    test_remove_all_extents<int(...) const volatile&& noexcept>();

    test_remove_all_extents<int(int, ...)>();
    test_remove_all_extents<int(int, ...)&>();
    test_remove_all_extents<int(int, ...) &&>();
    test_remove_all_extents<int(int, ...) const>();
    test_remove_all_extents<int(int, ...) const&>();
    test_remove_all_extents<int(int, ...) const&&>();
    test_remove_all_extents<int(int, ...) volatile>();
    test_remove_all_extents<int(int, ...) volatile&>();
    test_remove_all_extents<int(int, ...) volatile&&>();
    test_remove_all_extents<int(int, ...) const volatile>();
    test_remove_all_extents<int(int, ...) const volatile&>();
    test_remove_all_extents<int(int, ...) const volatile&&>();
    test_remove_all_extents<int(int, ...) noexcept>();
    test_remove_all_extents<int(int, ...)& noexcept>();
    test_remove_all_extents<int(int, ...)&& noexcept>();
    test_remove_all_extents<int(int, ...) const noexcept>();
    test_remove_all_extents<int(int, ...) const& noexcept>();
    test_remove_all_extents<int(int, ...) const&& noexcept>();
    test_remove_all_extents<int(int, ...) volatile noexcept>();
    test_remove_all_extents<int(int, ...) volatile& noexcept>();
    test_remove_all_extents<int(int, ...) volatile&& noexcept>();
    test_remove_all_extents<int(int, ...) const volatile noexcept>();
    test_remove_all_extents<int(int, ...) const volatile& noexcept>();
    test_remove_all_extents<int(int, ...) const volatile&& noexcept>();

    test_remove_all_extents<void (*)()>();
    test_remove_all_extents<void (*)() noexcept>();

    test_remove_all_extents<void (*)(int)>();
    test_remove_all_extents<void (*)(int) noexcept>();

    test_remove_all_extents<void (*)(...)>();
    test_remove_all_extents<void (*)(...) noexcept>();

    test_remove_all_extents<void (*)(int, ...)>();
    test_remove_all_extents<void (*)(int, ...) noexcept>();

    test_remove_all_extents<int (*)()>();
    test_remove_all_extents<int (*)() noexcept>();

    test_remove_all_extents<int (*)(int)>();
    test_remove_all_extents<int (*)(int) noexcept>();

    test_remove_all_extents<int (*)(...)>();
    test_remove_all_extents<int (*)(...) noexcept>();

    test_remove_all_extents<int (*)(int, ...)>();
    test_remove_all_extents<int (*)(int, ...) noexcept>();

    test_remove_all_extents<void (&)()>();
    test_remove_all_extents<void (&)() noexcept>();

    test_remove_all_extents<void (&)(int)>();
    test_remove_all_extents<void (&)(int) noexcept>();

    test_remove_all_extents<void (&)(...)>();
    test_remove_all_extents<void (&)(...) noexcept>();

    test_remove_all_extents<void (&)(int, ...)>();
    test_remove_all_extents<void (&)(int, ...) noexcept>();

    test_remove_all_extents<int (&)()>();
    test_remove_all_extents<int (&)() noexcept>();

    test_remove_all_extents<int (&)(int)>();
    test_remove_all_extents<int (&)(int) noexcept>();

    test_remove_all_extents<int (&)(...)>();
    test_remove_all_extents<int (&)(...) noexcept>();

    test_remove_all_extents<int (&)(int, ...)>();
    test_remove_all_extents<int (&)(int, ...) noexcept>();

    test_remove_all_extents<void(&&)()>();
    test_remove_all_extents<void(&&)() noexcept>();

    test_remove_all_extents<void(&&)(int)>();
    test_remove_all_extents<void(&&)(int) noexcept>();

    test_remove_all_extents<void(&&)(...)>();
    test_remove_all_extents<void(&&)(...) noexcept>();

    test_remove_all_extents<void(&&)(int, ...)>();
    test_remove_all_extents<void(&&)(int, ...) noexcept>();

    test_remove_all_extents<int(&&)()>();
    test_remove_all_extents<int(&&)() noexcept>();

    test_remove_all_extents<int(&&)(int)>();
    test_remove_all_extents<int(&&)(int) noexcept>();

    test_remove_all_extents<int(&&)(...)>();
    test_remove_all_extents<int(&&)(...) noexcept>();

    test_remove_all_extents<int(&&)(int, ...)>();
    test_remove_all_extents<int(&&)(int, ...) noexcept>();

    test_remove_all_extents<void (Class::*)()>();
    test_remove_all_extents<void (Class::*)()&>();
    test_remove_all_extents<void (Class::*)() &&>();
    test_remove_all_extents<void (Class::*)() const>();
    test_remove_all_extents<void (Class::*)() const&>();
    test_remove_all_extents<void (Class::*)() const&&>();
    test_remove_all_extents<void (Class::*)() noexcept>();
    test_remove_all_extents<void (Class::*)()& noexcept>();
    test_remove_all_extents<void (Class::*)()&& noexcept>();
    test_remove_all_extents<void (Class::*)() const noexcept>();
    test_remove_all_extents<void (Class::*)() const& noexcept>();
    test_remove_all_extents<void (Class::*)() const&& noexcept>();

    test_remove_all_extents<void (Class::*)(int)>();
    test_remove_all_extents<void (Class::*)(int)&>();
    test_remove_all_extents<void (Class::*)(int) &&>();
    test_remove_all_extents<void (Class::*)(int) const>();
    test_remove_all_extents<void (Class::*)(int) const&>();
    test_remove_all_extents<void (Class::*)(int) const&&>();
    test_remove_all_extents<void (Class::*)(int) noexcept>();
    test_remove_all_extents<void (Class::*)(int)& noexcept>();
    test_remove_all_extents<void (Class::*)(int)&& noexcept>();
    test_remove_all_extents<void (Class::*)(int) const noexcept>();
    test_remove_all_extents<void (Class::*)(int) const& noexcept>();
    test_remove_all_extents<void (Class::*)(int) const&& noexcept>();

    test_remove_all_extents<void (Class::*)(...)>();
    test_remove_all_extents<void (Class::*)(...)&>();
    test_remove_all_extents<void (Class::*)(...) &&>();
    test_remove_all_extents<void (Class::*)(...) const>();
    test_remove_all_extents<void (Class::*)(...) const&>();
    test_remove_all_extents<void (Class::*)(...) const&&>();
    test_remove_all_extents<void (Class::*)(...) noexcept>();
    test_remove_all_extents<void (Class::*)(...)& noexcept>();
    test_remove_all_extents<void (Class::*)(...)&& noexcept>();
    test_remove_all_extents<void (Class::*)(...) const noexcept>();
    test_remove_all_extents<void (Class::*)(...) const& noexcept>();
    test_remove_all_extents<void (Class::*)(...) const&& noexcept>();

    test_remove_all_extents<void (Class::*)(int, ...)>();
    test_remove_all_extents<void (Class::*)(int, ...)&>();
    test_remove_all_extents<void (Class::*)(int, ...) &&>();
    test_remove_all_extents<void (Class::*)(int, ...) const>();
    test_remove_all_extents<void (Class::*)(int, ...) const&>();
    test_remove_all_extents<void (Class::*)(int, ...) const&&>();
    test_remove_all_extents<void (Class::*)(int, ...) noexcept>();
    test_remove_all_extents<void (Class::*)(int, ...)& noexcept>();
    test_remove_all_extents<void (Class::*)(int, ...)&& noexcept>();
    test_remove_all_extents<void (Class::*)(int, ...) const noexcept>();
    test_remove_all_extents<void (Class::*)(int, ...) const& noexcept>();
    test_remove_all_extents<void (Class::*)(int, ...) const&& noexcept>();

    test_remove_all_extents<int (Class::*)()>();
    test_remove_all_extents<int (Class::*)()&>();
    test_remove_all_extents<int (Class::*)() &&>();
    test_remove_all_extents<int (Class::*)() const>();
    test_remove_all_extents<int (Class::*)() const&>();
    test_remove_all_extents<int (Class::*)() const&&>();
    test_remove_all_extents<int (Class::*)() noexcept>();
    test_remove_all_extents<int (Class::*)()& noexcept>();
    test_remove_all_extents<int (Class::*)()&& noexcept>();
    test_remove_all_extents<int (Class::*)() const noexcept>();
    test_remove_all_extents<int (Class::*)() const& noexcept>();
    test_remove_all_extents<int (Class::*)() const&& noexcept>();

    test_remove_all_extents<int (Class::*)(int)>();
    test_remove_all_extents<int (Class::*)(int)&>();
    test_remove_all_extents<int (Class::*)(int) &&>();
    test_remove_all_extents<int (Class::*)(int) const>();
    test_remove_all_extents<int (Class::*)(int) const&>();
    test_remove_all_extents<int (Class::*)(int) const&&>();
    test_remove_all_extents<int (Class::*)(int) noexcept>();
    test_remove_all_extents<int (Class::*)(int)& noexcept>();
    test_remove_all_extents<int (Class::*)(int)&& noexcept>();
    test_remove_all_extents<int (Class::*)(int) const noexcept>();
    test_remove_all_extents<int (Class::*)(int) const& noexcept>();
    test_remove_all_extents<int (Class::*)(int) const&& noexcept>();

    test_remove_all_extents<int (Class::*)(...)>();
    test_remove_all_extents<int (Class::*)(...)&>();
    test_remove_all_extents<int (Class::*)(...) &&>();
    test_remove_all_extents<int (Class::*)(...) const>();
    test_remove_all_extents<int (Class::*)(...) const&>();
    test_remove_all_extents<int (Class::*)(...) const&&>();
    test_remove_all_extents<int (Class::*)(...) noexcept>();
    test_remove_all_extents<int (Class::*)(...)& noexcept>();
    test_remove_all_extents<int (Class::*)(...)&& noexcept>();
    test_remove_all_extents<int (Class::*)(...) const noexcept>();
    test_remove_all_extents<int (Class::*)(...) const& noexcept>();
    test_remove_all_extents<int (Class::*)(...) const&& noexcept>();

    test_remove_all_extents<int (Class::*)(int, ...)>();
    test_remove_all_extents<int (Class::*)(int, ...)&>();
    test_remove_all_extents<int (Class::*)(int, ...) &&>();
    test_remove_all_extents<int (Class::*)(int, ...) const>();
    test_remove_all_extents<int (Class::*)(int, ...) const&>();
    test_remove_all_extents<int (Class::*)(int, ...) const&&>();
    test_remove_all_extents<int (Class::*)(int, ...) noexcept>();
    test_remove_all_extents<int (Class::*)(int, ...)& noexcept>();
    test_remove_all_extents<int (Class::*)(int, ...)&& noexcept>();
    test_remove_all_extents<int (Class::*)(int, ...) const noexcept>();
    test_remove_all_extents<int (Class::*)(int, ...) const& noexcept>();
    test_remove_all_extents<int (Class::*)(int, ...) const&& noexcept>();
}
