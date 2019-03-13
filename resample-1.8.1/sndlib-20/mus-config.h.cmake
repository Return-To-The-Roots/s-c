/* mus-config.h.  Generated from mus-config.h.in by configure.  */
#ifndef SNDLIB_CONFIG_H_LOADED
#define SNDLIB_CONFIG_H_LOADED

/* Define to `int' or something if <sys/types.h> doesn't define.  */
/* #undef mode_t */
/* #undef pid_t */
/* #undef size_t */
/* #undef off_t */

#define HAVE_GETCWD 1
#define HAVE_STRFTIME 1
#define HAVE_STRERROR 1
#define HAVE_ACCESS 0
#define HAVE_VSNPRINTF 1
#define HAVE_SNPRINTF 1
#define HAVE_MEMMOVE 1
#define HAVE_STRDUP 1
#define HAVE_FILENO 1
#define HAVE_COMPLEX_TRIG 1
#define HAVE_PATHCONF 0

#if defined _WIN32 || defined __CYGWIN__
#       undef LITTLE_ENDIAN
#       undef BIG_ENDIAN
#       undef BYTE_ORDER
#       define LITTLE_ENDIAN 1234
#       define BIG_ENDIAN    4321
#       define BYTE_ORDER    LITTLE_ENDIAN
#else
#       include <sys/param.h>
#endif // !_WIN32 && !__CYGWIN__

#if !defined(BYTE_ORDER) && defined(__BYTE_ORDER)
#define BYTE_ORDER __BYTE_ORDER
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN __LITTLE_ENDIAN
#endif /* LITTLE_ENDIAN */
#ifndef BIG_ENDIAN
#define BIG_ENDIAN __LITTLE_ENDIAN
#endif /* BIG_ENDIAN */
#endif /* BYTE_ORDER */

#if BYTE_ORDER != LITTLE_ENDIAN && BYTE_ORDER != BIG_ENDIAN
#       error "Sorry your Byteorder is not supported by this Library"
#endif // BYTE_ORDER != LITTLE_ENDIAN && BYTE_ORDER != BIG_ENDIAN

#if BYTE_ORDER == LITTLE_ENDIAN
#   define WORDS_BIGENDIAN 0
#else
#   define WORDS_BIGENDIAN 1
#endif // BYTE_ORDER != LITTLE_ENDIAN

#cmakedefine01 HAVE_FCNTL_H
#cmakedefine01 HAVE_LIMITS_H
#cmakedefine01 HAVE_STRING_H
#cmakedefine01 HAVE_UNISTD_H
#cmakedefine01 HAVE_STDBOOL_H
#cmakedefine01 HAVE_SYS_SOUNDCARD_H
#cmakedefine01 HAVE_MACHINE_SOUNDCARD_H
#cmakedefine01 HAVE_SYS_MIXER_H
#cmakedefine01 MUS_HAVE_USR_LIB_OSS
#cmakedefine01 MUS_HAVE_USR_LOCAL_LIB_OSS
#cmakedefine01 MUS_HAVE_OPT_OSS
#cmakedefine01 MUS_HAVE_VAR_LIB_OSS
#cmakedefine01 HAVE_LIBC_H
#cmakedefine01 HAVE_ALSA_ASOUNDLIB_H
#cmakedefine01 HAVE_STDINT_H

#define SIZEOF_OFF_T @SIZEOF_OFF_T@
#define SIZEOF_LONG @SIZEOF_LONG@
#define HAVE_DECL_ISNAN 1
#define HAVE_DECL_ISINF 1

#cmakedefine MUS_LINUX 1
#cmakedefine MUS_SGI 1
#cmakedefine MUS_ALPHA 1
#cmakedefine01 MUS_SUN
#cmakedefine MUS_OPENBSD 1
#cmakedefine01 MUS_NETBSD
#cmakedefine01 MUS_WINDOZE
#cmakedefine01 HAVE_OSS
#cmakedefine01 HAVE_ALSA
#cmakedefine01 HAVE_JACK
#cmakedefine01 HAVE_SAM_9407
#cmakedefine01 MUS_MAC_OSX
#cmakedefine MUS_ESD 1
#cmakedefine MUS_HPUX 1

#define HAVE_GUILE 0
#define HAVE_SCHEME 0
#define HAVE_RUBY 0
#define HAVE_FORTH 0
/* #undef HAVE_GAUCHE */
#define HAVE_EXTENSION_LANGUAGE 0
/* #undef SND_CONFIG_GET_ID_ARGS */
#define Float float
#define _FILE_OFFSET_BITS 64
/* #undef _LARGE_FILES */
/* #undef HAVE_GSL */
#define SNDLIB_USE_FLOATS 0
#define MUS_SAMPLE_BITS 24
/* #undef MUS_ESD_VERSION */
/* #undef MUS_AUDIOFILE_VERSION */
/* #undef HAVE_READLINE */
/* #undef HAVE_APPLICABLE_SMOB */
/* #undef HAVE_SCM_REMEMBER_UPTO_HERE */
/* #undef HAVE_SCM_MAKE_REAL */
/* #undef HAVE_SCM_OBJECT_TO_STRING */
/* #undef HAVE_SCM_NUM2LONG_LONG */
/* #undef HAVE_SCM_C_MAKE_VECTOR */
/* #undef HAVE_SCM_C_DEFINE */
/* #undef HAVE_SCM_C_DEFINE_GSUBR */
/* #undef HAVE_SCM_C_EVAL_STRING */
/* #undef HAVE_SCM_NUM2INT */
/* #undef HAVE_SCM_LIST_N */
/* #undef HAVE_SCM_STR2SYMBOL */
/* #undef HAVE_SCM_T_CATCH_BODY */
/* #undef HAVE_SCM_TO_SIGNED_INTEGER */
/* #undef HAVE_SCM_C_MAKE_RECTANGULAR */
/* #undef HAVE_SCM_CAR */
/* #undef HAVE_SCM_FROM_LOCALE_KEYWORD */
/* #undef HAVE_SCM_IS_VECTOR */
/* #undef HAVE_SCM_IS_SIMPLE_VECTOR */
/* #undef HAVE_RB_GC_DISABLE */
/* #undef HAVE_RB_ARY_DUP */
/* #undef WITH_MODULES */
/* #undef HAVE_KAUDIODEVICEPROPERTYTRANSPORTTYPE */
/* #undef HAVE_KLINEARPCMFORMATFLAGISNONINTERLEAVED */
/* #undef WITH_HOBBIT */

#define MUS_OUT_FORMAT MUS_LFLOAT
#define USE_SND 0
#define MUS_DEBUGGING 0

#endif
