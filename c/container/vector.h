
#ifndef __HANDY_C_CONTAINER_VECTOR_H
#define __HANDY_C_CONTAINER_VECTOR_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef void* CVectorDataPtr;

typedef struct __c_vector {
    CVectorDataPtr start;
    CVectorDataPtr finish;
    CVectorDataPtr end_of_storage;
} CVector;


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HANDY_C_CONTAINER_VECTOR_H
