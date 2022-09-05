phi_include_guard()

include(CheckLinkerFlag)
include(CMakeParseArguments)
include(internal/PhiCheckCXXCompilerFlag)

set(PHI_SANITIZER_OPTIONS
    address
    hwaddress
    leak
    memory
    safe-stack
    shadow-call-stack
    thread
    undefined
    CACHE INTERNAL "")

# Check supported sanitizer
set(_phi_sanitizer_support_flags CACHE INTERNAL "")
foreach(_test ${PHI_SANITIZER_OPTIONS})
  string(REPLACE "-" "_" _testName ${_test})
  string(TOUPPER ${_testName} _testName)

  check_linker_flag(CXX ${PHI_FLAG_PREFIX_CHAR}fsanitize=${_test}
                    "PHI_SUPPORTS_SANITIZER_${_testName}")
  if(PHI_SUPPORTS_SANITIZER_${_testName})
    set(_phi_sanitizer_support_flags
        ${_phi_sanitizer_support_flags};${_test}
        CACHE INTERNAL "")
    option(PHI_ENABLE_SANITIZER_${_testName} "Enable ${_test} sanitizer (which is supported)" FALSE)
  else()
    option(PHI_ENABLE_SANITIZER_${_testName} "Enable ${_test} sanitizer (which is not supported)"
           FALSE)
  endif()
endforeach(_test)

# Extra ASAN
set(phi_asan_extra_flags use-after-return=always use-after-scope use-odr-indicator)

# Check supported extra asan flags
set(_phi_asan_extra_flags_supported CACHE INTERNAL "")
if(PHI_SUPPORTS_SANITIZER_ADDRESS)
  foreach(_test ${phi_asan_extra_flags})
    string(REPLACE "-" "_" _testName ${_test})
    string(REPLACE "=" "_" _testName ${_testName})
    string(TOUPPER ${_testName} _testName)

    check_linker_flag(CXX ${PHI_FLAG_PREFIX_CHAR}fsanitize-address-${_test}
                      "PHI_SUPPORTS_SANITIZER_ADDRESS_${_testName}")
    if(PHI_SUPPORTS_SANITIZER_ADDRESS_${_testName})
      set(_phi_asan_extra_flags_supported
          ${_phi_asan_extra_flags_supported};${PHI_FLAG_PREFIX_CHAR}fsanitize-address-${_test}
          CACHE INTERNAL "")
    endif()
  endforeach(_test)
endif()

# Extra ASAN sanitizer options
set(phi_asan_extra_options pointer-compare pointer-subtract)

# Check supported extra asan options
set(_phi_asan_extra_options_supported CACHE INTERNAL "")

if(PHI_SUPPORTS_SANITIZER_ADDRESS)
  foreach(_test ${phi_asan_extra_options})
    string(REPLACE "-" "_" _testName ${_test})
    string(REPLACE "=" "_" _testName ${_testName})
    string(TOUPPER ${_testName} _testName)

    check_linker_flag(CXX ${PHI_FLAG_PREFIX_CHAR}fsanitize=${_test}
                      "PHI_SUPPORTS_SANITIZER_${_testName}")
    if(PHI_SUPPORTS_SANITIZER_${_testName})
      set(_phi_asan_extra_options_supported
          ${_phi_asan_extra_options_supported};${PHI_FLAG_PREFIX_CHAR}fsanitize-address-${_test}
          CACHE INTERNAL "")
    endif()
  endforeach()
endif()

# Extra MSAN
set(phi_msan_extra_flags track-origins=2 use-after-dtor)

# Check supported extra msan flags
set(_phi_msan_extra_flags_supported CACHE INTERNAL "")
if(PHI_SUPPORTS_SANITIZER_MEMORY)
  foreach(_test ${phi_msan_extra_flags})
    string(REPLACE "-" "_" _testName ${_test})
    string(REPLACE "=" "_" _testName ${_testName})
    string(TOUPPER ${_testName} _testName)

    check_linker_flag(CXX ${PHI_FLAG_PREFIX_CHAR}fsanitize-memory-${_test}
                      "PHI_SUPPORTS_SANITIZER_MEMORY_${_testName}")
    if(PHI_SUPPORTS_SANITIZER_MEMORY_${_testName})
      set(_phi_msan_extra_flags_supported
          ${_phi_msan_extra_flags_supported};${PHI_FLAG_PREFIX_CHAR}fsanitize-memory-${_test}
          CACHE INTERNAL "")
    endif()
  endforeach(_test)
endif()

# Extra UBSAN
set(phi_ubsan_extra_flags
    alignment
    bool
    bounds
    builtin
    enum
    float-cast-overflow
    float-divide-by-zero
    integer-divide-by-zero
    nonnull-attribute
    null
    # object-size
    pointer-overflow
    return
    returns-nonnull-attribute
    shift
    shift-base
    shift-exponent
    signed-integer-overflow
    unreachable
    vla-bound
    vptr
    # GCC only
    bounds-strict
    # clang only
    array-bounds
    function
    implicit-conversion
    implicit-integer-arithmetic-value-change
    implicit-integer-sign-change
    implicit-integer-truncation
    implicit-signed-integer-truncation
    implicit-unsigned-integer-truncation
    integer
    local-bounds
    nullability
    nullability-arg
    nullability-assign
    nullability-return
    objc-cast
    unsigned-integer-overflow
    unsigned-shift-base)

