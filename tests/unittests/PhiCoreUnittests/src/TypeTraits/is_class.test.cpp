#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/is_array.hpp>
#include <Phi/TypeTraits/is_class.hpp>
#include <Phi/TypeTraits/is_compound.hpp>
#include <Phi/TypeTraits/is_enum.hpp>
#include <Phi/TypeTraits/is_function.hpp>
#include <Phi/TypeTraits/is_lvalue_reference.hpp>
#include <Phi/TypeTraits/is_member_function_pointer.hpp>
#include <Phi/TypeTraits/is_member_object_pointer.hpp>
#include <Phi/TypeTraits/is_member_pointer.hpp>
#include <Phi/TypeTraits/is_null_pointer.hpp>
#include <Phi/TypeTraits/is_object.hpp>
#include <Phi/TypeTraits/is_pointer.hpp>
#include <Phi/TypeTraits/is_reference.hpp>
#include <Phi/TypeTraits/is_rvalue_reference.hpp>
#include <Phi/TypeTraits/is_union.hpp>
#include <Phi/TypeTraits/is_unsafe_arithmetic.hpp>
#include <Phi/TypeTraits/is_unsafe_bool.hpp>
#include <Phi/TypeTraits/is_unsafe_floating_point.hpp>
#include <Phi/TypeTraits/is_unsafe_fundamental.hpp>
#include <Phi/TypeTraits/is_unsafe_integer.hpp>
#include <Phi/TypeTraits/is_unsafe_integral.hpp>
#include <Phi/TypeTraits/is_unsafe_scalar.hpp>
#include <Phi/TypeTraits/is_void.hpp>
#include <vector>

template <typename T>
void test_is_class_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_bool<T>::value);
    STATIC_REQUIRE(phi::is_class<T>::value);
    STATIC_REQUIRE(phi::is_compound<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_fundamental<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integral<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<T>::value);
    STATIC_REQUIRE(phi::is_object<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_scalar<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_bool_v<T>);
    STATIC_REQUIRE(phi::is_class_v<T>);
    STATIC_REQUIRE(phi::is_compound_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_fundamental_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integral_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<T>);
    STATIC_REQUIRE(phi::is_object_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_scalar_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);
#endif
}

template <typename T>
void test_is_class()
{
    test_is_class_impl<T>();
    test_is_class_impl<const T>();
    test_is_class_impl<volatile T>();
    test_is_class_impl<const volatile T>();
}

template <typename T>
void test_is_not_class()
{
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<const volatile T>);
#endif
}

