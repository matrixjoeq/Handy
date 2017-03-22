

#include <stdlib.h>
#include <assert.h>
#include "vector.h"

struct __c_vector {
    CReferencePtr start;
    CReferencePtr finish;
    CReferencePtr end_of_storage;
};
