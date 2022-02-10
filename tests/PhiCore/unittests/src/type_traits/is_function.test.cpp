#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/extended_attributes.hpp>
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
#include <phi/type_traits/is_unsafe_floating_point.hpp>
#include <phi/type_traits/is_void.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_function_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<T>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
#endif
    STATIC_REQUIRE(phi::is_compound<T>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
#endif
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
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE_FALSE(phi::is_object<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_scalar<T>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_function<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<T>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
#    endif
    STATIC_REQUIRE(phi::is_compound_v<T>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
#    endif
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
#    if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE_FALSE(phi::is_object_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
#    if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_scalar_v<T>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);

    STATIC_REQUIRE_FALSE(phi::is_not_function_v<T>);
#endif

    // Standard compatibility
    STATIC_REQUIRE(std::is_function<T>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_function_v<T>);
#endif
}

template <typename T>
void test_is_function()
{
    test_is_function_impl<T>();
    test_is_function_impl<const T>();
    test_is_function_impl<volatile T>();
    test_is_function_impl<const volatile T>();
}

template <typename T>
void test_is_not_function_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE(phi::is_not_function<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE(phi::is_not_function_v<T>);
#endif

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_function<T>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_function_v<T>);
#endif
}

template <typename T>
void test_is_not_function()
{
    test_is_not_function_impl<T>();
    test_is_not_function_impl<const T>();
    test_is_not_function_impl<volatile T>();
    test_is_not_function_impl<const volatile T>();
}

void f()
{}

PHI_ATTRIBUTE_CONST int g()
{
    return 0;
}

TEST_CASE("is_function")
{
    test_is_function<void(void)>();
    test_is_function<int(int)>();
    test_is_function<int(int, double)>();
    test_is_function<int(int, double, float, char, bool)>();
    test_is_function<int(Abstract*)>();
    test_is_function<void(...)>();
    test_is_function<bool(...)>();
    test_is_function<decltype(f)>();
    test_is_function<decltype(g)>();

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

    test_is_not_function<phi::boolean>();
    test_is_not_function<phi::integer<signed char>>();
    test_is_not_function<phi::integer<unsigned char>>();
    test_is_not_function<phi::integer<short>>();
    test_is_not_function<phi::integer<unsigned short>>();
    test_is_not_function<phi::integer<int>>();
    test_is_not_function<phi::integer<unsigned int>>();
    test_is_not_function<phi::integer<long>>();
    test_is_not_function<phi::integer<unsigned long>>();
    test_is_not_function<phi::integer<long long>>();
    test_is_not_function<phi::integer<unsigned long long>>();
    test_is_not_function<phi::floating_point<float>>();
    test_is_not_function<phi::floating_point<double>>();
    test_is_not_function<phi::floating_point<long double>>();

    test_is_not_function<std::vector<int>>();
    test_is_not_function<phi::scope_ptr<int>>();

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
    test_is_not_function<Template<void>>();
    test_is_not_function<Template<int>>();
    test_is_not_function<Template<Class>>();
    test_is_not_function<Template<IncompleteType>>();
    test_is_not_function<VariadicTemplate<>>();
    test_is_not_function<VariadicTemplate<void>>();
    test_is_not_function<VariadicTemplate<int>>();
    test_is_not_function<VariadicTemplate<Class>>();
    test_is_not_function<VariadicTemplate<IncompleteType>>();
    test_is_not_function<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_function<PublicDerivedFromTemplate<Base>>();
    test_is_not_function<PublicDerivedFromTemplate<Derived>>();
    test_is_not_function<PublicDerivedFromTemplate<Class>>();
    test_is_not_function<PrivateDerivedFromTemplate<Base>>();
    test_is_not_function<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_function<PrivateDerivedFromTemplate<Class>>();
    test_is_not_function<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_function<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_function<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_function<Union>();
    test_is_not_function<NonEmptyUnion>();
    test_is_not_function<Empty>();
    test_is_not_function<NotEmpty>();
    test_is_not_function<BitZero>();
    test_is_not_function<BitOne>();
    test_is_not_function<Base>();
    test_is_not_function<Derived>();
    test_is_not_function<Abstract>();
    test_is_not_function<PublicAbstract>();
    test_is_not_function<PrivateAbstract>();
    test_is_not_function<ProtectedAbstract>();
    test_is_not_function<AbstractTemplate<int>>();
    test_is_not_function<AbstractTemplate<double>>();
    test_is_not_function<AbstractTemplate<Class>>();
    test_is_not_function<AbstractTemplate<IncompleteType>>();
    test_is_not_function<Final>();
    test_is_not_function<PublicDestructor>();
    test_is_not_function<ProtectedDestructor>();
    test_is_not_function<PrivateDestructor>();
    test_is_not_function<VirtualPublicDestructor>();
    test_is_not_function<VirtualProtectedDestructor>();
    test_is_not_function<VirtualPrivateDestructor>();
    test_is_not_function<PurePublicDestructor>();
    test_is_not_function<PureProtectedDestructor>();
    test_is_not_function<PurePrivateDestructor>();
    test_is_not_function<DeletedPublicDestructor>();
    test_is_not_function<DeletedProtectedDestructor>();
    test_is_not_function<DeletedPrivateDestructor>();
    test_is_not_function<DeletedVirtualPublicDestructor>();
    test_is_not_function<DeletedVirtualProtectedDestructor>();
    test_is_not_function<DeletedVirtualPrivateDestructor>();
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
    test_is_not_function<IncompleteType>();
    test_is_not_function<IncompleteTemplate<void>>();
    test_is_not_function<IncompleteTemplate<int>>();
    test_is_not_function<IncompleteTemplate<Class>>();
    test_is_not_function<IncompleteTemplate<IncompleteType>>();
    test_is_not_function<IncompleteVariadicTemplate<>>();
    test_is_not_function<IncompleteVariadicTemplate<void>>();
    test_is_not_function<IncompleteVariadicTemplate<int>>();
    test_is_not_function<IncompleteVariadicTemplate<Class>>();
    test_is_not_function<IncompleteVariadicTemplate<IncompleteType>>();
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
    test_is_not_function<TrapDeref>();
    test_is_not_function<TrapArraySubscript>();

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
