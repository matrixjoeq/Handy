
#ifndef __HANDY_ALGORITHM_IS_PRIME_H
#define __HANDY_ALGORITHM_IS_PRIME_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

inline bool is_prime(int32_t number)
{
    number = abs(number);
    if (number == 0 || number == 1) return true;

    uint32_t divisor = 0;
    for (divisor = number / 2; number % divisor != 0; --divisor) ;

    return (divisor == 1);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __HANDY_ALGORITHM_IS_PRIME_H
