#include "option.h"

void print_recipe(set_id *set)
{
	printf("---------------------------------\n");
	printf("weight: %f\n", set->w_soap);
	for (int i = 0; i < set->size; i++)
		printf("%s = %f\n", oil[set->id[i]].name, set->d.w[i]);

	printf("characteristic:\n");
	for (int i = 0; i < t_max; i++)
		printf("h = %f\n", set->d.delta[i]);
}

#define recipe_max 100
int recipe_cur = 0;
set_id recipe[recipe_max];
TStep recipe_delta = 1;

bool recipe_check(set_id *set)
{
	bool fl = true;
	for (int i = 0; i < recipe_cur; i++) {
		fl = true;
		for (int j = 0; j < t_max && fl; j++) {
			if (fabs(recipe[i].d.delta[j] - set->d.delta[j]) > recipe_delta)
				fl = false;
		}
		if (fabs(recipe[i].w_soap - set->w_soap) < recipe_delta && fl)
			return true;
	}
	return false;
}

void recipe_add(set_id *set)
{
	if (!recipe_check(set) && recipe_cur < recipe_max) {
		recipe[recipe_cur] = init_set(set->size);
		if (copy_set(&recipe[recipe_cur], set->id)) {
			recipe[recipe_cur].w_soap = set->w_soap;
			memcpy(recipe[recipe_cur].d.w, set->d.w, set->size * sizeof(TWeight));
			memcpy(recipe[recipe_cur].d.q, set->d.q, t_max * sizeof(TDQuality));
			memcpy(recipe[recipe_cur].d.delta, set->d.delta, t_max * sizeof(TFQuality));
			recipe_cur++;
		} else
			printf("error add recipe\n");
	}
}

void recipe_clear()
{
	for (int i = 0; i < recipe_cur; i++)
		free_set(&recipe[i]);
}

void recipe_print_all()
{
	printf("recipe_cur = %d\n", recipe_cur);
	// for (int i = 0; i < recipe_cur; i++)
	// 	print_recipe(&recipe[i]);
}