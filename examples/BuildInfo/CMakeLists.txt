# Phi_BuildInfo

project(Phi_BuildInfo LANGUAGES CXX)

add_executable(${PROJECT_NAME} "src/main.cpp")

phi_enable_static_analyzers(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE Phi::Core Phi::InternalProjectOptions)
