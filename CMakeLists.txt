cmake_minimum_required(VERSION 3.16)
project(FonoJuego VERSION 1.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -ffast-math")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

# RAYLIB
FetchContent_Declare(raylib URL "https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz")
FetchContent_MakeAvailable(raylib)

# WHISPER
set(WHISPER_BUILD_TESTS OFF CACHE BOOL "No tests" FORCE)
set(WHISPER_BUILD_EXAMPLES OFF CACHE BOOL "No examples" FORCE)
FetchContent_Declare(whisper_download URL "https://github.com/ggerganov/whisper.cpp/archive/refs/tags/v1.5.4.tar.gz")
FetchContent_MakeAvailable(whisper_download)

# INCLUDES Y FUENTES
include_directories(include src ${whisper_download_SOURCE_DIR})

set(SOURCES 
    src/main.cpp 
    src/LogicaJuego.cpp
    src/AudioIA.cpp
    src/Graficos.cpp
    src/Mapa.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib whisper m pthread dl rt)

# ASSETS
set(ASSETS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets" CACHE STRING "Path assets")
target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_PATH="${ASSETS_PATH}")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
