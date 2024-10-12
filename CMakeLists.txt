cmake_minimum_required(VERSION 3.30)
project(cordstone)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(SOURCES
        src/cordstone.cpp
        src/cordstone.h
        src/discord/discord.cpp
        src/discord/discord.h
        src/discord/message_type.hpp
        src/json/json_loader.cpp
        src/json/json_loader.h
        src/minecraft/image_uploader.cpp
        src/minecraft/image_uploader.h
)

set(OUTPUT_NAME ${PROJECT_NAME})
if(WIN32)
    set(OS_NAME "windows")
elseif(UNIX)
    set(OS_NAME "linux")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(OUTPUT_NAME "${OUTPUT_NAME}_${OS_NAME}_debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(OUTPUT_NAME "${OUTPUT_NAME}_${OS_NAME}")
endif()

include(FetchContent)

FetchContent_Declare(
        endstone
        GIT_REPOSITORY https://github.com/EndstoneMC/endstone.git
        GIT_TAG v0.5.4.1
)
FetchContent_MakeAvailable(endstone)

FetchContent_Declare(
        dpp
        GIT_REPOSITORY https://github.com/brainboxdotcc/DPP.git
        GIT_TAG v10.0.31
)

set(DPP_BUILD_SHARED OFF CACHE BOOL "Build DPP as a static library")
FetchContent_MakeAvailable(dpp)

FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

endstone_add_plugin(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE dpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES} -static -static-libgcc -static-libstdc++ -lz -lssl -lcrypto)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})
