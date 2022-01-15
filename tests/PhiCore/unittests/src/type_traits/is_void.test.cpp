#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
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
void test_is_void_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<T>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_compound<T>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
#endif
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
    STATIC_REQUIRE(phi::is_void<T>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_void<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<T>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_compound_v<T>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
#    endif
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
    STATIC_REQUIRE(phi::is_void_v<T>);

    STATIC_REQUIRE_FALSE(phi::is_not_void_v<T>);
#endif

    // Standard compatbility
    STATIC_REQUIRE(std::is_void<T>::value);
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
void test_is_not_void_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);
    STATIC_REQUIRE(phi::is_not_void<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);
    STATIC_REQUIRE(phi::is_not_void_v<T>);
#endif

    // Standard compatbility
    STATIC_REQUIRE_FALSE(std::is_void<T>::value);
}

template <typename T>
void test_is_not_void()
{
    test_is_not_void_impl<T>();
    test_is_not_void_impl<const T>();
    test_is_not_void_impl<volatile T>();
    test_is_not_void_impl<const volatile T>();
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

    test_is_not_void<phi::boolean>();
    test_is_not_void<phi::integer<signed char>>();
    test_is_not_void<phi::integer<unsigned char>>();
    test_is_not_void<phi::integer<short>>();
    test_is_not_void<phi::integer<unsigned short>>();
    test_is_not_void<phi::integer<int>>();
    test_is_not_void<phi::integer<unsigned int>>();
    test_is_not_void<phi::integer<long>>();
    test_is_not_void<phi::integer<unsigned long>>();
    test_is_not_void<phi::integer<long long>>();
    test_is_not_void<phi::integer<unsigned long long>>();
    test_is_not_void<phi::floating_point<float>>();
    test_is_not_void<phi::floating_point<double>>();
    test_is_not_void<phi::floating_point<long double>>();

    test_is_not_void<std::vector<int>>();
    test_is_not_void<phi::scope_ptr<int>>();

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
    test_is_not_void<Template<void>>();
    test_is_not_void<Template<int>>();
    test_is_not_void<Template<Class>>();
    test_is_not_void<Template<incomplete_type>>();
    test_is_not_void<VariadicTemplate<>>();
    test_is_not_void<VariadicTemplate<void>>();
    test_is_not_void<VariadicTemplate<int>>();
    test_is_not_void<VariadicTemplate<Class>>();
    test_is_not_void<VariadicTemplate<incomplete_type>>();
    test_is_not_void<VariadicTemplate<int, void, Class, volatile char[]>>();
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
    test_is_not_void<PublicAbstract>();
    test_is_not_void<PrivateAbstract>();
    test_is_not_void<ProtectedAbstract>();
    test_is_not_void<AbstractTemplate<int>>();
    test_is_not_void<AbstractTemplate<double>>();
    test_is_not_void<AbstractTemplate<Class>>();
    test_is_not_void<AbstractTemplate<incomplete_type>>();
    test_is_not_void<Final>();
    test_is_not_void<PublicDestructor>();
    test_is_not_void<ProtectedDestructor>();
    test_is_not_void<PrivateDestructor>();
    test_is_not_void<VirtualPublicDestructor>();
    test_is_not_void<VirtualProtectedDestructor>();
    test_is_not_void<VirtualPrivateDestructor>();
    test_is_not_void<PurePublicDestructor>();
    test_is_not_void<PureProtectedDestructor>();
    test_is_not_void<PurePrivateDestructor>();
    test_is_not_void<DeletedPublicDestructor>();
    test_is_not_void<DeletedProtectedDestructor>();
    test_is_not_void<DeletedPrivateDestructor>();
    test_is_not_void<DeletedVirtualPublicDestructor>();
    test_is_not_void<DeletedVirtualProtectedDestructor>();
    test_is_not_void<DeletedVirtualPrivateDestructor>();
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
    test_is_not_void<TrapDeref>();
    test_is_not_void<TrapArraySubscript>();

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
