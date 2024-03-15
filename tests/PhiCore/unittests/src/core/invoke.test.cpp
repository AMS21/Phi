#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/noexcept.hpp>
#include <phi/compiler_support/standard_library.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/declval.hpp>
#include <phi/core/forward.hpp>
#include <phi/core/move.hpp>
#include <functional>
#include <type_traits>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wsign-conversion")
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

#include <phi/core/invoke.hpp>

// TODO: Make tests work with MSVC
#if PHI_COMPILER_IS_NOT(MSVC) && PHI_HAS_WORKING_IS_INVOCABLE()

struct NonCopyable
{
    // NOLINTNEXTLINE(modernize-use-equals-default)
    NonCopyable()
    {}

    NonCopyable(NonCopyable const&)            = delete;
    NonCopyable& operator=(NonCopyable const&) = delete;
};

struct TestClass
{
    explicit TestClass(int input_data)
        : data(input_data)
    {}

    int& operator()(NonCopyable&& /*unused*/) &
    {
        return data;
    }
    int const& operator()(NonCopyable&& /*unused*/) const&
    {
        return data;
    }
    int volatile& operator()(NonCopyable&& /*unused*/) volatile&
    {
        return data;
    }
    int const volatile& operator()(NonCopyable&& /*unused*/) const volatile&
    {
        return data;
    }

    int&& operator()(NonCopyable&& /*unused*/) &&
    {
        return phi::move(data);
    }
    int const&& operator()(NonCopyable&& /*unused*/) const&&
    {
        return phi::move(data);
    }
    int volatile&& operator()(NonCopyable&& /*unused*/) volatile&&
    {
        return phi::move(data);
    }
    int const volatile&& operator()(NonCopyable&& /*unused*/) const volatile&&
    {
        return phi::move(data);
    }

    int data;

    TestClass(TestClass const&)            = delete;
    TestClass& operator=(TestClass const&) = delete;
};

struct DerivedFromTestClass : public TestClass
{
    explicit DerivedFromTestClass(int input_data)
        : TestClass(input_data)
    {}
};

int& foo(NonCopyable&& /*unused*/)
{
    static int data = 42;
    return data;
}

template <typename SignatureT, typename ExpectT, typename FunctorT>
void test_b12(FunctorT&& function)
{
    // Create the callable object.
    using ClassFunc                       = SignatureT TestClass::*;
    ClassFunc                    func_ptr = &TestClass::operator();

    // Create the dummy arg.
    NonCopyable arg;

    // Check that the deduced return type of invoke is what is expected.
    using DeducedReturnType =
            decltype(phi::invoke(func_ptr, phi::forward<FunctorT>(function), phi::move(arg)));
    CHECK_SAME_TYPE(DeducedReturnType, ExpectT);

#    if PHI_STANDARD_LIBRARY_LIBCXX() || PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK(); // Emcc stdlib and winclang doesn't seem to have std::result_of
#    else
    // Check that result_of_t matches Expect.
    using ResultOfReturnType =
            typename std::result_of<ClassFunc && (FunctorT&&, NonCopyable&&)>::type;
    CHECK_SAME_TYPE(ResultOfReturnType, ExpectT);
#    endif

    // Run invoke and check the return value.
    DeducedReturnType ret = phi::invoke(func_ptr, phi::forward<FunctorT>(function), phi::move(arg));
    CHECK(ret == 42);
}

template <typename ExpectT, typename FunctorT>
void test_b34(FunctorT&& function)
{
    // Create the callable object.
    using ClassFunc                = int TestClass::*;
    ClassFunc             func_ptr = &TestClass::data;

    // Check that the deduced return type of invoke is what is expected.
    using DeducedReturnType = decltype(phi::invoke(func_ptr, phi::forward<FunctorT>(function)));
    CHECK_SAME_TYPE(DeducedReturnType, ExpectT);

    // Check that result_of_t matches Expect.
#    if PHI_STANDARD_LIBRARY_LIBCXX() || PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK(); // Emcc stdlib and winclang doesn't seem to have std::result_of
#    else
    using ResultOfReturnType = typename std::result_of<ClassFunc && (FunctorT&&)>::type;
    CHECK_SAME_TYPE(ResultOfReturnType, ExpectT);
#    endif

    // Run invoke and check the return value.
    DeducedReturnType ret = phi::invoke(func_ptr, phi::forward<FunctorT>(function));
    CHECK(ret == 42);
}

