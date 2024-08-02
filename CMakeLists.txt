cmake_minimum_required(VERSION 3.0)
project(untitled)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)






add_subdirectory(deps)
if(WIN32)
set(SDL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL)
set(bgfx_common ${CMAKE_CURRENT_SOURCE_DIR}/deps/bgfx.cmake/bgfx/examples/common)

set(SDL2MAIN_LIBRARY SDL2main)
set(SDL2_LIBRARY SDL2-static)
set(SDL2_IMAGE_INCLUDE_DIR)

set(SDL2_INCLUDE_DIR ${SDL_DIR}/include)

set(ENET_LIBRARY enet)
set(ENET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/enet/include)

set(STB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/bgfx.cmake/bimg/3rdparty/stb)

#set(ENET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/enet)
#add_subdirectory(deps)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/deps/sdl2 )


else()
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/deps/cmake")

    set(SDL2MAIN_LIBRARY "")

    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(ENet REQUIRED)

    set(ENET_INCLUDE_DIR ${ENET_INCLUDE_DIRS})
    set(ENET_LIBRARY ${ENET_LIBRARIES})
    # find_package(SDL2_ttf REQUIRED)
endif()







#include(deps/bgfx.cmake/cmake/util/ConfigureDebugging.cmake)

file(GLOB_RECURSE src "src/*.cpp")
list(FILTER src EXCLUDE REGEX "src/main.cpp")  # Exclude Main.cpp from the source files

# Add the executable and link against the necessary libraries

add_executable(game ${src} src/main.cpp ${PROJECT_SOURCE_DIR}/res/shaders/fs_cubes.sc ${PROJECT_SOURCE_DIR}/res/shaders/vs_cubes.sc)# ${PROJECT_SOURCE_DIR}/res/shaders/ChunkVertex.sc ${PROJECT_SOURCE_DIR}/res/shaders/vs_cubes.sc ${PROJECT_SOURCE_DIR}/res/shaders/ChunkFragment.sc)


BGFX_COMPILE_SHADER_TO_HEADER(
    TYPE VERTEX
    SHADERS ${PROJECT_SOURCE_DIR}/res/shaders/vs_cubes.sc
    VARYING_DEF ${PROJECT_SOURCE_DIR}/res/shaders/varying.def.sc
    OUTPUT_DIR ${CMAKE_BINARY_DIR}/shaders
)


BGFX_COMPILE_SHADER_TO_HEADER(
    TYPE FRAGMENT
    SHADERS ${PROJECT_SOURCE_DIR}/res/shaders/fs_cubes.sc
    VARYING_DEF ${PROJECT_SOURCE_DIR}/res/shaders/varying.def.sc
    OUTPUT_DIR ${CMAKE_BINARY_DIR}/shaders
)






#add_shader( ${PROJECT_SOURCE_DIR}/res/shaders/vs_cubes.sc VERTEX   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders DX11_MODEL 5_0 GLSL 130 )
#add_shader( ${PROJECT_SOURCE_DIR}/res/shaders/fs_cubes.sc FRAGMENT OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders DX11_MODEL 5_0 GLSL 130 )

#add_shader( ${PROJECT_SOURCE_DIR}/res/shaders/ChunkVertex.sc VERTEX   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders DX11_MODEL 5_0 GLSL 130 )
#add_shader( ${PROJECT_SOURCE_DIR}/res/shaders/ChunkFragment.sc FRAGMENT OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders DX11_MODEL 5_0 GLSL 130 )

#target_link_libraries(game PRIVATE SDL2main SDL2-static bgfx glm enet)
target_link_libraries(game PRIVATE 
    glm 
    bgfx 
    bx
    bimg
    
    example-common

    bgfx-shader



    ${ENET_LIBRARY}

    ${SDL2MAIN_LIBRARY} 
    ${SDL2_LIBRARY} 
    ${SDL2_IMAGE_INCLUDE_DIR})


#target_include_directories(game PRIVATE src "${SDL_DIR}/include" "${ENET_DIR}/include")
target_include_directories(game PRIVATE src 
    ${SDL2_INCLUDE_DIR} 
    ${ENET_INCLUDE_DIR} 
    ${SDL2_IMAGE_INCLUDE_DIR}

    ${STB_DIR}

    ${CMAKE_BINARY_DIR}/shaders
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/bgfx.cmake/bgfx/src
)

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})

