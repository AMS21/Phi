#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_arithmetic.hpp>
#include <phi/type_traits/is_array.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_compound.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_floating_point.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_fundamental.hpp>
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
void test_is_member_object_pointer_imp()
{
    STATIC_REQUIRE(phi::is_member_object_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_member_object_pointer<T>::value);
    STATIC_REQUIRE(phi::is_member_pointer<T>::value);
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object<T>::value);
#endif
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE(phi::is_scalar<T>::value);
#endif
    STATIC_REQUIRE(phi::is_compound<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_void<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_floating_point<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<T>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
#endif
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_fundamental<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_member_object_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_member_object_pointer_v<T>);
    STATIC_REQUIRE(phi::is_member_pointer_v<T>);
#    if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object_v<T>);
#    endif
#    if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE(phi::is_scalar_v<T>);
#    endif
    STATIC_REQUIRE(phi::is_compound_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_void_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_floating_point_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<T>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
#    endif
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<T>);
#endif

    // Standard compatbililty
    STATIC_REQUIRE(std::is_member_object_pointer<T>::value);
}

template <typename T>
void test_is_member_object_pointer()
{
    test_is_member_object_pointer_imp<T>();
    test_is_member_object_pointer_imp<const T>();
    test_is_member_object_pointer_imp<volatile T>();
    test_is_member_object_pointer_imp<const volatile T>();
}

template <typename T>
void test_is_not_member_object_pointer_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<T>::value);
    STATIC_REQUIRE(phi::is_not_member_object_pointer<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<T>);
    STATIC_REQUIRE(phi::is_not_member_object_pointer_v<T>);
#endif

    // Standard compatbililty
    STATIC_REQUIRE_FALSE(std::is_member_object_pointer<T>::value);
}

template <typename T>
void test_is_not_member_object_pointer()
{
    test_is_not_member_object_pointer_impl<T>();
    test_is_not_member_object_pointer_impl<const T>();
    test_is_not_member_object_pointer_impl<volatile T>();
    test_is_not_member_object_pointer_impl<const volatile T>();
}

