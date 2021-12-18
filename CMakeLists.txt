cmake_minimum_required(VERSION 3.1)

project(AssetSupplier)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS TRUE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(
	GLOB_RECURSE
	SOURCE_VAR
	src/*.cpp
)

add_subdirectory(external/assimp)
add_subdirectory(external/spdlog)

add_executable(AssetSupplier ${SOURCE_VAR})

target_include_directories(
	AssetSupplier 
	PRIVATE 
	external/assimp/include
	external/spdlog/include
)

target_link_libraries(
	AssetSupplier 
	assimp
	spdlog
)