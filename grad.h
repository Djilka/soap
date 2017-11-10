#ifndef GRAD_H
#define GRAD_H

#include "recipe.h"

void init_decision(set_id *set)
{
	for (int i = 0; i < set->size; i++)
		set->d.w[i] = init_weight;
	set->w_soap = init_weight * set->size;
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

TCheckDecision quality_step(set_id *set, TStep step, int id)
{
	if (set->d.w[id] + step < 0.0 || set->d.w[id] + step > max_weight)
		return tcd_bad;

	TDQuality q[t_max], delta[t_max];
	unsigned char fl[tcd_bad];
	memset(fl, 0, sizeof(unsigned char) * tcd_bad);

	for (int i = 0; i < t_max; i++) {
		// printf("i = %d\n", i);
		q[i] = set->d.q[i] + step * oil[set->id[id]].internal[i];
		delta[i] = q[i] / (set->w_soap + step);
		// printf("delta = %f; set->d.delta[i] = %f\n", delta[i], set->d.delta[i]);
		if (delta[i] == set->d.delta[i])
			fl[tcd_eq]++;
		if (internal[i].min <= delta[i] && delta[i] <= internal[i].max) {
			fl[tcd_ok]++;
			continue;
		}
		if (delta[i] == set->d.delta[i])
			continue;
		if ((delta[i] < internal[i].min && set->d.delta[i] < internal[i].min &&
			delta[i] > set->d.delta[i]) || (delta[i] > internal[i].max && 
			set->d.delta[i] > internal[i].max && delta[i] < set->d.delta[i])) {
			fl[tcd_next]++;
			continue;
		}
		return tcd_bad;
	}

	// printf("ok: tcd_ok = %d; tcd_next = %d\n", fl[tcd_ok], fl[tcd_next]);
	if (fl[tcd_eq] == t_max)
		return tcd_bad;

	memcpy(set->d.delta, delta, sizeof(delta));
	memcpy(set->d.q, q, sizeof(q));
	set->w_soap += step;
	set->d.w[id] += step;
	return (fl[tcd_ok] == t_max) ? tcd_ok : tcd_next;
}

void grad(set_id *set)
{
	TCheckDecision cd = tcd_next;
	init_decision(set);
	quality_set(set);

	TStep step = max_step;
	while (fabs(step) > min_step && cd != tcd_ok) {
		for (int i = 0; i < set->size && cd != tcd_ok; i++)
			while ((cd = quality_step(set, step, i)) == tcd_next);
		step = (-step) / step_delta;
	}

	if (cd == tcd_ok)
		recipe_add(set);
}

#endif