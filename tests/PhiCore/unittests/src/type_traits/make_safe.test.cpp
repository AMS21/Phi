#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_safe_bool.hpp>
#include <phi/type_traits/make_safe.hpp>
#include <vector>

struct A; // incomplete

template <typename InT, typename OutT = InT>
void test_make_safe()
{
    CHECK_SAME_TYPE(typename phi::make_safe<InT>::type, OutT);
    CHECK_SAME_TYPE(typename phi::make_safe<const InT>::type, const OutT);
    CHECK_SAME_TYPE(typename phi::make_safe<volatile InT>::type, volatile OutT);
    CHECK_SAME_TYPE(typename phi::make_safe<const volatile InT>::type, const volatile OutT);

    CHECK_SAME_TYPE(typename phi::make_safe_t<InT>, OutT);
    CHECK_SAME_TYPE(typename phi::make_safe_t<const InT>, const OutT);
    CHECK_SAME_TYPE(typename phi::make_safe_t<volatile InT>, volatile OutT);
    CHECK_SAME_TYPE(typename phi::make_safe_t<const volatile InT>, const volatile OutT);
}

TEST_CASE("make_safe")
{
    test_make_safe<void>();
    test_make_safe<phi::nullptr_t>();
    test_make_safe<bool, phi::boolean>();
    test_make_safe<char, char>();
    test_make_safe<signed char, phi::integer<signed char>>();
    test_make_safe<unsigned char, phi::integer<unsigned char>>();
    test_make_safe<short, phi::integer<short>>();
    test_make_safe<unsigned short, phi::integer<unsigned short>>();
    test_make_safe<int, phi::integer<int>>();
    test_make_safe<unsigned int, phi::integer<unsigned int>>();
    test_make_safe<long, phi::integer<long>>();
    test_make_safe<unsigned long, phi::integer<unsigned long>>();
    test_make_safe<long long, phi::integer<long long>>();
    test_make_safe<unsigned long long, phi::integer<unsigned long long>>();
    test_make_safe<float, phi::floating_point<float>>();
    test_make_safe<double, phi::floating_point<double>>();
    test_make_safe<long double, phi::floating_point<long double>>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_make_safe<char8_t>();
#endif
    test_make_safe<char16_t>();
    test_make_safe<char32_t>();
    test_make_safe<wchar_t>();

    test_make_safe<phi::boolean>();
    test_make_safe<phi::integer<signed char>>();
    test_make_safe<phi::integer<unsigned char>>();
    test_make_safe<phi::integer<short>>();
    test_make_safe<phi::integer<unsigned short>>();
    test_make_safe<phi::integer<int>>();
    test_make_safe<phi::integer<unsigned int>>();
    test_make_safe<phi::integer<long>>();
    test_make_safe<phi::integer<unsigned long>>();
    test_make_safe<phi::integer<long long>>();
    test_make_safe<phi::integer<unsigned long long>>();
    test_make_safe<phi::floating_point<float>>();
    test_make_safe<phi::floating_point<double>>();
    test_make_safe<phi::floating_point<long double>>();

    test_make_safe<std::vector<int>>();
    test_make_safe<phi::scope_ptr<int>>();

    test_make_safe<int&>();
    test_make_safe<const int&>();
    test_make_safe<volatile int&>();
    test_make_safe<const volatile int&>();
    test_make_safe<int&&>();
    test_make_safe<const int&&>();
    test_make_safe<volatile int&&>();
    test_make_safe<const volatile int&&>();
    test_make_safe<int*>();
    test_make_safe<const int*>();
    test_make_safe<volatile int*>();
    test_make_safe<const volatile int*>();
    test_make_safe<int**>();
    test_make_safe<const int**>();
    test_make_safe<volatile int**>();
    test_make_safe<const volatile int**>();
    test_make_safe<int*&>();
    test_make_safe<const int*&>();
    test_make_safe<volatile int*&>();
    test_make_safe<const volatile int*&>();
    test_make_safe<int*&&>();
    test_make_safe<const int*&&>();
    test_make_safe<volatile int*&&>();
    test_make_safe<const volatile int*&&>();
    test_make_safe<void*>();
    test_make_safe<char[3]>();
    test_make_safe<char[]>();
    test_make_safe<char* [3]>();
    test_make_safe<char*[]>();
    test_make_safe<int(*)[3]>();
    test_make_safe<int(*)[]>();
    test_make_safe<int(&)[3]>();
    test_make_safe<int(&)[]>();
    test_make_safe<int(&&)[3]>();
    test_make_safe<int(&&)[]>();
    test_make_safe<char[3][2]>();
    test_make_safe<char[][2]>();
    test_make_safe<char* [3][2]>();
    test_make_safe<char*[][2]>();
    test_make_safe<int(*)[3][2]>();
    test_make_safe<int(*)[][2]>();
    test_make_safe<int(&)[3][2]>();
    test_make_safe<int(&)[][2]>();
    test_make_safe<int(&&)[3][2]>();
    test_make_safe<int(&&)[][2]>();
    test_make_safe<Class>();
    test_make_safe<Class[]>();
    test_make_safe<Class[2]>();
    test_make_safe<Template<void>>();
    test_make_safe<Template<int>>();
    test_make_safe<Template<Class>>();
    test_make_safe<Template<IncompleteType>>();
    test_make_safe<VariadicTemplate<>>();
    test_make_safe<VariadicTemplate<void>>();
    test_make_safe<VariadicTemplate<int>>();
    test_make_safe<VariadicTemplate<Class>>();
    test_make_safe<VariadicTemplate<IncompleteType>>();
    test_make_safe<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_make_safe<PublicDerivedFromTemplate<Base>>();
    test_make_safe<PublicDerivedFromTemplate<Derived>>();
    test_make_safe<PublicDerivedFromTemplate<Class>>();
    test_make_safe<PrivateDerivedFromTemplate<Base>>();
    test_make_safe<PrivateDerivedFromTemplate<Derived>>();
    test_make_safe<PrivateDerivedFromTemplate<Class>>();
    test_make_safe<ProtectedDerivedFromTemplate<Base>>();
    test_make_safe<ProtectedDerivedFromTemplate<Derived>>();
    test_make_safe<ProtectedDerivedFromTemplate<Class>>();
    test_make_safe<Union>();
    test_make_safe<NonEmptyUnion>();
    test_make_safe<Empty>();
    test_make_safe<NotEmpty>();
    test_make_safe<BitZero>();
    test_make_safe<BitOne>();
    test_make_safe<Base>();
    test_make_safe<Derived>();
    test_make_safe<Abstract>();
    test_make_safe<PublicAbstract>();
    test_make_safe<PrivateAbstract>();
    test_make_safe<ProtectedAbstract>();
    test_make_safe<AbstractTemplate<int>>();
    test_make_safe<AbstractTemplate<double>>();
    test_make_safe<AbstractTemplate<Class>>();
    test_make_safe<AbstractTemplate<IncompleteType>>();
    test_make_safe<Final>();
    test_make_safe<PublicDestructor>();
    test_make_safe<ProtectedDestructor>();
    test_make_safe<PrivateDestructor>();
    test_make_safe<VirtualPublicDestructor>();
    test_make_safe<VirtualProtectedDestructor>();
    test_make_safe<VirtualPrivateDestructor>();
    test_make_safe<PurePublicDestructor>();
    test_make_safe<PureProtectedDestructor>();
    test_make_safe<PurePrivateDestructor>();
    test_make_safe<DeletedPublicDestructor>();
    test_make_safe<DeletedProtectedDestructor>();
    test_make_safe<DeletedPrivateDestructor>();
    test_make_safe<DeletedVirtualPublicDestructor>();
    test_make_safe<DeletedVirtualProtectedDestructor>();
    test_make_safe<DeletedVirtualPrivateDestructor>();
    test_make_safe<Enum>();
    test_make_safe<EnumSigned>();
    test_make_safe<EnumUnsigned>();
    test_make_safe<EnumClass>();
    test_make_safe<EnumStruct>();
    test_make_safe<Function>();
    test_make_safe<FunctionPtr>();
    test_make_safe<MemberObjectPtr>();
    test_make_safe<MemberFunctionPtr>();
    test_make_safe<IncompleteType>();
    test_make_safe<IncompleteTemplate<void>>();
    test_make_safe<IncompleteTemplate<int>>();
    test_make_safe<IncompleteTemplate<Class>>();
    test_make_safe<IncompleteTemplate<IncompleteType>>();
    test_make_safe<IncompleteVariadicTemplate<>>();
    test_make_safe<IncompleteVariadicTemplate<void>>();
    test_make_safe<IncompleteVariadicTemplate<int>>();
    test_make_safe<IncompleteVariadicTemplate<Class>>();
    test_make_safe<IncompleteVariadicTemplate<IncompleteType>>();
    test_make_safe<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_make_safe<int Class::*>();
    test_make_safe<float Class::*>();
    test_make_safe<void * Class::*>();
    test_make_safe<int * Class::*>();
    test_make_safe<int Class::*&>();
    test_make_safe<float Class::*&>();
    test_make_safe<void * Class::*&>();
    test_make_safe<int * Class::*&>();
    test_make_safe<int Class::*&&>();
    test_make_safe<float Class::*&&>();
    test_make_safe<void * Class::*&&>();
    test_make_safe<int * Class::*&&>();
    test_make_safe<int Class::*const>();
    test_make_safe<float Class::*const>();
    test_make_safe<void * Class::*const>();
    test_make_safe<int Class::*const&>();
    test_make_safe<float Class::*const&>();
    test_make_safe<void * Class::*const&>();
    test_make_safe<int Class::*const&&>();
    test_make_safe<float Class::*const&&>();
    test_make_safe<void * Class::*const&&>();
    test_make_safe<int Class::*volatile>();
    test_make_safe<float Class::*volatile>();
    test_make_safe<void * Class::*volatile>();
    test_make_safe<int Class::*volatile&>();
    test_make_safe<float Class::*volatile&>();
    test_make_safe<void * Class::*volatile&>();
    test_make_safe<int Class::*volatile&&>();
    test_make_safe<float Class::*volatile&&>();
    test_make_safe<void * Class::*volatile&&>();
    test_make_safe<int Class::*const volatile>();
    test_make_safe<float Class::*const volatile>();
    test_make_safe<void * Class::*const volatile>();
    test_make_safe<int Class::*const volatile&>();
    test_make_safe<float Class::*const volatile&>();
    test_make_safe<void * Class::*const volatile&>();
    test_make_safe<int Class::*const volatile&&>();
    test_make_safe<float Class::*const volatile&&>();
    test_make_safe<void * Class::*const volatile&&>();
    test_make_safe<NonCopyable>();
    test_make_safe<NonMoveable>();
    test_make_safe<NonConstructible>();
    test_make_safe<Tracked>();
    test_make_safe<TrapConstructible>();
    test_make_safe<TrapImplicitConversion>();
    test_make_safe<TrapComma>();
    test_make_safe<TrapCall>();
    test_make_safe<TrapSelfAssign>();
    test_make_safe<TrapDeref>();
    test_make_safe<TrapArraySubscript>();

    test_make_safe<void()>();
    test_make_safe<void()&>();
    test_make_safe<void() &&>();
    test_make_safe<void() const>();
    test_make_safe<void() const&>();
    test_make_safe<void() const&&>();
    test_make_safe<void() volatile>();
    test_make_safe<void() volatile&>();
    test_make_safe<void() volatile&&>();
    test_make_safe<void() const volatile>();
    test_make_safe<void() const volatile&>();
    test_make_safe<void() const volatile&&>();
    test_make_safe<void() noexcept>();
    test_make_safe<void()& noexcept>();
    test_make_safe<void()&& noexcept>();
    test_make_safe<void() const noexcept>();
    test_make_safe<void() const& noexcept>();
    test_make_safe<void() const&& noexcept>();
    test_make_safe<void() volatile noexcept>();
    test_make_safe<void() volatile& noexcept>();
    test_make_safe<void() volatile&& noexcept>();
    test_make_safe<void() const volatile noexcept>();
    test_make_safe<void() const volatile& noexcept>();
    test_make_safe<void() const volatile&& noexcept>();

    test_make_safe<void(int)>();
    test_make_safe<void(int)&>();
    test_make_safe<void(int) &&>();
    test_make_safe<void(int) const>();
    test_make_safe<void(int) const&>();
    test_make_safe<void(int) const&&>();
    test_make_safe<void(int) volatile>();
    test_make_safe<void(int) volatile&>();
    test_make_safe<void(int) volatile&&>();
    test_make_safe<void(int) const volatile>();
    test_make_safe<void(int) const volatile&>();
    test_make_safe<void(int) const volatile&&>();
    test_make_safe<void(int) noexcept>();
    test_make_safe<void(int)& noexcept>();
    test_make_safe<void(int)&& noexcept>();
    test_make_safe<void(int) const noexcept>();
    test_make_safe<void(int) const& noexcept>();
    test_make_safe<void(int) const&& noexcept>();
    test_make_safe<void(int) volatile noexcept>();
    test_make_safe<void(int) volatile& noexcept>();
    test_make_safe<void(int) volatile&& noexcept>();
    test_make_safe<void(int) const volatile noexcept>();
    test_make_safe<void(int) const volatile& noexcept>();
    test_make_safe<void(int) const volatile&& noexcept>();

    test_make_safe<void(...)>();
    test_make_safe<void(...)&>();
    test_make_safe<void(...) &&>();
    test_make_safe<void(...) const>();
    test_make_safe<void(...) const&>();
    test_make_safe<void(...) const&&>();
    test_make_safe<void(...) volatile>();
    test_make_safe<void(...) volatile&>();
    test_make_safe<void(...) volatile&&>();
    test_make_safe<void(...) const volatile>();
    test_make_safe<void(...) const volatile&>();
    test_make_safe<void(...) const volatile&&>();
    test_make_safe<void(...) noexcept>();
    test_make_safe<void(...)& noexcept>();
    test_make_safe<void(...)&& noexcept>();
    test_make_safe<void(...) const noexcept>();
    test_make_safe<void(...) const& noexcept>();
    test_make_safe<void(...) const&& noexcept>();
    test_make_safe<void(...) volatile noexcept>();
    test_make_safe<void(...) volatile& noexcept>();
    test_make_safe<void(...) volatile&& noexcept>();
    test_make_safe<void(...) const volatile noexcept>();
    test_make_safe<void(...) const volatile& noexcept>();
    test_make_safe<void(...) const volatile&& noexcept>();

    test_make_safe<void(int, ...)>();
    test_make_safe<void(int, ...)&>();
    test_make_safe<void(int, ...) &&>();
    test_make_safe<void(int, ...) const>();
    test_make_safe<void(int, ...) const&>();
    test_make_safe<void(int, ...) const&&>();
    test_make_safe<void(int, ...) volatile>();
    test_make_safe<void(int, ...) volatile&>();
    test_make_safe<void(int, ...) volatile&&>();
    test_make_safe<void(int, ...) const volatile>();
    test_make_safe<void(int, ...) const volatile&>();
    test_make_safe<void(int, ...) const volatile&&>();
    test_make_safe<void(int, ...) noexcept>();
    test_make_safe<void(int, ...)& noexcept>();
    test_make_safe<void(int, ...)&& noexcept>();
    test_make_safe<void(int, ...) const noexcept>();
    test_make_safe<void(int, ...) const& noexcept>();
    test_make_safe<void(int, ...) const&& noexcept>();
    test_make_safe<void(int, ...) volatile noexcept>();
    test_make_safe<void(int, ...) volatile& noexcept>();
    test_make_safe<void(int, ...) volatile&& noexcept>();
    test_make_safe<void(int, ...) const volatile noexcept>();
    test_make_safe<void(int, ...) const volatile& noexcept>();
    test_make_safe<void(int, ...) const volatile&& noexcept>();

    test_make_safe<int()>();
    test_make_safe<int()&>();
    test_make_safe<int() &&>();
    test_make_safe<int() const>();
    test_make_safe<int() const&>();
    test_make_safe<int() const&&>();
    test_make_safe<int() volatile>();
    test_make_safe<int() volatile&>();
    test_make_safe<int() volatile&&>();
    test_make_safe<int() const volatile>();
    test_make_safe<int() const volatile&>();
    test_make_safe<int() const volatile&&>();
    test_make_safe<int() noexcept>();
    test_make_safe<int()& noexcept>();
    test_make_safe<int()&& noexcept>();
    test_make_safe<int() const noexcept>();
    test_make_safe<int() const& noexcept>();
    test_make_safe<int() const&& noexcept>();
    test_make_safe<int() volatile noexcept>();
    test_make_safe<int() volatile& noexcept>();
    test_make_safe<int() volatile&& noexcept>();
    test_make_safe<int() const volatile noexcept>();
    test_make_safe<int() const volatile& noexcept>();
    test_make_safe<int() const volatile&& noexcept>();

    test_make_safe<int(int)>();
    test_make_safe<int(int)&>();
    test_make_safe<int(int) &&>();
    test_make_safe<int(int) const>();
    test_make_safe<int(int) const&>();
    test_make_safe<int(int) const&&>();
    test_make_safe<int(int) volatile>();
    test_make_safe<int(int) volatile&>();
    test_make_safe<int(int) volatile&&>();
    test_make_safe<int(int) const volatile>();
    test_make_safe<int(int) const volatile&>();
    test_make_safe<int(int) const volatile&&>();
    test_make_safe<int(int) noexcept>();
    test_make_safe<int(int)& noexcept>();
    test_make_safe<int(int)&& noexcept>();
    test_make_safe<int(int) const noexcept>();
    test_make_safe<int(int) const& noexcept>();
    test_make_safe<int(int) const&& noexcept>();
    test_make_safe<int(int) volatile noexcept>();
    test_make_safe<int(int) volatile& noexcept>();
    test_make_safe<int(int) volatile&& noexcept>();
    test_make_safe<int(int) const volatile noexcept>();
    test_make_safe<int(int) const volatile& noexcept>();
    test_make_safe<int(int) const volatile&& noexcept>();

    test_make_safe<int(...)>();
    test_make_safe<int(...)&>();
    test_make_safe<int(...) &&>();
    test_make_safe<int(...) const>();
    test_make_safe<int(...) const&>();
    test_make_safe<int(...) const&&>();
    test_make_safe<int(...) volatile>();
    test_make_safe<int(...) volatile&>();
    test_make_safe<int(...) volatile&&>();
    test_make_safe<int(...) const volatile>();
    test_make_safe<int(...) const volatile&>();
    test_make_safe<int(...) const volatile&&>();
    test_make_safe<int(...) noexcept>();
    test_make_safe<int(...)& noexcept>();
    test_make_safe<int(...)&& noexcept>();
    test_make_safe<int(...) const noexcept>();
    test_make_safe<int(...) const& noexcept>();
    test_make_safe<int(...) const&& noexcept>();
    test_make_safe<int(...) volatile noexcept>();
    test_make_safe<int(...) volatile& noexcept>();
    test_make_safe<int(...) volatile&& noexcept>();
    test_make_safe<int(...) const volatile noexcept>();
    test_make_safe<int(...) const volatile& noexcept>();
    test_make_safe<int(...) const volatile&& noexcept>();

    test_make_safe<int(int, ...)>();
    test_make_safe<int(int, ...)&>();
    test_make_safe<int(int, ...) &&>();
    test_make_safe<int(int, ...) const>();
    test_make_safe<int(int, ...) const&>();
    test_make_safe<int(int, ...) const&&>();
    test_make_safe<int(int, ...) volatile>();
    test_make_safe<int(int, ...) volatile&>();
    test_make_safe<int(int, ...) volatile&&>();
    test_make_safe<int(int, ...) const volatile>();
    test_make_safe<int(int, ...) const volatile&>();
    test_make_safe<int(int, ...) const volatile&&>();
    test_make_safe<int(int, ...) noexcept>();
    test_make_safe<int(int, ...)& noexcept>();
    test_make_safe<int(int, ...)&& noexcept>();
    test_make_safe<int(int, ...) const noexcept>();
    test_make_safe<int(int, ...) const& noexcept>();
    test_make_safe<int(int, ...) const&& noexcept>();
    test_make_safe<int(int, ...) volatile noexcept>();
    test_make_safe<int(int, ...) volatile& noexcept>();
    test_make_safe<int(int, ...) volatile&& noexcept>();
    test_make_safe<int(int, ...) const volatile noexcept>();
    test_make_safe<int(int, ...) const volatile& noexcept>();
    test_make_safe<int(int, ...) const volatile&& noexcept>();

    test_make_safe<void (*)()>();
    test_make_safe<void (*)() noexcept>();

    test_make_safe<void (*)(int)>();
    test_make_safe<void (*)(int) noexcept>();

    test_make_safe<void (*)(...)>();
    test_make_safe<void (*)(...) noexcept>();

    test_make_safe<void (*)(int, ...)>();
    test_make_safe<void (*)(int, ...) noexcept>();

    test_make_safe<int (*)()>();
    test_make_safe<int (*)() noexcept>();

    test_make_safe<int (*)(int)>();
    test_make_safe<int (*)(int) noexcept>();

    test_make_safe<int (*)(...)>();
    test_make_safe<int (*)(...) noexcept>();

    test_make_safe<int (*)(int, ...)>();
    test_make_safe<int (*)(int, ...) noexcept>();

    test_make_safe<void (&)()>();
    test_make_safe<void (&)() noexcept>();

    test_make_safe<void (&)(int)>();
    test_make_safe<void (&)(int) noexcept>();

    test_make_safe<void (&)(...)>();
    test_make_safe<void (&)(...) noexcept>();

    test_make_safe<void (&)(int, ...)>();
    test_make_safe<void (&)(int, ...) noexcept>();

    test_make_safe<int (&)()>();
    test_make_safe<int (&)() noexcept>();

    test_make_safe<int (&)(int)>();
    test_make_safe<int (&)(int) noexcept>();

    test_make_safe<int (&)(...)>();
    test_make_safe<int (&)(...) noexcept>();

    test_make_safe<int (&)(int, ...)>();
    test_make_safe<int (&)(int, ...) noexcept>();

    test_make_safe<void(&&)()>();
    test_make_safe<void(&&)() noexcept>();

    test_make_safe<void(&&)(int)>();
    test_make_safe<void(&&)(int) noexcept>();

    test_make_safe<void(&&)(...)>();
    test_make_safe<void(&&)(...) noexcept>();

    test_make_safe<void(&&)(int, ...)>();
    test_make_safe<void(&&)(int, ...) noexcept>();

    test_make_safe<int(&&)()>();
    test_make_safe<int(&&)() noexcept>();

    test_make_safe<int(&&)(int)>();
    test_make_safe<int(&&)(int) noexcept>();

    test_make_safe<int(&&)(...)>();
    test_make_safe<int(&&)(...) noexcept>();

    test_make_safe<int(&&)(int, ...)>();
    test_make_safe<int(&&)(int, ...) noexcept>();

    test_make_safe<void (Class::*)()>();
    test_make_safe<void (Class::*)()&>();
    test_make_safe<void (Class::*)() &&>();
    test_make_safe<void (Class::*)() const>();
    test_make_safe<void (Class::*)() const&>();
    test_make_safe<void (Class::*)() const&&>();
    test_make_safe<void (Class::*)() noexcept>();
    test_make_safe<void (Class::*)()& noexcept>();
    test_make_safe<void (Class::*)()&& noexcept>();
    test_make_safe<void (Class::*)() const noexcept>();
    test_make_safe<void (Class::*)() const& noexcept>();
    test_make_safe<void (Class::*)() const&& noexcept>();

    test_make_safe<void (Class::*)(int)>();
    test_make_safe<void (Class::*)(int)&>();
    test_make_safe<void (Class::*)(int) &&>();
    test_make_safe<void (Class::*)(int) const>();
    test_make_safe<void (Class::*)(int) const&>();
    test_make_safe<void (Class::*)(int) const&&>();
    test_make_safe<void (Class::*)(int) noexcept>();
    test_make_safe<void (Class::*)(int)& noexcept>();
    test_make_safe<void (Class::*)(int)&& noexcept>();
    test_make_safe<void (Class::*)(int) const noexcept>();
    test_make_safe<void (Class::*)(int) const& noexcept>();
    test_make_safe<void (Class::*)(int) const&& noexcept>();

    test_make_safe<void (Class::*)(...)>();
    test_make_safe<void (Class::*)(...)&>();
    test_make_safe<void (Class::*)(...) &&>();
    test_make_safe<void (Class::*)(...) const>();
    test_make_safe<void (Class::*)(...) const&>();
    test_make_safe<void (Class::*)(...) const&&>();
    test_make_safe<void (Class::*)(...) noexcept>();
    test_make_safe<void (Class::*)(...)& noexcept>();
    test_make_safe<void (Class::*)(...)&& noexcept>();
    test_make_safe<void (Class::*)(...) const noexcept>();
    test_make_safe<void (Class::*)(...) const& noexcept>();
    test_make_safe<void (Class::*)(...) const&& noexcept>();

    test_make_safe<void (Class::*)(int, ...)>();
    test_make_safe<void (Class::*)(int, ...)&>();
    test_make_safe<void (Class::*)(int, ...) &&>();
    test_make_safe<void (Class::*)(int, ...) const>();
    test_make_safe<void (Class::*)(int, ...) const&>();
    test_make_safe<void (Class::*)(int, ...) const&&>();
    test_make_safe<void (Class::*)(int, ...) noexcept>();
    test_make_safe<void (Class::*)(int, ...)& noexcept>();
    test_make_safe<void (Class::*)(int, ...)&& noexcept>();
    test_make_safe<void (Class::*)(int, ...) const noexcept>();
    test_make_safe<void (Class::*)(int, ...) const& noexcept>();
    test_make_safe<void (Class::*)(int, ...) const&& noexcept>();

    test_make_safe<int (Class::*)()>();
    test_make_safe<int (Class::*)()&>();
    test_make_safe<int (Class::*)() &&>();
    test_make_safe<int (Class::*)() const>();
    test_make_safe<int (Class::*)() const&>();
    test_make_safe<int (Class::*)() const&&>();
    test_make_safe<int (Class::*)() noexcept>();
    test_make_safe<int (Class::*)()& noexcept>();
    test_make_safe<int (Class::*)()&& noexcept>();
    test_make_safe<int (Class::*)() const noexcept>();
    test_make_safe<int (Class::*)() const& noexcept>();
    test_make_safe<int (Class::*)() const&& noexcept>();

    test_make_safe<int (Class::*)(int)>();
    test_make_safe<int (Class::*)(int)&>();
    test_make_safe<int (Class::*)(int) &&>();
    test_make_safe<int (Class::*)(int) const>();
    test_make_safe<int (Class::*)(int) const&>();
    test_make_safe<int (Class::*)(int) const&&>();
    test_make_safe<int (Class::*)(int) noexcept>();
    test_make_safe<int (Class::*)(int)& noexcept>();
    test_make_safe<int (Class::*)(int)&& noexcept>();
    test_make_safe<int (Class::*)(int) const noexcept>();
    test_make_safe<int (Class::*)(int) const& noexcept>();
    test_make_safe<int (Class::*)(int) const&& noexcept>();

    test_make_safe<int (Class::*)(...)>();
    test_make_safe<int (Class::*)(...)&>();
    test_make_safe<int (Class::*)(...) &&>();
    test_make_safe<int (Class::*)(...) const>();
    test_make_safe<int (Class::*)(...) const&>();
    test_make_safe<int (Class::*)(...) const&&>();
    test_make_safe<int (Class::*)(...) noexcept>();
    test_make_safe<int (Class::*)(...)& noexcept>();
    test_make_safe<int (Class::*)(...)&& noexcept>();
    test_make_safe<int (Class::*)(...) const noexcept>();
    test_make_safe<int (Class::*)(...) const& noexcept>();
    test_make_safe<int (Class::*)(...) const&& noexcept>();

    test_make_safe<int (Class::*)(int, ...)>();
    test_make_safe<int (Class::*)(int, ...)&>();
    test_make_safe<int (Class::*)(int, ...) &&>();
    test_make_safe<int (Class::*)(int, ...) const>();
    test_make_safe<int (Class::*)(int, ...) const&>();
    test_make_safe<int (Class::*)(int, ...) const&&>();
    test_make_safe<int (Class::*)(int, ...) noexcept>();
    test_make_safe<int (Class::*)(int, ...)& noexcept>();
    test_make_safe<int (Class::*)(int, ...)&& noexcept>();
    test_make_safe<int (Class::*)(int, ...) const noexcept>();
    test_make_safe<int (Class::*)(int, ...) const& noexcept>();
    test_make_safe<int (Class::*)(int, ...) const&& noexcept>();
}
