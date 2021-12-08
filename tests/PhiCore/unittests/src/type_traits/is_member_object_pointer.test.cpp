#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/core/nullptr_t.hpp>
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

template <typename T>
void test_is_member_object_pointer_imp()
{
    STATIC_REQUIRE(phi::is_member_object_pointer<T>::value);
    STATIC_REQUIRE(phi::is_member_pointer<T>::value);
    STATIC_REQUIRE(phi::is_object<T>::value);
    STATIC_REQUIRE(phi::is_scalar<T>::value);
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
    STATIC_REQUIRE_FALSE(phi::is_enum<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_union<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_class<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_fundamental<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_member_object_pointer_v<T>);
    STATIC_REQUIRE(phi::is_member_pointer_v<T>);
    STATIC_REQUIRE(phi::is_object_v<T>);
    STATIC_REQUIRE(phi::is_scalar_v<T>);
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
    STATIC_REQUIRE_FALSE(phi::is_enum_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_union_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_class_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<T>);
#endif
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
void test_is_not_member_object_pointer()
{
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<const volatile T>);
#endif
}

TEST_CASE("is_member_object_pointer")
{
    test_is_member_object_pointer<int Abstract::*>();
    test_is_member_object_pointer<double NotEmpty::*>();
    test_is_member_object_pointer<FunctionPtr Empty::*>();
    test_is_member_object_pointer<int Class::*>();
    test_is_member_object_pointer<int Class::*>();
    test_is_member_object_pointer<MemberObjectPtr>();

    test_is_not_member_object_pointer<phi::nullptr_t>();
    test_is_not_member_object_pointer<void>();
    test_is_not_member_object_pointer<short>();
    test_is_not_member_object_pointer<int>();
    test_is_not_member_object_pointer<int&>();
    test_is_not_member_object_pointer<int&&>();
    test_is_not_member_object_pointer<int*>();
    test_is_not_member_object_pointer<const int*>();
    test_is_not_member_object_pointer<volatile int*>();
    test_is_not_member_object_pointer<const volatile int*>();
    test_is_not_member_object_pointer<int**>();
    test_is_not_member_object_pointer<float>();
    test_is_not_member_object_pointer<double>();
    test_is_not_member_object_pointer<char[3]>();
    test_is_not_member_object_pointer<char[]>();
    test_is_not_member_object_pointer<Union>();
    test_is_not_member_object_pointer<Class>();
    test_is_not_member_object_pointer<NonEmptyUnion>();
    test_is_not_member_object_pointer<Enum>();
    test_is_not_member_object_pointer<EnumSigned>();
    test_is_not_member_object_pointer<EnumUnsigned>();
    test_is_not_member_object_pointer<EnumClass>();
    test_is_not_member_object_pointer<Function>();
    test_is_not_member_object_pointer<FunctionPtr>();
    test_is_not_member_object_pointer<MemberFunctionPtr>();
    test_is_not_member_object_pointer<Empty>();
    test_is_not_member_object_pointer<bit_zero>();
    test_is_not_member_object_pointer<bit_one>();
    test_is_not_member_object_pointer<NotEmpty>();
    test_is_not_member_object_pointer<Abstract>();
    test_is_not_member_object_pointer<AbstractTemplate<int>>();
    test_is_not_member_object_pointer<AbstractTemplate<double>>();
    test_is_not_member_object_pointer<incomplete_type>(); // LWG#2582
}
