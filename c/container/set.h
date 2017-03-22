
#ifndef __HANDY_C_CONTAINER_SET_H
#define __HANDY_C_CONTAINER_SET_H

#include <stdbool.h>
#include <stddef.h>
#include "shared_types.h"
#include "tree.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef CTreeNode* CSetIterator;

struct __c_set;
typedef struct __c_set CSet;


/**
 * constructor/destructor
 */
CSet* CSET_CreateSet(CSet** set, CCompare comp);
void CSET_DestroySet(CSet* set);

/**
 * element access
 */
CReferencePtr CSET_Reference(CSetIterator it);

/**
 * iterators
 */
CSetIterator CSET_Begin(CSet* set);
CSetIterator CSET_End(CSet* set);
void CSET_Forward(CSetIterator* it);
void CSET_Backward(CSetIterator* it);

/**
 * capacity
 */
bool CSET_Empty(CSet* set);
size_t CSET_Size(CSet* set);
size_t CSET_MaxSize(void);

/**
 * modifiers
 */
CSetIterator CSET_Insert(CSet* set, CReferencePtr data);
void CSET_Erase(CSet* set, CSetIterator it);
void CSET_Clear(CSet* set);

/**
 * algorithms
 */
CSetIterator CSET_Find(CSet* set, CReferencePtr data);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HANDY_C_CONTAINER_SET_H
