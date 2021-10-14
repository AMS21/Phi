#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_arithmetic.hpp>
#include <Phi/TypeTraits/is_array.hpp>
#include <Phi/TypeTraits/is_bool.hpp>
#include <Phi/TypeTraits/is_class.hpp>
#include <Phi/TypeTraits/is_compound.hpp>
#include <Phi/TypeTraits/is_enum.hpp>
#include <Phi/TypeTraits/is_floating_point.hpp>
#include <Phi/TypeTraits/is_function.hpp>
#include <Phi/TypeTraits/is_fundamental.hpp>
#include <Phi/TypeTraits/is_integer.hpp>
#include <Phi/TypeTraits/is_integral.hpp>
#include <Phi/TypeTraits/is_lvalue_reference.hpp>
#include <Phi/TypeTraits/is_member_function_pointer.hpp>
#include <Phi/TypeTraits/is_member_object_pointer.hpp>
#include <Phi/TypeTraits/is_member_pointer.hpp>
#include <Phi/TypeTraits/is_null_pointer.hpp>
#include <Phi/TypeTraits/is_object.hpp>
#include <Phi/TypeTraits/is_pointer.hpp>
#include <Phi/TypeTraits/is_reference.hpp>
#include <Phi/TypeTraits/is_rvalue_reference.hpp>
#include <Phi/TypeTraits/is_scalar.hpp>
#include <Phi/TypeTraits/is_union.hpp>
#include <Phi/TypeTraits/is_void.hpp>
#include <vector>

