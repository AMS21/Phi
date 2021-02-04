if(PHI_ENABLE_CPPCHECK)
  find_program(CPPCHECK cppcheck)

  if(CPPCHECK)
    phi_log("CppCheck found: ${CPPCHECK}")

    set(CPPCHECK
        ${CPPCHECK}
        --suppress=missingInclude
        --enable=all
        --inline-suppr
        --inconclusive
        -i
        ${CMAKE_SOURCE_DIR}/extlib)
  else()
    phi_warn("CppCheck requested but executable not found")
    set(PHI_ENABLE_CPPCHECK
        OFF
        CACHE BOOL "" FORCE)
  endif()
endif()

if(PHI_ENABLE_CLANG_TIDY)
  find_program(
    CLANG_TIDY
    NAMES clang-tidy
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

  if(CLANG_TIDY)
    phi_log("clang-tidy found: ${CLANG_TIDY}")
  else()
    phi_warn("clang-tidy requested but executable not found")
    set(PHI_ENABLE_CLANG_TIDY
        OFF
        CACHE BOOL "" FORCE)
  endif()
endif()

if(PHI_ENABLE_IWYU)
  find_program(INCLUDE_WHAT_YOU_USE NAMES include-what-you-use iwyu)

  if(INCLUDE_WHAT_YOU_USE)
    phi_log("include-what-you-use found: ${INCLUDE_WHAT_YOU_USE}")
  else()
    phi_warn("include-what-you-use requested but executable not found")
    set(PHI_ENABLE_IWYU
        OFF
        CACHE BOOL "" FORCE)
  endif()
endif()

# Enable static analysis on a specific project
function(phi_enable_static_analyzers project)
  set_target_properties(
    ${project}
    PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY}"
               CXX_CPPCHECK "${CPPCHECK}"
               CXX_INCLUDE_WHAT_YOU_USE "${INCLUDE_WHAT_YOU_USE}")
endfunction()
