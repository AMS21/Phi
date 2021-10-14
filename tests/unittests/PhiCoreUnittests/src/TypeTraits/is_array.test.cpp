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
void test_is_array_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
    STATIC_REQUIRE(phi::is_compound<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
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
    STATIC_REQUIRE_FALSE(phi::is_scalar<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
    STATIC_REQUIRE(phi::is_compound_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
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
    STATIC_REQUIRE_FALSE(phi::is_scalar_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);
#endif
}

template <typename T>
void test_is_array()
{
    test_is_array_impl<T>();
    test_is_array_impl<const T>();
    test_is_array_impl<volatile T>();
    test_is_array_impl<const volatile T>();
}

template <typename T>
void test_is_not_array()
{
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<const volatile T>);
#endif
}

using array            = char[3];
using const_array      = const char[3];
using incomplete_array = char[];

TEST_CASE("is_array")
{
    test_is_array<char[3]>();
    test_is_array<char[]>();
    test_is_array<char[][3]>();
    test_is_array<char[3][3]>();
    test_is_array<Union[]>();
    test_is_array<Union[2]>();
    test_is_array<Class[]>();
    test_is_array<Class[3]>();
    test_is_array<array>();
    test_is_array<const_array>();
    test_is_array<incomplete_array>();
    test_is_array<incomplete_type[]>();
    test_is_array<incomplete_type[3]>();
    test_is_array<int[1][2][3][4][5][6][7][8][9][10]>();

    test_is_not_array<void>();
    test_is_not_array<phi::nullptr_t>();
    test_is_not_array<bool>();
    test_is_not_array<char>();
    test_is_not_array<signed char>();
    test_is_not_array<unsigned char>();
    test_is_not_array<short>();
    test_is_not_array<unsigned short>();
    test_is_not_array<int>();
    test_is_not_array<unsigned int>();
    test_is_not_array<long>();
    test_is_not_array<unsigned long>();
    test_is_not_array<long long>();
    test_is_not_array<unsigned long long>();
    test_is_not_array<float>();
    test_is_not_array<double>();
    test_is_not_array<long double>();
    test_is_not_array<char8_t>();
    test_is_not_array<char16_t>();
    test_is_not_array<char32_t>();
    test_is_not_array<wchar_t>();

    test_is_not_array<phi::Boolean>();
    test_is_not_array<phi::Integer<signed char>>();
    test_is_not_array<phi::Integer<unsigned char>>();
    test_is_not_array<phi::Integer<short>>();
    test_is_not_array<phi::Integer<unsigned short>>();
    test_is_not_array<phi::Integer<int>>();
    test_is_not_array<phi::Integer<unsigned int>>();
    test_is_not_array<phi::Integer<long>>();
    test_is_not_array<phi::Integer<unsigned long>>();
    test_is_not_array<phi::Integer<long long>>();
    test_is_not_array<phi::Integer<unsigned long long>>();
    test_is_not_array<phi::FloatingPoint<float>>();
    test_is_not_array<phi::FloatingPoint<double>>();
    test_is_not_array<phi::FloatingPoint<long double>>();

    test_is_not_array<std::vector<int>>();
    test_is_not_array<phi::ScopePtr<int>>();

    test_is_not_array<int&>();
    test_is_not_array<const int&>();
    test_is_not_array<volatile int&>();
    test_is_not_array<const volatile int&>();
    test_is_not_array<int&&>();
    test_is_not_array<const int&&>();
    test_is_not_array<volatile int&&>();
    test_is_not_array<const volatile int&&>();
    test_is_not_array<int*>();
    test_is_not_array<const int*>();
    test_is_not_array<volatile int*>();
    test_is_not_array<const volatile int*>();
    test_is_not_array<int**>();
    test_is_not_array<const int**>();
    test_is_not_array<volatile int**>();
    test_is_not_array<const volatile int**>();
    test_is_not_array<int*&>();
    test_is_not_array<const int*&>();
    test_is_not_array<volatile int*&>();
    test_is_not_array<const volatile int*&>();
    test_is_not_array<int*&&>();
    test_is_not_array<const int*&&>();
    test_is_not_array<volatile int*&&>();
    test_is_not_array<const volatile int*&&>();
    test_is_not_array<void*>();
    test_is_array<char[3]>();
    test_is_array<char[]>();
    test_is_array<char* [3]>();
    test_is_array<char*[]>();
    test_is_not_array<int(*)[3]>();
    test_is_not_array<int(*)[]>();
    test_is_not_array<int(&)[3]>();
    test_is_not_array<int(&)[]>();
    test_is_not_array<int(&&)[3]>();
    test_is_not_array<int(&&)[]>();
    test_is_array<char[3][2]>();
    test_is_array<char[][2]>();
    test_is_array<char* [3][2]>();
    test_is_array<char*[][2]>();
    test_is_not_array<int(*)[3][2]>();
    test_is_not_array<int(*)[][2]>();
    test_is_not_array<int(&)[3][2]>();
    test_is_not_array<int(&)[][2]>();
    test_is_not_array<int(&&)[3][2]>();
    test_is_not_array<int(&&)[][2]>();
    test_is_not_array<Class>();
    test_is_array<Class[]>();
    test_is_array<Class[2]>();
    test_is_not_array<Struct>();
    test_is_not_array<TemplateClass<void>>();
    test_is_not_array<TemplateClass<int>>();
    test_is_not_array<TemplateClass<Class>>();
    test_is_not_array<TemplateClass<incomplete_type>>();
    test_is_not_array<TemplateStruct<void>>();
    test_is_not_array<TemplateStruct<int>>();
    test_is_not_array<TemplateStruct<Class>>();
    test_is_not_array<TemplateStruct<incomplete_type>>();
    test_is_not_array<VariadicTemplateClass<>>();
    test_is_not_array<VariadicTemplateClass<void>>();
    test_is_not_array<VariadicTemplateClass<int>>();
    test_is_not_array<VariadicTemplateClass<Class>>();
    test_is_not_array<VariadicTemplateClass<incomplete_type>>();
    test_is_not_array<VariadicTemplateClass<int, void, Class, volatile char[]>>();
    test_is_not_array<VariadicTemplateStruct<>>();
    test_is_not_array<VariadicTemplateStruct<void>>();
    test_is_not_array<VariadicTemplateStruct<int>>();
    test_is_not_array<VariadicTemplateStruct<Class>>();
    test_is_not_array<VariadicTemplateStruct<incomplete_type>>();
    test_is_not_array<VariadicTemplateStruct<int, void, Class, volatile char[]>>();
    test_is_not_array<PublicDerviedFromTemplate<Base>>();
    test_is_not_array<PublicDerviedFromTemplate<Derived>>();
    test_is_not_array<PublicDerviedFromTemplate<Class>>();
    test_is_not_array<PrivateDerviedFromTemplate<Base>>();
    test_is_not_array<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_array<PrivateDerviedFromTemplate<Class>>();
    test_is_not_array<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_array<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_array<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_array<Union>();
    test_is_not_array<NonEmptyUnion>();
    test_is_not_array<Empty>();
    test_is_not_array<NotEmpty>();
    test_is_not_array<bit_zero>();
    test_is_not_array<bit_one>();
    test_is_not_array<Base>();
    test_is_not_array<Derived>();
    test_is_not_array<Abstract>();
    test_is_not_array<AbstractTemplate<int>>();
    test_is_not_array<AbstractTemplate<double>>();
    test_is_not_array<AbstractTemplate<Class>>();
    test_is_not_array<AbstractTemplate<incomplete_type>>();
    test_is_not_array<Final>();
    test_is_not_array<Enum>();
    test_is_not_array<EnumSigned>();
    test_is_not_array<EnumUnsigned>();
    test_is_not_array<EnumClass>();
    test_is_not_array<EnumStruct>();
    test_is_not_array<Function>();
    test_is_not_array<FunctionPtr>();
    test_is_not_array<MemberObjectPtr>();
    test_is_not_array<MemberFunctionPtr>();
    test_is_not_array<incomplete_type>(); // LWG#2582
    test_is_not_array<IncompleteTemplate<void>>();
    test_is_not_array<IncompleteTemplate<int>>();
    test_is_not_array<IncompleteTemplate<Class>>();
    test_is_not_array<IncompleteTemplate<incomplete_type>>();
    test_is_not_array<IncompleteVariadicTemplate<>>();
    test_is_not_array<IncompleteVariadicTemplate<void>>();
    test_is_not_array<IncompleteVariadicTemplate<int>>();
    test_is_not_array<IncompleteVariadicTemplate<Class>>();
    test_is_not_array<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_array<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_array<int Class::*>();
    test_is_not_array<float Class::*>();
    test_is_not_array<void * Class::*>();
    test_is_not_array<int * Class::*>();
    test_is_not_array<int Class::*&>();
    test_is_not_array<float Class::*&>();
    test_is_not_array<void * Class::*&>();
    test_is_not_array<int * Class::*&>();
    test_is_not_array<int Class::*&&>();
    test_is_not_array<float Class::*&&>();
    test_is_not_array<void * Class::*&&>();
    test_is_not_array<int * Class::*&&>();
    test_is_not_array<int Class::*const>();
    test_is_not_array<float Class::*const>();
    test_is_not_array<void * Class::*const>();
    test_is_not_array<int Class::*const&>();
    test_is_not_array<float Class::*const&>();
    test_is_not_array<void * Class::*const&>();
    test_is_not_array<int Class::*const&&>();
    test_is_not_array<float Class::*const&&>();
    test_is_not_array<void * Class::*const&&>();
    test_is_not_array<int Class::*volatile>();
    test_is_not_array<float Class::*volatile>();
    test_is_not_array<void * Class::*volatile>();
    test_is_not_array<int Class::*volatile&>();
    test_is_not_array<float Class::*volatile&>();
    test_is_not_array<void * Class::*volatile&>();
    test_is_not_array<int Class::*volatile&&>();
    test_is_not_array<float Class::*volatile&&>();
    test_is_not_array<void * Class::*volatile&&>();
    test_is_not_array<int Class::*const volatile>();
    test_is_not_array<float Class::*const volatile>();
    test_is_not_array<void * Class::*const volatile>();
    test_is_not_array<int Class::*const volatile&>();
    test_is_not_array<float Class::*const volatile&>();
    test_is_not_array<void * Class::*const volatile&>();
    test_is_not_array<int Class::*const volatile&&>();
    test_is_not_array<float Class::*const volatile&&>();
    test_is_not_array<void * Class::*const volatile&&>();
    test_is_not_array<NonCopyable>();
    test_is_not_array<NonMoveable>();
    test_is_not_array<NonConstructible>();
    test_is_not_array<Tracked>();
    test_is_not_array<TrapConstructible>();
    test_is_not_array<TrapImplicitConversion>();
    test_is_not_array<TrapComma>();
    test_is_not_array<TrapCall>();
    test_is_not_array<TrapSelfAssign>();

    test_is_not_array<void()>();
    test_is_not_array<void()&>();
    test_is_not_array<void() &&>();
    test_is_not_array<void() const>();
    test_is_not_array<void() const&>();
    test_is_not_array<void() const&&>();
    test_is_not_array<void() noexcept>();
    test_is_not_array<void()& noexcept>();
    test_is_not_array<void()&& noexcept>();
    test_is_not_array<void() const noexcept>();
    test_is_not_array<void() const& noexcept>();
    test_is_not_array<void() const&& noexcept>();

    test_is_not_array<void(int)>();
    test_is_not_array<void(int)&>();
    test_is_not_array<void(int) &&>();
    test_is_not_array<void(int) const>();
    test_is_not_array<void(int) const&>();
    test_is_not_array<void(int) const&&>();
    test_is_not_array<void(int) noexcept>();
    test_is_not_array<void(int)& noexcept>();
    test_is_not_array<void(int)&& noexcept>();
    test_is_not_array<void(int) const noexcept>();
    test_is_not_array<void(int) const& noexcept>();
    test_is_not_array<void(int) const&& noexcept>();

    test_is_not_array<void(...)>();
    test_is_not_array<void(...)&>();
    test_is_not_array<void(...) &&>();
    test_is_not_array<void(...) const>();
    test_is_not_array<void(...) const&>();
    test_is_not_array<void(...) const&&>();
    test_is_not_array<void(...) noexcept>();
    test_is_not_array<void(...)& noexcept>();
    test_is_not_array<void(...)&& noexcept>();
    test_is_not_array<void(...) const noexcept>();
    test_is_not_array<void(...) const& noexcept>();
    test_is_not_array<void(...) const&& noexcept>();

    test_is_not_array<void(int, ...)>();
    test_is_not_array<void(int, ...)&>();
    test_is_not_array<void(int, ...) &&>();
    test_is_not_array<void(int, ...) const>();
    test_is_not_array<void(int, ...) const&>();
    test_is_not_array<void(int, ...) const&&>();
    test_is_not_array<void(int, ...) noexcept>();
    test_is_not_array<void(int, ...)& noexcept>();
    test_is_not_array<void(int, ...)&& noexcept>();
    test_is_not_array<void(int, ...) const noexcept>();
    test_is_not_array<void(int, ...) const& noexcept>();
    test_is_not_array<void(int, ...) const&& noexcept>();

    test_is_not_array<int()>();
    test_is_not_array<int()&>();
    test_is_not_array<int() &&>();
    test_is_not_array<int() const>();
    test_is_not_array<int() const&>();
    test_is_not_array<int() const&&>();
    test_is_not_array<int() noexcept>();
    test_is_not_array<int()& noexcept>();
    test_is_not_array<int()&& noexcept>();
    test_is_not_array<int() const noexcept>();
    test_is_not_array<int() const& noexcept>();
    test_is_not_array<int() const&& noexcept>();

    test_is_not_array<int(int)>();
    test_is_not_array<int(int)&>();
    test_is_not_array<int(int) &&>();
    test_is_not_array<int(int) const>();
    test_is_not_array<int(int) const&>();
    test_is_not_array<int(int) const&&>();
    test_is_not_array<int(int) noexcept>();
    test_is_not_array<int(int)& noexcept>();
    test_is_not_array<int(int)&& noexcept>();
    test_is_not_array<int(int) const noexcept>();
    test_is_not_array<int(int) const& noexcept>();
    test_is_not_array<int(int) const&& noexcept>();

    test_is_not_array<int(...)>();
    test_is_not_array<int(...)&>();
    test_is_not_array<int(...) &&>();
    test_is_not_array<int(...) const>();
    test_is_not_array<int(...) const&>();
    test_is_not_array<int(...) const&&>();
    test_is_not_array<int(...) noexcept>();
    test_is_not_array<int(...)& noexcept>();
    test_is_not_array<int(...)&& noexcept>();
    test_is_not_array<int(...) const noexcept>();
    test_is_not_array<int(...) const& noexcept>();
    test_is_not_array<int(...) const&& noexcept>();

    test_is_not_array<int(int, ...)>();
    test_is_not_array<int(int, ...)&>();
    test_is_not_array<int(int, ...) &&>();
    test_is_not_array<int(int, ...) const>();
    test_is_not_array<int(int, ...) const&>();
    test_is_not_array<int(int, ...) const&&>();
    test_is_not_array<int(int, ...) noexcept>();
    test_is_not_array<int(int, ...)& noexcept>();
    test_is_not_array<int(int, ...)&& noexcept>();
    test_is_not_array<int(int, ...) const noexcept>();
    test_is_not_array<int(int, ...) const& noexcept>();
    test_is_not_array<int(int, ...) const&& noexcept>();

    test_is_not_array<void (*)()>();
    test_is_not_array<void (*)() noexcept>();

    test_is_not_array<void (*)(int)>();
    test_is_not_array<void (*)(int) noexcept>();

    test_is_not_array<void (*)(...)>();
    test_is_not_array<void (*)(...) noexcept>();

    test_is_not_array<void (*)(int, ...)>();
    test_is_not_array<void (*)(int, ...) noexcept>();

    test_is_not_array<int (*)()>();
    test_is_not_array<int (*)() noexcept>();

    test_is_not_array<int (*)(int)>();
    test_is_not_array<int (*)(int) noexcept>();

    test_is_not_array<int (*)(...)>();
    test_is_not_array<int (*)(...) noexcept>();

    test_is_not_array<int (*)(int, ...)>();
    test_is_not_array<int (*)(int, ...) noexcept>();

    test_is_not_array<void (&)()>();
    test_is_not_array<void (&)() noexcept>();

    test_is_not_array<void (&)(int)>();
    test_is_not_array<void (&)(int) noexcept>();

    test_is_not_array<void (&)(...)>();
    test_is_not_array<void (&)(...) noexcept>();

    test_is_not_array<void (&)(int, ...)>();
    test_is_not_array<void (&)(int, ...) noexcept>();

    test_is_not_array<int (&)()>();
    test_is_not_array<int (&)() noexcept>();

    test_is_not_array<int (&)(int)>();
    test_is_not_array<int (&)(int) noexcept>();

    test_is_not_array<int (&)(...)>();
    test_is_not_array<int (&)(...) noexcept>();

    test_is_not_array<int (&)(int, ...)>();
    test_is_not_array<int (&)(int, ...) noexcept>();

    test_is_not_array<void(&&)()>();
    test_is_not_array<void(&&)() noexcept>();

    test_is_not_array<void(&&)(int)>();
    test_is_not_array<void(&&)(int) noexcept>();

    test_is_not_array<void(&&)(...)>();
    test_is_not_array<void(&&)(...) noexcept>();

    test_is_not_array<void(&&)(int, ...)>();
    test_is_not_array<void(&&)(int, ...) noexcept>();

    test_is_not_array<int(&&)()>();
    test_is_not_array<int(&&)() noexcept>();

    test_is_not_array<int(&&)(int)>();
    test_is_not_array<int(&&)(int) noexcept>();

    test_is_not_array<int(&&)(...)>();
    test_is_not_array<int(&&)(...) noexcept>();

    test_is_not_array<int(&&)(int, ...)>();
    test_is_not_array<int(&&)(int, ...) noexcept>();

    test_is_not_array<void (Class::*)()>();
    test_is_not_array<void (Class::*)()&>();
    test_is_not_array<void (Class::*)() &&>();
    test_is_not_array<void (Class::*)() const>();
    test_is_not_array<void (Class::*)() const&>();
    test_is_not_array<void (Class::*)() const&&>();
    test_is_not_array<void (Class::*)() noexcept>();
    test_is_not_array<void (Class::*)()& noexcept>();
    test_is_not_array<void (Class::*)()&& noexcept>();
    test_is_not_array<void (Class::*)() const noexcept>();
    test_is_not_array<void (Class::*)() const& noexcept>();
    test_is_not_array<void (Class::*)() const&& noexcept>();

    test_is_not_array<void (Class::*)(int)>();
    test_is_not_array<void (Class::*)(int)&>();
    test_is_not_array<void (Class::*)(int) &&>();
    test_is_not_array<void (Class::*)(int) const>();
    test_is_not_array<void (Class::*)(int) const&>();
    test_is_not_array<void (Class::*)(int) const&&>();
    test_is_not_array<void (Class::*)(int) noexcept>();
    test_is_not_array<void (Class::*)(int)& noexcept>();
    test_is_not_array<void (Class::*)(int)&& noexcept>();
    test_is_not_array<void (Class::*)(int) const noexcept>();
    test_is_not_array<void (Class::*)(int) const& noexcept>();
    test_is_not_array<void (Class::*)(int) const&& noexcept>();

    test_is_not_array<void (Class::*)(...)>();
    test_is_not_array<void (Class::*)(...)&>();
    test_is_not_array<void (Class::*)(...) &&>();
    test_is_not_array<void (Class::*)(...) const>();
    test_is_not_array<void (Class::*)(...) const&>();
    test_is_not_array<void (Class::*)(...) const&&>();
    test_is_not_array<void (Class::*)(...) noexcept>();
    test_is_not_array<void (Class::*)(...)& noexcept>();
    test_is_not_array<void (Class::*)(...)&& noexcept>();
    test_is_not_array<void (Class::*)(...) const noexcept>();
    test_is_not_array<void (Class::*)(...) const& noexcept>();
    test_is_not_array<void (Class::*)(...) const&& noexcept>();

    test_is_not_array<void (Class::*)(int, ...)>();
    test_is_not_array<void (Class::*)(int, ...)&>();
    test_is_not_array<void (Class::*)(int, ...) &&>();
    test_is_not_array<void (Class::*)(int, ...) const>();
    test_is_not_array<void (Class::*)(int, ...) const&>();
    test_is_not_array<void (Class::*)(int, ...) const&&>();
    test_is_not_array<void (Class::*)(int, ...) noexcept>();
    test_is_not_array<void (Class::*)(int, ...)& noexcept>();
    test_is_not_array<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_array<void (Class::*)(int, ...) const noexcept>();
    test_is_not_array<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_array<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_array<int (Class::*)()>();
    test_is_not_array<int (Class::*)()&>();
    test_is_not_array<int (Class::*)() &&>();
    test_is_not_array<int (Class::*)() const>();
    test_is_not_array<int (Class::*)() const&>();
    test_is_not_array<int (Class::*)() const&&>();
    test_is_not_array<int (Class::*)() noexcept>();
    test_is_not_array<int (Class::*)()& noexcept>();
    test_is_not_array<int (Class::*)()&& noexcept>();
    test_is_not_array<int (Class::*)() const noexcept>();
    test_is_not_array<int (Class::*)() const& noexcept>();
    test_is_not_array<int (Class::*)() const&& noexcept>();

    test_is_not_array<int (Class::*)(int)>();
    test_is_not_array<int (Class::*)(int)&>();
    test_is_not_array<int (Class::*)(int) &&>();
    test_is_not_array<int (Class::*)(int) const>();
    test_is_not_array<int (Class::*)(int) const&>();
    test_is_not_array<int (Class::*)(int) const&&>();
    test_is_not_array<int (Class::*)(int) noexcept>();
    test_is_not_array<int (Class::*)(int)& noexcept>();
    test_is_not_array<int (Class::*)(int)&& noexcept>();
    test_is_not_array<int (Class::*)(int) const noexcept>();
    test_is_not_array<int (Class::*)(int) const& noexcept>();
    test_is_not_array<int (Class::*)(int) const&& noexcept>();

    test_is_not_array<int (Class::*)(...)>();
    test_is_not_array<int (Class::*)(...)&>();
    test_is_not_array<int (Class::*)(...) &&>();
    test_is_not_array<int (Class::*)(...) const>();
    test_is_not_array<int (Class::*)(...) const&>();
    test_is_not_array<int (Class::*)(...) const&&>();
    test_is_not_array<int (Class::*)(...) noexcept>();
    test_is_not_array<int (Class::*)(...)& noexcept>();
    test_is_not_array<int (Class::*)(...)&& noexcept>();
    test_is_not_array<int (Class::*)(...) const noexcept>();
    test_is_not_array<int (Class::*)(...) const& noexcept>();
    test_is_not_array<int (Class::*)(...) const&& noexcept>();

    test_is_not_array<int (Class::*)(int, ...)>();
    test_is_not_array<int (Class::*)(int, ...)&>();
    test_is_not_array<int (Class::*)(int, ...) &&>();
    test_is_not_array<int (Class::*)(int, ...) const>();
    test_is_not_array<int (Class::*)(int, ...) const&>();
    test_is_not_array<int (Class::*)(int, ...) const&&>();
    test_is_not_array<int (Class::*)(int, ...) noexcept>();
    test_is_not_array<int (Class::*)(int, ...)& noexcept>();
    test_is_not_array<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_array<int (Class::*)(int, ...) const noexcept>();
    test_is_not_array<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_array<int (Class::*)(int, ...) const&& noexcept>();
}
