
ADD_EXECUTABLE(s-c_resample resample.c filterkit.c resamplesubs.c sndlibextra.c)

IF (NOT MSVC)
	TARGET_LINK_LIBRARIES(s-c_resample resample-sndlib-20 m)
ELSE()
	TARGET_LINK_LIBRARIES(s-c_resample resample-sndlib-20)
ENDIF()

IF ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" AND NOT MSVC)
	ADD_CUSTOM_COMMAND(TARGET s-c_resample POST_BUILD COMMAND if [ -f s-c_resample.exe ] \; then cp -v s-c_resample.exe s-c_resample \; fi)
ENDIF ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" AND NOT MSVC)
		
IF (MSVC)
	SET_TARGET_PROPERTIES(s-c_resample PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/RTTR"
		RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/RTTR"
		RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/RTTR"
	)
ELSE()
	ADD_CUSTOM_COMMAND(TARGET s-c_resample POST_BUILD COMMAND cp -v $<TARGET_FILE:s-c_resample> ../../../RTTR/s-c_resample)
ENDIF()
		
INSTALL(TARGETS s-c_resample DESTINATION ${RTTR_LIBDIR}/RTTR)

#################################################################################
