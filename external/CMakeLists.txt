# Submodules

include(ExternalProject)

# Add git submodules
phi_add_external_project(PROJECT Catch2 TARGETS Catch2 Catch2WithMain)
phi_add_external_project(PROJECT spdlog TARGETS spdlog)
