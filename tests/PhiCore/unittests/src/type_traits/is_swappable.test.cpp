#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/nullptr_t.hpp>
#include <type_traits>
#include <vector>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

#include <phi/algorithm/swap.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_swappable.hpp>

template <typename T>
void test_is_swappable_impl()
{
    STATIC_REQUIRE(phi::is_swappable<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_swappable<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_swappable_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_swappable_v<T>);
#endif

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_swappable<T>::value);
#endif
}

template <typename T>
void test_is_not_swappable_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_swappable<T>::value);
    STATIC_REQUIRE(phi::is_not_swappable<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_swappable_v<T>);
    STATIC_REQUIRE(phi::is_not_swappable_v<T>);
#endif

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_swappable<T>::value);
#endif
}

template <typename T>
void test_is_swappable()
{
    test_is_swappable_impl<T>();
    test_is_not_swappable_impl<const T>();
    test_is_not_swappable_impl<volatile T>();
    test_is_not_swappable_impl<const volatile T>();
}

template <typename T>
void test_is_swappable_v()
{
    test_is_swappable_impl<T>();
    test_is_not_swappable_impl<const T>();
    test_is_swappable_impl<volatile T>();
    test_is_not_swappable_impl<const volatile T>();
}

template <typename T>
void test_is_swappable_cv()
{
    test_is_swappable_impl<T>();
    test_is_swappable_impl<const T>();
    test_is_swappable_impl<volatile T>();
    test_is_swappable_impl<const volatile T>();
}

template <typename T>
void test_is_not_swappable()
{
    test_is_not_swappable_impl<T>();
    test_is_not_swappable_impl<const T>();
    test_is_not_swappable_impl<volatile T>();
    test_is_not_swappable_impl<const volatile T>();
}

namespace is_swappable_ns
{
    // Make the test types non-copyable so that generic phi::swap is not valid.
    struct A
    {
        A(A const&) = delete;
        A& operator=(A const&) = delete;
    };

    struct B
    {
        B(B const&) = delete;
        B& operator=(B const&) = delete;
    };

    struct C
    {};

    struct D
    {};

    void swap(A&, A&)
    {}

    void swap(A&, B&)
    {}

    void swap(B&, A&)
    {}

    void swap(A&, C&)
    {} // missing swap(C, A)

    void swap(D&, C&)
    {}

    struct M
    {
        M(M const&) = delete;
        M& operator=(M const&) = delete;
    };

    void swap(M&&, M&&)
    {}

    struct DeletedSwap
    {
#if PHI_COMPILER_IS_BELOW(GCC, 5, 0, 0)
        // For some reason gcc before version 5.0 don't compile with the friend declaration...
        void swap(DeletedSwap&, DeletedSwap&) = delete;
#else
        friend void swap(DeletedSwap&, DeletedSwap&) = delete;
#endif
    };

    struct F
    {};

    void swap(F&, F&) = delete;
    void swap(F (&)[5], F (&)[5]);

    struct F2
    {
        friend void swap(F2&, F2&) = delete;
    };

    struct F3
    {
        friend void swap(F3&, F3)
        {}
    };
} // namespace is_swappable_ns

namespace is_swappable_ns_2
{
    struct AmbiguousSwap
    {};

    template <typename T>
    void swap(T&, T&)
    {}

} // namespace is_swappable_ns_2

