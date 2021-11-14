#include <catch2/catch.hpp>

#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/conditional.hpp>
#include <Phi/TypeTraits/make_unsigned.hpp>
#include <cstdint>
#include <vector>

enum BigEnum : unsigned long long
{
    bigzero,
    big = 0xFFFFFFFFFFFFFFFFULL
};

template <typename T, typename U = T>
void test_make_unsigned()
{
    CHECK_SAME_TYPE(typename phi::make_unsigned<T>::type, U);
    CHECK_SAME_TYPE(typename phi::make_unsigned<const T>::type, const U);
    CHECK_SAME_TYPE(typename phi::make_unsigned<volatile T>::type, volatile U);
    CHECK_SAME_TYPE(typename phi::make_unsigned<const volatile T>::type, const volatile U);

    CHECK_SAME_TYPE(phi::make_unsigned_t<T>, U);
    CHECK_SAME_TYPE(phi::make_unsigned_t<const T>, const U);
    CHECK_SAME_TYPE(phi::make_unsigned_t<volatile T>, volatile U);
    CHECK_SAME_TYPE(phi::make_unsigned_t<const volatile T>, const volatile U);
}

TEST_CASE("make_unsigned")
{
    // test_make_unsigned<
    //         Enum, phi::conditional<sizeof(Enum) == sizeof(int), unsigned int, unsigned char>>();

    test_make_unsigned<void>();
    test_make_unsigned<phi::nullptr_t>();
    test_make_unsigned<bool>();
    test_make_unsigned<char, unsigned char>();
    test_make_unsigned<signed char, unsigned char>();
    test_make_unsigned<unsigned char, unsigned char>();
    test_make_unsigned<short, unsigned short>();
    test_make_unsigned<unsigned short, unsigned short>();
    test_make_unsigned<int, unsigned int>();
    test_make_unsigned<unsigned int, unsigned int>();
    test_make_unsigned<long, unsigned long>();
    test_make_unsigned<unsigned long, unsigned long>();
    test_make_unsigned<long long, unsigned long long>();
    test_make_unsigned<unsigned long long, unsigned long long>();
    test_make_unsigned<float>();
    test_make_unsigned<double>();
    test_make_unsigned<long double>();
    //test_make_unsigned<char8_t, std::uint8_t>();
    //test_make_unsigned<char16_t, std::uint16_t>();
    //test_make_unsigned<char32_t, std::uint32_t>();
    //test_make_unsigned<wchar_t,
    //                   phi::conditional<sizeof(wchar_t) == 4, std::uint32_t, std::uint16_t>>();

    test_make_unsigned<phi::Boolean>();
    test_make_unsigned<phi::Integer<signed char>, phi::Integer<unsigned char>>();
    test_make_unsigned<phi::Integer<unsigned char>, phi::Integer<unsigned char>>();
    test_make_unsigned<phi::Integer<short>, phi::Integer<unsigned short>>();
    test_make_unsigned<phi::Integer<unsigned short>, phi::Integer<unsigned short>>();
    test_make_unsigned<phi::Integer<int>, phi::Integer<unsigned int>>();
    test_make_unsigned<phi::Integer<unsigned int>, phi::Integer<unsigned int>>();
    test_make_unsigned<phi::Integer<long>, phi::Integer<unsigned long>>();
    test_make_unsigned<phi::Integer<unsigned long>, phi::Integer<unsigned long>>();
    test_make_unsigned<phi::Integer<long long>, phi::Integer<unsigned long long>>();
    test_make_unsigned<phi::Integer<unsigned long long>, phi::Integer<unsigned long long>>();
    test_make_unsigned<phi::FloatingPoint<float>>();
    test_make_unsigned<phi::FloatingPoint<double>>();
    test_make_unsigned<phi::FloatingPoint<long double>>();

    test_make_unsigned<std::vector<int>>();
    test_make_unsigned<phi::ScopePtr<int>>();

    test_make_unsigned<int&>();
    test_make_unsigned<const int&>();
    test_make_unsigned<volatile int&>();
    test_make_unsigned<const volatile int&>();
    test_make_unsigned<int&&>();
    test_make_unsigned<const int&&>();
    test_make_unsigned<volatile int&&>();
    test_make_unsigned<const volatile int&&>();
    test_make_unsigned<int*>();
    test_make_unsigned<const int*>();
    test_make_unsigned<volatile int*>();
    test_make_unsigned<const volatile int*>();
    test_make_unsigned<int**>();
    test_make_unsigned<const int**>();
    test_make_unsigned<volatile int**>();
    test_make_unsigned<const volatile int**>();
    test_make_unsigned<int*&>();
    test_make_unsigned<const int*&>();
    test_make_unsigned<volatile int*&>();
    test_make_unsigned<const volatile int*&>();
    test_make_unsigned<int*&&>();
    test_make_unsigned<const int*&&>();
    test_make_unsigned<volatile int*&&>();
    test_make_unsigned<const volatile int*&&>();
    test_make_unsigned<void*>();
    test_make_unsigned<char[3]>();
    test_make_unsigned<char[]>();
    test_make_unsigned<char* [3]>();
    test_make_unsigned<char*[]>();
    test_make_unsigned<int(*)[3]>();
    test_make_unsigned<int(*)[]>();
    test_make_unsigned<int(&)[3]>();
    test_make_unsigned<int(&)[]>();
    test_make_unsigned<int(&&)[3]>();
    test_make_unsigned<int(&&)[]>();
    test_make_unsigned<char[3][2]>();
    test_make_unsigned<char[][2]>();
    test_make_unsigned<char* [3][2]>();
    test_make_unsigned<char*[][2]>();
    test_make_unsigned<int(*)[3][2]>();
    test_make_unsigned<int(*)[][2]>();
    test_make_unsigned<int(&)[3][2]>();
    test_make_unsigned<int(&)[][2]>();
    test_make_unsigned<int(&&)[3][2]>();
    test_make_unsigned<int(&&)[][2]>();
    test_make_unsigned<Class>();
    test_make_unsigned<Class[]>();
    test_make_unsigned<Class[2]>();
    test_make_unsigned<Template<void>>();
    test_make_unsigned<Template<int>>();
    test_make_unsigned<Template<Class>>();
    test_make_unsigned<Template<incomplete_type>>();
    test_make_unsigned<VariadicTemplate<>>();
    test_make_unsigned<VariadicTemplate<void>>();
    test_make_unsigned<VariadicTemplate<int>>();
    test_make_unsigned<VariadicTemplate<Class>>();
    test_make_unsigned<VariadicTemplate<incomplete_type>>();
    test_make_unsigned<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_make_unsigned<PublicDerviedFromTemplate<Base>>();
    test_make_unsigned<PublicDerviedFromTemplate<Derived>>();
    test_make_unsigned<PublicDerviedFromTemplate<Class>>();
    test_make_unsigned<PrivateDerviedFromTemplate<Base>>();
    test_make_unsigned<PrivateDerviedFromTemplate<Derived>>();
    test_make_unsigned<PrivateDerviedFromTemplate<Class>>();
    test_make_unsigned<ProtectedDerviedFromTemplate<Base>>();
    test_make_unsigned<ProtectedDerviedFromTemplate<Derived>>();
    test_make_unsigned<ProtectedDerviedFromTemplate<Class>>();
    test_make_unsigned<Union>();
    test_make_unsigned<NonEmptyUnion>();
    test_make_unsigned<Empty>();
    test_make_unsigned<NotEmpty>();
    test_make_unsigned<bit_zero>();
    test_make_unsigned<bit_one>();
    test_make_unsigned<Base>();
    test_make_unsigned<Derived>();
    test_make_unsigned<Abstract>();
    test_make_unsigned<AbstractTemplate<int>>();
    test_make_unsigned<AbstractTemplate<double>>();
    test_make_unsigned<AbstractTemplate<Class>>();
    test_make_unsigned<AbstractTemplate<incomplete_type>>();
    test_make_unsigned<Final>();
    //test_make_unsigned<Enum, unsigned>();
    //test_make_unsigned<EnumSigned, unsigned>();
    //test_make_unsigned<EnumUnsigned, unsigned>();
    //test_make_unsigned<EnumClass, unsigned>();
    //test_make_unsigned<EnumStruct, unsigned>();
    test_make_unsigned<Function>();
    test_make_unsigned<FunctionPtr>();
    test_make_unsigned<MemberObjectPtr>();
    test_make_unsigned<MemberFunctionPtr>();
    test_make_unsigned<incomplete_type>();
    test_make_unsigned<IncompleteTemplate<void>>();
    test_make_unsigned<IncompleteTemplate<int>>();
    test_make_unsigned<IncompleteTemplate<Class>>();
    test_make_unsigned<IncompleteTemplate<incomplete_type>>();
    test_make_unsigned<IncompleteVariadicTemplate<>>();
    test_make_unsigned<IncompleteVariadicTemplate<void>>();
    test_make_unsigned<IncompleteVariadicTemplate<int>>();
    test_make_unsigned<IncompleteVariadicTemplate<Class>>();
    test_make_unsigned<IncompleteVariadicTemplate<incomplete_type>>();
    test_make_unsigned<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_make_unsigned<int Class::*>();
    test_make_unsigned<float Class::*>();
    test_make_unsigned<void * Class::*>();
    test_make_unsigned<int * Class::*>();
    test_make_unsigned<int Class::*&>();
    test_make_unsigned<float Class::*&>();
    test_make_unsigned<void * Class::*&>();
    test_make_unsigned<int * Class::*&>();
    test_make_unsigned<int Class::*&&>();
    test_make_unsigned<float Class::*&&>();
    test_make_unsigned<void * Class::*&&>();
    test_make_unsigned<int * Class::*&&>();
    test_make_unsigned<NonCopyable>();
    test_make_unsigned<NonMoveable>();
    test_make_unsigned<NonConstructible>();
    test_make_unsigned<Tracked>();
    test_make_unsigned<TrapConstructible>();
    test_make_unsigned<TrapImplicitConversion>();
    test_make_unsigned<TrapComma>();
    test_make_unsigned<TrapCall>();
    test_make_unsigned<TrapSelfAssign>();

    test_make_unsigned<void()>();
    test_make_unsigned<void()&>();
    test_make_unsigned<void() &&>();
    test_make_unsigned<void() const>();
    test_make_unsigned<void() const&>();
    test_make_unsigned<void() const&&>();
    test_make_unsigned<void() noexcept>();
    test_make_unsigned<void()& noexcept>();
    test_make_unsigned<void()&& noexcept>();
    test_make_unsigned<void() const noexcept>();
    test_make_unsigned<void() const& noexcept>();
    test_make_unsigned<void() const&& noexcept>();

    test_make_unsigned<void(int)>();
    test_make_unsigned<void(int)&>();
    test_make_unsigned<void(int) &&>();
    test_make_unsigned<void(int) const>();
    test_make_unsigned<void(int) const&>();
    test_make_unsigned<void(int) const&&>();
    test_make_unsigned<void(int) noexcept>();
    test_make_unsigned<void(int)& noexcept>();
    test_make_unsigned<void(int)&& noexcept>();
    test_make_unsigned<void(int) const noexcept>();
    test_make_unsigned<void(int) const& noexcept>();
    test_make_unsigned<void(int) const&& noexcept>();

    test_make_unsigned<void(...)>();
    test_make_unsigned<void(...)&>();
    test_make_unsigned<void(...) &&>();
    test_make_unsigned<void(...) const>();
    test_make_unsigned<void(...) const&>();
    test_make_unsigned<void(...) const&&>();
    test_make_unsigned<void(...) noexcept>();
    test_make_unsigned<void(...)& noexcept>();
    test_make_unsigned<void(...)&& noexcept>();
    test_make_unsigned<void(...) const noexcept>();
    test_make_unsigned<void(...) const& noexcept>();
    test_make_unsigned<void(...) const&& noexcept>();

    test_make_unsigned<void(int, ...)>();
    test_make_unsigned<void(int, ...)&>();
    test_make_unsigned<void(int, ...) &&>();
    test_make_unsigned<void(int, ...) const>();
    test_make_unsigned<void(int, ...) const&>();
    test_make_unsigned<void(int, ...) const&&>();
    test_make_unsigned<void(int, ...) noexcept>();
    test_make_unsigned<void(int, ...)& noexcept>();
    test_make_unsigned<void(int, ...)&& noexcept>();
    test_make_unsigned<void(int, ...) const noexcept>();
    test_make_unsigned<void(int, ...) const& noexcept>();
    test_make_unsigned<void(int, ...) const&& noexcept>();

    test_make_unsigned<int()>();
    test_make_unsigned<int()&>();
    test_make_unsigned<int() &&>();
    test_make_unsigned<int() const>();
    test_make_unsigned<int() const&>();
    test_make_unsigned<int() const&&>();
    test_make_unsigned<int() noexcept>();
    test_make_unsigned<int()& noexcept>();
    test_make_unsigned<int()&& noexcept>();
    test_make_unsigned<int() const noexcept>();
    test_make_unsigned<int() const& noexcept>();
    test_make_unsigned<int() const&& noexcept>();

    test_make_unsigned<int(int)>();
    test_make_unsigned<int(int)&>();
    test_make_unsigned<int(int) &&>();
    test_make_unsigned<int(int) const>();
    test_make_unsigned<int(int) const&>();
    test_make_unsigned<int(int) const&&>();
    test_make_unsigned<int(int) noexcept>();
    test_make_unsigned<int(int)& noexcept>();
    test_make_unsigned<int(int)&& noexcept>();
    test_make_unsigned<int(int) const noexcept>();
    test_make_unsigned<int(int) const& noexcept>();
    test_make_unsigned<int(int) const&& noexcept>();

    test_make_unsigned<int(...)>();
    test_make_unsigned<int(...)&>();
    test_make_unsigned<int(...) &&>();
    test_make_unsigned<int(...) const>();
    test_make_unsigned<int(...) const&>();
    test_make_unsigned<int(...) const&&>();
    test_make_unsigned<int(...) noexcept>();
    test_make_unsigned<int(...)& noexcept>();
    test_make_unsigned<int(...)&& noexcept>();
    test_make_unsigned<int(...) const noexcept>();
    test_make_unsigned<int(...) const& noexcept>();
    test_make_unsigned<int(...) const&& noexcept>();

    test_make_unsigned<int(int, ...)>();
    test_make_unsigned<int(int, ...)&>();
    test_make_unsigned<int(int, ...) &&>();
    test_make_unsigned<int(int, ...) const>();
    test_make_unsigned<int(int, ...) const&>();
    test_make_unsigned<int(int, ...) const&&>();
    test_make_unsigned<int(int, ...) noexcept>();
    test_make_unsigned<int(int, ...)& noexcept>();
    test_make_unsigned<int(int, ...)&& noexcept>();
    test_make_unsigned<int(int, ...) const noexcept>();
    test_make_unsigned<int(int, ...) const& noexcept>();
    test_make_unsigned<int(int, ...) const&& noexcept>();

    test_make_unsigned<void (*)()>();
    test_make_unsigned<void (*)() noexcept>();

    test_make_unsigned<void (*)(int)>();
    test_make_unsigned<void (*)(int) noexcept>();

    test_make_unsigned<void (*)(...)>();
    test_make_unsigned<void (*)(...) noexcept>();

    test_make_unsigned<void (*)(int, ...)>();
    test_make_unsigned<void (*)(int, ...) noexcept>();

    test_make_unsigned<int (*)()>();
    test_make_unsigned<int (*)() noexcept>();

    test_make_unsigned<int (*)(int)>();
    test_make_unsigned<int (*)(int) noexcept>();

    test_make_unsigned<int (*)(...)>();
    test_make_unsigned<int (*)(...) noexcept>();

    test_make_unsigned<int (*)(int, ...)>();
    test_make_unsigned<int (*)(int, ...) noexcept>();

    test_make_unsigned<void (&)()>();
    test_make_unsigned<void (&)() noexcept>();

    test_make_unsigned<void (&)(int)>();
    test_make_unsigned<void (&)(int) noexcept>();

    test_make_unsigned<void (&)(...)>();
    test_make_unsigned<void (&)(...) noexcept>();

    test_make_unsigned<void (&)(int, ...)>();
    test_make_unsigned<void (&)(int, ...) noexcept>();

    test_make_unsigned<int (&)()>();
    test_make_unsigned<int (&)() noexcept>();

    test_make_unsigned<int (&)(int)>();
    test_make_unsigned<int (&)(int) noexcept>();

    test_make_unsigned<int (&)(...)>();
    test_make_unsigned<int (&)(...) noexcept>();

    test_make_unsigned<int (&)(int, ...)>();
    test_make_unsigned<int (&)(int, ...) noexcept>();

    test_make_unsigned<void(&&)()>();
    test_make_unsigned<void(&&)() noexcept>();

    test_make_unsigned<void(&&)(int)>();
    test_make_unsigned<void(&&)(int) noexcept>();

    test_make_unsigned<void(&&)(...)>();
    test_make_unsigned<void(&&)(...) noexcept>();

    test_make_unsigned<void(&&)(int, ...)>();
    test_make_unsigned<void(&&)(int, ...) noexcept>();

    test_make_unsigned<int(&&)()>();
    test_make_unsigned<int(&&)() noexcept>();

    test_make_unsigned<int(&&)(int)>();
    test_make_unsigned<int(&&)(int) noexcept>();

    test_make_unsigned<int(&&)(...)>();
    test_make_unsigned<int(&&)(...) noexcept>();

    test_make_unsigned<int(&&)(int, ...)>();
    test_make_unsigned<int(&&)(int, ...) noexcept>();

    test_make_unsigned<void (Class::*)()>();
    test_make_unsigned<void (Class::*)()&>();
    test_make_unsigned<void (Class::*)() &&>();
    test_make_unsigned<void (Class::*)() const>();
    test_make_unsigned<void (Class::*)() const&>();
    test_make_unsigned<void (Class::*)() const&&>();
    test_make_unsigned<void (Class::*)() noexcept>();
    test_make_unsigned<void (Class::*)()& noexcept>();
    test_make_unsigned<void (Class::*)()&& noexcept>();
    test_make_unsigned<void (Class::*)() const noexcept>();
    test_make_unsigned<void (Class::*)() const& noexcept>();
    test_make_unsigned<void (Class::*)() const&& noexcept>();

    test_make_unsigned<void (Class::*)(int)>();
    test_make_unsigned<void (Class::*)(int)&>();
    test_make_unsigned<void (Class::*)(int) &&>();
    test_make_unsigned<void (Class::*)(int) const>();
    test_make_unsigned<void (Class::*)(int) const&>();
    test_make_unsigned<void (Class::*)(int) const&&>();
    test_make_unsigned<void (Class::*)(int) noexcept>();
    test_make_unsigned<void (Class::*)(int)& noexcept>();
    test_make_unsigned<void (Class::*)(int)&& noexcept>();
    test_make_unsigned<void (Class::*)(int) const noexcept>();
    test_make_unsigned<void (Class::*)(int) const& noexcept>();
    test_make_unsigned<void (Class::*)(int) const&& noexcept>();

    test_make_unsigned<void (Class::*)(...)>();
    test_make_unsigned<void (Class::*)(...)&>();
    test_make_unsigned<void (Class::*)(...) &&>();
    test_make_unsigned<void (Class::*)(...) const>();
    test_make_unsigned<void (Class::*)(...) const&>();
    test_make_unsigned<void (Class::*)(...) const&&>();
    test_make_unsigned<void (Class::*)(...) noexcept>();
    test_make_unsigned<void (Class::*)(...)& noexcept>();
    test_make_unsigned<void (Class::*)(...)&& noexcept>();
    test_make_unsigned<void (Class::*)(...) const noexcept>();
    test_make_unsigned<void (Class::*)(...) const& noexcept>();
    test_make_unsigned<void (Class::*)(...) const&& noexcept>();

    test_make_unsigned<void (Class::*)(int, ...)>();
    test_make_unsigned<void (Class::*)(int, ...)&>();
    test_make_unsigned<void (Class::*)(int, ...) &&>();
    test_make_unsigned<void (Class::*)(int, ...) const>();
    test_make_unsigned<void (Class::*)(int, ...) const&>();
    test_make_unsigned<void (Class::*)(int, ...) const&&>();
    test_make_unsigned<void (Class::*)(int, ...) noexcept>();
    test_make_unsigned<void (Class::*)(int, ...)& noexcept>();
    test_make_unsigned<void (Class::*)(int, ...)&& noexcept>();
    test_make_unsigned<void (Class::*)(int, ...) const noexcept>();
    test_make_unsigned<void (Class::*)(int, ...) const& noexcept>();
    test_make_unsigned<void (Class::*)(int, ...) const&& noexcept>();

    test_make_unsigned<int (Class::*)()>();
    test_make_unsigned<int (Class::*)()&>();
    test_make_unsigned<int (Class::*)() &&>();
    test_make_unsigned<int (Class::*)() const>();
    test_make_unsigned<int (Class::*)() const&>();
    test_make_unsigned<int (Class::*)() const&&>();
    test_make_unsigned<int (Class::*)() noexcept>();
    test_make_unsigned<int (Class::*)()& noexcept>();
    test_make_unsigned<int (Class::*)()&& noexcept>();
    test_make_unsigned<int (Class::*)() const noexcept>();
    test_make_unsigned<int (Class::*)() const& noexcept>();
    test_make_unsigned<int (Class::*)() const&& noexcept>();

    test_make_unsigned<int (Class::*)(int)>();
    test_make_unsigned<int (Class::*)(int)&>();
    test_make_unsigned<int (Class::*)(int) &&>();
    test_make_unsigned<int (Class::*)(int) const>();
    test_make_unsigned<int (Class::*)(int) const&>();
    test_make_unsigned<int (Class::*)(int) const&&>();
    test_make_unsigned<int (Class::*)(int) noexcept>();
    test_make_unsigned<int (Class::*)(int)& noexcept>();
    test_make_unsigned<int (Class::*)(int)&& noexcept>();
    test_make_unsigned<int (Class::*)(int) const noexcept>();
    test_make_unsigned<int (Class::*)(int) const& noexcept>();
    test_make_unsigned<int (Class::*)(int) const&& noexcept>();

    test_make_unsigned<int (Class::*)(...)>();
    test_make_unsigned<int (Class::*)(...)&>();
    test_make_unsigned<int (Class::*)(...) &&>();
    test_make_unsigned<int (Class::*)(...) const>();
    test_make_unsigned<int (Class::*)(...) const&>();
    test_make_unsigned<int (Class::*)(...) const&&>();
    test_make_unsigned<int (Class::*)(...) noexcept>();
    test_make_unsigned<int (Class::*)(...)& noexcept>();
    test_make_unsigned<int (Class::*)(...)&& noexcept>();
    test_make_unsigned<int (Class::*)(...) const noexcept>();
    test_make_unsigned<int (Class::*)(...) const& noexcept>();
    test_make_unsigned<int (Class::*)(...) const&& noexcept>();

    test_make_unsigned<int (Class::*)(int, ...)>();
    test_make_unsigned<int (Class::*)(int, ...)&>();
    test_make_unsigned<int (Class::*)(int, ...) &&>();
    test_make_unsigned<int (Class::*)(int, ...) const>();
    test_make_unsigned<int (Class::*)(int, ...) const&>();
    test_make_unsigned<int (Class::*)(int, ...) const&&>();
    test_make_unsigned<int (Class::*)(int, ...) noexcept>();
    test_make_unsigned<int (Class::*)(int, ...)& noexcept>();
    test_make_unsigned<int (Class::*)(int, ...)&& noexcept>();
    test_make_unsigned<int (Class::*)(int, ...) const noexcept>();
    test_make_unsigned<int (Class::*)(int, ...) const& noexcept>();
    test_make_unsigned<int (Class::*)(int, ...) const&& noexcept>();
}
