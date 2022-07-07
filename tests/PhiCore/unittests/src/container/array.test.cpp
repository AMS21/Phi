#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include "phi/compiler_support/unused.hpp"
#include "test_types.hpp"
#include <phi/compiler_support/warning.hpp>
#include <phi/container/array.hpp>
#include <phi/core/max_align_t.hpp>

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_PUSH()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wunreachable-code")
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wunused-variable")
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wunused-result")

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4189) // 'x': local variable is initialized but not referenced
PHI_MSVC_SUPPRESS_WARNING(4834) // discarding return value of function with 'nodiscard' attribute
PHI_MSVC_SUPPRESS_WARNING(4702) // unreachable code
PHI_MSVC_SUPPRESS_WARNING(
        5246) // 'member': the initialization of a subobject should be wrapped in braces

// NOLINTNEXTLINE(readability-function-size)
TEST_CASE("Array")
{
    using T   = phi::array<int, 3>;
    using TC  = phi::array<const int, 3>;
    using T0  = phi::array<int, 0>;
    using TC0 = phi::array<const int, 0>;

    SECTION("at/operator[]")
    {
        SECTION("Constexpr")
        {
            EXT_CONSTEXPR_RUNTIME T arr = {1, 2, 4};

            EXT_STATIC_REQUIRE(arr.at(0u) == 1);
            EXT_STATIC_REQUIRE(arr[0u] == 1);
            EXT_STATIC_REQUIRE(arr.at(1u) == 2);
            EXT_STATIC_REQUIRE(arr[1u] == 2);
            EXT_STATIC_REQUIRE(arr.at(2u) == 4);
            EXT_STATIC_REQUIRE(arr[2u] == 4);
        }

        SECTION("non const")
        {
            T arr = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr.at(0u)), T::reference);
            CHECK_SAME_TYPE(decltype(arr.at(0u)), int&);
            CHECK_SAME_TYPE(decltype(arr[0u]), T::reference);
            CHECK_SAME_TYPE(decltype(arr[0u]), int&);
            CHECK_NOEXCEPT(arr.at(0u));
            CHECK_NOEXCEPT(arr[0u]);

            typename T::reference ref1 = arr.at(0u);
            CHECK(ref1 == 1);
            ref1 = 5;
            CHECK(ref1 == 5);
            CHECK(arr.at(0u) == 5);
            CHECK(arr[0u] == 5);

            typename T::reference ref2 = arr.at(1u);
            CHECK(ref2 == 2);
            ref2 = 21;
            CHECK(ref2 == 21);
            CHECK(arr.at(1u) == 21);
            CHECK(arr[1u] == 21);
        }

        SECTION("const")
        {
            const T arr = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr.at(0u)), T::const_reference);
            CHECK_SAME_TYPE(decltype(arr.at(0u)), const int&);
            CHECK_SAME_TYPE(decltype(arr[0u]), T::const_reference);
            CHECK_SAME_TYPE(decltype(arr[0u]), const int&);
            CHECK_NOEXCEPT(arr.at(0u));
            CHECK_NOEXCEPT(arr[0u]);

            typename T::const_reference ref1 = arr.at(0u);
            CHECK(ref1 == 1);

            typename T::const_reference ref2 = arr.at(1u);
            CHECK(ref2 == 2);
        }

        SECTION("Zero sized non const")
        {
            {
                T0 arr = {};

                CHECK_SAME_TYPE(decltype(arr.at(0u)), T0::reference);
                CHECK_SAME_TYPE(decltype(arr.at(0u)), int&);
                CHECK_SAME_TYPE(decltype(arr[0u]), T0::reference);
                CHECK_SAME_TYPE(decltype(arr[0u]), int&);
                CHECK_NOEXCEPT(arr.at(0u));
                CHECK_NOEXCEPT(arr[0u]);

                if (arr.size() > 0u) // always false
                {
                    T0::reference ref1 = arr.at(0u);
                    T0::reference ref2 = arr[0u];
                }
            }

            {
                TC0 arr = {};

                CHECK_SAME_TYPE(decltype(arr.at(0u)), TC0::reference);
                CHECK_SAME_TYPE(decltype(arr.at(0u)), const int&);
                CHECK_SAME_TYPE(decltype(arr[0u]), TC0::reference);
                CHECK_SAME_TYPE(decltype(arr[0u]), const int&);
                CHECK_NOEXCEPT(arr.at(0u));
                CHECK_NOEXCEPT(arr[0u]);

                if (arr.size() > 0u) // always false
                {
                    TC0::reference ref1 = arr.at(0u);
                    TC0::reference ref2 = arr[0u];
                }
            }
        }

        SECTION("Zero sized const")
        {
            {
                const T0 arr = {};

                CHECK_SAME_TYPE(decltype(arr.at(0u)), T0::const_reference);
                CHECK_SAME_TYPE(decltype(arr.at(0u)), const int&);
                CHECK_SAME_TYPE(decltype(arr[0u]), T0::const_reference);
                CHECK_SAME_TYPE(decltype(arr[0u]), const int&);
                CHECK_NOEXCEPT(arr.at(0u));
                CHECK_NOEXCEPT(arr[0u]);

                if (arr.size() > 0u) // always false
                {
                    T0::const_reference ref1 = arr.at(0u);
                    T0::const_reference ref2 = arr[0u];
                }
            }

            {
                const TC0 arr = {};

                CHECK_SAME_TYPE(decltype(arr.at(0u)), TC0::const_reference);
                CHECK_SAME_TYPE(decltype(arr.at(0u)), const int&);
                CHECK_SAME_TYPE(decltype(arr[0u]), TC0::const_reference);
                CHECK_SAME_TYPE(decltype(arr[0u]), const int&);
                CHECK_NOEXCEPT(arr.at(0u));
                CHECK_NOEXCEPT(arr[0u]);

                if (arr.size() > 0u) // always false
                {
                    TC0::const_reference ref1 = arr.at(0u);
                    TC0::const_reference ref2 = arr[0u];
                }
            }
        }

        SECTION("tracked")
        {
            phi::array<tracked, 3> tracked_array;

            CHECK(tracked_array.at(0u).value() == 0);

            tracked_array.at(0u).set_value(25);

            CHECK(tracked_array.at(0u).value() == 25);
        }

        SECTION("Traps")
        {
            phi::array<trap_constructible, 3> test1 = {};
            trap_constructible&               a_ref = test1.at(0u);
            PHI_UNUSED_VARIABLE(a_ref);

            phi::array<trap_implicit_conversion, 3> test2 = {};
            trap_implicit_conversion&               b_ref = test2.at(0u);
            PHI_UNUSED_VARIABLE(b_ref);

            phi::array<trap_comma, 3> test3 = {};
            trap_comma&               c_ref = test3.at(0u);
            PHI_UNUSED_VARIABLE(c_ref);

            phi::array<trap_call, 3> test4 = {};
            trap_call&               d_ref = test4.at(0u);
            PHI_UNUSED_VARIABLE(d_ref);

            phi::array<trap_self_assign, 3> test5 = {};
            trap_self_assign&               e_ref = test5.at(0u);
            PHI_UNUSED_VARIABLE(e_ref);
        }
    }

    SECTION("front")
    {
        SECTION("Constexpr")
        {
            EXT_CONSTEXPR_RUNTIME T constexpr_array = {1, 2, 4};

            EXT_STATIC_REQUIRE(constexpr_array.front() == 1);
        }

        SECTION("non const")
        {
            T arr = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr.front()), T::reference);
            CHECK_SAME_TYPE(decltype(arr.front()), int&);
            CHECK_NOEXCEPT(arr.front());

            typename T::reference ref = arr.front();
            CHECK(ref == 1);
            CHECK(arr.front() == 1);
            CHECK(arr.at(0u) == 1);
            CHECK(arr[0u] == 1);
            ref = 5;
            CHECK(ref == 5);
            CHECK(arr.front() == 5);
            CHECK(arr.at(0u) == 5);
            CHECK(arr[0u] == 5);
        }

        SECTION("const")
        {
            const T arr = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr.front()), T::const_reference);
            CHECK_SAME_TYPE(decltype(arr.front()), const int&);
            CHECK_NOEXCEPT(arr.front());

            typename T::const_reference ref = arr.front();
            CHECK(ref == 1);
            CHECK(arr.front() == 1);
            CHECK(arr.at(0u) == 1);
            CHECK(arr[0u] == 1);
        }

        SECTION("Zero size non const")
        {
            T0 arr = {};
            CHECK_SAME_TYPE(decltype(arr.front()), T0::reference);
            CHECK_SAME_TYPE(decltype(arr.front()), int&);
            CHECK_NOEXCEPT(arr.front());

            if (arr.size() > 0u) // always false
            {
                arr.front();
            }

            TC0 arr2 = {};
            CHECK_SAME_TYPE(decltype(arr2.front()), TC0::reference);
            CHECK_SAME_TYPE(decltype(arr2.front()), const int&);
            CHECK_NOEXCEPT(arr2.front());

            if (arr2.size() > 0u) // always false
            {
                arr2.front();
            }
        }

        SECTION("Zero size const")
        {
            const T0 arr = {};
            CHECK_SAME_TYPE(decltype(arr.front()), T0::const_reference);
            CHECK_SAME_TYPE(decltype(arr.front()), const int&);
            CHECK_NOEXCEPT(arr.front());

            if (arr.size() > 0u) // always false
            {
                arr.front();
            }

            const TC0 arr2 = {};
            CHECK_SAME_TYPE(decltype(arr2.front()), TC0::const_reference);
            CHECK_SAME_TYPE(decltype(arr2.front()), const int&);
            CHECK_NOEXCEPT(arr2.front());

            if (arr2.size() > 0u) // always false
            {
                arr2.front();
            }
        }

        SECTION("tracked")
        {
            phi::array<tracked, 3> tracked_array;

            CHECK(tracked_array.front().value() == 0);

            tracked_array.front().set_value(25);

            CHECK(tracked_array.front().value() == 25);
        }

        SECTION("Traps")
        {
            phi::array<trap_constructible, 3> test1 = {};
            trap_constructible&               a_ref = test1.front();
            PHI_UNUSED_VARIABLE(a_ref);

            phi::array<trap_implicit_conversion, 3> test2 = {};
            trap_implicit_conversion&               b_ref = test2.front();
            PHI_UNUSED_VARIABLE(b_ref);

            phi::array<trap_comma, 3> test3 = {};
            trap_comma&               c_ref = test3.front();
            PHI_UNUSED_VARIABLE(c_ref);

            phi::array<trap_call, 3> test4 = {};
            trap_call&               d_ref = test4.front();
            PHI_UNUSED_VARIABLE(d_ref);

            phi::array<trap_self_assign, 3> test5 = {};
            trap_self_assign&               e_ref = test5.front();
            PHI_UNUSED_VARIABLE(e_ref);
        }
    }

    SECTION("back")
    {
        SECTION("Constexpr")
        {
            EXT_CONSTEXPR_RUNTIME T constexpr_array = {1, 2, 4};

            EXT_STATIC_REQUIRE(constexpr_array.back() == 4);
        }

        SECTION("non const")
        {
            T arr = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr.back()), T::reference);
            CHECK_SAME_TYPE(decltype(arr.back()), int&);
            CHECK_NOEXCEPT(arr.back());

            typename T::reference ref = arr.back();
            CHECK(ref == 4);
            CHECK(arr.back() == 4);
            CHECK(arr.at(2u) == 4);
            CHECK(arr[2u] == 4);
            ref = 5;
            CHECK(ref == 5);
            CHECK(arr.back() == 5);
            CHECK(arr.at(2u) == 5);
            CHECK(arr[2u] == 5);
        }

        SECTION("const")
        {
            const T arr = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr.back()), T::const_reference);
            CHECK_SAME_TYPE(decltype(arr.back()), const int&);
            CHECK_NOEXCEPT(arr.back());

            typename T::const_reference ref = arr.back();
            CHECK(ref == 4);
            CHECK(arr.back() == 4);
            CHECK(arr.at(2u) == 4);
            CHECK(arr[2u] == 4);
        }

        SECTION("Zero size non const")
        {
            T0 arr = {};
            CHECK_SAME_TYPE(decltype(arr.back()), T0::reference);
            CHECK_SAME_TYPE(decltype(arr.back()), int&);
            CHECK_NOEXCEPT(arr.back());

            if (arr.size() > 0u) // always false
            {
                arr.back();
            }

            TC0 arr2 = {};
            CHECK_SAME_TYPE(decltype(arr2.back()), TC0::reference);
            CHECK_SAME_TYPE(decltype(arr2.back()), const int&);
            CHECK_NOEXCEPT(arr2.back());

            if (arr2.size() > 0u) // always false
            {
                arr2.back();
            }
        }

        SECTION("Zero size const")
        {
            const T0 arr = {};
            CHECK_SAME_TYPE(decltype(arr.back()), T0::const_reference);
            CHECK_SAME_TYPE(decltype(arr.back()), const int&);
            CHECK_NOEXCEPT(arr.back());

            if (arr.size() > 0u) // always false
            {
                arr.back();
            }

            const TC0 arr2 = {};
            CHECK_SAME_TYPE(decltype(arr2.back()), TC0::const_reference);
            CHECK_SAME_TYPE(decltype(arr2.back()), const int&);
            CHECK_NOEXCEPT(arr2.back());

            if (arr2.size() > 0u) // always false
            {
                arr2.back();
            }
        }

        SECTION("tracked")
        {
            phi::array<tracked, 3> tracked_array;

            CHECK(tracked_array.back().value() == 0);

            tracked_array.back().set_value(25);

            CHECK(tracked_array.back().value() == 25);
        }

        SECTION("Traps")
        {
            phi::array<trap_constructible, 3> test1 = {};
            trap_constructible&               a_ref = test1.back();
            PHI_UNUSED_VARIABLE(a_ref);

            phi::array<trap_implicit_conversion, 3> test2 = {};
            trap_implicit_conversion&               b_ref = test2.back();
            PHI_UNUSED_VARIABLE(b_ref);

            phi::array<trap_comma, 3> test3 = {};
            trap_comma&               c_ref = test3.back();
            PHI_UNUSED_VARIABLE(c_ref);

            phi::array<trap_call, 3> test4 = {};
            trap_call&               d_ref = test4.back();
            PHI_UNUSED_VARIABLE(d_ref);

            phi::array<trap_self_assign, 3> test5 = {};
            trap_self_assign&               e_ref = test5.back();
            PHI_UNUSED_VARIABLE(e_ref);
        }
    }

    SECTION("data")
    {
        SECTION("non const")
        {
            {
                T    arr     = {1, 2, 4};
                int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), T::pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(arr.data() == &arr[0u]); // NOLINT(readability-container-data-pointer)
                CHECK(*arr.data() == arr[0u]);

                CHECK(pointer != nullptr);
                CHECK(*pointer == 1);
                CHECK(pointer[0] == 1);
                CHECK(pointer[1] == 2);
                CHECK(pointer[2] == 4);

                pointer[0] = 5;

                CHECK(*pointer == 5);
                CHECK(pointer[0] == 5);
                CHECK(*arr.data() == 5);
                CHECK(arr.data()[0] == 5);
                CHECK(arr.at(0u) == 5);
                CHECK(arr[0u] == 5);
            }

            {
                TC         arr     = {1, 2, 4};
                const int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), TC::pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(arr.data() == &arr[0u]); // NOLINT(readability-container-data-pointer)
                CHECK(*arr.data() == arr[0u]);

                CHECK(pointer != nullptr);
                CHECK(*pointer == 1);
                CHECK(pointer[0] == 1);
                CHECK(pointer[1] == 2);
                CHECK(pointer[2] == 4);
            }
        }

        SECTION("const")
        {
            {
                const T    arr     = {1, 2, 4};
                const int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), T::const_pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(arr.data() == &arr[0u]); // NOLINT(readability-container-data-pointer)
                CHECK(*arr.data() == arr[0u]);

                CHECK(pointer != nullptr);
                CHECK(*pointer == 1);
                CHECK(pointer[0] == 1);
                CHECK(pointer[1] == 2);
                CHECK(pointer[2] == 4);
            }

            {
                const TC   arr     = {1, 2, 4};
                const int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), TC::const_pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(arr.data() == &arr[0u]); // NOLINT(readability-container-data-pointer)
                CHECK(*arr.data() == arr[0u]);

                CHECK(pointer != nullptr);
                CHECK(*pointer == 1);
                CHECK(pointer[0] == 1);
                CHECK(pointer[1] == 2);
                CHECK(pointer[2] == 4);
            }
        }

        SECTION("zero sized non const")
        {
            {
                T0   arr     = {};
                int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), T0::pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(pointer == nullptr);
            }

            {
                TC0        arr     = {};
                const int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), TC0::pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(pointer == nullptr);
            }

            {
                using T2                           = phi::array<non_default_constructible, 0>;
                T2                         arr     = {};
                non_default_constructible* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), T2::pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), non_default_constructible*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(pointer == nullptr);
            }
        }

        SECTION("zero sized const")
        {
            {
                const T0   arr     = {};
                const int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), T0::const_pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(pointer == nullptr);
            }

            {
                const TC0  arr     = {};
                const int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), TC0::const_pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(pointer == nullptr);
            }

            {
                using T2                                 = phi::array<non_default_constructible, 0>;
                const T2                         arr     = {};
                const non_default_constructible* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), T2::const_pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const non_default_constructible*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(pointer == nullptr);
            }
        }

        SECTION("alignment")
        {
            {
                using T2                         = phi::array<natural_alignment, 0>;
                const T2                 arr     = {};
                const natural_alignment* pointer = arr.data();
                std::uintptr_t           p_int   = reinterpret_cast<std::uintptr_t>(pointer);

                CHECK(p_int % alignof(natural_alignment) == 0);
            }

            {
                using T2                         = phi::array<natural_alignment, 3>;
                const T2                 arr     = {};
                const natural_alignment* pointer = arr.data();
                std::uintptr_t           p_int   = reinterpret_cast<std::uintptr_t>(pointer);

                CHECK(p_int % alignof(natural_alignment) == 0);
            }

            {
                using T2                        = phi::array<phi::max_align_t, 0>;
                const T2                arr     = {};
                const phi::max_align_t* pointer = arr.data();
                std::uintptr_t          p_int   = reinterpret_cast<std::uintptr_t>(pointer);

                CHECK(p_int % alignof(phi::max_align_t) == 0);
            }

            {
                using T2                        = phi::array<phi::max_align_t, 3>;
                const T2                arr     = {};
                const phi::max_align_t* pointer = arr.data();
                std::uintptr_t          p_int   = reinterpret_cast<std::uintptr_t>(pointer);

                CHECK(p_int % alignof(phi::max_align_t) == 0);
            }
        }

        SECTION("tracked")
        {
            phi::array<tracked, 3> tracked_array;
            tracked*               pointer = tracked_array.data();

            CHECK(pointer->value() == 0);

            pointer->set_value(25);

            CHECK(pointer->value() == 25);
        }

        SECTION("Traps")
        {
            phi::array<trap_constructible, 3> test1 = {};
            trap_constructible*               a_p   = test1.data();
            PHI_UNUSED_VARIABLE(a_p);

            phi::array<trap_implicit_conversion, 3> test2 = {};
            trap_implicit_conversion*               b_p   = test2.data();
            PHI_UNUSED_VARIABLE(b_p);

            phi::array<trap_comma, 3> test3 = {};
            trap_comma*               c_p   = test3.data();
            PHI_UNUSED_VARIABLE(c_p);

            phi::array<trap_call, 3> test4 = {};
            trap_call*               d_p   = test4.data();
            PHI_UNUSED_VARIABLE(d_p);

            phi::array<trap_self_assign, 3> test5 = {};
            trap_self_assign*               e_p   = test5.data();
            PHI_UNUSED_VARIABLE(e_p);
        }
    }

    SECTION("reverse")
    {
        {
            T arr = {1, 2, 3};
            arr.reverse();

            CHECK_NOEXCEPT(arr.reverse());

            CHECK(arr.at(0u) == 3);
            CHECK(arr.at(1u) == 2);
            CHECK(arr.at(2u) == 1);
        }

        SECTION("Traps")
        {
            phi::array<trap_implicit_conversion, 3> test1 = {};
            test1.reverse();

            phi::array<trap_comma, 3> test2 = {};
            test2.reverse();

            phi::array<trap_call, 3> test3 = {};
            test3.reverse();

            phi::array<trap_self_assign, 3> test4 = {};
            test4.reverse();
        }
    }

    SECTION("to_reversed")
    {
        {
            const T arr      = {1, 2, 3};
            T       reversed = arr.to_reversed();

            CHECK_NOEXCEPT(arr.to_reversed());

            CHECK(arr.at(0u) == 1);
            CHECK(arr.at(1u) == 2);
            CHECK(arr.at(2u) == 3);

            CHECK(reversed.at(0u) == 3);
            CHECK(reversed.at(1u) == 2);
            CHECK(reversed.at(2u) == 1);
        }

        SECTION("Traps")
        {
            phi::array<trap_implicit_conversion, 3> test1 = {};
            (void)test1.to_reversed();

            phi::array<trap_comma, 3> test2 = {};
            (void)test2.to_reversed();

            phi::array<trap_call, 3> test3 = {};
            (void)test3.to_reversed();

            phi::array<trap_self_assign, 3> test4 = {};
            (void)test4.to_reversed();
        }
    }
}

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()
