cmake_minimum_required(VERSION 3.1)

project(SRM-Example VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

file(
	GLOB_RECURSE
	SOURCE_VAR
	Source/*.cpp
)

add_executable(SRM-Example ${SOURCE_VAR})

target_include_directories(
	SRM-Example 
	PRIVATE
	../SmartResourceManager/Include
)

target_link_libraries(
	SRM-Example
	SmartResourceManager_s
)