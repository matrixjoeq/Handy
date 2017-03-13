
#ifndef __HANDY_C_CONTAINER_VECTOR_H
#define __HANDY_C_CONTAINER_VECTOR_H

#include <stdbool.h>
#include <stddef.h>
#include "shared_types.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct __c_vector {
    CReferencePtr start;
    CReferencePtr finish;
    CReferencePtr end_of_storage;
} CVector;


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HANDY_C_CONTAINER_VECTOR_H
