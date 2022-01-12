#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/generated/compiler_support/features.hpp>
#include <phi/type_traits/is_invocable_r.hpp>
#include <phi/type_traits/is_nothrow_invocable_r.hpp>
#include <vector>

struct Tag
{};

struct Implicit
{
    Implicit(int) noexcept
    {}
};

struct ThrowsImplicit
{
    ThrowsImplicit(int)
    {}
};

struct Explicit
{
    explicit Explicit(int) noexcept
    {}
};

template <bool IsNoexcept, typename Ret, typename... Args>
struct CallObject
{
    Ret operator()(Args&&...) const noexcept(IsNoexcept);
};

struct Sink
{
    template <typename... Args>
    void operator()(Args&&...) const noexcept
    {}
};

template <typename Ret, typename Fn, typename... Args>
constexpr bool throws_invocable_r()
{
    return phi::is_invocable_r<Ret, Fn, Args...>::value &&
           !phi::is_nothrow_invocable_r<Ret, Fn, Args...>::value;
}

template <typename FunctionT, typename... ArgsT>
void test_is_nothrow_invocable_r()
{
    STATIC_REQUIRE(phi::is_nothrow_invocable_r<FunctionT, ArgsT...>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_invocable_r<FunctionT, ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_invocable_r_v<FunctionT, ArgsT...>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_invocable_r_v<FunctionT, ArgsT...>);
#endif
}

template <typename FunctionT, typename... ArgsT>
void test_is_not_nothrow_invocable_r()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<FunctionT, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_not_nothrow_invocable_r<FunctionT, ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r_v<FunctionT, ArgsT...>);
    STATIC_REQUIRE(phi::is_not_nothrow_invocable_r_v<FunctionT, ArgsT...>);
#endif
}

TEST_CASE("is_nothrow_invocable_r")
{
#if PHI_HAS_FEATURE_NOEXCEPT_FUNCTION_TYPE()
    using AbominableFunc = void(...) const noexcept;
#else
    using AbominableFunc = void(...) const;
#endif
    //  Non-callable things
    {
        test_is_not_nothrow_invocable_r<int, void>();
        test_is_not_nothrow_invocable_r<int, const void>();
        test_is_not_nothrow_invocable_r<int, volatile void>();
        test_is_not_nothrow_invocable_r<int, const volatile void>();
        test_is_not_nothrow_invocable_r<int, phi::nullptr_t>();
        test_is_not_nothrow_invocable_r<int, int>();
        test_is_not_nothrow_invocable_r<int, double>();

        test_is_not_nothrow_invocable_r<int, int[]>();
        test_is_not_nothrow_invocable_r<int, int[3]>();

        test_is_not_nothrow_invocable_r<int, int*>();
        test_is_not_nothrow_invocable_r<int, const int*>();
        test_is_not_nothrow_invocable_r<int, int const*>();

        test_is_not_nothrow_invocable_r<int, int&>();
        test_is_not_nothrow_invocable_r<int, const int&>();
        test_is_not_nothrow_invocable_r<int, int&&>();

        test_is_not_nothrow_invocable_r<int, std::vector<int>>();
        test_is_not_nothrow_invocable_r<int, std::vector<int*>>();
        test_is_not_nothrow_invocable_r<int, std::vector<int**>>();
        test_is_not_nothrow_invocable_r<int, AbominableFunc>();

        //  with parameters
        test_is_not_nothrow_invocable_r<int, int, int>();
        test_is_not_nothrow_invocable_r<int, int, double, float>();
        test_is_not_nothrow_invocable_r<int, int, char, double, float>();
        test_is_not_nothrow_invocable_r<void, Sink, AbominableFunc>();
        test_is_not_nothrow_invocable_r<void, Sink, void>();
        test_is_not_nothrow_invocable_r<void, Sink, const void>();
        test_is_not_nothrow_invocable_r<void, Sink, volatile void>();
        test_is_not_nothrow_invocable_r<void, Sink, const volatile void>();
    }

    {
        // Check that the conversion to the return type is properly checked
        using Fn = CallObject<true, int>;
        test_is_nothrow_invocable_r<Implicit, Fn>();
        test_is_nothrow_invocable_r<double, Fn>();
        test_is_nothrow_invocable_r<void, Fn>();
        test_is_nothrow_invocable_r<const void, Fn>();
        test_is_nothrow_invocable_r<volatile void, Fn>();
        test_is_nothrow_invocable_r<const volatile void, Fn>();
        STATIC_REQUIRE(throws_invocable_r<ThrowsImplicit, Fn>());
    }
    {
        // Check that PMD derefs are noexcept
        using Fn = int Tag::*;
        test_is_nothrow_invocable_r<Implicit, Fn, Tag&>();
        STATIC_REQUIRE(throws_invocable_r<ThrowsImplicit, Fn, Tag&>());
    }
    {
        // Check for is_nothrow_invocable_r_v
        using Fn = CallObject<true, int>;
        test_is_nothrow_invocable_r<void, Fn>();
        test_is_not_nothrow_invocable_r<int, Fn, int>();
    }
}
