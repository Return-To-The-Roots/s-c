#################################################################################
### $Id: CMakeLists.txt 6461 2010-05-31 11:46:20Z FloSoft $
#################################################################################

ADD_EXECUTABLE(s-c_resample resample.c filterkit.c resamplesubs.c sndlibextra.c)

SET(s-c_resample_LIBS resample-sndlib-20)
IF (NOT MSVC)
	SET(s-c_resample_LIBS "${s-c_resample_LIBS} m")
ENDIF()

TARGET_LINK_LIBRARIES(s-c_resample ${s-c_resample_LIBS})

IF ( "${COMPILEFOR}" STREQUAL "windows" AND NOT MSVC)
	ADD_CUSTOM_COMMAND(TARGET s-c_resample POST_BUILD COMMAND if [ -f s-c_resample.exe ] \; then cp -v s-c_resample.exe s-c_resample \; fi)
ENDIF ( "${COMPILEFOR}" STREQUAL "windows" AND NOT MSVC)
		
IF (NOT MSVC)
	ADD_CUSTOM_COMMAND(TARGET s-c_resample POST_BUILD COMMAND cp -v s-c_resample ../../../RTTR/s-c_resample)
ENDIF()
		
INSTALL(TARGETS s-c_resample DESTINATION ${DATADIR}/RTTR)

#################################################################################
