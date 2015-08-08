#ifndef _WIN32

#ifdef __APPLE__
#include <sys/_endian.h>
#elif defined __linux__
#include <endian.h>
#else
#include <sys/endian.h>
#endif

#endif

