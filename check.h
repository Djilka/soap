#include "recipe.h"

static int *optim_weight = NULL;
extern int all_weight;

static bool check_item(int item, int index)
{
	return ((normal_oil.internal[index].min <= item) 
		&& (item <= normal_oil.internal[index].max));
}

static bool check_nomal(Oil_Data *data)
{
	int balance = 0;
	int weight = 0;

	for (int j = 0; j < data->size; j++) 
		weight += data->weight[j];

	for (int i = 0; i < t_max; i++) {
		int item = 0;
		for (int j = 0; j < data->size; j++) {
			item += data->weight[j]*data->oil[j].internal[i];
		}
		item = item/weight;
		// printf("h = %d\n", item);
		balance += item;
		if (!check_item(item, i))
			return false;
	}
	return (abs(normal_oil.balance - balance) <= normal_oil.delta );
}