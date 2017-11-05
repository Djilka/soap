#include "check.h"

static
bool init_data_oil(Oil_Data *data, int size)
{
	data->oil = malloc(sizeof(Oil)*size);
	data->size = size;
	return data->oil != NULL;
}

void optim(Oil_Data *data);