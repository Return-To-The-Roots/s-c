
cmake_minimum_required(VERSION 3.8)
PROJECT(resample-1.8.1)

################################################################################

IF (NOT MSVC)
	add_compile_options("-std=c99")
ELSE (NOT MSVC)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
	ADD_DEFINITIONS(/W2)
	ADD_DEFINITIONS(/wd"4244") # conversion double to x
ENDIF (NOT MSVC)

ADD_SUBDIRECTORY( sndlib-20 )
ADD_SUBDIRECTORY( src )
