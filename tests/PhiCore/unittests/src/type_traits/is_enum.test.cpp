#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_arithmetic.hpp>
#include <phi/type_traits/is_array.hpp>
#include <phi/type_traits/is_bool.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_compound.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_floating_point.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_fundamental.hpp>
#include <phi/type_traits/is_integer.hpp>
#include <phi/type_traits/is_integral.hpp>
#include <phi/type_traits/is_lvalue_reference.hpp>
#include <phi/type_traits/is_member_function_pointer.hpp>
#include <phi/type_traits/is_member_object_pointer.hpp>
#include <phi/type_traits/is_member_pointer.hpp>
#include <phi/type_traits/is_null_pointer.hpp>
#include <phi/type_traits/is_object.hpp>
#include <phi/type_traits/is_pointer.hpp>
#include <phi/type_traits/is_reference.hpp>
#include <phi/type_traits/is_rvalue_reference.hpp>
#include <phi/type_traits/is_scalar.hpp>
#include <phi/type_traits/is_union.hpp>
#include <phi/type_traits/is_void.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_enum_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<T>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
#endif
    STATIC_REQUIRE(phi::is_compound<T>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE(phi::is_enum<T>::value);
#endif
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
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE(phi::is_scalar<T>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_not_enum<T>::value);
#endif

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<T>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
#    endif
    STATIC_REQUIRE(phi::is_compound_v<T>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE(phi::is_enum_v<T>);
#    endif
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
#    if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
#    if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE(phi::is_scalar_v<T>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);

#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_not_enum_v<T>);
#    endif
#endif

    // Standard compatibility
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE(std::is_enum<T>::value);
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_enum_v<T>);
#    endif
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
void test_is_not_enum_impl()
{
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
    STATIC_REQUIRE(phi::is_not_enum<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
    STATIC_REQUIRE(phi::is_not_enum_v<T>);
#    endif

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_enum<T>::value);
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_enum_v<T>);
#    endif
#endif
}

