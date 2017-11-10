#include "oil.h"
#include <math.h>

typedef int 	TIter;
typedef float 	TStep;
typedef float 	TWeight;
typedef double 	TDQuality;

typedef enum TCheckDecision {
	tcd_null 	= -1,
	tcd_ok 		= 0,
	tcd_next 	= 1,
	tcd_eq 		= 2,
	tcd_bad 	= 3,
	tcd_max,
} TCheckDecision;

typedef struct TDecision {
	TWeight		*w;
	TDQuality	q[t_max];
	TDQuality	delta[t_max];
} TDecision;

typedef struct set_id {
	int 		size;
	TWeight 	w_soap;
	TIdOil		*id;
	TDecision	d;
} set_id;

set_id init_set(int size)
{
	set_id set = {
		.size = size, 
		.id = malloc(size * sizeof(TIdOil)),
		.d.w = malloc(size * sizeof(TWeight)),
	};
	return set;
}

bool copy_set(set_id *set, int *idx)
{
	if (NULL != set->id && NULL != set->d.w) {
		memcpy(set->id, idx, set->size * sizeof(int));
		return true;
	}
	return false;
}

void free_set(set_id *set)
{
	set->size = 0;
	free(set->id);
	free(set->d.w);
	set->id = NULL;
	set->d.w = NULL;
}