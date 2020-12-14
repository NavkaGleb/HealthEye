set(HEADER_FILES
    include/Engine/States/State.hpp
    src/States/StateStack.hpp
    include/Engine/Application/Application.hpp
    include/Engine/System/Shortcut.hpp
    src/States/StateInterface.hpp
    include/Engine/Engine.hpp
)

set(SOURCE_FILES
    include/Engine/States/State.cpp
    src/States/StateStack.cpp
    include/Engine/Application/Application.cpp
    include/Engine/System/Shortcut.cpp
)

# SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

# ImGui-SFML
find_package(ImGui-SFML REQUIRED)

include_directories("include/Engine" "src" ${SFML_INCLUDE_DIR})

add_library(Engine ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(Engine PUBLIC ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ImGui-SFML::ImGui-SFML)