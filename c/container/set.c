
#include <stdlib.h>
#include <assert.h>
#include "set.h"

CSet* CSET_CreateSet(CSet** set, CCompare comp)
{
	if (!set || *set) {
        return NULL;
    }

    *set = (CSet*) malloc(sizeof(CSet));
    if (!(*set)) {
        return NULL;
    }

    if (!CTREE_CreateTree(&((*set)->repr), comp)) {
		FREE(*set);
		return NULL;
	}

    return *set;
}

void CSET_DestroySet(CSet* set)
{
	if (set) {
		CTREE_DestroyTree(set->repr);
		FREE(set);
	}
}

CReferencePtr CSET_Reference(CSetIterator* it)
{
	return (it ? CTREE_Reference((CTreeNode*)it) : NULL);
}

CSetIterator* CSET_Begin(CSet* set)
{
	return (set ? (CSetIterator*)CTREE_Begin(set->repr) : NULL);
}

CSetIterator* CSET_End(CSet* set)
{
	return (set ? (CSetIterator*)CTREE_End(set->repr) : NULL);
}

void CSET_Forward(CSetIterator** it)
{
	CTREE_Forward((CTreeNode**)it);
}

void CSET_Backward(CSetIterator** it)
{
	CTREE_Backward((CTreeNode**)it);
}

bool CSET_Empty(CSet* set)
{
	return (set ? CTREE_Empty(set->repr) : true);
}

size_t CSET_Size(CSet* set)
{
	return (set ? CTREE_Size(set->repr) : 0);
}

size_t CSET_MaxSize(void)
{
	return CTREE_MaxSize();
}

CSetIterator* CSET_Insert(CSet* set, CReferencePtr data)
{
	return (set ? (CSetIterator*)CTREE_InsertUnique(set->repr, data) : NULL);
}

void CSET_Erase(CSet* set, CSetIterator* it)
{
	if (set && it) {
		CTREE_Erase(set->repr, (CTreeNode*)it);
	}
}

void CSET_Clear(CSet* set)
{
	if (set) {
		CTREE_Clear(set->repr);
	}
}

CSetIterator* CSET_Find(CSet* set, CReferencePtr data)
{
	return (set ? (CSetIterator*)CTREE_Find(set->repr, data) : CSET_End(set));
}
