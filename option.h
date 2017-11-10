#include "oil.h"
#include <math.h>

typedef int 	TIter;
typedef float 	TStep;
typedef float 	TWeight;
typedef float	TFQuality;
typedef double 	TDQuality;

TWeight min_weight = 0.0;
TWeight max_weight = 400.0;
TWeight init_weight = 200.0;

TStep max_step = 200.0;
TStep min_step = 0.005;
int step_delta = 3;

// delete flag
bool fl_end = false;
typedef enum TCheckDecision {
	tcd_null 	= -1,
	tcd_ok 		= 0,
	tcd_next 	= 1,
	tcd_eq 		= 2,
	tcd_bad 	= 3,
	tcd_max,
}TCheckDecision;

typedef struct TDecision {
	TWeight		*w;
	TDQuality	q[t_max];
	TFQuality	delta[t_max];
}TDecision;

typedef struct set_id {
	int 		size;
	TWeight 	w_soap;
	TIdOil		*id;
	TDecision	d;
}set_id;

set_id init_set(int size)
{
	set_id set = {
		.size = size, 
		.id = malloc(size * sizeof(TIdOil)),
		.d.w = malloc(size * sizeof(TWeight)),
	};
	return set;
}

// repair type
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