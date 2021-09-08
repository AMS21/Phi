# Phi_BuildInfo

project(Phi_BuildInfo LANGUAGES CXX)

phi_add_executable(
  NAME
  ${PROJECT_NAME}
  SOURCES
  "src/main.cpp"
  PRIVATE_LINK_LIBRARIES
  Phi::Core
  Phi::InternalProjectOptions
  FOLDER
  "Examples")

phi_enable_static_analyzers(${PROJECT_NAME})
