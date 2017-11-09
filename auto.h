#include "grad.h"

int compare(const void *a, const void *b)
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

	for (int i = len_id - 1; i >= 0 && id[i] >= max_id; i--) {
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

bool corrected(set_id *set, int size, char *list[])
{
	unsigned int id[size];
	str2int(size, list, id);

	qsort(id, size, sizeof(int), compare);

	int len_id = remove_lake(size, id);

	if (len_id > 1) {
		(*set) = init_set(len_id);
		return copy_set(set, id);
	}

	return false;
}

bool is_used_id(TIdOil id, TIdOil *used_id, int index)
{
	for (int j = 0; j <= index - 1; j++)
		if (used_id[j] == id)
			return true;
	return false;
}

void change_set(set_id *set, TIdOil *id, TIdOil *used_id, int index)
{
	if (index == set->size)
		grad(set);
	else {
		for (int i = 0; i < set->size; i++) {
			if (is_used_id(id[i], used_id, index))
				continue;
			
			set->id[index] = id[i];
			used_id[index] = id[i];
			change_set(set, id, used_id, index + 1);
		}
	}
}

void range_set(set_id *set)
{
	TIdOil id[set->size], used_id[set->size];
	memcpy(id, set->id, sizeof(TIdOil) * set->size);
	change_set(set, id, used_id, 0);
	// grad(set);
	recipe_print_all();
	recipe_clear();
}

void auto_range(int size, char *list[])
{
	set_id set;
	if (!corrected(&set, size, list))
		return;

	range_set(&set);
	free_set(&set);
}