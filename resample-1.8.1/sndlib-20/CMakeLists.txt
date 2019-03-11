
IF(WIN32 OR CYGWIN)
	SET(MUS_WINDOZE TRUE)
ELSEIF(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	SET(MUS_LINUX TRUE)
ELSEIF(APPLE)
	SET(MUS_MAC_OSX TRUE)
ELSEIF(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
	SET(MUS_OSS TRUE)
ELSE()
	MESSAGE(FATAL_ERROR "Unknown system: ${CMAKE_SYSTEM_NAME}")
ENDIF()

INCLUDE(CheckIncludeFile)
include (CheckTypeSize)

# We just assume all compilers have this to avoid the checks
set(HAVE_LIMITS_H 1)
set(HAVE_STRING_H 1)
set(HAVE_STDBOOL_H 1)
set(HAVE_STDINT_H 1)

CHECK_INCLUDE_FILE(fcntl.h HAVE_FCNTL_H)
CHECK_INCLUDE_FILE(unistd.h HAVE_UNISTD_H)
CHECK_INCLUDE_FILE(sys/mixer.h HAVE_SYS_MIXER_H)
CHECK_INCLUDE_FILE(libc.h HAVE_LIBC_H)
CHECK_INCLUDE_FILE(alsa/asoundlib.h HAVE_ALSA_ASOUNDLIB_H)
CHECK_INCLUDE_FILE(byteswap.h HAVE_BYTESWAP_H)
CHECK_INCLUDE_FILE(sys/soundcard.h HAVE_SYS_SOUNDCARD_H)
CHECK_INCLUDE_FILE(machine/soundcard.h HAVE_MACHINE_SOUNDCARD_H)
CHECK_INCLUDE_FILE(/usr/lib/oss/include/sys/soundcard.h MUS_HAVE_USR_LIB_OSS)
CHECK_INCLUDE_FILE(/usr/local/lib/oss/include/sys/soundcard.h MUS_HAVE_USR_LOCAL_LIB_OSS)
CHECK_INCLUDE_FILE(/opt/oss/include/sys/soundcard.h MUS_HAVE_OPT_OSS)
CHECK_INCLUDE_FILE(/var/lib/oss/include/sys/soundcard.h MUS_HAVE_VAR_LIB_OSS)

CHECK_TYPE_SIZE("off_t" SIZEOF_OFF_T LANGUAGE C)
CHECK_TYPE_SIZE("long" SIZEOF_LONG LANGUAGE C)

CONFIGURE_FILE(mus-config.h.cmake mus-config.h @ONLY)

add_library(resample-sndlib-20 STATIC audio.c sound.c io.c headers.c)
target_include_directories(resample-sndlib-20 PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

include(EnableWarnings)
enable_warnings(resample-sndlib-20)

# Avoid warning in some GCC versions
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(resample-sndlib-20 PRIVATE -Wno-strict-overflow)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  # To many to fix
	target_compile_options(resample-sndlib-20 PRIVATE -Wno-unused-parameter)
endif()

FILE(GLOB SRC_FILES *.c *.h)
if(ClangFormat_FOUND)
    add_clangFormat_files(${SRC_FILES})
endif()
