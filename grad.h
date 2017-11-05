#include "recipe.h"
#include <math.h>

void init_decision(set_id *set)
{
	for (int i = 0; i < set->size; i++)
		set->d.w[i] = init_weight;
	set->w_soap = init_weight * set->size;
}

bool quality_check(set_id *set, int i, TFQuality delta)
{
	if ((delta < normal_oil.internal[i].min && 
		set->d.delta[i] < normal_oil.internal[i].min &&
		delta < set->d.delta[i]) ||
		(delta > normal_oil.internal[i].max && 
		set->d.delta[i] > normal_oil.internal[i].max &&
		delta > set->d.delta[i]))
		return false;
	return true;
}

void quality_set(set_id *set)
{
	memset(set->d.q, 0, t_max * sizeof(TDQuality));
	for (int i = 0; i < t_max; i++) {
		for (int j = 0; j < set->size; j++)
			set->d.q[i] += set->d.w[j] * oil[set->id[j]].internal[i];
		set->d.delta[i] = set->d.q[i] / set->w_soap;
	}
}

bool quality_step(set_id *set, TStep step, int id)
{
	if (set->d.w[id] + step < 0.0 ||
		set->d.w[id] + step > max_weight)
		return false;

	bool fl = true;
	bool fl_eq = false;
	TDQuality q[t_max];
	TFQuality delta[t_max];
	
	for (int i = 0; i < t_max && fl; i++) {
		q[i] = set->d.q[i] + step * oil[set->id[id]].internal[i];
		delta[i] = q[i] / (set->w_soap + step);
		fl = quality_check(set, i, delta[i]);
		if (delta[i] != set->d.delta[i])
			fl_eq = true;
	}

	if (fl && fl_eq) {
		memcpy(set->d.delta, delta, sizeof(delta));
		memcpy(set->d.q, q, sizeof(q));
	}
	
	return fl && fl_eq;
}

void grad(set_id *set)
{
	init_decision(set);
	quality_set(set);
	
	TStep step = max_step;
	while (fabs(step) > min_step) {
		for (int i = 0; i < set->size; i++) {
			while (quality_step(set, step, i)) {
				set->w_soap += step;
				set->d.w[i] += step;
			}
		}
		step = (-step) / 2;
	}

	print_recipe(set);
}