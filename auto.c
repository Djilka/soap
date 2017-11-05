



int compare(const void * a, const void * b)
{
  return ( *(unsigned int*)a - *(unsigned int*)b );
}

void str2int(int size, char *list[], unsigned int *id)
{
	for (int i = 0; i < size; i++)
		id[i] = atoi(list[i]);
}

int remove_lake(int size, unsigned int *id)
{
	int len_id = size;
	int max_id = oil_get_count();

	for (int i = len_id-1; i >= 0 && id[i] < max_id; i--) {
		len_id--;
	}

	int i = 0;
	while (++i < len_id) {
		if (id[i-1] == id[i]) {
			len_id--;
			memcpy(&id[i], &id[i+1], len_id);
		}
	}

	return len_id;
}

bool corrected(set_id *set)
{
	unsigned int id[size];
	str2int(size, list, id);

	qsort(id, size, sizeof(int), compare);

	int len_id = remove_lake(size, id);

	if (len_id > 1) {
		(*set) = init_set(len_id);
		return (NULL != set.id);
	}

	return false;
}

// void index_set(int index, set_id set, Oil_Data *data)
// {
// 	if (index == set.size) {
// 		optim(data);
// 		return;
// 	}

// 	bool fexsis = false;
// 	for (int i = 0; i < set.size; i++) {
// 		for (int j = 0; j < index; j++)
// 			if (data->oil[j].name == oil[set.id[i]].name) {
// 				fexsis = true;
// 				break;
// 			}
// 		if (fexsis) {
// 			fexsis = false;
// 			continue;
// 		}
// 		data->oil[index] = oil[set.id[i]];
// 		index_set(index + 1, set, data);
// 	}
// }

void range_set(set_id set)
{
	// Oil_Data data = {
	// 	.weight = NULL,
	// 	.delta = NULL,
	// 	.oil = NULL,
	// 	.size = 0,
	// };
	// if (!init_data_oil(&data, set.size))
	// 	return;
	
	// index_set(0, set, &data);

	// if (data.weight) 	free(data.weight);
	// if (data.oil) 		free(data.oil);
	// if (data.delta) 	free(data.delta);
}

void auto_range(int size, char *list[])
{
	printf("auto_range: size = %d\n", size);

	set_id set;
	if (!corrected(&set))
		return;

	range_set(set);
	free_set(&set);
}