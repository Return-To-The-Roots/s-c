find_package(Boost 1.55 REQUIRED COMPONENTS filesystem system program_options)
set(SRC_FILES getopt.cpp getopt_long.cpp sound-convert.cpp)
ADD_EXECUTABLE(sound-convert ${SRC_FILES})

TARGET_LINK_LIBRARIES(sound-convert siedler2 s25util ${Boost_LIBRARIES} nowide-static)

INSTALL(TARGETS sound-convert DESTINATION ${RTTR_BINDIR}/RTTR)
if(ClangFormat_FOUND)
    add_clangFormat_files(${SRC_FILES})
endif()
