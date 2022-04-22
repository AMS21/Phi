#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_array.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_compound.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_lvalue_reference.hpp>
#include <phi/type_traits/is_member_function_pointer.hpp>
#include <phi/type_traits/is_member_object_pointer.hpp>
#include <phi/type_traits/is_member_pointer.hpp>
#include <phi/type_traits/is_null_pointer.hpp>
#include <phi/type_traits/is_object.hpp>
#include <phi/type_traits/is_pointer.hpp>
#include <phi/type_traits/is_reference.hpp>
#include <phi/type_traits/is_rvalue_reference.hpp>
#include <phi/type_traits/is_union.hpp>
#include <phi/type_traits/is_unsafe_arithmetic.hpp>
#include <phi/type_traits/is_unsafe_bool.hpp>
#include <phi/type_traits/is_unsafe_floating_point.hpp>
#include <phi/type_traits/is_unsafe_fundamental.hpp>
#include <phi/type_traits/is_unsafe_integer.hpp>
#include <phi/type_traits/is_unsafe_integral.hpp>
#include <phi/type_traits/is_unsafe_scalar.hpp>
#include <phi/type_traits/is_void.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_class_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_bool<T>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE(phi::is_class<T>::value);
#endif
    STATIC_REQUIRE(phi::is_compound<T>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
#endif
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
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
#if PHI_HAS_WORKING_IS_UNSAFE_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_scalar<T>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_not_class<T>::value);
#endif

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_unsafe_bool_v<T>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE(phi::is_class_v<T>);
#    endif
    STATIC_REQUIRE(phi::is_compound_v<T>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
#    endif
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
#    if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
#    if PHI_HAS_WORKING_IS_UNSAFE_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_scalar_v<T>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);

#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_not_class_v<T>);
#    endif
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_class<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_class<T>);

    // Standard compatibility
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE(std::is_class<T>::value);
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_class_v<T>);
#    endif
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
void test_is_not_class_impl()
{
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
    STATIC_REQUIRE(phi::is_not_class<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
    STATIC_REQUIRE(phi::is_not_class_v<T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_class<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_class<T>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_class<T>::value);
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_class_v<T>);
#    endif
#endif
}

