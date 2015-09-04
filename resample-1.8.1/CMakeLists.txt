
PROJECT(resample-1.8.1)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
CMAKE_POLICY(SET CMP0003 NEW)

################################################################################

IF (NOT MSVC)
	ADD_FLAGS(CMAKE_C_FLAGS "-std=c99")
ELSE (NOT MSVC)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
	ADD_DEFINITIONS(/W2)
	ADD_DEFINITIONS(/wd"4244") # conversion double to x
ENDIF (NOT MSVC)

ADD_SUBDIRECTORY( sndlib-20 )
ADD_SUBDIRECTORY( src )

#################################################################################
