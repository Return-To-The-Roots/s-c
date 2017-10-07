
PROJECT(sound-convert)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
CMAKE_POLICY(SET CMP0003 NEW)

################################################################################

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")

# ensure out of source build
INCLUDE(MacroEnsureOutOfSourceBuild)
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build. Please go to the build directory and run './cmake.sh [options]' there.")

################################################################################
if(COMMAND rttr_set_output_dir)
    rttr_set_output_dir(RUNTIME ${RTTR_BINDIR}/RTTR)
endif()

ADD_SUBDIRECTORY( resample-1.8.1 )
ADD_SUBDIRECTORY( src )

#################################################################################
