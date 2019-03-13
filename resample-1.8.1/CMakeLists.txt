
cmake_minimum_required(VERSION 3.8)
project(resample-1.8.1)

################################################################################

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_compile_options(/W2)
	add_compile_options(/wd"4244") # conversion double to x
ELSE()
	set(CMAKE_C_STANDARD 11)
	set(CMAKE_C_STANDARD_REQUIRED ON)
ENDIF()

add_subdirectory( sndlib-20 )
add_subdirectory( src )
