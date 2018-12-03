cmake_minimum_required (VERSION 3.5)
project(KoreanVocTester)


set(SOURCE_DIR src)
set(INCLUDE_DIR include)
set(SOURCE_FILES
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/App.cpp
        ${SOURCE_DIR}/FileParser.cpp
        ${INCLUDE_DIR}/StringOps.hpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_compile_options (${PROJECT_NAME} PRIVATE -std=c++17 -W -Wall -Wextra)