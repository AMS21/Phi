#include <phi/test/test_macros.hpp>

#include "phi/compiler_support/char8_t.hpp"
#include "test_types.hpp"
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_array.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_lvalue_reference.hpp>
#include <phi/type_traits/is_member_function_pointer.hpp>
#include <phi/type_traits/is_member_object_pointer.hpp>
#include <phi/type_traits/is_member_pointer.hpp>
#include <phi/type_traits/is_null_pointer.hpp>
#include <phi/type_traits/is_pointer.hpp>
#include <phi/type_traits/is_reference.hpp>
#include <phi/type_traits/is_rvalue_reference.hpp>
#include <phi/type_traits/is_union.hpp>
#include <phi/type_traits/is_void.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_pointer_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<T>::value);
    STATIC_REQUIRE(phi::is_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_pointer<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<T>);
    STATIC_REQUIRE(phi::is_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);

    STATIC_REQUIRE_FALSE(phi::is_not_pointer_v<T>);
#endif

    // Standard compatibility
    STATIC_REQUIRE(std::is_pointer<T>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_pointer_v<T>);
#endif
}

template <typename T>
void test_is_pointer()
{
    test_is_pointer_impl<T>();
    test_is_pointer_impl<const T>();
    test_is_pointer_impl<volatile T>();
    test_is_pointer_impl<const volatile T>();
}

template <typename T>
void test_is_not_pointer_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_pointer<T>::value);
    STATIC_REQUIRE(phi::is_not_pointer<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<T>);
    STATIC_REQUIRE(phi::is_not_pointer_v<T>);
#endif

    // Stanard compatibility
    STATIC_REQUIRE_FALSE(std::is_pointer<T>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_pointer_v<T>);
#endif
}

template <typename T>
void test_is_not_pointer()
{
    test_is_not_pointer_impl<T>();
    test_is_not_pointer_impl<const T>();
    test_is_not_pointer_impl<volatile T>();
    test_is_not_pointer_impl<const volatile T>();
}

