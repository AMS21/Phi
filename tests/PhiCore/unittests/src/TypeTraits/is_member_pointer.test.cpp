#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_member_pointer.hpp>

template <typename T>
void test_is_member_pointer()
{
    STATIC_REQUIRE(phi::is_member_pointer<T>::value);
    STATIC_REQUIRE(phi::is_member_pointer<const T>::value);
    STATIC_REQUIRE(phi::is_member_pointer<volatile T>::value);
    STATIC_REQUIRE(phi::is_member_pointer<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_member_pointer_v<T>);
    STATIC_REQUIRE(phi::is_member_pointer_v<const T>);
    STATIC_REQUIRE(phi::is_member_pointer_v<volatile T>);
    STATIC_REQUIRE(phi::is_member_pointer_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_member_pointer()
{
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<const volatile T>);
#endif
}

TEST_CASE("is_member_pointer")
{
    // Member object pointers
    test_is_member_pointer<MemberObjectPtr>();
    test_is_member_pointer<int Abstract::*>();
    test_is_member_pointer<double NotEmpty::*>();
    test_is_member_pointer<FunctionPtr Empty::*>();
    test_is_member_pointer<void (Empty::*)()>();
    test_is_member_pointer<int Abstract::*>();
    test_is_member_pointer<double NotEmpty::*>();
    test_is_member_pointer<FunctionPtr Empty::*>();
    test_is_member_pointer<int Class::*>();
    test_is_member_pointer<int Class::*>();

    // Member function pointers
    test_is_member_pointer<MemberFunctionPtr>();
    test_is_member_pointer<int (Empty::*)(int, ...) const>();
    test_is_member_pointer<int (Empty::*)(int, long, long) const noexcept>();
    test_is_member_pointer<int (Empty::*)()& noexcept>();
    test_is_member_pointer<int Empty::*>();
    test_is_member_pointer<void (Empty::*)(int)>();

    test_is_member_pointer<void (Class::*)()>();
    test_is_member_pointer<void (Class::*)(int)>();
    test_is_member_pointer<void (Class::*)(int, char)>();

    test_is_member_pointer<void (Class::*)()>();
    test_is_member_pointer<void (Class::*)(int)>();
    test_is_member_pointer<void (Class::*)(int, char)>();

    test_is_member_pointer<void (Class::*)() const>();
    test_is_member_pointer<void (Class::*)(int) const>();
    test_is_member_pointer<void (Class::*)(int, char) const>();

    test_is_member_pointer<void (Class::*)() volatile>();
    test_is_member_pointer<void (Class::*)(int) volatile>();
    test_is_member_pointer<void (Class::*)(int, char) volatile>();

    test_is_member_pointer<void (Class::*)(...)>();
    test_is_member_pointer<void (Class::*)(int, ...)>();
    test_is_member_pointer<void (Class::*)(int, char, ...)>();

    test_is_member_pointer<void (Class::*)(...) const>();
    test_is_member_pointer<void (Class::*)(int, ...) const>();
    test_is_member_pointer<void (Class::*)(int, char, ...) const>();

    test_is_member_pointer<void (Class::*)(...) volatile>();
    test_is_member_pointer<void (Class::*)(int, ...) volatile>();
    test_is_member_pointer<void (Class::*)(int, char, ...) volatile>();

    // Noexcept qualifiers
    test_is_member_pointer<void (Class::*)() noexcept>();
    test_is_member_pointer<void (Class::*)(int) noexcept>();
    test_is_member_pointer<void (Class::*)(int, char) noexcept>();

    test_is_member_pointer<void (Class::*)() const noexcept>();
    test_is_member_pointer<void (Class::*)(int) const noexcept>();
    test_is_member_pointer<void (Class::*)(int, char) const noexcept>();

    test_is_member_pointer<void (Class::*)() volatile noexcept>();
    test_is_member_pointer<void (Class::*)(int) volatile noexcept>();
    test_is_member_pointer<void (Class::*)(int, char) volatile noexcept>();

    test_is_member_pointer<void (Class::*)(...) noexcept>();
    test_is_member_pointer<void (Class::*)(int, ...) noexcept>();
    test_is_member_pointer<void (Class::*)(int, char, ...) noexcept>();

    test_is_member_pointer<void (Class::*)(...) const noexcept>();
    test_is_member_pointer<void (Class::*)(int, ...) const noexcept>();
    test_is_member_pointer<void (Class::*)(int, char, ...) const noexcept>();

    test_is_member_pointer<void (Class::*)(...) volatile noexcept>();
    test_is_member_pointer<void (Class::*)(int, ...) volatile noexcept>();
    test_is_member_pointer<void (Class::*)(int, char, ...) volatile noexcept>();

    // lvalue qualifiers
    test_is_member_pointer<void (Class::*)()&>();
    test_is_member_pointer<void (Class::*)(int)&>();
    test_is_member_pointer<void (Class::*)(int, char)&>();
    test_is_member_pointer<void (Class::*)(...)&>();
    test_is_member_pointer<void (Class::*)(int, ...)&>();
    test_is_member_pointer<void (Class::*)(int, char, ...)&>();

    test_is_member_pointer<void (Class::*)() const&>();
    test_is_member_pointer<void (Class::*)(int) const&>();
    test_is_member_pointer<void (Class::*)(int, char) const&>();
    test_is_member_pointer<void (Class::*)(...) const&>();
    test_is_member_pointer<void (Class::*)(int, ...) const&>();
    test_is_member_pointer<void (Class::*)(int, char, ...) const&>();

    test_is_member_pointer<void (Class::*)() volatile&>();
    test_is_member_pointer<void (Class::*)(int) volatile&>();
    test_is_member_pointer<void (Class::*)(int, char) volatile&>();
    test_is_member_pointer<void (Class::*)(...) volatile&>();
    test_is_member_pointer<void (Class::*)(int, ...) volatile&>();
    test_is_member_pointer<void (Class::*)(int, char, ...) volatile&>();

    test_is_member_pointer<void (Class::*)() const volatile&>();
    test_is_member_pointer<void (Class::*)(int) const volatile&>();
    test_is_member_pointer<void (Class::*)(int, char) const volatile&>();
    test_is_member_pointer<void (Class::*)(...) const volatile&>();
    test_is_member_pointer<void (Class::*)(int, ...) const volatile&>();
    test_is_member_pointer<void (Class::*)(int, char, ...) const volatile&>();

    // Lvalue qualifiers with noexcept
    test_is_member_pointer<void (Class::*)()& noexcept>();
    test_is_member_pointer<void (Class::*)(int)& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char)& noexcept>();
    test_is_member_pointer<void (Class::*)(...)& noexcept>();
    test_is_member_pointer<void (Class::*)(int, ...)& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char, ...)& noexcept>();

    test_is_member_pointer<void (Class::*)() const& noexcept>();
    test_is_member_pointer<void (Class::*)(int) const& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char) const& noexcept>();
    test_is_member_pointer<void (Class::*)(...) const& noexcept>();
    test_is_member_pointer<void (Class::*)(int, ...) const& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char, ...) const& noexcept>();

    test_is_member_pointer<void (Class::*)() volatile& noexcept>();
    test_is_member_pointer<void (Class::*)(int) volatile& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char) volatile& noexcept>();
    test_is_member_pointer<void (Class::*)(...) volatile& noexcept>();
    test_is_member_pointer<void (Class::*)(int, ...) volatile& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char, ...) volatile& noexcept>();

    test_is_member_pointer<void (Class::*)() const volatile& noexcept>();
    test_is_member_pointer<void (Class::*)(int) const volatile& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char) const volatile& noexcept>();
    test_is_member_pointer<void (Class::*)(...) const volatile& noexcept>();
    test_is_member_pointer<void (Class::*)(int, ...) const volatile& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char, ...) const volatile& noexcept>();

    // RValue qualifiers
    test_is_member_pointer<void (Class::*)() &&>();
    test_is_member_pointer<void (Class::*)(int) &&>();
    test_is_member_pointer<void (Class::*)(int, char) &&>();
    test_is_member_pointer<void (Class::*)(...) &&>();
    test_is_member_pointer<void (Class::*)(int, ...) &&>();
    test_is_member_pointer<void (Class::*)(int, char, ...) &&>();

    test_is_member_pointer<void (Class::*)() const&&>();
    test_is_member_pointer<void (Class::*)(int) const&&>();
    test_is_member_pointer<void (Class::*)(int, char) const&&>();
    test_is_member_pointer<void (Class::*)(...) const&&>();
    test_is_member_pointer<void (Class::*)(int, ...) const&&>();
    test_is_member_pointer<void (Class::*)(int, char, ...) const&&>();

    test_is_member_pointer<void (Class::*)() volatile&&>();
    test_is_member_pointer<void (Class::*)(int) volatile&&>();
    test_is_member_pointer<void (Class::*)(int, char) volatile&&>();
    test_is_member_pointer<void (Class::*)(...) volatile&&>();
    test_is_member_pointer<void (Class::*)(int, ...) volatile&&>();
    test_is_member_pointer<void (Class::*)(int, char, ...) volatile&&>();

    test_is_member_pointer<void (Class::*)() const volatile&&>();
    test_is_member_pointer<void (Class::*)(int) const volatile&&>();
    test_is_member_pointer<void (Class::*)(int, char) const volatile&&>();
    test_is_member_pointer<void (Class::*)(...) const volatile&&>();
    test_is_member_pointer<void (Class::*)(int, ...) const volatile&&>();
    test_is_member_pointer<void (Class::*)(int, char, ...) const volatile&&>();

    // RValue qualifiers with noexcept
    test_is_member_pointer<void (Class::*)()&& noexcept>();
    test_is_member_pointer<void (Class::*)(int)&& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char)&& noexcept>();
    test_is_member_pointer<void (Class::*)(...)&& noexcept>();
    test_is_member_pointer<void (Class::*)(int, ...)&& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char, ...)&& noexcept>();

    test_is_member_pointer<void (Class::*)() const&& noexcept>();
    test_is_member_pointer<void (Class::*)(int) const&& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char) const&& noexcept>();
    test_is_member_pointer<void (Class::*)(...) const&& noexcept>();
    test_is_member_pointer<void (Class::*)(int, ...) const&& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char, ...) const&& noexcept>();

    test_is_member_pointer<void (Class::*)() volatile&& noexcept>();
    test_is_member_pointer<void (Class::*)(int) volatile&& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char) volatile&& noexcept>();
    test_is_member_pointer<void (Class::*)(...) volatile&& noexcept>();
    test_is_member_pointer<void (Class::*)(int, ...) volatile&& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char, ...) volatile&& noexcept>();

    test_is_member_pointer<void (Class::*)() const volatile&& noexcept>();
    test_is_member_pointer<void (Class::*)(int) const volatile&& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char) const volatile&& noexcept>();
    test_is_member_pointer<void (Class::*)(...) const volatile&& noexcept>();
    test_is_member_pointer<void (Class::*)(int, ...) const volatile&& noexcept>();
    test_is_member_pointer<void (Class::*)(int, char, ...) const volatile&& noexcept>();

    // Non member pointers
    test_is_not_member_pointer<phi::nullptr_t>();
    test_is_not_member_pointer<void>();
    test_is_not_member_pointer<void*>();
    test_is_not_member_pointer<short>();
    test_is_not_member_pointer<int>();
    test_is_not_member_pointer<int&>();
    test_is_not_member_pointer<int&&>();
    test_is_not_member_pointer<int*>();
    test_is_not_member_pointer<const int*>();
    test_is_not_member_pointer<volatile int*>();
    test_is_not_member_pointer<const volatile int*>();
    test_is_not_member_pointer<int**>();
    test_is_not_member_pointer<float>();
    test_is_not_member_pointer<double>();
    test_is_not_member_pointer<char[3]>();
    test_is_not_member_pointer<char[]>();
    test_is_not_member_pointer<int(int)>();
    test_is_not_member_pointer<Class>();
    test_is_not_member_pointer<Empty>();
    test_is_not_member_pointer<NotEmpty>();
    test_is_not_member_pointer<Union>();
    test_is_not_member_pointer<NonEmptyUnion>();
    test_is_not_member_pointer<bit_zero>();
    test_is_not_member_pointer<bit_one>();
    test_is_not_member_pointer<Abstract>();
    test_is_not_member_pointer<AbstractTemplate<int>>();
    test_is_not_member_pointer<AbstractTemplate<double>>();
    test_is_not_member_pointer<Enum>();
    test_is_not_member_pointer<EnumSigned>();
    test_is_not_member_pointer<EnumUnsigned>();
    test_is_not_member_pointer<EnumClass>();
    test_is_not_member_pointer<incomplete_type>();
    test_is_not_member_pointer<Function>();
    test_is_not_member_pointer<FunctionPtr>();
}