# Extra UBSAN
set(_phi_ubsan_extra_flags_supported CACHE INTERNAL "")
if(PHI_SUPPORTS_SANITIZER_UNDEFINED)
  foreach(_test ${phi_ubsan_extra_flags})
    string(REPLACE "-" "_" _testName ${_test})
    string(TOUPPER ${_testName} _testName)

    check_linker_flag(CXX ${PHI_FLAG_PREFIX_CHAR}fsanitize=${_test}
                      "PHI_SUPPORTS_SANITIZER_${_testName}")
    if(PHI_SUPPORTS_SANITIZER_${_testName})
      set(_phi_ubsan_extra_flags_supported
          ${_phi_ubsan_extra_flags_supported};${_test}
          CACHE INTERNAL "")
    endif()
  endforeach(_test)
endif()

# Extra sanitizer flags
set(phi_sanitizer_support_flags
    fno-common
    fno-inline
    fno-inline-functions
    fno-omit-frame-pointer
    fno-optimize-sibling-calls
    fno-sanitize-recover=all
    g3)

# Check sanitizer support flags
set(_phi_extra_santizer_support_flags CACHE INTERNAL "")
foreach(_test ${phi_sanitizer_support_flags})
  string(REPLACE "-" "_" _testName ${_test})
  string(REPLACE "=" "_" _testName ${_testName})
  string(TOUPPER ${_testName} _testName)

  phi_check_cxx_compiler_flag(${PHI_FLAG_PREFIX_CHAR}${_test} "PHI_HAS_FLAG_${_testName}")

  if(PHI_HAS_FLAG_${_testName})
    set(_phi_extra_santizer_support_flags
        ${_phi_extra_santizer_support_flags};${PHI_FLAG_PREFIX_CHAR}${_test}
        CACHE INTERNAL "")
  endif()
endforeach(_test)

function(phi_target_enable_sanitizer)
  # Command line arguments
  cmake_parse_arguments(san "" "TARGET" "SANITIZERS" ${ARGN})

  # Check required arguments
  if(NOT san_TARGET)
    phi_error("phi_target_enable_sanitizer: You must specify a target using TARGET")
  endif()

  if(NOT TARGET ${san_TARGET})
    phi_error(
      "phi_target_enable_sanitizer: The specified target \"${san_TARGET}\" doesn't seem to exist")
  endif()

  if(NOT san_SANITIZERS)
    phi_error("phi_target_enable_sanitizer: No sanitizer specified.")
  endif()

  # Build extra compile flags
  set(extra_compile_flags "")
  foreach(extra_flag ${_phi_extra_santizer_support_flags})
    if(extra_compile_flags EQUAL "")
      set(extra_compile_flags ${extra_flag})
    else()
      set(extra_compile_flags ${extra_compile_flags} ${extra_flag})
    endif()
  endforeach()

  # Enable required sanitizers
  set(list_of_sanitizers "")
  foreach(sanitizer ${san_SANITIZERS})
    string(REPLACE "-" "_" var_sanitizer ${sanitizer})
    string(TOUPPER ${var_sanitizer} var_sanitizer)

    # Check if sanitizer is actually supported
    if(NOT PHI_SUPPORTS_SANITIZER_${var_sanitizer})
      phi_error(
        "phi_target_enable_sanitizer: Trying to enable '${sanitizer}' which is not supported!")
    endif()

    # Append sanitizer to our list of sanitizers
    if(list_of_sanitizers STREQUAL "")
      set(list_of_sanitizers "${sanitizer}")
    else()
      set(list_of_sanitizers "${list_of_sanitizers},${sanitizer}")
    endif()

    # Add extra ASAN options
    if(sanitizer STREQUAL "address")
      # Extra flags
      foreach(asan_extra ${_phi_asan_extra_flags_supported})
        if(extra_compile_flags EQUAL "")
          set(extra_compile_flags ${asan_extra})
        else()
          set(extra_compile_flags ${extra_compile_flags} ${asan_extra})
        endif()
      endforeach()
      # Extra sanitizer options
      list(JOIN _phi_asan_extra_options_supported "," asan_extra)
      set(list_of_sanitizers "${list_of_sanitizers},${asan_extra}")
      # Add extra MSAN options
    elseif(santizier STREQUAL "memory")
      foreach(asan_extra ${_phi_msan_extra_flags_supported})
        if(extra_compile_flags EQUAL "")
          set(extra_compile_flags ${msan_extra})
        else()
          set(extra_compile_flags ${extra_compile_flags} ${msan_extra})
        endif()
      endforeach()
      # Add extra UBSAN options
    elseif(sanitizer STREQUAL "undefined")
      list(JOIN _phi_ubsan_extra_flags_supported "," ubsan_extra)
      set(list_of_sanitizers "${list_of_sanitizers},${ubsan_extra}")
    endif()
  endforeach()

  # Get target type
  get_property(
    target_type
    TARGET ${san_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Set sanitizer flags to target
  target_compile_options(${san_TARGET} ${visibility_scope} -fsanitize=${list_of_sanitizers})
  target_link_options(${san_TARGET} ${visibility_scope} -fsanitize=${list_of_sanitizers})

  # Set extra sanitizer flags to target
  foreach(extra_flag ${extra_compile_flags})
    target_compile_options(${san_TARGET} ${visibility_scope} ${extra_flag})
    target_link_options(${san_TARGET} ${visibility_scope} ${extra_flag})
  endforeach()

  return()

  # Fancy printing
  list(JOIN san_SANITIZERS "," fancy_list_of_sanitizers)
  list(LENGTH san_SANITIZERS num_of_santiziers)
  set(quantifier "s")
  if(${num_of_santiziers} EQUAL "1")
    set(quantifier "")
  endif()
  phi_trace(
    "Enabled ${num_of_santiziers} sanitizer${quantifier} '${fancy_list_of_sanitizers}' for target '${san_TARGET}'"
  )
endfunction()
