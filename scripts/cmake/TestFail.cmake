phi_include_guard()

include("CMakeParseArguments")
include(Environment)
include(Testing)

function(runtime_failure_test)
  # Commandline
  cmake_parse_arguments(rtf "" "NAME;SOURCE;REGEX;LIB" "CONFIGURATIONS" ${ARGN})

  # Check required arguments
  if(NOT DEFINED rtf_NAME)
    phi_error("runtime_failure_test: NAME must be defined.")
  endif()

  if(NOT DEFINED rtf_SOURCE)
    phi_error("runtime_failure_test: SOURCE must be defined.")
  endif()

  set(TEST_NAME "RuntimeFailure_${rtf_NAME}")

  # Add Executable
  add_executable(${TEST_NAME} "${rtf_SOURCE}")
  set_target_properties(${TEST_NAME} PROPERTIES FOLDER "Tests/RuntimeFailure")
  # Required to link to Phi
  target_link_libraries(${TEST_NAME} PRIVATE Phi::Core)
  target_include_directories(${TEST_NAME} PRIVATE "${PHI_BASE_DIR}/tests/support/runtime_failure")
  target_compile_definitions(${TEST_NAME} PRIVATE "PHI_DEBUG" "PHI_CONFIG_DISABLE_NULLABILITY")

  # Link to additional lib
  if(DEFINED rtf_LIB)
    target_link_libraries(${TEST_NAME} PRIVATE ${rtf_LIB})
  endif()

  # Add test
  phi_add_test(TARGET ${TEST_NAME} CONFIGURATIONS "${rtf_CONFIGURATIONS}")

  # Optionally enable regex
  if(DEFINED rtf_REGEX)
    set_tests_properties(${TEST_NAME} PROPERTIES PASS_REGULAR_EXPRESSION "${rtf_REGEX}")
  else()
    set_tests_properties(${TEST_NAME} PROPERTIES WILL_FAIL TRUE)
  endif()

  # Set linker language
  set_target_properties(${TEST_NAME} PROPERTIES LINKER_LANGUAGE CXX)
endfunction(runtime_failure_test)

function(compile_failure_test)
  # Commandline
  cmake_parse_arguments(ctf "" "NAME;SOURCE;LIB" "CONFIGURATIONS" ${ARGN})

  # Check required arguments
  if(NOT DEFINED ctf_NAME)
    phi_error("compile_failure_test: NAME must be defined.")
  endif()

  if(NOT DEFINED ctf_SOURCE)
    phi_error("compile_failure_test: SOURCE must be defined.")
  endif()

  set(TEST_NAME "CompileFailure_${ctf_NAME}")

  # Add executable
  add_executable(${TEST_NAME} "${ctf_SOURCE}")
  set_target_properties(
    ${TEST_NAME}
    PROPERTIES EXCLUDE_FROM_ALL TRUE
               EXCLUDE_FROM_DEFAULT_BUILD TRUE
               FOLDER "Tests/CompileTimeFailure")
  # Required to link to Phi
  target_link_libraries(${TEST_NAME} PRIVATE Phi::Core)

  # Link to additional lib
  if(DEFINED ctf_LIB)
    target_link_libraries(${TEST_NAME} PRIVATE ${ctf_LIB})
  endif()

  # Add test
  if(DEFINED rtf_CONFIGURATIONS)
    add_test(
      NAME ${TEST_NAME}
      COMMAND ${CMAKE_COMMAND} --build "${CMAKE_BINARY_DIR}" --target ${TEST_NAME} --config
              $<CONFIGURATION>
      CONFIGURATIONS ${rtf_CONFIGURATIONS})
  else()
    add_test(NAME ${TEST_NAME} COMMAND ${CMAKE_COMMAND} --build "${CMAKE_BINARY_DIR}" --target
                                       ${TEST_NAME} --config $<CONFIGURATION>)
  endif()

  set_tests_properties(${TEST_NAME} PROPERTIES WILL_FAIL true)

  # Set linker language
  set_target_properties(${TEST_NAME} PROPERTIES LINKER_LANGUAGE CXX)
endfunction(compile_failure_test)
