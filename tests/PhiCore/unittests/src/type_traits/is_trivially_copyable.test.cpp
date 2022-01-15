#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_trivially_copyable.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_trivially_copyable_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE()
    STATIC_REQUIRE(phi::is_trivially_copyable<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_copyable<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_copyable_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_copyable_v<T>);
#    endif

    // Standard compatibility
    STATIC_REQUIRE(std::is_trivially_copyable<T>::value);
#endif
}

template <typename T>
void test_is_not_trivially_copyable_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_copyable<T>::value);
    STATIC_REQUIRE(phi::is_not_trivially_copyable<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_copyable_v<T>);
    STATIC_REQUIRE(phi::is_not_trivially_copyable_v<T>);
#    endif

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_trivially_copyable<T>::value);
#endif
}

template <typename T>
void test_is_trivially_copyable()
{
    test_is_trivially_copyable_impl<T>();
    test_is_trivially_copyable_impl<const T>();
    test_is_trivially_copyable_impl<volatile T>();
    test_is_trivially_copyable_impl<const volatile T>();
}

template <typename T>
void test_is_not_trivially_copyable()
{
    test_is_not_trivially_copyable_impl<T>();
    test_is_not_trivially_copyable_impl<const T>();
    test_is_not_trivially_copyable_impl<volatile T>();
    test_is_not_trivially_copyable_impl<const volatile T>();
}

template <typename T>
void test_is_trivially_copyable_gcc_compat()
{
    test_is_trivially_copyable_impl<T>();
    test_is_trivially_copyable_impl<const T>();
#if PHI_COMPILER_IS_BELOW(GCC, 10, 0, 0)
    test_is_not_trivially_copyable_impl<volatile T>();
    test_is_not_trivially_copyable_impl<const volatile T>();
#else
    test_is_trivially_copyable_impl<volatile T>();
    test_is_trivially_copyable_impl<const volatile T>();
#endif
}

template <typename T>
void test_is_trivially_copyable_gcc_compat_volatile()
{
#if PHI_COMPILER_IS_BELOW(GCC, 10, 0, 0)
    test_is_not_trivially_copyable<T>();
#else
    test_is_trivially_copyable<T>();
#endif
}

struct A
{
    int i;
};

struct B
{
    int i;

    ~B()
    {
        i = 3;
    }
};

class C
{
public:
    C();
};

struct S
{
    S(S const&) = default;
    S(S&&)      = default;
    S& operator=(S const&) = delete;
    S& operator=(S&&) = delete;
};

