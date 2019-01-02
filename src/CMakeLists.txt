find_package(Boost 1.55 REQUIRED COMPONENTS filesystem program_options)
set(SRC_FILES sound-convert.cpp)

add_executable(sound-convert ${SRC_FILES})
target_link_libraries(sound-convert PRIVATE siedler2 s25util Boost::filesystem Boost::program_options nowide::static)

install(TARGETS sound-convert DESTINATION ${RTTR_EXTRA_BINDIR})
if(ClangFormat_FOUND)
    add_clangFormat_files(${SRC_FILES})
endif()