template <typename ExpectT, typename FunctorT>
void test_b5(FunctorT&& function)
{
    NonCopyable arg;

    // Check that the deduced return type of invoke is what is expected.
    using DeducedReturnType =
            decltype(phi::invoke(phi::forward<FunctorT>(function), phi::move(arg)));
    STATIC_REQUIRE((phi::is_same<DeducedReturnType, ExpectT>::value));

    // Check that result_of_t matches Expect.
#    if PHI_STANDARD_LIBRARY_LIBCXX() || PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK(); // Emcc stdlib and winclang doesn't seem to have std::result_of
#    else
    using ResultOfReturnType = typename std::result_of<FunctorT && (NonCopyable&&)>::type;
    STATIC_REQUIRE((phi::is_same<ResultOfReturnType, ExpectT>::value));
#    endif

    // Run invoke and check the return value.
    DeducedReturnType ret = phi::invoke(phi::forward<FunctorT>(function), phi::move(arg));
    CHECK(ret == 42);
}

TEST_CASE("invoke bullet one and two")
{
    {
        TestClass test_class(42);
        test_b12<int&(NonCopyable&&)&, int&>(test_class);
        test_b12<int const&(NonCopyable&&) const&, int const&>(test_class);
        test_b12<int volatile&(NonCopyable&&) volatile&, int volatile&>(test_class);
        test_b12<int const volatile&(NonCopyable&&) const volatile&, int const volatile&>(
                test_class);

        test_b12<int && (NonCopyable&&)&&, int&&>(phi::move(test_class));
        test_b12<int const && (NonCopyable&&) const&&, int const&&>(phi::move(test_class));
        test_b12<int volatile && (NonCopyable&&) volatile&&, int volatile&&>(phi::move(test_class));
        test_b12<int const volatile && (NonCopyable&&) const volatile&&, int const volatile&&>(
                phi::move(test_class));
    }
    {
        DerivedFromTestClass test_class(42);
        test_b12<int&(NonCopyable&&)&, int&>(test_class);
        test_b12<int const&(NonCopyable&&) const&, int const&>(test_class);
        test_b12<int volatile&(NonCopyable&&) volatile&, int volatile&>(test_class);
        test_b12<int const volatile&(NonCopyable&&) const volatile&, int const volatile&>(
                test_class);

        test_b12<int && (NonCopyable&&)&&, int&&>(phi::move(test_class));
        test_b12<int const && (NonCopyable&&) const&&, int const&&>(phi::move(test_class));
        test_b12<int volatile && (NonCopyable&&) volatile&&, int volatile&&>(phi::move(test_class));
        test_b12<int const volatile && (NonCopyable&&) const volatile&&, int const volatile&&>(
                phi::move(test_class));
    }
    {
        TestClass                         cl_obj(42);
        std::reference_wrapper<TestClass> test_class_ref(cl_obj);
        test_b12<int&(NonCopyable&&)&, int&>(test_class_ref);
        test_b12<int const&(NonCopyable&&) const&, int const&>(test_class_ref);
        test_b12<int volatile&(NonCopyable&&) volatile&, int volatile&>(test_class_ref);
        test_b12<int const volatile&(NonCopyable&&) const volatile&, int const volatile&>(
                test_class_ref);

        test_b12<int&(NonCopyable&&)&, int&>(phi::move(test_class_ref));
        test_b12<int const&(NonCopyable&&) const&, int const&>(phi::move(test_class_ref));
        test_b12<int volatile&(NonCopyable&&) volatile&, int volatile&>(phi::move(test_class_ref));
        test_b12<int const volatile&(NonCopyable&&) const volatile&, int const volatile&>(
                phi::move(test_class_ref));
    }
    {
        DerivedFromTestClass                         cl_obj(42);
        std::reference_wrapper<DerivedFromTestClass> ref(cl_obj);
        test_b12<int&(NonCopyable&&)&, int&>(ref);
        test_b12<int const&(NonCopyable&&) const&, int const&>(ref);
        test_b12<int volatile&(NonCopyable&&) volatile&, int volatile&>(ref);
        test_b12<int const volatile&(NonCopyable&&) const volatile&, int const volatile&>(ref);

        test_b12<int&(NonCopyable&&)&, int&>(phi::move(ref));
        test_b12<int const&(NonCopyable&&) const&, int const&>(phi::move(ref));
        test_b12<int volatile&(NonCopyable&&) volatile&, int volatile&>(phi::move(ref));
        test_b12<int const volatile&(NonCopyable&&) const volatile&, int const volatile&>(
                phi::move(ref));
    }
    {
        TestClass  cl_obj(42);
        TestClass* pointer = &cl_obj;
        test_b12<int&(NonCopyable&&)&, int&>(pointer);
        test_b12<int const&(NonCopyable&&) const&, int const&>(pointer);
        test_b12<int volatile&(NonCopyable&&) volatile&, int volatile&>(pointer);
        test_b12<int const volatile&(NonCopyable&&) const volatile&, int const volatile&>(pointer);
    }
    {
        DerivedFromTestClass  cl_obj(42);
        DerivedFromTestClass* pointer = &cl_obj;
        test_b12<int&(NonCopyable&&)&, int&>(pointer);
        test_b12<int const&(NonCopyable&&) const&, int const&>(pointer);
        test_b12<int volatile&(NonCopyable&&) volatile&, int volatile&>(pointer);
        test_b12<int const volatile&(NonCopyable&&) const volatile&, int const volatile&>(pointer);
    }
}

