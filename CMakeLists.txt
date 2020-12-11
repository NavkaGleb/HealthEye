# init
cmake_minimum_required(VERSION 3.17)
project(HealthEye)

set(CMAKE_CXX_STANDARD 20)

# SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)

# ImGui-SFML
find_package(ImGui-SFML REQUIRED)

file(GLOB HEADER_FILES "src/*.h" "src/*.hpp")
file(GLOB SOURCE_FILES "src/*.cpp")

include_directories("src" ${SFML_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ImGui-SFML::ImGui-SFML)