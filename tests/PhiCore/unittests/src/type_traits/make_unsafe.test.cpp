#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/make_unsafe.hpp>
#include <vector>

template <typename InT, typename OutT = InT>
void test_make_unsafe()
{
    CHECK_SAME_TYPE(typename phi::make_unsafe<InT>::type, OutT);
    CHECK_SAME_TYPE(typename phi::make_unsafe<const InT>::type, const OutT);
    CHECK_SAME_TYPE(typename phi::make_unsafe<volatile InT>::type, volatile OutT);
    CHECK_SAME_TYPE(typename phi::make_unsafe<const volatile InT>::type, const volatile OutT);

    CHECK_SAME_TYPE(typename phi::make_unsafe_t<InT>, OutT);
    CHECK_SAME_TYPE(typename phi::make_unsafe_t<const InT>, const OutT);
    CHECK_SAME_TYPE(typename phi::make_unsafe_t<volatile InT>, volatile OutT);
    CHECK_SAME_TYPE(typename phi::make_unsafe_t<const volatile InT>, const volatile OutT);
}

TEST_CASE("make_unsafe")
{
    test_make_unsafe<void>();
    test_make_unsafe<phi::nullptr_t>();
    test_make_unsafe<bool>();
    test_make_unsafe<char>();
    test_make_unsafe<signed char>();
    test_make_unsafe<unsigned char>();
    test_make_unsafe<short>();
    test_make_unsafe<unsigned short>();
    test_make_unsafe<int>();
    test_make_unsafe<unsigned int>();
    test_make_unsafe<long>();
    test_make_unsafe<unsigned long>();
    test_make_unsafe<long long>();
    test_make_unsafe<unsigned long long>();
    test_make_unsafe<float>();
    test_make_unsafe<double>();
    test_make_unsafe<long double>();
    test_make_unsafe<char8_t>();
    test_make_unsafe<char16_t>();
    test_make_unsafe<char32_t>();
    test_make_unsafe<wchar_t>();

    test_make_unsafe<phi::boolean, bool>();
    test_make_unsafe<phi::integer<signed char>, signed char>();
    test_make_unsafe<phi::integer<unsigned char>, unsigned char>();
    test_make_unsafe<phi::integer<short>, short>();
    test_make_unsafe<phi::integer<unsigned short>, unsigned short>();
    test_make_unsafe<phi::integer<int>, int>();
    test_make_unsafe<phi::integer<unsigned int>, unsigned int>();
    test_make_unsafe<phi::integer<long>, long>();
    test_make_unsafe<phi::integer<unsigned long>, unsigned long>();
    test_make_unsafe<phi::integer<long long>, long long>();
    test_make_unsafe<phi::integer<unsigned long long>, unsigned long long>();
    test_make_unsafe<phi::floating_point<float>, float>();
    test_make_unsafe<phi::floating_point<double>, double>();
    test_make_unsafe<phi::floating_point<long double>, long double>();

    test_make_unsafe<std::vector<int>>();
    test_make_unsafe<phi::scope_ptr<int>>();

    test_make_unsafe<int&>();
    test_make_unsafe<const int&>();
    test_make_unsafe<volatile int&>();
    test_make_unsafe<const volatile int&>();
    test_make_unsafe<int&&>();
    test_make_unsafe<const int&&>();
    test_make_unsafe<volatile int&&>();
    test_make_unsafe<const volatile int&&>();
    test_make_unsafe<int*>();
    test_make_unsafe<const int*>();
    test_make_unsafe<volatile int*>();
    test_make_unsafe<const volatile int*>();
    test_make_unsafe<int**>();
    test_make_unsafe<const int**>();
    test_make_unsafe<volatile int**>();
    test_make_unsafe<const volatile int**>();
    test_make_unsafe<int*&>();
    test_make_unsafe<const int*&>();
    test_make_unsafe<volatile int*&>();
    test_make_unsafe<const volatile int*&>();
    test_make_unsafe<int*&&>();
    test_make_unsafe<const int*&&>();
    test_make_unsafe<volatile int*&&>();
    test_make_unsafe<const volatile int*&&>();
    test_make_unsafe<void*>();
    test_make_unsafe<char[3]>();
    test_make_unsafe<char[]>();
    test_make_unsafe<char* [3]>();
    test_make_unsafe<char*[]>();
    test_make_unsafe<int(*)[3]>();
    test_make_unsafe<int(*)[]>();
    test_make_unsafe<int(&)[3]>();
    test_make_unsafe<int(&)[]>();
    test_make_unsafe<int(&&)[3]>();
    test_make_unsafe<int(&&)[]>();
    test_make_unsafe<char[3][2]>();
    test_make_unsafe<char[][2]>();
    test_make_unsafe<char* [3][2]>();
    test_make_unsafe<char*[][2]>();
    test_make_unsafe<int(*)[3][2]>();
    test_make_unsafe<int(*)[][2]>();
    test_make_unsafe<int(&)[3][2]>();
    test_make_unsafe<int(&)[][2]>();
    test_make_unsafe<int(&&)[3][2]>();
    test_make_unsafe<int(&&)[][2]>();
    test_make_unsafe<Class>();
    test_make_unsafe<Class[]>();
    test_make_unsafe<Class[2]>();
    test_make_unsafe<Template<void>>();
    test_make_unsafe<Template<int>>();
    test_make_unsafe<Template<Class>>();
    test_make_unsafe<Template<IncompleteType>>();
    test_make_unsafe<VariadicTemplate<>>();
    test_make_unsafe<VariadicTemplate<void>>();
    test_make_unsafe<VariadicTemplate<int>>();
    test_make_unsafe<VariadicTemplate<Class>>();
    test_make_unsafe<VariadicTemplate<IncompleteType>>();
    test_make_unsafe<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_make_unsafe<PublicDerivedFromTemplate<Base>>();
    test_make_unsafe<PublicDerivedFromTemplate<Derived>>();
    test_make_unsafe<PublicDerivedFromTemplate<Class>>();
    test_make_unsafe<PrivateDerivedFromTemplate<Base>>();
    test_make_unsafe<PrivateDerivedFromTemplate<Derived>>();
    test_make_unsafe<PrivateDerivedFromTemplate<Class>>();
    test_make_unsafe<ProtectedDerivedFromTemplate<Base>>();
    test_make_unsafe<ProtectedDerivedFromTemplate<Derived>>();
    test_make_unsafe<ProtectedDerivedFromTemplate<Class>>();
    test_make_unsafe<Union>();
    test_make_unsafe<NonEmptyUnion>();
    test_make_unsafe<Empty>();
    test_make_unsafe<NotEmpty>();
    test_make_unsafe<BitZero>();
    test_make_unsafe<BitOne>();
    test_make_unsafe<Base>();
    test_make_unsafe<Derived>();
    test_make_unsafe<Abstract>();
    test_make_unsafe<PublicAbstract>();
    test_make_unsafe<PrivateAbstract>();
    test_make_unsafe<ProtectedAbstract>();
    test_make_unsafe<AbstractTemplate<int>>();
    test_make_unsafe<AbstractTemplate<double>>();
    test_make_unsafe<AbstractTemplate<Class>>();
    test_make_unsafe<AbstractTemplate<IncompleteType>>();
    test_make_unsafe<Final>();
    test_make_unsafe<PublicDestructor>();
    test_make_unsafe<ProtectedDestructor>();
    test_make_unsafe<PrivateDestructor>();
    test_make_unsafe<VirtualPublicDestructor>();
    test_make_unsafe<VirtualProtectedDestructor>();
    test_make_unsafe<VirtualPrivateDestructor>();
    test_make_unsafe<PurePublicDestructor>();
    test_make_unsafe<PureProtectedDestructor>();
    test_make_unsafe<PurePrivateDestructor>();
    test_make_unsafe<DeletedPublicDestructor>();
    test_make_unsafe<DeletedProtectedDestructor>();
    test_make_unsafe<DeletedPrivateDestructor>();
    test_make_unsafe<DeletedVirtualPublicDestructor>();
    test_make_unsafe<DeletedVirtualProtectedDestructor>();
    test_make_unsafe<DeletedVirtualPrivateDestructor>();
    test_make_unsafe<Enum>();
    test_make_unsafe<EnumSigned>();
    test_make_unsafe<EnumUnsigned>();
    test_make_unsafe<EnumClass>();
    test_make_unsafe<EnumStruct>();
    test_make_unsafe<Function>();
    test_make_unsafe<FunctionPtr>();
    test_make_unsafe<MemberObjectPtr>();
    test_make_unsafe<MemberFunctionPtr>();
    test_make_unsafe<IncompleteType>();
    test_make_unsafe<IncompleteTemplate<void>>();
    test_make_unsafe<IncompleteTemplate<int>>();
    test_make_unsafe<IncompleteTemplate<Class>>();
    test_make_unsafe<IncompleteTemplate<IncompleteType>>();
    test_make_unsafe<IncompleteVariadicTemplate<>>();
    test_make_unsafe<IncompleteVariadicTemplate<void>>();
    test_make_unsafe<IncompleteVariadicTemplate<int>>();
    test_make_unsafe<IncompleteVariadicTemplate<Class>>();
    test_make_unsafe<IncompleteVariadicTemplate<IncompleteType>>();
    test_make_unsafe<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_make_unsafe<int Class::*>();
    test_make_unsafe<float Class::*>();
    test_make_unsafe<void * Class::*>();
    test_make_unsafe<int * Class::*>();
    test_make_unsafe<int Class::*&>();
    test_make_unsafe<float Class::*&>();
    test_make_unsafe<void * Class::*&>();
    test_make_unsafe<int * Class::*&>();
    test_make_unsafe<int Class::*&&>();
    test_make_unsafe<float Class::*&&>();
    test_make_unsafe<void * Class::*&&>();
    test_make_unsafe<int * Class::*&&>();
    test_make_unsafe<int Class::*const>();
    test_make_unsafe<float Class::*const>();
    test_make_unsafe<void * Class::*const>();
    test_make_unsafe<int Class::*const&>();
    test_make_unsafe<float Class::*const&>();
    test_make_unsafe<void * Class::*const&>();
    test_make_unsafe<int Class::*const&&>();
    test_make_unsafe<float Class::*const&&>();
    test_make_unsafe<void * Class::*const&&>();
    test_make_unsafe<int Class::*volatile>();
    test_make_unsafe<float Class::*volatile>();
    test_make_unsafe<void * Class::*volatile>();
    test_make_unsafe<int Class::*volatile&>();
    test_make_unsafe<float Class::*volatile&>();
    test_make_unsafe<void * Class::*volatile&>();
    test_make_unsafe<int Class::*volatile&&>();
    test_make_unsafe<float Class::*volatile&&>();
    test_make_unsafe<void * Class::*volatile&&>();
    test_make_unsafe<int Class::*const volatile>();
    test_make_unsafe<float Class::*const volatile>();
    test_make_unsafe<void * Class::*const volatile>();
    test_make_unsafe<int Class::*const volatile&>();
    test_make_unsafe<float Class::*const volatile&>();
    test_make_unsafe<void * Class::*const volatile&>();
    test_make_unsafe<int Class::*const volatile&&>();
    test_make_unsafe<float Class::*const volatile&&>();
    test_make_unsafe<void * Class::*const volatile&&>();
    test_make_unsafe<NonCopyable>();
    test_make_unsafe<NonMoveable>();
    test_make_unsafe<NonConstructible>();
    test_make_unsafe<Tracked>();
    test_make_unsafe<TrapConstructible>();
    test_make_unsafe<TrapImplicitConversion>();
    test_make_unsafe<TrapComma>();
    test_make_unsafe<TrapCall>();
    test_make_unsafe<TrapSelfAssign>();
    test_make_unsafe<TrapDeref>();
    test_make_unsafe<TrapArraySubscript>();

    test_make_unsafe<void()>();
    test_make_unsafe<void()&>();
    test_make_unsafe<void() &&>();
    test_make_unsafe<void() const>();
    test_make_unsafe<void() const&>();
    test_make_unsafe<void() const&&>();
    test_make_unsafe<void() volatile>();
    test_make_unsafe<void() volatile&>();
    test_make_unsafe<void() volatile&&>();
    test_make_unsafe<void() const volatile>();
    test_make_unsafe<void() const volatile&>();
    test_make_unsafe<void() const volatile&&>();
    test_make_unsafe<void() noexcept>();
    test_make_unsafe<void()& noexcept>();
    test_make_unsafe<void()&& noexcept>();
    test_make_unsafe<void() const noexcept>();
    test_make_unsafe<void() const& noexcept>();
    test_make_unsafe<void() const&& noexcept>();
    test_make_unsafe<void() volatile noexcept>();
    test_make_unsafe<void() volatile& noexcept>();
    test_make_unsafe<void() volatile&& noexcept>();
    test_make_unsafe<void() const volatile noexcept>();
    test_make_unsafe<void() const volatile& noexcept>();
    test_make_unsafe<void() const volatile&& noexcept>();

    test_make_unsafe<void(int)>();
    test_make_unsafe<void(int)&>();
    test_make_unsafe<void(int) &&>();
    test_make_unsafe<void(int) const>();
    test_make_unsafe<void(int) const&>();
    test_make_unsafe<void(int) const&&>();
    test_make_unsafe<void(int) volatile>();
    test_make_unsafe<void(int) volatile&>();
    test_make_unsafe<void(int) volatile&&>();
    test_make_unsafe<void(int) const volatile>();
    test_make_unsafe<void(int) const volatile&>();
    test_make_unsafe<void(int) const volatile&&>();
    test_make_unsafe<void(int) noexcept>();
    test_make_unsafe<void(int)& noexcept>();
    test_make_unsafe<void(int)&& noexcept>();
    test_make_unsafe<void(int) const noexcept>();
    test_make_unsafe<void(int) const& noexcept>();
    test_make_unsafe<void(int) const&& noexcept>();
    test_make_unsafe<void(int) volatile noexcept>();
    test_make_unsafe<void(int) volatile& noexcept>();
    test_make_unsafe<void(int) volatile&& noexcept>();
    test_make_unsafe<void(int) const volatile noexcept>();
    test_make_unsafe<void(int) const volatile& noexcept>();
    test_make_unsafe<void(int) const volatile&& noexcept>();

    test_make_unsafe<void(...)>();
    test_make_unsafe<void(...)&>();
    test_make_unsafe<void(...) &&>();
    test_make_unsafe<void(...) const>();
    test_make_unsafe<void(...) const&>();
    test_make_unsafe<void(...) const&&>();
    test_make_unsafe<void(...) volatile>();
    test_make_unsafe<void(...) volatile&>();
    test_make_unsafe<void(...) volatile&&>();
    test_make_unsafe<void(...) const volatile>();
    test_make_unsafe<void(...) const volatile&>();
    test_make_unsafe<void(...) const volatile&&>();
    test_make_unsafe<void(...) noexcept>();
    test_make_unsafe<void(...)& noexcept>();
    test_make_unsafe<void(...)&& noexcept>();
    test_make_unsafe<void(...) const noexcept>();
    test_make_unsafe<void(...) const& noexcept>();
    test_make_unsafe<void(...) const&& noexcept>();
    test_make_unsafe<void(...) volatile noexcept>();
    test_make_unsafe<void(...) volatile& noexcept>();
    test_make_unsafe<void(...) volatile&& noexcept>();
    test_make_unsafe<void(...) const volatile noexcept>();
    test_make_unsafe<void(...) const volatile& noexcept>();
    test_make_unsafe<void(...) const volatile&& noexcept>();

    test_make_unsafe<void(int, ...)>();
    test_make_unsafe<void(int, ...)&>();
    test_make_unsafe<void(int, ...) &&>();
    test_make_unsafe<void(int, ...) const>();
    test_make_unsafe<void(int, ...) const&>();
    test_make_unsafe<void(int, ...) const&&>();
    test_make_unsafe<void(int, ...) volatile>();
    test_make_unsafe<void(int, ...) volatile&>();
    test_make_unsafe<void(int, ...) volatile&&>();
    test_make_unsafe<void(int, ...) const volatile>();
    test_make_unsafe<void(int, ...) const volatile&>();
    test_make_unsafe<void(int, ...) const volatile&&>();
    test_make_unsafe<void(int, ...) noexcept>();
    test_make_unsafe<void(int, ...)& noexcept>();
    test_make_unsafe<void(int, ...)&& noexcept>();
    test_make_unsafe<void(int, ...) const noexcept>();
    test_make_unsafe<void(int, ...) const& noexcept>();
    test_make_unsafe<void(int, ...) const&& noexcept>();
    test_make_unsafe<void(int, ...) volatile noexcept>();
    test_make_unsafe<void(int, ...) volatile& noexcept>();
    test_make_unsafe<void(int, ...) volatile&& noexcept>();
    test_make_unsafe<void(int, ...) const volatile noexcept>();
    test_make_unsafe<void(int, ...) const volatile& noexcept>();
    test_make_unsafe<void(int, ...) const volatile&& noexcept>();

    test_make_unsafe<int()>();
    test_make_unsafe<int()&>();
    test_make_unsafe<int() &&>();
    test_make_unsafe<int() const>();
    test_make_unsafe<int() const&>();
    test_make_unsafe<int() const&&>();
    test_make_unsafe<int() volatile>();
    test_make_unsafe<int() volatile&>();
    test_make_unsafe<int() volatile&&>();
    test_make_unsafe<int() const volatile>();
    test_make_unsafe<int() const volatile&>();
    test_make_unsafe<int() const volatile&&>();
    test_make_unsafe<int() noexcept>();
    test_make_unsafe<int()& noexcept>();
    test_make_unsafe<int()&& noexcept>();
    test_make_unsafe<int() const noexcept>();
    test_make_unsafe<int() const& noexcept>();
    test_make_unsafe<int() const&& noexcept>();
    test_make_unsafe<int() volatile noexcept>();
    test_make_unsafe<int() volatile& noexcept>();
    test_make_unsafe<int() volatile&& noexcept>();
    test_make_unsafe<int() const volatile noexcept>();
    test_make_unsafe<int() const volatile& noexcept>();
    test_make_unsafe<int() const volatile&& noexcept>();

    test_make_unsafe<int(int)>();
    test_make_unsafe<int(int)&>();
    test_make_unsafe<int(int) &&>();
    test_make_unsafe<int(int) const>();
    test_make_unsafe<int(int) const&>();
    test_make_unsafe<int(int) const&&>();
    test_make_unsafe<int(int) volatile>();
    test_make_unsafe<int(int) volatile&>();
    test_make_unsafe<int(int) volatile&&>();
    test_make_unsafe<int(int) const volatile>();
    test_make_unsafe<int(int) const volatile&>();
    test_make_unsafe<int(int) const volatile&&>();
    test_make_unsafe<int(int) noexcept>();
    test_make_unsafe<int(int)& noexcept>();
    test_make_unsafe<int(int)&& noexcept>();
    test_make_unsafe<int(int) const noexcept>();
    test_make_unsafe<int(int) const& noexcept>();
    test_make_unsafe<int(int) const&& noexcept>();
    test_make_unsafe<int(int) volatile noexcept>();
    test_make_unsafe<int(int) volatile& noexcept>();
    test_make_unsafe<int(int) volatile&& noexcept>();
    test_make_unsafe<int(int) const volatile noexcept>();
    test_make_unsafe<int(int) const volatile& noexcept>();
    test_make_unsafe<int(int) const volatile&& noexcept>();

    test_make_unsafe<int(...)>();
    test_make_unsafe<int(...)&>();
    test_make_unsafe<int(...) &&>();
    test_make_unsafe<int(...) const>();
    test_make_unsafe<int(...) const&>();
    test_make_unsafe<int(...) const&&>();
    test_make_unsafe<int(...) volatile>();
    test_make_unsafe<int(...) volatile&>();
    test_make_unsafe<int(...) volatile&&>();
    test_make_unsafe<int(...) const volatile>();
    test_make_unsafe<int(...) const volatile&>();
    test_make_unsafe<int(...) const volatile&&>();
    test_make_unsafe<int(...) noexcept>();
    test_make_unsafe<int(...)& noexcept>();
    test_make_unsafe<int(...)&& noexcept>();
    test_make_unsafe<int(...) const noexcept>();
    test_make_unsafe<int(...) const& noexcept>();
    test_make_unsafe<int(...) const&& noexcept>();
    test_make_unsafe<int(...) volatile noexcept>();
    test_make_unsafe<int(...) volatile& noexcept>();
    test_make_unsafe<int(...) volatile&& noexcept>();
    test_make_unsafe<int(...) const volatile noexcept>();
    test_make_unsafe<int(...) const volatile& noexcept>();
    test_make_unsafe<int(...) const volatile&& noexcept>();

    test_make_unsafe<int(int, ...)>();
    test_make_unsafe<int(int, ...)&>();
    test_make_unsafe<int(int, ...) &&>();
    test_make_unsafe<int(int, ...) const>();
    test_make_unsafe<int(int, ...) const&>();
    test_make_unsafe<int(int, ...) const&&>();
    test_make_unsafe<int(int, ...) volatile>();
    test_make_unsafe<int(int, ...) volatile&>();
    test_make_unsafe<int(int, ...) volatile&&>();
    test_make_unsafe<int(int, ...) const volatile>();
    test_make_unsafe<int(int, ...) const volatile&>();
    test_make_unsafe<int(int, ...) const volatile&&>();
    test_make_unsafe<int(int, ...) noexcept>();
    test_make_unsafe<int(int, ...)& noexcept>();
    test_make_unsafe<int(int, ...)&& noexcept>();
    test_make_unsafe<int(int, ...) const noexcept>();
    test_make_unsafe<int(int, ...) const& noexcept>();
    test_make_unsafe<int(int, ...) const&& noexcept>();
    test_make_unsafe<int(int, ...) volatile noexcept>();
    test_make_unsafe<int(int, ...) volatile& noexcept>();
    test_make_unsafe<int(int, ...) volatile&& noexcept>();
    test_make_unsafe<int(int, ...) const volatile noexcept>();
    test_make_unsafe<int(int, ...) const volatile& noexcept>();
    test_make_unsafe<int(int, ...) const volatile&& noexcept>();

    test_make_unsafe<void (*)()>();
    test_make_unsafe<void (*)() noexcept>();

    test_make_unsafe<void (*)(int)>();
    test_make_unsafe<void (*)(int) noexcept>();

    test_make_unsafe<void (*)(...)>();
    test_make_unsafe<void (*)(...) noexcept>();

    test_make_unsafe<void (*)(int, ...)>();
    test_make_unsafe<void (*)(int, ...) noexcept>();

    test_make_unsafe<int (*)()>();
    test_make_unsafe<int (*)() noexcept>();

    test_make_unsafe<int (*)(int)>();
    test_make_unsafe<int (*)(int) noexcept>();

    test_make_unsafe<int (*)(...)>();
    test_make_unsafe<int (*)(...) noexcept>();

    test_make_unsafe<int (*)(int, ...)>();
    test_make_unsafe<int (*)(int, ...) noexcept>();

    test_make_unsafe<void (&)()>();
    test_make_unsafe<void (&)() noexcept>();

    test_make_unsafe<void (&)(int)>();
    test_make_unsafe<void (&)(int) noexcept>();

    test_make_unsafe<void (&)(...)>();
    test_make_unsafe<void (&)(...) noexcept>();

    test_make_unsafe<void (&)(int, ...)>();
    test_make_unsafe<void (&)(int, ...) noexcept>();

    test_make_unsafe<int (&)()>();
    test_make_unsafe<int (&)() noexcept>();

    test_make_unsafe<int (&)(int)>();
    test_make_unsafe<int (&)(int) noexcept>();

    test_make_unsafe<int (&)(...)>();
    test_make_unsafe<int (&)(...) noexcept>();

    test_make_unsafe<int (&)(int, ...)>();
    test_make_unsafe<int (&)(int, ...) noexcept>();

    test_make_unsafe<void(&&)()>();
    test_make_unsafe<void(&&)() noexcept>();

    test_make_unsafe<void(&&)(int)>();
    test_make_unsafe<void(&&)(int) noexcept>();

    test_make_unsafe<void(&&)(...)>();
    test_make_unsafe<void(&&)(...) noexcept>();

    test_make_unsafe<void(&&)(int, ...)>();
    test_make_unsafe<void(&&)(int, ...) noexcept>();

    test_make_unsafe<int(&&)()>();
    test_make_unsafe<int(&&)() noexcept>();

    test_make_unsafe<int(&&)(int)>();
    test_make_unsafe<int(&&)(int) noexcept>();

    test_make_unsafe<int(&&)(...)>();
    test_make_unsafe<int(&&)(...) noexcept>();

    test_make_unsafe<int(&&)(int, ...)>();
    test_make_unsafe<int(&&)(int, ...) noexcept>();

    test_make_unsafe<void (Class::*)()>();
    test_make_unsafe<void (Class::*)()&>();
    test_make_unsafe<void (Class::*)() &&>();
    test_make_unsafe<void (Class::*)() const>();
    test_make_unsafe<void (Class::*)() const&>();
    test_make_unsafe<void (Class::*)() const&&>();
    test_make_unsafe<void (Class::*)() noexcept>();
    test_make_unsafe<void (Class::*)()& noexcept>();
    test_make_unsafe<void (Class::*)()&& noexcept>();
    test_make_unsafe<void (Class::*)() const noexcept>();
    test_make_unsafe<void (Class::*)() const& noexcept>();
    test_make_unsafe<void (Class::*)() const&& noexcept>();

    test_make_unsafe<void (Class::*)(int)>();
    test_make_unsafe<void (Class::*)(int)&>();
    test_make_unsafe<void (Class::*)(int) &&>();
    test_make_unsafe<void (Class::*)(int) const>();
    test_make_unsafe<void (Class::*)(int) const&>();
    test_make_unsafe<void (Class::*)(int) const&&>();
    test_make_unsafe<void (Class::*)(int) noexcept>();
    test_make_unsafe<void (Class::*)(int)& noexcept>();
    test_make_unsafe<void (Class::*)(int)&& noexcept>();
    test_make_unsafe<void (Class::*)(int) const noexcept>();
    test_make_unsafe<void (Class::*)(int) const& noexcept>();
    test_make_unsafe<void (Class::*)(int) const&& noexcept>();

    test_make_unsafe<void (Class::*)(...)>();
    test_make_unsafe<void (Class::*)(...)&>();
    test_make_unsafe<void (Class::*)(...) &&>();
    test_make_unsafe<void (Class::*)(...) const>();
    test_make_unsafe<void (Class::*)(...) const&>();
    test_make_unsafe<void (Class::*)(...) const&&>();
    test_make_unsafe<void (Class::*)(...) noexcept>();
    test_make_unsafe<void (Class::*)(...)& noexcept>();
    test_make_unsafe<void (Class::*)(...)&& noexcept>();
    test_make_unsafe<void (Class::*)(...) const noexcept>();
    test_make_unsafe<void (Class::*)(...) const& noexcept>();
    test_make_unsafe<void (Class::*)(...) const&& noexcept>();

    test_make_unsafe<void (Class::*)(int, ...)>();
    test_make_unsafe<void (Class::*)(int, ...)&>();
    test_make_unsafe<void (Class::*)(int, ...) &&>();
    test_make_unsafe<void (Class::*)(int, ...) const>();
    test_make_unsafe<void (Class::*)(int, ...) const&>();
    test_make_unsafe<void (Class::*)(int, ...) const&&>();
    test_make_unsafe<void (Class::*)(int, ...) noexcept>();
    test_make_unsafe<void (Class::*)(int, ...)& noexcept>();
    test_make_unsafe<void (Class::*)(int, ...)&& noexcept>();
    test_make_unsafe<void (Class::*)(int, ...) const noexcept>();
    test_make_unsafe<void (Class::*)(int, ...) const& noexcept>();
    test_make_unsafe<void (Class::*)(int, ...) const&& noexcept>();

    test_make_unsafe<int (Class::*)()>();
    test_make_unsafe<int (Class::*)()&>();
    test_make_unsafe<int (Class::*)() &&>();
    test_make_unsafe<int (Class::*)() const>();
    test_make_unsafe<int (Class::*)() const&>();
    test_make_unsafe<int (Class::*)() const&&>();
    test_make_unsafe<int (Class::*)() noexcept>();
    test_make_unsafe<int (Class::*)()& noexcept>();
    test_make_unsafe<int (Class::*)()&& noexcept>();
    test_make_unsafe<int (Class::*)() const noexcept>();
    test_make_unsafe<int (Class::*)() const& noexcept>();
    test_make_unsafe<int (Class::*)() const&& noexcept>();

    test_make_unsafe<int (Class::*)(int)>();
    test_make_unsafe<int (Class::*)(int)&>();
    test_make_unsafe<int (Class::*)(int) &&>();
    test_make_unsafe<int (Class::*)(int) const>();
    test_make_unsafe<int (Class::*)(int) const&>();
    test_make_unsafe<int (Class::*)(int) const&&>();
    test_make_unsafe<int (Class::*)(int) noexcept>();
    test_make_unsafe<int (Class::*)(int)& noexcept>();
    test_make_unsafe<int (Class::*)(int)&& noexcept>();
    test_make_unsafe<int (Class::*)(int) const noexcept>();
    test_make_unsafe<int (Class::*)(int) const& noexcept>();
    test_make_unsafe<int (Class::*)(int) const&& noexcept>();

    test_make_unsafe<int (Class::*)(...)>();
    test_make_unsafe<int (Class::*)(...)&>();
    test_make_unsafe<int (Class::*)(...) &&>();
    test_make_unsafe<int (Class::*)(...) const>();
    test_make_unsafe<int (Class::*)(...) const&>();
    test_make_unsafe<int (Class::*)(...) const&&>();
    test_make_unsafe<int (Class::*)(...) noexcept>();
    test_make_unsafe<int (Class::*)(...)& noexcept>();
    test_make_unsafe<int (Class::*)(...)&& noexcept>();
    test_make_unsafe<int (Class::*)(...) const noexcept>();
    test_make_unsafe<int (Class::*)(...) const& noexcept>();
    test_make_unsafe<int (Class::*)(...) const&& noexcept>();

    test_make_unsafe<int (Class::*)(int, ...)>();
    test_make_unsafe<int (Class::*)(int, ...)&>();
    test_make_unsafe<int (Class::*)(int, ...) &&>();
    test_make_unsafe<int (Class::*)(int, ...) const>();
    test_make_unsafe<int (Class::*)(int, ...) const&>();
    test_make_unsafe<int (Class::*)(int, ...) const&&>();
    test_make_unsafe<int (Class::*)(int, ...) noexcept>();
    test_make_unsafe<int (Class::*)(int, ...)& noexcept>();
    test_make_unsafe<int (Class::*)(int, ...)&& noexcept>();
    test_make_unsafe<int (Class::*)(int, ...) const noexcept>();
    test_make_unsafe<int (Class::*)(int, ...) const& noexcept>();
    test_make_unsafe<int (Class::*)(int, ...) const&& noexcept>();
}
