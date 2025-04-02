cmake_minimum_required(VERSION 3.19)

set(CMAKE_TOOLCHAIN_FILE "C:/local/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file" FORCE)

include(${CMAKE_TOOLCHAIN_FILE})

set(CMAKE_CXX_STANDARD 20)

set(VCPKG_DEFAULT_TRIPLET "x64-windows")

project(fgame)
find_package(OpenGL REQUIRED)

find_package(SDL2 CONFIG REQUIRED)

find_package(SDL2_image REQUIRED)

find_package(ImGui REQUIRED)

find_package(GLEW REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.h src/shaders/*.vert src/shaders/*.frag)

add_executable(${PROJECT_NAME} src/main.cpp ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_image::SDL2_image GLEW::GLEW OpenGL::GL imgui::imgui)


make_directory(${CMAKE_BINARY_DIR}/resources/shaders)
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/shaders/*")
foreach(SRC_FILE ${SRC_FILES})
	file(COPY ${SRC_FILE} DESTINATION ${CMAKE_BINARY_DIR}/resources/shaders)
	file(COPY ${SRC_FILE} DESTINATION ${CMAKE_BINARY_DIR}/Debug/resources/shaders)
	file(COPY ${SRC_FILE} DESTINATION ${CMAKE_BINARY_DIR}/Release/resources/shaders)
endforeach()

make_directory(${CMAKE_BINARY_DIR}/resources/textures)
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/textures/*")
foreach(SRC_FILE ${SRC_FILES})
	file(COPY ${SRC_FILE} DESTINATION ${CMAKE_BINARY_DIR}/resources/textures)
	file(COPY ${SRC_FILE} DESTINATION ${CMAKE_BINARY_DIR}/Debug/resources/textures)
	file(COPY ${SRC_FILE} DESTINATION ${CMAKE_BINARY_DIR}/Release/resources/textures)
endforeach()