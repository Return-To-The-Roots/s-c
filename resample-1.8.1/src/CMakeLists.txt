
ADD_EXECUTABLE(s-c_resample resample.c filterkit.c resamplesubs.c sndlibextra.c)

IF (NOT MSVC)
	TARGET_LINK_LIBRARIES(s-c_resample resample-sndlib-20 m)
ELSE()
	TARGET_LINK_LIBRARIES(s-c_resample resample-sndlib-20)
ENDIF()

IF ( "${COMPILEFOR}" STREQUAL "windows" AND NOT MSVC)
	ADD_CUSTOM_COMMAND(TARGET s-c_resample POST_BUILD COMMAND if [ -f s-c_resample.exe ] \; then cp -v s-c_resample.exe s-c_resample \; fi)
ENDIF ( "${COMPILEFOR}" STREQUAL "windows" AND NOT MSVC)
		
IF (NOT MSVC)
	ADD_CUSTOM_COMMAND(TARGET s-c_resample POST_BUILD COMMAND cp -v s-c_resample ../../../RTTR/s-c_resample)
ENDIF()
		
INSTALL(TARGETS s-c_resample DESTINATION ${DATADIR}/RTTR)

#################################################################################
