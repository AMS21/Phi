project("RuntimeFailureRunner" LANGUAGES CXX)

find_package(Threads)

file(GLOB RTFR_SOURCE
    "src/main.cpp")

file(GLOB RTFR_HEADERS)

add_executable(${PROJECT_NAME} ${RTFR_SOURCE} ${RTFR_HEADERS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${RTFR_SOURCE} ${RTFR_HEADERS})

enable_static_analyzers(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC Phi::ProjectOptions Threads::Threads)
