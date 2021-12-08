phi_include_guard()

# reference https://cmake.org/cmake/help/latest/command/message.html
function(phi_message _opt_mode)
  set(_msg_mode)
  set(_msg_text)

  if(${_opt_mode} STREQUAL "FATAL_ERROR")
    set(_msg_mode "FATAL_ERROR")
  elseif(${_opt_mode} STREQUAL "SEND_ERROR")
    set(_msg_mode "SEND_ERROR")
  elseif(${_opt_mode} STREQUAL "WARNING")
    set(_msg_mode "WARNING")
  elseif(${_opt_mode} STREQUAL "AUTHOR_WARNING")
    set(_msg_mode "AUTHOR_WARNING")
  elseif(${_opt_mode} STREQUAL "DEPRECATED")
    set(_msg_mode "DEPRECATED")
  elseif(${_opt_mode} STREQUAL "STATUS")
    set(_msg_mode "STATUS")

    # CMake >= 3.15
  elseif(${_opt_mode} STREQUAL "NOTICE")
    set(_msg_mode "NOTICE")
  elseif(${_opt_mode} STREQUAL "VERBOSE")
    set(_msg_mode "VERBOSE")
  elseif(${_opt_mode} STREQUAL "DEBUG")
    set(_msg_mode "DEBUG")
  elseif(${_opt_mode} STREQUAL "TRACE")
    set(_msg_mode "TRACE")

    # Reporting checks (CMake >= 3.17)
  elseif(${_opt_mode} STREQUAL "CHECK_START")
    set(_msg_mode "CHECK_START")
  elseif(${_opt_mode} STREQUAL "CHECK_PASS")
    set(_msg_mode "CHECK_PASS")
  elseif(${_opt_mode} STREQUAL "CHECK_FAIL")
    set(_msg_mode "CHECK_FAIL")

  else()
    set(_msg_text ${_opt_mode})
  endif()

  message(${_opt_mode} ${_msg_text} ${ARGN})
endfunction()
