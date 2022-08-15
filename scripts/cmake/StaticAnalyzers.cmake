phi_include_guard()

include(CMakeParseArguments)

# cppcheck
find_program(PHI_CPPCHECK_EXECUTABLE cppcheck)

# Extract version from command "cppcheck --version"
if(PHI_CPPCHECK_EXECUTABLE)
  execute_process(
    COMMAND ${PHI_CPPCHECK_EXECUTABLE} --version
    OUTPUT_VARIABLE CPPCHECK_VERSION
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

  # CPPCHECK_VERSION sample: "Cppcheck 2.7"
  string(REGEX REPLACE "Cppcheck ([.0-9]+).*" "\\1" CPPCHECK_VERSION "${CPPCHECK_VERSION}")
  # CPPCHECK_VERSION sample: "2.7"

  # Extract version components
  string(REPLACE "." ";" cppcheck_version_parts "${CPPCHECK_VERSION}")
  list(LENGTH cppcheck_version_parts CPPCHECK_VERSION_COUNT)
  if(CPPCHECK_VERSION_COUNT GREATER 0)
    list(GET cppcheck_version_parts 0 CPPCHECK_VERSION_MAJOR)
  else()
    set(CPPCHECK_VERSION_MAJOR 0)
  endif()
  if(CPPCHECK_VERSION_COUNT GREATER 1)
    list(GET cppcheck_version_parts 1 CPPCHECK_VERSION_MINOR)
  else()
    set(CPPCHECK_VERSION_MINOR 0)
  endif()
  if(CPPCHECK_VERSION_COUNT GREATER 2)
    list(GET cppcheck_version_parts 2 CPPCHECK_VERSION_PATCH)
  else()
    set(CPPCHECK_VERSION_PATCH 0)
  endif()

  phi_log("Found CppCheck version ${CPPCHECK_VERSION} at \"${PHI_CPPCHECK_EXECUTABLE}\"")

else()
  phi_log("CppCheck not found")

endif()

# clang-tidy
find_program(
  PHI_CLANG_TIDY_EXECUTABLE
  NAMES clang-tidy
        clang-tidy-15
        clang-tidy-14
        clang-tidy-13
        clang-tidy-12
        clang-tidy-11
        clang-tidy-10
        clang-tidy-9
        clang-tidy-8
        clang-tidy-7
        clang-tidy-6.0
        clang-tidy-5.0
        clang-tidy-4.0
        clang-tidy-3.9
        clang-tidy-3.8
        clang-tidy-3.7
        clang-tidy-3.6
        clang-tidy-3.5
        clang-tidy-3.4
        clang-tidy-3.3)

if(PHI_CLANG_TIDY_EXECUTABLE)
  # Extract version info
  execute_process(
    COMMAND ${PHI_CLANG_TIDY_EXECUTABLE} --version
    OUTPUT_VARIABLE CLANG_TIDY_VERSION
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
  # CLANG_TIDY_VERSION sample: "LLVM (http://llvm.org/): LLVM version 14.0.6 Optimized build.
  # Default target: x86_64-pc-linux-gnu Host CPU: skylake"

  string(REGEX REPLACE ".*LLVM version ([.0-9]+).*" "\\1" CLANG_TIDY_VERSION
                       "${CLANG_TIDY_VERSION}")

  # Extract version components
  string(REPLACE "." ";" clang_tidy_version_parts "${CLANG_TIDY_VERSION}")
  list(LENGTH clang_tidy_version_parts CLANG_TIDY_VERSION_COUNT)
  if(CLANG_TIDY_VERSION_COUNT GREATER 0)
    list(GET clang_tidy_version_parts 0 CLANG_TIDY_VERSION_MAJOR)
  else()
    set(CLANG_TIDY_VERSION_MAJOR 0)
  endif()
  if(CLANG_TIDY_VERSION_COUNT GREATER 1)
    list(GET clang_tidy_version_parts 1 CLANG_TIDY_VERSION_MINOR)
  else()
    set(CLANG_TIDY_VERSION_MINOR 0)
  endif()
  if(CLANG_TIDY_VERSION_COUNT GREATER 2)
    list(GET clang_tidy_version_parts 2 CLANG_TIDY_VERSION_PATCH)
  else()
    set(CLANG_TIDY_VERSION_PATCH 0)
  endif()

  phi_log("Found clang-tidy version ${CLANG_TIDY_VERSION} at \"${PHI_CLANG_TIDY_EXECUTABLE}\"")
else()
  phi_log("clang-tidy not found")
endif()

# include-what-you-use
find_program(PHI_IWYU_EXECUTABLE NAMES include-what-you-use iwyu)

if(PHI_IWYU_EXECUTABLE)
  # Extract version info
  execute_process(
    COMMAND ${PHI_IWYU_EXECUTABLE} --version
    OUTPUT_VARIABLE IWYU_VERSION
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
  # IWYU_VERSION sample: "include-what-you-use 0.18 (git:abd5d2b) based on clang version 14.0.6
  # (https://github.com/llvm/llvm-project.git f28c006a5895fc0e329fe15fead81e37457cb1d1)"

  string(REGEX REPLACE "include-what-you-use ([.0-9]+).*" "\\1" IWYU_VERSION "${IWYU_VERSION}")

  # Extract version components
  string(REPLACE "." ";" iwyu_version_parts "${IWYU_VERSION}")
  list(LENGTH iwyu_version_parts IWYU_VERSION_COUNT)
  if(IWYU_VERSION_COUNT GREATER 0)
    list(GET iwyu_version_parts 0 IWYU_VERSION_MAJOR)
  else()
    set(IWYU_VERSION_MAJOR 0)
  endif()
  if(IWYU_VERSION_COUNT GREATER 1)
    list(GET iwyu_version_parts 1 IWYU_VERSION_MINOR)
  else()
    set(IWYU_VERSION_MINOR 0)
  endif()
  if(IWYU_VERSION_COUNT GREATER 2)
    list(GET iwyu_version_parts 2 IWYU_VERSION_PATCH)
  else()
    set(IWYU_VERSION_PATCH 0)
  endif()

  phi_log("Found include-what-you-use version ${IWYU_VERSION} at \"${PHI_IWYU_EXECUTABLE}\"")
else()
  phi_log("include-what-you-use not found")
endif()

# TODO: Support MSVC analysis
function(phi_target_use_static_analyzers)
  cmake_parse_arguments(sa "CLANG_TIDY;CPPCHECK;IWYU;ALL;SUPPORTED;WARNINGS_AS_ERRORS" "TARGET"
                        "CLANG_TIDY_OPTIONS;CPPCHECK_OPTIONS;IWYU_OPTIONS" ${ARGN})

  # Check for require arguments
  if(NOT DEFINED sa_TARGET)
    phi_error(
      "phi_target_use_static_analyzers: No target defined. You must specify it by using TARGET")
  endif()

  if(NOT TARGET ${sa_TARGET})
    phi_error("phi_target_use_static_analyzers: The target \"${sa_TARGET}\" doesn't seem to exist")
  endif()

  # Check that we enable atleast one
  if(NOT sa_CLANG_TIDY
     AND NOT sa_CPPCHECK
     AND NOT sa_IWYU
     AND NOT sa_ALL
     AND NOT sa_SUPPORTED)
    phi_error(
      "phi_target_use_static_analyzers: No static analyzer enabled. Specify CLANG_TIDY, CPPCHECK, IWYU, ALL or SUPPORTED to enable some."
    )
  endif()

  # Check that ALL and SUPPORTED are mutually exclusive
  if(sa_ALL AND sa_SUPPORTED)
    phi_error("phi_target_use_static_analyzers: Only specify ALL or SUPPORTED not both")
  endif()

  # Check that ALL is mutually exclusive to all explicit options
  if(sa_ALL
     AND (sa_CLANG_TIDY
          OR sa_CPPCHECK
          OR sa_IWYU))
    phi_error(
      "phi_target_use_static_analyzers: Only specify ALL or one/multiple of CLANG_TIDY, CPPCHECK, IWYU but not both."
    )
  endif()

  # Check that SUPPORTED is mutually exclusive to all explicit options
  if(sa_SUPPORTED
     AND (sa_CLANG_TIDY
          OR sa_CPPCHECK
          OR sa_IWYU))
    phi_error(
      "phi_target_use_static_analyzers: Only specify SUPPORTED or one/multiple of CLANG_TIDY, CPPCHECK, IWYU but not both."
    )
  endif()

  # For ALL simply set all to true
  if(sa_ALL)
    set(sa_CLANG_TIDY 1)
    set(sa_CPPCHECK 1)
    set(sa_IWYU 1)
  endif()

  # For SUPPORTED only enable the ones which where found
  if(sa_SUPPORTED)
    # clang-tidy
    if(PHI_CLANG_TIDY_EXECUTABLE)
      set(sa_CLANG_TIDY 1)
    endif()

    # cppcheck
    if(PHI_CPPCHECK_EXECUTABLE)
      set(sa_CPPCHECK 1)
    endif()

    # include-what-you-use
    if(PHI_IWYU_EXECUTABLE)
      set(sa_IWYU 1)
    endif()
  endif()

  # Enable clang-tidy for the specified target if requested
  if(sa_CLANG_TIDY)
    if(NOT PHI_CLANG_TIDY_EXECUTABLE)
      phi_error(
        "phi_target_use_static_analyzers: clang-tidy was explicitly enabled for target \"${sa_TARGET}\" but seems to be missing"
      )
    endif()

    set(ct_cmdline ${PHI_CLANG_TIDY_EXECUTABLE} -header-filter=.*
                   -extra-arg=-Wno-unknown-warning-option)

    # Optionally enable warnings as errors
    if(sa_WARNINGS_AS_ERRORS)
      list(APPEND ct_cmdline -warnings-as-errors=*)
    endif()

    # Optionally add user options
    if(DEFINED sa_CLANG_TIDY_OPTIONS)
      list(APPEND ct_cmdline ${sa_CLANG_TIDY_OPTIONS})
    endif()

    # Set target property
    set_target_properties(${sa_TARGET} PROPERTIES CXX_CLANG_TIDY "${ct_cmdline}")
  endif()

  # Enable cppcheck for the specified target if requested
  if(sa_CPPCHECK)
    if(NOT PHI_CPPCHECK_EXECUTABLE)
      phi_error(
        "phi_target_use_static_analyzers: cppcheck was explicitly enabled for target \"${sa_TARGET}\" but seems to be missing"
      )
    endif()

    if(CMAKE_GENERATOR MATCHES ".*Visual Studio.*")
      set(CPPCHECK_TEMPLATE "vs")
    else()
      set(CPPCHECK_TEMPLATE "gcc")
    endif()

    set(cc_cmdline ${PHI_CPPCHECK_EXECUTABLE})

    # Optionally add user options
    if(DEFINED sa_CPPCHECK_OPTIONS)
      # if the user provides a CPPCHECK_OPTIONS with a template specified, it will override this
      # template
      list(APPEND cc_cmdline --template=${CPPCHECK_TEMPLATE} ${sa_CPPCHECK_OPTIONS})
    else()
      # Provide a "reasonable" standard config
      list(
        APPEND
        cc_cmdline
        --template=${CPPCHECK_TEMPLATE}
        --enable=all
        --inline-suppr
        # We cannot act on a bug/missing feature of cppcheck
        --suppress=internalAstError
        # if a file does not have an internalAstError, we get an unmatchedSuppression error
        --suppress=unmatchedSuppression
        --inconclusive)
    endif()

    # Optionally enable warnings as errors
    if(sa_WARNINGS_AS_ERRORS)
      list(APPEND cc_cmdline --error-exitcode=2)
    endif()

    # Set target property
    set_target_properties(${sa_TARGET} PROPERTIES CXX_CPPCHECK "${cc_cmdline}")
  endif()

  # Enable include-what-you-use for the specified target if requested
  if(sa_IWYU)
    if(NOT PHI_IWYU_EXECUTABLE)
      phi_error(
        "phi_target_use_static_analyzers: include-what-you-use was explicitly enabled for target \"${sa_TARGET}\" but seems to be missing"
      )
    endif()

    set(iwyu_cmdline ${PHI_IWYU_EXECUTABLE})

    # Optionally add user options
    if(DEFINED sa_IWYU_OPTIONS)
      list(APPEND iwyu_cmdline ${sa_IWYU_OPTIONS})
    endif()

    # Set target property
    set_target_properties(${sa_TARGET} PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_cmdline})
  endif()
endfunction()
