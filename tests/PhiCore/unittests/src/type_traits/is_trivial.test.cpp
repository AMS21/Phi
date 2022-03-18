#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_trivial.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_trivial_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIAL()
    STATIC_REQUIRE(phi::is_trivial<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_trivial<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivial_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_trivial_v<T>);
#    endif

    // Standard compatibility
    STATIC_REQUIRE(std::is_trivial<T>::value);
#endif
}

template <typename T>
void test_is_not_trivial_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIAL()
    STATIC_REQUIRE_FALSE(phi::is_trivial<T>::value);
    STATIC_REQUIRE(phi::is_not_trivial<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivial_v<T>);
    STATIC_REQUIRE(phi::is_not_trivial_v<T>);
#    endif

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_trivial<T>::value);
#endif
}

template <typename T>
void test_is_trivial()
{
    test_is_trivial_impl<T>();
    test_is_trivial_impl<const T>();
    test_is_trivial_impl<volatile T>();
    test_is_trivial_impl<const volatile T>();
}

template <typename T>
void test_is_not_trivial()
{
    test_is_not_trivial_impl<T>();
    test_is_not_trivial_impl<const T>();
    test_is_not_trivial_impl<volatile T>();
    test_is_not_trivial_impl<const volatile T>();
}

struct A
{};

class B
{
public:
    B();
};

