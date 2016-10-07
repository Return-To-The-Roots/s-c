
IF(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	SET(MUS_WINDOZE TRUE)
ELSEIF(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	SET(MUS_LINUX TRUE)
ELSEIF(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
	SET(MUS_MAC_OSX TRUE)
ELSEIF(${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
	SET(MUS_OSS TRUE)
ELSE()
	MESSAGE(FATAL_ERROR "Unknown system: ${CMAKE_SYSTEM_NAME}")
ENDIF()

INCLUDE(CheckIncludeFile)

CHECK_INCLUDE_FILE(fcntl.h HAVE_FCNTL_H)
CHECK_INCLUDE_FILE(limits.h HAVE_LIMITS_H)
CHECK_INCLUDE_FILE(string.h HAVE_STRING_H)
CHECK_INCLUDE_FILE(unistd.h HAVE_UNISTD_H)
CHECK_INCLUDE_FILE(stdbool.h HAVE_STDBOOL_H)
CHECK_INCLUDE_FILE(sys/soundcard.h HAVE_SYS_SOUNDCARD_H)
CHECK_INCLUDE_FILE(machine/soundcard.h HAVE_MACHINE_SOUNDCARD_H)
CHECK_INCLUDE_FILE(sys/mixer.h HAVE_SYS_MIXER_H)
CHECK_INCLUDE_FILE(/usr/lib/oss/include/sys/soundcard.h MUS_HAVE_USR_LIB_OSS)
CHECK_INCLUDE_FILE(/usr/local/lib/oss/include/sys/soundcard.h MUS_HAVE_USR_LOCAL_LIB_OSS)
CHECK_INCLUDE_FILE(/opt/oss/include/sys/soundcard.h MUS_HAVE_OPT_OSS)
CHECK_INCLUDE_FILE(/var/lib/oss/include/sys/soundcard.h MUS_HAVE_VAR_LIB_OSS)
CHECK_INCLUDE_FILE(libc.h HAVE_LIBC_H)
CHECK_INCLUDE_FILE(alsa/asoundlib.h HAVE_ALSA_ASOUNDLIB_H)
CHECK_INCLUDE_FILE(byteswap.h HAVE_BYTESWAP_H)
CHECK_INCLUDE_FILE(stdint.h HAVE_STDINT_H)

CONFIGURE_FILE(mus-config.h.cmake mus-config.h @ONLY)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
# Avoid warning in some GCC versions
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	ADD_DEFINITIONS(-Wno-strict-overflow)
endif()

ADD_LIBRARY(resample-sndlib-20 STATIC audio.c sound.c io.c headers.c)
		
#################################################################################
