set(HEADER_FILES
    include/Engine/States/State.hpp
    include/Engine/Application/Application.hpp
    include/Engine/System/Shortcut.hpp
    include/Engine/Engine.hpp
    src/States/StateStack.hpp
    src/States/StateInterface.hpp
    )

set(SOURCE_FILES
    include/Engine/States/State.cpp
    include/Engine/Application/Application.cpp
    include/Engine/System/Shortcut.cpp
    src/States/StateStack.cpp
)

# SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

# ImGui-SFML
find_package(ImGui-SFML REQUIRED)

#include_directories(
#    include/Engine
#    src
#)

add_library(Engine ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(Engine INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include" ${SFML_INCLUDE_DIR})
#target_include_directories(Engine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(Engine PUBLIC ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ImGui-SFML::ImGui-SFML)