template <typename T>
void test_is_not_class()
{
    test_is_not_class_impl<T>();
    test_is_not_class_impl<const T>();
    test_is_not_class_impl<volatile T>();
    test_is_not_class_impl<const volatile T>();
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

    test_is_class<phi::boolean>();
    test_is_class<phi::integer<signed char>>();
    test_is_class<phi::integer<unsigned char>>();
    test_is_class<phi::integer<short>>();
    test_is_class<phi::integer<unsigned short>>();
    test_is_class<phi::integer<int>>();
    test_is_class<phi::integer<unsigned int>>();
    test_is_class<phi::integer<long>>();
    test_is_class<phi::integer<unsigned long>>();
    test_is_class<phi::integer<long long>>();
    test_is_class<phi::integer<unsigned long long>>();
    test_is_class<phi::floating_point<float>>();
    test_is_class<phi::floating_point<double>>();
    test_is_class<phi::floating_point<long double>>();

    test_is_class<std::vector<int>>();
    test_is_class<phi::scope_ptr<int>>();

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
    test_is_class<Template<void>>();
    test_is_class<Template<int>>();
    test_is_class<Template<Class>>();
    test_is_class<Template<IncompleteType>>();
    test_is_class<VariadicTemplate<>>();
    test_is_class<VariadicTemplate<void>>();
    test_is_class<VariadicTemplate<int>>();
    test_is_class<VariadicTemplate<Class>>();
    test_is_class<VariadicTemplate<IncompleteType>>();
    test_is_class<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_class<PublicDerivedFromTemplate<Base>>();
    test_is_class<PublicDerivedFromTemplate<Derived>>();
    test_is_class<PublicDerivedFromTemplate<Class>>();
    test_is_class<PrivateDerivedFromTemplate<Base>>();
    test_is_class<PrivateDerivedFromTemplate<Derived>>();
    test_is_class<PrivateDerivedFromTemplate<Class>>();
    test_is_class<ProtectedDerivedFromTemplate<Base>>();
    test_is_class<ProtectedDerivedFromTemplate<Derived>>();
    test_is_class<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_class<Union>();
    test_is_not_class<NonEmptyUnion>();
    test_is_class<Empty>();
    test_is_class<NotEmpty>();
    test_is_class<BitZero>();
    test_is_class<BitOne>();
    test_is_class<Base>();
    test_is_class<Derived>();
    test_is_class<Abstract>();
    test_is_class<PublicAbstract>();
    test_is_class<PrivateAbstract>();
    test_is_class<ProtectedAbstract>();
    test_is_class<AbstractTemplate<int>>();
    test_is_class<AbstractTemplate<double>>();
    test_is_class<AbstractTemplate<Class>>();
    test_is_class<AbstractTemplate<IncompleteType>>();
    test_is_class<Final>();
    test_is_class<PublicDestructor>();
    test_is_class<ProtectedDestructor>();
    test_is_class<PrivateDestructor>();
    test_is_class<VirtualPublicDestructor>();
    test_is_class<VirtualProtectedDestructor>();
    test_is_class<VirtualPrivateDestructor>();
    test_is_class<PurePublicDestructor>();
    test_is_class<PureProtectedDestructor>();
    test_is_class<PurePrivateDestructor>();
    test_is_class<DeletedPublicDestructor>();
    test_is_class<DeletedProtectedDestructor>();
    test_is_class<DeletedPrivateDestructor>();
    test_is_class<DeletedVirtualPublicDestructor>();
    test_is_class<DeletedVirtualProtectedDestructor>();
    test_is_class<DeletedVirtualPrivateDestructor>();
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
    test_is_class<IncompleteType>();
    test_is_class<IncompleteTemplate<void>>();
    test_is_class<IncompleteTemplate<int>>();
    test_is_class<IncompleteTemplate<Class>>();
    test_is_class<IncompleteTemplate<IncompleteType>>();
    test_is_class<IncompleteVariadicTemplate<>>();
    test_is_class<IncompleteVariadicTemplate<void>>();
    test_is_class<IncompleteVariadicTemplate<int>>();
    test_is_class<IncompleteVariadicTemplate<Class>>();
    test_is_class<IncompleteVariadicTemplate<IncompleteType>>();
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
    test_is_class<TrapDeref>();
    test_is_class<TrapArraySubscript>();

    test_is_not_class<void()>();
    test_is_not_class<void()&>();
    test_is_not_class<void() &&>();
    test_is_not_class<void() const>();
    test_is_not_class<void() const&>();
    test_is_not_class<void() const&&>();
    test_is_not_class<void() volatile>();
    test_is_not_class<void() volatile&>();
    test_is_not_class<void() volatile&&>();
    test_is_not_class<void() const volatile>();
    test_is_not_class<void() const volatile&>();
    test_is_not_class<void() const volatile&&>();
    test_is_not_class<void() noexcept>();
    test_is_not_class<void()& noexcept>();
    test_is_not_class<void()&& noexcept>();
    test_is_not_class<void() const noexcept>();
    test_is_not_class<void() const& noexcept>();
    test_is_not_class<void() const&& noexcept>();
    test_is_not_class<void() volatile noexcept>();
    test_is_not_class<void() volatile& noexcept>();
    test_is_not_class<void() volatile&& noexcept>();
    test_is_not_class<void() const volatile noexcept>();
    test_is_not_class<void() const volatile& noexcept>();
    test_is_not_class<void() const volatile&& noexcept>();

    test_is_not_class<void(int)>();
    test_is_not_class<void(int)&>();
    test_is_not_class<void(int) &&>();
    test_is_not_class<void(int) const>();
    test_is_not_class<void(int) const&>();
    test_is_not_class<void(int) const&&>();
    test_is_not_class<void(int) volatile>();
    test_is_not_class<void(int) volatile&>();
    test_is_not_class<void(int) volatile&&>();
    test_is_not_class<void(int) const volatile>();
    test_is_not_class<void(int) const volatile&>();
    test_is_not_class<void(int) const volatile&&>();
    test_is_not_class<void(int) noexcept>();
    test_is_not_class<void(int)& noexcept>();
    test_is_not_class<void(int)&& noexcept>();
    test_is_not_class<void(int) const noexcept>();
    test_is_not_class<void(int) const& noexcept>();
    test_is_not_class<void(int) const&& noexcept>();
    test_is_not_class<void(int) volatile noexcept>();
    test_is_not_class<void(int) volatile& noexcept>();
    test_is_not_class<void(int) volatile&& noexcept>();
    test_is_not_class<void(int) const volatile noexcept>();
    test_is_not_class<void(int) const volatile& noexcept>();
    test_is_not_class<void(int) const volatile&& noexcept>();

    test_is_not_class<void(...)>();
    test_is_not_class<void(...)&>();
    test_is_not_class<void(...) &&>();
    test_is_not_class<void(...) const>();
    test_is_not_class<void(...) const&>();
    test_is_not_class<void(...) const&&>();
    test_is_not_class<void(...) volatile>();
    test_is_not_class<void(...) volatile&>();
    test_is_not_class<void(...) volatile&&>();
    test_is_not_class<void(...) const volatile>();
    test_is_not_class<void(...) const volatile&>();
    test_is_not_class<void(...) const volatile&&>();
    test_is_not_class<void(...) noexcept>();
    test_is_not_class<void(...)& noexcept>();
    test_is_not_class<void(...)&& noexcept>();
    test_is_not_class<void(...) const noexcept>();
    test_is_not_class<void(...) const& noexcept>();
    test_is_not_class<void(...) const&& noexcept>();
    test_is_not_class<void(...) volatile noexcept>();
    test_is_not_class<void(...) volatile& noexcept>();
    test_is_not_class<void(...) volatile&& noexcept>();
    test_is_not_class<void(...) const volatile noexcept>();
    test_is_not_class<void(...) const volatile& noexcept>();
    test_is_not_class<void(...) const volatile&& noexcept>();

    test_is_not_class<void(int, ...)>();
    test_is_not_class<void(int, ...)&>();
    test_is_not_class<void(int, ...) &&>();
    test_is_not_class<void(int, ...) const>();
    test_is_not_class<void(int, ...) const&>();
    test_is_not_class<void(int, ...) const&&>();
    test_is_not_class<void(int, ...) volatile>();
    test_is_not_class<void(int, ...) volatile&>();
    test_is_not_class<void(int, ...) volatile&&>();
    test_is_not_class<void(int, ...) const volatile>();
    test_is_not_class<void(int, ...) const volatile&>();
    test_is_not_class<void(int, ...) const volatile&&>();
    test_is_not_class<void(int, ...) noexcept>();
    test_is_not_class<void(int, ...)& noexcept>();
    test_is_not_class<void(int, ...)&& noexcept>();
    test_is_not_class<void(int, ...) const noexcept>();
    test_is_not_class<void(int, ...) const& noexcept>();
    test_is_not_class<void(int, ...) const&& noexcept>();
    test_is_not_class<void(int, ...) volatile noexcept>();
    test_is_not_class<void(int, ...) volatile& noexcept>();
    test_is_not_class<void(int, ...) volatile&& noexcept>();
    test_is_not_class<void(int, ...) const volatile noexcept>();
    test_is_not_class<void(int, ...) const volatile& noexcept>();
    test_is_not_class<void(int, ...) const volatile&& noexcept>();

    test_is_not_class<int()>();
    test_is_not_class<int()&>();
    test_is_not_class<int() &&>();
    test_is_not_class<int() const>();
    test_is_not_class<int() const&>();
    test_is_not_class<int() const&&>();
    test_is_not_class<int() volatile>();
    test_is_not_class<int() volatile&>();
    test_is_not_class<int() volatile&&>();
    test_is_not_class<int() const volatile>();
    test_is_not_class<int() const volatile&>();
    test_is_not_class<int() const volatile&&>();
    test_is_not_class<int() noexcept>();
    test_is_not_class<int()& noexcept>();
    test_is_not_class<int()&& noexcept>();
    test_is_not_class<int() const noexcept>();
    test_is_not_class<int() const& noexcept>();
    test_is_not_class<int() const&& noexcept>();
    test_is_not_class<int() volatile noexcept>();
    test_is_not_class<int() volatile& noexcept>();
    test_is_not_class<int() volatile&& noexcept>();
    test_is_not_class<int() const volatile noexcept>();
    test_is_not_class<int() const volatile& noexcept>();
    test_is_not_class<int() const volatile&& noexcept>();

    test_is_not_class<int(int)>();
    test_is_not_class<int(int)&>();
    test_is_not_class<int(int) &&>();
    test_is_not_class<int(int) const>();
    test_is_not_class<int(int) const&>();
    test_is_not_class<int(int) const&&>();
    test_is_not_class<int(int) volatile>();
    test_is_not_class<int(int) volatile&>();
    test_is_not_class<int(int) volatile&&>();
    test_is_not_class<int(int) const volatile>();
    test_is_not_class<int(int) const volatile&>();
    test_is_not_class<int(int) const volatile&&>();
    test_is_not_class<int(int) noexcept>();
    test_is_not_class<int(int)& noexcept>();
    test_is_not_class<int(int)&& noexcept>();
    test_is_not_class<int(int) const noexcept>();
    test_is_not_class<int(int) const& noexcept>();
    test_is_not_class<int(int) const&& noexcept>();
    test_is_not_class<int(int) volatile noexcept>();
    test_is_not_class<int(int) volatile& noexcept>();
    test_is_not_class<int(int) volatile&& noexcept>();
    test_is_not_class<int(int) const volatile noexcept>();
    test_is_not_class<int(int) const volatile& noexcept>();
    test_is_not_class<int(int) const volatile&& noexcept>();

    test_is_not_class<int(...)>();
    test_is_not_class<int(...)&>();
    test_is_not_class<int(...) &&>();
    test_is_not_class<int(...) const>();
    test_is_not_class<int(...) const&>();
    test_is_not_class<int(...) const&&>();
    test_is_not_class<int(...) volatile>();
    test_is_not_class<int(...) volatile&>();
    test_is_not_class<int(...) volatile&&>();
    test_is_not_class<int(...) const volatile>();
    test_is_not_class<int(...) const volatile&>();
    test_is_not_class<int(...) const volatile&&>();
    test_is_not_class<int(...) noexcept>();
    test_is_not_class<int(...)& noexcept>();
    test_is_not_class<int(...)&& noexcept>();
    test_is_not_class<int(...) const noexcept>();
    test_is_not_class<int(...) const& noexcept>();
    test_is_not_class<int(...) const&& noexcept>();
    test_is_not_class<int(...) volatile noexcept>();
    test_is_not_class<int(...) volatile& noexcept>();
    test_is_not_class<int(...) volatile&& noexcept>();
    test_is_not_class<int(...) const volatile noexcept>();
    test_is_not_class<int(...) const volatile& noexcept>();
    test_is_not_class<int(...) const volatile&& noexcept>();

    test_is_not_class<int(int, ...)>();
    test_is_not_class<int(int, ...)&>();
    test_is_not_class<int(int, ...) &&>();
    test_is_not_class<int(int, ...) const>();
    test_is_not_class<int(int, ...) const&>();
    test_is_not_class<int(int, ...) const&&>();
    test_is_not_class<int(int, ...) volatile>();
    test_is_not_class<int(int, ...) volatile&>();
    test_is_not_class<int(int, ...) volatile&&>();
    test_is_not_class<int(int, ...) const volatile>();
    test_is_not_class<int(int, ...) const volatile&>();
    test_is_not_class<int(int, ...) const volatile&&>();
    test_is_not_class<int(int, ...) noexcept>();
    test_is_not_class<int(int, ...)& noexcept>();
    test_is_not_class<int(int, ...)&& noexcept>();
    test_is_not_class<int(int, ...) const noexcept>();
    test_is_not_class<int(int, ...) const& noexcept>();
    test_is_not_class<int(int, ...) const&& noexcept>();
    test_is_not_class<int(int, ...) volatile noexcept>();
    test_is_not_class<int(int, ...) volatile& noexcept>();
    test_is_not_class<int(int, ...) volatile&& noexcept>();
    test_is_not_class<int(int, ...) const volatile noexcept>();
    test_is_not_class<int(int, ...) const volatile& noexcept>();
    test_is_not_class<int(int, ...) const volatile&& noexcept>();

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
