#include "oil.h"

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
