project("Phi_C_Compatibility" C)

phi_add_executable(
  NAME
  "${PROJECT_NAME}"
  SOURCES
  "main.c"
  FOLDER
  "Tests/Integration"
  PRIVATE_LINK_LIBRARIES
  Phi::Core)

# Set linker language to C
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)

phi_add_test(TARGET "${PROJECT_NAME}")
