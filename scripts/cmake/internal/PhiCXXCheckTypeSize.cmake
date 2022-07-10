phi_include_guard()

include(internal/PhiLog)

# Function to check the size of a cxx type which works when cross compiling
function(phi_cxx_check_type_size TYPE VARIABLE)
  # Check if we already have the result cached
  if(DEFINED ${VARIABLE})
    return()
  endif()

  # Preparation
  set(src_path ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/PhiCXXCheckTypeSize/${VARIABLE}.cpp)
  set(check_sizes "1" "2" "4" "8" "16")

  phi_log("Checking size of ${TYPE}")

  foreach(size ${check_sizes})
    # Prepare source code
    set(src "static_assert(sizeof(${TYPE}) == ${size}, \"\")\; int main() { return 0\; }")
    file(WRITE ${src_path} ${src})

    try_compile(
      HAVE_${var}_${size} ${CMAKE_BINARY_DIR}
      ${src_path}
      COMPILE_DEFINITIONS ${CMAKE_REQUIRED_DEFINITIONS}
      LINK_OPTIONS ${CMAKE_REQUIRED_LINK_OPTIONS}
      LINK_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES}
      CMAKE_FLAGS "-DCOMPILE_DEFINITIONS:STRING=${CMAKE_REQUIRED_FLAGS}"
                  "-DINCLUDE_DIRECTORIES:STRING=${CMAKE_REQUIRED_INCLUDES}"
      OUTPUT_VARIABLE output)

    # Check if compile worked
    if(HAVE_${var}_${size})
      phi_log("Checking size of ${TYPE} - ${size}")
      phi_set_cache_value(NAME ${VARIABLE} VALUE "${size}")
      return()
    endif()
  endforeach()

  # No suitable size found
  phi_log("Checking size of ${TYPE} - Failed")
  phi_set_cache_value(NAME ${VARIABLE} VALUE "0")
endfunction()
