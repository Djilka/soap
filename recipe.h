#include "option.h"

typedef struct Oil_Data {
	int 	*delta;
	Oil 	*oil;
	int 	*weight;
	int 	size;
}Oil_Data;

#if D_USER
static 
void print_recipe(Oil_Data *data)
{
	int weight = 0;

	for (int i = 0; i < data->size; i++) {
		weight += data->weight[i];
	}

	for (int i = 0; i < t_max; i++) {
		int item = 0;
		for (int j = 0; j < data->size; j++) {
			item += data->weight[j]*data->oil[j].internal[i];
		}
		item = item/weight;
		if ((i == 0 && item < 33) || 
			(i == 3 && item > 40) || 
			(i == 5 && item > 70))
			return;
	}

	weight = 0;

	printf("---------------------------------\n");
	for (int i = 0; i < data->size; i++) {
		printf("%s = %d\n", data->oil[i].name, data->weight[i]);
		weight += data->weight[i];
	}

	printf("characteristic:\n");
	for (int i = 0; i < t_max; i++) {
		int item = 0;
		for (int j = 0; j < data->size; j++) {
			item += data->weight[j]*data->oil[j].internal[i];
		}
		item = item/weight;
		printf("h = %d\n", item);
	}
}
#endif

static 
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

typedef struct list_recipe {
	int 	size;
	int 	*weight;
	Oil 	*oil;
}list_recipe;

static int max_recipe = 255;
static list_recipe recipe;