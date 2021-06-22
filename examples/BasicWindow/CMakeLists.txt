# Phi_BasicWindow

project(Phi_BasicWindow LANGUAGES CXX)

add_executable(${PROJECT_NAME} "src/main.cpp")

phi_enable_static_analyzers(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Examples")

target_link_libraries(${PROJECT_NAME} PRIVATE Phi::Window Phi::InternalProjectOptions)