TEST_CASE("is_class")
{
    test_is_not_class<void>();
    test_is_not_class<phi::nullptr_t>();
    test_is_not_class<bool>();
    test_is_not_class<char>();
    test_is_not_class<signed char>();
    test_is_not_class<unsigned char>();
    test_is_not_class<short>();
    test_is_not_class<unsigned short>();
    test_is_not_class<int>();
    test_is_not_class<unsigned int>();
    test_is_not_class<long>();
    test_is_not_class<unsigned long>();
    test_is_not_class<long long>();
    test_is_not_class<unsigned long long>();
    test_is_not_class<float>();
    test_is_not_class<double>();
    test_is_not_class<long double>();
    test_is_not_class<char8_t>();
    test_is_not_class<char16_t>();
    test_is_not_class<char32_t>();
    test_is_not_class<wchar_t>();

    test_is_class<phi::Boolean>();
    test_is_class<phi::Integer<signed char>>();
    test_is_class<phi::Integer<unsigned char>>();
    test_is_class<phi::Integer<short>>();
    test_is_class<phi::Integer<unsigned short>>();
    test_is_class<phi::Integer<int>>();
    test_is_class<phi::Integer<unsigned int>>();
    test_is_class<phi::Integer<long>>();
    test_is_class<phi::Integer<unsigned long>>();
    test_is_class<phi::Integer<long long>>();
    test_is_class<phi::Integer<unsigned long long>>();
    test_is_class<phi::FloatingPoint<float>>();
    test_is_class<phi::FloatingPoint<double>>();
    test_is_class<phi::FloatingPoint<long double>>();

    test_is_class<std::vector<int>>();
    test_is_class<phi::ScopePtr<int>>();

    test_is_not_class<int&>();
    test_is_not_class<const int&>();
    test_is_not_class<volatile int&>();
    test_is_not_class<const volatile int&>();
    test_is_not_class<int&&>();
    test_is_not_class<const int&&>();
    test_is_not_class<volatile int&&>();
    test_is_not_class<const volatile int&&>();
    test_is_not_class<int*>();
    test_is_not_class<const int*>();
    test_is_not_class<volatile int*>();
    test_is_not_class<const volatile int*>();
    test_is_not_class<int**>();
    test_is_not_class<const int**>();
    test_is_not_class<volatile int**>();
    test_is_not_class<const volatile int**>();
    test_is_not_class<int*&>();
    test_is_not_class<const int*&>();
    test_is_not_class<volatile int*&>();
    test_is_not_class<const volatile int*&>();
    test_is_not_class<int*&&>();
    test_is_not_class<const int*&&>();
    test_is_not_class<volatile int*&&>();
    test_is_not_class<const volatile int*&&>();
    test_is_not_class<void*>();
    test_is_not_class<char[3]>();
    test_is_not_class<char[]>();
    test_is_not_class<char* [3]>();
    test_is_not_class<char*[]>();
    test_is_not_class<int(*)[3]>();
    test_is_not_class<int(*)[]>();
    test_is_not_class<int(&)[3]>();
    test_is_not_class<int(&)[]>();
    test_is_not_class<int(&&)[3]>();
    test_is_not_class<int(&&)[]>();
    test_is_not_class<char[3][2]>();
    test_is_not_class<char[][2]>();
    test_is_not_class<char* [3][2]>();
    test_is_not_class<char*[][2]>();
    test_is_not_class<int(*)[3][2]>();
    test_is_not_class<int(*)[][2]>();
    test_is_not_class<int(&)[3][2]>();
    test_is_not_class<int(&)[][2]>();
    test_is_not_class<int(&&)[3][2]>();
    test_is_not_class<int(&&)[][2]>();
    test_is_class<Class>();
    test_is_not_class<Class[]>();
    test_is_not_class<Class[2]>();
    test_is_class<Struct>();
    test_is_class<TemplateClass<void>>();
    test_is_class<TemplateClass<int>>();
    test_is_class<TemplateClass<Class>>();
    test_is_class<TemplateClass<incomplete_type>>();
    test_is_class<TemplateStruct<void>>();
    test_is_class<TemplateStruct<int>>();
    test_is_class<TemplateStruct<Class>>();
    test_is_class<TemplateStruct<incomplete_type>>();
    test_is_class<VariadicTemplateClass<>>();
    test_is_class<VariadicTemplateClass<void>>();
    test_is_class<VariadicTemplateClass<int>>();
    test_is_class<VariadicTemplateClass<Class>>();
    test_is_class<VariadicTemplateClass<incomplete_type>>();
    test_is_class<VariadicTemplateClass<int, void, Class, volatile char[]>>();
    test_is_class<VariadicTemplateStruct<>>();
    test_is_class<VariadicTemplateStruct<void>>();
    test_is_class<VariadicTemplateStruct<int>>();
    test_is_class<VariadicTemplateStruct<Class>>();
    test_is_class<VariadicTemplateStruct<incomplete_type>>();
    test_is_class<VariadicTemplateStruct<int, void, Class, volatile char[]>>();
    test_is_class<PublicDerviedFromTemplate<Base>>();
    test_is_class<PublicDerviedFromTemplate<Derived>>();
    test_is_class<PublicDerviedFromTemplate<Class>>();
    test_is_class<PrivateDerviedFromTemplate<Base>>();
    test_is_class<PrivateDerviedFromTemplate<Derived>>();
    test_is_class<PrivateDerviedFromTemplate<Class>>();
    test_is_class<ProtectedDerviedFromTemplate<Base>>();
    test_is_class<ProtectedDerviedFromTemplate<Derived>>();
    test_is_class<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_class<Union>();
    test_is_not_class<NonEmptyUnion>();
    test_is_class<Empty>();
    test_is_class<NotEmpty>();
    test_is_class<bit_zero>();
    test_is_class<bit_one>();
    test_is_class<Base>();
    test_is_class<Derived>();
    test_is_class<Abstract>();
    test_is_class<AbstractTemplate<int>>();
    test_is_class<AbstractTemplate<double>>();
    test_is_class<AbstractTemplate<Class>>();
    test_is_class<AbstractTemplate<incomplete_type>>();
    test_is_class<Final>();
    test_is_not_class<Enum>();
    test_is_not_class<EnumSigned>();
    test_is_not_class<EnumUnsigned>();
    test_is_not_class<EnumClass>();
    test_is_not_class<EnumStruct>();
    test_is_not_class<Function>();
    test_is_not_class<FunctionPtr>();
    test_is_not_class<MemberObjectPtr>();
    test_is_not_class<MemberFunctionPtr>();
    test_is_class<incomplete_type>(); // LWG#2582
    test_is_class<IncompleteTemplate<void>>();
    test_is_class<IncompleteTemplate<int>>();
    test_is_class<IncompleteTemplate<Class>>();
    test_is_class<IncompleteTemplate<incomplete_type>>();
    test_is_class<IncompleteVariadicTemplate<>>();
    test_is_class<IncompleteVariadicTemplate<void>>();
    test_is_class<IncompleteVariadicTemplate<int>>();
    test_is_class<IncompleteVariadicTemplate<Class>>();
    test_is_class<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_class<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_class<int Class::*>();
    test_is_not_class<float Class::*>();
    test_is_not_class<void * Class::*>();
    test_is_not_class<int * Class::*>();
    test_is_not_class<int Class::*&>();
    test_is_not_class<float Class::*&>();
    test_is_not_class<void * Class::*&>();
    test_is_not_class<int * Class::*&>();
    test_is_not_class<int Class::*&&>();
    test_is_not_class<float Class::*&&>();
    test_is_not_class<void * Class::*&&>();
    test_is_not_class<int * Class::*&&>();
    test_is_not_class<int Class::*const>();
    test_is_not_class<float Class::*const>();
    test_is_not_class<void * Class::*const>();
    test_is_not_class<int Class::*const&>();
    test_is_not_class<float Class::*const&>();
    test_is_not_class<void * Class::*const&>();
    test_is_not_class<int Class::*const&&>();
    test_is_not_class<float Class::*const&&>();
    test_is_not_class<void * Class::*const&&>();
    test_is_not_class<int Class::*volatile>();
    test_is_not_class<float Class::*volatile>();
    test_is_not_class<void * Class::*volatile>();
    test_is_not_class<int Class::*volatile&>();
    test_is_not_class<float Class::*volatile&>();
    test_is_not_class<void * Class::*volatile&>();
    test_is_not_class<int Class::*volatile&&>();
    test_is_not_class<float Class::*volatile&&>();
    test_is_not_class<void * Class::*volatile&&>();
    test_is_not_class<int Class::*const volatile>();
    test_is_not_class<float Class::*const volatile>();
    test_is_not_class<void * Class::*const volatile>();
    test_is_not_class<int Class::*const volatile&>();
    test_is_not_class<float Class::*const volatile&>();
    test_is_not_class<void * Class::*const volatile&>();
    test_is_not_class<int Class::*const volatile&&>();
    test_is_not_class<float Class::*const volatile&&>();
    test_is_not_class<void * Class::*const volatile&&>();
    test_is_class<NonCopyable>();
    test_is_class<NonMoveable>();
    test_is_class<NonConstructible>();
    test_is_class<Tracked>();
    test_is_class<TrapConstructible>();
    test_is_class<TrapImplicitConversion>();
    test_is_class<TrapComma>();
    test_is_class<TrapCall>();
    test_is_class<TrapSelfAssign>();

    test_is_not_class<void()>();
    test_is_not_class<void()&>();
    test_is_not_class<void() &&>();
    test_is_not_class<void() const>();
    test_is_not_class<void() const&>();
    test_is_not_class<void() const&&>();
    test_is_not_class<void() noexcept>();
    test_is_not_class<void()& noexcept>();
    test_is_not_class<void()&& noexcept>();
    test_is_not_class<void() const noexcept>();
    test_is_not_class<void() const& noexcept>();
    test_is_not_class<void() const&& noexcept>();

    test_is_not_class<void(int)>();
    test_is_not_class<void(int)&>();
    test_is_not_class<void(int) &&>();
    test_is_not_class<void(int) const>();
    test_is_not_class<void(int) const&>();
    test_is_not_class<void(int) const&&>();
    test_is_not_class<void(int) noexcept>();
    test_is_not_class<void(int)& noexcept>();
    test_is_not_class<void(int)&& noexcept>();
    test_is_not_class<void(int) const noexcept>();
    test_is_not_class<void(int) const& noexcept>();
    test_is_not_class<void(int) const&& noexcept>();

    test_is_not_class<void(...)>();
    test_is_not_class<void(...)&>();
    test_is_not_class<void(...) &&>();
    test_is_not_class<void(...) const>();
    test_is_not_class<void(...) const&>();
    test_is_not_class<void(...) const&&>();
    test_is_not_class<void(...) noexcept>();
    test_is_not_class<void(...)& noexcept>();
    test_is_not_class<void(...)&& noexcept>();
    test_is_not_class<void(...) const noexcept>();
    test_is_not_class<void(...) const& noexcept>();
    test_is_not_class<void(...) const&& noexcept>();

    test_is_not_class<void(int, ...)>();
    test_is_not_class<void(int, ...)&>();
    test_is_not_class<void(int, ...) &&>();
    test_is_not_class<void(int, ...) const>();
    test_is_not_class<void(int, ...) const&>();
    test_is_not_class<void(int, ...) const&&>();
    test_is_not_class<void(int, ...) noexcept>();
    test_is_not_class<void(int, ...)& noexcept>();
    test_is_not_class<void(int, ...)&& noexcept>();
    test_is_not_class<void(int, ...) const noexcept>();
    test_is_not_class<void(int, ...) const& noexcept>();
    test_is_not_class<void(int, ...) const&& noexcept>();

    test_is_not_class<int()>();
    test_is_not_class<int()&>();
    test_is_not_class<int() &&>();
    test_is_not_class<int() const>();
    test_is_not_class<int() const&>();
    test_is_not_class<int() const&&>();
    test_is_not_class<int() noexcept>();
    test_is_not_class<int()& noexcept>();
    test_is_not_class<int()&& noexcept>();
    test_is_not_class<int() const noexcept>();
    test_is_not_class<int() const& noexcept>();
    test_is_not_class<int() const&& noexcept>();

    test_is_not_class<int(int)>();
    test_is_not_class<int(int)&>();
    test_is_not_class<int(int) &&>();
    test_is_not_class<int(int) const>();
    test_is_not_class<int(int) const&>();
    test_is_not_class<int(int) const&&>();
    test_is_not_class<int(int) noexcept>();
    test_is_not_class<int(int)& noexcept>();
    test_is_not_class<int(int)&& noexcept>();
    test_is_not_class<int(int) const noexcept>();
    test_is_not_class<int(int) const& noexcept>();
    test_is_not_class<int(int) const&& noexcept>();

    test_is_not_class<int(...)>();
    test_is_not_class<int(...)&>();
    test_is_not_class<int(...) &&>();
    test_is_not_class<int(...) const>();
    test_is_not_class<int(...) const&>();
    test_is_not_class<int(...) const&&>();
    test_is_not_class<int(...) noexcept>();
    test_is_not_class<int(...)& noexcept>();
    test_is_not_class<int(...)&& noexcept>();
    test_is_not_class<int(...) const noexcept>();
    test_is_not_class<int(...) const& noexcept>();
    test_is_not_class<int(...) const&& noexcept>();

    test_is_not_class<int(int, ...)>();
    test_is_not_class<int(int, ...)&>();
    test_is_not_class<int(int, ...) &&>();
    test_is_not_class<int(int, ...) const>();
    test_is_not_class<int(int, ...) const&>();
    test_is_not_class<int(int, ...) const&&>();
    test_is_not_class<int(int, ...) noexcept>();
    test_is_not_class<int(int, ...)& noexcept>();
    test_is_not_class<int(int, ...)&& noexcept>();
    test_is_not_class<int(int, ...) const noexcept>();
    test_is_not_class<int(int, ...) const& noexcept>();
    test_is_not_class<int(int, ...) const&& noexcept>();

    test_is_not_class<void (*)()>();
    test_is_not_class<void (*)() noexcept>();

    test_is_not_class<void (*)(int)>();
    test_is_not_class<void (*)(int) noexcept>();

    test_is_not_class<void (*)(...)>();
    test_is_not_class<void (*)(...) noexcept>();

    test_is_not_class<void (*)(int, ...)>();
    test_is_not_class<void (*)(int, ...) noexcept>();

    test_is_not_class<int (*)()>();
    test_is_not_class<int (*)() noexcept>();

    test_is_not_class<int (*)(int)>();
    test_is_not_class<int (*)(int) noexcept>();

    test_is_not_class<int (*)(...)>();
    test_is_not_class<int (*)(...) noexcept>();

    test_is_not_class<int (*)(int, ...)>();
    test_is_not_class<int (*)(int, ...) noexcept>();

    test_is_not_class<void (&)()>();
    test_is_not_class<void (&)() noexcept>();

    test_is_not_class<void (&)(int)>();
    test_is_not_class<void (&)(int) noexcept>();

    test_is_not_class<void (&)(...)>();
    test_is_not_class<void (&)(...) noexcept>();

    test_is_not_class<void (&)(int, ...)>();
    test_is_not_class<void (&)(int, ...) noexcept>();

    test_is_not_class<int (&)()>();
    test_is_not_class<int (&)() noexcept>();

    test_is_not_class<int (&)(int)>();
    test_is_not_class<int (&)(int) noexcept>();

    test_is_not_class<int (&)(...)>();
    test_is_not_class<int (&)(...) noexcept>();

    test_is_not_class<int (&)(int, ...)>();
    test_is_not_class<int (&)(int, ...) noexcept>();

    test_is_not_class<void(&&)()>();
    test_is_not_class<void(&&)() noexcept>();

    test_is_not_class<void(&&)(int)>();
    test_is_not_class<void(&&)(int) noexcept>();

    test_is_not_class<void(&&)(...)>();
    test_is_not_class<void(&&)(...) noexcept>();

    test_is_not_class<void(&&)(int, ...)>();
    test_is_not_class<void(&&)(int, ...) noexcept>();

    test_is_not_class<int(&&)()>();
    test_is_not_class<int(&&)() noexcept>();

    test_is_not_class<int(&&)(int)>();
    test_is_not_class<int(&&)(int) noexcept>();

    test_is_not_class<int(&&)(...)>();
    test_is_not_class<int(&&)(...) noexcept>();

    test_is_not_class<int(&&)(int, ...)>();
    test_is_not_class<int(&&)(int, ...) noexcept>();

    test_is_not_class<void (Class::*)()>();
    test_is_not_class<void (Class::*)()&>();
    test_is_not_class<void (Class::*)() &&>();
    test_is_not_class<void (Class::*)() const>();
    test_is_not_class<void (Class::*)() const&>();
    test_is_not_class<void (Class::*)() const&&>();
    test_is_not_class<void (Class::*)() noexcept>();
    test_is_not_class<void (Class::*)()& noexcept>();
    test_is_not_class<void (Class::*)()&& noexcept>();
    test_is_not_class<void (Class::*)() const noexcept>();
    test_is_not_class<void (Class::*)() const& noexcept>();
    test_is_not_class<void (Class::*)() const&& noexcept>();

    test_is_not_class<void (Class::*)(int)>();
    test_is_not_class<void (Class::*)(int)&>();
    test_is_not_class<void (Class::*)(int) &&>();
    test_is_not_class<void (Class::*)(int) const>();
    test_is_not_class<void (Class::*)(int) const&>();
    test_is_not_class<void (Class::*)(int) const&&>();
    test_is_not_class<void (Class::*)(int) noexcept>();
    test_is_not_class<void (Class::*)(int)& noexcept>();
    test_is_not_class<void (Class::*)(int)&& noexcept>();
    test_is_not_class<void (Class::*)(int) const noexcept>();
    test_is_not_class<void (Class::*)(int) const& noexcept>();
    test_is_not_class<void (Class::*)(int) const&& noexcept>();

    test_is_not_class<void (Class::*)(...)>();
    test_is_not_class<void (Class::*)(...)&>();
    test_is_not_class<void (Class::*)(...) &&>();
    test_is_not_class<void (Class::*)(...) const>();
    test_is_not_class<void (Class::*)(...) const&>();
    test_is_not_class<void (Class::*)(...) const&&>();
    test_is_not_class<void (Class::*)(...) noexcept>();
    test_is_not_class<void (Class::*)(...)& noexcept>();
    test_is_not_class<void (Class::*)(...)&& noexcept>();
    test_is_not_class<void (Class::*)(...) const noexcept>();
    test_is_not_class<void (Class::*)(...) const& noexcept>();
    test_is_not_class<void (Class::*)(...) const&& noexcept>();

    test_is_not_class<void (Class::*)(int, ...)>();
    test_is_not_class<void (Class::*)(int, ...)&>();
    test_is_not_class<void (Class::*)(int, ...) &&>();
    test_is_not_class<void (Class::*)(int, ...) const>();
    test_is_not_class<void (Class::*)(int, ...) const&>();
    test_is_not_class<void (Class::*)(int, ...) const&&>();
    test_is_not_class<void (Class::*)(int, ...) noexcept>();
    test_is_not_class<void (Class::*)(int, ...)& noexcept>();
    test_is_not_class<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_class<void (Class::*)(int, ...) const noexcept>();
    test_is_not_class<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_class<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_class<int (Class::*)()>();
    test_is_not_class<int (Class::*)()&>();
    test_is_not_class<int (Class::*)() &&>();
    test_is_not_class<int (Class::*)() const>();
    test_is_not_class<int (Class::*)() const&>();
    test_is_not_class<int (Class::*)() const&&>();
    test_is_not_class<int (Class::*)() noexcept>();
    test_is_not_class<int (Class::*)()& noexcept>();
    test_is_not_class<int (Class::*)()&& noexcept>();
    test_is_not_class<int (Class::*)() const noexcept>();
    test_is_not_class<int (Class::*)() const& noexcept>();
    test_is_not_class<int (Class::*)() const&& noexcept>();

    test_is_not_class<int (Class::*)(int)>();
    test_is_not_class<int (Class::*)(int)&>();
    test_is_not_class<int (Class::*)(int) &&>();
    test_is_not_class<int (Class::*)(int) const>();
    test_is_not_class<int (Class::*)(int) const&>();
    test_is_not_class<int (Class::*)(int) const&&>();
    test_is_not_class<int (Class::*)(int) noexcept>();
    test_is_not_class<int (Class::*)(int)& noexcept>();
    test_is_not_class<int (Class::*)(int)&& noexcept>();
    test_is_not_class<int (Class::*)(int) const noexcept>();
    test_is_not_class<int (Class::*)(int) const& noexcept>();
    test_is_not_class<int (Class::*)(int) const&& noexcept>();

    test_is_not_class<int (Class::*)(...)>();
    test_is_not_class<int (Class::*)(...)&>();
    test_is_not_class<int (Class::*)(...) &&>();
    test_is_not_class<int (Class::*)(...) const>();
    test_is_not_class<int (Class::*)(...) const&>();
    test_is_not_class<int (Class::*)(...) const&&>();
    test_is_not_class<int (Class::*)(...) noexcept>();
    test_is_not_class<int (Class::*)(...)& noexcept>();
    test_is_not_class<int (Class::*)(...)&& noexcept>();
    test_is_not_class<int (Class::*)(...) const noexcept>();
    test_is_not_class<int (Class::*)(...) const& noexcept>();
    test_is_not_class<int (Class::*)(...) const&& noexcept>();

    test_is_not_class<int (Class::*)(int, ...)>();
    test_is_not_class<int (Class::*)(int, ...)&>();
    test_is_not_class<int (Class::*)(int, ...) &&>();
    test_is_not_class<int (Class::*)(int, ...) const>();
    test_is_not_class<int (Class::*)(int, ...) const&>();
    test_is_not_class<int (Class::*)(int, ...) const&&>();
    test_is_not_class<int (Class::*)(int, ...) noexcept>();
    test_is_not_class<int (Class::*)(int, ...)& noexcept>();
    test_is_not_class<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_class<int (Class::*)(int, ...) const noexcept>();
    test_is_not_class<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_class<int (Class::*)(int, ...) const&& noexcept>();
}
