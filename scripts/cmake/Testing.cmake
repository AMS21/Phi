phi_include_guard()

include(CTest)
include(Environment)
include(Functions)

# Add a test
function(phi_add_test)
  # Commandline
  cmake_parse_arguments(ts "" "TARGET;" "CONFIGURATIONS" ${ARGN})

  # Check required arguments
  if(NOT DEFINED ts_TARGET)
    phi_error("Required argument TARGET is missing!")
  elseif(NOT TARGET ${ts_TARGET})
    phi_error("No target named '${ts_TARGET}' found!")
  endif()

  if(NOT DEFINED ts_CONFIGURATIONS)
    set(all_configs TRUE)
  endif()

  if(PHI_PLATFORM_EMSCRIPTEN)
    # Run the target file with node with emscripten
    if(all_configs)
      add_test(NAME ${ts_TARGET} COMMAND node "$<TARGET_FILE:${ts_TARGET}>")
    else()
      add_test(
        NAME ${ts_TARGET}
        COMMAND node "$<TARGET_FILE:${ts_TARGET}>"
        CONFIGURATIONS "${ts_CONFIGURATIONS}")
    endif()
  else()
    if(all_configs)
      add_test(NAME ${ts_TARGET} COMMAND $<TARGET_FILE:${ts_TARGET}>)
    else()
      add_test(
        NAME ${ts_TARGET}
        COMMAND $<TARGET_FILE:${ts_TARGET}>
        CONFIGURATIONS "${ts_CONFIGURATIONS}")
    endif()
  endif()
endfunction()
