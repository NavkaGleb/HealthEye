set(HEADER_FILES
    include/Engine/State.hpp
    include/Engine/StateStack.hpp
    include/Engine/Application.hpp
    include/Engine/Shortcut.hpp
    src/StateInterface.hpp
)

set(SOURCE_FILES
    include/Engine/State.cpp
    include/Engine/StateStack.cpp
    include/Engine/Application.cpp
    include/Engine/Shortcut.cpp
)

# SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

# ImGui-SFML
find_package(ImGui-SFML REQUIRED)

include_directories("include" "src" ${SFML_INCLUDE_DIR})

add_library(Engine ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(Engine PUBLIC ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ImGui-SFML::ImGui-SFML)