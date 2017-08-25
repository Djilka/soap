#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "oil.h"

static int *optim_weight = NULL;
struct Oil_Data {
	int 	*delta;
	Oil 	*oil;
	int 	*weight;
	int 	size;
};
typedef struct Oil_Data Oil_Data;

extern int all_weight;

static void print_recipe(Oil_Data *data)
{
	int weight = 0;

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