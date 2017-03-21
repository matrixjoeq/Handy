
#ifndef __HANDY_C_CONTAINER_SHARED_TYPES_H
#define __HANDY_C_CONTAINER_SHARED_TYPES_H

#ifndef GTEST_UNIT_TEST
#define STATIC static
#define INLINE inline
#else
#define STATIC
#define INLINE
#endif

typedef void* CReferencePtr;
typedef void (*CUnaryFunction)(CReferencePtr data);

// return true if data matches condition
typedef bool (*CUnaryPredicate)(CReferencePtr data);

// return true if lhs < rhs
typedef bool (*CCompare)(CReferencePtr lhs, CReferencePtr rhs);

typedef struct __c_iterator {
    void (*increment)(struct __c_iterator*);
    void (*decrement)(struct __c_iterator*);
} CIterator;

// general macro
#define FREE(x) \
    do { \
        if ((x)) { \
            free((x)); \
            (x) = NULL; \
        } \
    } while (0)

#define UNUSE(x) (void)(x)
#define ARRAY_LENGTH(__array) sizeof(__array)/sizeof(__array[0])
#define ARRAY_FOREACH(__array, __index) for (uint32_t __index = 0; __index < ARRAY_LENGTH(__array); ++__index)

// for container
#define CREATE_DATA(x, type, value) \
    type* x = (type*) malloc(sizeof(type)); \
    memcpy(x, &(value), sizeof(type))

#endif // __HANDY_C_CONTAINER_SHARED_TYPES_H
