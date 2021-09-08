# Submodules

include(ExternalProject)

# Add git submodules
phi_add_external_project(PROJECT Catch2 TARGETS Catch2 Catch2WithMain)

# Patch spdlog cmake_minium_required version to 3.5
file(READ "spdlog/CMakeLists.txt" FILE_CONTENTS)
string(REPLACE "cmake_minimum_required(VERSION 3.10)" "cmake_minimum_required(VERSION 3.5)" FILE_CONTENTS "${FILE_CONTENTS}")
file(WRITE "spdlog/CMakeLists.txt" "${FILE_CONTENTS}")

phi_add_external_project(PROJECT spdlog TARGETS spdlog)

# Reset spdlog files
file(READ "spdlog/CMakeLists.txt" FILE_CONTENTS)
string(REPLACE "cmake_minimum_required(VERSION 3.5)" "cmake_minimum_required(VERSION 3.10)" FILE_CONTENTS "${FILE_CONTENTS}")
file(WRITE "spdlog/CMakeLists.txt" "${FILE_CONTENTS}")
