#include <catch2/catch_test_macros.hpp>

#include "TestTypes.hpp"
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_arithmetic.hpp>
#include <Phi/TypeTraits/is_compound.hpp>
#include <Phi/TypeTraits/is_fundamental.hpp>
#include <Phi/TypeTraits/is_lvalue_reference.hpp>
#include <Phi/TypeTraits/is_member_function_pointer.hpp>
#include <Phi/TypeTraits/is_member_object_pointer.hpp>
#include <Phi/TypeTraits/is_null_pointer.hpp>
#include <Phi/TypeTraits/is_object.hpp>
#include <Phi/TypeTraits/is_reference.hpp>
#include <Phi/TypeTraits/is_rvalue_reference.hpp>
#include <Phi/TypeTraits/is_scalar.hpp>

template <typename T>
void test_is_member_function_pointer_imp()
{
    STATIC_REQUIRE(phi::is_member_function_pointer<T>::value);
    STATIC_REQUIRE(phi::is_member_pointer<T>::value);
    STATIC_REQUIRE(phi::is_object<T>::value);
    STATIC_REQUIRE(phi::is_scalar<T>::value);
    STATIC_REQUIRE(phi::is_compound<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_fundamental<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);

    STATIC_REQUIRE(phi::is_member_function_pointer_v<T>);
    STATIC_REQUIRE(phi::is_member_pointer_v<T>);
    STATIC_REQUIRE(phi::is_object_v<T>);
    STATIC_REQUIRE(phi::is_scalar_v<T>);
    STATIC_REQUIRE(phi::is_compound_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
}

template <typename T>
void test_is_member_function_pointer()
{
    test_is_member_function_pointer_imp<T>();
    test_is_member_function_pointer_imp<const T>();
    test_is_member_function_pointer_imp<volatile T>();
    test_is_member_function_pointer_imp<const volatile T>();
}

template <typename T>
void test_is_not_member_function_pointer()
{
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<const volatile T>::value);

    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<const volatile T>);
}

