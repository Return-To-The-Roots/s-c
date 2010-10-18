#################################################################################
### $Id: CMakeLists.txt 6461 2010-05-31 11:46:20Z FloSoft $
#################################################################################

ADD_EXECUTABLE(sound-convert getopt.cpp getopt_long.cpp main.cpp tempname.cpp)

TARGET_LINK_LIBRARIES(sound-convert siedler2)
		
IF ( "${COMPILEFOR}" STREQUAL "windows")
	ADD_CUSTOM_COMMAND(TARGET sound-convert POST_BUILD COMMAND if [ -f sound-convert.exe ] \; then cp -v sound-convert.exe sound-convert \; fi)
ENDIF ( "${COMPILEFOR}" STREQUAL "windows")
		
ADD_CUSTOM_COMMAND(TARGET sound-convert POST_BUILD COMMAND cp -v sound-convert ../../RTTR/sound-convert)
		
INSTALL(TARGETS sound-convert DESTINATION ${DATADIR}/RTTR)

#################################################################################
