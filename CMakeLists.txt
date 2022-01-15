cmake_minimum_required(VERSION 3.10)

project(STGAsepriteTest VERSION 1.0)

find_package(SDL2 REQUIRED)
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${JSONC_INCLUDE}
)

add_executable(STGAsepriteTest src/main.c)
target_link_directories(
    STGAsepriteTest
    PRIVATE
    ${JSONC_LIB}
)
target_link_libraries(
    STGAsepriteTest
    PUBLIC
    stgaseprite
    json-c
    SDL2
)
target_include_directories(STGAsepriteTest PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/STGAseprite"
)
add_library(stgaseprite SHARED src/STGAseprite/STGAseprite.c)
