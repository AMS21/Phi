# Phi_BuildInfo

project(Phi_BuildInfo CXX)

phi_add_executable(
  NAME
  ${PROJECT_NAME}
  SOURCES
  "src/main.cpp"
  PRIVATE_LINK_LIBRARIES
  Phi::Core
  FOLDER
  "Examples")
phi_add_test(TARGET "${PROJECT_NAME}")
