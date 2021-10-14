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
#include <Phi/TypeTraits/is_unsafe_floating_point.hpp>
#include <Phi/TypeTraits/is_void.hpp>
#include <vector>

template <typename T>
void test_is_unsafe_floating_point_impl()
{
    STATIC_REQUIRE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_compound<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
    STATIC_REQUIRE(phi::is_unsafe_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE(phi::is_fundamental<T>::value);
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
    STATIC_REQUIRE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_compound_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
    STATIC_REQUIRE(phi::is_unsafe_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE(phi::is_fundamental_v<T>);
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
void test_is_unsafe_floating_point()
{
    test_is_unsafe_floating_point_impl<T>();
    test_is_unsafe_floating_point_impl<const T>();
    test_is_unsafe_floating_point_impl<volatile T>();
    test_is_unsafe_floating_point_impl<const volatile T>();
}

template <typename T>
void test_is_not_unsafe_floating_point()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point_v<const volatile T>);
#endif
}

TEST_CASE("is_unsafe_floating_point")
{
    test_is_not_unsafe_floating_point<void>();
    test_is_not_unsafe_floating_point<phi::nullptr_t>();
    test_is_not_unsafe_floating_point<bool>();
    test_is_not_unsafe_floating_point<char>();
    test_is_not_unsafe_floating_point<signed char>();
    test_is_not_unsafe_floating_point<unsigned char>();
    test_is_not_unsafe_floating_point<short>();
    test_is_not_unsafe_floating_point<unsigned short>();
    test_is_not_unsafe_floating_point<int>();
    test_is_not_unsafe_floating_point<unsigned int>();
    test_is_not_unsafe_floating_point<long>();
    test_is_not_unsafe_floating_point<unsigned long>();
    test_is_not_unsafe_floating_point<long long>();
    test_is_not_unsafe_floating_point<unsigned long long>();
    test_is_unsafe_floating_point<float>();
    test_is_unsafe_floating_point<double>();
    test_is_unsafe_floating_point<long double>();
    test_is_not_unsafe_floating_point<char8_t>();
    test_is_not_unsafe_floating_point<char16_t>();
    test_is_not_unsafe_floating_point<char32_t>();
    test_is_not_unsafe_floating_point<wchar_t>();

    test_is_not_unsafe_floating_point<phi::Boolean>();
    test_is_not_unsafe_floating_point<phi::Integer<signed char>>();
    test_is_not_unsafe_floating_point<phi::Integer<unsigned char>>();
    test_is_not_unsafe_floating_point<phi::Integer<short>>();
    test_is_not_unsafe_floating_point<phi::Integer<unsigned short>>();
    test_is_not_unsafe_floating_point<phi::Integer<int>>();
    test_is_not_unsafe_floating_point<phi::Integer<unsigned int>>();
    test_is_not_unsafe_floating_point<phi::Integer<long>>();
    test_is_not_unsafe_floating_point<phi::Integer<unsigned long>>();
    test_is_not_unsafe_floating_point<phi::Integer<long long>>();
    test_is_not_unsafe_floating_point<phi::Integer<unsigned long long>>();
    test_is_not_unsafe_floating_point<phi::FloatingPoint<float>>();
    test_is_not_unsafe_floating_point<phi::FloatingPoint<double>>();
    test_is_not_unsafe_floating_point<phi::FloatingPoint<long double>>();

    test_is_not_unsafe_floating_point<std::vector<int>>();
    test_is_not_unsafe_floating_point<phi::ScopePtr<int>>();

    test_is_not_unsafe_floating_point<int&>();
    test_is_not_unsafe_floating_point<const int&>();
    test_is_not_unsafe_floating_point<volatile int&>();
    test_is_not_unsafe_floating_point<const volatile int&>();
    test_is_not_unsafe_floating_point<int&&>();
    test_is_not_unsafe_floating_point<const int&&>();
    test_is_not_unsafe_floating_point<volatile int&&>();
    test_is_not_unsafe_floating_point<const volatile int&&>();
    test_is_not_unsafe_floating_point<int*>();
    test_is_not_unsafe_floating_point<const int*>();
    test_is_not_unsafe_floating_point<volatile int*>();
    test_is_not_unsafe_floating_point<const volatile int*>();
    test_is_not_unsafe_floating_point<int**>();
    test_is_not_unsafe_floating_point<const int**>();
    test_is_not_unsafe_floating_point<volatile int**>();
    test_is_not_unsafe_floating_point<const volatile int**>();
    test_is_not_unsafe_floating_point<int*&>();
    test_is_not_unsafe_floating_point<const int*&>();
    test_is_not_unsafe_floating_point<volatile int*&>();
    test_is_not_unsafe_floating_point<const volatile int*&>();
    test_is_not_unsafe_floating_point<int*&&>();
    test_is_not_unsafe_floating_point<const int*&&>();
    test_is_not_unsafe_floating_point<volatile int*&&>();
    test_is_not_unsafe_floating_point<const volatile int*&&>();
    test_is_not_unsafe_floating_point<void*>();
    test_is_not_unsafe_floating_point<char[3]>();
    test_is_not_unsafe_floating_point<char[]>();
    test_is_not_unsafe_floating_point<char* [3]>();
    test_is_not_unsafe_floating_point<char*[]>();
    test_is_not_unsafe_floating_point<int(*)[3]>();
    test_is_not_unsafe_floating_point<int(*)[]>();
    test_is_not_unsafe_floating_point<int(&)[3]>();
    test_is_not_unsafe_floating_point<int(&)[]>();
    test_is_not_unsafe_floating_point<int(&&)[3]>();
    test_is_not_unsafe_floating_point<int(&&)[]>();
    test_is_not_unsafe_floating_point<char[3][2]>();
    test_is_not_unsafe_floating_point<char[][2]>();
    test_is_not_unsafe_floating_point<char* [3][2]>();
    test_is_not_unsafe_floating_point<char*[][2]>();
    test_is_not_unsafe_floating_point<int(*)[3][2]>();
    test_is_not_unsafe_floating_point<int(*)[][2]>();
    test_is_not_unsafe_floating_point<int(&)[3][2]>();
    test_is_not_unsafe_floating_point<int(&)[][2]>();
    test_is_not_unsafe_floating_point<int(&&)[3][2]>();
    test_is_not_unsafe_floating_point<int(&&)[][2]>();
    test_is_not_unsafe_floating_point<Class>();
    test_is_not_unsafe_floating_point<Class[]>();
    test_is_not_unsafe_floating_point<Class[2]>();
    test_is_not_unsafe_floating_point<Struct>();
    test_is_not_unsafe_floating_point<TemplateClass<void>>();
    test_is_not_unsafe_floating_point<TemplateClass<int>>();
    test_is_not_unsafe_floating_point<TemplateClass<Class>>();
    test_is_not_unsafe_floating_point<TemplateClass<incomplete_type>>();
    test_is_not_unsafe_floating_point<TemplateStruct<void>>();
    test_is_not_unsafe_floating_point<TemplateStruct<int>>();
    test_is_not_unsafe_floating_point<TemplateStruct<Class>>();
    test_is_not_unsafe_floating_point<TemplateStruct<incomplete_type>>();
    test_is_not_unsafe_floating_point<VariadicTemplateClass<>>();
    test_is_not_unsafe_floating_point<VariadicTemplateClass<void>>();
    test_is_not_unsafe_floating_point<VariadicTemplateClass<int>>();
    test_is_not_unsafe_floating_point<VariadicTemplateClass<Class>>();
    test_is_not_unsafe_floating_point<VariadicTemplateClass<incomplete_type>>();
    test_is_not_unsafe_floating_point<VariadicTemplateClass<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_floating_point<VariadicTemplateStruct<>>();
    test_is_not_unsafe_floating_point<VariadicTemplateStruct<void>>();
    test_is_not_unsafe_floating_point<VariadicTemplateStruct<int>>();
    test_is_not_unsafe_floating_point<VariadicTemplateStruct<Class>>();
    test_is_not_unsafe_floating_point<VariadicTemplateStruct<incomplete_type>>();
    test_is_not_unsafe_floating_point<VariadicTemplateStruct<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_floating_point<PublicDerviedFromTemplate<Base>>();
    test_is_not_unsafe_floating_point<PublicDerviedFromTemplate<Derived>>();
    test_is_not_unsafe_floating_point<PublicDerviedFromTemplate<Class>>();
    test_is_not_unsafe_floating_point<PrivateDerviedFromTemplate<Base>>();
    test_is_not_unsafe_floating_point<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_unsafe_floating_point<PrivateDerviedFromTemplate<Class>>();
    test_is_not_unsafe_floating_point<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_unsafe_floating_point<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_unsafe_floating_point<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_unsafe_floating_point<Union>();
    test_is_not_unsafe_floating_point<NonEmptyUnion>();
    test_is_not_unsafe_floating_point<Empty>();
    test_is_not_unsafe_floating_point<NotEmpty>();
    test_is_not_unsafe_floating_point<bit_zero>();
    test_is_not_unsafe_floating_point<bit_one>();
    test_is_not_unsafe_floating_point<Base>();
    test_is_not_unsafe_floating_point<Derived>();
    test_is_not_unsafe_floating_point<Abstract>();
    test_is_not_unsafe_floating_point<AbstractTemplate<int>>();
    test_is_not_unsafe_floating_point<AbstractTemplate<double>>();
    test_is_not_unsafe_floating_point<AbstractTemplate<Class>>();
    test_is_not_unsafe_floating_point<AbstractTemplate<incomplete_type>>();
    test_is_not_unsafe_floating_point<Final>();
    test_is_not_unsafe_floating_point<Enum>();
    test_is_not_unsafe_floating_point<EnumSigned>();
    test_is_not_unsafe_floating_point<EnumUnsigned>();
    test_is_not_unsafe_floating_point<EnumClass>();
    test_is_not_unsafe_floating_point<EnumStruct>();
    test_is_not_unsafe_floating_point<Function>();
    test_is_not_unsafe_floating_point<FunctionPtr>();
    test_is_not_unsafe_floating_point<MemberObjectPtr>();
    test_is_not_unsafe_floating_point<MemberFunctionPtr>();
    test_is_not_unsafe_floating_point<incomplete_type>();
    test_is_not_unsafe_floating_point<IncompleteTemplate<void>>();
    test_is_not_unsafe_floating_point<IncompleteTemplate<int>>();
    test_is_not_unsafe_floating_point<IncompleteTemplate<Class>>();
    test_is_not_unsafe_floating_point<IncompleteTemplate<incomplete_type>>();
    test_is_not_unsafe_floating_point<IncompleteVariadicTemplate<>>();
    test_is_not_unsafe_floating_point<IncompleteVariadicTemplate<void>>();
    test_is_not_unsafe_floating_point<IncompleteVariadicTemplate<int>>();
    test_is_not_unsafe_floating_point<IncompleteVariadicTemplate<Class>>();
    test_is_not_unsafe_floating_point<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_unsafe_floating_point<
            IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_unsafe_floating_point<int Class::*>();
    test_is_not_unsafe_floating_point<float Class::*>();
    test_is_not_unsafe_floating_point<void * Class::*>();
    test_is_not_unsafe_floating_point<int * Class::*>();
    test_is_not_unsafe_floating_point<int Class::*&>();
    test_is_not_unsafe_floating_point<float Class::*&>();
    test_is_not_unsafe_floating_point<void * Class::*&>();
    test_is_not_unsafe_floating_point<int * Class::*&>();
    test_is_not_unsafe_floating_point<int Class::*&&>();
    test_is_not_unsafe_floating_point<float Class::*&&>();
    test_is_not_unsafe_floating_point<void * Class::*&&>();
    test_is_not_unsafe_floating_point<int * Class::*&&>();
    test_is_not_unsafe_floating_point<int Class::*const>();
    test_is_not_unsafe_floating_point<float Class::*const>();
    test_is_not_unsafe_floating_point<void * Class::*const>();
    test_is_not_unsafe_floating_point<int Class::*const&>();
    test_is_not_unsafe_floating_point<float Class::*const&>();
    test_is_not_unsafe_floating_point<void * Class::*const&>();
    test_is_not_unsafe_floating_point<int Class::*const&&>();
    test_is_not_unsafe_floating_point<float Class::*const&&>();
    test_is_not_unsafe_floating_point<void * Class::*const&&>();
    test_is_not_unsafe_floating_point<int Class::*volatile>();
    test_is_not_unsafe_floating_point<float Class::*volatile>();
    test_is_not_unsafe_floating_point<void * Class::*volatile>();
    test_is_not_unsafe_floating_point<int Class::*volatile&>();
    test_is_not_unsafe_floating_point<float Class::*volatile&>();
    test_is_not_unsafe_floating_point<void * Class::*volatile&>();
    test_is_not_unsafe_floating_point<int Class::*volatile&&>();
    test_is_not_unsafe_floating_point<float Class::*volatile&&>();
    test_is_not_unsafe_floating_point<void * Class::*volatile&&>();
    test_is_not_unsafe_floating_point<int Class::*const volatile>();
    test_is_not_unsafe_floating_point<float Class::*const volatile>();
    test_is_not_unsafe_floating_point<void * Class::*const volatile>();
    test_is_not_unsafe_floating_point<int Class::*const volatile&>();
    test_is_not_unsafe_floating_point<float Class::*const volatile&>();
    test_is_not_unsafe_floating_point<void * Class::*const volatile&>();
    test_is_not_unsafe_floating_point<int Class::*const volatile&&>();
    test_is_not_unsafe_floating_point<float Class::*const volatile&&>();
    test_is_not_unsafe_floating_point<void * Class::*const volatile&&>();
    test_is_not_unsafe_floating_point<NonCopyable>();
    test_is_not_unsafe_floating_point<NonMoveable>();
    test_is_not_unsafe_floating_point<NonConstructible>();
    test_is_not_unsafe_floating_point<Tracked>();
    test_is_not_unsafe_floating_point<TrapConstructible>();
    test_is_not_unsafe_floating_point<TrapImplicitConversion>();
    test_is_not_unsafe_floating_point<TrapComma>();
    test_is_not_unsafe_floating_point<TrapCall>();
    test_is_not_unsafe_floating_point<TrapSelfAssign>();

    test_is_not_unsafe_floating_point<void()>();
    test_is_not_unsafe_floating_point<void()&>();
    test_is_not_unsafe_floating_point<void() &&>();
    test_is_not_unsafe_floating_point<void() const>();
    test_is_not_unsafe_floating_point<void() const&>();
    test_is_not_unsafe_floating_point<void() const&&>();
    test_is_not_unsafe_floating_point<void() noexcept>();
    test_is_not_unsafe_floating_point<void()& noexcept>();
    test_is_not_unsafe_floating_point<void()&& noexcept>();
    test_is_not_unsafe_floating_point<void() const noexcept>();
    test_is_not_unsafe_floating_point<void() const& noexcept>();
    test_is_not_unsafe_floating_point<void() const&& noexcept>();

    test_is_not_unsafe_floating_point<void(int)>();
    test_is_not_unsafe_floating_point<void(int)&>();
    test_is_not_unsafe_floating_point<void(int) &&>();
    test_is_not_unsafe_floating_point<void(int) const>();
    test_is_not_unsafe_floating_point<void(int) const&>();
    test_is_not_unsafe_floating_point<void(int) const&&>();
    test_is_not_unsafe_floating_point<void(int) noexcept>();
    test_is_not_unsafe_floating_point<void(int)& noexcept>();
    test_is_not_unsafe_floating_point<void(int)&& noexcept>();
    test_is_not_unsafe_floating_point<void(int) const noexcept>();
    test_is_not_unsafe_floating_point<void(int) const& noexcept>();
    test_is_not_unsafe_floating_point<void(int) const&& noexcept>();

    test_is_not_unsafe_floating_point<void(...)>();
    test_is_not_unsafe_floating_point<void(...)&>();
    test_is_not_unsafe_floating_point<void(...) &&>();
    test_is_not_unsafe_floating_point<void(...) const>();
    test_is_not_unsafe_floating_point<void(...) const&>();
    test_is_not_unsafe_floating_point<void(...) const&&>();
    test_is_not_unsafe_floating_point<void(...) noexcept>();
    test_is_not_unsafe_floating_point<void(...)& noexcept>();
    test_is_not_unsafe_floating_point<void(...)&& noexcept>();
    test_is_not_unsafe_floating_point<void(...) const noexcept>();
    test_is_not_unsafe_floating_point<void(...) const& noexcept>();
    test_is_not_unsafe_floating_point<void(...) const&& noexcept>();

    test_is_not_unsafe_floating_point<void(int, ...)>();
    test_is_not_unsafe_floating_point<void(int, ...)&>();
    test_is_not_unsafe_floating_point<void(int, ...) &&>();
    test_is_not_unsafe_floating_point<void(int, ...) const>();
    test_is_not_unsafe_floating_point<void(int, ...) const&>();
    test_is_not_unsafe_floating_point<void(int, ...) const&&>();
    test_is_not_unsafe_floating_point<void(int, ...) noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...)& noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...)&& noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) const noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) const& noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) const&& noexcept>();

    test_is_not_unsafe_floating_point<int()>();
    test_is_not_unsafe_floating_point<int()&>();
    test_is_not_unsafe_floating_point<int() &&>();
    test_is_not_unsafe_floating_point<int() const>();
    test_is_not_unsafe_floating_point<int() const&>();
    test_is_not_unsafe_floating_point<int() const&&>();
    test_is_not_unsafe_floating_point<int() noexcept>();
    test_is_not_unsafe_floating_point<int()& noexcept>();
    test_is_not_unsafe_floating_point<int()&& noexcept>();
    test_is_not_unsafe_floating_point<int() const noexcept>();
    test_is_not_unsafe_floating_point<int() const& noexcept>();
    test_is_not_unsafe_floating_point<int() const&& noexcept>();

    test_is_not_unsafe_floating_point<int(int)>();
    test_is_not_unsafe_floating_point<int(int)&>();
    test_is_not_unsafe_floating_point<int(int) &&>();
    test_is_not_unsafe_floating_point<int(int) const>();
    test_is_not_unsafe_floating_point<int(int) const&>();
    test_is_not_unsafe_floating_point<int(int) const&&>();
    test_is_not_unsafe_floating_point<int(int) noexcept>();
    test_is_not_unsafe_floating_point<int(int)& noexcept>();
    test_is_not_unsafe_floating_point<int(int)&& noexcept>();
    test_is_not_unsafe_floating_point<int(int) const noexcept>();
    test_is_not_unsafe_floating_point<int(int) const& noexcept>();
    test_is_not_unsafe_floating_point<int(int) const&& noexcept>();

    test_is_not_unsafe_floating_point<int(...)>();
    test_is_not_unsafe_floating_point<int(...)&>();
    test_is_not_unsafe_floating_point<int(...) &&>();
    test_is_not_unsafe_floating_point<int(...) const>();
    test_is_not_unsafe_floating_point<int(...) const&>();
    test_is_not_unsafe_floating_point<int(...) const&&>();
    test_is_not_unsafe_floating_point<int(...) noexcept>();
    test_is_not_unsafe_floating_point<int(...)& noexcept>();
    test_is_not_unsafe_floating_point<int(...)&& noexcept>();
    test_is_not_unsafe_floating_point<int(...) const noexcept>();
    test_is_not_unsafe_floating_point<int(...) const& noexcept>();
    test_is_not_unsafe_floating_point<int(...) const&& noexcept>();

    test_is_not_unsafe_floating_point<int(int, ...)>();
    test_is_not_unsafe_floating_point<int(int, ...)&>();
    test_is_not_unsafe_floating_point<int(int, ...) &&>();
    test_is_not_unsafe_floating_point<int(int, ...) const>();
    test_is_not_unsafe_floating_point<int(int, ...) const&>();
    test_is_not_unsafe_floating_point<int(int, ...) const&&>();
    test_is_not_unsafe_floating_point<int(int, ...) noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...)& noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...)&& noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) const noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) const& noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) const&& noexcept>();

    test_is_not_unsafe_floating_point<void (*)()>();
    test_is_not_unsafe_floating_point<void (*)() noexcept>();

    test_is_not_unsafe_floating_point<void (*)(int)>();
    test_is_not_unsafe_floating_point<void (*)(int) noexcept>();

    test_is_not_unsafe_floating_point<void (*)(...)>();
    test_is_not_unsafe_floating_point<void (*)(...) noexcept>();

    test_is_not_unsafe_floating_point<void (*)(int, ...)>();
    test_is_not_unsafe_floating_point<void (*)(int, ...) noexcept>();

    test_is_not_unsafe_floating_point<int (*)()>();
    test_is_not_unsafe_floating_point<int (*)() noexcept>();

    test_is_not_unsafe_floating_point<int (*)(int)>();
    test_is_not_unsafe_floating_point<int (*)(int) noexcept>();

    test_is_not_unsafe_floating_point<int (*)(...)>();
    test_is_not_unsafe_floating_point<int (*)(...) noexcept>();

    test_is_not_unsafe_floating_point<int (*)(int, ...)>();
    test_is_not_unsafe_floating_point<int (*)(int, ...) noexcept>();

    test_is_not_unsafe_floating_point<void (&)()>();
    test_is_not_unsafe_floating_point<void (&)() noexcept>();

    test_is_not_unsafe_floating_point<void (&)(int)>();
    test_is_not_unsafe_floating_point<void (&)(int) noexcept>();

    test_is_not_unsafe_floating_point<void (&)(...)>();
    test_is_not_unsafe_floating_point<void (&)(...) noexcept>();

    test_is_not_unsafe_floating_point<void (&)(int, ...)>();
    test_is_not_unsafe_floating_point<void (&)(int, ...) noexcept>();

    test_is_not_unsafe_floating_point<int (&)()>();
    test_is_not_unsafe_floating_point<int (&)() noexcept>();

    test_is_not_unsafe_floating_point<int (&)(int)>();
    test_is_not_unsafe_floating_point<int (&)(int) noexcept>();

    test_is_not_unsafe_floating_point<int (&)(...)>();
    test_is_not_unsafe_floating_point<int (&)(...) noexcept>();

    test_is_not_unsafe_floating_point<int (&)(int, ...)>();
    test_is_not_unsafe_floating_point<int (&)(int, ...) noexcept>();

    test_is_not_unsafe_floating_point<void(&&)()>();
    test_is_not_unsafe_floating_point<void(&&)() noexcept>();

    test_is_not_unsafe_floating_point<void(&&)(int)>();
    test_is_not_unsafe_floating_point<void(&&)(int) noexcept>();

    test_is_not_unsafe_floating_point<void(&&)(...)>();
    test_is_not_unsafe_floating_point<void(&&)(...) noexcept>();

    test_is_not_unsafe_floating_point<void(&&)(int, ...)>();
    test_is_not_unsafe_floating_point<void(&&)(int, ...) noexcept>();

    test_is_not_unsafe_floating_point<int(&&)()>();
    test_is_not_unsafe_floating_point<int(&&)() noexcept>();

    test_is_not_unsafe_floating_point<int(&&)(int)>();
    test_is_not_unsafe_floating_point<int(&&)(int) noexcept>();

    test_is_not_unsafe_floating_point<int(&&)(...)>();
    test_is_not_unsafe_floating_point<int(&&)(...) noexcept>();

    test_is_not_unsafe_floating_point<int(&&)(int, ...)>();
    test_is_not_unsafe_floating_point<int(&&)(int, ...) noexcept>();

    test_is_not_unsafe_floating_point<void (Class::*)()>();
    test_is_not_unsafe_floating_point<void (Class::*)()&>();
    test_is_not_unsafe_floating_point<void (Class::*)() &&>();
    test_is_not_unsafe_floating_point<void (Class::*)() const>();
    test_is_not_unsafe_floating_point<void (Class::*)() const&>();
    test_is_not_unsafe_floating_point<void (Class::*)() const&&>();
    test_is_not_unsafe_floating_point<void (Class::*)() noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)()& noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)()&& noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)() const noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)() const& noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)() const&& noexcept>();

    test_is_not_unsafe_floating_point<void (Class::*)(int)>();
    test_is_not_unsafe_floating_point<void (Class::*)(int)&>();
    test_is_not_unsafe_floating_point<void (Class::*)(int) &&>();
    test_is_not_unsafe_floating_point<void (Class::*)(int) const>();
    test_is_not_unsafe_floating_point<void (Class::*)(int) const&>();
    test_is_not_unsafe_floating_point<void (Class::*)(int) const&&>();
    test_is_not_unsafe_floating_point<void (Class::*)(int) noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(int)& noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(int) const noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_floating_point<void (Class::*)(...)>();
    test_is_not_unsafe_floating_point<void (Class::*)(...)&>();
    test_is_not_unsafe_floating_point<void (Class::*)(...) &&>();
    test_is_not_unsafe_floating_point<void (Class::*)(...) const>();
    test_is_not_unsafe_floating_point<void (Class::*)(...) const&>();
    test_is_not_unsafe_floating_point<void (Class::*)(...) const&&>();
    test_is_not_unsafe_floating_point<void (Class::*)(...) noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(...)& noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(...) const noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(...) const&& noexcept>();

    test_is_not_unsafe_floating_point<void (Class::*)(int, ...)>();
    test_is_not_unsafe_floating_point<void (Class::*)(int, ...)&>();
    test_is_not_unsafe_floating_point<void (Class::*)(int, ...) &&>();
    test_is_not_unsafe_floating_point<void (Class::*)(int, ...) const>();
    test_is_not_unsafe_floating_point<void (Class::*)(int, ...) const&>();
    test_is_not_unsafe_floating_point<void (Class::*)(int, ...) const&&>();
    test_is_not_unsafe_floating_point<void (Class::*)(int, ...) noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(int, ...)& noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(int, ...) const noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsafe_floating_point<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_unsafe_floating_point<int (Class::*)()>();
    test_is_not_unsafe_floating_point<int (Class::*)()&>();
    test_is_not_unsafe_floating_point<int (Class::*)() &&>();
    test_is_not_unsafe_floating_point<int (Class::*)() const>();
    test_is_not_unsafe_floating_point<int (Class::*)() const&>();
    test_is_not_unsafe_floating_point<int (Class::*)() const&&>();
    test_is_not_unsafe_floating_point<int (Class::*)() noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)()& noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)()&& noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)() const noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)() const& noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)() const&& noexcept>();

    test_is_not_unsafe_floating_point<int (Class::*)(int)>();
    test_is_not_unsafe_floating_point<int (Class::*)(int)&>();
    test_is_not_unsafe_floating_point<int (Class::*)(int) &&>();
    test_is_not_unsafe_floating_point<int (Class::*)(int) const>();
    test_is_not_unsafe_floating_point<int (Class::*)(int) const&>();
    test_is_not_unsafe_floating_point<int (Class::*)(int) const&&>();
    test_is_not_unsafe_floating_point<int (Class::*)(int) noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(int)& noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(int)&& noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(int) const noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(int) const& noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(int) const&& noexcept>();

    test_is_not_unsafe_floating_point<int (Class::*)(...)>();
    test_is_not_unsafe_floating_point<int (Class::*)(...)&>();
    test_is_not_unsafe_floating_point<int (Class::*)(...) &&>();
    test_is_not_unsafe_floating_point<int (Class::*)(...) const>();
    test_is_not_unsafe_floating_point<int (Class::*)(...) const&>();
    test_is_not_unsafe_floating_point<int (Class::*)(...) const&&>();
    test_is_not_unsafe_floating_point<int (Class::*)(...) noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(...)& noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(...)&& noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(...) const noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(...) const& noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(...) const&& noexcept>();

    test_is_not_unsafe_floating_point<int (Class::*)(int, ...)>();
    test_is_not_unsafe_floating_point<int (Class::*)(int, ...)&>();
    test_is_not_unsafe_floating_point<int (Class::*)(int, ...) &&>();
    test_is_not_unsafe_floating_point<int (Class::*)(int, ...) const>();
    test_is_not_unsafe_floating_point<int (Class::*)(int, ...) const&>();
    test_is_not_unsafe_floating_point<int (Class::*)(int, ...) const&&>();
    test_is_not_unsafe_floating_point<int (Class::*)(int, ...) noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(int, ...)& noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(int, ...) const noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_unsafe_floating_point<int (Class::*)(int, ...) const&& noexcept>();
}