template <typename T>
void test_is_enum_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
    STATIC_REQUIRE(phi::is_compound<T>::value);
    STATIC_REQUIRE(phi::is_enum<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_fundamental<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<T>::value);
    STATIC_REQUIRE(phi::is_object<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
    STATIC_REQUIRE(phi::is_scalar<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
    STATIC_REQUIRE(phi::is_compound_v<T>);
    STATIC_REQUIRE(phi::is_enum_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<T>);
    STATIC_REQUIRE(phi::is_object_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
    STATIC_REQUIRE(phi::is_scalar_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);
#endif
}

template <typename T>
void test_is_enum()
{
    test_is_enum_impl<T>();
    test_is_enum_impl<const T>();
    test_is_enum_impl<volatile T>();
    test_is_enum_impl<const volatile T>();
}

template <typename T>
void test_is_not_enum()
{
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_enum<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_enum<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_enum<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_enum_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_enum_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_enum_v<const volatile T>);
#endif
}

TEST_CASE("is_enum")
{
    test_is_not_enum<void>();
    test_is_not_enum<phi::nullptr_t>();
    test_is_not_enum<bool>();
    test_is_not_enum<char>();
    test_is_not_enum<signed char>();
    test_is_not_enum<unsigned char>();
    test_is_not_enum<short>();
    test_is_not_enum<unsigned short>();
    test_is_not_enum<int>();
    test_is_not_enum<unsigned int>();
    test_is_not_enum<long>();
    test_is_not_enum<unsigned long>();
    test_is_not_enum<long long>();
    test_is_not_enum<unsigned long long>();
    test_is_not_enum<float>();
    test_is_not_enum<double>();
    test_is_not_enum<long double>();
    test_is_not_enum<char8_t>();
    test_is_not_enum<char16_t>();
    test_is_not_enum<char32_t>();
    test_is_not_enum<wchar_t>();

    test_is_not_enum<phi::Boolean>();
    test_is_not_enum<phi::Integer<signed char>>();
    test_is_not_enum<phi::Integer<unsigned char>>();
    test_is_not_enum<phi::Integer<short>>();
    test_is_not_enum<phi::Integer<unsigned short>>();
    test_is_not_enum<phi::Integer<int>>();
    test_is_not_enum<phi::Integer<unsigned int>>();
    test_is_not_enum<phi::Integer<long>>();
    test_is_not_enum<phi::Integer<unsigned long>>();
    test_is_not_enum<phi::Integer<long long>>();
    test_is_not_enum<phi::Integer<unsigned long long>>();
    test_is_not_enum<phi::FloatingPoint<float>>();
    test_is_not_enum<phi::FloatingPoint<double>>();
    test_is_not_enum<phi::FloatingPoint<long double>>();

    test_is_not_enum<std::vector<int>>();
    test_is_not_enum<phi::ScopePtr<int>>();

    test_is_not_enum<int&>();
    test_is_not_enum<const int&>();
    test_is_not_enum<volatile int&>();
    test_is_not_enum<const volatile int&>();
    test_is_not_enum<int&&>();
    test_is_not_enum<const int&&>();
    test_is_not_enum<volatile int&&>();
    test_is_not_enum<const volatile int&&>();
    test_is_not_enum<int*>();
    test_is_not_enum<const int*>();
    test_is_not_enum<volatile int*>();
    test_is_not_enum<const volatile int*>();
    test_is_not_enum<int**>();
    test_is_not_enum<const int**>();
    test_is_not_enum<volatile int**>();
    test_is_not_enum<const volatile int**>();
    test_is_not_enum<int*&>();
    test_is_not_enum<const int*&>();
    test_is_not_enum<volatile int*&>();
    test_is_not_enum<const volatile int*&>();
    test_is_not_enum<int*&&>();
    test_is_not_enum<const int*&&>();
    test_is_not_enum<volatile int*&&>();
    test_is_not_enum<const volatile int*&&>();
    test_is_not_enum<void*>();
    test_is_not_enum<char[3]>();
    test_is_not_enum<char[]>();
    test_is_not_enum<char* [3]>();
    test_is_not_enum<char*[]>();
    test_is_not_enum<int(*)[3]>();
    test_is_not_enum<int(*)[]>();
    test_is_not_enum<int(&)[3]>();
    test_is_not_enum<int(&)[]>();
    test_is_not_enum<int(&&)[3]>();
    test_is_not_enum<int(&&)[]>();
    test_is_not_enum<char[3][2]>();
    test_is_not_enum<char[][2]>();
    test_is_not_enum<char* [3][2]>();
    test_is_not_enum<char*[][2]>();
    test_is_not_enum<int(*)[3][2]>();
    test_is_not_enum<int(*)[][2]>();
    test_is_not_enum<int(&)[3][2]>();
    test_is_not_enum<int(&)[][2]>();
    test_is_not_enum<int(&&)[3][2]>();
    test_is_not_enum<int(&&)[][2]>();
    test_is_not_enum<Class>();
    test_is_not_enum<Class[]>();
    test_is_not_enum<Class[2]>();
    test_is_not_enum<Struct>();
    test_is_not_enum<TemplateClass<void>>();
    test_is_not_enum<TemplateClass<int>>();
    test_is_not_enum<TemplateClass<Class>>();
    test_is_not_enum<TemplateClass<incomplete_type>>();
    test_is_not_enum<TemplateStruct<void>>();
    test_is_not_enum<TemplateStruct<int>>();
    test_is_not_enum<TemplateStruct<Class>>();
    test_is_not_enum<TemplateStruct<incomplete_type>>();
    test_is_not_enum<VariadicTemplateClass<>>();
    test_is_not_enum<VariadicTemplateClass<void>>();
    test_is_not_enum<VariadicTemplateClass<int>>();
    test_is_not_enum<VariadicTemplateClass<Class>>();
    test_is_not_enum<VariadicTemplateClass<incomplete_type>>();
    test_is_not_enum<VariadicTemplateClass<int, void, Class, volatile char[]>>();
    test_is_not_enum<VariadicTemplateStruct<>>();
    test_is_not_enum<VariadicTemplateStruct<void>>();
    test_is_not_enum<VariadicTemplateStruct<int>>();
    test_is_not_enum<VariadicTemplateStruct<Class>>();
    test_is_not_enum<VariadicTemplateStruct<incomplete_type>>();
    test_is_not_enum<VariadicTemplateStruct<int, void, Class, volatile char[]>>();
    test_is_not_enum<PublicDerviedFromTemplate<Base>>();
    test_is_not_enum<PublicDerviedFromTemplate<Derived>>();
    test_is_not_enum<PublicDerviedFromTemplate<Class>>();
    test_is_not_enum<PrivateDerviedFromTemplate<Base>>();
    test_is_not_enum<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_enum<PrivateDerviedFromTemplate<Class>>();
    test_is_not_enum<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_enum<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_enum<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_enum<Union>();
    test_is_not_enum<NonEmptyUnion>();
    test_is_not_enum<Empty>();
    test_is_not_enum<NotEmpty>();
    test_is_not_enum<bit_zero>();
    test_is_not_enum<bit_one>();
    test_is_not_enum<Base>();
    test_is_not_enum<Derived>();
    test_is_not_enum<Abstract>();
    test_is_not_enum<AbstractTemplate<int>>();
    test_is_not_enum<AbstractTemplate<double>>();
    test_is_not_enum<AbstractTemplate<Class>>();
    test_is_not_enum<AbstractTemplate<incomplete_type>>();
    test_is_not_enum<Final>();
    test_is_enum<Enum>();
    test_is_enum<EnumSigned>();
    test_is_enum<EnumUnsigned>();
    test_is_enum<EnumClass>();
    test_is_enum<EnumStruct>();
    test_is_not_enum<Function>();
    test_is_not_enum<FunctionPtr>();
    test_is_not_enum<MemberObjectPtr>();
    test_is_not_enum<MemberFunctionPtr>();
    test_is_not_enum<incomplete_type>();
    test_is_not_enum<IncompleteTemplate<void>>();
    test_is_not_enum<IncompleteTemplate<int>>();
    test_is_not_enum<IncompleteTemplate<Class>>();
    test_is_not_enum<IncompleteTemplate<incomplete_type>>();
    test_is_not_enum<IncompleteVariadicTemplate<>>();
    test_is_not_enum<IncompleteVariadicTemplate<void>>();
    test_is_not_enum<IncompleteVariadicTemplate<int>>();
    test_is_not_enum<IncompleteVariadicTemplate<Class>>();
    test_is_not_enum<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_enum<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_enum<int Class::*>();
    test_is_not_enum<float Class::*>();
    test_is_not_enum<void * Class::*>();
    test_is_not_enum<int * Class::*>();
    test_is_not_enum<int Class::*&>();
    test_is_not_enum<float Class::*&>();
    test_is_not_enum<void * Class::*&>();
    test_is_not_enum<int * Class::*&>();
    test_is_not_enum<int Class::*&&>();
    test_is_not_enum<float Class::*&&>();
    test_is_not_enum<void * Class::*&&>();
    test_is_not_enum<int * Class::*&&>();
    test_is_not_enum<int Class::*const>();
    test_is_not_enum<float Class::*const>();
    test_is_not_enum<void * Class::*const>();
    test_is_not_enum<int Class::*const&>();
    test_is_not_enum<float Class::*const&>();
    test_is_not_enum<void * Class::*const&>();
    test_is_not_enum<int Class::*const&&>();
    test_is_not_enum<float Class::*const&&>();
    test_is_not_enum<void * Class::*const&&>();
    test_is_not_enum<int Class::*volatile>();
    test_is_not_enum<float Class::*volatile>();
    test_is_not_enum<void * Class::*volatile>();
    test_is_not_enum<int Class::*volatile&>();
    test_is_not_enum<float Class::*volatile&>();
    test_is_not_enum<void * Class::*volatile&>();
    test_is_not_enum<int Class::*volatile&&>();
    test_is_not_enum<float Class::*volatile&&>();
    test_is_not_enum<void * Class::*volatile&&>();
    test_is_not_enum<int Class::*const volatile>();
    test_is_not_enum<float Class::*const volatile>();
    test_is_not_enum<void * Class::*const volatile>();
    test_is_not_enum<int Class::*const volatile&>();
    test_is_not_enum<float Class::*const volatile&>();
    test_is_not_enum<void * Class::*const volatile&>();
    test_is_not_enum<int Class::*const volatile&&>();
    test_is_not_enum<float Class::*const volatile&&>();
    test_is_not_enum<void * Class::*const volatile&&>();
    test_is_not_enum<NonCopyable>();
    test_is_not_enum<NonMoveable>();
    test_is_not_enum<NonConstructible>();
    test_is_not_enum<Tracked>();
    test_is_not_enum<TrapConstructible>();
    test_is_not_enum<TrapImplicitConversion>();
    test_is_not_enum<TrapComma>();
    test_is_not_enum<TrapCall>();
    test_is_not_enum<TrapSelfAssign>();

    test_is_not_enum<void()>();
    test_is_not_enum<void()&>();
    test_is_not_enum<void() &&>();
    test_is_not_enum<void() const>();
    test_is_not_enum<void() const&>();
    test_is_not_enum<void() const&&>();
    test_is_not_enum<void() noexcept>();
    test_is_not_enum<void()& noexcept>();
    test_is_not_enum<void()&& noexcept>();
    test_is_not_enum<void() const noexcept>();
    test_is_not_enum<void() const& noexcept>();
    test_is_not_enum<void() const&& noexcept>();

    test_is_not_enum<void(int)>();
    test_is_not_enum<void(int)&>();
    test_is_not_enum<void(int) &&>();
    test_is_not_enum<void(int) const>();
    test_is_not_enum<void(int) const&>();
    test_is_not_enum<void(int) const&&>();
    test_is_not_enum<void(int) noexcept>();
    test_is_not_enum<void(int)& noexcept>();
    test_is_not_enum<void(int)&& noexcept>();
    test_is_not_enum<void(int) const noexcept>();
    test_is_not_enum<void(int) const& noexcept>();
    test_is_not_enum<void(int) const&& noexcept>();

    test_is_not_enum<void(...)>();
    test_is_not_enum<void(...)&>();
    test_is_not_enum<void(...) &&>();
    test_is_not_enum<void(...) const>();
    test_is_not_enum<void(...) const&>();
    test_is_not_enum<void(...) const&&>();
    test_is_not_enum<void(...) noexcept>();
    test_is_not_enum<void(...)& noexcept>();
    test_is_not_enum<void(...)&& noexcept>();
    test_is_not_enum<void(...) const noexcept>();
    test_is_not_enum<void(...) const& noexcept>();
    test_is_not_enum<void(...) const&& noexcept>();

    test_is_not_enum<void(int, ...)>();
    test_is_not_enum<void(int, ...)&>();
    test_is_not_enum<void(int, ...) &&>();
    test_is_not_enum<void(int, ...) const>();
    test_is_not_enum<void(int, ...) const&>();
    test_is_not_enum<void(int, ...) const&&>();
    test_is_not_enum<void(int, ...) noexcept>();
    test_is_not_enum<void(int, ...)& noexcept>();
    test_is_not_enum<void(int, ...)&& noexcept>();
    test_is_not_enum<void(int, ...) const noexcept>();
    test_is_not_enum<void(int, ...) const& noexcept>();
    test_is_not_enum<void(int, ...) const&& noexcept>();

    test_is_not_enum<int()>();
    test_is_not_enum<int()&>();
    test_is_not_enum<int() &&>();
    test_is_not_enum<int() const>();
    test_is_not_enum<int() const&>();
    test_is_not_enum<int() const&&>();
    test_is_not_enum<int() noexcept>();
    test_is_not_enum<int()& noexcept>();
    test_is_not_enum<int()&& noexcept>();
    test_is_not_enum<int() const noexcept>();
    test_is_not_enum<int() const& noexcept>();
    test_is_not_enum<int() const&& noexcept>();

    test_is_not_enum<int(int)>();
    test_is_not_enum<int(int)&>();
    test_is_not_enum<int(int) &&>();
    test_is_not_enum<int(int) const>();
    test_is_not_enum<int(int) const&>();
    test_is_not_enum<int(int) const&&>();
    test_is_not_enum<int(int) noexcept>();
    test_is_not_enum<int(int)& noexcept>();
    test_is_not_enum<int(int)&& noexcept>();
    test_is_not_enum<int(int) const noexcept>();
    test_is_not_enum<int(int) const& noexcept>();
    test_is_not_enum<int(int) const&& noexcept>();

    test_is_not_enum<int(...)>();
    test_is_not_enum<int(...)&>();
    test_is_not_enum<int(...) &&>();
    test_is_not_enum<int(...) const>();
    test_is_not_enum<int(...) const&>();
    test_is_not_enum<int(...) const&&>();
    test_is_not_enum<int(...) noexcept>();
    test_is_not_enum<int(...)& noexcept>();
    test_is_not_enum<int(...)&& noexcept>();
    test_is_not_enum<int(...) const noexcept>();
    test_is_not_enum<int(...) const& noexcept>();
    test_is_not_enum<int(...) const&& noexcept>();

    test_is_not_enum<int(int, ...)>();
    test_is_not_enum<int(int, ...)&>();
    test_is_not_enum<int(int, ...) &&>();
    test_is_not_enum<int(int, ...) const>();
    test_is_not_enum<int(int, ...) const&>();
    test_is_not_enum<int(int, ...) const&&>();
    test_is_not_enum<int(int, ...) noexcept>();
    test_is_not_enum<int(int, ...)& noexcept>();
    test_is_not_enum<int(int, ...)&& noexcept>();
    test_is_not_enum<int(int, ...) const noexcept>();
    test_is_not_enum<int(int, ...) const& noexcept>();
    test_is_not_enum<int(int, ...) const&& noexcept>();

    test_is_not_enum<void (*)()>();
    test_is_not_enum<void (*)() noexcept>();

    test_is_not_enum<void (*)(int)>();
    test_is_not_enum<void (*)(int) noexcept>();

    test_is_not_enum<void (*)(...)>();
    test_is_not_enum<void (*)(...) noexcept>();

    test_is_not_enum<void (*)(int, ...)>();
    test_is_not_enum<void (*)(int, ...) noexcept>();

    test_is_not_enum<int (*)()>();
    test_is_not_enum<int (*)() noexcept>();

    test_is_not_enum<int (*)(int)>();
    test_is_not_enum<int (*)(int) noexcept>();

    test_is_not_enum<int (*)(...)>();
    test_is_not_enum<int (*)(...) noexcept>();

    test_is_not_enum<int (*)(int, ...)>();
    test_is_not_enum<int (*)(int, ...) noexcept>();

    test_is_not_enum<void (&)()>();
    test_is_not_enum<void (&)() noexcept>();

    test_is_not_enum<void (&)(int)>();
    test_is_not_enum<void (&)(int) noexcept>();

    test_is_not_enum<void (&)(...)>();
    test_is_not_enum<void (&)(...) noexcept>();

    test_is_not_enum<void (&)(int, ...)>();
    test_is_not_enum<void (&)(int, ...) noexcept>();

    test_is_not_enum<int (&)()>();
    test_is_not_enum<int (&)() noexcept>();

    test_is_not_enum<int (&)(int)>();
    test_is_not_enum<int (&)(int) noexcept>();

    test_is_not_enum<int (&)(...)>();
    test_is_not_enum<int (&)(...) noexcept>();

    test_is_not_enum<int (&)(int, ...)>();
    test_is_not_enum<int (&)(int, ...) noexcept>();

    test_is_not_enum<void(&&)()>();
    test_is_not_enum<void(&&)() noexcept>();

    test_is_not_enum<void(&&)(int)>();
    test_is_not_enum<void(&&)(int) noexcept>();

    test_is_not_enum<void(&&)(...)>();
    test_is_not_enum<void(&&)(...) noexcept>();

    test_is_not_enum<void(&&)(int, ...)>();
    test_is_not_enum<void(&&)(int, ...) noexcept>();

    test_is_not_enum<int(&&)()>();
    test_is_not_enum<int(&&)() noexcept>();

    test_is_not_enum<int(&&)(int)>();
    test_is_not_enum<int(&&)(int) noexcept>();

    test_is_not_enum<int(&&)(...)>();
    test_is_not_enum<int(&&)(...) noexcept>();

    test_is_not_enum<int(&&)(int, ...)>();
    test_is_not_enum<int(&&)(int, ...) noexcept>();

    test_is_not_enum<void (Class::*)()>();
    test_is_not_enum<void (Class::*)()&>();
    test_is_not_enum<void (Class::*)() &&>();
    test_is_not_enum<void (Class::*)() const>();
    test_is_not_enum<void (Class::*)() const&>();
    test_is_not_enum<void (Class::*)() const&&>();
    test_is_not_enum<void (Class::*)() noexcept>();
    test_is_not_enum<void (Class::*)()& noexcept>();
    test_is_not_enum<void (Class::*)()&& noexcept>();
    test_is_not_enum<void (Class::*)() const noexcept>();
    test_is_not_enum<void (Class::*)() const& noexcept>();
    test_is_not_enum<void (Class::*)() const&& noexcept>();

    test_is_not_enum<void (Class::*)(int)>();
    test_is_not_enum<void (Class::*)(int)&>();
    test_is_not_enum<void (Class::*)(int) &&>();
    test_is_not_enum<void (Class::*)(int) const>();
    test_is_not_enum<void (Class::*)(int) const&>();
    test_is_not_enum<void (Class::*)(int) const&&>();
    test_is_not_enum<void (Class::*)(int) noexcept>();
    test_is_not_enum<void (Class::*)(int)& noexcept>();
    test_is_not_enum<void (Class::*)(int)&& noexcept>();
    test_is_not_enum<void (Class::*)(int) const noexcept>();
    test_is_not_enum<void (Class::*)(int) const& noexcept>();
    test_is_not_enum<void (Class::*)(int) const&& noexcept>();

    test_is_not_enum<void (Class::*)(...)>();
    test_is_not_enum<void (Class::*)(...)&>();
    test_is_not_enum<void (Class::*)(...) &&>();
    test_is_not_enum<void (Class::*)(...) const>();
    test_is_not_enum<void (Class::*)(...) const&>();
    test_is_not_enum<void (Class::*)(...) const&&>();
    test_is_not_enum<void (Class::*)(...) noexcept>();
    test_is_not_enum<void (Class::*)(...)& noexcept>();
    test_is_not_enum<void (Class::*)(...)&& noexcept>();
    test_is_not_enum<void (Class::*)(...) const noexcept>();
    test_is_not_enum<void (Class::*)(...) const& noexcept>();
    test_is_not_enum<void (Class::*)(...) const&& noexcept>();

    test_is_not_enum<void (Class::*)(int, ...)>();
    test_is_not_enum<void (Class::*)(int, ...)&>();
    test_is_not_enum<void (Class::*)(int, ...) &&>();
    test_is_not_enum<void (Class::*)(int, ...) const>();
    test_is_not_enum<void (Class::*)(int, ...) const&>();
    test_is_not_enum<void (Class::*)(int, ...) const&&>();
    test_is_not_enum<void (Class::*)(int, ...) noexcept>();
    test_is_not_enum<void (Class::*)(int, ...)& noexcept>();
    test_is_not_enum<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_enum<void (Class::*)(int, ...) const noexcept>();
    test_is_not_enum<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_enum<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_enum<int (Class::*)()>();
    test_is_not_enum<int (Class::*)()&>();
    test_is_not_enum<int (Class::*)() &&>();
    test_is_not_enum<int (Class::*)() const>();
    test_is_not_enum<int (Class::*)() const&>();
    test_is_not_enum<int (Class::*)() const&&>();
    test_is_not_enum<int (Class::*)() noexcept>();
    test_is_not_enum<int (Class::*)()& noexcept>();
    test_is_not_enum<int (Class::*)()&& noexcept>();
    test_is_not_enum<int (Class::*)() const noexcept>();
    test_is_not_enum<int (Class::*)() const& noexcept>();
    test_is_not_enum<int (Class::*)() const&& noexcept>();

    test_is_not_enum<int (Class::*)(int)>();
    test_is_not_enum<int (Class::*)(int)&>();
    test_is_not_enum<int (Class::*)(int) &&>();
    test_is_not_enum<int (Class::*)(int) const>();
    test_is_not_enum<int (Class::*)(int) const&>();
    test_is_not_enum<int (Class::*)(int) const&&>();
    test_is_not_enum<int (Class::*)(int) noexcept>();
    test_is_not_enum<int (Class::*)(int)& noexcept>();
    test_is_not_enum<int (Class::*)(int)&& noexcept>();
    test_is_not_enum<int (Class::*)(int) const noexcept>();
    test_is_not_enum<int (Class::*)(int) const& noexcept>();
    test_is_not_enum<int (Class::*)(int) const&& noexcept>();

    test_is_not_enum<int (Class::*)(...)>();
    test_is_not_enum<int (Class::*)(...)&>();
    test_is_not_enum<int (Class::*)(...) &&>();
    test_is_not_enum<int (Class::*)(...) const>();
    test_is_not_enum<int (Class::*)(...) const&>();
    test_is_not_enum<int (Class::*)(...) const&&>();
    test_is_not_enum<int (Class::*)(...) noexcept>();
    test_is_not_enum<int (Class::*)(...)& noexcept>();
    test_is_not_enum<int (Class::*)(...)&& noexcept>();
    test_is_not_enum<int (Class::*)(...) const noexcept>();
    test_is_not_enum<int (Class::*)(...) const& noexcept>();
    test_is_not_enum<int (Class::*)(...) const&& noexcept>();

    test_is_not_enum<int (Class::*)(int, ...)>();
    test_is_not_enum<int (Class::*)(int, ...)&>();
    test_is_not_enum<int (Class::*)(int, ...) &&>();
    test_is_not_enum<int (Class::*)(int, ...) const>();
    test_is_not_enum<int (Class::*)(int, ...) const&>();
    test_is_not_enum<int (Class::*)(int, ...) const&&>();
    test_is_not_enum<int (Class::*)(int, ...) noexcept>();
    test_is_not_enum<int (Class::*)(int, ...)& noexcept>();
    test_is_not_enum<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_enum<int (Class::*)(int, ...) const noexcept>();
    test_is_not_enum<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_enum<int (Class::*)(int, ...) const&& noexcept>();
}
