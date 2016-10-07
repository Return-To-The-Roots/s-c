
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/..")
# libSiedler2 headers use boost
FIND_PACKAGE(Boost 1.55.0 COMPONENTS iostreams system filesystem REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

ADD_EXECUTABLE(sound-convert getopt.cpp getopt_long.cpp main.cpp)

TARGET_LINK_LIBRARIES(sound-convert siedler2 s25util ${Boost_LIBRARIES})
		
IF ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" AND NOT MSVC)
	ADD_CUSTOM_COMMAND(TARGET sound-convert POST_BUILD COMMAND if [ -f sound-convert.exe ] \; then cp -v sound-convert.exe sound-convert \; fi)
ENDIF ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" AND NOT MSVC)
		
IF (MSVC)
	SET_TARGET_PROPERTIES(sound-convert PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/RTTR"
		RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/RTTR"
		RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/RTTR"
	)
ELSE()
	ADD_CUSTOM_COMMAND(TARGET sound-convert POST_BUILD COMMAND cp -v $<TARGET_FILE:sound-convert> ../../RTTR/sound-convert)
ENDIF()
		
INSTALL(TARGETS sound-convert DESTINATION ${RTTR_LIBDIR}/RTTR)

#################################################################################
