#ifndef GRAD_H
#define GRAD_H

#include "recipe.h"

#define DFNEW 1

void init_decision(set_id *set)
{
	for (int i = 0; i < set->size; i++)
		set->d.w[i] = init_weight;
	set->w_soap = init_weight * set->size;
}

bool quality_check(set_id *set, int i, TFQuality delta)
{
	if (delta < internal[i].min || 
		delta > internal[i].max)
		fl_end = true;

	if ((delta < internal[i].min && set->d.delta[i] < internal[i].min &&
		delta < set->d.delta[i]) ||
		(delta > internal[i].max && set->d.delta[i] > internal[i].max &&
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

#if DFNEW
TCheckDecision quality_step(set_id *set, TStep step, int id)
{
	if (set->d.w[id] + step < 0.0 || set->d.w[id] + step > max_weight)
		return tcd_bad;

	TDQuality q[t_max];
	TFQuality delta[t_max];
	TDecision pd = set->d;
	unsigned char fl[tcd_bad];
	memset(fl, 0, sizeof(unsigned char) * tcd_bad);

	for (int i = 0; i < t_max; i++) {
		// printf("i = %d\n", i);
		q[i] = pd.q[i] + step * oil[set->id[id]].internal[i];
		delta[i] = q[i] / (set->w_soap + step);
		// printf("delta = %f; pd.delta[i] = %f\n", delta[i], pd.delta[i]);
		if (delta[i] == pd.delta[i]) {
			fl[tcd_eq]++;
		}
		if (internal[i].min <= delta[i] && delta[i] <= internal[i].max) {
			fl[tcd_ok]++;
			continue;
		}
		if (delta[i] == pd.delta[i])
			continue;
		if ((delta[i] < internal[i].min && pd.delta[i] < internal[i].min &&
			delta[i] > pd.delta[i]) ||
			(delta[i] > internal[i].max && pd.delta[i] > internal[i].max &&
			delta[i] < pd.delta[i])) {
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
#else
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
	unsigned long iter = 0;

	fl_end = true;
	init_decision(set);
	quality_set(set);
	
	TStep step = max_step;
	while (fabs(step) > min_step) {
		for (int i = 0; i < set->size; i++) {
			if (!fl_end)
				goto finish;
			fl_end = false;
			while (quality_step(set, step, i)) {
				iter++;
				set->w_soap += step;
				set->d.w[i] += step;
				if (!fl_end)
					goto finish;
			}
		}
		step = (-step) / step_delta;
	}

	finish:
	if (!fl_end)
		recipe_add(set);
	// printf("iter = %lu\n", iter);
}
#endif

#endif