cmake_minimum_required(VERSION 3.1)

project(AssetSupplier)

file(
	GLOB_RECURSE
	SOURCE_VAR
	src/*.cpp
)

add_subdirectory(external/assimp)

add_executable(AssetSupplier ${SOURCE_VAR})

target_include_directories(AssetSupplier PRIVATE external/assimp/include)
target_link_libraries(AssetSupplier assimp)