TEST_CASE("is_trivially_copyable")
{
    test_is_trivially_copyable<A>();
    test_is_not_trivially_copyable<A&>();
    test_is_not_trivially_copyable<const A&>();
    test_is_not_trivially_copyable<B>();
    test_is_not_trivially_copyable<B&>();
    test_is_not_trivially_copyable<const B&>();
    test_is_trivially_copyable<C>();
    test_is_not_trivially_copyable<C&>();
    test_is_not_trivially_copyable<const C&>();

    test_is_trivially_copyable<S>();

    test_is_not_trivially_copyable<void>();
    test_is_trivially_copyable_gcc_compat<phi::nullptr_t>();
    test_is_trivially_copyable_gcc_compat<bool>();
    test_is_trivially_copyable_gcc_compat<char>();
    test_is_trivially_copyable_gcc_compat<signed char>();
    test_is_trivially_copyable_gcc_compat<unsigned char>();
    test_is_trivially_copyable_gcc_compat<short>();
    test_is_trivially_copyable_gcc_compat<unsigned short>();
    test_is_trivially_copyable_gcc_compat<int>();
    test_is_trivially_copyable_gcc_compat<unsigned int>();
    test_is_trivially_copyable_gcc_compat<long>();
    test_is_trivially_copyable_gcc_compat<unsigned long>();
    test_is_trivially_copyable_gcc_compat<long long>();
    test_is_trivially_copyable_gcc_compat<unsigned long long>();
    test_is_trivially_copyable_gcc_compat<float>();
    test_is_trivially_copyable_gcc_compat<double>();
    test_is_trivially_copyable_gcc_compat<long double>();
    test_is_trivially_copyable_gcc_compat<char8_t>();
    test_is_trivially_copyable_gcc_compat<char16_t>();
    test_is_trivially_copyable_gcc_compat<char32_t>();
    test_is_trivially_copyable_gcc_compat<wchar_t>();

    test_is_trivially_copyable<phi::boolean>();
    test_is_trivially_copyable<phi::integer<signed char>>();
    test_is_trivially_copyable<phi::integer<unsigned char>>();
    test_is_trivially_copyable<phi::integer<short>>();
    test_is_trivially_copyable<phi::integer<unsigned short>>();
    test_is_trivially_copyable<phi::integer<int>>();
    test_is_trivially_copyable<phi::integer<unsigned int>>();
    test_is_trivially_copyable<phi::integer<long>>();
    test_is_trivially_copyable<phi::integer<unsigned long>>();
    test_is_trivially_copyable<phi::integer<long long>>();
    test_is_trivially_copyable<phi::integer<unsigned long long>>();
    test_is_trivially_copyable<phi::floating_point<float>>();
    test_is_trivially_copyable<phi::floating_point<double>>();
    test_is_trivially_copyable<phi::floating_point<long double>>();

    test_is_not_trivially_copyable<std::vector<int>>();
    test_is_not_trivially_copyable<phi::scope_ptr<int>>();

    test_is_not_trivially_copyable<int&>();
    test_is_not_trivially_copyable<const int&>();
    test_is_not_trivially_copyable<volatile int&>();
    test_is_not_trivially_copyable<const volatile int&>();
    test_is_not_trivially_copyable<int&&>();
    test_is_not_trivially_copyable<const int&&>();
    test_is_not_trivially_copyable<volatile int&&>();
    test_is_not_trivially_copyable<const volatile int&&>();
    test_is_trivially_copyable_gcc_compat<int*>();
    test_is_trivially_copyable_gcc_compat<const int*>();
    test_is_trivially_copyable_gcc_compat<volatile int*>();
    test_is_trivially_copyable_gcc_compat<const volatile int*>();
    test_is_trivially_copyable_gcc_compat<int**>();
    test_is_trivially_copyable_gcc_compat<const int**>();
    test_is_trivially_copyable_gcc_compat<volatile int**>();
    test_is_trivially_copyable_gcc_compat<const volatile int**>();
    test_is_not_trivially_copyable<int*&>();
    test_is_not_trivially_copyable<const int*&>();
    test_is_not_trivially_copyable<volatile int*&>();
    test_is_not_trivially_copyable<const volatile int*&>();
    test_is_not_trivially_copyable<int*&&>();
    test_is_not_trivially_copyable<const int*&&>();
    test_is_not_trivially_copyable<volatile int*&&>();
    test_is_not_trivially_copyable<const volatile int*&&>();
    test_is_trivially_copyable_gcc_compat<void*>();
    test_is_trivially_copyable_gcc_compat<char[3]>();
    test_is_trivially_copyable_gcc_compat<char[]>();
    test_is_trivially_copyable_gcc_compat<char* [3]>();
    test_is_trivially_copyable_gcc_compat<char*[]>();
    test_is_trivially_copyable_gcc_compat<int(*)[3]>();
    test_is_trivially_copyable_gcc_compat<int(*)[]>();
    test_is_not_trivially_copyable<int(&)[3]>();
    test_is_not_trivially_copyable<int(&)[]>();
    test_is_not_trivially_copyable<int(&&)[3]>();
    test_is_not_trivially_copyable<int(&&)[]>();
    test_is_trivially_copyable_gcc_compat<char[3][2]>();
    test_is_trivially_copyable_gcc_compat<char[][2]>();
    test_is_trivially_copyable_gcc_compat<char* [3][2]>();
    test_is_trivially_copyable_gcc_compat<char*[][2]>();
    test_is_trivially_copyable_gcc_compat<int(*)[3][2]>();
    test_is_trivially_copyable_gcc_compat<int(*)[][2]>();
    test_is_not_trivially_copyable<int(&)[3][2]>();
    test_is_not_trivially_copyable<int(&)[][2]>();
    test_is_not_trivially_copyable<int(&&)[3][2]>();
    test_is_not_trivially_copyable<int(&&)[][2]>();
    test_is_not_trivially_copyable<Class>();
    test_is_not_trivially_copyable<Class[]>();
    test_is_not_trivially_copyable<Class[2]>();
    test_is_trivially_copyable<Template<void>>();
    test_is_trivially_copyable<Template<int>>();
    test_is_trivially_copyable<Template<Class>>();
    test_is_trivially_copyable<Template<incomplete_type>>();
    test_is_trivially_copyable<VariadicTemplate<>>();
    test_is_trivially_copyable<VariadicTemplate<void>>();
    test_is_trivially_copyable<VariadicTemplate<int>>();
    test_is_trivially_copyable<VariadicTemplate<Class>>();
    test_is_trivially_copyable<VariadicTemplate<incomplete_type>>();
    test_is_trivially_copyable<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_trivially_copyable<PublicDerviedFromTemplate<Base>>();
    test_is_trivially_copyable<PublicDerviedFromTemplate<Derived>>();
    test_is_not_trivially_copyable<PublicDerviedFromTemplate<Class>>();
    test_is_trivially_copyable<PrivateDerviedFromTemplate<Base>>();
    test_is_trivially_copyable<PrivateDerviedFromTemplate<Derived>>();
    test_is_not_trivially_copyable<PrivateDerviedFromTemplate<Class>>();
    test_is_trivially_copyable<ProtectedDerviedFromTemplate<Base>>();
    test_is_trivially_copyable<ProtectedDerviedFromTemplate<Derived>>();
    test_is_not_trivially_copyable<ProtectedDerviedFromTemplate<Class>>();
    test_is_trivially_copyable<Union>();
    test_is_trivially_copyable<NonEmptyUnion>();
    test_is_trivially_copyable<Empty>();
    test_is_not_trivially_copyable<NotEmpty>();
    test_is_trivially_copyable<bit_zero>();
    test_is_trivially_copyable<bit_one>();
    test_is_trivially_copyable<Base>();
    test_is_trivially_copyable<Derived>();
    test_is_not_trivially_copyable<Abstract>();
    test_is_not_trivially_copyable<PublicAbstract>();
    test_is_not_trivially_copyable<PrivateAbstract>();
    test_is_not_trivially_copyable<ProtectedAbstract>();
    test_is_not_trivially_copyable<AbstractTemplate<int>>();
    test_is_trivially_copyable<AbstractTemplate<double>>();
    test_is_not_trivially_copyable<AbstractTemplate<Class>>();
    test_is_not_trivially_copyable<AbstractTemplate<incomplete_type>>();
    test_is_trivially_copyable<Final>();
    test_is_trivially_copyable<PublicDestructor>();
    test_is_trivially_copyable<ProtectedDestructor>();
    test_is_trivially_copyable<PrivateDestructor>();
    test_is_not_trivially_copyable<VirtualPublicDestructor>();
    test_is_not_trivially_copyable<VirtualProtectedDestructor>();
    test_is_not_trivially_copyable<VirtualPrivateDestructor>();
    test_is_not_trivially_copyable<PurePublicDestructor>();
    test_is_not_trivially_copyable<PureProtectedDestructor>();
    test_is_not_trivially_copyable<PurePrivateDestructor>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivially_copyable<DeletedPublicDestructor>();
    test_is_not_trivially_copyable<DeletedProtectedDestructor>();
    test_is_not_trivially_copyable<DeletedPrivateDestructor>();
#else
    test_is_trivially_copyable<DeletedPublicDestructor>();
    test_is_trivially_copyable<DeletedProtectedDestructor>();
    test_is_trivially_copyable<DeletedPrivateDestructor>();
#endif
    test_is_not_trivially_copyable<DeletedVirtualPublicDestructor>();
    test_is_not_trivially_copyable<DeletedVirtualProtectedDestructor>();
    test_is_not_trivially_copyable<DeletedVirtualPrivateDestructor>();
    test_is_trivially_copyable_gcc_compat<Enum>();
    test_is_trivially_copyable_gcc_compat<EnumSigned>();
    test_is_trivially_copyable_gcc_compat<EnumUnsigned>();
    test_is_trivially_copyable_gcc_compat<EnumClass>();
    test_is_trivially_copyable_gcc_compat<EnumStruct>();
    test_is_not_trivially_copyable<Function>();
    test_is_trivially_copyable_gcc_compat<FunctionPtr>();
    test_is_trivially_copyable_gcc_compat<MemberObjectPtr>();
    test_is_trivially_copyable_gcc_compat<MemberFunctionPtr>();
    test_is_trivially_copyable_gcc_compat<int Class::*>();
    test_is_trivially_copyable_gcc_compat<float Class::*>();
    test_is_trivially_copyable_gcc_compat<void * Class::*>();
    test_is_trivially_copyable_gcc_compat<int * Class::*>();
    test_is_not_trivially_copyable<int Class::*&>();
    test_is_not_trivially_copyable<float Class::*&>();
    test_is_not_trivially_copyable<void * Class::*&>();
    test_is_not_trivially_copyable<int * Class::*&>();
    test_is_not_trivially_copyable<int Class::*&&>();
    test_is_not_trivially_copyable<float Class::*&&>();
    test_is_not_trivially_copyable<void * Class::*&&>();
    test_is_not_trivially_copyable<int * Class::*&&>();
    test_is_trivially_copyable_gcc_compat<int Class::*const>();
    test_is_trivially_copyable_gcc_compat<float Class::*const>();
    test_is_trivially_copyable_gcc_compat<void * Class::*const>();
    test_is_not_trivially_copyable<int Class::*const&>();
    test_is_not_trivially_copyable<float Class::*const&>();
    test_is_not_trivially_copyable<void * Class::*const&>();
    test_is_not_trivially_copyable<int Class::*const&&>();
    test_is_not_trivially_copyable<float Class::*const&&>();
    test_is_not_trivially_copyable<void * Class::*const&&>();
    test_is_trivially_copyable_gcc_compat_volatile<int Class::*volatile>();
    test_is_trivially_copyable_gcc_compat_volatile<float Class::*volatile>();
    test_is_trivially_copyable_gcc_compat_volatile<void * Class::*volatile>();
    test_is_not_trivially_copyable<int Class::*volatile&>();
    test_is_not_trivially_copyable<float Class::*volatile&>();
    test_is_not_trivially_copyable<void * Class::*volatile&>();
    test_is_not_trivially_copyable<int Class::*volatile&&>();
    test_is_not_trivially_copyable<float Class::*volatile&&>();
    test_is_not_trivially_copyable<void * Class::*volatile&&>();
    test_is_trivially_copyable_gcc_compat_volatile<int Class::*const volatile>();
    test_is_trivially_copyable_gcc_compat_volatile<float Class::*const volatile>();
    test_is_trivially_copyable_gcc_compat_volatile<void * Class::*const volatile>();
    test_is_not_trivially_copyable<int Class::*const volatile&>();
    test_is_not_trivially_copyable<float Class::*const volatile&>();
    test_is_not_trivially_copyable<void * Class::*const volatile&>();
    test_is_not_trivially_copyable<int Class::*const volatile&&>();
    test_is_not_trivially_copyable<float Class::*const volatile&&>();
    test_is_not_trivially_copyable<void * Class::*const volatile&&>();
    test_is_trivially_copyable<NonCopyable>();
    test_is_trivially_copyable<NonMoveable>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivially_copyable<NonConstructible>();
#else
    test_is_trivially_copyable<NonConstructible>();
#endif
    test_is_not_trivially_copyable<Tracked>();
    test_is_trivially_copyable<TrapConstructible>();
    test_is_trivially_copyable<TrapImplicitConversion>();
    test_is_trivially_copyable<TrapComma>();
    test_is_trivially_copyable<TrapCall>();
    test_is_not_trivially_copyable<TrapSelfAssign>();
    test_is_trivially_copyable<TrapDeref>();
    test_is_trivially_copyable<TrapArraySubscript>();

    test_is_not_trivially_copyable<void()>();
    test_is_not_trivially_copyable<void()&>();
    test_is_not_trivially_copyable<void() &&>();
    test_is_not_trivially_copyable<void() const>();
    test_is_not_trivially_copyable<void() const&>();
    test_is_not_trivially_copyable<void() const&&>();
    test_is_not_trivially_copyable<void() volatile>();
    test_is_not_trivially_copyable<void() volatile&>();
    test_is_not_trivially_copyable<void() volatile&&>();
    test_is_not_trivially_copyable<void() const volatile>();
    test_is_not_trivially_copyable<void() const volatile&>();
    test_is_not_trivially_copyable<void() const volatile&&>();
    test_is_not_trivially_copyable<void() noexcept>();
    test_is_not_trivially_copyable<void()& noexcept>();
    test_is_not_trivially_copyable<void()&& noexcept>();
    test_is_not_trivially_copyable<void() const noexcept>();
    test_is_not_trivially_copyable<void() const& noexcept>();
    test_is_not_trivially_copyable<void() const&& noexcept>();
    test_is_not_trivially_copyable<void() volatile noexcept>();
    test_is_not_trivially_copyable<void() volatile& noexcept>();
    test_is_not_trivially_copyable<void() volatile&& noexcept>();
    test_is_not_trivially_copyable<void() const volatile noexcept>();
    test_is_not_trivially_copyable<void() const volatile& noexcept>();
    test_is_not_trivially_copyable<void() const volatile&& noexcept>();

    test_is_not_trivially_copyable<void(int)>();
    test_is_not_trivially_copyable<void(int)&>();
    test_is_not_trivially_copyable<void(int) &&>();
    test_is_not_trivially_copyable<void(int) const>();
    test_is_not_trivially_copyable<void(int) const&>();
    test_is_not_trivially_copyable<void(int) const&&>();
    test_is_not_trivially_copyable<void(int) volatile>();
    test_is_not_trivially_copyable<void(int) volatile&>();
    test_is_not_trivially_copyable<void(int) volatile&&>();
    test_is_not_trivially_copyable<void(int) const volatile>();
    test_is_not_trivially_copyable<void(int) const volatile&>();
    test_is_not_trivially_copyable<void(int) const volatile&&>();
    test_is_not_trivially_copyable<void(int) noexcept>();
    test_is_not_trivially_copyable<void(int)& noexcept>();
    test_is_not_trivially_copyable<void(int)&& noexcept>();
    test_is_not_trivially_copyable<void(int) const noexcept>();
    test_is_not_trivially_copyable<void(int) const& noexcept>();
    test_is_not_trivially_copyable<void(int) const&& noexcept>();
    test_is_not_trivially_copyable<void(int) volatile noexcept>();
    test_is_not_trivially_copyable<void(int) volatile& noexcept>();
    test_is_not_trivially_copyable<void(int) volatile&& noexcept>();
    test_is_not_trivially_copyable<void(int) const volatile noexcept>();
    test_is_not_trivially_copyable<void(int) const volatile& noexcept>();
    test_is_not_trivially_copyable<void(int) const volatile&& noexcept>();

    test_is_not_trivially_copyable<void(...)>();
    test_is_not_trivially_copyable<void(...)&>();
    test_is_not_trivially_copyable<void(...) &&>();
    test_is_not_trivially_copyable<void(...) const>();
    test_is_not_trivially_copyable<void(...) const&>();
    test_is_not_trivially_copyable<void(...) const&&>();
    test_is_not_trivially_copyable<void(...) volatile>();
    test_is_not_trivially_copyable<void(...) volatile&>();
    test_is_not_trivially_copyable<void(...) volatile&&>();
    test_is_not_trivially_copyable<void(...) const volatile>();
    test_is_not_trivially_copyable<void(...) const volatile&>();
    test_is_not_trivially_copyable<void(...) const volatile&&>();
    test_is_not_trivially_copyable<void(...) noexcept>();
    test_is_not_trivially_copyable<void(...)& noexcept>();
    test_is_not_trivially_copyable<void(...)&& noexcept>();
    test_is_not_trivially_copyable<void(...) const noexcept>();
    test_is_not_trivially_copyable<void(...) const& noexcept>();
    test_is_not_trivially_copyable<void(...) const&& noexcept>();
    test_is_not_trivially_copyable<void(...) volatile noexcept>();
    test_is_not_trivially_copyable<void(...) volatile& noexcept>();
    test_is_not_trivially_copyable<void(...) volatile&& noexcept>();
    test_is_not_trivially_copyable<void(...) const volatile noexcept>();
    test_is_not_trivially_copyable<void(...) const volatile& noexcept>();
    test_is_not_trivially_copyable<void(...) const volatile&& noexcept>();

    test_is_not_trivially_copyable<void(int, ...)>();
    test_is_not_trivially_copyable<void(int, ...)&>();
    test_is_not_trivially_copyable<void(int, ...) &&>();
    test_is_not_trivially_copyable<void(int, ...) const>();
    test_is_not_trivially_copyable<void(int, ...) const&>();
    test_is_not_trivially_copyable<void(int, ...) const&&>();
    test_is_not_trivially_copyable<void(int, ...) volatile>();
    test_is_not_trivially_copyable<void(int, ...) volatile&>();
    test_is_not_trivially_copyable<void(int, ...) volatile&&>();
    test_is_not_trivially_copyable<void(int, ...) const volatile>();
    test_is_not_trivially_copyable<void(int, ...) const volatile&>();
    test_is_not_trivially_copyable<void(int, ...) const volatile&&>();
    test_is_not_trivially_copyable<void(int, ...) noexcept>();
    test_is_not_trivially_copyable<void(int, ...)& noexcept>();
    test_is_not_trivially_copyable<void(int, ...)&& noexcept>();
    test_is_not_trivially_copyable<void(int, ...) const noexcept>();
    test_is_not_trivially_copyable<void(int, ...) const& noexcept>();
    test_is_not_trivially_copyable<void(int, ...) const&& noexcept>();
    test_is_not_trivially_copyable<void(int, ...) volatile noexcept>();
    test_is_not_trivially_copyable<void(int, ...) volatile& noexcept>();
    test_is_not_trivially_copyable<void(int, ...) volatile&& noexcept>();
    test_is_not_trivially_copyable<void(int, ...) const volatile noexcept>();
    test_is_not_trivially_copyable<void(int, ...) const volatile& noexcept>();
    test_is_not_trivially_copyable<void(int, ...) const volatile&& noexcept>();

    test_is_not_trivially_copyable<int()>();
    test_is_not_trivially_copyable<int()&>();
    test_is_not_trivially_copyable<int() &&>();
    test_is_not_trivially_copyable<int() const>();
    test_is_not_trivially_copyable<int() const&>();
    test_is_not_trivially_copyable<int() const&&>();
    test_is_not_trivially_copyable<int() volatile>();
    test_is_not_trivially_copyable<int() volatile&>();
    test_is_not_trivially_copyable<int() volatile&&>();
    test_is_not_trivially_copyable<int() const volatile>();
    test_is_not_trivially_copyable<int() const volatile&>();
    test_is_not_trivially_copyable<int() const volatile&&>();
    test_is_not_trivially_copyable<int() noexcept>();
    test_is_not_trivially_copyable<int()& noexcept>();
    test_is_not_trivially_copyable<int()&& noexcept>();
    test_is_not_trivially_copyable<int() const noexcept>();
    test_is_not_trivially_copyable<int() const& noexcept>();
    test_is_not_trivially_copyable<int() const&& noexcept>();
    test_is_not_trivially_copyable<int() volatile noexcept>();
    test_is_not_trivially_copyable<int() volatile& noexcept>();
    test_is_not_trivially_copyable<int() volatile&& noexcept>();
    test_is_not_trivially_copyable<int() const volatile noexcept>();
    test_is_not_trivially_copyable<int() const volatile& noexcept>();
    test_is_not_trivially_copyable<int() const volatile&& noexcept>();

    test_is_not_trivially_copyable<int(int)>();
    test_is_not_trivially_copyable<int(int)&>();
    test_is_not_trivially_copyable<int(int) &&>();
    test_is_not_trivially_copyable<int(int) const>();
    test_is_not_trivially_copyable<int(int) const&>();
    test_is_not_trivially_copyable<int(int) const&&>();
    test_is_not_trivially_copyable<int(int) volatile>();
    test_is_not_trivially_copyable<int(int) volatile&>();
    test_is_not_trivially_copyable<int(int) volatile&&>();
    test_is_not_trivially_copyable<int(int) const volatile>();
    test_is_not_trivially_copyable<int(int) const volatile&>();
    test_is_not_trivially_copyable<int(int) const volatile&&>();
    test_is_not_trivially_copyable<int(int) noexcept>();
    test_is_not_trivially_copyable<int(int)& noexcept>();
    test_is_not_trivially_copyable<int(int)&& noexcept>();
    test_is_not_trivially_copyable<int(int) const noexcept>();
    test_is_not_trivially_copyable<int(int) const& noexcept>();
    test_is_not_trivially_copyable<int(int) const&& noexcept>();
    test_is_not_trivially_copyable<int(int) volatile noexcept>();
    test_is_not_trivially_copyable<int(int) volatile& noexcept>();
    test_is_not_trivially_copyable<int(int) volatile&& noexcept>();
    test_is_not_trivially_copyable<int(int) const volatile noexcept>();
    test_is_not_trivially_copyable<int(int) const volatile& noexcept>();
    test_is_not_trivially_copyable<int(int) const volatile&& noexcept>();

    test_is_not_trivially_copyable<int(...)>();
    test_is_not_trivially_copyable<int(...)&>();
    test_is_not_trivially_copyable<int(...) &&>();
    test_is_not_trivially_copyable<int(...) const>();
    test_is_not_trivially_copyable<int(...) const&>();
    test_is_not_trivially_copyable<int(...) const&&>();
    test_is_not_trivially_copyable<int(...) volatile>();
    test_is_not_trivially_copyable<int(...) volatile&>();
    test_is_not_trivially_copyable<int(...) volatile&&>();
    test_is_not_trivially_copyable<int(...) const volatile>();
    test_is_not_trivially_copyable<int(...) const volatile&>();
    test_is_not_trivially_copyable<int(...) const volatile&&>();
    test_is_not_trivially_copyable<int(...) noexcept>();
    test_is_not_trivially_copyable<int(...)& noexcept>();
    test_is_not_trivially_copyable<int(...)&& noexcept>();
    test_is_not_trivially_copyable<int(...) const noexcept>();
    test_is_not_trivially_copyable<int(...) const& noexcept>();
    test_is_not_trivially_copyable<int(...) const&& noexcept>();
    test_is_not_trivially_copyable<int(...) volatile noexcept>();
    test_is_not_trivially_copyable<int(...) volatile& noexcept>();
    test_is_not_trivially_copyable<int(...) volatile&& noexcept>();
    test_is_not_trivially_copyable<int(...) const volatile noexcept>();
    test_is_not_trivially_copyable<int(...) const volatile& noexcept>();
    test_is_not_trivially_copyable<int(...) const volatile&& noexcept>();

    test_is_not_trivially_copyable<int(int, ...)>();
    test_is_not_trivially_copyable<int(int, ...)&>();
    test_is_not_trivially_copyable<int(int, ...) &&>();
    test_is_not_trivially_copyable<int(int, ...) const>();
    test_is_not_trivially_copyable<int(int, ...) const&>();
    test_is_not_trivially_copyable<int(int, ...) const&&>();
    test_is_not_trivially_copyable<int(int, ...) volatile>();
    test_is_not_trivially_copyable<int(int, ...) volatile&>();
    test_is_not_trivially_copyable<int(int, ...) volatile&&>();
    test_is_not_trivially_copyable<int(int, ...) const volatile>();
    test_is_not_trivially_copyable<int(int, ...) const volatile&>();
    test_is_not_trivially_copyable<int(int, ...) const volatile&&>();
    test_is_not_trivially_copyable<int(int, ...) noexcept>();
    test_is_not_trivially_copyable<int(int, ...)& noexcept>();
    test_is_not_trivially_copyable<int(int, ...)&& noexcept>();
    test_is_not_trivially_copyable<int(int, ...) const noexcept>();
    test_is_not_trivially_copyable<int(int, ...) const& noexcept>();
    test_is_not_trivially_copyable<int(int, ...) const&& noexcept>();
    test_is_not_trivially_copyable<int(int, ...) volatile noexcept>();
    test_is_not_trivially_copyable<int(int, ...) volatile& noexcept>();
    test_is_not_trivially_copyable<int(int, ...) volatile&& noexcept>();
    test_is_not_trivially_copyable<int(int, ...) const volatile noexcept>();
    test_is_not_trivially_copyable<int(int, ...) const volatile& noexcept>();
    test_is_not_trivially_copyable<int(int, ...) const volatile&& noexcept>();

    test_is_trivially_copyable_gcc_compat<void (*)()>();
    test_is_trivially_copyable_gcc_compat<void (*)() noexcept>();

    test_is_trivially_copyable_gcc_compat<void (*)(int)>();
    test_is_trivially_copyable_gcc_compat<void (*)(int) noexcept>();

    test_is_trivially_copyable_gcc_compat<void (*)(...)>();
    test_is_trivially_copyable_gcc_compat<void (*)(...) noexcept>();

    test_is_trivially_copyable_gcc_compat<void (*)(int, ...)>();
    test_is_trivially_copyable_gcc_compat<void (*)(int, ...) noexcept>();

    test_is_trivially_copyable_gcc_compat<int (*)()>();
    test_is_trivially_copyable_gcc_compat<int (*)() noexcept>();

    test_is_trivially_copyable_gcc_compat<int (*)(int)>();
    test_is_trivially_copyable_gcc_compat<int (*)(int) noexcept>();

    test_is_trivially_copyable_gcc_compat<int (*)(...)>();
    test_is_trivially_copyable_gcc_compat<int (*)(...) noexcept>();

    test_is_trivially_copyable_gcc_compat<int (*)(int, ...)>();
    test_is_trivially_copyable_gcc_compat<int (*)(int, ...) noexcept>();

    test_is_not_trivially_copyable<void (&)()>();
    test_is_not_trivially_copyable<void (&)() noexcept>();

    test_is_not_trivially_copyable<void (&)(int)>();
    test_is_not_trivially_copyable<void (&)(int) noexcept>();

    test_is_not_trivially_copyable<void (&)(...)>();
    test_is_not_trivially_copyable<void (&)(...) noexcept>();

    test_is_not_trivially_copyable<void (&)(int, ...)>();
    test_is_not_trivially_copyable<void (&)(int, ...) noexcept>();

    test_is_not_trivially_copyable<int (&)()>();
    test_is_not_trivially_copyable<int (&)() noexcept>();

    test_is_not_trivially_copyable<int (&)(int)>();
    test_is_not_trivially_copyable<int (&)(int) noexcept>();

    test_is_not_trivially_copyable<int (&)(...)>();
    test_is_not_trivially_copyable<int (&)(...) noexcept>();

    test_is_not_trivially_copyable<int (&)(int, ...)>();
    test_is_not_trivially_copyable<int (&)(int, ...) noexcept>();

    test_is_not_trivially_copyable<void(&&)()>();
    test_is_not_trivially_copyable<void(&&)() noexcept>();

    test_is_not_trivially_copyable<void(&&)(int)>();
    test_is_not_trivially_copyable<void(&&)(int) noexcept>();

    test_is_not_trivially_copyable<void(&&)(...)>();
    test_is_not_trivially_copyable<void(&&)(...) noexcept>();

    test_is_not_trivially_copyable<void(&&)(int, ...)>();
    test_is_not_trivially_copyable<void(&&)(int, ...) noexcept>();

    test_is_not_trivially_copyable<int(&&)()>();
    test_is_not_trivially_copyable<int(&&)() noexcept>();

    test_is_not_trivially_copyable<int(&&)(int)>();
    test_is_not_trivially_copyable<int(&&)(int) noexcept>();

    test_is_not_trivially_copyable<int(&&)(...)>();
    test_is_not_trivially_copyable<int(&&)(...) noexcept>();

    test_is_not_trivially_copyable<int(&&)(int, ...)>();
    test_is_not_trivially_copyable<int(&&)(int, ...) noexcept>();

    test_is_trivially_copyable_gcc_compat<void (Class::*)()>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)()&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)() &&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)() const>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)() const&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)() const&&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)() noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)()& noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)()&& noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)() const noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)() const& noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)() const&& noexcept>();

    test_is_trivially_copyable_gcc_compat<void (Class::*)(int)>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int)&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int) &&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int) const>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int) const&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int) const&&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int) noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int)& noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int)&& noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int) const noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int) const& noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int) const&& noexcept>();

    test_is_trivially_copyable_gcc_compat<void (Class::*)(...)>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(...)&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(...) &&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(...) const>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(...) const&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(...) const&&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(...) noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(...)& noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(...)&& noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(...) const noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(...) const& noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(...) const&& noexcept>();

    test_is_trivially_copyable_gcc_compat<void (Class::*)(int, ...)>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int, ...)&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int, ...) &&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int, ...) const>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int, ...) const&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int, ...) const&&>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int, ...) noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int, ...)& noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int, ...)&& noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int, ...) const noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int, ...) const& noexcept>();
    test_is_trivially_copyable_gcc_compat<void (Class::*)(int, ...) const&& noexcept>();

    test_is_trivially_copyable_gcc_compat<int (Class::*)()>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)()&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)() &&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)() const>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)() const&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)() const&&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)() noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)()& noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)()&& noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)() const noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)() const& noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)() const&& noexcept>();

    test_is_trivially_copyable_gcc_compat<int (Class::*)(int)>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int)&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int) &&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int) const>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int) const&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int) const&&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int) noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int)& noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int)&& noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int) const noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int) const& noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int) const&& noexcept>();

    test_is_trivially_copyable_gcc_compat<int (Class::*)(...)>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(...)&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(...) &&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(...) const>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(...) const&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(...) const&&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(...) noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(...)& noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(...)&& noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(...) const noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(...) const& noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(...) const&& noexcept>();

    test_is_trivially_copyable_gcc_compat<int (Class::*)(int, ...)>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int, ...)&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int, ...) &&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int, ...) const>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int, ...) const&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int, ...) const&&>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int, ...) noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int, ...)& noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int, ...)&& noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int, ...) const noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int, ...) const& noexcept>();
    test_is_trivially_copyable_gcc_compat<int (Class::*)(int, ...) const&& noexcept>();
}
