# Submodules
add_subdirectory(Catch2)
add_subdirectory(CppBase)
add_subdirectory(spdlog)

target_link_libraries(spdlog PRIVATE project_options)