TEST_CASE("invoke bullet tree and four")
{
    {
        using Fn = TestClass;
        Fn test(42);
        test_b34<int&>(test);
        test_b34<int const&>(static_cast<Fn const&>(test));
        test_b34<int volatile&>(static_cast<Fn volatile&>(test));
        test_b34<int const volatile&>(static_cast<Fn const volatile&>(test));

        test_b34<int&&>(static_cast<Fn&&>(test));
        test_b34<int const&&>(static_cast<Fn const&&>(test));
        test_b34<int volatile&&>(static_cast<Fn volatile&&>(test));
        test_b34<int const volatile&&>(static_cast<Fn const volatile&&>(test));
    }
    {
        using Fn = DerivedFromTestClass;
        Fn test(42);
        test_b34<int&>(test);
        test_b34<int const&>(static_cast<Fn const&>(test));
        test_b34<int volatile&>(static_cast<Fn volatile&>(test));
        test_b34<int const volatile&>(static_cast<Fn const volatile&>(test));

        test_b34<int&&>(static_cast<Fn&&>(test));
        test_b34<int const&&>(static_cast<Fn const&&>(test));
        test_b34<int volatile&&>(static_cast<Fn volatile&&>(test));
        test_b34<int const volatile&&>(static_cast<Fn const volatile&&>(test));
    }
    {
        using Fn = TestClass;
        Fn test(42);
        test_b34<int&>(std::reference_wrapper<Fn>(test));
        test_b34<int const&>(std::reference_wrapper<Fn const>(test));
        test_b34<int volatile&>(std::reference_wrapper<Fn volatile>(test));
        test_b34<int const volatile&>(std::reference_wrapper<Fn const volatile>(test));
    }
    {
        using Fn = DerivedFromTestClass;
        Fn test(42);
        test_b34<int&>(std::reference_wrapper<Fn>(test));
        test_b34<int const&>(std::reference_wrapper<Fn const>(test));
        test_b34<int volatile&>(std::reference_wrapper<Fn volatile>(test));
        test_b34<int const volatile&>(std::reference_wrapper<Fn const volatile>(test));
    }
    {
        using Fn = TestClass;
        Fn  cl_obj(42);
        Fn* ptr = &cl_obj;
        test_b34<int&>(ptr);
        test_b34<int const&>(static_cast<Fn const*>(ptr));
        test_b34<int volatile&>(static_cast<Fn volatile*>(ptr));
        test_b34<int const volatile&>(static_cast<Fn const volatile*>(ptr));
    }
    {
        using Fn = DerivedFromTestClass;
        Fn  cl_obj(42);
        Fn* ptr = &cl_obj;
        test_b34<int&>(ptr);
        test_b34<int const&>(static_cast<Fn const*>(ptr));
        test_b34<int volatile&>(static_cast<Fn volatile*>(ptr));
        test_b34<int const volatile&>(static_cast<Fn const volatile*>(ptr));
    }
}

