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
