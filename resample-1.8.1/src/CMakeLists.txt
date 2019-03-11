ADD_EXECUTABLE(s-c_resample resample.c filterkit.c resamplesubs.c sndlibextra.c)

TARGET_LINK_LIBRARIES(s-c_resample PRIVATE resample-sndlib-20)
IF (NOT MSVC)
	TARGET_LINK_LIBRARIES(s-c_resample PUBLIC m)
ENDIF()

INSTALL(TARGETS s-c_resample DESTINATION ${RTTR_EXTRA_BINDIR})

FILE(GLOB SRC_FILES *.c *.h)
if(ClangFormat_FOUND)
    add_clangFormat_files(${SRC_FILES})
endif()
