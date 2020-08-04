option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
option(ENABLE_IWYU "Enable static analysis with include-what-you-use" OFF)

if(ENABLE_CPPCHECK)
  find_program(CPPCHECK cppcheck)
  if(CPPCHECK)
    message(STATUS "cppcheck found: ${CPPCHECK}")

    set(CPPCHECK ${CPPCHECK} --suppress=missingInclude --enable=all --inconclusive -i
                 ${CMAKE_SOURCE_DIR}/extlib)
  else()
    message(SEND_ERROR "cppcheck requested but executable not found")
  endif()
endif()

if(ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY clang-tidy)
  if(CLANG_TIDY)
    message(STATUS "clang-tidy found: ${CLANG_TIDY}")
  else()
    message(SEND_ERROR "clang-tidy requested but executable not found")
  endif()
endif()

if(ENABLE_IWYU)
  find_program(INCLUDE_WHAT_YOU_USE NAMES "include-what-you-use" "iwyu")
  if(INCLUDE_WHAT_YOU_USE)
    message(STATUS "include-what-you-use found: ${INCLUDE_WHAT_YOU_USE}")
  else()
    message(SEND_ERROR "include-what-you-use requested but executable not found")
  endif()
endif()

# Enable static analysis on a specific project
function(enable_static_analyzers project)
  set_target_properties(
    ${project} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY}" CXX_CPPCHECK "${CPPCHECK}"
                          CXX_INCLUDE_WHAT_YOU_USE "${INCLUDE_WHAT_YOU_USE}")
endfunction()