TEST_CASE("is_pointer")
{
    test_is_pointer<Class*>();
    test_is_pointer<Class**>();
    test_is_pointer<Abstract*>();
    test_is_pointer<incomplete_type*>();

    test_is_not_pointer<void>();
    test_is_not_pointer<phi::nullptr_t>();
    test_is_not_pointer<bool>();
    test_is_not_pointer<char>();
    test_is_not_pointer<signed char>();
    test_is_not_pointer<unsigned char>();
    test_is_not_pointer<short>();
    test_is_not_pointer<unsigned short>();
    test_is_not_pointer<int>();
    test_is_not_pointer<unsigned int>();
    test_is_not_pointer<long>();
    test_is_not_pointer<unsigned long>();
    test_is_not_pointer<long long>();
    test_is_not_pointer<unsigned long long>();
    test_is_not_pointer<float>();
    test_is_not_pointer<double>();
    test_is_not_pointer<long double>();
    test_is_not_pointer<char8_t>();
    test_is_not_pointer<char16_t>();
    test_is_not_pointer<char32_t>();
    test_is_not_pointer<wchar_t>();

    test_is_not_pointer<phi::boolean>();
    test_is_not_pointer<phi::integer<signed char>>();
    test_is_not_pointer<phi::integer<unsigned char>>();
    test_is_not_pointer<phi::integer<short>>();
    test_is_not_pointer<phi::integer<unsigned short>>();
    test_is_not_pointer<phi::integer<int>>();
    test_is_not_pointer<phi::integer<unsigned int>>();
    test_is_not_pointer<phi::integer<long>>();
    test_is_not_pointer<phi::integer<unsigned long>>();
    test_is_not_pointer<phi::integer<long long>>();
    test_is_not_pointer<phi::integer<unsigned long long>>();
    test_is_not_pointer<phi::floating_point<float>>();
    test_is_not_pointer<phi::floating_point<double>>();
    test_is_not_pointer<phi::floating_point<long double>>();

    test_is_not_pointer<std::vector<int>>();
    test_is_not_pointer<phi::scope_ptr<int>>();

    test_is_not_pointer<int&>();
    test_is_not_pointer<const int&>();
    test_is_not_pointer<volatile int&>();
    test_is_not_pointer<const volatile int&>();
    test_is_not_pointer<int&&>();
    test_is_not_pointer<const int&&>();
    test_is_not_pointer<volatile int&&>();
    test_is_not_pointer<const volatile int&&>();
    test_is_pointer<int*>();
    test_is_pointer<const int*>();
    test_is_pointer<volatile int*>();
    test_is_pointer<const volatile int*>();
    test_is_pointer<int**>();
    test_is_pointer<const int**>();
    test_is_pointer<volatile int**>();
    test_is_pointer<const volatile int**>();
    test_is_not_pointer<int*&>();
    test_is_not_pointer<const int*&>();
    test_is_not_pointer<volatile int*&>();
    test_is_not_pointer<const volatile int*&>();
    test_is_not_pointer<int*&&>();
    test_is_not_pointer<const int*&&>();
    test_is_not_pointer<volatile int*&&>();
    test_is_not_pointer<const volatile int*&&>();
    test_is_pointer<void*>();
    test_is_not_pointer<char[3]>();
    test_is_not_pointer<char[]>();
    test_is_not_pointer<char* [3]>();
    test_is_not_pointer<char*[]>();
    test_is_pointer<int(*)[3]>();
    test_is_pointer<int(*)[]>();
    test_is_not_pointer<int(&)[3]>();
    test_is_not_pointer<int(&)[]>();
    test_is_not_pointer<int(&&)[3]>();
    test_is_not_pointer<int(&&)[]>();
    test_is_not_pointer<char[3][2]>();
    test_is_not_pointer<char[][2]>();
    test_is_not_pointer<char* [3][2]>();
    test_is_not_pointer<char*[][2]>();
    test_is_pointer<int(*)[3][2]>();
    test_is_pointer<int(*)[][2]>();
    test_is_not_pointer<int(&)[3][2]>();
    test_is_not_pointer<int(&)[][2]>();
    test_is_not_pointer<int(&&)[3][2]>();
    test_is_not_pointer<int(&&)[][2]>();
    test_is_not_pointer<Class>();
    test_is_not_pointer<Class[]>();
    test_is_not_pointer<Class[2]>();
    test_is_not_pointer<Template<void>>();
    test_is_not_pointer<Template<int>>();
    test_is_not_pointer<Template<Class>>();
    test_is_not_pointer<Template<incomplete_type>>();
    test_is_not_pointer<VariadicTemplate<>>();
    test_is_not_pointer<VariadicTemplate<void>>();
    test_is_not_pointer<VariadicTemplate<int>>();
    test_is_not_pointer<VariadicTemplate<Class>>();
    test_is_not_pointer<VariadicTemplate<incomplete_type>>();
    test_is_not_pointer<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_pointer<PublicDerviedFromTemplate<Base>>();
    test_is_not_pointer<PublicDerviedFromTemplate<Derived>>();
    test_is_not_pointer<PublicDerviedFromTemplate<Class>>();
    test_is_not_pointer<PrivateDerviedFromTemplate<Base>>();
    test_is_not_pointer<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_pointer<PrivateDerviedFromTemplate<Class>>();
    test_is_not_pointer<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_pointer<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_pointer<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_pointer<Union>();
    test_is_not_pointer<NonEmptyUnion>();
    test_is_not_pointer<Empty>();
    test_is_not_pointer<NotEmpty>();
    test_is_not_pointer<bit_zero>();
    test_is_not_pointer<bit_one>();
    test_is_not_pointer<Base>();
    test_is_not_pointer<Derived>();
    test_is_not_pointer<Abstract>();
    test_is_not_pointer<PublicAbstract>();
    test_is_not_pointer<PrivateAbstract>();
    test_is_not_pointer<ProtectedAbstract>();
    test_is_not_pointer<AbstractTemplate<int>>();
    test_is_not_pointer<AbstractTemplate<double>>();
    test_is_not_pointer<AbstractTemplate<Class>>();
    test_is_not_pointer<AbstractTemplate<incomplete_type>>();
    test_is_not_pointer<Final>();
    test_is_not_pointer<PublicDestructor>();
    test_is_not_pointer<ProtectedDestructor>();
    test_is_not_pointer<PrivateDestructor>();
    test_is_not_pointer<VirtualPublicDestructor>();
    test_is_not_pointer<VirtualProtectedDestructor>();
    test_is_not_pointer<VirtualPrivateDestructor>();
    test_is_not_pointer<PurePublicDestructor>();
    test_is_not_pointer<PureProtectedDestructor>();
    test_is_not_pointer<PurePrivateDestructor>();
    test_is_not_pointer<DeletedPublicDestructor>();
    test_is_not_pointer<DeletedProtectedDestructor>();
    test_is_not_pointer<DeletedPrivateDestructor>();
    test_is_not_pointer<DeletedVirtualPublicDestructor>();
    test_is_not_pointer<DeletedVirtualProtectedDestructor>();
    test_is_not_pointer<DeletedVirtualPrivateDestructor>();
    test_is_not_pointer<Final>();
    test_is_not_pointer<Enum>();
    test_is_not_pointer<EnumSigned>();
    test_is_not_pointer<EnumUnsigned>();
    test_is_not_pointer<EnumClass>();
    test_is_not_pointer<EnumStruct>();
    test_is_not_pointer<Function>();
    test_is_pointer<FunctionPtr>();
    test_is_not_pointer<MemberObjectPtr>();
    test_is_not_pointer<MemberFunctionPtr>();
    test_is_not_pointer<incomplete_type>();
    test_is_not_pointer<IncompleteTemplate<void>>();
    test_is_not_pointer<IncompleteTemplate<int>>();
    test_is_not_pointer<IncompleteTemplate<Class>>();
    test_is_not_pointer<IncompleteTemplate<incomplete_type>>();
    test_is_not_pointer<IncompleteVariadicTemplate<>>();
    test_is_not_pointer<IncompleteVariadicTemplate<void>>();
    test_is_not_pointer<IncompleteVariadicTemplate<int>>();
    test_is_not_pointer<IncompleteVariadicTemplate<Class>>();
    test_is_not_pointer<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_pointer<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_pointer<int Class::*>();
    test_is_not_pointer<float Class::*>();
    test_is_not_pointer<void * Class::*>();
    test_is_not_pointer<int * Class::*>();
    test_is_not_pointer<int Class::*&>();
    test_is_not_pointer<float Class::*&>();
    test_is_not_pointer<void * Class::*&>();
    test_is_not_pointer<int * Class::*&>();
    test_is_not_pointer<int Class::*&&>();
    test_is_not_pointer<float Class::*&&>();
    test_is_not_pointer<void * Class::*&&>();
    test_is_not_pointer<int * Class::*&&>();
    test_is_not_pointer<int Class::*const>();
    test_is_not_pointer<float Class::*const>();
    test_is_not_pointer<void * Class::*const>();
    test_is_not_pointer<int Class::*const&>();
    test_is_not_pointer<float Class::*const&>();
    test_is_not_pointer<void * Class::*const&>();
    test_is_not_pointer<int Class::*const&&>();
    test_is_not_pointer<float Class::*const&&>();
    test_is_not_pointer<void * Class::*const&&>();
    test_is_not_pointer<int Class::*volatile>();
    test_is_not_pointer<float Class::*volatile>();
    test_is_not_pointer<void * Class::*volatile>();
    test_is_not_pointer<int Class::*volatile&>();
    test_is_not_pointer<float Class::*volatile&>();
    test_is_not_pointer<void * Class::*volatile&>();
    test_is_not_pointer<int Class::*volatile&&>();
    test_is_not_pointer<float Class::*volatile&&>();
    test_is_not_pointer<void * Class::*volatile&&>();
    test_is_not_pointer<int Class::*const volatile>();
    test_is_not_pointer<float Class::*const volatile>();
    test_is_not_pointer<void * Class::*const volatile>();
    test_is_not_pointer<int Class::*const volatile&>();
    test_is_not_pointer<float Class::*const volatile&>();
    test_is_not_pointer<void * Class::*const volatile&>();
    test_is_not_pointer<int Class::*const volatile&&>();
    test_is_not_pointer<float Class::*const volatile&&>();
    test_is_not_pointer<void * Class::*const volatile&&>();
    test_is_not_pointer<NonCopyable>();
    test_is_not_pointer<NonMoveable>();
    test_is_not_pointer<NonConstructible>();
    test_is_not_pointer<Tracked>();
    test_is_not_pointer<TrapConstructible>();
    test_is_not_pointer<TrapImplicitConversion>();
    test_is_not_pointer<TrapComma>();
    test_is_not_pointer<TrapCall>();
    test_is_not_pointer<TrapSelfAssign>();
    test_is_not_pointer<TrapDeref>();
    test_is_not_pointer<TrapArraySubscript>();

    test_is_not_pointer<void()>();
    test_is_not_pointer<void()&>();
    test_is_not_pointer<void() &&>();
    test_is_not_pointer<void() const>();
    test_is_not_pointer<void() const&>();
    test_is_not_pointer<void() const&&>();
    test_is_not_pointer<void() volatile>();
    test_is_not_pointer<void() volatile&>();
    test_is_not_pointer<void() volatile&&>();
    test_is_not_pointer<void() const volatile>();
    test_is_not_pointer<void() const volatile&>();
    test_is_not_pointer<void() const volatile&&>();
    test_is_not_pointer<void() noexcept>();
    test_is_not_pointer<void()& noexcept>();
    test_is_not_pointer<void()&& noexcept>();
    test_is_not_pointer<void() const noexcept>();
    test_is_not_pointer<void() const& noexcept>();
    test_is_not_pointer<void() const&& noexcept>();
    test_is_not_pointer<void() volatile noexcept>();
    test_is_not_pointer<void() volatile& noexcept>();
    test_is_not_pointer<void() volatile&& noexcept>();
    test_is_not_pointer<void() const volatile noexcept>();
    test_is_not_pointer<void() const volatile& noexcept>();
    test_is_not_pointer<void() const volatile&& noexcept>();

    test_is_not_pointer<void(int)>();
    test_is_not_pointer<void(int)&>();
    test_is_not_pointer<void(int) &&>();
    test_is_not_pointer<void(int) const>();
    test_is_not_pointer<void(int) const&>();
    test_is_not_pointer<void(int) const&&>();
    test_is_not_pointer<void(int) volatile>();
    test_is_not_pointer<void(int) volatile&>();
    test_is_not_pointer<void(int) volatile&&>();
    test_is_not_pointer<void(int) const volatile>();
    test_is_not_pointer<void(int) const volatile&>();
    test_is_not_pointer<void(int) const volatile&&>();
    test_is_not_pointer<void(int) noexcept>();
    test_is_not_pointer<void(int)& noexcept>();
    test_is_not_pointer<void(int)&& noexcept>();
    test_is_not_pointer<void(int) const noexcept>();
    test_is_not_pointer<void(int) const& noexcept>();
    test_is_not_pointer<void(int) const&& noexcept>();
    test_is_not_pointer<void(int) volatile noexcept>();
    test_is_not_pointer<void(int) volatile& noexcept>();
    test_is_not_pointer<void(int) volatile&& noexcept>();
    test_is_not_pointer<void(int) const volatile noexcept>();
    test_is_not_pointer<void(int) const volatile& noexcept>();
    test_is_not_pointer<void(int) const volatile&& noexcept>();

    test_is_not_pointer<void(...)>();
    test_is_not_pointer<void(...)&>();
    test_is_not_pointer<void(...) &&>();
    test_is_not_pointer<void(...) const>();
    test_is_not_pointer<void(...) const&>();
    test_is_not_pointer<void(...) const&&>();
    test_is_not_pointer<void(...) volatile>();
    test_is_not_pointer<void(...) volatile&>();
    test_is_not_pointer<void(...) volatile&&>();
    test_is_not_pointer<void(...) const volatile>();
    test_is_not_pointer<void(...) const volatile&>();
    test_is_not_pointer<void(...) const volatile&&>();
    test_is_not_pointer<void(...) noexcept>();
    test_is_not_pointer<void(...)& noexcept>();
    test_is_not_pointer<void(...)&& noexcept>();
    test_is_not_pointer<void(...) const noexcept>();
    test_is_not_pointer<void(...) const& noexcept>();
    test_is_not_pointer<void(...) const&& noexcept>();
    test_is_not_pointer<void(...) volatile noexcept>();
    test_is_not_pointer<void(...) volatile& noexcept>();
    test_is_not_pointer<void(...) volatile&& noexcept>();
    test_is_not_pointer<void(...) const volatile noexcept>();
    test_is_not_pointer<void(...) const volatile& noexcept>();
    test_is_not_pointer<void(...) const volatile&& noexcept>();

    test_is_not_pointer<void(int, ...)>();
    test_is_not_pointer<void(int, ...)&>();
    test_is_not_pointer<void(int, ...) &&>();
    test_is_not_pointer<void(int, ...) const>();
    test_is_not_pointer<void(int, ...) const&>();
    test_is_not_pointer<void(int, ...) const&&>();
    test_is_not_pointer<void(int, ...) volatile>();
    test_is_not_pointer<void(int, ...) volatile&>();
    test_is_not_pointer<void(int, ...) volatile&&>();
    test_is_not_pointer<void(int, ...) const volatile>();
    test_is_not_pointer<void(int, ...) const volatile&>();
    test_is_not_pointer<void(int, ...) const volatile&&>();
    test_is_not_pointer<void(int, ...) noexcept>();
    test_is_not_pointer<void(int, ...)& noexcept>();
    test_is_not_pointer<void(int, ...)&& noexcept>();
    test_is_not_pointer<void(int, ...) const noexcept>();
    test_is_not_pointer<void(int, ...) const& noexcept>();
    test_is_not_pointer<void(int, ...) const&& noexcept>();
    test_is_not_pointer<void(int, ...) volatile noexcept>();
    test_is_not_pointer<void(int, ...) volatile& noexcept>();
    test_is_not_pointer<void(int, ...) volatile&& noexcept>();
    test_is_not_pointer<void(int, ...) const volatile noexcept>();
    test_is_not_pointer<void(int, ...) const volatile& noexcept>();
    test_is_not_pointer<void(int, ...) const volatile&& noexcept>();

    test_is_not_pointer<int()>();
    test_is_not_pointer<int()&>();
    test_is_not_pointer<int() &&>();
    test_is_not_pointer<int() const>();
    test_is_not_pointer<int() const&>();
    test_is_not_pointer<int() const&&>();
    test_is_not_pointer<int() volatile>();
    test_is_not_pointer<int() volatile&>();
    test_is_not_pointer<int() volatile&&>();
    test_is_not_pointer<int() const volatile>();
    test_is_not_pointer<int() const volatile&>();
    test_is_not_pointer<int() const volatile&&>();
    test_is_not_pointer<int() noexcept>();
    test_is_not_pointer<int()& noexcept>();
    test_is_not_pointer<int()&& noexcept>();
    test_is_not_pointer<int() const noexcept>();
    test_is_not_pointer<int() const& noexcept>();
    test_is_not_pointer<int() const&& noexcept>();
    test_is_not_pointer<int() volatile noexcept>();
    test_is_not_pointer<int() volatile& noexcept>();
    test_is_not_pointer<int() volatile&& noexcept>();
    test_is_not_pointer<int() const volatile noexcept>();
    test_is_not_pointer<int() const volatile& noexcept>();
    test_is_not_pointer<int() const volatile&& noexcept>();

    test_is_not_pointer<int(int)>();
    test_is_not_pointer<int(int)&>();
    test_is_not_pointer<int(int) &&>();
    test_is_not_pointer<int(int) const>();
    test_is_not_pointer<int(int) const&>();
    test_is_not_pointer<int(int) const&&>();
    test_is_not_pointer<int(int) volatile>();
    test_is_not_pointer<int(int) volatile&>();
    test_is_not_pointer<int(int) volatile&&>();
    test_is_not_pointer<int(int) const volatile>();
    test_is_not_pointer<int(int) const volatile&>();
    test_is_not_pointer<int(int) const volatile&&>();
    test_is_not_pointer<int(int) noexcept>();
    test_is_not_pointer<int(int)& noexcept>();
    test_is_not_pointer<int(int)&& noexcept>();
    test_is_not_pointer<int(int) const noexcept>();
    test_is_not_pointer<int(int) const& noexcept>();
    test_is_not_pointer<int(int) const&& noexcept>();
    test_is_not_pointer<int(int) volatile noexcept>();
    test_is_not_pointer<int(int) volatile& noexcept>();
    test_is_not_pointer<int(int) volatile&& noexcept>();
    test_is_not_pointer<int(int) const volatile noexcept>();
    test_is_not_pointer<int(int) const volatile& noexcept>();
    test_is_not_pointer<int(int) const volatile&& noexcept>();

    test_is_not_pointer<int(...)>();
    test_is_not_pointer<int(...)&>();
    test_is_not_pointer<int(...) &&>();
    test_is_not_pointer<int(...) const>();
    test_is_not_pointer<int(...) const&>();
    test_is_not_pointer<int(...) const&&>();
    test_is_not_pointer<int(...) volatile>();
    test_is_not_pointer<int(...) volatile&>();
    test_is_not_pointer<int(...) volatile&&>();
    test_is_not_pointer<int(...) const volatile>();
    test_is_not_pointer<int(...) const volatile&>();
    test_is_not_pointer<int(...) const volatile&&>();
    test_is_not_pointer<int(...) noexcept>();
    test_is_not_pointer<int(...)& noexcept>();
    test_is_not_pointer<int(...)&& noexcept>();
    test_is_not_pointer<int(...) const noexcept>();
    test_is_not_pointer<int(...) const& noexcept>();
    test_is_not_pointer<int(...) const&& noexcept>();
    test_is_not_pointer<int(...) volatile noexcept>();
    test_is_not_pointer<int(...) volatile& noexcept>();
    test_is_not_pointer<int(...) volatile&& noexcept>();
    test_is_not_pointer<int(...) const volatile noexcept>();
    test_is_not_pointer<int(...) const volatile& noexcept>();
    test_is_not_pointer<int(...) const volatile&& noexcept>();

    test_is_not_pointer<int(int, ...)>();
    test_is_not_pointer<int(int, ...)&>();
    test_is_not_pointer<int(int, ...) &&>();
    test_is_not_pointer<int(int, ...) const>();
    test_is_not_pointer<int(int, ...) const&>();
    test_is_not_pointer<int(int, ...) const&&>();
    test_is_not_pointer<int(int, ...) volatile>();
    test_is_not_pointer<int(int, ...) volatile&>();
    test_is_not_pointer<int(int, ...) volatile&&>();
    test_is_not_pointer<int(int, ...) const volatile>();
    test_is_not_pointer<int(int, ...) const volatile&>();
    test_is_not_pointer<int(int, ...) const volatile&&>();
    test_is_not_pointer<int(int, ...) noexcept>();
    test_is_not_pointer<int(int, ...)& noexcept>();
    test_is_not_pointer<int(int, ...)&& noexcept>();
    test_is_not_pointer<int(int, ...) const noexcept>();
    test_is_not_pointer<int(int, ...) const& noexcept>();
    test_is_not_pointer<int(int, ...) const&& noexcept>();
    test_is_not_pointer<int(int, ...) volatile noexcept>();
    test_is_not_pointer<int(int, ...) volatile& noexcept>();
    test_is_not_pointer<int(int, ...) volatile&& noexcept>();
    test_is_not_pointer<int(int, ...) const volatile noexcept>();
    test_is_not_pointer<int(int, ...) const volatile& noexcept>();
    test_is_not_pointer<int(int, ...) const volatile&& noexcept>();

    test_is_pointer<void (*)()>();
    test_is_pointer<void (*)() noexcept>();

    test_is_pointer<void (*)(int)>();
    test_is_pointer<void (*)(int) noexcept>();

    test_is_pointer<void (*)(...)>();
    test_is_pointer<void (*)(...) noexcept>();

    test_is_pointer<void (*)(int, ...)>();
    test_is_pointer<void (*)(int, ...) noexcept>();

    test_is_pointer<int (*)()>();
    test_is_pointer<int (*)() noexcept>();

    test_is_pointer<int (*)(int)>();
    test_is_pointer<int (*)(int) noexcept>();

    test_is_pointer<int (*)(...)>();
    test_is_pointer<int (*)(...) noexcept>();

    test_is_pointer<int (*)(int, ...)>();
    test_is_pointer<int (*)(int, ...) noexcept>();

    test_is_not_pointer<void (&)()>();
    test_is_not_pointer<void (&)() noexcept>();

    test_is_not_pointer<void (&)(int)>();
    test_is_not_pointer<void (&)(int) noexcept>();

    test_is_not_pointer<void (&)(...)>();
    test_is_not_pointer<void (&)(...) noexcept>();

    test_is_not_pointer<void (&)(int, ...)>();
    test_is_not_pointer<void (&)(int, ...) noexcept>();

    test_is_not_pointer<int (&)()>();
    test_is_not_pointer<int (&)() noexcept>();

    test_is_not_pointer<int (&)(int)>();
    test_is_not_pointer<int (&)(int) noexcept>();

    test_is_not_pointer<int (&)(...)>();
    test_is_not_pointer<int (&)(...) noexcept>();

    test_is_not_pointer<int (&)(int, ...)>();
    test_is_not_pointer<int (&)(int, ...) noexcept>();

    test_is_not_pointer<void(&&)()>();
    test_is_not_pointer<void(&&)() noexcept>();

    test_is_not_pointer<void(&&)(int)>();
    test_is_not_pointer<void(&&)(int) noexcept>();

    test_is_not_pointer<void(&&)(...)>();
    test_is_not_pointer<void(&&)(...) noexcept>();

    test_is_not_pointer<void(&&)(int, ...)>();
    test_is_not_pointer<void(&&)(int, ...) noexcept>();

    test_is_not_pointer<int(&&)()>();
    test_is_not_pointer<int(&&)() noexcept>();

    test_is_not_pointer<int(&&)(int)>();
    test_is_not_pointer<int(&&)(int) noexcept>();

    test_is_not_pointer<int(&&)(...)>();
    test_is_not_pointer<int(&&)(...) noexcept>();

    test_is_not_pointer<int(&&)(int, ...)>();
    test_is_not_pointer<int(&&)(int, ...) noexcept>();

    test_is_not_pointer<void (Class::*)()>();
    test_is_not_pointer<void (Class::*)()&>();
    test_is_not_pointer<void (Class::*)() &&>();
    test_is_not_pointer<void (Class::*)() const>();
    test_is_not_pointer<void (Class::*)() const&>();
    test_is_not_pointer<void (Class::*)() const&&>();
    test_is_not_pointer<void (Class::*)() noexcept>();
    test_is_not_pointer<void (Class::*)()& noexcept>();
    test_is_not_pointer<void (Class::*)()&& noexcept>();
    test_is_not_pointer<void (Class::*)() const noexcept>();
    test_is_not_pointer<void (Class::*)() const& noexcept>();
    test_is_not_pointer<void (Class::*)() const&& noexcept>();

    test_is_not_pointer<void (Class::*)(int)>();
    test_is_not_pointer<void (Class::*)(int)&>();
    test_is_not_pointer<void (Class::*)(int) &&>();
    test_is_not_pointer<void (Class::*)(int) const>();
    test_is_not_pointer<void (Class::*)(int) const&>();
    test_is_not_pointer<void (Class::*)(int) const&&>();
    test_is_not_pointer<void (Class::*)(int) noexcept>();
    test_is_not_pointer<void (Class::*)(int)& noexcept>();
    test_is_not_pointer<void (Class::*)(int)&& noexcept>();
    test_is_not_pointer<void (Class::*)(int) const noexcept>();
    test_is_not_pointer<void (Class::*)(int) const& noexcept>();
    test_is_not_pointer<void (Class::*)(int) const&& noexcept>();

    test_is_not_pointer<void (Class::*)(...)>();
    test_is_not_pointer<void (Class::*)(...)&>();
    test_is_not_pointer<void (Class::*)(...) &&>();
    test_is_not_pointer<void (Class::*)(...) const>();
    test_is_not_pointer<void (Class::*)(...) const&>();
    test_is_not_pointer<void (Class::*)(...) const&&>();
    test_is_not_pointer<void (Class::*)(...) noexcept>();
    test_is_not_pointer<void (Class::*)(...)& noexcept>();
    test_is_not_pointer<void (Class::*)(...)&& noexcept>();
    test_is_not_pointer<void (Class::*)(...) const noexcept>();
    test_is_not_pointer<void (Class::*)(...) const& noexcept>();
    test_is_not_pointer<void (Class::*)(...) const&& noexcept>();

    test_is_not_pointer<void (Class::*)(int, ...)>();
    test_is_not_pointer<void (Class::*)(int, ...)&>();
    test_is_not_pointer<void (Class::*)(int, ...) &&>();
    test_is_not_pointer<void (Class::*)(int, ...) const>();
    test_is_not_pointer<void (Class::*)(int, ...) const&>();
    test_is_not_pointer<void (Class::*)(int, ...) const&&>();
    test_is_not_pointer<void (Class::*)(int, ...) noexcept>();
    test_is_not_pointer<void (Class::*)(int, ...)& noexcept>();
    test_is_not_pointer<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_pointer<void (Class::*)(int, ...) const noexcept>();
    test_is_not_pointer<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_pointer<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_pointer<int (Class::*)()>();
    test_is_not_pointer<int (Class::*)()&>();
    test_is_not_pointer<int (Class::*)() &&>();
    test_is_not_pointer<int (Class::*)() const>();
    test_is_not_pointer<int (Class::*)() const&>();
    test_is_not_pointer<int (Class::*)() const&&>();
    test_is_not_pointer<int (Class::*)() noexcept>();
    test_is_not_pointer<int (Class::*)()& noexcept>();
    test_is_not_pointer<int (Class::*)()&& noexcept>();
    test_is_not_pointer<int (Class::*)() const noexcept>();
    test_is_not_pointer<int (Class::*)() const& noexcept>();
    test_is_not_pointer<int (Class::*)() const&& noexcept>();

    test_is_not_pointer<int (Class::*)(int)>();
    test_is_not_pointer<int (Class::*)(int)&>();
    test_is_not_pointer<int (Class::*)(int) &&>();
    test_is_not_pointer<int (Class::*)(int) const>();
    test_is_not_pointer<int (Class::*)(int) const&>();
    test_is_not_pointer<int (Class::*)(int) const&&>();
    test_is_not_pointer<int (Class::*)(int) noexcept>();
    test_is_not_pointer<int (Class::*)(int)& noexcept>();
    test_is_not_pointer<int (Class::*)(int)&& noexcept>();
    test_is_not_pointer<int (Class::*)(int) const noexcept>();
    test_is_not_pointer<int (Class::*)(int) const& noexcept>();
    test_is_not_pointer<int (Class::*)(int) const&& noexcept>();

    test_is_not_pointer<int (Class::*)(...)>();
    test_is_not_pointer<int (Class::*)(...)&>();
    test_is_not_pointer<int (Class::*)(...) &&>();
    test_is_not_pointer<int (Class::*)(...) const>();
    test_is_not_pointer<int (Class::*)(...) const&>();
    test_is_not_pointer<int (Class::*)(...) const&&>();
    test_is_not_pointer<int (Class::*)(...) noexcept>();
    test_is_not_pointer<int (Class::*)(...)& noexcept>();
    test_is_not_pointer<int (Class::*)(...)&& noexcept>();
    test_is_not_pointer<int (Class::*)(...) const noexcept>();
    test_is_not_pointer<int (Class::*)(...) const& noexcept>();
    test_is_not_pointer<int (Class::*)(...) const&& noexcept>();

    test_is_not_pointer<int (Class::*)(int, ...)>();
    test_is_not_pointer<int (Class::*)(int, ...)&>();
    test_is_not_pointer<int (Class::*)(int, ...) &&>();
    test_is_not_pointer<int (Class::*)(int, ...) const>();
    test_is_not_pointer<int (Class::*)(int, ...) const&>();
    test_is_not_pointer<int (Class::*)(int, ...) const&&>();
    test_is_not_pointer<int (Class::*)(int, ...) noexcept>();
    test_is_not_pointer<int (Class::*)(int, ...)& noexcept>();
    test_is_not_pointer<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_pointer<int (Class::*)(int, ...) const noexcept>();
    test_is_not_pointer<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_pointer<int (Class::*)(int, ...) const&& noexcept>();
}
