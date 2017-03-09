

#ifndef __HANDY_C_UTIL_UTIL_H
#define __HANDY_C_UTIL_UTIL_H

#include <stddef.h>

char* CUTIL_GenerateRandomString(char *buf, size_t size);
char* CUTIL_GenerateRandomStringWithPrefix(const char* prefix, char *buf, size_t size);
char* CUTIL_GenerateRandomStringWithSurfix(const char* surfix, char* buf, size_t size);

#endif // __HANDY_C_UTIL_UTIL_H
