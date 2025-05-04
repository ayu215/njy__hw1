cmake_minimum_required(VERSION 3.10)

project (main)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_C_STANDARD 99)

aux_source_directory(src SRC_LIST)

include_directories(inc)

add_executable(main ${SRC_LIST})