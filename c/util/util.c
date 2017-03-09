
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "util.h"

static void generateRandomSeed(void)
{
    static bool inited = false;

    if (!inited) {
        time_t now = time(NULL);
        srandom((unsigned int)now);
        inited = true;
    }
}

char* CUTIL_GenerateRandomString(char *buf, size_t size)
{
    static const char alpha_numbers[] = "0123456789"
                                        "abcdefghijklmnopqrstuvwxyz"
                                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const size_t max_size = sizeof(alpha_numbers) - 1;

    if (!buf) {
        return NULL;
    }

    generateRandomSeed();
    char *p = buf;
    for (size_t i = 0; i < size; ++i, ++p) {
        *p = alpha_numbers[random() % max_size];
    }

    return buf;
}

char* CUTIL_GenerateRandomStringWithPrefix(const char* prefix, char *buf, size_t size)
{
    if (prefix) {
        size_t length = strlen(prefix);
        if (length > size) {
            return NULL;
        }

        strncpy(buf, prefix, length);
        CUTIL_GenerateRandomString(buf + length, size - length);
    }
    else {
        CUTIL_GenerateRandomString(buf, size);
    }

    return buf;
}

char* CUTIL_GenerateRandomStringWithSurfix(const char* surfix, char* buf, size_t size)
{
    if (surfix) {
        size_t length = strlen(surfix);
        if (length > size) {
            return NULL;
        }

        strncpy(buf + size - length, surfix, length);
        CUTIL_GenerateRandomString(buf, size - length);
    }
    else {
        CUTIL_GenerateRandomString(buf, size);
    }

    return buf;
}
