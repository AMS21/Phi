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
void test_is_function_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
    STATIC_REQUIRE(phi::is_compound<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point<T>::value);
    STATIC_REQUIRE(phi::is_function<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_fundamental<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_object<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_scalar<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
    STATIC_REQUIRE(phi::is_compound_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point_v<T>);
    STATIC_REQUIRE(phi::is_function_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_object_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_scalar_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);
#endif
};

template <typename T>
void test_is_function()
{
    test_is_function_impl<T>();
    test_is_function_impl<const T>();
    test_is_function_impl<volatile T>();
    test_is_function_impl<const volatile T>();
}

template <typename T>
void test_is_not_function()
{
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<const volatile T>);
#endif
};

TEST_CASE("is_function")
{
    test_is_function<void(void)>();
    test_is_function<int(int)>();
    test_is_function<int(int, double)>();
    test_is_function<int(int, double, float, char, bool)>();
    test_is_function<int(Abstract*)>();
    test_is_function<void(...)>();
    test_is_function<bool(...)>();
    test_is_function<Function>();

    test_is_not_function<void>();
    test_is_not_function<phi::nullptr_t>();
    test_is_not_function<bool>();
    test_is_not_function<char>();
    test_is_not_function<signed char>();
    test_is_not_function<unsigned char>();
    test_is_not_function<short>();
    test_is_not_function<unsigned short>();
    test_is_not_function<int>();
    test_is_not_function<unsigned int>();
    test_is_not_function<long>();
    test_is_not_function<unsigned long>();
    test_is_not_function<long long>();
    test_is_not_function<unsigned long long>();
    test_is_not_function<float>();
    test_is_not_function<double>();
    test_is_not_function<long double>();
    test_is_not_function<char8_t>();
    test_is_not_function<char16_t>();
    test_is_not_function<char32_t>();
    test_is_not_function<wchar_t>();

    test_is_not_function<phi::Boolean>();
    test_is_not_function<phi::Integer<signed char>>();
    test_is_not_function<phi::Integer<unsigned char>>();
    test_is_not_function<phi::Integer<short>>();
    test_is_not_function<phi::Integer<unsigned short>>();
    test_is_not_function<phi::Integer<int>>();
    test_is_not_function<phi::Integer<unsigned int>>();
    test_is_not_function<phi::Integer<long>>();
    test_is_not_function<phi::Integer<unsigned long>>();
    test_is_not_function<phi::Integer<long long>>();
    test_is_not_function<phi::Integer<unsigned long long>>();
    test_is_not_function<phi::FloatingPoint<float>>();
    test_is_not_function<phi::FloatingPoint<double>>();
    test_is_not_function<phi::FloatingPoint<long double>>();

    test_is_not_function<std::vector<int>>();
    test_is_not_function<phi::ScopePtr<int>>();

    test_is_not_function<int&>();
    test_is_not_function<const int&>();
    test_is_not_function<volatile int&>();
    test_is_not_function<const volatile int&>();
    test_is_not_function<int&&>();
    test_is_not_function<const int&&>();
    test_is_not_function<volatile int&&>();
    test_is_not_function<const volatile int&&>();
    test_is_not_function<int*>();
    test_is_not_function<const int*>();
    test_is_not_function<volatile int*>();
    test_is_not_function<const volatile int*>();
    test_is_not_function<int**>();
    test_is_not_function<const int**>();
    test_is_not_function<volatile int**>();
    test_is_not_function<const volatile int**>();
    test_is_not_function<int*&>();
    test_is_not_function<const int*&>();
    test_is_not_function<volatile int*&>();
    test_is_not_function<const volatile int*&>();
    test_is_not_function<int*&&>();
    test_is_not_function<const int*&&>();
    test_is_not_function<volatile int*&&>();
    test_is_not_function<const volatile int*&&>();
    test_is_not_function<void*>();
    test_is_not_function<char[3]>();
    test_is_not_function<char[]>();
    test_is_not_function<char* [3]>();
    test_is_not_function<char*[]>();
    test_is_not_function<int(*)[3]>();
    test_is_not_function<int(*)[]>();
    test_is_not_function<int(&)[3]>();
    test_is_not_function<int(&)[]>();
    test_is_not_function<int(&&)[3]>();
    test_is_not_function<int(&&)[]>();
    test_is_not_function<char[3][2]>();
    test_is_not_function<char[][2]>();
    test_is_not_function<char* [3][2]>();
    test_is_not_function<char*[][2]>();
    test_is_not_function<int(*)[3][2]>();
    test_is_not_function<int(*)[][2]>();
    test_is_not_function<int(&)[3][2]>();
    test_is_not_function<int(&)[][2]>();
    test_is_not_function<int(&&)[3][2]>();
    test_is_not_function<int(&&)[][2]>();
    test_is_not_function<Class>();
    test_is_not_function<Class[]>();
    test_is_not_function<Class[2]>();
    test_is_not_function<Struct>();
    test_is_not_function<TemplateClass<void>>();
    test_is_not_function<TemplateClass<int>>();
    test_is_not_function<TemplateClass<Class>>();
    test_is_not_function<TemplateClass<incomplete_type>>();
    test_is_not_function<TemplateStruct<void>>();
    test_is_not_function<TemplateStruct<int>>();
    test_is_not_function<TemplateStruct<Class>>();
    test_is_not_function<TemplateStruct<incomplete_type>>();
    test_is_not_function<VariadicTemplateClass<>>();
    test_is_not_function<VariadicTemplateClass<void>>();
    test_is_not_function<VariadicTemplateClass<int>>();
    test_is_not_function<VariadicTemplateClass<Class>>();
    test_is_not_function<VariadicTemplateClass<incomplete_type>>();
    test_is_not_function<VariadicTemplateClass<int, void, Class, volatile char[]>>();
    test_is_not_function<VariadicTemplateStruct<>>();
    test_is_not_function<VariadicTemplateStruct<void>>();
    test_is_not_function<VariadicTemplateStruct<int>>();
    test_is_not_function<VariadicTemplateStruct<Class>>();
    test_is_not_function<VariadicTemplateStruct<incomplete_type>>();
    test_is_not_function<VariadicTemplateStruct<int, void, Class, volatile char[]>>();
    test_is_not_function<PublicDerviedFromTemplate<Base>>();
    test_is_not_function<PublicDerviedFromTemplate<Derived>>();
    test_is_not_function<PublicDerviedFromTemplate<Class>>();
    test_is_not_function<PrivateDerviedFromTemplate<Base>>();
    test_is_not_function<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_function<PrivateDerviedFromTemplate<Class>>();
    test_is_not_function<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_function<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_function<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_function<Union>();
    test_is_not_function<NonEmptyUnion>();
    test_is_not_function<Empty>();
    test_is_not_function<NotEmpty>();
    test_is_not_function<bit_zero>();
    test_is_not_function<bit_one>();
    test_is_not_function<Base>();
    test_is_not_function<Derived>();
    test_is_not_function<Abstract>();
    test_is_not_function<AbstractTemplate<int>>();
    test_is_not_function<AbstractTemplate<double>>();
    test_is_not_function<AbstractTemplate<Class>>();
    test_is_not_function<AbstractTemplate<incomplete_type>>();
    test_is_not_function<Final>();
    test_is_not_function<Enum>();
    test_is_not_function<EnumSigned>();
    test_is_not_function<EnumUnsigned>();
    test_is_not_function<EnumClass>();
    test_is_not_function<EnumStruct>();
    test_is_function<Function>();
    test_is_not_function<FunctionPtr>();
    test_is_not_function<MemberObjectPtr>();
    test_is_not_function<MemberFunctionPtr>();
    test_is_not_function<incomplete_type>();
    test_is_not_function<IncompleteTemplate<void>>();
    test_is_not_function<IncompleteTemplate<int>>();
    test_is_not_function<IncompleteTemplate<Class>>();
    test_is_not_function<IncompleteTemplate<incomplete_type>>();
    test_is_not_function<IncompleteVariadicTemplate<>>();
    test_is_not_function<IncompleteVariadicTemplate<void>>();
    test_is_not_function<IncompleteVariadicTemplate<int>>();
    test_is_not_function<IncompleteVariadicTemplate<Class>>();
    test_is_not_function<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_function<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_function<int Class::*>();
    test_is_not_function<float Class::*>();
    test_is_not_function<void * Class::*>();
    test_is_not_function<int * Class::*>();
    test_is_not_function<int Class::*&>();
    test_is_not_function<float Class::*&>();
    test_is_not_function<void * Class::*&>();
    test_is_not_function<int * Class::*&>();
    test_is_not_function<int Class::*&&>();
    test_is_not_function<float Class::*&&>();
    test_is_not_function<void * Class::*&&>();
    test_is_not_function<int * Class::*&&>();
    test_is_not_function<int Class::*const>();
    test_is_not_function<float Class::*const>();
    test_is_not_function<void * Class::*const>();
    test_is_not_function<int Class::*const&>();
    test_is_not_function<float Class::*const&>();
    test_is_not_function<void * Class::*const&>();
    test_is_not_function<int Class::*const&&>();
    test_is_not_function<float Class::*const&&>();
    test_is_not_function<void * Class::*const&&>();
    test_is_not_function<int Class::*volatile>();
    test_is_not_function<float Class::*volatile>();
    test_is_not_function<void * Class::*volatile>();
    test_is_not_function<int Class::*volatile&>();
    test_is_not_function<float Class::*volatile&>();
    test_is_not_function<void * Class::*volatile&>();
    test_is_not_function<int Class::*volatile&&>();
    test_is_not_function<float Class::*volatile&&>();
    test_is_not_function<void * Class::*volatile&&>();
    test_is_not_function<int Class::*const volatile>();
    test_is_not_function<float Class::*const volatile>();
    test_is_not_function<void * Class::*const volatile>();
    test_is_not_function<int Class::*const volatile&>();
    test_is_not_function<float Class::*const volatile&>();
    test_is_not_function<void * Class::*const volatile&>();
    test_is_not_function<int Class::*const volatile&&>();
    test_is_not_function<float Class::*const volatile&&>();
    test_is_not_function<void * Class::*const volatile&&>();
    test_is_not_function<NonCopyable>();
    test_is_not_function<NonMoveable>();
    test_is_not_function<NonConstructible>();
    test_is_not_function<Tracked>();
    test_is_not_function<TrapConstructible>();
    test_is_not_function<TrapImplicitConversion>();
    test_is_not_function<TrapComma>();
    test_is_not_function<TrapCall>();
    test_is_not_function<TrapSelfAssign>();

    test_is_function<void()>();
    test_is_function<void()&>();
    test_is_function<void() &&>();
    test_is_function<void() const>();
    test_is_function<void() const&>();
    test_is_function<void() const&&>();
    test_is_function<void() volatile>();
    test_is_function<void() volatile&>();
    test_is_function<void() volatile&&>();
    test_is_function<void() const volatile>();
    test_is_function<void() const volatile&>();
    test_is_function<void() const volatile&&>();
    test_is_function<void() noexcept>();
    test_is_function<void()& noexcept>();
    test_is_function<void()&& noexcept>();
    test_is_function<void() const noexcept>();
    test_is_function<void() const& noexcept>();
    test_is_function<void() const&& noexcept>();
    test_is_function<void() volatile noexcept>();
    test_is_function<void() volatile& noexcept>();
    test_is_function<void() volatile&& noexcept>();
    test_is_function<void() const volatile noexcept>();
    test_is_function<void() const volatile& noexcept>();
    test_is_function<void() const volatile&& noexcept>();

    test_is_function<void(int)>();
    test_is_function<void(int)&>();
    test_is_function<void(int) &&>();
    test_is_function<void(int) const>();
    test_is_function<void(int) const&>();
    test_is_function<void(int) const&&>();
    test_is_function<void(int) volatile>();
    test_is_function<void(int) volatile&>();
    test_is_function<void(int) volatile&&>();
    test_is_function<void(int) const volatile>();
    test_is_function<void(int) const volatile&>();
    test_is_function<void(int) const volatile&&>();
    test_is_function<void(int) noexcept>();
    test_is_function<void(int)& noexcept>();
    test_is_function<void(int)&& noexcept>();
    test_is_function<void(int) const noexcept>();
    test_is_function<void(int) const& noexcept>();
    test_is_function<void(int) const&& noexcept>();
    test_is_function<void(int) volatile noexcept>();
    test_is_function<void(int) volatile& noexcept>();
    test_is_function<void(int) volatile&& noexcept>();
    test_is_function<void(int) const volatile noexcept>();
    test_is_function<void(int) const volatile& noexcept>();
    test_is_function<void(int) const volatile&& noexcept>();

    test_is_function<void(...)>();
    test_is_function<void(...)&>();
    test_is_function<void(...) &&>();
    test_is_function<void(...) const>();
    test_is_function<void(...) const&>();
    test_is_function<void(...) const&&>();
    test_is_function<void(...) volatile>();
    test_is_function<void(...) volatile&>();
    test_is_function<void(...) volatile&&>();
    test_is_function<void(...) const volatile>();
    test_is_function<void(...) const volatile&>();
    test_is_function<void(...) const volatile&&>();
    test_is_function<void(...) noexcept>();
    test_is_function<void(...)& noexcept>();
    test_is_function<void(...)&& noexcept>();
    test_is_function<void(...) const noexcept>();
    test_is_function<void(...) const& noexcept>();
    test_is_function<void(...) const&& noexcept>();
    test_is_function<void(...) volatile noexcept>();
    test_is_function<void(...) volatile& noexcept>();
    test_is_function<void(...) volatile&& noexcept>();
    test_is_function<void(...) const volatile noexcept>();
    test_is_function<void(...) const volatile& noexcept>();
    test_is_function<void(...) const volatile&& noexcept>();

    test_is_function<void(int, ...)>();
    test_is_function<void(int, ...)&>();
    test_is_function<void(int, ...) &&>();
    test_is_function<void(int, ...) const>();
    test_is_function<void(int, ...) const&>();
    test_is_function<void(int, ...) const&&>();
    test_is_function<void(int, ...) volatile>();
    test_is_function<void(int, ...) volatile&>();
    test_is_function<void(int, ...) volatile&&>();
    test_is_function<void(int, ...) const volatile>();
    test_is_function<void(int, ...) const volatile&>();
    test_is_function<void(int, ...) const volatile&&>();
    test_is_function<void(int, ...) noexcept>();
    test_is_function<void(int, ...)& noexcept>();
    test_is_function<void(int, ...)&& noexcept>();
    test_is_function<void(int, ...) const noexcept>();
    test_is_function<void(int, ...) const& noexcept>();
    test_is_function<void(int, ...) const&& noexcept>();
    test_is_function<void(int, ...) volatile noexcept>();
    test_is_function<void(int, ...) volatile& noexcept>();
    test_is_function<void(int, ...) volatile&& noexcept>();
    test_is_function<void(int, ...) const volatile noexcept>();
    test_is_function<void(int, ...) const volatile& noexcept>();
    test_is_function<void(int, ...) const volatile&& noexcept>();

    test_is_function<int()>();
    test_is_function<int()&>();
    test_is_function<int() &&>();
    test_is_function<int() const>();
    test_is_function<int() const&>();
    test_is_function<int() const&&>();
    test_is_function<int() volatile>();
    test_is_function<int() volatile&>();
    test_is_function<int() volatile&&>();
    test_is_function<int() const volatile>();
    test_is_function<int() const volatile&>();
    test_is_function<int() const volatile&&>();
    test_is_function<int() noexcept>();
    test_is_function<int()& noexcept>();
    test_is_function<int()&& noexcept>();
    test_is_function<int() const noexcept>();
    test_is_function<int() const& noexcept>();
    test_is_function<int() const&& noexcept>();
    test_is_function<int() volatile noexcept>();
    test_is_function<int() volatile& noexcept>();
    test_is_function<int() volatile&& noexcept>();
    test_is_function<int() const volatile noexcept>();
    test_is_function<int() const volatile& noexcept>();
    test_is_function<int() const volatile&& noexcept>();

    test_is_function<int(int)>();
    test_is_function<int(int)&>();
    test_is_function<int(int) &&>();
    test_is_function<int(int) const>();
    test_is_function<int(int) const&>();
    test_is_function<int(int) const&&>();
    test_is_function<int(int) volatile>();
    test_is_function<int(int) volatile&>();
    test_is_function<int(int) volatile&&>();
    test_is_function<int(int) const volatile>();
    test_is_function<int(int) const volatile&>();
    test_is_function<int(int) const volatile&&>();
    test_is_function<int(int) noexcept>();
    test_is_function<int(int)& noexcept>();
    test_is_function<int(int)&& noexcept>();
    test_is_function<int(int) const noexcept>();
    test_is_function<int(int) const& noexcept>();
    test_is_function<int(int) const&& noexcept>();
    test_is_function<int(int) volatile noexcept>();
    test_is_function<int(int) volatile& noexcept>();
    test_is_function<int(int) volatile&& noexcept>();
    test_is_function<int(int) const volatile noexcept>();
    test_is_function<int(int) const volatile& noexcept>();
    test_is_function<int(int) const volatile&& noexcept>();

    test_is_function<int(...)>();
    test_is_function<int(...)&>();
    test_is_function<int(...) &&>();
    test_is_function<int(...) const>();
    test_is_function<int(...) const&>();
    test_is_function<int(...) const&&>();
    test_is_function<int(...) volatile>();
    test_is_function<int(...) volatile&>();
    test_is_function<int(...) volatile&&>();
    test_is_function<int(...) const volatile>();
    test_is_function<int(...) const volatile&>();
    test_is_function<int(...) const volatile&&>();
    test_is_function<int(...) noexcept>();
    test_is_function<int(...)& noexcept>();
    test_is_function<int(...)&& noexcept>();
    test_is_function<int(...) const noexcept>();
    test_is_function<int(...) const& noexcept>();
    test_is_function<int(...) const&& noexcept>();
    test_is_function<int(...) volatile noexcept>();
    test_is_function<int(...) volatile& noexcept>();
    test_is_function<int(...) volatile&& noexcept>();
    test_is_function<int(...) const volatile noexcept>();
    test_is_function<int(...) const volatile& noexcept>();
    test_is_function<int(...) const volatile&& noexcept>();

    test_is_function<int(int, ...)>();
    test_is_function<int(int, ...)&>();
    test_is_function<int(int, ...) &&>();
    test_is_function<int(int, ...) const>();
    test_is_function<int(int, ...) const&>();
    test_is_function<int(int, ...) const&&>();
    test_is_function<int(int, ...) volatile>();
    test_is_function<int(int, ...) volatile&>();
    test_is_function<int(int, ...) volatile&&>();
    test_is_function<int(int, ...) const volatile>();
    test_is_function<int(int, ...) const volatile&>();
    test_is_function<int(int, ...) const volatile&&>();
    test_is_function<int(int, ...) noexcept>();
    test_is_function<int(int, ...)& noexcept>();
    test_is_function<int(int, ...)&& noexcept>();
    test_is_function<int(int, ...) const noexcept>();
    test_is_function<int(int, ...) const& noexcept>();
    test_is_function<int(int, ...) const&& noexcept>();
    test_is_function<int(int, ...) volatile noexcept>();
    test_is_function<int(int, ...) volatile& noexcept>();
    test_is_function<int(int, ...) volatile&& noexcept>();
    test_is_function<int(int, ...) const volatile noexcept>();
    test_is_function<int(int, ...) const volatile& noexcept>();
    test_is_function<int(int, ...) const volatile&& noexcept>();

    test_is_not_function<void (*)()>();
    test_is_not_function<void (*)() noexcept>();

    test_is_not_function<void (*)(int)>();
    test_is_not_function<void (*)(int) noexcept>();

    test_is_not_function<void (*)(...)>();
    test_is_not_function<void (*)(...) noexcept>();

    test_is_not_function<void (*)(int, ...)>();
    test_is_not_function<void (*)(int, ...) noexcept>();

    test_is_not_function<int (*)()>();
    test_is_not_function<int (*)() noexcept>();

    test_is_not_function<int (*)(int)>();
    test_is_not_function<int (*)(int) noexcept>();

    test_is_not_function<int (*)(...)>();
    test_is_not_function<int (*)(...) noexcept>();

    test_is_not_function<int (*)(int, ...)>();
    test_is_not_function<int (*)(int, ...) noexcept>();

    test_is_not_function<void (&)()>();
    test_is_not_function<void (&)() noexcept>();

    test_is_not_function<void (&)(int)>();
    test_is_not_function<void (&)(int) noexcept>();

    test_is_not_function<void (&)(...)>();
    test_is_not_function<void (&)(...) noexcept>();

    test_is_not_function<void (&)(int, ...)>();
    test_is_not_function<void (&)(int, ...) noexcept>();

    test_is_not_function<int (&)()>();
    test_is_not_function<int (&)() noexcept>();

    test_is_not_function<int (&)(int)>();
    test_is_not_function<int (&)(int) noexcept>();

    test_is_not_function<int (&)(...)>();
    test_is_not_function<int (&)(...) noexcept>();

    test_is_not_function<int (&)(int, ...)>();
    test_is_not_function<int (&)(int, ...) noexcept>();

    test_is_not_function<void(&&)()>();
    test_is_not_function<void(&&)() noexcept>();

    test_is_not_function<void(&&)(int)>();
    test_is_not_function<void(&&)(int) noexcept>();

    test_is_not_function<void(&&)(...)>();
    test_is_not_function<void(&&)(...) noexcept>();

    test_is_not_function<void(&&)(int, ...)>();
    test_is_not_function<void(&&)(int, ...) noexcept>();

    test_is_not_function<int(&&)()>();
    test_is_not_function<int(&&)() noexcept>();

    test_is_not_function<int(&&)(int)>();
    test_is_not_function<int(&&)(int) noexcept>();

    test_is_not_function<int(&&)(...)>();
    test_is_not_function<int(&&)(...) noexcept>();

    test_is_not_function<int(&&)(int, ...)>();
    test_is_not_function<int(&&)(int, ...) noexcept>();

    test_is_not_function<void (Class::*)()>();
    test_is_not_function<void (Class::*)()&>();
    test_is_not_function<void (Class::*)() &&>();
    test_is_not_function<void (Class::*)() const>();
    test_is_not_function<void (Class::*)() const&>();
    test_is_not_function<void (Class::*)() const&&>();
    test_is_not_function<void (Class::*)() noexcept>();
    test_is_not_function<void (Class::*)()& noexcept>();
    test_is_not_function<void (Class::*)()&& noexcept>();
    test_is_not_function<void (Class::*)() const noexcept>();
    test_is_not_function<void (Class::*)() const& noexcept>();
    test_is_not_function<void (Class::*)() const&& noexcept>();

    test_is_not_function<void (Class::*)(int)>();
    test_is_not_function<void (Class::*)(int)&>();
    test_is_not_function<void (Class::*)(int) &&>();
    test_is_not_function<void (Class::*)(int) const>();
    test_is_not_function<void (Class::*)(int) const&>();
    test_is_not_function<void (Class::*)(int) const&&>();
    test_is_not_function<void (Class::*)(int) noexcept>();
    test_is_not_function<void (Class::*)(int)& noexcept>();
    test_is_not_function<void (Class::*)(int)&& noexcept>();
    test_is_not_function<void (Class::*)(int) const noexcept>();
    test_is_not_function<void (Class::*)(int) const& noexcept>();
    test_is_not_function<void (Class::*)(int) const&& noexcept>();

    test_is_not_function<void (Class::*)(...)>();
    test_is_not_function<void (Class::*)(...)&>();
    test_is_not_function<void (Class::*)(...) &&>();
    test_is_not_function<void (Class::*)(...) const>();
    test_is_not_function<void (Class::*)(...) const&>();
    test_is_not_function<void (Class::*)(...) const&&>();
    test_is_not_function<void (Class::*)(...) noexcept>();
    test_is_not_function<void (Class::*)(...)& noexcept>();
    test_is_not_function<void (Class::*)(...)&& noexcept>();
    test_is_not_function<void (Class::*)(...) const noexcept>();
    test_is_not_function<void (Class::*)(...) const& noexcept>();
    test_is_not_function<void (Class::*)(...) const&& noexcept>();

    test_is_not_function<void (Class::*)(int, ...)>();
    test_is_not_function<void (Class::*)(int, ...)&>();
    test_is_not_function<void (Class::*)(int, ...) &&>();
    test_is_not_function<void (Class::*)(int, ...) const>();
    test_is_not_function<void (Class::*)(int, ...) const&>();
    test_is_not_function<void (Class::*)(int, ...) const&&>();
    test_is_not_function<void (Class::*)(int, ...) noexcept>();
    test_is_not_function<void (Class::*)(int, ...)& noexcept>();
    test_is_not_function<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_function<void (Class::*)(int, ...) const noexcept>();
    test_is_not_function<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_function<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_function<int (Class::*)()>();
    test_is_not_function<int (Class::*)()&>();
    test_is_not_function<int (Class::*)() &&>();
    test_is_not_function<int (Class::*)() const>();
    test_is_not_function<int (Class::*)() const&>();
    test_is_not_function<int (Class::*)() const&&>();
    test_is_not_function<int (Class::*)() noexcept>();
    test_is_not_function<int (Class::*)()& noexcept>();
    test_is_not_function<int (Class::*)()&& noexcept>();
    test_is_not_function<int (Class::*)() const noexcept>();
    test_is_not_function<int (Class::*)() const& noexcept>();
    test_is_not_function<int (Class::*)() const&& noexcept>();

    test_is_not_function<int (Class::*)(int)>();
    test_is_not_function<int (Class::*)(int)&>();
    test_is_not_function<int (Class::*)(int) &&>();
    test_is_not_function<int (Class::*)(int) const>();
    test_is_not_function<int (Class::*)(int) const&>();
    test_is_not_function<int (Class::*)(int) const&&>();
    test_is_not_function<int (Class::*)(int) noexcept>();
    test_is_not_function<int (Class::*)(int)& noexcept>();
    test_is_not_function<int (Class::*)(int)&& noexcept>();
    test_is_not_function<int (Class::*)(int) const noexcept>();
    test_is_not_function<int (Class::*)(int) const& noexcept>();
    test_is_not_function<int (Class::*)(int) const&& noexcept>();

    test_is_not_function<int (Class::*)(...)>();
    test_is_not_function<int (Class::*)(...)&>();
    test_is_not_function<int (Class::*)(...) &&>();
    test_is_not_function<int (Class::*)(...) const>();
    test_is_not_function<int (Class::*)(...) const&>();
    test_is_not_function<int (Class::*)(...) const&&>();
    test_is_not_function<int (Class::*)(...) noexcept>();
    test_is_not_function<int (Class::*)(...)& noexcept>();
    test_is_not_function<int (Class::*)(...)&& noexcept>();
    test_is_not_function<int (Class::*)(...) const noexcept>();
    test_is_not_function<int (Class::*)(...) const& noexcept>();
    test_is_not_function<int (Class::*)(...) const&& noexcept>();

    test_is_not_function<int (Class::*)(int, ...)>();
    test_is_not_function<int (Class::*)(int, ...)&>();
    test_is_not_function<int (Class::*)(int, ...) &&>();
    test_is_not_function<int (Class::*)(int, ...) const>();
    test_is_not_function<int (Class::*)(int, ...) const&>();
    test_is_not_function<int (Class::*)(int, ...) const&&>();
    test_is_not_function<int (Class::*)(int, ...) noexcept>();
    test_is_not_function<int (Class::*)(int, ...)& noexcept>();
    test_is_not_function<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_function<int (Class::*)(int, ...) const noexcept>();
    test_is_not_function<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_function<int (Class::*)(int, ...) const&& noexcept>();
}
