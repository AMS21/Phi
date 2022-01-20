#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_scoped_enum.hpp>
#include <phi/type_traits/is_unscoped_enum.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_scoped_enum_impl()
{
#if PHI_HAS_WORKING_IS_SCOPED_ENUM()
    STATIC_REQUIRE(phi::is_scoped_enum<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_scoped_enum<T>::value);
#    if PHI_HAS_WORKING_IS_UNSCOPED_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_unscoped_enum<T>::value);
#    endif
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE(phi::is_enum<T>::value);
#    endif

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_scoped_enum_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_scoped_enum_v<T>);
#        if PHI_HAS_WORKING_IS_UNSCOPED_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_unscoped_enum_v<T>);
#        endif
#        if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE(phi::is_enum_v<T>);
#        endif
#    endif

#    if PHI_CPP_STANDARD_IS_ATLEAST(23)
    STATIC_REQUIRE(std::is_scoped_enum<T>::value);
#    endif
#endif
}

template <typename T>
void test_is_not_scoped_enum_impl()
{
#if PHI_HAS_WORKING_IS_SCOPED_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum<T>::value);
    STATIC_REQUIRE(phi::is_not_scoped_enum<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_scoped_enum_v<T>);
    STATIC_REQUIRE(phi::is_not_scoped_enum_v<T>);
#    endif

#    if PHI_CPP_STANDARD_IS_ATLEAST(23)
    STATIC_REQUIRE_FALSE(std::is_scoped_enum<T>::value);
#    endif
#endif
}

template <typename T>
void test_is_scoped_enum()
{
    test_is_scoped_enum_impl<T>();
    test_is_scoped_enum_impl<const T>();
    test_is_scoped_enum_impl<volatile T>();
    test_is_scoped_enum_impl<const volatile T>();
}

template <typename T>
void test_is_not_scoped_enum()
{
    test_is_not_scoped_enum_impl<T>();
    test_is_not_scoped_enum_impl<const T>();
    test_is_not_scoped_enum_impl<volatile T>();
    test_is_not_scoped_enum_impl<const volatile T>();
}

class A
{};

enum E
{
};

enum struct EStruct
{
};

enum class EClass
{
};

