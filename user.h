#include "optim.h"

bool io_system(Oil_Data *data)
{
	int count = 0;
	printf("Input count of oil\n");
	scanf("%d", &count);

	if (!init_data_oil(data, count))
		return false;

	print_iol();

	int i = 0;
	for (; i < data->size; i++) {
		scanf("%d", &count);
		if (count < 0 || count >= oil_count)
			break;
		data->oil[i] = oil[count];
	}
	return data->size == i;
}

void user()
{
	Oil_Data data = {
		.weight = NULL,
		.delta = NULL,
		.oil = NULL,
		.size = 0,
	};
	if (io_system(&data))
		optim(&data);
	
	if (data.weight)
		free(data.weight);
	if (data.oil)
		free(data.oil);
	if (data.delta)
		free(data.delta);
}
