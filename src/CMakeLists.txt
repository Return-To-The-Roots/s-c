
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/libsiedler2/src")
# libSiedler2 headers use boost
FIND_PACKAGE(Boost 1.55.0 COMPONENTS iostreams REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

ADD_EXECUTABLE(sound-convert getopt.cpp getopt_long.cpp main.cpp tempname.cpp)

TARGET_LINK_LIBRARIES(sound-convert siedler2 ${Boost_LIBRARIES})
		
IF ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" AND NOT MSVC)
	ADD_CUSTOM_COMMAND(TARGET sound-convert POST_BUILD COMMAND if [ -f sound-convert.exe ] \; then cp -v sound-convert.exe sound-convert \; fi)
ENDIF ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" AND NOT MSVC)
		
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
