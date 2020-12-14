# init
cmake_minimum_required(VERSION 3.17)
project(HealthEye)

set(CMAKE_CXX_STANDARD 20)

# SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)

# ImGui-SFML
find_package(ImGui-SFML REQUIRED)

file(GLOB HEADER_FILES "HealthEye/src/*.h" "HealthEye/src/*.hpp")
file(GLOB SOURCE_FILES "HealthEye/src/*.cpp")

include_directories("HealthEye/src" ${SFML_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} HealthEye/src/Application/Application.cpp HealthEye/src/Application/Application.hpp HealthEye/src/Timer/Timer.cpp HealthEye/src/Timer/Timer.hpp HealthEye/src/Application/Shortcut.cpp HealthEye/src/Application/Shortcut.hpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ImGui-SFML::ImGui-SFML)