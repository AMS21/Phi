include("CMakeParseArguments")

function(runtime_failure_test)
  # Commandline
  cmake_parse_arguments(rtf "" "NAME;SOURCE;REGEX" "CONFIGURATIONS" ${ARGN})

  # Check required arguments
  if(NOT DEFINED rtf_NAME)
    message(FATAL_ERROR "NAME must be defined.")
  endif()

  if(NOT DEFINED rtf_SOURCE)
    message(FATAL_ERROR "SOURCE must be defined.")
  endif()

  set(TEST_NAME "RuntimeFailure_${rtf_NAME}")

  # Add Executable
  add_executable(${TEST_NAME} "${rtf_SOURCE}")
  set_target_properties(${TEST_NAME} PROPERTIES FOLDER "Tests/RuntimeFailure")
  # Required to link to Phi
  target_link_libraries(${TEST_NAME} PRIVATE Phi::ProjectOptions Phi::Engine)

  # Add test
  if(DEFINED rtf_CONFIGURATIONS)
    add_test(
      NAME ${TEST_NAME}
      COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}
      CONFIGURATIONS ${rtf_CONFIGURATIONS})
  else()
    add_test(NAME ${TEST_NAME} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME})
  endif()

  # Optionally enable regex
  if(DEFINED rtf_REGEX)
    set_tests_properties(${TEST_NAME} PROPERTIES PASS_REGULAR_EXPRESSION "${rtf_REGEX}")
  else()
    set_tests_properties(${TEST_NAME} PROPERTIES WILL_FAIL TRUE)
  endif()
endfunction(runtime_failure_test)

function(compile_failure_test)
  # Commandline
  cmake_parse_arguments(ctf "" "NAME;SOURCE" "CONFIGURATIONS" ${ARGN})

  # Check required arguments
  if(NOT DEFINED ctf_NAME)
    message(FATAL_ERROR "NAME must be defined.")
  endif()

  if(NOT DEFINED ctf_SOURCE)
    message(FATAL_ERROR "SOURCE must be defined.")
  endif()

  set(TEST_NAME "CompileFailure_${ctf_NAME}")

  # Add executable
  add_executable(${TEST_NAME} "${ctf_SOURCE}")
  set_target_properties(
    ${TEST_NAME} PROPERTIES EXCLUDE_FROM_ALL TRUE EXCLUDE_FROM_DEFAULT_BUILD TRUE
                            FOLDER "Tests/CompileTimeFailure")
  # Required to link to Phi
  target_link_libraries(${TEST_NAME} PRIVATE Phi::ProjectOptions Phi::Engine)

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
endfunction(compile_failure_test)