TEST_CASE("is_member_function_pointer")
{
    test_is_member_function_pointer<void (Class::*)()>();
    test_is_member_function_pointer<void (Class::*)(int)>();
    test_is_member_function_pointer<void (Class::*)(int, char)>();

    test_is_member_function_pointer<void (Class::*)()>();
    test_is_member_function_pointer<void (Class::*)(int)>();
    test_is_member_function_pointer<void (Class::*)(int, char)>();

    test_is_member_function_pointer<void (Class::*)() const>();
    test_is_member_function_pointer<void (Class::*)(int) const>();
    test_is_member_function_pointer<void (Class::*)(int, char) const>();

    test_is_member_function_pointer<void (Class::*)() volatile>();
    test_is_member_function_pointer<void (Class::*)(int) volatile>();
    test_is_member_function_pointer<void (Class::*)(int, char) volatile>();

    test_is_member_function_pointer<void (Class::*)(...)>();
    test_is_member_function_pointer<void (Class::*)(int, ...)>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...)>();

    test_is_member_function_pointer<void (Class::*)(...) const>();
    test_is_member_function_pointer<void (Class::*)(int, ...) const>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) const>();

    test_is_member_function_pointer<void (Class::*)(...) volatile>();
    test_is_member_function_pointer<void (Class::*)(int, ...) volatile>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) volatile>();

    // Noexcept qualifiers
    test_is_member_function_pointer<void (Class::*)() noexcept>();
    test_is_member_function_pointer<void (Class::*)(int) noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char) noexcept>();

    test_is_member_function_pointer<void (Class::*)() const noexcept>();
    test_is_member_function_pointer<void (Class::*)(int) const noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char) const noexcept>();

    test_is_member_function_pointer<void (Class::*)() volatile noexcept>();
    test_is_member_function_pointer<void (Class::*)(int) volatile noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char) volatile noexcept>();

    test_is_member_function_pointer<void (Class::*)(...) noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, ...) noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) noexcept>();

    test_is_member_function_pointer<void (Class::*)(...) const noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, ...) const noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) const noexcept>();

    test_is_member_function_pointer<void (Class::*)(...) volatile noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, ...) volatile noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) volatile noexcept>();

    // lvalue qualifiers
    test_is_member_function_pointer<void (Class::*)()&>();
    test_is_member_function_pointer<void (Class::*)(int)&>();
    test_is_member_function_pointer<void (Class::*)(int, char)&>();
    test_is_member_function_pointer<void (Class::*)(...)&>();
    test_is_member_function_pointer<void (Class::*)(int, ...)&>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...)&>();

    test_is_member_function_pointer<void (Class::*)() const&>();
    test_is_member_function_pointer<void (Class::*)(int) const&>();
    test_is_member_function_pointer<void (Class::*)(int, char) const&>();
    test_is_member_function_pointer<void (Class::*)(...) const&>();
    test_is_member_function_pointer<void (Class::*)(int, ...) const&>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) const&>();

    test_is_member_function_pointer<void (Class::*)() volatile&>();
    test_is_member_function_pointer<void (Class::*)(int) volatile&>();
    test_is_member_function_pointer<void (Class::*)(int, char) volatile&>();
    test_is_member_function_pointer<void (Class::*)(...) volatile&>();
    test_is_member_function_pointer<void (Class::*)(int, ...) volatile&>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) volatile&>();

    test_is_member_function_pointer<void (Class::*)() const volatile&>();
    test_is_member_function_pointer<void (Class::*)(int) const volatile&>();
    test_is_member_function_pointer<void (Class::*)(int, char) const volatile&>();
    test_is_member_function_pointer<void (Class::*)(...) const volatile&>();
    test_is_member_function_pointer<void (Class::*)(int, ...) const volatile&>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) const volatile&>();

    // Lvalue qualifiers with noexcept
    test_is_member_function_pointer<void (Class::*)()& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int)& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char)& noexcept>();
    test_is_member_function_pointer<void (Class::*)(...)& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, ...)& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...)& noexcept>();

    test_is_member_function_pointer<void (Class::*)() const& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int) const& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char) const& noexcept>();
    test_is_member_function_pointer<void (Class::*)(...) const& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, ...) const& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) const& noexcept>();

    test_is_member_function_pointer<void (Class::*)() volatile& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int) volatile& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char) volatile& noexcept>();
    test_is_member_function_pointer<void (Class::*)(...) volatile& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, ...) volatile& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) volatile& noexcept>();

    test_is_member_function_pointer<void (Class::*)() const volatile& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int) const volatile& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char) const volatile& noexcept>();
    test_is_member_function_pointer<void (Class::*)(...) const volatile& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, ...) const volatile& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) const volatile& noexcept>();

    // RValue qualifiers
    test_is_member_function_pointer<void (Class::*)() &&>();
    test_is_member_function_pointer<void (Class::*)(int) &&>();
    test_is_member_function_pointer<void (Class::*)(int, char) &&>();
    test_is_member_function_pointer<void (Class::*)(...) &&>();
    test_is_member_function_pointer<void (Class::*)(int, ...) &&>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) &&>();

    test_is_member_function_pointer<void (Class::*)() const&&>();
    test_is_member_function_pointer<void (Class::*)(int) const&&>();
    test_is_member_function_pointer<void (Class::*)(int, char) const&&>();
    test_is_member_function_pointer<void (Class::*)(...) const&&>();
    test_is_member_function_pointer<void (Class::*)(int, ...) const&&>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) const&&>();

    test_is_member_function_pointer<void (Class::*)() volatile&&>();
    test_is_member_function_pointer<void (Class::*)(int) volatile&&>();
    test_is_member_function_pointer<void (Class::*)(int, char) volatile&&>();
    test_is_member_function_pointer<void (Class::*)(...) volatile&&>();
    test_is_member_function_pointer<void (Class::*)(int, ...) volatile&&>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) volatile&&>();

    test_is_member_function_pointer<void (Class::*)() const volatile&&>();
    test_is_member_function_pointer<void (Class::*)(int) const volatile&&>();
    test_is_member_function_pointer<void (Class::*)(int, char) const volatile&&>();
    test_is_member_function_pointer<void (Class::*)(...) const volatile&&>();
    test_is_member_function_pointer<void (Class::*)(int, ...) const volatile&&>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) const volatile&&>();

    // RValue qualifiers with noexcept
    test_is_member_function_pointer<void (Class::*)()&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int)&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char)&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(...)&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, ...)&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...)&& noexcept>();

    test_is_member_function_pointer<void (Class::*)() const&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int) const&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char) const&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(...) const&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, ...) const&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) const&& noexcept>();

    test_is_member_function_pointer<void (Class::*)() volatile&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int) volatile&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char) volatile&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(...) volatile&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, ...) volatile&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) volatile&& noexcept>();

    test_is_member_function_pointer<void (Class::*)() const volatile&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int) const volatile&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char) const volatile&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(...) const volatile&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, ...) const volatile&& noexcept>();
    test_is_member_function_pointer<void (Class::*)(int, char, ...) const volatile&& noexcept>();

    test_is_member_function_pointer<MemberFunctionPtr>();

    // LWG#2582
    test_is_not_member_function_pointer<incomplete_type>();

    // Other types
    test_is_not_member_function_pointer<phi::nullptr_t>();
    test_is_not_member_function_pointer<short>();
    test_is_not_member_function_pointer<int>();
    test_is_not_member_function_pointer<float>();
    test_is_not_member_function_pointer<double>();
    test_is_not_member_function_pointer<void>();
    test_is_not_member_function_pointer<int&>();
    test_is_not_member_function_pointer<int&&>();
    test_is_not_member_function_pointer<int*>();
    test_is_not_member_function_pointer<const int*>();
    test_is_not_member_function_pointer<volatile int*>();
    test_is_not_member_function_pointer<const volatile int*>();
    test_is_not_member_function_pointer<int**>();
    test_is_not_member_function_pointer<char[3]>();
    test_is_not_member_function_pointer<char[]>();
    test_is_not_member_function_pointer<Class>();
    test_is_not_member_function_pointer<Struct>();
    test_is_not_member_function_pointer<Empty>();
    test_is_not_member_function_pointer<NotEmpty>();
    test_is_not_member_function_pointer<Union>();
    test_is_not_member_function_pointer<NonEmptyUnion>();
    test_is_not_member_function_pointer<bit_zero>();
    test_is_not_member_function_pointer<bit_one>();
    test_is_not_member_function_pointer<AbstractTemplate<int>>();
    test_is_not_member_function_pointer<AbstractTemplate<double>>();
    test_is_not_member_function_pointer<Enum>();
    test_is_not_member_function_pointer<EnumSigned>();
    test_is_not_member_function_pointer<EnumUnsigned>();
    test_is_not_member_function_pointer<EnumClass>();
    test_is_not_member_function_pointer<Function>();
    test_is_not_member_function_pointer<FunctionPtr>();
    test_is_not_member_function_pointer<MemberObjectPtr>();
    test_is_not_member_function_pointer<int Class::*>();
    test_is_not_member_function_pointer<bool Class::*>();
}
