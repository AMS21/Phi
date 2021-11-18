#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_trivially_move_assignable.hpp>
#include <vector>

template <typename T>
void test_is_trivially_move_assignable()
{
#if PHI_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE()
    STATIC_REQUIRE(phi::is_trivially_move_assignable<T>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_move_assignable_v<T>);
#    endif
#endif
}

template <typename T>
void test_is_not_trivially_move_assignable()
{
#if PHI_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_move_assignable<T>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_move_assignable_v<T>);
#    endif
#endif
}

struct A
{
    A& operator=(const A&);
};

struct B
{
    B& operator=(const B&) = default;
};

TEST_CASE("is_trivially_move_assignable")
{
    test_is_not_trivially_move_assignable<A>();
    test_is_trivially_move_assignable<B>();

    test_is_not_trivially_move_assignable<void>();
    test_is_trivially_move_assignable<phi::nullptr_t>();
    test_is_trivially_move_assignable<bool>();
    test_is_trivially_move_assignable<char>();
    test_is_trivially_move_assignable<signed char>();
    test_is_trivially_move_assignable<unsigned char>();
    test_is_trivially_move_assignable<short>();
    test_is_trivially_move_assignable<unsigned short>();
    test_is_trivially_move_assignable<int>();
    test_is_trivially_move_assignable<unsigned int>();
    test_is_trivially_move_assignable<long>();
    test_is_trivially_move_assignable<unsigned long>();
    test_is_trivially_move_assignable<long long>();
    test_is_trivially_move_assignable<unsigned long long>();
    test_is_trivially_move_assignable<float>();
    test_is_trivially_move_assignable<double>();
    test_is_trivially_move_assignable<long double>();
    test_is_trivially_move_assignable<char8_t>();
    test_is_trivially_move_assignable<char16_t>();
    test_is_trivially_move_assignable<char32_t>();
    test_is_trivially_move_assignable<wchar_t>();

    test_is_trivially_move_assignable<phi::Boolean>();
    test_is_trivially_move_assignable<phi::Integer<signed char>>();
    test_is_trivially_move_assignable<phi::Integer<unsigned char>>();
    test_is_trivially_move_assignable<phi::Integer<short>>();
    test_is_trivially_move_assignable<phi::Integer<unsigned short>>();
    test_is_trivially_move_assignable<phi::Integer<int>>();
    test_is_trivially_move_assignable<phi::Integer<unsigned int>>();
    test_is_trivially_move_assignable<phi::Integer<long>>();
    test_is_trivially_move_assignable<phi::Integer<unsigned long>>();
    test_is_trivially_move_assignable<phi::Integer<long long>>();
    test_is_trivially_move_assignable<phi::Integer<unsigned long long>>();
    test_is_trivially_move_assignable<phi::FloatingPoint<float>>();
    test_is_trivially_move_assignable<phi::FloatingPoint<double>>();
    test_is_trivially_move_assignable<phi::FloatingPoint<long double>>();

    test_is_not_trivially_move_assignable<std::vector<int>>();
    test_is_not_trivially_move_assignable<phi::ScopePtr<int>>();

    test_is_trivially_move_assignable<int&>();
    test_is_not_trivially_move_assignable<const int&>();
    test_is_trivially_move_assignable<volatile int&>();
    test_is_not_trivially_move_assignable<const volatile int&>();
    test_is_trivially_move_assignable<int&&>();
    test_is_not_trivially_move_assignable<const int&&>();
    test_is_trivially_move_assignable<volatile int&&>();
    test_is_not_trivially_move_assignable<const volatile int&&>();
    test_is_trivially_move_assignable<int*>();
    test_is_trivially_move_assignable<const int*>();
    test_is_trivially_move_assignable<volatile int*>();
    test_is_trivially_move_assignable<const volatile int*>();
    test_is_trivially_move_assignable<int**>();
    test_is_trivially_move_assignable<const int**>();
    test_is_trivially_move_assignable<volatile int**>();
    test_is_trivially_move_assignable<const volatile int**>();
    test_is_trivially_move_assignable<void*>();
    test_is_not_trivially_move_assignable<char[3]>();
    test_is_not_trivially_move_assignable<char[]>();
    test_is_not_trivially_move_assignable<char* [3]>();
    test_is_not_trivially_move_assignable<char*[]>();
    test_is_trivially_move_assignable<Class>();
    test_is_trivially_move_assignable<Union>();
    test_is_trivially_move_assignable<NonEmptyUnion>();
    test_is_trivially_move_assignable<Empty>();
    test_is_not_trivially_move_assignable<NotEmpty>();
    test_is_trivially_move_assignable<bit_zero>();
    test_is_trivially_move_assignable<bit_one>();
    test_is_not_trivially_move_assignable<Abstract>();
    test_is_not_trivially_move_assignable<AbstractTemplate<int>>();
    test_is_trivially_move_assignable<AbstractTemplate<double>>();
    test_is_not_trivially_move_assignable<AbstractTemplate<Class>>();
    test_is_trivially_move_assignable<Final>();
    test_is_trivially_move_assignable<Enum>();
    test_is_trivially_move_assignable<EnumSigned>();
    test_is_trivially_move_assignable<EnumUnsigned>();
    test_is_trivially_move_assignable<EnumClass>();
    test_is_not_trivially_move_assignable<Function>();
    test_is_trivially_move_assignable<FunctionPtr>();
    test_is_trivially_move_assignable<MemberObjectPtr>();
    test_is_trivially_move_assignable<MemberFunctionPtr>();
    test_is_trivially_move_assignable<int Class::*>();
    test_is_trivially_move_assignable<float Class::*>();

    test_is_not_trivially_move_assignable<void()>();
    test_is_not_trivially_move_assignable<void() noexcept>();
    test_is_not_trivially_move_assignable<void(int)>();
    test_is_not_trivially_move_assignable<void(int) noexcept>();

    test_is_not_trivially_move_assignable<void(...)>();
    test_is_not_trivially_move_assignable<void(...) noexcept>();
    test_is_not_trivially_move_assignable<void(int, ...)>();
    test_is_not_trivially_move_assignable<void(int, ...) noexcept>();

    test_is_trivially_move_assignable<void (*)()>();
    test_is_trivially_move_assignable<void (*)() noexcept>();
    test_is_trivially_move_assignable<void (*)(int)>();
    test_is_trivially_move_assignable<void (*)(int) noexcept>();

    test_is_trivially_move_assignable<void (*)(...)>();
    test_is_trivially_move_assignable<void (*)(...) noexcept>();
    test_is_trivially_move_assignable<void (*)(int, ...)>();
    test_is_trivially_move_assignable<void (*)(int, ...) noexcept>();

    test_is_trivially_move_assignable<void (Class::*)()>();
    test_is_trivially_move_assignable<void (Class::*)()&>();
    test_is_trivially_move_assignable<void (Class::*)() &&>();
    test_is_trivially_move_assignable<void (Class::*)() const>();
    test_is_trivially_move_assignable<void (Class::*)() const&>();
    test_is_trivially_move_assignable<void (Class::*)() const&&>();

    test_is_trivially_move_assignable<void (Class::*)() noexcept>();
    test_is_trivially_move_assignable<void (Class::*)()& noexcept>();
    test_is_trivially_move_assignable<void (Class::*)()&& noexcept>();
    test_is_trivially_move_assignable<void (Class::*)() const noexcept>();
    test_is_trivially_move_assignable<void (Class::*)() const& noexcept>();
    test_is_trivially_move_assignable<void (Class::*)() const&& noexcept>();

    test_is_trivially_move_assignable<void (Class::*)(int)>();
    test_is_trivially_move_assignable<void (Class::*)(int)&>();
    test_is_trivially_move_assignable<void (Class::*)(int) &&>();
    test_is_trivially_move_assignable<void (Class::*)(int) const>();
    test_is_trivially_move_assignable<void (Class::*)(int) const&>();
    test_is_trivially_move_assignable<void (Class::*)(int) const&&>();

    test_is_trivially_move_assignable<void (Class::*)(int) noexcept>();
    test_is_trivially_move_assignable<void (Class::*)(int)& noexcept>();
    test_is_trivially_move_assignable<void (Class::*)(int)&& noexcept>();
    test_is_trivially_move_assignable<void (Class::*)(int) const noexcept>();
    test_is_trivially_move_assignable<void (Class::*)(int) const& noexcept>();
    test_is_trivially_move_assignable<void (Class::*)(int) const&& noexcept>();

    test_is_trivially_move_assignable<void (Class::*)(...)>();
    test_is_trivially_move_assignable<void (Class::*)(...)&>();
    test_is_trivially_move_assignable<void (Class::*)(...) &&>();
    test_is_trivially_move_assignable<void (Class::*)(...) const>();
    test_is_trivially_move_assignable<void (Class::*)(...) const&>();
    test_is_trivially_move_assignable<void (Class::*)(...) const&&>();

    test_is_trivially_move_assignable<void (Class::*)(...) noexcept>();
    test_is_trivially_move_assignable<void (Class::*)(...)& noexcept>();
    test_is_trivially_move_assignable<void (Class::*)(...)&& noexcept>();
    test_is_trivially_move_assignable<void (Class::*)(...) const noexcept>();
    test_is_trivially_move_assignable<void (Class::*)(...) const& noexcept>();
    test_is_trivially_move_assignable<void (Class::*)(...) const&& noexcept>();
}
