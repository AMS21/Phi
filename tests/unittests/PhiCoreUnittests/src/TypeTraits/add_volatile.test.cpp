#include <catch2/catch.hpp>

#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/add_volatile.hpp>
#include <vector>

template <typename T>
void test_add_volatile()
{
    CHECK_SAME_TYPE(typename phi::add_volatile<T>::type, volatile T);
    CHECK_SAME_TYPE(typename phi::add_volatile<const T>::type, const volatile T);
    CHECK_SAME_TYPE(typename phi::add_volatile<volatile T>::type, volatile T);
    CHECK_SAME_TYPE(typename phi::add_volatile<const volatile T>::type, const volatile T);

    CHECK_SAME_TYPE(phi::add_volatile_t<T>, volatile T);
    CHECK_SAME_TYPE(phi::add_volatile_t<const T>, const volatile T);
    CHECK_SAME_TYPE(phi::add_volatile_t<volatile T>, volatile T);
    CHECK_SAME_TYPE(phi::add_volatile_t<const volatile T>, const volatile T);
}

TEST_CASE("add_volatile")
{
    test_add_volatile<void>();
    test_add_volatile<phi::nullptr_t>();
    test_add_volatile<bool>();
    test_add_volatile<char>();
    test_add_volatile<signed char>();
    test_add_volatile<unsigned char>();
    test_add_volatile<short>();
    test_add_volatile<unsigned short>();
    test_add_volatile<int>();
    test_add_volatile<unsigned int>();
    test_add_volatile<long>();
    test_add_volatile<unsigned long>();
    test_add_volatile<long long>();
    test_add_volatile<unsigned long long>();
    test_add_volatile<float>();
    test_add_volatile<double>();
    test_add_volatile<long double>();
    test_add_volatile<char8_t>();
    test_add_volatile<char16_t>();
    test_add_volatile<char32_t>();
    test_add_volatile<wchar_t>();

    test_add_volatile<phi::Boolean>();
    test_add_volatile<phi::Integer<signed char>>();
    test_add_volatile<phi::Integer<unsigned char>>();
    test_add_volatile<phi::Integer<short>>();
    test_add_volatile<phi::Integer<unsigned short>>();
    test_add_volatile<phi::Integer<int>>();
    test_add_volatile<phi::Integer<unsigned int>>();
    test_add_volatile<phi::Integer<long>>();
    test_add_volatile<phi::Integer<unsigned long>>();
    test_add_volatile<phi::Integer<long long>>();
    test_add_volatile<phi::Integer<unsigned long long>>();
    test_add_volatile<phi::FloatingPoint<float>>();
    test_add_volatile<phi::FloatingPoint<double>>();
    test_add_volatile<phi::FloatingPoint<long double>>();

    test_add_volatile<std::vector<int>>();
    test_add_volatile<phi::ScopePtr<int>>();

    test_add_volatile<int&>();
    test_add_volatile<const int&>();
    test_add_volatile<volatile int&>();
    test_add_volatile<const volatile int&>();
    test_add_volatile<int&&>();
    test_add_volatile<const int&&>();
    test_add_volatile<volatile int&&>();
    test_add_volatile<const volatile int&&>();
    test_add_volatile<int*>();
    test_add_volatile<const int*>();
    test_add_volatile<volatile int*>();
    test_add_volatile<const volatile int*>();
    test_add_volatile<int**>();
    test_add_volatile<const int**>();
    test_add_volatile<volatile int**>();
    test_add_volatile<const volatile int**>();
    test_add_volatile<int*&>();
    test_add_volatile<const int*&>();
    test_add_volatile<volatile int*&>();
    test_add_volatile<const volatile int*&>();
    test_add_volatile<int*&&>();
    test_add_volatile<const int*&&>();
    test_add_volatile<volatile int*&&>();
    test_add_volatile<const volatile int*&&>();
    test_add_volatile<void*>();
    test_add_volatile<char[3]>();
    test_add_volatile<char[]>();
    test_add_volatile<char* [3]>();
    test_add_volatile<char*[]>();
    test_add_volatile<int(*)[3]>();
    test_add_volatile<int(*)[]>();
    test_add_volatile<int(&)[3]>();
    test_add_volatile<int(&)[]>();
    test_add_volatile<int(&&)[3]>();
    test_add_volatile<int(&&)[]>();
    test_add_volatile<char[3][2]>();
    test_add_volatile<char[][2]>();
    test_add_volatile<char* [3][2]>();
    test_add_volatile<char*[][2]>();
    test_add_volatile<int(*)[3][2]>();
    test_add_volatile<int(*)[][2]>();
    test_add_volatile<int(&)[3][2]>();
    test_add_volatile<int(&)[][2]>();
    test_add_volatile<int(&&)[3][2]>();
    test_add_volatile<int(&&)[][2]>();
    test_add_volatile<Class>();
    test_add_volatile<Class[]>();
    test_add_volatile<Class[2]>();
    test_add_volatile<Struct>();
    test_add_volatile<TemplateClass<void>>();
    test_add_volatile<TemplateClass<int>>();
    test_add_volatile<TemplateClass<Class>>();
    test_add_volatile<TemplateClass<incomplete_type>>();
    test_add_volatile<TemplateStruct<void>>();
    test_add_volatile<TemplateStruct<int>>();
    test_add_volatile<TemplateStruct<Class>>();
    test_add_volatile<TemplateStruct<incomplete_type>>();
    test_add_volatile<VariadicTemplateClass<>>();
    test_add_volatile<VariadicTemplateClass<void>>();
    test_add_volatile<VariadicTemplateClass<int>>();
    test_add_volatile<VariadicTemplateClass<Class>>();
    test_add_volatile<VariadicTemplateClass<incomplete_type>>();
    test_add_volatile<VariadicTemplateClass<int, void, Class, volatile char[]>>();
    test_add_volatile<VariadicTemplateStruct<>>();
    test_add_volatile<VariadicTemplateStruct<void>>();
    test_add_volatile<VariadicTemplateStruct<int>>();
    test_add_volatile<VariadicTemplateStruct<Class>>();
    test_add_volatile<VariadicTemplateStruct<incomplete_type>>();
    test_add_volatile<VariadicTemplateStruct<int, void, Class, volatile char[]>>();
    test_add_volatile<PublicDerviedFromTemplate<Base>>();
    test_add_volatile<PublicDerviedFromTemplate<Derived>>();
    test_add_volatile<PublicDerviedFromTemplate<Class>>();
    test_add_volatile<PrivateDerviedFromTemplate<Base>>();
    test_add_volatile<PrivateDerviedFromTemplate<Derived>>();
    test_add_volatile<PrivateDerviedFromTemplate<Class>>();
    test_add_volatile<ProtectedDerviedFromTemplate<Base>>();
    test_add_volatile<ProtectedDerviedFromTemplate<Derived>>();
    test_add_volatile<ProtectedDerviedFromTemplate<Class>>();
    test_add_volatile<Union>();
    test_add_volatile<NonEmptyUnion>();
    test_add_volatile<Empty>();
    test_add_volatile<NotEmpty>();
    test_add_volatile<bit_zero>();
    test_add_volatile<bit_one>();
    test_add_volatile<Base>();
    test_add_volatile<Derived>();
    test_add_volatile<Abstract>();
    test_add_volatile<AbstractTemplate<int>>();
    test_add_volatile<AbstractTemplate<double>>();
    test_add_volatile<AbstractTemplate<Class>>();
    test_add_volatile<AbstractTemplate<incomplete_type>>();
    test_add_volatile<Final>();
    test_add_volatile<Enum>();
    test_add_volatile<EnumSigned>();
    test_add_volatile<EnumUnsigned>();
    test_add_volatile<EnumClass>();
    test_add_volatile<EnumStruct>();
    test_add_volatile<Function>();
    test_add_volatile<FunctionPtr>();
    test_add_volatile<MemberObjectPtr>();
    test_add_volatile<MemberFunctionPtr>();
    test_add_volatile<incomplete_type>();
    test_add_volatile<IncompleteTemplate<void>>();
    test_add_volatile<IncompleteTemplate<int>>();
    test_add_volatile<IncompleteTemplate<Class>>();
    test_add_volatile<IncompleteTemplate<incomplete_type>>();
    test_add_volatile<IncompleteVariadicTemplate<>>();
    test_add_volatile<IncompleteVariadicTemplate<void>>();
    test_add_volatile<IncompleteVariadicTemplate<int>>();
    test_add_volatile<IncompleteVariadicTemplate<Class>>();
    test_add_volatile<IncompleteVariadicTemplate<incomplete_type>>();
    test_add_volatile<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_add_volatile<int Class::*>();
    test_add_volatile<float Class::*>();
    test_add_volatile<void * Class::*>();
    test_add_volatile<int * Class::*>();
    test_add_volatile<int Class::*&>();
    test_add_volatile<float Class::*&>();
    test_add_volatile<void * Class::*&>();
    test_add_volatile<int * Class::*&>();
    test_add_volatile<int Class::*&&>();
    test_add_volatile<float Class::*&&>();
    test_add_volatile<void * Class::*&&>();
    test_add_volatile<int * Class::*&&>();
    test_add_volatile<int Class::*const>();
    test_add_volatile<float Class::*const>();
    test_add_volatile<void * Class::*const>();
    test_add_volatile<int Class::*const&>();
    test_add_volatile<float Class::*const&>();
    test_add_volatile<void * Class::*const&>();
    test_add_volatile<int Class::*const&&>();
    test_add_volatile<float Class::*const&&>();
    test_add_volatile<void * Class::*const&&>();
    test_add_volatile<int Class::*volatile>();
    test_add_volatile<float Class::*volatile>();
    test_add_volatile<void * Class::*volatile>();
    test_add_volatile<int Class::*volatile&>();
    test_add_volatile<float Class::*volatile&>();
    test_add_volatile<void * Class::*volatile&>();
    test_add_volatile<int Class::*volatile&&>();
    test_add_volatile<float Class::*volatile&&>();
    test_add_volatile<void * Class::*volatile&&>();
    test_add_volatile<int Class::*const volatile>();
    test_add_volatile<float Class::*const volatile>();
    test_add_volatile<void * Class::*const volatile>();
    test_add_volatile<int Class::*const volatile&>();
    test_add_volatile<float Class::*const volatile&>();
    test_add_volatile<void * Class::*const volatile&>();
    test_add_volatile<int Class::*const volatile&&>();
    test_add_volatile<float Class::*const volatile&&>();
    test_add_volatile<void * Class::*const volatile&&>();
    test_add_volatile<NonCopyable>();
    test_add_volatile<NonMoveable>();
    test_add_volatile<NonConstructible>();
    test_add_volatile<Tracked>();
    test_add_volatile<TrapConstructible>();
    test_add_volatile<TrapImplicitConversion>();
    test_add_volatile<TrapComma>();
    test_add_volatile<TrapCall>();
    test_add_volatile<TrapSelfAssign>();

    test_add_volatile<void()>();
    test_add_volatile<void()&>();
    test_add_volatile<void() &&>();
    test_add_volatile<void() const>();
    test_add_volatile<void() const&>();
    test_add_volatile<void() const&&>();
    test_add_volatile<void() noexcept>();
    test_add_volatile<void()& noexcept>();
    test_add_volatile<void()&& noexcept>();
    test_add_volatile<void() const noexcept>();
    test_add_volatile<void() const& noexcept>();
    test_add_volatile<void() const&& noexcept>();

    test_add_volatile<void(int)>();
    test_add_volatile<void(int)&>();
    test_add_volatile<void(int) &&>();
    test_add_volatile<void(int) const>();
    test_add_volatile<void(int) const&>();
    test_add_volatile<void(int) const&&>();
    test_add_volatile<void(int) noexcept>();
    test_add_volatile<void(int)& noexcept>();
    test_add_volatile<void(int)&& noexcept>();
    test_add_volatile<void(int) const noexcept>();
    test_add_volatile<void(int) const& noexcept>();
    test_add_volatile<void(int) const&& noexcept>();

    test_add_volatile<void(...)>();
    test_add_volatile<void(...)&>();
    test_add_volatile<void(...) &&>();
    test_add_volatile<void(...) const>();
    test_add_volatile<void(...) const&>();
    test_add_volatile<void(...) const&&>();
    test_add_volatile<void(...) noexcept>();
    test_add_volatile<void(...)& noexcept>();
    test_add_volatile<void(...)&& noexcept>();
    test_add_volatile<void(...) const noexcept>();
    test_add_volatile<void(...) const& noexcept>();
    test_add_volatile<void(...) const&& noexcept>();

    test_add_volatile<void(int, ...)>();
    test_add_volatile<void(int, ...)&>();
    test_add_volatile<void(int, ...) &&>();
    test_add_volatile<void(int, ...) const>();
    test_add_volatile<void(int, ...) const&>();
    test_add_volatile<void(int, ...) const&&>();
    test_add_volatile<void(int, ...) noexcept>();
    test_add_volatile<void(int, ...)& noexcept>();
    test_add_volatile<void(int, ...)&& noexcept>();
    test_add_volatile<void(int, ...) const noexcept>();
    test_add_volatile<void(int, ...) const& noexcept>();
    test_add_volatile<void(int, ...) const&& noexcept>();

    test_add_volatile<int()>();
    test_add_volatile<int()&>();
    test_add_volatile<int() &&>();
    test_add_volatile<int() const>();
    test_add_volatile<int() const&>();
    test_add_volatile<int() const&&>();
    test_add_volatile<int() noexcept>();
    test_add_volatile<int()& noexcept>();
    test_add_volatile<int()&& noexcept>();
    test_add_volatile<int() const noexcept>();
    test_add_volatile<int() const& noexcept>();
    test_add_volatile<int() const&& noexcept>();

    test_add_volatile<int(int)>();
    test_add_volatile<int(int)&>();
    test_add_volatile<int(int) &&>();
    test_add_volatile<int(int) const>();
    test_add_volatile<int(int) const&>();
    test_add_volatile<int(int) const&&>();
    test_add_volatile<int(int) noexcept>();
    test_add_volatile<int(int)& noexcept>();
    test_add_volatile<int(int)&& noexcept>();
    test_add_volatile<int(int) const noexcept>();
    test_add_volatile<int(int) const& noexcept>();
    test_add_volatile<int(int) const&& noexcept>();

    test_add_volatile<int(...)>();
    test_add_volatile<int(...)&>();
    test_add_volatile<int(...) &&>();
    test_add_volatile<int(...) const>();
    test_add_volatile<int(...) const&>();
    test_add_volatile<int(...) const&&>();
    test_add_volatile<int(...) noexcept>();
    test_add_volatile<int(...)& noexcept>();
    test_add_volatile<int(...)&& noexcept>();
    test_add_volatile<int(...) const noexcept>();
    test_add_volatile<int(...) const& noexcept>();
    test_add_volatile<int(...) const&& noexcept>();

    test_add_volatile<int(int, ...)>();
    test_add_volatile<int(int, ...)&>();
    test_add_volatile<int(int, ...) &&>();
    test_add_volatile<int(int, ...) const>();
    test_add_volatile<int(int, ...) const&>();
    test_add_volatile<int(int, ...) const&&>();
    test_add_volatile<int(int, ...) noexcept>();
    test_add_volatile<int(int, ...)& noexcept>();
    test_add_volatile<int(int, ...)&& noexcept>();
    test_add_volatile<int(int, ...) const noexcept>();
    test_add_volatile<int(int, ...) const& noexcept>();
    test_add_volatile<int(int, ...) const&& noexcept>();

    test_add_volatile<void (*)()>();
    test_add_volatile<void (*)() noexcept>();

    test_add_volatile<void (*)(int)>();
    test_add_volatile<void (*)(int) noexcept>();

    test_add_volatile<void (*)(...)>();
    test_add_volatile<void (*)(...) noexcept>();

    test_add_volatile<void (*)(int, ...)>();
    test_add_volatile<void (*)(int, ...) noexcept>();

    test_add_volatile<int (*)()>();
    test_add_volatile<int (*)() noexcept>();

    test_add_volatile<int (*)(int)>();
    test_add_volatile<int (*)(int) noexcept>();

    test_add_volatile<int (*)(...)>();
    test_add_volatile<int (*)(...) noexcept>();

    test_add_volatile<int (*)(int, ...)>();
    test_add_volatile<int (*)(int, ...) noexcept>();

    test_add_volatile<void (&)()>();
    test_add_volatile<void (&)() noexcept>();

    test_add_volatile<void (&)(int)>();
    test_add_volatile<void (&)(int) noexcept>();

    test_add_volatile<void (&)(...)>();
    test_add_volatile<void (&)(...) noexcept>();

    test_add_volatile<void (&)(int, ...)>();
    test_add_volatile<void (&)(int, ...) noexcept>();

    test_add_volatile<int (&)()>();
    test_add_volatile<int (&)() noexcept>();

    test_add_volatile<int (&)(int)>();
    test_add_volatile<int (&)(int) noexcept>();

    test_add_volatile<int (&)(...)>();
    test_add_volatile<int (&)(...) noexcept>();

    test_add_volatile<int (&)(int, ...)>();
    test_add_volatile<int (&)(int, ...) noexcept>();

    test_add_volatile<void(&&)()>();
    test_add_volatile<void(&&)() noexcept>();

    test_add_volatile<void(&&)(int)>();
    test_add_volatile<void(&&)(int) noexcept>();

    test_add_volatile<void(&&)(...)>();
    test_add_volatile<void(&&)(...) noexcept>();

    test_add_volatile<void(&&)(int, ...)>();
    test_add_volatile<void(&&)(int, ...) noexcept>();

    test_add_volatile<int(&&)()>();
    test_add_volatile<int(&&)() noexcept>();

    test_add_volatile<int(&&)(int)>();
    test_add_volatile<int(&&)(int) noexcept>();

    test_add_volatile<int(&&)(...)>();
    test_add_volatile<int(&&)(...) noexcept>();

    test_add_volatile<int(&&)(int, ...)>();
    test_add_volatile<int(&&)(int, ...) noexcept>();

    test_add_volatile<void (Class::*)()>();
    test_add_volatile<void (Class::*)()&>();
    test_add_volatile<void (Class::*)() &&>();
    test_add_volatile<void (Class::*)() const>();
    test_add_volatile<void (Class::*)() const&>();
    test_add_volatile<void (Class::*)() const&&>();
    test_add_volatile<void (Class::*)() noexcept>();
    test_add_volatile<void (Class::*)()& noexcept>();
    test_add_volatile<void (Class::*)()&& noexcept>();
    test_add_volatile<void (Class::*)() const noexcept>();
    test_add_volatile<void (Class::*)() const& noexcept>();
    test_add_volatile<void (Class::*)() const&& noexcept>();

    test_add_volatile<void (Class::*)(int)>();
    test_add_volatile<void (Class::*)(int)&>();
    test_add_volatile<void (Class::*)(int) &&>();
    test_add_volatile<void (Class::*)(int) const>();
    test_add_volatile<void (Class::*)(int) const&>();
    test_add_volatile<void (Class::*)(int) const&&>();
    test_add_volatile<void (Class::*)(int) noexcept>();
    test_add_volatile<void (Class::*)(int)& noexcept>();
    test_add_volatile<void (Class::*)(int)&& noexcept>();
    test_add_volatile<void (Class::*)(int) const noexcept>();
    test_add_volatile<void (Class::*)(int) const& noexcept>();
    test_add_volatile<void (Class::*)(int) const&& noexcept>();

    test_add_volatile<void (Class::*)(...)>();
    test_add_volatile<void (Class::*)(...)&>();
    test_add_volatile<void (Class::*)(...) &&>();
    test_add_volatile<void (Class::*)(...) const>();
    test_add_volatile<void (Class::*)(...) const&>();
    test_add_volatile<void (Class::*)(...) const&&>();
    test_add_volatile<void (Class::*)(...) noexcept>();
    test_add_volatile<void (Class::*)(...)& noexcept>();
    test_add_volatile<void (Class::*)(...)&& noexcept>();
    test_add_volatile<void (Class::*)(...) const noexcept>();
    test_add_volatile<void (Class::*)(...) const& noexcept>();
    test_add_volatile<void (Class::*)(...) const&& noexcept>();

    test_add_volatile<void (Class::*)(int, ...)>();
    test_add_volatile<void (Class::*)(int, ...)&>();
    test_add_volatile<void (Class::*)(int, ...) &&>();
    test_add_volatile<void (Class::*)(int, ...) const>();
    test_add_volatile<void (Class::*)(int, ...) const&>();
    test_add_volatile<void (Class::*)(int, ...) const&&>();
    test_add_volatile<void (Class::*)(int, ...) noexcept>();
    test_add_volatile<void (Class::*)(int, ...)& noexcept>();
    test_add_volatile<void (Class::*)(int, ...)&& noexcept>();
    test_add_volatile<void (Class::*)(int, ...) const noexcept>();
    test_add_volatile<void (Class::*)(int, ...) const& noexcept>();
    test_add_volatile<void (Class::*)(int, ...) const&& noexcept>();

    test_add_volatile<int (Class::*)()>();
    test_add_volatile<int (Class::*)()&>();
    test_add_volatile<int (Class::*)() &&>();
    test_add_volatile<int (Class::*)() const>();
    test_add_volatile<int (Class::*)() const&>();
    test_add_volatile<int (Class::*)() const&&>();
    test_add_volatile<int (Class::*)() noexcept>();
    test_add_volatile<int (Class::*)()& noexcept>();
    test_add_volatile<int (Class::*)()&& noexcept>();
    test_add_volatile<int (Class::*)() const noexcept>();
    test_add_volatile<int (Class::*)() const& noexcept>();
    test_add_volatile<int (Class::*)() const&& noexcept>();

    test_add_volatile<int (Class::*)(int)>();
    test_add_volatile<int (Class::*)(int)&>();
    test_add_volatile<int (Class::*)(int) &&>();
    test_add_volatile<int (Class::*)(int) const>();
    test_add_volatile<int (Class::*)(int) const&>();
    test_add_volatile<int (Class::*)(int) const&&>();
    test_add_volatile<int (Class::*)(int) noexcept>();
    test_add_volatile<int (Class::*)(int)& noexcept>();
    test_add_volatile<int (Class::*)(int)&& noexcept>();
    test_add_volatile<int (Class::*)(int) const noexcept>();
    test_add_volatile<int (Class::*)(int) const& noexcept>();
    test_add_volatile<int (Class::*)(int) const&& noexcept>();

    test_add_volatile<int (Class::*)(...)>();
    test_add_volatile<int (Class::*)(...)&>();
    test_add_volatile<int (Class::*)(...) &&>();
    test_add_volatile<int (Class::*)(...) const>();
    test_add_volatile<int (Class::*)(...) const&>();
    test_add_volatile<int (Class::*)(...) const&&>();
    test_add_volatile<int (Class::*)(...) noexcept>();
    test_add_volatile<int (Class::*)(...)& noexcept>();
    test_add_volatile<int (Class::*)(...)&& noexcept>();
    test_add_volatile<int (Class::*)(...) const noexcept>();
    test_add_volatile<int (Class::*)(...) const& noexcept>();
    test_add_volatile<int (Class::*)(...) const&& noexcept>();

    test_add_volatile<int (Class::*)(int, ...)>();
    test_add_volatile<int (Class::*)(int, ...)&>();
    test_add_volatile<int (Class::*)(int, ...) &&>();
    test_add_volatile<int (Class::*)(int, ...) const>();
    test_add_volatile<int (Class::*)(int, ...) const&>();
    test_add_volatile<int (Class::*)(int, ...) const&&>();
    test_add_volatile<int (Class::*)(int, ...) noexcept>();
    test_add_volatile<int (Class::*)(int, ...)& noexcept>();
    test_add_volatile<int (Class::*)(int, ...)&& noexcept>();
    test_add_volatile<int (Class::*)(int, ...) const noexcept>();
    test_add_volatile<int (Class::*)(int, ...) const& noexcept>();
    test_add_volatile<int (Class::*)(int, ...) const&& noexcept>();
}