TEST_CASE("invoke bullet five")
{
    using FooType = int&(NonCopyable&&);
    {
        FooType& function = foo;
        test_b5<int&>(function);
    }
    {
        FooType* function = foo;
        test_b5<int&>(function);
    }
    {
        using Fn = TestClass;
        Fn test(42);
        test_b5<int&>(test);
        test_b5<int const&>(static_cast<Fn const&>(test));
        test_b5<int volatile&>(static_cast<Fn volatile&>(test));
        test_b5<int const volatile&>(static_cast<Fn const volatile&>(test));

        test_b5<int&&>(static_cast<Fn&&>(test));
        test_b5<int const&&>(static_cast<Fn const&&>(test));
        test_b5<int volatile&&>(static_cast<Fn volatile&&>(test));
        test_b5<int const volatile&&>(static_cast<Fn const volatile&&>(test));
    }
}

struct CopyThrows
{
    // NOLINTNEXTLINE(modernize-use-equals-default)
    CopyThrows()
    {}

    // NOLINTNEXTLINE(modernize-use-equals-default)
    CopyThrows(const CopyThrows& /*unused*/)
    {}

    CopyThrows(CopyThrows&& /*unused*/) PHI_NOEXCEPT
    {}
};

struct NoThrowCallable
{
    void operator()() PHI_NOEXCEPT
    {}

    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    void operator()(CopyThrows /*unused*/) PHI_NOEXCEPT
    {}
};

struct ThrowsCallable
{
    void operator()()
    {}
};

struct MemberObj
{
    int x;
};

TEST_CASE("invoke noexcept")
{
    {
        NoThrowCallable obj;
        ((void)obj); // suppress unused warning
        CopyThrows arg;
        ((void)arg); // suppress unused warning
        STATIC_REQUIRE(noexcept(phi::invoke(obj)));
        STATIC_REQUIRE(!noexcept(phi::invoke(obj, arg)));
        STATIC_REQUIRE(noexcept(phi::invoke(obj, phi::move(arg))));
    }
    {
        ThrowsCallable obj;
        ((void)obj); // suppress unused warning
        STATIC_REQUIRE(!noexcept(phi::invoke(obj)));
    }
    {
        MemberObj obj{42};
        ((void)obj); // suppress unused warning.
        STATIC_REQUIRE(noexcept(phi::invoke(&MemberObj::x, obj)));
    }
}

template <typename TypeT, int N>
struct Array
{
    using type = TypeT[N];
};

struct Type
{
    Array<char, 1>::type& f1();
    PHI_NODISCARD Array<char, 2>::type& f2() const;
    Array<char, 1>::type&               g1() &;
    PHI_NODISCARD Array<char, 2>::type& g2() const&;
    Array<char, 3>::type&               g3() &&;
    PHI_NODISCARD Array<char, 4>::type& g4() const&&;
};

TEST_CASE("invoke")
{
    STATIC_REQUIRE(sizeof(phi::invoke(&Type::f1, phi::declval<Type>())) == 1);
    STATIC_REQUIRE(sizeof(phi::invoke(&Type::f2, phi::declval<Type const>())) == 2);
    STATIC_REQUIRE(sizeof(phi::invoke(&Type::g1, phi::declval<Type&>())) == 1);
    STATIC_REQUIRE(sizeof(phi::invoke(&Type::g2, phi::declval<Type const&>())) == 2);
    STATIC_REQUIRE(sizeof(phi::invoke(&Type::g3, phi::declval<Type&&>())) == 3);
    STATIC_REQUIRE(sizeof(phi::invoke(&Type::g4, phi::declval<Type const&&>())) == 4);
}

int foo(int /*unused*/)
{
    return 42;
}

TEST_CASE("invoke basic test")
{
    CHECK(foo(101) == 42);
    //REQUIRE(phi::invoke(foo, 101) == 42);
}

#endif

PHI_GCC_SUPPRESS_WARNING_POP()