template <typename T>
void test_is_not_enum()
{
    test_is_not_enum_impl<T>();
    test_is_not_enum_impl<const T>();
    test_is_not_enum_impl<volatile T>();
    test_is_not_enum_impl<const volatile T>();
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

    test_is_not_enum<phi::boolean>();
    test_is_not_enum<phi::integer<signed char>>();
    test_is_not_enum<phi::integer<unsigned char>>();
    test_is_not_enum<phi::integer<short>>();
    test_is_not_enum<phi::integer<unsigned short>>();
    test_is_not_enum<phi::integer<int>>();
    test_is_not_enum<phi::integer<unsigned int>>();
    test_is_not_enum<phi::integer<long>>();
    test_is_not_enum<phi::integer<unsigned long>>();
    test_is_not_enum<phi::integer<long long>>();
    test_is_not_enum<phi::integer<unsigned long long>>();
    test_is_not_enum<phi::floating_point<float>>();
    test_is_not_enum<phi::floating_point<double>>();
    test_is_not_enum<phi::floating_point<long double>>();

    test_is_not_enum<std::vector<int>>();
    test_is_not_enum<phi::scope_ptr<int>>();

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
    test_is_not_enum<Template<void>>();
    test_is_not_enum<Template<int>>();
    test_is_not_enum<Template<Class>>();
    test_is_not_enum<Template<IncompleteType>>();
    test_is_not_enum<VariadicTemplate<>>();
    test_is_not_enum<VariadicTemplate<void>>();
    test_is_not_enum<VariadicTemplate<int>>();
    test_is_not_enum<VariadicTemplate<Class>>();
    test_is_not_enum<VariadicTemplate<IncompleteType>>();
    test_is_not_enum<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_enum<PublicDerivedFromTemplate<Base>>();
    test_is_not_enum<PublicDerivedFromTemplate<Derived>>();
    test_is_not_enum<PublicDerivedFromTemplate<Class>>();
    test_is_not_enum<PrivateDerivedFromTemplate<Base>>();
    test_is_not_enum<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_enum<PrivateDerivedFromTemplate<Class>>();
    test_is_not_enum<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_enum<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_enum<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_enum<Union>();
    test_is_not_enum<NonEmptyUnion>();
    test_is_not_enum<Empty>();
    test_is_not_enum<NotEmpty>();
    test_is_not_enum<BitZero>();
    test_is_not_enum<BitOne>();
    test_is_not_enum<Base>();
    test_is_not_enum<Derived>();
    test_is_not_enum<Abstract>();
    test_is_not_enum<PublicAbstract>();
    test_is_not_enum<PrivateAbstract>();
    test_is_not_enum<ProtectedAbstract>();
    test_is_not_enum<AbstractTemplate<int>>();
    test_is_not_enum<AbstractTemplate<double>>();
    test_is_not_enum<AbstractTemplate<Class>>();
    test_is_not_enum<AbstractTemplate<IncompleteType>>();
    test_is_not_enum<Final>();
    test_is_not_enum<PublicDestructor>();
    test_is_not_enum<ProtectedDestructor>();
    test_is_not_enum<PrivateDestructor>();
    test_is_not_enum<VirtualPublicDestructor>();
    test_is_not_enum<VirtualProtectedDestructor>();
    test_is_not_enum<VirtualPrivateDestructor>();
    test_is_not_enum<PurePublicDestructor>();
    test_is_not_enum<PureProtectedDestructor>();
    test_is_not_enum<PurePrivateDestructor>();
    test_is_not_enum<DeletedPublicDestructor>();
    test_is_not_enum<DeletedProtectedDestructor>();
    test_is_not_enum<DeletedPrivateDestructor>();
    test_is_not_enum<DeletedVirtualPublicDestructor>();
    test_is_not_enum<DeletedVirtualProtectedDestructor>();
    test_is_not_enum<DeletedVirtualPrivateDestructor>();
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
    test_is_not_enum<IncompleteType>();
    test_is_not_enum<IncompleteTemplate<void>>();
    test_is_not_enum<IncompleteTemplate<int>>();
    test_is_not_enum<IncompleteTemplate<Class>>();
    test_is_not_enum<IncompleteTemplate<IncompleteType>>();
    test_is_not_enum<IncompleteVariadicTemplate<>>();
    test_is_not_enum<IncompleteVariadicTemplate<void>>();
    test_is_not_enum<IncompleteVariadicTemplate<int>>();
    test_is_not_enum<IncompleteVariadicTemplate<Class>>();
    test_is_not_enum<IncompleteVariadicTemplate<IncompleteType>>();
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
    test_is_not_enum<TrapDeref>();
    test_is_not_enum<TrapArraySubscript>();

    test_is_not_enum<void()>();
    test_is_not_enum<void()&>();
    test_is_not_enum<void() &&>();
    test_is_not_enum<void() const>();
    test_is_not_enum<void() const&>();
    test_is_not_enum<void() const&&>();
    test_is_not_enum<void() volatile>();
    test_is_not_enum<void() volatile&>();
    test_is_not_enum<void() volatile&&>();
    test_is_not_enum<void() const volatile>();
    test_is_not_enum<void() const volatile&>();
    test_is_not_enum<void() const volatile&&>();
    test_is_not_enum<void() noexcept>();
    test_is_not_enum<void()& noexcept>();
    test_is_not_enum<void()&& noexcept>();
    test_is_not_enum<void() const noexcept>();
    test_is_not_enum<void() const& noexcept>();
    test_is_not_enum<void() const&& noexcept>();
    test_is_not_enum<void() volatile noexcept>();
    test_is_not_enum<void() volatile& noexcept>();
    test_is_not_enum<void() volatile&& noexcept>();
    test_is_not_enum<void() const volatile noexcept>();
    test_is_not_enum<void() const volatile& noexcept>();
    test_is_not_enum<void() const volatile&& noexcept>();

    test_is_not_enum<void(int)>();
    test_is_not_enum<void(int)&>();
    test_is_not_enum<void(int) &&>();
    test_is_not_enum<void(int) const>();
    test_is_not_enum<void(int) const&>();
    test_is_not_enum<void(int) const&&>();
    test_is_not_enum<void(int) volatile>();
    test_is_not_enum<void(int) volatile&>();
    test_is_not_enum<void(int) volatile&&>();
    test_is_not_enum<void(int) const volatile>();
    test_is_not_enum<void(int) const volatile&>();
    test_is_not_enum<void(int) const volatile&&>();
    test_is_not_enum<void(int) noexcept>();
    test_is_not_enum<void(int)& noexcept>();
    test_is_not_enum<void(int)&& noexcept>();
    test_is_not_enum<void(int) const noexcept>();
    test_is_not_enum<void(int) const& noexcept>();
    test_is_not_enum<void(int) const&& noexcept>();
    test_is_not_enum<void(int) volatile noexcept>();
    test_is_not_enum<void(int) volatile& noexcept>();
    test_is_not_enum<void(int) volatile&& noexcept>();
    test_is_not_enum<void(int) const volatile noexcept>();
    test_is_not_enum<void(int) const volatile& noexcept>();
    test_is_not_enum<void(int) const volatile&& noexcept>();

    test_is_not_enum<void(...)>();
    test_is_not_enum<void(...)&>();
    test_is_not_enum<void(...) &&>();
    test_is_not_enum<void(...) const>();
    test_is_not_enum<void(...) const&>();
    test_is_not_enum<void(...) const&&>();
    test_is_not_enum<void(...) volatile>();
    test_is_not_enum<void(...) volatile&>();
    test_is_not_enum<void(...) volatile&&>();
    test_is_not_enum<void(...) const volatile>();
    test_is_not_enum<void(...) const volatile&>();
    test_is_not_enum<void(...) const volatile&&>();
    test_is_not_enum<void(...) noexcept>();
    test_is_not_enum<void(...)& noexcept>();
    test_is_not_enum<void(...)&& noexcept>();
    test_is_not_enum<void(...) const noexcept>();
    test_is_not_enum<void(...) const& noexcept>();
    test_is_not_enum<void(...) const&& noexcept>();
    test_is_not_enum<void(...) volatile noexcept>();
    test_is_not_enum<void(...) volatile& noexcept>();
    test_is_not_enum<void(...) volatile&& noexcept>();
    test_is_not_enum<void(...) const volatile noexcept>();
    test_is_not_enum<void(...) const volatile& noexcept>();
    test_is_not_enum<void(...) const volatile&& noexcept>();

    test_is_not_enum<void(int, ...)>();
    test_is_not_enum<void(int, ...)&>();
    test_is_not_enum<void(int, ...) &&>();
    test_is_not_enum<void(int, ...) const>();
    test_is_not_enum<void(int, ...) const&>();
    test_is_not_enum<void(int, ...) const&&>();
    test_is_not_enum<void(int, ...) volatile>();
    test_is_not_enum<void(int, ...) volatile&>();
    test_is_not_enum<void(int, ...) volatile&&>();
    test_is_not_enum<void(int, ...) const volatile>();
    test_is_not_enum<void(int, ...) const volatile&>();
    test_is_not_enum<void(int, ...) const volatile&&>();
    test_is_not_enum<void(int, ...) noexcept>();
    test_is_not_enum<void(int, ...)& noexcept>();
    test_is_not_enum<void(int, ...)&& noexcept>();
    test_is_not_enum<void(int, ...) const noexcept>();
    test_is_not_enum<void(int, ...) const& noexcept>();
    test_is_not_enum<void(int, ...) const&& noexcept>();
    test_is_not_enum<void(int, ...) volatile noexcept>();
    test_is_not_enum<void(int, ...) volatile& noexcept>();
    test_is_not_enum<void(int, ...) volatile&& noexcept>();
    test_is_not_enum<void(int, ...) const volatile noexcept>();
    test_is_not_enum<void(int, ...) const volatile& noexcept>();
    test_is_not_enum<void(int, ...) const volatile&& noexcept>();

    test_is_not_enum<int()>();
    test_is_not_enum<int()&>();
    test_is_not_enum<int() &&>();
    test_is_not_enum<int() const>();
    test_is_not_enum<int() const&>();
    test_is_not_enum<int() const&&>();
    test_is_not_enum<int() volatile>();
    test_is_not_enum<int() volatile&>();
    test_is_not_enum<int() volatile&&>();
    test_is_not_enum<int() const volatile>();
    test_is_not_enum<int() const volatile&>();
    test_is_not_enum<int() const volatile&&>();
    test_is_not_enum<int() noexcept>();
    test_is_not_enum<int()& noexcept>();
    test_is_not_enum<int()&& noexcept>();
    test_is_not_enum<int() const noexcept>();
    test_is_not_enum<int() const& noexcept>();
    test_is_not_enum<int() const&& noexcept>();
    test_is_not_enum<int() volatile noexcept>();
    test_is_not_enum<int() volatile& noexcept>();
    test_is_not_enum<int() volatile&& noexcept>();
    test_is_not_enum<int() const volatile noexcept>();
    test_is_not_enum<int() const volatile& noexcept>();
    test_is_not_enum<int() const volatile&& noexcept>();

    test_is_not_enum<int(int)>();
    test_is_not_enum<int(int)&>();
    test_is_not_enum<int(int) &&>();
    test_is_not_enum<int(int) const>();
    test_is_not_enum<int(int) const&>();
    test_is_not_enum<int(int) const&&>();
    test_is_not_enum<int(int) volatile>();
    test_is_not_enum<int(int) volatile&>();
    test_is_not_enum<int(int) volatile&&>();
    test_is_not_enum<int(int) const volatile>();
    test_is_not_enum<int(int) const volatile&>();
    test_is_not_enum<int(int) const volatile&&>();
    test_is_not_enum<int(int) noexcept>();
    test_is_not_enum<int(int)& noexcept>();
    test_is_not_enum<int(int)&& noexcept>();
    test_is_not_enum<int(int) const noexcept>();
    test_is_not_enum<int(int) const& noexcept>();
    test_is_not_enum<int(int) const&& noexcept>();
    test_is_not_enum<int(int) volatile noexcept>();
    test_is_not_enum<int(int) volatile& noexcept>();
    test_is_not_enum<int(int) volatile&& noexcept>();
    test_is_not_enum<int(int) const volatile noexcept>();
    test_is_not_enum<int(int) const volatile& noexcept>();
    test_is_not_enum<int(int) const volatile&& noexcept>();

    test_is_not_enum<int(...)>();
    test_is_not_enum<int(...)&>();
    test_is_not_enum<int(...) &&>();
    test_is_not_enum<int(...) const>();
    test_is_not_enum<int(...) const&>();
    test_is_not_enum<int(...) const&&>();
    test_is_not_enum<int(...) volatile>();
    test_is_not_enum<int(...) volatile&>();
    test_is_not_enum<int(...) volatile&&>();
    test_is_not_enum<int(...) const volatile>();
    test_is_not_enum<int(...) const volatile&>();
    test_is_not_enum<int(...) const volatile&&>();
    test_is_not_enum<int(...) noexcept>();
    test_is_not_enum<int(...)& noexcept>();
    test_is_not_enum<int(...)&& noexcept>();
    test_is_not_enum<int(...) const noexcept>();
    test_is_not_enum<int(...) const& noexcept>();
    test_is_not_enum<int(...) const&& noexcept>();
    test_is_not_enum<int(...) volatile noexcept>();
    test_is_not_enum<int(...) volatile& noexcept>();
    test_is_not_enum<int(...) volatile&& noexcept>();
    test_is_not_enum<int(...) const volatile noexcept>();
    test_is_not_enum<int(...) const volatile& noexcept>();
    test_is_not_enum<int(...) const volatile&& noexcept>();

    test_is_not_enum<int(int, ...)>();
    test_is_not_enum<int(int, ...)&>();
    test_is_not_enum<int(int, ...) &&>();
    test_is_not_enum<int(int, ...) const>();
    test_is_not_enum<int(int, ...) const&>();
    test_is_not_enum<int(int, ...) const&&>();
    test_is_not_enum<int(int, ...) volatile>();
    test_is_not_enum<int(int, ...) volatile&>();
    test_is_not_enum<int(int, ...) volatile&&>();
    test_is_not_enum<int(int, ...) const volatile>();
    test_is_not_enum<int(int, ...) const volatile&>();
    test_is_not_enum<int(int, ...) const volatile&&>();
    test_is_not_enum<int(int, ...) noexcept>();
    test_is_not_enum<int(int, ...)& noexcept>();
    test_is_not_enum<int(int, ...)&& noexcept>();
    test_is_not_enum<int(int, ...) const noexcept>();
    test_is_not_enum<int(int, ...) const& noexcept>();
    test_is_not_enum<int(int, ...) const&& noexcept>();
    test_is_not_enum<int(int, ...) volatile noexcept>();
    test_is_not_enum<int(int, ...) volatile& noexcept>();
    test_is_not_enum<int(int, ...) volatile&& noexcept>();
    test_is_not_enum<int(int, ...) const volatile noexcept>();
    test_is_not_enum<int(int, ...) const volatile& noexcept>();
    test_is_not_enum<int(int, ...) const volatile&& noexcept>();

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