TEST_CASE("is_member_object_pointer")
{
    test_is_member_object_pointer<int Abstract::*>();
    test_is_member_object_pointer<double NotEmpty::*>();
    test_is_member_object_pointer<FunctionPtr Empty::*>();
    test_is_member_object_pointer<int Class::*>();
    test_is_member_object_pointer<int Class::*>();
    test_is_member_object_pointer<MemberObjectPtr>();

    test_is_not_member_object_pointer<void>();
    test_is_not_member_object_pointer<phi::nullptr_t>();
    test_is_not_member_object_pointer<bool>();
    test_is_not_member_object_pointer<char>();
    test_is_not_member_object_pointer<signed char>();
    test_is_not_member_object_pointer<unsigned char>();
    test_is_not_member_object_pointer<short>();
    test_is_not_member_object_pointer<unsigned short>();
    test_is_not_member_object_pointer<int>();
    test_is_not_member_object_pointer<unsigned int>();
    test_is_not_member_object_pointer<long>();
    test_is_not_member_object_pointer<unsigned long>();
    test_is_not_member_object_pointer<long long>();
    test_is_not_member_object_pointer<unsigned long long>();
    test_is_not_member_object_pointer<float>();
    test_is_not_member_object_pointer<double>();
    test_is_not_member_object_pointer<long double>();
    test_is_not_member_object_pointer<char8_t>();
    test_is_not_member_object_pointer<char16_t>();
    test_is_not_member_object_pointer<char32_t>();
    test_is_not_member_object_pointer<wchar_t>();

    test_is_not_member_object_pointer<phi::boolean>();
    test_is_not_member_object_pointer<phi::integer<signed char>>();
    test_is_not_member_object_pointer<phi::integer<unsigned char>>();
    test_is_not_member_object_pointer<phi::integer<short>>();
    test_is_not_member_object_pointer<phi::integer<unsigned short>>();
    test_is_not_member_object_pointer<phi::integer<int>>();
    test_is_not_member_object_pointer<phi::integer<unsigned int>>();
    test_is_not_member_object_pointer<phi::integer<long>>();
    test_is_not_member_object_pointer<phi::integer<unsigned long>>();
    test_is_not_member_object_pointer<phi::integer<long long>>();
    test_is_not_member_object_pointer<phi::integer<unsigned long long>>();
    test_is_not_member_object_pointer<phi::floating_point<float>>();
    test_is_not_member_object_pointer<phi::floating_point<double>>();
    test_is_not_member_object_pointer<phi::floating_point<long double>>();

    test_is_not_member_object_pointer<std::vector<int>>();
    test_is_not_member_object_pointer<phi::scope_ptr<int>>();

    test_is_not_member_object_pointer<int&>();
    test_is_not_member_object_pointer<const int&>();
    test_is_not_member_object_pointer<volatile int&>();
    test_is_not_member_object_pointer<const volatile int&>();
    test_is_not_member_object_pointer<int&&>();
    test_is_not_member_object_pointer<const int&&>();
    test_is_not_member_object_pointer<volatile int&&>();
    test_is_not_member_object_pointer<const volatile int&&>();
    test_is_not_member_object_pointer<int*>();
    test_is_not_member_object_pointer<const int*>();
    test_is_not_member_object_pointer<volatile int*>();
    test_is_not_member_object_pointer<const volatile int*>();
    test_is_not_member_object_pointer<int**>();
    test_is_not_member_object_pointer<const int**>();
    test_is_not_member_object_pointer<volatile int**>();
    test_is_not_member_object_pointer<const volatile int**>();
    test_is_not_member_object_pointer<int*&>();
    test_is_not_member_object_pointer<const int*&>();
    test_is_not_member_object_pointer<volatile int*&>();
    test_is_not_member_object_pointer<const volatile int*&>();
    test_is_not_member_object_pointer<int*&&>();
    test_is_not_member_object_pointer<const int*&&>();
    test_is_not_member_object_pointer<volatile int*&&>();
    test_is_not_member_object_pointer<const volatile int*&&>();
    test_is_not_member_object_pointer<void*>();
    test_is_not_member_object_pointer<char[3]>();
    test_is_not_member_object_pointer<char[]>();
    test_is_not_member_object_pointer<char* [3]>();
    test_is_not_member_object_pointer<char*[]>();
    test_is_not_member_object_pointer<int(*)[3]>();
    test_is_not_member_object_pointer<int(*)[]>();
    test_is_not_member_object_pointer<int(&)[3]>();
    test_is_not_member_object_pointer<int(&)[]>();
    test_is_not_member_object_pointer<int(&&)[3]>();
    test_is_not_member_object_pointer<int(&&)[]>();
    test_is_not_member_object_pointer<char[3][2]>();
    test_is_not_member_object_pointer<char[][2]>();
    test_is_not_member_object_pointer<char* [3][2]>();
    test_is_not_member_object_pointer<char*[][2]>();
    test_is_not_member_object_pointer<int(*)[3][2]>();
    test_is_not_member_object_pointer<int(*)[][2]>();
    test_is_not_member_object_pointer<int(&)[3][2]>();
    test_is_not_member_object_pointer<int(&)[][2]>();
    test_is_not_member_object_pointer<int(&&)[3][2]>();
    test_is_not_member_object_pointer<int(&&)[][2]>();
    test_is_not_member_object_pointer<Class>();
    test_is_not_member_object_pointer<Class[]>();
    test_is_not_member_object_pointer<Class[2]>();
    test_is_not_member_object_pointer<Template<void>>();
    test_is_not_member_object_pointer<Template<int>>();
    test_is_not_member_object_pointer<Template<Class>>();
    test_is_not_member_object_pointer<Template<IncompleteType>>();
    test_is_not_member_object_pointer<VariadicTemplate<>>();
    test_is_not_member_object_pointer<VariadicTemplate<void>>();
    test_is_not_member_object_pointer<VariadicTemplate<int>>();
    test_is_not_member_object_pointer<VariadicTemplate<Class>>();
    test_is_not_member_object_pointer<VariadicTemplate<IncompleteType>>();
    test_is_not_member_object_pointer<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_member_object_pointer<PublicDerivedFromTemplate<Base>>();
    test_is_not_member_object_pointer<PublicDerivedFromTemplate<Derived>>();
    test_is_not_member_object_pointer<PublicDerivedFromTemplate<Class>>();
    test_is_not_member_object_pointer<PrivateDerivedFromTemplate<Base>>();
    test_is_not_member_object_pointer<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_member_object_pointer<PrivateDerivedFromTemplate<Class>>();
    test_is_not_member_object_pointer<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_member_object_pointer<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_member_object_pointer<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_member_object_pointer<Union>();
    test_is_not_member_object_pointer<NonEmptyUnion>();
    test_is_not_member_object_pointer<Empty>();
    test_is_not_member_object_pointer<NotEmpty>();
    test_is_not_member_object_pointer<BitZero>();
    test_is_not_member_object_pointer<BitOne>();
    test_is_not_member_object_pointer<Base>();
    test_is_not_member_object_pointer<Derived>();
    test_is_not_member_object_pointer<Abstract>();
    test_is_not_member_object_pointer<PublicAbstract>();
    test_is_not_member_object_pointer<PrivateAbstract>();
    test_is_not_member_object_pointer<ProtectedAbstract>();
    test_is_not_member_object_pointer<AbstractTemplate<int>>();
    test_is_not_member_object_pointer<AbstractTemplate<double>>();
    test_is_not_member_object_pointer<AbstractTemplate<Class>>();
    test_is_not_member_object_pointer<AbstractTemplate<IncompleteType>>();
    test_is_not_member_object_pointer<Final>();
    test_is_not_member_object_pointer<PublicDestructor>();
    test_is_not_member_object_pointer<ProtectedDestructor>();
    test_is_not_member_object_pointer<PrivateDestructor>();
    test_is_not_member_object_pointer<VirtualPublicDestructor>();
    test_is_not_member_object_pointer<VirtualProtectedDestructor>();
    test_is_not_member_object_pointer<VirtualPrivateDestructor>();
    test_is_not_member_object_pointer<PurePublicDestructor>();
    test_is_not_member_object_pointer<PureProtectedDestructor>();
    test_is_not_member_object_pointer<PurePrivateDestructor>();
    test_is_not_member_object_pointer<DeletedPublicDestructor>();
    test_is_not_member_object_pointer<DeletedProtectedDestructor>();
    test_is_not_member_object_pointer<DeletedPrivateDestructor>();
    test_is_not_member_object_pointer<DeletedVirtualPublicDestructor>();
    test_is_not_member_object_pointer<DeletedVirtualProtectedDestructor>();
    test_is_not_member_object_pointer<DeletedVirtualPrivateDestructor>();
    test_is_not_member_object_pointer<Enum>();
    test_is_not_member_object_pointer<EnumSigned>();
    test_is_not_member_object_pointer<EnumUnsigned>();
    test_is_not_member_object_pointer<EnumClass>();
    test_is_not_member_object_pointer<EnumStruct>();
    test_is_not_member_object_pointer<Function>();
    test_is_not_member_object_pointer<FunctionPtr>();
    test_is_member_object_pointer<MemberObjectPtr>();
    test_is_not_member_object_pointer<MemberFunctionPtr>();
    test_is_not_member_object_pointer<IncompleteType>();
    test_is_not_member_object_pointer<IncompleteTemplate<void>>();
    test_is_not_member_object_pointer<IncompleteTemplate<int>>();
    test_is_not_member_object_pointer<IncompleteTemplate<Class>>();
    test_is_not_member_object_pointer<IncompleteTemplate<IncompleteType>>();
    test_is_not_member_object_pointer<IncompleteVariadicTemplate<>>();
    test_is_not_member_object_pointer<IncompleteVariadicTemplate<void>>();
    test_is_not_member_object_pointer<IncompleteVariadicTemplate<int>>();
    test_is_not_member_object_pointer<IncompleteVariadicTemplate<Class>>();
    test_is_not_member_object_pointer<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_member_object_pointer<
            IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_member_object_pointer<int Class::*>();
    test_is_member_object_pointer<float Class::*>();
    test_is_member_object_pointer<void * Class::*>();
    test_is_member_object_pointer<int * Class::*>();
    test_is_not_member_object_pointer<int Class::*&>();
    test_is_not_member_object_pointer<float Class::*&>();
    test_is_not_member_object_pointer<void * Class::*&>();
    test_is_not_member_object_pointer<int * Class::*&>();
    test_is_not_member_object_pointer<int Class::*&&>();
    test_is_not_member_object_pointer<float Class::*&&>();
    test_is_not_member_object_pointer<void * Class::*&&>();
    test_is_not_member_object_pointer<int * Class::*&&>();
    test_is_member_object_pointer<int Class::*const>();
    test_is_member_object_pointer<float Class::*const>();
    test_is_member_object_pointer<void * Class::*const>();
    test_is_not_member_object_pointer<int Class::*const&>();
    test_is_not_member_object_pointer<float Class::*const&>();
    test_is_not_member_object_pointer<void * Class::*const&>();
    test_is_not_member_object_pointer<int Class::*const&&>();
    test_is_not_member_object_pointer<float Class::*const&&>();
    test_is_not_member_object_pointer<void * Class::*const&&>();
    test_is_member_object_pointer<int Class::*volatile>();
    test_is_member_object_pointer<float Class::*volatile>();
    test_is_member_object_pointer<void * Class::*volatile>();
    test_is_not_member_object_pointer<int Class::*volatile&>();
    test_is_not_member_object_pointer<float Class::*volatile&>();
    test_is_not_member_object_pointer<void * Class::*volatile&>();
    test_is_not_member_object_pointer<int Class::*volatile&&>();
    test_is_not_member_object_pointer<float Class::*volatile&&>();
    test_is_not_member_object_pointer<void * Class::*volatile&&>();
    test_is_member_object_pointer<int Class::*const volatile>();
    test_is_member_object_pointer<float Class::*const volatile>();
    test_is_member_object_pointer<void * Class::*const volatile>();
    test_is_not_member_object_pointer<int Class::*const volatile&>();
    test_is_not_member_object_pointer<float Class::*const volatile&>();
    test_is_not_member_object_pointer<void * Class::*const volatile&>();
    test_is_not_member_object_pointer<int Class::*const volatile&&>();
    test_is_not_member_object_pointer<float Class::*const volatile&&>();
    test_is_not_member_object_pointer<void * Class::*const volatile&&>();
    test_is_not_member_object_pointer<NonCopyable>();
    test_is_not_member_object_pointer<NonMoveable>();
    test_is_not_member_object_pointer<NonConstructible>();
    test_is_not_member_object_pointer<Tracked>();
    test_is_not_member_object_pointer<TrapConstructible>();
    test_is_not_member_object_pointer<TrapImplicitConversion>();
    test_is_not_member_object_pointer<TrapComma>();
    test_is_not_member_object_pointer<TrapCall>();
    test_is_not_member_object_pointer<TrapSelfAssign>();
    test_is_not_member_object_pointer<TrapDeref>();
    test_is_not_member_object_pointer<TrapArraySubscript>();

    test_is_not_member_object_pointer<void()>();
    test_is_not_member_object_pointer<void()&>();
    test_is_not_member_object_pointer<void() &&>();
    test_is_not_member_object_pointer<void() const>();
    test_is_not_member_object_pointer<void() const&>();
    test_is_not_member_object_pointer<void() const&&>();
    test_is_not_member_object_pointer<void() volatile>();
    test_is_not_member_object_pointer<void() volatile&>();
    test_is_not_member_object_pointer<void() volatile&&>();
    test_is_not_member_object_pointer<void() const volatile>();
    test_is_not_member_object_pointer<void() const volatile&>();
    test_is_not_member_object_pointer<void() const volatile&&>();
    test_is_not_member_object_pointer<void() noexcept>();
    test_is_not_member_object_pointer<void()& noexcept>();
    test_is_not_member_object_pointer<void()&& noexcept>();
    test_is_not_member_object_pointer<void() const noexcept>();
    test_is_not_member_object_pointer<void() const& noexcept>();
    test_is_not_member_object_pointer<void() const&& noexcept>();
    test_is_not_member_object_pointer<void() volatile noexcept>();
    test_is_not_member_object_pointer<void() volatile& noexcept>();
    test_is_not_member_object_pointer<void() volatile&& noexcept>();
    test_is_not_member_object_pointer<void() const volatile noexcept>();
    test_is_not_member_object_pointer<void() const volatile& noexcept>();
    test_is_not_member_object_pointer<void() const volatile&& noexcept>();

    test_is_not_member_object_pointer<void(int)>();
    test_is_not_member_object_pointer<void(int)&>();
    test_is_not_member_object_pointer<void(int) &&>();
    test_is_not_member_object_pointer<void(int) const>();
    test_is_not_member_object_pointer<void(int) const&>();
    test_is_not_member_object_pointer<void(int) const&&>();
    test_is_not_member_object_pointer<void(int) volatile>();
    test_is_not_member_object_pointer<void(int) volatile&>();
    test_is_not_member_object_pointer<void(int) volatile&&>();
    test_is_not_member_object_pointer<void(int) const volatile>();
    test_is_not_member_object_pointer<void(int) const volatile&>();
    test_is_not_member_object_pointer<void(int) const volatile&&>();
    test_is_not_member_object_pointer<void(int) noexcept>();
    test_is_not_member_object_pointer<void(int)& noexcept>();
    test_is_not_member_object_pointer<void(int)&& noexcept>();
    test_is_not_member_object_pointer<void(int) const noexcept>();
    test_is_not_member_object_pointer<void(int) const& noexcept>();
    test_is_not_member_object_pointer<void(int) const&& noexcept>();
    test_is_not_member_object_pointer<void(int) volatile noexcept>();
    test_is_not_member_object_pointer<void(int) volatile& noexcept>();
    test_is_not_member_object_pointer<void(int) volatile&& noexcept>();
    test_is_not_member_object_pointer<void(int) const volatile noexcept>();
    test_is_not_member_object_pointer<void(int) const volatile& noexcept>();
    test_is_not_member_object_pointer<void(int) const volatile&& noexcept>();

    test_is_not_member_object_pointer<void(...)>();
    test_is_not_member_object_pointer<void(...)&>();
    test_is_not_member_object_pointer<void(...) &&>();
    test_is_not_member_object_pointer<void(...) const>();
    test_is_not_member_object_pointer<void(...) const&>();
    test_is_not_member_object_pointer<void(...) const&&>();
    test_is_not_member_object_pointer<void(...) volatile>();
    test_is_not_member_object_pointer<void(...) volatile&>();
    test_is_not_member_object_pointer<void(...) volatile&&>();
    test_is_not_member_object_pointer<void(...) const volatile>();
    test_is_not_member_object_pointer<void(...) const volatile&>();
    test_is_not_member_object_pointer<void(...) const volatile&&>();
    test_is_not_member_object_pointer<void(...) noexcept>();
    test_is_not_member_object_pointer<void(...)& noexcept>();
    test_is_not_member_object_pointer<void(...)&& noexcept>();
    test_is_not_member_object_pointer<void(...) const noexcept>();
    test_is_not_member_object_pointer<void(...) const& noexcept>();
    test_is_not_member_object_pointer<void(...) const&& noexcept>();
    test_is_not_member_object_pointer<void(...) volatile noexcept>();
    test_is_not_member_object_pointer<void(...) volatile& noexcept>();
    test_is_not_member_object_pointer<void(...) volatile&& noexcept>();
    test_is_not_member_object_pointer<void(...) const volatile noexcept>();
    test_is_not_member_object_pointer<void(...) const volatile& noexcept>();
    test_is_not_member_object_pointer<void(...) const volatile&& noexcept>();

    test_is_not_member_object_pointer<void(int, ...)>();
    test_is_not_member_object_pointer<void(int, ...)&>();
    test_is_not_member_object_pointer<void(int, ...) &&>();
    test_is_not_member_object_pointer<void(int, ...) const>();
    test_is_not_member_object_pointer<void(int, ...) const&>();
    test_is_not_member_object_pointer<void(int, ...) const&&>();
    test_is_not_member_object_pointer<void(int, ...) volatile>();
    test_is_not_member_object_pointer<void(int, ...) volatile&>();
    test_is_not_member_object_pointer<void(int, ...) volatile&&>();
    test_is_not_member_object_pointer<void(int, ...) const volatile>();
    test_is_not_member_object_pointer<void(int, ...) const volatile&>();
    test_is_not_member_object_pointer<void(int, ...) const volatile&&>();
    test_is_not_member_object_pointer<void(int, ...) noexcept>();
    test_is_not_member_object_pointer<void(int, ...)& noexcept>();
    test_is_not_member_object_pointer<void(int, ...)&& noexcept>();
    test_is_not_member_object_pointer<void(int, ...) const noexcept>();
    test_is_not_member_object_pointer<void(int, ...) const& noexcept>();
    test_is_not_member_object_pointer<void(int, ...) const&& noexcept>();
    test_is_not_member_object_pointer<void(int, ...) volatile noexcept>();
    test_is_not_member_object_pointer<void(int, ...) volatile& noexcept>();
    test_is_not_member_object_pointer<void(int, ...) volatile&& noexcept>();
    test_is_not_member_object_pointer<void(int, ...) const volatile noexcept>();
    test_is_not_member_object_pointer<void(int, ...) const volatile& noexcept>();
    test_is_not_member_object_pointer<void(int, ...) const volatile&& noexcept>();

    test_is_not_member_object_pointer<int()>();
    test_is_not_member_object_pointer<int()&>();
    test_is_not_member_object_pointer<int() &&>();
    test_is_not_member_object_pointer<int() const>();
    test_is_not_member_object_pointer<int() const&>();
    test_is_not_member_object_pointer<int() const&&>();
    test_is_not_member_object_pointer<int() volatile>();
    test_is_not_member_object_pointer<int() volatile&>();
    test_is_not_member_object_pointer<int() volatile&&>();
    test_is_not_member_object_pointer<int() const volatile>();
    test_is_not_member_object_pointer<int() const volatile&>();
    test_is_not_member_object_pointer<int() const volatile&&>();
    test_is_not_member_object_pointer<int() noexcept>();
    test_is_not_member_object_pointer<int()& noexcept>();
    test_is_not_member_object_pointer<int()&& noexcept>();
    test_is_not_member_object_pointer<int() const noexcept>();
    test_is_not_member_object_pointer<int() const& noexcept>();
    test_is_not_member_object_pointer<int() const&& noexcept>();
    test_is_not_member_object_pointer<int() volatile noexcept>();
    test_is_not_member_object_pointer<int() volatile& noexcept>();
    test_is_not_member_object_pointer<int() volatile&& noexcept>();
    test_is_not_member_object_pointer<int() const volatile noexcept>();
    test_is_not_member_object_pointer<int() const volatile& noexcept>();
    test_is_not_member_object_pointer<int() const volatile&& noexcept>();

    test_is_not_member_object_pointer<int(int)>();
    test_is_not_member_object_pointer<int(int)&>();
    test_is_not_member_object_pointer<int(int) &&>();
    test_is_not_member_object_pointer<int(int) const>();
    test_is_not_member_object_pointer<int(int) const&>();
    test_is_not_member_object_pointer<int(int) const&&>();
    test_is_not_member_object_pointer<int(int) volatile>();
    test_is_not_member_object_pointer<int(int) volatile&>();
    test_is_not_member_object_pointer<int(int) volatile&&>();
    test_is_not_member_object_pointer<int(int) const volatile>();
    test_is_not_member_object_pointer<int(int) const volatile&>();
    test_is_not_member_object_pointer<int(int) const volatile&&>();
    test_is_not_member_object_pointer<int(int) noexcept>();
    test_is_not_member_object_pointer<int(int)& noexcept>();
    test_is_not_member_object_pointer<int(int)&& noexcept>();
    test_is_not_member_object_pointer<int(int) const noexcept>();
    test_is_not_member_object_pointer<int(int) const& noexcept>();
    test_is_not_member_object_pointer<int(int) const&& noexcept>();
    test_is_not_member_object_pointer<int(int) volatile noexcept>();
    test_is_not_member_object_pointer<int(int) volatile& noexcept>();
    test_is_not_member_object_pointer<int(int) volatile&& noexcept>();
    test_is_not_member_object_pointer<int(int) const volatile noexcept>();
    test_is_not_member_object_pointer<int(int) const volatile& noexcept>();
    test_is_not_member_object_pointer<int(int) const volatile&& noexcept>();

    test_is_not_member_object_pointer<int(...)>();
    test_is_not_member_object_pointer<int(...)&>();
    test_is_not_member_object_pointer<int(...) &&>();
    test_is_not_member_object_pointer<int(...) const>();
    test_is_not_member_object_pointer<int(...) const&>();
    test_is_not_member_object_pointer<int(...) const&&>();
    test_is_not_member_object_pointer<int(...) volatile>();
    test_is_not_member_object_pointer<int(...) volatile&>();
    test_is_not_member_object_pointer<int(...) volatile&&>();
    test_is_not_member_object_pointer<int(...) const volatile>();
    test_is_not_member_object_pointer<int(...) const volatile&>();
    test_is_not_member_object_pointer<int(...) const volatile&&>();
    test_is_not_member_object_pointer<int(...) noexcept>();
    test_is_not_member_object_pointer<int(...)& noexcept>();
    test_is_not_member_object_pointer<int(...)&& noexcept>();
    test_is_not_member_object_pointer<int(...) const noexcept>();
    test_is_not_member_object_pointer<int(...) const& noexcept>();
    test_is_not_member_object_pointer<int(...) const&& noexcept>();
    test_is_not_member_object_pointer<int(...) volatile noexcept>();
    test_is_not_member_object_pointer<int(...) volatile& noexcept>();
    test_is_not_member_object_pointer<int(...) volatile&& noexcept>();
    test_is_not_member_object_pointer<int(...) const volatile noexcept>();
    test_is_not_member_object_pointer<int(...) const volatile& noexcept>();
    test_is_not_member_object_pointer<int(...) const volatile&& noexcept>();

    test_is_not_member_object_pointer<int(int, ...)>();
    test_is_not_member_object_pointer<int(int, ...)&>();
    test_is_not_member_object_pointer<int(int, ...) &&>();
    test_is_not_member_object_pointer<int(int, ...) const>();
    test_is_not_member_object_pointer<int(int, ...) const&>();
    test_is_not_member_object_pointer<int(int, ...) const&&>();
    test_is_not_member_object_pointer<int(int, ...) volatile>();
    test_is_not_member_object_pointer<int(int, ...) volatile&>();
    test_is_not_member_object_pointer<int(int, ...) volatile&&>();
    test_is_not_member_object_pointer<int(int, ...) const volatile>();
    test_is_not_member_object_pointer<int(int, ...) const volatile&>();
    test_is_not_member_object_pointer<int(int, ...) const volatile&&>();
    test_is_not_member_object_pointer<int(int, ...) noexcept>();
    test_is_not_member_object_pointer<int(int, ...)& noexcept>();
    test_is_not_member_object_pointer<int(int, ...)&& noexcept>();
    test_is_not_member_object_pointer<int(int, ...) const noexcept>();
    test_is_not_member_object_pointer<int(int, ...) const& noexcept>();
    test_is_not_member_object_pointer<int(int, ...) const&& noexcept>();
    test_is_not_member_object_pointer<int(int, ...) volatile noexcept>();
    test_is_not_member_object_pointer<int(int, ...) volatile& noexcept>();
    test_is_not_member_object_pointer<int(int, ...) volatile&& noexcept>();
    test_is_not_member_object_pointer<int(int, ...) const volatile noexcept>();
    test_is_not_member_object_pointer<int(int, ...) const volatile& noexcept>();
    test_is_not_member_object_pointer<int(int, ...) const volatile&& noexcept>();

    test_is_not_member_object_pointer<void (*)()>();
    test_is_not_member_object_pointer<void (*)() noexcept>();

    test_is_not_member_object_pointer<void (*)(int)>();
    test_is_not_member_object_pointer<void (*)(int) noexcept>();

    test_is_not_member_object_pointer<void (*)(...)>();
    test_is_not_member_object_pointer<void (*)(...) noexcept>();

    test_is_not_member_object_pointer<void (*)(int, ...)>();
    test_is_not_member_object_pointer<void (*)(int, ...) noexcept>();

    test_is_not_member_object_pointer<int (*)()>();
    test_is_not_member_object_pointer<int (*)() noexcept>();

    test_is_not_member_object_pointer<int (*)(int)>();
    test_is_not_member_object_pointer<int (*)(int) noexcept>();

    test_is_not_member_object_pointer<int (*)(...)>();
    test_is_not_member_object_pointer<int (*)(...) noexcept>();

    test_is_not_member_object_pointer<int (*)(int, ...)>();
    test_is_not_member_object_pointer<int (*)(int, ...) noexcept>();

    test_is_not_member_object_pointer<void (&)()>();
    test_is_not_member_object_pointer<void (&)() noexcept>();

    test_is_not_member_object_pointer<void (&)(int)>();
    test_is_not_member_object_pointer<void (&)(int) noexcept>();

    test_is_not_member_object_pointer<void (&)(...)>();
    test_is_not_member_object_pointer<void (&)(...) noexcept>();

    test_is_not_member_object_pointer<void (&)(int, ...)>();
    test_is_not_member_object_pointer<void (&)(int, ...) noexcept>();

    test_is_not_member_object_pointer<int (&)()>();
    test_is_not_member_object_pointer<int (&)() noexcept>();

    test_is_not_member_object_pointer<int (&)(int)>();
    test_is_not_member_object_pointer<int (&)(int) noexcept>();

    test_is_not_member_object_pointer<int (&)(...)>();
    test_is_not_member_object_pointer<int (&)(...) noexcept>();

    test_is_not_member_object_pointer<int (&)(int, ...)>();
    test_is_not_member_object_pointer<int (&)(int, ...) noexcept>();

    test_is_not_member_object_pointer<void(&&)()>();
    test_is_not_member_object_pointer<void(&&)() noexcept>();

    test_is_not_member_object_pointer<void(&&)(int)>();
    test_is_not_member_object_pointer<void(&&)(int) noexcept>();

    test_is_not_member_object_pointer<void(&&)(...)>();
    test_is_not_member_object_pointer<void(&&)(...) noexcept>();

    test_is_not_member_object_pointer<void(&&)(int, ...)>();
    test_is_not_member_object_pointer<void(&&)(int, ...) noexcept>();

    test_is_not_member_object_pointer<int(&&)()>();
    test_is_not_member_object_pointer<int(&&)() noexcept>();

    test_is_not_member_object_pointer<int(&&)(int)>();
    test_is_not_member_object_pointer<int(&&)(int) noexcept>();

    test_is_not_member_object_pointer<int(&&)(...)>();
    test_is_not_member_object_pointer<int(&&)(...) noexcept>();

    test_is_not_member_object_pointer<int(&&)(int, ...)>();
    test_is_not_member_object_pointer<int(&&)(int, ...) noexcept>();

    test_is_not_member_object_pointer<void (Class::*)()>();
    test_is_not_member_object_pointer<void (Class::*)()&>();
    test_is_not_member_object_pointer<void (Class::*)() &&>();
    test_is_not_member_object_pointer<void (Class::*)() const>();
    test_is_not_member_object_pointer<void (Class::*)() const&>();
    test_is_not_member_object_pointer<void (Class::*)() const&&>();
    test_is_not_member_object_pointer<void (Class::*)() noexcept>();
    test_is_not_member_object_pointer<void (Class::*)()& noexcept>();
    test_is_not_member_object_pointer<void (Class::*)()&& noexcept>();
    test_is_not_member_object_pointer<void (Class::*)() const noexcept>();
    test_is_not_member_object_pointer<void (Class::*)() const& noexcept>();
    test_is_not_member_object_pointer<void (Class::*)() const&& noexcept>();

    test_is_not_member_object_pointer<void (Class::*)(int)>();
    test_is_not_member_object_pointer<void (Class::*)(int)&>();
    test_is_not_member_object_pointer<void (Class::*)(int) &&>();
    test_is_not_member_object_pointer<void (Class::*)(int) const>();
    test_is_not_member_object_pointer<void (Class::*)(int) const&>();
    test_is_not_member_object_pointer<void (Class::*)(int) const&&>();
    test_is_not_member_object_pointer<void (Class::*)(int) noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(int)& noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(int)&& noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(int) const noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(int) const& noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(int) const&& noexcept>();

    test_is_not_member_object_pointer<void (Class::*)(...)>();
    test_is_not_member_object_pointer<void (Class::*)(...)&>();
    test_is_not_member_object_pointer<void (Class::*)(...) &&>();
    test_is_not_member_object_pointer<void (Class::*)(...) const>();
    test_is_not_member_object_pointer<void (Class::*)(...) const&>();
    test_is_not_member_object_pointer<void (Class::*)(...) const&&>();
    test_is_not_member_object_pointer<void (Class::*)(...) noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(...)& noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(...)&& noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(...) const noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(...) const& noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(...) const&& noexcept>();

    test_is_not_member_object_pointer<void (Class::*)(int, ...)>();
    test_is_not_member_object_pointer<void (Class::*)(int, ...)&>();
    test_is_not_member_object_pointer<void (Class::*)(int, ...) &&>();
    test_is_not_member_object_pointer<void (Class::*)(int, ...) const>();
    test_is_not_member_object_pointer<void (Class::*)(int, ...) const&>();
    test_is_not_member_object_pointer<void (Class::*)(int, ...) const&&>();
    test_is_not_member_object_pointer<void (Class::*)(int, ...) noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(int, ...)& noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(int, ...) const noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_member_object_pointer<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_member_object_pointer<int (Class::*)()>();
    test_is_not_member_object_pointer<int (Class::*)()&>();
    test_is_not_member_object_pointer<int (Class::*)() &&>();
    test_is_not_member_object_pointer<int (Class::*)() const>();
    test_is_not_member_object_pointer<int (Class::*)() const&>();
    test_is_not_member_object_pointer<int (Class::*)() const&&>();
    test_is_not_member_object_pointer<int (Class::*)() noexcept>();
    test_is_not_member_object_pointer<int (Class::*)()& noexcept>();
    test_is_not_member_object_pointer<int (Class::*)()&& noexcept>();
    test_is_not_member_object_pointer<int (Class::*)() const noexcept>();
    test_is_not_member_object_pointer<int (Class::*)() const& noexcept>();
    test_is_not_member_object_pointer<int (Class::*)() const&& noexcept>();

    test_is_not_member_object_pointer<int (Class::*)(int)>();
    test_is_not_member_object_pointer<int (Class::*)(int)&>();
    test_is_not_member_object_pointer<int (Class::*)(int) &&>();
    test_is_not_member_object_pointer<int (Class::*)(int) const>();
    test_is_not_member_object_pointer<int (Class::*)(int) const&>();
    test_is_not_member_object_pointer<int (Class::*)(int) const&&>();
    test_is_not_member_object_pointer<int (Class::*)(int) noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(int)& noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(int)&& noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(int) const noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(int) const& noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(int) const&& noexcept>();

    test_is_not_member_object_pointer<int (Class::*)(...)>();
    test_is_not_member_object_pointer<int (Class::*)(...)&>();
    test_is_not_member_object_pointer<int (Class::*)(...) &&>();
    test_is_not_member_object_pointer<int (Class::*)(...) const>();
    test_is_not_member_object_pointer<int (Class::*)(...) const&>();
    test_is_not_member_object_pointer<int (Class::*)(...) const&&>();
    test_is_not_member_object_pointer<int (Class::*)(...) noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(...)& noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(...)&& noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(...) const noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(...) const& noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(...) const&& noexcept>();

    test_is_not_member_object_pointer<int (Class::*)(int, ...)>();
    test_is_not_member_object_pointer<int (Class::*)(int, ...)&>();
    test_is_not_member_object_pointer<int (Class::*)(int, ...) &&>();
    test_is_not_member_object_pointer<int (Class::*)(int, ...) const>();
    test_is_not_member_object_pointer<int (Class::*)(int, ...) const&>();
    test_is_not_member_object_pointer<int (Class::*)(int, ...) const&&>();
    test_is_not_member_object_pointer<int (Class::*)(int, ...) noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(int, ...)& noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(int, ...) const noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_member_object_pointer<int (Class::*)(int, ...) const&& noexcept>();
}
