#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "optim.h"

bool init_data_oil(Oil_Data *data, int size)
{
	data->oil = malloc(sizeof(Oil)*size);
	data->size = size;
	return data->oil != NULL;
}

// void print_iol()
// {
// 	int i = 0;
// 	for (; i + 1 < oil_count; i += 2) {
// 		printf("%d. %s \t %d. %s \n", i, oil[i].name, 
// 			i + 1, oil[i + 1].name);
// 	}
// 	if (i == oil_count - 1)
// 		printf("%d. %s\n", i, oil[i].name); 
// }

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

// void auto_item(int *list, int index, int max_index)
// {
// 	int i = index;
// 	for (; i < max_index; i++) {
		
// 	}

// }

void auto_user(int argc, char *argv[])
{
	int max_oil = argc-1;
	int oil[max_oil];
	
	// int i = 1;
	// for (; i < argc; i++) {
	// 	itoa(oil[i-1], argv[i], 10);
	// }

	// for (i = 0; i < max_oil; i++) {

	// }
}

int main(int argc, char *argv[])
{
	oil_auto_init();
	if (argc == 1)
		user();
	else {
		auto_user(argc, argv);
	}

	oil_clear();
	return 0;
}