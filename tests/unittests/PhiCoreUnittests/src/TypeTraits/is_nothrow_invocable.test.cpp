#include <catch2/catch.hpp>

#include <Phi/CompilerSupport/Features.hpp>
#include <Phi/Config/Warning.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_invocable.hpp>
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

template <typename Fn, typename... Args>
constexpr bool throws_invocable()
{
    return phi::is_invocable<Fn, Args...>::value && !phi::is_nothrow_invocable<Fn, Args...>::value;
}

template <typename Ret, typename Fn, typename... Args>
constexpr bool throws_invocable_r()
{
    return phi::is_invocable_r<Ret, Fn, Args...>::value &&
           !phi::is_nothrow_invocable_r<Ret, Fn, Args...>::value;
}

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunneeded-member-function")

// FIXME(EricWF) Don't test the where noexcept is *not* part of the type system
// once implementations have caught up.
void test_noexcept_function_pointers()
{
    struct Dummy
    {
        void foo() noexcept
        {}
        static void bar() noexcept
        {}
    };
#if !PHI_HAS_FEATURE_NOEXCEPT_FUNCTION_TYPE()
    {
        // Check that PMF's and function pointers *work*. is_nothrow_invocable will always
        // return false because 'noexcept' is not part of the function type.
        STATIC_REQUIRE(throws_invocable<decltype(&Dummy::foo), Dummy&>());
        STATIC_REQUIRE(throws_invocable<decltype(&Dummy::bar)>());
    }
#else
    {
        // Check that PMF's and function pointers actually work and that
        // is_nothrow_invocable returns true for noexcept PMF's and function
        // pointers.
        STATIC_REQUIRE(phi::is_nothrow_invocable<decltype(&Dummy::foo), Dummy&>::value);
        STATIC_REQUIRE(phi::is_nothrow_invocable<decltype(&Dummy::bar)>::value);
    }
#endif
}

PHI_CLANG_SUPPRESS_WARNING_POP()

TEST_CASE("is_nothrow_invocable")
{
#if PHI_HAS_FEATURE_NOEXCEPT_FUNCTION_TYPE()
    using AbominableFunc = void(...) const noexcept;
#else
    using AbominableFunc = void(...) const;
#endif
    //  Non-callable things
    {
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<void>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<const void>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<volatile void>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<const volatile void>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<phi::nullptr_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<int>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<double>::value);

        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<int[]>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<int[3]>::value);

        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<int*>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<const int*>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<int const*>::value);

        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<int&>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<const int&>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<int&&>::value);

        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<int, std::vector<int>>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<int, std::vector<int*>>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<int, std::vector<int**>>::value);

        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<AbominableFunc>::value);

        //  with parameters
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<int, int>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<int, double, float>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<int, char, float, double>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<Sink, AbominableFunc>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<Sink, void>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<Sink, const volatile void>::value);

        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, void>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, const void>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, volatile void>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, const volatile void>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, phi::nullptr_t>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, int>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, double>::value);

        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, int[]>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, int[3]>::value);

        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, int*>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, const int*>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, int const*>::value);

        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, int&>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, const int&>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, int&&>::value);

        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, std::vector<int>>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, std::vector<int*>>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, std::vector<int**>>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<void, AbominableFunc>::value);

        //  with parameters
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, int, int>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, int, double, float>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<int, int, char, float, double>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<void, Sink, AbominableFunc>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<void, Sink, void>::value);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<void, Sink, const volatile void>::value);
    }

    {
        // Check that the conversion to the return type is properly checked
        using Fn = CallObject<true, int>;
        STATIC_REQUIRE(phi::is_nothrow_invocable_r<Implicit, Fn>::value);
        STATIC_REQUIRE(phi::is_nothrow_invocable_r<double, Fn>::value);
        STATIC_REQUIRE(phi::is_nothrow_invocable_r<const volatile void, Fn>::value);
        STATIC_REQUIRE(throws_invocable_r<ThrowsImplicit, Fn>());
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<Fn(), Explicit>());
    }
    {
        // Check that the conversion to the parameters is properly checked
        using Fn = CallObject<true, void, const Implicit&, const ThrowsImplicit&>;
        STATIC_REQUIRE(phi::is_nothrow_invocable<Fn, Implicit&, ThrowsImplicit&>::value);
        STATIC_REQUIRE(phi::is_nothrow_invocable<Fn, int, ThrowsImplicit&>::value);
        STATIC_REQUIRE(throws_invocable<Fn, int, int>());
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<Fn>::value);
    }
    {
        // Check that the noexcept-ness of function objects is checked.
        using Fn  = CallObject<true, void>;
        using Fn2 = CallObject<false, void>;
        STATIC_REQUIRE(phi::is_nothrow_invocable<Fn>::value);
        STATIC_REQUIRE(throws_invocable<Fn2>());
    }
    {
        // Check that PMD derefs are noexcept
        using Fn = int Tag::*;
        STATIC_REQUIRE(phi::is_nothrow_invocable<Fn, Tag&>::value);
        STATIC_REQUIRE(phi::is_nothrow_invocable_r<Implicit, Fn, Tag&>::value);
        STATIC_REQUIRE(throws_invocable_r<ThrowsImplicit, Fn, Tag&>());
    }
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    {
        // Check for is_nothrow_invocable_v
        using Fn = CallObject<true, int>;
        STATIC_REQUIRE(phi::is_nothrow_invocable_v<Fn>);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_v<Fn, int>);
    }
    {
        // Check for is_nothrow_invocable_r_v
        using Fn = CallObject<true, int>;
        STATIC_REQUIRE(phi::is_nothrow_invocable_r_v<void, Fn>);
        STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r_v<int, Fn, int>);
    }
#endif

    test_noexcept_function_pointers();
}
