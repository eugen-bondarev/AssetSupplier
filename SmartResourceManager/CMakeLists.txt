cmake_minimum_required(VERSION 3.1)

project(SmartResourceManager VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

file(
	GLOB_RECURSE
	SOURCE_VAR
	Source/*.cpp
)

add_library(SmartResourceManager SHARED ${SOURCE_VAR})
add_library(SmartResourceManager_s STATIC ${SOURCE_VAR})

target_include_directories(
	SmartResourceManager 
	PRIVATE
	Source/External/FileWatcher/include
	Include/SRM
)

target_include_directories(
	SmartResourceManager_s
	PRIVATE
	Source/External/FileWatcher/include
	Include/SRM
)