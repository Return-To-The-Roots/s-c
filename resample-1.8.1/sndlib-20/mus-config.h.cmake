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
/*#define HAVE_ACCESS 1 */
#define HAVE_VSNPRINTF 1
#define HAVE_SNPRINTF 1
#define HAVE_MEMMOVE 1
#define HAVE_STRDUP 1
#define HAVE_FILENO 1
#define HAVE_COMPLEX_TRIG 1

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

#if BYTE_ORDER != LITTLE_ENDIAN && BYTE_ORDER != BIG_ENDIAN
#       error "Sorry your Byteorder is not supported by this Library"
#endif // BYTE_ORDER != LITTLE_ENDIAN && BYTE_ORDER != BIG_ENDIAN

#if BYTE_ORDER == LITTLE_ENDIAN
#   undef WORDS_BIGENDIAN
#else
#   define WORDS_BIGENDIAN 1
#endif // BYTE_ORDER != LITTLE_ENDIAN

#cmakedefine HAVE_FCNTL_H 1
#cmakedefine HAVE_LIMITS_H 1
#cmakedefine HAVE_STRING_H 1
#cmakedefine HAVE_UNISTD_H 1
#cmakedefine HAVE_STDBOOL_H 1
#cmakedefine HAVE_SYS_SOUNDCARD_H 1
#cmakedefine HAVE_MACHINE_SOUNDCARD_H 1
#cmakedefine HAVE_SYS_MIXER_H 1
#cmakedefine MUS_HAVE_USR_LIB_OSS 1
#cmakedefine MUS_HAVE_USR_LOCAL_LIB_OSS 1
#cmakedefine MUS_HAVE_OPT_OSS 1
#cmakedefine MUS_HAVE_VAR_LIB_OSS 1
#cmakedefine HAVE_LIBC_H 1
#cmakedefine HAVE_ALSA_ASOUNDLIB_H 1
#cmakedefine HAVE_BYTESWAP_H 1 
#cmakedefine HAVE_STDINT_H 1

#define SIZEOF_OFF_T 8
#define HAVE_DECL_ISNAN 1
#define HAVE_DECL_ISINF 1

#cmakedefine MUS_LINUX 1
#cmakedefine MUS_SGI 1
#cmakedefine MUS_ALPHA 1
#cmakedefine MUS_SUN 1
#cmakedefine MUS_OPENBSD 1
#cmakedefine MUS_NETBSD 1
#cmakedefine MUS_WINDOZE 1
#cmakedefine HAVE_OSS 1
#cmakedefine HAVE_ALSA 1
#cmakedefine HAVE_JACK 1
#cmakedefine HAVE_SAM_9407 1
#cmakedefine MUS_MAC_OSX 1
#cmakedefine MUS_ESD 1
#cmakedefine MUS_HPUX 1

#define HAVE_GUILE 0
/* #undef HAVE_SCHEME */
/* #undef HAVE_RUBY */
/* #undef HAVE_FORTH */
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

#endif
