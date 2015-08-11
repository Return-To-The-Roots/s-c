#################################################################################
### $Id: CMakeLists.txt 6942 2010-12-24 07:50:41Z FloSoft $
#################################################################################

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/libsiedler2/src")
# libSiedler2 headers use boost
FIND_PACKAGE(Boost 1.54.0 REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

ADD_EXECUTABLE(sound-convert getopt.cpp getopt_long.cpp main.cpp tempname.cpp)

TARGET_LINK_LIBRARIES(sound-convert siedler2)
		
IF ( "${COMPILEFOR}" STREQUAL "windows" AND NOT MSVC)
	ADD_CUSTOM_COMMAND(TARGET sound-convert POST_BUILD COMMAND if [ -f sound-convert.exe ] \; then cp -v sound-convert.exe sound-convert \; fi)
ENDIF ( "${COMPILEFOR}" STREQUAL "windows" AND NOT MSVC)
		
IF (MSVC)
	SET_TARGET_PROPERTIES(sound-convert PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/../../RTTR/"
		RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}/../../RTTR/"
	)
ELSE()
	ADD_CUSTOM_COMMAND(TARGET sound-convert POST_BUILD COMMAND cp -v sound-convert ../../RTTR/sound-convert)
ENDIF()
		
INSTALL(TARGETS sound-convert DESTINATION ${DATADIR}/RTTR)

#################################################################################
