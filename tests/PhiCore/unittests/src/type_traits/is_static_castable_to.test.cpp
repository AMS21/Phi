#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/type_traits/is_static_castable_to.hpp>

template <typename FromT, typename ToT>
void test_is_static_castable_to()
{
    STATIC_REQUIRE(phi::is_static_castable_to<FromT, ToT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_static_castable_to<FromT, ToT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_static_castable_to_v<FromT, ToT>);
    STATIC_REQUIRE_FALSE(phi::is_not_static_castable_to_v<FromT, ToT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_static_castable_to<FromT, ToT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_static_castable_to<FromT, ToT>);
}

template <typename FromT, typename ToT>
void test_is_not_static_castable_to()
{
    STATIC_REQUIRE_FALSE(phi::is_static_castable_to<FromT, ToT>::value);
    STATIC_REQUIRE(phi::is_not_static_castable_to<FromT, ToT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_static_castable_to_v<FromT, ToT>);
    STATIC_REQUIRE(phi::is_not_static_castable_to_v<FromT, ToT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_static_castable_to<FromT, ToT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_static_castable_to<FromT, ToT>);
}

struct ConstructFromInt
{
    ConstructFromInt(int /*unused*/)
    {}
};

TEST_CASE("type_traits.is_static_castable_to")
{
    test_is_static_castable_to<int, int>();
    test_is_static_castable_to<float, int>();
    test_is_static_castable_to<double, float>();
    test_is_static_castable_to<void, void>();
    test_is_not_static_castable_to<void, int>();
    test_is_not_static_castable_to<void, float>();
    test_is_static_castable_to<int, void>();
    test_is_static_castable_to<const int, int>();
    test_is_static_castable_to<int, const int>();
    test_is_static_castable_to<int, unsigned>();
    test_is_static_castable_to<unsigned, int>();

    // Explicit conversion
    test_is_static_castable_to<explicit_to<float>, float>();
    test_is_not_static_castable_to<explicit_to<float>, double>();
    test_is_not_static_castable_to<explicit_to<float>, int>();
    test_is_static_castable_to<explicit_to<int>, int>();
    test_is_not_static_castable_to<explicit_to<int>, unsigned>();

    // Implicit conversion
    test_is_static_castable_to<implicit_to<int>, int>();
    test_is_static_castable_to<implicit_to<int>, unsigned>();
    test_is_static_castable_to<implicit_to<int>, float>();
    test_is_static_castable_to<implicit_to<float>, int>();
    test_is_static_castable_to<implicit_to<float>, unsigned>();
    test_is_static_castable_to<implicit_to<float>, float>();

    // void* can be casted to and from any pointer typee
    test_is_static_castable_to<void*, int*>();
    test_is_static_castable_to<void*, const int*>();
    test_is_static_castable_to<const void*, const int*>();
    test_is_not_static_castable_to<const void*, int*>();
    test_is_static_castable_to<int*, void*>();

    test_is_not_static_castable_to<void*, int>();
    test_is_not_static_castable_to<int, void*>();

    // class_type
    test_is_not_static_castable_to<class_type, int>();
    test_is_not_static_castable_to<int, class_type>();
    test_is_static_castable_to<int, ConstructFromInt>();

    // Enums
    test_is_static_castable_to<Enum, int>();
    test_is_static_castable_to<Enum, float>();
    test_is_static_castable_to<Enum, char>();
    test_is_static_castable_to<Enum, void>();
    test_is_static_castable_to<int, Enum>();
    test_is_static_castable_to<float, Enum>();
    test_is_not_static_castable_to<void, Enum>();
    test_is_static_castable_to<Enum, EnumClass>();
    test_is_static_castable_to<EnumClass, Enum>();
    test_is_static_castable_to<EnumClass, int>();
    test_is_static_castable_to<int, EnumClass>();
}