TEST_CASE("is_swappable")
{
    using namespace is_swappable_ns;

    // Test that is_swappable applies an lvalue reference to the type.
    test_is_swappable<A>();
    test_is_swappable_cv<A&>();
    test_is_swappable_cv<A&&>();
    test_is_not_swappable<M>();
    test_is_not_swappable<M&>();
    test_is_not_swappable<M&&>();

    test_is_not_swappable<B>();
    test_is_swappable<C>();

    // test non-referencable types
    test_is_not_swappable<void>();
    test_is_not_swappable<int() const>();
    test_is_not_swappable<int()&>();

#if !PHI_COMPILER_IS_BELOW(GCC, 5, 0, 0)
    // test that a deleted swap is correctly handled.
    test_is_not_swappable<DeletedSwap>();
#endif

    // test that a swap with ambiguous overloads is handled correctly.
    test_is_not_swappable_impl<is_swappable_ns_2::AmbiguousSwap>();
    test_is_swappable_impl<const is_swappable_ns_2::AmbiguousSwap>();

    // TODO: The commented out tests currently crash
    test_is_swappable<F3>();
    test_is_swappable<F3[1]>();
    //test_is_not_swappable<F3[1][2]>();
    //test_is_swappable<F3[1][2][3]>();

    test_is_not_swappable<F>();
    //test_is_not_swappable<F[1]>();
    test_is_not_swappable<F[1][2]>();
    test_is_not_swappable<F[1][2][3]>();
    //test_is_not_swappable<F[4]>();
    test_is_not_swappable<F2>();
    //test_is_not_swappable<F2[1]>();
    test_is_not_swappable<F2[1][2]>();
    test_is_not_swappable<F2[1][2][3]>();
    //test_is_not_swappable<F2[4]>();
    //test_is_not_swappable<F2[5]>();

    test_is_not_swappable<void>();
    test_is_swappable_v<phi::nullptr_t>();
    test_is_swappable_v<bool>();
    test_is_swappable_v<char>();
    test_is_swappable_v<signed char>();
    test_is_swappable_v<unsigned char>();
    test_is_swappable_v<short>();
    test_is_swappable_v<unsigned short>();
    test_is_swappable_v<int>();
    test_is_swappable_v<unsigned int>();
    test_is_swappable_v<long>();
    test_is_swappable_v<unsigned long>();
    test_is_swappable_v<long long>();
    test_is_swappable_v<unsigned long long>();
    test_is_swappable_v<float>();
    test_is_swappable_v<double>();
    test_is_swappable_v<long double>();
    test_is_swappable_v<char8_t>();
    test_is_swappable_v<char16_t>();
    test_is_swappable_v<char32_t>();
    test_is_swappable_v<wchar_t>();

    test_is_swappable<phi::boolean>();
    test_is_swappable<phi::integer<signed char>>();
    test_is_swappable<phi::integer<unsigned char>>();
    test_is_swappable<phi::integer<short>>();
    test_is_swappable<phi::integer<unsigned short>>();
    test_is_swappable<phi::integer<int>>();
    test_is_swappable<phi::integer<unsigned int>>();
    test_is_swappable<phi::integer<long>>();
    test_is_swappable<phi::integer<unsigned long>>();
    test_is_swappable<phi::integer<long long>>();
    test_is_swappable<phi::integer<unsigned long long>>();
    test_is_swappable<phi::floating_point<float>>();
    test_is_swappable<phi::floating_point<double>>();
    test_is_swappable<phi::floating_point<long double>>();

#if PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_swappable<std::vector<int>>();
#endif
    test_is_swappable<phi::scope_ptr<int>>();

    test_is_swappable_cv<int&>();
    test_is_not_swappable<const int&>();
    test_is_swappable_cv<volatile int&>();
    test_is_not_swappable<const volatile int&>();
    test_is_swappable_cv<int&&>();
    test_is_not_swappable<const int&&>();
    test_is_swappable_cv<volatile int&&>();
    test_is_not_swappable<const volatile int&&>();
    test_is_swappable_v<int*>();
    test_is_swappable_v<const int*>();
    test_is_swappable_v<volatile int*>();
    test_is_swappable_v<const volatile int*>();
    test_is_swappable_v<int**>();
    test_is_swappable_v<const int**>();
    test_is_swappable_v<volatile int**>();
    test_is_swappable_v<const volatile int**>();
    test_is_swappable_cv<int*&>();
    test_is_swappable_cv<const int*&>();
    test_is_swappable_cv<volatile int*&>();
    test_is_swappable_cv<const volatile int*&>();
    test_is_swappable_cv<int*&&>();
    test_is_swappable_cv<const int*&&>();
    test_is_swappable_cv<volatile int*&&>();
    test_is_swappable_cv<const volatile int*&&>();
    test_is_swappable_v<void*>();
    test_is_swappable_v<char[3]>();
    test_is_swappable_v<char* [3]>();
    test_is_swappable_v<int(*)[3]>();
    test_is_swappable_cv<int(&)[3]>();
    test_is_swappable_cv<int(&&)[3]>();
    //test_is_swappable<char[3][2]>();
    //test_is_swappable<char* [3][2]>();
    test_is_swappable_v<int(*)[3][2]>();
    //test_is_swappable<int(&)[3][2]>();
    //test_is_swappable<int(&&)[3][2]>();
    test_is_swappable<Class>();
    test_is_swappable<Class[2]>();
    test_is_swappable<Template<void>>();
    test_is_swappable<Template<int>>();
    test_is_swappable<Template<Class>>();
    test_is_swappable<VariadicTemplate<>>();
    test_is_swappable<VariadicTemplate<void>>();
    test_is_swappable<VariadicTemplate<int>>();
    test_is_swappable<VariadicTemplate<Class>>();
    test_is_swappable<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_swappable<PublicDerivedFromTemplate<Base>>();
    test_is_swappable<PublicDerivedFromTemplate<Derived>>();
    test_is_swappable<PublicDerivedFromTemplate<Class>>();
    test_is_swappable<PrivateDerivedFromTemplate<Base>>();
    test_is_swappable<PrivateDerivedFromTemplate<Derived>>();
    test_is_swappable<PrivateDerivedFromTemplate<Class>>();
    test_is_swappable<ProtectedDerivedFromTemplate<Base>>();
    test_is_swappable<ProtectedDerivedFromTemplate<Derived>>();
    test_is_swappable<ProtectedDerivedFromTemplate<Class>>();
    test_is_swappable<Union>();
    test_is_swappable<NonEmptyUnion>();
    test_is_swappable<Empty>();
    test_is_swappable<NotEmpty>();
    test_is_swappable<BitZero>();
    test_is_swappable<BitOne>();
    test_is_swappable<Base>();
    test_is_swappable<Derived>();
    test_is_not_swappable<Abstract>();
    test_is_not_swappable<PublicAbstract>();
    test_is_not_swappable<PrivateAbstract>();
    test_is_not_swappable<ProtectedAbstract>();
    test_is_not_swappable<AbstractTemplate<int>>();
    test_is_swappable<AbstractTemplate<double>>();
    test_is_not_swappable<AbstractTemplate<Class>>();
    test_is_swappable<Final>();
    test_is_swappable<PublicDestructor>();
    test_is_not_swappable<ProtectedDestructor>();
    test_is_not_swappable<PrivateDestructor>();
    test_is_swappable<VirtualPublicDestructor>();
    test_is_not_swappable<VirtualProtectedDestructor>();
    test_is_not_swappable<VirtualPrivateDestructor>();
    test_is_not_swappable<PurePublicDestructor>();
    test_is_not_swappable<PureProtectedDestructor>();
    test_is_not_swappable<PurePrivateDestructor>();
    test_is_not_swappable<DeletedPublicDestructor>();
    test_is_not_swappable<DeletedProtectedDestructor>();
    test_is_not_swappable<DeletedPrivateDestructor>();
    test_is_not_swappable<DeletedVirtualPublicDestructor>();
    test_is_not_swappable<DeletedVirtualProtectedDestructor>();
    test_is_not_swappable<DeletedVirtualPrivateDestructor>();
    test_is_swappable_v<Enum>();
    test_is_swappable_v<EnumSigned>();
    test_is_swappable_v<EnumUnsigned>();
    test_is_swappable_v<EnumClass>();
    test_is_swappable_v<EnumStruct>();
    test_is_not_swappable<Function>();
    test_is_swappable_v<FunctionPtr>();
    test_is_swappable_v<MemberObjectPtr>();
    test_is_swappable_v<MemberFunctionPtr>();
    test_is_swappable_v<int Class::*>();
    test_is_swappable_v<float Class::*>();
    test_is_swappable_v<void * Class::*>();
    test_is_swappable_v<int * Class::*>();
    test_is_swappable_cv<int Class::*&>();
    test_is_swappable_cv<float Class::*&>();
    test_is_swappable_cv<void * Class::*&>();
    test_is_swappable_cv<int * Class::*&>();
    test_is_swappable_cv<int Class::*&&>();
    test_is_swappable_cv<float Class::*&&>();
    test_is_swappable_cv<void * Class::*&&>();
    test_is_swappable_cv<int * Class::*&&>();
    test_is_not_swappable<int Class::*const>();
    test_is_not_swappable<float Class::*const>();
    test_is_not_swappable<void * Class::*const>();
    test_is_not_swappable<int Class::*const&>();
    test_is_not_swappable<float Class::*const&>();
    test_is_not_swappable<void * Class::*const&>();
    test_is_not_swappable<int Class::*const&&>();
    test_is_not_swappable<float Class::*const&&>();
    test_is_not_swappable<void * Class::*const&&>();
    test_is_swappable_v<int Class::*volatile>();
    test_is_swappable_v<float Class::*volatile>();
    test_is_swappable_v<void * Class::*volatile>();
    test_is_swappable_cv<int Class::*volatile&>();
    test_is_swappable_cv<float Class::*volatile&>();
    test_is_swappable_cv<void * Class::*volatile&>();
    test_is_swappable_cv<int Class::*volatile&&>();
    test_is_swappable_cv<float Class::*volatile&&>();
    test_is_swappable_cv<void * Class::*volatile&&>();
    test_is_not_swappable<int Class::*const volatile>();
    test_is_not_swappable<float Class::*const volatile>();
    test_is_not_swappable<void * Class::*const volatile>();
    test_is_not_swappable<int Class::*const volatile&>();
    test_is_not_swappable<float Class::*const volatile&>();
    test_is_not_swappable<void * Class::*const volatile&>();
    test_is_not_swappable<int Class::*const volatile&&>();
    test_is_not_swappable<float Class::*const volatile&&>();
    test_is_not_swappable<void * Class::*const volatile&&>();
    test_is_swappable<NonCopyable>();
    test_is_not_swappable<NonMoveable>();
    test_is_not_swappable<NonConstructible>();
    test_is_swappable<Tracked>();
    test_is_swappable<TrapConstructible>();
    test_is_swappable<TrapImplicitConversion>();
    test_is_swappable<TrapComma>();
    test_is_swappable<TrapCall>();
    test_is_swappable<TrapSelfAssign>();
    test_is_swappable<TrapDeref>();
    test_is_swappable<TrapArraySubscript>();

    test_is_not_swappable<void()>();
    test_is_not_swappable<void()&>();
    test_is_not_swappable<void() &&>();
    test_is_not_swappable<void() const>();
    test_is_not_swappable<void() const&>();
    test_is_not_swappable<void() const&&>();
    test_is_not_swappable<void() volatile>();
    test_is_not_swappable<void() volatile&>();
    test_is_not_swappable<void() volatile&&>();
    test_is_not_swappable<void() const volatile>();
    test_is_not_swappable<void() const volatile&>();
    test_is_not_swappable<void() const volatile&&>();
    test_is_not_swappable<void() noexcept>();
    test_is_not_swappable<void()& noexcept>();
    test_is_not_swappable<void()&& noexcept>();
    test_is_not_swappable<void() const noexcept>();
    test_is_not_swappable<void() const& noexcept>();
    test_is_not_swappable<void() const&& noexcept>();
    test_is_not_swappable<void() volatile noexcept>();
    test_is_not_swappable<void() volatile& noexcept>();
    test_is_not_swappable<void() volatile&& noexcept>();
    test_is_not_swappable<void() const volatile noexcept>();
    test_is_not_swappable<void() const volatile& noexcept>();
    test_is_not_swappable<void() const volatile&& noexcept>();

    test_is_not_swappable<void(int)>();
    test_is_not_swappable<void(int)&>();
    test_is_not_swappable<void(int) &&>();
    test_is_not_swappable<void(int) const>();
    test_is_not_swappable<void(int) const&>();
    test_is_not_swappable<void(int) const&&>();
    test_is_not_swappable<void(int) volatile>();
    test_is_not_swappable<void(int) volatile&>();
    test_is_not_swappable<void(int) volatile&&>();
    test_is_not_swappable<void(int) const volatile>();
    test_is_not_swappable<void(int) const volatile&>();
    test_is_not_swappable<void(int) const volatile&&>();
    test_is_not_swappable<void(int) noexcept>();
    test_is_not_swappable<void(int)& noexcept>();
    test_is_not_swappable<void(int)&& noexcept>();
    test_is_not_swappable<void(int) const noexcept>();
    test_is_not_swappable<void(int) const& noexcept>();
    test_is_not_swappable<void(int) const&& noexcept>();
    test_is_not_swappable<void(int) volatile noexcept>();
    test_is_not_swappable<void(int) volatile& noexcept>();
    test_is_not_swappable<void(int) volatile&& noexcept>();
    test_is_not_swappable<void(int) const volatile noexcept>();
    test_is_not_swappable<void(int) const volatile& noexcept>();
    test_is_not_swappable<void(int) const volatile&& noexcept>();

    test_is_not_swappable<void(...)>();
    test_is_not_swappable<void(...)&>();
    test_is_not_swappable<void(...) &&>();
    test_is_not_swappable<void(...) const>();
    test_is_not_swappable<void(...) const&>();
    test_is_not_swappable<void(...) const&&>();
    test_is_not_swappable<void(...) volatile>();
    test_is_not_swappable<void(...) volatile&>();
    test_is_not_swappable<void(...) volatile&&>();
    test_is_not_swappable<void(...) const volatile>();
    test_is_not_swappable<void(...) const volatile&>();
    test_is_not_swappable<void(...) const volatile&&>();
    test_is_not_swappable<void(...) noexcept>();
    test_is_not_swappable<void(...)& noexcept>();
    test_is_not_swappable<void(...)&& noexcept>();
    test_is_not_swappable<void(...) const noexcept>();
    test_is_not_swappable<void(...) const& noexcept>();
    test_is_not_swappable<void(...) const&& noexcept>();
    test_is_not_swappable<void(...) volatile noexcept>();
    test_is_not_swappable<void(...) volatile& noexcept>();
    test_is_not_swappable<void(...) volatile&& noexcept>();
    test_is_not_swappable<void(...) const volatile noexcept>();
    test_is_not_swappable<void(...) const volatile& noexcept>();
    test_is_not_swappable<void(...) const volatile&& noexcept>();

    test_is_not_swappable<void(int, ...)>();
    test_is_not_swappable<void(int, ...)&>();
    test_is_not_swappable<void(int, ...) &&>();
    test_is_not_swappable<void(int, ...) const>();
    test_is_not_swappable<void(int, ...) const&>();
    test_is_not_swappable<void(int, ...) const&&>();
    test_is_not_swappable<void(int, ...) volatile>();
    test_is_not_swappable<void(int, ...) volatile&>();
    test_is_not_swappable<void(int, ...) volatile&&>();
    test_is_not_swappable<void(int, ...) const volatile>();
    test_is_not_swappable<void(int, ...) const volatile&>();
    test_is_not_swappable<void(int, ...) const volatile&&>();
    test_is_not_swappable<void(int, ...) noexcept>();
    test_is_not_swappable<void(int, ...)& noexcept>();
    test_is_not_swappable<void(int, ...)&& noexcept>();
    test_is_not_swappable<void(int, ...) const noexcept>();
    test_is_not_swappable<void(int, ...) const& noexcept>();
    test_is_not_swappable<void(int, ...) const&& noexcept>();
    test_is_not_swappable<void(int, ...) volatile noexcept>();
    test_is_not_swappable<void(int, ...) volatile& noexcept>();
    test_is_not_swappable<void(int, ...) volatile&& noexcept>();
    test_is_not_swappable<void(int, ...) const volatile noexcept>();
    test_is_not_swappable<void(int, ...) const volatile& noexcept>();
    test_is_not_swappable<void(int, ...) const volatile&& noexcept>();

    test_is_not_swappable<int()>();
    test_is_not_swappable<int()&>();
    test_is_not_swappable<int() &&>();
    test_is_not_swappable<int() const>();
    test_is_not_swappable<int() const&>();
    test_is_not_swappable<int() const&&>();
    test_is_not_swappable<int() volatile>();
    test_is_not_swappable<int() volatile&>();
    test_is_not_swappable<int() volatile&&>();
    test_is_not_swappable<int() const volatile>();
    test_is_not_swappable<int() const volatile&>();
    test_is_not_swappable<int() const volatile&&>();
    test_is_not_swappable<int() noexcept>();
    test_is_not_swappable<int()& noexcept>();
    test_is_not_swappable<int()&& noexcept>();
    test_is_not_swappable<int() const noexcept>();
    test_is_not_swappable<int() const& noexcept>();
    test_is_not_swappable<int() const&& noexcept>();
    test_is_not_swappable<int() volatile noexcept>();
    test_is_not_swappable<int() volatile& noexcept>();
    test_is_not_swappable<int() volatile&& noexcept>();
    test_is_not_swappable<int() const volatile noexcept>();
    test_is_not_swappable<int() const volatile& noexcept>();
    test_is_not_swappable<int() const volatile&& noexcept>();

    test_is_not_swappable<int(int)>();
    test_is_not_swappable<int(int)&>();
    test_is_not_swappable<int(int) &&>();
    test_is_not_swappable<int(int) const>();
    test_is_not_swappable<int(int) const&>();
    test_is_not_swappable<int(int) const&&>();
    test_is_not_swappable<int(int) volatile>();
    test_is_not_swappable<int(int) volatile&>();
    test_is_not_swappable<int(int) volatile&&>();
    test_is_not_swappable<int(int) const volatile>();
    test_is_not_swappable<int(int) const volatile&>();
    test_is_not_swappable<int(int) const volatile&&>();
    test_is_not_swappable<int(int) noexcept>();
    test_is_not_swappable<int(int)& noexcept>();
    test_is_not_swappable<int(int)&& noexcept>();
    test_is_not_swappable<int(int) const noexcept>();
    test_is_not_swappable<int(int) const& noexcept>();
    test_is_not_swappable<int(int) const&& noexcept>();
    test_is_not_swappable<int(int) volatile noexcept>();
    test_is_not_swappable<int(int) volatile& noexcept>();
    test_is_not_swappable<int(int) volatile&& noexcept>();
    test_is_not_swappable<int(int) const volatile noexcept>();
    test_is_not_swappable<int(int) const volatile& noexcept>();
    test_is_not_swappable<int(int) const volatile&& noexcept>();

    test_is_not_swappable<int(...)>();
    test_is_not_swappable<int(...)&>();
    test_is_not_swappable<int(...) &&>();
    test_is_not_swappable<int(...) const>();
    test_is_not_swappable<int(...) const&>();
    test_is_not_swappable<int(...) const&&>();
    test_is_not_swappable<int(...) volatile>();
    test_is_not_swappable<int(...) volatile&>();
    test_is_not_swappable<int(...) volatile&&>();
    test_is_not_swappable<int(...) const volatile>();
    test_is_not_swappable<int(...) const volatile&>();
    test_is_not_swappable<int(...) const volatile&&>();
    test_is_not_swappable<int(...) noexcept>();
    test_is_not_swappable<int(...)& noexcept>();
    test_is_not_swappable<int(...)&& noexcept>();
    test_is_not_swappable<int(...) const noexcept>();
    test_is_not_swappable<int(...) const& noexcept>();
    test_is_not_swappable<int(...) const&& noexcept>();
    test_is_not_swappable<int(...) volatile noexcept>();
    test_is_not_swappable<int(...) volatile& noexcept>();
    test_is_not_swappable<int(...) volatile&& noexcept>();
    test_is_not_swappable<int(...) const volatile noexcept>();
    test_is_not_swappable<int(...) const volatile& noexcept>();
    test_is_not_swappable<int(...) const volatile&& noexcept>();

    test_is_not_swappable<int(int, ...)>();
    test_is_not_swappable<int(int, ...)&>();
    test_is_not_swappable<int(int, ...) &&>();
    test_is_not_swappable<int(int, ...) const>();
    test_is_not_swappable<int(int, ...) const&>();
    test_is_not_swappable<int(int, ...) const&&>();
    test_is_not_swappable<int(int, ...) volatile>();
    test_is_not_swappable<int(int, ...) volatile&>();
    test_is_not_swappable<int(int, ...) volatile&&>();
    test_is_not_swappable<int(int, ...) const volatile>();
    test_is_not_swappable<int(int, ...) const volatile&>();
    test_is_not_swappable<int(int, ...) const volatile&&>();
    test_is_not_swappable<int(int, ...) noexcept>();
    test_is_not_swappable<int(int, ...)& noexcept>();
    test_is_not_swappable<int(int, ...)&& noexcept>();
    test_is_not_swappable<int(int, ...) const noexcept>();
    test_is_not_swappable<int(int, ...) const& noexcept>();
    test_is_not_swappable<int(int, ...) const&& noexcept>();
    test_is_not_swappable<int(int, ...) volatile noexcept>();
    test_is_not_swappable<int(int, ...) volatile& noexcept>();
    test_is_not_swappable<int(int, ...) volatile&& noexcept>();
    test_is_not_swappable<int(int, ...) const volatile noexcept>();
    test_is_not_swappable<int(int, ...) const volatile& noexcept>();
    test_is_not_swappable<int(int, ...) const volatile&& noexcept>();

    test_is_swappable_v<void (*)()>();
    test_is_swappable_v<void (*)() noexcept>();

    test_is_swappable_v<void (*)(int)>();
    test_is_swappable_v<void (*)(int) noexcept>();

    test_is_swappable_v<void (*)(...)>();
    test_is_swappable_v<void (*)(...) noexcept>();

    test_is_swappable_v<void (*)(int, ...)>();
    test_is_swappable_v<void (*)(int, ...) noexcept>();

    test_is_swappable_v<int (*)()>();
    test_is_swappable_v<int (*)() noexcept>();

    test_is_swappable_v<int (*)(int)>();
    test_is_swappable_v<int (*)(int) noexcept>();

    test_is_swappable_v<int (*)(...)>();
    test_is_swappable_v<int (*)(...) noexcept>();

    test_is_swappable_v<int (*)(int, ...)>();
    test_is_swappable_v<int (*)(int, ...) noexcept>();

    test_is_not_swappable<void (&)()>();
    test_is_not_swappable<void (&)() noexcept>();

    test_is_not_swappable<void (&)(int)>();
    test_is_not_swappable<void (&)(int) noexcept>();

    test_is_not_swappable<void (&)(...)>();
    test_is_not_swappable<void (&)(...) noexcept>();

    test_is_not_swappable<void (&)(int, ...)>();
    test_is_not_swappable<void (&)(int, ...) noexcept>();

    test_is_not_swappable<int (&)()>();
    test_is_not_swappable<int (&)() noexcept>();

    test_is_not_swappable<int (&)(int)>();
    test_is_not_swappable<int (&)(int) noexcept>();

    test_is_not_swappable<int (&)(...)>();
    test_is_not_swappable<int (&)(...) noexcept>();

    test_is_not_swappable<int (&)(int, ...)>();
    test_is_not_swappable<int (&)(int, ...) noexcept>();

    test_is_not_swappable<void(&&)()>();
    test_is_not_swappable<void(&&)() noexcept>();

    test_is_not_swappable<void(&&)(int)>();
    test_is_not_swappable<void(&&)(int) noexcept>();

    test_is_not_swappable<void(&&)(...)>();
    test_is_not_swappable<void(&&)(...) noexcept>();

    test_is_not_swappable<void(&&)(int, ...)>();
    test_is_not_swappable<void(&&)(int, ...) noexcept>();

    test_is_not_swappable<int(&&)()>();
    test_is_not_swappable<int(&&)() noexcept>();

    test_is_not_swappable<int(&&)(int)>();
    test_is_not_swappable<int(&&)(int) noexcept>();

    test_is_not_swappable<int(&&)(...)>();
    test_is_not_swappable<int(&&)(...) noexcept>();

    test_is_not_swappable<int(&&)(int, ...)>();
    test_is_not_swappable<int(&&)(int, ...) noexcept>();

    test_is_swappable_v<void (Class::*)()>();
    test_is_swappable_v<void (Class::*)()&>();
    test_is_swappable_v<void (Class::*)() &&>();
    test_is_swappable_v<void (Class::*)() const>();
    test_is_swappable_v<void (Class::*)() const&>();
    test_is_swappable_v<void (Class::*)() const&&>();
    test_is_swappable_v<void (Class::*)() noexcept>();
    test_is_swappable_v<void (Class::*)()& noexcept>();
    test_is_swappable_v<void (Class::*)()&& noexcept>();
    test_is_swappable_v<void (Class::*)() const noexcept>();
    test_is_swappable_v<void (Class::*)() const& noexcept>();
    test_is_swappable_v<void (Class::*)() const&& noexcept>();

    test_is_swappable_v<void (Class::*)(int)>();
    test_is_swappable_v<void (Class::*)(int)&>();
    test_is_swappable_v<void (Class::*)(int) &&>();
    test_is_swappable_v<void (Class::*)(int) const>();
    test_is_swappable_v<void (Class::*)(int) const&>();
    test_is_swappable_v<void (Class::*)(int) const&&>();
    test_is_swappable_v<void (Class::*)(int) noexcept>();
    test_is_swappable_v<void (Class::*)(int)& noexcept>();
    test_is_swappable_v<void (Class::*)(int)&& noexcept>();
    test_is_swappable_v<void (Class::*)(int) const noexcept>();
    test_is_swappable_v<void (Class::*)(int) const& noexcept>();
    test_is_swappable_v<void (Class::*)(int) const&& noexcept>();

    test_is_swappable_v<void (Class::*)(...)>();
    test_is_swappable_v<void (Class::*)(...)&>();
    test_is_swappable_v<void (Class::*)(...) &&>();
    test_is_swappable_v<void (Class::*)(...) const>();
    test_is_swappable_v<void (Class::*)(...) const&>();
    test_is_swappable_v<void (Class::*)(...) const&&>();
    test_is_swappable_v<void (Class::*)(...) noexcept>();
    test_is_swappable_v<void (Class::*)(...)& noexcept>();
    test_is_swappable_v<void (Class::*)(...)&& noexcept>();
    test_is_swappable_v<void (Class::*)(...) const noexcept>();
    test_is_swappable_v<void (Class::*)(...) const& noexcept>();
    test_is_swappable_v<void (Class::*)(...) const&& noexcept>();

    test_is_swappable_v<void (Class::*)(int, ...)>();
    test_is_swappable_v<void (Class::*)(int, ...)&>();
    test_is_swappable_v<void (Class::*)(int, ...) &&>();
    test_is_swappable_v<void (Class::*)(int, ...) const>();
    test_is_swappable_v<void (Class::*)(int, ...) const&>();
    test_is_swappable_v<void (Class::*)(int, ...) const&&>();
    test_is_swappable_v<void (Class::*)(int, ...) noexcept>();
    test_is_swappable_v<void (Class::*)(int, ...)& noexcept>();
    test_is_swappable_v<void (Class::*)(int, ...)&& noexcept>();
    test_is_swappable_v<void (Class::*)(int, ...) const noexcept>();
    test_is_swappable_v<void (Class::*)(int, ...) const& noexcept>();
    test_is_swappable_v<void (Class::*)(int, ...) const&& noexcept>();

    test_is_swappable_v<int (Class::*)()>();
    test_is_swappable_v<int (Class::*)()&>();
    test_is_swappable_v<int (Class::*)() &&>();
    test_is_swappable_v<int (Class::*)() const>();
    test_is_swappable_v<int (Class::*)() const&>();
    test_is_swappable_v<int (Class::*)() const&&>();
    test_is_swappable_v<int (Class::*)() noexcept>();
    test_is_swappable_v<int (Class::*)()& noexcept>();
    test_is_swappable_v<int (Class::*)()&& noexcept>();
    test_is_swappable_v<int (Class::*)() const noexcept>();
    test_is_swappable_v<int (Class::*)() const& noexcept>();
    test_is_swappable_v<int (Class::*)() const&& noexcept>();

    test_is_swappable_v<int (Class::*)(int)>();
    test_is_swappable_v<int (Class::*)(int)&>();
    test_is_swappable_v<int (Class::*)(int) &&>();
    test_is_swappable_v<int (Class::*)(int) const>();
    test_is_swappable_v<int (Class::*)(int) const&>();
    test_is_swappable_v<int (Class::*)(int) const&&>();
    test_is_swappable_v<int (Class::*)(int) noexcept>();
    test_is_swappable_v<int (Class::*)(int)& noexcept>();
    test_is_swappable_v<int (Class::*)(int)&& noexcept>();
    test_is_swappable_v<int (Class::*)(int) const noexcept>();
    test_is_swappable_v<int (Class::*)(int) const& noexcept>();
    test_is_swappable_v<int (Class::*)(int) const&& noexcept>();

    test_is_swappable_v<int (Class::*)(...)>();
    test_is_swappable_v<int (Class::*)(...)&>();
    test_is_swappable_v<int (Class::*)(...) &&>();
    test_is_swappable_v<int (Class::*)(...) const>();
    test_is_swappable_v<int (Class::*)(...) const&>();
    test_is_swappable_v<int (Class::*)(...) const&&>();
    test_is_swappable_v<int (Class::*)(...) noexcept>();
    test_is_swappable_v<int (Class::*)(...)& noexcept>();
    test_is_swappable_v<int (Class::*)(...)&& noexcept>();
    test_is_swappable_v<int (Class::*)(...) const noexcept>();
    test_is_swappable_v<int (Class::*)(...) const& noexcept>();
    test_is_swappable_v<int (Class::*)(...) const&& noexcept>();

    test_is_swappable_v<int (Class::*)(int, ...)>();
    test_is_swappable_v<int (Class::*)(int, ...)&>();
    test_is_swappable_v<int (Class::*)(int, ...) &&>();
    test_is_swappable_v<int (Class::*)(int, ...) const>();
    test_is_swappable_v<int (Class::*)(int, ...) const&>();
    test_is_swappable_v<int (Class::*)(int, ...) const&&>();
    test_is_swappable_v<int (Class::*)(int, ...) noexcept>();
    test_is_swappable_v<int (Class::*)(int, ...)& noexcept>();
    test_is_swappable_v<int (Class::*)(int, ...)&& noexcept>();
    test_is_swappable_v<int (Class::*)(int, ...) const noexcept>();
    test_is_swappable_v<int (Class::*)(int, ...) const& noexcept>();
    test_is_swappable_v<int (Class::*)(int, ...) const&& noexcept>();
}
