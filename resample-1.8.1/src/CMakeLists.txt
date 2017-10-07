ADD_EXECUTABLE(s-c_resample resample.c filterkit.c resamplesubs.c sndlibextra.c)

TARGET_LINK_LIBRARIES(s-c_resample resample-sndlib-20)
IF (NOT MSVC)
	TARGET_LINK_LIBRARIES(s-c_resample m)
ENDIF()
		
INSTALL(TARGETS s-c_resample DESTINATION ${RTTR_BINDIR}/RTTR)
