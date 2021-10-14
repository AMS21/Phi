# Submodules

include(ExternalProject)

# Add git submodules
if (${CMAKE_VERSION} VERSION_LESS 3.5)
execute_process(COMMAND "git submodule foreach git reset --hard" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}../")
file(READ "Catch2/CMakeLists.txt" FILE_CONTENTS)
# Patch catch2 cmake_minium_required version to 2.8.12
string(REPLACE "cmake_minimum_required(VERSION 3.5)" "cmake_minimum_required(VERSION 2.8.12)" FILE_CONTENTS "${FILE_CONTENTS}")
# Patch use of project
string(REPLACE "project(Catch2 LANGUAGES CXX VERSION 2.13.7)" "project(Catch2 CXX)" FILE_CONTENTS "${FILE_CONTENTS}")
file(WRITE "Catch2/CMakeLists.txt" "${FILE_CONTENTS}")
endif()

phi_add_external_project(PROJECT Catch2 TARGETS Catch2)

if (${CMAKE_VERSION} VERSION_LESS 3.5)
# Reset catch files
execute_process(COMMAND "git submodule foreach git reset --hard" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}../")
endif()
