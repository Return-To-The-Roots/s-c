find_package(Boost 1.55 COMPONENTS filesystem system program_options REQUIRED)
set(SRC_FILES getopt.cpp getopt_long.cpp sound-convert.cpp)
ADD_EXECUTABLE(sound-convert ${SRC_FILES})

TARGET_LINK_LIBRARIES(sound-convert siedler2 s25util ${Boost_LIBRARIES} nowide-static)

SET(_OUTPUT_DIR "${CMAKE_BINARY_DIR}/${RTTR_BINDIR}/RTTR")	
SET_TARGET_PROPERTIES(sound-convert PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "${_OUTPUT_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${_OUTPUT_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${_OUTPUT_DIR}"
)

INSTALL(TARGETS sound-convert DESTINATION ${RTTR_BINDIR}/RTTR)
if(ClangFormat_FOUND)
    add_clangFormat_files(${SRC_FILES})
endif()
