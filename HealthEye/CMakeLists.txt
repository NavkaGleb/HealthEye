set(HEADER_FILES
    src/Application/Application.hpp
    src/Timer/Timer.hpp
)

set(SOURCE_FILES
    src/main.cpp
    src/Application/Application.cpp
    src/Timer/Timer.cpp
)

include_directories("src")

add_executable(HealthEye ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(HealthEye PRIVATE Engine)