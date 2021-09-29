#include <catch2/catch.hpp>

#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/add_const.hpp>
#include <vector>

template <typename T, typename U>
void test_add_const_imp()
{
    CHECK_SAME_TYPE(const U, typename phi::add_const<T>::type);
    CHECK_SAME_TYPE(const U, phi::add_const_t<T>);
}

template <typename T>
void test_add_const()
{
    test_add_const_imp<T, const T>();
    test_add_const_imp<const T, const T>();
    test_add_const_imp<volatile T, volatile const T>();
    test_add_const_imp<const volatile T, const volatile T>();
}

TEST_CASE("add_const")
{
    test_add_const<void>();
    test_add_const<phi::nullptr_t>();
    test_add_const<bool>();
    test_add_const<char>();
    test_add_const<signed char>();
    test_add_const<unsigned char>();
    test_add_const<short>();
    test_add_const<unsigned short>();
    test_add_const<int>();
    test_add_const<unsigned int>();
    test_add_const<long>();
    test_add_const<unsigned long>();
    test_add_const<long long>();
    test_add_const<unsigned long long>();
    test_add_const<float>();
    test_add_const<double>();
    test_add_const<long double>();
    test_add_const<char8_t>();
    test_add_const<char16_t>();
    test_add_const<char32_t>();
    test_add_const<wchar_t>();

    test_add_const<phi::Boolean>();
    test_add_const<phi::Integer<signed char>>();
    test_add_const<phi::Integer<unsigned char>>();
    test_add_const<phi::Integer<short>>();
    test_add_const<phi::Integer<unsigned short>>();
    test_add_const<phi::Integer<int>>();
    test_add_const<phi::Integer<unsigned int>>();
    test_add_const<phi::Integer<long>>();
    test_add_const<phi::Integer<unsigned long>>();
    test_add_const<phi::Integer<long long>>();
    test_add_const<phi::Integer<unsigned long long>>();
    test_add_const<phi::FloatingPoint<float>>();
    test_add_const<phi::FloatingPoint<double>>();
    test_add_const<phi::FloatingPoint<long double>>();

    test_add_const<std::vector<int>>();
    test_add_const<phi::ScopePtr<int>>();

    test_add_const<int&>();
    test_add_const<const int&>();
    test_add_const<volatile int&>();
    test_add_const<const volatile int&>();
    test_add_const<int&&>();
    test_add_const<const int&&>();
    test_add_const<volatile int&&>();
    test_add_const<const volatile int&&>();
    test_add_const<int*>();
    test_add_const<const int*>();
    test_add_const<volatile int*>();
    test_add_const<const volatile int*>();
    test_add_const<int**>();
    test_add_const<const int**>();
    test_add_const<volatile int**>();
    test_add_const<const volatile int**>();
    test_add_const<int*&>();
    test_add_const<const int*&>();
    test_add_const<volatile int*&>();
    test_add_const<const volatile int*&>();
    test_add_const<void*>();
    test_add_const<char[3]>();
    test_add_const<char[]>();
    test_add_const<char* [3]>();
    test_add_const<char*[]>();
    test_add_const<int(*)[3]>();
    test_add_const<int(*)[]>();
    test_add_const<int(&)[3]>();
    test_add_const<int(&)[]>();
    test_add_const<char[3][2]>();
    test_add_const<char[][2]>();
    test_add_const<char* [3][2]>();
    test_add_const<char*[][2]>();
    test_add_const<int(*)[3][2]>();
    test_add_const<int(*)[][2]>();
    test_add_const<int(&)[3][2]>();
    test_add_const<int(&)[][2]>();
    test_add_const<Class>();
    test_add_const<Class[]>();
    test_add_const<Class[2]>();
    test_add_const<Struct>();
    test_add_const<TemplateClass<void>>();
    test_add_const<TemplateClass<int>>();
    test_add_const<TemplateClass<Class>>();
    test_add_const<TemplateClass<incomplete_type>>();
    test_add_const<TemplateStruct<void>>();
    test_add_const<TemplateStruct<int>>();
    test_add_const<TemplateStruct<Class>>();
    test_add_const<TemplateStruct<incomplete_type>>();
    test_add_const<VariadicTemplateClass<>>();
    test_add_const<VariadicTemplateClass<void>>();
    test_add_const<VariadicTemplateClass<int>>();
    test_add_const<VariadicTemplateClass<Class>>();
    test_add_const<VariadicTemplateClass<incomplete_type>>();
    test_add_const<VariadicTemplateClass<int, void, Class, volatile char[]>>();
    test_add_const<VariadicTemplateStruct<>>();
    test_add_const<VariadicTemplateStruct<void>>();
    test_add_const<VariadicTemplateStruct<int>>();
    test_add_const<VariadicTemplateStruct<Class>>();
    test_add_const<VariadicTemplateStruct<incomplete_type>>();
    test_add_const<VariadicTemplateStruct<int, void, Class, volatile char[]>>();
    test_add_const<PublicDerviedFromTemplate<Base>>();
    test_add_const<PublicDerviedFromTemplate<Derived>>();
    test_add_const<PublicDerviedFromTemplate<Class>>();
    test_add_const<PrivateDerviedFromTemplate<Base>>();
    test_add_const<PrivateDerviedFromTemplate<Derived>>();
    test_add_const<PrivateDerviedFromTemplate<Class>>();
    test_add_const<ProtectedDerviedFromTemplate<Base>>();
    test_add_const<ProtectedDerviedFromTemplate<Derived>>();
    test_add_const<ProtectedDerviedFromTemplate<Class>>();
    test_add_const<Union>();
    test_add_const<NonEmptyUnion>();
    test_add_const<Empty>();
    test_add_const<NotEmpty>();
    test_add_const<bit_zero>();
    test_add_const<bit_one>();
    test_add_const<Base>();
    test_add_const<Derived>();
    test_add_const<Abstract>();
    test_add_const<AbstractTemplate<int>>();
    test_add_const<AbstractTemplate<double>>();
    test_add_const<AbstractTemplate<Class>>();
    test_add_const<AbstractTemplate<incomplete_type>>();
    test_add_const<Final>();
    test_add_const<Enum>();
    test_add_const<EnumSigned>();
    test_add_const<EnumUnsigned>();
    test_add_const<EnumClass>();
    test_add_const<EnumStruct>();
    test_add_const<Function>();
    test_add_const<FunctionPtr>();
    test_add_const<MemberObjectPtr>();
    test_add_const<MemberFunctionPtr>();
    test_add_const<incomplete_type>();
    test_add_const<IncompleteTemplate<void>>();
    test_add_const<IncompleteTemplate<int>>();
    test_add_const<IncompleteTemplate<Class>>();
    test_add_const<IncompleteTemplate<incomplete_type>>();
    test_add_const<int Class::*>();
    test_add_const<float Class::*>();
    test_add_const<void * Class::*>();
    test_add_const<int * Class::*>();
    test_add_const<NonCopyable>();
    test_add_const<NonMoveable>();
    test_add_const<NonConstructible>();
    test_add_const<Tracked>();
    test_add_const<TrapConstructible>();
    test_add_const<TrapImplicitConversion>();
    test_add_const<TrapComma>();
    test_add_const<TrapCall>();
    test_add_const<TrapSelfAssign>();

    test_add_const<void()>();
    test_add_const<void()&>();
    test_add_const<void() &&>();
    test_add_const<void() const>();
    test_add_const<void() const&>();
    test_add_const<void() const&&>();
    test_add_const<void() noexcept>();
    test_add_const<void()& noexcept>();
    test_add_const<void()&& noexcept>();
    test_add_const<void() const noexcept>();
    test_add_const<void() const& noexcept>();
    test_add_const<void() const&& noexcept>();

    test_add_const<void(int)>();
    test_add_const<void(int)&>();
    test_add_const<void(int) &&>();
    test_add_const<void(int) const>();
    test_add_const<void(int) const&>();
    test_add_const<void(int) const&&>();
    test_add_const<void(int) noexcept>();
    test_add_const<void(int)& noexcept>();
    test_add_const<void(int)&& noexcept>();
    test_add_const<void(int) const noexcept>();
    test_add_const<void(int) const& noexcept>();
    test_add_const<void(int) const&& noexcept>();

    test_add_const<void(...)>();
    test_add_const<void(...)&>();
    test_add_const<void(...) &&>();
    test_add_const<void(...) const>();
    test_add_const<void(...) const&>();
    test_add_const<void(...) const&&>();
    test_add_const<void(...) noexcept>();
    test_add_const<void(...)& noexcept>();
    test_add_const<void(...)&& noexcept>();
    test_add_const<void(...) const noexcept>();
    test_add_const<void(...) const& noexcept>();
    test_add_const<void(...) const&& noexcept>();

    test_add_const<void(int, ...)>();
    test_add_const<void(int, ...)&>();
    test_add_const<void(int, ...) &&>();
    test_add_const<void(int, ...) const>();
    test_add_const<void(int, ...) const&>();
    test_add_const<void(int, ...) const&&>();
    test_add_const<void(int, ...) noexcept>();
    test_add_const<void(int, ...)& noexcept>();
    test_add_const<void(int, ...)&& noexcept>();
    test_add_const<void(int, ...) const noexcept>();
    test_add_const<void(int, ...) const& noexcept>();
    test_add_const<void(int, ...) const&& noexcept>();

    test_add_const<int()>();
    test_add_const<int()&>();
    test_add_const<int() &&>();
    test_add_const<int() const>();
    test_add_const<int() const&>();
    test_add_const<int() const&&>();
    test_add_const<int() noexcept>();
    test_add_const<int()& noexcept>();
    test_add_const<int()&& noexcept>();
    test_add_const<int() const noexcept>();
    test_add_const<int() const& noexcept>();
    test_add_const<int() const&& noexcept>();

    test_add_const<int(int)>();
    test_add_const<int(int)&>();
    test_add_const<int(int) &&>();
    test_add_const<int(int) const>();
    test_add_const<int(int) const&>();
    test_add_const<int(int) const&&>();
    test_add_const<int(int) noexcept>();
    test_add_const<int(int)& noexcept>();
    test_add_const<int(int)&& noexcept>();
    test_add_const<int(int) const noexcept>();
    test_add_const<int(int) const& noexcept>();
    test_add_const<int(int) const&& noexcept>();

    test_add_const<int(...)>();
    test_add_const<int(...)&>();
    test_add_const<int(...) &&>();
    test_add_const<int(...) const>();
    test_add_const<int(...) const&>();
    test_add_const<int(...) const&&>();
    test_add_const<int(...) noexcept>();
    test_add_const<int(...)& noexcept>();
    test_add_const<int(...)&& noexcept>();
    test_add_const<int(...) const noexcept>();
    test_add_const<int(...) const& noexcept>();
    test_add_const<int(...) const&& noexcept>();

    test_add_const<int(int, ...)>();
    test_add_const<int(int, ...)&>();
    test_add_const<int(int, ...) &&>();
    test_add_const<int(int, ...) const>();
    test_add_const<int(int, ...) const&>();
    test_add_const<int(int, ...) const&&>();
    test_add_const<int(int, ...) noexcept>();
    test_add_const<int(int, ...)& noexcept>();
    test_add_const<int(int, ...)&& noexcept>();
    test_add_const<int(int, ...) const noexcept>();
    test_add_const<int(int, ...) const& noexcept>();
    test_add_const<int(int, ...) const&& noexcept>();

    test_add_const<void (*)()>();
    test_add_const<void (*)() noexcept>();

    test_add_const<void (*)(int)>();
    test_add_const<void (*)(int) noexcept>();

    test_add_const<void (*)(...)>();
    test_add_const<void (*)(...) noexcept>();

    test_add_const<void (*)(int, ...)>();
    test_add_const<void (*)(int, ...) noexcept>();

    test_add_const<int (*)()>();
    test_add_const<int (*)() noexcept>();

    test_add_const<int (*)(int)>();
    test_add_const<int (*)(int) noexcept>();

    test_add_const<int (*)(...)>();
    test_add_const<int (*)(...) noexcept>();

    test_add_const<int (*)(int, ...)>();
    test_add_const<int (*)(int, ...) noexcept>();

    test_add_const<void (&)()>();
    test_add_const<void (&)() noexcept>();

    test_add_const<void (&)(int)>();
    test_add_const<void (&)(int) noexcept>();

    test_add_const<void (&)(...)>();
    test_add_const<void (&)(...) noexcept>();

    test_add_const<void (&)(int, ...)>();
    test_add_const<void (&)(int, ...) noexcept>();

    test_add_const<int (&)()>();
    test_add_const<int (&)() noexcept>();

    test_add_const<int (&)(int)>();
    test_add_const<int (&)(int) noexcept>();

    test_add_const<int (&)(...)>();
    test_add_const<int (&)(...) noexcept>();

    test_add_const<int (&)(int, ...)>();
    test_add_const<int (&)(int, ...) noexcept>();

    test_add_const<void (Class::*)()>();
    test_add_const<void (Class::*)()&>();
    test_add_const<void (Class::*)() &&>();
    test_add_const<void (Class::*)() const>();
    test_add_const<void (Class::*)() const&>();
    test_add_const<void (Class::*)() const&&>();
    test_add_const<void (Class::*)() noexcept>();
    test_add_const<void (Class::*)()& noexcept>();
    test_add_const<void (Class::*)()&& noexcept>();
    test_add_const<void (Class::*)() const noexcept>();
    test_add_const<void (Class::*)() const& noexcept>();
    test_add_const<void (Class::*)() const&& noexcept>();

    test_add_const<void (Class::*)(int)>();
    test_add_const<void (Class::*)(int)&>();
    test_add_const<void (Class::*)(int) &&>();
    test_add_const<void (Class::*)(int) const>();
    test_add_const<void (Class::*)(int) const&>();
    test_add_const<void (Class::*)(int) const&&>();
    test_add_const<void (Class::*)(int) noexcept>();
    test_add_const<void (Class::*)(int)& noexcept>();
    test_add_const<void (Class::*)(int)&& noexcept>();
    test_add_const<void (Class::*)(int) const noexcept>();
    test_add_const<void (Class::*)(int) const& noexcept>();
    test_add_const<void (Class::*)(int) const&& noexcept>();

    test_add_const<void (Class::*)(...)>();
    test_add_const<void (Class::*)(...)&>();
    test_add_const<void (Class::*)(...) &&>();
    test_add_const<void (Class::*)(...) const>();
    test_add_const<void (Class::*)(...) const&>();
    test_add_const<void (Class::*)(...) const&&>();
    test_add_const<void (Class::*)(...) noexcept>();
    test_add_const<void (Class::*)(...)& noexcept>();
    test_add_const<void (Class::*)(...)&& noexcept>();
    test_add_const<void (Class::*)(...) const noexcept>();
    test_add_const<void (Class::*)(...) const& noexcept>();
    test_add_const<void (Class::*)(...) const&& noexcept>();

    test_add_const<void (Class::*)(int, ...)>();
    test_add_const<void (Class::*)(int, ...)&>();
    test_add_const<void (Class::*)(int, ...) &&>();
    test_add_const<void (Class::*)(int, ...) const>();
    test_add_const<void (Class::*)(int, ...) const&>();
    test_add_const<void (Class::*)(int, ...) const&&>();
    test_add_const<void (Class::*)(int, ...) noexcept>();
    test_add_const<void (Class::*)(int, ...)& noexcept>();
    test_add_const<void (Class::*)(int, ...)&& noexcept>();
    test_add_const<void (Class::*)(int, ...) const noexcept>();
    test_add_const<void (Class::*)(int, ...) const& noexcept>();
    test_add_const<void (Class::*)(int, ...) const&& noexcept>();

    test_add_const<int (Class::*)()>();
    test_add_const<int (Class::*)()&>();
    test_add_const<int (Class::*)() &&>();
    test_add_const<int (Class::*)() const>();
    test_add_const<int (Class::*)() const&>();
    test_add_const<int (Class::*)() const&&>();
    test_add_const<int (Class::*)() noexcept>();
    test_add_const<int (Class::*)()& noexcept>();
    test_add_const<int (Class::*)()&& noexcept>();
    test_add_const<int (Class::*)() const noexcept>();
    test_add_const<int (Class::*)() const& noexcept>();
    test_add_const<int (Class::*)() const&& noexcept>();

    test_add_const<int (Class::*)(int)>();
    test_add_const<int (Class::*)(int)&>();
    test_add_const<int (Class::*)(int) &&>();
    test_add_const<int (Class::*)(int) const>();
    test_add_const<int (Class::*)(int) const&>();
    test_add_const<int (Class::*)(int) const&&>();
    test_add_const<int (Class::*)(int) noexcept>();
    test_add_const<int (Class::*)(int)& noexcept>();
    test_add_const<int (Class::*)(int)&& noexcept>();
    test_add_const<int (Class::*)(int) const noexcept>();
    test_add_const<int (Class::*)(int) const& noexcept>();
    test_add_const<int (Class::*)(int) const&& noexcept>();

    test_add_const<int (Class::*)(...)>();
    test_add_const<int (Class::*)(...)&>();
    test_add_const<int (Class::*)(...) &&>();
    test_add_const<int (Class::*)(...) const>();
    test_add_const<int (Class::*)(...) const&>();
    test_add_const<int (Class::*)(...) const&&>();
    test_add_const<int (Class::*)(...) noexcept>();
    test_add_const<int (Class::*)(...)& noexcept>();
    test_add_const<int (Class::*)(...)&& noexcept>();
    test_add_const<int (Class::*)(...) const noexcept>();
    test_add_const<int (Class::*)(...) const& noexcept>();
    test_add_const<int (Class::*)(...) const&& noexcept>();

    test_add_const<int (Class::*)(int, ...)>();
    test_add_const<int (Class::*)(int, ...)&>();
    test_add_const<int (Class::*)(int, ...) &&>();
    test_add_const<int (Class::*)(int, ...) const>();
    test_add_const<int (Class::*)(int, ...) const&>();
    test_add_const<int (Class::*)(int, ...) const&&>();
    test_add_const<int (Class::*)(int, ...) noexcept>();
    test_add_const<int (Class::*)(int, ...)& noexcept>();
    test_add_const<int (Class::*)(int, ...)&& noexcept>();
    test_add_const<int (Class::*)(int, ...) const noexcept>();
    test_add_const<int (Class::*)(int, ...) const& noexcept>();
    test_add_const<int (Class::*)(int, ...) const&& noexcept>();
}
