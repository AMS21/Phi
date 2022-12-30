include(Fuzzing)

# Core
phi_add_fuzzer(NAME "fuzzer_core_algorithm_string_length" SOURCES
               "core/algorithm/string_length.fuzz.cpp" LINK_LIBRARIES Phi::Core)
phi_add_fuzzer(NAME "fuzzer_core_algorithm_string_length_unsafe" SOURCES
               "core/algorithm/string_length_unsafe.fuzz.cpp" LINK_LIBRARIES Phi::Core)
