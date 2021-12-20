cmake_minimum_required(VERSION 3.1)

project(SmartResourceManager VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

file(
	GLOB_RECURSE
	SOURCE_VAR
	Source/*.cpp
	External/*.cpp
)

add_library(SmartResourceManager SHARED ${SOURCE_VAR})
add_library(SmartResourceManager_s STATIC ${SOURCE_VAR})

target_include_directories(
	SmartResourceManager
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/Include/SRM
		${CMAKE_CURRENT_SOURCE_DIR}/External/FileWatcher/Include
)

target_include_directories(
	SmartResourceManager_s
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/Include/SRM
		${CMAKE_CURRENT_SOURCE_DIR}/External/FileWatcher/Include
)