TEST_CASE("is_trivial")
{
    test_is_trivial<A>();
    test_is_not_trivial<B>();

    test_is_not_trivial<void>();
    test_is_trivial<phi::nullptr_t>();
    test_is_trivial<bool>();
    test_is_trivial<char>();
    test_is_trivial<signed char>();
    test_is_trivial<unsigned char>();
    test_is_trivial<short>();
    test_is_trivial<unsigned short>();
    test_is_trivial<int>();
    test_is_trivial<unsigned int>();
    test_is_trivial<long>();
    test_is_trivial<unsigned long>();
    test_is_trivial<long long>();
    test_is_trivial<unsigned long long>();
    test_is_trivial<float>();
    test_is_trivial<double>();
    test_is_trivial<long double>();
    test_is_trivial<char8_t>();
    test_is_trivial<char16_t>();
    test_is_trivial<char32_t>();
    test_is_trivial<wchar_t>();

#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivial<phi::boolean>();
    test_is_not_trivial<phi::integer<signed char>>();
    test_is_not_trivial<phi::integer<unsigned char>>();
    test_is_not_trivial<phi::integer<short>>();
    test_is_not_trivial<phi::integer<unsigned short>>();
    test_is_not_trivial<phi::integer<int>>();
    test_is_not_trivial<phi::integer<unsigned int>>();
    test_is_not_trivial<phi::integer<long>>();
    test_is_not_trivial<phi::integer<unsigned long>>();
    test_is_not_trivial<phi::integer<long long>>();
    test_is_not_trivial<phi::integer<unsigned long long>>();
    test_is_not_trivial<phi::floating_point<float>>();
    test_is_not_trivial<phi::floating_point<double>>();
    test_is_not_trivial<phi::floating_point<long double>>();
#elif PHI_COMPILER_IS(WINCLANG)
    // TODO: Investigate these
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
#else
    test_is_trivial<phi::boolean>();
    test_is_trivial<phi::integer<signed char>>();
    test_is_trivial<phi::integer<unsigned char>>();
    test_is_trivial<phi::integer<short>>();
    test_is_trivial<phi::integer<unsigned short>>();
    test_is_trivial<phi::integer<int>>();
    test_is_trivial<phi::integer<unsigned int>>();
    test_is_trivial<phi::integer<long>>();
    test_is_trivial<phi::integer<unsigned long>>();
    test_is_trivial<phi::integer<long long>>();
    test_is_trivial<phi::integer<unsigned long long>>();
    test_is_trivial<phi::floating_point<float>>();
    test_is_trivial<phi::floating_point<double>>();
    test_is_trivial<phi::floating_point<long double>>();
#endif

    test_is_not_trivial<std::vector<int>>();
    test_is_not_trivial<phi::scope_ptr<int>>();

    test_is_not_trivial<int&>();
    test_is_not_trivial<const int&>();
    test_is_not_trivial<volatile int&>();
    test_is_not_trivial<const volatile int&>();
    test_is_not_trivial<int&&>();
    test_is_not_trivial<const int&&>();
    test_is_not_trivial<volatile int&&>();
    test_is_not_trivial<const volatile int&&>();
    test_is_trivial<int*>();
    test_is_trivial<const int*>();
    test_is_trivial<volatile int*>();
    test_is_trivial<const volatile int*>();
    test_is_trivial<int**>();
    test_is_trivial<const int**>();
    test_is_trivial<volatile int**>();
    test_is_trivial<const volatile int**>();
    test_is_not_trivial<int*&>();
    test_is_not_trivial<const int*&>();
    test_is_not_trivial<volatile int*&>();
    test_is_not_trivial<const volatile int*&>();
    test_is_not_trivial<int*&&>();
    test_is_not_trivial<const int*&&>();
    test_is_not_trivial<volatile int*&&>();
    test_is_not_trivial<const volatile int*&&>();
    test_is_trivial<void*>();
    test_is_trivial<char[3]>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivial<char[]>();
#elif PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_trivial<char[]>();
#endif
    test_is_trivial<char* [3]>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivial<char*[]>();
#elif PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_trivial<char*[]>();
#endif
    test_is_trivial<int(*)[3]>();
    test_is_trivial<int(*)[]>();
    test_is_not_trivial<int(&)[3]>();
    test_is_not_trivial<int(&)[]>();
    test_is_not_trivial<int(&&)[3]>();
    test_is_not_trivial<int(&&)[]>();
    test_is_trivial<char[3][2]>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivial<char[][2]>();
#elif PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_trivial<char[][2]>();
#endif
    test_is_trivial<char* [3][2]>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivial<char*[][2]>();
#elif PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_trivial<char*[][2]>();
#endif
    test_is_trivial<int(*)[3][2]>();
    test_is_trivial<int(*)[][2]>();
    test_is_not_trivial<int(&)[3][2]>();
    test_is_not_trivial<int(&)[][2]>();
    test_is_not_trivial<int(&&)[3][2]>();
    test_is_not_trivial<int(&&)[][2]>();
    test_is_not_trivial<Class>();
    test_is_not_trivial<Class[]>();
    test_is_not_trivial<Class[2]>();
    test_is_trivial<Template<void>>();
    test_is_trivial<Template<int>>();
    test_is_trivial<Template<Class>>();
    test_is_trivial<Template<IncompleteType>>();
    test_is_trivial<VariadicTemplate<>>();
    test_is_trivial<VariadicTemplate<void>>();
    test_is_trivial<VariadicTemplate<int>>();
    test_is_trivial<VariadicTemplate<Class>>();
    test_is_trivial<VariadicTemplate<IncompleteType>>();
    test_is_trivial<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_trivial<PublicDerivedFromTemplate<Base>>();
    test_is_trivial<PublicDerivedFromTemplate<Derived>>();
    test_is_not_trivial<PublicDerivedFromTemplate<Class>>();
    test_is_trivial<PrivateDerivedFromTemplate<Base>>();
    test_is_trivial<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_trivial<PrivateDerivedFromTemplate<Class>>();
    test_is_trivial<ProtectedDerivedFromTemplate<Base>>();
    test_is_trivial<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_trivial<ProtectedDerivedFromTemplate<Class>>();
    test_is_trivial<Union>();
    test_is_trivial<NonEmptyUnion>();
    test_is_trivial<Empty>();
    test_is_not_trivial<NotEmpty>();
    test_is_trivial<BitZero>();
    test_is_trivial<BitOne>();
    test_is_trivial<Base>();
    test_is_trivial<Derived>();
    test_is_not_trivial<Abstract>();
    test_is_not_trivial<PublicAbstract>();
    test_is_not_trivial<PrivateAbstract>();
    test_is_not_trivial<ProtectedAbstract>();
    test_is_not_trivial<AbstractTemplate<int>>();
    test_is_trivial<AbstractTemplate<double>>();
    test_is_not_trivial<AbstractTemplate<Class>>();
    test_is_not_trivial<AbstractTemplate<IncompleteType>>();
    test_is_trivial<Final>();
    test_is_trivial<PublicDestructor>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivial<ProtectedDestructor>();
    test_is_not_trivial<PrivateDestructor>();
#elif PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
    SKIP_CHECK();
#else
    test_is_trivial<ProtectedDestructor>();
    test_is_trivial<PrivateDestructor>();
#endif
    test_is_not_trivial<VirtualPublicDestructor>();
    test_is_not_trivial<VirtualProtectedDestructor>();
    test_is_not_trivial<VirtualPrivateDestructor>();
    test_is_not_trivial<PurePublicDestructor>();
    test_is_not_trivial<PureProtectedDestructor>();
    test_is_not_trivial<PurePrivateDestructor>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivial<DeletedPublicDestructor>();
    test_is_not_trivial<DeletedProtectedDestructor>();
    test_is_not_trivial<DeletedPrivateDestructor>();
#elif PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
#else
    test_is_trivial<DeletedPublicDestructor>();
    test_is_trivial<DeletedProtectedDestructor>();
    test_is_trivial<DeletedPrivateDestructor>();
#endif
    test_is_not_trivial<DeletedVirtualPublicDestructor>();
    test_is_not_trivial<DeletedVirtualProtectedDestructor>();
    test_is_not_trivial<DeletedVirtualPrivateDestructor>();
    test_is_trivial<Enum>();
    test_is_trivial<EnumSigned>();
    test_is_trivial<EnumUnsigned>();
    test_is_trivial<EnumClass>();
    test_is_trivial<EnumStruct>();
    test_is_not_trivial<Function>();
    test_is_trivial<FunctionPtr>();
    test_is_trivial<MemberObjectPtr>();
    test_is_trivial<MemberFunctionPtr>();
    test_is_trivial<int Class::*>();
    test_is_trivial<float Class::*>();
    test_is_trivial<void * Class::*>();
    test_is_trivial<int * Class::*>();
    test_is_not_trivial<int Class::*&>();
    test_is_not_trivial<float Class::*&>();
    test_is_not_trivial<void * Class::*&>();
    test_is_not_trivial<int * Class::*&>();
    test_is_not_trivial<int Class::*&&>();
    test_is_not_trivial<float Class::*&&>();
    test_is_not_trivial<void * Class::*&&>();
    test_is_not_trivial<int * Class::*&&>();
    test_is_trivial<int Class::*const>();
    test_is_trivial<float Class::*const>();
    test_is_trivial<void * Class::*const>();
    test_is_not_trivial<int Class::*const&>();
    test_is_not_trivial<float Class::*const&>();
    test_is_not_trivial<void * Class::*const&>();
    test_is_not_trivial<int Class::*const&&>();
    test_is_not_trivial<float Class::*const&&>();
    test_is_not_trivial<void * Class::*const&&>();
    test_is_trivial<int Class::*volatile>();
    test_is_trivial<float Class::*volatile>();
    test_is_trivial<void * Class::*volatile>();
    test_is_not_trivial<int Class::*volatile&>();
    test_is_not_trivial<float Class::*volatile&>();
    test_is_not_trivial<void * Class::*volatile&>();
    test_is_not_trivial<int Class::*volatile&&>();
    test_is_not_trivial<float Class::*volatile&&>();
    test_is_not_trivial<void * Class::*volatile&&>();
    test_is_trivial<int Class::*const volatile>();
    test_is_trivial<float Class::*const volatile>();
    test_is_trivial<void * Class::*const volatile>();
    test_is_not_trivial<int Class::*const volatile&>();
    test_is_not_trivial<float Class::*const volatile&>();
    test_is_not_trivial<void * Class::*const volatile&>();
    test_is_not_trivial<int Class::*const volatile&&>();
    test_is_not_trivial<float Class::*const volatile&&>();
    test_is_not_trivial<void * Class::*const volatile&&>();
    test_is_trivial<NonCopyable>();
    test_is_trivial<NonMoveable>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivial<NonConstructible>();
#elif PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_trivial<NonConstructible>();
#endif
    test_is_not_trivial<Tracked>();
#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS_BELOW(CLANG, 11, 0, 0) ||     \
        PHI_COMPILER_IS_BELOW(EMCC, 1, 39, 0) || PHI_COMPILER_IS(APPLECLANG)
    // TODO: Investigate by clang, GCC and MSVC disagree here so much
    test_is_trivial<TrapConstructible>();
#elif PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_not_trivial<TrapConstructible>();
#endif
    test_is_trivial<TrapImplicitConversion>();
    test_is_trivial<TrapComma>();
    test_is_trivial<TrapCall>();
    test_is_not_trivial<TrapSelfAssign>();
    test_is_trivial<TrapDeref>();
    test_is_trivial<TrapArraySubscript>();

    test_is_not_trivial<void()>();
    test_is_not_trivial<void()&>();
    test_is_not_trivial<void() &&>();
    test_is_not_trivial<void() const>();
    test_is_not_trivial<void() const&>();
    test_is_not_trivial<void() const&&>();
    test_is_not_trivial<void() volatile>();
    test_is_not_trivial<void() volatile&>();
    test_is_not_trivial<void() volatile&&>();
    test_is_not_trivial<void() const volatile>();
    test_is_not_trivial<void() const volatile&>();
    test_is_not_trivial<void() const volatile&&>();
    test_is_not_trivial<void() noexcept>();
    test_is_not_trivial<void()& noexcept>();
    test_is_not_trivial<void()&& noexcept>();
    test_is_not_trivial<void() const noexcept>();
    test_is_not_trivial<void() const& noexcept>();
    test_is_not_trivial<void() const&& noexcept>();
    test_is_not_trivial<void() volatile noexcept>();
    test_is_not_trivial<void() volatile& noexcept>();
    test_is_not_trivial<void() volatile&& noexcept>();
    test_is_not_trivial<void() const volatile noexcept>();
    test_is_not_trivial<void() const volatile& noexcept>();
    test_is_not_trivial<void() const volatile&& noexcept>();

    test_is_not_trivial<void(int)>();
    test_is_not_trivial<void(int)&>();
    test_is_not_trivial<void(int) &&>();
    test_is_not_trivial<void(int) const>();
    test_is_not_trivial<void(int) const&>();
    test_is_not_trivial<void(int) const&&>();
    test_is_not_trivial<void(int) volatile>();
    test_is_not_trivial<void(int) volatile&>();
    test_is_not_trivial<void(int) volatile&&>();
    test_is_not_trivial<void(int) const volatile>();
    test_is_not_trivial<void(int) const volatile&>();
    test_is_not_trivial<void(int) const volatile&&>();
    test_is_not_trivial<void(int) noexcept>();
    test_is_not_trivial<void(int)& noexcept>();
    test_is_not_trivial<void(int)&& noexcept>();
    test_is_not_trivial<void(int) const noexcept>();
    test_is_not_trivial<void(int) const& noexcept>();
    test_is_not_trivial<void(int) const&& noexcept>();
    test_is_not_trivial<void(int) volatile noexcept>();
    test_is_not_trivial<void(int) volatile& noexcept>();
    test_is_not_trivial<void(int) volatile&& noexcept>();
    test_is_not_trivial<void(int) const volatile noexcept>();
    test_is_not_trivial<void(int) const volatile& noexcept>();
    test_is_not_trivial<void(int) const volatile&& noexcept>();

    test_is_not_trivial<void(...)>();
    test_is_not_trivial<void(...)&>();
    test_is_not_trivial<void(...) &&>();
    test_is_not_trivial<void(...) const>();
    test_is_not_trivial<void(...) const&>();
    test_is_not_trivial<void(...) const&&>();
    test_is_not_trivial<void(...) volatile>();
    test_is_not_trivial<void(...) volatile&>();
    test_is_not_trivial<void(...) volatile&&>();
    test_is_not_trivial<void(...) const volatile>();
    test_is_not_trivial<void(...) const volatile&>();
    test_is_not_trivial<void(...) const volatile&&>();
    test_is_not_trivial<void(...) noexcept>();
    test_is_not_trivial<void(...)& noexcept>();
    test_is_not_trivial<void(...)&& noexcept>();
    test_is_not_trivial<void(...) const noexcept>();
    test_is_not_trivial<void(...) const& noexcept>();
    test_is_not_trivial<void(...) const&& noexcept>();
    test_is_not_trivial<void(...) volatile noexcept>();
    test_is_not_trivial<void(...) volatile& noexcept>();
    test_is_not_trivial<void(...) volatile&& noexcept>();
    test_is_not_trivial<void(...) const volatile noexcept>();
    test_is_not_trivial<void(...) const volatile& noexcept>();
    test_is_not_trivial<void(...) const volatile&& noexcept>();

    test_is_not_trivial<void(int, ...)>();
    test_is_not_trivial<void(int, ...)&>();
    test_is_not_trivial<void(int, ...) &&>();
    test_is_not_trivial<void(int, ...) const>();
    test_is_not_trivial<void(int, ...) const&>();
    test_is_not_trivial<void(int, ...) const&&>();
    test_is_not_trivial<void(int, ...) volatile>();
    test_is_not_trivial<void(int, ...) volatile&>();
    test_is_not_trivial<void(int, ...) volatile&&>();
    test_is_not_trivial<void(int, ...) const volatile>();
    test_is_not_trivial<void(int, ...) const volatile&>();
    test_is_not_trivial<void(int, ...) const volatile&&>();
    test_is_not_trivial<void(int, ...) noexcept>();
    test_is_not_trivial<void(int, ...)& noexcept>();
    test_is_not_trivial<void(int, ...)&& noexcept>();
    test_is_not_trivial<void(int, ...) const noexcept>();
    test_is_not_trivial<void(int, ...) const& noexcept>();
    test_is_not_trivial<void(int, ...) const&& noexcept>();
    test_is_not_trivial<void(int, ...) volatile noexcept>();
    test_is_not_trivial<void(int, ...) volatile& noexcept>();
    test_is_not_trivial<void(int, ...) volatile&& noexcept>();
    test_is_not_trivial<void(int, ...) const volatile noexcept>();
    test_is_not_trivial<void(int, ...) const volatile& noexcept>();
    test_is_not_trivial<void(int, ...) const volatile&& noexcept>();

    test_is_not_trivial<int()>();
    test_is_not_trivial<int()&>();
    test_is_not_trivial<int() &&>();
    test_is_not_trivial<int() const>();
    test_is_not_trivial<int() const&>();
    test_is_not_trivial<int() const&&>();
    test_is_not_trivial<int() volatile>();
    test_is_not_trivial<int() volatile&>();
    test_is_not_trivial<int() volatile&&>();
    test_is_not_trivial<int() const volatile>();
    test_is_not_trivial<int() const volatile&>();
    test_is_not_trivial<int() const volatile&&>();
    test_is_not_trivial<int() noexcept>();
    test_is_not_trivial<int()& noexcept>();
    test_is_not_trivial<int()&& noexcept>();
    test_is_not_trivial<int() const noexcept>();
    test_is_not_trivial<int() const& noexcept>();
    test_is_not_trivial<int() const&& noexcept>();
    test_is_not_trivial<int() volatile noexcept>();
    test_is_not_trivial<int() volatile& noexcept>();
    test_is_not_trivial<int() volatile&& noexcept>();
    test_is_not_trivial<int() const volatile noexcept>();
    test_is_not_trivial<int() const volatile& noexcept>();
    test_is_not_trivial<int() const volatile&& noexcept>();

    test_is_not_trivial<int(int)>();
    test_is_not_trivial<int(int)&>();
    test_is_not_trivial<int(int) &&>();
    test_is_not_trivial<int(int) const>();
    test_is_not_trivial<int(int) const&>();
    test_is_not_trivial<int(int) const&&>();
    test_is_not_trivial<int(int) volatile>();
    test_is_not_trivial<int(int) volatile&>();
    test_is_not_trivial<int(int) volatile&&>();
    test_is_not_trivial<int(int) const volatile>();
    test_is_not_trivial<int(int) const volatile&>();
    test_is_not_trivial<int(int) const volatile&&>();
    test_is_not_trivial<int(int) noexcept>();
    test_is_not_trivial<int(int)& noexcept>();
    test_is_not_trivial<int(int)&& noexcept>();
    test_is_not_trivial<int(int) const noexcept>();
    test_is_not_trivial<int(int) const& noexcept>();
    test_is_not_trivial<int(int) const&& noexcept>();
    test_is_not_trivial<int(int) volatile noexcept>();
    test_is_not_trivial<int(int) volatile& noexcept>();
    test_is_not_trivial<int(int) volatile&& noexcept>();
    test_is_not_trivial<int(int) const volatile noexcept>();
    test_is_not_trivial<int(int) const volatile& noexcept>();
    test_is_not_trivial<int(int) const volatile&& noexcept>();

    test_is_not_trivial<int(...)>();
    test_is_not_trivial<int(...)&>();
    test_is_not_trivial<int(...) &&>();
    test_is_not_trivial<int(...) const>();
    test_is_not_trivial<int(...) const&>();
    test_is_not_trivial<int(...) const&&>();
    test_is_not_trivial<int(...) volatile>();
    test_is_not_trivial<int(...) volatile&>();
    test_is_not_trivial<int(...) volatile&&>();
    test_is_not_trivial<int(...) const volatile>();
    test_is_not_trivial<int(...) const volatile&>();
    test_is_not_trivial<int(...) const volatile&&>();
    test_is_not_trivial<int(...) noexcept>();
    test_is_not_trivial<int(...)& noexcept>();
    test_is_not_trivial<int(...)&& noexcept>();
    test_is_not_trivial<int(...) const noexcept>();
    test_is_not_trivial<int(...) const& noexcept>();
    test_is_not_trivial<int(...) const&& noexcept>();
    test_is_not_trivial<int(...) volatile noexcept>();
    test_is_not_trivial<int(...) volatile& noexcept>();
    test_is_not_trivial<int(...) volatile&& noexcept>();
    test_is_not_trivial<int(...) const volatile noexcept>();
    test_is_not_trivial<int(...) const volatile& noexcept>();
    test_is_not_trivial<int(...) const volatile&& noexcept>();

    test_is_not_trivial<int(int, ...)>();
    test_is_not_trivial<int(int, ...)&>();
    test_is_not_trivial<int(int, ...) &&>();
    test_is_not_trivial<int(int, ...) const>();
    test_is_not_trivial<int(int, ...) const&>();
    test_is_not_trivial<int(int, ...) const&&>();
    test_is_not_trivial<int(int, ...) volatile>();
    test_is_not_trivial<int(int, ...) volatile&>();
    test_is_not_trivial<int(int, ...) volatile&&>();
    test_is_not_trivial<int(int, ...) const volatile>();
    test_is_not_trivial<int(int, ...) const volatile&>();
    test_is_not_trivial<int(int, ...) const volatile&&>();
    test_is_not_trivial<int(int, ...) noexcept>();
    test_is_not_trivial<int(int, ...)& noexcept>();
    test_is_not_trivial<int(int, ...)&& noexcept>();
    test_is_not_trivial<int(int, ...) const noexcept>();
    test_is_not_trivial<int(int, ...) const& noexcept>();
    test_is_not_trivial<int(int, ...) const&& noexcept>();
    test_is_not_trivial<int(int, ...) volatile noexcept>();
    test_is_not_trivial<int(int, ...) volatile& noexcept>();
    test_is_not_trivial<int(int, ...) volatile&& noexcept>();
    test_is_not_trivial<int(int, ...) const volatile noexcept>();
    test_is_not_trivial<int(int, ...) const volatile& noexcept>();
    test_is_not_trivial<int(int, ...) const volatile&& noexcept>();

    test_is_trivial<void (*)()>();
    test_is_trivial<void (*)() noexcept>();

    test_is_trivial<void (*)(int)>();
    test_is_trivial<void (*)(int) noexcept>();

    test_is_trivial<void (*)(...)>();
    test_is_trivial<void (*)(...) noexcept>();

    test_is_trivial<void (*)(int, ...)>();
    test_is_trivial<void (*)(int, ...) noexcept>();

    test_is_trivial<int (*)()>();
    test_is_trivial<int (*)() noexcept>();

    test_is_trivial<int (*)(int)>();
    test_is_trivial<int (*)(int) noexcept>();

    test_is_trivial<int (*)(...)>();
    test_is_trivial<int (*)(...) noexcept>();

    test_is_trivial<int (*)(int, ...)>();
    test_is_trivial<int (*)(int, ...) noexcept>();

    test_is_not_trivial<void (&)()>();
    test_is_not_trivial<void (&)() noexcept>();

    test_is_not_trivial<void (&)(int)>();
    test_is_not_trivial<void (&)(int) noexcept>();

    test_is_not_trivial<void (&)(...)>();
    test_is_not_trivial<void (&)(...) noexcept>();

    test_is_not_trivial<void (&)(int, ...)>();
    test_is_not_trivial<void (&)(int, ...) noexcept>();

    test_is_not_trivial<int (&)()>();
    test_is_not_trivial<int (&)() noexcept>();

    test_is_not_trivial<int (&)(int)>();
    test_is_not_trivial<int (&)(int) noexcept>();

    test_is_not_trivial<int (&)(...)>();
    test_is_not_trivial<int (&)(...) noexcept>();

    test_is_not_trivial<int (&)(int, ...)>();
    test_is_not_trivial<int (&)(int, ...) noexcept>();

    test_is_not_trivial<void(&&)()>();
    test_is_not_trivial<void(&&)() noexcept>();

    test_is_not_trivial<void(&&)(int)>();
    test_is_not_trivial<void(&&)(int) noexcept>();

    test_is_not_trivial<void(&&)(...)>();
    test_is_not_trivial<void(&&)(...) noexcept>();

    test_is_not_trivial<void(&&)(int, ...)>();
    test_is_not_trivial<void(&&)(int, ...) noexcept>();

    test_is_not_trivial<int(&&)()>();
    test_is_not_trivial<int(&&)() noexcept>();

    test_is_not_trivial<int(&&)(int)>();
    test_is_not_trivial<int(&&)(int) noexcept>();

    test_is_not_trivial<int(&&)(...)>();
    test_is_not_trivial<int(&&)(...) noexcept>();

    test_is_not_trivial<int(&&)(int, ...)>();
    test_is_not_trivial<int(&&)(int, ...) noexcept>();

    test_is_trivial<void (Class::*)()>();
    test_is_trivial<void (Class::*)()&>();
    test_is_trivial<void (Class::*)() &&>();
    test_is_trivial<void (Class::*)() const>();
    test_is_trivial<void (Class::*)() const&>();
    test_is_trivial<void (Class::*)() const&&>();
    test_is_trivial<void (Class::*)() noexcept>();
    test_is_trivial<void (Class::*)()& noexcept>();
    test_is_trivial<void (Class::*)()&& noexcept>();
    test_is_trivial<void (Class::*)() const noexcept>();
    test_is_trivial<void (Class::*)() const& noexcept>();
    test_is_trivial<void (Class::*)() const&& noexcept>();

    test_is_trivial<void (Class::*)(int)>();
    test_is_trivial<void (Class::*)(int)&>();
    test_is_trivial<void (Class::*)(int) &&>();
    test_is_trivial<void (Class::*)(int) const>();
    test_is_trivial<void (Class::*)(int) const&>();
    test_is_trivial<void (Class::*)(int) const&&>();
    test_is_trivial<void (Class::*)(int) noexcept>();
    test_is_trivial<void (Class::*)(int)& noexcept>();
    test_is_trivial<void (Class::*)(int)&& noexcept>();
    test_is_trivial<void (Class::*)(int) const noexcept>();
    test_is_trivial<void (Class::*)(int) const& noexcept>();
    test_is_trivial<void (Class::*)(int) const&& noexcept>();

    test_is_trivial<void (Class::*)(...)>();
    test_is_trivial<void (Class::*)(...)&>();
    test_is_trivial<void (Class::*)(...) &&>();
    test_is_trivial<void (Class::*)(...) const>();
    test_is_trivial<void (Class::*)(...) const&>();
    test_is_trivial<void (Class::*)(...) const&&>();
    test_is_trivial<void (Class::*)(...) noexcept>();
    test_is_trivial<void (Class::*)(...)& noexcept>();
    test_is_trivial<void (Class::*)(...)&& noexcept>();
    test_is_trivial<void (Class::*)(...) const noexcept>();
    test_is_trivial<void (Class::*)(...) const& noexcept>();
    test_is_trivial<void (Class::*)(...) const&& noexcept>();

    test_is_trivial<void (Class::*)(int, ...)>();
    test_is_trivial<void (Class::*)(int, ...)&>();
    test_is_trivial<void (Class::*)(int, ...) &&>();
    test_is_trivial<void (Class::*)(int, ...) const>();
    test_is_trivial<void (Class::*)(int, ...) const&>();
    test_is_trivial<void (Class::*)(int, ...) const&&>();
    test_is_trivial<void (Class::*)(int, ...) noexcept>();
    test_is_trivial<void (Class::*)(int, ...)& noexcept>();
    test_is_trivial<void (Class::*)(int, ...)&& noexcept>();
    test_is_trivial<void (Class::*)(int, ...) const noexcept>();
    test_is_trivial<void (Class::*)(int, ...) const& noexcept>();
    test_is_trivial<void (Class::*)(int, ...) const&& noexcept>();

    test_is_trivial<int (Class::*)()>();
    test_is_trivial<int (Class::*)()&>();
    test_is_trivial<int (Class::*)() &&>();
    test_is_trivial<int (Class::*)() const>();
    test_is_trivial<int (Class::*)() const&>();
    test_is_trivial<int (Class::*)() const&&>();
    test_is_trivial<int (Class::*)() noexcept>();
    test_is_trivial<int (Class::*)()& noexcept>();
    test_is_trivial<int (Class::*)()&& noexcept>();
    test_is_trivial<int (Class::*)() const noexcept>();
    test_is_trivial<int (Class::*)() const& noexcept>();
    test_is_trivial<int (Class::*)() const&& noexcept>();

    test_is_trivial<int (Class::*)(int)>();
    test_is_trivial<int (Class::*)(int)&>();
    test_is_trivial<int (Class::*)(int) &&>();
    test_is_trivial<int (Class::*)(int) const>();
    test_is_trivial<int (Class::*)(int) const&>();
    test_is_trivial<int (Class::*)(int) const&&>();
    test_is_trivial<int (Class::*)(int) noexcept>();
    test_is_trivial<int (Class::*)(int)& noexcept>();
    test_is_trivial<int (Class::*)(int)&& noexcept>();
    test_is_trivial<int (Class::*)(int) const noexcept>();
    test_is_trivial<int (Class::*)(int) const& noexcept>();
    test_is_trivial<int (Class::*)(int) const&& noexcept>();

    test_is_trivial<int (Class::*)(...)>();
    test_is_trivial<int (Class::*)(...)&>();
    test_is_trivial<int (Class::*)(...) &&>();
    test_is_trivial<int (Class::*)(...) const>();
    test_is_trivial<int (Class::*)(...) const&>();
    test_is_trivial<int (Class::*)(...) const&&>();
    test_is_trivial<int (Class::*)(...) noexcept>();
    test_is_trivial<int (Class::*)(...)& noexcept>();
    test_is_trivial<int (Class::*)(...)&& noexcept>();
    test_is_trivial<int (Class::*)(...) const noexcept>();
    test_is_trivial<int (Class::*)(...) const& noexcept>();
    test_is_trivial<int (Class::*)(...) const&& noexcept>();

    test_is_trivial<int (Class::*)(int, ...)>();
    test_is_trivial<int (Class::*)(int, ...)&>();
    test_is_trivial<int (Class::*)(int, ...) &&>();
    test_is_trivial<int (Class::*)(int, ...) const>();
    test_is_trivial<int (Class::*)(int, ...) const&>();
    test_is_trivial<int (Class::*)(int, ...) const&&>();
    test_is_trivial<int (Class::*)(int, ...) noexcept>();
    test_is_trivial<int (Class::*)(int, ...)& noexcept>();
    test_is_trivial<int (Class::*)(int, ...)&& noexcept>();
    test_is_trivial<int (Class::*)(int, ...) const noexcept>();
    test_is_trivial<int (Class::*)(int, ...) const& noexcept>();
    test_is_trivial<int (Class::*)(int, ...) const&& noexcept>();
}
