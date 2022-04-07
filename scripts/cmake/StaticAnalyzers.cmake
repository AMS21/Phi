phi_include_guard()

include(CMakeParseArguments)

# cppcheck
find_program(PHI_CPPCHECK cppcheck)

# TODO: Print version
if(PHI_CPPCHECK)
  phi_log("CppCheck found: \"${PHI_CPPCHECK}\"")
else()
  phi_log("CppCheck not found")
endif()

# clang-tidy
find_program(
  PHI_CLANG_TIDY
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

# TODO: Print version
if(PHI_CLANG_TIDY)
  phi_log("clang-tidy found: \"${PHI_CLANG_TIDY}\"")
else()
  phi_log("clang-tidy not found")
endif()

# include-what-you-use
find_program(PHI_INCLUDE_WHAT_YOU_USE NAMES include-what-you-use iwyu)

# TODO: Print version
if(PHI_INCLUDE_WHAT_YOU_USE)
  phi_log("include-what-you-use found: \"${PHI_INCLUDE_WHAT_YOU_USE}\"")
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
    if(PHI_CLANG_TIDY)
      set(sa_CLANG_TIDY 1)
    endif()

    # cppcheck
    if(PHI_CPPCHECK)
      set(sa_CPPCHECK 1)
    endif()

    # include-what-you-use
    if(PHI_INCLUDE_WHAT_YOU_USE)
      set(sa_IWYU 1)
    endif()
  endif()

  # Enable clang-tidy for the specified target if requested
  if(sa_CLANG_TIDY)
    if(NOT PHI_CLANG_TIDY)
      phi_error(
        "phi_target_use_static_analyzers: clang-tidy was explicitly enabled for target \"${sa_TARGET}\" but seems to be missing"
      )
    endif()

    set(ct_cmdline ${PHI_CLANG_TIDY} -header-filter=.* -extra-arg=-Wno-unknown-warning-option)

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
    if(NOT PHI_CPPCHECK)
      phi_error(
        "phi_target_use_static_analyzers: cppcheck was explicitly enabled for target \"${sa_TARGET}\" but seems to be missing"
      )
    endif()

    if(CMAKE_GENERATOR MATCHES ".*Visual Studio.*")
      set(CPPCHECK_TEMPLATE "vs")
    else()
      set(CPPCHECK_TEMPLATE "gcc")
    endif()

    set(cc_cmdline ${PHI_CPPCHECK})

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
    if(NOT PHI_INCLUDE_WHAT_YOU_USE)
      phi_error(
        "phi_target_use_static_analyzers: include-what-you-use was explicitly enabled for target \"${sa_TARGET}\" but seems to be missing"
      )
    endif()

    set(iwyu_cmdline ${PHI_INCLUDE_WHAT_YOU_USE})

    # Optionally add user options
    if(DEFINED sa_IWYU_OPTIONS)
      list(APPEND iwyu_cmdline ${sa_IWYU_OPTIONS})
    endif()

    # Set target property
    set_target_properties(${sa_TARGET} PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_cmdline})
  endif()
endfunction()
