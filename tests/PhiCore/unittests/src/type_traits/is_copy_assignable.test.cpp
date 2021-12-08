#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_copy_assignable.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_copy_assignable()
{
    STATIC_REQUIRE(phi::is_copy_assignable<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_copy_assignable<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_copy_assignable_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_copy_assignable_v<T>);
#endif

    // Standard compatbility
    STATIC_REQUIRE(std::is_copy_assignable<T>::value);
}

template <typename T>
void test_is_not_copy_assignable()
{
    STATIC_REQUIRE_FALSE(phi::is_copy_assignable<T>::value);
    STATIC_REQUIRE(phi::is_not_copy_assignable<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_copy_assignable_v<T>);
    STATIC_REQUIRE(phi::is_not_copy_assignable_v<T>);
#endif

    STATIC_REQUIRE_FALSE(std::is_copy_assignable<T>::value);
}

struct A
{
    A();
};

class B
{
    B& operator=(const B&);
};

struct C
{
    void operator=(C&); // not const
};

TEST_CASE("is_copy_assignable")
{
    test_is_copy_assignable<A>();

    test_is_not_copy_assignable<B>();
    test_is_not_copy_assignable<C>();

    test_is_not_copy_assignable<void>();
    test_is_copy_assignable<phi::nullptr_t>();
    test_is_copy_assignable<bool>();
    test_is_copy_assignable<char>();
    test_is_copy_assignable<signed char>();
    test_is_copy_assignable<unsigned char>();
    test_is_copy_assignable<short>();
    test_is_copy_assignable<unsigned short>();
    test_is_copy_assignable<int>();
    test_is_copy_assignable<unsigned int>();
    test_is_copy_assignable<long>();
    test_is_copy_assignable<unsigned long>();
    test_is_copy_assignable<long long>();
    test_is_copy_assignable<unsigned long long>();
    test_is_copy_assignable<float>();
    test_is_copy_assignable<double>();
    test_is_copy_assignable<long double>();
    test_is_copy_assignable<char8_t>();
    test_is_copy_assignable<char16_t>();
    test_is_copy_assignable<char32_t>();
    test_is_copy_assignable<wchar_t>();

    test_is_copy_assignable<phi::boolean>();
    test_is_copy_assignable<phi::integer<signed char>>();
    test_is_copy_assignable<phi::integer<unsigned char>>();
    test_is_copy_assignable<phi::integer<short>>();
    test_is_copy_assignable<phi::integer<unsigned short>>();
    test_is_copy_assignable<phi::integer<int>>();
    test_is_copy_assignable<phi::integer<unsigned int>>();
    test_is_copy_assignable<phi::integer<long>>();
    test_is_copy_assignable<phi::integer<unsigned long>>();
    test_is_copy_assignable<phi::integer<long long>>();
    test_is_copy_assignable<phi::integer<unsigned long long>>();
    test_is_copy_assignable<phi::floating_point<float>>();
    test_is_copy_assignable<phi::floating_point<double>>();
    test_is_copy_assignable<phi::floating_point<long double>>();

    test_is_copy_assignable<std::vector<int>>();
    test_is_not_copy_assignable<phi::scope_ptr<int>>();

    test_is_copy_assignable<int&>();
    test_is_not_copy_assignable<const int&>();
    test_is_copy_assignable<volatile int&>();
    test_is_not_copy_assignable<const volatile int&>();
    test_is_copy_assignable<int&&>();
    test_is_not_copy_assignable<const int&&>();
    test_is_copy_assignable<volatile int&&>();
    test_is_not_copy_assignable<const volatile int&&>();
    test_is_copy_assignable<int*>();
    test_is_copy_assignable<const int*>();
    test_is_copy_assignable<volatile int*>();
    test_is_copy_assignable<const volatile int*>();
    test_is_copy_assignable<int**>();
    test_is_copy_assignable<const int**>();
    test_is_copy_assignable<volatile int**>();
    test_is_copy_assignable<const volatile int**>();
    test_is_copy_assignable<int*&>();
    test_is_copy_assignable<const int*&>();
    test_is_copy_assignable<volatile int*&>();
    test_is_copy_assignable<const volatile int*&>();
    test_is_copy_assignable<int*&&>();
    test_is_copy_assignable<const int*&&>();
    test_is_copy_assignable<volatile int*&&>();
    test_is_copy_assignable<const volatile int*&&>();
    test_is_copy_assignable<void*>();
    test_is_not_copy_assignable<char[3]>();
    test_is_not_copy_assignable<char[]>();
    test_is_not_copy_assignable<char* [3]>();
    test_is_not_copy_assignable<char*[]>();
    test_is_copy_assignable<int(*)[3]>();
    test_is_copy_assignable<int(*)[]>();
    test_is_not_copy_assignable<int(&)[3]>();
    test_is_not_copy_assignable<int(&)[]>();
    test_is_not_copy_assignable<int(&&)[3]>();
    test_is_not_copy_assignable<int(&&)[]>();
    test_is_not_copy_assignable<char[3][2]>();
    test_is_not_copy_assignable<char[][2]>();
    test_is_not_copy_assignable<char* [3][2]>();
    test_is_not_copy_assignable<char*[][2]>();
    test_is_copy_assignable<int(*)[3][2]>();
    test_is_copy_assignable<int(*)[][2]>();
    test_is_not_copy_assignable<int(&)[3][2]>();
    test_is_not_copy_assignable<int(&)[][2]>();
    test_is_not_copy_assignable<int(&&)[3][2]>();
    test_is_not_copy_assignable<int(&&)[][2]>();
    test_is_copy_assignable<Class>();
    test_is_not_copy_assignable<Class[]>();
    test_is_not_copy_assignable<Class[2]>();
    test_is_copy_assignable<Template<void>>();
    test_is_copy_assignable<Template<int>>();
    test_is_copy_assignable<Template<Class>>();
    test_is_copy_assignable<Template<incomplete_type>>();
    test_is_copy_assignable<VariadicTemplate<>>();
    test_is_copy_assignable<VariadicTemplate<void>>();
    test_is_copy_assignable<VariadicTemplate<int>>();
    test_is_copy_assignable<VariadicTemplate<Class>>();
    test_is_copy_assignable<VariadicTemplate<incomplete_type>>();
    test_is_copy_assignable<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_copy_assignable<PublicDerviedFromTemplate<Base>>();
    test_is_copy_assignable<PublicDerviedFromTemplate<Derived>>();
    test_is_copy_assignable<PublicDerviedFromTemplate<Class>>();
    test_is_copy_assignable<PrivateDerviedFromTemplate<Base>>();
    test_is_copy_assignable<PrivateDerviedFromTemplate<Derived>>();
    test_is_copy_assignable<PrivateDerviedFromTemplate<Class>>();
    test_is_copy_assignable<ProtectedDerviedFromTemplate<Base>>();
    test_is_copy_assignable<ProtectedDerviedFromTemplate<Derived>>();
    test_is_copy_assignable<ProtectedDerviedFromTemplate<Class>>();
    test_is_copy_assignable<Union>();
    test_is_copy_assignable<NonEmptyUnion>();
    test_is_copy_assignable<Empty>();
    test_is_copy_assignable<NotEmpty>();
    test_is_copy_assignable<bit_zero>();
    test_is_copy_assignable<bit_one>();
    test_is_copy_assignable<Base>();
    test_is_copy_assignable<Derived>();
    test_is_copy_assignable<Abstract>();
    test_is_copy_assignable<PublicAbstract>();
    test_is_copy_assignable<PrivateAbstract>();
    test_is_copy_assignable<ProtectedAbstract>();
    test_is_copy_assignable<AbstractTemplate<int>>();
    test_is_copy_assignable<AbstractTemplate<double>>();
    test_is_copy_assignable<AbstractTemplate<Class>>();
    test_is_copy_assignable<AbstractTemplate<incomplete_type>>();
    test_is_copy_assignable<Final>();
    test_is_copy_assignable<PublicDestructor>();
    test_is_copy_assignable<ProtectedDestructor>();
    test_is_copy_assignable<PrivateDestructor>();
    test_is_copy_assignable<VirtualPublicDestructor>();
    test_is_copy_assignable<VirtualProtectedDestructor>();
    test_is_copy_assignable<VirtualPrivateDestructor>();
    test_is_copy_assignable<PurePublicDestructor>();
    test_is_copy_assignable<PureProtectedDestructor>();
    test_is_copy_assignable<PurePrivateDestructor>();
    test_is_copy_assignable<DeletedPublicDestructor>();
    test_is_copy_assignable<DeletedProtectedDestructor>();
    test_is_copy_assignable<DeletedPrivateDestructor>();
    test_is_copy_assignable<DeletedVirtualPublicDestructor>();
    test_is_copy_assignable<DeletedVirtualProtectedDestructor>();
    test_is_copy_assignable<DeletedVirtualPrivateDestructor>();
    test_is_copy_assignable<Enum>();
    test_is_copy_assignable<EnumSigned>();
    test_is_copy_assignable<EnumUnsigned>();
    test_is_copy_assignable<EnumClass>();
    test_is_copy_assignable<EnumStruct>();
    test_is_not_copy_assignable<Function>();
    test_is_copy_assignable<FunctionPtr>();
    test_is_copy_assignable<MemberObjectPtr>();
    test_is_copy_assignable<MemberFunctionPtr>();
    //test_is_not_copy_assignable<incomplete_type>();
    //test_is_not_copy_assignable<IncompleteTemplate<void>>();
    //test_is_not_copy_assignable<IncompleteTemplate<int>>();
    //test_is_not_copy_assignable<IncompleteTemplate<Class>>();
    //test_is_not_copy_assignable<IncompleteTemplate<incomplete_type>>();
    //test_is_not_copy_assignable<IncompleteVariadicTemplate<>>();
    //test_is_not_copy_assignable<IncompleteVariadicTemplate<void>>();
    //test_is_not_copy_assignable<IncompleteVariadicTemplate<int>>();
    //test_is_not_copy_assignable<IncompleteVariadicTemplate<Class>>();
    //test_is_not_copy_assignable<IncompleteVariadicTemplate<incomplete_type>>();
    //test_is_not_copy_assignable<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_copy_assignable<int Class::*>();
    test_is_copy_assignable<float Class::*>();
    test_is_copy_assignable<void * Class::*>();
    test_is_copy_assignable<int * Class::*>();
    test_is_copy_assignable<int Class::*&>();
    test_is_copy_assignable<float Class::*&>();
    test_is_copy_assignable<void * Class::*&>();
    test_is_copy_assignable<int * Class::*&>();
    test_is_copy_assignable<int Class::*&&>();
    test_is_copy_assignable<float Class::*&&>();
    test_is_copy_assignable<void * Class::*&&>();
    test_is_copy_assignable<int * Class::*&&>();
    test_is_not_copy_assignable<int Class::*const>();
    test_is_not_copy_assignable<float Class::*const>();
    test_is_not_copy_assignable<void * Class::*const>();
    test_is_not_copy_assignable<int Class::*const&>();
    test_is_not_copy_assignable<float Class::*const&>();
    test_is_not_copy_assignable<void * Class::*const&>();
    test_is_not_copy_assignable<int Class::*const&&>();
    test_is_not_copy_assignable<float Class::*const&&>();
    test_is_not_copy_assignable<void * Class::*const&&>();
    test_is_copy_assignable<int Class::*volatile>();
    test_is_copy_assignable<float Class::*volatile>();
    test_is_copy_assignable<void * Class::*volatile>();
    test_is_copy_assignable<int Class::*volatile&>();
    test_is_copy_assignable<float Class::*volatile&>();
    test_is_copy_assignable<void * Class::*volatile&>();
    test_is_copy_assignable<int Class::*volatile&&>();
    test_is_copy_assignable<float Class::*volatile&&>();
    test_is_copy_assignable<void * Class::*volatile&&>();
    test_is_not_copy_assignable<int Class::*const volatile>();
    test_is_not_copy_assignable<float Class::*const volatile>();
    test_is_not_copy_assignable<void * Class::*const volatile>();
    test_is_not_copy_assignable<int Class::*const volatile&>();
    test_is_not_copy_assignable<float Class::*const volatile&>();
    test_is_not_copy_assignable<void * Class::*const volatile&>();
    test_is_not_copy_assignable<int Class::*const volatile&&>();
    test_is_not_copy_assignable<float Class::*const volatile&&>();
    test_is_not_copy_assignable<void * Class::*const volatile&&>();
    test_is_not_copy_assignable<NonCopyable>();
    test_is_copy_assignable<NonMoveable>();
    test_is_not_copy_assignable<NonConstructible>();
    test_is_copy_assignable<Tracked>();
    test_is_copy_assignable<TrapConstructible>();
    test_is_copy_assignable<TrapImplicitConversion>();
    test_is_copy_assignable<TrapComma>();
    test_is_copy_assignable<TrapCall>();
    test_is_copy_assignable<TrapSelfAssign>();
    test_is_copy_assignable<TrapDeref>();
    test_is_copy_assignable<TrapArraySubscript>();

    test_is_not_copy_assignable<void()>();
    test_is_not_copy_assignable<void()&>();
    test_is_not_copy_assignable<void() &&>();
    test_is_not_copy_assignable<void() const>();
    test_is_not_copy_assignable<void() const&>();
    test_is_not_copy_assignable<void() const&&>();
    test_is_not_copy_assignable<void() volatile>();
    test_is_not_copy_assignable<void() volatile&>();
    test_is_not_copy_assignable<void() volatile&&>();
    test_is_not_copy_assignable<void() const volatile>();
    test_is_not_copy_assignable<void() const volatile&>();
    test_is_not_copy_assignable<void() const volatile&&>();
    test_is_not_copy_assignable<void() noexcept>();
    test_is_not_copy_assignable<void()& noexcept>();
    test_is_not_copy_assignable<void()&& noexcept>();
    test_is_not_copy_assignable<void() const noexcept>();
    test_is_not_copy_assignable<void() const& noexcept>();
    test_is_not_copy_assignable<void() const&& noexcept>();
    test_is_not_copy_assignable<void() volatile noexcept>();
    test_is_not_copy_assignable<void() volatile& noexcept>();
    test_is_not_copy_assignable<void() volatile&& noexcept>();
    test_is_not_copy_assignable<void() const volatile noexcept>();
    test_is_not_copy_assignable<void() const volatile& noexcept>();
    test_is_not_copy_assignable<void() const volatile&& noexcept>();

    test_is_not_copy_assignable<void(int)>();
    test_is_not_copy_assignable<void(int)&>();
    test_is_not_copy_assignable<void(int) &&>();
    test_is_not_copy_assignable<void(int) const>();
    test_is_not_copy_assignable<void(int) const&>();
    test_is_not_copy_assignable<void(int) const&&>();
    test_is_not_copy_assignable<void(int) volatile>();
    test_is_not_copy_assignable<void(int) volatile&>();
    test_is_not_copy_assignable<void(int) volatile&&>();
    test_is_not_copy_assignable<void(int) const volatile>();
    test_is_not_copy_assignable<void(int) const volatile&>();
    test_is_not_copy_assignable<void(int) const volatile&&>();
    test_is_not_copy_assignable<void(int) noexcept>();
    test_is_not_copy_assignable<void(int)& noexcept>();
    test_is_not_copy_assignable<void(int)&& noexcept>();
    test_is_not_copy_assignable<void(int) const noexcept>();
    test_is_not_copy_assignable<void(int) const& noexcept>();
    test_is_not_copy_assignable<void(int) const&& noexcept>();
    test_is_not_copy_assignable<void(int) volatile noexcept>();
    test_is_not_copy_assignable<void(int) volatile& noexcept>();
    test_is_not_copy_assignable<void(int) volatile&& noexcept>();
    test_is_not_copy_assignable<void(int) const volatile noexcept>();
    test_is_not_copy_assignable<void(int) const volatile& noexcept>();
    test_is_not_copy_assignable<void(int) const volatile&& noexcept>();

    test_is_not_copy_assignable<void(...)>();
    test_is_not_copy_assignable<void(...)&>();
    test_is_not_copy_assignable<void(...) &&>();
    test_is_not_copy_assignable<void(...) const>();
    test_is_not_copy_assignable<void(...) const&>();
    test_is_not_copy_assignable<void(...) const&&>();
    test_is_not_copy_assignable<void(...) volatile>();
    test_is_not_copy_assignable<void(...) volatile&>();
    test_is_not_copy_assignable<void(...) volatile&&>();
    test_is_not_copy_assignable<void(...) const volatile>();
    test_is_not_copy_assignable<void(...) const volatile&>();
    test_is_not_copy_assignable<void(...) const volatile&&>();
    test_is_not_copy_assignable<void(...) noexcept>();
    test_is_not_copy_assignable<void(...)& noexcept>();
    test_is_not_copy_assignable<void(...)&& noexcept>();
    test_is_not_copy_assignable<void(...) const noexcept>();
    test_is_not_copy_assignable<void(...) const& noexcept>();
    test_is_not_copy_assignable<void(...) const&& noexcept>();
    test_is_not_copy_assignable<void(...) volatile noexcept>();
    test_is_not_copy_assignable<void(...) volatile& noexcept>();
    test_is_not_copy_assignable<void(...) volatile&& noexcept>();
    test_is_not_copy_assignable<void(...) const volatile noexcept>();
    test_is_not_copy_assignable<void(...) const volatile& noexcept>();
    test_is_not_copy_assignable<void(...) const volatile&& noexcept>();

    test_is_not_copy_assignable<void(int, ...)>();
    test_is_not_copy_assignable<void(int, ...)&>();
    test_is_not_copy_assignable<void(int, ...) &&>();
    test_is_not_copy_assignable<void(int, ...) const>();
    test_is_not_copy_assignable<void(int, ...) const&>();
    test_is_not_copy_assignable<void(int, ...) const&&>();
    test_is_not_copy_assignable<void(int, ...) volatile>();
    test_is_not_copy_assignable<void(int, ...) volatile&>();
    test_is_not_copy_assignable<void(int, ...) volatile&&>();
    test_is_not_copy_assignable<void(int, ...) const volatile>();
    test_is_not_copy_assignable<void(int, ...) const volatile&>();
    test_is_not_copy_assignable<void(int, ...) const volatile&&>();
    test_is_not_copy_assignable<void(int, ...) noexcept>();
    test_is_not_copy_assignable<void(int, ...)& noexcept>();
    test_is_not_copy_assignable<void(int, ...)&& noexcept>();
    test_is_not_copy_assignable<void(int, ...) const noexcept>();
    test_is_not_copy_assignable<void(int, ...) const& noexcept>();
    test_is_not_copy_assignable<void(int, ...) const&& noexcept>();
    test_is_not_copy_assignable<void(int, ...) volatile noexcept>();
    test_is_not_copy_assignable<void(int, ...) volatile& noexcept>();
    test_is_not_copy_assignable<void(int, ...) volatile&& noexcept>();
    test_is_not_copy_assignable<void(int, ...) const volatile noexcept>();
    test_is_not_copy_assignable<void(int, ...) const volatile& noexcept>();
    test_is_not_copy_assignable<void(int, ...) const volatile&& noexcept>();

    test_is_not_copy_assignable<int()>();
    test_is_not_copy_assignable<int()&>();
    test_is_not_copy_assignable<int() &&>();
    test_is_not_copy_assignable<int() const>();
    test_is_not_copy_assignable<int() const&>();
    test_is_not_copy_assignable<int() const&&>();
    test_is_not_copy_assignable<int() volatile>();
    test_is_not_copy_assignable<int() volatile&>();
    test_is_not_copy_assignable<int() volatile&&>();
    test_is_not_copy_assignable<int() const volatile>();
    test_is_not_copy_assignable<int() const volatile&>();
    test_is_not_copy_assignable<int() const volatile&&>();
    test_is_not_copy_assignable<int() noexcept>();
    test_is_not_copy_assignable<int()& noexcept>();
    test_is_not_copy_assignable<int()&& noexcept>();
    test_is_not_copy_assignable<int() const noexcept>();
    test_is_not_copy_assignable<int() const& noexcept>();
    test_is_not_copy_assignable<int() const&& noexcept>();
    test_is_not_copy_assignable<int() volatile noexcept>();
    test_is_not_copy_assignable<int() volatile& noexcept>();
    test_is_not_copy_assignable<int() volatile&& noexcept>();
    test_is_not_copy_assignable<int() const volatile noexcept>();
    test_is_not_copy_assignable<int() const volatile& noexcept>();
    test_is_not_copy_assignable<int() const volatile&& noexcept>();

    test_is_not_copy_assignable<int(int)>();
    test_is_not_copy_assignable<int(int)&>();
    test_is_not_copy_assignable<int(int) &&>();
    test_is_not_copy_assignable<int(int) const>();
    test_is_not_copy_assignable<int(int) const&>();
    test_is_not_copy_assignable<int(int) const&&>();
    test_is_not_copy_assignable<int(int) volatile>();
    test_is_not_copy_assignable<int(int) volatile&>();
    test_is_not_copy_assignable<int(int) volatile&&>();
    test_is_not_copy_assignable<int(int) const volatile>();
    test_is_not_copy_assignable<int(int) const volatile&>();
    test_is_not_copy_assignable<int(int) const volatile&&>();
    test_is_not_copy_assignable<int(int) noexcept>();
    test_is_not_copy_assignable<int(int)& noexcept>();
    test_is_not_copy_assignable<int(int)&& noexcept>();
    test_is_not_copy_assignable<int(int) const noexcept>();
    test_is_not_copy_assignable<int(int) const& noexcept>();
    test_is_not_copy_assignable<int(int) const&& noexcept>();
    test_is_not_copy_assignable<int(int) volatile noexcept>();
    test_is_not_copy_assignable<int(int) volatile& noexcept>();
    test_is_not_copy_assignable<int(int) volatile&& noexcept>();
    test_is_not_copy_assignable<int(int) const volatile noexcept>();
    test_is_not_copy_assignable<int(int) const volatile& noexcept>();
    test_is_not_copy_assignable<int(int) const volatile&& noexcept>();

    test_is_not_copy_assignable<int(...)>();
    test_is_not_copy_assignable<int(...)&>();
    test_is_not_copy_assignable<int(...) &&>();
    test_is_not_copy_assignable<int(...) const>();
    test_is_not_copy_assignable<int(...) const&>();
    test_is_not_copy_assignable<int(...) const&&>();
    test_is_not_copy_assignable<int(...) volatile>();
    test_is_not_copy_assignable<int(...) volatile&>();
    test_is_not_copy_assignable<int(...) volatile&&>();
    test_is_not_copy_assignable<int(...) const volatile>();
    test_is_not_copy_assignable<int(...) const volatile&>();
    test_is_not_copy_assignable<int(...) const volatile&&>();
    test_is_not_copy_assignable<int(...) noexcept>();
    test_is_not_copy_assignable<int(...)& noexcept>();
    test_is_not_copy_assignable<int(...)&& noexcept>();
    test_is_not_copy_assignable<int(...) const noexcept>();
    test_is_not_copy_assignable<int(...) const& noexcept>();
    test_is_not_copy_assignable<int(...) const&& noexcept>();
    test_is_not_copy_assignable<int(...) volatile noexcept>();
    test_is_not_copy_assignable<int(...) volatile& noexcept>();
    test_is_not_copy_assignable<int(...) volatile&& noexcept>();
    test_is_not_copy_assignable<int(...) const volatile noexcept>();
    test_is_not_copy_assignable<int(...) const volatile& noexcept>();
    test_is_not_copy_assignable<int(...) const volatile&& noexcept>();

    test_is_not_copy_assignable<int(int, ...)>();
    test_is_not_copy_assignable<int(int, ...)&>();
    test_is_not_copy_assignable<int(int, ...) &&>();
    test_is_not_copy_assignable<int(int, ...) const>();
    test_is_not_copy_assignable<int(int, ...) const&>();
    test_is_not_copy_assignable<int(int, ...) const&&>();
    test_is_not_copy_assignable<int(int, ...) volatile>();
    test_is_not_copy_assignable<int(int, ...) volatile&>();
    test_is_not_copy_assignable<int(int, ...) volatile&&>();
    test_is_not_copy_assignable<int(int, ...) const volatile>();
    test_is_not_copy_assignable<int(int, ...) const volatile&>();
    test_is_not_copy_assignable<int(int, ...) const volatile&&>();
    test_is_not_copy_assignable<int(int, ...) noexcept>();
    test_is_not_copy_assignable<int(int, ...)& noexcept>();
    test_is_not_copy_assignable<int(int, ...)&& noexcept>();
    test_is_not_copy_assignable<int(int, ...) const noexcept>();
    test_is_not_copy_assignable<int(int, ...) const& noexcept>();
    test_is_not_copy_assignable<int(int, ...) const&& noexcept>();
    test_is_not_copy_assignable<int(int, ...) volatile noexcept>();
    test_is_not_copy_assignable<int(int, ...) volatile& noexcept>();
    test_is_not_copy_assignable<int(int, ...) volatile&& noexcept>();
    test_is_not_copy_assignable<int(int, ...) const volatile noexcept>();
    test_is_not_copy_assignable<int(int, ...) const volatile& noexcept>();
    test_is_not_copy_assignable<int(int, ...) const volatile&& noexcept>();

    test_is_copy_assignable<void (*)()>();
    test_is_copy_assignable<void (*)() noexcept>();

    test_is_copy_assignable<void (*)(int)>();
    test_is_copy_assignable<void (*)(int) noexcept>();

    test_is_copy_assignable<void (*)(...)>();
    test_is_copy_assignable<void (*)(...) noexcept>();

    test_is_copy_assignable<void (*)(int, ...)>();
    test_is_copy_assignable<void (*)(int, ...) noexcept>();

    test_is_copy_assignable<int (*)()>();
    test_is_copy_assignable<int (*)() noexcept>();

    test_is_copy_assignable<int (*)(int)>();
    test_is_copy_assignable<int (*)(int) noexcept>();

    test_is_copy_assignable<int (*)(...)>();
    test_is_copy_assignable<int (*)(...) noexcept>();

    test_is_copy_assignable<int (*)(int, ...)>();
    test_is_copy_assignable<int (*)(int, ...) noexcept>();

    test_is_not_copy_assignable<void (&)()>();
    test_is_not_copy_assignable<void (&)() noexcept>();

    test_is_not_copy_assignable<void (&)(int)>();
    test_is_not_copy_assignable<void (&)(int) noexcept>();

    test_is_not_copy_assignable<void (&)(...)>();
    test_is_not_copy_assignable<void (&)(...) noexcept>();

    test_is_not_copy_assignable<void (&)(int, ...)>();
    test_is_not_copy_assignable<void (&)(int, ...) noexcept>();

    test_is_not_copy_assignable<int (&)()>();
    test_is_not_copy_assignable<int (&)() noexcept>();

    test_is_not_copy_assignable<int (&)(int)>();
    test_is_not_copy_assignable<int (&)(int) noexcept>();

    test_is_not_copy_assignable<int (&)(...)>();
    test_is_not_copy_assignable<int (&)(...) noexcept>();

    test_is_not_copy_assignable<int (&)(int, ...)>();
    test_is_not_copy_assignable<int (&)(int, ...) noexcept>();

    test_is_not_copy_assignable<void(&&)()>();
    test_is_not_copy_assignable<void(&&)() noexcept>();

    test_is_not_copy_assignable<void(&&)(int)>();
    test_is_not_copy_assignable<void(&&)(int) noexcept>();

    test_is_not_copy_assignable<void(&&)(...)>();
    test_is_not_copy_assignable<void(&&)(...) noexcept>();

    test_is_not_copy_assignable<void(&&)(int, ...)>();
    test_is_not_copy_assignable<void(&&)(int, ...) noexcept>();

    test_is_not_copy_assignable<int(&&)()>();
    test_is_not_copy_assignable<int(&&)() noexcept>();

    test_is_not_copy_assignable<int(&&)(int)>();
    test_is_not_copy_assignable<int(&&)(int) noexcept>();

    test_is_not_copy_assignable<int(&&)(...)>();
    test_is_not_copy_assignable<int(&&)(...) noexcept>();

    test_is_not_copy_assignable<int(&&)(int, ...)>();
    test_is_not_copy_assignable<int(&&)(int, ...) noexcept>();

    test_is_copy_assignable<void (Class::*)()>();
    test_is_copy_assignable<void (Class::*)()&>();
    test_is_copy_assignable<void (Class::*)() &&>();
    test_is_copy_assignable<void (Class::*)() const>();
    test_is_copy_assignable<void (Class::*)() const&>();
    test_is_copy_assignable<void (Class::*)() const&&>();
    test_is_copy_assignable<void (Class::*)() noexcept>();
    test_is_copy_assignable<void (Class::*)()& noexcept>();
    test_is_copy_assignable<void (Class::*)()&& noexcept>();
    test_is_copy_assignable<void (Class::*)() const noexcept>();
    test_is_copy_assignable<void (Class::*)() const& noexcept>();
    test_is_copy_assignable<void (Class::*)() const&& noexcept>();

    test_is_copy_assignable<void (Class::*)(int)>();
    test_is_copy_assignable<void (Class::*)(int)&>();
    test_is_copy_assignable<void (Class::*)(int) &&>();
    test_is_copy_assignable<void (Class::*)(int) const>();
    test_is_copy_assignable<void (Class::*)(int) const&>();
    test_is_copy_assignable<void (Class::*)(int) const&&>();
    test_is_copy_assignable<void (Class::*)(int) noexcept>();
    test_is_copy_assignable<void (Class::*)(int)& noexcept>();
    test_is_copy_assignable<void (Class::*)(int)&& noexcept>();
    test_is_copy_assignable<void (Class::*)(int) const noexcept>();
    test_is_copy_assignable<void (Class::*)(int) const& noexcept>();
    test_is_copy_assignable<void (Class::*)(int) const&& noexcept>();

    test_is_copy_assignable<void (Class::*)(...)>();
    test_is_copy_assignable<void (Class::*)(...)&>();
    test_is_copy_assignable<void (Class::*)(...) &&>();
    test_is_copy_assignable<void (Class::*)(...) const>();
    test_is_copy_assignable<void (Class::*)(...) const&>();
    test_is_copy_assignable<void (Class::*)(...) const&&>();
    test_is_copy_assignable<void (Class::*)(...) noexcept>();
    test_is_copy_assignable<void (Class::*)(...)& noexcept>();
    test_is_copy_assignable<void (Class::*)(...)&& noexcept>();
    test_is_copy_assignable<void (Class::*)(...) const noexcept>();
    test_is_copy_assignable<void (Class::*)(...) const& noexcept>();
    test_is_copy_assignable<void (Class::*)(...) const&& noexcept>();

    test_is_copy_assignable<void (Class::*)(int, ...)>();
    test_is_copy_assignable<void (Class::*)(int, ...)&>();
    test_is_copy_assignable<void (Class::*)(int, ...) &&>();
    test_is_copy_assignable<void (Class::*)(int, ...) const>();
    test_is_copy_assignable<void (Class::*)(int, ...) const&>();
    test_is_copy_assignable<void (Class::*)(int, ...) const&&>();
    test_is_copy_assignable<void (Class::*)(int, ...) noexcept>();
    test_is_copy_assignable<void (Class::*)(int, ...)& noexcept>();
    test_is_copy_assignable<void (Class::*)(int, ...)&& noexcept>();
    test_is_copy_assignable<void (Class::*)(int, ...) const noexcept>();
    test_is_copy_assignable<void (Class::*)(int, ...) const& noexcept>();
    test_is_copy_assignable<void (Class::*)(int, ...) const&& noexcept>();

    test_is_copy_assignable<int (Class::*)()>();
    test_is_copy_assignable<int (Class::*)()&>();
    test_is_copy_assignable<int (Class::*)() &&>();
    test_is_copy_assignable<int (Class::*)() const>();
    test_is_copy_assignable<int (Class::*)() const&>();
    test_is_copy_assignable<int (Class::*)() const&&>();
    test_is_copy_assignable<int (Class::*)() noexcept>();
    test_is_copy_assignable<int (Class::*)()& noexcept>();
    test_is_copy_assignable<int (Class::*)()&& noexcept>();
    test_is_copy_assignable<int (Class::*)() const noexcept>();
    test_is_copy_assignable<int (Class::*)() const& noexcept>();
    test_is_copy_assignable<int (Class::*)() const&& noexcept>();

    test_is_copy_assignable<int (Class::*)(int)>();
    test_is_copy_assignable<int (Class::*)(int)&>();
    test_is_copy_assignable<int (Class::*)(int) &&>();
    test_is_copy_assignable<int (Class::*)(int) const>();
    test_is_copy_assignable<int (Class::*)(int) const&>();
    test_is_copy_assignable<int (Class::*)(int) const&&>();
    test_is_copy_assignable<int (Class::*)(int) noexcept>();
    test_is_copy_assignable<int (Class::*)(int)& noexcept>();
    test_is_copy_assignable<int (Class::*)(int)&& noexcept>();
    test_is_copy_assignable<int (Class::*)(int) const noexcept>();
    test_is_copy_assignable<int (Class::*)(int) const& noexcept>();
    test_is_copy_assignable<int (Class::*)(int) const&& noexcept>();

    test_is_copy_assignable<int (Class::*)(...)>();
    test_is_copy_assignable<int (Class::*)(...)&>();
    test_is_copy_assignable<int (Class::*)(...) &&>();
    test_is_copy_assignable<int (Class::*)(...) const>();
    test_is_copy_assignable<int (Class::*)(...) const&>();
    test_is_copy_assignable<int (Class::*)(...) const&&>();
    test_is_copy_assignable<int (Class::*)(...) noexcept>();
    test_is_copy_assignable<int (Class::*)(...)& noexcept>();
    test_is_copy_assignable<int (Class::*)(...)&& noexcept>();
    test_is_copy_assignable<int (Class::*)(...) const noexcept>();
    test_is_copy_assignable<int (Class::*)(...) const& noexcept>();
    test_is_copy_assignable<int (Class::*)(...) const&& noexcept>();

    test_is_copy_assignable<int (Class::*)(int, ...)>();
    test_is_copy_assignable<int (Class::*)(int, ...)&>();
    test_is_copy_assignable<int (Class::*)(int, ...) &&>();
    test_is_copy_assignable<int (Class::*)(int, ...) const>();
    test_is_copy_assignable<int (Class::*)(int, ...) const&>();
    test_is_copy_assignable<int (Class::*)(int, ...) const&&>();
    test_is_copy_assignable<int (Class::*)(int, ...) noexcept>();
    test_is_copy_assignable<int (Class::*)(int, ...)& noexcept>();
    test_is_copy_assignable<int (Class::*)(int, ...)&& noexcept>();
    test_is_copy_assignable<int (Class::*)(int, ...) const noexcept>();
    test_is_copy_assignable<int (Class::*)(int, ...) const& noexcept>();
    test_is_copy_assignable<int (Class::*)(int, ...) const&& noexcept>();
}
