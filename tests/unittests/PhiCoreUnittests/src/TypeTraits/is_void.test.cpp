#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
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
void test_is_void_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_compound<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE(phi::is_fundamental<T>::value);
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
    STATIC_REQUIRE(phi::is_void<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_compound_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE(phi::is_fundamental_v<T>);
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
    STATIC_REQUIRE(phi::is_void_v<T>);
#endif
}

template <typename T>
void test_is_void()
{
    test_is_void_impl<T>();
    test_is_void_impl<const T>();
    test_is_void_impl<volatile T>();
    test_is_void_impl<const volatile T>();
}

template <typename T>
void test_is_not_void()
{
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<const volatile T>);
#endif
}

TEST_CASE("is_void")
{
    test_is_void<void>();
    test_is_not_void<phi::nullptr_t>();
    test_is_not_void<bool>();
    test_is_not_void<char>();
    test_is_not_void<signed char>();
    test_is_not_void<unsigned char>();
    test_is_not_void<short>();
    test_is_not_void<unsigned short>();
    test_is_not_void<int>();
    test_is_not_void<unsigned int>();
    test_is_not_void<long>();
    test_is_not_void<unsigned long>();
    test_is_not_void<long long>();
    test_is_not_void<unsigned long long>();
    test_is_not_void<float>();
    test_is_not_void<double>();
    test_is_not_void<long double>();
    test_is_not_void<char8_t>();
    test_is_not_void<char16_t>();
    test_is_not_void<char32_t>();
    test_is_not_void<wchar_t>();

    test_is_not_void<phi::Boolean>();
    test_is_not_void<phi::Integer<signed char>>();
    test_is_not_void<phi::Integer<unsigned char>>();
    test_is_not_void<phi::Integer<short>>();
    test_is_not_void<phi::Integer<unsigned short>>();
    test_is_not_void<phi::Integer<int>>();
    test_is_not_void<phi::Integer<unsigned int>>();
    test_is_not_void<phi::Integer<long>>();
    test_is_not_void<phi::Integer<unsigned long>>();
    test_is_not_void<phi::Integer<long long>>();
    test_is_not_void<phi::Integer<unsigned long long>>();
    test_is_not_void<phi::FloatingPoint<float>>();
    test_is_not_void<phi::FloatingPoint<double>>();
    test_is_not_void<phi::FloatingPoint<long double>>();

    test_is_not_void<std::vector<int>>();
    test_is_not_void<phi::ScopePtr<int>>();

    test_is_not_void<int&>();
    test_is_not_void<const int&>();
    test_is_not_void<volatile int&>();
    test_is_not_void<const volatile int&>();
    test_is_not_void<int&&>();
    test_is_not_void<const int&&>();
    test_is_not_void<volatile int&&>();
    test_is_not_void<const volatile int&&>();
    test_is_not_void<int*>();
    test_is_not_void<const int*>();
    test_is_not_void<volatile int*>();
    test_is_not_void<const volatile int*>();
    test_is_not_void<int**>();
    test_is_not_void<const int**>();
    test_is_not_void<volatile int**>();
    test_is_not_void<const volatile int**>();
    test_is_not_void<int*&>();
    test_is_not_void<const int*&>();
    test_is_not_void<volatile int*&>();
    test_is_not_void<const volatile int*&>();
    test_is_not_void<int*&&>();
    test_is_not_void<const int*&&>();
    test_is_not_void<volatile int*&&>();
    test_is_not_void<const volatile int*&&>();
    test_is_not_void<void*>();
    test_is_not_void<char[3]>();
    test_is_not_void<char[]>();
    test_is_not_void<char* [3]>();
    test_is_not_void<char*[]>();
    test_is_not_void<int(*)[3]>();
    test_is_not_void<int(*)[]>();
    test_is_not_void<int(&)[3]>();
    test_is_not_void<int(&)[]>();
    test_is_not_void<int(&&)[3]>();
    test_is_not_void<int(&&)[]>();
    test_is_not_void<char[3][2]>();
    test_is_not_void<char[][2]>();
    test_is_not_void<char* [3][2]>();
    test_is_not_void<char*[][2]>();
    test_is_not_void<int(*)[3][2]>();
    test_is_not_void<int(*)[][2]>();
    test_is_not_void<int(&)[3][2]>();
    test_is_not_void<int(&)[][2]>();
    test_is_not_void<int(&&)[3][2]>();
    test_is_not_void<int(&&)[][2]>();
    test_is_not_void<Class>();
    test_is_not_void<Class[]>();
    test_is_not_void<Class[2]>();
    test_is_not_void<Struct>();
    test_is_not_void<TemplateClass<void>>();
    test_is_not_void<TemplateClass<int>>();
    test_is_not_void<TemplateClass<Class>>();
    test_is_not_void<TemplateClass<incomplete_type>>();
    test_is_not_void<TemplateStruct<void>>();
    test_is_not_void<TemplateStruct<int>>();
    test_is_not_void<TemplateStruct<Class>>();
    test_is_not_void<TemplateStruct<incomplete_type>>();
    test_is_not_void<VariadicTemplateClass<>>();
    test_is_not_void<VariadicTemplateClass<void>>();
    test_is_not_void<VariadicTemplateClass<int>>();
    test_is_not_void<VariadicTemplateClass<Class>>();
    test_is_not_void<VariadicTemplateClass<incomplete_type>>();
    test_is_not_void<VariadicTemplateClass<int, void, Class, volatile char[]>>();
    test_is_not_void<VariadicTemplateStruct<>>();
    test_is_not_void<VariadicTemplateStruct<void>>();
    test_is_not_void<VariadicTemplateStruct<int>>();
    test_is_not_void<VariadicTemplateStruct<Class>>();
    test_is_not_void<VariadicTemplateStruct<incomplete_type>>();
    test_is_not_void<VariadicTemplateStruct<int, void, Class, volatile char[]>>();
    test_is_not_void<PublicDerviedFromTemplate<Base>>();
    test_is_not_void<PublicDerviedFromTemplate<Derived>>();
    test_is_not_void<PublicDerviedFromTemplate<Class>>();
    test_is_not_void<PrivateDerviedFromTemplate<Base>>();
    test_is_not_void<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_void<PrivateDerviedFromTemplate<Class>>();
    test_is_not_void<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_void<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_void<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_void<Union>();
    test_is_not_void<NonEmptyUnion>();
    test_is_not_void<Empty>();
    test_is_not_void<NotEmpty>();
    test_is_not_void<bit_zero>();
    test_is_not_void<bit_one>();
    test_is_not_void<Base>();
    test_is_not_void<Derived>();
    test_is_not_void<Abstract>();
    test_is_not_void<AbstractTemplate<int>>();
    test_is_not_void<AbstractTemplate<double>>();
    test_is_not_void<AbstractTemplate<Class>>();
    test_is_not_void<AbstractTemplate<incomplete_type>>();
    test_is_not_void<Final>();
    test_is_not_void<Enum>();
    test_is_not_void<EnumSigned>();
    test_is_not_void<EnumUnsigned>();
    test_is_not_void<EnumClass>();
    test_is_not_void<EnumStruct>();
    test_is_not_void<Function>();
    test_is_not_void<FunctionPtr>();
    test_is_not_void<MemberObjectPtr>();
    test_is_not_void<MemberFunctionPtr>();
    test_is_not_void<incomplete_type>();
    test_is_not_void<IncompleteTemplate<void>>();
    test_is_not_void<IncompleteTemplate<int>>();
    test_is_not_void<IncompleteTemplate<Class>>();
    test_is_not_void<IncompleteTemplate<incomplete_type>>();
    test_is_not_void<IncompleteVariadicTemplate<>>();
    test_is_not_void<IncompleteVariadicTemplate<void>>();
    test_is_not_void<IncompleteVariadicTemplate<int>>();
    test_is_not_void<IncompleteVariadicTemplate<Class>>();
    test_is_not_void<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_void<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_void<int Class::*>();
    test_is_not_void<float Class::*>();
    test_is_not_void<void * Class::*>();
    test_is_not_void<int * Class::*>();
    test_is_not_void<int Class::*&>();
    test_is_not_void<float Class::*&>();
    test_is_not_void<void * Class::*&>();
    test_is_not_void<int * Class::*&>();
    test_is_not_void<int Class::*&&>();
    test_is_not_void<float Class::*&&>();
    test_is_not_void<void * Class::*&&>();
    test_is_not_void<int * Class::*&&>();
    test_is_not_void<int Class::*const>();
    test_is_not_void<float Class::*const>();
    test_is_not_void<void * Class::*const>();
    test_is_not_void<int Class::*const&>();
    test_is_not_void<float Class::*const&>();
    test_is_not_void<void * Class::*const&>();
    test_is_not_void<int Class::*const&&>();
    test_is_not_void<float Class::*const&&>();
    test_is_not_void<void * Class::*const&&>();
    test_is_not_void<int Class::*volatile>();
    test_is_not_void<float Class::*volatile>();
    test_is_not_void<void * Class::*volatile>();
    test_is_not_void<int Class::*volatile&>();
    test_is_not_void<float Class::*volatile&>();
    test_is_not_void<void * Class::*volatile&>();
    test_is_not_void<int Class::*volatile&&>();
    test_is_not_void<float Class::*volatile&&>();
    test_is_not_void<void * Class::*volatile&&>();
    test_is_not_void<int Class::*const volatile>();
    test_is_not_void<float Class::*const volatile>();
    test_is_not_void<void * Class::*const volatile>();
    test_is_not_void<int Class::*const volatile&>();
    test_is_not_void<float Class::*const volatile&>();
    test_is_not_void<void * Class::*const volatile&>();
    test_is_not_void<int Class::*const volatile&&>();
    test_is_not_void<float Class::*const volatile&&>();
    test_is_not_void<void * Class::*const volatile&&>();
    test_is_not_void<NonCopyable>();
    test_is_not_void<NonMoveable>();
    test_is_not_void<NonConstructible>();
    test_is_not_void<Tracked>();
    test_is_not_void<TrapConstructible>();
    test_is_not_void<TrapImplicitConversion>();
    test_is_not_void<TrapComma>();
    test_is_not_void<TrapCall>();
    test_is_not_void<TrapSelfAssign>();

    test_is_not_void<void()>();
    test_is_not_void<void()&>();
    test_is_not_void<void() &&>();
    test_is_not_void<void() const>();
    test_is_not_void<void() const&>();
    test_is_not_void<void() const&&>();
    test_is_not_void<void() volatile>();
    test_is_not_void<void() volatile&>();
    test_is_not_void<void() volatile&&>();
    test_is_not_void<void() const volatile>();
    test_is_not_void<void() const volatile&>();
    test_is_not_void<void() const volatile&&>();
    test_is_not_void<void() noexcept>();
    test_is_not_void<void()& noexcept>();
    test_is_not_void<void()&& noexcept>();
    test_is_not_void<void() const noexcept>();
    test_is_not_void<void() const& noexcept>();
    test_is_not_void<void() const&& noexcept>();
    test_is_not_void<void() volatile noexcept>();
    test_is_not_void<void() volatile& noexcept>();
    test_is_not_void<void() volatile&& noexcept>();
    test_is_not_void<void() const volatile noexcept>();
    test_is_not_void<void() const volatile& noexcept>();
    test_is_not_void<void() const volatile&& noexcept>();

    test_is_not_void<void(int)>();
    test_is_not_void<void(int)&>();
    test_is_not_void<void(int) &&>();
    test_is_not_void<void(int) const>();
    test_is_not_void<void(int) const&>();
    test_is_not_void<void(int) const&&>();
    test_is_not_void<void(int) volatile>();
    test_is_not_void<void(int) volatile&>();
    test_is_not_void<void(int) volatile&&>();
    test_is_not_void<void(int) const volatile>();
    test_is_not_void<void(int) const volatile&>();
    test_is_not_void<void(int) const volatile&&>();
    test_is_not_void<void(int) noexcept>();
    test_is_not_void<void(int)& noexcept>();
    test_is_not_void<void(int)&& noexcept>();
    test_is_not_void<void(int) const noexcept>();
    test_is_not_void<void(int) const& noexcept>();
    test_is_not_void<void(int) const&& noexcept>();
    test_is_not_void<void(int) volatile noexcept>();
    test_is_not_void<void(int) volatile& noexcept>();
    test_is_not_void<void(int) volatile&& noexcept>();
    test_is_not_void<void(int) const volatile noexcept>();
    test_is_not_void<void(int) const volatile& noexcept>();
    test_is_not_void<void(int) const volatile&& noexcept>();

    test_is_not_void<void(...)>();
    test_is_not_void<void(...)&>();
    test_is_not_void<void(...) &&>();
    test_is_not_void<void(...) const>();
    test_is_not_void<void(...) const&>();
    test_is_not_void<void(...) const&&>();
    test_is_not_void<void(...) volatile>();
    test_is_not_void<void(...) volatile&>();
    test_is_not_void<void(...) volatile&&>();
    test_is_not_void<void(...) const volatile>();
    test_is_not_void<void(...) const volatile&>();
    test_is_not_void<void(...) const volatile&&>();
    test_is_not_void<void(...) noexcept>();
    test_is_not_void<void(...)& noexcept>();
    test_is_not_void<void(...)&& noexcept>();
    test_is_not_void<void(...) const noexcept>();
    test_is_not_void<void(...) const& noexcept>();
    test_is_not_void<void(...) const&& noexcept>();
    test_is_not_void<void(...) volatile noexcept>();
    test_is_not_void<void(...) volatile& noexcept>();
    test_is_not_void<void(...) volatile&& noexcept>();
    test_is_not_void<void(...) const volatile noexcept>();
    test_is_not_void<void(...) const volatile& noexcept>();
    test_is_not_void<void(...) const volatile&& noexcept>();

    test_is_not_void<void(int, ...)>();
    test_is_not_void<void(int, ...)&>();
    test_is_not_void<void(int, ...) &&>();
    test_is_not_void<void(int, ...) const>();
    test_is_not_void<void(int, ...) const&>();
    test_is_not_void<void(int, ...) const&&>();
    test_is_not_void<void(int, ...) volatile>();
    test_is_not_void<void(int, ...) volatile&>();
    test_is_not_void<void(int, ...) volatile&&>();
    test_is_not_void<void(int, ...) const volatile>();
    test_is_not_void<void(int, ...) const volatile&>();
    test_is_not_void<void(int, ...) const volatile&&>();
    test_is_not_void<void(int, ...) noexcept>();
    test_is_not_void<void(int, ...)& noexcept>();
    test_is_not_void<void(int, ...)&& noexcept>();
    test_is_not_void<void(int, ...) const noexcept>();
    test_is_not_void<void(int, ...) const& noexcept>();
    test_is_not_void<void(int, ...) const&& noexcept>();
    test_is_not_void<void(int, ...) volatile noexcept>();
    test_is_not_void<void(int, ...) volatile& noexcept>();
    test_is_not_void<void(int, ...) volatile&& noexcept>();
    test_is_not_void<void(int, ...) const volatile noexcept>();
    test_is_not_void<void(int, ...) const volatile& noexcept>();
    test_is_not_void<void(int, ...) const volatile&& noexcept>();

    test_is_not_void<int()>();
    test_is_not_void<int()&>();
    test_is_not_void<int() &&>();
    test_is_not_void<int() const>();
    test_is_not_void<int() const&>();
    test_is_not_void<int() const&&>();
    test_is_not_void<int() volatile>();
    test_is_not_void<int() volatile&>();
    test_is_not_void<int() volatile&&>();
    test_is_not_void<int() const volatile>();
    test_is_not_void<int() const volatile&>();
    test_is_not_void<int() const volatile&&>();
    test_is_not_void<int() noexcept>();
    test_is_not_void<int()& noexcept>();
    test_is_not_void<int()&& noexcept>();
    test_is_not_void<int() const noexcept>();
    test_is_not_void<int() const& noexcept>();
    test_is_not_void<int() const&& noexcept>();
    test_is_not_void<int() volatile noexcept>();
    test_is_not_void<int() volatile& noexcept>();
    test_is_not_void<int() volatile&& noexcept>();
    test_is_not_void<int() const volatile noexcept>();
    test_is_not_void<int() const volatile& noexcept>();
    test_is_not_void<int() const volatile&& noexcept>();

    test_is_not_void<int(int)>();
    test_is_not_void<int(int)&>();
    test_is_not_void<int(int) &&>();
    test_is_not_void<int(int) const>();
    test_is_not_void<int(int) const&>();
    test_is_not_void<int(int) const&&>();
    test_is_not_void<int(int) volatile>();
    test_is_not_void<int(int) volatile&>();
    test_is_not_void<int(int) volatile&&>();
    test_is_not_void<int(int) const volatile>();
    test_is_not_void<int(int) const volatile&>();
    test_is_not_void<int(int) const volatile&&>();
    test_is_not_void<int(int) noexcept>();
    test_is_not_void<int(int)& noexcept>();
    test_is_not_void<int(int)&& noexcept>();
    test_is_not_void<int(int) const noexcept>();
    test_is_not_void<int(int) const& noexcept>();
    test_is_not_void<int(int) const&& noexcept>();
    test_is_not_void<int(int) volatile noexcept>();
    test_is_not_void<int(int) volatile& noexcept>();
    test_is_not_void<int(int) volatile&& noexcept>();
    test_is_not_void<int(int) const volatile noexcept>();
    test_is_not_void<int(int) const volatile& noexcept>();
    test_is_not_void<int(int) const volatile&& noexcept>();

    test_is_not_void<int(...)>();
    test_is_not_void<int(...)&>();
    test_is_not_void<int(...) &&>();
    test_is_not_void<int(...) const>();
    test_is_not_void<int(...) const&>();
    test_is_not_void<int(...) const&&>();
    test_is_not_void<int(...) volatile>();
    test_is_not_void<int(...) volatile&>();
    test_is_not_void<int(...) volatile&&>();
    test_is_not_void<int(...) const volatile>();
    test_is_not_void<int(...) const volatile&>();
    test_is_not_void<int(...) const volatile&&>();
    test_is_not_void<int(...) noexcept>();
    test_is_not_void<int(...)& noexcept>();
    test_is_not_void<int(...)&& noexcept>();
    test_is_not_void<int(...) const noexcept>();
    test_is_not_void<int(...) const& noexcept>();
    test_is_not_void<int(...) const&& noexcept>();
    test_is_not_void<int(...) volatile noexcept>();
    test_is_not_void<int(...) volatile& noexcept>();
    test_is_not_void<int(...) volatile&& noexcept>();
    test_is_not_void<int(...) const volatile noexcept>();
    test_is_not_void<int(...) const volatile& noexcept>();
    test_is_not_void<int(...) const volatile&& noexcept>();

    test_is_not_void<int(int, ...)>();
    test_is_not_void<int(int, ...)&>();
    test_is_not_void<int(int, ...) &&>();
    test_is_not_void<int(int, ...) const>();
    test_is_not_void<int(int, ...) const&>();
    test_is_not_void<int(int, ...) const&&>();
    test_is_not_void<int(int, ...) volatile>();
    test_is_not_void<int(int, ...) volatile&>();
    test_is_not_void<int(int, ...) volatile&&>();
    test_is_not_void<int(int, ...) const volatile>();
    test_is_not_void<int(int, ...) const volatile&>();
    test_is_not_void<int(int, ...) const volatile&&>();
    test_is_not_void<int(int, ...) noexcept>();
    test_is_not_void<int(int, ...)& noexcept>();
    test_is_not_void<int(int, ...)&& noexcept>();
    test_is_not_void<int(int, ...) const noexcept>();
    test_is_not_void<int(int, ...) const& noexcept>();
    test_is_not_void<int(int, ...) const&& noexcept>();
    test_is_not_void<int(int, ...) volatile noexcept>();
    test_is_not_void<int(int, ...) volatile& noexcept>();
    test_is_not_void<int(int, ...) volatile&& noexcept>();
    test_is_not_void<int(int, ...) const volatile noexcept>();
    test_is_not_void<int(int, ...) const volatile& noexcept>();
    test_is_not_void<int(int, ...) const volatile&& noexcept>();

    test_is_not_void<void (*)()>();
    test_is_not_void<void (*)() noexcept>();

    test_is_not_void<void (*)(int)>();
    test_is_not_void<void (*)(int) noexcept>();

    test_is_not_void<void (*)(...)>();
    test_is_not_void<void (*)(...) noexcept>();

    test_is_not_void<void (*)(int, ...)>();
    test_is_not_void<void (*)(int, ...) noexcept>();

    test_is_not_void<int (*)()>();
    test_is_not_void<int (*)() noexcept>();

    test_is_not_void<int (*)(int)>();
    test_is_not_void<int (*)(int) noexcept>();

    test_is_not_void<int (*)(...)>();
    test_is_not_void<int (*)(...) noexcept>();

    test_is_not_void<int (*)(int, ...)>();
    test_is_not_void<int (*)(int, ...) noexcept>();

    test_is_not_void<void (&)()>();
    test_is_not_void<void (&)() noexcept>();

    test_is_not_void<void (&)(int)>();
    test_is_not_void<void (&)(int) noexcept>();

    test_is_not_void<void (&)(...)>();
    test_is_not_void<void (&)(...) noexcept>();

    test_is_not_void<void (&)(int, ...)>();
    test_is_not_void<void (&)(int, ...) noexcept>();

    test_is_not_void<int (&)()>();
    test_is_not_void<int (&)() noexcept>();

    test_is_not_void<int (&)(int)>();
    test_is_not_void<int (&)(int) noexcept>();

    test_is_not_void<int (&)(...)>();
    test_is_not_void<int (&)(...) noexcept>();

    test_is_not_void<int (&)(int, ...)>();
    test_is_not_void<int (&)(int, ...) noexcept>();

    test_is_not_void<void(&&)()>();
    test_is_not_void<void(&&)() noexcept>();

    test_is_not_void<void(&&)(int)>();
    test_is_not_void<void(&&)(int) noexcept>();

    test_is_not_void<void(&&)(...)>();
    test_is_not_void<void(&&)(...) noexcept>();

    test_is_not_void<void(&&)(int, ...)>();
    test_is_not_void<void(&&)(int, ...) noexcept>();

    test_is_not_void<int(&&)()>();
    test_is_not_void<int(&&)() noexcept>();

    test_is_not_void<int(&&)(int)>();
    test_is_not_void<int(&&)(int) noexcept>();

    test_is_not_void<int(&&)(...)>();
    test_is_not_void<int(&&)(...) noexcept>();

    test_is_not_void<int(&&)(int, ...)>();
    test_is_not_void<int(&&)(int, ...) noexcept>();

    test_is_not_void<void (Class::*)()>();
    test_is_not_void<void (Class::*)()&>();
    test_is_not_void<void (Class::*)() &&>();
    test_is_not_void<void (Class::*)() const>();
    test_is_not_void<void (Class::*)() const&>();
    test_is_not_void<void (Class::*)() const&&>();
    test_is_not_void<void (Class::*)() noexcept>();
    test_is_not_void<void (Class::*)()& noexcept>();
    test_is_not_void<void (Class::*)()&& noexcept>();
    test_is_not_void<void (Class::*)() const noexcept>();
    test_is_not_void<void (Class::*)() const& noexcept>();
    test_is_not_void<void (Class::*)() const&& noexcept>();

    test_is_not_void<void (Class::*)(int)>();
    test_is_not_void<void (Class::*)(int)&>();
    test_is_not_void<void (Class::*)(int) &&>();
    test_is_not_void<void (Class::*)(int) const>();
    test_is_not_void<void (Class::*)(int) const&>();
    test_is_not_void<void (Class::*)(int) const&&>();
    test_is_not_void<void (Class::*)(int) noexcept>();
    test_is_not_void<void (Class::*)(int)& noexcept>();
    test_is_not_void<void (Class::*)(int)&& noexcept>();
    test_is_not_void<void (Class::*)(int) const noexcept>();
    test_is_not_void<void (Class::*)(int) const& noexcept>();
    test_is_not_void<void (Class::*)(int) const&& noexcept>();

    test_is_not_void<void (Class::*)(...)>();
    test_is_not_void<void (Class::*)(...)&>();
    test_is_not_void<void (Class::*)(...) &&>();
    test_is_not_void<void (Class::*)(...) const>();
    test_is_not_void<void (Class::*)(...) const&>();
    test_is_not_void<void (Class::*)(...) const&&>();
    test_is_not_void<void (Class::*)(...) noexcept>();
    test_is_not_void<void (Class::*)(...)& noexcept>();
    test_is_not_void<void (Class::*)(...)&& noexcept>();
    test_is_not_void<void (Class::*)(...) const noexcept>();
    test_is_not_void<void (Class::*)(...) const& noexcept>();
    test_is_not_void<void (Class::*)(...) const&& noexcept>();

    test_is_not_void<void (Class::*)(int, ...)>();
    test_is_not_void<void (Class::*)(int, ...)&>();
    test_is_not_void<void (Class::*)(int, ...) &&>();
    test_is_not_void<void (Class::*)(int, ...) const>();
    test_is_not_void<void (Class::*)(int, ...) const&>();
    test_is_not_void<void (Class::*)(int, ...) const&&>();
    test_is_not_void<void (Class::*)(int, ...) noexcept>();
    test_is_not_void<void (Class::*)(int, ...)& noexcept>();
    test_is_not_void<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_void<void (Class::*)(int, ...) const noexcept>();
    test_is_not_void<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_void<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_void<int (Class::*)()>();
    test_is_not_void<int (Class::*)()&>();
    test_is_not_void<int (Class::*)() &&>();
    test_is_not_void<int (Class::*)() const>();
    test_is_not_void<int (Class::*)() const&>();
    test_is_not_void<int (Class::*)() const&&>();
    test_is_not_void<int (Class::*)() noexcept>();
    test_is_not_void<int (Class::*)()& noexcept>();
    test_is_not_void<int (Class::*)()&& noexcept>();
    test_is_not_void<int (Class::*)() const noexcept>();
    test_is_not_void<int (Class::*)() const& noexcept>();
    test_is_not_void<int (Class::*)() const&& noexcept>();

    test_is_not_void<int (Class::*)(int)>();
    test_is_not_void<int (Class::*)(int)&>();
    test_is_not_void<int (Class::*)(int) &&>();
    test_is_not_void<int (Class::*)(int) const>();
    test_is_not_void<int (Class::*)(int) const&>();
    test_is_not_void<int (Class::*)(int) const&&>();
    test_is_not_void<int (Class::*)(int) noexcept>();
    test_is_not_void<int (Class::*)(int)& noexcept>();
    test_is_not_void<int (Class::*)(int)&& noexcept>();
    test_is_not_void<int (Class::*)(int) const noexcept>();
    test_is_not_void<int (Class::*)(int) const& noexcept>();
    test_is_not_void<int (Class::*)(int) const&& noexcept>();

    test_is_not_void<int (Class::*)(...)>();
    test_is_not_void<int (Class::*)(...)&>();
    test_is_not_void<int (Class::*)(...) &&>();
    test_is_not_void<int (Class::*)(...) const>();
    test_is_not_void<int (Class::*)(...) const&>();
    test_is_not_void<int (Class::*)(...) const&&>();
    test_is_not_void<int (Class::*)(...) noexcept>();
    test_is_not_void<int (Class::*)(...)& noexcept>();
    test_is_not_void<int (Class::*)(...)&& noexcept>();
    test_is_not_void<int (Class::*)(...) const noexcept>();
    test_is_not_void<int (Class::*)(...) const& noexcept>();
    test_is_not_void<int (Class::*)(...) const&& noexcept>();

    test_is_not_void<int (Class::*)(int, ...)>();
    test_is_not_void<int (Class::*)(int, ...)&>();
    test_is_not_void<int (Class::*)(int, ...) &&>();
    test_is_not_void<int (Class::*)(int, ...) const>();
    test_is_not_void<int (Class::*)(int, ...) const&>();
    test_is_not_void<int (Class::*)(int, ...) const&&>();
    test_is_not_void<int (Class::*)(int, ...) noexcept>();
    test_is_not_void<int (Class::*)(int, ...)& noexcept>();
    test_is_not_void<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_void<int (Class::*)(int, ...) const noexcept>();
    test_is_not_void<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_void<int (Class::*)(int, ...) const&& noexcept>();
}
