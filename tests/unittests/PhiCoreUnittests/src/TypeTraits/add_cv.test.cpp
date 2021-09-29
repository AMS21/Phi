#include <catch2/catch.hpp>

#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/add_cv.hpp>
#include <vector>

template <typename T, typename U>
void test_add_cv_imp()
{
    CHECK_SAME_TYPE(const volatile U, typename phi::add_cv<T>::type);
    CHECK_SAME_TYPE(const volatile U, phi::add_cv_t<T>);
}

template <typename T>
void test_add_cv()
{
    test_add_cv_imp<T, const volatile T>();
    test_add_cv_imp<const T, const volatile T>();
    test_add_cv_imp<volatile T, const volatile T>();
    test_add_cv_imp<const volatile T, const volatile T>();
}

TEST_CASE("add_cv")
{
    test_add_cv<void>();
    test_add_cv<phi::nullptr_t>();
    test_add_cv<bool>();
    test_add_cv<char>();
    test_add_cv<signed char>();
    test_add_cv<unsigned char>();
    test_add_cv<short>();
    test_add_cv<unsigned short>();
    test_add_cv<int>();
    test_add_cv<unsigned int>();
    test_add_cv<long>();
    test_add_cv<unsigned long>();
    test_add_cv<long long>();
    test_add_cv<unsigned long long>();
    test_add_cv<float>();
    test_add_cv<double>();
    test_add_cv<long double>();
    test_add_cv<char8_t>();
    test_add_cv<char16_t>();
    test_add_cv<char32_t>();
    test_add_cv<wchar_t>();

    test_add_cv<phi::Boolean>();
    test_add_cv<phi::Integer<signed char>>();
    test_add_cv<phi::Integer<unsigned char>>();
    test_add_cv<phi::Integer<short>>();
    test_add_cv<phi::Integer<unsigned short>>();
    test_add_cv<phi::Integer<int>>();
    test_add_cv<phi::Integer<unsigned int>>();
    test_add_cv<phi::Integer<long>>();
    test_add_cv<phi::Integer<unsigned long>>();
    test_add_cv<phi::Integer<long long>>();
    test_add_cv<phi::Integer<unsigned long long>>();
    test_add_cv<phi::FloatingPoint<float>>();
    test_add_cv<phi::FloatingPoint<double>>();
    test_add_cv<phi::FloatingPoint<long double>>();

    test_add_cv<std::vector<int>>();
    test_add_cv<phi::ScopePtr<int>>();

    test_add_cv<int&>();
    test_add_cv<const int&>();
    test_add_cv<volatile int&>();
    test_add_cv<const volatile int&>();
    test_add_cv<int&&>();
    test_add_cv<const int&&>();
    test_add_cv<volatile int&&>();
    test_add_cv<const volatile int&&>();
    test_add_cv<int*>();
    test_add_cv<const int*>();
    test_add_cv<volatile int*>();
    test_add_cv<const volatile int*>();
    test_add_cv<int**>();
    test_add_cv<const int**>();
    test_add_cv<volatile int**>();
    test_add_cv<const volatile int**>();
    test_add_cv<int*&>();
    test_add_cv<const int*&>();
    test_add_cv<volatile int*&>();
    test_add_cv<const volatile int*&>();
    test_add_cv<void*>();
    test_add_cv<char[3]>();
    test_add_cv<char[]>();
    test_add_cv<char* [3]>();
    test_add_cv<char*[]>();
    test_add_cv<int(*)[3]>();
    test_add_cv<int(*)[]>();
    test_add_cv<int(&)[3]>();
    test_add_cv<int(&)[]>();
    test_add_cv<char[3][2]>();
    test_add_cv<char[][2]>();
    test_add_cv<char* [3][2]>();
    test_add_cv<char*[][2]>();
    test_add_cv<int(*)[3][2]>();
    test_add_cv<int(*)[][2]>();
    test_add_cv<int(&)[3][2]>();
    test_add_cv<int(&)[][2]>();
    test_add_cv<Class>();
    test_add_cv<Class[]>();
    test_add_cv<Class[2]>();
    test_add_cv<Struct>();
    test_add_cv<TemplateClass<void>>();
    test_add_cv<TemplateClass<int>>();
    test_add_cv<TemplateClass<Class>>();
    test_add_cv<TemplateClass<incomplete_type>>();
    test_add_cv<TemplateStruct<void>>();
    test_add_cv<TemplateStruct<int>>();
    test_add_cv<TemplateStruct<Class>>();
    test_add_cv<TemplateStruct<incomplete_type>>();
    test_add_cv<VariadicTemplateClass<>>();
    test_add_cv<VariadicTemplateClass<void>>();
    test_add_cv<VariadicTemplateClass<int>>();
    test_add_cv<VariadicTemplateClass<Class>>();
    test_add_cv<VariadicTemplateClass<incomplete_type>>();
    test_add_cv<VariadicTemplateClass<int, void, Class, volatile char[]>>();
    test_add_cv<VariadicTemplateStruct<>>();
    test_add_cv<VariadicTemplateStruct<void>>();
    test_add_cv<VariadicTemplateStruct<int>>();
    test_add_cv<VariadicTemplateStruct<Class>>();
    test_add_cv<VariadicTemplateStruct<incomplete_type>>();
    test_add_cv<VariadicTemplateStruct<int, void, Class, volatile char[]>>();
    test_add_cv<PublicDerviedFromTemplate<Base>>();
    test_add_cv<PublicDerviedFromTemplate<Derived>>();
    test_add_cv<PublicDerviedFromTemplate<Class>>();
    test_add_cv<PrivateDerviedFromTemplate<Base>>();
    test_add_cv<PrivateDerviedFromTemplate<Derived>>();
    test_add_cv<PrivateDerviedFromTemplate<Class>>();
    test_add_cv<ProtectedDerviedFromTemplate<Base>>();
    test_add_cv<ProtectedDerviedFromTemplate<Derived>>();
    test_add_cv<ProtectedDerviedFromTemplate<Class>>();
    test_add_cv<Union>();
    test_add_cv<NonEmptyUnion>();
    test_add_cv<Empty>();
    test_add_cv<NotEmpty>();
    test_add_cv<bit_zero>();
    test_add_cv<bit_one>();
    test_add_cv<Base>();
    test_add_cv<Derived>();
    test_add_cv<Abstract>();
    test_add_cv<AbstractTemplate<int>>();
    test_add_cv<AbstractTemplate<double>>();
    test_add_cv<AbstractTemplate<Class>>();
    test_add_cv<AbstractTemplate<incomplete_type>>();
    test_add_cv<Final>();
    test_add_cv<Enum>();
    test_add_cv<EnumSigned>();
    test_add_cv<EnumUnsigned>();
    test_add_cv<EnumClass>();
    test_add_cv<EnumStruct>();
    test_add_cv<Function>();
    test_add_cv<FunctionPtr>();
    test_add_cv<MemberObjectPtr>();
    test_add_cv<MemberFunctionPtr>();
    test_add_cv<incomplete_type>();
    test_add_cv<IncompleteTemplate<void>>();
    test_add_cv<IncompleteTemplate<int>>();
    test_add_cv<IncompleteTemplate<Class>>();
    test_add_cv<IncompleteTemplate<incomplete_type>>();
    test_add_cv<int Class::*>();
    test_add_cv<float Class::*>();
    test_add_cv<void * Class::*>();
    test_add_cv<int * Class::*>();
    test_add_cv<NonCopyable>();
    test_add_cv<NonMoveable>();
    test_add_cv<NonConstructible>();
    test_add_cv<Tracked>();
    test_add_cv<TrapConstructible>();
    test_add_cv<TrapImplicitConversion>();
    test_add_cv<TrapComma>();
    test_add_cv<TrapCall>();
    test_add_cv<TrapSelfAssign>();

    test_add_cv<void()>();
    test_add_cv<void()&>();
    test_add_cv<void() &&>();
    test_add_cv<void() const>();
    test_add_cv<void() const&>();
    test_add_cv<void() const&&>();
    test_add_cv<void() noexcept>();
    test_add_cv<void()& noexcept>();
    test_add_cv<void()&& noexcept>();
    test_add_cv<void() const noexcept>();
    test_add_cv<void() const& noexcept>();
    test_add_cv<void() const&& noexcept>();

    test_add_cv<void(int)>();
    test_add_cv<void(int)&>();
    test_add_cv<void(int) &&>();
    test_add_cv<void(int) const>();
    test_add_cv<void(int) const&>();
    test_add_cv<void(int) const&&>();
    test_add_cv<void(int) noexcept>();
    test_add_cv<void(int)& noexcept>();
    test_add_cv<void(int)&& noexcept>();
    test_add_cv<void(int) const noexcept>();
    test_add_cv<void(int) const& noexcept>();
    test_add_cv<void(int) const&& noexcept>();

    test_add_cv<void(...)>();
    test_add_cv<void(...)&>();
    test_add_cv<void(...) &&>();
    test_add_cv<void(...) const>();
    test_add_cv<void(...) const&>();
    test_add_cv<void(...) const&&>();
    test_add_cv<void(...) noexcept>();
    test_add_cv<void(...)& noexcept>();
    test_add_cv<void(...)&& noexcept>();
    test_add_cv<void(...) const noexcept>();
    test_add_cv<void(...) const& noexcept>();
    test_add_cv<void(...) const&& noexcept>();

    test_add_cv<void(int, ...)>();
    test_add_cv<void(int, ...)&>();
    test_add_cv<void(int, ...) &&>();
    test_add_cv<void(int, ...) const>();
    test_add_cv<void(int, ...) const&>();
    test_add_cv<void(int, ...) const&&>();
    test_add_cv<void(int, ...) noexcept>();
    test_add_cv<void(int, ...)& noexcept>();
    test_add_cv<void(int, ...)&& noexcept>();
    test_add_cv<void(int, ...) const noexcept>();
    test_add_cv<void(int, ...) const& noexcept>();
    test_add_cv<void(int, ...) const&& noexcept>();

    test_add_cv<int()>();
    test_add_cv<int()&>();
    test_add_cv<int() &&>();
    test_add_cv<int() const>();
    test_add_cv<int() const&>();
    test_add_cv<int() const&&>();
    test_add_cv<int() noexcept>();
    test_add_cv<int()& noexcept>();
    test_add_cv<int()&& noexcept>();
    test_add_cv<int() const noexcept>();
    test_add_cv<int() const& noexcept>();
    test_add_cv<int() const&& noexcept>();

    test_add_cv<int(int)>();
    test_add_cv<int(int)&>();
    test_add_cv<int(int) &&>();
    test_add_cv<int(int) const>();
    test_add_cv<int(int) const&>();
    test_add_cv<int(int) const&&>();
    test_add_cv<int(int) noexcept>();
    test_add_cv<int(int)& noexcept>();
    test_add_cv<int(int)&& noexcept>();
    test_add_cv<int(int) const noexcept>();
    test_add_cv<int(int) const& noexcept>();
    test_add_cv<int(int) const&& noexcept>();

    test_add_cv<int(...)>();
    test_add_cv<int(...)&>();
    test_add_cv<int(...) &&>();
    test_add_cv<int(...) const>();
    test_add_cv<int(...) const&>();
    test_add_cv<int(...) const&&>();
    test_add_cv<int(...) noexcept>();
    test_add_cv<int(...)& noexcept>();
    test_add_cv<int(...)&& noexcept>();
    test_add_cv<int(...) const noexcept>();
    test_add_cv<int(...) const& noexcept>();
    test_add_cv<int(...) const&& noexcept>();

    test_add_cv<int(int, ...)>();
    test_add_cv<int(int, ...)&>();
    test_add_cv<int(int, ...) &&>();
    test_add_cv<int(int, ...) const>();
    test_add_cv<int(int, ...) const&>();
    test_add_cv<int(int, ...) const&&>();
    test_add_cv<int(int, ...) noexcept>();
    test_add_cv<int(int, ...)& noexcept>();
    test_add_cv<int(int, ...)&& noexcept>();
    test_add_cv<int(int, ...) const noexcept>();
    test_add_cv<int(int, ...) const& noexcept>();
    test_add_cv<int(int, ...) const&& noexcept>();

    test_add_cv<void (*)()>();
    test_add_cv<void (*)() noexcept>();

    test_add_cv<void (*)(int)>();
    test_add_cv<void (*)(int) noexcept>();

    test_add_cv<void (*)(...)>();
    test_add_cv<void (*)(...) noexcept>();

    test_add_cv<void (*)(int, ...)>();
    test_add_cv<void (*)(int, ...) noexcept>();

    test_add_cv<int (*)()>();
    test_add_cv<int (*)() noexcept>();

    test_add_cv<int (*)(int)>();
    test_add_cv<int (*)(int) noexcept>();

    test_add_cv<int (*)(...)>();
    test_add_cv<int (*)(...) noexcept>();

    test_add_cv<int (*)(int, ...)>();
    test_add_cv<int (*)(int, ...) noexcept>();

    test_add_cv<void (&)()>();
    test_add_cv<void (&)() noexcept>();

    test_add_cv<void (&)(int)>();
    test_add_cv<void (&)(int) noexcept>();

    test_add_cv<void (&)(...)>();
    test_add_cv<void (&)(...) noexcept>();

    test_add_cv<void (&)(int, ...)>();
    test_add_cv<void (&)(int, ...) noexcept>();

    test_add_cv<int (&)()>();
    test_add_cv<int (&)() noexcept>();

    test_add_cv<int (&)(int)>();
    test_add_cv<int (&)(int) noexcept>();

    test_add_cv<int (&)(...)>();
    test_add_cv<int (&)(...) noexcept>();

    test_add_cv<int (&)(int, ...)>();
    test_add_cv<int (&)(int, ...) noexcept>();

    test_add_cv<void (Class::*)()>();
    test_add_cv<void (Class::*)()&>();
    test_add_cv<void (Class::*)() &&>();
    test_add_cv<void (Class::*)() const>();
    test_add_cv<void (Class::*)() const&>();
    test_add_cv<void (Class::*)() const&&>();
    test_add_cv<void (Class::*)() noexcept>();
    test_add_cv<void (Class::*)()& noexcept>();
    test_add_cv<void (Class::*)()&& noexcept>();
    test_add_cv<void (Class::*)() const noexcept>();
    test_add_cv<void (Class::*)() const& noexcept>();
    test_add_cv<void (Class::*)() const&& noexcept>();

    test_add_cv<void (Class::*)(int)>();
    test_add_cv<void (Class::*)(int)&>();
    test_add_cv<void (Class::*)(int) &&>();
    test_add_cv<void (Class::*)(int) const>();
    test_add_cv<void (Class::*)(int) const&>();
    test_add_cv<void (Class::*)(int) const&&>();
    test_add_cv<void (Class::*)(int) noexcept>();
    test_add_cv<void (Class::*)(int)& noexcept>();
    test_add_cv<void (Class::*)(int)&& noexcept>();
    test_add_cv<void (Class::*)(int) const noexcept>();
    test_add_cv<void (Class::*)(int) const& noexcept>();
    test_add_cv<void (Class::*)(int) const&& noexcept>();

    test_add_cv<void (Class::*)(...)>();
    test_add_cv<void (Class::*)(...)&>();
    test_add_cv<void (Class::*)(...) &&>();
    test_add_cv<void (Class::*)(...) const>();
    test_add_cv<void (Class::*)(...) const&>();
    test_add_cv<void (Class::*)(...) const&&>();
    test_add_cv<void (Class::*)(...) noexcept>();
    test_add_cv<void (Class::*)(...)& noexcept>();
    test_add_cv<void (Class::*)(...)&& noexcept>();
    test_add_cv<void (Class::*)(...) const noexcept>();
    test_add_cv<void (Class::*)(...) const& noexcept>();
    test_add_cv<void (Class::*)(...) const&& noexcept>();

    test_add_cv<void (Class::*)(int, ...)>();
    test_add_cv<void (Class::*)(int, ...)&>();
    test_add_cv<void (Class::*)(int, ...) &&>();
    test_add_cv<void (Class::*)(int, ...) const>();
    test_add_cv<void (Class::*)(int, ...) const&>();
    test_add_cv<void (Class::*)(int, ...) const&&>();
    test_add_cv<void (Class::*)(int, ...) noexcept>();
    test_add_cv<void (Class::*)(int, ...)& noexcept>();
    test_add_cv<void (Class::*)(int, ...)&& noexcept>();
    test_add_cv<void (Class::*)(int, ...) const noexcept>();
    test_add_cv<void (Class::*)(int, ...) const& noexcept>();
    test_add_cv<void (Class::*)(int, ...) const&& noexcept>();

    test_add_cv<int (Class::*)()>();
    test_add_cv<int (Class::*)()&>();
    test_add_cv<int (Class::*)() &&>();
    test_add_cv<int (Class::*)() const>();
    test_add_cv<int (Class::*)() const&>();
    test_add_cv<int (Class::*)() const&&>();
    test_add_cv<int (Class::*)() noexcept>();
    test_add_cv<int (Class::*)()& noexcept>();
    test_add_cv<int (Class::*)()&& noexcept>();
    test_add_cv<int (Class::*)() const noexcept>();
    test_add_cv<int (Class::*)() const& noexcept>();
    test_add_cv<int (Class::*)() const&& noexcept>();

    test_add_cv<int (Class::*)(int)>();
    test_add_cv<int (Class::*)(int)&>();
    test_add_cv<int (Class::*)(int) &&>();
    test_add_cv<int (Class::*)(int) const>();
    test_add_cv<int (Class::*)(int) const&>();
    test_add_cv<int (Class::*)(int) const&&>();
    test_add_cv<int (Class::*)(int) noexcept>();
    test_add_cv<int (Class::*)(int)& noexcept>();
    test_add_cv<int (Class::*)(int)&& noexcept>();
    test_add_cv<int (Class::*)(int) const noexcept>();
    test_add_cv<int (Class::*)(int) const& noexcept>();
    test_add_cv<int (Class::*)(int) const&& noexcept>();

    test_add_cv<int (Class::*)(...)>();
    test_add_cv<int (Class::*)(...)&>();
    test_add_cv<int (Class::*)(...) &&>();
    test_add_cv<int (Class::*)(...) const>();
    test_add_cv<int (Class::*)(...) const&>();
    test_add_cv<int (Class::*)(...) const&&>();
    test_add_cv<int (Class::*)(...) noexcept>();
    test_add_cv<int (Class::*)(...)& noexcept>();
    test_add_cv<int (Class::*)(...)&& noexcept>();
    test_add_cv<int (Class::*)(...) const noexcept>();
    test_add_cv<int (Class::*)(...) const& noexcept>();
    test_add_cv<int (Class::*)(...) const&& noexcept>();

    test_add_cv<int (Class::*)(int, ...)>();
    test_add_cv<int (Class::*)(int, ...)&>();
    test_add_cv<int (Class::*)(int, ...) &&>();
    test_add_cv<int (Class::*)(int, ...) const>();
    test_add_cv<int (Class::*)(int, ...) const&>();
    test_add_cv<int (Class::*)(int, ...) const&&>();
    test_add_cv<int (Class::*)(int, ...) noexcept>();
    test_add_cv<int (Class::*)(int, ...)& noexcept>();
    test_add_cv<int (Class::*)(int, ...)&& noexcept>();
    test_add_cv<int (Class::*)(int, ...) const noexcept>();
    test_add_cv<int (Class::*)(int, ...) const& noexcept>();
    test_add_cv<int (Class::*)(int, ...) const&& noexcept>();
}