TEST_CASE("type_traits is_scoped_enum", "[Core][TypeTraits][is_scoped_enum]")
{
    test_is_scoped_enum<EStruct>();
    test_is_scoped_enum<EClass>();

    test_is_not_scoped_enum<A>();
    test_is_not_scoped_enum<E>();

    test_is_not_scoped_enum<void>();
    test_is_not_scoped_enum<phi::nullptr_t>();
    test_is_not_scoped_enum<bool>();
    test_is_not_scoped_enum<char>();
    test_is_not_scoped_enum<signed char>();
    test_is_not_scoped_enum<unsigned char>();
    test_is_not_scoped_enum<short>();
    test_is_not_scoped_enum<unsigned short>();
    test_is_not_scoped_enum<int>();
    test_is_not_scoped_enum<unsigned int>();
    test_is_not_scoped_enum<long>();
    test_is_not_scoped_enum<unsigned long>();
    test_is_not_scoped_enum<long long>();
    test_is_not_scoped_enum<unsigned long long>();
    test_is_not_scoped_enum<float>();
    test_is_not_scoped_enum<double>();
    test_is_not_scoped_enum<long double>();
    test_is_not_scoped_enum<char8_t>();
    test_is_not_scoped_enum<char16_t>();
    test_is_not_scoped_enum<char32_t>();
    test_is_not_scoped_enum<wchar_t>();

    test_is_not_scoped_enum<phi::boolean>();
    test_is_not_scoped_enum<phi::integer<signed char>>();
    test_is_not_scoped_enum<phi::integer<unsigned char>>();
    test_is_not_scoped_enum<phi::integer<short>>();
    test_is_not_scoped_enum<phi::integer<unsigned short>>();
    test_is_not_scoped_enum<phi::integer<int>>();
    test_is_not_scoped_enum<phi::integer<unsigned int>>();
    test_is_not_scoped_enum<phi::integer<long>>();
    test_is_not_scoped_enum<phi::integer<unsigned long>>();
    test_is_not_scoped_enum<phi::integer<long long>>();
    test_is_not_scoped_enum<phi::integer<unsigned long long>>();
    test_is_not_scoped_enum<phi::floating_point<float>>();
    test_is_not_scoped_enum<phi::floating_point<double>>();
    test_is_not_scoped_enum<phi::floating_point<long double>>();

    test_is_not_scoped_enum<std::vector<int>>();
    test_is_not_scoped_enum<phi::scope_ptr<int>>();

    test_is_not_scoped_enum<int&>();
    test_is_not_scoped_enum<const int&>();
    test_is_not_scoped_enum<volatile int&>();
    test_is_not_scoped_enum<const volatile int&>();
    test_is_not_scoped_enum<int&&>();
    test_is_not_scoped_enum<const int&&>();
    test_is_not_scoped_enum<volatile int&&>();
    test_is_not_scoped_enum<const volatile int&&>();
    test_is_not_scoped_enum<int*>();
    test_is_not_scoped_enum<const int*>();
    test_is_not_scoped_enum<volatile int*>();
    test_is_not_scoped_enum<const volatile int*>();
    test_is_not_scoped_enum<int**>();
    test_is_not_scoped_enum<const int**>();
    test_is_not_scoped_enum<volatile int**>();
    test_is_not_scoped_enum<const volatile int**>();
    test_is_not_scoped_enum<int*&>();
    test_is_not_scoped_enum<const int*&>();
    test_is_not_scoped_enum<volatile int*&>();
    test_is_not_scoped_enum<const volatile int*&>();
    test_is_not_scoped_enum<int*&&>();
    test_is_not_scoped_enum<const int*&&>();
    test_is_not_scoped_enum<volatile int*&&>();
    test_is_not_scoped_enum<const volatile int*&&>();
    test_is_not_scoped_enum<void*>();
    test_is_not_scoped_enum<char[3]>();
    test_is_not_scoped_enum<char[]>();
    test_is_not_scoped_enum<char* [3]>();
    test_is_not_scoped_enum<char*[]>();
    test_is_not_scoped_enum<int(*)[3]>();
    test_is_not_scoped_enum<int(*)[]>();
    test_is_not_scoped_enum<int(&)[3]>();
    test_is_not_scoped_enum<int(&)[]>();
    test_is_not_scoped_enum<int(&&)[3]>();
    test_is_not_scoped_enum<int(&&)[]>();
    test_is_not_scoped_enum<char[3][2]>();
    test_is_not_scoped_enum<char[][2]>();
    test_is_not_scoped_enum<char* [3][2]>();
    test_is_not_scoped_enum<char*[][2]>();
    test_is_not_scoped_enum<int(*)[3][2]>();
    test_is_not_scoped_enum<int(*)[][2]>();
    test_is_not_scoped_enum<int(&)[3][2]>();
    test_is_not_scoped_enum<int(&)[][2]>();
    test_is_not_scoped_enum<int(&&)[3][2]>();
    test_is_not_scoped_enum<int(&&)[][2]>();
    test_is_not_scoped_enum<Class>();
    test_is_not_scoped_enum<Class[]>();
    test_is_not_scoped_enum<Class[2]>();
    test_is_not_scoped_enum<Template<void>>();
    test_is_not_scoped_enum<Template<int>>();
    test_is_not_scoped_enum<Template<Class>>();
    test_is_not_scoped_enum<Template<incomplete_type>>();
    test_is_not_scoped_enum<VariadicTemplate<>>();
    test_is_not_scoped_enum<VariadicTemplate<void>>();
    test_is_not_scoped_enum<VariadicTemplate<int>>();
    test_is_not_scoped_enum<VariadicTemplate<Class>>();
    test_is_not_scoped_enum<VariadicTemplate<incomplete_type>>();
    test_is_not_scoped_enum<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_scoped_enum<PublicDerviedFromTemplate<Base>>();
    test_is_not_scoped_enum<PublicDerviedFromTemplate<Derived>>();
    test_is_not_scoped_enum<PublicDerviedFromTemplate<Class>>();
    test_is_not_scoped_enum<PrivateDerviedFromTemplate<Base>>();
    test_is_not_scoped_enum<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_scoped_enum<PrivateDerviedFromTemplate<Class>>();
    test_is_not_scoped_enum<ProtectedDerviedFromTemplate<Base>>();
    test_is_not_scoped_enum<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_scoped_enum<ProtectedDerviedFromTemplate<Class>>();
    test_is_not_scoped_enum<Union>();
    test_is_not_scoped_enum<NonEmptyUnion>();
    test_is_not_scoped_enum<Empty>();
    test_is_not_scoped_enum<NotEmpty>();
    test_is_not_scoped_enum<bit_zero>();
    test_is_not_scoped_enum<bit_one>();
    test_is_not_scoped_enum<Base>();
    test_is_not_scoped_enum<Derived>();
    test_is_not_scoped_enum<Abstract>();
    test_is_not_scoped_enum<PublicAbstract>();
    test_is_not_scoped_enum<PrivateAbstract>();
    test_is_not_scoped_enum<ProtectedAbstract>();
    test_is_not_scoped_enum<AbstractTemplate<int>>();
    test_is_not_scoped_enum<AbstractTemplate<double>>();
    test_is_not_scoped_enum<AbstractTemplate<Class>>();
    test_is_not_scoped_enum<AbstractTemplate<incomplete_type>>();
    test_is_not_scoped_enum<Final>();
    test_is_not_scoped_enum<PublicDestructor>();
    test_is_not_scoped_enum<ProtectedDestructor>();
    test_is_not_scoped_enum<PrivateDestructor>();
    test_is_not_scoped_enum<VirtualPublicDestructor>();
    test_is_not_scoped_enum<VirtualProtectedDestructor>();
    test_is_not_scoped_enum<VirtualPrivateDestructor>();
    test_is_not_scoped_enum<PurePublicDestructor>();
    test_is_not_scoped_enum<PureProtectedDestructor>();
    test_is_not_scoped_enum<PurePrivateDestructor>();
    test_is_not_scoped_enum<DeletedPublicDestructor>();
    test_is_not_scoped_enum<DeletedProtectedDestructor>();
    test_is_not_scoped_enum<DeletedPrivateDestructor>();
    test_is_not_scoped_enum<DeletedVirtualPublicDestructor>();
    test_is_not_scoped_enum<DeletedVirtualProtectedDestructor>();
    test_is_not_scoped_enum<DeletedVirtualPrivateDestructor>();
    test_is_not_scoped_enum<Enum>();
    test_is_not_scoped_enum<EnumSigned>();
    test_is_not_scoped_enum<EnumUnsigned>();
    test_is_scoped_enum<EnumClass>();
    test_is_scoped_enum<EnumStruct>();
    test_is_not_scoped_enum<Function>();
    test_is_not_scoped_enum<FunctionPtr>();
    test_is_not_scoped_enum<MemberObjectPtr>();
    test_is_not_scoped_enum<MemberFunctionPtr>();
    test_is_not_scoped_enum<incomplete_type>();
    test_is_not_scoped_enum<IncompleteTemplate<void>>();
    test_is_not_scoped_enum<IncompleteTemplate<int>>();
    test_is_not_scoped_enum<IncompleteTemplate<Class>>();
    test_is_not_scoped_enum<IncompleteTemplate<incomplete_type>>();
    test_is_not_scoped_enum<IncompleteVariadicTemplate<>>();
    test_is_not_scoped_enum<IncompleteVariadicTemplate<void>>();
    test_is_not_scoped_enum<IncompleteVariadicTemplate<int>>();
    test_is_not_scoped_enum<IncompleteVariadicTemplate<Class>>();
    test_is_not_scoped_enum<IncompleteVariadicTemplate<incomplete_type>>();
    test_is_not_scoped_enum<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_scoped_enum<int Class::*>();
    test_is_not_scoped_enum<float Class::*>();
    test_is_not_scoped_enum<void * Class::*>();
    test_is_not_scoped_enum<int * Class::*>();
    test_is_not_scoped_enum<int Class::*&>();
    test_is_not_scoped_enum<float Class::*&>();
    test_is_not_scoped_enum<void * Class::*&>();
    test_is_not_scoped_enum<int * Class::*&>();
    test_is_not_scoped_enum<int Class::*&&>();
    test_is_not_scoped_enum<float Class::*&&>();
    test_is_not_scoped_enum<void * Class::*&&>();
    test_is_not_scoped_enum<int * Class::*&&>();
    test_is_not_scoped_enum<int Class::*const>();
    test_is_not_scoped_enum<float Class::*const>();
    test_is_not_scoped_enum<void * Class::*const>();
    test_is_not_scoped_enum<int Class::*const&>();
    test_is_not_scoped_enum<float Class::*const&>();
    test_is_not_scoped_enum<void * Class::*const&>();
    test_is_not_scoped_enum<int Class::*const&&>();
    test_is_not_scoped_enum<float Class::*const&&>();
    test_is_not_scoped_enum<void * Class::*const&&>();
    test_is_not_scoped_enum<int Class::*volatile>();
    test_is_not_scoped_enum<float Class::*volatile>();
    test_is_not_scoped_enum<void * Class::*volatile>();
    test_is_not_scoped_enum<int Class::*volatile&>();
    test_is_not_scoped_enum<float Class::*volatile&>();
    test_is_not_scoped_enum<void * Class::*volatile&>();
    test_is_not_scoped_enum<int Class::*volatile&&>();
    test_is_not_scoped_enum<float Class::*volatile&&>();
    test_is_not_scoped_enum<void * Class::*volatile&&>();
    test_is_not_scoped_enum<int Class::*const volatile>();
    test_is_not_scoped_enum<float Class::*const volatile>();
    test_is_not_scoped_enum<void * Class::*const volatile>();
    test_is_not_scoped_enum<int Class::*const volatile&>();
    test_is_not_scoped_enum<float Class::*const volatile&>();
    test_is_not_scoped_enum<void * Class::*const volatile&>();
    test_is_not_scoped_enum<int Class::*const volatile&&>();
    test_is_not_scoped_enum<float Class::*const volatile&&>();
    test_is_not_scoped_enum<void * Class::*const volatile&&>();
    test_is_not_scoped_enum<NonCopyable>();
    test_is_not_scoped_enum<NonMoveable>();
    test_is_not_scoped_enum<NonConstructible>();
    test_is_not_scoped_enum<Tracked>();
    test_is_not_scoped_enum<TrapConstructible>();
    test_is_not_scoped_enum<TrapImplicitConversion>();
    test_is_not_scoped_enum<TrapComma>();
    test_is_not_scoped_enum<TrapCall>();
    test_is_not_scoped_enum<TrapSelfAssign>();
    test_is_not_scoped_enum<TrapDeref>();
    test_is_not_scoped_enum<TrapArraySubscript>();

    test_is_not_scoped_enum<void()>();
    test_is_not_scoped_enum<void()&>();
    test_is_not_scoped_enum<void() &&>();
    test_is_not_scoped_enum<void() const>();
    test_is_not_scoped_enum<void() const&>();
    test_is_not_scoped_enum<void() const&&>();
    test_is_not_scoped_enum<void() volatile>();
    test_is_not_scoped_enum<void() volatile&>();
    test_is_not_scoped_enum<void() volatile&&>();
    test_is_not_scoped_enum<void() const volatile>();
    test_is_not_scoped_enum<void() const volatile&>();
    test_is_not_scoped_enum<void() const volatile&&>();
    test_is_not_scoped_enum<void() noexcept>();
    test_is_not_scoped_enum<void()& noexcept>();
    test_is_not_scoped_enum<void()&& noexcept>();
    test_is_not_scoped_enum<void() const noexcept>();
    test_is_not_scoped_enum<void() const& noexcept>();
    test_is_not_scoped_enum<void() const&& noexcept>();
    test_is_not_scoped_enum<void() volatile noexcept>();
    test_is_not_scoped_enum<void() volatile& noexcept>();
    test_is_not_scoped_enum<void() volatile&& noexcept>();
    test_is_not_scoped_enum<void() const volatile noexcept>();
    test_is_not_scoped_enum<void() const volatile& noexcept>();
    test_is_not_scoped_enum<void() const volatile&& noexcept>();

    test_is_not_scoped_enum<void(int)>();
    test_is_not_scoped_enum<void(int)&>();
    test_is_not_scoped_enum<void(int) &&>();
    test_is_not_scoped_enum<void(int) const>();
    test_is_not_scoped_enum<void(int) const&>();
    test_is_not_scoped_enum<void(int) const&&>();
    test_is_not_scoped_enum<void(int) volatile>();
    test_is_not_scoped_enum<void(int) volatile&>();
    test_is_not_scoped_enum<void(int) volatile&&>();
    test_is_not_scoped_enum<void(int) const volatile>();
    test_is_not_scoped_enum<void(int) const volatile&>();
    test_is_not_scoped_enum<void(int) const volatile&&>();
    test_is_not_scoped_enum<void(int) noexcept>();
    test_is_not_scoped_enum<void(int)& noexcept>();
    test_is_not_scoped_enum<void(int)&& noexcept>();
    test_is_not_scoped_enum<void(int) const noexcept>();
    test_is_not_scoped_enum<void(int) const& noexcept>();
    test_is_not_scoped_enum<void(int) const&& noexcept>();
    test_is_not_scoped_enum<void(int) volatile noexcept>();
    test_is_not_scoped_enum<void(int) volatile& noexcept>();
    test_is_not_scoped_enum<void(int) volatile&& noexcept>();
    test_is_not_scoped_enum<void(int) const volatile noexcept>();
    test_is_not_scoped_enum<void(int) const volatile& noexcept>();
    test_is_not_scoped_enum<void(int) const volatile&& noexcept>();

    test_is_not_scoped_enum<void(...)>();
    test_is_not_scoped_enum<void(...)&>();
    test_is_not_scoped_enum<void(...) &&>();
    test_is_not_scoped_enum<void(...) const>();
    test_is_not_scoped_enum<void(...) const&>();
    test_is_not_scoped_enum<void(...) const&&>();
    test_is_not_scoped_enum<void(...) volatile>();
    test_is_not_scoped_enum<void(...) volatile&>();
    test_is_not_scoped_enum<void(...) volatile&&>();
    test_is_not_scoped_enum<void(...) const volatile>();
    test_is_not_scoped_enum<void(...) const volatile&>();
    test_is_not_scoped_enum<void(...) const volatile&&>();
    test_is_not_scoped_enum<void(...) noexcept>();
    test_is_not_scoped_enum<void(...)& noexcept>();
    test_is_not_scoped_enum<void(...)&& noexcept>();
    test_is_not_scoped_enum<void(...) const noexcept>();
    test_is_not_scoped_enum<void(...) const& noexcept>();
    test_is_not_scoped_enum<void(...) const&& noexcept>();
    test_is_not_scoped_enum<void(...) volatile noexcept>();
    test_is_not_scoped_enum<void(...) volatile& noexcept>();
    test_is_not_scoped_enum<void(...) volatile&& noexcept>();
    test_is_not_scoped_enum<void(...) const volatile noexcept>();
    test_is_not_scoped_enum<void(...) const volatile& noexcept>();
    test_is_not_scoped_enum<void(...) const volatile&& noexcept>();

    test_is_not_scoped_enum<void(int, ...)>();
    test_is_not_scoped_enum<void(int, ...)&>();
    test_is_not_scoped_enum<void(int, ...) &&>();
    test_is_not_scoped_enum<void(int, ...) const>();
    test_is_not_scoped_enum<void(int, ...) const&>();
    test_is_not_scoped_enum<void(int, ...) const&&>();
    test_is_not_scoped_enum<void(int, ...) volatile>();
    test_is_not_scoped_enum<void(int, ...) volatile&>();
    test_is_not_scoped_enum<void(int, ...) volatile&&>();
    test_is_not_scoped_enum<void(int, ...) const volatile>();
    test_is_not_scoped_enum<void(int, ...) const volatile&>();
    test_is_not_scoped_enum<void(int, ...) const volatile&&>();
    test_is_not_scoped_enum<void(int, ...) noexcept>();
    test_is_not_scoped_enum<void(int, ...)& noexcept>();
    test_is_not_scoped_enum<void(int, ...)&& noexcept>();
    test_is_not_scoped_enum<void(int, ...) const noexcept>();
    test_is_not_scoped_enum<void(int, ...) const& noexcept>();
    test_is_not_scoped_enum<void(int, ...) const&& noexcept>();
    test_is_not_scoped_enum<void(int, ...) volatile noexcept>();
    test_is_not_scoped_enum<void(int, ...) volatile& noexcept>();
    test_is_not_scoped_enum<void(int, ...) volatile&& noexcept>();
    test_is_not_scoped_enum<void(int, ...) const volatile noexcept>();
    test_is_not_scoped_enum<void(int, ...) const volatile& noexcept>();
    test_is_not_scoped_enum<void(int, ...) const volatile&& noexcept>();

    test_is_not_scoped_enum<int()>();
    test_is_not_scoped_enum<int()&>();
    test_is_not_scoped_enum<int() &&>();
    test_is_not_scoped_enum<int() const>();
    test_is_not_scoped_enum<int() const&>();
    test_is_not_scoped_enum<int() const&&>();
    test_is_not_scoped_enum<int() volatile>();
    test_is_not_scoped_enum<int() volatile&>();
    test_is_not_scoped_enum<int() volatile&&>();
    test_is_not_scoped_enum<int() const volatile>();
    test_is_not_scoped_enum<int() const volatile&>();
    test_is_not_scoped_enum<int() const volatile&&>();
    test_is_not_scoped_enum<int() noexcept>();
    test_is_not_scoped_enum<int()& noexcept>();
    test_is_not_scoped_enum<int()&& noexcept>();
    test_is_not_scoped_enum<int() const noexcept>();
    test_is_not_scoped_enum<int() const& noexcept>();
    test_is_not_scoped_enum<int() const&& noexcept>();
    test_is_not_scoped_enum<int() volatile noexcept>();
    test_is_not_scoped_enum<int() volatile& noexcept>();
    test_is_not_scoped_enum<int() volatile&& noexcept>();
    test_is_not_scoped_enum<int() const volatile noexcept>();
    test_is_not_scoped_enum<int() const volatile& noexcept>();
    test_is_not_scoped_enum<int() const volatile&& noexcept>();

    test_is_not_scoped_enum<int(int)>();
    test_is_not_scoped_enum<int(int)&>();
    test_is_not_scoped_enum<int(int) &&>();
    test_is_not_scoped_enum<int(int) const>();
    test_is_not_scoped_enum<int(int) const&>();
    test_is_not_scoped_enum<int(int) const&&>();
    test_is_not_scoped_enum<int(int) volatile>();
    test_is_not_scoped_enum<int(int) volatile&>();
    test_is_not_scoped_enum<int(int) volatile&&>();
    test_is_not_scoped_enum<int(int) const volatile>();
    test_is_not_scoped_enum<int(int) const volatile&>();
    test_is_not_scoped_enum<int(int) const volatile&&>();
    test_is_not_scoped_enum<int(int) noexcept>();
    test_is_not_scoped_enum<int(int)& noexcept>();
    test_is_not_scoped_enum<int(int)&& noexcept>();
    test_is_not_scoped_enum<int(int) const noexcept>();
    test_is_not_scoped_enum<int(int) const& noexcept>();
    test_is_not_scoped_enum<int(int) const&& noexcept>();
    test_is_not_scoped_enum<int(int) volatile noexcept>();
    test_is_not_scoped_enum<int(int) volatile& noexcept>();
    test_is_not_scoped_enum<int(int) volatile&& noexcept>();
    test_is_not_scoped_enum<int(int) const volatile noexcept>();
    test_is_not_scoped_enum<int(int) const volatile& noexcept>();
    test_is_not_scoped_enum<int(int) const volatile&& noexcept>();

    test_is_not_scoped_enum<int(...)>();
    test_is_not_scoped_enum<int(...)&>();
    test_is_not_scoped_enum<int(...) &&>();
    test_is_not_scoped_enum<int(...) const>();
    test_is_not_scoped_enum<int(...) const&>();
    test_is_not_scoped_enum<int(...) const&&>();
    test_is_not_scoped_enum<int(...) volatile>();
    test_is_not_scoped_enum<int(...) volatile&>();
    test_is_not_scoped_enum<int(...) volatile&&>();
    test_is_not_scoped_enum<int(...) const volatile>();
    test_is_not_scoped_enum<int(...) const volatile&>();
    test_is_not_scoped_enum<int(...) const volatile&&>();
    test_is_not_scoped_enum<int(...) noexcept>();
    test_is_not_scoped_enum<int(...)& noexcept>();
    test_is_not_scoped_enum<int(...)&& noexcept>();
    test_is_not_scoped_enum<int(...) const noexcept>();
    test_is_not_scoped_enum<int(...) const& noexcept>();
    test_is_not_scoped_enum<int(...) const&& noexcept>();
    test_is_not_scoped_enum<int(...) volatile noexcept>();
    test_is_not_scoped_enum<int(...) volatile& noexcept>();
    test_is_not_scoped_enum<int(...) volatile&& noexcept>();
    test_is_not_scoped_enum<int(...) const volatile noexcept>();
    test_is_not_scoped_enum<int(...) const volatile& noexcept>();
    test_is_not_scoped_enum<int(...) const volatile&& noexcept>();

    test_is_not_scoped_enum<int(int, ...)>();
    test_is_not_scoped_enum<int(int, ...)&>();
    test_is_not_scoped_enum<int(int, ...) &&>();
    test_is_not_scoped_enum<int(int, ...) const>();
    test_is_not_scoped_enum<int(int, ...) const&>();
    test_is_not_scoped_enum<int(int, ...) const&&>();
    test_is_not_scoped_enum<int(int, ...) volatile>();
    test_is_not_scoped_enum<int(int, ...) volatile&>();
    test_is_not_scoped_enum<int(int, ...) volatile&&>();
    test_is_not_scoped_enum<int(int, ...) const volatile>();
    test_is_not_scoped_enum<int(int, ...) const volatile&>();
    test_is_not_scoped_enum<int(int, ...) const volatile&&>();
    test_is_not_scoped_enum<int(int, ...) noexcept>();
    test_is_not_scoped_enum<int(int, ...)& noexcept>();
    test_is_not_scoped_enum<int(int, ...)&& noexcept>();
    test_is_not_scoped_enum<int(int, ...) const noexcept>();
    test_is_not_scoped_enum<int(int, ...) const& noexcept>();
    test_is_not_scoped_enum<int(int, ...) const&& noexcept>();
    test_is_not_scoped_enum<int(int, ...) volatile noexcept>();
    test_is_not_scoped_enum<int(int, ...) volatile& noexcept>();
    test_is_not_scoped_enum<int(int, ...) volatile&& noexcept>();
    test_is_not_scoped_enum<int(int, ...) const volatile noexcept>();
    test_is_not_scoped_enum<int(int, ...) const volatile& noexcept>();
    test_is_not_scoped_enum<int(int, ...) const volatile&& noexcept>();

    test_is_not_scoped_enum<void (*)()>();
    test_is_not_scoped_enum<void (*)() noexcept>();

    test_is_not_scoped_enum<void (*)(int)>();
    test_is_not_scoped_enum<void (*)(int) noexcept>();

    test_is_not_scoped_enum<void (*)(...)>();
    test_is_not_scoped_enum<void (*)(...) noexcept>();

    test_is_not_scoped_enum<void (*)(int, ...)>();
    test_is_not_scoped_enum<void (*)(int, ...) noexcept>();

    test_is_not_scoped_enum<int (*)()>();
    test_is_not_scoped_enum<int (*)() noexcept>();

    test_is_not_scoped_enum<int (*)(int)>();
    test_is_not_scoped_enum<int (*)(int) noexcept>();

    test_is_not_scoped_enum<int (*)(...)>();
    test_is_not_scoped_enum<int (*)(...) noexcept>();

    test_is_not_scoped_enum<int (*)(int, ...)>();
    test_is_not_scoped_enum<int (*)(int, ...) noexcept>();

    test_is_not_scoped_enum<void (&)()>();
    test_is_not_scoped_enum<void (&)() noexcept>();

    test_is_not_scoped_enum<void (&)(int)>();
    test_is_not_scoped_enum<void (&)(int) noexcept>();

    test_is_not_scoped_enum<void (&)(...)>();
    test_is_not_scoped_enum<void (&)(...) noexcept>();

    test_is_not_scoped_enum<void (&)(int, ...)>();
    test_is_not_scoped_enum<void (&)(int, ...) noexcept>();

    test_is_not_scoped_enum<int (&)()>();
    test_is_not_scoped_enum<int (&)() noexcept>();

    test_is_not_scoped_enum<int (&)(int)>();
    test_is_not_scoped_enum<int (&)(int) noexcept>();

    test_is_not_scoped_enum<int (&)(...)>();
    test_is_not_scoped_enum<int (&)(...) noexcept>();

    test_is_not_scoped_enum<int (&)(int, ...)>();
    test_is_not_scoped_enum<int (&)(int, ...) noexcept>();

    test_is_not_scoped_enum<void(&&)()>();
    test_is_not_scoped_enum<void(&&)() noexcept>();

    test_is_not_scoped_enum<void(&&)(int)>();
    test_is_not_scoped_enum<void(&&)(int) noexcept>();

    test_is_not_scoped_enum<void(&&)(...)>();
    test_is_not_scoped_enum<void(&&)(...) noexcept>();

    test_is_not_scoped_enum<void(&&)(int, ...)>();
    test_is_not_scoped_enum<void(&&)(int, ...) noexcept>();

    test_is_not_scoped_enum<int(&&)()>();
    test_is_not_scoped_enum<int(&&)() noexcept>();

    test_is_not_scoped_enum<int(&&)(int)>();
    test_is_not_scoped_enum<int(&&)(int) noexcept>();

    test_is_not_scoped_enum<int(&&)(...)>();
    test_is_not_scoped_enum<int(&&)(...) noexcept>();

    test_is_not_scoped_enum<int(&&)(int, ...)>();
    test_is_not_scoped_enum<int(&&)(int, ...) noexcept>();

    test_is_not_scoped_enum<void (Class::*)()>();
    test_is_not_scoped_enum<void (Class::*)()&>();
    test_is_not_scoped_enum<void (Class::*)() &&>();
    test_is_not_scoped_enum<void (Class::*)() const>();
    test_is_not_scoped_enum<void (Class::*)() const&>();
    test_is_not_scoped_enum<void (Class::*)() const&&>();
    test_is_not_scoped_enum<void (Class::*)() noexcept>();
    test_is_not_scoped_enum<void (Class::*)()& noexcept>();
    test_is_not_scoped_enum<void (Class::*)()&& noexcept>();
    test_is_not_scoped_enum<void (Class::*)() const noexcept>();
    test_is_not_scoped_enum<void (Class::*)() const& noexcept>();
    test_is_not_scoped_enum<void (Class::*)() const&& noexcept>();

    test_is_not_scoped_enum<void (Class::*)(int)>();
    test_is_not_scoped_enum<void (Class::*)(int)&>();
    test_is_not_scoped_enum<void (Class::*)(int) &&>();
    test_is_not_scoped_enum<void (Class::*)(int) const>();
    test_is_not_scoped_enum<void (Class::*)(int) const&>();
    test_is_not_scoped_enum<void (Class::*)(int) const&&>();
    test_is_not_scoped_enum<void (Class::*)(int) noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int)& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int)&& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int) const noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int) const& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int) const&& noexcept>();

    test_is_not_scoped_enum<void (Class::*)(...)>();
    test_is_not_scoped_enum<void (Class::*)(...)&>();
    test_is_not_scoped_enum<void (Class::*)(...) &&>();
    test_is_not_scoped_enum<void (Class::*)(...) const>();
    test_is_not_scoped_enum<void (Class::*)(...) const&>();
    test_is_not_scoped_enum<void (Class::*)(...) const&&>();
    test_is_not_scoped_enum<void (Class::*)(...) noexcept>();
    test_is_not_scoped_enum<void (Class::*)(...)& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(...)&& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(...) const noexcept>();
    test_is_not_scoped_enum<void (Class::*)(...) const& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(...) const&& noexcept>();

    test_is_not_scoped_enum<void (Class::*)(int, ...)>();
    test_is_not_scoped_enum<void (Class::*)(int, ...)&>();
    test_is_not_scoped_enum<void (Class::*)(int, ...) &&>();
    test_is_not_scoped_enum<void (Class::*)(int, ...) const>();
    test_is_not_scoped_enum<void (Class::*)(int, ...) const&>();
    test_is_not_scoped_enum<void (Class::*)(int, ...) const&&>();
    test_is_not_scoped_enum<void (Class::*)(int, ...) noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int, ...)& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int, ...) const noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_scoped_enum<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_scoped_enum<int (Class::*)()>();
    test_is_not_scoped_enum<int (Class::*)()&>();
    test_is_not_scoped_enum<int (Class::*)() &&>();
    test_is_not_scoped_enum<int (Class::*)() const>();
    test_is_not_scoped_enum<int (Class::*)() const&>();
    test_is_not_scoped_enum<int (Class::*)() const&&>();
    test_is_not_scoped_enum<int (Class::*)() noexcept>();
    test_is_not_scoped_enum<int (Class::*)()& noexcept>();
    test_is_not_scoped_enum<int (Class::*)()&& noexcept>();
    test_is_not_scoped_enum<int (Class::*)() const noexcept>();
    test_is_not_scoped_enum<int (Class::*)() const& noexcept>();
    test_is_not_scoped_enum<int (Class::*)() const&& noexcept>();

    test_is_not_scoped_enum<int (Class::*)(int)>();
    test_is_not_scoped_enum<int (Class::*)(int)&>();
    test_is_not_scoped_enum<int (Class::*)(int) &&>();
    test_is_not_scoped_enum<int (Class::*)(int) const>();
    test_is_not_scoped_enum<int (Class::*)(int) const&>();
    test_is_not_scoped_enum<int (Class::*)(int) const&&>();
    test_is_not_scoped_enum<int (Class::*)(int) noexcept>();
    test_is_not_scoped_enum<int (Class::*)(int)& noexcept>();
    test_is_not_scoped_enum<int (Class::*)(int)&& noexcept>();
    test_is_not_scoped_enum<int (Class::*)(int) const noexcept>();
    test_is_not_scoped_enum<int (Class::*)(int) const& noexcept>();
    test_is_not_scoped_enum<int (Class::*)(int) const&& noexcept>();

    test_is_not_scoped_enum<int (Class::*)(...)>();
    test_is_not_scoped_enum<int (Class::*)(...)&>();
    test_is_not_scoped_enum<int (Class::*)(...) &&>();
    test_is_not_scoped_enum<int (Class::*)(...) const>();
    test_is_not_scoped_enum<int (Class::*)(...) const&>();
    test_is_not_scoped_enum<int (Class::*)(...) const&&>();
    test_is_not_scoped_enum<int (Class::*)(...) noexcept>();
    test_is_not_scoped_enum<int (Class::*)(...)& noexcept>();
    test_is_not_scoped_enum<int (Class::*)(...)&& noexcept>();
    test_is_not_scoped_enum<int (Class::*)(...) const noexcept>();
    test_is_not_scoped_enum<int (Class::*)(...) const& noexcept>();
    test_is_not_scoped_enum<int (Class::*)(...) const&& noexcept>();

    test_is_not_scoped_enum<int (Class::*)(int, ...)>();
    test_is_not_scoped_enum<int (Class::*)(int, ...)&>();
    test_is_not_scoped_enum<int (Class::*)(int, ...) &&>();
    test_is_not_scoped_enum<int (Class::*)(int, ...) const>();
    test_is_not_scoped_enum<int (Class::*)(int, ...) const&>();
    test_is_not_scoped_enum<int (Class::*)(int, ...) const&&>();
    test_is_not_scoped_enum<int (Class::*)(int, ...) noexcept>();
    test_is_not_scoped_enum<int (Class::*)(int, ...)& noexcept>();
    test_is_not_scoped_enum<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_scoped_enum<int (Class::*)(int, ...) const noexcept>();
    test_is_not_scoped_enum<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_scoped_enum<int (Class::*)(int, ...) const&& noexcept>();
}
