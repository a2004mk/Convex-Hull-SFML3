cmake_minimum_required(VERSION 3.15)
project(ConHull LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Sources & Headers ────────────────────────────────────────────────
set(SOURCES
    src/ConHull.cpp
    src/ConvexHull.cpp
    src/GameState.cpp
    src/Renderer.cpp
    src/InputHandler.cpp
    src/Button.cpp
    src/InputField.cpp
    src/EditPointWindow.cpp
    src/Point.cpp
)

set(HEADERS
    include/ConvexHull.h
    include/GameState.h
    include/Renderer.h
    include/InputHandler.h
    include/Button.h
    include/InputField.h
    include/EditPointWindow.h
    include/Point.h
)

# ── Executable ───────────────────────────────────────────────────────
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# ── Fetch SFML 3 ────────────────────────────────────────────────────
# Automatically downloads and builds SFML 3.0.2 if not found locally.
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.2
    GIT_SHALLOW    TRUE
)
set(SFML_BUILD_AUDIO    OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK  OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SFML)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

# ── Copy resources next to the binary ────────────────────────────────
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources"
    COMMENT "Copying resources to build directory"
)

# ── Compiler warnings ───────────────────────────────────────────────
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()
