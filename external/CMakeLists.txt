# Submodules

include(ExternalProject)

add_subdirectory(Catch2)
add_subdirectory(CppBase)
add_subdirectory(spdlog)

phi_external_project(Catch2)
phi_external_project(CppBase)
phi_external_project(spdlog)
