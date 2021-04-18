include_guard(GLOBAL)

include(CTest)
include(Environment)
include(Functions)

# Add a test
function(phi_add_test target)
  if(NOT TARGET ${target})
    phi_error("No target named '${target}' found!")
  endif()

  if(PHI_PLATFORM_EMSCRIPTEN)
    add_test(NAME ${target} COMMAND node "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.js")
  else()
    add_test(NAME ${target} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target})
  endif()
endfunction()
