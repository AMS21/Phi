#ifndef INCG_PHI_UNITTEST_TYPE_TRAITS_HELPER_HPP
#define INCG_PHI_UNITTEST_TYPE_TRAITS_HELPER_HPP

#include <phi/test/test_macros.hpp>

#define TEST_TYPE_TRAITS_TYPE_DEFS(...)                                                            \
    CHECK_SAME_TYPE(typename __VA_ARGS__::value_type, typename __VA_ARGS__::value_type);           \
    CHECK_SAME_TYPE(typename __VA_ARGS__::type, typename __VA_ARGS__::type);                       \
    CHECK_SAME_TYPE(typename __VA_ARGS__::this_type, typename __VA_ARGS__::this_type);             \
    CHECK_SAME_TYPE(typename __VA_ARGS__::type::value_type, typename __VA_ARGS__::value_type);     \
    CHECK_SAME_TYPE(typename __VA_ARGS__::type::type, typename __VA_ARGS__::type);                 \
    CHECK_SAME_TYPE(typename __VA_ARGS__::type::this_type, typename __VA_ARGS__::this_type);       \
    CHECK_SAME_TYPE(typename __VA_ARGS__::this_type::value_type,                                   \
                    typename __VA_ARGS__::value_type);                                             \
    CHECK_SAME_TYPE(typename __VA_ARGS__::this_type::type, typename __VA_ARGS__::type);            \
    CHECK_SAME_TYPE(typename __VA_ARGS__::this_type::this_type, typename __VA_ARGS__::this_type)

#endif // INCG_PHI_UNITTEST_TYPE_TRAITS_HELPER_HPP
