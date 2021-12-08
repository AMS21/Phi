#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/add_const.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_add_const()
{
    CHECK_SAME_TYPE(typename phi::add_const<T>::type, const T);
    CHECK_SAME_TYPE(typename phi::add_const<const T>::type, const T);
    CHECK_SAME_TYPE(typename phi::add_const<volatile T>::type, const volatile T);
    CHECK_SAME_TYPE(typename phi::add_const<const volatile T>::type, const volatile T);

    CHECK_SAME_TYPE(phi::add_const_t<T>, const T);
    CHECK_SAME_TYPE(phi::add_const_t<const T>, const T);
    CHECK_SAME_TYPE(phi::add_const_t<volatile T>, const volatile T);
    CHECK_SAME_TYPE(phi::add_const_t<const volatile T>, const volatile T);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_const<T>::type, typename std::add_const<T>::type);
    CHECK_SAME_TYPE(typename phi::add_const<const T>::type, typename std::add_const<const T>::type);
    CHECK_SAME_TYPE(typename phi::add_const<volatile T>::type,
                    typename std::add_const<volatile T>::type);
    CHECK_SAME_TYPE(typename phi::add_const<const volatile T>::type,
                    typename std::add_const<const volatile T>::type);
}

TEST_CASE("add_const")
{
    test_add_const<void>();
    test_add_const<phi::nullptr_t>();
    test_add_const<bool>();
    test_add_const<char>();
    test_add_const<signed char>();
    test_add_const<unsigned char>();
    test_add_const<short>();
    test_add_const<unsigned short>();
    test_add_const<int>();
    test_add_const<unsigned int>();
    test_add_const<long>();
    test_add_const<unsigned long>();
    test_add_const<long long>();
    test_add_const<unsigned long long>();
    test_add_const<float>();
    test_add_const<double>();
    test_add_const<long double>();
    test_add_const<char8_t>();
    test_add_const<char16_t>();
    test_add_const<char32_t>();
    test_add_const<wchar_t>();

    test_add_const<phi::boolean>();
    test_add_const<phi::integer<signed char>>();
    test_add_const<phi::integer<unsigned char>>();
    test_add_const<phi::integer<short>>();
    test_add_const<phi::integer<unsigned short>>();
    test_add_const<phi::integer<int>>();
    test_add_const<phi::integer<unsigned int>>();
    test_add_const<phi::integer<long>>();
    test_add_const<phi::integer<unsigned long>>();
    test_add_const<phi::integer<long long>>();
    test_add_const<phi::integer<unsigned long long>>();
    test_add_const<phi::floating_point<float>>();
    test_add_const<phi::floating_point<double>>();
    test_add_const<phi::floating_point<long double>>();

    test_add_const<std::vector<int>>();
    test_add_const<phi::scope_ptr<int>>();

    test_add_const<int&>();
    test_add_const<const int&>();
    test_add_const<volatile int&>();
    test_add_const<const volatile int&>();
    test_add_const<int&&>();
    test_add_const<const int&&>();
    test_add_const<volatile int&&>();
    test_add_const<const volatile int&&>();
    test_add_const<int*>();
    test_add_const<const int*>();
    test_add_const<volatile int*>();
    test_add_const<const volatile int*>();
    test_add_const<int**>();
    test_add_const<const int**>();
    test_add_const<volatile int**>();
    test_add_const<const volatile int**>();
    test_add_const<int*&>();
    test_add_const<const int*&>();
    test_add_const<volatile int*&>();
    test_add_const<const volatile int*&>();
    test_add_const<int*&&>();
    test_add_const<const int*&&>();
    test_add_const<volatile int*&&>();
    test_add_const<const volatile int*&&>();
    test_add_const<void*>();
    test_add_const<char[3]>();
    test_add_const<char[]>();
    test_add_const<char* [3]>();
    test_add_const<char*[]>();
    test_add_const<int(*)[3]>();
    test_add_const<int(*)[]>();
    test_add_const<int(&)[3]>();
    test_add_const<int(&)[]>();
    test_add_const<int(&&)[3]>();
    test_add_const<int(&&)[]>();
    test_add_const<char[3][2]>();
    test_add_const<char[][2]>();
    test_add_const<char* [3][2]>();
    test_add_const<char*[][2]>();
    test_add_const<int(*)[3][2]>();
    test_add_const<int(*)[][2]>();
    test_add_const<int(&)[3][2]>();
    test_add_const<int(&)[][2]>();
    test_add_const<int(&&)[3][2]>();
    test_add_const<int(&&)[][2]>();
    test_add_const<Class>();
    test_add_const<Class[]>();
    test_add_const<Class[2]>();
    test_add_const<Template<void>>();
    test_add_const<Template<int>>();
    test_add_const<Template<Class>>();
    test_add_const<Template<incomplete_type>>();
    test_add_const<VariadicTemplate<>>();
    test_add_const<VariadicTemplate<void>>();
    test_add_const<VariadicTemplate<int>>();
    test_add_const<VariadicTemplate<Class>>();
    test_add_const<VariadicTemplate<incomplete_type>>();
    test_add_const<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_add_const<PublicDerviedFromTemplate<Base>>();
    test_add_const<PublicDerviedFromTemplate<Derived>>();
    test_add_const<PublicDerviedFromTemplate<Class>>();
    test_add_const<PrivateDerviedFromTemplate<Base>>();
    test_add_const<PrivateDerviedFromTemplate<Derived>>();
    test_add_const<PrivateDerviedFromTemplate<Class>>();
    test_add_const<ProtectedDerviedFromTemplate<Base>>();
    test_add_const<ProtectedDerviedFromTemplate<Derived>>();
    test_add_const<ProtectedDerviedFromTemplate<Class>>();
    test_add_const<Union>();
    test_add_const<NonEmptyUnion>();
    test_add_const<Empty>();
    test_add_const<NotEmpty>();
    test_add_const<bit_zero>();
    test_add_const<bit_one>();
    test_add_const<Base>();
    test_add_const<Derived>();
    test_add_const<Abstract>();
    test_add_const<PublicAbstract>();
    test_add_const<PrivateAbstract>();
    test_add_const<ProtectedAbstract>();
    test_add_const<AbstractTemplate<int>>();
    test_add_const<AbstractTemplate<double>>();
    test_add_const<AbstractTemplate<Class>>();
    test_add_const<AbstractTemplate<incomplete_type>>();
    test_add_const<Final>();
    test_add_const<PublicDestructor>();
    test_add_const<ProtectedDestructor>();
    test_add_const<PrivateDestructor>();
    test_add_const<VirtualPublicDestructor>();
    test_add_const<VirtualProtectedDestructor>();
    test_add_const<VirtualPrivateDestructor>();
    test_add_const<PurePublicDestructor>();
    test_add_const<PureProtectedDestructor>();
    test_add_const<PurePrivateDestructor>();
    test_add_const<DeletedPublicDestructor>();
    test_add_const<DeletedProtectedDestructor>();
    test_add_const<DeletedPrivateDestructor>();
    test_add_const<DeletedVirtualPublicDestructor>();
    test_add_const<DeletedVirtualProtectedDestructor>();
    test_add_const<DeletedVirtualPrivateDestructor>();
    test_add_const<Final>();
    test_add_const<Enum>();
    test_add_const<EnumSigned>();
    test_add_const<EnumUnsigned>();
    test_add_const<EnumClass>();
    test_add_const<EnumStruct>();
    test_add_const<Function>();
    test_add_const<FunctionPtr>();
    test_add_const<MemberObjectPtr>();
    test_add_const<MemberFunctionPtr>();
    test_add_const<incomplete_type>();
    test_add_const<IncompleteTemplate<void>>();
    test_add_const<IncompleteTemplate<int>>();
    test_add_const<IncompleteTemplate<Class>>();
    test_add_const<IncompleteTemplate<incomplete_type>>();
    test_add_const<IncompleteVariadicTemplate<>>();
    test_add_const<IncompleteVariadicTemplate<void>>();
    test_add_const<IncompleteVariadicTemplate<int>>();
    test_add_const<IncompleteVariadicTemplate<Class>>();
    test_add_const<IncompleteVariadicTemplate<incomplete_type>>();
    test_add_const<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_add_const<int Class::*>();
    test_add_const<float Class::*>();
    test_add_const<void * Class::*>();
    test_add_const<int * Class::*>();
    test_add_const<int Class::*&>();
    test_add_const<float Class::*&>();
    test_add_const<void * Class::*&>();
    test_add_const<int * Class::*&>();
    test_add_const<int Class::*&&>();
    test_add_const<float Class::*&&>();
    test_add_const<void * Class::*&&>();
    test_add_const<int * Class::*&&>();
    test_add_const<int Class::*const>();
    test_add_const<float Class::*const>();
    test_add_const<void * Class::*const>();
    test_add_const<int Class::*const&>();
    test_add_const<float Class::*const&>();
    test_add_const<void * Class::*const&>();
    test_add_const<int Class::*const&&>();
    test_add_const<float Class::*const&&>();
    test_add_const<void * Class::*const&&>();
    test_add_const<int Class::*volatile>();
    test_add_const<float Class::*volatile>();
    test_add_const<void * Class::*volatile>();
    test_add_const<int Class::*volatile&>();
    test_add_const<float Class::*volatile&>();
    test_add_const<void * Class::*volatile&>();
    test_add_const<int Class::*volatile&&>();
    test_add_const<float Class::*volatile&&>();
    test_add_const<void * Class::*volatile&&>();
    test_add_const<int Class::*const volatile>();
    test_add_const<float Class::*const volatile>();
    test_add_const<void * Class::*const volatile>();
    test_add_const<int Class::*const volatile&>();
    test_add_const<float Class::*const volatile&>();
    test_add_const<void * Class::*const volatile&>();
    test_add_const<int Class::*const volatile&&>();
    test_add_const<float Class::*const volatile&&>();
    test_add_const<void * Class::*const volatile&&>();
    test_add_const<NonCopyable>();
    test_add_const<NonMoveable>();
    test_add_const<NonConstructible>();
    test_add_const<Tracked>();
    test_add_const<TrapConstructible>();
    test_add_const<TrapImplicitConversion>();
    test_add_const<TrapComma>();
    test_add_const<TrapCall>();
    test_add_const<TrapSelfAssign>();
    test_add_const<TrapDeref>();
    test_add_const<TrapArraySubscript>();

    test_add_const<void()>();
    test_add_const<void()&>();
    test_add_const<void() &&>();
    test_add_const<void() const>();
    test_add_const<void() const&>();
    test_add_const<void() const&&>();
    test_add_const<void() volatile>();
    test_add_const<void() volatile&>();
    test_add_const<void() volatile&&>();
    test_add_const<void() const volatile>();
    test_add_const<void() const volatile&>();
    test_add_const<void() const volatile&&>();
    test_add_const<void() noexcept>();
    test_add_const<void()& noexcept>();
    test_add_const<void()&& noexcept>();
    test_add_const<void() const noexcept>();
    test_add_const<void() const& noexcept>();
    test_add_const<void() const&& noexcept>();
    test_add_const<void() volatile noexcept>();
    test_add_const<void() volatile& noexcept>();
    test_add_const<void() volatile&& noexcept>();
    test_add_const<void() const volatile noexcept>();
    test_add_const<void() const volatile& noexcept>();
    test_add_const<void() const volatile&& noexcept>();

    test_add_const<void(int)>();
    test_add_const<void(int)&>();
    test_add_const<void(int) &&>();
    test_add_const<void(int) const>();
    test_add_const<void(int) const&>();
    test_add_const<void(int) const&&>();
    test_add_const<void(int) volatile>();
    test_add_const<void(int) volatile&>();
    test_add_const<void(int) volatile&&>();
    test_add_const<void(int) const volatile>();
    test_add_const<void(int) const volatile&>();
    test_add_const<void(int) const volatile&&>();
    test_add_const<void(int) noexcept>();
    test_add_const<void(int)& noexcept>();
    test_add_const<void(int)&& noexcept>();
    test_add_const<void(int) const noexcept>();
    test_add_const<void(int) const& noexcept>();
    test_add_const<void(int) const&& noexcept>();
    test_add_const<void(int) volatile noexcept>();
    test_add_const<void(int) volatile& noexcept>();
    test_add_const<void(int) volatile&& noexcept>();
    test_add_const<void(int) const volatile noexcept>();
    test_add_const<void(int) const volatile& noexcept>();
    test_add_const<void(int) const volatile&& noexcept>();

    test_add_const<void(...)>();
    test_add_const<void(...)&>();
    test_add_const<void(...) &&>();
    test_add_const<void(...) const>();
    test_add_const<void(...) const&>();
    test_add_const<void(...) const&&>();
    test_add_const<void(...) volatile>();
    test_add_const<void(...) volatile&>();
    test_add_const<void(...) volatile&&>();
    test_add_const<void(...) const volatile>();
    test_add_const<void(...) const volatile&>();
    test_add_const<void(...) const volatile&&>();
    test_add_const<void(...) noexcept>();
    test_add_const<void(...)& noexcept>();
    test_add_const<void(...)&& noexcept>();
    test_add_const<void(...) const noexcept>();
    test_add_const<void(...) const& noexcept>();
    test_add_const<void(...) const&& noexcept>();
    test_add_const<void(...) volatile noexcept>();
    test_add_const<void(...) volatile& noexcept>();
    test_add_const<void(...) volatile&& noexcept>();
    test_add_const<void(...) const volatile noexcept>();
    test_add_const<void(...) const volatile& noexcept>();
    test_add_const<void(...) const volatile&& noexcept>();

    test_add_const<void(int, ...)>();
    test_add_const<void(int, ...)&>();
    test_add_const<void(int, ...) &&>();
    test_add_const<void(int, ...) const>();
    test_add_const<void(int, ...) const&>();
    test_add_const<void(int, ...) const&&>();
    test_add_const<void(int, ...) volatile>();
    test_add_const<void(int, ...) volatile&>();
    test_add_const<void(int, ...) volatile&&>();
    test_add_const<void(int, ...) const volatile>();
    test_add_const<void(int, ...) const volatile&>();
    test_add_const<void(int, ...) const volatile&&>();
    test_add_const<void(int, ...) noexcept>();
    test_add_const<void(int, ...)& noexcept>();
    test_add_const<void(int, ...)&& noexcept>();
    test_add_const<void(int, ...) const noexcept>();
    test_add_const<void(int, ...) const& noexcept>();
    test_add_const<void(int, ...) const&& noexcept>();
    test_add_const<void(int, ...) volatile noexcept>();
    test_add_const<void(int, ...) volatile& noexcept>();
    test_add_const<void(int, ...) volatile&& noexcept>();
    test_add_const<void(int, ...) const volatile noexcept>();
    test_add_const<void(int, ...) const volatile& noexcept>();
    test_add_const<void(int, ...) const volatile&& noexcept>();

    test_add_const<int()>();
    test_add_const<int()&>();
    test_add_const<int() &&>();
    test_add_const<int() const>();
    test_add_const<int() const&>();
    test_add_const<int() const&&>();
    test_add_const<int() volatile>();
    test_add_const<int() volatile&>();
    test_add_const<int() volatile&&>();
    test_add_const<int() const volatile>();
    test_add_const<int() const volatile&>();
    test_add_const<int() const volatile&&>();
    test_add_const<int() noexcept>();
    test_add_const<int()& noexcept>();
    test_add_const<int()&& noexcept>();
    test_add_const<int() const noexcept>();
    test_add_const<int() const& noexcept>();
    test_add_const<int() const&& noexcept>();
    test_add_const<int() volatile noexcept>();
    test_add_const<int() volatile& noexcept>();
    test_add_const<int() volatile&& noexcept>();
    test_add_const<int() const volatile noexcept>();
    test_add_const<int() const volatile& noexcept>();
    test_add_const<int() const volatile&& noexcept>();

    test_add_const<int(int)>();
    test_add_const<int(int)&>();
    test_add_const<int(int) &&>();
    test_add_const<int(int) const>();
    test_add_const<int(int) const&>();
    test_add_const<int(int) const&&>();
    test_add_const<int(int) volatile>();
    test_add_const<int(int) volatile&>();
    test_add_const<int(int) volatile&&>();
    test_add_const<int(int) const volatile>();
    test_add_const<int(int) const volatile&>();
    test_add_const<int(int) const volatile&&>();
    test_add_const<int(int) noexcept>();
    test_add_const<int(int)& noexcept>();
    test_add_const<int(int)&& noexcept>();
    test_add_const<int(int) const noexcept>();
    test_add_const<int(int) const& noexcept>();
    test_add_const<int(int) const&& noexcept>();
    test_add_const<int(int) volatile noexcept>();
    test_add_const<int(int) volatile& noexcept>();
    test_add_const<int(int) volatile&& noexcept>();
    test_add_const<int(int) const volatile noexcept>();
    test_add_const<int(int) const volatile& noexcept>();
    test_add_const<int(int) const volatile&& noexcept>();

    test_add_const<int(...)>();
    test_add_const<int(...)&>();
    test_add_const<int(...) &&>();
    test_add_const<int(...) const>();
    test_add_const<int(...) const&>();
    test_add_const<int(...) const&&>();
    test_add_const<int(...) volatile>();
    test_add_const<int(...) volatile&>();
    test_add_const<int(...) volatile&&>();
    test_add_const<int(...) const volatile>();
    test_add_const<int(...) const volatile&>();
    test_add_const<int(...) const volatile&&>();
    test_add_const<int(...) noexcept>();
    test_add_const<int(...)& noexcept>();
    test_add_const<int(...)&& noexcept>();
    test_add_const<int(...) const noexcept>();
    test_add_const<int(...) const& noexcept>();
    test_add_const<int(...) const&& noexcept>();
    test_add_const<int(...) volatile noexcept>();
    test_add_const<int(...) volatile& noexcept>();
    test_add_const<int(...) volatile&& noexcept>();
    test_add_const<int(...) const volatile noexcept>();
    test_add_const<int(...) const volatile& noexcept>();
    test_add_const<int(...) const volatile&& noexcept>();

    test_add_const<int(int, ...)>();
    test_add_const<int(int, ...)&>();
    test_add_const<int(int, ...) &&>();
    test_add_const<int(int, ...) const>();
    test_add_const<int(int, ...) const&>();
    test_add_const<int(int, ...) const&&>();
    test_add_const<int(int, ...) volatile>();
    test_add_const<int(int, ...) volatile&>();
    test_add_const<int(int, ...) volatile&&>();
    test_add_const<int(int, ...) const volatile>();
    test_add_const<int(int, ...) const volatile&>();
    test_add_const<int(int, ...) const volatile&&>();
    test_add_const<int(int, ...) noexcept>();
    test_add_const<int(int, ...)& noexcept>();
    test_add_const<int(int, ...)&& noexcept>();
    test_add_const<int(int, ...) const noexcept>();
    test_add_const<int(int, ...) const& noexcept>();
    test_add_const<int(int, ...) const&& noexcept>();
    test_add_const<int(int, ...) volatile noexcept>();
    test_add_const<int(int, ...) volatile& noexcept>();
    test_add_const<int(int, ...) volatile&& noexcept>();
    test_add_const<int(int, ...) const volatile noexcept>();
    test_add_const<int(int, ...) const volatile& noexcept>();
    test_add_const<int(int, ...) const volatile&& noexcept>();

    test_add_const<void (*)()>();
    test_add_const<void (*)() noexcept>();

    test_add_const<void (*)(int)>();
    test_add_const<void (*)(int) noexcept>();

    test_add_const<void (*)(...)>();
    test_add_const<void (*)(...) noexcept>();

    test_add_const<void (*)(int, ...)>();
    test_add_const<void (*)(int, ...) noexcept>();

    test_add_const<int (*)()>();
    test_add_const<int (*)() noexcept>();

    test_add_const<int (*)(int)>();
    test_add_const<int (*)(int) noexcept>();

    test_add_const<int (*)(...)>();
    test_add_const<int (*)(...) noexcept>();

    test_add_const<int (*)(int, ...)>();
    test_add_const<int (*)(int, ...) noexcept>();

    test_add_const<void (&)()>();
    test_add_const<void (&)() noexcept>();

    test_add_const<void (&)(int)>();
    test_add_const<void (&)(int) noexcept>();

    test_add_const<void (&)(...)>();
    test_add_const<void (&)(...) noexcept>();

    test_add_const<void (&)(int, ...)>();
    test_add_const<void (&)(int, ...) noexcept>();

    test_add_const<int (&)()>();
    test_add_const<int (&)() noexcept>();

    test_add_const<int (&)(int)>();
    test_add_const<int (&)(int) noexcept>();

    test_add_const<int (&)(...)>();
    test_add_const<int (&)(...) noexcept>();

    test_add_const<int (&)(int, ...)>();
    test_add_const<int (&)(int, ...) noexcept>();

    test_add_const<void(&&)()>();
    test_add_const<void(&&)() noexcept>();

    test_add_const<void(&&)(int)>();
    test_add_const<void(&&)(int) noexcept>();

    test_add_const<void(&&)(...)>();
    test_add_const<void(&&)(...) noexcept>();

    test_add_const<void(&&)(int, ...)>();
    test_add_const<void(&&)(int, ...) noexcept>();

    test_add_const<int(&&)()>();
    test_add_const<int(&&)() noexcept>();

    test_add_const<int(&&)(int)>();
    test_add_const<int(&&)(int) noexcept>();

    test_add_const<int(&&)(...)>();
    test_add_const<int(&&)(...) noexcept>();

    test_add_const<int(&&)(int, ...)>();
    test_add_const<int(&&)(int, ...) noexcept>();

    test_add_const<void (Class::*)()>();
    test_add_const<void (Class::*)()&>();
    test_add_const<void (Class::*)() &&>();
    test_add_const<void (Class::*)() const>();
    test_add_const<void (Class::*)() const&>();
    test_add_const<void (Class::*)() const&&>();
    test_add_const<void (Class::*)() noexcept>();
    test_add_const<void (Class::*)()& noexcept>();
    test_add_const<void (Class::*)()&& noexcept>();
    test_add_const<void (Class::*)() const noexcept>();
    test_add_const<void (Class::*)() const& noexcept>();
    test_add_const<void (Class::*)() const&& noexcept>();

    test_add_const<void (Class::*)(int)>();
    test_add_const<void (Class::*)(int)&>();
    test_add_const<void (Class::*)(int) &&>();
    test_add_const<void (Class::*)(int) const>();
    test_add_const<void (Class::*)(int) const&>();
    test_add_const<void (Class::*)(int) const&&>();
    test_add_const<void (Class::*)(int) noexcept>();
    test_add_const<void (Class::*)(int)& noexcept>();
    test_add_const<void (Class::*)(int)&& noexcept>();
    test_add_const<void (Class::*)(int) const noexcept>();
    test_add_const<void (Class::*)(int) const& noexcept>();
    test_add_const<void (Class::*)(int) const&& noexcept>();

    test_add_const<void (Class::*)(...)>();
    test_add_const<void (Class::*)(...)&>();
    test_add_const<void (Class::*)(...) &&>();
    test_add_const<void (Class::*)(...) const>();
    test_add_const<void (Class::*)(...) const&>();
    test_add_const<void (Class::*)(...) const&&>();
    test_add_const<void (Class::*)(...) noexcept>();
    test_add_const<void (Class::*)(...)& noexcept>();
    test_add_const<void (Class::*)(...)&& noexcept>();
    test_add_const<void (Class::*)(...) const noexcept>();
    test_add_const<void (Class::*)(...) const& noexcept>();
    test_add_const<void (Class::*)(...) const&& noexcept>();

    test_add_const<void (Class::*)(int, ...)>();
    test_add_const<void (Class::*)(int, ...)&>();
    test_add_const<void (Class::*)(int, ...) &&>();
    test_add_const<void (Class::*)(int, ...) const>();
    test_add_const<void (Class::*)(int, ...) const&>();
    test_add_const<void (Class::*)(int, ...) const&&>();
    test_add_const<void (Class::*)(int, ...) noexcept>();
    test_add_const<void (Class::*)(int, ...)& noexcept>();
    test_add_const<void (Class::*)(int, ...)&& noexcept>();
    test_add_const<void (Class::*)(int, ...) const noexcept>();
    test_add_const<void (Class::*)(int, ...) const& noexcept>();
    test_add_const<void (Class::*)(int, ...) const&& noexcept>();

    test_add_const<int (Class::*)()>();
    test_add_const<int (Class::*)()&>();
    test_add_const<int (Class::*)() &&>();
    test_add_const<int (Class::*)() const>();
    test_add_const<int (Class::*)() const&>();
    test_add_const<int (Class::*)() const&&>();
    test_add_const<int (Class::*)() noexcept>();
    test_add_const<int (Class::*)()& noexcept>();
    test_add_const<int (Class::*)()&& noexcept>();
    test_add_const<int (Class::*)() const noexcept>();
    test_add_const<int (Class::*)() const& noexcept>();
    test_add_const<int (Class::*)() const&& noexcept>();

    test_add_const<int (Class::*)(int)>();
    test_add_const<int (Class::*)(int)&>();
    test_add_const<int (Class::*)(int) &&>();
    test_add_const<int (Class::*)(int) const>();
    test_add_const<int (Class::*)(int) const&>();
    test_add_const<int (Class::*)(int) const&&>();
    test_add_const<int (Class::*)(int) noexcept>();
    test_add_const<int (Class::*)(int)& noexcept>();
    test_add_const<int (Class::*)(int)&& noexcept>();
    test_add_const<int (Class::*)(int) const noexcept>();
    test_add_const<int (Class::*)(int) const& noexcept>();
    test_add_const<int (Class::*)(int) const&& noexcept>();

    test_add_const<int (Class::*)(...)>();
    test_add_const<int (Class::*)(...)&>();
    test_add_const<int (Class::*)(...) &&>();
    test_add_const<int (Class::*)(...) const>();
    test_add_const<int (Class::*)(...) const&>();
    test_add_const<int (Class::*)(...) const&&>();
    test_add_const<int (Class::*)(...) noexcept>();
    test_add_const<int (Class::*)(...)& noexcept>();
    test_add_const<int (Class::*)(...)&& noexcept>();
    test_add_const<int (Class::*)(...) const noexcept>();
    test_add_const<int (Class::*)(...) const& noexcept>();
    test_add_const<int (Class::*)(...) const&& noexcept>();

    test_add_const<int (Class::*)(int, ...)>();
    test_add_const<int (Class::*)(int, ...)&>();
    test_add_const<int (Class::*)(int, ...) &&>();
    test_add_const<int (Class::*)(int, ...) const>();
    test_add_const<int (Class::*)(int, ...) const&>();
    test_add_const<int (Class::*)(int, ...) const&&>();
    test_add_const<int (Class::*)(int, ...) noexcept>();
    test_add_const<int (Class::*)(int, ...)& noexcept>();
    test_add_const<int (Class::*)(int, ...)&& noexcept>();
    test_add_const<int (Class::*)(int, ...) const noexcept>();
    test_add_const<int (Class::*)(int, ...) const& noexcept>();
    test_add_const<int (Class::*)(int, ...) const&& noexcept>();
}
