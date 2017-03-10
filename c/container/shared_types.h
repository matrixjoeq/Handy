
#ifndef __HANDY_C_CONTAINER_SHARED_TYPES_H
#define __HANDY_C_CONTAINER_SHARED_TYPES_H

#ifndef UNIT_TEST
#define STATIC static
#define INLINE inline
#else
#define STATIC
#define INLINE
#endif

typedef void* CReferencePtr;
typedef void* CUserDataPtr;
typedef void (*CDestroyHandler)(CReferencePtr data);
typedef void (*CUnaryFunction)(CReferencePtr data);
typedef void (*CBinaryFunction)(CReferencePtr data, CUserDataPtr userData);
typedef bool (*CPredicate)(CReferencePtr lhs, CReferencePtr rhs);

// return true if lhs < rhs
typedef bool (*CCompare)(CReferencePtr lhs, CReferencePtr rhs);

#define FREE(x) \
    do { \
        if ((x)) { \
            free((x)); \
            (x) = NULL; \
        } \
    } while (0)

#endif // __HANDY_C_CONTAINER_SHARED_TYPES_H
